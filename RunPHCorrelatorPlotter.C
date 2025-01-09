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
#include "options/PlotsToMake.h"

// abbreviate common namespaces
namespace BO = BaseOptions;
namespace PM = PlotsToMake;



// ============================================================================
//! Run PHENIX ENC plotting routines
// ============================================================================
void RunPHCorrelatorPlotter(const int plot = PM::SimVsReco) {

  // announce start
  std::cout << "\n  Beginning PHENIX ENC plotting routines..." << std::endl;

  // ==========================================================================
  // open outputs & load inputs
  // ==========================================================================

  // open relevant output files
  std::vector<TFile*> ofiles;
  switch (plot) {

    case PM::SimVsReco:
      ofiles.push_back( PHEC::Tools::OpenFile("simVsRecoEEC.ppRun15.d7m1y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("simVsRecoCollins.ppRun15.d7m1y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("simVsRecoHadAvg.ppRun15.d7m1y2025.root", "recreate") );
      break;

    case PM::VsPtJet:
      ofiles.push_back( PHEC::Tools::OpenFile("vsPtJetEEC.ppRun15.d7m1y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("vsPtJetCollins.ppRun15.d7m1y2025.root", "recreate") );
      ofiles.push_back( PHEC::Tools::OpenFile("vsPtJetHadAvg.ppRun15.d7m1y2025.root", "recreate") );
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

  // ==========================================================================
  // compare sim vs. data distributions
  // ==========================================================================
  if (plot == PM::SimVsReco) {

    // loop through all combinations of species, jet pt, and spin
    for (std::size_t ico = 0; ico < io.Files().GetSpeciesTags().size(); ++ico) {
      for (std::size_t ipt = 0; ipt < io.Hists().GetPtTags().size(); ++ipt) {
        for (std::size_t isp = 0; isp < io.Hists().GetSpinTags().size(); ++isp) {

          // only consider blue polarizations for pAu
          if (ico == InFiles::PAu) {
            const bool isOnlyBlue = ((isp == InHists::BU) || (isp == InHists::BD) || (isp == InHists::Int));
            if (!isOnlyBlue) continue;
          }

          // make sure collision system is correct
          if (ico == InFiles::PAu) plotter.SetTextBox( BO::Text(ico) );

          // create comparison for each desired 1D histogram
          PM::SimVsReco1D("EEC", ico, ipt, isp, SB::Side, io, plotter, ofiles[0]);
          PM::SimVsReco1D("SpinCollinsBlue", ico, ipt, isp, SB::Angle, io, plotter, ofiles[1]);
          PM::SimVsReco1D("SpinHadAvgBlue", ico, ipt, isp, SB::Angle, io, plotter, ofiles[2]);
          if (ico != InFiles::PAu) {
            PM::SimVsReco1D("SpinCollinsYell", ico, ipt, isp, SB::Angle, io, plotter, ofiles[1]);
            PM::SimVsReco1D("SpinHadAvgYell", ico, ipt, isp, SB::Angle, io, plotter, ofiles[2]);
          }

          // create comparison for each desired 2D histogram
          PM::SimVsReco2D("EECCollinsBlueVsR", ico, ipt, isp, io, plotter, ofiles[1]);
          PM::SimVsReco2D("EECHadAvgBlueVsR", ico, ipt, isp, io, plotter, ofiles[2]);
          if (ico != InFiles::PAu) {
            PM::SimVsReco2D("EECCollinsYellVsR", ico, ipt, isp, io, plotter, ofiles[1]);
            PM::SimVsReco2D("EECHadAvgYellVsR", ico, ipt, isp, io, plotter, ofiles[2]);
          }

        }  // end spin loop
      }  // end pt jet loop
    }  // end species loop

  }  // end SimVsReco plot
  std::cout << "    Completed sim vs. reco plots." << std::endl;

  // ==========================================================================
  // compare distributions as a function of pt jet
  // ==========================================================================
  if (plot == PM::VsPtJet) {

    // loop through all combinations of species, level, and spin
    for (std::size_t ico = 0; ico < io.Files().GetSpeciesTags().size(); ++ico) {
      for (std::size_t ilv = 0; ilv < io.Files().GetLevelTags().size(); ++ilv) {
        for (std::size_t isp = 0; isp < io.Hists().GetSpinTags().size(); ++isp) {

          // only consider blue polarizations for pAu
          if (ico == InFiles::PAu) {
            const bool isOnlyBlue = ((isp == InHists::BU) || (isp == InHists::BD) || (isp == InHists::Int));
            if (!isOnlyBlue) continue;
          }

          // make sure collision system is correct
          if (ico == InFiles::PAu) plotter.SetTextBox( BO::Text(ico) );

          // create comparisons for each desired 1D histogram
          PM::VsPtJet1D("EEC", ico, ilv, isp, SB::Side, io, plotter, ofiles[0]);
          PM::VsPtJet1D("SpinCollinsBlue", ico, ilv, isp, SB::Angle, io, plotter, ofiles[1]);
          PM::VsPtJet1D("SpinHadAvgBlue", ico, ilv, isp, SB::Angle, io, plotter, ofiles[2]);
          if (ico != InFiles::PAu) {
            PM::VsPtJet1D("SpinCollinsYell", ico, ilv, isp, SB::Angle, io, plotter, ofiles[1]);
            PM::VsPtJet1D("SpinHadAvgYell", ico, ilv, isp, SB::Angle, io, plotter, ofiles[2]);
          }

          // create comparisons for each desired 2D histogram
          PM::VsPtJet2D("EECCollinsBlueVsR", ico, ilv, isp, io, plotter, ofiles[1]);
          PM::VsPtJet2D("EECHadAvgBlueVsR", ico, ilv, isp, io, plotter, ofiles[2]);
          if (ico != InFiles::PAu) {
            PM::VsPtJet2D("EECCollinsYellVsR", ico, ilv, isp, io, plotter, ofiles[1]);
            PM::VsPtJet2D("EECHadAvgYellVsR", ico, ilv, isp, io, plotter, ofiles[2]);
          }

        }  // end spin loop
      }  // end level oop
    }  // end species loop
  }  // end VsPtJet plot

  /* TODO add EEC pp vs. pau comparison here */

  // close files & exit -------------------------------------------------------

  // close output file
  for (std::size_t iout = 0; iout < ofiles.size(); ++iout) {
    ofiles[iout] -> cd();
    ofiles[iout] -> Close();
  }
  return;

}

// end ========================================================================
