/// ===========================================================================
/*! \file    PHCorrelatorSpinRatios.h
 *  \authors Derek Anderson
 *  \date    05.09.2025
 *
 *  Output wiring to make spin ratio plots
 */
/// ===========================================================================

#ifndef PHCORRELATORSPINRATIOS_H
#define PHCORRELATORSPINRATIOS_H

// c++ utilities
#include <string>
#include <vector>
#include <utility>
// root libraries
#include <TFile.h>
// plotting utilities
#include "PHCorrelatorBaseOutput.h"
#include "PHCorrelatorIOTypes.h"
#include "../elements/PHCorrelatorPlotterElements.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Spin Ratios Output Wiring
  // ==========================================================================
  /*! Wiring to create a plot of spin ratios.
   */
  class SpinRatios : public BaseOutput {

    public:

      // ----------------------------------------------------------------------
      //! Make 1D spin ratios plot
      // ----------------------------------------------------------------------
      /*! Wiring to make a 1D spin ratios plot.
       *
       *  \param variable what variable (spectra) is being plotted
       *  \param opt      what axis option to use
       *  \param ofile    what file to write output to 
       */ 
      void MakePlot1D(const std::string& variable, const int opt, TFile* ofile) {

        // TODO combos to hit:
        //   - BD/YU
        //   - BU/YD
        //   - any others?

        // replicate indices and constrain levels
        Type::PlotIndex iData = m_index;
        Type::PlotIndex iReco = m_index;
        Type::PlotIndex iTrue = m_index;
        iData.level = FileInput::Data;
        iReco.level = FileInput::Reco;
        iTrue.level = FileInput::True;

        // load up combos of spins to make ratios of
        //   - first  = numerator
        //   - second = denominator
        std::vector<std::pair<int, int> > spins;
        spins.push_back( std::make_pair(HistInput::BD, HistInput::YU) );
        spins.push_back( std::make_pair(HistInput::BU, HistInput::YD) );

        // additional tags for canvas name
        std::vector<std::string> spin_can;
        spin_can.push_back("BDDivYU");
        spin_can.push_back("BUDivYD");

        // colors for different levels
        std::pair<std::size_t, std::size_t> dat_col = std::make_pair(898, 899);
        std::pair<std::size_t, std::size_t> rec_col = std::make_pair(858, 859);
        std::pair<std::size_t, std::size_t> tru_col = std::make_pair(921, 923);

        // markers for different levels
        std::pair<std::size_t, std::size_t> dat_mar = std::make_pair(24, 20);
        std::pair<std::size_t, std::size_t> rec_mar = std::make_pair(25, 21);
        std::pair<std::size_t, std::size_t> tru_mar = std::make_pair(30, 29);

        // now loop through combos and make plots
        for (std::size_t isp = 0; isp < spins.size(); ++isp) {

          // replicate indices and constrain spins
          Type::PlotIndex iDatNum = iData;
          Type::PlotIndex iDatDen = iData;
          iDatNum.spin = spins[isp].first;
          iDatDen.spin = spins[isp].second;

          Type::PlotIndex iRecNum = iReco;
          Type::PlotIndex iRecDen = iReco;
          iRecNum.spin = spins[isp].first;
          iRecDen.spin = spins[isp].second;

          Type::PlotIndex iTruNum = iTrue;
          Type::PlotIndex iTruDen = iTrue;
          iTruNum.spin = spins[isp].first;
          iTruDen.spin = spins[isp].second;

          // make canvas name and tag
          const std::string tag    = m_input.MakeSpeciesTag("SpinRatio", m_index.species) + "_";
          const std::string canvas = m_input.MakeCanvasName("cSpinRatio" + spin_can[isp] + variable, m_index);

          // build hist names
          const std::pair<std::string, std::string> dat_hist = std::make_pair(
            m_input.MakeHistName(variable, iDatNum),
            m_input.MakeHistName(variable, iDatDen)
          );
          const std::pair<std::string, std::string> rec_hist = std::make_pair(
            m_input.MakeHistName(variable, iRecNum),
            m_input.MakeHistName(variable, iRecDen)
          );
          const std::pair<std::string, std::string> tru_hist = std::make_pair(
            m_input.MakeHistName(variable, iTruNum),
            m_input.MakeHistName(variable, iTruDen)
          );

          // build hist renames
          const std::pair<std::string, std::string> dat_name = std::make_pair(
            m_input.MakeHistName(variable, iDatNum, tag),
            m_input.MakeHistName(variable, iDatDen, tag)
          );
          const std::pair<std::string, std::string> rec_name = std::make_pair(
            m_input.MakeHistName(variable, iRecNum, tag),
            m_input.MakeHistName(variable, iRecDen, tag)
          );
          const std::pair<std::string, std::string> tru_name = std::make_pair(
            m_input.MakeHistName(variable, iTruNum, tag),
            m_input.MakeHistName(variable, iTruDen, tag)
          );

          // build hist legends
          const std::pair<std::string, std::string> dat_leg = std::make_pair(
            m_input.MakeLegend(iDatNum),
            m_input.MakeLegend(iDatDen)
          );
          const std::pair<std::string, std::string> rec_leg = std::make_pair(
            m_input.MakeLegend(iRecNum),
            m_input.MakeLegend(iRecDen)
          );
          const std::pair<std::string, std::string> tru_leg = std::make_pair(
            m_input.MakeLegend(iTruNum),
            m_input.MakeLegend(iTruDen)
          );

          // bundle input options
          std::vector<PlotInput> in_nums;
          in_nums.push_back(
            PlotInput(
              m_input.GetFiles().GetFile(iDatNum),
              dat_hist.first,
              dat_name.first,
              dat_leg.first,
              "",
              Style::Plot(
                dat_col.first,
                dat_mar.first
              )
            )
          );
          in_nums.push_back(
            PlotInput(
              m_input.GetFiles().GetFile(iRecNum),
              rec_hist.first,
              rec_name.first,
              rec_leg.first,
              "",
              Style::Plot(
                rec_col.first,
                rec_mar.first
              )
            )
          );
          in_nums.push_back(
            PlotInput(
              m_input.GetFiles().GetFile(iTruNum),
              tru_hist.first,
              tru_name.first,
              tru_leg.first,
              "",
              Style::Plot(
                tru_col.first,
                tru_mar.first
              )
            )
          );

          std::vector<PlotInput> in_dens;
          in_dens.push_back(
            PlotInput(
              m_input.GetFiles().GetFile(iDatDen),
              dat_hist.second,
              dat_name.second,
              dat_leg.second,
              "",
              Style::Plot(
                dat_col.second,
                dat_mar.second
              )
            )
          );
          in_dens.push_back(
            PlotInput(
              m_input.GetFiles().GetFile(iRecDen),
              rec_hist.second,
              rec_name.second,
              rec_leg.second,
              "",
              Style::Plot(
                rec_col.second,
                rec_mar.second
              )
            )
          );
          in_dens.push_back(
            PlotInput(
              m_input.GetFiles().GetFile(iTruDen),
              tru_hist.second,
              tru_name.second,
              tru_leg.second,
              "",
              Style::Plot(
                tru_col.second,
                tru_mar.second
              )
            )
          );

          // make plot
          m_maker.GetPlotRatios1D().Configure(in_dens, in_nums, canvas, opt);
          m_maker.GetPlotRatios1D().Plot(ofile);
        }
        return;

      }  // end 'MakePlot1D(std::string&, int, TFile*)'

      // ----------------------------------------------------------------------
      //! Make 2D spin ratios plot
      // ----------------------------------------------------------------------
      /*! Wiring to make a 2D spin ratios plot.
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
      SpinRatios()  {};
      ~SpinRatios() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      SpinRatios(const Type::PlotIndex& index, const PlotMaker& maker, const Input& input)
        : BaseOutput(index, maker, input) {};

  };  // end SpinRatios

}  // end PHEnergyCorrelator namesapce

#endif

/// end =======================================================================

