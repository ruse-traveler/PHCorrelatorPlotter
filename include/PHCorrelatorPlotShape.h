/// ===========================================================================
/*! \file    PHCorrelatorPlotShape.h
 *  \authors Derek Anderson
 *  \date    02.03.2025
 *
 *  Definition of a shape to be plotted ruing a
 *  plotting routine.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTSHAPE_H
#define PHCORRELATORPLOTSHAPE_H

// c++ utilities
#include <string>
// plotting utilities
#include "PHCorrelatorShape.h"
#include "PHCorrelatorStyle.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Shape definition
  // ==========================================================================
  /*! A small struct to consolidate data for
   *  plotting a shape during a plotting
   *  routine
   */
  struct PlotShape {

    Shape       shape;   ///!< shape definition
    Style::Plot style;   ///!< marker, line, and fill style
    std::string legend;  ///!< legend entry

    // ------------------------------------------------------------------------
    //! default ctor
    // ------------------------------------------------------------------------
    PlotShape() {
      shape  = Shape();
      style  = Style::Plot();
      legend = "";
    };

    // ------------------------------------------------------------------------
    //! default dtor
    // ------------------------------------------------------------------------
    ~PlotShape() {};

    // ------------------------------------------------------------------------
    //! ctor acceptingt arguments
    // ------------------------------------------------------------------------
    PlotShape(
      const Shape sharg,
      const std::string& larg,
      const Style::Plot& sarg = Style::Plot()
    ) {
      shape  = sharg;
      legend = larg;
      style  = sarg;
    };

  };  // end PlotShape(Shape, std::string&, Style::Plot&)'

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
