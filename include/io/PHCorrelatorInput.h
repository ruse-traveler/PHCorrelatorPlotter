/// ===========================================================================
/*! \file   PHCorrelatorInput.h
 *  \author Derek Anderson
 *  \date   03.20.2025
 *
 *  Wrapper class to hold PHCorrelatorFileInput and
 *  PHCorrelatorHistInput classes.
 */
/// ===========================================================================

#ifndef PHCORRELATORINPUT_H
#define PHCORRELATORINPUT_H

// c++ utilities
#include <string>
#include <vector>
// plotting utilities
#include "PHCorrelatorFileInput.h"
#include "PHCorrelatorHistInput.h"
#include "PHCorrelatorIOTypes.h"



namespace PHEnergyCorrelator {

  // ============================================================================
  //! Plotting Input/Output Options
  // ============================================================================
  /*! A small wrapper class to interface with FileInput
   *  and HistInput objects.
   */
  class Input {

    private:

      // data members
      FileInput m_files;
      HistInput m_hists;

    public:

      // ------------------------------------------------------------------------
      //! Setters
      // ------------------------------------------------------------------------
      void Files(const FileInput& files) {m_files = files;}
      void Hists(const HistInput& hists) {m_hists = hists;}

      // ------------------------------------------------------------------------
      //! Getters
      // ------------------------------------------------------------------------
      FileInput Files() const {return m_files;}
      HistInput Hists() const {return m_hists;}

      // ------------------------------------------------------------------------
      //! Check if is p+Au
      // ------------------------------------------------------------------------
      bool IsPAu(const Type::PlotIndex& idx) {

        return (idx.species == FileInput::PAu);

      }  // end 'IsPAu(Type::PlotIndex&);

      // ------------------------------------------------------------------------
      //! Check if only blue polarizations should be considered
      // ------------------------------------------------------------------------
      bool IsBluePolarization(const Type::PlotIndex& idx) {

        const bool isBlue = (
          (idx.spin == HistInput::BU) ||
          (idx.spin == HistInput::BD) ||
          (idx.spin == HistInput::Int)
        );
        return isBlue;

      }  // end 'IsBluePolarization(Type::PlotIndex&)'

      // ------------------------------------------------------------------------
      //! Make a variable + species tag
      // ------------------------------------------------------------------------
      String MakeSpeciesTag(const String& base, const int spe) const {

        return base + m_files.GetSpeciesTag(spe);

      }  // end 'MakeSpeciesTag(String&, int)'

      // ------------------------------------------------------------------------
      //! Make a histogram name
      // ------------------------------------------------------------------------
      String MakeHistName(
        const String& var,
        const Type::PlotIndex& idx,
        const String& tag = ""
      ) const {

        const String base  = "h" + tag + m_files.GetLevelTag(idx.level) + var + "Stat_";
        const String index = m_hists.GetPtTag(idx.pt) + "cf0" + m_hists.GetChargeTag(idx.chrg) + m_hists.GetSpinTag(idx.spin);
        return base + index;

      }  // end 'MakeHistName(String&, Type::PlotIndex&, String&)'

      // ------------------------------------------------------------------------
      //! Make a histogram legend
      // ------------------------------------------------------------------------
      String MakeLegend(const Type::PlotIndex& idx) const {

        String legend;
        if (idx.species > -1) {
          legend += m_files.GetSpeciesLegend(idx.species) + " ";
        }
        if (idx.level > -1) {
          legend += m_files.GetLevelLegend(idx.level) + " ";
        }
        legend += m_hists.GetSpinLegend(idx.spin) + ", " + m_hists.GetPtLegend(idx.pt) + ", " + m_hists.GetChargeLegend(idx.chrg);
        return legend;

      }  // end 'MakeLegend(Type::PlotIndex&)'

      // ------------------------------------------------------------------------
      //! Make canvas name
      // ------------------------------------------------------------------------
      String MakeCanvasName(
        const String& base,
        const Type::PlotIndex& idx
      ) const {

        String name = base;
        if (idx.species > -1) {
          name += "_" + m_files.GetSpeciesTag(idx.species);
        }
        if (idx.level > -1) {
          name += m_files.GetLevelTag(idx.level);
        }
        name += "_";

        if (idx.pt > -1) {
          name += m_hists.GetPtTag(idx.pt);
        }
        if (idx.chrg > -1) {
          name += m_hists.GetChargeTag(idx.chrg);
        }
        if (idx.spin > -1) {
          name += m_hists.GetSpinTag(idx.spin);
        }
        return name;

      }  // end 'MakeCanvasName(String&, Type::PlotIndex&)'

      // ------------------------------------------------------------------------
      // default ctor/dtor
      // ------------------------------------------------------------------------
      Input()  {};
      ~Input() {};

  };    // end Input

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
