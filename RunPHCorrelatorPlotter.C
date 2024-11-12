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
#include <string>
#include <iostream>
// analysis components
#include "src/PHCorrelatorPlotter.h"



// ============================================================================
//! Run PHCorrelatorPlotter
// ============================================================================
void RunPHCorrelatorPlotter() {

  //R__LOAD_LIBRARY(PHCorrelatorPlotter_cc.so)  // TODO load library when needed
  std::cout << "\n  Beginning PHENC plotting routines!" << std::endl;

  // create plotter class
  PHCorrelatorPlotter* plotter = new PHCorrelatorPlotter();

  /* TODO run routines here */

  std::cout << "  Finished plotting!\n" << std::endl;

}

// end ========================================================================
