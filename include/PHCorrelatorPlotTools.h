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
#include <optional>
// root libraries
#include <TObject.h>



namespace PHEnergyCorrelator {
  namespace Tools {

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
