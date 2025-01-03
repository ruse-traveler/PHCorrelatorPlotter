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
#define SPECTRAVSBASLINE_H

// c++ utilities
#include <string>
#include <vector>
#include <utility>
// plotting utilities
#include "../include/PHCorrelatorPlotting.h"



// ============================================================================
//! Spectra vs. Baseline Comparison Options
// ============================================================================
/*! This namespace collects all the parameters associated with
 *  the `PHCorrelatorPlotter::CompareSpectraToBaseline` routines. 
 */
namespace SpectraVsBaseline {

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
    input_files.push_back("./input/ppRun15_simWithSpin_r0_30.d26m12y2024.root");

    // return vector
    return input_files;

  }  // end 'LoadInputFiles()'



  // ==========================================================================
  //! Create denominator input
  // ==========================================================================
  /*! This method collects all information needed to plot
   *  the baseline to be compared against. Needed
   *  information:
   *
   *    .file   = file object to be drawn is located in,
   *    .object = name of object to be drawn
   *    .rename = what to rename object to when saving to output
   *    .legend = what object's entry in a TLegend will say
   *    .style  = color, marker, line, and fill style
   *              (grouped into a PlotHelper::Style::Plot struct)
   */
  PHEC::PlotInput Denominator() {

    // load input files
    std::vector<std::string> input_files = LoadInputFiles();

    // collect information
    PHEC::PlotInput denominator = PHEC::PlotInput(
      input_files[1],
      "hTrueJetEECStat_pt1cf0spBD",
      "hSpectraVsBaseline_TrueEEC_BlueDown_ptJet10",
      "#bf{[Truth]} B#downarrow, p_{T}^{jet} #in (10, 15) GeV/c",
      PHEC::Style::Plot(923, 29, 0)
    );
    return denominator;

  }  // end 'Denominator()'



  // ==========================================================================
  //! Create numerator input list
  // ==========================================================================
  /*! This method collects all information needed to plot
   *  the spectra to compare against the baseline. Needed
   *  information:
   *
   *    .file   = file object to be drawn is located in,
   *    .object = name of object to be drawn
   *    .rename = what to rename object to when saving to output
   *    .legend = what object's entry in a TLegend will say
   *    .style  = color, marker, line, and fill style
   *              (grouped into a PlotHelper::Style::Plot struct)
   */
  std::vector<PHEC::PlotInput> Numerators() {

    // load input files
    std::vector<std::string> input_files = LoadInputFiles();

    // collect numerator information
    std::vector<PHEC::PlotInput> numerators;
    numerators.push_back(
      PHEC::PlotInput(
        input_files[1],
        "hRecoJetEECStat_pt1cf0spBD",
        "hSpectraVsBaseline_RecoEEC_BlueDown_ptJet10",
        "#bf{[Reco.]} B#downarrow, p_{T}^{jet} #in (10, 15) GeV/c",
        PHEC::Style::Plot(859, 24, 0)
      )
    );
    numerators.push_back(
      PHEC::PlotInput(
        input_files[0],
        "hDataJetEECStat_pt1cf0spBD",
        "hSpectraVsBaseline_DataEEC_BlueDown_ptJet10",
        "#bf{[Data]} B#downarrow, p_{T}^{jet} #in (10, 15) GeV/c",
        PHEC::Style::Plot(899, 25, 0)
      )
    );
    return numerators;

  }  // end 'Numerators()'



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
    // turn on log y/x when necessary
    PHEC::PadOpts ratio_opts = PHEC::PadOpts();
    ratio_opts.logx = 1;

    PHEC::PadOpts spect_opts = PHEC::PadOpts();
    spect_opts.logx = 1;
    spect_opts.logy = 1;

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
    PHEC::Canvas canvas = PHEC::Canvas("cSpectraVsBaseline", "", std::make_pair(950, 1568), PHEC::PadOpts());
    canvas.AddPad( PHEC::Pad("pRatio",   "", ratio_vtxs, ratio_margins, ratio_opts) );
    canvas.AddPad( PHEC::Pad("pSpectra", "", spect_vtxs, spect_margins, spect_opts) );
    return canvas;

  }  // end 'Canvas()'



  // ==========================================================================
  //! Define legend header
  // ==========================================================================
  /*! Note that the header is optional parameter that
   *  can be provided as the last argument of
   *  `PHCorrelatorPlotterlotter::DoSpectraVsBaseline`.
   */
  std::string Header() {

    return std::string("Data vs. Sim. [Max p_{T}^{jet}]");

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
