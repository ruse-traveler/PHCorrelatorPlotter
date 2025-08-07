/// ===========================================================================
/*! \file   PHCorrelatorFileInput.h
 *  \author Derek Anderson
 *  \date   03.20.2025
 *
 *  Helper class to manage input files and
 *  associated strings.
 */
/// ===========================================================================

#ifndef PHCORRELATORFILEINPUT_H
#define PHCORRELATORFILEINPUT_H

// c++ utilities
#include <string>
#include <vector>
// plotting utilities
#include "PHCorrelatorIOTypes.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Input files database
  // ==========================================================================
  /*! A small helper class to manage input files and associated strings.
   */
  class FileInput {

    public:

      ///! enumerate species indices
      enum Species {
        PP  = 0,
        PAu = 1
      };

      ///! enumerate level indices
      enum Level {
        Data = 0,
        Reco = 1,
        True = 2
      };

    private:

      // data members
      std::string[2][3] m_files;
      std::string[2]    m_tags_species;
      std::string[3]    m_tags_levels;
      std::string[2]    m_legs_species;
      std::string[3]    m_legs_levels;

      // ----------------------------------------------------------------------
      //! Load default species hist tags and legends
      // ----------------------------------------------------------------------
      /*! The default histogram tags and legend associated
       *  with the "species" (pp vs. pAu) are defined here.
       *  Can be configured via accessor functions.
       */
      void LoadDefaultSpeciesStrings() {

        // define tags
        m_tags_species[PP]  = "PP";
        m_tags_species[PAu] = "PAu";

        // define legends
        m_legs_species[PP]  = "#bf{[p+p]}";
        m_legs_species[PAu] = "#bf{[p+Au]}";
        return;

      }  // end 'LoadSpeciesStrings()'

      // ----------------------------------------------------------------------
      //! Load default level hist tags and legend text
      // ----------------------------------------------------------------------
      /*! The histogram tags and legend associated with the
       *  "level" (data, sim reco, sim truth) are defined
       *  here, and then retrived via the accessor
       *  functions.
       */
      void LoadDefaultLevelStrings() {

        // set tags
        m_tags_levels[Data] = "DataJet";
        m_tags_levels[Reco] = "RecoJet";
        m_tags_levels[True] = "TrueJet";

        // define legends
        m_legs_levels[Data] = "#bf{[Data]}";
        m_legs_levels[Reco] = "#bf{[Reco.]}";
        m_legs_levels[True] = "#bf{[Truth]}";
        return;

      }  // end 'LoadLevelStrings()'

    public:

      // ----------------------------------------------------------------------
      //! Set a file
      // ----------------------------------------------------------------------
      void SetFile(const Species sp, const Level lv, const std::string& file) {

        m_files[sp][lv] = file;
        return;

      }  // end 'SetFile(Species, Level, std::string&)'

      // ----------------------------------------------------------------------
      //! Set a species tag
      // ----------------------------------------------------------------------
      void SetSpeciesTag(const Species sp, const std::string& tag) {

        m_tags_species[sp] = tag;
        return;

      }  // end 'SetSpeciesTag(Species, std::string&)'

      // ----------------------------------------------------------------------
      //! Set a level tag
      // ----------------------------------------------------------------------
      void SetLevelTag(const Level lv, const std::string& tag) {

        m_tags_levels[lv] = tag;
        return;

      }  // end 'SetLevelTag(Level, std::string&)'

      // ----------------------------------------------------------------------
      //! Set a species legend
      // ----------------------------------------------------------------------
      void SetSpeciesLegend(const Species sp, const std::string& leg) {

        m_legs_species[sp] = leg;
        return;

      }  // end 'SetSpeciesLegend(Species, std::string&)'

      // ----------------------------------------------------------------------
      //! Set a level legend
      // ----------------------------------------------------------------------
      void SetLevelLegend(const Level lv, const std::string& leg) {

        m_legs_levels[lv] = leg;
        return;

      }  // end 'SetLevelLegend(Level, std::string&)'

      // ----------------------------------------------------------------------
      //! Get a file via explicity identify species & level index
      // ----------------------------------------------------------------------
      std::string GetFile(const Species sp, const Level lv) const {

        return m_file[sp][lv];

      }  // end 'GetFile(Species, Level)'

      // ----------------------------------------------------------------------
      //! Get a file via plot index 
      // ----------------------------------------------------------------------
      std::string GetFile(const Type::PlotIndex& idx) const {

        return m_file[idx.species][idx.level];

      }  // end 'GetFile(Type::PlotIndex&)'

      // ----------------------------------------------------------------------
      //! default ctor
      // ----------------------------------------------------------------------
      FileInput() {

        LoadDefaultSpeciesStrings();
        LoadDefaultLevelStrings();

      };  // end ctor()

      // ----------------------------------------------------------------------
      //! default dtor
      // ----------------------------------------------------------------------
      ~FileInput() {};

  };    // end FileInput

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
