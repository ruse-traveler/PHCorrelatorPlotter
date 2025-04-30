/// ===========================================================================
/*! \file    PHCorrelatorPlotRatios1D.h
 *  \authors Derek Anderson
 *  \date    04.19.2024
 *
 *  PlotMaker routine to plot various pairs of 1D
 *  spectra and their ratios.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTRATIOS1D_H
#define PHCORRELATORPLOTRATIOS1D_H

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
  //! 1D Ratio Plotting Routine
  // ==========================================================================
  /*! Routine to plot various pairs of 1D spectra
   *  and their ratios on two panels.
   */
  class PlotRatios1D : public BaseRoutine {

    public:

      // ======================================================================
      //! Parameters for plotting pairs of spectra
      // ======================================================================
      /*! Struct to consolidate parameters for the "PlotRatios1D"
       *  plotting routine.
       */
      struct Params {

        // members
        Type::Inputs denominators;  ///!< baselines to compare against and their details
        Type::Inputs numerators;    ///!< list of spectra to compare and their details
        PlotShape    unity;         ///!< definition of unit ratio line to draw
        Type::Shapes shapes;        ///!< additional shapes (e.g. lines) to draw
        PlotOpts     options;       ///!< auxilliary plot options

        // --------------------------------------------------------------------
        //! default ctor
        // --------------------------------------------------------------------
        Params() {
          denominators = Type::Inputs();
          numerators   = Type::Inputs();
          unity        = PlotShape();
          shapes       = Type::Shapes();
          options      = PlotOpts();
        }

        // --------------------------------------------------------------------
        //! default dtor
        // --------------------------------------------------------------------
        ~Params() {};

        // --------------------------------------------------------------------
        //! ctor accepting arguments
        // --------------------------------------------------------------------
        Params(
          const Type::Inputs& denom_args,
          const Type::Inputs& numer_args,
          const PlotShape& unity_arg,
          const Type::Shapes& shape_args,
          const PlotOpts& opt_args
        ) {
          denominators = denom_args;
          numerators   = numer_args;
          unity        = unity_arg;
          shapes       = shape_args;
          options      = opt_args;
        }  // end ctor(Type::Inputs& x 2, Type::PlotShape&, Type::Shapes&, PlotOpts&)'

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
        const Type::Inputs& in_denoms,
        const Type::Inputs& in_numers,
        const std::string& canvas_name = "cCompareRatios1D",
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
        m_params.denominators = in_denoms;
        m_params.numerators   = in_numers;
        m_params.options      = plot_opts;
        m_params.unity        = Default::Unity(range_opt);
        return;

      }  // end 'Configure(Inputs& x 2, std::string&, int)'

      // ----------------------------------------------------------------------
      //! Plot various pairs of 1D ENC (or otherwise) spectra and their ratios
      // ----------------------------------------------------------------------
      /*! Compares a variety of pairs of 1D ENC (or otherwise) spectra from
       *  different sources and their ratios. Upper panel shows spectra,
       *  lower panel shows ratios.
       *
       *  \param[out] ofile file to write to
       */
      void Plot(TFile* ofile) const {

        // announce start
        std::cout << "\n -------------------------------- \n"
                  << "  Beginning ratio comparison plotting!\n"
                  << "    Opening inputs:"
                  << std::endl;

        // throw error if no. of denominators and numerators don't match
        if (m_params.denominators.size() != m_params.numerators.size()) {
          std::cerr << "PANIC: number of denominators and numerators should be the same!\n"
                    << "       denominators = " << m_params.denominators.size() << "\n"
                    << "       numerators   = " << m_params.numerators.size()
                    << std::endl;
          assert(m_params.denominators.size() == m_params.numerators.size());
        }

        // open denominator inputs
        std::vector<TFile*> dfiles;
        std::vector<TH1*>   dhists;
        for (std::size_t iden = 0; iden < m_params.denominators.size(); ++iden) {

          dfiles.push_back(
            Tools::OpenFile(m_params.denominators[iden].file, "read")
          );
          dhists.push_back(
            (TH1*) Tools::GrabObject( m_params.denominators[iden].object, dfiles.back() )
          );
          dhists.back() -> SetName( m_params.denominators[iden].rename.data() );
          std::cout << "      File (denom) = " << m_params.denominators[iden].file << "\n"
                    << "      Hist (denom) = " << m_params.denominators[iden].object
                    << std::endl;

          // normalize denominaotr if need be
          if (m_params.options.do_norm) {
            Tools::NormalizeByIntegral(
              dhists.back(),
              m_params.options.norm_to,
              m_params.options.norm_range.GetX().first,
              m_params.options.norm_range.GetX().second
            );
          }
        }  // end denominator loop

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
        for (std::size_t iden = 0; iden < nhists.size(); ++iden) {

          // create name
          std::string name( dhists[iden] -> GetName() );
          name += "_Ratio";

          // do division
          rhists.push_back( Tools::DivideHist1D( nhists[iden], dhists[iden]) );
          rhists.back() -> SetName( name.data() );
        }
        std::cout << "    Calculated ratios." << std::endl;

        // determine no. of legend lines
        const std::size_t nlines = !m_params.options.header.empty()
                                 ? nhists.size() + dhists.size() + 1
                                 : nhists.size() + dhists.size();

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
        for (std::size_t iden = 0; iden < dhists.size(); ++iden) {
          legdef.AddEntry( Legend::Entry(dhists[iden], m_params.denominators[iden].legend, "PF") );
          legdef.AddEntry( Legend::Entry(nhists[iden], m_params.numerators[iden].legend, "PF") );
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

        // set styles
        Type::Styles den_styles = GenerateStyles( m_params.denominators );
        Type::Styles num_styles = GenerateStyles( m_params.numerators );
        for (std::size_t iden = 0; iden < nhists.size(); ++iden) {

          // set denominator style
          den_styles[iden].SetPlotStyle( m_params.denominators[iden].style );
          den_styles[iden].Apply( dhists[iden] );
          m_params.options.plot_range.Apply(Range::X, dhists[iden] -> GetXaxis());
          m_params.options.plot_range.Apply(Range::Y, dhists[iden] -> GetYaxis());

          // set numerator style
          num_styles[iden].SetPlotStyle( m_params.numerators[iden].style );
          num_styles[iden].Apply( nhists[iden] );
          m_params.options.plot_range.Apply(Range::X, nhists[iden] -> GetXaxis());
          m_params.options.plot_range.Apply(Range::Y, nhists[iden] -> GetYaxis());

          // set ratio style
          den_styles[iden].Apply( rhists[iden] );
          m_params.options.plot_range.Apply(Range::X, rhists[iden] -> GetXaxis());
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
        dhists[0] -> Draw();
        nhists[0] -> Draw("same");
        for (std::size_t iden = 1; iden < dhists.size(); ++iden) {
          dhists[iden] -> Draw("same");
          nhists[iden] -> Draw("same");
        }
        legend -> Draw();
        text   -> Draw();
        std:: cout << "    Made plot." << std::endl;

        // save output
        ofile -> cd();
        for (std::size_t iden = 0; iden < dhists.size(); ++iden) {
          dhists[iden] -> Write();
          nhists[iden] -> Write();
          rhists[iden] -> Write();
        }
        manager.Write();
        manager.Close();
        std::cout << "    Saved output." << std::endl;

        // announce end
        std::cout << "  Finished spectra plotting!\n"
                  << " -------------------------------- \n"
                  << std::endl;

        // exit routine
        Tools::CloseFiles(dfiles);
        Tools::CloseFiles(nfiles);
        return;

      }  // end 'Plot(TFile*)'

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      PlotRatios1D()  {};
      ~PlotRatios1D() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      explicit PlotRatios1D(const Style& plot, const Style& text, const TextBox& box)
        : BaseRoutine(plot, text, box) {};

  };  // end PlotRatios1D

}    // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================
