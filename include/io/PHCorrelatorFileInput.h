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
        pp_files.push_back("~/PHCorrelatorPlotter/input/Apr2025/ppRun15_datFullStats_forDiFF_r03full.d17m4y2025.root");
        pp_files.push_back("~/PHCorrelatorPlotter/input/Apr2025/ppRun15_recFullStats_forDiFF_r03full.d18m4y2025.root");
        pp_files.push_back("~/PHCorrelatorPlotter/input/Apr2025/ppRun15_truFullStats_forDiFF_r03full.d27m4y2025.root");

        // define input files for pAu
        std::vector<std::string> pa_files;
        pa_files.push_back("~/PHCorrelatorPlotter/input/May2025/paRun15_datFullStats_forDiFF_r03cen084full.d2m5y2025.root");
        pa_files.push_back("~/PHCorrelatorPlotter/input/May2025/paRun15_recFullStats_forDiFF_r03cen084full.d3m5y2025.root");
        pa_files.push_back("~/PHCorrelatorPlotter/input/May2025/paRun15_truFullStats_forDiFF_r03cen084full.d3m5y2025.root");

        // load vector of inputs
        m_files.clear();
        m_files.push_back(pp_files);
        m_files.push_back(pa_files);
        return;

      }  // end 'LoadInputFiles()'

      // ----------------------------------------------------------------------
      //! Load default species hist tags and legends
      // ----------------------------------------------------------------------
      /*! The default histogram tags and legend associated
       *  with the "species" (pp vs. pAu) are defined here,
       *  and then retrived via the accessor functions.
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
      //! Get a tag, legend text
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
