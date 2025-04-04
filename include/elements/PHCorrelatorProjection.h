/// ===========================================================================
/*! \file    PHCorrelatorProjection.h
 *  \authors Derek Anderson
 *  \date    02.12.2025
 *
 *  Definition of a projection to make.
 */
/// ===========================================================================

#ifndef PHCORRELATORPROJECTION_H
#define PHCORRELATORPROJECTION_H

// c++ utilities
#include <string>
// root libraries
#include <TH1.h>
#include <TH2.h>
// plotting utilities
#include "PHCorrelatorPlotTypes.h"
#include "PHCorrelatorRange.h"
#include "PHCorrelatorStyle.h"



namespace PHEnergyCorrelator {

  //===========================================================================
  //! Projection definition
  // ==========================================================================
  /*! A small struct to consolidate info needed
   *  to define a projection (2D -> 1D).
   */
  struct Projection {

    Type::Axis  axis;    ///!< axis to project
    Type::PairF range;   ///!< range to project over
    std::string rename;  ///!< rename projected histogram to this
    std::string legend;  ///!< legend entry
    std::string draw;    ///!< draw option
    Style::Plot style;   ///!< marker, line, and fill style

    // ------------------------------------------------------------------------
    //! Do projection
    // ------------------------------------------------------------------------
    TH1* ProjectTH1(const TH2* hist) {

      /* TODO fill in */
      return new TH1D("hToDo", "TODO", 10, 0.0, 1.0);

    }  // end 'ProjectTH1(TH2*)'

    // ------------------------------------------------------------------------
    //! default ctor
    // ------------------------------------------------------------------------
    Projection() {
      axis   = Type::X;
      range  = std::make_pair(0.0, 1.0);
      rename = "";
      legend = "";
      draw   = "";
      style  = Style::Plot();
    }  // end ctor()

    // ------------------------------------------------------------------------
    //! default dtor
    // ------------------------------------------------------------------------
    ~Projection() {};

    // ------------------------------------------------------------------------
    //! ctor accepting arguments
    // ------------------------------------------------------------------------
    Projection(
      const Type::Axis& aarg,
      const Type::PairF& parg,
      const std::string& rarg,
      const std::string& larg,
      const std::string& darg,
      const Style::Plot& sarg = Style::Plot()
    ) {
      axis   = aarg;
      range  = parg;
      rename = rarg;
      legend = larg;
      draw   = darg;
      style  = Style::Plot();
    }  // end ctor(Type::Axis&, Type::PairF&, std::string& x 3, Style::Plot&)

  };  // end Projection 

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
