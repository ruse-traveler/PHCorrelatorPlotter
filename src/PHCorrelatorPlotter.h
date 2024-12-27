/// ===========================================================================
/*! \file    PHCorrelatorPlotter.h
 *  \authors Derek Anderson
 *  \date    11.12.2024
 *
 *  Class to consolidate plotting routines associated with
 *  the PHENIX ENC analysis.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTTER_H
#define PHCORRELATORPLOTTER_H

// c++ utilities
#include <string>
#include <vector>
// plotting utilities
#include "../include/PHCorrelatorPlotting.h"

// forward declarations
class TCanvas;
class TFile;
class TLegend;

// useful alias
typedef std::vector<PHEC::Style> Styles; 
typedef std::vector<PHEC::PlotInput> Inputs;



// ============================================================================
//! ENC Plotter
// ============================================================================
/*! This class consolidates plotting routines associated
 *  with the PHENIX ENC analysis.
 */
class PHCorrelatorPlotter {

  public:

    // default ctor/dtor
    PHCorrelatorPlotter();
    ~PHCorrelatorPlotter();

    // ctor accepting arguments
    PHCorrelatorPlotter(
      const PHEC::Style& plot,
      const PHEC::Style& text,
      const PHEC::TextBox& box = PHEC::TextBox()
    );

    // getters
    PHEC::Style   GetBasePlotStyle() const {return m_basePlotStyle;}
    PHEC::Style   GetBaseTextStyle() const {return m_baseTextStyle;}
    PHEC::TextBox GetTextBox()       const {return m_textBox;}

    // setters
    void SetBasePlotStyle(const PHEC::Style& style) {m_basePlotStyle = style;}
    void SetBaseTextStyle(const PHEC::Style& style) {m_baseTextStyle = style;}
    void SetTextBox(const PHEC::TextBox& text)      {m_textBox       = text;}

    // plotting routines
    void CompareSpectra(
      const Inputs& inputs,
      const PHEC::Range& range,
      const PHEC::Canvas& canvas,
      TFile* ofile,
      const std::string& header = ""
    ) const;
    void CompareSpectraToBaseline(
      const PHEC::PlotInput& in_denom,
      const Inputs& in_numers,
      const PHEC::Range& range,
      const PHEC::Canvas& canvas,
      TFile* ofile,
      const std::string& header = ""
    ) const;
    void CompareRatios(
      const Inputs& in_denoms,
      const Inputs& in_numers,
      const PHEC::Range& range,
      const PHEC::Canvas& canvas,
      TFile* ofile,
      const std::string& header = ""
    ) const;

    // static methods
    static TFile*   OpenFile(const std::string& name, const std::string &option);
    static TObject* GrabObject(const std::string& object, TFile* file);

  private:

    // members
    PHEC::Style   m_basePlotStyle;
    PHEC::Style   m_baseTextStyle;
    PHEC::TextBox m_textBox;

    // helper methods
    Styles GenerateStyles(const Inputs& inputs) const;

};  // end Plotter

#endif

// end ========================================================================
