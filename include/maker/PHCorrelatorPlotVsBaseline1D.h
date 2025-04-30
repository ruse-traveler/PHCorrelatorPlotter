/// ===========================================================================
/*! \file    PHCorrelatorPlotVsBaseline1D.h
 *  \authors Derek Anderson
 *  \date    04.26.2025
 *
 *  PlotMaker routine to plot various 1D spectra.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTVSBASELINE1D_H
#define PHCORRELATORPLOTVSBASELINE1D_H

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
#include "PHCorrelatorPlotMakerDefault.h"
#include "PHCorrelatorPlotMakerTools.h"
#include "PHCorrelatorPlotMakerTypes.h"
#include "../elements/PHCorrelatorPlotterElements.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! 1D Spectra vs. Baseline Plotting Routine
  // ==========================================================================
  /*! Routine to plot various 1D spectra
   *  vs.a baseline and their ratio.
   */
  class PlotVsBaseline1D : public BaseRoutine {

    public:

      // ======================================================================
      //! Parameters for plotting 1D spectra vs. a baseline
      // ======================================================================
      /*! Struct to consolidate parameters for the "PlotVsBaseline1D"
       *  plotting routine.
       */
      struct Params {

        // members
        PlotInput    denominator;  ///!< baseline to compare against and its details
        Type::Inputs numerators;   ///!< list of spectra to compare and their details
        PlotShape    unity;        ///!< definition of unit ratio line to draw
        Type::Shapes shapes;       ///!< additional shapes (e.g. lines) to draw
        PlotOpts     options;      ///!< auxilliary plot options

        // --------------------------------------------------------------------
        //! default ctor
        // --------------------------------------------------------------------
        Params() {
          denominator = PlotInput();
          numerators  = Type::Inputs();
          unity       = PlotShape();
          shapes      = Type::Shapes();
          options     = PlotOpts();
        }

        // --------------------------------------------------------------------
        //! default dtor
        // --------------------------------------------------------------------
        ~Params() {};

        // --------------------------------------------------------------------
        //! ctor accepting arguments
        // --------------------------------------------------------------------
        Params(
          const PlotInput& denom_arg,
          const Type::Inputs& numer_args,
          const PlotShape& unity_arg,
          const Type::Shapes& shape_args,
          const PlotOpts& opt_args
        ) {
          denominator = denom_arg;
          numerators  = numer_args;
          unity       = unity_arg;
          shapes      = shape_args;
          options     = opt_args;
        }  // end ctor(PlotInput&, Type::Inputs&, PlotShape&, Type::Shapes&, PlotOpts&)'

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
      //! Configure routine
      // ----------------------------------------------------------------------
      /*! Sets routine parameters with reasonable default values
       *  based on provided inputs.
       */
      void Configure(
        const PlotInput& in_denom,
        const Type::Inputs& in_numers,
        const std::string& canvas_name = "cSpectraVsBaseline",
        const int range_opt = Type::Side
      ) {

        // grab default pad options, and
        // turn on log y/x when necessary
        PadOpts ratio_opts = PadOpts();
        PadOpts spect_opts = PadOpts();
        if (range_opt == Type::Side) {
          ratio_opts.logx = 1;
          spect_opts.logx = 1;
          spect_opts.logy = 1;
        }

        // generate ratio canvas
        Canvas canvas = Tools::MakeRatioCanvas(
          canvas_name,
          "pSpectra",
          "pRatio",
          0.35,
          spect_opts,
          ratio_opts
        );

        // set auxilliary options
        PlotOpts plot_opts;
        plot_opts.plot_range  = Default::PlotRange(range_opt);
        plot_opts.norm_range  = Default::NormRange(range_opt);
        plot_opts.canvas      = canvas;
        plot_opts.ratio_pad   = "ratio";
        plot_opts.spectra_pad = "spectra";

        // bundle parameters
        m_params.denominator = in_denom;
        m_params.numerators  = in_numers;
        m_params.options     = plot_opts;
        m_params.unity       = Default::Unity(range_opt);
        return;

      }  // end 'Configure(PlotInput&, Type::Inputs&, std::string&, int)'

      // ----------------------------------------------------------------------
      //! Plot various ENC (or othwerise) spectra vs. a baseline
      // ----------------------------------------------------------------------
      /*! Compares a variety of 1D ENC (or otherwise) spectra from different
       *  sources to a baseline. Upper panel shows spectra, lower panel
       *  shows ratio of spectra to baseline.
       *
       *  \param[out] ofile file to write to
       */
      void Plot(TFile* ofile) const {

        // announce start
        std::cout << "\n -------------------------------- \n"
                  << "  Beginning spectra vs. baseline plotting!\n"
                  << "    Opening inputs:"
                  << std::endl;

        // open denominator input
        TFile* dfile = Tools::OpenFile( m_params.denominator.file, "read" );
        TH1*   dhist = (TH1*) Tools::GrabObject( m_params.denominator.object, dfile );
        dhist -> SetName( m_params.denominator.rename.data() );
        std::cout << "      File (denom) = " << m_params.denominator.file << "\n"
                  << "      Hist (denom) = " << m_params.denominator.object
                  << std::endl;

        // normalize denominator if need be
        if (m_params.options.do_norm) {
          Tools::NormalizeByIntegral(
            dhist,
            m_params.options.norm_to,
            m_params.options.norm_range.GetX().first,
            m_params.options.norm_range.GetX().second
          );
        }

        // open numerator inputs
        std::vector<TFile*> nfiles;
        std::vector<TH1*>   nhists;
        for (std::size_t inum = 0; inum < m_params.numerators.size(); ++inum) {

          nfiles.push_back(
            Tools::OpenFile(m_params.numerators[inum].file, "read")
          );
          nhists.push_back(
            (TH1*) Tools::GrabObject( m_params.numerators[inum].object, nfiles.back() )
          );
          nhists.back() -> SetName( m_params.numerators[inum].rename.data() );
          std::cout << "      File (numer) = " << m_params.numerators[inum].file << "\n"
                    << "      Hist (numer) = " << m_params.numerators[inum].object
                    << std::endl;

          // normalize numerator if need be
          if (m_params.options.do_norm) {
            Tools::NormalizeByIntegral(
              nhists.back(),
              m_params.options.norm_to,
              m_params.options.norm_range.GetX().first,
              m_params.options.norm_range.GetX().second
            );
          }
        }  // end numerator loop

        // take ratios
        std::vector<TH1*> rhists;
        for (std::size_t inum = 0; inum < nhists.size(); ++inum) {

          // create name
          std::string name( nhists[inum] -> GetName() );
          name += "_Ratio";

          // do division
          rhists.push_back( Tools::DivideHist1D( nhists[inum], dhist) );
          rhists.back() -> SetName( name.data() );
        }
        std::cout << "    Calculated ratios." << std::endl;

        // determine no. of legend lines
        const std::size_t nlines = !m_params.options.header.empty()
                                 ? nhists.size() + 2
                                 : nhists.size() + 1;

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
        legdef.AddEntry( Legend::Entry(dhist, m_params.denominator.legend, "PF") ); 
        for (std::size_t inum = 0; inum < nhists.size(); ++inum) {
          legdef.AddEntry( Legend::Entry(nhists[inum], m_params.numerators[inum].legend, "PF") );
        }
        legdef.SetVertices( vtxleg );
        if (!m_params.options.header.empty()) {
          legdef.SetHeader( m_params.options.header );
        }

        // determine relevant range to draw line
        Shape unitydef = m_params.unity.shape;
        unitydef.SetXRange(
          Tools::GetDrawRange( m_params.options.plot_range.GetX(), rhists.front() -> GetXaxis() )
        );

        // create root objects
        TLine*     unity  = unitydef.MakeTLine();
        TLegend*   legend = legdef.MakeLegend();
        TPaveText* text   = m_textBox.MakeTPaveText();
        std::cout << "    Created legend and text box." << std::endl;

        // set denominator style
        Style den_style = m_basePlotStyle;
        den_style.SetPlotStyle( m_params.denominator.style );
        den_style.Apply( dhist );
        m_params.options.plot_range.Apply(Range::X, dhist -> GetXaxis());
        m_params.options.plot_range.Apply(Range::Y, dhist -> GetYaxis());

        // set numerator and ratio styles
        Type::Styles num_styles = GenerateStyles( m_params.numerators );
        for (std::size_t inum = 0; inum < nhists.size(); ++inum) {
          num_styles[inum].SetPlotStyle( m_params.numerators[inum].style );
          num_styles[inum].Apply( nhists[inum] );
          num_styles[inum].Apply( rhists[inum] );
          m_params.options.plot_range.Apply(Range::X, nhists[inum] -> GetXaxis());
          m_params.options.plot_range.Apply(Range::Y, nhists[inum] -> GetYaxis());
          m_params.options.plot_range.Apply(Range::X, rhists[inum] -> GetXaxis());
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
        for (std::size_t irat = 0; irat < rhists.size(); ++irat) {
          manager.ScaleAxisText(
            m_params.options.spectra_pad,
            m_params.options.ratio_pad,
            Range::X,
            rhists[irat] -> GetXaxis()
          );
          manager.ScaleAxisText(
            m_params.options.spectra_pad,
            m_params.options.ratio_pad,
            Range::Y,
            rhists[irat] -> GetYaxis()
          );
        }

        // draw objects
        manager.Draw();
        manager.GetTPad( m_params.options.ratio_pad ) -> cd();
        rhists[0] -> Draw();
        for (std::size_t irat = 1; irat < rhists.size(); ++irat) {
          rhists[irat] -> Draw("same");
        }
        unity -> Draw();
        manager.GetTPad( m_params.options.spectra_pad ) -> cd();
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
        Tools::CloseFiles(nfiles);
        dfile -> Close();
        return;

      }  // end 'Plot(TFile*)'

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      PlotVsBaseline1D()  {};
      ~PlotVsBaseline1D() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      explicit PlotVsBaseline1D(const Style& plot, const Style& text, const TextBox& box)
        : BaseRoutine(plot, text, box) {};

  };  // end PlotVsBaseline1D

}    // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================

