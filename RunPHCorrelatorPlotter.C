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
#include "options/InputOutput.h"
#include "options/PlotOptions.h"
#include "options/PlotsToMake.h"

// abbreviate common namespaces
namespace BO = BaseOptions;
namespace PO = PlotOptions;
namespace PM = PlotsToMake;



// ============================================================================
//! Run PHENIX ENC plotting routines
// ============================================================================
void RunPHCorrelatorPlotter(const int plot = PM::SimVsReco) {

  // announce start
  std::cout << "\n  Beginning PHENIX ENC plotting routines..." << std::endl;

  // --------------------------------------------------------------------------
  // open outputs & load inputs
  // --------------------------------------------------------------------------
  std::vector<TFile*> ofiles;
  switch (plot) {

    case PM::SimVsReco:
      ofiles.push_back( PHEC::Tools::OpenFile("simVsRecoEEC.ppRun15_debuggingPlotIndex.d17m3y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("simVsRecoCollins.ppRun15_debuggingPlotIndex.d17m3y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("simVsRecoBoerMulders.ppRun15_debuggingPlotIndex.d17m3y2025.root", "recreate") );
      break;

    case PM::VsPtJet:
      ofiles.push_back( PHEC::Tools::OpenFile("vsPtJetEEC.ppRun15_debuggingPlotIndex.d17m3y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("vsPtJetCollins.ppRun15_debuggingPlotIndex.d17m3y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("vsPtJetBoerMulders.ppRun15_debuggingPlotIndex.d17m3y2025.root", "recreate") );
      break;

    case PM::PPVsPAu:
      ofiles.push_back( PHEC::Tools::OpenFile("ppVsPAuEEC.ppRun15_debuggingPlotIndex.d17m3y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("ppVsPAuCollins.ppRun15_debuggingPlotIndex.d17m3y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("ppVsPAuBoerMulders.ppRun15_debuggingPlotIndex.d17m3y2025.root", "recreate") );
      break;

    case PM::CorrectSpectra:
      ofiles.push_back( PHEC::Tools::OpenFile("correctedEEC.ppRun15_debuggingPlotIndex.d17m3y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("correctedCollins.ppRun15_debuggingPlotIndex.d17m3y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("correctedBoerMulders.ppRun15_debuggingPlotIndex.d17m3y2025.root", "recreate") );
      break;

    default:
      std::cerr << "PANIC: unknown plot (" << plot << ") to make!" << std::endl;
      break;

  }
  std::cout << "    Opened output file" << std::endl;

  // load input options
  InputOutput io = InputOutput();
  std::cout << "    Loaded input options." << std::endl;

  // create maker
  PHEC::PHCorrelatorPlotMaker maker = PHEC::PHCorrelatorPlotMaker(
    BO::BasePlotStyle(),
    BO::BaseTextStyle(),
    BO::Text()
  );
  std::cout << "    Made maker." << std::endl;

  // --------------------------------------------------------------------------
  // compare sim vs. data distributions
  // --------------------------------------------------------------------------
  if (plot == PM::SimVsReco) {

    // loop through all combinations of species, jet pt,charge, and spin
    PHEC::Type::PlotIndex idx(-1);
    for (idx.species = 0; idx.species < io.Files().GetSpeciesTags().size(); ++idx.species) {
      for (idx.pt = 0; idx.pt < io.Hists().GetPtTags().size(); ++idx.pt) {
        for (idx.chrg = 0; idx.chrg < io.Hists().GetChargeTags().size(); ++idx.chrg) {
          for (idx.spin = 0; idx.spin < io.Hists().GetSpinTags().size(); ++idx.spin) {

            // only consider blue polarizations for pAu
            const bool isPAu = io.IsPAu(idx);
            if (isPAu && !io.IsBluePolarization(idx)) {
              continue;
            }

            // make sure collision system is correct
            if (isPAu) maker.SetTextBox( BO::Text(idx.species) );

            // create comparison for each desired 1D histogram
            PM::SimVsReco1D("EEC", PO::Side, idx, io, maker, ofiles[0]);
            PM::SimVsReco1D("CollinsBlue", PO::Angle, idx, io, maker, ofiles[1]);
            PM::SimVsReco1D("BoerMuldersBlue", PO::Angle, idx, io, maker, ofiles[2]);
            if (isPAu) {
              PM::SimVsReco1D("CollinsYell", PO::Angle, idx, io, maker, ofiles[1]);
              PM::SimVsReco1D("BoerMuldersYell", PO::Angle, idx, io, maker, ofiles[2]);
            }

            // create comparison for each desired 2D histogram
            PM::SimVsReco2D("CollinsBlueVsR", idx, io, maker, ofiles[1]);
            PM::SimVsReco2D("BoerMuldersBlueVsR", idx, io, maker, ofiles[2]);
            if (!isPAu) {
              PM::SimVsReco2D("CollinsYellVsR", idx, io, maker, ofiles[1]);
              PM::SimVsReco2D("BoerMuldersYellVsR", idx, io, maker, ofiles[2]);
            }

          }  // end spin loop
        }  // end jet charge loop
      }  // end pt jet loop
    }  // end species loop
    std::cout << "    Completed sim vs. reco plots." << std::endl;

  }  // end SimVsReco plot

  // --------------------------------------------------------------------------
  // compare distributions as a function of pt jet
  // --------------------------------------------------------------------------
  if (plot == PM::VsPtJet) {

    // loop through all combinations of species, level, charge, and spin
    PHEC::Type::PlotIndex idx(-1);
    for (idx.species = 0; idx.species < io.Files().GetSpeciesTags().size(); ++idx.species) {
      for (idx.level = 0; idx.level < io.Files().GetLevelTags().size(); ++idx.level) {
        for (idx.chrg = 0; idx.chrg < io.Hists().GetChargeTags().size(); ++idx.chrg) {
          for (idx.spin = 0; idx.spin < io.Hists().GetSpinTags().size(); ++idx.spin) {

            // only consider blue polarizations for pAu
            const bool isPAu = io.IsPAu(idx);
            if (isPAu && !io.IsBluePolarization(idx)) {
              continue;
            }

            // make sure collision system is correct
            if (isPAu) maker.SetTextBox( BO::Text(idx.species) );

            // create comparisons for each desired 1D histogram
            PM::VsPtJet1D("EEC", PO::Side, idx, io, maker, ofiles[0]);
            PM::VsPtJet1D("CollinsBlue", PO::Angle, idx, io, maker, ofiles[1]);
            PM::VsPtJet1D("BoerMuldersBlue", PO::Angle, idx, io, maker, ofiles[2]);
            if (!isPAu) {
              PM::VsPtJet1D("CollinsYell", PO::Angle, idx, io, maker, ofiles[1]);
              PM::VsPtJet1D("BoerMuldersYell", PO::Angle, idx, io, maker, ofiles[2]);
            }

            // create comparisons for each desired 2D histogram
            PM::VsPtJet2D("CollinsBlueVsR", idx, io, maker, ofiles[1]);
            PM::VsPtJet2D("BoerMuldersBlueVsR", idx, io, maker, ofiles[2]);
            if (!isPAu) {
              PM::VsPtJet2D("CollinsYellVsR", idx, io, maker, ofiles[1]);
              PM::VsPtJet2D("BoerMuldersYellVsR", idx, io, maker, ofiles[2]);
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
  if (plot == PM::PPVsPAu) {

    // loop through all combinations of level, charge, and spin
    PHEC::Type::PlotIndex idx(-1);
    for (idx.level = 0; idx.level < io.Files().GetLevelTags().size(); ++idx.level) {
      for (idx.chrg = 0; idx.chrg < io.Hists().GetChargeTags().size(); ++idx.chrg) {
        for (idx.spin = 0; idx.spin < io.Hists().GetSpinTags().size(); ++idx.spin) {

          // only consider blue polarizations for pAu
          if (!io.IsBluePolarization(idx)) continue;

          // create comparisons for each desired 1D histogram
          PM::PPVsPAu1D("EEC", PO::Side, idx, io, maker, ofiles[0]);
          PM::PPVsPAu1D("CollinsBlue", PO::Angle, idx, io, maker, ofiles[1]);
          PM::PPVsPAu1D("BoerMuldersBlue", PO::Angle, idx, io, maker, ofiles[2]);

          /* TODO add 2D comparison */

        }  // end spin loop
      }  // end jet charge loop
    }  // end level loop
    std::cout << "    Completed pp vs. pAu plots." << std::endl;

  }  // end PPVsPAu plot

  // --------------------------------------------------------------------------
  // apply correction factors
  // --------------------------------------------------------------------------
  if (plot == PM::CorrectSpectra) {

    // loop through all combinations of species, charge, and spin
    PHEC::Type::PlotIndex idx(-1);
    for (idx.species = 0; idx.species < io.Files().GetSpeciesTags().size(); ++idx.species) {
      for (idx.chrg = 0; idx.chrg < io.Hists().GetChargeTags().size(); ++idx.chrg) {
        for (idx.spin = 0; idx.spin < io.Hists().GetSpinTags().size(); ++idx.spin) {

          // only consider blue polarizations for pAu
          const bool isPAu = io.IsPAu(idx);
          if (isPAu && !io.IsBluePolarization(idx)) {
            continue;
          }

          // make sure collision system is correct
          if (isPAu) maker.SetTextBox( BO::Text(idx.species) );

          // calculate/apply corrections for each desired 1D histogram
          PM::CorrectSpectra1D("EEC", PO::Side, idx, io, maker, ofiles[0]);
          PM::CorrectSpectra1D("CollinsBlue", PO::Angle, idx, io, maker, ofiles[1]);
          PM::CorrectSpectra1D("BoerMuldersBlue", PO::Angle, idx, io, maker, ofiles[2]);
          if (!isPAu) {
            PM::CorrectSpectra1D("CollinsYell", PO::Angle, idx, io, maker, ofiles[1]);
            PM::CorrectSpectra1D("BoerMuldersYell", PO::Angle, idx, io, maker, ofiles[2]);
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

// end ========================================================================
