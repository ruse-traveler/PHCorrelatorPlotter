/// ===========================================================================
/*! \file    PHCorrelatorRange.h
 *  \authors Derek Anderson
 *  \date    12.26.2024
 *
 *  Definition of a plotting range.
 */
/// ===========================================================================

#ifndef PHCORRELATORRANGE_H
#define PHCORRELATORRANGE_H

// c++ utilities
#include <optional>
// plotting utilities
#include "PHCorrelatorPlotTools.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Plot range
  // ==========================================================================
  /*! This struct groups together the start/stop
   *  points for all 3 axes for convenience.
   */
  struct Range {

    // members
    Tools::Interval x;
    Tools::Interval y;
    Tools::Interval z;

    // ------------------------------------------------------------------------
    //! default ctor/dtor
    // ------------------------------------------------------------------------
    Range()  {};
    ~Range() {};

    // ------------------------------------------------------------------------
    //! ctor accepting only x range
    // ------------------------------------------------------------------------
    Range(const Tools::Interval& xrange) {
      x = xrange;
    }

    // ------------------------------------------------------------------------
    //! ctor accepting x, y, and possibly z range
    // ------------------------------------------------------------------------
    Range(
      const Tools::Interval& xrange,
      const Tools::Interval& yrange,
      std::optional<Tools::Interval> zrange = std::nullopt
    ) {
      x = xrange;
      y = yrange;
      if (zrange.has_value()) {
        z = zrange.value();
      }
    }

  };  // end Range

}  // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
