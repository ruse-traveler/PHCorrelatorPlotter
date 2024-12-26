/// ===========================================================================
/*! \file   PHCorrelatorPlotter.cc
 *  \author Derek Anderson
 *  \date   11.12.2024
 *
 *  Class to consolidate plotting routines associated with
 *  the PHENIX ENC analysis.
 */
/// ===========================================================================

#define PHCORRELATORPLOTTER_CC

// c++ utilities
#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
// root libraries
#include <TCanvas.h>
#include <TFile.h>
#include <TH1.h>
#include <TLegend.h>
// class definition
#include "PHCorrelatorPlotter.h"



// public methods =============================================================

// ----------------------------------------------------------------------------
//! Compare truth vs. reco EEC
// ----------------------------------------------------------------------------
/*! Compares truth vs. reconstructed two-point
 *  spectra from simulation.
 */
void PHCorrelatorPlotter::CompareTrueVsRecoEEC(const std::string in_file, const std::string out_file) {

  // announce start
  std::cout << "\n -------------------------------- \n"
            << "   Beginning true vs. reco EEC comparison!"
            << std::endl;

  // open files
  TFile* ofile = OpenFile(in_file,  "read");
  TFile* ifile = OpenFile(out_file, "recreate");

  // announce files
  std::cout << "     Opened files:\n"
            << "       input  = " << in_file << "\n"
            << "       output = " << out_file
            << std::endl;

  /* TODO fill in routine here */

  // close files
  ofile -> cd();
  ofile -> Close();
  ifile -> cd();
  ifile -> Close();

  // announce end
  std::cout << "  Finished true vs. reco EEC comparison!\n"
            << " -------------------------------- \n"
            << std::endl;

  // exit routine
  return;

}  // end 'DoTrueVsRecoComparison(std::string, std::string)'



// private methods ============================================================

// ----------------------------------------------------------------------------
//! Open file and check if good
// ----------------------------------------------------------------------------
TFile* PHCorrelatorPlotter::OpenFile(const std::string name, const std::string option) {

  // try to open file, throw error if not able
  TFile* file = new TFile( name.data(), option.data() );
  if (!file) {
    std::cerr << "PANIC: couldn't open file!\n"
              << "       file = " << name << "\n"
              << std::endl;
    assert(file);
  }

  // then check file by cd'ing into it
  const bool isGoodCD = file -> cd();
  if (!isGoodCD) {
    std::cerr << "PANIC: couldn't cd into file!\n"
              << "       file = " << name << "\n"
              << std::endl;
    assert(isGoodCD);
  }

  // return pointer
  return file;

}  // end 'OpenFile(std::string, std::string)'



// ----------------------------------------------------------------------------
//! Create legend
// ----------------------------------------------------------------------------
TLegend* PHCorrelatorPlotter::MakeLegend() {

  /* TODO fill in */
  return new TLegend(0.1, 0.1, 0.3, 0.3);

}  // end 'MakeLegend()'

// end ========================================================================
