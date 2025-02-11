/// ===========================================================================
/*! \file   InputOutput.h
 *  \author Derek Anderson
 *  \date   01.05.2025
 *
 *  Helper classes to facilitate I/O operations
 *  all plotting routines (e.g. input file names,
 *  output files, histograms to grab, etc.)
 */
/// ===========================================================================

#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

// c++ utilities
#include <string>
#include <vector>

// Useful aliases
typedef std::string String;
typedef std::vector<std::string> Strings;
typedef std::vector<std::vector<std::string> > Files;



// ============================================================================
//! Input files database
// ============================================================================
/*! A small helper class to manage input files and associated strings.
 */
class InFiles {

  public:

    // ------------------------------------------------------------------------
    // Accessors for vectors
    // ------------------------------------------------------------------------
    enum Species {PP, PAu};
    enum Level   {Data, Reco, True};

  private:

    // data members
    Files   m_files;
    Strings m_tags_species;
    Strings m_tags_levels;
    Strings m_legs_species;
    Strings m_legs_levels;

    // ------------------------------------------------------------------------
    //! Define input files
    // ------------------------------------------------------------------------
    /*! All inputs files you'll need are defined here should
     *  be defined here. Then files can be retrieved via the
     *  accessor functions.
     */
    void LoadInputFiles() {

      // define input files for pp
      std::vector<std::string> pp_files;
      pp_files.push_back("./input/ppRun15_dataWithBetterWraps_r03all.d6m2y2025.root");
      pp_files.push_back("./input/ppRun15_simWithBetterWraps_r03all.d6m2y2025.root");
      pp_files.push_back("./input/ppRun15_simWithBetterWraps_r03all.d6m2y2025.root");

      // define input files for pAu
      std::vector<std::string> pa_files;
      pa_files.push_back("./input/paRun15_dataWithJetCharge_r03all_084.d27m1y2025.root");
      pa_files.push_back("./input/paRun15_simWithJetCharge_r03all_084.d27m1y2025.root");
      pa_files.push_back("./input/paRun15_simWithJetCharge_r03all_084.d27m1y2025.root");

      // load vector of inputs
      m_files.clear();
      m_files.push_back(pp_files);
      m_files.push_back(pa_files);
      return;

    }  // end 'LoadInputFiles()'

    // ------------------------------------------------------------------------
    //! Define species hist tags and legends
    // ------------------------------------------------------------------------
    /*! The histogram tags and legend associated with the
     *  "species" (pp vs. pAu) should be defined here,
     *  and then retrived via the accessor functions.
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

    // ------------------------------------------------------------------------
    //! Define level hist tags and legend text
    // ------------------------------------------------------------------------
    /*! The histogram tags and legend associated with the
     *  "level" (data, sim reco, sim truth) should be
     *  defined here, and then retrived via the accessor
     *  functions.
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

    // ------------------------------------------------------------------------
    //! Setters
    // ------------------------------------------------------------------------
    void SetFiles(const Files& files)           {m_files        = files;}
    void SetSpeciesTags(const Strings& tags)    {m_tags_species = tags;}
    void SetLevelTags(const Strings& tags)      {m_tags_levels  = tags;}
    void SetSpeciesLegends(const Strings& legs) {m_legs_species = legs;}
    void SetLevelLegends(const Strings& legs)   {m_legs_levels  = legs;}

    // ------------------------------------------------------------------------
    //! Getters
    // ------------------------------------------------------------------------
    Files   GetFiles()          const {return m_files;}
    Strings GetSpeciesTags()    const {return m_tags_species;}
    Strings GetLevelTags()      const {return m_tags_levels;}
    Strings GetSpeciesLegends() const {return m_legs_species;}
    Strings GetLeveLegends()    const {return m_legs_levels;}

    // ------------------------------------------------------------------------
    //! Get a particular tag, legend text
    // ------------------------------------------------------------------------
    String GetSpeciesTag(const int species)    const {return m_tags_species.at(species);}
    String GetLevelTag(const int level)        const {return m_tags_levels.at(level);}
    String GetSpeciesLegend(const int species) const {return m_legs_species.at(species);}
    String GetLevelLegend(const int level)     const {return m_legs_levels.at(level);}

    // ------------------------------------------------------------------------
    //! Get files for a specific species
    // ------------------------------------------------------------------------
    Strings GetFiles(const int species) const {

      return m_files.at(species);

    }  // end 'GetFiles(int)'

    // ------------------------------------------------------------------------
    //! Get a particular file
    // ------------------------------------------------------------------------
    String GetFile(const int species, const int level) const {

      return m_files.at(species).at(level);

    }  // end 'GetFile(int, int)'

    // ------------------------------------------------------------------------
    //! default ctor
    // ------------------------------------------------------------------------
    InFiles() {

      LoadInputFiles();
      LoadSpeciesStrings();
      LoadLevelStrings();

    };  // end ctor()

    // ------------------------------------------------------------------------
    //! default dtor
    // ------------------------------------------------------------------------
    ~InFiles() {};

};  // end InFiles



// ============================================================================
//! Input histogram database
// ============================================================================
/*! A small helper class to manage histograms
 *  and associated strings.
 */
class InHists {

  public:

    enum PtJet {Pt5, Pt10, Pt15};
    enum Spin  {BU, BD, YU, YD, BUYU, BUYD, BDYU, BDYD, Int};

  private:

    // data members
    Strings m_tags_pt;
    Strings m_tags_ch;
    Strings m_tags_sp;
    Strings m_legs_pt;
    Strings m_legs_ch;
    Strings m_legs_sp;

    // ------------------------------------------------------------------------
    //! Define pt hist tags and legend text
    // ------------------------------------------------------------------------
    /*! All histogram tags and legend entries associated
     *  with the jet pt should be defined here, and then
     *  retrieved with the accessor functions.
     */ 
    void LoadPtStrings() {

      // define tags
      m_tags_pt.clear();
      m_tags_pt.push_back("pt0");
      m_tags_pt.push_back("pt1");
      m_tags_pt.push_back("pt2");

      // define legends
      m_legs_pt.clear();
      m_legs_pt.push_back("p_{T}^{jet} #in (5, 10) GeV/c");
      m_legs_pt.push_back("p_{T}^{jet} #in (10, 15) GeV/c");
      m_legs_pt.push_back("p_{T}^{jet} #in (15, 20) GeV/c");
      return;

    }  // end 'LoadPtStrings()'

    // ------------------------------------------------------------------------
    //! Define jet charge hist tags and legend text
    // ------------------------------------------------------------------------
    /*! All histogram tags and legend entries associated
     *  with the jet charge should be defined here, and
     *  then retrieved with the accessor functions.
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

    // ------------------------------------------------------------------------
    //! Load spin hist tags and legend text
    // ------------------------------------------------------------------------
    /*! All histogram tags and legend entries associated
     *  with the spin should be defined here, and then
     *  retrieved with the accessor functions.
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
      m_tags_sp.push_back("spInt");

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

    // ------------------------------------------------------------------------
    //! Setters
    // ------------------------------------------------------------------------
    void SetPtTags(Strings& tags)        {m_tags_pt = tags;}
    void SetChargeTags(Strings& tags)    {m_tags_ch = tags;}
    void SetSpinTags(Strings& tags)      {m_tags_sp = tags;}
    void SetPtLegends(Strings& legs)     {m_legs_pt = legs;}
    void SetChargeLegends(Strings& legs) {m_legs_ch = legs;}
    void SetSpinLegends(Strings& legs)   {m_legs_sp = legs;}

    // ------------------------------------------------------------------------
    //! Getters
    // ------------------------------------------------------------------------
    Strings GetPtTags()        const {return m_tags_pt;}
    Strings GetChargeTags()    const {return m_tags_ch;}
    Strings GetSpinTags()      const {return m_tags_sp;}
    Strings GetPtLegends()     const {return m_legs_pt;}
    Strings GetChargeLegends() const {return m_legs_ch;}
    Strings GetSpinLegends()   const {return m_legs_sp;}

    // ------------------------------------------------------------------------
    //! Get a particular tag, legend text
    // ------------------------------------------------------------------------
    String GetPtTag(const int pt)        const {return m_tags_pt.at(pt);}
    String GetChargeTag(const int ch)    const {return m_tags_ch.at(ch);}
    String GetSpinTag(const int sp)      const {return m_tags_sp.at(sp);}
    String GetPtLegend(const int pt)     const {return m_legs_pt.at(pt);}
    String GetChargeLegend(const int ch) const {return m_legs_ch.at(ch);}
    String GetSpinLegend(const int sp)   const {return m_legs_sp.at(sp);}

    // ------------------------------------------------------------------------
    //! default ctor
    // ------------------------------------------------------------------------
    InHists() {

      LoadPtStrings();
      LoadChargeStrings();
      LoadSpinStrings();

    };  // end ctor()

    // ------------------------------------------------------------------------
    //! default dtor
    // ------------------------------------------------------------------------
    ~InHists() {};

};  // end InHists



// ============================================================================
//! Plotting Input/Output Options
// ============================================================================
/*! Wrapper class to hold and interface with InFiles and
 *  InHists objects.
 */
class InputOutput {

  private:

    // data members
    InFiles m_files;
    InHists m_hists;

  public:

    // ------------------------------------------------------------------------
    //! Setters
    // ------------------------------------------------------------------------
    void Files(const InFiles& files) {m_files = files;}
    void Hists(const InHists& hists) {m_hists = hists;}

    // ------------------------------------------------------------------------
    //! Getters
    // ------------------------------------------------------------------------
    InFiles Files() const {return m_files;}
    InHists Hists() const {return m_hists;}

    // ------------------------------------------------------------------------
    //! Make a variable + species tag
    // ------------------------------------------------------------------------
    String MakeSpeciesTag(const String& base, const int spe) const {

      return base + m_files.GetSpeciesTag(spe);

    }  // 'MakeSpeciesTag(String&, int)'

    // ------------------------------------------------------------------------
    //! Make a histogram name
    // ------------------------------------------------------------------------
    String MakeHistName(
      const String& var,
      const int lvl,
      const int pt,
      const int ch,
      const int sp,
      const String& tag = ""
    ) const {

      const String base  = "h" + tag + m_files.GetLevelTag(lvl) + var + "Stat_";
      const String index = m_hists.GetPtTag(pt) + "cf0" + m_hists.GetChargeTag(ch) + m_hists.GetSpinTag(sp);
      return base + index;

    }  // end 'MakeHistName(String&, int x 4, String&)'

    // ------------------------------------------------------------------------
    //! Make a histogram legend
    // ------------------------------------------------------------------------
    String MakeLegend(
      const int pt,
      const int ch,
      const int sp,
      const int lvl = -1,
      const int spe = -1
    ) const {

      String legend;
      if (spe > -1) {
        legend += m_files.GetSpeciesLegend(spe) + " ";
      }
      if (lvl > -1) {
        legend += m_files.GetLevelLegend(lvl) + " ";
      }
      legend += m_hists.GetSpinLegend(sp) + ", " + m_hists.GetPtLegend(pt) + ", " + m_hists.GetChargeLegend(ch);
      return legend;

    }  // end 'MakeLegend(int x 6)'

    // ------------------------------------------------------------------------
    //! Make canvas name
    // ------------------------------------------------------------------------
    String MakeCanvasName(
      const String& base,
      const int pt  = -1,
      const int ch  = -1,
      const int sp  = -1,
      const int lvl = -1,
      const int spe = -1
    ) const {

      String name = base;
      if (spe > -1) {
        name += "_" + m_files.GetSpeciesTag(spe);
      }
      if (lvl > -1) {
        name += m_files.GetLevelTag(lvl);
      }
      name += "_";

      if (pt > -1) {
        name += m_hists.GetPtTag(pt);
      }
      if (ch > -1) {
        name += m_hists.GetChargeTag(ch);
      }
      if (sp > -1) {
        name += m_hists.GetSpinTag(sp);
      }
      return name;

    }  // end 'MakeCanvasName(int x 6)'

    // ------------------------------------------------------------------------
    // default ctor/dtor
    // ------------------------------------------------------------------------
    InputOutput()  {};
    ~InputOutput() {};

};  // end InputOutput

#endif

// end ========================================================================
