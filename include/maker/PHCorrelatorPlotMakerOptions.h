/// ===========================================================================
/*! \file   PHCorrelatorPlotMakerOptions.h
 *  \author Derek Anderson
 *  \date   02.05.2024
 *
 *  A small namespace to define options for
 *  various plotting routines.
 *
 *  FIXME THIS NEEDS TO GET MERGED WITH THE
 *  PLOT MAKER ROUTINES
 *
 *  FIXME AND THEN MAKE IT CONFIGURABLE FROM
 *  THE MACRO
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTMAKEROPTIONS_H
#define PHCORRELATORPLOTMAKEROPTIONS_H

// c++ utilities
#include <cmath>
#include <string>
#include <vector>
#include <utility>
// plotting utilities
#include "./PHCorrelatorPlotMaker.h"
#include "../elements/PHCorrelatorPlotterElements.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Plot Maker Options
  // ==========================================================================
  /*! This namespace collects all the parameters associated with
   *  the various `PlotMaker` routines.
   */
  namespace PlotMakerOptions {

    // ------------------------------------------------------------------------
    // Options for plot ranges
    // ------------------------------------------------------------------------
    /* FIXME should go in constants */
    enum RangeOpt {Side, Angle};



    // helper methods =========================================================

    std::size_t GetRowNumber(const std::size_t nhist, const std::size_t ncol) {

      const std::size_t div_one = (nhist / ncol) + 1;
      const std::size_t div_mod = (nhist / ncol) + (nhist % ncol);
      return min(div_one, div_mod);

    }  // end 'GetRowNumber(std::size_t, std::size_t)'



    // ------------------------------------------------------------------------
    //! Define plot range
    // ------------------------------------------------------------------------
    /*! Plot range arguments:
     *    first  = x range to plot
     *    second = y range to plot
     *    third  = z range to plot
     */ 
    Range DefinePlotRange(const int opt = Side) {

      Range range;
      switch (opt) {

        case Side:
          range = Range(
            std::make_pair(0.003, 3.),
            std::make_pair(0.00003, 0.7),
            std::make_pair(0.00003, 33.)
          );
          break;

        case Angle:
          range = Range(
            std::make_pair(0.0, 6.30),
            std::make_pair(-0.007, 0.07),
            std::make_pair(0.00003, 33.)
          );
          break;

        default:
          range = Range();
          std::cout << "WARNING: unknown option " << opt << "!" << std::endl;
          break;

      }
      return range;

    }  // end 'DefinePlotRange(int)'



    // ------------------------------------------------------------------------
    //! Define normalization range
    // ------------------------------------------------------------------------
    Range DefineNormRange(const int opt = Side) {

      // grab plot range
      Range plot_range = DefinePlotRange(opt);

      // set normalization range
      Range range = Range(plot_range.GetX());
      return range;

    }  // end 'DefineNormRange(int)'



    // ------------------------------------------------------------------------
    //! Define line for unit ratio
    // ------------------------------------------------------------------------
    PlotShape DefineUnity(const int opt = Side) {

      return PlotShape(
        Shape(DefinePlotRange(opt).GetX(), std::make_pair(1.0, 1.0)),
        Style::Plot(923, 1, 0, 9, 2)
      );

    }  // end 'DefineUnity(int)'



    // bundle parameters ======================================================

    // ------------------------------------------------------------------------
    //! Bundle 1D `CompareSpectra` parameters
    // ------------------------------------------------------------------------
    PlotMaker::CompareSpectraParams CompareSpectra1D(
      const Inputs& inputs,
      const std::string& canvas_name = "cSpectra1D",
      const int range_opt = Side
    ) {

      // grab default pad options, and
      // turn on log y
      PadOpts pad_opts = PadOpts();
      if (range_opt == Side) {
        pad_opts.logx = 1;
        pad_opts.logy = 1;
      }

      // set margins
      Type::Margins margins;
      margins.push_back(0.02);
      margins.push_back(0.02);
      margins.push_back(0.15);
      margins.push_back(0.15);

      // define canvas (use default pad options)
      Canvas canvas = Canvas(canvas_name, "", std::make_pair(750, 750), pad_opts);
      canvas.SetMargins( margins );

      // set auxilliary options
      PlotOpts plot_opts;
      plot_opts.plot_range = DefinePlotRange(range_opt);
      plot_opts.norm_range = DefineNormRange(range_opt);
      plot_opts.canvas     = canvas;

      // bundle parameters
      PlotMaker::CompareSpectraParams params;
      params.inputs  = inputs;
      params.options = plot_opts;
      return params;

    }  // end 'CompareSpectra1D(Inputs&, std::string&, int)'



    // ------------------------------------------------------------------------
    //! Bundle 2D `CompareSpectra` parameters
    // ------------------------------------------------------------------------
    PlotMaker::CompareSpectraParams CompareSpectra2D(
      const Inputs& inputs,
      const std::string& canvas_name = "cSpectra2D",
      const std::size_t ncolumn = 2
    ) {

      // grab default pad options, and
      // turn on log z
      PadOpts pad_opts = PadOpts();
      pad_opts.logx = 1;
      pad_opts.logz = 1;

      // basic dimension of each pad
      std::size_t pad_dim = 375;
      std::size_t nrow    = GetRowNumber(inputs.size(), ncolumn);

      // determine canvas dimensions
      const Type::Dimensions dimensions = std::make_pair(
        pad_dim * ncolumn,
        pad_dim * nrow
      );

      // determine vertices of pads
      std::vector<Type::Vertices> pad_vtxs;    
      for (std::size_t iin = 0; iin < inputs.size(); ++iin) {

        // get column/row indices
        const std::size_t icol = iin % ncolumn;
        const std::size_t irow = GetRowNumber(iin, ncolumn);

        // set x vertices
        const double startx = icol * (1.0 / (double) ncolumn);
        const double stopx  = (icol % ncolumn) * (1.0 / (double) ncolumn);

        // set y vertices
        const double starty = irow * (1.0 / (double) nrow);
        const double stopy  = (irow % nrow) * (1.0 / (double) nrow);

        // add to vector
        pad_vtxs.push_back( Type::Vertices() );
        pad_vtxs.back().push_back( startx );
        pad_vtxs.back().push_back( starty );
        pad_vtxs.back().push_back( stopx );
        pad_vtxs.back().push_back( stopy );
      }

      // set pad margins
      Type::Margins pad_margins;
      pad_margins.push_back(0.15);
      pad_margins.push_back(0.15);
      pad_margins.push_back(0.15);
      pad_margins.push_back(0.15);

      // define canvas (use default pad options)
      Canvas canvas = Canvas(canvas_name, "", dimensions, PadOpts());
      for (std::size_t iin = 0; iin < inputs.size(); ++iin) {

        // create name
        TString tname("pSpec");
        tname += iin;

        // add pad
        canvas.AddPad(
          Pad(
            std::string(tname.Data()),
            "",
            pad_vtxs[iin],
            pad_margins,
            pad_opts
          )
        );
      }

      // set ranges
      const Range plot_range = Range(
        DefinePlotRange(Side).GetX(),
        DefinePlotRange(Angle).GetY(),
        DefinePlotRange(Side).GetZ()
      );
      const Range norm_range = plot_range;

      // set auxilliary options
      PlotOpts plot_opts;
      plot_opts.plot_range = plot_range;
      plot_opts.norm_range = norm_range;
      plot_opts.canvas     = canvas;

      // bundle parameters
      PlotMaker::CompareSpectraParams params;
      params.inputs  = inputs;
      params.options = plot_opts;
      return params;

    }  // end 'CompareSpectra2D(Inputs&, std::string&)'



    // ------------------------------------------------------------------------
    //! Bundle 1D `CompareRatios` parameters
    // ------------------------------------------------------------------------
    PlotMaker::CompareRatiosParams CompareRatios1D(
      const Inputs& in_denoms,
      const Inputs& in_numers,
      const std::string& canvas_name = "cCompareRatios1D",
      const int range_opt = Side
    ) {

      // grab default pad options, and
      // turn on log y/x when necessary
      PadOpts ratio_opts = PadOpts();
      PadOpts spect_opts = PadOpts();
      if (range_opt == Side) {
        ratio_opts.logx = 1;
        spect_opts.logx = 1;
        spect_opts.logy = 1;
      }

      // set pad vertices
      Type::Vertices ratio_vtxs;
      ratio_vtxs.push_back(0.00);
      ratio_vtxs.push_back(0.00);
      ratio_vtxs.push_back(1.00);
      ratio_vtxs.push_back(0.35);

      Type::Vertices spect_vtxs;
      spect_vtxs.push_back(0.00);
      spect_vtxs.push_back(0.35);
      spect_vtxs.push_back(1.00);
      spect_vtxs.push_back(1.00);

      // set spectra margins
      Type::Margins ratio_margins;
      ratio_margins.push_back(0.005);
      ratio_margins.push_back(0.02);
      ratio_margins.push_back(0.25);
      ratio_margins.push_back(0.15);

      Type::Margins spect_margins;
      spect_margins.push_back(0.02);
      spect_margins.push_back(0.02);
      spect_margins.push_back(0.005);
      spect_margins.push_back(0.15);

      // define canvas (use default pad options)
      Canvas canvas = Canvas(canvas_name, "", std::make_pair(750, 1125), PadOpts());
      canvas.AddPad( Pad("pRatio",   "", ratio_vtxs, ratio_margins, ratio_opts), "ratio" );
      canvas.AddPad( Pad("pSpectra", "", spect_vtxs, spect_margins, spect_opts), "spectra" );

      // set auxilliary options
      PlotOpts plot_opts;
      plot_opts.plot_range  = DefinePlotRange(range_opt);
      plot_opts.norm_range  = DefineNormRange(range_opt);
      plot_opts.canvas      = canvas;
      plot_opts.ratio_pad   = "ratio";
      plot_opts.spectra_pad = "spectra";

      // bundle parameters
      PlotMaker::CompareRatiosParams params;
      params.denominators = in_denoms;
      params.numerators   = in_numers;
      params.options      = plot_opts;
      params.unity        = DefineUnity(range_opt);
      return params;

    }  // end 'CompareRatios1D(Inputs& x 2, std::string&, int)'



    // ------------------------------------------------------------------------
    //! Bundle `SpectraVsBaseline` parameters
    // ------------------------------------------------------------------------
    PlotMaker::SpectraVsBaselineParams SpectraVsBaseline(
      const PlotInput& in_denom,
      const Inputs& in_numers,
      const std::string& canvas_name = "cSpectraVsBaseline",
      const int range_opt = Side
    ) {

      // grab default pad options, and
      // turn on log y/x when necessary
      PadOpts ratio_opts = PadOpts();
      PadOpts spect_opts = PadOpts();
      if (range_opt == Side) {
        ratio_opts.logx = 1;
        spect_opts.logx = 1;
        spect_opts.logy = 1;
      }

      // set pad vertices
      Type::Vertices ratio_vtxs;
      ratio_vtxs.push_back(0.00);
      ratio_vtxs.push_back(0.00);
      ratio_vtxs.push_back(1.00);
      ratio_vtxs.push_back(0.35);

      Type::Vertices spect_vtxs;
      spect_vtxs.push_back(0.00);
      spect_vtxs.push_back(0.35);
      spect_vtxs.push_back(1.00);
      spect_vtxs.push_back(1.00);

      // set spectra margins
      Type::Margins ratio_margins;
      ratio_margins.push_back(0.005);
      ratio_margins.push_back(0.02);
      ratio_margins.push_back(0.25);
      ratio_margins.push_back(0.15);

      Type::Margins spect_margins;
      spect_margins.push_back(0.02);
      spect_margins.push_back(0.02);
      spect_margins.push_back(0.005);
      spect_margins.push_back(0.15);

      // define canvas (use default pad options)
      Canvas canvas = Canvas(canvas_name, "", std::make_pair(750, 1125), PadOpts());
      canvas.AddPad( Pad("pRatio",   "", ratio_vtxs, ratio_margins, ratio_opts), "ratio" );
      canvas.AddPad( Pad("pSpectra", "", spect_vtxs, spect_margins, spect_opts), "spectra" );

      // set auxilliary options
      PlotOpts plot_opts;
      plot_opts.plot_range  = DefinePlotRange(range_opt);
      plot_opts.norm_range  = DefineNormRange(range_opt);
      plot_opts.canvas      = canvas;
      plot_opts.ratio_pad   = "ratio";
      plot_opts.spectra_pad = "spectra";

      // bundle parameters
      PlotMaker::SpectraVsBaselineParams params;
      params.denominator = in_denom;
      params.numerators  = in_numers;
      params.options     = plot_opts;
      params.unity       = DefineUnity(range_opt);
      return params;

    }  // end 'SpectraVsBaseline(PlotInput&, Inputs&, std::string&, int)'



    // ------------------------------------------------------------------------
    //! Bundle `CompareRatios` parameters
    // ------------------------------------------------------------------------
    PlotMaker::CompareRatiosParams CompareRatios(
      const Inputs& in_denoms,
      const Inputs& in_numers,
      const std::string& canvas_name = "cRatios",
      const int range_opt = Side
    ) {

      // grab default pad options, and
      // turn on log y/x when necessary
      PadOpts ratio_opts = PadOpts();
      PadOpts spect_opts = PadOpts();
      if (range_opt == Side) {
        ratio_opts.logx = 1;
        spect_opts.logx = 1;
        spect_opts.logy = 1;
      }

      // set pad vertices
      Type::Vertices ratio_vtxs;
      ratio_vtxs.push_back(0.00);
      ratio_vtxs.push_back(0.00);
      ratio_vtxs.push_back(1.00);
      ratio_vtxs.push_back(0.35);

      Type::Vertices spect_vtxs;
      spect_vtxs.push_back(0.00);
      spect_vtxs.push_back(0.35);
      spect_vtxs.push_back(1.00);
      spect_vtxs.push_back(1.00);

      // set spectra margins
      Type::Margins ratio_margins;
      ratio_margins.push_back(0.005);
      ratio_margins.push_back(0.02);
      ratio_margins.push_back(0.25);
      ratio_margins.push_back(0.15);

      Type::Margins spect_margins;
      spect_margins.push_back(0.02);
      spect_margins.push_back(0.02);
      spect_margins.push_back(0.005);
      spect_margins.push_back(0.15);

      // define canvas (use default pad options)
      Canvas canvas = Canvas(canvas_name, "", std::make_pair(750, 1125), PadOpts());
      canvas.AddPad( Pad("pRatio",   "", ratio_vtxs, ratio_margins, ratio_opts), "ratio" );
      canvas.AddPad( Pad("pSpectra", "", spect_vtxs, spect_margins, spect_opts), "spectra" );

      // set auxilliary options
      PlotOpts plot_opts;
      plot_opts.plot_range  = DefinePlotRange(range_opt);
      plot_opts.norm_range  = DefineNormRange(range_opt);
      plot_opts.canvas      = canvas;
      plot_opts.ratio_pad   = "ratio";
      plot_opts.spectra_pad = "spectra";

      // bundle parameters
      PlotMaker::CompareRatiosParams params;
      params.denominators = in_denoms;
      params.numerators   = in_numers;
      params.options      = plot_opts;
      params.unity        = DefineUnity(range_opt);
      return params;

    }  // end 'CompareRatios(Inputs&, Inputs&, std::string&, int)'



    // ------------------------------------------------------------------------
    //! Bundle 1D `CorrectSpectra` parameters
    // ------------------------------------------------------------------------
    PlotMaker::CorrectSpectraParams CorrectSpectra1D(
      const Inputs& in_data,
      const Inputs& in_reco,
      const Inputs& in_true,
      const std::string& canvas_name = "cCorrectSpectra1D",
      const int range_opt = Side
    ) {

      // grab default pad options, and
      // turn on log y/x when necessary
      PadOpts rat_opts  = PadOpts();
      PadOpts corr_opts = PadOpts();
      PadOpts spec_opts = PadOpts();
      if (range_opt == Side) {
        rat_opts.logx  = 1;
        corr_opts.logx = 1;
        spec_opts.logx = 1;
        spec_opts.logy = 1;
      }

      // set pad vertices
      Type::Vertices corr_vtxs;
      corr_vtxs.push_back(0.00);
      corr_vtxs.push_back(0.00);
      corr_vtxs.push_back(1.00);
      corr_vtxs.push_back(0.25);

      Type::Vertices rat_vtxs;
      rat_vtxs.push_back(0.00);
      rat_vtxs.push_back(0.25);
      rat_vtxs.push_back(1.00);
      rat_vtxs.push_back(0.50);

      Type::Vertices spec_vtxs;
      spec_vtxs.push_back(0.00);
      spec_vtxs.push_back(0.50);
      spec_vtxs.push_back(1.00);
      spec_vtxs.push_back(1.00);

      // set spectra margins
      Type::Margins corr_margins;
      corr_margins.push_back(0.005);
      corr_margins.push_back(0.02);
      corr_margins.push_back(0.25);
      corr_margins.push_back(0.15);

      Type::Margins rat_margins;
      rat_margins.push_back(0.005);
      rat_margins.push_back(0.02);
      rat_margins.push_back(0.005);
      rat_margins.push_back(0.15);

      Type::Margins spec_margins;
      spec_margins.push_back(0.02);
      spec_margins.push_back(0.02);
      spec_margins.push_back(0.005);
      spec_margins.push_back(0.15);

      // define canvas (use default pad options)
      Canvas canvas = Canvas(canvas_name, "", std::make_pair(750, 1125), PadOpts());
      canvas.AddPad( Pad("pCorrect", "", corr_vtxs, corr_margins, corr_opts), "correct" );
      canvas.AddPad( Pad("pRatio",   "", rat_vtxs,  rat_margins,  rat_opts),  "ratio");
      canvas.AddPad( Pad("pSpectra", "", spec_vtxs, spec_margins, spec_opts), "spectra" );

      // set auxilliary options
      PlotOpts plot_opts;
      plot_opts.plot_range  = DefinePlotRange(range_opt);
      plot_opts.norm_range  = DefineNormRange(range_opt);
      plot_opts.canvas      = canvas;
      plot_opts.correct_pad = "correct";
      plot_opts.ratio_pad   = "ratio";
      plot_opts.spectra_pad = "spectra";

      // bundle parameters
      PlotMaker::CorrectSpectraParams params;
      params.data    = in_data;
      params.recon   = in_reco;
      params.truth   = in_true;
      params.options = plot_opts;
      params.unity   = DefineUnity(range_opt);
      return params;

    }  // end 'CorrectSpectra1D(Inputs& x 3, std::string&, int)'

  }  // end PlotMakerOptions namespace
}  // end PHEnergyCorrelator namespace 

#endif


/// end =======================================================================
