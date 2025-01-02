/// ===========================================================================
/*! \file    PHCorrelatorPlotManager.hxx
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
  class PlotManager {

    private:

      // canvas definition
      Canvas m_define;

      // root members
      TCanvas*           m_canvas;
      std::vector<TPad*> m_pads;

      // pad-label-to-index map
      Type::LabelList       m_labels;
      Type::LabelToIndexMap m_labtoindex;

      // ----------------------------------------------------------------------
      //! Convert an index to a string
      // ----------------------------------------------------------------------
      std::string StringifyIndex(const std::size_t index) const {

        // create TString, add index
        TString tstr;
        tstr += index;

        // create std::string and return
        const std::string sstr(tstr.Data());
        return sstr;

      }  // end 'StringifyIndex(std::size_t)'

      // ----------------------------------------------------------------------
      //! Make a pad label
      // ----------------------------------------------------------------------
      std::string MakePadLabel(const std::size_t index) const {

        // by default use the index as a label
        std::string label = StringifyIndex(index);

        // but if corresponding label exists, use that
        if (index < m_labels.size()) {
          label = m_labels[index];
        }
        return label;

      }  // end 'MakePadLabel(std::size_t)'

      // ----------------------------------------------------------------------
      //! Make label-to-index map
      // ----------------------------------------------------------------------
      void MakeLabelToIndexMap() {

        // emit warning if size of label list and pad vector
        // are different
        if (m_labels.size() != m_define.GetPads().size()) {
          std::cerr << "WARNING: provided label list is NOT the same length as the list of pads to make!" << std::endl;
        }

        // create label-to-index map
        for (std::size_t ipad = 0; ipad < m_define.GetPads().size(); ++ipad) {
          const std::string label = MakePadLabel(ipad);
          m_labtoindex[label] = ipad;
        }
        return;

      }  // end 'MakeLabelToIndexMap()'

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Canvas             GetDefinition() const {return m_define;}
      TCanvas*           GetTCanvas()    const {return m_canvas;}
      Type::LabelList    GetPadLabels()  const {return m_labels;}
      std::vector<TPad*> GetTPads()      const {return m_pads;}

      // ----------------------------------------------------------------------
      //! Setters 
      // ----------------------------------------------------------------------
      void SetDefinition(const Canvas& define)         {m_define = define;}
      void SetPadLabels(const Type::LabelList& labels) {m_labels = labels;}

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
      //! Get a specific pad via its label
      // ----------------------------------------------------------------------
      TPad* GetTPad(const std::string& label) const {

        /* FIXME add size checks here */

        return m_pads[ m_labtoindex.at(label) ];

      }  // end 'GetTPad(std::string&)'

      // ----------------------------------------------------------------------
      //! Get a specific pad via its index
      // ----------------------------------------------------------------------
      TPad* GetTPad(const std::size_t index) const {

        /* FIXME add size checks here */

        return m_pads[ index ];

      }  // end 'GetTPad(std::size_t)'

      // ----------------------------------------------------------------------
      //! default ctor/dtor 
      // ----------------------------------------------------------------------
      PlotManager()  {};
      ~PlotManager() {};

      // ----------------------------------------------------------------------
      //! ctor accepting a canvas definition and possibly a
      //  list of pad labels
      // ----------------------------------------------------------------------
      PlotManager(
        const Canvas& define,
        const Type::LabelList& padlabels = Type::LabelList()
      ) {

        m_define = define;
        if (!padlabels.empty()) {
          m_labels = padlabels;
        }

      }   // end ctor(Canvas&)' 

  };  // end PlotManager

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
