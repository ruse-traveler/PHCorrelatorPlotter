/// ===========================================================================
/*! \file    PHCorrelatorPlotMakerTools.h
 *  \authors Derek Anderson
 *  \date    04.12.2025
 *
 *  Useful tools for making plots and setting
 *  their options.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTMAKERTOOLS_H
#define PHCORRELATORPLOTMAKERTOOLS_H

// c++ utilities
#include <cmath>
#include <string>
// root libraries
#include <TString.h>
// plotting utilities
#include "./PHCorrelatorPlotMaker.h"
#include "../elements/PHCorrelatorPlotterElements.h"



namespace PHEnergyCorrelator {
  namespace Tools {

    // ------------------------------------------------------------------------
    // Options for plot ranges
    // ------------------------------------------------------------------------
    /* FIXME should go in constants */
    enum RangeOpt {Side, Angle};



    // ------------------------------------------------------------------------
    //! Get number of rows in a grid
    // ------------------------------------------------------------------------
    /*! Helper method to determine the relevant number of rows in a grid
     *  given a number of cells (e.g. histograms) and columns
     */
    std::size_t GetRowNumber(const std::size_t ncell, const std::size_t ncol) {

      const std::size_t div_one = (ncell / ncol) + 1;
      const std::size_t div_mod = (ncell / ncol) + (ncell % ncol);
      return std::min(div_one, div_mod);

    }  // end 'GetRowNumber(std::size_t, std::size_t)'



    // ------------------------------------------------------------------------
    //! Make ratio canvas
    // ------------------------------------------------------------------------
    /*! Creates a canvas divided into an upper panel (usually for
     *  various spectra) and a lower panel (usually for ratios).
     *
     *    \param can_name  canvas name
     *    \param up_name   name of upper pad
     *    \param lo_name   name of lower pad
     *    \param lo_height height (in % of canvas height) of upper pad
     *    \param up_opts   options for upper pad
     *    \param lo_opts   options for lower pad
     */ 
    Canvas MakeRatioCanvas(
      const std::string can_name,
      const std::string up_name,
      const std::string lo_name,
      const float lo_height = 0.35,
      const PadOpts& up_opts = PadOpts(),
      const PadOpts& lo_opts = PadOpts()
    ) {

      // set pad vertices
      Type::Vertices lo_vtxs;
      lo_vtxs.push_back(0.00);
      lo_vtxs.push_back(0.00);
      lo_vtxs.push_back(1.00);
      lo_vtxs.push_back(lo_height);

      Type::Vertices up_vtxs;
      up_vtxs.push_back(0.00);
      up_vtxs.push_back(lo_height);
      up_vtxs.push_back(1.00);
      up_vtxs.push_back(1.00);

      // set spectra margins
      //  - FIXME these should be in Const! 
      Type::Margins lo_margins;
      lo_margins.push_back(0.005);
      lo_margins.push_back(0.02);
      lo_margins.push_back(0.25);
      lo_margins.push_back(0.15);

      Type::Margins up_margins;
      up_margins.push_back(0.02);
      up_margins.push_back(0.02);
      up_margins.push_back(0.005);
      up_margins.push_back(0.15);

      // define canvas (use default pad options)
      //   - FIXME dimensions should also be in Const!
      Canvas canvas = Canvas(can_name, "", std::make_pair(750, 1125), PadOpts());
      canvas.AddPad( Pad(lo_name, "", lo_vtxs, lo_margins, lo_opts), "ratio" );
      canvas.AddPad( Pad(up_name, "", up_vtxs, up_margins, up_opts), "spectra" );
      return canvas;

    }  // end 'MakeRatioCanvas(std::string x 3, float, PadOpts& x 2)'



    // -----------------------------------------------------------------------
    //! Make a grid canvas
    // -----------------------------------------------------------------------
    /*! Creates a canvas divided into npad (or npad + ncol) pads based
     *  on provided parameters.
     *
     *    \param can_name canvas name
     *    \param pad_name base name of pads
     *    \param npad     number of pads
     *    \param ncolumn  number of columns
     *    \param margins  margins of each pad
     *    \param opts     options for each pad
     *    \param dim      (x, y) height of each pad
     */ 
    Canvas MakeGridCanvas(
      const std::string can_name,
      const std::string pad_name,
      const std::size_t npad,
      const std::size_t ncolumn,
      const Type::Margins& margins,
      const PadOpts& opts = PadOpts(),
      const float dim = 375
    ) {

      // determine number of rows
      const std::size_t nrow = GetRowNumber(npad, ncolumn);

      // determine canvas dimensions
      const Type::Dimensions dimensions = std::make_pair(
        dim * ncolumn,
        dim * nrow
      );

      // determine vertices of pads
      std::vector<Type::Vertices> pad_vtxs;    
      for (std::size_t ipad = 0; ipad < npad; ++ipad) {

        // get column/row indices
        const std::size_t icol = ipad % ncolumn;
        const std::size_t irow = GetRowNumber(ipad, ncolumn);

        // set x vertices
        const double startx = icol * (1.0 / (double) ncolumn);
        const double stopx  = (icol % ncolumn) * (1.0 / (double) ncolumn);

        // set y vertices
        const double starty = irow * (1.0 / (double) nrow);
        const double stopy  = (irow % nrow) * (1.0 / (double) nrow);

        // add to vector
        pad_vtxs.push_back( Type::Vertices() );
        pad_vtxs.back().push_back( startx );
        pad_vtxs.back().push_back( starty );
        pad_vtxs.back().push_back( stopx );
        pad_vtxs.back().push_back( stopy );
      }

      // define canvas (use default pad options)
      Canvas canvas = Canvas(can_name, "", dimensions, PadOpts());
      for (std::size_t ipad = 0; ipad < npad; ++ipad) {

        // create name
        TString tname(pad_name.data());
        tname += ipad;

        // add pad
        canvas.AddPad(
          Pad(
            std::string(tname.Data()),
            "",
            pad_vtxs[ipad],
            margins,
            opts
          )
        );
      }
      return canvas;

    }  // end 'MakeGridCanvas(std::string x 2, std::size_t x 2, Type::Margins&, PadOpts&, float)'

  }  // end Tools namespace
}  // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================
