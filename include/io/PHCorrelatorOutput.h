/// ===========================================================================
/*! \file   PHCorrelatorOutput.h
 *  \author Derek Anderson
 *  \date   01.08.2025
 *
 *  Class to define what specific plots
 *  to output.
 */
/// ===========================================================================

#ifndef PHCORRELATOROUTPUT_H
#define PHCORRELATOROUTPUT_H

// c++ utilities
#include <string>
#include <utility>
#include <vector>
// root libraries
#include <TFile.h>
// plotting utilities
#include "PHCorrelatorFileInput.h"
#include "PHCorrelatorHistInput.h"
#include "PHCorrelatorInput.h"
#include "PHCorrelatorIOTypes.h"
#include "../elements/PHCorrelatorPlotterElements.h"
#include "../maker/PHCorrelatorPlotMaker.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Plotting Output ()
  // ==========================================================================
  /*! A class to apply the generic routines of PHEC::PlotMaker
   *  to the inputs deined by PHEC::Input.
   */
  class Output {

    public:

      // enumerate outputs
      enum Plots {SimVsData, RecoVsData, VsPtJet, PPVsPAu, CorrectSpectra};

    private:

      // data members
      Type::PlotIndex m_index;
      PlotMaker       m_maker;
      Input           m_input;

    public:

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetIndex(const Type::PlotIndex& index) {m_index = index;}
      void SetMaker(const PlotMaker& maker)       {m_maker = maker;}
      void SetInput(const Input& input)           {m_input = input;}

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Type::PlotIndex GetIndex() const {return m_index;}
      PlotMaker       GetMaker() const {return m_maker;}
      Input           GetInput() const {return m_input;}

      // ----------------------------------------------------------------------
      //! Make 1D sim vs. data plot
      // ----------------------------------------------------------------------
      void SimVsData1D(const std::string& variable, const int opt, TFile* ofile) {

        // constrain level indices
        Type::PlotIndex iData = m_index;
        Type::PlotIndex iReco = m_index;
        Type::PlotIndex iTrue = m_index;
        iData.level = FileInput::Data;
        iReco.level = FileInput::Reco;
        iTrue.level = FileInput::True;

        // colors for data, reco, and truth levels
        const std::size_t dat_col = 899;
        const std::size_t rec_col = 859;
        const std::size_t tru_col = 923;

        // markers for data, reco, and truth levels
        const std::size_t dat_mar = 24;
        const std::size_t rec_mar = 25;
        const std::size_t tru_mar = 29;

        // make canvas name and tag
        const std::string tag    = m_input.MakeSpeciesTag("DataVsSim", m_index.species) + "_";
        const std::string canvas = m_input.MakeCanvasName("cDataVsSim" + variable, m_index);

        // build hist names
        const std::string dat_hist = m_input.MakeHistName(variable, iData);
        const std::string rec_hist = m_input.MakeHistName(variable, iReco);
        const std::string tru_hist = m_input.MakeHistName(variable, iTrue);

        // build hist renames
        const std::string dat_name = m_input.MakeHistName(variable, iData, tag);
        const std::string rec_name = m_input.MakeHistName(variable, iReco, tag);
        const std::string tru_name = m_input.MakeHistName(variable, iTrue, tag);

        // build hist legends
        const std::string dat_leg = m_input.MakeLegend(iData);
        const std::string rec_leg = m_input.MakeLegend(iReco);
        const std::string tru_leg = m_input.MakeLegend(iTrue);

        // bundle input options
        PlotInput dat_opt = PlotInput(
          m_input.GetFiles().GetFile(iData),
          dat_hist,
          dat_name,
          dat_leg,
          "",
          Style::Plot(
            dat_col,
            dat_mar
          )
        );
        PlotInput rec_opt = PlotInput(
          m_input.GetFiles().GetFile(iReco),
          rec_hist,
          rec_name,
          rec_leg,
          "",
          Style::Plot(
            rec_col,
            rec_mar
          )
        );
        PlotInput tru_opt = PlotInput(
          m_input.GetFiles().GetFile(iTrue),
          tru_hist,
          tru_name,
          tru_leg,
          "",
          Style::Plot(
            tru_col,
            tru_mar
          )
        );

        // load into vector
        std::vector<PlotInput> num_input;
        num_input.push_back( dat_opt );
        num_input.push_back( rec_opt );

        // make plot
        m_maker.GetPlotVsBaseline1D().Configure(tru_opt, num_input, canvas, opt);
        m_maker.GetPlotVsBaseline1D().Plot(ofile);
        return;

      }  // end 'SimVsData1D(std::string&, int, TFile*)'

      // ----------------------------------------------------------------------
      // Make 2D sim vs. data plot
      // ----------------------------------------------------------------------
      void SimVsData2D(const std::string& variable, TFile* ofile) {

        // constrain level indices
        Type::PlotIndex iData = m_index;
        Type::PlotIndex iReco = m_index;
        Type::PlotIndex iTrue = m_index;
        iData.level = FileInput::Data;
        iReco.level = FileInput::Reco;
        iTrue.level = FileInput::True;

        // make canvas name and tag
        const std::string tag    = m_input.MakeSpeciesTag("DataVsSim", m_index.species) + "_";
        const std::string canvas = m_input.MakeCanvasName("cDataVsSim" + variable, m_index);

        // build hist names
        const std::string dat_hist = m_input.MakeHistName(variable, iData);
        const std::string rec_hist = m_input.MakeHistName(variable, iReco);
        const std::string tru_hist = m_input.MakeHistName(variable, iTrue);

        // build hist renames
        const std::string dat_name = m_input.MakeHistName(variable, iData, tag);
        const std::string rec_name = m_input.MakeHistName(variable, iReco, tag);
        const std::string tru_name = m_input.MakeHistName(variable, iTrue, tag);

        // build hist legends
        const std::string dat_leg = m_input.MakeLegend(iData);
        const std::string rec_leg = m_input.MakeLegend(iReco);
        const std::string tru_leg = m_input.MakeLegend(iTrue);

        // bundle input options
        PlotInput dat_opt = PlotInput(
          m_input.GetFiles().GetFile(iData),
          dat_hist,
          dat_name,
          dat_leg,
          "colz"
        );
        PlotInput rec_opt = PlotInput(
          m_input.GetFiles().GetFile(iReco),
          rec_hist,
          rec_name,
          rec_leg,
          "colz"
        );
        PlotInput tru_opt = PlotInput(
          m_input.GetFiles().GetFile(iTrue),
          tru_hist,
          tru_name,
          tru_leg,
          "colz"
        );

        // load into vector
        std::vector<PlotInput> inputs;
        inputs.push_back( dat_opt );
        inputs.push_back( rec_opt );
        inputs.push_back( tru_opt );

        // make plot
        m_maker.GetPlotSpectra2D().Configure(inputs, canvas);
        m_maker.GetPlotSpectra2D().Plot(ofile);
        return;

      }  // end 'SimVsData2D(std::string&, TFile*)'

      // ----------------------------------------------------------------------
      //! Make 1D reco vs. data comparison plot
      // ----------------------------------------------------------------------
      void RecoVsData1D(const std::string& variable, const int opt, TFile* ofile) {

        // constrain level indices
        Type::PlotIndex iData = m_index;
        Type::PlotIndex iReco = m_index;
        iData.level = FileInput::Data;
        iReco.level = FileInput::Reco;

        // make canvas name and tag
        const std::string tag    = m_input.MakeSpeciesTag("DataVsReco", m_index.species) + "_";
        const std::string canvas = m_input.MakeCanvasName("cDataVsReco" + variable, m_index);

        // bundle input options
        PlotInput dat_opt = PlotInput(
          m_input.GetFiles().GetFile(iData),
          m_input.MakeHistName(variable, iData),
          m_input.MakeHistName(variable, iData, tag),
          m_input.MakeLegend(iData),
          "",
          Style::Plot(923, 20)
        );
        PlotInput rec_opt = PlotInput(
          m_input.GetFiles().GetFile(iReco),
          m_input.MakeHistName(variable, iReco),
          m_input.MakeHistName(variable, iReco, tag),
          m_input.MakeLegend(iReco),
          "",
          Style::Plot(899, 24)
        );

        // load into vectors
        std::vector<PlotInput> dat_in;
        std::vector<PlotInput> rec_in;
        dat_in.push_back( dat_opt );
        rec_in.push_back( rec_opt );

        //  make plot
        m_maker.GetPlotRatios1D().Configure(dat_in, rec_in, canvas, opt);
        m_maker.GetPlotRatios1D().Plot(ofile);
        return;

      }  // end 'RecoVsData1D(std::string&, int, TFile*)'

      // ----------------------------------------------------------------------
      // Make 1D vs. jet pt comparison
      // ----------------------------------------------------------------------
      void VsPtJet1D(const std::string& variable, const int opt, TFile* ofile) {

        // constrain pt indices
        Type::PlotIndex iPt5  = m_index;
        Type::PlotIndex iPt10 = m_index;
        Type::PlotIndex iPt15 = m_index;
        iPt5.pt  = HistInput::Pt5;
        iPt10.pt = HistInput::Pt10;
        iPt15.pt = HistInput::Pt15;

        // colors for diferent jet pt
        const std::size_t pt5_col  = 799;
        const std::size_t pt10_col = 899;
        const std::size_t pt15_col = 879;

        // markers for different jet pt
        const std::size_t pt5_mar  = 26;
        const std::size_t pt10_mar = 24;
        const std::size_t pt15_mar = 32;

        // make canvas name and tag
        const std::string tag    = m_input.MakeSpeciesTag("VsPtJet", m_index.species) + "_";
        const std::string canvas = m_input.MakeCanvasName("cVsPtJet" + variable, m_index);

        // build hist names
        const std::string pt5_hist  = m_input.MakeHistName(variable, iPt5);
        const std::string pt10_hist = m_input.MakeHistName(variable, iPt10);
        const std::string pt15_hist = m_input.MakeHistName(variable, iPt15);

        // build hist renames
        const std::string pt5_name  = m_input.MakeHistName(variable, iPt5,  tag);
        const std::string pt10_name = m_input.MakeHistName(variable, iPt10, tag);
        const std::string pt15_name = m_input.MakeHistName(variable, iPt15, tag);

        // build hist legends
        const std::string pt5_leg  = m_input.MakeLegend(iPt5);
        const std::string pt10_leg = m_input.MakeLegend(iPt10);
        const std::string pt15_leg = m_input.MakeLegend(iPt15);

        // bundle input options
        PlotInput pt5_opt = PlotInput(
          m_input.GetFiles().GetFile(iPt5),
          pt5_hist,
          pt5_name,
          pt5_leg,
          "",
          Style::Plot(
            pt5_col,
            pt5_mar
          )
        );
        PlotInput pt10_opt = PlotInput(
          m_input.GetFiles().GetFile(iPt10),
          pt10_hist,
          pt10_name,
          pt10_leg,
          "",
          Style::Plot(
            pt10_col,
            pt10_mar
          )
        );
        PlotInput pt15_opt = PlotInput(
          m_input.GetFiles().GetFile(iPt15),
          pt15_hist,
          pt15_name,
          pt15_leg,
          "",
          Style::Plot(
            pt15_col,
            pt15_mar
          )
        );

        // load into vector
        std::vector<PlotInput> inputs;
        inputs.push_back( pt5_opt );
        inputs.push_back( pt10_opt );
        inputs.push_back( pt15_opt );

        // make plot
        m_maker.GetPlotSpectra1D().Configure(inputs, canvas, opt);
        m_maker.GetPlotSpectra1D().Plot(ofile);
        return;

      }  // end 'VsPtJet1D(std::string&, int, TFile*)'

      // ----------------------------------------------------------------------
      // Make 2D vs. jet pt comparison
      // ----------------------------------------------------------------------
      void VsPtJet2D(const std::string& variable, TFile* ofile) {

        // constrain pt indices
        Type::PlotIndex iPt5  = m_index;
        Type::PlotIndex iPt10 = m_index;
        Type::PlotIndex iPt15 = m_index;
        iPt5.pt  = HistInput::Pt5;
        iPt10.pt = HistInput::Pt10;
        iPt15.pt = HistInput::Pt15;

        // make canvas name and tag
        const std::string tag    = m_input.MakeSpeciesTag("VsPtJet", m_index.species) + "_";
        const std::string canvas = m_input.MakeCanvasName("cVsPtJet" + variable, m_index);

        // build hist names
        const std::string pt5_hist  = m_input.MakeHistName(variable, iPt5);
        const std::string pt10_hist = m_input.MakeHistName(variable, iPt10);
        const std::string pt15_hist = m_input.MakeHistName(variable, iPt15);

        // build hist renames
        const std::string pt5_name  = m_input.MakeHistName(variable, iPt5,  tag);
        const std::string pt10_name = m_input.MakeHistName(variable, iPt10, tag);
        const std::string pt15_name = m_input.MakeHistName(variable, iPt15, tag);

        // build hist legends
        const std::string pt5_leg  = m_input.MakeLegend(iPt5);
        const std::string pt10_leg = m_input.MakeLegend(iPt10);
        const std::string pt15_leg = m_input.MakeLegend(iPt15);

        // bundle input options
        PlotInput pt5_opt = PlotInput(
          m_input.GetFiles().GetFile(iPt5),
          pt5_hist,
          pt5_name,
          pt5_leg,
          "colz"
        );
        PlotInput pt10_opt = PlotInput(
          m_input.GetFiles().GetFile(iPt10),
          pt10_hist,
          pt10_name,
          pt10_leg,
          "colz"
        );
        PlotInput pt15_opt = PlotInput(
          m_input.GetFiles().GetFile(iPt15),
          pt15_hist,
          pt15_name,
          pt15_leg,
          "colz"
        );

        // load into vector
        std::vector<PlotInput> inputs;
        inputs.push_back( pt5_opt );
        inputs.push_back( pt10_opt );
        inputs.push_back( pt15_opt );

        // make plot
        m_maker.GetPlotSpectra2D().Configure(inputs, canvas);
        m_maker.GetPlotSpectra2D().Plot(ofile);
        return;

      }  // end 'VsPtJet2D(std::string&, TFile*)'

      // ----------------------------------------------------------------------
      // Make 1D pp vs. pau plot
      // ----------------------------------------------------------------------
      void PPVsPAu1D(const std::string& variable, const int opt, TFile* ofile) {

        // constrain pt indices
        Type::PlotIndex iPt5  = m_index;
        Type::PlotIndex iPt10 = m_index;
        Type::PlotIndex iPt15 = m_index;
        iPt5.pt  = HistInput::Pt5;
        iPt10.pt = HistInput::Pt10;
        iPt15.pt = HistInput::Pt15;

        // colors for diferent jet pt
        const Type::StylePair pt5_col  = std::make_pair(809, 799);
        const Type::StylePair pt10_col = std::make_pair(899, 909);
        const Type::StylePair pt15_col = std::make_pair(889, 879);

        // markers for different jet pt
        const Type::StylePair pt5_mar  = std::make_pair(22, 26);
        const Type::StylePair pt10_mar = std::make_pair(20, 24);
        const Type::StylePair pt15_mar = std::make_pair(23, 32);

        // make canvas name and tag
        const std::string tag    = "PPVsPAu_";
        const std::string canvas = m_input.MakeCanvasName("cPPVsPAu" + variable, m_index);

        // build hist names
        const std::string pt5_hist  = m_input.MakeHistName(variable, iPt5);
        const std::string pt10_hist = m_input.MakeHistName(variable, iPt10);
        const std::string pt15_hist = m_input.MakeHistName(variable, iPt15);

        // build hist renames
        const Type::StringPair pt5_name  = std::make_pair(
          m_input.MakeHistName(variable, iPt5, tag + "PP_"),
          m_input.MakeHistName(variable, iPt5, tag + "PAu)")
        );
        const Type::StringPair pt10_name = std::make_pair(
          m_input.MakeHistName(variable, iPt10, tag + "PP_"),
          m_input.MakeHistName(variable, iPt10, tag + "PAu_")
        );
        const Type::StringPair pt15_name = std::make_pair(
          m_input.MakeHistName(variable, iPt15, tag + "PP_"),
          m_input.MakeHistName(variable, iPt15, tag + "PAu_")
        );

        // set up pp vs. p+Au indices
        Type::PlotIndex iPt5pp  = iPt5;
        Type::PlotIndex iPt5pa  = iPt5;
        Type::PlotIndex iPt10pp = iPt10;
        Type::PlotIndex iPt10pa = iPt10;
        Type::PlotIndex iPt15pp = iPt15;
        Type::PlotIndex iPt15pa = iPt15;
        iPt5pp.species  = FileInput::PP;
        iPt5pa.species  = FileInput::PAu;
        iPt10pp.species = FileInput::PP;
        iPt10pa.species = FileInput::PAu;
        iPt15pp.species = FileInput::PP;
        iPt15pa.species = FileInput::PAu;

        // build hist legends
        const Type::StringPair pt5_leg  = std::make_pair(
          m_input.MakeLegend(iPt5pp),
          m_input.MakeLegend(iPt5pa)
        );
        const Type::StringPair pt10_leg = std::make_pair(
          m_input.MakeLegend(iPt10pp),
          m_input.MakeLegend(iPt10pa)
        );
        const Type::StringPair pt15_leg = std::make_pair(
          m_input.MakeLegend(iPt15pp),
          m_input.MakeLegend(iPt15pa)
        );

        // bundle input options
        Type::InputPair pt5_opt = std::make_pair(
          PlotInput(
            m_input.GetFiles().GetFile(iPt5pp),
            pt5_hist,
            pt5_name.first,
            pt5_leg.first,
            "",
            Style::Plot(
              pt5_col.first,
              pt5_mar.first
            )
          ),
          PlotInput(
            m_input.GetFiles().GetFile(iPt5pa),
            pt5_hist,
            pt5_name.second,
            pt5_leg.second,
            "",
            Style::Plot(
              pt5_col.second,
              pt5_mar.second
            )
          )
        );
        Type::InputPair pt10_opt = std::make_pair(
          PlotInput(
            m_input.GetFiles().GetFile(iPt10pp),
            pt10_hist,
            pt10_name.first,
            pt10_leg.first,
            "",
            Style::Plot(
              pt10_col.first,
              pt10_mar.first
            )
          ),
          PlotInput(
            m_input.GetFiles().GetFile(iPt10pa),
            pt10_hist,
            pt10_name.second,
            pt10_leg.second,
            "",
            Style::Plot(
              pt10_col.second,
              pt10_mar.second
            )
          )
        );
        Type::InputPair pt15_opt = std::make_pair(
          PlotInput(
            m_input.GetFiles().GetFile(iPt15pp),
            pt15_hist,
            pt15_name.first,
            pt15_leg.first,
            "",
            Style::Plot(
              pt15_col.first,
              pt15_mar.first
            )
          ),
          PlotInput(
            m_input.GetFiles().GetFile(iPt15pa),
            pt15_hist,
            pt15_name.second,
            pt15_leg.second,
            "",
            Style::Plot(
              pt15_col.second,
              pt15_mar.second
            )
          )
        );

        // load denominators
        std::vector<PlotInput> denominator;
        denominator.push_back( pt5_opt.first );
        denominator.push_back( pt10_opt.first );
        denominator.push_back( pt15_opt.first );

        // load numerators
        std::vector<PlotInput> numerator;
        numerator.push_back( pt5_opt.second );
        numerator.push_back( pt10_opt.second );
        numerator.push_back( pt15_opt.second );

        // make plot
        m_maker.GetPlotRatios1D().Configure(denominator, numerator, canvas, opt);
        m_maker.GetPlotRatios1D().Plot(ofile);
        return;

      }  // end 'PPVsPAu1D(std::string&, int, TFile*)'

      // ----------------------------------------------------------------------
      //! Make 1D corrected spectrum plot
      // ----------------------------------------------------------------------
      void CorrectSpectra1D(const std::string& variable, const int opt, TFile* ofile) {

        // constrain level, pt indices
        Type::PlotIndex iPt5data = m_index;
        Type::PlotIndex iPt5reco = m_index;
        Type::PlotIndex iPt5true = m_index;
        iPt5data.pt    = HistInput::Pt5;
        iPt5data.level = FileInput::Data;
        iPt5reco.pt    = HistInput::Pt5;
        iPt5reco.level = FileInput::Reco;
        iPt5true.pt    = HistInput::Pt5;
        iPt5true.level = FileInput::True;

        Type::PlotIndex iPt10data = m_index;
        Type::PlotIndex iPt10reco = m_index;
        Type::PlotIndex iPt10true = m_index;
        iPt10data.pt    = HistInput::Pt10;
        iPt10data.level = FileInput::Data;
        iPt10reco.pt    = HistInput::Pt10;
        iPt10reco.level = FileInput::Reco;
        iPt10true.pt    = HistInput::Pt10;
        iPt10true.level = FileInput::True;

        Type::PlotIndex iPt15data = m_index;
        Type::PlotIndex iPt15reco = m_index;
        Type::PlotIndex iPt15true = m_index;
        iPt15data.pt    = HistInput::Pt15;
        iPt15data.level = FileInput::Data;
        iPt15reco.pt    = HistInput::Pt15;
        iPt15reco.level = FileInput::Reco;
        iPt15true.pt    = HistInput::Pt15;
        iPt15true.level = FileInput::True;

        // colors for diferent jet pt
        const std::size_t pt5_col[3]  = {799, 797, 809};
        const std::size_t pt10_col[3] = {899, 909, 907};
        const std::size_t pt15_col[3] = {889, 879, 877};

        // markers for different jet pt
        const std::size_t pt5_mar[3]  = {22, 22, 26};
        const std::size_t pt10_mar[3] = {20, 24, 24};
        const std::size_t pt15_mar[3] = {23, 23, 32};

        // make canvas name and tag
        const std::string tag    = m_input.MakeSpeciesTag("Correct1D", m_index.species) + "_";
        const std::string canvas = m_input.MakeCanvasName("cCorrect" + variable, m_index);

        // build data hist names
        const std::string pt5_dhist  = m_input.MakeHistName(variable, iPt5data);
        const std::string pt10_dhist = m_input.MakeHistName(variable, iPt10data);
        const std::string pt15_dhist = m_input.MakeHistName(variable, iPt15data);

        // build reco hist names
        const std::string pt5_rhist  = m_input.MakeHistName(variable, iPt5reco);
        const std::string pt10_rhist = m_input.MakeHistName(variable, iPt10reco);
        const std::string pt15_rhist = m_input.MakeHistName(variable, iPt15reco);

        // build true hist names
        const std::string pt5_thist  = m_input.MakeHistName(variable, iPt5true);
        const std::string pt10_thist = m_input.MakeHistName(variable, iPt10true);
        const std::string pt15_thist = m_input.MakeHistName(variable, iPt15true);

        // build hist renames
        const std::string pt5_name[3] = {
          m_input.MakeHistName(variable, iPt5data, tag),
          m_input.MakeHistName(variable, iPt5reco, tag),
          m_input.MakeHistName(variable, iPt5true, tag)
        };
        const std::string pt10_name[3] = {
          m_input.MakeHistName(variable, iPt10data, tag),
          m_input.MakeHistName(variable, iPt10reco, tag),
          m_input.MakeHistName(variable, iPt10true, tag)
        };
        const std::string pt15_name[3] = {
          m_input.MakeHistName(variable, iPt15data, tag),
          m_input.MakeHistName(variable, iPt15reco, tag),
          m_input.MakeHistName(variable, iPt15true, tag)
        };

        // build hist legends
        const std::string pt5_leg[3] = {
          m_input.MakeLegend(iPt5data),
          m_input.MakeLegend(iPt5reco),
          m_input.MakeLegend(iPt5true)
        };
        const std::string pt10_leg[3] = {
          m_input.MakeLegend(iPt10data),
          m_input.MakeLegend(iPt10reco),
          m_input.MakeLegend(iPt10true)
        };
        const std::string pt15_leg[3] = {
          m_input.MakeLegend(iPt15data),
          m_input.MakeLegend(iPt15reco),
          m_input.MakeLegend(iPt15true)
        };

        // bundle input data options
        Type::Inputs data_opt;
        data_opt.push_back(
          PlotInput(
            m_input.GetFiles().GetFile(iPt5data),
            pt5_dhist,
            pt5_name[0],
            pt5_leg[0],
            "",
            Style::Plot(
              pt5_col[0],
              pt5_mar[0]
            )
          )
        );
        data_opt.push_back(
          PlotInput(
            m_input.GetFiles().GetFile(iPt10data),
            pt10_dhist,
            pt10_name[0],
            pt10_leg[0],
            "",
            Style::Plot(
              pt10_col[0],
              pt10_mar[0]
            )
          )
        );
        data_opt.push_back(
          PlotInput(
            m_input.GetFiles().GetFile(iPt15data),
            pt15_dhist,
            pt15_name[0],
            pt15_leg[0],
            "",
            Style::Plot(
              pt15_col[0],
              pt15_mar[0]
            )
          )
        );

        // bundle input reco options
        Type::Inputs reco_opt;
        reco_opt.push_back(
          PlotInput(
            m_input.GetFiles().GetFile(iPt5reco),
            pt5_rhist,
            pt5_name[1],
            pt5_leg[1],
            "",
            Style::Plot(
              pt5_col[1],
              pt5_mar[1]
            )
          )
        );
        reco_opt.push_back(
          PlotInput(
            m_input.GetFiles().GetFile(iPt10reco),
            pt10_rhist,
            pt10_name[1],
            pt10_leg[1],
            "",
            Style::Plot(
              pt10_col[1],
              pt10_mar[1]
            )
          )
        );
        reco_opt.push_back(
          PlotInput(
            m_input.GetFiles().GetFile(iPt15reco),
            pt15_rhist,
            pt15_name[1],
            pt15_leg[1],
            "",
            Style::Plot(
              pt15_col[1],
              pt15_mar[1]
            )
          )
        );

        // bundle input true options
        Type::Inputs true_opt;
        true_opt.push_back(
          PlotInput(
            m_input.GetFiles().GetFile(iPt5true),
            pt5_thist,
            pt5_name[2],
            pt5_leg[2],
            "",
            Style::Plot(
              pt5_col[2],
              pt5_mar[2]
            )
          )
        );
        true_opt.push_back(
          PlotInput(
            m_input.GetFiles().GetFile(iPt10true),
            pt10_thist,
            pt10_name[2],
            pt10_leg[2],
            "",
            Style::Plot(
              pt10_col[2],
              pt10_mar[2]
            )
          )
        );
        true_opt.push_back(
          PlotInput(
            m_input.GetFiles().GetFile(iPt15true),
            pt15_thist,
            pt15_name[2],
            pt15_leg[2],
            "",
            Style::Plot(
              pt15_col[2],
              pt15_mar[2]
            )
          )
        );

        // make plot
        m_maker.GetCorrectSpectra1D().Configure(data_opt, reco_opt, true_opt, canvas, opt);
        m_maker.GetCorrectSpectra1D().Plot(ofile);
        return;

      }  // end 'CorrectSpectra1D(std::string&, int, TFile*)'

      // ------------------------------------------------------------------------
      // default ctor/dtor
      // ------------------------------------------------------------------------
      Output()  {};
      ~Output() {};

  };  // end output

}  // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================
