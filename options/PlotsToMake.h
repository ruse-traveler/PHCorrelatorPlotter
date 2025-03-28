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
    const PHEC::Input& input,
    const PHEC::PlotMaker& maker,
    TFile* ofile
  ) {

    // constrain level indices
    PHEC::Type::PlotIndex iData = index;
    PHEC::Type::PlotIndex iReco = index;
    PHEC::Type::PlotIndex iTrue = index;
    iData.level = PHEC::FileInput::Data;
    iReco.level = PHEC::FileInput::Reco;
    iTrue.level = PHEC::FileInput::True;

    // colors for data, reco, and truth levels
    const std::size_t dat_col = 899;
    const std::size_t rec_col = 859;
    const std::size_t tru_col = 923;

    // markers for data, reco, and truth levels
    const std::size_t dat_mar = 24;
    const std::size_t rec_mar = 25;
    const std::size_t tru_mar = 29;

    // make canvas name and tag
    const std::string tag    = input.MakeSpeciesTag("DataVsSim", index.species) + "_";
    const std::string canvas = input.MakeCanvasName("cDataVsSim" + variable, index);

    // build hist names
    const std::string dat_hist = input.MakeHistName(variable, iData);
    const std::string rec_hist = input.MakeHistName(variable, iReco);
    const std::string tru_hist = input.MakeHistName(variable, iTrue);

    // build hist renames
    const std::string dat_name = input.MakeHistName(variable, iData, tag);
    const std::string rec_name = input.MakeHistName(variable, iReco, tag);
    const std::string tru_name = input.MakeHistName(variable, iTrue, tag);

    // build hist legends
    const std::string dat_leg = input.MakeLegend(iData);
    const std::string rec_leg = input.MakeLegend(iReco);
    const std::string tru_leg = input.MakeLegend(iTrue);

    // bundle input options
    PHEC::PlotInput dat_opt = PHEC::PlotInput(
      input.Files().GetFile(iData),
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
      input.Files().GetFile(iReco),
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
      input.Files().GetFile(iTrue),
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
    const PHEC::Input& input,
    const PHEC::PlotMaker& maker,
    TFile* ofile
  ) {

    // constrain level indices
    PHEC::Type::PlotIndex iData = index;
    PHEC::Type::PlotIndex iReco = index;
    PHEC::Type::PlotIndex iTrue = index;
    iData.level = PHEC::FileInput::Data;
    iReco.level = PHEC::FileInput::Reco;
    iTrue.level = PHEC::FileInput::True;

    // make canvas name and tag
    const std::string tag    = input.MakeSpeciesTag("DataVsSim", index.species) + "_";
    const std::string canvas = input.MakeCanvasName("cDataVsSim" + variable, index);

    // build hist names
    const std::string dat_hist = input.MakeHistName(variable, iData);
    const std::string rec_hist = input.MakeHistName(variable, iReco);
    const std::string tru_hist = input.MakeHistName(variable, iTrue);

    // build hist renames
    const std::string dat_name = input.MakeHistName(variable, iData, tag);
    const std::string rec_name = input.MakeHistName(variable, iReco, tag);
    const std::string tru_name = input.MakeHistName(variable, iTrue, tag);

    // build hist legends
    const std::string dat_leg = input.MakeLegend(iData);
    const std::string rec_leg = input.MakeLegend(iReco);
    const std::string tru_leg = input.MakeLegend(iTrue);

    // bundle input options
    PHEC::PlotInput dat_opt = PHEC::PlotInput(
      input.Files().GetFile(iData),
      dat_hist,
      dat_name,
      dat_leg,
      "colz"
    );
    PHEC::PlotInput rec_opt = PHEC::PlotInput(
      input.Files().GetFile(iReco),
      rec_hist,
      rec_name,
      rec_leg,
      "colz"
    );
    PHEC::PlotInput tru_opt = PHEC::PlotInput(
      input.Files().GetFile(iTrue),
      tru_hist,
      tru_name,
      tru_leg,
      "colz"
    );

    // load into vector
    std::vector<PHEC::PlotInput> inputs;
    inputs.push_back( dat_opt );
    inputs.push_back( rec_opt );
    inputs.push_back( tru_opt );

    // make plot
    maker.PlotSpectra2D(
      PO::CompareSpectra2D(inputs, canvas),
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
    const PHEC::Input& input,
    const PHEC::PlotMaker& maker,
    TFile* ofile
  ) {

    // constrain pt indices
    PHEC::Type::PlotIndex iPt5  = index;
    PHEC::Type::PlotIndex iPt10 = index;
    PHEC::Type::PlotIndex iPt15 = index;
    iPt5.pt  = PHEC::HistInput::Pt5;
    iPt10.pt = PHEC::HistInput::Pt10;
    iPt15.pt = PHEC::HistInput::Pt15;

    // colors for diferent jet pt
    const std::size_t pt5_col  = 799;
    const std::size_t pt10_col = 899;
    const std::size_t pt15_col = 879;

    // markers for different jet pt
    const std::size_t pt5_mar  = 26;
    const std::size_t pt10_mar = 24;
    const std::size_t pt15_mar = 32;

    // make canvas name and tag
    const std::string tag    = input.MakeSpeciesTag("VsPtJet", index.species) + "_";
    const std::string canvas = input.MakeCanvasName("cVsPtJet" + variable, index);

    // build hist names
    const std::string pt5_hist  = input.MakeHistName(variable, iPt5);
    const std::string pt10_hist = input.MakeHistName(variable, iPt10);
    const std::string pt15_hist = input.MakeHistName(variable, iPt15);

    // build hist renames
    const std::string pt5_name  = input.MakeHistName(variable, iPt5,  tag);
    const std::string pt10_name = input.MakeHistName(variable, iPt10, tag);
    const std::string pt15_name = input.MakeHistName(variable, iPt15, tag);

    // build hist legends
    const std::string pt5_leg  = input.MakeLegend(iPt5);
    const std::string pt10_leg = input.MakeLegend(iPt10);
    const std::string pt15_leg = input.MakeLegend(iPt15);

    // bundle input options
    PHEC::PlotInput pt5_opt = PHEC::PlotInput(
      input.Files().GetFile(iPt5),
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
      input.Files().GetFile(iPt10),
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
      input.Files().GetFile(iPt15),
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
    std::vector<PHEC::PlotInput> inputs;
    inputs.push_back( pt5_opt );
    inputs.push_back( pt10_opt );
    inputs.push_back( pt15_opt );

    // make plot
    maker.PlotSpectra1D(
      PO::CompareSpectra1D(inputs, canvas, opt),
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
    const PHEC::Input& input,
    const PHEC::PlotMaker& maker,
    TFile* ofile
  ) {

    // constrain pt indices
    PHEC::Type::PlotIndex iPt5  = index;
    PHEC::Type::PlotIndex iPt10 = index;
    PHEC::Type::PlotIndex iPt15 = index;
    iPt5.pt  = PHEC::HistInput::Pt5;
    iPt10.pt = PHEC::HistInput::Pt10;
    iPt15.pt = PHEC::HistInput::Pt15;

    // make canvas name and tag
    const std::string tag    = input.MakeSpeciesTag("VsPtJet", index.species) + "_";
    const std::string canvas = input.MakeCanvasName("cVsPtJet" + variable, index);

    // build hist names
    const std::string pt5_hist  = input.MakeHistName(variable, iPt5);
    const std::string pt10_hist = input.MakeHistName(variable, iPt10);
    const std::string pt15_hist = input.MakeHistName(variable, iPt15);

    // build hist renames
    const std::string pt5_name  = input.MakeHistName(variable, iPt5,  tag);
    const std::string pt10_name = input.MakeHistName(variable, iPt10, tag);
    const std::string pt15_name = input.MakeHistName(variable, iPt15, tag);

    // build hist legends
    const std::string pt5_leg  = input.MakeLegend(iPt5);
    const std::string pt10_leg = input.MakeLegend(iPt10);
    const std::string pt15_leg = input.MakeLegend(iPt15);

    // bundle input options
    PHEC::PlotInput pt5_opt = PHEC::PlotInput(
      input.Files().GetFile(iPt5),
      pt5_hist,
      pt5_name,
      pt5_leg,
      "colz"
    );
    PHEC::PlotInput pt10_opt = PHEC::PlotInput(
      input.Files().GetFile(iPt10),
      pt10_hist,
      pt10_name,
      pt10_leg,
      "colz"
    );
    PHEC::PlotInput pt15_opt = PHEC::PlotInput(
      input.Files().GetFile(iPt15),
      pt15_hist,
      pt15_name,
      pt15_leg,
      "colz"
    );

    // load into vector
    std::vector<PHEC::PlotInput> inputs;
    inputs.push_back( pt5_opt );
    inputs.push_back( pt10_opt );
    inputs.push_back( pt15_opt );

    // make plot
    maker.PlotSpectra2D(
      PO::CompareSpectra2D(inputs, canvas),
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
    const PHEC::Input& input,
    const PHEC::PlotMaker& maker,
    TFile* ofile
  ) {

    // constrain pt indices
    PHEC::Type::PlotIndex iPt5  = index;
    PHEC::Type::PlotIndex iPt10 = index;
    PHEC::Type::PlotIndex iPt15 = index;
    iPt5.pt  = PHEC::HistInput::Pt5;
    iPt10.pt = PHEC::HistInput::Pt10;
    iPt15.pt = PHEC::HistInput::Pt15;

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
    const std::string canvas = input.MakeCanvasName("cPPVsPAu" + variable, index);

    // build hist names
    const std::string pt5_hist  = input.MakeHistName(variable, iPt5);
    const std::string pt10_hist = input.MakeHistName(variable, iPt10);
    const std::string pt15_hist = input.MakeHistName(variable, iPt15);

    // build hist renames
    const StringPair pt5_name  = std::make_pair(
      input.MakeHistName(variable, iPt5, tag + "PP_"),
      input.MakeHistName(variable, iPt5, tag + "PAu)")
    );
    const StringPair pt10_name = std::make_pair(
      input.MakeHistName(variable, iPt10, tag + "PP_"),
      input.MakeHistName(variable, iPt10, tag + "PAu_")
    );
    const StringPair pt15_name = std::make_pair(
      input.MakeHistName(variable, iPt15, tag + "PP_"),
      input.MakeHistName(variable, iPt15, tag + "PAu_")
    );

    // set up pp vs. p+Au indices
    PHEC::Type::PlotIndex iPt5pp  = iPt5;
    PHEC::Type::PlotIndex iPt5pa  = iPt5;
    PHEC::Type::PlotIndex iPt10pp = iPt10;
    PHEC::Type::PlotIndex iPt10pa = iPt10;
    PHEC::Type::PlotIndex iPt15pp = iPt15;
    PHEC::Type::PlotIndex iPt15pa = iPt15;
    iPt5pp.species  = PHEC::FileInput::PP;
    iPt5pa.species  = PHEC::FileInput::PAu;
    iPt10pp.species = PHEC::FileInput::PP;
    iPt10pa.species = PHEC::FileInput::PAu;
    iPt15pp.species = PHEC::FileInput::PP;
    iPt15pa.species = PHEC::FileInput::PAu;

    // build hist legends
    const StringPair pt5_leg  = std::make_pair(
      input.MakeLegend(iPt5pp),
      input.MakeLegend(iPt5pa)
    );
    const StringPair pt10_leg = std::make_pair(
      input.MakeLegend(iPt10pp),
      input.MakeLegend(iPt10pa)
    );
    const StringPair pt15_leg = std::make_pair(
      input.MakeLegend(iPt15pp),
      input.MakeLegend(iPt15pa)
    );

    // bundle input options
    InputPair pt5_opt = std::make_pair(
      PHEC::PlotInput(
        input.Files().GetFile(iPt5pp),
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
        input.Files().GetFile(iPt5pa),
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
        input.Files().GetFile(iPt10pp),
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
        input.Files().GetFile(iPt10pa),
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
        input.Files().GetFile(iPt15pp),
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
        input.Files().GetFile(iPt15pa),
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
    const PHEC::Input& input,
    const PHEC::PlotMaker& maker,
    TFile* ofile
  ) {

    // constrain level, pt indices
    PHEC::Type::PlotIndex iPt5data = index;
    PHEC::Type::PlotIndex iPt5reco = index;
    PHEC::Type::PlotIndex iPt5true = index;
    iPt5data.pt    = PHEC::HistInput::Pt5;
    iPt5data.level = PHEC::FileInput::Data;
    iPt5reco.pt    = PHEC::HistInput::Pt5;
    iPt5reco.level = PHEC::FileInput::Reco;
    iPt5true.pt    = PHEC::HistInput::Pt5;
    iPt5true.level = PHEC::FileInput::True;

    PHEC::Type::PlotIndex iPt10data = index;
    PHEC::Type::PlotIndex iPt10reco = index;
    PHEC::Type::PlotIndex iPt10true = index;
    iPt10data.pt    = PHEC::HistInput::Pt10;
    iPt10data.level = PHEC::FileInput::Data;
    iPt10reco.pt    = PHEC::HistInput::Pt10;
    iPt10reco.level = PHEC::FileInput::Reco;
    iPt10true.pt    = PHEC::HistInput::Pt10;
    iPt10true.level = PHEC::FileInput::True;

    PHEC::Type::PlotIndex iPt15data = index;
    PHEC::Type::PlotIndex iPt15reco = index;
    PHEC::Type::PlotIndex iPt15true = index;
    iPt15data.pt    = PHEC::HistInput::Pt15;
    iPt15data.level = PHEC::FileInput::Data;
    iPt15reco.pt    = PHEC::HistInput::Pt15;
    iPt15reco.level = PHEC::FileInput::Reco;
    iPt15true.pt    = PHEC::HistInput::Pt15;
    iPt15true.level = PHEC::FileInput::True;

    // colors for diferent jet pt
    const std::size_t pt5_col[3]  = {799, 797, 809};
    const std::size_t pt10_col[3] = {899, 909, 907};
    const std::size_t pt15_col[3] = {889, 879, 877};

    // markers for different jet pt
    const std::size_t pt5_mar[3]  = {22, 22, 26};
    const std::size_t pt10_mar[3] = {20, 24, 24};
    const std::size_t pt15_mar[3] = {23, 23, 32};

    // make canvas name and tag
    const std::string tag    = input.MakeSpeciesTag("Correct1D", index.species) + "_";
    const std::string canvas = input.MakeCanvasName("cCorrect" + variable, index);

    // build data hist names
    const std::string pt5_dhist  = input.MakeHistName(variable, iPt5data);
    const std::string pt10_dhist = input.MakeHistName(variable, iPt10data);
    const std::string pt15_dhist = input.MakeHistName(variable, iPt15data);

    // build reco hist names
    const std::string pt5_rhist  = input.MakeHistName(variable, iPt5reco);
    const std::string pt10_rhist = input.MakeHistName(variable, iPt10reco);
    const std::string pt15_rhist = input.MakeHistName(variable, iPt15reco);

    // build true hist names
    const std::string pt5_thist  = input.MakeHistName(variable, iPt5true);
    const std::string pt10_thist = input.MakeHistName(variable, iPt10true);
    const std::string pt15_thist = input.MakeHistName(variable, iPt15true);

    // build hist renames
    const std::string pt5_name[3] = {
      input.MakeHistName(variable, iPt5data, tag),
      input.MakeHistName(variable, iPt5reco, tag),
      input.MakeHistName(variable, iPt5true, tag)
    };
    const std::string pt10_name[3] = {
      input.MakeHistName(variable, iPt10data, tag),
      input.MakeHistName(variable, iPt10reco, tag),
      input.MakeHistName(variable, iPt10true, tag)
    };
    const std::string pt15_name[3] = {
      input.MakeHistName(variable, iPt15data, tag),
      input.MakeHistName(variable, iPt15reco, tag),
      input.MakeHistName(variable, iPt15true, tag)
    };

    // build hist legends
    const std::string pt5_leg[3] = {
      input.MakeLegend(iPt5data),
      input.MakeLegend(iPt5reco),
      input.MakeLegend(iPt5true)
    };
    const std::string pt10_leg[3] = {
      input.MakeLegend(iPt10data),
      input.MakeLegend(iPt10reco),
      input.MakeLegend(iPt10true)
    };
    const std::string pt15_leg[3] = {
      input.MakeLegend(iPt15data),
      input.MakeLegend(iPt15reco),
      input.MakeLegend(iPt15true)
    };

    // bundle input data options
    PHEC::Inputs data_opt;
    data_opt.push_back(
      PHEC::PlotInput(
        input.Files().GetFile(iPt5data),
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
        input.Files().GetFile(iPt10data),
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
        input.Files().GetFile(iPt15data),
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
        input.Files().GetFile(iPt5reco),
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
        input.Files().GetFile(iPt10reco),
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
        input.Files().GetFile(iPt15reco),
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
        input.Files().GetFile(iPt5true),
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
        input.Files().GetFile(iPt10true),
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
        input.Files().GetFile(iPt15true),
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
