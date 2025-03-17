/// ===========================================================================
/*! \file    PHCorrelatorPlotTypes.h
 *  \authors Derek Anderson
 *  \date    12.26.2024
 *
 *  Useful types related to plotting.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTTYPES_H
#define PHCORRELATORPLOTTYPES_H

// c++ utilities
#include <map>
#include <string>
#include <utility>
#include <vector>
// root libraries
#include <TObject.h>



namespace PHEnergyCorrelator {
  namespace Type {

    // typedefs ===============================================================

    // ------------------------------------------------------------------------
    //! Convenient types
    // ------------------------------------------------------------------------
    typedef std::vector<float>                  Vertices;
    typedef std::vector<float>                  Margins;
    typedef std::vector<TObject*>               Objects;
    typedef std::vector<std::string>            TextList;
    typedef std::vector<std::string>            LabelList;
    typedef std::map<std::string, std::size_t>  LabelToIndexMap;
    typedef std::map<std::string, std::string>  FileMap;
    typedef std::pair<float, float>             Interval;
    typedef std::pair<float, float>             PairF;
    typedef std::pair<float, float>             Point;
    typedef std::pair<std::size_t, std::size_t> Dimensions;

    // ------------------------------------------------------------------------
    //! Iterator for iterating over label-to-index maps
    // ------------------------------------------------------------------------
    typedef std::map<std::string, std::size_t>::iterator it_label;



    // enums ==================================================================

    // ------------------------------------------------------------------------
    //! Different axes of histograms & graphs
    // ------------------------------------------------------------------------
    enum Axis {X, Y, Z};

    // ------------------------------------------------------------------------
    //! Different margins of a pad or canvas
    // ------------------------------------------------------------------------
    enum Margin {Top, Right, Bottom, Left};



    // structs ================================================================

    // ------------------------------------------------------------------------
    //! Plot index
    // ------------------------------------------------------------------------
    /*! FIXME after merging, should split off file indices into
     *  a separate FileIndex type, and then make PlotIndex
     *  composed of HistIndex + FileIndex.
     *
     *  FIXME the default arguments should be a constant.
     */
    struct PlotIndex {

      // data members
      int level;
      int species;
      int pt;
      int cf;
      int chrg;
      int spin;

      //! default ctor/dtor
      PlotIndex()  {};
      ~PlotIndex() {};

      //! ctor accepting a single argument
      PlotIndex(const int iarg) {
        level   = iarg;
        species = iarg;
        pt      = iarg;
        cf      = iarg;
        chrg    = iarg;
        spin    = iarg;
      }  // end ctor(int)

      //! ctor accepting all arguments
      PlotIndex(
        const int ilvl,
        const int icol,
        const int ipt,
        const int icf = -1,
        const int ich = -1,
        const int isp = -1
      ) {
        level   = ilvl;
        species = icol;
        pt      = ipt;
        cf      = icf;
        chrg    = ich;
        spin    = isp;
      }  // end ctor(int x 6)

    };  // end PlotIndex

  }  // end Types namespace
}  // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
