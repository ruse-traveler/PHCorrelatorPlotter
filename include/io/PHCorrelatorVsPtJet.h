/// ===========================================================================
/*! \file    PHCorrelatorVsPtJet.h
 *  \authors Derek Anderson
 *  \date    05.04.2025
 *
 *  Output wiring to make sim vs. data plots
 */
/// ===========================================================================

#ifndef PHCORRELATORVSPTJET_H
#define PHCORRELATORVSPTJET_H

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
  //! Vs. PtJet Output Wiring
  // ==========================================================================
  /*! Wiring to create a plot of spectra vs. ptJet.
   */
  class VsPtJet : BaseOutput {

    public:

      // ----------------------------------------------------------------------
      //! Make 1D Spectra vs. PtJet Plot
      // ----------------------------------------------------------------------
      /*! Wiring to make a 1D spectra vs. ptJet plot.
       *
       *  \param variable what variable (spectra) is being plotted
       *  \param opt      what axis option to use
       *  \param ofile    what file to write output to 
       */ 
      void MakePlot1D(const std::string& variable, const int opt, TFile* ofile) {

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

      }  // end 'MakePlot1D(std::string&, int, TFile*)'

      // ----------------------------------------------------------------------
      //! Make 2D spectra vs. PtJet Plot
      // ----------------------------------------------------------------------
      /*! Wiring to make a 2D spectra vs.ptJet plot.
       *
       *  \param variable what variable (spectra) is being plotted
       *  \param ofile    what file to write output to 
       */ 
      void MakePlot2D(const std::string& variable, TFile* ofile) {

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

      }  // end 'MakePlot2D(std::string&, TFile*)' 

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      VsPtJet()  {};
      ~VsPtJet() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      explicit VsPtJet(const Type::PlotIndex& index, const PlotMaker& maker, const Input& input)
        : BaseOutput(index, maker, input) {};

  };  // end VsPtJet

}  // end PHEnergyCorrelator namesapce

#endif

/// end =======================================================================
