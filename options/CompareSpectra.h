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
#include "../include/PHCorrelatorPlotting.h"



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
   *
   *  FIXME it might be useful to create an input file list
   *  as part of the plotter...
   */
  std::vector<std::string> LoadInputFiles() {

    // load vector of inputs
    std::vector<std::string> input_files;
    input_files.push_back("./input/ppRun15_dataWithSpin_r0_30.d26m12y2024.root");

    // return vector
    return input_files;

  }  // end 'LoadInputFiles()'



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

    // load input files
    std::vector<std::string> input_files = LoadInputFiles();

    // collect input information
    std::vector<PHEC::PlotInput> inputs;
    inputs.push_back(
      PHEC::PlotInput(
        input_files[0],
        "hDataJetEECStat_pt1cf0spBD",
        "hDataEEC_BlueDown_ptJet10",
        "B#downarrow, p_{T}^{jet} #in (10, 15) GeV/c",
        PHEC::Style::Plot(863, 20, 0)
      )
    );
    inputs.push_back(
      PHEC::PlotInput(
        input_files[0],
        "hDataJetEECStat_pt1cf0spBU",
        "hDataEEC_BlueUp_ptJet10",
        "B#uparrow, p_{T}^{jet} #in (10, 15) GeV/c",
        PHEC::Style::Plot(859, 24, 0)
      )
    );
    inputs.push_back(
      PHEC::PlotInput(
        input_files[0],
        "hDataJetEECStat_pt1cf0spYD",
        "hDataEEC_YellDown_ptJet10",
        "Y#downarrow, p_{T}^{jet} #in (10, 15) GeV/c",
        PHEC::Style::Plot(803, 21, 0)
      )
    );
    inputs.push_back(
      PHEC::PlotInput(
        input_files[0],
        "hDataJetEECStat_pt1cf0spYU",
        "hDataEEC_YellUp_ptJet10",
        "Y#uparrow, p_{T}^{jet} #in (10, 15) GeV/c",
        PHEC::Style::Plot(799, 25, 0)
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
  PHEC::Range PlotRange() {

    PHEC::Range range = PHEC::Range(
      std::make_pair(0.003, 3.),
      std::make_pair(0.00003, 0.7)
    );
    return range;

  }  // end 'PlotRange()'



  // ==========================================================================
  //! Define normalization range
  // ==========================================================================
  PHEC::Range NormRange() {

    // grab plot range
    PHEC::Range plot_range = PlotRange();

    // set normalization range
    PHEC::Range range = PHEC::Range(plot_range.x);
    return range;

  }  // end 'NormRange()'



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



  // ==========================================================================
  //! Define normalization
  // ==========================================================================
  /*! Used to set what value to normalize to.
   */
  double Norm() {

    return 1.0;

  }  // end 'Norm()'

}  // end EnergySepctra namespace

#endif

// end ========================================================================
