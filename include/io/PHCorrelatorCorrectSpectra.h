/// ===========================================================================
/*! \file    PHCorrelatorCorrectSpectra.h
 *  \authors Derek Anderson
 *  \date    05.04.2025
 *
 *  Output wiring to make sim vs. data plots
 */
/// ===========================================================================

#ifndef PHCORRELATORCORRECTSPECTRA_H
#define PHCORRELATORCORRECTSPECTRA_H

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
  //! Corrected Spectra Output Wiring
  // ==========================================================================
  /*! Wiring to create a plot of corrected spectra.
   */
  class CorrectSpectra : BaseOutput {

    public:

      // ----------------------------------------------------------------------
      //! Make 1D Corrected Spectra Plot
      // ----------------------------------------------------------------------
      /*! Wiring to make a 1D corrected spectra plot.
       *
       *  \param variable what variable (spectra) is being plotted
       *  \param opt      what axis option to use
       *  \param ofile    what file to write output to 
       */ 
      void MakePlot1D(const std::string& variable, const int opt, TFile* ofile) {

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

      }  // end 'MakePlot1D(std::string&, int, TFile*)'

      // ----------------------------------------------------------------------
      //! Make 2D Corrected Spectra Plot
      // ----------------------------------------------------------------------
      /*! Wiring to make a 2D corrected spectra plot.
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
      CorrectSpectra()  {};
      ~CorrectSpectra() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      explicit CorrectSpectra(const Type::PlotIndex& index, const PlotMaker& maker, const Input& input)
        : BaseOutput(index, maker, input) {};

  };  // end CorrectSpectra

}  // end PHEnergyCorrelator namesapce

#endif

/// end =======================================================================
