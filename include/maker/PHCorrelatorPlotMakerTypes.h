/// ===========================================================================
/*! \file    PHCorrelatorPlotMakerTypes.h
 *  \authors Derek Anderson
 *  \date    04.13.2025
 *
 *  Useful types for making plots.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTMAKERTYPES_H
#define PHCORRELATORPLOTMAKERTYPES_H

// c++ utilities
#include <map>
#include <string>
// plotting utilities
#include "../elements/PHCorrelatorPlotterElements.h"



namespace PHEnergyCorrelator {
  namespace Type {

    // typedefs ===============================================================

    // ------------------------------------------------------------------------
    //! Convenient types
    // ------------------------------------------------------------------------
    typedef std::map<std::string, PlotShape> Shapes;
    typedef std::vector<PlotInput>           Inputs;
    typedef std::vector<Style>               Styles;



    // enums ==================================================================

    // ------------------------------------------------------------------------
    // Options for plot ranges
    // ------------------------------------------------------------------------
    enum RangeOpt {Side, Angle};

  }  // end Types namespace
}  // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================
