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

    }  // end 'MakeRatioCanvas(...)'



    // ------------------------------------------------------------------------
    //! Make 1D correction canvas
    // ------------------------------------------------------------------------
    /*! Creates a canvas divided into an upper panel (usually for truth vs.
     *  corrected spectra), a middle panel (usually for ratios of corrected
     *  over truth), and a lower panel (usually for correction factors).
     *
     *    \param can_name   canvas name
     *    \param up_name    name of upper pad
     *    \param mid_name   name of middle pad
     *    \param lo_name    name of lower pad
     *    \param lo_height  height (in % of canvas height) of upper pad
     *    \param mid_height height (in % of canvas height) of middle pad
     *    \param up_opts    options for upper pad
     *    \param mid_opts   options for middle pad
     *    \param lo_opts    options for lower pad
     */
    Canvas MakeCorrectionCanvas1D(
      const std::string can_name,
      const std::string up_name,
      const std::string mid_name,
      const std::string lo_name,
      const float lo_height = 0.25,
      const float mid_height = 0.50,
      const PadOpts& up_opts = PadOpts(),
      const PadOpts& mid_opts = PadOpts(),
      const PadOpts& lo_opts = PadOpts()
    ) {

      // set pad vertices
      Type::Vertices lo_vtxs;
      lo_vtxs.push_back(0.00);
      lo_vtxs.push_back(0.00);
      lo_vtxs.push_back(1.00);
      lo_vtxs.push_back(lo_height);

      Type::Vertices mid_vtxs;
      mid_vtxs.push_back(0.00);
      mid_vtxs.push_back(lo_height);
      mid_vtxs.push_back(1.00);
      mid_vtxs.push_back(mid_height);

      Type::Vertices up_vtxs;
      up_vtxs.push_back(0.00);
      up_vtxs.push_back(mid_height);
      up_vtxs.push_back(1.00);
      up_vtxs.push_back(1.00);

      // set spectra margins
      Type::Margins lo_margins;
      lo_margins.push_back(0.005);
      lo_margins.push_back(0.02);
      lo_margins.push_back(0.25);
      lo_margins.push_back(0.15);

      Type::Margins mid_margins;
      mid_margins.push_back(0.005);
      mid_margins.push_back(0.02);
      mid_margins.push_back(0.005);
      mid_margins.push_back(0.15);

      Type::Margins up_margins;
      up_margins.push_back(0.02);
      up_margins.push_back(0.02);
      up_margins.push_back(0.005);
      up_margins.push_back(0.15);

      // define canvas (use default pad options)
      Canvas canvas = Canvas(can_name, "", std::make_pair(750, 1125), PadOpts());
      canvas.AddPad( Pad(lo_name,  "", lo_vtxs,  lo_margins,  lo_opts),  "correct" );
      canvas.AddPad( Pad(mid_name, "", mid_vtxs, mid_margins, mid_opts), "ratio");
      canvas.AddPad( Pad(up_name,  "", up_vtxs,  up_margins,  up_opts),  "spectra" );
      return canvas;

    }  // end 'MakeCorrectionCanvas(...)'



    // -----------------------------------------------------------------------
    //! Make a grid canvas
    // -----------------------------------------------------------------------
    /*! Creates a canvas divided into npad (or npad + ncol) pads based
     *  on provided parameters.
     *
     *    \param can_name canvas name
     *    \param pad_name base name of pads
     *    \param npad     number of histograms (or inputs)
     *    \param ncolumn  number of columns
     *    \param margins  margins of each pad
     *    \param opts     options for each pad
     *    \param dim      (x, y) height of each pad
     */ 
    Canvas MakeGridCanvas(
      const std::string can_name,
      const std::string pad_name,
      const std::size_t nhist,
      const std::size_t ncolumn,
      const Type::Margins& margins,
      const PadOpts& opts = PadOpts(),
      const float dim = 375
    ) {

      // determine number of rows/pads
      const std::size_t nrow = GetRowNumber(nhist, ncolumn);
      const std::size_t npad = nrow * ncolumn;

      // determine canvas dimensions
      const Type::Dimensions dimensions = std::make_pair(
        dim * ncolumn,
        dim * nrow
      );

      // get pad width (xstep), heights (ystep)
      const double xstep = 1.0 / (double) nrow;
      const double ystep = 1.0 / (double) ncolumn;

      // determine vertices of pads
      std::vector<Type::Vertices> pad_vtxs;    
      for (std::size_t irow = nrow; irow > 0; --irow) {
        for (std::size_t icol = 0; icol < ncolumn; ++icol) {

          // set x vertices
          const double startx = icol * xstep;
          const double stopx  = (icol + 1) * xstep;

          // set y vertices
          const double starty =  (irow - 1) * ystep;
          const double stopy  =  irow * ystep;

          // add to vector
          pad_vtxs.push_back( Type::Vertices() );
          pad_vtxs.back().push_back( startx );
          pad_vtxs.back().push_back( starty );
          pad_vtxs.back().push_back( stopx );
          pad_vtxs.back().push_back( stopy );
        }
      }

      // define canvas (use default pad options)
      Canvas canvas = Canvas(can_name, "", dimensions, opts);
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

    }  // end 'MakeGridCanvas(...)'

  }  // end Tools namespace
}  // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================
