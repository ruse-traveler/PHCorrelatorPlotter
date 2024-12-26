/// ===========================================================================
/*! \file    PHCorrelatorTextBox.hxx
 *  \authors Derek Anderson
 *  \date    12.26.2024
 *
 *  Definition of a text box.
 */
/// ===========================================================================

#ifndef PHCORRELATORTEXTBOX_H
#define PHCORRELATORTEXTBOX_H

// c++ utilities
#include <string>
// root libraries
#include <TPaveText.h>
// plotting utilities
#include "PHCorrelatorPlotTypes.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Text box definition
  // ==========================================================================
  /*! A small class to consolidate necessary data
   *  to define a TPaveText
   */
  class TextBox {

    private:

      // data members
      Types::TextList m_text;
      Types::Vertices m_vtxs;
      std::string     m_opt = "NDC NB";

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Types::TextList GetText()     const {return m_text;}
      Types::Vertices GetVertices() const {return m_vtxs;}
      std::string     GetOption()   const {return m_opt;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetText(const Types::TextList& text)     {m_text = text;}
      void SetVertices(const Types::Vertices& vtxs) {m_vtxs = vtxs;}
      void SetOption(const std::string& opt)        {m_opt  = opt;}

      // ----------------------------------------------------------------------
      //! Add a line of text
      // ----------------------------------------------------------------------
      void AddText(const std::string& line) {

        m_text.push_back( line );
        return;

      }  // end 'AddText(std::string&)'

      // ----------------------------------------------------------------------
      //! Create a TPaveText*
      // ----------------------------------------------------------------------
      TPaveText* MakeTPaveText() {

        TPaveText* pt = new TPaveText(
          m_vtxs[0],
          m_vtxs[1],
          m_vtxs[2],
          m_vtxs[3],
          m_opt.data()
        );

        for (const std::string& text : m_text) {
          pt -> AddText( text.data() );
        }
        return pt;

      }  // end 'MakeTPaveText()'
 
      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      TextBox()  {};
      ~TextBox() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      TextBox(
        const Types::TextList& text, 
        const Types::Vertices& vtxs,
        const std::string& opt = "NDC NB"
      ) {

        m_text = text;
        m_vtxs = vtxs;
        m_opt  = opt;

      }  // end ctor(Types::TextList&, Types::Vertices&, std::string&)'

  };  // end TextBox

}  // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
