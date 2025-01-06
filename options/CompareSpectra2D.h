/// ===========================================================================
/*! \file   CompareSpectra2D.h
 *  \author Derek Anderson
 *  \date   01.05.2024
 *
 *  A small namespace to define inputs to the
 *  2D spectra plotting routine.
 */
/// ===========================================================================

#ifndef COMPARESPECTRA2D_H
#define COMPARESPECTRA2D_H

// c++ utilities
#include <string>
#include <vector>
#include <utility>
// root libraries
#include <TString.h>
// plotting utilities
#include "../include/PHCorrelatorPlotting.h"



// ============================================================================
//! 2D Spectra Comparison Options
// ============================================================================
/*! This namespace collects all the parameters associated with
 *  the `PHCorrelatorPlotter::CompareSpectra2D` routines. 
 */
namespace CompareSpectra2D {

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
    input_files.push_back("./input/ppRun15_simWithSpin_r0_30.d26m12y2024.root");
    input_files.push_back("./input/ppRun15_dataWithSpin_r0_30.d26m12y2024.root");

    // return vector
    return input_files;

  }  // end 'LoadInputFiles()'



  // ==========================================================================
  //! Create input list for 2D spectra
  // ==========================================================================
  /*! This method collects all information needed to plot
   *  various 2D spectra. Additional inputs can be added
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
    //   - n.b. marker and color aren't used here
    std::vector<PHEC::PlotInput> inputs;
    inputs.push_back(
      PHEC::PlotInput(
        input_files[0],
        "hTrueJetEECCollinsBlueVsRStat_pt1cf0spBD",
        "hSpectra2D_CollinsVsR_BlueDown_ptJet10",
        "#bf{[Truth]} B#downarrow, p_{T}^{jet} #in (10, 15) GeV/c",
        PHEC::Style::Plot(1, 1, 0)
      )
    );
    inputs.push_back(
      PHEC::PlotInput(
        input_files[0],
        "hRecoJetEECCollinsBlueVsRStat_pt1cf0spBD",
        "hSpectra2D_CollinsVsR_BlueDown_ptJet10",
        "#bf{[Reco.]} B#downarrow, p_{T}^{jet} #in (10, 15) GeV/c",
        PHEC::Style::Plot(1, 1, 0)
      )
    );
    inputs.push_back(
      PHEC::PlotInput(
        input_files[1],
        "hDataJetEECCollinsBlueVsRStat_pt1cf0spBD",
        "hSpectra2D_CollinsVsR_BlueDown_ptJet10",
        "#bf{[Data]} B#downarrow, p_{T}^{jet} #in (10, 15) GeV/c",
        PHEC::Style::Plot(1, 1, 0)
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
   *    third  = z range to plot
   */ 
  PHEC::Range PlotRange() {

    PHEC::Range range = PHEC::Range(
      std::make_pair(0.003, 3.),
      std::make_pair(-3.15, 3.15),
      std::make_pair(0.00003, 33.)
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
    PHEC::Range range = PHEC::Range(plot_range.x, plot_range.y);
    return range;

  }  // end 'NormRange()'



  // ==========================================================================
  //! Define canvas
  // ==========================================================================
  PHEC::Canvas Canvas() {

    // load inputs
    std::vector<PHEC::PlotInput> inputs = Inputs();

    // grab default pad options, and
    // turn on log z
    PHEC::PadOpts opts = PHEC::PadOpts();
    opts.logz = 1;

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
    PHEC::Canvas canvas = PHEC::Canvas("cSpectra2D", "", dimensions, PHEC::PadOpts());
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
          opts
        )
      );
    }
    return canvas;

  }  // end 'Canvas()'



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
