/// ===========================================================================
/*! \file   CompareSpectra.h
 *  \author Derek Anderson
 *  \date   12.27.2024
 *
 *  A small namespace to define inputs to the
 *  ENC spectra plotting routine.
 */
/// ===========================================================================

#ifndef COMPARESPECTRA_H
#define COMPARESPECTRA_H

// c++ utilities
#include <string>
#include <vector>
#include <utility>
// plotting utilities
#include "../include/PHCorrelatorPlotting.h"
// plotting options
#include "InputOutput.h"




// ============================================================================
//! Spectra Comparison Options
// ============================================================================
/*! This namespace collects all the parameters associated with
 *  the `PHCorrelatorPlotter::CompareSpectra` routines. 
 */
namespace CompareSpectra {

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
  PHEC::Canvas Canvas(const std::string& name = "cSpectra", const int opt = Side) {

    // grab default pad options, and
    // turn on log y
    PHEC::PadOpts opts = PHEC::PadOpts();
    if (opt == Side) {
      opts.logx = 1;
      opts.logy = 1;
    }

    // set margins
    PHEC::Type::Margins margins;
    margins.push_back(0.02);
    margins.push_back(0.02);
    margins.push_back(0.15);
    margins.push_back(0.15);

    // define canvas (use default pad options)
    PHEC::Canvas canvas = PHEC::Canvas(name, "", std::make_pair(950, 950), opts);
    canvas.SetMargins( margins );
    return canvas;

  }  // end 'Canvas(std::string&, int)'



  // --------------------------------------------------------------------------
  //! Define legend header
  // --------------------------------------------------------------------------
  /*! Note that the header is optional parameter that
   *  can be provided as the last argument of
   *  `PHCorrelatorPlotterlotter::DoCompareSpectra`.
   */
  std::string Header() {

    return std::string("Reconstructed [Max p_{T}^{jet}]");

  }  // end 'Header()'



  // --------------------------------------------------------------------------
  //! Define normalization
  // --------------------------------------------------------------------------
  /*! Used to set what value to normalize to.
   */
  double Norm() {

    return 1.0;

  }  // end 'Norm()'

}  // end CompareSepctra namespace

#endif

// end ========================================================================
