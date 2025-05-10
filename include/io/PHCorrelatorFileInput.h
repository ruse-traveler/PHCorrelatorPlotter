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
      Type::Files   m_files;
      Type::Strings m_tags_species;
      Type::Strings m_tags_levels;
      Type::Strings m_legs_species;
      Type::Strings m_legs_levels;

      // ----------------------------------------------------------------------
      //! Define input files
      // ----------------------------------------------------------------------
      /*! All inputs files you'll need are defined here should
       *  be defined here. Then files can be retrieved via the
       *  accessor functions.
       *
       *  FIXME make configurable
       */
      void LoadInputFiles() {

        // define input files for pp
        std::vector<std::string> pp_files;
        pp_files.push_back("~/PHCorrelatorPlotter/input/ppRun15_datFullStats_forDiFF_r03full.d17m4y2025.root");
        pp_files.push_back("~/PHCorrelatorPlotter/input/ppRun15_recFullStats_forDiFF_r03full.d18m4y2025.root");
        pp_files.push_back("~/PHCorrelatorPlotter/input/ppRun15_truFullStats_forDiFF_r03full.d27m4y2025.root");

        // define input files for pAu
        std::vector<std::string> pa_files;
        pa_files.push_back("~/PHCorrelatorPlotter/input/paRun15_datFullStats_forDiFF_r03cen084full.d2m5y2025.root");
        pa_files.push_back("~/PHCorrelatorPlotter/input/paRun15_recFullStats_forDiFF_r03cen084full.d3m5y2025.root");
        pa_files.push_back("~/PHCorrelatorPlotter/input/paRun15_truFullStats_forDiFF_r03cen084full.d3m5y2025.root");

        // load vector of inputs
        m_files.clear();
        m_files.push_back(pp_files);
        m_files.push_back(pa_files);
        return;

      }  // end 'LoadInputFiles()'

      // ----------------------------------------------------------------------
      //! Define species hist tags and legends
      // ----------------------------------------------------------------------
      /*! The histogram tags and legend associated with the
       *  "species" (pp vs. pAu) should be defined here,
       *  and then retrived via the accessor functions.
       *
       *  FIXME make configurable(?)
       */
      void LoadSpeciesStrings() {

        // define tags
        m_tags_species.clear();
        m_tags_species.push_back("PP");
        m_tags_species.push_back("PAu");

        // define legends
        m_legs_species.clear();
        m_legs_species.push_back("#bf{[p+p]}");
        m_legs_species.push_back("#bf{[p+Au]}");
        return;

      }  // end 'LoadSpeciesStrings()'

      // ----------------------------------------------------------------------
      //! Define level hist tags and legend text
      // ----------------------------------------------------------------------
      /*! The histogram tags and legend associated with the
       *  "level" (data, sim reco, sim truth) should be
       *  defined here, and then retrived via the accessor
       *  functions.
       *
       *  FIXME make configurable(?)
       */
      void LoadLevelStrings() {

        // define tags
        m_tags_levels.clear();
        m_tags_levels.push_back("DataJet");
        m_tags_levels.push_back("RecoJet");
        m_tags_levels.push_back("TrueJet");

        // define legends
        m_legs_levels.clear();
        m_legs_levels.push_back("#bf{[Data]}");
        m_legs_levels.push_back("#bf{[Reco.]}");
        m_legs_levels.push_back("#bf{[Truth]}");
        return;

      }  // end 'LoadLevelStrings()'

    public:

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetFiles(const Type::Files& files)           {m_files        = files;}
      void SetSpeciesTags(const Type::Strings& tags)    {m_tags_species = tags;}
      void SetLevelTags(const Type::Strings& tags)      {m_tags_levels  = tags;}
      void SetSpeciesLegends(const Type::Strings& legs) {m_legs_species = legs;}
      void SetLevelLegends(const Type::Strings& legs)   {m_legs_levels  = legs;}

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Type::Files   GetFiles()          const {return m_files;}
      Type::Strings GetSpeciesTags()    const {return m_tags_species;}
      Type::Strings GetLevelTags()      const {return m_tags_levels;}
      Type::Strings GetSpeciesLegends() const {return m_legs_species;}
      Type::Strings GetLeveLegends()    const {return m_legs_levels;}

      // ----------------------------------------------------------------------
      //! Get a particular tag, legend text
      // ----------------------------------------------------------------------
      std::string GetSpeciesTag(const int species)    const {return m_tags_species.at(species);}
      std::string GetLevelTag(const int level)        const {return m_tags_levels.at(level);}
      std::string GetSpeciesLegend(const int species) const {return m_legs_species.at(species);}
      std::string GetLevelLegend(const int level)     const {return m_legs_levels.at(level);}

      // ----------------------------------------------------------------------
      //! Get files for a specific species
      // ----------------------------------------------------------------------
      Type::Strings GetFiles(const Type::PlotIndex& idx) const {

        return m_files.at(idx.species);

      }  // end 'GetFiles(Type::PlotIndex&)'

      // ----------------------------------------------------------------------
      //! Get a particular file
      // ----------------------------------------------------------------------
      std::string GetFile(const Type::PlotIndex& idx) const {

        return m_files.at(idx.species).at(idx.level);

      }  // end 'GetFile(Type::PlotIndex&)'

      // ----------------------------------------------------------------------
      //! default ctor
      // ----------------------------------------------------------------------
      FileInput() {

        LoadInputFiles();
        LoadSpeciesStrings();
        LoadLevelStrings();

      };  // end ctor()

      // ----------------------------------------------------------------------
      //! default dtor
      // ----------------------------------------------------------------------
      ~FileInput() {};

  };    // end FileInput

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
