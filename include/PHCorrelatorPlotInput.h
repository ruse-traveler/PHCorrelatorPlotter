/// ===========================================================================
/*! \file    PHCorrelatorPlotInput.h
 *  \authors Derek Anderson
 *  \date    12.27.2024
 *
 *  Definition of input for a plotting routine.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTINPUT_H
#define PHCORRELATORPLOTINPUT_H

// c++ utilities
#include <string>
// plotting utilities
#include "PHCorrelatorStyle.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! BHCal plot input
  // ==========================================================================
  /*! A small struct to consolidate input for
   *  plotting routines
   */
  struct PlotInput {

    std::string file;    ///!< file where object is
    std::string object;  ///!< object to be plotted
    std::string rename;  ///!< rename object to this
    std::string legend;  ///!< legend entry
    Style::Plot style;   ///!< marker, line, and fill style

    // ------------------------------------------------------------------------
    //! default ctor
    // ------------------------------------------------------------------------
    PlotInput() {
      file   = "";
      object = "";
      rename = "";
      legend = "";
      style  = Style::Plot();
    };

    // ------------------------------------------------------------------------
    //! default dtor
    // ------------------------------------------------------------------------
    ~PlotInput() {};

    // ------------------------------------------------------------------------
    //! ctor acceptingt arguments
    // ------------------------------------------------------------------------
    PlotInput(
      const std::string farg,
      const std::string oarg,
      const std::string rarg,
      const std::string larg,
      const Style::Plot sarg
    ) {
      file   = farg;
      object = oarg;
      rename = rarg;
      legend = larg;
      style  = sarg;
    };

  };  // end PlotInput

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
