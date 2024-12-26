/// ===========================================================================
/*! \file    PHCorrelatorPadOpts.h
 *  \authors Derek Anderson
 *  \date    12.26.2024
 *
 *  Definition of user options for pads.
 */
/// ===========================================================================

#ifndef PHCORRELATORPADOPTS_H
#define PHCORRELATORPADOPTS_H

// c++ utilities
#include <utility>
// root libraries
#include <TCanvas.h>
#include <TPad.h>



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! General options for pads/canvases
  // ==========================================================================
  /*! A small struct to consolidate options
   *  common to both TPads & TCanvases
   */  
  struct PadOpts {

    // members
    std::size_t logx;
    std::size_t logy;
    std::size_t tickx;
    std::size_t ticky;
    std::size_t gridx;
    std::size_t gridy;
    std::size_t bmode;
    std::size_t bsize;
    std::size_t frame;

    // ------------------------------------------------------------------------
    //! Apply options to a TCanvas
    // ------------------------------------------------------------------------
    void Apply(TCanvas* canvas) const {

      canvas -> SetLogx(logx);
      canvas -> SetLogy(logy);
      canvas -> SetTicks(tickx, ticky);
      canvas -> SetGrid(gridx, gridy);
      canvas -> SetBorderMode(bmode);
      canvas -> SetBorderSize(bsize);
      canvas -> SetFrameBorderMode(frame);
      return;

    }  // end 'Apply(TCanvas*)'

    // ------------------------------------------------------------------------
    //! Apply options to a TPad
    // ------------------------------------------------------------------------
    void Apply(TPad* pad) const {

      pad -> SetLogx(logx);
      pad -> SetLogy(logy);
      pad -> SetTicks(tickx, ticky);
      pad -> SetGrid(gridx, gridy);
      pad -> SetBorderMode(bmode);
      pad -> SetBorderSize(bsize);
      pad -> SetFrameBorderMode(frame);
      return;

    }  // end 'Apply(TPad*)'

    // ------------------------------------------------------------------------
    //! default ctor
    // ------------------------------------------------------------------------
    PadOpts() {
      logx  = 0;
      logy  = 0;
      tickx = 1;
      ticky = 1;
      gridx = 0;
      gridy = 0;
      bmode = 0;
      bsize = 2;
      frame = 0;
    };

    // ------------------------------------------------------------------------
    //! default dtor
    // ------------------------------------------------------------------------
    ~PadOpts() {};

    // ------------------------------------------------------------------------
    //! ctor accepting only log values
    // ------------------------------------------------------------------------
    PadOpts(const std::pair<std::size_t, std::size_t> log) {

      logx = log.first;
      logy = log.second;

    }  // end ctor(std::pair<std::size_t, std::size_t>)'

    // ------------------------------------------------------------------------
    //! ctor accepting all arguments
    // ------------------------------------------------------------------------
    PadOpts(
      const std::pair<std::size_t, std::size_t> log,
      const std::pair<std::size_t, std::size_t> tick,
      const std::pair<std::size_t, std::size_t> grid,
      const std::size_t mode = 0,
      const std::size_t size = 2,
      const std::size_t framearg = 0
    ) {

      logx  = log.first;
      logy  = log.second;
      tickx = tick.first;
      ticky = tick.second;
      gridx = grid.first;
      gridy = grid.second;
      bmode = mode;
      bsize = size;
      frame = framearg;

    }  // end ctor(std::pair<std::size_t, std::size_t> x 3, std::size_t x 3)'

  };  // end PadOpts

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
