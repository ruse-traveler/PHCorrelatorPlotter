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
  TFile* simdata_eec_ofile  = PHEC::Tools::OpenFile("simVsRecoEEC.ppRun15.d5m1y2025.root", "recreate");
  TFile* simdata_coll_ofile = PHEC::Tools::OpenFile("simVsRecoCollins.ppRun15.d5m1y2025.root", "recreate");
  TFile* simdata_havg_ofile = PHEC::Tools::OpenFile("simVsRecoHadAvg.ppRun15.d5m1y2025.root", "recreate");
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
          const bool isOnlyBlue = ((isp == IO::BU) || (isp == IO::BD) || (isp == IO::Int));
          if (!isOnlyBlue) continue;
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
            simdata_eec_ofile
          );
        }  // end eec sim vs. reco plot

        // make collins angle (blue) comparison -------------------------------
        {

          // make canvas name
          const std::string collb_canvas = IO::MakeCanvasName("cDataVsSimCollinsB", pt_hist[ipt], spin_hist[isp], "", spe_hist[ico]);

          // build hist names
          std::string collb_dat_hist = IO::MakeHistName("SpinCollinsBlue", lvl_hist[IO::Data], pt_hist[ipt], spin_hist[isp]);
          std::string collb_rec_hist = IO::MakeHistName("SpinCollinsBlue", lvl_hist[IO::Reco], pt_hist[ipt], spin_hist[isp]);
          std::string collb_tru_hist = IO::MakeHistName("SpinCollinsBlue", lvl_hist[IO::True], pt_hist[ipt], spin_hist[isp]);

          // build hist renames
          std::string collb_dat_name = IO::MakeHistName("SpinCollinsBlue", lvl_hist[IO::Data], pt_hist[ipt], spin_hist[isp], tag);
          std::string collb_rec_name = IO::MakeHistName("SpinCollinsBlue", lvl_hist[IO::Reco], pt_hist[ipt], spin_hist[isp], tag);
          std::string collb_tru_name = IO::MakeHistName("SpinCollinsBlue", lvl_hist[IO::True], pt_hist[ipt], spin_hist[isp], tag);

          // build hist legends
          std::string collb_dat_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::Data]);
          std::string collb_rec_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::Reco]);
          std::string collb_tru_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::True]);

          // bundle input options
          IO::Opts collb_dat_opt = IO::Opts(
            in_files[ico][IO::Data],
            collb_dat_hist,
            collb_dat_name,
            collb_dat_leg,
            899,
            24
          );
          IO::Opts collb_rec_opt = IO::Opts(
            in_files[ico][IO::Reco],
            collb_rec_hist,
            collb_rec_name,
            collb_rec_leg,
            859,
            25
          );
          IO::Opts collb_tru_opt = IO::Opts(
            in_files[ico][IO::True],
            collb_tru_hist,
            collb_tru_name,
            collb_tru_leg,
            923,
            29
          );

          // load into vector
          std::vector<IO::Opts> collb_num_opts;
          collb_num_opts.push_back( collb_dat_opt );
          collb_num_opts.push_back( collb_rec_opt );

          // make plot
          plotter.CompareSpectraToBaseline(
            SB::Denominator(collb_tru_opt),
            SB::Numerators(collb_num_opts),
            SB::PlotRange(SB::Angle),
            SB::NormRange(SB::Angle),
            SB::Canvas(collb_canvas, SB::Angle),
            simdata_coll_ofile
          );
        }  // end collb sim vs. reco plot

        // make collins angle (yellow) comparison -----------------------------
        if (ico != IO::PAu) {

          // make canvas name
          const std::string colly_canvas = IO::MakeCanvasName("cDataVsSimCollinsY", pt_hist[ipt], spin_hist[isp], "", spe_hist[ico]);

          // build hist names
          std::string colly_dat_hist = IO::MakeHistName("SpinCollinsYell", lvl_hist[IO::Data], pt_hist[ipt], spin_hist[isp]);
          std::string colly_rec_hist = IO::MakeHistName("SpinCollinsYell", lvl_hist[IO::Reco], pt_hist[ipt], spin_hist[isp]);
          std::string colly_tru_hist = IO::MakeHistName("SpinCollinsYell", lvl_hist[IO::True], pt_hist[ipt], spin_hist[isp]);

          // build hist renames
          std::string colly_dat_name = IO::MakeHistName("SpinCollinsYell", lvl_hist[IO::Data], pt_hist[ipt], spin_hist[isp], tag);
          std::string colly_rec_name = IO::MakeHistName("SpinCollinsYell", lvl_hist[IO::Reco], pt_hist[ipt], spin_hist[isp], tag);
          std::string colly_tru_name = IO::MakeHistName("SpinCollinsYell", lvl_hist[IO::True], pt_hist[ipt], spin_hist[isp], tag);

          // build hist legends
          std::string colly_dat_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::Data]);
          std::string colly_rec_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::Reco]);
          std::string colly_tru_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::True]);

          // bundle input options
          IO::Opts colly_dat_opt = IO::Opts(
            in_files[ico][IO::Data],
            colly_dat_hist,
            colly_dat_name,
            colly_dat_leg,
            899,
            24
          );
          IO::Opts colly_rec_opt = IO::Opts(
            in_files[ico][IO::Reco],
            colly_rec_hist,
            colly_rec_name,
            colly_rec_leg,
            859,
            25
          );
          IO::Opts colly_tru_opt = IO::Opts(
            in_files[ico][IO::True],
            colly_tru_hist,
            colly_tru_name,
            colly_tru_leg,
            923,
            29
          );

          // load into vector
          std::vector<IO::Opts> colly_num_opts;
          colly_num_opts.push_back( colly_dat_opt );
          colly_num_opts.push_back( colly_rec_opt );

          // make plot
          plotter.CompareSpectraToBaseline(
            SB::Denominator(colly_tru_opt),
            SB::Numerators(colly_num_opts),
            SB::PlotRange(SB::Angle),
            SB::NormRange(SB::Angle),
            SB::Canvas(colly_canvas, SB::Angle),
            simdata_coll_ofile
          );
        }  // end colly sim vs. reco plot

        // make hadron-average angle (blue) comparison ------------------------
        {

          // make canvas name
          const std::string havgb_canvas = IO::MakeCanvasName("cDataVsSimHadAvgB", pt_hist[ipt], spin_hist[isp], "", spe_hist[ico]);

          // build hist names
          std::string havgb_dat_hist = IO::MakeHistName("SpinHadAvgBlue", lvl_hist[IO::Data], pt_hist[ipt], spin_hist[isp]);
          std::string havgb_rec_hist = IO::MakeHistName("SpinHadAvgBlue", lvl_hist[IO::Reco], pt_hist[ipt], spin_hist[isp]);
          std::string havgb_tru_hist = IO::MakeHistName("SpinHadAvgBlue", lvl_hist[IO::True], pt_hist[ipt], spin_hist[isp]);

          // build hist renames
          std::string havgb_dat_name = IO::MakeHistName("SpinHadAvgBlue", lvl_hist[IO::Data], pt_hist[ipt], spin_hist[isp], tag);
          std::string havgb_rec_name = IO::MakeHistName("SpinHadAvgBlue", lvl_hist[IO::Reco], pt_hist[ipt], spin_hist[isp], tag);
          std::string havgb_tru_name = IO::MakeHistName("SpinHadAvgBlue", lvl_hist[IO::True], pt_hist[ipt], spin_hist[isp], tag);

          // build hist legends
          std::string havgb_dat_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::Data]);
          std::string havgb_rec_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::Reco]);
          std::string havgb_tru_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::True]);

          // bundle input options
          IO::Opts havgb_dat_opt = IO::Opts(
            in_files[ico][IO::Data],
            havgb_dat_hist,
            havgb_dat_name,
            havgb_dat_leg,
            899,
            24
          );
          IO::Opts havgb_rec_opt = IO::Opts(
            in_files[ico][IO::Reco],
            havgb_rec_hist,
            havgb_rec_name,
            havgb_rec_leg,
            859,
            25
          );
          IO::Opts havgb_tru_opt = IO::Opts(
            in_files[ico][IO::True],
            havgb_tru_hist,
            havgb_tru_name,
            havgb_tru_leg,
            923,
            29
          );

          // load into vector
          std::vector<IO::Opts> havgb_num_opts;
          havgb_num_opts.push_back( havgb_dat_opt );
          havgb_num_opts.push_back( havgb_rec_opt );

          // make plot
          plotter.CompareSpectraToBaseline(
            SB::Denominator(havgb_tru_opt),
            SB::Numerators(havgb_num_opts),
            SB::PlotRange(SB::Angle),
            SB::NormRange(SB::Angle),
            SB::Canvas(havgb_canvas, SB::Angle),
            simdata_havg_ofile
          );
        }  // end havgb sim vs. reco plot

        // make collins angle (yellow) comparison -----------------------------
        if (ico != IO::PAu) {

          // make canvas name
          const std::string havgy_canvas = IO::MakeCanvasName("cDataVsSimHadAvgY", pt_hist[ipt], spin_hist[isp], "", spe_hist[ico]);

          // build hist names
          std::string havgy_dat_hist = IO::MakeHistName("SpinHadAvgYell", lvl_hist[IO::Data], pt_hist[ipt], spin_hist[isp]);
          std::string havgy_rec_hist = IO::MakeHistName("SpinHadAvgYell", lvl_hist[IO::Reco], pt_hist[ipt], spin_hist[isp]);
          std::string havgy_tru_hist = IO::MakeHistName("SpinHadAvgYell", lvl_hist[IO::True], pt_hist[ipt], spin_hist[isp]);

          // build hist renames
          std::string havgy_dat_name = IO::MakeHistName("SpinHadAvgYell", lvl_hist[IO::Data], pt_hist[ipt], spin_hist[isp], tag);
          std::string havgy_rec_name = IO::MakeHistName("SpinHadAvgYell", lvl_hist[IO::Reco], pt_hist[ipt], spin_hist[isp], tag);
          std::string havgy_tru_name = IO::MakeHistName("SpinHadAvgYell", lvl_hist[IO::True], pt_hist[ipt], spin_hist[isp], tag);

          // build hist legends
          std::string havgy_dat_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::Data]);
          std::string havgy_rec_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::Reco]);
          std::string havgy_tru_leg = IO::MakeLegend(pt_legs[ipt], spin_legs[isp], lvl_legs[IO::True]);

          // bundle input options
          IO::Opts havgy_dat_opt = IO::Opts(
            in_files[ico][IO::Data],
            havgy_dat_hist,
            havgy_dat_name,
            havgy_dat_leg,
            899,
            24
          );
          IO::Opts havgy_rec_opt = IO::Opts(
            in_files[ico][IO::Reco],
            havgy_rec_hist,
            havgy_rec_name,
            havgy_rec_leg,
            859,
            25
          );
          IO::Opts havgy_tru_opt = IO::Opts(
            in_files[ico][IO::True],
            havgy_tru_hist,
            havgy_tru_name,
            havgy_tru_leg,
            923,
            29
          );

          // load into vector
          std::vector<IO::Opts> havgy_num_opts;
          havgy_num_opts.push_back( havgy_dat_opt );
          havgy_num_opts.push_back( havgy_rec_opt );

          // make plot
          plotter.CompareSpectraToBaseline(
            SB::Denominator(havgy_tru_opt),
            SB::Numerators(havgy_num_opts),
            SB::PlotRange(SB::Angle),
            SB::NormRange(SB::Angle),
            SB::Canvas(havgy_canvas, SB::Angle),
            simdata_havg_ofile
          );
        }  // end colly sim vs. reco plot

        /* TODO add 2d comparisons here */

      }  // end spin loop
    }  // end pt jet loop
  }  // end species loop

  /* TODO add EEC vs. pt comparison here */
  /* TODO add EEC pp vs. pau comparison here */

  std::cout << "    Completed sim vs. reco plots." << std::endl;

  // close files & exit -------------------------------------------------------

  // close output file
  simdata_eec_ofile -> cd();
  simdata_eec_ofile -> Close();
  return;

}

// end ========================================================================
