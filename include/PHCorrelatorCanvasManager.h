/// ===========================================================================
/*! \file    PHCorrelatorCanvasManager.h
 *  \authors Derek Anderson
 *  \date    12.26.2024
 *
 *  A class to manage a canvas and its associated pads.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTMANAGER_H
#define PHCORRELATORPLOTMANAGER_H

// c++ utilities
#include <iostream>
#include <string>
#include <utility>
#include <vector>
// root libraries
#include <TCanvas.h>
#include <TPad.h>
#include <TString.h>
// plotting utilities
#include "PHCorrelatorCanvas.h"
#include "PHCorrelatorPad.h"
#include "PHCorrelatorPlotTypes.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! ENC Plot (pad/canvas) manager
  // ==========================================================================
  /*! A small class to hold/organize the pointers
   *  to a TCanvas and all of its associated pads.
   */ 
  class CanvasManager {

    private:

      // canvas definition
      Canvas                m_define;
      TCanvas*              m_canvas;
      std::vector<TPad*>    m_pads;
      Type::LabelToIndexMap m_labtoindex;

      // ----------------------------------------------------------------------
      //! Generate label-to-index map for pads
      // ----------------------------------------------------------------------
      void MakeLabelToIndexMap() {

        for (std::size_t ipad = 0; ipad < m_pads.size(); ++ipad) {
          m_labtoindex[ m_define.GetPadLabel(ipad) ] = ipad;
        }
        return;

      }  // end 'MakeLabelToIndexMap()'

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Canvas             GetDefinition() const {return m_define;}
      TCanvas*           GetTCanvas()    const {return m_canvas;}
      std::vector<TPad*> GetTPads()      const {return m_pads;}

      // ----------------------------------------------------------------------
      //! Setters 
      // ----------------------------------------------------------------------
      void SetDefinition(const Canvas& define) {m_define = define;}

      // ----------------------------------------------------------------------
      //! Make canvas and pads 
      // ----------------------------------------------------------------------
      void MakePlot() {

        // create canvas/pads
        m_canvas = m_define.MakeTCanvas();
        m_pads   = m_define.MakeTPads();

        // generate lable-index map & exit
        MakeLabelToIndexMap();
        return;

      }  // end 'MakePlot()' '

      // ----------------------------------------------------------------------
      //! Draw canvas and pads
      // ----------------------------------------------------------------------
      void Draw() {

        m_canvas -> Draw();
        for (std::size_t ipad = 0; ipad < m_pads.size(); ++ipad) {
          m_pads[ipad] -> Draw();
        }
        return;

      }  // end 'Draw()'

      // ----------------------------------------------------------------------
      //! Write canvas
      // ----------------------------------------------------------------------
      void Write() {

        m_canvas -> Write();
        return;

      }  // end 'Write()'

      // ----------------------------------------------------------------------
      //! Close canvas
      // ----------------------------------------------------------------------
      void Close() {

        m_canvas -> Close();
        return;

      }  // end 'Close()'

      // ----------------------------------------------------------------------
      //! Get a specific pad via its index
      // ----------------------------------------------------------------------
      TPad* GetTPad(const std::size_t index) const {

        return m_pads.at( index );

      }  // end 'GetTPad(std::size_t)'

      // ----------------------------------------------------------------------
      //! Get a specific pad via its label
      // ----------------------------------------------------------------------
      TPad* GetTPad(const std::string& label) const {

        return m_pads.at( m_labtoindex.at(label) );

      }  // end 'GetTPad(std::string&)'

      // ----------------------------------------------------------------------
      //! default ctor/dtor 
      // ----------------------------------------------------------------------
      CanvasManager()  {};
      ~CanvasManager() {};

      // ----------------------------------------------------------------------
      //! ctor accepting a canvas definition
      // ----------------------------------------------------------------------
      CanvasManager(const Canvas& define) {
        m_define = define;
      }   // end ctor(Canvas&)' 

  };  // end CanvasManager

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
