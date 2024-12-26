/// ===========================================================================
/*! \file    PHCorrelatorPlotTypes.hxx
 *  \authors Derek Anderson
 *  \date    12.26.2024
 *
 *  Useful types related to plotting.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTTYPES_H
#define PHCORRELATORPLOTTYPES_H

// c++ utilities
#include <array>
#include <map>
#include <string>
#include <utility>
#include <vector>
// root libraries
#include <TObject.h>



namespace PHEnergyCorrelator {
  namespace Types {

    // ------------------------------------------------------------------------
    //! Convenient types
    // ------------------------------------------------------------------------
    typedef std::array<float, 4>               Vertices;
    typedef std::array<float, 4>               Margins;
    typedef std::vector<TObject*>              Objects;
    typedef std::vector<std::string>           TextList;
    typedef std::vector<std::string>           LabelList;
    typedef std::pair<float, float>            Interval;
    typedef std::pair<uint32_t, uint32_t>      Dimensions;
    typedef std::map<std::string, std::size_t> LabelToIndexMap;



    // ------------------------------------------------------------------------
    //! Different margins of a pad or canvas
    // ------------------------------------------------------------------------
    enum Margin {Top, Right, Bottom, Left};

  }  // end Types namespace
}  // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
