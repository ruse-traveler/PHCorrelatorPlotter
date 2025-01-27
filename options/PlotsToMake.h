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
#include <utility>
// plotting utilities
#include "../include/PHCorrelatorPlotting.h"
// plotting options
#include "CompareRatios.h"
#include "CompareSpectra.h"
#include "CompareSpectra2D.h"
#include "InputOutput.h"
#include "SpectraVsBaseline.h"

// abbreviate common namespaces
namespace CR = CompareRatios;
namespace CS = CompareSpectra;
namespace C2 = CompareSpectra2D;
namespace SB = SpectraVsBaseline;

// useful types
typedef std::pair<std::size_t, std::size_t> StylePair;
typedef std::pair<std::string, std::string> StringPair;
typedef std::pair<PHEC::PlotInput, PHEC::PlotInput> InputPair;



namespace PlotsToMake {

  // --------------------------------------------------------------------------
  //! Enumerate plots to make
  // --------------------------------------------------------------------------
  enum Plots {SimVsReco, VsPtJet, PPVsPAu, QuickRatios};



  // --------------------------------------------------------------------------
  // Make 1D sim vs. reco plot
  // --------------------------------------------------------------------------
  void SimVsReco1D(
    const std::string& variable,
    const int species,
    const int pt,
    const int ch,
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
    const std::string canvas = io.MakeCanvasName("cDataVsSim" + variable, pt, ch, spin, -1, species);

    // build hist names
    const std::string dat_hist = io.MakeHistName(variable, InFiles::Data, pt, ch, spin);
    const std::string rec_hist = io.MakeHistName(variable, InFiles::Reco, pt, ch, spin);
    const std::string tru_hist = io.MakeHistName(variable, InFiles::True, pt, ch, spin);

    // build hist renames
    const std::string dat_name = io.MakeHistName(variable, InFiles::Data, pt, ch, spin, tag);
    const std::string rec_name = io.MakeHistName(variable, InFiles::Reco, pt, ch, spin, tag);
    const std::string tru_name = io.MakeHistName(variable, InFiles::True, pt, ch, spin, tag);

    // build hist legends
    const std::string dat_leg = io.MakeLegend(pt, ch, spin, InFiles::Data);
    const std::string rec_leg = io.MakeLegend(pt, ch, spin, InFiles::Reco);
    const std::string tru_leg = io.MakeLegend(pt, ch, spin, InFiles::True);

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
      SB::Options(canvas, opt),
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
    const int ch,
    const int spin,
    const InputOutput& io,
    const PHEC::PHCorrelatorPlotter& plotter,
    TFile* ofile
  ) {

    // make canvas name and tag
    const std::string tag    = io.MakeSpeciesTag("DataVsSim", species) + "_";
    const std::string canvas = io.MakeCanvasName("cDataVsSim" + variable, pt, ch, spin, -1, species);

    // build hist names
    const std::string dat_hist = io.MakeHistName(variable, InFiles::Data, pt, ch, spin);
    const std::string rec_hist = io.MakeHistName(variable, InFiles::Reco, pt, ch, spin);
    const std::string tru_hist = io.MakeHistName(variable, InFiles::True, pt, ch, spin);

    // build hist renames
    const std::string dat_name = io.MakeHistName(variable, InFiles::Data, pt, ch, spin, tag);
    const std::string rec_name = io.MakeHistName(variable, InFiles::Reco, pt, ch, spin, tag);
    const std::string tru_name = io.MakeHistName(variable, InFiles::True, pt, ch, spin, tag);

    // build hist legends
    const std::string dat_leg = io.MakeLegend(pt, ch, spin, InFiles::Data);
    const std::string rec_leg = io.MakeLegend(pt, ch, spin, InFiles::Reco);
    const std::string tru_leg = io.MakeLegend(pt, ch, spin, InFiles::True);

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
      C2::Options(canvas, input),
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
    const int ch,
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
    const std::string canvas = io.MakeCanvasName("cVsPtJet" + variable, -1, ch, spin, level, species);

    // build hist names
    const std::string pt5_hist  = io.MakeHistName(variable, level, InHists::Pt5,  ch, spin);
    const std::string pt10_hist = io.MakeHistName(variable, level, InHists::Pt10, ch, spin);
    const std::string pt15_hist = io.MakeHistName(variable, level, InHists::Pt15, ch, spin);

    // build hist renames
    const std::string pt5_name  = io.MakeHistName(variable, level, InHists::Pt5,  ch, spin, tag);
    const std::string pt10_name = io.MakeHistName(variable, level, InHists::Pt10, ch, spin, tag);
    const std::string pt15_name = io.MakeHistName(variable, level, InHists::Pt15, ch, spin, tag);

    // build hist legends
    const std::string pt5_leg  = io.MakeLegend(InHists::Pt5,  ch, spin, level);
    const std::string pt10_leg = io.MakeLegend(InHists::Pt10, ch, spin, level);
    const std::string pt15_leg = io.MakeLegend(InHists::Pt15, ch, spin, level);

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
      CS::Options(canvas, opt),
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
    const int ch,
    const int spin,
    const InputOutput& io,
    const PHEC::PHCorrelatorPlotter& plotter,
    TFile* ofile
  ) {

    // make canvas name and tag
    const std::string tag    = io.MakeSpeciesTag("VsPtJet", species) + "_";
    const std::string canvas = io.MakeCanvasName("cVsPtJet" + variable, -1, ch, spin, level, species);

    // build hist names
    const std::string pt5_hist  = io.MakeHistName(variable, level, InHists::Pt5,  ch, spin);
    const std::string pt10_hist = io.MakeHistName(variable, level, InHists::Pt10, ch, spin);
    const std::string pt15_hist = io.MakeHistName(variable, level, InHists::Pt15, ch, spin);

    // build hist renames
    const std::string pt5_name  = io.MakeHistName(variable, level, InHists::Pt5,  ch, spin, tag);
    const std::string pt10_name = io.MakeHistName(variable, level, InHists::Pt10, ch, spin, tag);
    const std::string pt15_name = io.MakeHistName(variable, level, InHists::Pt15, ch, spin, tag);

    // build hist legends
    const std::string pt5_leg  = io.MakeLegend(InHists::Pt5,  ch, spin, level);
    const std::string pt10_leg = io.MakeLegend(InHists::Pt10, ch, spin, level);
    const std::string pt15_leg = io.MakeLegend(InHists::Pt15, ch, spin, level);

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
      C2::Options(canvas, input),
      ofile
    );
    return;

  }  // end 'VsPtJet2D(...)'



  // --------------------------------------------------------------------------
  // Make 1D pp vs. pau plot
  // --------------------------------------------------------------------------
  void PPVsPAu1D(
    const std::string& variable,
    const int level,
    const int ch,
    const int spin,
    const int opt,
    const InputOutput& io,
    const PHEC::PHCorrelatorPlotter& plotter,
    TFile* ofile
  ) {

    // colors for diferent jet pt
    const StylePair pt5_col  = std::make_pair(809, 799);
    const StylePair pt10_col = std::make_pair(899, 909);
    const StylePair pt15_col = std::make_pair(889, 879);

    // markers for different jet pt
    const StylePair pt5_mar  = std::make_pair(22, 26);
    const StylePair pt10_mar = std::make_pair(20, 24);
    const StylePair pt15_mar = std::make_pair(23, 32);

    // make canvas name and tag
    const std::string tag    = "PPVsPAu_";
    const std::string canvas = io.MakeCanvasName("cPPVsPAu" + variable, -1, ch, spin, level);

    // build hist names
    const std::string pt5_hist  = io.MakeHistName(variable, level, InHists::Pt5,  ch, spin);
    const std::string pt10_hist = io.MakeHistName(variable, level, InHists::Pt10, ch, spin);
    const std::string pt15_hist = io.MakeHistName(variable, level, InHists::Pt15, ch, spin);

    // build hist renames
    const StringPair pt5_name  = std::make_pair(
      io.MakeHistName(variable, level, InHists::Pt5, ch, spin, tag + "PP_"),
      io.MakeHistName(variable, level, InHists::Pt5, ch, spin, tag + "PAu)")
    );
    const StringPair pt10_name = std::make_pair(
      io.MakeHistName(variable, level, InHists::Pt10, ch, spin, tag + "PP_"),
      io.MakeHistName(variable, level, InHists::Pt10, ch, spin, tag + "PAu_")
    );
    const StringPair pt15_name = std::make_pair(
      io.MakeHistName(variable, level, InHists::Pt15, ch, spin, tag + "PP_"),
      io.MakeHistName(variable, level, InHists::Pt15, ch, spin, tag + "PAu_")
    );

    // build hist legends
    const StringPair pt5_leg  = std::make_pair(
      io.MakeLegend(InHists::Pt5, ch, spin, level, InFiles::PP),
      io.MakeLegend(InHists::Pt5, ch, spin, level, InFiles::PAu)
    );
    const StringPair pt10_leg = std::make_pair(
      io.MakeLegend(InHists::Pt10, ch, spin, level, InFiles::PP),
      io.MakeLegend(InHists::Pt10, ch, spin, level, InFiles::PAu)
    );
    const StringPair pt15_leg = std::make_pair(
      io.MakeLegend(InHists::Pt15, ch, spin, level, InFiles::PP),
      io.MakeLegend(InHists::Pt15, ch, spin, level, InFiles::PAu)
    );

    // bundle input options
    InputPair pt5_opt = std::make_pair(
      PHEC::PlotInput(
        io.Files().GetFile(InFiles::PP, level),
        pt5_hist,
        pt5_name.first,
        pt5_leg.first,
        PHEC::Style::Plot(
          pt5_col.first,
          pt5_mar.first
        )
      ),
      PHEC::PlotInput(
        io.Files().GetFile(InFiles::PAu, level),
        pt5_hist,
        pt5_name.second,
        pt5_leg.second,
        PHEC::Style::Plot(
          pt5_col.second,
          pt5_mar.second
        )
      )
    );
    InputPair pt10_opt = std::make_pair(
      PHEC::PlotInput(
        io.Files().GetFile(InFiles::PP, level),
        pt10_hist,
        pt10_name.first,
        pt10_leg.first,
        PHEC::Style::Plot(
          pt10_col.first,
          pt10_mar.first
        )
      ),
      PHEC::PlotInput(
        io.Files().GetFile(InFiles::PAu, level),
        pt10_hist,
        pt10_name.second,
        pt10_leg.second,
        PHEC::Style::Plot(
          pt10_col.second,
          pt10_mar.second
        )
      )
    );
    InputPair pt15_opt = std::make_pair(
      PHEC::PlotInput(
        io.Files().GetFile(InFiles::PP, level),
        pt15_hist,
        pt15_name.first,
        pt15_leg.first,
        PHEC::Style::Plot(
          pt15_col.first,
          pt15_mar.first
        )
      ),
      PHEC::PlotInput(
        io.Files().GetFile(InFiles::PAu, level),
        pt15_hist,
        pt15_name.second,
        pt15_leg.second,
        PHEC::Style::Plot(
          pt15_col.second,
          pt15_mar.second
        )
      )
    );

    // load denominators
    std::vector<PHEC::PlotInput> denominator;
    denominator.push_back( pt5_opt.first );
    denominator.push_back( pt10_opt.first );
    denominator.push_back( pt15_opt.first );

    // load numerators
    std::vector<PHEC::PlotInput> numerator;
    numerator.push_back( pt5_opt.second );
    numerator.push_back( pt10_opt.second );
    numerator.push_back( pt15_opt.second );

    // make plot
    plotter.CompareRatios(
      denominator,
      numerator,
      CR::Options(canvas, opt),
      ofile
    );
    return;

  }  // end 'PPVsPAu1D(...)'

}  // end PlotsToMake namespace

#endif

// end ========================================================================
