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
#include <string>
// root libraries
#include <TFile.h>
#include <TH1.h>
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
