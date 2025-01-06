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
// plotting utilities
#include "include/PHCorrelatorPlotting.h"
// plotting options
#include "options/BaseOptions.h"
#include "options/CompareSpectra.h"
#include "options/CompareSpectra2D.h"
#include "options/SpectraVsBaseline.h"

// abbreviate common namespaces
namespace BO = BaseOptions;
namespace CS = CompareSpectra;
namespace C2 = CompareSpectra2D;
namespace SB = SpectraVsBaseline;



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
    CS::NormRange(),
    CS::Canvas(),
    ofile
  );
  std::cout << "    Ran spectra comparison routines." << std::endl;

  // compare 2d spectra -------------------------------------------------------

  plotter.CompareSpectra2D(
    C2::Inputs(),
    C2::PlotRange(),
    C2::NormRange(),
    C2::Canvas(),
    ofile
  );
  std::cout << "    Ran 2d spectra comparison routines." << std::endl;

  // spectra vs. baseline -----------------------------------------------------

  plotter.CompareSpectraToBaseline(
    SB::Denominator(),
    SB::Numerators(),
    SB::PlotRange(),
    SB::NormRange(),
    SB::Canvas(),
    ofile
  );
  std::cout << "    Ran spectra vs. baseline routines." << std::endl;

  // close files & exit -------------------------------------------------------

  // close output file
  ofile -> cd();
  ofile -> Close();
  return;

}

// end ========================================================================
