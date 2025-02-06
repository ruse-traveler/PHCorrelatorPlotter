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
#include "include/PHCorrelatorPlotting.h"
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
      ofiles.push_back( PHEC::Tools::OpenFile("simVsRecoEEC.ppRun15_forCorrections.d6m2y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("simVsRecoCollins.ppRun15_forCorrections.d6m2y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("simVsRecoBoerMulders.ppRun15_forCorrections.d6m2y2025.root", "recreate") );
      break;

    case PM::VsPtJet:
      ofiles.push_back( PHEC::Tools::OpenFile("vsPtJetEEC.ppRun15_forCorrections.d6m2y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("vsPtJetCollins.ppRun15_forCorrections.d6m2y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("vsPtJetBoerMulders.ppRun15_forCorrections.d6m2y2025.root", "recreate") );
      break;

    case PM::PPVsPAu:
      ofiles.push_back( PHEC::Tools::OpenFile("ppVsPAuEEC.ppRun15_forCorrections.d6m2y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("ppVsPAuCollins.ppRun15_forCorrections.d6m2y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("ppVsPAuBoerMulders.ppRun15_forCorrections.d6m2y2025.root", "recreate") );
      break;

    case PM::CorrectSpectra:
      ofiles.push_back( PHEC::Tools::OpenFile("correctedEEC.ppRun15_forCorrections.d6m2y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("correctedCollins.ppRun15_forCorrections.d6m2y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("correctedBoerMulders.ppRun15_forCorrections.d6m2y2025.root", "recreate") );
      break;

    default:
      std::cerr << "PANIC: unknown plot (" << plot << ") to make!" << std::endl;
      break;

  }
  std::cout << "    Opened output file" << std::endl;

  // load input options
  InputOutput io = InputOutput();
  std::cout << "    Loaded input options." << std::endl;

  // create plotter
  PHEC::PHCorrelatorPlotter plotter = PHEC::PHCorrelatorPlotter(
    BO::BasePlotStyle(),
    BO::BaseTextStyle(),
    BO::Text()
  );
  std::cout << "    Made plotter." << std::endl;

  // --------------------------------------------------------------------------
  // compare sim vs. data distributions
  // --------------------------------------------------------------------------
  if (plot == PM::SimVsReco) {

    // loop through all combinations of species, jet pt,charge, and spin
    for (std::size_t ico = 0; ico < io.Files().GetSpeciesTags().size(); ++ico) {
      for (std::size_t ipt = 0; ipt < io.Hists().GetPtTags().size(); ++ipt) {
        for (std::size_t ich = 0; ich < io.Hists().GetChargeTags().size(); ++ich) {
          for (std::size_t isp = 0; isp < io.Hists().GetSpinTags().size(); ++isp) {

            // only consider blue polarizations for pAu
            if (ico == InFiles::PAu) {
              const bool isOnlyBlue = ((isp == InHists::BU) || (isp == InHists::BD) || (isp == InHists::Int));
              if (!isOnlyBlue) continue;
            }

            // make sure collision system is correct
            if (ico == InFiles::PAu) plotter.SetTextBox( BO::Text(ico) );

            // create comparison for each desired 1D histogram
            PM::SimVsReco1D("EEC", ico, ipt, ich, isp, PO::Side, io, plotter, ofiles[0]);
            PM::SimVsReco1D("CollinsBlue", ico, ipt, ich, isp, PO::Angle, io, plotter, ofiles[1]);
            PM::SimVsReco1D("BoerMuldersBlue", ico, ipt, ich, isp, PO::Angle, io, plotter, ofiles[2]);
            if (ico != InFiles::PAu) {
              PM::SimVsReco1D("CollinsYell", ico, ipt, ich, isp, PO::Angle, io, plotter, ofiles[1]);
              PM::SimVsReco1D("BoerMuldersYell", ico, ipt, ich, isp, PO::Angle, io, plotter, ofiles[2]);
            }

            // create comparison for each desired 2D histogram
            PM::SimVsReco2D("CollinsBlueVsR", ico, ipt, ich, isp, io, plotter, ofiles[1]);
            PM::SimVsReco2D("BoerMuldersBlueVsR", ico, ipt, ich, isp, io, plotter, ofiles[2]);
            if (ico != InFiles::PAu) {
              PM::SimVsReco2D("CollinsYellVsR", ico, ipt, ich, isp, io, plotter, ofiles[1]);
              PM::SimVsReco2D("BoerMuldersYellVsR", ico, ipt, ich, isp, io, plotter, ofiles[2]);
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
    for (std::size_t ico = 0; ico < io.Files().GetSpeciesTags().size(); ++ico) {
      for (std::size_t ilv = 0; ilv < io.Files().GetLevelTags().size(); ++ilv) {
        for (std::size_t ich = 0; ich < io.Hists().GetChargeTags().size(); ++ich) {
          for (std::size_t isp = 0; isp < io.Hists().GetSpinTags().size(); ++isp) {

            // only consider blue polarizations for pAu
            if (ico == InFiles::PAu) {
              const bool isOnlyBlue = ((isp == InHists::BU) || (isp == InHists::BD) || (isp == InHists::Int));
              if (!isOnlyBlue) continue;
            }

            // make sure collision system is correct
            if (ico == InFiles::PAu) plotter.SetTextBox( BO::Text(ico) );

            // create comparisons for each desired 1D histogram
            PM::VsPtJet1D("EEC", ico, ilv, ich, isp, PO::Side, io, plotter, ofiles[0]);
            PM::VsPtJet1D("CollinsBlue", ico, ilv, ich, isp, PO::Angle, io, plotter, ofiles[1]);
            PM::VsPtJet1D("BoerMuldersBlue", ico, ilv, ich, isp, PO::Angle, io, plotter, ofiles[2]);
            if (ico != InFiles::PAu) {
              PM::VsPtJet1D("CollinsYell", ico, ilv, ich, isp, PO::Angle, io, plotter, ofiles[1]);
              PM::VsPtJet1D("BoerMuldersYell", ico, ilv, ich, isp, PO::Angle, io, plotter, ofiles[2]);
            }

            // create comparisons for each desired 2D histogram
            PM::VsPtJet2D("CollinsBlueVsR", ico, ilv, ich, isp, io, plotter, ofiles[1]);
            PM::VsPtJet2D("BoerMuldersBlueVsR", ico, ilv, ich, isp, io, plotter, ofiles[2]);
            if (ico != InFiles::PAu) {
              PM::VsPtJet2D("CollinsYellVsR", ico, ilv, ich, isp, io, plotter, ofiles[1]);
              PM::VsPtJet2D("BoerMuldersYellVsR", ico, ilv, ich, isp, io, plotter, ofiles[2]);
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
    for (std::size_t ilv = 0; ilv < io.Files().GetLevelTags().size(); ++ilv) {
      for (std::size_t ich = 0; ich < io.Hists().GetChargeTags().size(); ++ich) {
        for (std::size_t isp = 0; isp < io.Hists().GetSpinTags().size(); ++isp) {

          // only consider blue polarizations for pAu
          const bool isOnlyBlue = ((isp == InHists::BU) || (isp == InHists::BD) || (isp == InHists::Int));
          if (!isOnlyBlue) continue;

          // create comparisons for each desired 1D histogram
          PM::PPVsPAu1D("EEC", ilv, ich, isp, PO::Side, io, plotter, ofiles[0]);
          PM::PPVsPAu1D("CollinsBlue", ilv, ich, isp, PO::Angle, io, plotter, ofiles[1]);
          PM::PPVsPAu1D("BoerMuldersBlue", ilv, ich, isp, PO::Angle, io, plotter, ofiles[2]);

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
    for (std::size_t ico = 0; ico < io.Files().GetSpeciesTags().size(); ++ico) {
      for (std::size_t ich = 0; ich < io.Hists().GetChargeTags().size(); ++ich) {
        for (std::size_t isp = 0; isp < io.Hists().GetSpinTags().size(); ++isp) {

          // only consider blue polarizations for pAu
          const bool isOnlyBlue = ((isp == InHists::BU) || (isp == InHists::BD) || (isp == InHists::Int));
          if (!isOnlyBlue) continue;

          // calculate/apply corrections for each desired 1D histogram
          PM::CorrectSpectra1D("EEC", ico, ich, isp, PO::Side, io, plotter, ofiles[0]);
          PM::CorrectSpectra1D("CollinsBlue", ico, ich, isp, PO::Angle, io, plotter, ofiles[1]);
          PM::CorrectSpectra1D("BoerMuldersBlue", ico, ich, isp, PO::Angle, io, plotter, ofiles[2]);
          if (ico != InFiles::PAu) {
            PM::CorrectSpectra1D("CollinsYell", ico, ich, isp, PO::Angle, io, plotter, ofiles[1]);
            PM::CorrectSpectra1D("BoerMuldersYell", ico, ich, isp, PO::Angle, io, plotter, ofiles[2]);
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
