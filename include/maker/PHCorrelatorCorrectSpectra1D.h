/// ===========================================================================
/*! \file    PHCorrelatorCorrectSpectra1D.h
 *  \authors Derek Anderson
 *  \date    04.27.2025
 *
 *  PlotMaker routine to plot various 1D spectra.
 */
/// ===========================================================================

#ifndef PHCORRELATORCORRECTSPECTRA1D_H
#define PHCORRELATORCORRECTSPECTRA1D_H

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
#include "PHCorrelatorPlotMakerTypes.h"
#include "../elements/PHCorrelatorPlotterElements.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! 1D Spectra Correction Routine
  // ==========================================================================
  /*! Routine to correct various 1D spectra, and plot
   *  the corrected spectra, their correction factors,
   *  and their ratio to the generator-level spectra
   *  used for correction.
   */
  class CorrectSpectra1D : public BaseRoutine {

    public:

      // ======================================================================
      //! Parameters for correcting 1D spectra
      // ======================================================================
      /*! Struct to consolidate parameters for the "CorrectSpectra1D"
       *  plotting routine.
       */ 
      struct Params {

        // members
        Inputs    data;     ///!< spectra to be corrected (e.g. data)
        Inputs    recon;    ///!< numerators for correction factors (e.g. reco-level sim)
        Inputs    truth;    ///!< denominators for correct factors (e.g. truth-level sim)
        PlotShape unity;    ///!< definition of unit ratio line to draw
        Shapes    shapes;   ///!< additional shapes (e.g. lines) to draw
        PlotOpts  options;  ///!< auxilliary plot options

        // --------------------------------------------------------------------
        //! default ctor
        // --------------------------------------------------------------------
        Params() {
          data    = Inputs();
          recon   = Inputs();
          truth   = Inputs();
          unity   = PlotShape();
          shapes  = Shapes();
          options = PlotOpts();
        }

        // --------------------------------------------------------------------
        //! default dtor
        // --------------------------------------------------------------------
        ~Params() {};

        // --------------------------------------------------------------------
        //! ctor accepting arguments
        // --------------------------------------------------------------------
        Params(
          const Inputs& data_args,
          const Inputs& reco_args,
          const Inputs& true_args,
          const PlotShape& unity_arg,
          const Shapes& shape_args,
          const PlotOpts&  opt_args
        ) {
          data    = data_args;
          recon   = reco_args;
          truth   = true_args;
          unity   = unity_arg;
          shapes  = shape_args;
          options = opt_args;
        }  // end ctor(Inputs& x 3, PlotShape&, Shapes&, PlotOpts&)

      };  // end Params

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
      //! Correct various 1D spectra
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
                  << "  Beginning 1D spectra correction!\n"
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
        std::vector<TH1*>   dhists;
        for (std::size_t idat = 0; idat < m_params.data.size(); ++idat) {

          dfiles.push_back(
            Tools::OpenFile(m_params.data[idat].file, "read")
          );
          dhists.push_back(
            (TH1*) Tools::GrabObject( m_params.data[idat].object, dfiles.back() )
          );
          dhists.back() -> SetName( m_params.data[idat].rename.data() );
          std::cout << "      File (data) = " << m_params.data[idat].file << "\n"
                    << "      Hist (data) = " << m_params.data[idat].object
                    << std::endl;
        }  // end data loop

        // open reco inputs
        std::vector<TFile*> rfiles;
        std::vector<TH1*>   rhists;
        for (std::size_t irec = 0; irec < m_params.recon.size(); ++irec) {

          rfiles.push_back(
            Tools::OpenFile(m_params.recon[irec].file, "read")
          );
          rhists.push_back(
            (TH1*) Tools::GrabObject( m_params.recon[irec].object, rfiles.back() )
          );
          rhists.back() -> SetName( m_params.recon[irec].rename.data() );
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
        std::vector<TH1*>   thists;
        for (std::size_t itru = 0; itru < m_params.truth.size(); ++itru) {

          tfiles.push_back(
            Tools::OpenFile(m_params.truth[itru].file, "read")
          );
          thists.push_back(
            (TH1*) Tools::GrabObject( m_params.truth[itru].object, tfiles.back() )
          );
          thists.back() -> SetName( m_params.truth[itru].rename.data() );
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
        std::vector<TH1*> chists;
        for (std::size_t itru = 0; itru < thists.size(); ++itru) {

          // create name
          std::string name( thists[itru] -> GetName() );
          name += "_CorrectionFactor";

          // do division
          chists.push_back( Tools::DivideHist1D(rhists[itru], thists[itru]) );
          chists.back() -> SetName( name.data() );
        }
        std::cout << "    Calculated correction factors." << std::endl;

        // apply correction factors
        for (std::size_t idat = 0; idat < dhists.size(); ++idat) {

          // create name
          std::string name( dhists[idat] -> GetName() );
          name += "_Corrected";

          // divide by (reco / true)
          dhists[idat] = Tools::DivideHist1D( dhists[idat], chists[idat] );
          dhists[idat] -> SetName( name.data() );

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
        std::vector<TH1*> fhists;
        for (std::size_t idat = 0; idat < dhists.size(); ++idat) {

          // create name
          std::string name( m_params.data[idat].rename );
          name += "_CorrectOverTruth";

          // do division
          fhists.push_back( Tools::DivideHist1D(dhists[idat], thists[idat]) );
          fhists.back() -> SetName( name.data() );
        }
        std::cout << "    Calculated corrected / truth ratios." << std::endl;

        // determine no. of legend lines
        const std::size_t nlines = !m_params.options.header.empty()
                                 ? dhists.size() + thists.size() + 1
                                 : dhists.size() + thists.size();

        // define legend dimensions
        const float spacing   = m_baseTextStyle.GetTextStyle().spacing;
        const float legheight = Tools::GetHeight(nlines, spacing);

        // generate legend vertices
        Type::Vertices vtxleg;
        vtxleg.push_back(0.3);
        vtxleg.push_back(0.1);
        vtxleg.push_back(0.5);
        vtxleg.push_back((float) 0.1 + legheight);

        // define legend
        //   - FIXME option should be configurable
        Legend legdef;
        for (std::size_t idat = 0; idat < dhists.size(); ++idat) {
          legdef.AddEntry( Legend::Entry(dhists[idat], m_params.data[idat].legend,  "PF") );
          legdef.AddEntry( Legend::Entry(thists[idat], m_params.truth[idat].legend, "PF") );
        }
        legdef.SetVertices( vtxleg );
        if (!m_params.options.header.empty()) {
          legdef.SetHeader( m_params.options.header );
        }

        // determine relevant range to draw line
        Shape unitydef = m_params.unity.shape;
        unitydef.SetXRange(
          Tools::GetDrawRange( m_params.options.plot_range.GetX(), chists.front() -> GetXaxis() )
        );

        // create root objects
        TLine*     unity  = unitydef.MakeTLine();
        TLegend*   legend = legdef.MakeLegend();
        TPaveText* text   = m_textBox.MakeTPaveText();
        std::cout << "    Created legend and text box." << std::endl;

        // set styles
        Styles dat_styles = GenerateStyles( m_params.data );
        Styles tru_styles = GenerateStyles( m_params.truth );
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

        // set legend/text styles
        m_params.unity.style.Apply( unity );
        m_baseTextStyle.Apply( legend );
        m_baseTextStyle.Apply( text );
        std::cout << "    Set styles." << std::endl;

        // initialize canvas manager
        CanvasManager manager = CanvasManager( m_params.options.canvas );
        manager.MakePlot();

        // scale text of objects in smaller panels
        for (std::size_t icor = 0; icor < chists.size(); ++icor) {

          // scale correction factors
          manager.ScaleAxisText(
            m_params.options.spectra_pad,
            m_params.options.correct_pad,
            Range::X,
            chists[icor] -> GetXaxis()
          );
          manager.ScaleAxisText(
            m_params.options.spectra_pad,
            m_params.options.correct_pad,
            Range::Y,
            chists[icor] -> GetYaxis()
          );

          // scale ratios
          manager.ScaleAxisText(
            m_params.options.spectra_pad,
            m_params.options.ratio_pad,
            Range::X,
            fhists[icor] -> GetXaxis()
          );
          manager.ScaleAxisText(
            m_params.options.spectra_pad,
            m_params.options.ratio_pad,
            Range::Y,
            fhists[icor] -> GetYaxis()
          );
        }

        // draw objects
        //   - FIXME option should be configurable
        manager.Draw();
        manager.GetTPad( m_params.options.correct_pad ) -> cd();
        chists[0] -> Draw("hist");
        for (std::size_t icor = 1; icor < chists.size(); ++icor) {
          chists[icor] -> Draw("hist same");
        }
        unity -> Draw();
        manager.GetTPad( m_params.options.ratio_pad ) -> cd();
        fhists[0] -> Draw();
        for (std::size_t irat = 1; irat < fhists.size(); ++irat) {
          fhists[irat] -> Draw("same");
        }
        unity -> Draw();
        manager.GetTPad( m_params.options.spectra_pad ) -> cd();
        dhists[0] -> Draw();
        thists[0] -> Draw("hist same");
        for (std::size_t idat = 1; idat < dhists.size(); ++idat) {
          dhists[idat] -> Draw("same");
          thists[idat] -> Draw("hist same");

        }
        legend -> Draw();
        text   -> Draw();
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
        std::cout << "  Finished 1D spectra correction!\n"
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
      CorrectSpectra1D()  {};
      ~CorrectSpectra1D() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      explicit CorrectSpectra1D(const Style& plot, const Style& text, const TextBox& box)
        : BaseRoutine(plot, text, box) {};

  };  // end CorrectSpectra1D

}    // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================
