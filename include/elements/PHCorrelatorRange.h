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
  /*! This class groups together the start/stop
   *  points for all 3 axes for convenience.
   */
  class Range {

    public:

      // accessor
      //   - FIXME should be in Constants
      enum Axis {X, Y, Z};

    private:

      // members
      Type::Interval m_x;
      Type::Interval m_y;
      Type::Interval m_z;

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Type::Interval GetX() const {return m_x;}
      Type::Interval GetY() const {return m_y;}
      Type::Interval GetZ() const {return m_z;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetX(const Type::Interval& range) {m_x = range;}
      void SetY(const Type::Interval& range) {m_y = range;}
      void SetZ(const Type::Interval& range) {m_z = range;}

      // ----------------------------------------------------------------------
      //! Apply a range to a TAxis
      // ----------------------------------------------------------------------
      void Apply(const Axis axis, TAxis* to_range) const {

        switch (axis) {
          case X:
            to_range -> SetRangeUser(m_x.first, m_x.second);
            break;
          case Y:
            to_range -> SetRangeUser(m_y.first, m_y.second);
            break;
          case Z:
            to_range -> SetRangeUser(m_z.first, m_z.second);
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
        m_x = std::make_pair(0.0, 1.0);
        m_y = std::make_pair(0.0, 1.0);
        m_z = std::make_pair(0.0, 1.0);
      };

      // ----------------------------------------------------------------------
      //! default dtor
      // ----------------------------------------------------------------------
      ~Range() {};

      // ----------------------------------------------------------------------
      //! ctor accepting only x range
      // ----------------------------------------------------------------------
      Range(const Type::Interval& xrange) {
        m_x = xrange;
      }

      // ----------------------------------------------------------------------
      //! ctor accepting x and y range
      // ----------------------------------------------------------------------
      Range(
        const Type::Interval& xrange,
        const Type::Interval& yrange
      ) {
        m_x = xrange;
        m_y = yrange;
      }

      // ----------------------------------------------------------------------
      //! ctor accepting x, y, and z range
      // ----------------------------------------------------------------------
      Range(
        const Type::Interval& xrange,
        const Type::Interval& yrange,
        const Type::Interval& zrange
      ) {
        m_x = xrange;
        m_y = yrange;
        m_z = zrange;
      }

  };  // end Range

}  // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================
