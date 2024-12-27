/// ===========================================================================
/*! \file   PHCorrelatorPlotter.cc
 *  \author Derek Anderson
 *  \date   11.12.2024
 *
 *  Class to consolidate plotting routines associated with
 *  the PHENIX ENC analysis.
 */
/// ===========================================================================

#define PHCORRELATORPLOTTER_CC

// class definition
#include "PHCorrelatorPlotter.h"

// c++ utilities
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
// root libraries
#include <TCanvas.h>
#include <TFile.h>
#include <TH1.h>
#include <TLegend.h>



// ctor/dtor ==================================================================

// ----------------------------------------------------------------------------
//! default ctor
// ----------------------------------------------------------------------------
PHCorrelatorPlotter::PHCorrelatorPlotter() {

  //... nothing to do ...//

}  // end ctor()



// ----------------------------------------------------------------------------
//! default dtor
// ----------------------------------------------------------------------------
PHCorrelatorPlotter::~PHCorrelatorPlotter() {

  //... nothing to do ...//

}  // end dtor()



// ----------------------------------------------------------------------------
//! ctor accepting arguments
// ----------------------------------------------------------------------------
PHCorrelatorPlotter::PHCorrelatorPlotter(
  const PHEC::Style& plot,
  const PHEC::Style& text,
  const PHEC::TextBox& box
) {

  m_basePlotStyle = plot;
  m_baseTextStyle = text;
  m_textBox       = box;

}  // end ctor(PHEC::Style&, PHEC::Style&, PHEC::TextBox&)'



// public methods =============================================================

// ----------------------------------------------------------------------------
//! Compare various ENC (or othwerise) spectra
// ----------------------------------------------------------------------------
void PHCorrelatorPlotter::CompareSpectra(
  const Inputs& inputs,
  const PHEC::Range& range,
  const PHEC::Canvas& canvas,
  TFile* ofile,
  const std::string& header
) const {

  /* TODO fill in */
  return;

}  // end 'CompareSpectra(Inputs&, PHEC::Range&, PHEC::Canvas&, TFile*, std::string&)'



// ----------------------------------------------------------------------------
//! Compare various ENC (or othwerise) spectra to a baseline
// ----------------------------------------------------------------------------
void PHCorrelatorPlotter::CompareSpectraToBaseline(
  const PHEC::PlotInput& in_denom,
  const Inputs& in_numers,
  const PHEC::Range& range,
  const PHEC::Canvas& canvas,
  TFile* ofile,
  const std::string& header
) const {

  /* TODO fill in */
  return;

}  // end 'CompareSpectraToBaseline(PHEC::PlotInput&, Inputs&, PHEC::Range&, PHEC::Canvas&, TFile*, std::string&)'



// ----------------------------------------------------------------------------
//! Compare ratios of various pairs of ENC (or otherwise) spectra
// ----------------------------------------------------------------------------
void PHCorrelatorPlotter::CompareRatios(
  const Inputs& in_denoms,
  const Inputs& in_numers,
  const PHEC::Range& range,
  const PHEC::Canvas& canvas,
  TFile* ofile,
  const std::string& header
) const {

  /* TODO fill in */
  return;

}  // end 'CompareRatios(Inputs&, Inputs&, PHEC::Range&, PHEC::Canvas&, TFile*, std::string&)'



// static methods =============================================================

// ----------------------------------------------------------------------------
//! Open file and check if good
// ----------------------------------------------------------------------------
TFile* PHCorrelatorPlotter::OpenFile(const std::string& name, const std::string& option) {

  // try to open file, throw error if not able
  TFile* file = new TFile( name.data(), option.data() );
  if (!file) {
    std::cerr << "PANIC: couldn't open file!\n"
              << "       file = " << name << "\n"
              << std::endl;
    assert(file);
  }

  // then check file by cd'ing into it
  const bool isGoodCD = file -> cd();
  if (!isGoodCD) {
    std::cerr << "PANIC: couldn't cd into file!\n"
              << "       file = " << name << "\n"
              << std::endl;
    assert(isGoodCD);
  }
  return file;

}  // end 'OpenFile(std::string&, std::string&)'



// ----------------------------------------------------------------------------
//! Grab an object from a file
// ----------------------------------------------------------------------------
TObject* PHCorrelatorPlotter::GrabObject(const std::string& object, TFile* file) {

   // try to grab object from file, throw error if not able
   TObject* grabbed = (TObject*) file -> Get( object.data() );
   if (!grabbed) {
     std::cerr << "PANIC: couldn't grab object!\n"
               << "       file   = " << file   << "\n"
               << "       object = " << object << "\n"
               << std::endl;
     assert(grabbed);
   }
   return grabbed;

}  // end 'GrabObject(std::string&, TFile*)'



// private methods ============================================================

// ----------------------------------------------------------------------------
//! Generate list of styles to be applied
// ---------------------------------------------------------------------------- 
Styles PHCorrelatorPlotter::GenerateStyles(const Inputs& inputs) const {

  // fill styles with base
  Styles styles( inputs.size() );
  std::fill( styles.begin(), styles.end(), m_basePlotStyle );

  // then update plot-specific elements
  for (std::size_t isty = 0; isty < inputs.size(); ++isty) {
    styles[isty].SetPlotStyle( inputs[isty].style );
  }
  return styles;

}  // end 'GenerateStyles(Inputs&)'

// end ========================================================================
