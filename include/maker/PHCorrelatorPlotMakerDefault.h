/// ===========================================================================
/*! \file   PHCorrelatorPlotMakerDefault.h
 *  \author Derek Anderson
 *  \date   04.28.2025
 *
 *  A small struct to define defaults for
 *  various plotting routines.
 */
/// ===========================================================================

#ifndef PHCORRELATORPLOTMAKERDEFAULT_H
#define PHCORRELATORPLOTMAKERDEFAULT_H

// plotting utilities
#include "./PHCorrelatorPlotMakerTools.h"
#include "./PHCorrelatorPlotMakerTypes.h"
#include "../elements/PHCorrelatorPlotterElements.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Plotting Routine Defaults
  // ==========================================================================
  /*! A small namespace to define various defaults useful
   *  for parameterizing plotting routines associated
   *  with the PHENIX ENC analysis.
   */ 
  namespace Default {

    // ========================================================================
    //! Default values
    // ========================================================================
    /*! A small struct to consolidate all default values.
     *  Can be adjusted in macro.
     */
    struct DefVals {

      std::size_t Small;       ///!< small width/height of a canvas
      std::size_t Medium;      ///!< medium width/height of a canvas 
      std::size_t Big;         ///!< big width/height of a canvas
      Style::Plot UnityStyle;  ///!< style of a line at unity
      Range       RSide;       ///!< axis ranges for an ENC histogram
      Range       RAngle;      ///!< axis ranges for an angle histogram

      // ----------------------------------------------------------------------
      //! Default ctor
      // ----------------------------------------------------------------------
      DefVals()
        : Small(750)
        , Medium(1150)
        , Big(1500)
        , UnityStyle(923, 1, 0, 9, 2)
        , RSide( 
            std::make_pair(0.003, 3.),
            std::make_pair(0.00003, 0.7),
            std::make_pair(0.00003, 33.)
          )
        , RAngle(
            std::make_pair(0.0, 6.30),
            std::make_pair(-0.007, 0.07),
            std::make_pair(0.00003, 33.)
          )
        {};

      // ----------------------------------------------------------------------
      //! Default dtor
      // ----------------------------------------------------------------------
      ~DefVals() {};

    } Values;   ///!< global instantiation of default values



    // ------------------------------------------------------------------------
    //! Select a plot range
    // ------------------------------------------------------------------------
    /*! Selects a default plot range.  Options are:
     *    - opt = Type::Side, use EEC range defaults;
     *    - opt = Type::Angle, use angle range defaults.
     *
     *  \param opt range option
     */ 
    Range PlotRange(const int opt = Type::Side) {

      Range range;
      switch (opt) {

        case Type::Side:
          range = Values.RSide;
          break;

        case Type::Angle:
          range = Values.RAngle;
          break;

        default:
          range = Range();
          std::cout << "WARNING: unknown option " << opt << "!" << std::endl;
          break;

      }
      return range;

    }  // end 'PlotRange(int)'

    // ------------------------------------------------------------------------
    //! Select a normalization range
    // ------------------------------------------------------------------------
    /*! Selects a default normalization range. Picks from
     *  the x-axes of the default plot ranges.
     *
     *  \param opt range option
     */
    Range NormRange(const int opt = Type::Side) {

      // grab plot range
      Range plot_range = PlotRange(opt);

      // set normalization range
      Range range = Range(plot_range.GetX());
      return range;

    }  // end 'NormRange(int)'

    // ------------------------------------------------------------------------
    //! Define line for unity
    // ------------------------------------------------------------------------
    /*! Defines a line sitting at y = 1 spanning the x-axis of the default 
     *  plot ranges.
     *
     *  \param opt range option
     */
    PlotShape Unity(const int opt = Type::Side) {

      return PlotShape(
        Shape(PlotRange(opt).GetX(), std::make_pair(1.0, 1.0)),
        Values.UnityStyle
      );

    }  // end 'Unity(int)'

  }  // end Defaults namespace
}  // end PHEnergyCorrelator namespace 

#endif

/// end =======================================================================
