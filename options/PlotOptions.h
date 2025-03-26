/// ===========================================================================
/*! \file   PlotOptions.h
 *  \author Derek Anderson
 *  \date   02.05.2024
 *
 *  A small namespace to define options for
 *  various plotting routines.
 */
/// ===========================================================================

#ifndef PLOTOPTIONS_H
#define PLOTOPTIONS_H

// c++ utilities
#include <cmath>
#include <string>
#include <vector>
#include <utility>
// plotting utilities
#include "../include/PHCorrelatorPlotter.h"



// ============================================================================
//! Plot Options
// ============================================================================
/*! This namespace collects all the parameters associated with
 *  the various `PlotMaker` routines.
 */
namespace PlotOptions {

  // --------------------------------------------------------------------------
  // Options for plot ranges
  // --------------------------------------------------------------------------
  /* FIXME should go in constants */
  enum RangeOpt {Side, Angle};



  // helper methods ===========================================================

  std::size_t GetRowNumber(const std::size_t nhist, const std::size_t ncol) {

    const std::size_t div_one = (nhist / ncol) + 1;
    const std::size_t div_mod = (nhist / ncol) + (nhist % ncol);
    return min(div_one, div_mod);

  }  // end 'GetRowNumber(std::size_t, std::size_t)'



  // --------------------------------------------------------------------------
  //! Define plot range
  // --------------------------------------------------------------------------
  /*! Plot range arguments:
   *    first  = x range to plot
   *    second = y range to plot
   *    third  = z range to plot
   */ 
  PHEC::Range DefinePlotRange(const int opt = Side) {

    PHEC::Range range;
    switch (opt) {

      case Side:
        range = PHEC::Range(
          std::make_pair(0.003, 3.),
          std::make_pair(0.00003, 0.7),
          std::make_pair(0.00003, 33.)
        );
        break;

      case Angle:
        range = PHEC::Range(
          std::make_pair(0.0, 6.30),
          std::make_pair(-0.007, 0.07),
          std::make_pair(0.00003, 33.)
        );
        break;

      default:
        range = PHEC::Range();
        std::cout << "WARNING: unknown option " << opt << "!" << std::endl;
        break;

    }
    return range;

  }  // end 'DefinePlotRange(int)'



  // --------------------------------------------------------------------------
  //! Define normalization range
  // --------------------------------------------------------------------------
  PHEC::Range DefineNormRange(const int opt = Side) {

    // grab plot range
    PHEC::Range plot_range = DefinePlotRange(opt);

    // set normalization range
    PHEC::Range range = PHEC::Range(plot_range.GetX());
    return range;

  }  // end 'DefineNormRange(int)'



  // --------------------------------------------------------------------------
  //! Define line for unit ratio
  // --------------------------------------------------------------------------
  PHEC::PlotShape DefineUnity(const int opt = Side) {

    return PHEC::PlotShape(
      PHEC::Shape(DefinePlotRange(opt).GetX(), std::make_pair(1.0, 1.0)),
      PHEC::Style::Plot(923, 1, 0, 9, 2)
    );

  }  // end 'DefineUnity(int)'



  // bundle parameters ========================================================

  // --------------------------------------------------------------------------
  //! Bundle 1D `CompareSpectra` parameters
  // --------------------------------------------------------------------------
  PHEC::PlotMaker::CompareSpectraParams CompareSpectra1D(
    const PHEC::Inputs& inputs,
    const std::string& canvas_name = "cSpectra1D",
    const int range_opt = Side
  ) {

    // grab default pad options, and
    // turn on log y
    PHEC::PadOpts pad_opts = PHEC::PadOpts();
    if (range_opt == Side) {
      pad_opts.logx = 1;
      pad_opts.logy = 1;
    }

    // set margins
    PHEC::Type::Margins margins;
    margins.push_back(0.02);
    margins.push_back(0.02);
    margins.push_back(0.15);
    margins.push_back(0.15);

    // define canvas (use default pad options)
    PHEC::Canvas canvas = PHEC::Canvas(canvas_name, "", std::make_pair(750, 750), pad_opts);
    canvas.SetMargins( margins );

    // set auxilliary options
    PHEC::PlotOpts plot_opts;
    plot_opts.plot_range = DefinePlotRange(range_opt);
    plot_opts.norm_range = DefineNormRange(range_opt);
    plot_opts.canvas     = canvas;

    // bundle parameters
    PHEC::PlotMaker::CompareSpectraParams params;
    params.inputs  = inputs;
    params.options = plot_opts;
    return params;

  }  // end 'CompareSpectra1D(PHEC::Inputs&, std::string&, int)'



  // --------------------------------------------------------------------------
  //! Bundle 2D `CompareSpectra` parameters
  // --------------------------------------------------------------------------
  PHEC::PlotMaker::CompareSpectraParams CompareSpectra2D(
    const PHEC::Inputs& inputs,
    const std::string& canvas_name = "cSpectra2D",
    const std::size_t ncolumn = 2
  ) {

    // grab default pad options, and
    // turn on log z
    PHEC::PadOpts pad_opts = PHEC::PadOpts();
    pad_opts.logx = 1;
    pad_opts.logz = 1;

    // basic dimension of each pad
    std::size_t pad_dim = 375;
    std::size_t nrow    = GetRowNumber(inputs.size(), ncolumn);

    // determine canvas dimensions
    const PHEC::Type::Dimensions dimensions = std::make_pair(
      pad_dim * ncolumn,
      pad_dim * nrow
    );

    // determine vertices of pads
    std::vector<PHEC::Type::Vertices> pad_vtxs;    
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
      pad_vtxs.push_back( PHEC::Type::Vertices() );
      pad_vtxs.back().push_back( startx );
      pad_vtxs.back().push_back( starty );
      pad_vtxs.back().push_back( stopx );
      pad_vtxs.back().push_back( stopy );
    }

    // set pad margins
    PHEC::Type::Margins pad_margins;
    pad_margins.push_back(0.15);
    pad_margins.push_back(0.15);
    pad_margins.push_back(0.15);
    pad_margins.push_back(0.15);

    // define canvas (use default pad options)
    PHEC::Canvas canvas = PHEC::Canvas(canvas_name, "", dimensions, PHEC::PadOpts());
    for (std::size_t iin = 0; iin < inputs.size(); ++iin) {

      // create name
      TString tname("pSpec");
      tname += iin;

      // add pad
      canvas.AddPad(
        PHEC::Pad(
          std::string(tname.Data()),
          "",
          pad_vtxs[iin],
          pad_margins,
          pad_opts
        )
      );
    }

    // set ranges
    const PHEC::Range plot_range = PHEC::Range(
      DefinePlotRange(Side).GetX(),
      DefinePlotRange(Angle).GetY(),
      DefinePlotRange(Side).GetZ()
    );
    const PHEC::Range norm_range = plot_range;

    // set auxilliary options
    PHEC::PlotOpts plot_opts;
    plot_opts.plot_range = plot_range;
    plot_opts.norm_range = norm_range;
    plot_opts.canvas     = canvas;

    // bundle parameters
    PHEC::PlotMaker::CompareSpectraParams params;
    params.inputs  = inputs;
    params.options = plot_opts;
    return params;

  }  // end 'CompareSpectra2D(PHEC::Inputs&, std::string&)'



  // --------------------------------------------------------------------------
  //! Bundle `SpectraVsBaseline` parameters
  // --------------------------------------------------------------------------
  PHEC::PlotMaker::SpectraVsBaselineParams SpectraVsBaseline(
    const PHEC::PlotInput& in_denom,
    const PHEC::Inputs& in_numers,
    const std::string& canvas_name = "cSpectraVsBaseline",
    const int range_opt = Side
  ) {

    // grab default pad options, and
    // turn on log y/x when necessary
    PHEC::PadOpts ratio_opts = PHEC::PadOpts();
    PHEC::PadOpts spect_opts = PHEC::PadOpts();
    if (range_opt == Side) {
      ratio_opts.logx = 1;
      spect_opts.logx = 1;
      spect_opts.logy = 1;
    }

    // set pad vertices
    PHEC::Type::Vertices ratio_vtxs;
    ratio_vtxs.push_back(0.00);
    ratio_vtxs.push_back(0.00);
    ratio_vtxs.push_back(1.00);
    ratio_vtxs.push_back(0.35);

    PHEC::Type::Vertices spect_vtxs;
    spect_vtxs.push_back(0.00);
    spect_vtxs.push_back(0.35);
    spect_vtxs.push_back(1.00);
    spect_vtxs.push_back(1.00);

    // set spectra margins
    PHEC::Type::Margins ratio_margins;
    ratio_margins.push_back(0.005);
    ratio_margins.push_back(0.02);
    ratio_margins.push_back(0.25);
    ratio_margins.push_back(0.15);

    PHEC::Type::Margins spect_margins;
    spect_margins.push_back(0.02);
    spect_margins.push_back(0.02);
    spect_margins.push_back(0.005);
    spect_margins.push_back(0.15);

    // define canvas (use default pad options)
    PHEC::Canvas canvas = PHEC::Canvas(canvas_name, "", std::make_pair(750, 1125), PHEC::PadOpts());
    canvas.AddPad( PHEC::Pad("pRatio",   "", ratio_vtxs, ratio_margins, ratio_opts), "ratio" );
    canvas.AddPad( PHEC::Pad("pSpectra", "", spect_vtxs, spect_margins, spect_opts), "spectra" );

    // set auxilliary options
    PHEC::PlotOpts plot_opts;
    plot_opts.plot_range  = DefinePlotRange(range_opt);
    plot_opts.norm_range  = DefineNormRange(range_opt);
    plot_opts.canvas      = canvas;
    plot_opts.ratio_pad   = "ratio";
    plot_opts.spectra_pad = "spectra";

    // bundle parameters
    PHEC::PlotMaker::SpectraVsBaselineParams params;
    params.denominator = in_denom;
    params.numerators  = in_numers;
    params.options     = plot_opts;
    params.unity       = DefineUnity(range_opt);
    return params;

  }  // end 'SpectraVsBaseline(PHEC::PlotInput&, PHEC::Inputs&, std::string&, int)'



  // --------------------------------------------------------------------------
  //! Bundle `CompareRatios` parameters
  // --------------------------------------------------------------------------
  PHEC::PlotMaker::CompareRatiosParams CompareRatios(
    const PHEC::Inputs& in_denoms,
    const PHEC::Inputs& in_numers,
    const std::string& canvas_name = "cRatios",
    const int range_opt = Side
  ) {

    // grab default pad options, and
    // turn on log y/x when necessary
    PHEC::PadOpts ratio_opts = PHEC::PadOpts();
    PHEC::PadOpts spect_opts = PHEC::PadOpts();
    if (range_opt == Side) {
      ratio_opts.logx = 1;
      spect_opts.logx = 1;
      spect_opts.logy = 1;
    }

    // set pad vertices
    PHEC::Type::Vertices ratio_vtxs;
    ratio_vtxs.push_back(0.00);
    ratio_vtxs.push_back(0.00);
    ratio_vtxs.push_back(1.00);
    ratio_vtxs.push_back(0.35);

    PHEC::Type::Vertices spect_vtxs;
    spect_vtxs.push_back(0.00);
    spect_vtxs.push_back(0.35);
    spect_vtxs.push_back(1.00);
    spect_vtxs.push_back(1.00);

    // set spectra margins
    PHEC::Type::Margins ratio_margins;
    ratio_margins.push_back(0.005);
    ratio_margins.push_back(0.02);
    ratio_margins.push_back(0.25);
    ratio_margins.push_back(0.15);

    PHEC::Type::Margins spect_margins;
    spect_margins.push_back(0.02);
    spect_margins.push_back(0.02);
    spect_margins.push_back(0.005);
    spect_margins.push_back(0.15);

    // define canvas (use default pad options)
    PHEC::Canvas canvas = PHEC::Canvas(canvas_name, "", std::make_pair(750, 1125), PHEC::PadOpts());
    canvas.AddPad( PHEC::Pad("pRatio",   "", ratio_vtxs, ratio_margins, ratio_opts), "ratio" );
    canvas.AddPad( PHEC::Pad("pSpectra", "", spect_vtxs, spect_margins, spect_opts), "spectra" );

    // set auxilliary options
    PHEC::PlotOpts plot_opts;
    plot_opts.plot_range  = DefinePlotRange(range_opt);
    plot_opts.norm_range  = DefineNormRange(range_opt);
    plot_opts.canvas      = canvas;
    plot_opts.ratio_pad   = "ratio";
    plot_opts.spectra_pad = "spectra";

    // bundle parameters
    PHEC::PlotMaker::CompareRatiosParams params;
    params.denominators = in_denoms;
    params.numerators   = in_numers;
    params.options      = plot_opts;
    params.unity        = DefineUnity(range_opt);
    return params;

  }  // end 'CompareRatios(PHEC::Inputs&, PHEC::Inputs&, std::string&, int)'



  // --------------------------------------------------------------------------
  //! Bundle 1D `CorrectSpectra` parameters
  // --------------------------------------------------------------------------
  PHEC::PlotMaker::CorrectSpectraParams CorrectSpectra1D(
    const PHEC::Inputs& in_data,
    const PHEC::Inputs& in_reco,
    const PHEC::Inputs& in_true,
    const std::string& canvas_name = "cCorrectSpectra1D",
    const int range_opt = Side
  ) {

    // grab default pad options, and
    // turn on log y/x when necessary
    PHEC::PadOpts rat_opts  = PHEC::PadOpts();
    PHEC::PadOpts corr_opts = PHEC::PadOpts();
    PHEC::PadOpts spec_opts = PHEC::PadOpts();
    if (range_opt == Side) {
      rat_opts.logx  = 1;
      corr_opts.logx = 1;
      spec_opts.logx = 1;
      spec_opts.logy = 1;
    }

    // set pad vertices
    PHEC::Type::Vertices corr_vtxs;
    corr_vtxs.push_back(0.00);
    corr_vtxs.push_back(0.00);
    corr_vtxs.push_back(1.00);
    corr_vtxs.push_back(0.25);

    PHEC::Type::Vertices rat_vtxs;
    rat_vtxs.push_back(0.00);
    rat_vtxs.push_back(0.25);
    rat_vtxs.push_back(1.00);
    rat_vtxs.push_back(0.50);

    PHEC::Type::Vertices spec_vtxs;
    spec_vtxs.push_back(0.00);
    spec_vtxs.push_back(0.50);
    spec_vtxs.push_back(1.00);
    spec_vtxs.push_back(1.00);

    // set spectra margins
    PHEC::Type::Margins corr_margins;
    corr_margins.push_back(0.005);
    corr_margins.push_back(0.02);
    corr_margins.push_back(0.25);
    corr_margins.push_back(0.15);

    PHEC::Type::Margins rat_margins;
    rat_margins.push_back(0.005);
    rat_margins.push_back(0.02);
    rat_margins.push_back(0.005);
    rat_margins.push_back(0.15);

    PHEC::Type::Margins spec_margins;
    spec_margins.push_back(0.02);
    spec_margins.push_back(0.02);
    spec_margins.push_back(0.005);
    spec_margins.push_back(0.15);

    // define canvas (use default pad options)
    PHEC::Canvas canvas = PHEC::Canvas(canvas_name, "", std::make_pair(750, 1125), PHEC::PadOpts());
    canvas.AddPad( PHEC::Pad("pCorrect", "", corr_vtxs, corr_margins, corr_opts), "correct" );
    canvas.AddPad( PHEC::Pad("pRatio",   "", rat_vtxs,  rat_margins,  rat_opts),  "ratio");
    canvas.AddPad( PHEC::Pad("pSpectra", "", spec_vtxs, spec_margins, spec_opts), "spectra" );

    // set auxilliary options
    PHEC::PlotOpts plot_opts;
    plot_opts.plot_range  = DefinePlotRange(range_opt);
    plot_opts.norm_range  = DefineNormRange(range_opt);
    plot_opts.canvas      = canvas;
    plot_opts.correct_pad = "correct";
    plot_opts.ratio_pad   = "ratio";
    plot_opts.spectra_pad = "spectra";

    // bundle parameters
    PHEC::PlotMaker::CorrectSpectraParams params;
    params.data    = in_data;
    params.recon   = in_reco;
    params.truth   = in_true;
    params.options = plot_opts;
    params.unity   = DefineUnity(range_opt);
    return params;

  }  // end 'CorrectSpectra1D(PHEC::Inputs& x 3, std::string&, int)'

}  // end PlotOptions namespace

#endif

// end ========================================================================
