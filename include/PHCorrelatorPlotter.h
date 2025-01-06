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
      Style         m_basePlotStyle;
      Style         m_baseTextStyle;
      TextBox       m_textBox;
      Type::FileMap m_fileMap;

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
      //! Add filename in map of files
      // ----------------------------------------------------------------------
      void AddFileToMap(const std::string& label, const std::string& file) {

        m_fileMap[label] = file;
        return;

      }  // end 'AddFileToMap(std::string&, std:string&)'

      // ----------------------------------------------------------------------
      //! Get filename from map of files
      // ----------------------------------------------------------------------
      std::string GetFileFromMap(const std::string& label) {

        return m_fileMap[label];

      }  // end 'GetFileFromMap(std::string&)'

      // ----------------------------------------------------------------------
      //! Compare various ENC (or othwerise) spectra
      // ----------------------------------------------------------------------
      /*! Compares a variety of ENC (or otherwise) spectra from different
       *  sources.
       *
       *  \param[in]  inputs      list of objects to plot and their details
       *  \param[in]  plot_range  (x, y) ranges to plot
       *  \param[in]  norm_range  (x) range to normalize histogram to
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

      }  // end 'CompareSpectra(...)'

      // ----------------------------------------------------------------------
      //! Compare various ENC (or othwerise) spectra to a baseline
      // ----------------------------------------------------------------------
      /*! Compares a variety of ENC (or otherwise) spectra from different
       *  sources to a baseline. Uppder panel shows spectra, lower panel
       *  shows ratio of spectra to baseline.
       *
       *  \param[in]  in_denom    baseline to compare against and its info
       *  \param[in]  in_numers   spectra to compare against baseline and their info
       *  \param[in]  plot_range  (x, y) ranges to plot
       *  \param[in]  norm_range  (x) range to normalize histograms to
       *  \param[in]  canvas      definition of the canvas to draw on
       *  \param[out] ofile       file to write to
       *  \param[in]  header      optionally, can provide header for legend
       *  \param[in]  norm_to     optionally, can set what to normalize to
       *  \param[in]  do_norm     optionally, turn normalization on/off
       */
      void CompareSpectraToBaseline(
        const PlotInput& in_denom,
        const Inputs& in_numers,
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
                  << "  Beginning spectra vs. baseline plotting!\n"
                  << "    Opening inputs:"
                  << std::endl;

        // open denominator input
        TFile* dfile = Tools::OpenFile( in_denom.file, "read" );
        TH1*   dhist = (TH1*) Tools::GrabObject( in_denom.object, dfile );
        dhist -> SetName( in_denom.rename.data() );
        std::cout << "      File (denom) = " << in_denom.file << "\n"
                  << "      Hist (denom) = " << in_denom.object
                  << std::endl;

        // normalize denominator if need be
        if (do_norm) {
          Tools::NormalizeByIntegral(
            dhist,
            norm_to,
            norm_range.x.first,
            norm_range.x.second
          );
        }

        // open numerator inputs
        std::vector<TFile*> nfiles;
        std::vector<TH1*>   nhists;
        for (std::size_t inum = 0; inum < in_numers.size(); ++inum) {

          nfiles.push_back(
            Tools::OpenFile(in_numers[inum].file, "read")
          );
          nhists.push_back(
            (TH1*) Tools::GrabObject( in_numers[inum].object, nfiles.back() )
          );
          nhists.back() -> SetName( in_numers[inum].rename.data() );
          std::cout << "      File (numer) = " << in_numers[inum].file << "\n"
                    << "      Hist (numer) = " << in_numers[inum].object
                    << std::endl;

          // normalize numerator if need be
          if (do_norm) {
            Tools::NormalizeByIntegral(
              nhists.back(),
              norm_to,
              norm_range.x.first,
              norm_range.x.second
            );
          }
        }  // end input loop

        // take ratios
        std::vector<TH1*> rhists;
        for (std::size_t inum = 0; inum < nhists.size(); ++inum) {

          // create name
          std::string name( nhists[inum] -> GetName() );
          name += "_Ratio";

          // do division and apply style
          rhists.push_back( Tools::DivideHist1D( nhists[inum], dhist) );
          rhists.back() -> SetName( name.data() );
        }

        // define legend dimensions
        const std::size_t nlines    = !header.empty() ? nhists.size() + 2 : nhists.size() + 1;
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
        legdef.AddEntry( Legend::Entry(dhist,in_denom.legend, "PF") ); 
        for (std::size_t inum = 0; inum < nhists.size(); ++inum) {
          legdef.AddEntry( Legend::Entry(nhists[inum], in_numers[inum].legend, "PF") );
        }
        legdef.SetVertices( vtxleg );
        if (!header.empty()) {
          legdef.SetHeader( header );
        }

        // create root objects
        //   - FIXME line should be configurable
        TLine*     line   = new TLine( plot_range.x.first, 1.0, plot_range.x.second, 1.0 );
        TLegend*   legend = legdef.MakeLegend();
        TPaveText* text   = m_textBox.MakeTPaveText();
        std::cout << "    Created legend and text box." << std::endl;

        // set denominator style
        Style den_style = m_basePlotStyle;
        den_style.SetPlotStyle( in_denom.style );
        den_style.Apply( dhist );
        dhist -> GetXaxis() -> SetRangeUser( plot_range.x.first, plot_range.x.second );
        dhist -> GetYaxis() -> SetRangeUser( plot_range.y.first, plot_range.y.second );

        // set numerator and ratio styles
        Styles num_styles = GenerateStyles( in_numers );
        for (std::size_t inum = 0; inum < nhists.size(); ++inum) {
          num_styles[inum].SetPlotStyle( in_numers[inum].style );
          num_styles[inum].Apply( nhists[inum] );
          num_styles[inum].Apply( rhists[inum] );
          nhists[inum] -> GetXaxis() -> SetRangeUser( plot_range.x.first, plot_range.x.second );
          nhists[inum] -> GetYaxis() -> SetRangeUser( plot_range.y.first, plot_range.y.second );
          rhists[inum] -> GetXaxis() -> SetRangeUser( plot_range.x.first, plot_range.x.second );
        }

        // set line styles
        //   - FIXME line should be configurable
        line -> SetLineStyle(9);
        line -> SetLineColor(923);

        // set legend/text styles
        m_baseTextStyle.Apply( legend );
        m_baseTextStyle.Apply( text );
        std::cout << "    Set styles." << std::endl;

        // draw plot
        //   - FIXME need to be able to specify labels from macro
        PlotManager manager = PlotManager( canvas );
        manager.MakePlot();
        manager.Draw();
        manager.GetTPad(0) -> cd();
        rhists[0] -> Draw();
        for (std::size_t inum = 1; inum < nhists.size(); ++inum) {
          rhists[inum] -> Draw("same");
        }
        line -> Draw();
        manager.GetTPad(1) -> cd();
        dhist -> Draw();
        for (std::size_t inum = 0; inum < nhists.size(); ++inum) {
          nhists[inum] -> Draw("same");
        }
        legend -> Draw();
        text   -> Draw();
        std:: cout << "    Made plot." << std::endl;

        // save output
        ofile -> cd();
        dhist -> Write();
        for (std::size_t inum = 0; inum < nhists.size(); ++inum) {
          nhists[inum] -> Write();
          rhists[inum] -> Write();
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

      }  // end 'CompareSpectraToBaseline(...)'

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

      }  // end 'CompareRatios(...)'

      // ----------------------------------------------------------------------
      //! Compare various 2D spectra
      // ----------------------------------------------------------------------
      /*! Compares a variety of 2D spectra from different sources.
       *
       *  \param[in]  inputs      list of objects to plot and their details
       *  \param[in]  plot_range  (x, y, z) ranges to plot
       *  \param[in]  norm_range  (x, y) to normalize histogram to
       *  \param[in]  canvas      definition of the canvas to draw on
       *  \param[out] ofile       file to write to
       *  \param[in]  norm_to     optionally, can set what to normalize to
       *  \param[in]  do_norm     optionally, turn normalization on/off
       */
      void CompareSpectra2D(
        const Inputs& inputs,
        const Range& plot_range,
        const Range& norm_range,
        const Canvas& canvas,
        TFile* ofile,
        const double norm_to = 1.0,
        const double do_norm = false
      ) const {

        // announce start
        std::cout << "\n -------------------------------- \n"
                  << "  Beginning 2D spectra plotting!\n"
                  << "    Opening inputs:"
                  << std::endl;

        // open inputs
        std::vector<TFile*> ifiles;
        std::vector<TH2*>   ihists;
        for (std::size_t iin = 0; iin < inputs.size(); ++iin) {

          ifiles.push_back(
            Tools::OpenFile(inputs[iin].file, "read")
          );
          ihists.push_back(
            (TH2*) Tools::GrabObject( inputs[iin].object, ifiles.back() )
          );
          ihists.back() -> SetName( inputs[iin].rename.data() );
          ihists.back() -> SetTitle( inputs[iin].legend.data() );
          std::cout << "      File = " << inputs[iin].file << "\n"
                    << "      Hist = " << inputs[iin].object
                    << std::endl;

          // normalize input if need be
          if (do_norm) {
            Tools::NormalizeByIntegral(
              ihists.back(),
              norm_to,
              norm_range.x.first,
              norm_range.x.second,
              norm_range.y.first,
              norm_range.y.second
            );
          }
        }  // end input loop

        // create text box
        TPaveText* text = m_textBox.MakeTPaveText();
        m_baseTextStyle.Apply( text );
        std::cout << "    Created text box." << std::endl;

        // set hist styles
        Styles styles = GenerateStyles( inputs );
        for (std::size_t ihst = 0; ihst < ihists.size(); ++ihst) {
          styles[ihst].SetPlotStyle( inputs[ihst].style );
          styles[ihst].Apply( ihists[ihst] );
          ihists[ihst] -> GetXaxis() -> SetRangeUser( plot_range.x.first, plot_range.x.second );
          ihists[ihst] -> GetYaxis() -> SetRangeUser( plot_range.y.first, plot_range.y.second );
          ihists[ihst] -> GetZaxis() -> SetRangeUser( plot_range.z.first, plot_range.z.second );
        }
        std::cout << "    Set styles." << std::endl;

        // draw plot
        PlotManager manager = PlotManager( canvas );
        manager.MakePlot();
        manager.Draw();

        // throw error if not enough pads are present for histograms
        if (manager.GetTPads().size() < ihists.size()) {
          std::cerr << "PANIC: more histograms to draw than pads in " << manager.GetTCanvas() -> GetName() << "!" << std::endl;
          assert(manager.GetTPads().size() >= ihists.size());
        }

        // otherwise draw 1 histogram per pad and
        // text box on last pad
        //   - FIXME need to be able to specify labels from macro
        //   - FIXME draw options should be configurable from macro
        for (std::size_t ihst = 0; ihst < ihists.size(); ++ihst) {
          manager.GetTPad(ihst) -> cd();
          ihists[ihst] -> Draw("colz");
        }
        manager.GetTPads().back() -> cd();
        text -> Draw();
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
        std::cout << "  Finished 2D spectra plotting!\n"
                  << " -------------------------------- \n"
                  << std::endl;

        // exit routine
        return;

      }  // end 'ComparSpectra2D(...)'

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
