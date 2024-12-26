/// ===========================================================================
/*! \file    PHCorrelatorPlotTools.hxx
 *  \authors Derek Anderson
 *  \date    12.26.2024
 *
 *  Useful tools related to plotting.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTTOOLS_H
#define PHCORRELATORPLOTTOOLS_H

// c++ utilities
#include <array>
#include <map>
#include <optional>
#include <string>
#include <utility>
#include <vector>
// root libraries
#include <TObject.h>



namespace PHEnergyCorrelator {
  namespace Tools {

    // ------------------------------------------------------------------------
    //! Convenient types
    // ------------------------------------------------------------------------
    /*! FIXME this might be better served in a dedicated "Type" or "Constant"
     *  namespace...
     */ 
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
    /*! FIXME this might be better served in a dedicated "Type" or "Constant"
     *  namespace...
     */ 
    enum Margin {Top, Right, Bottom, Left};



    // ------------------------------------------------------------------------
    //! Helper method to calculate a height based on line spacing
    // ------------------------------------------------------------------------
    float GetHeight(
      const std::size_t nlines,
      const float spacing,
      std::optional<float> off = std::nullopt
    ) {

      float height = nlines * spacing;
      if (off.has_value()) {
        height += off.value();
      }
      return height;

    }  // end 'GetHeight(std::size_t float, std::optional<float>)'

  }  // end Tools namespace
}  // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
