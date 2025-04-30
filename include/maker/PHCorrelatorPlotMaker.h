/// ===========================================================================
/*! \file    PHCorrelatorPlotMaker.h
 *  \authors Derek Anderson
 *  \date    04.28.2025
 *
 *  Driver class to consolidate plotting routines associated with
 *  the PHENIX ENC analysis.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTMAKER_H
#define PHCORRELATORPLOTMAKER_H

// c++ utilities
#include <map>
#include <string>
#include <utility>
// plotting utilities
#include "PHCorrelatorPlotMakerDefault.h"
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



namespace PHEnergyCorrelator {

  // ============================================================================
  //! ENC Plot Maker
  // ============================================================================
  /*! This class consolidates plotting routines associated
   *  with the PHENIX ENC analysis.
   */
  class PlotMaker {

    private:

      // members
      bool    m_isInit;
      Style   m_basePlotStyle;
      Style   m_baseTextStyle;
      TextBox m_textBox;

      // routines
      CorrectSpectra1D m_corrSpec1D;
      CorrectSpectra2D m_corrSpec2D;
      PlotRatios1D     m_plotRatio1D;
      PlotRatios2D     m_plotRatio2D;
      PlotSpectra1D    m_plotSpec1D;
      PlotSpectra2D    m_plotSpec2D;
      PlotVsBaseline1D m_plotVsBase1D;
      PlotVsBaseline2D m_plotVsBase2D;

      // ----------------------------------------------------------------------
      //! Initialize plotting routines
      // ----------------------------------------------------------------------
      void InitRoutines() {

        m_corrSpec1D   = CorrectSpectra1D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        m_corrSpec2D   = CorrectSpectra2D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        m_plotRatio1D  = PlotRatios1D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        m_plotRatio2D  = PlotRatios2D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        m_plotSpec1D   = PlotSpectra1D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        m_plotSpec2D   = PlotSpectra2D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        m_plotVsBase1D = PlotVsBaseline1D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        m_plotVsBase2D = PlotVsBaseline2D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        return;

      }  // end 'InitRoutines()'

    public:

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetBasePlotStyle(const Style& style) {m_basePlotStyle = style;}
      void SetBaseTextStyle(const Style& style) {m_baseTextStyle = style;}
      void SetTextBox(const TextBox& text)      {m_textBox       = text;}

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Style   GetBasePlotStyle() const {return m_basePlotStyle;}
      Style   GetBaseTextStyle() const {return m_baseTextStyle;}
      TextBox GetTextBox()       const {return m_textBox;}

      // ----------------------------------------------------------------------
      //! Routine accessors
      // ----------------------------------------------------------------------
      CorrectSpectra1D& GetCorrectSpectra1D() {return m_corrSpec1D;}
      CorrectSpectra2D& GetCorrectSpectra2D() {return m_corrSpec2D;}
      PlotRatios1D&     GetPlotRatios1D()     {return m_plotRatio1D;}
      PlotRatios2D&     GetPlotRatios2D()     {return m_plotRatio2D;}
      PlotSpectra1D&    GetPlotSpectra1D()    {return m_plotSpec1D;}
      PlotSpectra2D&    GetPlotSpectra2D()    {return m_plotSpec2D;}
      PlotVsBaseline1D& GetPlotVsBaseline1D() {return m_plotVsBase1D;}
      PlotVsBaseline2D& GetPlotVsBaseline2D() {return m_plotVsBase2D;}

      // ----------------------------------------------------------------------
      //! Initialize maker by loading default routines
      // ----------------------------------------------------------------------
      /*! Note that calling after using the ctor accepting arguments,
       *  does nothing. If using the default ctor, this should be called
       *  after setting data members to load the default routines.
       */ 
      void Init() {

        if (!m_isInit) {
          InitRoutines();
          m_isInit = true;
        }
        return;

      } // end 'Init()'

      // ----------------------------------------------------------------------
      //! Default ctor
      // ----------------------------------------------------------------------
      PlotMaker() : m_isInit(false) {};

      // ----------------------------------------------------------------------
      //! Default dtor
      // ----------------------------------------------------------------------
      ~PlotMaker() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      PlotMaker(
        const Style& plot,
        const Style& text,
        const TextBox& box = TextBox()
      ) {

        // set base styles
        m_basePlotStyle = plot;
        m_baseTextStyle = text;
        m_textBox       = box;

        // now initialize routines
        InitRoutines();
        m_isInit = true;

      }  // end ctor(Style&, Style&, TextBox&)'

  };  // end PlotMaker

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
