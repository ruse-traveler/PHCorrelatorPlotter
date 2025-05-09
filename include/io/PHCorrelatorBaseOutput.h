/// ===========================================================================
/*! \file    PHCorrelatorBaseOutput.h
 *  \authors Derek Anderson
 *  \date    05.04.2025
 *
 *  Base output wiring for
 *  the PlotMaker.
 */
/// ===========================================================================

#ifndef PHCORRELATORBASEOUTPUT_H
#define PHCORRELATORBASEOUTPUT_H

// root libraries
#include <TFile.h>
// plotting utilities
#include "PHCorrelatorInput.h"
#include "PHCorrelatorIOTypes.h"
#include "../maker/PHCorrelatorPlotMaker.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Base Output Wiring
  // ==========================================================================
  /*! Base class for wiring in outputs from
   *  the PlotMaker.
   */
  class BaseOutput {

    protected:

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
      //! Make 1D output plot
      // ----------------------------------------------------------------------
      /*! Should be overwritten by derived wiring.
       */
      virtual void MakePlot1D(const std::string& /*variable*/, const int /*opt*/, TFile* /*ofile*/) {return;}

      // ----------------------------------------------------------------------
      //! Make 2D output plot
      // ----------------------------------------------------------------------
      /*! Should be overwritten by derived wiring.
       */
      virtual void MakePlot2D(const std::string& /*variable*/, TFile* /*ofile*/) {return;}

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      BaseOutput()  {};
      ~BaseOutput() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      explicit BaseOutput(
        const Type::PlotIndex& index,
        const PlotMaker& maker,
        const Input& input
      ) {

        m_index = index;
        m_maker = maker;
        m_input = input;

      }  // end ctor(Type::PlotIndex&, PlotMaker&, Input&)'

  };  // end BaseOutput

}    // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================
