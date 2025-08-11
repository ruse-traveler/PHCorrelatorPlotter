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
  //! Plotting Input Options
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
      void SetFiles(const FileInput& files) {m_files = files;}
      void SetHists(const HistInput& hists) {m_hists = hists;}

      // ------------------------------------------------------------------------
      //! Getters
      // ------------------------------------------------------------------------
      FileInput& GetFiles() {return &m_files;}
      HistInput& GetHists() {return &m_hists;}

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
          (idx.spin == HistInput::SpInt)
        );
        return isBlue;

      }  // end 'IsBluePolarization(Type::PlotIndex&)'

      // ------------------------------------------------------------------------
      //! Make a variable + species tag
      // ------------------------------------------------------------------------
      std::string MakeSpeciesTag(const std::string& base, const int spe) const {

        return base + m_files.GetSpeciesTag(spe);

      }  // end 'MakeSpeciesTag(std::string&, int)'

      // ------------------------------------------------------------------------
      //! Make a histogram name
      // ------------------------------------------------------------------------
      std::string MakeHistName(
        const std::string& var,
        const Type::PlotIndex& idx,
        const std::string& tag = ""
      ) const {

        // create base (level + var) part of histogram name
        std::string base  = "h" + tag;
        if (idx.level > -1) {
          base += m_files.GetLevelTag(idx.level);
        }
        base += var + "Stat_";

        // and now create index (pt, chrg, cf, spin) part of
        // histogram name
        std::string index = "";
        if (idx.pt > -1) {
          index += m_hists.GetPtTag(idx.pt);
        }
        if (idx.cf > -1) {
          index += m_hists.GetCFTag(idx.cf);
        }
        if (idx.spin > -1) {
          index += m_hists.GetSpinTag(idx.spin);
        }
        return base + index;

      }  // end 'MakeHistName(std::string&, Type::PlotIndex&, std::string&)'

      // ------------------------------------------------------------------------
      //! Make a histogram legend
      // ------------------------------------------------------------------------
      std::string MakeLegend(const Type::PlotIndex& idx) const {

        std::string legend;
        if (idx.species > -1) {
          legend += m_files.GetSpeciesLegend(idx.species) + " ";
        }
        if (idx.level > -1) {
          legend += m_files.GetLevelLegend(idx.level) + " ";
        }
        if (idx.spin > -1) {
          legend += m_hists.GetSpinLegend(idx.spin) + ", ";
        }
        if (idx.pt > -1) {
          legend += m_hists.GetPtLegend(idx.pt);
        }
        if (idx.chrg > -1) {
          legend += ", " + m_hists.GetChargeLegend(idx.chrg);
        }
        if (idx.cf > -1) {
          legend += ", " + m_hists.GetCFLegend(idx.cf);
        }
        return legend;

      }  // end 'MakeLegend(Type::PlotIndex&)'

      // ------------------------------------------------------------------------
      //! Make canvas name
      // ------------------------------------------------------------------------
      std::string MakeCanvasName(
        const std::string& base,
        const Type::PlotIndex& idx
      ) const {

        // create base (var + level) part of canvas name
        std::string name = base;
        if (idx.species > -1) {
          name += "_" + m_files.GetSpeciesTag(idx.species);
        }
        if (idx.level > -1) {
          name += m_files.GetLevelTag(idx.level);
        }
        name += "_";

        // create index (pt, chrg, cf, spin) part of canvas name
        if (idx.pt > -1) {
          name += m_hists.GetPtTag(idx.pt);
        }
        if (idx.chrg > -1) {
          name += m_hists.GetChargeTag(idx.chrg);
        }
        if (idx.cf > -1) {
          name += m_hists.GetCFTag(idx.cf);
        }
        if (idx.spin > -1) {
          name += m_hists.GetSpinTag(idx.spin);
        }
        return name;

      }  // end 'MakeCanvasName(std::string&, Type::PlotIndex&)'

      // ------------------------------------------------------------------------
      // default ctor/dtor
      // ------------------------------------------------------------------------
      Input()  {};
      ~Input() {};

  };    // end Input

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
