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
// root libraries
#include <TFile.h>
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
  PHEC::PlotMaker maker_a = PHEC::PlotMaker();
  maker_a.SetBasePlotStyle( BO::BasePlotStyle() );
  maker_a.SetBaseTextStyle( BO::BaseTextStyle() );
  maker_a.SetTextBox( BO::Text() );
  maker_a.Init();
  std::cout << "    ---- [PASS] created maker w/ default ctor" << std::endl;

  // --------------------------------------------------------------------------
  //! Test new plot maker
  // --------------------------------------------------------------------------
  std::cout << "    Case [2]: test maker using ctor w/ arguments" << std::endl;

  // instantiate plot maker with ctor(...)
  PHEC::PlotMaker maker_b = PHEC::PlotMaker(
    BO::BasePlotStyle(),
    BO::BaseTextStyle(),
    BO::Text()
  );
  std::cout << "    ---- [PASS] created maker w/ ctor(...)" << std::endl;

  // --------------------------------------------------------------------------
  //! Test output
  // --------------------------------------------------------------------------
  std::cout << "    Case [3]: test output" << std::endl;

  // instantiate outputs
  PHEC::Output output = PHEC::Output();
  output.SetMaker(maker_a);
  output.SetInput(input);
  std::cout << "    ---- [PASS] loaded outputs" << std::endl;

  // --------------------------------------------------------------------------
  //! Try making a couple plots
  // --------------------------------------------------------------------------
  std::cout << "    Case [4]: test making a couple plots" << std::endl;

  // create dummy index
  PHEC::Type::PlotIndex index(-1);
  index.species = 0;
  index.level = 0;
  index.spin = 0;
  index.pt = 0;

  // create test output file
  TFile* ofile = new TFile("test.root", "recreate");

  // make plots
  output.SetIndex(index);
  output.SimVsData1D("EEC", PHEC::Type::Side, ofile);
  output.SimVsData2D("CollinsBlueVsR", ofile);
  std::cout << "    ---- [PASS] made plots" << std::endl;

  // announce end
  std::cout << "  PHCorrelatorPlotter test complete!\n" << std::endl;

  // exit test
  //ofile -> cd();
  //ofile -> Close();
  return;

}

/// end =======================================================================
