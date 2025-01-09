/// ===========================================================================
/*! \file   CompareSpectra2D.h
 *  \author Derek Anderson
 *  \date   01.05.2024
 *
 *  A small namespace to define inputs to the
 *  2D spectra plotting routine.
 */
/// ===========================================================================

#ifndef COMPARESPECTRA2D_H
#define COMPARESPECTRA2D_H

// c++ utilities
#include <string>
#include <vector>
#include <utility>
// root libraries
#include <TString.h>
// plotting utilities
#include "../include/PHCorrelatorPlotting.h"



// ============================================================================
//! 2D Spectra Comparison Options
// ============================================================================
/*! This namespace collects all the parameters associated with
 *  the `PHCorrelatorPlotter::CompareSpectra2D` routines. 
 */
namespace CompareSpectra2D {

  // --------------------------------------------------------------------------
  //! Define plot range
  // --------------------------------------------------------------------------
  /*! Plot range arguments:
   *    first  = x range to plot
   *    second = y range to plot
   *    third  = z range to plot
   */ 
  PHEC::Range PlotRange() {

    PHEC::Range range = PHEC::Range(
      std::make_pair(0.003, 3.),
      std::make_pair(-3.15, 3.15),
      std::make_pair(0.00003, 33.)
    );
    return range;

  }  // end 'PlotRange()'



  // --------------------------------------------------------------------------
  //! Define normalization range
  // --------------------------------------------------------------------------
  PHEC::Range NormRange() {

    // grab plot range
    PHEC::Range plot_range = PlotRange();

    // set normalization range
    PHEC::Range range = PHEC::Range(plot_range.x, plot_range.y);
    return range;

  }  // end 'NormRange()'



  // --------------------------------------------------------------------------
  //! Define canvas
  // --------------------------------------------------------------------------
  /*! The 2nd parameter determines how many panels
   *  to create on the canvas: nominally should be
   *  1 for each histogram to draw.
   */ 
  PHEC::Canvas Canvas(
    const std::string& name = "cSpectra2D",
    const std::vector<PHEC::PlotInput>& inputs = std::vector<PHEC::PlotInput>()
  ) {

    // grab default pad options, and
    // turn on log z
    PHEC::PadOpts opts = PHEC::PadOpts();
    opts.logx = 1;
    opts.logz = 1;

    // determine canvas dimensions
    //   - FIXME layout of canvas should be configurable
    const PHEC::Type::Dimensions dimensions = std::make_pair(
      950 * inputs.size(),
      950
    );

    // determine vertices of pads
    std::vector<PHEC::Type::Vertices> pad_vtxs;    
    for (std::size_t iin = 0; iin < inputs.size(); ++iin) {

      // set x vertices
      const double startx = iin * (1.0 / inputs.size());
      const double stopx  = (iin + 1) * (1.0 / inputs.size());

      // add to vector
      pad_vtxs.push_back( PHEC::Type::Vertices() );
      pad_vtxs.back().push_back( startx );
      pad_vtxs.back().push_back( 0.00 );
      pad_vtxs.back().push_back( stopx );
      pad_vtxs.back().push_back( 1.00 );
    }

    // set pad margins
    PHEC::Type::Margins pad_margins;
    pad_margins.push_back(0.15);
    pad_margins.push_back(0.15);
    pad_margins.push_back(0.15);
    pad_margins.push_back(0.15);

    // define canvas (use default pad options)
    PHEC::Canvas canvas = PHEC::Canvas(name, "", dimensions, PHEC::PadOpts());
    for (std::size_t iin = 0; iin < inputs.size(); ++iin) {

      // create name
      TString tname("pSpec");
      tname += iin;

      // add pad
      canvas.AddPad(
        PHEC::Pad(
          std::string(tname.Data()),
          "",
          pad_vtxs[iin],
          pad_margins,
          opts
        )
      );
    }
    return canvas;

  }  // end 'Canvas(std::string&, std::vector<PHEC::PlotInput>&)'



  // --------------------------------------------------------------------------
  //! Define normalization
  // --------------------------------------------------------------------------
  /*! Used to set what value to normalize to.
   */
  double Norm() {

    return 1.0;

  }  // end 'Norm()'

}  // end CompareSpectra2D namespace

#endif

// end ========================================================================
