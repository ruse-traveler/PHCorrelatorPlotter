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
#include <string>
#include <vector>
#include <utility>
// plotting utilities
#include "../include/PHCorrelatorPlotting.h"



// ============================================================================
//! Plot Options
// ============================================================================
/*! This namespace collects all the parameters associated with
 *  the various `PHCorrelatorPlotter` routines.
 */
namespace PlotOptions {

  // --------------------------------------------------------------------------
  // Options for plot ranges
  // --------------------------------------------------------------------------
  /* FIXME should go in constants */
  enum RangeOpt {Side, Angle};



  // helper methods ===========================================================

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
          std::make_pair(-0.007, 0.017),
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



  // bundle parameters ========================================================

  // --------------------------------------------------------------------------
  //! Bundle 1D `CompareSpectra` parameters
  // --------------------------------------------------------------------------
  PHEC::PHCorrelatorPlotter::CompareSpectraParams CompareSpectra1D(
    const PHEC::Inputs& inputs,
    const std::string& canvas_name = "cSpectra",
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
    PHEC::Canvas canvas = PHEC::Canvas(canvas_name, "", std::make_pair(950, 950), pad_opts);
    canvas.SetMargins( margins );

    // set auxilliary options
    PHEC::PlotOpts plot_opts;
    plot_opts.plot_range = DefinePlotRange(range_opt);
    plot_opts.norm_range = DefineNormRange(range_opt);
    plot_opts.canvas     = canvas;

    // bundle parameters
    PHEC::PHCorrelatorPlotter::CompareSpectraParams params;
    params.inputs  = inputs;
    params.options = plot_opts;
    return params;

  }  // end 'CompareSpectra1D(PHEC::Inputs&, std::string&, int)'



  // --------------------------------------------------------------------------
  //! Bundle 2D `CompareSpectra` parameters
  // --------------------------------------------------------------------------
  PHEC::PHCorrelatorPlotter::CompareSpectraParams CompareSpectra2D(
    const PHEC::Inputs& inputs,
    const std::string& canvas_name = "cSpectra2D"
  ) {

    // grab default pad options, and
    // turn on log z
    PHEC::PadOpts pad_opts = PHEC::PadOpts();
    pad_opts.logx = 1;
    pad_opts.logz = 1;

    // determine canvas dimensions
    //   - FIXME layout of canvas should be configurable
    const PHEC::Type::Dimensions dimensions = std::make_pair(
      950 * inputs.size(),
      950
    );

    // determine vertices of pads
    std::vector<PHEC::Type::Vertices> pad_vtxs;    
    for (std::size_t iin = 0; iin < inputs.size(); ++iin) {

      // set x vertices
      const double startx = iin * (1.0 / inputs.size());
      const double stopx  = (iin + 1) * (1.0 / inputs.size());

      // add to vector
      pad_vtxs.push_back( PHEC::Type::Vertices() );
      pad_vtxs.back().push_back( startx );
      pad_vtxs.back().push_back( 0.00 );
      pad_vtxs.back().push_back( stopx );
      pad_vtxs.back().push_back( 1.00 );
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
    PHEC::PHCorrelatorPlotter::CompareSpectraParams params;
    params.inputs  = inputs;
    params.options = plot_opts;
    return params;

  }  // end 'CompareSpectra2D(PHEC::Inputs&, std::string&)'



  // --------------------------------------------------------------------------
  //! Bundle `SpectraVsBaseline` parameters
  // --------------------------------------------------------------------------
  PHEC::PHCorrelatorPlotter::SpectraVsBaselineParams SpectraVsBaseline(
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
    PHEC::Canvas canvas = PHEC::Canvas(canvas_name, "", std::make_pair(950, 1568), PHEC::PadOpts());
    canvas.AddPad( PHEC::Pad("pRatio",   "", ratio_vtxs, ratio_margins, ratio_opts) );
    canvas.AddPad( PHEC::Pad("pSpectra", "", spect_vtxs, spect_margins, spect_opts) );

    // set auxilliary options
    PHEC::PlotOpts plot_opts;
    plot_opts.plot_range = DefinePlotRange(range_opt);
    plot_opts.norm_range = DefinePlotRange(range_opt);
    plot_opts.canvas     = canvas;

    // bundle parameters
    PHEC::PHCorrelatorPlotter::SpectraVsBaselineParams params;
    params.denominator = in_denom;
    params.numerators  = in_numers;
    params.options     = plot_opts;
    return params;

  }  // end 'SpectraVsBaseline(PHEC::PlotInput&, PHEC::Inputs&, std::string&, int)'



  // --------------------------------------------------------------------------
  //! Bundle `CompareRatios` parameters
  // --------------------------------------------------------------------------
  PHEC::PHCorrelatorPlotter::CompareRatiosParams CompareRatios(
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
    PHEC::Canvas canvas = PHEC::Canvas(canvas_name, "", std::make_pair(950, 1568), PHEC::PadOpts());
    canvas.AddPad( PHEC::Pad("pRatio",   "", ratio_vtxs, ratio_margins, ratio_opts) );
    canvas.AddPad( PHEC::Pad("pSpectra", "", spect_vtxs, spect_margins, spect_opts) );

    // set auxilliary options
    PHEC::PlotOpts plot_opts;
    plot_opts.plot_range = DefinePlotRange(range_opt);
    plot_opts.norm_range = DefinePlotRange(range_opt);
    plot_opts.canvas     = canvas;

    // bundle parameters
    PHEC::PHCorrelatorPlotter::CompareRatiosParams params;
    params.denominators = in_denoms;
    params.numerators   = in_numers;
    params.options      = plot_opts;
    return params;

  }  // end 'CompareRatios(PHEC::Inputs&, PHEC::Inputs&, std::string&, int)'

}  // end PlotOptions namespace

#endif

// end ========================================================================
