/// ============================================================================
/*! \file    PHCorrelatorPlotterMaker.h
 *  \authors Derek Anderson
 *  \date    04.01.2025
 *
 *  All-in-one header for PHCorrelatorPlotter
 *  maker components.
 *
 *  FIXME THIS MIGHT NOT BE NECESSARY AFTER
 *  MERGING PLOT OPTIONS WITH ROUTINES
 */
/// ============================================================================

#ifndef PHCORRELATORPLOTTERMAKER_H
#define PHCORRELATORPLOTTERMAKER_H

// plotting components
#include "PHCorrelatorPlotMaker.h"
#include "PHCorrelatorPlotMakerNew.h"
#include "PHCorrelatorPlotMakerOptions.h"
#include "PHCorrelatorPlotMakerTools.h"
#include "PHCorrelatorPlotMakerTypes.h"

// plotting routines
#include "PHCorrelatorBaseRoutine.h"
#include "PHCorrelatorCorrectSpectra1D.h"
#include "PHCorrelatorCorrectSpectra2D.h"
#include "PHCorrelatorPlotRatios1D.h"
#include "PHCorrelatorPlotRatios2D.h"
#include "PHCorrelatorPlotSpectra1D.h"
#include "PHCorrelatorPlotSpectra2D.h"
#include "PHCorrelatorPlotVsBaseline1D.h"
#include "PHCorrelatorPlotVsBaseline2D.h"

// alias for convenience
namespace PHEnergyCorrelator {
  namespace PMO = PlotMakerOptions;
}

#endif

/// end =======================================================================
