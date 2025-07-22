// ============================================================================
//! \file   MakeSpeedTestPlot.cxx
//! \author Derek Anderson
//! \date   03.06.2025
// ----------------------------------------------------------------------------
//! A tiny macro to plot the results of the PHEnergyCorrelator
//! speed test.
// ============================================================================

#include <TCanvas.h>
#include <TGraph.h>
#include <TFile.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <vector>
#include <utility>



// ============================================================================
//! Make plot of speed test results
// ============================================================================
void MakeSpeedTestPlot() {

  // output file name
  const std::string sOutName = "speedTestResults_withUniquePairs.d17m3y2025.root";

  // legend header (description of parameters)
  const std::string sHeader = "#bf{N_{jet/evt} = 1, N_{cst/jet} = 3}";

  // no. of iterations for each test
  const std::vector<float> vecNumIter = {
    100.,
    1000.,
    10000.,
    100000.,
    1000000.
  };

  // test description and cpu times 
  //   <0> = description
  //   <1> = graph name
  //   <2> = graph color
  //   <3> = graph marker
  //   <4> = y-values
  const std::vector<
    std::tuple<
      std::string,
      std::string,
      uint32_t,
      uint32_t,
      std::vector<float>
    >
  > vecDescripts = {
    { 
      "#bf{Baseline:} main",
      "grBaseline",
      923,
      20,
      {0.17, 1.71, 17.85, 181.83, 1791.5}
    },
    {
      "#bf{Change 1:} use brackets instead of std::map::at",
      "grChange1",
      799,
      24,
      {0.19, 1.70, 18.26, 175.42, 1732.15}
    },
    {
      "#bf{Change 2:} remove unused histograms",
      "grChange2",
      899,
      25,
      {0.15, 1.28, 12.59, 131.86, 1359.72}
    },
    {
      "#bf{Change 3:} use hashes of histogram names as keys",
      "grChange3",
      879,
      26,
      {0.13, 1.17, 11.54, 112.9, 1157.41}
    },
    {
      "#bf{change 4:} look at only unique pairs",
      "grChange4",
      859,
      27,
      {0.80, 0.83, 7.56, 77.60, 772.97}
    }
  };

  // --------------------------------------------------------------------------

  // open file
  TFile* fOut = new TFile(sOutName.data(), "recreate");
  if (!fOut) return;

  // lambda to get the upper y coordinate for the legend
  auto getStopY = [](const float yStart, const std::size_t nLines) {
    return yStart + (0.05 * (nLines + 1));
  };

  // lambda to get scale graph name
  auto getScaleName = [](const std::string& name) {
    return name + "_scale";
  };

  // lambda to turn vector of times into scaled times
  auto getScales = [](const std::vector<float> times) {
    std::vector<float> scales;
    for (const float time : times) {
      scales.push_back( time / times.front() );
    }
    return scales;
  };

  // set up TLegend
  TLegend* leg = new TLegend(0.1, 0.1, 0.3, getStopY(0.1, vecDescripts.size()));
  leg -> SetFillColor(0);
  leg -> SetLineColor(0);
  leg -> SetTextFont(42);
  leg -> SetTextAlign(12);
  leg -> SetHeader(sHeader.data());

  // construct graphs
  std::vector<TGraph*> vecTimeGraphs;
  std::vector<TGraph*> vecScaleGraphs;
  for (const auto& descript : vecDescripts) {

    // make time graph
    vecTimeGraphs.push_back(
      new TGraph(
        vecNumIter.size(),
        vecNumIter.data(),
        get<4>(descript).data()
      )
    );

    // set time options
    vecTimeGraphs.back() -> SetName( get<1>(descript).data() );
    vecTimeGraphs.back() -> SetMarkerColor( get<2>(descript) );
    vecTimeGraphs.back() -> SetMarkerStyle( get<3>(descript) );
    vecTimeGraphs.back() -> SetLineColor( get<2>(descript) );
    vecTimeGraphs.back() -> SetLineStyle( 1 );
    vecTimeGraphs.back() -> SetFillColor( get<2>(descript) );
    vecTimeGraphs.back() -> SetFillStyle( 0 );
    vecTimeGraphs.back() -> GetXaxis() -> SetTitle("N_{iter}");
    vecTimeGraphs.back() -> GetYaxis() -> SetTitle("T_{CPU} = CPU time [s]");

    // add to legend
    leg -> AddEntry( vecTimeGraphs.back(), get<0>(descript).data(), "PF" );

    // make scale graph
    auto sName  = getScaleName( get<1>(descript) );
    auto scales = getScales( get<4>(descript) );
    vecScaleGraphs.push_back(
      new TGraph(
        vecNumIter.size(),
        vecNumIter.data(),
        scales.data()
      )
    );

    // set scale options
    vecScaleGraphs.back() -> SetName( sName.data() );
    vecScaleGraphs.back() -> SetMarkerColor( get<2>(descript) );
    vecScaleGraphs.back() -> SetMarkerStyle( get<3>(descript) );
    vecScaleGraphs.back() -> SetLineColor( get<2>(descript) );
    vecScaleGraphs.back() -> SetLineStyle( 1 );
    vecScaleGraphs.back() -> SetFillColor( get<2>(descript) );
    vecScaleGraphs.back() -> SetFillStyle( 0 );
    vecScaleGraphs.back() -> GetXaxis() -> SetTitle("N_{iter}");
    vecScaleGraphs.back() -> GetYaxis() -> SetTitle("T_{CPU}(N_{iter}) / T_{CPU}(1)");

  }  // end description loop

  // make time multigraph
  TMultiGraph* mgTime = new TMultiGraph();
  for (auto* graph : vecTimeGraphs) {
    mgTime -> Add(graph);
  }
  mgTime -> GetXaxis() -> SetTitle( vecTimeGraphs.back() -> GetXaxis() -> GetTitle() );
  mgTime -> GetYaxis() -> SetTitle( vecTimeGraphs.back() -> GetYaxis() -> GetTitle() );

  // make scale multigraph
  TMultiGraph* mgScale = new TMultiGraph();
  for (auto* graph : vecScaleGraphs) {
    mgScale -> Add(graph);
  }
  mgScale -> GetXaxis() -> SetTitle( vecScaleGraphs.back() -> GetXaxis() -> GetTitle() );
  mgScale -> GetYaxis() -> SetTitle( vecScaleGraphs.back() -> GetYaxis() -> GetTitle() );

  // make time plot
  TCanvas* cTime = new TCanvas("cTimeResults", "", 750, 750);
  cTime  -> SetLogx(1);
  cTime  -> SetLogy(0);
  cTime  -> SetGrid(0, 0);
  mgTime -> Draw("ALP");
  leg    -> Draw();
  fOut   -> cd();
  cTime  -> Write();
  cTime  -> Close();

  // make scale plot
  TCanvas* cScale = new TCanvas("cScaleResults", "", 750, 750);
  cScale  -> SetLogx(1);
  cScale  -> SetLogy(0);
  cScale  -> SetGrid(0, 0);
  mgScale -> Draw("ALP");
  leg     -> Draw();
  fOut    -> cd();
  cScale  -> Write();
  cScale  -> Close();

  // save graphs
  fOut -> cd();
  for (auto* graph : vecTimeGraphs) {
    graph -> Write();
  }
  for (auto* graph : vecScaleGraphs) {
    graph -> Write();
  }
  fOut -> Close();

}

// end ========================================================================
