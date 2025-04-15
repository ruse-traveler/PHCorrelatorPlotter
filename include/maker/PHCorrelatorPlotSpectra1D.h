/// ===========================================================================
/*! \file    PHCorrelatorPlotSpectra1D.h
 *  \authors Derek Anderson
 *  \date    04.13.2024
 *
 *  Base plotting routine for
 *  the PlotMaker.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTSPECTRA1D_H
#define PHCORRELATORPLOTSPECTRA1D_H

// c++ utilities
#include <algorithm>
#include <cassert>
#include <iostream>
// root libraries
#include <TCanvas.h>
#include <TFile.h>
#include <TH1.h>
#include <TLegend.h>
// plotting utilities
#include "PHCorrelatorBaseRoutine.h"
#include "PHCorrelatorPlotMakerTypes.h"
#include "../elements/PHCorrelatorPlotterElements.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! 1D Spectra Plotting Routine
  // ==========================================================================
  /*! Routine to plot various 1D spectra
   *  on a single panel.
   */
  class PlotSpectra1D : public BaseRoutine {

    public:

      // ======================================================================
      //! Parameters for plotting 1D spectra
      // ======================================================================
      /*! Struct to consolidate parameters for the "PlotSpectra1D"
       *  plotting routine.
       */
      struct Params {

        // members
        Inputs   inputs;   ///!< list objects to plots and their details
        Shapes   shapes;   ///!< shapes (e.g. lines) to draw
        PlotOpts options;  ///!< auxilliary plot options

        // --------------------------------------------------------------------
        //! default ctor
        // --------------------------------------------------------------------
        Params() {
          inputs  = Inputs();
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
          const Inputs& input_args,
          const Shapes& shape_args,
          const PlotOpts& opt_args
        ) {
          inputs  = input_args;
          shapes  = shape_args;
          options = opt_args;
        }  // end ctor(Inputs&, Shapes&, PlotOpts&)'

      };  // end Params

    private:

      // members
      Params m_params;

    public:

      /* TODO add configure */

      // ----------------------------------------------------------------------
      //! Plot various 1D ENC (or othwerise) spectra
      // ----------------------------------------------------------------------
      /*! Compares a variety of 1DENC (or otherwise) spectra from
       *  different sources.
       *
       *  \param[out] ofile file to write to
       */
      void Plot(TFile* ofile) {

        // announce start
        std::cout << "\n -------------------------------- \n"
                  << "  Beginning spectra plotting!\n"
                  << "    Opening inputs:"
                  << std::endl;

        // open inputs
        std::vector<TFile*> ifiles;
        std::vector<TH1*>   ihists;
        for (std::size_t iin = 0; iin < m_params.inputs.size(); ++iin) {

          ifiles.push_back(
            Tools::OpenFile(m_params.inputs[iin].file, "read")
          );
          ihists.push_back(
            (TH1*) Tools::GrabObject( m_params.inputs[iin].object, ifiles.back() )
          );
          ihists.back() -> SetName( m_params.inputs[iin].rename.data() );
          std::cout << "      File = " << m_params.inputs[iin].file << "\n"
                    << "      Hist = " << m_params.inputs[iin].object
                    << std::endl;

          // normalize input if need be
          if (m_params.options.do_norm) {
            Tools::NormalizeByIntegral(
              ihists.back(),
              m_params.options.norm_to,
              m_params.options.norm_range.GetX().first,
              m_params.options.norm_range.GetX().second
            );
          }
        }  // end input loop

        // determine no. of legend lines
        const std::size_t nlines = !m_params.options.header.empty()
                                 ? ihists.size() + 1
                                 : ihists.size();

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
        Legend legdef;
        for (std::size_t ihst = 0; ihst < ihists.size(); ++ihst) {
          legdef.AddEntry( Legend::Entry(ihists[ihst], m_params.inputs[ihst].legend, "PF") );
        }
        legdef.SetVertices( vtxleg );
        if (!m_params.options.header.empty()) {
          legdef.SetHeader( m_params.options.header );
        }

        // create root objects
        TLegend*   legend = legdef.MakeLegend();
        TPaveText* text   = m_textBox.MakeTPaveText();
        std::cout << "    Created legend and text box." << std::endl;

        // set hist styles
        Styles styles = GenerateStyles( m_params.inputs );
        for (std::size_t ihst = 0; ihst < ihists.size(); ++ihst) {
          styles[ihst].SetPlotStyle( m_params.inputs[ihst].style );
          styles[ihst].Apply( ihists[ihst] );
          m_params.options.plot_range.Apply(Range::X, ihists[ihst] -> GetXaxis());
          m_params.options.plot_range.Apply(Range::Y, ihists[ihst] -> GetYaxis());
        }

        // set legend/text styles
        m_baseTextStyle.Apply( legend );
        m_baseTextStyle.Apply( text );
        std::cout << "    Set styles." << std::endl;

        // draw plot
        CanvasManager manager = CanvasManager( m_params.options.canvas );
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
        Tools::CloseFiles(ifiles);
        return;

      }  // end 'Plot(TFile*)'

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      PlotSpectra1D()  {};
      ~PlotSpectra1D() {};

      /* TODO add other ctors */

  };  // end PlotSpectra1D

}    // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================
