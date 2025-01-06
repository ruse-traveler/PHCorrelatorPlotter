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

  // --------------------------------------------------------------------------
  // open outputs & load inputs
  // --------------------------------------------------------------------------

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

  // --------------------------------------------------------------------------
  // compare sim vs. data distributions
  // --------------------------------------------------------------------------
  for (std::size_t ico = 0; ico < spe_hist.size(); ++ico) {
    for (std::size_t ipt = 0; ipt < pt_hist.size(); ++ipt) {
      for (std::size_t isp = 0; isp < spin_hist.size(); ++isp) {

        // only consider blue polarizations for pAu
        if (ico == IO::PAu) {
          if ((isp != IO::BU) || (isp != IO::BD) || (isp != IO::Int)) continue;
        }

        // make hist tag
        const std::string tag    = "DataVsSim" + spe_hist[ico] + "_";

        // make EEC comparison ------------------------------------------------
        {

          // make canvas name
          const std::string eec_canvas = IO::MakeCanvasName("cDataVsSimEEC", pt_hist[ipt], spin_hist[isp], "", spe_hist[ico]);

          // build hist names
          std::string eec_dat_hist = IO::MakeHistName("EEC", lvl_hist[IO::Data], pt_hist[ipt], spin_hist[isp]);
          std::string eec_rec_hist = IO::MakeHistName("EEC", lvl_hist[IO::Reco], pt_hist[ipt], spin_hist[isp]);
          std::string eec_tru_hist = IO::MakeHistName("EEC", lvl_hist[IO::True], pt_hist[ipt], spin_hist[isp]);

          // build hist renames
          std::string eec_dat_name = IO::MakeHistName("EEC", lvl_hist[IO::Data], pt_hist[ipt], spin_hist[isp], tag);
          std::string eec_rec_name = IO::MakeHistName("EEC", lvl_hist[IO::Reco], pt_hist[ipt], spin_hist[isp], tag);
          std::string eec_tru_name = IO::MakeHistName("EEC", lvl_hist[IO::True], pt_hist[ipt], spin_hist[isp], tag);

          // build hist legends
          std::string eec_dat_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::Data]);
          std::string eec_rec_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::Reco]);
          std::string eec_tru_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::True]);

          // bundle input options
          IO::Opts eec_dat_opt = IO::Opts(
            in_files[ico][IO::Data],
            eec_dat_hist,
            eec_dat_name,
            eec_dat_leg,
            899,
            24
          );
          IO::Opts eec_rec_opt = IO::Opts(
            in_files[ico][IO::Reco],
            eec_rec_hist,
            eec_rec_name,
            eec_rec_leg,
            859,
            25
          );
          IO::Opts eec_tru_opt = IO::Opts(
            in_files[ico][IO::True],
            eec_tru_hist,
            eec_tru_name,
            eec_tru_leg,
            923,
            29
          );

          // load into vector
          std::vector<IO::Opts> eec_num_opts;
          eec_num_opts.push_back( eec_dat_opt );
          eec_num_opts.push_back( eec_rec_opt );

          // make plot
          plotter.CompareSpectraToBaseline(
            SB::Denominator(eec_tru_opt),
            SB::Numerators(eec_num_opts),
            SB::PlotRange(SB::Side),
            SB::NormRange(SB::Side),
            SB::Canvas(eec_canvas, SB::Side),
            ofile
          );
        }  // end eec sim vs. reco plot

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
