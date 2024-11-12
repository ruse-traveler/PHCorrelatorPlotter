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
// analysis components
#include "src/PHCorrelatorPlotter.h"

// load plotter library
R__LOAD_LIBRARY(./src/PHCorrelatorPlotter_cc.so)



// ============================================================================
//! Run PHCorrelatorPlotter
// ============================================================================
void RunPHCorrelatorPlotter() {

  // input files
  std::vector<std::string> input_files;
  input_files.push_back( "/gpfs/mnt/gpfs02/phenix/mpcex/lajoie/ISU/new_unfolding/Run15/EEC/jetAnaRun15_pp_R0.30.root" );

  // output files
  std::vector<std::string> output_files;
  output_files.push_back( "/sphenix/user/danderson/eec/PHCorrelatorPlotter/trueVsRecoEEC.run15pp.d12m11y2024.root" );

  // announce start
  std::cout << "\n  Beginning PHENC plotting routines!" << std::endl;

  // create plotter class
  PHCorrelatorPlotter* plotter = new PHCorrelatorPlotter();

  // run routines
  plotter -> CompareTrueVsRecoEEC( input_files[0], output_files[0] );

  // announce end
  std::cout << "  Finished plotting!\n" << std::endl;
  return;

}

// end ========================================================================
