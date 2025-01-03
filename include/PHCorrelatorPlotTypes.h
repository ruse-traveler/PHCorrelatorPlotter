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
    typedef std::pair<std::size_t, std::size_t> Dimensions;

    // ------------------------------------------------------------------------
    //! Iterator for iterating over label-to-index maps
    // ------------------------------------------------------------------------
    typedef std::map<std::string, std::size_t>::iterator it_label;



    // ------------------------------------------------------------------------
    //! Different axes of histograms & graphs
    // ------------------------------------------------------------------------
    enum Axis {X, Y, Z};

    // ------------------------------------------------------------------------
    //! Different margins of a pad or canvas
    // ------------------------------------------------------------------------
    enum Margin {Top, Right, Bottom, Left};

  }  // end Types namespace
}  // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
