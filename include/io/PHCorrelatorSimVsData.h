/// ===========================================================================
/*! \file    PHCorrelatorSimVsData.h
 *  \authors Derek Anderson
 *  \date    05.04.2025
 *
 *  Output wiring to make sim vs. data plots
 */
/// ===========================================================================

#ifndef PHCORRELATORSIMVSDATA_H
#define PHCORRELATORSIMVSDATA_H

// c++ utilities
#include <string>
#include <vector>
// root libraries
#include <TFile.h>
// plotting utilities
#include "PHCorrelatorBaseOutput.h"
#include "PHCorrelatorIOTypes.h"
#include "../elements/PHCorrelatorPlotterElements.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Sim vs. Data Output Wiring
  // ==========================================================================
  /*! Wiring to create a plot of simulated spectra
   *  vs. spectra in data.
   */
  class SimVsData : public BaseOutput {

    public:

      // ----------------------------------------------------------------------
      //! Make 1D Sim vs. Data Plot
      // ----------------------------------------------------------------------
      /*! Wiring to make a 1D sim vs. data plot.
       *
       *  \param variable what variable (spectra) is being plotted
       *  \param opt      what axis option to use
       *  \param ofile    what file to write output to 
       *  \param nrebin   what number of bins to merge if rebinning
       */
      void MakePlot1D(const std::string& variable, const int opt, TFile* ofile, const int nrebin = 1) {

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
          ),
          GetRebin(nrebin, opt)
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
          ),
          GetRebin(nrebin, opt)
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
          ),
          GetRebin(nrebin, opt)
        );

        // load into vector
        std::vector<PlotInput> num_input;
        num_input.push_back( dat_opt );
        num_input.push_back( rec_opt );

        // make plot
        m_maker.GetPlotVsBaseline1D().Configure(tru_opt, num_input, canvas, opt);
        m_maker.GetPlotVsBaseline1D().Plot(ofile);
        return;

      }  // end 'MakePlot1D(std::string&, int, TFile*)'

      // ----------------------------------------------------------------------
      //! Make 2D Sim vs. Data Plot
      // ----------------------------------------------------------------------
      /*! Wiring to make a 2D sim vs. data plot.
       *
       *  \param variable what variable (spectra) is being plotted
       *  \param ofile    what file to write output to 
       */ 
      void MakePlot2D(const std::string& variable, TFile* ofile) {

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

      }  // end 'MakePlot2D(std::string&, TFile*)' 

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      SimVsData()  {};
      ~SimVsData() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      SimVsData(const Type::PlotIndex& index, const PlotMaker& maker, const Input& input)
        : BaseOutput(index, maker, input) {};

  };  // end SimVsData

}  // end PHEnergyCorrelator namesapce

#endif

/// end =======================================================================
