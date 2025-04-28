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
  std::cout << "    Case [1]: test maker using default ctor" << std::endl;

  // instantiate plot maker with ctor()
  PHEC::PlotMakerNew maker_a = PHEC::PlotMakerNew();
  maker_a.SetBasePlotStyle( BO::BasePlotStyle() );
  maker_a.SetBaseTextStyle( BO::BaseTextStyle() );
  maker_a.SetTextBox( BO::Text() );
  std::cout << "    ---- [PASS] created maker w/ default ctor, n routines = "
            << maker_a.GetNRoutines()
            << std::endl;

  // --------------------------------------------------------------------------
  //! Test calling PHEC::PlotMakerNew::Init() after PHEC::PlotMakerNew()
  // --------------------------------------------------------------------------
  std::cout << "    Case [2]: test calling PHEC::PlotMakerNew::Init (1/2)" << std::endl;

  maker_a.Init();
  std::cout << "    ---- [PASS] called Init(), n routines = "
            << maker_a.GetNRoutines()
            << std::endl;

  // --------------------------------------------------------------------------
  //! Test new plot maker
  // --------------------------------------------------------------------------
  std::cout << "    Case [3]: test maker using ctor w/ arguments" << std::endl;

  // instantiate plot maker with ctor(...)
  PHEC::PlotMakerNew maker_b = PHEC::PlotMakerNew(
    BO::BasePlotStyle(),
    BO::BaseTextStyle(),
    BO::Text()
  );
  std::cout << "    ---- [PASS] created maker w/ ctor(...), n routines = "
            << maker_b.GetNRoutines()
            << std::endl;

  // --------------------------------------------------------------------------
  //! Test calling PHEC::PlotMakerNew::Init() after PHEC::PlotMakerNew(...)
  // --------------------------------------------------------------------------
  std::cout << "    Case [4]: test calling PHEC::PlotMakerNew::Init (2/2)" << std::endl;

  maker_b.Init();
  std::cout << "    ---- [PASS] called Init(), n routines = "
            << maker_b.GetNRoutines()
            << std::endl;

  // --------------------------------------------------------------------------
  //! Try accessing a plotting routine
  // --------------------------------------------------------------------------
  std::cout << "    Case [5]: test accessing a plotting routine" << std::endl;

  PHEC::BaseRoutine* routine = maker_b("PlotSpectra1D");
  std::cout << "    ---- [PASS] routine = " << routine << std::endl;

  // --------------------------------------------------------------------------
  //! Test output
  // --------------------------------------------------------------------------
  std::cout << "    Case [6]: test output" << std::endl;

  // FIXME remove once new maker is swapped in
  PHEC::PlotMaker maker = PHEC::PlotMaker(
    BO::BasePlotStyle(),
    BO::BaseTextStyle(),
    BO::Text()
  ); 

  // instantiate outputs
  PHEC::Output output = PHEC::Output();
  output.SetMaker(maker);
  output.SetInput(input);
  std::cout << "    ---- [PASS] loaded outputs" << std::endl;

  // announce end & exit test
  std::cout << "  PHCorrelatorPlotter test complete!\n" << std::endl;
  return;

}

/// end =======================================================================
