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
#include "InputOutput.h"
#include "PlotOptions.h"

// abbreviate common namespaces
namespace PO = PlotOptions;

// ----------------------------------------------------------------------------
// useful types
// ----------------------------------------------------------------------------
typedef std::pair<std::size_t, std::size_t> StylePair;
typedef std::pair<std::string, std::string> StringPair;
typedef std::pair<PHEC::PlotInput, PHEC::PlotInput> InputPair;



namespace PlotsToMake {

  // --------------------------------------------------------------------------
  //! Enumerate plots to make
  // --------------------------------------------------------------------------
  enum Plots {SimVsReco, VsPtJet, PPVsPAu, CorrectSpectra, QuickRatios};



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
    plotter.PlotSpectra1D(
      PO::SpectraVsBaseline(tru_opt, num_input, canvas, opt),
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
    plotter.PlotSpectra2D(
      PO::CompareSpectra2D(input, canvas),
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
    plotter.PlotSpectra1D(
      PO::CompareSpectra1D(input, canvas, opt),
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
    plotter.PlotSpectra2D(
      PO::CompareSpectra2D(input, canvas),
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
    plotter.PlotSpectra1D(
      PO::CompareRatios(denominator, numerator, canvas, opt),
      ofile
    );
    return;

  }  // end 'PPVsPAu1D(...)'



  // --------------------------------------------------------------------------
  //! Make 1D corrected spectrum plot
  // --------------------------------------------------------------------------
  void CorrectSpectra1D(
    const std::string& variable,
    const int species,
    const int ch,
    const int spin,
    const int opt,
    const InputOutput& io,
    const PHEC::PHCorrelatorPlotter& plotter,
    TFile* ofile
  ) {

    // colors for diferent jet pt
    const std::size_t pt5_col[3]  = {809, 799, 797};
    const std::size_t pt10_col[3] = {899, 909, 907};
    const std::size_t pt15_col[3] = {889, 879, 877};

    // markers for different jet pt
    const std::size_t pt5_mar[3]  = {22, 22, 26};
    const std::size_t pt10_mar[3] = {20, 24, 24};
    const std::size_t pt15_mar[3] = {23, 23, 32};

    // make canvas name and tag
    const std::string tag    = io.MakeSpeciesTag("Correct", species) + "_";
    const std::string canvas = io.MakeCanvasName("cCorrect" + variable, -1, ch, spin, -1);

    // build data hist names
    const std::string pt5_dhist  = io.MakeHistName(variable, InFiles::Data, InHists::Pt5,  ch, spin);
    const std::string pt10_dhist = io.MakeHistName(variable, InFiles::Data, InHists::Pt10, ch, spin);
    const std::string pt15_dhist = io.MakeHistName(variable, InFiles::Data, InHists::Pt15, ch, spin);

    // build reco hist names
    const std::string pt5_rhist  = io.MakeHistName(variable, InFiles::Reco, InHists::Pt5,  ch, spin);
    const std::string pt10_rhist = io.MakeHistName(variable, InFiles::Reco, InHists::Pt10, ch, spin);
    const std::string pt15_rhist = io.MakeHistName(variable, InFiles::Reco, InHists::Pt15, ch, spin);

    // build true hist names
    const std::string pt5_thist  = io.MakeHistName(variable, InFiles::True, InHists::Pt5,  ch, spin);
    const std::string pt10_thist = io.MakeHistName(variable, InFiles::True, InHists::Pt10, ch, spin);
    const std::string pt15_thist = io.MakeHistName(variable, InFiles::True, InHists::Pt15, ch, spin);

    // build hist renames
    const std::string pt5_name[3] = {
      io.MakeHistName(variable, InFiles::Data, InHists::Pt5, ch, spin, tag + "Data_"),
      io.MakeHistName(variable, InFiles::Reco, InHists::Pt5, ch, spin, tag + "Reco_"),
      io.MakeHistName(variable, InFiles::True, InHists::Pt5, ch, spin, tag + "True_")
    };
    const std::string pt10_name[3] = {
      io.MakeHistName(variable, InFiles::Data, InHists::Pt10, ch, spin, tag + "Data_"),
      io.MakeHistName(variable, InFiles::Reco, InHists::Pt10, ch, spin, tag + "Reco_"),
      io.MakeHistName(variable, InFiles::True, InHists::Pt10, ch, spin, tag + "True_")
    };
    const std::string pt15_name[3] = {
      io.MakeHistName(variable, InFiles::Data, InHists::Pt15, ch, spin, tag + "Data_"),
      io.MakeHistName(variable, InFiles::Reco, InHists::Pt15, ch, spin, tag + "Reco_"),
      io.MakeHistName(variable, InFiles::True, InHists::Pt15, ch, spin, tag + "True_")
    };

    // build hist legends
    const std::string pt5_leg[3] = {
      io.MakeLegend(InHists::Pt5, ch, spin, InFiles::Data, species),
      io.MakeLegend(InHists::Pt5, ch, spin, InFiles::Reco, species),
      io.MakeLegend(InHists::Pt5, ch, spin, InFiles::True, species)
    };
    const std::string pt10_leg[3] = {
      io.MakeLegend(InHists::Pt10, ch, spin, InFiles::Data, species),
      io.MakeLegend(InHists::Pt10, ch, spin, InFiles::Reco, species),
      io.MakeLegend(InHists::Pt10, ch, spin, InFiles::True, species)
    };
    const std::string pt15_leg[3] = {
      io.MakeLegend(InHists::Pt15, ch, spin, InFiles::Data, species),
      io.MakeLegend(InHists::Pt15, ch, spin, InFiles::Reco, species),
      io.MakeLegend(InHists::Pt15, ch, spin, InFiles::True, species)
    };

    // bundle input data options
    PHEC::Inputs data_opt;
    data_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(species, InFiles::Data),
        pt5_dhist,
        pt5_name[0],
        pt5_leg[0],
        PHEC::Style::Plot(
          pt5_col[0],
          pt5_mar[0]
        )
      )
    );
    data_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(species, InFiles::Data),
        pt10_dhist,
        pt10_name[0],
        pt10_leg[0],
        PHEC::Style::Plot(
          pt10_col[0],
          pt10_mar[0]
        )
      )
    );
    data_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(species, InFiles::Data),
        pt15_dhist,
        pt15_name[0],
        pt15_leg[0],
        PHEC::Style::Plot(
          pt15_col[0],
          pt15_mar[0]
        )
      )
    );

    // bundle input reco options
    PHEC::Inputs reco_opt;
    reco_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(species, InFiles::Reco),
        pt5_rhist,
        pt5_name[1],
        pt5_leg[1],
        PHEC::Style::Plot(
          pt5_col[1],
          pt5_mar[1]
        )
      )
    );
    reco_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(species, InFiles::Reco),
        pt10_rhist,
        pt10_name[1],
        pt10_leg[1],
        PHEC::Style::Plot(
          pt10_col[1],
          pt10_mar[1]
        )
      )
    );
    reco_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(species, InFiles::Reco),
        pt15_rhist,
        pt15_name[1],
        pt15_leg[1],
        PHEC::Style::Plot(
          pt15_col[1],
          pt15_mar[1]
        )
      )
    );

    // bundle input true options
    PHEC::Inputs true_opt;
    true_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(species, InFiles::True),
        pt5_thist,
        pt5_name[2],
        pt5_leg[2],
        PHEC::Style::Plot(
          pt5_col[2],
          pt5_mar[2]
        )
      )
    );
    true_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(species, InFiles::True),
        pt10_thist,
        pt10_name[2],
        pt10_leg[2],
        PHEC::Style::Plot(
          pt10_col[2],
          pt10_mar[2]
        )
      )
    );
    true_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(species, InFiles::True),
        pt15_thist,
        pt15_name[2],
        pt15_leg[2],
        PHEC::Style::Plot(
          pt15_col[2],
          pt15_mar[2]
        )
      )
    );

    // make plot
    plotter.PlotSpectra1D(
      PO::CorrectSpectra1D(data_opt, reco_opt, true_opt, canvas, opt),
      ofile
    );
    return;

  }  // end 'CorrectSpectra1D(...)'

}  // end PlotsToMake namespace

#endif

// end ========================================================================
