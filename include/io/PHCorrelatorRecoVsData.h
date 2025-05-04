/// ===========================================================================
/*! \file    PHCorrelatorRecoVsData.h
 *  \authors Derek Anderson
 *  \date    05.04.2025
 *
 *  Output wiring to make sim vs. data plots
 */
/// ===========================================================================

#ifndef PHCORRELATORRECOVSDATA_H
#define PHCORRELATORRECOVSDATA_H

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
  class RecoVsData : BaseOutput {

    public:

      // ----------------------------------------------------------------------
      //! Make 1D Reco vs. Data Plot
      // ----------------------------------------------------------------------
      /*! Wiring to make a 1D reco vs. data plot.
       *
       *  \param variable what variable (spectra) is being plotted
       *  \param opt      what axis option to use
       *  \param ofile    what file to write output to 
       */ 
      void MakePlot1D(const std::string& variable, const int opt, TFile* ofile) {

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

      }  // end 'MakePlot1D(std::string&, int, TFile*)'

      // ----------------------------------------------------------------------
      //! Make 2D Reco vs. Data Plot
      // ----------------------------------------------------------------------
      /*! Wiring to make a 2D reco vs. data plot.
       *
       *  \param variable what variable (spectra) is being plotted
       *  \param ofile    what file to write output to 
       */ 
      void MakePlot2D(const std::string& variable, TFile* ofile) {

        /* TODO fill in */
        return;

      }  // end 'MakePlot2D(std::string&, TFile*)' 

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      RecoVsData()  {};
      ~RecoVsData() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      explicit RecoVsData(const Type::PlotIndex& index, const PlotMaker& maker, const Input& input)
        : BaseOutput(index, maker, input) {};

  };  // end RecoVsData

}  // end PHEnergyCorrelator namesapce

#endif

/// end =======================================================================
