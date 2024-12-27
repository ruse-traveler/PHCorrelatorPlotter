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
#include "./src/PHCorrelatorPlotter.h"
// plotting options
#include "./BaseOptions.h"
//#include "./CompareSpectra.h"  // TODO add in after figuring-out linking

// abbreviate common namespaces
namespace BO = BaseOptions;
//namespace CS = CompareSpectra;  // TODO add in after figuring-out linking



// ============================================================================
//! Run PHENIX ENC plotting routines
// ============================================================================
void RunPHCorrelatorPlotter( const std::string out_file = "test.root" ) {

  // link against plotter library
  gSystem -> AddLinkedLibs("./src/PHCorrelatorPlotter_cc.so");

  // announce start
  std::cout << "\n  Beginning PHENIX ENC plotting routines..." << std::endl;

  // open output & create plotter ---------------------------------------------

  // open output file
  TFile* ofile = PHCorrelatorPlotter::OpenFile(out_file, "recreate");
  std::cout << "    Opened output file" << std::endl;

  // create plotter
  PHCorrelatorPlotter plotter = PHCorrelatorPlotter(
    BO::BasePlotStyle(),
    BO::BaseTextStyle(),
    BO::Text()
  );
  std::cout << "    Made plotter." << std::endl;

  // compare spectra ----------------------------------------------------------

/* TODO add in after figuring-out linking
  plotter.CompareSpectra(
    CS::Inputs(),
    CS::PlotRange(),
    CS::Canvas(),
    ofile
  );
*/
  std::cout << "    Ran spectra comparison routines." << std::endl;

  // close files & exit -------------------------------------------------------

  // close output file
  ofile -> cd();
  ofile -> Close();
  return;

}

// end ========================================================================
