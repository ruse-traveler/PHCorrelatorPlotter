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



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! General options for pads/canvases
  // ==========================================================================
  /*! A small struct to consolidate options
   *  common to both TPads & TCanvases
   */  
  struct PadOpts {

    // members
    uint32_t logx  = 0;
    uint32_t logy  = 0;
    uint32_t tickx = 1;
    uint32_t ticky = 1;
    uint32_t gridx = 0;
    uint32_t gridy = 0;
    uint32_t bmode = 0;
    uint32_t bsize = 2;
    uint32_t frame = 0;

    // ------------------------------------------------------------------------
    //! Apply options to a TPad or TCanvas
    // ------------------------------------------------------------------------
    template <typename T> void Apply(T* pad) const {

      pad -> SetLogx(logx);
      pad -> SetLogy(logy);
      pad -> SetTicks(tickx, ticky);
      pad -> SetGrid(gridx, gridy);
      pad -> SetBorderMode(bmode);
      pad -> SetBorderSize(bsize);
      pad -> SetFrameBorderMode(frame);
      return;

    }  // end 'Apply(T*)'

    // ------------------------------------------------------------------------
    //! default ctor/dtor
    // ------------------------------------------------------------------------
    PadOpts()  {};
    ~PadOpts() {};

    // ------------------------------------------------------------------------
    //! ctor accepting only log values
    // ------------------------------------------------------------------------
    PadOpts(const std::pair<uint32_t, uint32_t> log) {

      logx = log.first;
      logy = log.second;

    }  // end ctor(std::pair<uint32_t, uint32_t>)'

    // ------------------------------------------------------------------------
    //! ctor accepting all arguments
    // ------------------------------------------------------------------------
    PadOpts(
      const std::pair<uint32_t, uint32_t> log,
      const std::pair<uint32_t, uint32_t> tick,
      const std::pair<uint32_t, uint32_t> grid,
      const uint32_t mode = 0,
      const uint32_t size = 2,
      const uint32_t framearg = 0
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

    }  // end ctor(std::pair<uint32_t, uint32_t> x 3, uint32_t x 3)'

  };  // end PadOpts

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
