/// ===========================================================================
/*! \file    PHCorrelatorRebin.h
 *  \authors Derek Anderson
 *  \date    12.26.2024
 *
 *  Definition of a rebinner.
 */
/// ===========================================================================

#ifndef PHCORRELATORREBIN_H
#define PHCORRELATORREBIN_H

// c++ utilities
#include <utility>
// root libraries
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
// plotting utilities
#include "PHCorrelatorPlotTypes.h"
#include "PHCorrelatorRange.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Rebinning
  // ==========================================================================
  /*! A small helper class to facilitate rebinning.
   */
  class Rebin {

    private:

      Range::Axis m_axis;   ///!< which axis to rebin
      std::size_t m_num;    ///!< number of bins to merge
      bool        m_rebin;  ///!< do or do not do rebinning

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Range::Axis GetAxis()  const {return m_axis;}
      std::size_t GetNum()   const {return m_num;}
      bool        GetRebin() const {return m_rebin;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetAxis(const Range::Axis axis) {m_axis  = axis;}
      void SetNum(const std::size_t num)   {m_num   = num;}
      void SetRebin(const bool rebin)      {m_rebin = rebin;}

      // ----------------------------------------------------------------------
      //! Apply rebinning to a TH1
      // ----------------------------------------------------------------------
      void Apply(TH1* hist) const {

        hist -> Rebin(m_num);
        return;

      }  // end 'Apply(TH1*)'

      // ----------------------------------------------------------------------
      //! Apply rebinning to a TH2
      // ----------------------------------------------------------------------
      void Apply(TH2* hist) const {

        switch (m_axis) {
          case Range::Y:
            hist -> RebinY(m_num);
            break;
          case Range::X:
            hist -> RebinX(m_num);
            break;
          default:
            hist -> RebinX(m_num);
            break;
        }
        return;

      }  // end 'Apply(TH2*)'

      // ----------------------------------------------------------------------
      //! Apply rebinning to a TH3
      // ----------------------------------------------------------------------
      void Apply(TH3* hist) const {

        switch (m_axis) {
          case Range::Z:
            hist -> RebinZ(m_num);
            break;
          case Range::Y:
            hist -> RebinY(m_num);
            break;
          case Range::X:
            hist -> RebinX(m_num);
            break;
          default:
            hist -> RebinX(m_num);
            break;
        }
        return;

      }  // end 'Apply(TH3*)'

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      Rebin() : m_axis(Range::X), m_num(2), m_rebin(false) {};
      ~Rebin() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      Rebin(
        const bool rebin,
        const std::size_t num = 2,
        const Range::Axis axis = Range::X
      ) {
        m_rebin = rebin;
        m_num   = num;
        m_axis  = axis;
      }

  };  // end Rebin

}  // end PHEnergyCorrelator namespace

#endif

/// end =======================================================================
