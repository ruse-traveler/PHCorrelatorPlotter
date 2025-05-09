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
      ofiles.push_back( PHEC::Tools::OpenFile("simVsDataEEC.ppRun15_forDiFFCHeck.d3m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("simVsDataCollins.ppRun15_forDiFFCHeck.d3m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("simVsDataBoerMulders.ppRun15_forDiFFCHeck.d3m5y2025.root", "recreate") );
      break;

    case PHEC::Output::Plots::RecoVsData:
      ofiles.push_back( PHEC::Tools::OpenFile("recoVsDataEEC.ppRun15_forDiFFCHeck.d3m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("recoVsDataCollins.ppRun15_forDiFFCHeck.d3m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("recoVsDataBoerMulders.ppRun15_forDiFFCHeck.d3m5y2025.root", "recreate") );
      break;

    case PHEC::Output::Plots::VsPtJet:
      ofiles.push_back( PHEC::Tools::OpenFile("vsPtJetEEC.ppRun15_forDiFFCHeck.d3m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("vsPtJetCollins.ppRun15_forDiFFCHeck.d3m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("vsPtJetBoerMulders.ppRun15_forDiFFCHeck.d3m5y2025.root", "recreate") );
      break;

    case PHEC::Output::Plots::PPVsPAu:
      ofiles.push_back( PHEC::Tools::OpenFile("ppVsPAuEEC.ppRun15_forDiFFCHeck.d3m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("ppVsPAuCollins.ppRun15_forDiFFCHeck.d3m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("ppVsPAuBoerMulders.ppRun15_forDiFFCHeck.d3m5y2025.root", "recreate") );
      break;

    case PHEC::Output::Plots::CorrectSpectra:
      ofiles.push_back( PHEC::Tools::OpenFile("correctedEEC.ppRun15_forDiFFCHeck.d3m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("correctedCollins.ppRun15_forDiFFCHeck.d3m5y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("correctedBoerMulders.ppRun15_forDiFFCHeck.d3m5y2025.root", "recreate") );
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

    PHEC::Type::PlotIndex idx(-1);
    std::cout << "    Beginning sim vs. data plots." << std::endl;

    // loop through all combinations of species, jet pt,charge, and spin
    for (idx.species = 0; idx.species < input.GetFiles().GetSpeciesTags().size(); ++idx.species) {
      for (idx.pt = 0; idx.pt < input.GetHists().GetPtTags().size(); ++idx.pt) {
        for (idx.chrg = 0; idx.chrg < input.GetHists().GetChargeTags().size(); ++idx.chrg) {
          for (idx.spin = 0; idx.spin < input.GetHists().GetSpinTags().size(); ++idx.spin) {

            // only consider blue polarizations for pAu
            const bool isPAu = input.IsPAu(idx);
            if (isPAu && !input.IsBluePolarization(idx)) {
              continue;
            }

            // FIXME remove after we rerun p+Au samples
            if (isPAu) continue;

            // make sure collision system is correct
            if (isPAu) maker.SetTextBox( BO::Text(idx.species) );

            // set index
            output.UpdateIndex(idx);

            // create comparison for each desired 1D histogram
            output["SimVsData"] -> MakePlot1D("EEC", PHEC::Type::Side, ofiles[0]);
            output["SimVsData"] -> MakePlot1D("CollinsBlue", PHEC::Type::Angle, ofiles[1]);
            output["SimVsData"] -> MakePlot1D("BoerMuldersBlue", PHEC::Type::Angle, ofiles[2]);
            if (!isPAu) {
              output["SimVsData"] -> MakePlot1D("CollinsYell", PHEC::Type::Angle, ofiles[1]);
              output["SimVsData"] -> MakePlot1D("BoerMuldersYell", PHEC::Type::Angle, ofiles[2]);
            }

            // create comparison for each desired 2D histogram
            output["SimVsData"] -> MakePlot2D("CollinsBlueVsR", ofiles[1]);
            output["SimVsData"] -> MakePlot2D("BoerMuldersBlueVsR", ofiles[2]);
            if (!isPAu) {
              output["SimVsData"] -> MakePlot2D("CollinsYellVsR", ofiles[1]);
              output["SimVsData"] -> MakePlot2D("BoerMuldersYellVsR", ofiles[2]);
            }

          }  // end spin loop
        }  // end jet charge loop
      }  // end pt jet loop
    }  // end species loop
    std::cout << "    Completed sim vs. data plots." << std::endl;

  }  // end SimVsData plot

  // --------------------------------------------------------------------------
  // compare reco vs. data distributions
  // --------------------------------------------------------------------------
  if (plot == PHEC::Output::Plots::RecoVsData) {

    PHEC::Type::PlotIndex idx(-1);
    std::cout << "    Beginning reco vs. data plots." << std::endl;

    // loop through all combinations of species, jet pt,charge, and spin
    for (idx.species = 0; idx.species < input.GetFiles().GetSpeciesTags().size(); ++idx.species) {
      for (idx.pt = 0; idx.pt < input.GetHists().GetPtTags().size(); ++idx.pt) {
        for (idx.chrg = 0; idx.chrg < input.GetHists().GetChargeTags().size(); ++idx.chrg) {
          for (idx.spin = 0; idx.spin < input.GetHists().GetSpinTags().size(); ++idx.spin) {

            // only consider blue polarizations for pAu
            const bool isPAu = input.IsPAu(idx);
            if (isPAu && !input.IsBluePolarization(idx)) {
              continue;
            }

            // FIXME remove after we rerun p+Au samples
            if (isPAu) continue;

            // make sure collision system is correct
            if (isPAu) maker.SetTextBox( BO::Text(idx.species) );

            // set index
            output.UpdateIndex(idx);

            // create comparison for each desired 1D histogram
            output["RecoVsData"] -> MakePlot1D("EEC", PHEC::Type::Side, ofiles[0]);
            output["RecoVsData"] -> MakePlot1D("CollinsBlue", PHEC::Type::Angle, ofiles[1]);
            output["RecoVsData"] -> MakePlot1D("BoerMuldersBlue", PHEC::Type::Angle, ofiles[2]);
            if (!isPAu) {
              output["RecoVsData"] -> MakePlot1D("CollinsYell", PHEC::Type::Angle, ofiles[1]);
              output["RecoVsData"] -> MakePlot1D("BoerMuldersYell", PHEC::Type::Angle, ofiles[2]);
            }

            /* TODO make 2D comparisons */

          }  // end spin loop
        }  // end jet charge loop
      }  // end pt jet loop
    }  // end species loop
    std::cout << "    Completed sim vs. reco plots." << std::endl;

  }  // end SimVsData plot

  // --------------------------------------------------------------------------
  // compare distributions as a function of pt jet
  // --------------------------------------------------------------------------
  if (plot == PHEC::Output::Plots::VsPtJet) {

    PHEC::Type::PlotIndex idx(-1);
    std::cout << "    Beginning vs. ptJet plots." << std::endl;

    // loop through all combinations of species, level, charge, and spin
    for (idx.species = 0; idx.species < input.GetFiles().GetSpeciesTags().size(); ++idx.species) {
      for (idx.level = 0; idx.level < input.GetFiles().GetLevelTags().size(); ++idx.level) {
        for (idx.chrg = 0; idx.chrg < input.GetHists().GetChargeTags().size(); ++idx.chrg) {
          for (idx.spin = 0; idx.spin < input.GetHists().GetSpinTags().size(); ++idx.spin) {

            // only consider blue polarizations for pAu
            const bool isPAu = input.IsPAu(idx);
            if (isPAu && !input.IsBluePolarization(idx)) {
              continue;
            }

            // FIXME remove after we rerun p+Au samples
            if (isPAu) continue;

            // make sure collision system is correct
            if (isPAu) maker.SetTextBox( BO::Text(idx.species) );

            // set index
            output.UpdateIndex(idx);

            // create comparisons for each desired 1D histogram
            output["VsPtJet"] -> MakePlot1D("EEC", PHEC::Type::Side, ofiles[0]);
            output["VsPtJet"] -> MakePlot1D("CollinsBlue", PHEC::Type::Angle, ofiles[1]);
            output["VsPtJet"] -> MakePlot1D("BoerMuldersBlue", PHEC::Type::Angle, ofiles[2]);
            if (!isPAu) {
              output["VsPtJet"] -> MakePlot1D("CollinsYell", PHEC::Type::Angle, ofiles[1]);
              output["VsPtJet"] -> MakePlot1D("BoerMuldersYell", PHEC::Type::Angle, ofiles[2]);
            }

            // create comparisons for each desired 2D histogram
            output["VsPtJet"] -> MakePlot2D("CollinsBlueVsR", ofiles[1]);
            output["VsPtJet"] -> MakePlot2D("BoerMuldersBlueVsR", ofiles[2]);
            if (!isPAu) {
              output["VsPtJet"] -> MakePlot2D("CollinsYellVsR", ofiles[1]);
              output["VsPtJet"] -> MakePlot2D("BoerMuldersYellVsR", ofiles[2]);
            }

          }  // end spin loop
        }  // end jet charge loop
      }  // end level oop
    }  // end species loop
    std::cout << "    Completed vs. ptJet plots." << std::endl;

  }  // end VsPtJet plot

  // --------------------------------------------------------------------------
  // compare pp vs. pau distributions
  // --------------------------------------------------------------------------
  if (plot == PHEC::Output::Plots::PPVsPAu) {

    PHEC::Type::PlotIndex idx(-1);
    std::cout << "    Beginning pp vs. pAu plots." << std::endl;

    // loop through all combinations of level, charge, and spin
    for (idx.level = 0; idx.level < input.GetFiles().GetLevelTags().size(); ++idx.level) {
      for (idx.chrg = 0; idx.chrg < input.GetHists().GetChargeTags().size(); ++idx.chrg) {
        for (idx.spin = 0; idx.spin < input.GetHists().GetSpinTags().size(); ++idx.spin) {

          // only consider blue polarizations for pAu
          if (!input.IsBluePolarization(idx)) continue;

          // set index
          output.UpdateIndex(idx);

          // create comparisons for each desired 1D histogram
          output["PPVsPAu"] -> MakePlot1D("EEC", PHEC::Type::Side, ofiles[0]);
          output["PPVsPAu"] -> MakePlot1D("CollinsBlue", PHEC::Type::Angle, ofiles[1]);
          output["PPVsPAu"] -> MakePlot1D("BoerMuldersBlue", PHEC::Type::Angle, ofiles[2]);

          /* TODO add 2D comparison */

        }  // end spin loop
      }  // end jet charge loop
    }  // end level loop
    std::cout << "    Completed pp vs. pAu plots." << std::endl;

  }  // end PPVsPAu plot

  // --------------------------------------------------------------------------
  // apply correction factors
  // --------------------------------------------------------------------------
  if (plot == PHEC::Output::Plots::CorrectSpectra) {

    PHEC::Type::PlotIndex idx(-1);
    std::cout << "    Beginning correction plots." << std::endl;

    // loop through all combinations of species, charge, and spin
    for (idx.species = 0; idx.species < input.GetFiles().GetSpeciesTags().size(); ++idx.species) {
      for (idx.chrg = 0; idx.chrg < input.GetHists().GetChargeTags().size(); ++idx.chrg) {
        for (idx.spin = 0; idx.spin < input.GetHists().GetSpinTags().size(); ++idx.spin) {

          // only consider blue polarizations for pAu
          const bool isPAu = input.IsPAu(idx);
          if (isPAu && !input.IsBluePolarization(idx)) {
            continue;
          }

          // FIXME remove after we rerun p+Au samples
          if (isPAu) continue;

          // make sure collision system is correct
          if (isPAu) maker.SetTextBox( BO::Text(idx.species) );

          // set index
          output.UpdateIndex(idx);

          // calculate/apply corrections for each desired 1D histogram
          output["CorrectSpectra"] -> MakePlot1D("EEC", PHEC::Type::Side, ofiles[0]);
          output["CorrectSpectra"] -> MakePlot1D("CollinsBlue", PHEC::Type::Angle, ofiles[1]);
          output["CorrectSpectra"] -> MakePlot1D("BoerMuldersBlue", PHEC::Type::Angle, ofiles[2]);
          if (!isPAu) {
            output["CorrectSpectra"] -> MakePlot1D("CollinsYell", PHEC::Type::Angle, ofiles[1]);
            output["CorrectSpectra"] -> MakePlot1D("BoerMuldersYell", PHEC::Type::Angle, ofiles[2]);
          }

          /* TODO add 2D correction */

        }  // end spin loop
      }  // end charge loop
    }   // end species loop
    std::cout << "    Completed correction plots." << std::endl;

  }  // end CorrectSpectra plot

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
