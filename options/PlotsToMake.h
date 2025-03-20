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
#include "../include/PHCorrelatorPlotter.h"
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
    const int opt,
    const PHEC::Type::PlotIndex& index,
    const InputOutput& io,
    const PHEC::PHCorrelatorPlotMaker& maker,
    TFile* ofile
  ) {

    // constrain level indices
    PHEC::Type::PlotIndex iData = index;
    PHEC::Type::PlotIndex iReco = index;
    PHEC::Type::PlotIndex iTrue = index;
    iData.level = InFiles::Data;
    iReco.level = InFiles::Reco;
    iTrue.level = InFiles::True;

    // colors for data, reco, and truth levels
    const std::size_t dat_col = 899;
    const std::size_t rec_col = 859;
    const std::size_t tru_col = 923;

    // markers for data, reco, and truth levels
    const std::size_t dat_mar = 24;
    const std::size_t rec_mar = 25;
    const std::size_t tru_mar = 29;

    // make canvas name and tag
    const std::string tag    = io.MakeSpeciesTag("DataVsSim", index.species) + "_";
    const std::string canvas = io.MakeCanvasName("cDataVsSim" + variable, index);

    // build hist names
    const std::string dat_hist = io.MakeHistName(variable, iData);
    const std::string rec_hist = io.MakeHistName(variable, iReco);
    const std::string tru_hist = io.MakeHistName(variable, iTrue);

    // build hist renames
    const std::string dat_name = io.MakeHistName(variable, iData, tag);
    const std::string rec_name = io.MakeHistName(variable, iReco, tag);
    const std::string tru_name = io.MakeHistName(variable, iTrue, tag);

    // build hist legends
    const std::string dat_leg = io.MakeLegend(iData);
    const std::string rec_leg = io.MakeLegend(iReco);
    const std::string tru_leg = io.MakeLegend(iTrue);

    // bundle input options
    PHEC::PlotInput dat_opt = PHEC::PlotInput(
      io.Files().GetFile(iData),
      dat_hist,
      dat_name,
      dat_leg,
      "",
      PHEC::Style::Plot(
        dat_col,
        dat_mar
      )
    );
    PHEC::PlotInput rec_opt = PHEC::PlotInput(
      io.Files().GetFile(iReco),
      rec_hist,
      rec_name,
      rec_leg,
      "",
      PHEC::Style::Plot(
        rec_col,
        rec_mar
      )
    );
    PHEC::PlotInput tru_opt = PHEC::PlotInput(
      io.Files().GetFile(iTrue),
      tru_hist,
      tru_name,
      tru_leg,
      "",
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
    maker.PlotSpectra1D(
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
    const PHEC::Type::PlotIndex& index,
    const InputOutput& io,
    const PHEC::PHCorrelatorPlotMaker& maker,
    TFile* ofile
  ) {

    // constrain level indices
    PHEC::Type::PlotIndex iData = index;
    PHEC::Type::PlotIndex iReco = index;
    PHEC::Type::PlotIndex iTrue = index;
    iData.level = InFiles::Data;
    iReco.level = InFiles::Reco;
    iTrue.level = InFiles::True;

    // make canvas name and tag
    const std::string tag    = io.MakeSpeciesTag("DataVsSim", index.species) + "_";
    const std::string canvas = io.MakeCanvasName("cDataVsSim" + variable, index);

    // build hist names
    const std::string dat_hist = io.MakeHistName(variable, iData);
    const std::string rec_hist = io.MakeHistName(variable, iReco);
    const std::string tru_hist = io.MakeHistName(variable, iTrue);

    // build hist renames
    const std::string dat_name = io.MakeHistName(variable, iData, tag);
    const std::string rec_name = io.MakeHistName(variable, iReco, tag);
    const std::string tru_name = io.MakeHistName(variable, iTrue, tag);

    // build hist legends
    const std::string dat_leg = io.MakeLegend(iData);
    const std::string rec_leg = io.MakeLegend(iReco);
    const std::string tru_leg = io.MakeLegend(iTrue);

    // bundle input options
    PHEC::PlotInput dat_opt = PHEC::PlotInput(
      io.Files().GetFile(iData),
      dat_hist,
      dat_name,
      dat_leg,
      "colz"
    );
    PHEC::PlotInput rec_opt = PHEC::PlotInput(
      io.Files().GetFile(iReco),
      rec_hist,
      rec_name,
      rec_leg,
      "colz"
    );
    PHEC::PlotInput tru_opt = PHEC::PlotInput(
      io.Files().GetFile(iTrue),
      tru_hist,
      tru_name,
      tru_leg,
      "colz"
    );

    // load into vector
    std::vector<PHEC::PlotInput> input;
    input.push_back( dat_opt );
    input.push_back( rec_opt );
    input.push_back( tru_opt );

    // make plot
    maker.PlotSpectra2D(
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
    const int opt,
    const PHEC::Type::PlotIndex& index,
    const InputOutput& io,
    const PHEC::PHCorrelatorPlotMaker& maker,
    TFile* ofile
  ) {

    // constrain pt indices
    PHEC::Type::PlotIndex iPt5  = index;
    PHEC::Type::PlotIndex iPt10 = index;
    PHEC::Type::PlotIndex iPt15 = index;
    iPt5.pt  = InHists::Pt5;
    iPt10.pt = InHists::Pt10;
    iPt15.pt = InHists::Pt15;

    // colors for diferent jet pt
    const std::size_t pt5_col  = 799;
    const std::size_t pt10_col = 899;
    const std::size_t pt15_col = 879;

    // markers for different jet pt
    const std::size_t pt5_mar  = 26;
    const std::size_t pt10_mar = 24;
    const std::size_t pt15_mar = 32;

    // make canvas name and tag
    const std::string tag    = io.MakeSpeciesTag("VsPtJet", index.species) + "_";
    const std::string canvas = io.MakeCanvasName("cVsPtJet" + variable, index);

    // build hist names
    const std::string pt5_hist  = io.MakeHistName(variable, iPt5);
    const std::string pt10_hist = io.MakeHistName(variable, iPt10);
    const std::string pt15_hist = io.MakeHistName(variable, iPt15);

    // build hist renames
    const std::string pt5_name  = io.MakeHistName(variable, iPt5,  tag);
    const std::string pt10_name = io.MakeHistName(variable, iPt10, tag);
    const std::string pt15_name = io.MakeHistName(variable, iPt15, tag);

    // build hist legends
    const std::string pt5_leg  = io.MakeLegend(iPt5);
    const std::string pt10_leg = io.MakeLegend(iPt10);
    const std::string pt15_leg = io.MakeLegend(iPt15);

    // bundle input options
    PHEC::PlotInput pt5_opt = PHEC::PlotInput(
      io.Files().GetFile(iPt5),
      pt5_hist,
      pt5_name,
      pt5_leg,
      "",
      PHEC::Style::Plot(
        pt5_col,
        pt5_mar
      )
    );
    PHEC::PlotInput pt10_opt = PHEC::PlotInput(
      io.Files().GetFile(iPt10),
      pt10_hist,
      pt10_name,
      pt10_leg,
      "",
      PHEC::Style::Plot(
        pt10_col,
        pt10_mar
      )
    );
    PHEC::PlotInput pt15_opt = PHEC::PlotInput(
      io.Files().GetFile(iPt15),
      pt15_hist,
      pt15_name,
      pt15_leg,
      "",
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
    maker.PlotSpectra1D(
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
    const PHEC::Type::PlotIndex& index,
    const InputOutput& io,
    const PHEC::PHCorrelatorPlotMaker& maker,
    TFile* ofile
  ) {

    // constrain pt indices
    PHEC::Type::PlotIndex iPt5  = index;
    PHEC::Type::PlotIndex iPt10 = index;
    PHEC::Type::PlotIndex iPt15 = index;
    iPt5.pt  = InHists::Pt5;
    iPt10.pt = InHists::Pt10;
    iPt15.pt = InHists::Pt15;

    // make canvas name and tag
    const std::string tag    = io.MakeSpeciesTag("VsPtJet", index.species) + "_";
    const std::string canvas = io.MakeCanvasName("cVsPtJet" + variable, index);

    // build hist names
    const std::string pt5_hist  = io.MakeHistName(variable, iPt5);
    const std::string pt10_hist = io.MakeHistName(variable, iPt10);
    const std::string pt15_hist = io.MakeHistName(variable, iPt15);

    // build hist renames
    const std::string pt5_name  = io.MakeHistName(variable, iPt5,  tag);
    const std::string pt10_name = io.MakeHistName(variable, iPt10, tag);
    const std::string pt15_name = io.MakeHistName(variable, iPt15, tag);

    // build hist legends
    const std::string pt5_leg  = io.MakeLegend(iPt5);
    const std::string pt10_leg = io.MakeLegend(iPt10);
    const std::string pt15_leg = io.MakeLegend(iPt15);

    // bundle input options
    PHEC::PlotInput pt5_opt = PHEC::PlotInput(
      io.Files().GetFile(iPt5),
      pt5_hist,
      pt5_name,
      pt5_leg,
      "colz"
    );
    PHEC::PlotInput pt10_opt = PHEC::PlotInput(
      io.Files().GetFile(iPt10),
      pt10_hist,
      pt10_name,
      pt10_leg,
      "colz"
    );
    PHEC::PlotInput pt15_opt = PHEC::PlotInput(
      io.Files().GetFile(iPt15),
      pt15_hist,
      pt15_name,
      pt15_leg,
      "colz"
    );

    // load into vector
    std::vector<PHEC::PlotInput> input;
    input.push_back( pt5_opt );
    input.push_back( pt10_opt );
    input.push_back( pt15_opt );

    // make plot
    maker.PlotSpectra2D(
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
    const int opt,
    const PHEC::Type::PlotIndex& index,
    const InputOutput& io,
    const PHEC::PHCorrelatorPlotMaker& maker,
    TFile* ofile
  ) {

    // constrain pt indices
    PHEC::Type::PlotIndex iPt5  = index;
    PHEC::Type::PlotIndex iPt10 = index;
    PHEC::Type::PlotIndex iPt15 = index;
    iPt5.pt  = InHists::Pt5;
    iPt10.pt = InHists::Pt10;
    iPt15.pt = InHists::Pt15;

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
    const std::string canvas = io.MakeCanvasName("cPPVsPAu" + variable, index);

    // build hist names
    const std::string pt5_hist  = io.MakeHistName(variable, iPt5);
    const std::string pt10_hist = io.MakeHistName(variable, iPt10);
    const std::string pt15_hist = io.MakeHistName(variable, iPt15);

    // build hist renames
    const StringPair pt5_name  = std::make_pair(
      io.MakeHistName(variable, iPt5, tag + "PP_"),
      io.MakeHistName(variable, iPt5, tag + "PAu)")
    );
    const StringPair pt10_name = std::make_pair(
      io.MakeHistName(variable, iPt10, tag + "PP_"),
      io.MakeHistName(variable, iPt10, tag + "PAu_")
    );
    const StringPair pt15_name = std::make_pair(
      io.MakeHistName(variable, iPt15, tag + "PP_"),
      io.MakeHistName(variable, iPt15, tag + "PAu_")
    );

    // set up pp vs. p+Au indices
    PHEC::Type::PlotIndex iPt5pp  = iPt5;
    PHEC::Type::PlotIndex iPt5pa  = iPt5;
    PHEC::Type::PlotIndex iPt10pp = iPt10;
    PHEC::Type::PlotIndex iPt10pa = iPt10;
    PHEC::Type::PlotIndex iPt15pp = iPt15;
    PHEC::Type::PlotIndex iPt15pa = iPt15;
    iPt5pp.species  = InFiles::PP;
    iPt5pa.species  = InFiles::PAu;
    iPt10pp.species = InFiles::PP;
    iPt10pa.species = InFiles::PAu;
    iPt15pp.species = InFiles::PP;
    iPt15pa.species = InFiles::PAu;

    // build hist legends
    const StringPair pt5_leg  = std::make_pair(
      io.MakeLegend(iPt5pp),
      io.MakeLegend(iPt5pa)
    );
    const StringPair pt10_leg = std::make_pair(
      io.MakeLegend(iPt10pp),
      io.MakeLegend(iPt10pa)
    );
    const StringPair pt15_leg = std::make_pair(
      io.MakeLegend(iPt15pp),
      io.MakeLegend(iPt15pa)
    );

    // bundle input options
    InputPair pt5_opt = std::make_pair(
      PHEC::PlotInput(
        io.Files().GetFile(iPt5pp),
        pt5_hist,
        pt5_name.first,
        pt5_leg.first,
        "",
        PHEC::Style::Plot(
          pt5_col.first,
          pt5_mar.first
        )
      ),
      PHEC::PlotInput(
        io.Files().GetFile(iPt5pa),
        pt5_hist,
        pt5_name.second,
        pt5_leg.second,
        "",
        PHEC::Style::Plot(
          pt5_col.second,
          pt5_mar.second
        )
      )
    );
    InputPair pt10_opt = std::make_pair(
      PHEC::PlotInput(
        io.Files().GetFile(iPt10pp),
        pt10_hist,
        pt10_name.first,
        pt10_leg.first,
        "",
        PHEC::Style::Plot(
          pt10_col.first,
          pt10_mar.first
        )
      ),
      PHEC::PlotInput(
        io.Files().GetFile(iPt10pa),
        pt10_hist,
        pt10_name.second,
        pt10_leg.second,
        "",
        PHEC::Style::Plot(
          pt10_col.second,
          pt10_mar.second
        )
      )
    );
    InputPair pt15_opt = std::make_pair(
      PHEC::PlotInput(
        io.Files().GetFile(iPt15pp),
        pt15_hist,
        pt15_name.first,
        pt15_leg.first,
        "",
        PHEC::Style::Plot(
          pt15_col.first,
          pt15_mar.first
        )
      ),
      PHEC::PlotInput(
        io.Files().GetFile(iPt15pa),
        pt15_hist,
        pt15_name.second,
        pt15_leg.second,
        "",
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
    maker.PlotSpectra1D(
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
    const int opt,
    const PHEC::Type::PlotIndex& index,
    const InputOutput& io,
    const PHEC::PHCorrelatorPlotMaker& maker,
    TFile* ofile
  ) {

    // constrain level, pt indices
    PHEC::Type::PlotIndex iPt5data = index;
    PHEC::Type::PlotIndex iPt5reco = index;
    PHEC::Type::PlotIndex iPt5true = index;
    iPt5data.pt    = InHists::Pt5;
    iPt5data.level = InFiles::Data;
    iPt5reco.pt    = InHists::Pt5;
    iPt5reco.level = InFiles::Reco;
    iPt5true.pt    = InHists::Pt5;
    iPt5true.level = InFiles::True;

    PHEC::Type::PlotIndex iPt10data = index;
    PHEC::Type::PlotIndex iPt10reco = index;
    PHEC::Type::PlotIndex iPt10true = index;
    iPt10data.pt    = InHists::Pt10;
    iPt10data.level = InFiles::Data;
    iPt10reco.pt    = InHists::Pt10;
    iPt10reco.level = InFiles::Reco;
    iPt10true.pt    = InHists::Pt10;
    iPt10true.level = InFiles::True;

    PHEC::Type::PlotIndex iPt15data = index;
    PHEC::Type::PlotIndex iPt15reco = index;
    PHEC::Type::PlotIndex iPt15true = index;
    iPt15data.pt    = InHists::Pt15;
    iPt15data.level = InFiles::Data;
    iPt15reco.pt    = InHists::Pt15;
    iPt15reco.level = InFiles::Reco;
    iPt15true.pt    = InHists::Pt15;
    iPt15true.level = InFiles::True;

    // colors for diferent jet pt
    const std::size_t pt5_col[3]  = {799, 797, 809};
    const std::size_t pt10_col[3] = {899, 909, 907};
    const std::size_t pt15_col[3] = {889, 879, 877};

    // markers for different jet pt
    const std::size_t pt5_mar[3]  = {22, 22, 26};
    const std::size_t pt10_mar[3] = {20, 24, 24};
    const std::size_t pt15_mar[3] = {23, 23, 32};

    // make canvas name and tag
    const std::string tag    = io.MakeSpeciesTag("Correct1D", index.species) + "_";
    const std::string canvas = io.MakeCanvasName("cCorrect" + variable, index);

    // build data hist names
    const std::string pt5_dhist  = io.MakeHistName(variable, iPt5data);
    const std::string pt10_dhist = io.MakeHistName(variable, iPt10data);
    const std::string pt15_dhist = io.MakeHistName(variable, iPt15data);

    // build reco hist names
    const std::string pt5_rhist  = io.MakeHistName(variable, iPt5reco);
    const std::string pt10_rhist = io.MakeHistName(variable, iPt10reco);
    const std::string pt15_rhist = io.MakeHistName(variable, iPt15reco);

    // build true hist names
    const std::string pt5_thist  = io.MakeHistName(variable, iPt5true);
    const std::string pt10_thist = io.MakeHistName(variable, iPt10true);
    const std::string pt15_thist = io.MakeHistName(variable, iPt15true);

    // build hist renames
    const std::string pt5_name[3] = {
      io.MakeHistName(variable, iPt5data, tag),
      io.MakeHistName(variable, iPt5reco, tag),
      io.MakeHistName(variable, iPt5true, tag)
    };
    const std::string pt10_name[3] = {
      io.MakeHistName(variable, iPt10data, tag),
      io.MakeHistName(variable, iPt10reco, tag),
      io.MakeHistName(variable, iPt10true, tag)
    };
    const std::string pt15_name[3] = {
      io.MakeHistName(variable, iPt15data, tag),
      io.MakeHistName(variable, iPt15reco, tag),
      io.MakeHistName(variable, iPt15true, tag)
    };

    // build hist legends
    const std::string pt5_leg[3] = {
      io.MakeLegend(iPt5data),
      io.MakeLegend(iPt5reco),
      io.MakeLegend(iPt5true)
    };
    const std::string pt10_leg[3] = {
      io.MakeLegend(iPt10data),
      io.MakeLegend(iPt10reco),
      io.MakeLegend(iPt10true)
    };
    const std::string pt15_leg[3] = {
      io.MakeLegend(iPt15data),
      io.MakeLegend(iPt15reco),
      io.MakeLegend(iPt15true)
    };

    // bundle input data options
    PHEC::Inputs data_opt;
    data_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(iPt5data),
        pt5_dhist,
        pt5_name[0],
        pt5_leg[0],
        "",
        PHEC::Style::Plot(
          pt5_col[0],
          pt5_mar[0]
        )
      )
    );
    data_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(iPt10data),
        pt10_dhist,
        pt10_name[0],
        pt10_leg[0],
        "",
        PHEC::Style::Plot(
          pt10_col[0],
          pt10_mar[0]
        )
      )
    );
    data_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(iPt15data),
        pt15_dhist,
        pt15_name[0],
        pt15_leg[0],
        "",
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
        io.Files().GetFile(iPt5reco),
        pt5_rhist,
        pt5_name[1],
        pt5_leg[1],
        "",
        PHEC::Style::Plot(
          pt5_col[1],
          pt5_mar[1]
        )
      )
    );
    reco_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(iPt10reco),
        pt10_rhist,
        pt10_name[1],
        pt10_leg[1],
        "",
        PHEC::Style::Plot(
          pt10_col[1],
          pt10_mar[1]
        )
      )
    );
    reco_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(iPt15reco),
        pt15_rhist,
        pt15_name[1],
        pt15_leg[1],
        "",
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
        io.Files().GetFile(iPt5true),
        pt5_thist,
        pt5_name[2],
        pt5_leg[2],
        "",
        PHEC::Style::Plot(
          pt5_col[2],
          pt5_mar[2]
        )
      )
    );
    true_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(iPt10true),
        pt10_thist,
        pt10_name[2],
        pt10_leg[2],
        "",
        PHEC::Style::Plot(
          pt10_col[2],
          pt10_mar[2]
        )
      )
    );
    true_opt.push_back(
      PHEC::PlotInput(
        io.Files().GetFile(iPt15true),
        pt15_thist,
        pt15_name[2],
        pt15_leg[2],
        "",
        PHEC::Style::Plot(
          pt15_col[2],
          pt15_mar[2]
        )
      )
    );

    // make plot
    maker.PlotSpectra1D(
      PO::CorrectSpectra1D(data_opt, reco_opt, true_opt, canvas, opt),
      ofile
    );
    return;

  }  // end 'CorrectSpectra1D(...)'

}  // end PlotsToMake namespace

#endif

// end ========================================================================
