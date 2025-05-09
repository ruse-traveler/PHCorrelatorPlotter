/// ===========================================================================
/*! \file   PHCorrelatorHistInput.h
 *  \author Derek Anderson
 *  \date   03.20.2025
 *
 *  Helper class to manage histograms
 *  and associated strings.
 */
/// ===========================================================================

#ifndef PHCORRELATORHISTINPUT_H
#define PHCORRELATORHISTINPUT_H

// c++ utilities
#include <string>
#include <vector>
// plotting utilities
#include "PHCorrelatorIOTypes.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Input histogram database
  // ==========================================================================
  /*! A small helper class to manage histograms
   *  and associated strings.
   */
  class HistInput {

    public:

      enum PtJet {Pt5, Pt10, Pt15, PtInt};
      enum Chrg  {Pos, Neg, ChInt};
      enum Spin  {BU, BD, YU, YD, BUYU, BUYD, BDYU, BDYD, SpInt};

    private:

      // data members
      Type::Strings m_tags_pt;
      Type::Strings m_tags_ch;
      Type::Strings m_tags_sp;
      Type::Strings m_legs_pt;
      Type::Strings m_legs_ch;
      Type::Strings m_legs_sp;

      // ----------------------------------------------------------------------
      //! Define pt hist tags and legend text
      // ----------------------------------------------------------------------
      /*! All histogram tags and legend entries associated
       *  with the jet pt should be defined here, and then
       *  retrieved with the accessor functions.
       *
       *  FIXME make configurable(?)
       */ 
      void LoadPtStrings() {

        // define tags
        m_tags_pt.clear();
        m_tags_pt.push_back("pt0");
        m_tags_pt.push_back("pt1");
        m_tags_pt.push_back("pt2");
        m_tags_pt.push_back("ptINT");

        // define legends
        m_legs_pt.clear();
        m_legs_pt.push_back("p_{T}^{jet} #in (5, 10) GeV/c");
        m_legs_pt.push_back("p_{T}^{jet} #in (10, 15) GeV/c");
        m_legs_pt.push_back("p_{T}^{jet} #in (15, 20) GeV/c");
        m_legs_pt.push_back("p_PT}^{jet} > 5 GeV/c");
        return;

      }  // end 'LoadPtStrings()'

      // ----------------------------------------------------------------------
      //! Define jet charge hist tags and legend text
      // ----------------------------------------------------------------------
      /*! All histogram tags and legend entries associated
       *  with the jet charge should be defined here, and
       *  then retrieved with the accessor functions.
       *
       *  FIXME make configurable(?)
       */
      void LoadChargeStrings() {

        // define tags
        m_tags_ch.clear();
        m_tags_ch.push_back("ch0");
        m_tags_ch.push_back("ch1");

        // define legends
        m_legs_ch.clear();
        m_legs_ch.push_back("jet charge < 0");
        m_legs_ch.push_back("jet charge > 0");
        return;

      }  // end 'LoadChargeStrings()'

      // ----------------------------------------------------------------------
      //! Load spin hist tags and legend text
      // ----------------------------------------------------------------------
      /*! All histogram tags and legend entries associated
       *  with the spin should be defined here, and then
       *  retrieved with the accessor functions.
       *
       *  FIXME make configurable(?)
       */ 
      void LoadSpinStrings() {

        // define tags
        m_tags_sp.clear();
        m_tags_sp.push_back("spBU");
        m_tags_sp.push_back("spBD");
        m_tags_sp.push_back("spYU");
        m_tags_sp.push_back("spYD");
        m_tags_sp.push_back("spBUYU");
        m_tags_sp.push_back("spBUYD");
        m_tags_sp.push_back("spBDYU");
        m_tags_sp.push_back("spBDYD");
        m_tags_sp.push_back("spINT");

        // define legends
        m_legs_sp.clear();
        m_legs_sp.push_back("B#uparrow");
        m_legs_sp.push_back("B#downarrow");
        m_legs_sp.push_back("Y#uparrow");
        m_legs_sp.push_back("Y#downarrow");
        m_legs_sp.push_back("B#uparrowY#uparrow");
        m_legs_sp.push_back("B#uparrowY#downarrow");
        m_legs_sp.push_back("B#downarrowY#uparrow");
        m_legs_sp.push_back("B#downarrowY#downarrow");
        m_legs_sp.push_back("Integrated");
        return;

      }  // end 'LoadSpinStrings()'

    public:

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetPtTags(const Type::Strings& tags)        {m_tags_pt = tags;}
      void SetChargeTags(const Type::Strings& tags)    {m_tags_ch = tags;}
      void SetSpinTags(const Type::Strings& tags)      {m_tags_sp = tags;}
      void SetPtLegends(const Type::Strings& legs)     {m_legs_pt = legs;}
      void SetChargeLegends(const Type::Strings& legs) {m_legs_ch = legs;}
      void SetSpinLegends(const Type::Strings& legs)   {m_legs_sp = legs;}

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Type::Strings GetPtTags()        const {return m_tags_pt;}
      Type::Strings GetChargeTags()    const {return m_tags_ch;}
      Type::Strings GetSpinTags()      const {return m_tags_sp;}
      Type::Strings GetPtLegends()     const {return m_legs_pt;}
      Type::Strings GetChargeLegends() const {return m_legs_ch;}
      Type::Strings GetSpinLegends()   const {return m_legs_sp;}

      // ----------------------------------------------------------------------
      //! Get a particular tag, legend text
      // ----------------------------------------------------------------------
      std::string GetPtTag(const int pt)        const {return m_tags_pt.at(pt);}
      std::string GetChargeTag(const int ch)    const {return m_tags_ch.at(ch);}
      std::string GetSpinTag(const int sp)      const {return m_tags_sp.at(sp);}
      std::string GetPtLegend(const int pt)     const {return m_legs_pt.at(pt);}
      std::string GetChargeLegend(const int ch) const {return m_legs_ch.at(ch);}
      std::string GetSpinLegend(const int sp)   const {return m_legs_sp.at(sp);}

      // ----------------------------------------------------------------------
      //! default ctor
      // ----------------------------------------------------------------------
      HistInput() {

        LoadPtStrings();
        LoadChargeStrings();
        LoadSpinStrings();

      };  // end ctor()

      // ----------------------------------------------------------------------
      //! default dtor
      // ----------------------------------------------------------------------
      ~HistInput() {};

  };    // end HistInput

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
