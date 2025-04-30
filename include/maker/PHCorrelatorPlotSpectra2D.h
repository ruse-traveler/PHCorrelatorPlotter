/// ===========================================================================
/*! \file    PHCorrelatorPlotSpectra2D.h
 *  \authors Derek Anderson
 *  \date    04.19.2024
 *
 *  PlotMaker routine to plot various 2D spectra.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTSPECTRA2D_H
#define PHCORRELATORPLOTSPECTRA2D_H

// c++ utilities
#include <algorithm>
#include <cassert>
#include <iostream>
// root libraries
#include <TCanvas.h>
#include <TFile.h>
#include <TH2.h>
#include <TLegend.h>
#include <TPaveText.h>
// plotting utilities
#include "PHCorrelatorBaseRoutine.h"
#include "PHCorrelatorPlotMakerDefault.h"
#include "PHCorrelatorPlotMakerTools.h"
#include "PHCorrelatorPlotMakerTypes.h"
#include "PHCorrelatorPlotSpectra1D.h"
#include "../elements/PHCorrelatorPlotterElements.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! 2D Spectra Plotting Routine
  // ==========================================================================
  /*! Routine to plot various 2D spectra
   *  on a single panel.
   */
  class PlotSpectra2D : public BaseRoutine {

    public:

      // ======================================================================
      //! Parameters for plotting 2D spectra (same as 1D routine)
      // ======================================================================
      typedef PlotSpectra1D::Params Params;

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
      //! Configure routine
      // ----------------------------------------------------------------------
      /*! Sets routine parameters with reasonable default values
       *  based on provided inputs.
       */
      void Configure(
        const Type::Inputs& inputs,
        const std::string& canvas_name = "cSpectra2D",
        const std::size_t ncolumn = 2
      ) {

        // grab default pad options, and
        // turn on log z
        PadOpts pad_opts = PadOpts();
        pad_opts.logx = 1;
        pad_opts.logz = 1;

        // set pad margins
        Type::Margins pad_margins;
        pad_margins.push_back(0.15);
        pad_margins.push_back(0.15);
        pad_margins.push_back(0.15);
        pad_margins.push_back(0.15);

        // generate grid canvas
        Canvas canvas = Tools::MakeGridCanvas(
          canvas_name,
          "pPad",
          inputs.size(),
          ncolumn,
          pad_margins
        );

        // set ranges
        const Range plot_range = Range(
          Default::PlotRange(Type::Side).GetX(),
          Default::PlotRange(Type::Angle).GetY(),
          Default::PlotRange(Type::Side).GetZ()
        );
        const Range norm_range = plot_range;

        // set auxilliary options
        PlotOpts plot_opts;
        plot_opts.plot_range = plot_range;
        plot_opts.norm_range = norm_range;
        plot_opts.canvas     = canvas;

        // bundle parameters
        m_params.inputs  = inputs;
        m_params.options = plot_opts;
        return;

      }  // end 'Configure(Inputs&, std::string&, std::size_t)'

      // ----------------------------------------------------------------------
      //! Plot various 2D ENC (or othwerise) spectra
      // ----------------------------------------------------------------------
      /*! Compares a variety of 2D ENC (or otherwise) spectra from
       *  different sources.
       *
       *  \param[out] ofile file to write to
       */
      void Plot(TFile* ofile) const {

        // announce start
        std::cout << "\n -------------------------------- \n"
                  << "  Beginning 2D spectra plotting!\n"
                  << "    Opening inputs:"
                  << std::endl;

        // open inputs
        std::vector<TFile*> ifiles;
        std::vector<TH2*>   ihists;
        for (std::size_t iin = 0; iin < m_params.inputs.size(); ++iin) {

          ifiles.push_back(
            Tools::OpenFile(m_params.inputs[iin].file, "read")
          );
          ihists.push_back(
            (TH2*) Tools::GrabObject( m_params.inputs[iin].object, ifiles.back() )
          );
          ihists.back() -> SetName( m_params.inputs[iin].rename.data() );
          ihists.back() -> SetTitle( m_params.inputs[iin].legend.data() );
          std::cout << "      File = " << m_params.inputs[iin].file << "\n"
                    << "      Hist = " << m_params.inputs[iin].object
                    << std::endl;

          // normalize input if need be
          if (m_params.options.do_norm) {
            Tools::NormalizeByIntegral(
              ihists.back(),
              m_params.options.norm_to,
              m_params.options.norm_range.GetX().first,
              m_params.options.norm_range.GetX().second,
              m_params.options.norm_range.GetY().first,
              m_params.options.norm_range.GetY().second
            );
          }
        }  // end input loop

        // create text box
        TPaveText* text = m_textBox.MakeTPaveText();
        m_baseTextStyle.Apply( text );
        std::cout << "    Created text box." << std::endl;

        // set hist styles
        Type::Styles styles = GenerateStyles( m_params.inputs );
        for (std::size_t ihst = 0; ihst < ihists.size(); ++ihst) {
          styles[ihst].SetPlotStyle( m_params.inputs[ihst].style );
          styles[ihst].Apply( ihists[ihst] );
          m_params.options.plot_range.Apply(Range::X, ihists[ihst] -> GetXaxis());
          m_params.options.plot_range.Apply(Range::Y, ihists[ihst] -> GetYaxis());
          m_params.options.plot_range.Apply(Range::Z, ihists[ihst] -> GetZaxis());
        }
        std::cout << "    Set styles." << std::endl;

        // draw plot
        CanvasManager manager = CanvasManager( m_params.options.canvas );
        manager.MakePlot();
        manager.Draw();

        // throw error if not enough pads are present for histograms
        if (manager.GetTPads().size() < ihists.size()) {
          std::cerr << "PANIC: more histograms to draw than pads in " << manager.GetTCanvas() -> GetName() << "!" << std::endl;
          assert(manager.GetTPads().size() >= ihists.size());
        }

        // otherwise draw 1 histogram per pad and
        // text box on last pad
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
        Tools::CloseFiles(ifiles);
        return;

      }  // end 'Plot(TFile*)'

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      PlotSpectra2D()  {};
      ~PlotSpectra2D() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      explicit PlotSpectra2D(const Style& plot, const Style& text, const TextBox& box)
        : BaseRoutine(plot, text, box) {};

  };  // end PlotSpectra2D

}    // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================
