/// ===========================================================================
/*! \file   PHCorrelatorPlotter.h
 *  \author Derek Anderson
 *  \date   11.12.2024
 *
 *  Class to consolidate plotting routines associated with
 *  the PHENIX ENC analysis.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTTER_H
#define PHCORRELATORPLOTTER_H

// c++ utilities
#include <string>

// forward declarations
class TCanvas;
class TFile;
class TLegend;



// ============================================================================
//! ENC Plotter
// ============================================================================
class PHCorrelatorPlotter {

  public:

    PHCorrelatorPlotter()  {};
    ~PHCorrelatorPlotter() {};

    // plotting routines
    void CompareTrueVsRecoEEC(const std::string in_file, const std::string out_file);

  private:

    // helper methods
    TFile*   OpenFile(const std::string name, const std::string option);
    TLegend* MakeLegend();

};  // end Plotter

#endif

// end ========================================================================
