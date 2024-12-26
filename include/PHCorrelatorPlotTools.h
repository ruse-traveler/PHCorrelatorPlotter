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



namespace PHEnergyCorrelator {
  namespace Tools {

    // ------------------------------------------------------------------------
    //! Helper method to calculate a height based on line spacing
    // ------------------------------------------------------------------------
    float GetHeight(
      const std::size_t nlines,
      const float spacing,
      const float off = 0.0
    ) {

      float height = (nlines * spacing) + off;
      return height;

    }  // end 'GetHeight(std::size_t, float x 2)'

  }  // end Tools namespace
}  // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
