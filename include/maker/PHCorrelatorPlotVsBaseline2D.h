/// ===========================================================================
/*! \file    PHCorrelatorPlotVsBaseline2D.h
 *  \authors Derek Anderson
 *  \date    04.25.2025
 *
 *  PlotMaker routine to plot various 2D spectra.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTVSBASELINE2D_H
#define PHCORRELATORPLOTVSBASELINE2D_H

// c++ utilities
#include <algorithm>
#include <cassert>
#include <iostream>
// root libraries
#include <TCanvas.h>
#include <TFile.h>
#include <TH1.h>
#include <TLegend.h>
#include <TPaveText.h>
// plotting utilities
#include "PHCorrelatorBaseRoutine.h"
#include "PHCorrelatorPlotMakerDefault.h"
#include "PHCorrelatorPlotMakerTools.h"
#include "PHCorrelatorPlotMakerTypes.h"
#include "PHCorrelatorPlotVsBaseline1D.h"
#include "../elements/PHCorrelatorPlotterElements.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! 2D Spectra vs. Baseline Plotting Routine
  // ==========================================================================
  /*! Routine to plot various 2D spectra
   *  vs.a baseline and their ratio.
   */
  class PlotVsBaseline2D : public BaseRoutine {

    public:

      // ======================================================================
      //! Parameters for plotting 2D spectra vs. baseline (same as 1D routine)
      // ======================================================================
      typedef PlotSpectra1D::Params Params;

    private:

      // members
      Params m_params;

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Params GetParams() const {return m_params;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetParams(const Params& params) {m_params = params;}

      // ----------------------------------------------------------------------
      //! Plot various ENC (or othwerise) spectra vs. a baseline
      // ----------------------------------------------------------------------
      /*! Compares a variety of 2D ENC (or otherwise) spectra from different
       *  sources to a baseline. Upper panel shows spectra, lower panel
       *  shows ratio of spectra to baseline.
       *
       *  \param[out] ofile file to write to
       */
      void Plot(TFile* ofile) const {

        /* TODO fill in */
        return;

      }  // end 'Plot(TFile*)'

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      PlotVsBaseline2D()  {};
      ~PlotVsBaseline2D() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      explicit PlotVsBaseline2D(const Style& plot, const Style& text, const TextBox& box)
        : BaseRoutine(plot, text, box) {};

  };  // end PlotVsBaseline2D

}    // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================

