/// ===========================================================================
/*! \file    PHCorrelatorPlotIndexVector.h
 *  \authors Derek Anderson
 *  \date    05.10.2025
 *
 *  Helper class for PlotIndex ranges.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTINDEXVECTOR_H
#define PHCORRELATORPLOTINDEXVECTOR_H

// c++ utilities
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
// plotting utilities
#include "PHCorrelatorFileInput.h"
#include "PHCorrelatorHistInput.h"
#include "PHCorrelatorIOTypes.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Plot index vector
  // ==========================================================================
  /*! A helper class to define a range of plot
   *  indices to loop over.
   */
  class PlotIndexVector {

    private:

      // data members
      std::pair<int, int> m_levels;
      std::pair<int, int> m_species;
      std::pair<int, int> m_pts;
      std::pair<int, int> m_cfs;
      std::pair<int, int> m_chrgs;
      std::pair<int, int> m_spins;

    public:

      // ----------------------------------------------------------------------
      //! Reset ranges
      // ----------------------------------------------------------------------
      void Reset() {

        m_levels  = std::make_pair(-1, -1);
        m_species = std::make_pair(-1, -1);
        m_pts     = std::make_pair(-1, -1);
        m_cfs     = std::make_pair(-1, -1);
        m_chrgs   = std::make_pair(-1, -1);
        m_spins   = std::make_pair(-1, -1);
        return;

      }  // end 'Reset()'

      // ----------------------------------------------------------------------
      //! Set level range
      // ----------------------------------------------------------------------
      void SetLevelRange(const int start, const int stop) {

        m_levels = std::make_pair(
          std::max(start, static_cast<int>(FileInput::Data)),
          std::min(stop, static_cast<int>(FileInput::True))
        );
        return;

      }  // end 'SetLevelRange(int x 2)'

      // ----------------------------------------------------------------------
      //! Set species range
      // ----------------------------------------------------------------------
      void SetSpeciesRange(const int start, const int stop) {

        m_species = std::make_pair(
          std::max(start, static_cast<int>(FileInput::PP)),
          std::min(stop, static_cast<int>(FileInput::PAu))
        );
        return;

      }  // end 'SetSpeciesRange(int x 2)'

      // ----------------------------------------------------------------------
      //! Set pt range
      // ----------------------------------------------------------------------
      void SetPtRange(const int start, const int stop) {

        m_pts = std::make_pair(
          std::max(start, static_cast<int>(HistInput::Pt5)),
          std::min(stop, static_cast<int>(HistInput::PtInt))
        );
        return;

      }  // end 'SetPtRange(int x 2)'

      // ----------------------------------------------------------------------
      //! Set cf range
      // ----------------------------------------------------------------------
      void SetCFRange(const int start, const int stop) {

        m_cfs = std::make_pair(
          std::max(start, static_cast<int>(HistInput::CFLow)),
          std::min(stop, static_cast<int>(HistInput::CFInt))
        );
        return;

      }  // end 'SetCFRange(int x 2)'

      // ----------------------------------------------------------------------
      //! Set charge range
      // ----------------------------------------------------------------------
      void SetChargeRange(const int start, const int stop) {

        m_chrgs = std::make_pair(
          std::max(start, static_cast<int>(HistInput::Pos)),
          std::min(stop, static_cast<int>(HistInput::ChInt))
        );
        return;

      }  // end 'SetChargeRange(int x 2)'

      // ----------------------------------------------------------------------
      //! Set spin range
      // ----------------------------------------------------------------------
      void SetSpinRange(const int start, const int stop) {

        m_spins = std::make_pair(
          std::max(start, static_cast<int>(HistInput::BU)),
          std::min(stop, static_cast<int>(HistInput::SpInt))
        );
        return;

      }  // end 'SetSpinRange(int x 2)'

      // ----------------------------------------------------------------------
      //! Set level range to everyting
      // ----------------------------------------------------------------------
      void DoAllLevels() {

        m_levels = std::make_pair(FileInput::Data, FileInput::True);
        return;

      }  // end 'DoAllLevels()'

      // ----------------------------------------------------------------------
      //! Set species range to everyting
      // ----------------------------------------------------------------------
      void DoAllSpecies() {

        m_species = std::make_pair(FileInput::PP, FileInput::PAu);
        return;

      }  // end 'DoAllSpecies()'

      // ----------------------------------------------------------------------
      //! Set pt range to everyting
      // ----------------------------------------------------------------------
      void DoAllPt() {

        m_pts = std::make_pair(HistInput::Pt5, HistInput::PtInt);
        return;

      }  // end 'DoAllPt()'

      // ----------------------------------------------------------------------
      //! Set cf range to everyting
      // ----------------------------------------------------------------------
      void DoAllCF() {

        m_cfs = std::make_pair(HistInput::CFLow, HistInput::CFInt);
        return;

      }  // end 'DoAllCF()'

      // ----------------------------------------------------------------------
      //! Set charge range to everyting
      // ----------------------------------------------------------------------
      void DoAllCharge() {

        m_chrgs = std::make_pair(HistInput::Pos, HistInput::ChInt);
        return;

      }  // end 'DoAllCharge()'

      // ----------------------------------------------------------------------
      //! Set spin range to everyting
      // ----------------------------------------------------------------------
      void DoAllSpin() {

        m_spins = std::make_pair(HistInput::BU, HistInput::SpInt);
        return;

      }  // end 'DoAllSpin()'

      // ----------------------------------------------------------------------
      //! Generate a vector of indices
      // ----------------------------------------------------------------------
      void GetVector(std::vector<Type::PlotIndex>& indices) {

        for (int ilvl = m_levels.first; ilvl <= m_levels.second; ++ilvl) {
          for (int ispe = m_species.first; ispe <= m_species.second; ++ispe) {
            for (int ipt = m_pts.first; ipt <= m_pts.second; ++ipt) {
              for (int icf = m_cfs.first; icf <= m_cfs.second; ++icf) {
                for (int ich = m_chrgs.first; ich <= m_chrgs.second; ++ich) {
                  for (int isp = m_spins.first; isp <= m_spins.second; ++isp) {
                    indices.push_back( Type::PlotIndex(ilvl, ispe, ipt, icf, ich, isp) );
                  }  // end spin loop
                }  // end charge loop
              }  // end cf loop
            }  // end pt loop
          }  // end species loop
        }  // end level loop
        return;

      }  // end 'GetVector()'

      // ----------------------------------------------------------------------
      //! default ctor
      // ----------------------------------------------------------------------
      PlotIndexVector()
        : m_levels(std::make_pair(-1, -1))
        , m_species(std::make_pair(-1, -1))
        , m_pts(std::make_pair(-1, -1))
        , m_cfs(std::make_pair(-1, -1))
        , m_chrgs(std::make_pair(-1, -1))
        , m_spins(std::make_pair(-1, -1))
      {};

      // ----------------------------------------------------------------------
      //! default ctor
      // ----------------------------------------------------------------------
      ~PlotIndexVector() {};

  };  // end PlotIndexVector

}  // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================

