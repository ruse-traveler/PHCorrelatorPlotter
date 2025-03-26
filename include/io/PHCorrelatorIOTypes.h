/// ===========================================================================
/*! \file    PHCorrelatorIOTypes.h
 *  \authors Derek Anderson
 *  \date    03.20.2025
 *
 *  Useful types related to I/O
 */
/// ===========================================================================

#ifndef PHCORRELATORIOTYPES_H
#define PHCORRELATORIOTYPES_H

// c++ utilities
#include <string>
#include <vector>



namespace PHEnergyCorrelator {
  namespace Type {

    // typedefs ===============================================================

    // ------------------------------------------------------------------------
    //! Convenient types
    // ------------------------------------------------------------------------
    typedef std::vector<std::string> Strings;
    typedef std::vector<std::vector<std::string> > Files;



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

  }  // end Type namespace
}  // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
