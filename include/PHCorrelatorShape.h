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
#include <cmath>
#include <utility>
// root libraries
#include <TBox.h>
#include <TEllipse.h>
#include <TLine.h>
#include <TMath.h>
// plotting utilities
#include "PHCorrelatorPlotTools.h"
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
      Type::Point    m_center;
      Type::PairF    m_radii;
      float          m_theta;

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Type::Interval GetXRange()   const {return m_xrange;}
      Type::Interval GetYRange()   const {return m_xrange;}
      Type::Interval GetPhiRange() const {return m_phirange;}
      Type::Point    GetCenter()   const {return m_center;}
      Type::PairF    GetRadii()    const {return m_radii;}
      float          GetTheta()    const {return m_theta;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetXRange(const Type::Interval& range)   {m_xrange   = range;}
      void SetYRange(const Type::Interval& range)   {m_yrange   = range;}
      void SetPhiRange(const Type::Interval& range) {m_phirange = range;}
      void SetCenter(const Type::Point& point)      {m_center   = point;}
      void SetRadii(const Type::PairF& radii)       {m_radii    = radii;}
      void SetTheta(const float theta)              {m_theta    = theta;}

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

      // ----------------------------------------------------------------------
      //! Create a TEllipse
      // ----------------------------------------------------------------------
      TEllipse* MakeTEllipse() const {

        TEllipse* ellipse = new TEllipse(
          m_center.first,
          m_center.second,
          m_radii.first,
          m_radii.second,
          m_phirange.first,
          m_phirange.second,
          m_theta
        );
        return ellipse;

      }  // end 'MakeTEllipse()'

      // ----------------------------------------------------------------------
      //! default ctor
      // ----------------------------------------------------------------------
      Shape() {

        m_xrange   = std::make_pair(0.0, 1.0);
        m_yrange   = std::make_pair(0.0, 1.0);
        m_phirange = Tools::DefaultPhiRange();
        m_center   = std::make_pair(0.5, 0.5);
        m_radii    = std::make_pair(0.5, 0.5);
        m_theta    = 0.0;

      };  // end ctor()
 
      // ----------------------------------------------------------------------
      //! default dtor
      // ----------------------------------------------------------------------
      ~Shape() {};

      // ----------------------------------------------------------------------
      //! ctor accepting line/box arguments
      // ----------------------------------------------------------------------
      Shape(const Type::Interval& xrange, const Type::Interval& yrange) {

        const float xradius = 0.5 * abs(xrange.second - xrange.first);
        const float yradius = 0.5 * abs(yrange.second - yrange.first);
        const float xcenter = xrange.first + xradius;
        const float ycenter = yrange.first + yradius;

        m_xrange   = xrange;
        m_yrange   = yrange;
        m_center   = std::make_pair(xcenter, ycenter);
        m_radii    = std::make_pair(xradius, yradius);
        m_phirange = std::make_pair(0.0, 360.);
        m_theta    = 0.0;

      }  // end ctor(Type::Interval& x 2)'

      // ----------------------------------------------------------------------
      //! ctor accepting ellipse arguments
      // ----------------------------------------------------------------------
      Shape(
        const Type::Point& center,
        const Type::PairF& radii,
        const Type::Interval& phirange,
        const float theta = 0.0
      ) {

        const float thrad = (theta / 360.0) * TMath::TwoPi();
        const float thinv = TMath::Pi() - thrad;
        const float xmax  = TMath::Max( radii.first * TMath::Cos(thrad), radii.second * TMath::Cos(thinv) );
        const float ymax  = TMath::Max( radii.first * TMath::Sin(thrad), radii.second * TMath::Sin(thinv) );

        m_xrange   = std::make_pair(center.first - xmax, center.first + xmax);
        m_yrange   = std::make_pair(center.second - ymax, center.second + ymax);
        m_phirange = phirange;
        m_center   = center;
        m_radii    = radii;
        m_theta    = theta;

      }  // end ctor(Type::Point&, Type::PairF&, Type::Interval&, float)

  };  // end Shape

}  // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
