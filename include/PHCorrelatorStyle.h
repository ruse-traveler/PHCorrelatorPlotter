/// ===========================================================================
/*! \file    PHCorrelatorStyle.h
 *  \authors Derek Anderson
 *  \date    12.26.2024
 *
 *  Definition of style components.
 */
/// ===========================================================================

#ifndef PHCORRELATORSTYLE_H
#define PHCORRELATORSTYLE_H

// c++ utilities
#include <array>
#include <vector>
// root libraries
#include <TF1.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TH1.h>
#include <TLegend.h>
#include <TLine.h>
#include <TObject.h>
#include <TPaveText.h>
// plotting utilities
#include "../hist/HistTypes.hxx"
#include "PHCorrelatorPlotTypes.h"



namespace PHEnergyCorrelator {

  // ==========================================================================
  //! Style definition
  // ==========================================================================
  /*! This class consolidates all the various
   *  options that define the style (e.g. 
   *  marker color & style) of things like
   *  histograms, graphs, etc.
   *
   *  FIXME should also add TBox, TLine, TEllipse...
   */
  class Style { 

    public:

      // ======================================================================
      //! Plot Style
      // ======================================================================
      /*! A small struct to consolidate options
       *  for color, marker, lines, and fill styles.
       */ 
      struct Plot {

        // members
        uint32_t color  = 1;
        uint32_t marker = 1;
        uint32_t fill   = 0;
        uint32_t line   = 1;
        uint32_t width  = 1;

        // --------------------------------------------------------------------
        //! default ctor/dtor
        // --------------------------------------------------------------------
        Plot()  {};
        ~Plot() {};

        // --------------------------------------------------------------------
        //! ctor accepting arguments
        // --------------------------------------------------------------------
        Plot(
          const uint32_t col_arg,
          const uint32_t mar_arg,
          const uint32_t fil_arg,
          const uint32_t lin_arg = 1,
          const uint32_t lin_wid = 1
        ) {
          color  = col_arg;
          marker = mar_arg;
          fill   = fil_arg;
          line   = lin_arg;
          width  = lin_wid;
        }  // end ctor (uint32_t x 5)

      };  // end Plot

      // ======================================================================
      //! Text style
      // ======================================================================
      /*! A small struct to consolidate options
       *  for various text attributes.
       */ 
      struct Text {

        // members
        uint32_t color   = 1;
        uint32_t font    = 42;
        uint32_t align   = 12;
        float    spacing = 0.05;

        // --------------------------------------------------------------------
        //! default ctor/dtor
        // --------------------------------------------------------------------
        Text()  {};
        ~Text() {};

        // --------------------------------------------------------------------
        //! ctor accepting arguments
        // --------------------------------------------------------------------
        Text(
          const uint32_t col_arg,
          const uint32_t fon_arg,
          const uint32_t aln_arg = 12,
          const float    spa_arg = 0.05
        ) {
          color   = col_arg;
          font    = fon_arg;
          align   = aln_arg;
          spacing = spa_arg;
        }  // end ctor(uint32_t x 3, float)

      };  // end Text

      // ======================================================================
      //! Label style
      // ======================================================================
      /*! A small struct to consolidate options
       *  for histogram, graph axis labels.
       */ 
      struct Label {

        // members
        uint32_t color  = 1;
        uint32_t font   = 42;
        float    size   = 0.04;
        float    offset = 0.005;

        // --------------------------------------------------------------------
        //! default ctor/dtor
        // --------------------------------------------------------------------
        Label()  {};
        ~Label() {};

        // --------------------------------------------------------------------
        //! ctor accepting arguments
        // --------------------------------------------------------------------
        Label(
          const uint32_t col_arg,
          const uint32_t fon_arg,
          const float    siz_arg = 0.04,
          const float    off_arg = 0.005
        ) {
          color  = col_arg;
          font   = fon_arg;
          size   = siz_arg;
          offset = off_arg;
        }  // end ctor(uint32_t x 2, float x 2)

      };  // end LabelStyle

      // ======================================================================
      //! Title style
      // ======================================================================
      /*! A small struct to consolidate options
       *  for options for histogram, graph, etc.
       *  titles. 
       */
      struct Title {

        // members
        uint32_t color  = 1;
        uint32_t center = 0;
        uint32_t font   = 42;
        float    size   = 0.04;
        float    offset = 1.0;

        // --------------------------------------------------------------------
        //! defualt ctor/dtor
        // --------------------------------------------------------------------
        Title()  {};
        ~Title() {};

        // --------------------------------------------------------------------
        //! ctor accepting arguments
        // --------------------------------------------------------------------
        Title(
          const uint32_t col_arg,
          const uint32_t cen_arg,
          const uint32_t fon_arg,
          const float    siz_arg = 0.04,
          const float    off_arg = 1.0
        ) {
          color  = col_arg;
          center = cen_arg;
          font   = fon_arg;
          size   = siz_arg;
          offset = off_arg;
        }  // end ctor(uint32_t x 3, float x 3)

      };  // end Title

    private:

      // general members
      Plot m_plot;
      Text m_text;

      // axis dependent members
      std::array<Label, 3> m_labels;
      std::array<Title, 3> m_titles;

    public:

      // ----------------------------------------------------------------------
      //! General getters
      // ----------------------------------------------------------------------
      Plot GetPlotStyle() const {return m_plot;}
      Text GetTextStyle() const {return m_text;}

      // ----------------------------------------------------------------------
      //! General setters
      // ----------------------------------------------------------------------
      void SetPlotStyle(const Plot& plot) {m_plot = plot;}
      void SetTextStyle(const Text& text) {m_text = text;}

      // ----------------------------------------------------------------------
      //! Axis dependent getters
      // ----------------------------------------------------------------------
      Label GetLabelStyle(const Types::Axis& axis) const {return m_labels[axis];}
      Title GetTitleStyle(const Types::Axis& axis) const {return m_titles[axis];}

      // ----------------------------------------------------------------------
      //! Get all label styles
      // ----------------------------------------------------------------------
      std::vector<Label> GetLabelStyles() const {

        std::vector<Label> labels;
        for (const auto& label : m_labels) {
          labels.push_back( label );
        }
        return labels;

      }  // end 'GetLabelStyles()'

      // ----------------------------------------------------------------------
      //! Get all title styles
      // ----------------------------------------------------------------------
      std::vector<Title> GetTitleStyles() const {

        std::vector<Title> titles;
        for (const auto& title : m_titles) {
          titles.push_back( title );
        }
        return titles;

      }  // end 'GetTitleStyles()'

      // ----------------------------------------------------------------------
      //! Set a specific label style
      // ----------------------------------------------------------------------
      void SetLabelStyle(const Label& label, const Types::Axis& axis) {

        m_labels[axis] = label;
        return;

      }  // end 'SetLabelStyle(Label&, Types::Axis&)'

      // ----------------------------------------------------------------------
      //! Set a specific title style
      // ----------------------------------------------------------------------
      void SetTitleStyle(const Title& title, const Types::Axis& axis) {

        m_titles[axis] = title;
        return;

      }  // end 'SetTitleStyle(Title&, Types::Axis&)'

      // ----------------------------------------------------------------------
      //! Set all axis labels to same style
      // ----------------------------------------------------------------------
      void SetLabelStyles(const Label& label) {

        std::fill(m_labels.begin(), m_labels.end(), label);
        return;

      }  // end 'SetLabelStyles(Label&)'

      // ----------------------------------------------------------------------
      //! Set all axis titles to same style
      // ----------------------------------------------------------------------
      void SetTitleStyles(const Title& title) {

        std::fill(m_titles.begin(), m_titles.end(), title);
        return;

      }  // end 'SetTitleStyle(Title&)'

      // ----------------------------------------------------------------------
      //! Set all label styles
      // ----------------------------------------------------------------------
      void SetLabelStyles(const std::vector<Label>& labels) {

        if (labels.size() >= 1) m_labels[Types::Axis::X] = labels.at(0);
        if (labels.size() >= 2) m_labels[Types::Axis::Y] = labels.at(1);
        if (labels.size() >= 3) m_labels[Types::Axis::Z] = labels.at(2);
        return;

      }  // end 'SetLabelStyles(std::vector<Label>&)'

      // ----------------------------------------------------------------------
      //! Set all title styles
      // ----------------------------------------------------------------------
      void SetTitleStyles(const std::vector<Title>& titles) {

        if (titles.size() >= 1) m_titles[Types::Axis::X] = titles.at(0);
        if (titles.size() >= 2) m_titles[Types::Axis::Y] = titles.at(1);
        if (titles.size() >= 3) m_titles[Types::Axis::Z] = titles.at(2);
        return;

      }  // end 'SetTitleStyles(std::vector<Title>&)'

      // ----------------------------------------------------------------------
      //! Apply styles to a function
      // ----------------------------------------------------------------------
      /*! Note that this method is valid for a TF1, TF2, or TF3.
       */ 
      void Apply(TF1* func) const {

        func -> SetFillColor( m_plot.color );
        func -> SetFillStyle( m_plot.fill );
        func -> SetLineColor( m_plot.color );
        func -> SetLineStyle( m_plot.line );
        func -> SetLineWidth( m_plot.width );
        func -> SetMarkerColor( m_plot.color );
        func -> SetMarkerStyle( m_plot.marker );
        func -> GetXaxis() -> CenterTitle( m_titles[Types::Axis::X].center );
        func -> GetXaxis() -> SetTitleFont( m_titles[Types::Axis::X].font );
        func -> GetXaxis() -> SetTitleSize( m_titles[Types::Axis::X].size );
        func -> GetXaxis() -> SetTitleOffset( m_titles[Types::Axis::X].offset );
        func -> GetXaxis() -> SetLabelFont( m_labels[Types::Axis::X].font );
        func -> GetXaxis() -> SetLabelSize( m_labels[Types::Axis::X].size );
        func -> GetXaxis() -> SetLabelOffset( m_labels[Types::Axis::X].offset );
        func -> GetYaxis() -> CenterTitle( m_titles[Types::Axis::Y].center );
        func -> GetYaxis() -> SetTitleFont( m_titles[Types::Axis::Y].font );
        func -> GetYaxis() -> SetTitleSize( m_titles[Types::Axis::Y].size );
        func -> GetYaxis() -> SetTitleOffset( m_titles[Types::Axis::Y].offset );
        func -> GetYaxis() -> SetLabelFont( m_labels[Types::Axis::Y].font );
        func -> GetYaxis() -> SetLabelSize( m_labels[Types::Axis::Y].size );
        func -> GetYaxis() -> SetLabelOffset( m_labels[Types::Axis::Y].offset );
        func -> GetZaxis() -> CenterTitle( m_titles[Types::Axis::Z].center );
        func -> GetZaxis() -> SetTitleFont( m_titles[Types::Axis::Z].font );
        func -> GetZaxis() -> SetTitleSize( m_titles[Types::Axis::Z].size );
        func -> GetZaxis() -> SetTitleOffset( m_titles[Types::Axis::Z].offset );
        func -> GetZaxis() -> SetLabelFont( m_labels[Types::Axis::Z].font );
        func -> GetZaxis() -> SetLabelSize( m_labels[Types::Axis::Z].size );
        func -> GetZaxis() -> SetLabelOffset( m_labels[Types::Axis::Z].offset );
        return;

      }  // end 'Apply(TFN*)'

      // ----------------------------------------------------------------------
      //! Apply styles to a histogram
      // ----------------------------------------------------------------------
      /*! Note that this method is valid for a TH1, TH2, or TH3.
       */ 
      void Apply(TH1* hist) const {

        hist -> SetFillColor( m_plot.color );
        hist -> SetFillStyle( m_plot.fill );
        hist -> SetLineColor( m_plot.color );
        hist -> SetLineStyle( m_plot.line );
        hist -> SetLineWidth( m_plot.width );
        hist -> SetMarkerColor( m_plot.color );
        hist -> SetMarkerStyle( m_plot.marker );
        hist -> SetTitleFont( m_text.font );
        hist -> GetXaxis() -> CenterTitle( m_titles[Types::Axis::X].center );
        hist -> GetXaxis() -> SetTitleFont( m_titles[Types::Axis::X].font );
        hist -> GetXaxis() -> SetTitleSize( m_titles[Types::Axis::X].size );
        hist -> GetXaxis() -> SetTitleOffset( m_titles[Types::Axis::X].offset );
        hist -> GetXaxis() -> SetLabelFont( m_labels[Types::Axis::X].font );
        hist -> GetXaxis() -> SetLabelSize( m_labels[Types::Axis::X].size );
        hist -> GetXaxis() -> SetLabelOffset( m_labels[Types::Axis::X].offset );
        hist -> GetYaxis() -> CenterTitle( m_titles[Types::Axis::Y].center );
        hist -> GetYaxis() -> SetTitleFont( m_titles[Types::Axis::Y].font );
        hist -> GetYaxis() -> SetTitleSize( m_titles[Types::Axis::Y].size );
        hist -> GetYaxis() -> SetTitleOffset( m_titles[Types::Axis::Y].offset );
        hist -> GetYaxis() -> SetLabelFont( m_labels[Types::Axis::Y].font );
        hist -> GetYaxis() -> SetLabelSize( m_labels[Types::Axis::Y].size );
        hist -> GetYaxis() -> SetLabelOffset( m_labels[Types::Axis::Y].offset );
        hist -> GetZaxis() -> CenterTitle( m_titles[Types::Axis::Z].center );
        hist -> GetZaxis() -> SetTitleFont( m_titles[Types::Axis::Z].font );
        hist -> GetZaxis() -> SetTitleSize( m_titles[Types::Axis::Z].size );
        hist -> GetZaxis() -> SetTitleOffset( m_titles[Types::Axis::Z].offset );
        hist -> GetZaxis() -> SetLabelFont( m_labels[Types::Axis::Z].font );
        hist -> GetZaxis() -> SetLabelSize( m_labels[Types::Axis::Z].size );
        hist -> GetZaxis() -> SetLabelOffset( m_labels[Types::Axis::Z].offset );
        return;

      }  // end 'Apply(TH1*)'

      // ----------------------------------------------------------------------
      //! Apply styles to a 1D graph
      // ----------------------------------------------------------------------
      /*! Note that this method is valid for TGraph, TGraphErrors, and
       *  TGraphAsymmErrors.
       */ 
      void Apply(TGraph* graph) const {

        graph -> SetFillColor( m_plot.color );
        graph -> SetFillStyle( m_plot.fill );
        graph -> SetLineColor( m_plot.color );
        graph -> SetLineStyle( m_plot.line );
        graph -> SetLineWidth( m_plot.width );
        graph -> SetMarkerColor( m_plot.color );
        graph -> SetMarkerStyle( m_plot.marker );
        graph -> GetXaxis() -> CenterTitle( m_titles[Types::Axis::X].center );
        graph -> GetXaxis() -> SetTitleFont( m_titles[Types::Axis::X].font );
        graph -> GetXaxis() -> SetTitleSize( m_titles[Types::Axis::X].size );
        graph -> GetXaxis() -> SetTitleOffset( m_titles[Types::Axis::X].offset );
        graph -> GetXaxis() -> SetLabelFont( m_labels[Types::Axis::X].font );
        graph -> GetXaxis() -> SetLabelSize( m_labels[Types::Axis::X].size );
        graph -> GetXaxis() -> SetLabelOffset( m_labels[Types::Axis::X].offset );
        graph -> GetYaxis() -> CenterTitle( m_titles[Types::Axis::Y].center );
        graph -> GetYaxis() -> SetTitleFont( m_titles[Types::Axis::Y].font );
        graph -> GetYaxis() -> SetTitleSize( m_titles[Types::Axis::Y].size );
        graph -> GetYaxis() -> SetTitleOffset( m_titles[Types::Axis::Y].offset );
        graph -> GetYaxis() -> SetLabelFont( m_labels[Types::Axis::Y].font );
        graph -> GetYaxis() -> SetLabelSize( m_labels[Types::Axis::Y].size );
        graph -> GetYaxis() -> SetLabelOffset( m_labels[Types::Axis::Y].offset );
        return;

      }  // end 'Apply(TGraph*)'

      // ----------------------------------------------------------------------
      //! Apply styles to a 2D graph
      // ----------------------------------------------------------------------
      /*! Note that this method is valid for TGraph2D and TGraph2DErrors.
       */ 
      void Apply(TGraph2D* graph) const {

        graph -> SetFillColor( m_plot.color );
        graph -> SetFillStyle( m_plot.fill );
        graph -> SetLineColor( m_plot.color );
        graph -> SetLineStyle( m_plot.line );
        graph -> SetLineWidth( m_plot.width );
        graph -> SetMarkerColor( m_plot.color );
        graph -> SetMarkerStyle( m_plot.marker );
        graph -> GetXaxis() -> CenterTitle( m_titles[Types::Axis::X].center );
        graph -> GetXaxis() -> SetTitleFont( m_titles[Types::Axis::X].font );
        graph -> GetXaxis() -> SetTitleSize( m_titles[Types::Axis::X].size );
        graph -> GetXaxis() -> SetTitleOffset( m_titles[Types::Axis::X].offset );
        graph -> GetXaxis() -> SetLabelFont( m_labels[Types::Axis::X].font );
        graph -> GetXaxis() -> SetLabelSize( m_labels[Types::Axis::X].size );
        graph -> GetXaxis() -> SetLabelOffset( m_labels[Types::Axis::X].offset );
        graph -> GetYaxis() -> CenterTitle( m_titles[Types::Axis::Y].center );
        graph -> GetYaxis() -> SetTitleFont( m_titles[Types::Axis::Y].font );
        graph -> GetYaxis() -> SetTitleSize( m_titles[Types::Axis::Y].size );
        graph -> GetYaxis() -> SetTitleOffset( m_titles[Types::Axis::Y].offset );
        graph -> GetYaxis() -> SetLabelFont( m_labels[Types::Axis::Y].font );
        graph -> GetYaxis() -> SetLabelSize( m_labels[Types::Axis::Y].size );
        graph -> GetYaxis() -> SetLabelOffset( m_labels[Types::Axis::Y].offset );
        graph -> GetZaxis() -> CenterTitle( m_titles[Types::Axis::Z].center );
        graph -> GetZaxis() -> SetTitleFont( m_titles[Types::Axis::Z].font );
        graph -> GetZaxis() -> SetTitleSize( m_titles[Types::Axis::Z].size );
        graph -> GetZaxis() -> SetTitleOffset( m_titles[Types::Axis::Z].offset );
        graph -> GetZaxis() -> SetLabelFont( m_labels[Types::Axis::Z].font );
        graph -> GetZaxis() -> SetLabelSize( m_labels[Types::Axis::Z].size );
        graph -> GetZaxis() -> SetLabelOffset( m_labels[Types::Axis::Z].offset );
        return;

      }  // end 'Apply(TGraph2D*)'

      // ----------------------------------------------------------------------
      //! Apply styles to text box
      // ----------------------------------------------------------------------
      /*! n.b. this assumes the fill and border of the
       *  TPave will be the same color.
       */
      void Apply(TPaveText* text) const {

        text -> SetFillColor( m_plot.color );
        text -> SetFillStyle( m_plot.fill );
        text -> SetLineColor( m_plot.color );
        text -> SetLineStyle( m_plot.line );
        text -> SetTextColor( m_text.color );
        text -> SetTextFont( m_text.font );
        text -> SetTextAlign( m_text.align );
        return;

      }  // end 'Apply(TPaveText*)'

      // ----------------------------------------------------------------------
      //! Apply styles to a legend
      // ----------------------------------------------------------------------
      /*! n.b. this assumes the fill and border of the
       *  TLegend will be the same color.
       */
      void Apply(TLegend* leg) const {

        leg -> SetFillColor( m_plot.color );
        leg -> SetFillStyle( m_plot.fill );
        leg -> SetLineColor( m_plot.color );
        leg -> SetLineStyle( m_plot.line );
        leg -> SetTextColor( m_text.color );
        leg -> SetTextFont( m_text.font );
        leg -> SetTextAlign( m_text.align );
        return;

      }  //  end 'Apply(TLegend*)'
      
      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      Style()  {};
      ~Style() {};

      // ----------------------------------------------------------------------
      //! ctor accepting only plot style
      // ----------------------------------------------------------------------
      Style(const Plot& plot) {

        SetPlotStyle(plot);

      }  // end ctor(Plot&)

      // ----------------------------------------------------------------------
      //! ctor accepting styles other than plot (single values)
      // ----------------------------------------------------------------------
      Style(const Text& text, const Label& label, const Title& title) {

        SetTextStyle(text);
        SetLabelStyles(label);
        SetTitleStyles(title);

      }  // end ctor(Text&, Label&, Title&)'

      // ----------------------------------------------------------------------
      //! ctor accepting styles other than plot (axis-specific values)
      // ----------------------------------------------------------------------
      Style(
        const Text& text,
        const std::vector<Label>& labels,
        const std::vector<Title>& titles
      ) {

        SetTextStyle(text);
        SetLabelStyles(labels);
        SetTitleStyles(titles);

      }  // end ctor(Text&, std::vector<Label>&, std::vector<Title>&)'

      // ----------------------------------------------------------------------
      //! ctor accepting all styles (single values)
      // ----------------------------------------------------------------------
      Style(
        const Plot& plot,
        const Text& text,
        const Label& label,
        const Title& title
      ) {

        SetPlotStyle(plot);
        SetTextStyle(text);
        SetLabelStyles(label);
        SetTitleStyles(title);

      }  // ctor(Plot&, Text&, Label&, Title&)'

      // ----------------------------------------------------------------------
      //! ctor accepting all styles (axis-specific values)
      // ----------------------------------------------------------------------
      Style(
        const Plot& plot,
        const Text& text,
        const std::vector<Label>& labels,
        const std::vector<Title>& titles
      ) {

        SetPlotStyle(plot);
        SetTextStyle(text);
        SetLabelStyles(labels);
        SetTitleStyles(titles);

      }  // ctor(Plot&, Text&, std::vector<Label>&, std::vector<Title>&)'

  };  // end Style

}  // end PHEnergyCorrelator namespace

#endif

// end ========================================================================
