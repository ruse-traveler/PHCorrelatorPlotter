/// ===========================================================================
/*! \file    PHCorrelatorLegend.hxx
 *  \authors Derek Anderson
 *  \date    12.26.2024
 *
 *  Definition of a legend.
 */
/// ===========================================================================

#ifndef PHCORRELATORLEGEND_HXX
#define PHCORRELATORLEGEND_HXX

// c++ utilities
#include <string>
#include <vector>
// root libraries
#include <TLegend.h>
#include <TObject.h>
// plotting utilities
#include "PHCorrelatorPlotTools.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Legend definition
  // ==========================================================================
  /*! A small class to consolidate necessary data
   *  to define a TLegend.
   */ 
  class Legend {

    public:

      // ======================================================================
      //! Legend entry
      // ======================================================================
      /*! A small struct to consolidate the data for an individual
       *  entry in a TLegend.
       */
      struct Entry {

        // members
        TObject*    object;
        std::string label;
        std::string option = "PF";

        // --------------------------------------------------------------------
        // default ctor/dtor
        // --------------------------------------------------------------------
        Entry()  {};
        ~Entry() {};

        // --------------------------------------------------------------------
        // ctor accepting arguments
        // --------------------------------------------------------------------
        Entry(
          TObject* obj,
          const std::string& lbl,
          const std::string& opt = "PF"
        ) {
          object = obj;
          label  = lbl;
          option = opt;
        }  // end ctor (TOject*, std::string x 2)

      };  // end Entry

    private:

      // data members
      Tools::Vertices    m_vtxs;
      std::string        m_header = "";
      std::vector<Entry> m_entries;

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Tools::Vertices    GetVertices() const {return m_vtxs;}
      std::string        GetHeader()   const {return m_header;}
      std::vector<Entry> GetEntries()  const {return m_entries;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetVertices(const Tools::Vertices& vtxs)      {m_vtxs    = vtxs;}
      void SetHeader(const std::string& hdr)             {m_header  = hdr;}
      void SetEntries(const std::vector<Entry>& entries) {m_entries = entries;}

      // ----------------------------------------------------------------------
      //! Add an entry
      // ----------------------------------------------------------------------
      void AddEntry(const Entry& entry) {

        m_entries.emplace_back( entry );
        return;

      }  // end 'AddEntry(Entry&)'

      // ----------------------------------------------------------------------
      //! Create a TLegend
      // ----------------------------------------------------------------------
      TLegend* MakeLegend() {

        TLegend* leg = new TLegend(
          m_vtxs[0],
          m_vtxs[1],
          m_vtxs[2],
          m_vtxs[3],
          m_header.data()
        );
        for (const Entry& entry : m_entries) {
          leg -> AddEntry( entry.object, entry.label.data(), entry.option.data() );
        }
        return leg;

      }  // end 'MakeLegend()

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      Legend()  {};
      ~Legend() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments 
      // ----------------------------------------------------------------------
      Legend(
        const Tools::Vertices& vtxs,
        const std::vector<Entry>& entries,
        const std::string& hdr = ""
      ) {

        m_vtxs    = vtxs;
        m_header  = hdr;
        m_entries = entries;

      };  // end ctor(Tools::Vertices&, std::vector<Entry>&, std::string&)'

  };  // end Legend

}  // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
