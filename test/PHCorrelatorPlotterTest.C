/// ===========================================================================
/*! \file   PHCorrelatorPlotterTest.C
 *  \author Derek Anderson
 *  \date   04.03.2025
 *
 *  ROOT macro to run test loading the
 *  PHCorrelatorPlotter library.
 */
/// ===========================================================================

#define PHCORRELATORPLOTTERTEST_C

// c++ utilities
#include <iostream>
#include <string>
// plotting utilities
#include "../include/PHCorrelatorPlotter.h"
// plotting options
#include "../options/BaseOptions.h"

// abbreviate common namespaces
namespace BO = BaseOptions;



// ============================================================================
//! Test PHENIX ENC plotting library
// ============================================================================
void PHCorrelatorPlotterTest() {

  // announce start
  std::cout << "\n  Beginning PHCorrelatorPotter test macro." << std::endl;

  // --------------------------------------------------------------------------
  //! Test input
  // --------------------------------------------------------------------------
  std::cout << "    Case [0]: test input" << std::endl;

  // instantiate inputs
  PHEC::Input input = PHEC::Input();
  std::cout << "    ---- [PASS] loaded inputs" << std::endl;

  // --------------------------------------------------------------------------
  //! Test maker
  // --------------------------------------------------------------------------
  std::cout << "    Case [1]: test maker" << std::endl;

  // instantiate plot maker
  PHEC::PlotMaker maker = PHEC::PlotMaker();
  maker.SetBasePlotStyle( BO::BasePlotStyle() );
  maker.SetBaseTextStyle( BO::BaseTextStyle() );
  maker.SetTextBox( BO::Text() );
  std::cout << "    ---- [PASS] created plot maker" << std::endl;

  // --------------------------------------------------------------------------
  //! Test output
  // --------------------------------------------------------------------------
  std::cout << "    Case [2]: test output" << std::endl;

  // instantiate outputs
  PHEC::Output output = PHEC::Output();
  output.SetMaker(maker);
  output.SetInput(input);
  std::cout << "    ---- [PASS] loaded outputs" << std::endl;

  /* TODO test plotting routines */

  // announce end

  // exit test
  std::cout << "  PHCorrelatorPlotter test complete!\n" << std::endl;
  return;

}

/// end =======================================================================
