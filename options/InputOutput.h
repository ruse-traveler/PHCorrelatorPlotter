/// ===========================================================================
/*! \file   InputOutput.h
 *  \author Derek Anderson
 *  \date   01.25.2025
 *
 *  A small namespace to define inputs/outputs for
 *  all plotting routines (e.g. input file names,
 *  output files, histograms to grab, etc.)
 */
/// ===========================================================================

#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

// c++ utilities
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>
// root libraries
#include <TFile.h>



// ============================================================================
//! Plotting Input/Output Options
// ============================================================================
/*! This namespace collects all inupt/output options
 *  for various plotting routines.
 */
namespace InputOutput {

  // --------------------------------------------------------------------------
  // Useful aliases
  // --------------------------------------------------------------------------
  typedef std::vector<std::string> Strings;
  typedef std::vector<std::vector<std::string> > InFiles;



  // --------------------------------------------------------------------------
  // Accessors for vectors
  // --------------------------------------------------------------------------
  enum Species {PP, PAu};
  enum Level   {Data, Reco, True};
  enum PtJet   {Pt5, Pt10, Pt15};
  enum Spin    {BU, BD, YU, YD, BUYU, BUYD, BDYU, BDYD, Int};
  enum What    {Hist, Leg};



  // --------------------------------------------------------------------------
  //! Input files
  // --------------------------------------------------------------------------
  /*! For convenience, all inputs files you'll need can
   *  be collected here.
   */
  InFiles LoadInputFiles() {

    // input files for pp
    std::vector<std::string> pp_files;
    pp_files.push_back("./input/ppRun15_dataWithSpin_r0_30.d26m12y2024.root");
    pp_files.push_back("./input/ppRun15_simWithSpin_r0_30.d26m12y2024.root");
    pp_files.push_back("./input/ppRun15_simWithSpin_r0_30.d26m12y2024.root");

    // input files for pAu
    std::vector<std::string> pa_files;
    pa_files.push_back("./input/paRun15_dataWithSpin_r0_30_0_84.d26m12y2024.root");
    pa_files.push_back("./input/paRun15_simWithSpin_r0_30_0_84.d26m12y2024.root");
    pa_files.push_back("./input/paRun15_simWithSpin_r0_30_0_84.d26m12y2024.root");

    // load vector of inputs
    InFiles input_files;
    input_files.push_back(pp_files);
    input_files.push_back(pa_files);

    // return vector
    return input_files;

  }  // end 'LoadInputFiles()'



  // --------------------------------------------------------------------------
  //! Load species strings
  // --------------------------------------------------------------------------
  Strings LoadSpeciesStrings(const int what) {

    Strings strings;
    switch (what) {

      case Hist:
        strings.push_back("PP");
        strings.push_back("PAu");
        break;

      case Leg:
        strings.push_back("#bf{[p+p]}");
        strings.push_back("#bf{[p+Au]}");
        break;

      default:
        strings.push_back("");
        std::cout << "WARNING: unknown option " << what << "!" << std::endl;
        break;

    }
    return strings;

  }  // end 'LoadSpeciesStrings(int)'



  // --------------------------------------------------------------------------
  //! Load level strings
  // --------------------------------------------------------------------------
  Strings LoadLevelStrings(const int what) {

    Strings strings;
    switch (what) {

      case Hist:
        strings.push_back("DataJet");
        strings.push_back("RecoJet");
        strings.push_back("TrueJet");
        break;

      case Leg:
        strings.push_back("#bf{[Data]}");
        strings.push_back("#bf{[Reco.]}");
        strings.push_back("#bf{[Truth]}");
        break;

      default:
        strings.push_back("");
        std::cout << "WARNING: unknown option " << what << "!" << std::endl;
        break;

    }
    return strings;

  }  // end 'LoadPtStrings(int)'



  // --------------------------------------------------------------------------
  //! Load pt strings
  // --------------------------------------------------------------------------
  Strings LoadPtStrings(const int what) {

    Strings strings;
    switch (what) {

      case Hist:
        strings.push_back("pt0");
        strings.push_back("pt1");
        strings.push_back("pt2");
        break;

      case Leg:
        strings.push_back("p_{T}^{jet} #in (5, 10) GeV/c");
        strings.push_back("p_{T}^{jet} #in (10, 15) GeV/c");
        strings.push_back("p_{T}^{jet} #in (15, 20) GeV/c");
        break;

      default:
        strings.push_back("");
        std::cout << "WARNING: unknown option " << what << "!" << std::endl;
        break;

    }
    return strings;

  }  // end 'LoadPtStrings(int)'



  // --------------------------------------------------------------------------
  //! Load spin strings
  // --------------------------------------------------------------------------
  std::vector<std::string> LoadSpinStrings(const int what) {

    Strings strings;
    switch (what) {

      case Hist:
        strings.push_back("spBU");
        strings.push_back("spBD");
        strings.push_back("spYU");
        strings.push_back("spYD");
        strings.push_back("spBUYU");
        strings.push_back("spBUYD");
        strings.push_back("spBDYU");
        strings.push_back("spBDYD");
        strings.push_back("spInt");
        break;

      case Leg:
        strings.push_back("B#uparrow");
        strings.push_back("B#downarrow");
        strings.push_back("Y#uparrow");
        strings.push_back("Y#downarrow");
        strings.push_back("B#uparrowY#uparrow");
        strings.push_back("B#uparrowY#downarrow");
        strings.push_back("B#downarrowY#uparrow");
        strings.push_back("B#downarrowY#downarrow");
        strings.push_back("Integrated");
        break;

      default:
        strings.push_back("");
        std::cout << "WARNING: unknown option " << what << "!" << std::endl;
        break;

    }
    return strings;

  }  // end 'LoadSpinStrings(int)'



  // --------------------------------------------------------------------------
  //! Make a histogram name
  // --------------------------------------------------------------------------
  std::string MakeHistName(
    const std::string& var,
    const std::string& lvl,
    const std::string& pt,
    const std::string& spin,
    const std::string& tag = ""
  ) {

    return "h" + tag + lvl + var + "Stat_" + pt + "cf0" + spin;

  }  // end 'MakeHistName(std::string& x 5)'



  // --------------------------------------------------------------------------
  //! Make a histogram legend
  // --------------------------------------------------------------------------
  std::string MakeLegend(
    const std::string& pt,
    const std::string& spin,
    const std::string& lvl = "",
    const std::string& spe = ""
  ) {

    std::string legend;
    if (!spe.empty()) {
      legend += spe + " ";
    }
    if (!lvl.empty()) {
      legend += lvl + " ";
    }

    legend += spin + ", " + pt;
    return legend;

  }  // end 'MakeLegend(std::string& x 5)'



  // --------------------------------------------------------------------------
  //! Make canvas name
  // --------------------------------------------------------------------------
  std::string MakeCanvasName(
   const std::string& base,
   const std::string& pt,
   const std::string& spin,
   const std::string& lvl = "",
   const std::string& spe = ""
  ) {

    std::string name = base;
    if (!spe.empty()) {
      name += "_" + spe;
    }
    if (!lvl.empty()) {
      name += lvl;
    }

    name += "_" + pt + spin;
    return name;

  }  // end 'MakeCanvasName(std::string& x 5)'

}  // end InputOutput namespace

#endif

// end ========================================================================
