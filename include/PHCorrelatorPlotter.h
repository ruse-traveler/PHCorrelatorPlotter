/// ===========================================================================
/*! \file    PHCorrelatorPlotter.h
 *  \authors Derek Anderson
 *  \date    11.12.2024
 *
 *  Driver class to consolidate plotting routines associated with
 *  the PHENIX ENC analysis.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTTER_H
#define PHCORRELATORPLOTTER_H

// c++ utilities
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
// root libraries
#include <TCanvas.h>
#include <TFile.h>
#include <TH1.h>
#include <TLegend.h>
// plotting utilities
#include "PHCorrelatorLegend.h"
#include "PHCorrelatorPlotInput.h"
#include "PHCorrelatorPlotManager.h"
#include "PHCorrelatorPlotTools.h"
#include "PHCorrelatorPlotTypes.h"
#include "PHCorrelatorRange.h"
#include "PHCorrelatorStyle.h"
#include "PHCorrelatorTextBox.h"

// useful aliases
typedef std::vector<PHEnergyCorrelator::PlotInput> Inputs;
typedef std::vector<PHEnergyCorrelator::Style> Styles;



namespace PHEnergyCorrelator {

  // ============================================================================
  //! ENC Plotter
  // ============================================================================
  /*! This class consolidates plotting routines associated
   *  with the PHENIX ENC analysis.
   */
  class PHCorrelatorPlotter {

    private:

      // members
      Style   m_basePlotStyle;
      Style   m_baseTextStyle;
      TextBox m_textBox;

      // ----------------------------------------------------------------------
      //! Generate list of styles to be applied
      // ----------------------------------------------------------------------
      Styles GenerateStyles(const Inputs& inputs) const {

        // fill styles with base
        Styles styles( inputs.size() );
        std::fill( styles.begin(), styles.end(), m_basePlotStyle );

        // then update plot-specific elements
        for (std::size_t isty = 0; isty < inputs.size(); ++isty) {
          styles[isty].SetPlotStyle( inputs[isty].style );
        }
        return styles;

      }  // end 'GenerateStyles(Inputs&)'

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Style   GetBasePlotStyle() const {return m_basePlotStyle;}
      Style   GetBaseTextStyle() const {return m_baseTextStyle;}
      TextBox GetTextBox()       const {return m_textBox;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetBasePlotStyle(const Style& style) {m_basePlotStyle = style;}
      void SetBaseTextStyle(const Style& style) {m_baseTextStyle = style;}
      void SetTextBox(const TextBox& text)      {m_textBox       = text;}

      // ----------------------------------------------------------------------
      //! Compare various ENC (or othwerise) spectra
      // ----------------------------------------------------------------------
      /*! Compares a variety of ENC (or otherwise) spectra from different
       *  sources.
       *
       *  \param[in]  inputs      list of objects to plot and their details
       *  \param[in]  plot_range  (x, y) ranges to plot
       *  \param[in]  norm_range  (x) to normalize histogram to
       *  \param[in]  canvas      definition of the canvas to draw on
       *  \param[out] ofile       file to write to
       *  \param[in]  header      optionally, can provide header for legend
       *  \param[in]  norm_to     optionally, can set what to normalize to
       *  \param[in]  do_norm     optionally, turn normalization on/off
       */
      void CompareSpectra(
        const Inputs& inputs,
        const Range& plot_range,
        const Range& norm_range,
        const Canvas& canvas,
        TFile* ofile,
        const std::string& header = "",
        const double norm_to = 1.0,
        const double do_norm = true
      ) const {

        // announce start
        std::cout << "\n -------------------------------- \n"
                  << "  Beginning spectra plotting!\n"
                  << "    Opening inputs:"
                  << std::endl;

        // open inputs
        std::vector<TFile*> ifiles;
        std::vector<TH1*>   ihists;
        for (std::size_t iin = 0; iin < inputs.size(); ++iin) {

          ifiles.push_back(
            Tools::OpenFile(inputs[iin].file, "read")
          );
          ihists.push_back(
            (TH1*) Tools::GrabObject( inputs[iin].object, ifiles.back() )
          );
          ihists.back() -> SetName( inputs[iin].rename.data() );
          std::cout << "      File = " << inputs[iin].file << "\n"
                    << "      Hist = " << inputs[iin].object
                    << std::endl;

          // normalize input if need be
          if (do_norm) {
            Tools::NormalizeByIntegral(
              ihists.back(),
              norm_to,
              norm_range.x.first,
              norm_range.x.second
            );
          }
        }  // end input loop

        // define legend dimensions
        const std::size_t nlines    = !header.empty() ? ihists.size() + 1 : ihists.size();
        const float       spacing   = m_baseTextStyle.GetTextStyle().spacing;
        const float       legheight = Tools::GetHeight(nlines, spacing);

        // generate legend vertices
        Type::Vertices vtxleg;
        vtxleg.push_back(0.3);
        vtxleg.push_back(0.1);
        vtxleg.push_back(0.5);
        vtxleg.push_back((float) 0.1 + legheight);

        // define legend
        Legend legdef;
        for (std::size_t ihst = 0; ihst < ihists.size(); ++ihst) {
          legdef.AddEntry( Legend::Entry(ihists[ihst], inputs[ihst].legend, "PF") );
        }
        legdef.SetVertices( vtxleg );
        if (!header.empty()) {
          legdef.SetHeader( header );
        }

        // create root objects
        TLegend*   legend = legdef.MakeLegend();
        TPaveText* text   = m_textBox.MakeTPaveText();
        std::cout << "    Created legend and text box." << std::endl;

        // set hist styles
        Styles styles = GenerateStyles( inputs );
        for (std::size_t ihst = 0; ihst < ihists.size(); ++ihst) {
          styles[ihst].SetPlotStyle( inputs[ihst].style );
          styles[ihst].Apply( ihists[ihst] );
          ihists[ihst] -> GetXaxis() -> SetRangeUser( plot_range.x.first, plot_range.x.second );
          ihists[ihst] -> GetYaxis() -> SetRangeUser( plot_range.y.first, plot_range.y.second );
        }

        // set legend/text styles
        m_baseTextStyle.Apply( legend );
        m_baseTextStyle.Apply( text );
        std::cout << "    Set styles." << std::endl;

        // draw plot
        PlotManager manager = PlotManager( canvas );
        manager.MakePlot();
        manager.Draw();
        manager.GetTCanvas() -> cd();
        ihists[0] -> Draw();
        for (std::size_t ihst = 1; ihst < ihists.size(); ++ihst) {
          ihists[ihst] -> Draw("same");
        }
        legend -> Draw();
        text   -> Draw();
        std:: cout << "    Made plot." << std::endl;

        // save output
        ofile -> cd();
        for (std::size_t ihst = 0; ihst < ihists.size(); ++ihst) {
          ihists[ihst] -> Write();
        }
        manager.Write();
        manager.Close();
        std::cout << "    Saved output." << std::endl;

        // announce end
        std::cout << "  Finished spectra plotting!\n"
                  << " -------------------------------- \n"
                  << std::endl;

        // exit routine
        return;

      }  // end 'CompareSpectra(Inputs&, Range&, Canvas&, TFile*, std::string&)'

      // ----------------------------------------------------------------------
      //! Compare various ENC (or othwerise) spectra to a baseline
      // ----------------------------------------------------------------------
      void CompareSpectraToBaseline(
        const PlotInput& in_denom,
        const Inputs& in_numers,
        const Range& range,
        const Canvas& canvas,
        TFile* ofile,
        const std::string& header = ""
      ) const {

        /* TODO fill in */
        return;

      }  // end 'CompareSpectraToBaseline(PHEC::PlotInput&, Inputs&, PHEC::Range&, PHEC::Canvas&, TFile*, std::string&)'

      // ----------------------------------------------------------------------
      //! Compare ratios of various pairs of ENC (or otherwise) spectra
      // ----------------------------------------------------------------------
      void CompareRatios(
        const Inputs& in_denoms,
        const Inputs& in_numers,
        const Range& range,
        const Canvas& canvas,
        TFile* ofile,
        const std::string& header = ""
      ) const {

        /* TODO fill in */
        return;

      }  // end 'CompareRatios(Inputs&, Inputs&, PHEC::Range&, PHEC::Canvas&, TFile*, std::string&)'

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      PHCorrelatorPlotter()  {};
      ~PHCorrelatorPlotter() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      PHCorrelatorPlotter(
        const Style& plot,
        const Style& text,
        const TextBox& box = TextBox()
      ) {

        m_basePlotStyle = plot;
        m_baseTextStyle = text;
        m_textBox       = box;

      }  // end ctor(Style&, Style&, TextBox&)'

  };  // end Plotter

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
