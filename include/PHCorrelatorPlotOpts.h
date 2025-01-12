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
   *  common to plotting routine.
   */  
  struct PlotOpts {

    // members
    std::string header;
    Canvas      canvas;
    Range       plot_range;
    Range       norm_range;
    double      norm_to;
    bool        do_norm;

    // ------------------------------------------------------------------------
    //! default ctor
    // ------------------------------------------------------------------------
    PlotOpts() {
      header     = "";
      canvas     = Canvas();
      plot_range = Range();
      norm_range = Range();
      norm_to    = 1.0;
      do_norm    = true;
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
      const std::string header_arg = ""
    ) {
      canvas     = canvas_arg;
      plot_range = plot_range_arg;
      norm_range = norm_range_arg;
      do_norm    = do_norm_arg;
      norm_to    = norm_to_arg;
      header     = header_arg;
    }  // end ctor()

  };  // end PlotOpts

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
