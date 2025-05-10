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
#include <utility>
// root libraries
#include <TFile.h>
#include <TSystem.h>
// plotting utilities
#include "include/PHCorrelatorPlotter.h"
// plotting options
#include "options/BaseOptions.h"

// abbreviate common namespaces
namespace BO = BaseOptions;



// ============================================================================
//! Run PHENIX ENC plotting routines
// ============================================================================
void RunPHCorrelatorPlotter(const int plot = PHEC::Output::Plots::SimVsData) {

  // announce start
  std::cout << "\n  Beginning PHENIX ENC plotting routines..." << std::endl;

  // --------------------------------------------------------------------------
  // open outputs & load inputs
  // --------------------------------------------------------------------------
  std::vector<TFile*> ofiles;
  switch (plot) {

    case PHEC::Output::Plots::SimVsData:
      ofiles.push_back( PHEC::Tools::OpenFile("simVsDataEEC.run15_forDiFF.d9m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("simVsDataCollins.run15_forDiFF.d9m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("simVsDataBoerMulders.run15_forDiFF.d9m5y2025.root", "recreate") );
      break;

    case PHEC::Output::Plots::RecoVsData:
      ofiles.push_back( PHEC::Tools::OpenFile("recoVsDataEEC.run15_forDiFF.d9m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("recoVsDataCollins.run15_forDiFF.d9m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("recoVsDataBoerMulders.run15_forDiFF.d9m5y2025.root", "recreate") );
      break;

    case PHEC::Output::Plots::VsPtJet:
      ofiles.push_back( PHEC::Tools::OpenFile("vsPtJetEEC.run15_forDiFF.d9m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("vsPtJetCollins.run15_forDiFF.d9m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("vsPtJetBoerMulders.run15_forDiFF.d9m5y2025.root", "recreate") );
      break;

    case PHEC::Output::Plots::PPVsPAu:
      ofiles.push_back( PHEC::Tools::OpenFile("ppVsPAuEEC.run15_forDiFF.d9m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("ppVsPAuCollins.run15_forDiFF.d9m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("ppVsPAuBoerMulders.run15_forDiFF.d9m5y2025.root", "recreate") );
      break;

    case PHEC::Output::Plots::CorrectSpectra:
      ofiles.push_back( PHEC::Tools::OpenFile("correctedEEC.run15_forDiFF.d9m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("correctedCollins.run15_forDiFF.d9m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("correctedBoerMulders.run15_forDiFF.d9m5y2025.root", "recreate") );
      break;

    case PHEC::Output::Plots::SpinRatios:
      ofiles.push_back( PHEC::Tools::OpenFile("spinRatioEEC.run15_forDiFF.d9m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("spinRatioCollins.run15_forDiFF.d9m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("spinRatioBoerMulders.run15_forDiFF.d9m5y2025.root", "recreate") );
      break;

    default:
      std::cerr << "PANIC: unknown plot (" << plot << ") to make!" << std::endl;
      break;

  }
  std::cout << "    Opened output file" << std::endl;

  // load input options
  PHEC::Input input = PHEC::Input();
  std::cout << "    Loaded input options." << std::endl;

  // create plot maker
  PHEC::PlotMaker maker = PHEC::PlotMaker(
    BO::BasePlotStyle(),
    BO::BaseTextStyle(),
    BO::Text()
  );
  std::cout << "    Made plot maker." << std::endl;

  // load output options
  PHEC::Output output = PHEC::Output();
  output.SetMaker(maker);
  output.SetInput(input);
  output.Init();
  std::cout << "    Loaded output options." << std::endl;

  // --------------------------------------------------------------------------
  // compare sim vs. data distributions
  // --------------------------------------------------------------------------
  if (plot == PHEC::Output::Plots::SimVsData) {

    // set indices to loop over
    PHEC::PlotIndexVector loops;
    loops.DoAllSpecies();
    loops.DoAllPt();
    loops.DoAllSpin();

    // get plot indices
    std::vector<PHEC::Type::PlotIndex> indices;
    loops.GetVector(indices);
    std::cout << "    Beginning sim vs. data plots." << std::endl;

    // loop through combinations to plot
    for (std::size_t idx = 0; idx < indices.size(); ++idx) {

      // only consider blue polarizations for pAu
      const bool isPAu = input.IsPAu(indices[idx]);
      if (isPAu && !input.IsBluePolarization(indices[idx])) {
        continue;
      }

      // make sure collision system is correct
      if (isPAu) output.GetMaker().SetTextBox( BO::Text(indices[idx].species) );

      // set index
      output.UpdateIndex(indices[idx]);

      // create comparison for each desired 1D histogram
      output["SimVsData"] -> MakePlot1D("EEC", PHEC::Type::Side, ofiles[0]);
      output["SimVsData"] -> MakePlot1D("CollinsBlue", PHEC::Type::Angle, ofiles[1], 3);
      output["SimVsData"] -> MakePlot1D("BoerMuldersBlue", PHEC::Type::Angle, ofiles[2], 3);
      if (!isPAu) {
        output["SimVsData"] -> MakePlot1D("CollinsYell", PHEC::Type::Angle, ofiles[1]), 3;
        output["SimVsData"] -> MakePlot1D("BoerMuldersYell", PHEC::Type::Angle, ofiles[2], 3);
      }

      // create comparison for each desired 2D histogram
      output["SimVsData"] -> MakePlot2D("CollinsBlueVsR", ofiles[1]);
      output["SimVsData"] -> MakePlot2D("BoerMuldersBlueVsR", ofiles[2]);
      if (!isPAu) {
        output["SimVsData"] -> MakePlot2D("CollinsYellVsR", ofiles[1]);
        output["SimVsData"] -> MakePlot2D("BoerMuldersYellVsR", ofiles[2]);
      }

    }  // end index loop
    std::cout << "    Completed sim vs. data plots." << std::endl;

  }  // end SimVsData plot

  // --------------------------------------------------------------------------
  // compare reco vs. data distributions
  // --------------------------------------------------------------------------
  if (plot == PHEC::Output::Plots::RecoVsData) {

    // set indices to loop over
    PHEC::PlotIndexVector loops;
    loops.DoAllSpecies();
    loops.DoAllPt();
    loops.DoAllSpin();

    // get plot indices
    std::vector<PHEC::Type::PlotIndex> indices;
    loops.GetVector(indices);
    std::cout << "    Beginning reco vs. data plots." << std::endl;

    // loop through combinations to plot
    for (std::size_t idx = 0; idx < indices.size(); ++idx) {

      // only consider blue polarizations for pAu
      const bool isPAu = input.IsPAu(indices[idx]);
      if (isPAu && !input.IsBluePolarization(indices[idx])) {
        continue;
      }

      // make sure collision system is correct
      if (isPAu) output.GetMaker().SetTextBox( BO::Text(indices[idx].species) );

      // set index
      output.UpdateIndex(indices[idx]);

      // create comparison for each desired 1D histogram
      output["RecoVsData"] -> MakePlot1D("EEC", PHEC::Type::Side, ofiles[0]);
      output["RecoVsData"] -> MakePlot1D("CollinsBlue", PHEC::Type::Angle, ofiles[1], 3);
      output["RecoVsData"] -> MakePlot1D("BoerMuldersBlue", PHEC::Type::Angle, ofiles[2], 3);
      if (!isPAu) {
        output["RecoVsData"] -> MakePlot1D("CollinsYell", PHEC::Type::Angle, ofiles[1], 3);
        output["RecoVsData"] -> MakePlot1D("BoerMuldersYell", PHEC::Type::Angle, ofiles[2], 3);
      }

      /* TODO make 2D comparisons */

    }  // end index loop
    std::cout << "    Completed sim vs. reco plots." << std::endl;

  }  // end SimVsData plot

  // --------------------------------------------------------------------------
  // compare distributions as a function of pt jet
  // --------------------------------------------------------------------------
  if (plot == PHEC::Output::Plots::VsPtJet) {

    // set indices to loop over
    PHEC::PlotIndexVector loops;
    loops.DoAllSpecies();
    loops.DoAllLevels();
    loops.DoAllSpin();

    // get plot indices
    std::vector<PHEC::Type::PlotIndex> indices;
    loops.GetVector(indices);
    std::cout << "    Beginning vs. ptJet plots." << std::endl;

    // loop through combinations to plot
    for (std::size_t idx = 0; idx < indices.size(); ++idx) {

      // only consider blue polarizations for pAu
      const bool isPAu = input.IsPAu(indices[idx]);
      if (isPAu && !input.IsBluePolarization(indices[idx])) {
        continue;
      }

      // make sure collision system is correct
      if (isPAu) output.GetMaker().SetTextBox( BO::Text(indices[idx].species) );

      // set index
      output.UpdateIndex(indices[idx]);

      // create comparisons for each desired 1D histogram
      output["VsPtJet"] -> MakePlot1D("EEC", PHEC::Type::Side, ofiles[0]);
      output["VsPtJet"] -> MakePlot1D("CollinsBlue", PHEC::Type::Angle, ofiles[1], 3);
      output["VsPtJet"] -> MakePlot1D("BoerMuldersBlue", PHEC::Type::Angle, ofiles[2], 3);
      if (!isPAu) {
        output["VsPtJet"] -> MakePlot1D("CollinsYell", PHEC::Type::Angle, ofiles[1], 3);
        output["VsPtJet"] -> MakePlot1D("BoerMuldersYell", PHEC::Type::Angle, ofiles[2], 3);
      }

      // create comparisons for each desired 2D histogram
      output["VsPtJet"] -> MakePlot2D("CollinsBlueVsR", ofiles[1]);
      output["VsPtJet"] -> MakePlot2D("BoerMuldersBlueVsR", ofiles[2]);
      if (!isPAu) {
        output["VsPtJet"] -> MakePlot2D("CollinsYellVsR", ofiles[1]);
        output["VsPtJet"] -> MakePlot2D("BoerMuldersYellVsR", ofiles[2]);
      }

    }  // end index loop
    std::cout << "    Completed vs. ptJet plots." << std::endl;

  }  // end VsPtJet plot

  // --------------------------------------------------------------------------
  // compare pp vs. pau distributions
  // --------------------------------------------------------------------------
  if (plot == PHEC::Output::Plots::PPVsPAu) {

    // set indices to loop over
    PHEC::PlotIndexVector loops;
    loops.DoAllLevels();
    loops.DoAllSpin();

    // get plot indices
    std::vector<PHEC::Type::PlotIndex> indices;
    loops.GetVector(indices);
    std::cout << "    Beginning pp vs. pAu plots." << std::endl;

    // loop through combinations to plot
    for (std::size_t idx = 0; idx < indices.size(); ++idx) {

      // only consider blue polarizations for pAu
      if (!input.IsBluePolarization(indices[idx])) continue;

      // set index
      output.UpdateIndex(indices[idx]);

      // create comparisons for each desired 1D histogram
      output["PPVsPAu"] -> MakePlot1D("EEC", PHEC::Type::Side, ofiles[0]);
      output["PPVsPAu"] -> MakePlot1D("CollinsBlue", PHEC::Type::Angle, ofiles[1], 3);
      output["PPVsPAu"] -> MakePlot1D("BoerMuldersBlue", PHEC::Type::Angle, ofiles[2], 3);

      /* TODO add 2D comparison */

    }  // end index loop
    std::cout << "    Completed pp vs. pAu plots." << std::endl;

  }  // end PPVsPAu plot

  // --------------------------------------------------------------------------
  // apply correction factors
  // --------------------------------------------------------------------------
  if (plot == PHEC::Output::Plots::CorrectSpectra) {

    // set indices to loop over
    PHEC::PlotIndexVector loops;
    loops.DoAllSpecies();
    loops.DoAllSpin();

    // get plot indices
    std::vector<PHEC::Type::PlotIndex> indices;
    loops.GetVector(indices);
    std::cout << "    Beginning correction plots." << std::endl;

    // loop through combinations to plot
    for (std::size_t idx = 0; idx < indices.size(); ++idx) {

      // only consider blue polarizations for pAu
      const bool isPAu = input.IsPAu(indices[idx]);
      if (isPAu && !input.IsBluePolarization(indices[idx])) {
        continue;
      }

      // make sure collision system is correct
      if (isPAu) output.GetMaker().SetTextBox( BO::Text(indices[idx].species) );

      // set index
      output.UpdateIndex(indices[idx]);

      // calculate/apply corrections for each desired 1D histogram
      output["CorrectSpectra"] -> MakePlot1D("EEC", PHEC::Type::Side, ofiles[0]);
      output["CorrectSpectra"] -> MakePlot1D("CollinsBlue", PHEC::Type::Angle, ofiles[1], 3);
      output["CorrectSpectra"] -> MakePlot1D("BoerMuldersBlue", PHEC::Type::Angle, ofiles[2], 3);
      if (!isPAu) {
        output["CorrectSpectra"] -> MakePlot1D("CollinsYell", PHEC::Type::Angle, ofiles[1], 3);
        output["CorrectSpectra"] -> MakePlot1D("BoerMuldersYell", PHEC::Type::Angle, ofiles[2], 3);
      }

      /* TODO add 2D correction */

    }  // end index loop
    std::cout << "    Completed correction plots." << std::endl;

  }  // end CorrectSpectra plot

  // --------------------------------------------------------------------------
  // do spin ratios
  // --------------------------------------------------------------------------
  if (plot == PHEC::Output::Plots::SpinRatios) {

    // set indices to loop over
    PHEC::PlotIndexVector loops;
    loops.DoAllSpecies();
    loops.DoAllPt();

    // get plot indices
    std::vector<PHEC::Type::PlotIndex> indices;
    loops.GetVector(indices);
    std::cout << "    Beginning spin ratio plots." << std::endl;

    // loop through combinations to plot
    for (std::size_t idx = 0; idx < indices.size(); ++idx) {

      // only consider blue polarizations for pAu
      const bool isPAu = input.IsPAu(indices[idx]);
      if (isPAu && !input.IsBluePolarization(indices[idx])) {
        continue;
      }

      // make sure collision system is correct
      if (isPAu) output.GetMaker().SetTextBox( BO::Text(indices[idx].species) );

      // set index
      output.UpdateIndex(indices[idx]);

      // calculate/apply corrections for each desired 1D histogram
      output["SpinRatios"] -> MakePlot1D("EEC", PHEC::Type::Side, ofiles[0]);
      output["SpinRatios"] -> MakePlot1D("CollinsBlue", PHEC::Type::Angle, ofiles[1], 3);
      output["SpinRatios"] -> MakePlot1D("BoerMuldersBlue", PHEC::Type::Angle, ofiles[2], 3);
      if (!isPAu) {
        output["SpinRatios"] -> MakePlot1D("CollinsYell", PHEC::Type::Angle, ofiles[1], 3);
        output["SpinRatios"] -> MakePlot1D("BoerMuldersYell", PHEC::Type::Angle, ofiles[2], 3);
      }

      /* TODO add 2D correction */

    }  // end index loop
    std::cout << "    Completed spin ratio plots." << std::endl;

  }  // end SpinRatios plot

  // --------------------------------------------------------------------------
  // close files & exit
  // --------------------------------------------------------------------------
  PHEC::Tools::CloseFiles(ofiles);
  std::cout << "    Closed files.\n"
            << "  Finished PHENIX ENC plotting routines!\n"
            << std::endl;

  // exit routine
  return;

}

/// end =======================================================================
