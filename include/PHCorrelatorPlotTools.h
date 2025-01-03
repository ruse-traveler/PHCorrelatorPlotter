/// ===========================================================================
/*! \file    PHCorrelatorPlotTools.h
 *  \authors Derek Anderson
 *  \date    12.26.2024
 *
 *  Useful tools related to plotting.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTTOOLS_H
#define PHCORRELATORPLOTTOOLS_H

// c++ utilities
#include <limits>
#include <cassert>
#include <cmath>
#include <string>
// root libraries
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TObject.h>



namespace PHEnergyCorrelator {
  namespace Tools {

    // ------------------------------------------------------------------------
    //! Normalize a histogram by integral
    // ------------------------------------------------------------------------
    void NormalizeByIntegral(
      TH1* hist,
      const double norm = 1.0,
      const double start = -1. * std::numeric_limits<double>::max(),
      const double stop = std::numeric_limits<double>::max()
    ) {

      // calculate integral over provided range
      const int    istart   = hist -> FindBin(start);
      const int    istop    = hist -> FindBin(stop);
      const double integral = hist -> Integral(istart, istop);

      // apply if nonzero
      if (integral > 0.) hist -> Scale(norm / integral);
      return;

    }  // end 'NormalizeByIntegral(TH1*, double, double)'



    // ------------------------------------------------------------------------
    //! Helper method to calculate a height based on line spacing
    // ------------------------------------------------------------------------
    float GetHeight(
      const std::size_t nlines,
      const float spacing,
      const float off = 0.0
    ) {

      float height = (nlines * spacing) + off;
      return height;

    }  // end 'GetHeight(std::size_t, float x 2)'



    // ------------------------------------------------------------------------
    //! Divide two TH1s
    // ------------------------------------------------------------------------
    TH1* DivideHist1D(TH1* in_numer, TH1* in_denom, const double wnum = 1.0, const double wden = 1.0) {

      // grab inputs, create histogram to
      // hold result
      TH1* numer = (TH1*) in_numer -> Clone();
      TH1* denom = (TH1*) in_denom -> Clone();
      TH1* ratio = (TH1*) in_denom -> Clone();
      ratio -> Reset("ICE");

      // try automatic division
      const bool isGoodDiv = ratio -> Divide(numer, denom, wnum, wden);

      // if failed, do manual calculation
      if (!isGoodDiv) {

        // scale inputs
        numer -> Scale(wnum);
        denom -> Scale(wden);

        // loop through denominator bins
        const std::size_t ndenx = denom -> GetNbinsX();
        for (std::size_t idenx = 1; idenx < ndenx; ++idenx) {

          // find closest numerator bin
          const double      xden  = denom -> GetBinCenter(idenx);
          const std::size_t inumx = numer -> FindBin(xden);

          // grab content of dividends
          const double valnum = numer -> GetBinContent(inumx);
          const double valden = denom -> GetBinContent(idenx);
          const double errnum = numer -> GetBinError(inumx);
          const double errden = denom -> GetBinError(idenx);
          const double pernum = errnum / valnum;
          const double perden = errden / valden;

          // take ratios
          const double valrat = valnum / valden;
          const double errrat = valrat * sqrt((pernum * pernum) + (perden * perden));
          ratio -> SetBinContent(idenx, valrat);
          ratio -> SetBinError(idenx, errrat);
        }
      }
      return ratio;

    }  // end 'DivideHist1D(TH1*, TH1*, double, double)'



    // ------------------------------------------------------------------------
    //! Divide two TH2s
    // ------------------------------------------------------------------------
    TH1* DivideHist2D(TH2* in_numer, TH2* in_denom, const double wnum = 1.0, const double wden = 1.0) {

      // grab inputs, create histogram to
      // hold result
      TH2* numer = (TH2*) in_numer -> Clone();
      TH2* denom = (TH2*) in_denom -> Clone();
      TH2* ratio = (TH2*) in_denom -> Clone();
      ratio -> Reset("ICE");

      // try automatic division
      const bool isGoodDiv = ratio -> Divide(numer, denom, wnum, wden);

      // if failed, do manual calculation
      if (!isGoodDiv) {

        // scale inputs
        numer -> Scale(wnum);
        denom -> Scale(wden);

        // loop through denominator bins
        const std::size_t ndenx = denom -> GetNbinsX();
        const std::size_t ndeny = denom -> GetNbinsY();
        for (std::size_t idenx = 1; idenx < ndenx; ++idenx) {
          for (std::size_t ideny = 1; ideny < ndeny; ++ideny) {

            // find closest numerator bin
            const double      xden  = denom -> GetXaxis() -> GetBinCenter(idenx);
            const double      yden  = denom -> GetYaxis() -> GetBinCenter(ideny);
            const std::size_t inumx = numer -> GetXaxis() -> FindBin(xden);
            const std::size_t inumy = numer -> GetYaxis() -> FindBin(yden);

            // grab content of dividends
            const double valnum = numer -> GetBinContent(inumx, inumy);
            const double valden = denom -> GetBinContent(idenx, ideny);
            const double errnum = numer -> GetBinError(inumx, inumy);
            const double errden = denom -> GetBinError(idenx, ideny);
            const double pernum = errnum / valnum;
            const double perden = errden / valden;

            // take ratios
            const double valrat = valnum / valden;
            const double errrat = valrat * sqrt((pernum * pernum) + (perden * perden));
            ratio -> SetBinContent(idenx, ideny, valrat);
            ratio -> SetBinError(idenx, ideny, errrat);
          }  // end y bin loop
        }  // end x bin loop
      }
      return ratio;

    }  // end 'DivideHist2D(TH2*, TH2*, double, double)'



    // ------------------------------------------------------------------------
    //! Open file and check if good
    // ------------------------------------------------------------------------
    TFile* OpenFile(const std::string& name, const std::string &option) {

      // try to open file, throw error if not able
      TFile* file = new TFile( name.data(), option.data() );
      if (!file) {
        std::cerr << "PANIC: couldn't open file!\n"
                  << "       file = " << name << "\n"
                  << std::endl;
        assert(file);
      }

      // then check file by cd'ing into it
      const bool isGoodCD = file -> cd();
      if (!isGoodCD) {
        std::cerr << "PANIC: couldn't cd into file!\n"
                  << "       file = " << name << "\n"
                  << std::endl;
        assert(isGoodCD);
      }
      return file;

    }  // end 'OpenFile(std::string&, std::string&)'



    // ------------------------------------------------------------------------
    //! Grab an object from a file
    // ------------------------------------------------------------------------
    TObject* GrabObject(const std::string& object, TFile* file) {

      // try to grab object from file, throw error if not able
      TObject* grabbed = (TObject*) file -> Get( object.data() );
      if (!grabbed) {
        std::cerr << "PANIC: couldn't grab object!\n"
                  << "       file   = " << file   << "\n"
                  << "       object = " << object << "\n"
                  << std::endl;
        assert(grabbed);
      }
      return grabbed;

    }  // end 'GrabObject(std::string&, TFile*)'

  }  // end Tools namespace
}  // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
