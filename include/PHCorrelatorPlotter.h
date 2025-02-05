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
#include <map>
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
#include "PHCorrelatorPlotOpts.h"
#include "PHCorrelatorPlotShape.h"
#include "PHCorrelatorPlotTools.h"
#include "PHCorrelatorPlotTypes.h"
#include "PHCorrelatorRange.h"
#include "PHCorrelatorStyle.h"
#include "PHCorrelatorTextBox.h"



namespace PHEnergyCorrelator {

  // --------------------------------------------------------------------------
  // Useful aliases
  // ---------------------------------------------------------------------------
  typedef std::map<std::string, PlotShape> Shapes;
  typedef std::vector<PlotInput>           Inputs;
  typedef std::vector<Style>               Styles;



  // ============================================================================
  //! ENC Plotter
  // ============================================================================
  /*! This class consolidates plotting routines associated
   *  with the PHENIX ENC analysis.
   */
  class PHCorrelatorPlotter {

    public:

      // ======================================================================
      //! Parameters for comparing spectra
      // ======================================================================
      /*! Struct to consolidate parameters for the "Compare Spectra"
       *  plotting routines.
       */
      struct CompareSpectraParams {

        // members
        Inputs   inputs;   ///!< list objects to plots and their details
        Shapes   shapes;   ///!< shapes (e.g. lines) to draw
        PlotOpts options;  ///!< auxilliary plot options

        // --------------------------------------------------------------------
        //! default ctor
        // --------------------------------------------------------------------
        CompareSpectraParams() {
          inputs  = Inputs();
          shapes  = Shapes();
          options = PlotOpts();
        }

        // --------------------------------------------------------------------
        //! default dtor
        // --------------------------------------------------------------------
        ~CompareSpectraParams() {};

        // --------------------------------------------------------------------
        //! ctor accepting arguments
        // --------------------------------------------------------------------
        CompareSpectraParams(
          const Inputs& input_args,
          const Shapes& shape_args,
          const PlotOpts& opt_args
        ) {
          inputs  = input_args;
          shapes  = shape_args;
          options = opt_args;
        }  // end ctor(Inputs&, Shapes&, PlotOpts&)'

      };  // end CompareSpectraParams

      // ======================================================================
      //! Parameters for comparing spectra to a baseline
      // ======================================================================
      /*! Struct to consolidate arameters for the "Compare Spectra to Baseline"
       *  plotting routines.
       */
      struct SpectraVsBaselineParams {

        // members
        PlotInput denominator;  ///!< baseline to compare against and its details
        Inputs    numerators;   ///!< list of spectra to compare and their details
        PlotShape unity;        ///!< definition of unit ratio line to draw
        Shapes    shapes;       ///!< additional shapes (e.g. lines) to draw
        PlotOpts  options;      ///!< auxilliary plot options

        // --------------------------------------------------------------------
        //! default ctor
        // --------------------------------------------------------------------
        SpectraVsBaselineParams() {
          denominator = PlotInput();
          numerators  = Inputs();
          unity       = PlotShape();
          shapes      = Shapes();
          options     = PlotOpts();
        }

        // --------------------------------------------------------------------
        //! default dtor
        // --------------------------------------------------------------------
        ~SpectraVsBaselineParams() {};

        // --------------------------------------------------------------------
        //! ctor accepting arguments
        // --------------------------------------------------------------------
        SpectraVsBaselineParams(
          const PlotInput& denom_arg,
          const Inputs& numer_args,
          const PlotShape& unity_arg,
          const Shapes& shape_args,
          const PlotOpts& opt_args
        ) {
          denominator = denom_arg;
          numerators  = numer_args;
          unity       = unity_arg;
          shapes      = shape_args;
          options     = opt_args;
        }  // end ctor(PlotInput&, Inputs&, PlotShape&, Shapes&, PlotOpts&)'

      };  // end SpectraVsBaselineParams

      // ======================================================================
      //! Parameters for comparing pairs of spectra
      // ======================================================================
      /*! Struct to consolidate arameters for the "Compare Ratios"
       *  plotting routines.
       */
      struct CompareRatiosParams {

        // members
        Inputs    denominators;  ///!< baselines to compare against and their details
        Inputs    numerators;    ///!< list of spectra to compare and their details
        PlotShape unity;         ///!< definition of unit ratio line to draw
        Shapes    shapes;        ///!< additional shapes (e.g. lines) to draw
        PlotOpts  options;       ///!< auxilliary plot options

        // --------------------------------------------------------------------
        //! default ctor
        // --------------------------------------------------------------------
        CompareRatiosParams() {
          denominators = Inputs();
          numerators   = Inputs();
          unity        = PlotShape();
          shapes       = Shapes();
          options      = PlotOpts();
        }

        // --------------------------------------------------------------------
        //! default dtor
        // --------------------------------------------------------------------
        ~CompareRatiosParams() {};

        // --------------------------------------------------------------------
        //! ctor accepting arguments
        // --------------------------------------------------------------------
        CompareRatiosParams(
          const Inputs& denom_args,
          const Inputs& numer_args,
          const PlotShape& unity_arg,
          const Shapes& shape_args,
          const PlotOpts& opt_args
        ) {
          denominators = denom_args;
          numerators   = numer_args;
          unity        = unity_arg;
          shapes       = shape_args;
          options      = opt_args;
        }  // end ctor(Inputs&, Inputs&, PlotShape&, Shapes&, PlotOpts&)'

      };  // end CompareRatiosParams

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
       *  \param[in]  param routine parameters
       *  \param[out] ofile file to write to
       */
      void PlotSpectra1D(
        const CompareSpectraParams& param,
        TFile* ofile
      ) const {

        // announce start
        std::cout << "\n -------------------------------- \n"
                  << "  Beginning spectra plotting!\n"
                  << "    Opening inputs:"
                  << std::endl;

        // open inputs
        std::vector<TFile*> ifiles;
        std::vector<TH1*>   ihists;
        for (std::size_t iin = 0; iin < param.inputs.size(); ++iin) {

          ifiles.push_back(
            Tools::OpenFile(param.inputs[iin].file, "read")
          );
          ihists.push_back(
            (TH1*) Tools::GrabObject( param.inputs[iin].object, ifiles.back() )
          );
          ihists.back() -> SetName( param.inputs[iin].rename.data() );
          std::cout << "      File = " << param.inputs[iin].file << "\n"
                    << "      Hist = " << param.inputs[iin].object
                    << std::endl;

          // normalize input if need be
          if (param.options.do_norm) {
            Tools::NormalizeByIntegral(
              ihists.back(),
              param.options.norm_to,
              param.options.norm_range.GetX().first,
              param.options.norm_range.GetX().second
            );
          }
        }  // end input loop

        // define legend dimensions
        const std::size_t nlines    = !param.options.header.empty() ? ihists.size() + 1 : ihists.size();
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
          legdef.AddEntry( Legend::Entry(ihists[ihst], param.inputs[ihst].legend, "PF") );
        }
        legdef.SetVertices( vtxleg );
        if (!param.options.header.empty()) {
          legdef.SetHeader( param.options.header );
        }

        // create root objects
        TLegend*   legend = legdef.MakeLegend();
        TPaveText* text   = m_textBox.MakeTPaveText();
        std::cout << "    Created legend and text box." << std::endl;

        // set hist styles
        Styles styles = GenerateStyles( param.inputs );
        for (std::size_t ihst = 0; ihst < ihists.size(); ++ihst) {
          styles[ihst].SetPlotStyle( param.inputs[ihst].style );
          styles[ihst].Apply( ihists[ihst] );
          param.options.plot_range.Apply(Range::X, ihists[ihst] -> GetXaxis());
          param.options.plot_range.Apply(Range::Y, ihists[ihst] -> GetYaxis());
        }

        // set legend/text styles
        m_baseTextStyle.Apply( legend );
        m_baseTextStyle.Apply( text );
        std::cout << "    Set styles." << std::endl;

        // draw plot
        PlotManager manager = PlotManager( param.options.canvas );
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

      }  // end 'PlotSpectra1D(CompareSpectraParams&, TFile*)'

      // ----------------------------------------------------------------------
      //! Compare various ENC (or othwerise) spectra to a baseline
      // ----------------------------------------------------------------------
      /*! Compares a variety of ENC (or otherwise) spectra from different
       *  sources to a baseline. Uppder panel shows spectra, lower panel
       *  shows ratio of spectra to baseline.
       *
       *  \param[in]  param routine parameters
       *  \param[out] ofile file to write to
       */
      void PlotSpectra1D(
        const SpectraVsBaselineParams& param,
        TFile* ofile
      ) const {

        // announce start
        std::cout << "\n -------------------------------- \n"
                  << "  Beginning spectra vs. baseline plotting!\n"
                  << "    Opening inputs:"
                  << std::endl;

        // open denominator input
        TFile* dfile = Tools::OpenFile( param.denominator.file, "read" );
        TH1*   dhist = (TH1*) Tools::GrabObject( param.denominator.object, dfile );
        dhist -> SetName( param.denominator.rename.data() );
        std::cout << "      File (denom) = " << param.denominator.file << "\n"
                  << "      Hist (denom) = " << param.denominator.object
                  << std::endl;

        // normalize denominator if need be
        if (param.options.do_norm) {
          Tools::NormalizeByIntegral(
            dhist,
            param.options.norm_to,
            param.options.norm_range.GetX().first,
            param.options.norm_range.GetX().second
          );
        }

        // open numerator inputs
        std::vector<TFile*> nfiles;
        std::vector<TH1*>   nhists;
        for (std::size_t inum = 0; inum < param.numerators.size(); ++inum) {

          nfiles.push_back(
            Tools::OpenFile(param.numerators[inum].file, "read")
          );
          nhists.push_back(
            (TH1*) Tools::GrabObject( param.numerators[inum].object, nfiles.back() )
          );
          nhists.back() -> SetName( param.numerators[inum].rename.data() );
          std::cout << "      File (numer) = " << param.numerators[inum].file << "\n"
                    << "      Hist (numer) = " << param.numerators[inum].object
                    << std::endl;

          // normalize numerator if need be
          if (param.options.do_norm) {
            Tools::NormalizeByIntegral(
              nhists.back(),
              param.options.norm_to,
              param.options.norm_range.GetX().first,
              param.options.norm_range.GetX().second
            );
          }
        }  // end numerator loop

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
        const std::size_t nlines    = !param.options.header.empty() ? nhists.size() + 2 : nhists.size() + 1;
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
        legdef.AddEntry( Legend::Entry(dhist, param.denominator.legend, "PF") ); 
        for (std::size_t inum = 0; inum < nhists.size(); ++inum) {
          legdef.AddEntry( Legend::Entry(nhists[inum], param.numerators[inum].legend, "PF") );
        }
        legdef.SetVertices( vtxleg );
        if (!param.options.header.empty()) {
          legdef.SetHeader( param.options.header );
        }

        // determine relevant range to draw line
        Shape unitydef = param.unity.shape;
        unitydef.SetXRange(
          Tools::GetDrawRange( param.options.plot_range.GetX(), rhists.front() -> GetXaxis() )
        );

        // create root objects
        TLine*     unity  = unitydef.MakeTLine();
        TLegend*   legend = legdef.MakeLegend();
        TPaveText* text   = m_textBox.MakeTPaveText();
        std::cout << "    Created legend and text box." << std::endl;

        // set denominator style
        Style den_style = m_basePlotStyle;
        den_style.SetPlotStyle( param.denominator.style );
        den_style.Apply( dhist );
        param.options.plot_range.Apply(Range::X, dhist -> GetXaxis());
        param.options.plot_range.Apply(Range::Y, dhist -> GetYaxis());

        // set numerator and ratio styles
        Styles num_styles = GenerateStyles( param.numerators );
        for (std::size_t inum = 0; inum < nhists.size(); ++inum) {
          num_styles[inum].SetPlotStyle( param.numerators[inum].style );
          num_styles[inum].Apply( nhists[inum] );
          num_styles[inum].Apply( rhists[inum] );
          param.options.plot_range.Apply(Range::X, nhists[inum] -> GetXaxis());
          param.options.plot_range.Apply(Range::Y, nhists[inum] -> GetYaxis());
          param.options.plot_range.Apply(Range::X, rhists[inum] -> GetXaxis());
        }

        // set legend/text styles
        param.unity.style.Apply( unity );
        m_baseTextStyle.Apply( legend );
        m_baseTextStyle.Apply( text );
        std::cout << "    Set styles." << std::endl;

        // draw plot
        //   - FIXME need to be able to specify labels from macro
        PlotManager manager = PlotManager( param.options.canvas );
        manager.MakePlot();
        manager.Draw();
        manager.GetTPad(0) -> cd();
        rhists[0] -> Draw();
        for (std::size_t irat = 1; irat < rhists.size(); ++irat) {
          rhists[irat] -> Draw("same");
        }
        unity -> Draw();
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
        Tools::CloseFiles(nfiles);
        dfile -> Close();
        return;

      }  // end 'PlotSpectra1D(SpectraVsBaselineParams&, TFile*)'

      // ----------------------------------------------------------------------
      //! Compare ratios of various pairs of ENC (or otherwise) spectra
      // ----------------------------------------------------------------------
      /*! Compares a variety of pairs of ENC (or otherwise) spectra from
       *  different sources and their ratios. Uppder panel shows spectra,
       *  lower panel shows ratios.
       *
       *  \param[in]  param routine parameters
       *  \param[out] ofile file to write to
       */
      void PlotSpectra1D(
        const CompareRatiosParams& param,
        TFile* ofile
      ) const {

        // announce start
        std::cout << "\n -------------------------------- \n"
                  << "  Beginning ratio comparison plotting!\n"
                  << "    Opening inputs:"
                  << std::endl;

        // throw error if no. of denominators and numerators don't match
        if (param.denominators.size() != param.numerators.size()) {
          std::cerr << "PANIC: number of denominators and numerators should be the same!\n"
                    << "       denominators = " << param.denominators.size() << "\n"
                    << "       numerators   = " << param.numerators.size()
                    << std::endl;
          assert(param.denominators.size() == param.numerators.size());
        }

        // open denominator inputs
        std::vector<TFile*> dfiles;
        std::vector<TH1*>   dhists;
        for (std::size_t iden = 0; iden < param.denominators.size(); ++iden) {

          dfiles.push_back(
            Tools::OpenFile(param.denominators[iden].file, "read")
          );
          dhists.push_back(
            (TH1*) Tools::GrabObject( param.denominators[iden].object, dfiles.back() )
          );
          dhists.back() -> SetName( param.denominators[iden].rename.data() );
          std::cout << "      File (denom) = " << param.denominators[iden].file << "\n"
                    << "      Hist (denom) = " << param.denominators[iden].object
                    << std::endl;

          // normalize denominaotr if need be
          if (param.options.do_norm) {
            Tools::NormalizeByIntegral(
              dhists.back(),
              param.options.norm_to,
              param.options.norm_range.GetX().first,
              param.options.norm_range.GetX().second
            );
          }
        }  // end denominator loop

        // open numerator inputs
        std::vector<TFile*> nfiles;
        std::vector<TH1*>   nhists;
        for (std::size_t inum = 0; inum < param.numerators.size(); ++inum) {

          nfiles.push_back(
            Tools::OpenFile(param.numerators[inum].file, "read")
          );
          nhists.push_back(
            (TH1*) Tools::GrabObject( param.numerators[inum].object, nfiles.back() )
          );
          nhists.back() -> SetName( param.numerators[inum].rename.data() );
          std::cout << "      File (numer) = " << param.numerators[inum].file << "\n"
                    << "      Hist (numer) = " << param.numerators[inum].object
                    << std::endl;

          // normalize numerator if need be
          if (param.options.do_norm) {
            Tools::NormalizeByIntegral(
              nhists.back(),
              param.options.norm_to,
              param.options.norm_range.GetX().first,
              param.options.norm_range.GetX().second
            );
          }
        }  // end numerator loop

        // take ratios
        std::vector<TH1*> rhists;
        for (std::size_t iden = 0; iden < nhists.size(); ++iden) {

          // create name
          std::string name( dhists[iden] -> GetName() );
          name += "_Ratio";

          // do division and apply style
          rhists.push_back( Tools::DivideHist1D( nhists[iden], dhists[iden]) );
          rhists.back() -> SetName( name.data() );
        }

        // determine no. of legend lines
        const std::size_t nlines = !param.options.header.empty()
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
          legdef.AddEntry( Legend::Entry(dhists[iden], param.denominators[iden].legend, "PF") );
          legdef.AddEntry( Legend::Entry(nhists[iden], param.numerators[iden].legend, "PF") );
        }
        legdef.SetVertices( vtxleg );
        if (!param.options.header.empty()) {
          legdef.SetHeader( param.options.header );
        }

        // determine relevant range to draw line
        Shape unitydef = param.unity.shape;
        unitydef.SetXRange(
          Tools::GetDrawRange( param.options.plot_range.GetX(), rhists.front() -> GetXaxis() )
        );

        // create root objects
        TLine*     unity   = unitydef.MakeTLine();
        TLegend*   legend = legdef.MakeLegend();
        TPaveText* text   = m_textBox.MakeTPaveText();
        std::cout << "    Created legend and text box." << std::endl;

        // set styles
        Styles den_styles = GenerateStyles( param.denominators );
        Styles num_styles = GenerateStyles( param.numerators );
        for (std::size_t iden = 0; iden < nhists.size(); ++iden) {

          // set denominator style
          den_styles[iden].SetPlotStyle( param.denominators[iden].style );
          den_styles[iden].Apply( dhists[iden] );
          param.options.plot_range.Apply(Range::X, dhists[iden] -> GetXaxis());
          param.options.plot_range.Apply(Range::Y, dhists[iden] -> GetXaxis());

          // set numerator style
          num_styles[iden].SetPlotStyle( param.numerators[iden].style );
          num_styles[iden].Apply( nhists[iden] );
          param.options.plot_range.Apply(Range::X, nhists[iden] -> GetXaxis());
          param.options.plot_range.Apply(Range::Y, nhists[iden] -> GetXaxis());

          // set ratio style
          den_styles[iden].Apply( rhists[iden] );
          param.options.plot_range.Apply(Range::X, rhists[iden] -> GetXaxis());
        }

        // set legend/text styles
        param.unity.style.Apply( unity );
        m_baseTextStyle.Apply( legend );
        m_baseTextStyle.Apply( text );
        std::cout << "    Set styles." << std::endl;

        // draw plot
        //   - FIXME need to be able to specify labels from macro
        PlotManager manager = PlotManager( param.options.canvas );
        manager.MakePlot();
        manager.Draw();
        manager.GetTPad(0) -> cd();
        rhists[0] -> Draw();
        for (std::size_t irat = 1; irat < rhists.size(); ++irat) {
          rhists[irat] -> Draw("same");
        }
        unity -> Draw();
        manager.GetTPad(1) -> cd();
        dhists[0] -> Draw();
        nhists[1] -> Draw();
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

      }  // end 'PlotSpectra1D(CompareRatiosParams&, TFile*)'

      // ----------------------------------------------------------------------
      //! Compare various 2D spectra
      // ----------------------------------------------------------------------
      /*! Compares a variety of 2D spectra from different sources.
       *
       *  \param[in]  param routine parameters
       *  \param[out] ofile file to write to
       */
      void PlotSpectra2D(
        const CompareSpectraParams& param,
        TFile* ofile
      ) const {

        // announce start
        std::cout << "\n -------------------------------- \n"
                  << "  Beginning 2D spectra plotting!\n"
                  << "    Opening inputs:"
                  << std::endl;

        // open inputs
        std::vector<TFile*> ifiles;
        std::vector<TH2*>   ihists;
        for (std::size_t iin = 0; iin < param.inputs.size(); ++iin) {

          ifiles.push_back(
            Tools::OpenFile(param.inputs[iin].file, "read")
          );
          ihists.push_back(
            (TH2*) Tools::GrabObject( param.inputs[iin].object, ifiles.back() )
          );
          ihists.back() -> SetName( param.inputs[iin].rename.data() );
          ihists.back() -> SetTitle( param.inputs[iin].legend.data() );
          std::cout << "      File = " << param.inputs[iin].file << "\n"
                    << "      Hist = " << param.inputs[iin].object
                    << std::endl;

          // normalize input if need be
          if (param.options.do_norm) {
            Tools::NormalizeByIntegral(
              ihists.back(),
              param.options.norm_to,
              param.options.norm_range.GetX().first,
              param.options.norm_range.GetX().second,
              param.options.norm_range.GetY().first,
              param.options.norm_range.GetY().second
            );
          }
        }  // end input loop

        // create text box
        TPaveText* text = m_textBox.MakeTPaveText();
        m_baseTextStyle.Apply( text );
        std::cout << "    Created text box." << std::endl;

        // set hist styles
        Styles styles = GenerateStyles( param.inputs );
        for (std::size_t ihst = 0; ihst < ihists.size(); ++ihst) {
          styles[ihst].SetPlotStyle( param.inputs[ihst].style );
          styles[ihst].Apply( ihists[ihst] );
          param.options.plot_range.Apply(Range::X, ihists[ihst] -> GetXaxis());
          param.options.plot_range.Apply(Range::Y, ihists[ihst] -> GetYaxis());
          param.options.plot_range.Apply(Range::Z, ihists[ihst] -> GetZaxis());
        }
        std::cout << "    Set styles." << std::endl;

        // draw plot
        PlotManager manager = PlotManager( param.options.canvas );
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
        Tools::CloseFiles(ifiles);
        return;

      }  // end 'PlotSpectra2D(CompareSpectraParams&, TFile*)'

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
