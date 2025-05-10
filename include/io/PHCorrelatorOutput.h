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
#include <map>
#include <string>
#include <utility>
#include <vector>
// root libraries
#include <TFile.h>
// plotting utilities
#include "PHCorrelatorBaseOutput.h"
#include "PHCorrelatorCorrectSpectra.h"
#include "PHCorrelatorInput.h"
#include "PHCorrelatorIOTypes.h"
#include "PHCorrelatorPlotIndexVector.h"
#include "PHCorrelatorPPVsPAu.h"
#include "PHCorrelatorRecoVsData.h"
#include "PHCorrelatorSimVsData.h"
#include "PHCorrelatorSpinRatios.h"
#include "PHCorrelatorVsPtJet.h"
#include "../elements/PHCorrelatorPlotterElements.h"
#include "../maker/PHCorrelatorPlotMaker.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Plotting Output
  // ==========================================================================
  /*! A class to apply the generic routines of PHEC::PlotMaker
   *  to the inputs deined by PHEC::Input.
   */
  class Output : public BaseOutput {

    public:

      // enumerate outputs
      struct Plots {
        enum EnuPlots {SimVsData, RecoVsData, VsPtJet, PPVsPAu, CorrectSpectra, SpinRatios};
      };

      // for working with map of wirings
      typedef std::map<std::string, BaseOutput*> Wirings;
      typedef std::map<std::string, BaseOutput*>::iterator it_wire;

    private:

      // data members
      bool    m_isInit;
      Wirings m_outputs;

      // ----------------------------------------------------------------------
      //! Initialize wirings
      // ----------------------------------------------------------------------
      void InitWirings() {

        m_outputs["VsPtJet"]        = new VsPtJet(m_index, m_maker, m_input);
        m_outputs["SpinRatios"]     = new SpinRatios(m_index, m_maker, m_input);
        m_outputs["SimVsData"]      = new SimVsData(m_index, m_maker, m_input);
        m_outputs["RecoVsData"]     = new RecoVsData(m_index, m_maker, m_input);
        m_outputs["PPVsPAu"]        = new PPVsPAu(m_index, m_maker, m_input);
        m_outputs["CorrectSpectra"] = new CorrectSpectra(m_index, m_maker, m_input);
        return;

      }  // end 'InitWirings()'

    public:

      // ----------------------------------------------------------------------
      //! Update a plot index
      // ----------------------------------------------------------------------
      /*! FIXME should factorize index, maker, etc. so
       *  so that this gets updated ONCE rather than
       *  for every routine.
       */
      void UpdateIndex(const Type::PlotIndex& index) {

        for (it_wire output = m_outputs.begin(); output != m_outputs.end(); ++output) {
          (output -> second) -> SetIndex(index);
        }
        return;

      }  // end 'UpdateIndex(Type::PlotIndex&)'

      // ----------------------------------------------------------------------
      //! Initialize output
      // ----------------------------------------------------------------------
      /*! Note that calling after using the ctor accepting
       *  arguments does nothing. If using the default ctor,
       *  this should be called after setting data members
       *  (e.g. `SetInput(...)`) to initialize wirings.
       */
      void Init() {

        if (!m_isInit) {
          InitWirings();
          m_isInit = true;
        }
        return;

      }  // end 'Init()'

      // ----------------------------------------------------------------------
      //! Access a particular output
      // ----------------------------------------------------------------------
      BaseOutput* operator [](const std::string& name) {

        return m_outputs.at(name);

      }  // end '[](std::string&)'

      // ----------------------------------------------------------------------
      //! Default ctor
      // ----------------------------------------------------------------------
      Output() : m_isInit(false) {};

      // ----------------------------------------------------------------------
      //! Default dtor
      // ----------------------------------------------------------------------
      ~Output() {

        for (it_wire output = m_outputs.begin(); output != m_outputs.end(); ++output) {
          if (output -> second) {
            delete output -> second;
          }
          m_outputs.erase(output);
        }

      }  // end dtor

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      Output(
        const Type::PlotIndex& index,
        const PlotMaker& maker,
        const Input& input
      ) {

        // set members
        m_index = index;
        m_maker = maker;
        m_input = input;

        // initialize output wirings
        InitWirings();
        m_isInit = true;

      }  // end 'ctor(Type::PlotIndex&, PlotMaker&, Input&)'

  };  // end output

}  // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================
