/// ===========================================================================
/*! \file   CompareSpectra.h
 *  \author Derek Anderson
 *  \date   12.27.2024
 *
 *  A small namespace to define inputs to the
 *  energy spectra plotting routine.
 */
/// ===========================================================================

#ifndef COMPARESPECTRA_H
#define COMPARESPECTRA_H

// c++ utilities
#include <string>
#include <vector>
#include <utility>
// plotting utilities
#include "./include/PHCorrelatorPlotting.h"



// ============================================================================
//! Spectra Comparison Options
// ============================================================================
/*! This namespace collects all the parameters associated with
 *  the `PHCorrelatorPlotter::CompareSpectra` routines. 
 */
namespace CompareSpectra {

  // --------------------------------------------------------------------------
  //! Input files
  // --------------------------------------------------------------------------
  /*! For convenience, all inputs files you'll need can
   *  be collected here.
   */ 
  std::vector<std::string> input_files;
  input_files.push_back("./input/ppRun15_simReco_iter0.d12m11y2024.hists.root");



  // ==========================================================================
  //! Create input list for energy spectra
  // ==========================================================================
  /*! This method collects all information needed to plot
   *  various energy spectra. Additional inputs can be added
   *  or removed. Needed information:
   *
   *    .file   = file object to be drawn is located in,
   *    .object = name of object to be drawn
   *    .rename = what to rename object to when saving to output
   *    .legend = what object's entry in a TLegend will say
   *    .style  = color, marker, line, and fill style
   *              (grouped into a PlotHelper::Style::Plot struct)
   */
  std::vector<PHEC::PlotInput> Inputs() {

    std::vector<PHEC::PlotInput> inputs;
    inputs.push_back(
      PHEC::PlotInput(
        input_files[0],
        "hMR_pt5cf00",
        "hMaxReco_pt5cf00",
        "p_{T}^{jet} #in (5, 10) GeV/c, CF < 0.5",
        PHEC::Style::Plot(899, 21, 0)
      )
    );
    inputs.push_back(
      PHEC::PlotInput(
        input_files[0],
        "hMR_pt10cf00",
        "hMaxReco_pt10cf00",
        "p_{T}^{jet} #in (10, 15) GeV/c, CF < 0.5",
        PHEC::Style::Plot(879, 22, 0)
      )
    );
    inputs.push_back(
      PHEC::PlotInput(
        input_files[0],
        "hMR_pt15cf00",
        "hMaxReco_pt15cf00",
        "p_{T}^{jet} #in (15, 20) GeV/c, CF < 0.5",
        PHEC::Style::Plot(899, 23, 0)
      )
    );
    return inputs;

  }  // end 'Inputs()'



  // ==========================================================================
  //! Define plot range
  // ==========================================================================
  /*! Plot range arguments:
   *    first  = x range to plot
   *    second = y range to plot
   */ 
  PHEC::PlotRange PlotRange() {

    PHEC::PlotRange range = PHEC::PlotRange(
      std::make_pair(0.003, 3.),
      std::make_pair(0.00003, 0.7)
    );
    return range;

  }  // end 'PlotRange()'



  // ==========================================================================
  //! Define canvas
  // ==========================================================================
  PHEC::Canvas Canvas() {

    // grab default pad options, and
    // turn on log y
    PHEC::PadOpts opts = PHEC::PadOpts();
    opts.logx = 1;
    opts.logy = 1;

    // set margins
    PHEC::Type::Margins margins;
    margins.push_back(0.02);
    margins.push_back(0.02);
    margins.push_back(0.15);
    margins.push_back(0.15);

    // define canvas (use default pad options)
    PHEC::Canvas canvas = PHEC::Canvas("cSpectra", "", std::make_pair(950, 950), opts);
    canvas.SetMargins( margins );
    return canvas;

  }  // end 'Canvas()'



  // ==========================================================================
  //! Define legend header
  // ==========================================================================
  /*! Note that the header is optional parameter that
   *  can be provided as the last argument of
   *  `PHCorrelatorPlotterlotter::DoCompareSpectra`.
   */
  std::string Header() {

    return std::string("Reconstructed [Max p_{T}^{jet}]");

  }  // end 'Header()'

}  // end EnergySepctra namespace

#endif

// end ========================================================================
