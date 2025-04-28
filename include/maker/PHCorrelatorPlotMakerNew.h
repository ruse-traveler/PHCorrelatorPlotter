/// ===========================================================================
/*! \file    PHCorrelatorPlotMakerNew.h
 *  \authors Derek Anderson
 *  \date    04.28.2025
 *
 *  Driver class to consolidate plotting routines associated with
 *  the PHENIX ENC analysis.
 *
 *  FIXME remove "NEW" once swapped in.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTMAKERNEW_H
#define PHCORRELATORPLOTMAKERNEW_H

// c++ utilities
#include <map>
#include <string>
#include <utility>
// plotting utilities
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
  //! ENC Plot Maker (NEW)
  // ============================================================================
  /*! This class consolidates plotting routines associated
   *  with the PHENIX ENC analysis.
   */
  class PlotMakerNew {

    public:

      typedef std::map<std::string, BaseRoutine*>           RoutineMap;
      typedef std::map<std::string, BaseRoutine*>::iterator it_routine;

    private:

      // members
      bool       m_isInit;
      Style      m_basePlotStyle;
      Style      m_baseTextStyle;
      TextBox    m_textBox;
      RoutineMap m_routines;

      // ----------------------------------------------------------------------
      //! Load default plotting routines
      // ----------------------------------------------------------------------
      void LoadDefaultRoutines() {

        m_routines["CorrectSpectra1D"] = new CorrectSpectra1D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        m_routines["CorrectSpectra2D"] = new CorrectSpectra2D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        m_routines["PlotRatios1D"]     = new PlotRatios1D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        m_routines["PlotRatios2D"]     = new PlotRatios2D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        m_routines["PlotSpectra1D"]    = new PlotSpectra1D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        m_routines["PlotSpectra2D"]    = new PlotSpectra2D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        m_routines["PlotVsBaseline1D"] = new PlotVsBaseline1D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        m_routines["PlotVsBaseline2D"] = new PlotVsBaseline2D(m_basePlotStyle, m_baseTextStyle, m_textBox);
        return;

      }  // end 'LoadDefaultRoutines()'

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Style       GetBasePlotStyle() const {return m_basePlotStyle;}
      Style       GetBaseTextStyle() const {return m_baseTextStyle;}
      TextBox     GetTextBox()       const {return m_textBox;}
      std::size_t GetNRoutines()     const {return m_routines.size();}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetBasePlotStyle(const Style& style) {m_basePlotStyle = style;}
      void SetBaseTextStyle(const Style& style) {m_baseTextStyle = style;}
      void SetTextBox(const TextBox& text)      {m_textBox       = text;}

      // ----------------------------------------------------------------------
      //! Initialize maker by loading default routines
      // ----------------------------------------------------------------------
      /*! Note that calling after using the ctor accepting arguments,
       *  does nothing. If using the default ctor, this should be called
       *  after setting data members to load the default routines.
       */ 
      void Init() {

        if (!m_isInit) {
          LoadDefaultRoutines();
        }
        return;

      } // end 'Init()'

      // ----------------------------------------------------------------------
      //! Add a routine
      // ----------------------------------------------------------------------
      void AddRoutine(const std::string& name, BaseRoutine* routine) {

        m_routines.insert( std::make_pair(name, routine) );
        return;

      }  // end 'AddRoutine(std::string&, BaseRoutine*)'

      // ----------------------------------------------------------------------
      //! Access a particular routine
      // ----------------------------------------------------------------------
      BaseRoutine* operator () (const std::string& name) const {

        return m_routines.at(name);

      }  // end ()(std::string&)

      // ----------------------------------------------------------------------
      //! Default ctor
      // ----------------------------------------------------------------------
      PlotMakerNew() : m_isInit(false) {};

      // ----------------------------------------------------------------------
      //! Default dtor
      // ----------------------------------------------------------------------
      ~PlotMakerNew() {

        // clean up pointers to routines
        for (it_routine itr = m_routines.begin(); itr != m_routines.end(); ++itr) {
          if (itr -> second) {
            delete itr -> second;
            itr -> second = NULL;
          }
        }

      }  // end dtor

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      PlotMakerNew(
        const Style& plot,
        const Style& text,
        const TextBox& box = TextBox()
      ) {

        // set base styles
        m_basePlotStyle = plot;
        m_baseTextStyle = text;
        m_textBox       = box;

        // now load default routines
        LoadDefaultRoutines();
        m_isInit = true;

      }  // end ctor(Style&, Style&, TextBox&)'

  };  // end PlotMakerNew

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
