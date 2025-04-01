/// ===========================================================================
/*! \file    PHCorrelatorPlotOpts.h
 *  \authors Derek Anderson
 *  \date    01.11.2025
 *
 *  Definition of plotter options for plotter routines.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTOPTS_H
#define PHCORRELATORPLOTOPTS_H

// c++ utilities
#include <string>
// plotting utilities
#include "PHCorrelatorCanvas.h"
#include "PHCorrelatorRange.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Auxilliary options for plotter routines
  // ==========================================================================
  /*! A small struct to consolidate misc. options
   *  common to all or several plotting routines,
   *  i.e. a superset of such options.
   */  
  struct PlotOpts {

    // members
    std::string header;       ///!< legend header
    std::string ratio_pad;    ///!< label of pad to draw ratios in
    std::string spectra_pad;  ///!< label of pad to draw spectra in
    std::string correct_pad;  ///!< label of pad to draw correction factors in
    Canvas      canvas;       ///!< definition of canvas/pads
    Range       plot_range;   ///!< (x, y, z) ranges to plot over
    Range       norm_range;   ///!< (x, y, z) ranges to normalize to
    double      norm_to;      ///!< what value you're normalizing to
    bool        do_norm;      ///!< do or do not normalize

    // ------------------------------------------------------------------------
    //! default ctor
    // ------------------------------------------------------------------------
    PlotOpts() {
      header      = "";
      ratio_pad   = "";
      spectra_pad = "";
      correct_pad = "";
      canvas      = Canvas();
      plot_range  = Range();
      norm_range  = Range();
      norm_to     = 1.0;
      do_norm     = true;
    };

    // ------------------------------------------------------------------------
    //! default dtor
    // ------------------------------------------------------------------------
    ~PlotOpts() {};

    // ------------------------------------------------------------------------
    //! ctor accepting all arguments
    // ------------------------------------------------------------------------
    PlotOpts(
      const Canvas& canvas_arg,
      const Range& plot_range_arg,
      const Range& norm_range_arg,
      const bool do_norm_arg = true,
      const double norm_to_arg = 1.0,
      const std::string header_arg = "",
      const std::string ratio_arg = "",
      const std::string spectra_arg = "",
      const std::string correct_arg = ""
    ) {
      canvas      = canvas_arg;
      plot_range  = plot_range_arg;
      norm_range  = norm_range_arg;
      do_norm     = do_norm_arg;
      norm_to     = norm_to_arg;
      header      = header_arg;
      ratio_pad   = ratio_arg;
      spectra_pad = spectra_arg;
      correct_pad = correct_arg;
    }  // end ctor()

  };  // end PlotOpts

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
