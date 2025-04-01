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
// root libraries
#include <TAxis.h>
// plotting utilities
#include "PHCorrelatorPlotTypes.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Plot range
  // ==========================================================================
  /*! This struct groups together the start/stop
   *  points for all 3 axes for convenience.
   */
  class Range {

    public:

      // accessor
      //   - FIXME should be in Constants
      enum Axis {X, Y, Z};

    private:

      // members
      Type::Interval x;
      Type::Interval y;
      Type::Interval z;

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Type::Interval GetX() const {return x;}
      Type::Interval GetY() const {return y;}
      Type::Interval GetZ() const {return z;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetX(const Type::Interval& range) {x = range;}
      void SetY(const Type::Interval& range) {y = range;}
      void SetZ(const Type::Interval& range) {z = range;}

      // ----------------------------------------------------------------------
      //! Apply a range to a TAxis
      // ----------------------------------------------------------------------
      void Apply(const Axis axis, TAxis* to_range) const {

        switch (axis) {

          case X:
            to_range -> SetRangeUser(x.first, x.second);
            break;

          case Y:
            to_range -> SetRangeUser(y.first, y.second);
            break;

          case Z:
            to_range -> SetRangeUser(z.first, z.second);
            break;

          default:
            /* do nothing */
            break;

        }
        return;

      }  // end 'Apply(Axis, TAxis*)'

      // ----------------------------------------------------------------------
      //! default ctor
      // ----------------------------------------------------------------------
      Range() {
        x = std::make_pair(0.0, 1.0);
        y = std::make_pair(0.0, 1.0);
        z = std::make_pair(0.0, 1.0);
      };

      // ----------------------------------------------------------------------
      //! default dtor
      // ----------------------------------------------------------------------
      ~Range() {};

      // ----------------------------------------------------------------------
      //! ctor accepting only x range
      // ----------------------------------------------------------------------
      Range(const Type::Interval& xrange) {
        x = xrange;
      }

      // ----------------------------------------------------------------------
      //! ctor accepting x and y range
      // ----------------------------------------------------------------------
      Range(
        const Type::Interval& xrange,
        const Type::Interval& yrange
      ) {
        x = xrange;
        y = yrange;
      }

      // ----------------------------------------------------------------------
      //! ctor accepting x, y, and z range
      // ----------------------------------------------------------------------
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
