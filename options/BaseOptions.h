/// ===========================================================================
/*! \file   BaseOptions.h
 *  \author Derek Anderson
 *  \date   12.27.2024
 *
 *  A small namespace to collect all of the general options for
 *  the `PHCorrelatorPlotMaker` class (i.e. plotting options
 *  constant across multiple plotting routines).
 */
/// ===========================================================================

#ifndef BASEOPTIONS_H
#define BASEOPTIONS_H

// c++ utilities
#include <iostream>
#include <string>
#include <vector>
// plotting utilities
#include "../include/PHCorrelatorPlotter.h"
// plotting options
#include "InputOutput.h"



// ============================================================================
//! Base/General Plotting Options
// ============================================================================
/*! This namespace collects all the generic parameters associated with
 *  the `PHCorrelatorPlotMaker` routines, i.e. anything common across
 *  multiple routines.
 */
namespace BaseOptions {

  // --------------------------------------------------------------------------
  //! Define base plotting style
  // --------------------------------------------------------------------------
  /*! This defines the various style components
   *  for plottable-things (e.g. histograms, graphs,
   *  etc.) to be used across multiple plotting
   *  routines.
   */
  PHEC::Style BasePlotStyle() {

    // define text, axis label styles
    PHEC::Style::Text  text  = PHEC::Style::Text(1, 42);
    PHEC::Style::Label label = PHEC::Style::Label(1, 42, 0.03);

    // define axis title styles
    //   [0] = x
    //   [1] = y
    //   [2] = z
    std::vector<PHEC::Style::Title> titles;
    titles.push_back( PHEC::Style::Title(1, 1, 42, 0.04, 1.0) );
    titles.push_back( PHEC::Style::Title(1, 1, 42, 0.04, 1.2) );
    titles.push_back( PHEC::Style::Title(1, 1, 42, 0.04, 1.2) );

    // collect style components
    PHEC::Style style;
    style.SetTextStyle( text );
    style.SetLabelStyles( label );
    style.SetTitleStyles( titles );
    return style;

  }  // end 'BasePlotStyle()'



  // --------------------------------------------------------------------------
  //! Define base text style
  // --------------------------------------------------------------------------
  /*! This defines the various style components for
   *  text boxes (TPaveText, TLegend, etc.) to be
   *  used across multiple plotting routines.
   */ 
  PHEC::Style BaseTextStyle() {

    // define needed style components
    //   - note that the marker is unused for text boses
    PHEC::Style::Plot plot = PHEC::Style::Plot(0, 1, 0, 0, 1);
    PHEC::Style::Text text = PHEC::Style::Text(1, 42, 12, 0.05);

    // collect style components
    PHEC::Style style;
    style.SetPlotStyle( plot );
    style.SetTextStyle( text );
    return style;

  }  // end 'BaseTextStyle()'



  // --------------------------------------------------------------------------
  //! Define text box
  // --------------------------------------------------------------------------
  /*! This method defines the text box (a TPaveText)
   *  which holds information (e.g. about which
   *  simulation was used for the plots).
   */ 
  PHEC::TextBox Text(const int species = InFiles::PP) {

    std::string system("");
    switch (species) {
      case InFiles::PP:
        system += "p+p collisions";
        break;
      case InFiles::PAu:
        system += "p+Au collisions";
        break;
      default:
        std::cerr << "WARNING: unknown option " << species << "!" << std::endl;
        break;
    }

    // set text to display
    PHEC::Type::TextList lines;
    lines.push_back("#bf{#it{PHENIX}} Run-15");
    lines.push_back(system);

    // grab base text style for line spacing
    const PHEC::Style& style = BaseTextStyle();

    // get text box height
    const float height = PHEC::Tools::GetHeight(
      lines.size(),
      style.GetTextStyle().spacing
    );

    // set box dimenisons
    PHEC::Type::Vertices vertices;
    vertices.push_back(0.1);
    vertices.push_back(0.1);
    vertices.push_back(0.3);
    vertices.push_back((float) 0.1 + height);

    // return text box definition
    return PHEC::TextBox(lines, vertices);

  }  // end 'Text(int)'

}  // end BaseOptions namespace

#endif

// end ========================================================================
