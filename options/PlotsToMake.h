/// ===========================================================================
/*! \file   PlotsToMake.h
 *  \author Derek Anderson
 *  \date   01.08.2025
 *
 *  A namespace to define what plots
 *  to make specifically.
 */
/// ===========================================================================

#ifndef PLOTSTOMAKE_H
#define PLOTSTOMAKE_H

// c++ utilities
#include <string>
// plotting utilities
#include "../include/PHCorrelatorPlotting.h"
// plotting options
#include "CompareSpectra.h"
#include "CompareSpectra2D.h"
#include "InputOutput.h"
#include "SpectraVsBaseline.h"

// abbreviate common namespaces
namespace CS = CompareSpectra;
namespace C2 = CompareSpectra2D;
namespace SB = SpectraVsBaseline;



namespace PlotsToMake {

  // --------------------------------------------------------------------------
  //! Enumerate plots to make
  // --------------------------------------------------------------------------
  enum Plots {SimVsReco, VsPtJet};



  // --------------------------------------------------------------------------
  // Make 1D sim vs. reco plot
  // --------------------------------------------------------------------------
  void SimVsReco1D(
    const std::string& variable,
    const int species,
    const int pt,
    const int spin,
    const int opt,
    const InputOutput& io,
    const PHEC::PHCorrelatorPlotter& plotter,
    TFile* ofile
  ) {

    // colors for data, reco, and truth levels
    const std::size_t dat_col = 899;
    const std::size_t rec_col = 859;
    const std::size_t tru_col = 923;

    // markers for data, reco, and truth levels
    const std::size_t dat_mar = 24;
    const std::size_t rec_mar = 25;
    const std::size_t tru_mar = 29;

    // make canvas name and tag
    const std::string tag    = io.MakeSpeciesTag("DataVsSim", species) + "_";
    const std::string canvas = io.MakeCanvasName("cDataVsSim" + variable, pt, spin, -1, species);

    // build hist names
    const std::string dat_hist = io.MakeHistName(variable, InFiles::Data, pt, spin);
    const std::string rec_hist = io.MakeHistName(variable, InFiles::Reco, pt, spin);
    const std::string tru_hist = io.MakeHistName(variable, InFiles::True, pt, spin);

    // build hist renames
    const std::string dat_name = io.MakeHistName(variable, InFiles::Data, pt, spin, tag);
    const std::string rec_name = io.MakeHistName(variable, InFiles::Reco, pt, spin, tag);
    const std::string tru_name = io.MakeHistName(variable, InFiles::True, pt, spin, tag);

    // build hist legends
    const std::string dat_leg = io.MakeLegend(pt, spin, InFiles::Data);
    const std::string rec_leg = io.MakeLegend(pt, spin, InFiles::Reco);
    const std::string tru_leg = io.MakeLegend(pt, spin, InFiles::True);

    // bundle input options
    PHEC::PlotInput dat_opt = PHEC::PlotInput(
      io.Files().GetFile(species, InFiles::Data),
      dat_hist,
      dat_name,
      dat_leg,
      PHEC::Style::Plot(
        dat_col,
        dat_mar
      )
    );
    PHEC::PlotInput rec_opt = PHEC::PlotInput(
      io.Files().GetFile(species, InFiles::Reco),
      rec_hist,
      rec_name,
      rec_leg,
      PHEC::Style::Plot(
        rec_col,
        rec_mar
      )
    );
    PHEC::PlotInput tru_opt = PHEC::PlotInput(
      io.Files().GetFile(species, InFiles::True),
      tru_hist,
      tru_name,
      tru_leg,
      PHEC::Style::Plot(
        tru_col,
        tru_mar
      )
    );

    // load into vector
    std::vector<PHEC::PlotInput> num_input;
    num_input.push_back( dat_opt );
    num_input.push_back( rec_opt );

    // make plot
    plotter.CompareSpectraToBaseline(
      tru_opt,
      num_input,
      SB::PlotRange(opt),
      SB::NormRange(opt),
      SB::Canvas(canvas, opt),
      ofile
    );
    return;

  }  // end 'SimVsReco1D(...)'



  // --------------------------------------------------------------------------
  // Make 2D sim vs. reco plot
  // --------------------------------------------------------------------------
  void SimVsReco2D(
    const std::string& variable,
    const int species,
    const int pt,
    const int spin,
    const InputOutput& io,
    const PHEC::PHCorrelatorPlotter& plotter,
    TFile* ofile
  ) {

    // make canvas name and tag
    const std::string tag    = io.MakeSpeciesTag("DataVsSim", species) + "_";
    const std::string canvas = io.MakeCanvasName("cDataVsSim" + variable, pt, spin, -1, species);

    // build hist names
    const std::string dat_hist = io.MakeHistName(variable, InFiles::Data, pt, spin);
    const std::string rec_hist = io.MakeHistName(variable, InFiles::Reco, pt, spin);
    const std::string tru_hist = io.MakeHistName(variable, InFiles::True, pt, spin);

    // build hist renames
    const std::string dat_name = io.MakeHistName(variable, InFiles::Data, pt, spin, tag);
    const std::string rec_name = io.MakeHistName(variable, InFiles::Reco, pt, spin, tag);
    const std::string tru_name = io.MakeHistName(variable, InFiles::True, pt, spin, tag);

    // build hist legends
    const std::string dat_leg = io.MakeLegend(pt, spin, InFiles::Data);
    const std::string rec_leg = io.MakeLegend(pt, spin, InFiles::Reco);
    const std::string tru_leg = io.MakeLegend(pt, spin, InFiles::True);

    // bundle input options
    PHEC::PlotInput dat_opt = PHEC::PlotInput(
      io.Files().GetFile(species, InFiles::Data),
      dat_hist,
      dat_name,
      dat_leg
    );
    PHEC::PlotInput rec_opt = PHEC::PlotInput(
      io.Files().GetFile(species, InFiles::Reco),
      rec_hist,
      rec_name,
      rec_leg
    );
    PHEC::PlotInput tru_opt = PHEC::PlotInput(
      io.Files().GetFile(species, InFiles::True),
      tru_hist,
      tru_name,
      tru_leg
    );

    // load into vector
    std::vector<PHEC::PlotInput> input;
    input.push_back( dat_opt );
    input.push_back( rec_opt );
    input.push_back( tru_opt );

    // make plot
    plotter.CompareSpectra2D(
      input,
      C2::PlotRange(),
      C2::NormRange(),
      C2::Canvas(canvas, input),
      ofile
    );
    return;

  }  // end 'SimVsReco2D(...)'



  // --------------------------------------------------------------------------
  // Make 1D vs. jet pt comparison
  // --------------------------------------------------------------------------
  void VsPtJet1D(
    const std::string& variable,
    const int species,
    const int level,
    const int spin,
    const int opt,
    const InputOutput& io,
    const PHEC::PHCorrelatorPlotter& plotter,
    TFile* ofile
  ) {

    // colors for diferent jet pt
    const std::size_t pt5_col  = 799;
    const std::size_t pt10_col = 899;
    const std::size_t pt15_col = 879;

    // markers for different jet pt
    const std::size_t pt5_mar  = 26;
    const std::size_t pt10_mar = 24;
    const std::size_t pt15_mar = 32;

    // make canvas name and tag
    const std::string tag    = io.MakeSpeciesTag("VsPtJet", species) + "_";
    const std::string canvas = io.MakeCanvasName("cVsPtJet" + variable, -1, spin, level, species);

    // build hist names
    const std::string pt5_hist  = io.MakeHistName(variable, level, InHists::Pt5,  spin);
    const std::string pt10_hist = io.MakeHistName(variable, level, InHists::Pt10, spin);
    const std::string pt15_hist = io.MakeHistName(variable, level, InHists::Pt15, spin);

    // build hist renames
    const std::string pt5_name  = io.MakeHistName(variable, level, InHists::Pt5,  spin, tag);
    const std::string pt10_name = io.MakeHistName(variable, level, InHists::Pt10, spin, tag);
    const std::string pt15_name = io.MakeHistName(variable, level, InHists::Pt15, spin, tag);

    // build hist legends
    const std::string pt5_leg  = io.MakeLegend(InHists::Pt5,  spin, level);
    const std::string pt10_leg = io.MakeLegend(InHists::Pt10, spin, level);
    const std::string pt15_leg = io.MakeLegend(InHists::Pt15, spin, level);

    // bundle input options
    PHEC::PlotInput pt5_opt = PHEC::PlotInput(
      io.Files().GetFile(species, level),
      pt5_hist,
      pt5_name,
      pt5_leg,
      PHEC::Style::Plot(
        pt5_col,
        pt5_mar
      )
    );
    PHEC::PlotInput pt10_opt = PHEC::PlotInput(
      io.Files().GetFile(species, level),
      pt10_hist,
      pt10_name,
      pt10_leg,
      PHEC::Style::Plot(
        pt10_col,
        pt10_mar
      )
    );
    PHEC::PlotInput pt15_opt = PHEC::PlotInput(
      io.Files().GetFile(species, level),
      pt15_hist,
      pt15_name,
      pt15_leg,
      PHEC::Style::Plot(
        pt15_col,
        pt15_mar
      )
    );

    // load into vector
    std::vector<PHEC::PlotInput> input;
    input.push_back( pt5_opt );
    input.push_back( pt10_opt );
    input.push_back( pt15_opt );

    // make plot
    plotter.CompareSpectra(
      input,
      CS::PlotRange(opt),
      CS::NormRange(opt),
      CS::Canvas(canvas, opt),
      ofile
    );
    return;

  }  // end 'VsPtJet1D(...)'



  // --------------------------------------------------------------------------
  // Make 2D vs. jet pt comparison
  // --------------------------------------------------------------------------
  void VsPtJet2D(
    const std::string& variable,
    const int species,
    const int level,
    const int spin,
    const InputOutput& io,
    const PHEC::PHCorrelatorPlotter& plotter,
    TFile* ofile
  ) {

    // make canvas name and tag
    const std::string tag    = io.MakeSpeciesTag("VsPtJet", species) + "_";
    const std::string canvas = io.MakeCanvasName("cVsPtJet" + variable, -1, spin, level, species);

    // build hist names
    const std::string pt5_hist  = io.MakeHistName(variable, level, InHists::Pt5,  spin);
    const std::string pt10_hist = io.MakeHistName(variable, level, InHists::Pt10, spin);
    const std::string pt15_hist = io.MakeHistName(variable, level, InHists::Pt15, spin);

    // build hist renames
    const std::string pt5_name  = io.MakeHistName(variable, level, InHists::Pt5,  spin, tag);
    const std::string pt10_name = io.MakeHistName(variable, level, InHists::Pt10, spin, tag);
    const std::string pt15_name = io.MakeHistName(variable, level, InHists::Pt15, spin, tag);

    // build hist legends
    const std::string pt5_leg  = io.MakeLegend(InHists::Pt5,  spin, level);
    const std::string pt10_leg = io.MakeLegend(InHists::Pt10, spin, level);
    const std::string pt15_leg = io.MakeLegend(InHists::Pt15, spin, level);

    // bundle input options
    PHEC::PlotInput pt5_opt = PHEC::PlotInput(
      io.Files().GetFile(species, level),
      pt5_hist,
      pt5_name,
      pt5_leg
    );
    PHEC::PlotInput pt10_opt = PHEC::PlotInput(
      io.Files().GetFile(species, level),
      pt10_hist,
      pt10_name,
      pt10_leg
    );
    PHEC::PlotInput pt15_opt = PHEC::PlotInput(
      io.Files().GetFile(species, level),
      pt15_hist,
      pt15_name,
      pt15_leg
    );

    // load into vector
    std::vector<PHEC::PlotInput> input;
    input.push_back( pt5_opt );
    input.push_back( pt10_opt );
    input.push_back( pt15_opt );

    // make plot
    plotter.CompareSpectra2D(
      input,
      C2::PlotRange(),
      C2::NormRange(),
      C2::Canvas(canvas, input),
      ofile
    );
    return;

  }  // end 'VsPtJet2D(...)'

}  // end PlotsToMake namespace

#endif

// end ========================================================================
