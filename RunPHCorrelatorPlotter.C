/// ===========================================================================
/*! \file   RunPHCorrelatorPlotter.C
 *  \author Derek Anderson
 *  \date   11.12.2024
 *
 *  ROOT macro to run plotting routines for
 *  the PHENIX ENC analysis.
 */
/// ===========================================================================

#define RUNPHCORRELATORPLOTTER_C

// c++ utilities
#include <iostream>
#include <string>
#include <vector>
// root libraries
#include <TFile.h>
#include <TSystem.h>
// plotter definition
#include "include/PHCorrelatorPlotter.h"
// plotting options
#include "options/BaseOptions.h"
#include "options/CompareSpectra.h"

// abbreviate common namespaces
namespace BO = BaseOptions;
namespace CS = CompareSpectra;



// ============================================================================
//! Run PHENIX ENC plotting routines
// ============================================================================
void RunPHCorrelatorPlotter( const std::string out_file = "test.root" ) {

  // announce start
  std::cout << "\n  Beginning PHENIX ENC plotting routines..." << std::endl;

  // open output & create plotter ---------------------------------------------

  // open output file
  TFile* ofile = PHEC::Tools::OpenFile(out_file, "recreate");
  std::cout << "    Opened output file" << std::endl;

  // create plotter
  PHEC::PHCorrelatorPlotter plotter = PHEC::PHCorrelatorPlotter(
    BO::BasePlotStyle(),
    BO::BaseTextStyle(),
    BO::Text()
  );
  std::cout << "    Made plotter." << std::endl;

  // compare spectra ----------------------------------------------------------

  plotter.CompareSpectra(
    CS::Inputs(),
    CS::PlotRange(),
    CS::Canvas(),
    ofile
  );
  std::cout << "    Ran spectra comparison routines." << std::endl;

  // close files & exit -------------------------------------------------------

  // close output file
  ofile -> cd();
  ofile -> Close();
  return;

}

// end ========================================================================
