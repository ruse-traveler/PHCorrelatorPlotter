/// ===========================================================================
/*! \file    PHCorrelatorPPVsPAu.h
 *  \authors Derek Anderson
 *  \date    05.04.2025
 *
 *  Output wiring to make sim vs. data plots
 */
/// ===========================================================================

#ifndef PHCORRELATORPPVSPAU_H
#define PHCORRELATORPPVSPAU_H

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
  //! p+p vs. p+Au Output Wiring
  // ==========================================================================
  /*! Wiring to create a plot of p+p spectra
   *  vs. p+Au spectra.
   */
  class PPVsPAu : public BaseOutput {

    public:

      // ----------------------------------------------------------------------
      //! Make 1D p+p vs. p+Au Plot
      // ----------------------------------------------------------------------
      /*! Wiring to make a 1D p+p vs. p+Au plot.
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

      }  // end 'MakePlot1D(std::string&, int, TFile*)'

      // ----------------------------------------------------------------------
      //! Make 2D p+p vs. p+Au Plot
      // ----------------------------------------------------------------------
      /*! Wiring to make a 2D p+p vs. p+Au plot.
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
      PPVsPAu()  {};
      ~PPVsPAu() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      PPVsPAu(const Type::PlotIndex& index, const PlotMaker& maker, const Input& input)
        : BaseOutput(index, maker, input) {};

  };  // end PPVsPAu

}  // end PHEnergyCorrelator namesapce

#endif

/// end =======================================================================
