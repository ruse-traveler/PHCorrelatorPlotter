/// ===========================================================================
/*! \file    PHCorrelatorShape.h
 *  \authors Derek Anderson
 *  \date    01.07.2025
 *
 *  Definition of various shapes
 */
/// ===========================================================================

#ifndef PHCORRELATORSHAPE_H
#define PHCORRELATORSHAPE_H

// c++ utilities
#include <utility>
// root libraries
#include <TBox.h>
#include <TEllipse.h>
#include <TLine.h>
// plotting utilities
#include "PHCorrelatorPlotTypes.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Shape definition
  // ==========================================================================
  /*! A small class to consolidate necessary data
   *  to define a shapes (e.g. a line, a box, etc.)
   */
  class Shape {

    private:

      // data members
      Type::Interval m_xrange;
      Type::Interval m_yrange;
      Type::Interval m_phirange;
      /* TODO add remaining ellipse members */

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Type::Interval GetXRange()   const {return m_xrange;}
      Type::Interval GetYRange()   const {return m_xrange;}
      Type::Interval GetPhiRange() const {return m_phirange;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetXRange(const Type::Interval& range)   {m_xrange   = range;}
      void SetYRange(const Type::Interval& range)   {m_yrange   = range;}
      void SetPhiRange(const Type::Interval& range) {m_phirange = range;}

      // ----------------------------------------------------------------------
      //! Create a TLine
      // ----------------------------------------------------------------------
      TLine* MakeTLine() const {

        TLine* line = new TLine(
          m_xrange.first,
          m_yrange.first,
          m_xrange.second,
          m_yrange.second
        );
        return line;

      }  // end 'MakeTLine()'

      // ----------------------------------------------------------------------
      //! Create a TBox
      // ----------------------------------------------------------------------
      TBox* MakeTBox() const {

        TBox* box = new TBox(
          m_xrange.first,
          m_yrange.first,
          m_xrange.second,
          m_yrange.second
        );
        return box;

      }  // end 'MakeTBox()'
 
      /* TODO fill in ellipse maker */ 

      // ----------------------------------------------------------------------
      //! default ctor
      // ----------------------------------------------------------------------
      Shape() {
        m_xrange   = std::make_pair(0.0, 1.0);
        m_yrange   = std::make_pair(0.0, 1.0);
        m_phirange = std::make_pair(0.0, 360.);
      };
 
      // ----------------------------------------------------------------------
      //! default dtor
      // ----------------------------------------------------------------------
      ~Shape() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      /* TODO fill in */

  };  // end Shape

}  // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
