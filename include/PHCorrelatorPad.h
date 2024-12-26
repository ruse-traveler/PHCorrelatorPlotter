/// ===========================================================================
/*! \file    PHCorrelatorPad.h
 *  \authors Derek Anderson
 *  \date    12.26.2024
 *
 *  Definition of a canvas pad.
 */
/// ===========================================================================

#ifndef PHCORRELATORPAD_H
#define PHCORRELATORPAD_H

// c++ utilities
#include <utility>
// root libraries
#include <TPad.h>
// plotting utilities
#include "PHCorrelatorPadOpts.h"
#include "PHCorrelatorPlotTypes.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Pad definition
  // ==========================================================================
  /*! A small class to consolidate necessary data
   *  to define and work with a TPad 
   */  
  class Pad {

    private:

      // members
      PadOpts         m_opts;
      Types::Vertices m_vtxs;
      Types::Margins  m_mgns;
      std::string     m_name;
      std::string     m_title = "";

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      PadOpts         GetOptions()  const {return m_opts;}
      Types::Vertices GetVertices() const {return m_vtxs;}
      Types::Margins  GetMargins()  const {return m_mgns;}
      std::string     GetName()     const {return m_name;}
      std::string     GetTitle()    const {return m_title;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetOptions(const PadOpts& opts)          {m_opts  = opts;}
      void SetVertices(const Types::Vertices& vtxs) {m_vtxs  = vtxs;}
      void SetMargins(const Types::Margins& mgns)   {m_mgns  = mgns;}
      void SetName(const std::string& name)         {m_name  = name;}
      void SetTitle(const std::string& ttl)         {m_title = ttl;}

      // ----------------------------------------------------------------------
      //! Create a TPad 
      // ----------------------------------------------------------------------
      TPad* MakeTPad() const {

        // create pad
        TPad* pad = new TPad(
          m_name.data(),
          m_title.data(),
          m_vtxs[0],
          m_vtxs[1],
          m_vtxs[2],
          m_vtxs[3]
        );

        // set margins
        pad -> SetTopMargin( m_mgns[Types::Margin::Top] );
        pad -> SetRightMargin( m_mgns[Types::Margin::Right] );
        pad -> SetBottomMargin( m_mgns[Types::Margin::Bottom] );
        pad -> SetLeftMargin( m_mgns[Types::Margin::Left] );

        // apply options and return pointer
        m_opts.Apply(pad);
        return pad;

      }  // end 'MakeTPad()'

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      Pad()  {};
      ~Pad() {};

      // ----------------------------------------------------------------------
      //! ctor accepting all members
      // ----------------------------------------------------------------------
      Pad(
        const std::string& name,
        const std::string& title,
        const Types::Vertices& vtxs,
        const Types::Margins& mgns,
        const PadOpts& opts
      ) {

        m_name  = name;
        m_title = title;
        m_vtxs  = vtxs;
        m_mgns  = mgns;
        m_opts  = opts;

      }  // end ctor(std::string& x 2, Types::Vertices&, Types::Margins&, PadOpts&)'

  };  // end Pad

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
