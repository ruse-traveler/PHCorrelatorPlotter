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
#include "PHCorrelatorCanvasManager.h"
#include "PHCorrelatorLegend.h"
#include "PHCorrelatorPlotInput.h"
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
      /*! Struct to consolidate parameters for the "Compare Spectra to Baseline"
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
      /*! Struct to consolidate parameters for the "Compare Ratios"
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

      // ======================================================================
      //! Parameters for correcting a spectrum (or spectra)
      // ======================================================================
      /*! Struct to consolidate parameters for the "Correct Spectra"
       *  plotting routines.
       */ 
      struct CorrectSpectraParams {

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
        CorrectSpectraParams() {
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
        ~CorrectSpectraParams() {};

        // --------------------------------------------------------------------
        //! ctor accepting arguments
        // --------------------------------------------------------------------
        CorrectSpectraParams(
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

      };  // end CorrectSpectraParams

      // ======================================================================
      //! Parameters for EEC vs. angle projection plot
      // ======================================================================
      /*! Struct to consolidate parameters for the "Project EEC vs. Angle"
       *  plotting routine.
       */
      struct ProjectEECVsAngleParams {

        // --------------------------------------------------------------------
        //! default ctor
        // --------------------------------------------------------------------
        ProjectEECVsAngleParams() {
        }  // end ctor

        // --------------------------------------------------------------------
        //! default dtor
        // --------------------------------------------------------------------
        ~ProjectEECVsAngleParams() {};

        // --------------------------------------------------------------------
        //! ctor accepting arguments
        // --------------------------------------------------------------------
/* TODO
        ProjectEECVsAngleParams(
          const PlotInput& input,
          const S
        ) {
        }  // end ctor(...)
*/

      };  // end ProjectEECVsAngleParams

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

        // determine no. of legend lines
        const std::size_t nlines = !param.options.header.empty()
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
        CanvasManager manager = CanvasManager( param.options.canvas );
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
       *  sources to a baseline. Upper panel shows spectra, lower panel
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

          // do division
          rhists.push_back( Tools::DivideHist1D( nhists[inum], dhist) );
          rhists.back() -> SetName( name.data() );
        }
        std::cout << "    Calculated ratios." << std::endl;

        // determine no. of legend lines
        const std::size_t nlines = !param.options.header.empty()
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

        // initialize canvas manager
        CanvasManager manager = CanvasManager( param.options.canvas );
        manager.MakePlot();

        // scale text of objects in smaller panels
        for (std::size_t irat = 0; irat < rhists.size(); ++irat) {
          manager.ScaleAxisText(
            param.options.spectra_pad,
            param.options.ratio_pad,
            Range::X,
            rhists[irat] -> GetXaxis()
          );
          manager.ScaleAxisText(
            param.options.spectra_pad,
            param.options.ratio_pad,
            Range::Y,
            rhists[irat] -> GetYaxis()
          );
        }

        // draw objects
        manager.Draw();
        manager.GetTPad( param.options.ratio_pad ) -> cd();
        rhists[0] -> Draw();
        for (std::size_t irat = 1; irat < rhists.size(); ++irat) {
          rhists[irat] -> Draw("same");
        }
        unity -> Draw();
        manager.GetTPad( param.options.spectra_pad ) -> cd();
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
       *  different sources and their ratios. Upper panel shows spectra,
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

          // do division
          rhists.push_back( Tools::DivideHist1D( nhists[iden], dhists[iden]) );
          rhists.back() -> SetName( name.data() );
        }
        std::cout << "    Calculated ratios." << std::endl;

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
        TLine*     unity  = unitydef.MakeTLine();
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
          param.options.plot_range.Apply(Range::Y, dhists[iden] -> GetYaxis());

          // set numerator style
          num_styles[iden].SetPlotStyle( param.numerators[iden].style );
          num_styles[iden].Apply( nhists[iden] );
          param.options.plot_range.Apply(Range::X, nhists[iden] -> GetXaxis());
          param.options.plot_range.Apply(Range::Y, nhists[iden] -> GetYaxis());

          // set ratio style
          den_styles[iden].Apply( rhists[iden] );
          param.options.plot_range.Apply(Range::X, rhists[iden] -> GetXaxis());
        }

        // set legend/text styles
        param.unity.style.Apply( unity );
        m_baseTextStyle.Apply( legend );
        m_baseTextStyle.Apply( text );
        std::cout << "    Set styles." << std::endl;

        // initialize canvas manager
        CanvasManager manager = CanvasManager( param.options.canvas );
        manager.MakePlot();

        // scale text of objects in smaller panels
        for (std::size_t irat = 0; irat < rhists.size(); ++irat) {
          manager.ScaleAxisText(
            param.options.spectra_pad,
            param.options.ratio_pad,
            Range::X,
            rhists[irat] -> GetXaxis()
          );
          manager.ScaleAxisText(
            param.options.spectra_pad,
            param.options.ratio_pad,
            Range::Y,
            rhists[irat] -> GetYaxis()
          );
        }

        // draw objects
        manager.Draw();
        manager.GetTPad( param.options.ratio_pad ) -> cd();
        rhists[0] -> Draw();
        for (std::size_t irat = 1; irat < rhists.size(); ++irat) {
          rhists[irat] -> Draw("same");
        }
        unity -> Draw();
        manager.GetTPad( param.options.spectra_pad ) -> cd();
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
        CanvasManager manager = CanvasManager( param.options.canvas );
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

      }  // end 'PlotSpectra2D(CompareSpectraParams&, TFile*)'

      // ----------------------------------------------------------------------
      //! Correct various 1D spectra
      // ----------------------------------------------------------------------
      /*! Calculates and applies a bin-by-bin correction to a variety of ENC
       *  (or otherwise) spectra from different sources and their ratios. Upper
       *  panel shows corrected spectra vs truth, and lwer panel shows
       *  correction factors.
       *
       *  \param[in]  param routine parameters
       *  \param[out] ofile file to write to
       */
      void PlotSpectra1D(
        const CorrectSpectraParams& param,
        TFile* ofile
      ) const {

        // announce start
        std::cout << "\n -------------------------------- \n"
                  << "  Beginning 1D spectra correction!\n"
                  << "    Opening inputs:"
                  << std::endl;

        // throw error if no. of reco vs. truth inputs don't match
        if (param.recon.size() != param.truth.size()) {
          std::cerr << "PANIC: number of reconstructed and truth inputs should be the same!\n"
                    << "       reco inputs = " << param.recon.size() << "\n"
                    << "       true inputs = " << param.truth.size()
                    << std::endl;
          assert(param.recon.size() == param.truth.size());
        }

        // throw error if no. of data vs. reco inputs don't match
        if (param.data.size() != param.recon.size()) {
          std::cerr << "PANIC: number of raw and reconstructed inputs should be the same!\n"
                    << "       data inputs = " << param.data.size() << "\n"
                    << "       reco inputs = " << param.recon.size()
                    << std::endl;
          assert(param.data.size() == param.recon.size());
        }

        // open data inputs
        std::vector<TFile*> dfiles;
        std::vector<TH1*>   dhists;
        for (std::size_t idat = 0; idat < param.data.size(); ++idat) {

          dfiles.push_back(
            Tools::OpenFile(param.data[idat].file, "read")
          );
          dhists.push_back(
            (TH1*) Tools::GrabObject( param.data[idat].object, dfiles.back() )
          );
          dhists.back() -> SetName( param.data[idat].rename.data() );
          std::cout << "      File (data) = " << param.data[idat].file << "\n"
                    << "      Hist (data) = " << param.data[idat].object
                    << std::endl;
        }  // end data loop

        // open reco inputs
        std::vector<TFile*> rfiles;
        std::vector<TH1*>   rhists;
        for (std::size_t irec = 0; irec < param.recon.size(); ++irec) {

          rfiles.push_back(
            Tools::OpenFile(param.recon[irec].file, "read")
          );
          rhists.push_back(
            (TH1*) Tools::GrabObject( param.recon[irec].object, rfiles.back() )
          );
          rhists.back() -> SetName( param.recon[irec].rename.data() );
          std::cout << "      File (recon) = " << param.recon[irec].file << "\n"
                    << "      Hist (recon) = " << param.recon[irec].object
                    << std::endl;

          // normalize reco if need be
          if (param.options.do_norm) {
            Tools::NormalizeByIntegral(
              rhists.back(),
              param.options.norm_to,
              param.options.norm_range.GetX().first,
              param.options.norm_range.GetX().second
            );
          }
        }  // end reco loop

        // open true inputs
        std::vector<TFile*> tfiles;
        std::vector<TH1*>   thists;
        for (std::size_t itru = 0; itru < param.truth.size(); ++itru) {

          tfiles.push_back(
            Tools::OpenFile(param.truth[itru].file, "read")
          );
          thists.push_back(
            (TH1*) Tools::GrabObject( param.truth[itru].object, tfiles.back() )
          );
          thists.back() -> SetName( param.truth[itru].rename.data() );
          std::cout << "      File (truth) = " << param.truth[itru].file << "\n"
                    << "      Hist (truth) = " << param.truth[itru].object
                    << std::endl;

          // normalize true if need be
          if (param.options.do_norm) {
            Tools::NormalizeByIntegral(
              thists.back(),
              param.options.norm_to,
              param.options.norm_range.GetX().first,
              param.options.norm_range.GetX().second
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
          if (param.options.do_norm) {
            Tools::NormalizeByIntegral(
              dhists[idat],
              param.options.norm_to,
              param.options.norm_range.GetX().first,
              param.options.norm_range.GetX().second
            );
          }
        }
        std::cout << "    Applied correction factors." << std::endl;

        // calculate corrected / truth ratios ('f' for "fraction")
        std::vector<TH1*> fhists;
        for (std::size_t idat = 0; idat < dhists.size(); ++idat) {

          // create name
          std::string name( param.data[idat].rename );
          name += "_CorrectOverTruth";

          // do division
          fhists.push_back( Tools::DivideHist1D(dhists[idat], thists[idat]) );
          fhists.back() -> SetName( name.data() );
        }
        std::cout << "    Calculated corrected / truth ratios." << std::endl;

        // determine no. of legend lines
        const std::size_t nlines = !param.options.header.empty()
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
          legdef.AddEntry( Legend::Entry(dhists[idat], param.data[idat].legend,  "PF") );
          legdef.AddEntry( Legend::Entry(thists[idat], param.truth[idat].legend, "PF") );
        }
        legdef.SetVertices( vtxleg );
        if (!param.options.header.empty()) {
          legdef.SetHeader( param.options.header );
        }

        // determine relevant range to draw line
        Shape unitydef = param.unity.shape;
        unitydef.SetXRange(
          Tools::GetDrawRange( param.options.plot_range.GetX(), chists.front() -> GetXaxis() )
        );

        // create root objects
        TLine*     unity  = unitydef.MakeTLine();
        TLegend*   legend = legdef.MakeLegend();
        TPaveText* text   = m_textBox.MakeTPaveText();
        std::cout << "    Created legend and text box." << std::endl;

        // set styles
        Styles dat_styles = GenerateStyles( param.data );
        Styles tru_styles = GenerateStyles( param.truth );
        for (std::size_t idat = 0; idat < dhists.size(); ++idat) {

          // set data styles
          dat_styles[idat].SetPlotStyle( param.data[idat].style );
          dat_styles[idat].Apply( dhists[idat] );
          param.options.plot_range.Apply(Range::X, dhists[idat] -> GetXaxis());
          param.options.plot_range.Apply(Range::Y, dhists[idat] -> GetYaxis());

          // set truth styles
          tru_styles[idat].SetPlotStyle( param.truth[idat].style );
          tru_styles[idat].Apply( thists[idat] );
          param.options.plot_range.Apply(Range::X, thists[idat] -> GetXaxis());
          param.options.plot_range.Apply(Range::Y, thists[idat] -> GetYaxis());

          // set correction factor styles
          dat_styles[idat].Apply( chists[idat] );
          param.options.plot_range.Apply(Range::X, chists[idat] -> GetXaxis());

          // set ratio styles
          tru_styles[idat].Apply( fhists[idat] );
          param.options.plot_range.Apply(Range::X, fhists[idat] -> GetXaxis()); 
        }

        // set legend/text styles
        param.unity.style.Apply( unity );
        m_baseTextStyle.Apply( legend );
        m_baseTextStyle.Apply( text );
        std::cout << "    Set styles." << std::endl;

        // initialize canvas manager
        CanvasManager manager = CanvasManager( param.options.canvas );
        manager.MakePlot();

        // scale text of objects in smaller panels
        for (std::size_t icor = 0; icor < chists.size(); ++icor) {

          // scale correction factors
          manager.ScaleAxisText(
            param.options.spectra_pad,
            param.options.correct_pad,
            Range::X,
            chists[icor] -> GetXaxis()
          );
          manager.ScaleAxisText(
            param.options.spectra_pad,
            param.options.correct_pad,
            Range::Y,
            chists[icor] -> GetYaxis()
          );

          // scale ratios
          manager.ScaleAxisText(
            param.options.spectra_pad,
            param.options.ratio_pad,
            Range::X,
            fhists[icor] -> GetXaxis()
          );
          manager.ScaleAxisText(
            param.options.spectra_pad,
            param.options.ratio_pad,
            Range::Y,
            fhists[icor] -> GetYaxis()
          );
        }

        // draw objects
        //   - FIXME option should be configurable
        manager.Draw();
        manager.GetTPad( param.options.correct_pad ) -> cd();
        chists[0] -> Draw("hist");
        for (std::size_t icor = 1; icor < chists.size(); ++icor) {
          chists[icor] -> Draw("hist same");
        }
        unity -> Draw();
        manager.GetTPad( param.options.ratio_pad ) -> cd();
        fhists[0] -> Draw();
        for (std::size_t irat = 1; irat < fhists.size(); ++irat) {
          fhists[irat] -> Draw("same");
        }
        unity -> Draw();
        manager.GetTPad( param.options.spectra_pad ) -> cd();
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

      }  // end 'PlotSpectra1D(CorrectSpectraParams&, TFile*)'

      // ----------------------------------------------------------------------
      //! Correct various 2D spectra
      // ----------------------------------------------------------------------
      /*! Calculates and applies a bin-by-bin correction to a variety of ENC
       *  (or otherwise) spectra from different sources and their ratios. Upper
       *  panel shows corrected spectra vs truth, and lwer panel shows
       *  correction factors.
       *
       *  \param[in]  param routine parameters
       *  \param[out] ofile file to write to
       */
      void PlotSpectra2D(
        const CorrectSpectraParams& param,
        TFile* ofile
      ) const {

        // announce start
        std::cout << "\n -------------------------------- \n"
                  << "  Beginning 2D spectra correction!\n"
                  << "    Opening inputs:"
                  << std::endl;

        // throw error if no. of reco vs. truth inputs don't match
        if (param.recon.size() != param.truth.size()) {
          std::cerr << "PANIC: number of reconstructed and truth inputs should be the same!\n"
                    << "       reco inputs = " << param.recon.size() << "\n"
                    << "       true inputs = " << param.truth.size()
                    << std::endl;
          assert(param.recon.size() == param.truth.size());
        }

        // throw error if no. of data vs. reco inputs don't match
        if (param.data.size() != param.recon.size()) {
          std::cerr << "PANIC: number of raw and reconstructed inputs should be the same!\n"
                    << "       data inputs = " << param.data.size() << "\n"
                    << "       reco inputs = " << param.recon.size()
                    << std::endl;
          assert(param.data.size() == param.recon.size());
        }

        // open data inputs
        std::vector<TFile*> dfiles;
        std::vector<TH2*>   dhists;
        for (std::size_t idat = 0; idat < param.data.size(); ++idat) {

          dfiles.push_back(
            Tools::OpenFile(param.data[idat].file, "read")
          );
          dhists.push_back(
            (TH2*) Tools::GrabObject( param.data[idat].object, dfiles.back() )
          );
          dhists.back() -> SetName( param.data[idat].rename.data() );
          dhists.back() -> SetTitle( param.data[idat].legend.data() );
          std::cout << "      File (data) = " << param.data[idat].file << "\n"
                    << "      Hist (data) = " << param.data[idat].object
                    << std::endl;
        }  // end data loop

        // open reco inputs
        std::vector<TFile*> rfiles;
        std::vector<TH2*>   rhists;
        for (std::size_t irec = 0; irec < param.recon.size(); ++irec) {

          rfiles.push_back(
            Tools::OpenFile(param.recon[irec].file, "read")
          );
          rhists.push_back(
            (TH2*) Tools::GrabObject( param.recon[irec].object, rfiles.back() )
          );
          rhists.back() -> SetName( param.recon[irec].rename.data() );
          rhists.back() -> SetTitle( param.recon[irec].legend.data() );
          std::cout << "      File (recon) = " << param.recon[irec].file << "\n"
                    << "      Hist (recon) = " << param.recon[irec].object
                    << std::endl;

          // normalize reco if need be
          if (param.options.do_norm) {
            Tools::NormalizeByIntegral(
              rhists.back(),
              param.options.norm_to,
              param.options.norm_range.GetX().first,
              param.options.norm_range.GetX().second
            );
          }
        }  // end reco loop

        // open true inputs
        std::vector<TFile*> tfiles;
        std::vector<TH2*>   thists;
        for (std::size_t itru = 0; itru < param.truth.size(); ++itru) {

          tfiles.push_back(
            Tools::OpenFile(param.truth[itru].file, "read")
          );
          thists.push_back(
            (TH2*) Tools::GrabObject( param.truth[itru].object, tfiles.back() )
          );
          thists.back() -> SetName( param.truth[itru].rename.data() );
          thists.back() -> SetTitle( param.truth[itru].legend.data() );
          std::cout << "      File (truth) = " << param.truth[itru].file << "\n"
                    << "      Hist (truth) = " << param.truth[itru].object
                    << std::endl;

          // normalize true if need be
          if (param.options.do_norm) {
            Tools::NormalizeByIntegral(
              thists.back(),
              param.options.norm_to,
              param.options.norm_range.GetX().first,
              param.options.norm_range.GetX().second
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
          dhists[idat] -> SetTitle( param.data[idat].legend.data() );

          // normalize corrected spectrum if need be
          if (param.options.do_norm) {
            Tools::NormalizeByIntegral(
              dhists[idat],
              param.options.norm_to,
              param.options.norm_range.GetX().first,
              param.options.norm_range.GetX().second
            );
          }
        }
        std::cout << "    Applied correction factors." << std::endl;

        // calculate corrected / truth ratios ('f' for "fraction")
        std::vector<TH2*> fhists;
        for (std::size_t idat = 0; idat < dhists.size(); ++idat) {

          // create name
          std::string name( param.data[idat].rename );
          name += "_CorrectOverTruth";

          // do division
          fhists.push_back( Tools::DivideHist2D(dhists[idat], thists[idat]) );
          fhists.back() -> SetName( name.data() );
          fhists.back() -> SetTitle( "Corrected / Truth" );
        }
        std::cout << "    Calculated corrected / truth ratios." << std::endl;

        // determine no. of legend lines
        const std::size_t nlines = !param.options.header.empty()
                                 ? dhists.size() + thists.size() + 1
                                 : dhists.size() + thists.size();

        // create root objects
        TPaveText* text = m_textBox.MakeTPaveText();
        std::cout << "    Created legend and text box." << std::endl;

        // set styles
        Styles dat_styles = GenerateStyles( param.data );
        Styles tru_styles = GenerateStyles( param.truth );
        for (std::size_t idat = 0; idat < dhists.size(); ++idat) {

          // set data styles
          dat_styles[idat].SetPlotStyle( param.data[idat].style );
          dat_styles[idat].Apply( dhists[idat] );
          param.options.plot_range.Apply(Range::X, dhists[idat] -> GetXaxis());
          param.options.plot_range.Apply(Range::Y, dhists[idat] -> GetYaxis());

          // set truth styles
          tru_styles[idat].SetPlotStyle( param.truth[idat].style );
          tru_styles[idat].Apply( thists[idat] );
          param.options.plot_range.Apply(Range::X, thists[idat] -> GetXaxis());
          param.options.plot_range.Apply(Range::Y, thists[idat] -> GetYaxis());

          // set correction factor styles
          dat_styles[idat].Apply( chists[idat] );
          param.options.plot_range.Apply(Range::X, chists[idat] -> GetXaxis());

          // set ratio styles
          tru_styles[idat].Apply( fhists[idat] );
          param.options.plot_range.Apply(Range::X, fhists[idat] -> GetXaxis()); 
        }

        // set text styles
        m_baseTextStyle.Apply( text );
        std::cout << "    Set styles." << std::endl;

        // initialize canvas manager
        CanvasManager manager = CanvasManager( param.options.canvas );
        manager.MakePlot();

        // throw error if not enough pads are present for histograms
        if (manager.GetTPads().size() < (3 * dhists.size())) {
          std::cerr << "PANIC: more histograms to draw than pads in " << manager.GetTCanvas() -> GetName() << "!" << std::endl;
          assert(manager.GetTPads().size() >= (3 * dhists.size()));
        }

        // draw objects
        //   - FIXME option should be configurable
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

      }  // end 'PlotSpectra1D(CorrectSpectraParams&, TFile*)'

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
