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
/*! Compares a variety of ENC (or otherwise) spectra from different sources.
 *
 *  \param[in]  inputs list of objects to plot and their details
 *  \param[in]  range  (x, y) ranges to plot
 *  \param[in]  canvas definition of the canvas to draw on
 *  \param[out] ofile  file to write to
 *  \param[in]  header optionally, can provide header for legend
 */
void PHCorrelatorPlotter::CompareSpectra(
  const Inputs& inputs,
  const PHEC::Range& range,
  const PHEC::Canvas& canvas,
  TFile* ofile,
  const std::string& header
) const {

  // announce start
  std::cout << "\n -------------------------------- \n"
            << "  Beginning spectra plotting!\n"
            << "    Opening inputs:"
            << std::endl;

  // open inputs
  std::vector<TFile*> ifiles;
  std::vector<TH1*>   ihists;
  for (std::size_t iin = 0; iin < inputs.size(); ++iin) {

    ifiles.push_back(
      OpenFile(inputs[iin].file, "read")
    );
    ihists.push_back(
      (TH1*) GrabObject( inputs[iin].object, ifiles.back() )
    );
    ihists.back() -> SetName( inputs[iin].rename.data() );
    std::cout << "      File = " << inputs[iin].file << "\n"
              << "      Hist = " << inputs[iin].object
              << std::endl;

  }  // end input loop

  // define legend dimensions
  const std::size_t nlines    = !header.empty() ? ihists.size() + 1 : ihists.size();
  const float       spacing   = m_baseTextStyle.GetTextStyle().spacing;
  const float       legheight = PHEC::Tools::GetHeight(nlines, spacing);

  // generate legend vertices
  PHEC::Type::Vertices vtxleg;
  vtxleg.push_back(0.3);
  vtxleg.push_back(0.1);
  vtxleg.push_back(0.5);
  vtxleg.push_back((float) 0.1 + legheight);

  // define legend
  PHEC::Legend legdef;
  for (std::size_t ihst = 0; ihst < ihists.size(); ++ihst) {
    legdef.AddEntry( PHEC::Legend::Entry(ihists[ihst], inputs[ihst].legend, "PF") );
  }
  legdef.SetVertices( vtxleg );
  if (!header.empty()) {
    legdef.SetHeader( header );
  }

  // create root objects
  TLegend*   legend = legdef.MakeLegend();
  TPaveText* text   = m_textBox.MakeTPaveText();
  std::cout << "    Created legend and text box." << std::endl;

  // set hist styles
  Styles styles = GenerateStyles( inputs );
  for (std::size_t ihst = 0; ihst < ihists.size(); ++ihst) {
    styles[ihst].SetPlotStyle( inputs[ihst].style );
    styles[ihst].Apply( ihists[ihst] );
    ihists[ihst] -> GetXaxis() -> SetRangeUser( range.x.first, range.x.second );
    ihists[ihst] -> GetYaxis() -> SetRangeUser( range.y.first, range.y.second );
  }

  // set legend/text styles
  m_baseTextStyle.Apply( legend );
  m_baseTextStyle.Apply( text );
  std::cout << "    Set styles." << std::endl;

  // draw plot
  PHEC::PlotManager manager = PHEC::PlotManager( canvas );
  manager.MakePlot();
  manager.Draw();
  manager.GetTCanvas() -> cd();
  ihists[0] -> Draw();
  for (std::size_t ihst = 1; ihst < ihists.size(); ++ihst) {
    ihists[ihst] -> Draw("same");
  }
  legend -> Draw();
  text   -> Draw();
  std:: cout << "    Made plot." << std::endl;

  // save output
  ofile -> cd();
  for (std::size_t ihst = 0; ihst < ihists.size(); ++ihst) {
    ihists[ihst] -> Write();
  }
  manager.Write();
  manager.Close();
  std::cout << "    Saved output." << std::endl;

  // close input files
  for (std::size_t iin = 0; iin < ifiles.size(); ++iin)  {
    ifiles[iin] -> cd();
    ifiles[iin] -> Close();
  }
  std::cout << "    Closed input files." << std::endl;

  // announce end
  std::cout << "  Finished spectra plotting!\n"
            << " -------------------------------- \n"
            << endl;

  // exit routine
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
