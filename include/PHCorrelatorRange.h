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
#include <utility>
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
    //! default ctor
    // ------------------------------------------------------------------------
    Range() {
      x = std::make_pair(0.0, 1.0);
      y = std::make_pair(0.0, 1.0);
      z = std::make_pair(0.0, 1.0);
    };

    // ------------------------------------------------------------------------
    //! default dtor
    // ------------------------------------------------------------------------
    ~Range() {};

    // ------------------------------------------------------------------------
    //! ctor accepting only x range
    // ------------------------------------------------------------------------
    Range(const Type::Interval& xrange) {
      x = xrange;
    }

    // ------------------------------------------------------------------------
    //! ctor accepting x and y range
    // ------------------------------------------------------------------------
    Range(
      const Type::Interval& xrange,
      const Type::Interval& yrange
    ) {
      x = xrange;
      y = yrange;
    }

    // ------------------------------------------------------------------------
    //! ctor accepting x, y, and z range
    // ------------------------------------------------------------------------
    Range(
      const Type::Interval& xrange,
      const Type::Interval& yrange,
      const Type::Interval& zrange
    ) {
      x = xrange;
      y = yrange;
      z = zrange;
    }

  };  // end Range

}  // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
