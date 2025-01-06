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
#include "options/CompareSpectra.h"
#include "options/CompareSpectra2D.h"
#include "options/InputOutput.h"
#include "options/SpectraVsBaseline.h"

// abbreviate common namespaces
namespace BO = BaseOptions;
namespace CS = CompareSpectra;
namespace C2 = CompareSpectra2D;
namespace IO = InputOutput;
namespace SB = SpectraVsBaseline;



// ============================================================================
//! Run PHENIX ENC plotting routines
// ============================================================================
void RunPHCorrelatorPlotter() {

  // announce start
  std::cout << "\n  Beginning PHENIX ENC plotting routines..." << std::endl;

  // open outputs & load inputs -----------------------------------------------

  // open output files
  TFile* ofile = PHEC::Tools::OpenFile("simVsReco.ppRun15.d5m1y2025.root", "recreate");
  std::cout << "    Opened output file" << std::endl;

  // load input options
  IO::InFiles in_files  = IO::LoadInputFiles();
  IO::Strings spe_hist  = IO::LoadSpeciesStrings(IO::Hist);
  IO::Strings spe_legs  = IO::LoadSpeciesStrings(IO::Leg);
  IO::Strings lvl_hist  = IO::LoadLevelStrings(IO::Hist);
  IO::Strings lvl_legs  = IO::LoadLevelStrings(IO::Leg);
  IO::Strings pt_hist   = IO::LoadPtStrings(IO::Hist);
  IO::Strings pt_legs   = IO::LoadPtStrings(IO::Leg);
  IO::Strings spin_hist = IO::LoadSpinStrings(IO::Hist);
  IO::Strings spin_legs = IO::LoadSpinStrings(IO::Leg);
  std::cout << "    Loaded input options." << std::endl;

  // create plotter
  PHEC::PHCorrelatorPlotter plotter = PHEC::PHCorrelatorPlotter(
    BO::BasePlotStyle(),
    BO::BaseTextStyle(),
    BO::Text()
  );
  std::cout << "    Made plotter." << std::endl;

  // compare sim vs. data distributions ---------------------------------------

  // compare sim vs. data EEC spectra
  for (std::size_t ico = 0; ico < spe_hist.size(); ++ico) {
    for (std::size_t ipt = 0; ipt < pt_hist.size(); ++ipt) {
      for (std::size_t isp = 0; isp < spin_hist.size(); ++isp) {

        // make hist tag & canvas name
        const std::string tag    = "DataVsSim" + spe_hist[ico] + "_";
        const std::string canvas = IO::MakeCanvasName("cDataVsSimEEC", pt_hist[ipt], spin_hist[isp], "", spe_hist[ico]);

        // build hist names
        std::string dat_hist = IO::MakeHistName("EEC", lvl_hist[IO::Data], pt_hist[ipt], spin_hist[isp]);
        std::string rec_hist = IO::MakeHistName("EEC", lvl_hist[IO::Reco], pt_hist[ipt], spin_hist[isp]);
        std::string tru_hist = IO::MakeHistName("EEC", lvl_hist[IO::True], pt_hist[ipt], spin_hist[isp]);

        // build hist renames
        std::string dat_name = IO::MakeHistName("EEC", lvl_hist[IO::Data], pt_hist[ipt], spin_hist[isp], tag);
        std::string rec_name = IO::MakeHistName("EEC", lvl_hist[IO::Reco], pt_hist[ipt], spin_hist[isp], tag);
        std::string tru_name = IO::MakeHistName("EEC", lvl_hist[IO::True], pt_hist[ipt], spin_hist[isp], tag);

        // build hist legends
        std::string dat_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::Data]);
        std::string rec_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::Reco]);
        std::string tru_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::True]);

        // bundle input options
        IO::Opts dat_opt = IO::Opts(
          in_files[ico][IO::Data],
          dat_hist,
          dat_name,
          dat_leg,
          899,
          20
        );
        IO::Opts rec_opt = IO::Opts(
          in_files[ico][IO::Reco],
          rec_hist,
          rec_name,
          rec_leg,
          859,
          21
        );
        IO::Opts tru_opt = IO::Opts(
          in_files[ico][IO::True],
          tru_hist,
          tru_name,
          tru_leg,
          923,
          29
        );

        // load into vector
        std::vector<IO::Opts> opts;
        opts.push_back( dat_opt );
        opts.push_back( rec_opt );
        opts.push_back( tru_opt );

        // FIXME change to baseline
        plotter.CompareSpectra(
          CS::Inputs(opts),
          CS::PlotRange(CS::Side),
          CS::NormRange(CS::Side),
          CS::Canvas(canvas, CS::Side),
          ofile
        );

        /* TODO add angle comparisons here */
        /* TODO add 2d comparisons here */

      }  // end spin loop
    }  // end pt jet loop
  }  // end species loop

  /* TODO add EEC vs. pt comparison here */
  /* TODO add EEC pp vs. pau comparison here */

  std::cout << "    Completed sim vs. reco plots." << std::endl;

  // close files & exit -------------------------------------------------------

  // close output file
  ofile -> cd();
  ofile -> Close();
  return;

}

// end ========================================================================
