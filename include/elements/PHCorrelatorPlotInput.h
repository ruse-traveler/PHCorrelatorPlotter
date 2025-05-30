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
#include "PHCorrelatorRebin.h"
#include "PHCorrelatorStyle.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Plot input
  // ==========================================================================
  /*! A small struct to consolidate input for
   *  plotting routines
   */
  struct PlotInput {

    std::string file;    ///!< file where object is
    std::string object;  ///!< object to be plotted
    std::string rename;  ///!< rename object to this
    std::string legend;  ///!< legend entry
    std::string draw;    ///!< draw option
    Style::Plot style;   ///!< marker, line, and fill style
    Rebin       rebin;   ///!< do rebinning

    // ------------------------------------------------------------------------
    //! default ctor
    // ------------------------------------------------------------------------
    PlotInput() {
      file   = "";
      object = "";
      rename = "";
      legend = "";
      draw   = "";
      style  = Style::Plot();
      rebin  = Rebin();
    };

    // ------------------------------------------------------------------------
    //! default dtor
    // ------------------------------------------------------------------------
    ~PlotInput() {};

    // ------------------------------------------------------------------------
    //! ctor acceptingt arguments
    // ------------------------------------------------------------------------
    PlotInput(
      const std::string& farg,
      const std::string& oarg,
      const std::string& rarg,
      const std::string& larg,
      const std::string& darg,
      const Style::Plot& sarg = Style::Plot(),
      const Rebin& rearg = Rebin()
    ) {
      file   = farg;
      object = oarg;
      rename = rarg;
      legend = larg;
      draw   = darg;
      style  = sarg;
      rebin  = rearg;
    };  // end PlotInput(std::string& x 5, Style::Plot&, Rebin&)

  };  // end PlotInput

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
