/// ===========================================================================
/*! \file    PHCorrelatorCanvas.h
 *  \authors Derek Anderson
 *  \date    12.26.2024
 *
 *  Definition of a canvas.
 */
/// ===========================================================================

#ifndef PHCORRELATORCANVAS_H
#define PHCORRELATORCANVAS_H

// c++ utilities
#include <optional>
#include <string>
#include <utility>
#include <vector>
// root libraries
#include <TCanvas.h>
#include <TPad.h>
// plotting utilities
#include "PHCorrelatorPad.h"
#include "PHCorrelatorPadOpts.h"
#include "PHCorrelatorPlotTypes.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Canvas definition
  // ==========================================================================
  /*! A small class to consolidate necessary data
   *  to define and work with a TCanvas.
   */ 
  class Canvas {

    private:

      // members
      PadOpts          m_opts;
      Type::Margins    m_mgns;
      Type::Dimensions m_dims;
      std::string      m_name;
      std::string      m_title = "";
      std::vector<Pad> m_pads;

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      PadOpts          GetOptions()    const {return m_opts;}
      Type::Margins    GetMargins()    const {return m_mgns;}
      Type::Dimensions GetDimensions() const {return m_dims;}
      std::string      GetName()       const {return m_name;}
      std::string      GetTitle()      const {return m_title;}
      std::vector<Pad> GetPads()       const {return m_pads;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetOptions(const PadOpts& opts)             {m_opts  = opts;}
      void SetMargins(const Type::Margins& mgns)       {m_mgns  = mgns;}
      void SetDimensions(const Type::Dimensions& dims) {m_dims  = dims;}
      void SetName(const std::string& name)            {m_name  = name;}
      void SetTitle(const std::string& ttl)            {m_title = ttl;}
      void SetPads(const std::vector<Pad>& pads)       {m_pads  = pads;}

      // ----------------------------------------------------------------------
      //! Add an associated pad
      // ----------------------------------------------------------------------
      void AddPad(const Pad& pad) {

        m_pads.push_back( pad );
        return;

      }  // end 'AddPad(Pad&)'

      // ----------------------------------------------------------------------
      //! Get a apecific associated pad
      // ----------------------------------------------------------------------
      Pad GetPad(const std::size_t index) {

        return m_pads.at(index);

      }  // end 'GetPad(std::size_t)'

      // ----------------------------------------------------------------------
      //! Create a TCanvas
      // ----------------------------------------------------------------------
      TCanvas* MakeTCanvas() const {

        // create canvas
        TCanvas* canvas = new TCanvas(
          m_name.data(),
          m_title.data(),
          m_dims.first,
          m_dims.second
        );

        // set margins if needed
        if (m_pads.empty()) {
          canvas -> SetTopMargin( m_mgns[Type::Margin::Top] );
          canvas -> SetRightMargin( m_mgns[Type::Margin::Right] );
          canvas -> SetBottomMargin( m_mgns[Type::Margin::Bottom] );
          canvas -> SetLeftMargin( m_mgns[Type::Margin::Left] );
        }

        // apply options and return pointer
        m_opts.Apply(canvas);
        return canvas;

      }  // end 'MakeTCanvas()'

      // ----------------------------------------------------------------------
      //! Create associated TPads
      // ----------------------------------------------------------------------
      std::vector<TPad*> MakeTPads() {

        std::vector<TPad*> pads;
        for (const auto& pad : m_pads) {
          pads.push_back( pad.MakeTPad() ); 
        }
        return pads;

      }  // end 'MakeTPads()'

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      Canvas()  {};
      ~Canvas() {};

      // ----------------------------------------------------------------------
      //! ctor accepting all members
      // ----------------------------------------------------------------------
      Canvas(
        const std::string& name,
        const std::string& title,
        const Type::Dimensions& dims,
        const PadOpts& opts,
        std::optional<Type::Margins> mgns = std::nullopt,
        std::optional<std::vector<Pad>> pads = std::nullopt
      ) {

        // set necessary arguments
        m_name  = name;
        m_title = title;
        m_dims  = dims;
        m_opts  = opts;

        // set optional arguments
        if (mgns.has_value()) m_mgns = mgns.value();
        if (pads.has_value()) m_pads = pads.value();

      }  // end ctor(std::string& x 2, Type::Dimensions&, PadOpts&, std::optional x 2)'

  };  // end Canvas

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
