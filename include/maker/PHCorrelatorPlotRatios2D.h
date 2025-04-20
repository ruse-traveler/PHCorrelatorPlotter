/// ===========================================================================
/*! \file    PHCorrelatorPlotRatios2D.h
 *  \authors Derek Anderson
 *  \date    04.19.2024
 *
 *  PlotMaker routine to plot various pairs of 2D
 *  spectra and their ratios.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTRATIOS2D_H
#define PHCORRELATORPLOTRATIOS2D_H

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
#include "PHCorrelatorPlotMakerTypes.h"
#include "PHCorrelatorPlotRatios1D.h"
#include "../elements/PHCorrelatorPlotterElements.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! 1D Ratio Plotting Routine
  // ==========================================================================
  /*! Routine to plot various pairs of 1D spectra
   *  and their ratios on two panels.
   */
  class PlotRatios2D : public BaseRoutine {

    public:

      // ======================================================================
      //! Parameters for plotting 2D ratios (same as 1D routine)
      // ======================================================================
      typedef PlotRatios1D::Params Params;

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
      //! Plot various pairs of 2D ENC (or otherwise) spectra and their ratios
      // ----------------------------------------------------------------------
      /*! Compares a variety of pairs of 1D ENC (or otherwise) spectra from
       *  different sources and their ratios. Upper panel shows spectra,
       *  lower panel shows ratios.
       *
       *  \param[out] ofile file to write to
       */
      void Plot(TFile* ofile) const {

        /* TODO fill in here... */

      }  // end 'Plot(TFile*)'

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      PlotRatios2D()  {};
      ~PlotRatios2D() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      explicit PlotRatios2D(const Style& plot, const Style& text, const TextBox& box)
        : BaseRoutine(plot, text, box) {};

  };  // end PlotRatios2D

}    // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================
