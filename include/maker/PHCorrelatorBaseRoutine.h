/// ===========================================================================
/*! \file    PHCorrelatorBaseRoutine.h
 *  \authors Derek Anderson
 *  \date    04.13.2024
 *
 *  Base plotting routine for
 *  the PlotMaker.
 */
/// ===========================================================================

#ifndef PHCORRELATORBASEROUTINE_H
#define PHCORRELATORBASEROUTINE_H

// c++ utilities
#include <algorithm>
// plotting utilities
#include "PHCorrelatorPlotMakerTypes.h"
#include "../elements/PHCorrelatorPlotterElements.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Base ENC Plotting Routine
  // ==========================================================================
  /*! Base class for plotting routines added to
   *  the PlotMaker.
   */
  class BaseRoutine {

    protected:

      // data members
      Style   m_basePlotStyle;
      Style   m_baseTextStyle;
      TextBox m_textBox;

      // ----------------------------------------------------------------------
      //! Generate list of styles to be applied
      // ----------------------------------------------------------------------
      Type::Styles GenerateStyles(const Type::Inputs& inputs) const {

        // fill styles with base
        Type::Styles styles( inputs.size() );
        std::fill( styles.begin(), styles.end(), m_basePlotStyle );

        // then update plot-specific elements
        for (std::size_t isty = 0; isty < inputs.size(); ++isty) {
          styles[isty].SetPlotStyle( inputs[isty].style );
        }
        return styles;

      }  // end 'GenerateStyles(Type::Inputs&)'

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Style   GetBasePlotStyle() const {return m_basePlotStyle;}
      Style   GetBaseTextStyle() const {return m_baseTextStyle;}
      TextBox GetTextBox()       const {return m_textBox;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetBasePlotStyle(const Style& style) {m_basePlotStyle = style;}
      void SetBaseTextStyle(const Style& style) {m_baseTextStyle = style;}
      void SetTextBox(const TextBox& text)      {m_textBox       = text;}

      // ----------------------------------------------------------------------
      //! Do plotting routine
      // ----------------------------------------------------------------------
      /*! Should be overwritten by derived routine.
       */
      virtual void Plot(TFile* /*ofile*/) {return;}

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      BaseRoutine()  {};
      ~BaseRoutine() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      explicit BaseRoutine(const Style& plot, const Style& text, const TextBox& box) {

        m_basePlotStyle = plot;
        m_baseTextStyle = text;
        m_textBox       = box;

      }  // end ctor(Style&, Style&, TextBox&)'

  };  // end BaseRoutine

}    // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================
