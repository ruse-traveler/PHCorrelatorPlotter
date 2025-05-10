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
#include <cmath>
#include <string>
#include <utility>
#include <vector>
// root libraries
#include <TAxis.h>
#include <TCanvas.h>
#include <TPad.h>
// plotting utilities
#include "PHCorrelatorPad.h"
#include "PHCorrelatorPadOpts.h"
#include "PHCorrelatorPlotTypes.h"
#include "PHCorrelatorPlotTools.h"
#include "PHCorrelatorRange.h"  // FIXME remove once enum is in Const::



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
      std::string      m_name;
      std::string      m_title;
      std::vector<Pad> m_pads;
      Type::Margins    m_mgns;
      Type::Dimensions m_dims;
      Type::LabelList  m_labels;

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      PadOpts          GetOptions()    const {return m_opts;}
      std::string      GetName()       const {return m_name;}
      std::string      GetTitle()      const {return m_title;}
      std::vector<Pad> GetPads()       const {return m_pads;}
      Type::Margins    GetMargins()    const {return m_mgns;}
      Type::Dimensions GetDimensions() const {return m_dims;}
      Type::LabelList  GetPadLabels()  const {return m_labels;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetOptions(const PadOpts& opts)             {m_opts  = opts;}
      void SetName(const std::string& name)            {m_name  = name;}
      void SetTitle(const std::string& ttl)            {m_title = ttl;}
      void SetPads(const std::vector<Pad>& pads)       {m_pads  = pads;}
      void SetMargins(const Type::Margins& mgns)       {m_mgns  = mgns;}
      void SetDimensions(const Type::Dimensions& dims) {m_dims  = dims;}
      void SetPadLabels(const Type::LabelList& labels) {m_labels = labels;}

      // ----------------------------------------------------------------------
      //! Helper method to scale text of a TAxis
      // ----------------------------------------------------------------------
      void DoAxisTextScaling(
        const std::size_t ibig,
        const std::size_t ismall,
        const int axis,
        TAxis* to_scale
      ) {

        // get x,y sizes of pads
        const std::pair<float, float> xsize = std::make_pair(
          m_pads.at(ibig).GetVertices()[2] - m_pads.at(ibig).GetVertices()[0],
          m_pads.at(ismall).GetVertices()[2] - m_pads.at(ismall).GetVertices()[0]
        );
        const std::pair<float, float> ysize = std::make_pair(
          m_pads.at(ibig).GetVertices()[3] - m_pads.at(ibig).GetVertices()[1],
          m_pads.at(ismall).GetVertices()[3] - m_pads.at(ismall).GetVertices()[1]
        );

        // calculate scale
        const float xscale = abs(xsize.first) / abs(xsize.second);
        const float yscale = abs(ysize.first) / abs(ysize.second);
        const float scale  = xscale * yscale;

        // grab old title/label text
        const float size_ttl = to_scale -> GetTitleSize();
        const float off_ttl  = to_scale -> GetTitleOffset();
        const float size_lbl = to_scale -> GetLabelSize();
        const float off_lbl  = to_scale -> GetLabelOffset();

        // update title/label text
        to_scale -> SetTitleSize( size_ttl * scale );
        to_scale -> SetLabelSize( size_lbl * scale );
        if (axis == Range::Y) {
          to_scale -> SetTitleOffset( off_ttl / scale );
          to_scale -> SetLabelOffset( off_lbl / scale );
        }
        return;

      }  // end 'DoAxisTextScaling(std::size_t x 2, int, TAxis*)'

      // ----------------------------------------------------------------------
      //! Add an associated pad
      // ----------------------------------------------------------------------
      void AddPad(const Pad& pad, const std::string& label = "") {

        // add pad definition
        m_pads.push_back( pad );

        // by default, use the index as a label
        std::string label_use = label;
        if (label_use.empty()) {
          label_use = Tools::StringifyIndex( m_pads.size() - 1 );
        }
        m_labels.push_back( label_use );
        return;

      }  // end 'AddPad(Pad&)'

      // ----------------------------------------------------------------------
      //! Get a specific pad based on index
      // ----------------------------------------------------------------------
      Pad GetPad(const std::size_t index) {

        return m_pads.at(index);

      }  // end 'GetPad(std::size_t)'

      // ----------------------------------------------------------------------
      //! Get a specific pad label based on index
      // ----------------------------------------------------------------------
      std::string GetPadLabel(const std::size_t index) {

        return m_labels.at(index);

      }  // end 'GetPadLabel(std::size_t)'

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
          canvas -> SetTopMargin( m_mgns[Type::Top] );
          canvas -> SetRightMargin( m_mgns[Type::Right] );
          canvas -> SetBottomMargin( m_mgns[Type::Bottom] );
          canvas -> SetLeftMargin( m_mgns[Type::Left] );
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
        for (std::size_t ipad = 0; ipad < m_pads.size(); ++ipad) {
          pads.push_back( m_pads[ipad].MakeTPad() );
          m_pads[ipad].GetOptions().Apply( pads.back() ); 
        }
        return pads;

      }  // end 'MakeTPads()'

      // ----------------------------------------------------------------------
      //! default ctor
      // ----------------------------------------------------------------------
      Canvas() {
        m_title = "";
        m_dims  = std::make_pair(750, 750);
      };

      // ----------------------------------------------------------------------
      //! default dtor
      // ----------------------------------------------------------------------
      ~Canvas() {};

      // ----------------------------------------------------------------------
      //! ctor accepting all members
      // ----------------------------------------------------------------------
      Canvas(
        const std::string& name,
        const std::string& title,
        const Type::Dimensions& dims,
        const PadOpts& opts,
        const Type::Margins& mgns = std::vector<float>(),
        const std::vector<Pad>& pads = std::vector<Pad>(),
        const Type::LabelList& lbls = std::vector<std::string>()
      ) {

        // set necessary arguments
        m_name  = name;
        m_title = title;
        m_dims  = dims;
        m_opts  = opts;

        // set optional arguments
        if (!mgns.empty()) m_mgns   = mgns;
        if (!pads.empty()) m_pads   = pads;
        if (!lbls.empty()) m_labels = lbls;

      }  // end ctor(...)

  };  // end Canvas

}    // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
