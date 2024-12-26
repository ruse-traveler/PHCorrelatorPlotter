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
#include "PHCorrelatorPlotTypes.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Plot range
  // ==========================================================================
  /*! This struct groups together the start/stop
   *  points for all 3 axes for convenience.
   */
  struct Range {

    // members
    Type::Interval x;
    Type::Interval y;
    Type::Interval z;

    // ------------------------------------------------------------------------
    //! default ctor/dtor
    // ------------------------------------------------------------------------
    Range()  {};
    ~Range() {};

    // ------------------------------------------------------------------------
    //! ctor accepting only x range
    // ------------------------------------------------------------------------
    Range(const Type::Interval& xrange) {
      x = xrange;
    }

    // ------------------------------------------------------------------------
    //! ctor accepting x, y, and possibly z range
    // ------------------------------------------------------------------------
    Range(
      const Type::Interval& xrange,
      const Type::Interval& yrange,
      std::optional<Type::Interval> zrange = std::nullopt
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
