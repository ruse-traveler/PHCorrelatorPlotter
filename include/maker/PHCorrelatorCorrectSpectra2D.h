/// ===========================================================================
/*! \file    PHCorrelatorCorrectSpectra2D.h
 *  \authors Derek Anderson
 *  \date    04.27.2025
 *
 *  PlotMaker routine to plot various 2D spectra.
 */
/// ===========================================================================

#ifndef PHCORRELATORCORRECTSPECTRA2D_H
#define PHCORRELATORCORRECTSPECTRA2D_H

// c++ utilities
#include <algorithm>
#include <cassert>
#include <iostream>
// root libraries
#include <TCanvas.h>
#include <TFile.h>
#include <TH1.h>
#include <TLegend.h>
#include <TPaveText.h>
// plotting utilities
#include "PHCorrelatorBaseRoutine.h"
#include "PHCorrelatorCorrectSpectra1D.h"
#include "PHCorrelatorPlotMakerDefault.h"
#include "PHCorrelatorPlotMakerTools.h"
#include "PHCorrelatorPlotMakerTypes.h"
#include "../elements/PHCorrelatorPlotterElements.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! 2D Spectra Correction Routine
  // ==========================================================================
  /*! Routine to correct various 2D spectra, and plot
   *  the corrected spectra, their correction factors,
   *  and their ratio to the generator-level spectra
   *  used for correction.
   */
  class CorrectSpectra2D : public BaseRoutine {

    public:

      // ======================================================================
      //! Parameters for correcting 2D spectra (same as 1D routine)
      // ======================================================================
      typedef CorrectSpectra1D::Params Params;

    private:

      // members
      Params m_params;

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Params GetParams() const {return m_params;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetParams(const Params& params) {m_params = params;}

      // ----------------------------------------------------------------------
      //! Correct various 2D spectra
      // ----------------------------------------------------------------------
      /*! Calculates and applies a bin-by-bin correction to a variety of ENC
       *  (or otherwise) spectra from different sources and their ratios. Upper
       *  panel shows corrected spectra vs truth, and lwer panel shows
       *  correction factors.
       *
       *  \param[out] ofile file to write to
       */
      void Plot(TFile* ofile) const {

        // announce start
        std::cout << "\n -------------------------------- \n"
                  << "  Beginning 2D spectra correction!\n"
                  << "    Opening inputs:"
                  << std::endl;

        // throw error if no. of reco vs. truth inputs don't match
        if (m_params.recon.size() != m_params.truth.size()) {
          std::cerr << "PANIC: number of reconstructed and truth inputs should be the same!\n"
                    << "       reco inputs = " << m_params.recon.size() << "\n"
                    << "       true inputs = " << m_params.truth.size()
                    << std::endl;
          assert(m_params.recon.size() == m_params.truth.size());
        }

        // throw error if no. of data vs. reco inputs don't match
        if (m_params.data.size() != m_params.recon.size()) {
          std::cerr << "PANIC: number of raw and reconstructed inputs should be the same!\n"
                    << "       data inputs = " << m_params.data.size() << "\n"
                    << "       reco inputs = " << m_params.recon.size()
                    << std::endl;
          assert(m_params.data.size() == m_params.recon.size());
        }

        // open data inputs
        std::vector<TFile*> dfiles;
        std::vector<TH2*>   dhists;
        for (std::size_t idat = 0; idat < m_params.data.size(); ++idat) {

          dfiles.push_back(
            Tools::OpenFile(m_params.data[idat].file, "read")
          );
          dhists.push_back(
            (TH2*) Tools::GrabObject( m_params.data[idat].object, dfiles.back() )
          );
          dhists.back() -> SetName( m_params.data[idat].rename.data() );
          dhists.back() -> SetTitle( m_params.data[idat].legend.data() );
          std::cout << "      File (data) = " << m_params.data[idat].file << "\n"
                    << "      Hist (data) = " << m_params.data[idat].object
                    << std::endl;
        }  // end data loop

        // open reco inputs
        std::vector<TFile*> rfiles;
        std::vector<TH2*>   rhists;
        for (std::size_t irec = 0; irec < m_params.recon.size(); ++irec) {

          rfiles.push_back(
            Tools::OpenFile(m_params.recon[irec].file, "read")
          );
          rhists.push_back(
            (TH2*) Tools::GrabObject( m_params.recon[irec].object, rfiles.back() )
          );
          rhists.back() -> SetName( m_params.recon[irec].rename.data() );
          rhists.back() -> SetTitle( m_params.recon[irec].legend.data() );
          std::cout << "      File (recon) = " << m_params.recon[irec].file << "\n"
                    << "      Hist (recon) = " << m_params.recon[irec].object
                    << std::endl;

          // normalize reco if need be
          if (m_params.options.do_norm) {
            Tools::NormalizeByIntegral(
              rhists.back(),
              m_params.options.norm_to,
              m_params.options.norm_range.GetX().first,
              m_params.options.norm_range.GetX().second
            );
          }
        }  // end reco loop

        // open true inputs
        std::vector<TFile*> tfiles;
        std::vector<TH2*>   thists;
        for (std::size_t itru = 0; itru < m_params.truth.size(); ++itru) {

          tfiles.push_back(
            Tools::OpenFile(m_params.truth[itru].file, "read")
          );
          thists.push_back(
            (TH2*) Tools::GrabObject( m_params.truth[itru].object, tfiles.back() )
          );
          thists.back() -> SetName( m_params.truth[itru].rename.data() );
          thists.back() -> SetTitle( m_params.truth[itru].legend.data() );
          std::cout << "      File (truth) = " << m_params.truth[itru].file << "\n"
                    << "      Hist (truth) = " << m_params.truth[itru].object
                    << std::endl;

          // normalize true if need be
          if (m_params.options.do_norm) {
            Tools::NormalizeByIntegral(
              thists.back(),
              m_params.options.norm_to,
              m_params.options.norm_range.GetX().first,
              m_params.options.norm_range.GetX().second
            );
          }
        }  // end true loop

        // calculate correction factors
        std::vector<TH2*> chists;
        for (std::size_t itru = 0; itru < thists.size(); ++itru) {

          // create name
          std::string name( thists[itru] -> GetName() );
          name += "_CorrectionFactor";

          // do division
          chists.push_back( Tools::DivideHist2D(rhists[itru], thists[itru]) );
          chists.back() -> SetName( name.data() );
          chists.back() -> SetTitle( "Correction Factors" );
        }
        std::cout << "    Calculated correction factors." << std::endl;

        // apply correction factors
        for (std::size_t idat = 0; idat < dhists.size(); ++idat) {

          // create name
          std::string name( dhists[idat] -> GetName() );
          name += "_Corrected";

          // divide by (reco / true)
          dhists[idat] = Tools::DivideHist2D( dhists[idat], chists[idat] );
          dhists[idat] -> SetName( name.data() );
          dhists[idat] -> SetTitle( m_params.data[idat].legend.data() );

          // normalize corrected spectrum if need be
          if (m_params.options.do_norm) {
            Tools::NormalizeByIntegral(
              dhists[idat],
              m_params.options.norm_to,
              m_params.options.norm_range.GetX().first,
              m_params.options.norm_range.GetX().second
            );
          }
        }
        std::cout << "    Applied correction factors." << std::endl;

        // calculate corrected / truth ratios ('f' for "fraction")
        std::vector<TH2*> fhists;
        for (std::size_t idat = 0; idat < dhists.size(); ++idat) {

          // create name
          std::string name( m_params.data[idat].rename );
          name += "_CorrectOverTruth";

          // do division
          fhists.push_back( Tools::DivideHist2D(dhists[idat], thists[idat]) );
          fhists.back() -> SetName( name.data() );
          fhists.back() -> SetTitle( "Corrected / Truth" );
        }
        std::cout << "    Calculated corrected / truth ratios." << std::endl;

        // determine no. of legend lines
        const std::size_t nlines = !m_params.options.header.empty()
                                 ? dhists.size() + thists.size() + 1
                                 : dhists.size() + thists.size();

        // create root objects
        TPaveText* text = m_textBox.MakeTPaveText();
        std::cout << "    Created legend and text box." << std::endl;

        // set styles
        Type::Styles dat_styles = GenerateStyles( m_params.data );
        Type::Styles tru_styles = GenerateStyles( m_params.truth );
        for (std::size_t idat = 0; idat < dhists.size(); ++idat) {

          // set data styles
          dat_styles[idat].SetPlotStyle( m_params.data[idat].style );
          dat_styles[idat].Apply( dhists[idat] );
          m_params.options.plot_range.Apply(Range::X, dhists[idat] -> GetXaxis());
          m_params.options.plot_range.Apply(Range::Y, dhists[idat] -> GetYaxis());

          // set truth styles
          tru_styles[idat].SetPlotStyle( m_params.truth[idat].style );
          tru_styles[idat].Apply( thists[idat] );
          m_params.options.plot_range.Apply(Range::X, thists[idat] -> GetXaxis());
          m_params.options.plot_range.Apply(Range::Y, thists[idat] -> GetYaxis());

          // set correction factor styles
          dat_styles[idat].Apply( chists[idat] );
          m_params.options.plot_range.Apply(Range::X, chists[idat] -> GetXaxis());

          // set ratio styles
          tru_styles[idat].Apply( fhists[idat] );
          m_params.options.plot_range.Apply(Range::X, fhists[idat] -> GetXaxis()); 
        }

        // set text styles
        m_baseTextStyle.Apply( text );
        std::cout << "    Set styles." << std::endl;

        // initialize canvas manager
        CanvasManager manager = CanvasManager( m_params.options.canvas );
        manager.MakePlot();

        // throw error if not enough pads are present for histograms
        if (manager.GetTPads().size() < (3 * dhists.size())) {
          std::cerr << "PANIC: more histograms to draw than pads in " << manager.GetTCanvas() -> GetName() << "!" << std::endl;
          assert(manager.GetTPads().size() >= (3 * dhists.size()));
        }

        // draw objects
     
        manager.Draw();
        for (std::size_t ihst = 0; ihst < dhists.size(); ++ihst) {

          // draw corrected
          manager.GetTPad( ihst ) -> cd();
          dhists[ihst] -> Draw("colz");

          // draw correction factor
          manager.GetTPad( ihst + chists.size() ) -> cd();
          chists[ihst] -> Draw("colz");

          // draw ratio
          manager.GetTPad( ihst + (2 * chists.size()) ) -> cd();
          fhists[ihst] -> Draw("colz");
        }
        manager.GetTPads().back() -> cd();
        text -> Draw();
        std:: cout << "    Made plot." << std::endl;

        // save output
        ofile -> cd();
        for (std::size_t idat = 0; idat < dhists.size(); ++idat) {
          dhists[idat] -> Write();
          rhists[idat] -> Write();
          thists[idat] -> Write();
          chists[idat] -> Write();
          fhists[idat] -> Write();
        }
        manager.Write();
        manager.Close();
        std::cout << "    Saved output." << std::endl;

        // announce end
        std::cout << "  Finished 2D spectra correction!\n"
                  << " -------------------------------- \n"
                  << std::endl;

        // exit routine
        Tools::CloseFiles(dfiles);
        Tools::CloseFiles(rfiles);
        Tools::CloseFiles(tfiles);
        return;

      }  // end 'Plot(TFile*)'

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      CorrectSpectra2D()  {};
      ~CorrectSpectra2D() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      explicit CorrectSpectra2D(const Style& plot, const Style& text, const TextBox& box)
        : BaseRoutine(plot, text, box) {};

  };  // end CorrectSpectra2D

}    // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================
