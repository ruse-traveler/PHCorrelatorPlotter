/// ===========================================================================
/*! \file   SpectraVsBaseline.h
 *  \author Derek Anderson
 *  \date   01.23.2024
 *
 *  A small namespace to define inputs to the
 *  ENC spectra vs. baseline plotting routine.
 */
/// ===========================================================================

#ifndef SPECTRAVSBASELINE_H
#define SPECTRAVSBASELINE_H

// c++ utilities
#include <string>
#include <vector>
#include <utility>
// plotting utilities
#include "../include/PHCorrelatorPlotting.h"
// plotting options
#include "InputOutput.h"



// ============================================================================
//! Spectra vs. Baseline Comparison Options
// ============================================================================
/*! This namespace collects all the parameters associated with
 *  the `PHCorrelatorPlotter::CompareSpectraToBaseline` routines. 
 */
namespace SpectraVsBaseline {

  // --------------------------------------------------------------------------
  // Options for ranges
  // --------------------------------------------------------------------------
  enum RangeOpt {Side, Angle};



  // --------------------------------------------------------------------------
  //! Define plot range
  // --------------------------------------------------------------------------
  /*! Plot range arguments:
   *    first  = x range to plot
   *    second = y range to plot
   */ 
  PHEC::Range PlotRange(const int opt = Side) {

    PHEC::Range range;
    switch (opt) {

      case Side:
        range = PHEC::Range(
          std::make_pair(0.003, 3.),
          std::make_pair(0.00003, 0.7)
        );
        break;

      case Angle:
        range = PHEC::Range(
          std::make_pair(-3.15, 3.15),
          std::make_pair(-0.007, 0.017)
        );
        break;

      default:
        range = PHEC::Range();
        std::cout << "WARNING: unknown option " << opt << "!" << std::endl;
        break;

    }
    return range;

  }  // end 'PlotRange()'



  // --------------------------------------------------------------------------
  //! Define normalization range
  // --------------------------------------------------------------------------
  PHEC::Range NormRange(const int opt = Side) {

    // grab plot range
    PHEC::Range plot_range = PlotRange(opt);

    // set normalization range
    PHEC::Range range = PHEC::Range(plot_range.x);
    return range;

  }  // end 'NormRange(int)'



  // --------------------------------------------------------------------------
  //! Define canvas
  // --------------------------------------------------------------------------
  PHEC::Canvas Canvas(const std::string& name = "cSpectraVsBaseline", const int opt = Side) {

    // grab default pad options, and
    // turn on log y/x when necessary
    PHEC::PadOpts ratio_opts = PHEC::PadOpts();
    PHEC::PadOpts spect_opts = PHEC::PadOpts();
    if (opt == Side) {
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
    PHEC::Canvas canvas = PHEC::Canvas(name, "", std::make_pair(950, 1568), PHEC::PadOpts());
    canvas.AddPad( PHEC::Pad("pRatio",   "", ratio_vtxs, ratio_margins, ratio_opts) );
    canvas.AddPad( PHEC::Pad("pSpectra", "", spect_vtxs, spect_margins, spect_opts) );
    return canvas;

  }  // end 'Canvas()'



  // --------------------------------------------------------------------------
  //! Define legend header
  // --------------------------------------------------------------------------
  /*! Note that the header is optional parameter that
   *  can be provided as the last argument of
   *  `PHCorrelatorPlotter::CompareSpectraToBaseline`.
   */
  std::string Header() {

    return std::string("Data vs. Sim. [Max p_{T}^{jet}]");

  }  // end 'Header()'



  // --------------------------------------------------------------------------
  //! Define normalization
  // --------------------------------------------------------------------------
  /*! Used to set what value to normalize to.
   */
  double Norm() {

    return 1.0;

  }  // end 'Norm()'

}  // end SpectraVsBaseline namespace

#endif

// end ========================================================================
