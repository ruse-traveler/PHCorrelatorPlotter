// ============================================================================
//! \file   PutSurfHistsOnCanvases.cxx
//! \author Derek Anderson
//! \date   06.14.2025
// ----------------------------------------------------------------------------
//! A short macro to place a few specific 2D
//! histograms on a few canvases.
// ============================================================================

#include <TCanvas.h>
#include <TFile.h>
#include <TPad.h>
#include <TPaveText.h>
#include <TString.h>
#include <array>
#include <iostream>
#include <vector>



// ============================================================================
//! Place some 2D histograms on some canvases
// ============================================================================
void PutSurfHistsOnCanvases() {

  TFile* in  = new TFile("surfHistsForJohn.root");
  TFile* out = new TFile("surfCanvasesForJohn.root", "recreate");
  std::cout << "Opened files" << std::endl;

  enum H {
    RPP,
    TPP,
    RPA,
    TPA  
  };

  std::vector<TString> names = {
    "hRecoEECDiFFBxBU_pp",
    "hTrueEECxDiFFBxBU_pp",
    "hRecoEECxDiFFBxBU_pa",
    "hTrueEECxDiFFBxBU_pa"
  };
  std::cout << "Collected hist names: n names = " << names.size() << std::endl;

    
  std::vector<TH1D*> hists;
  for (const auto& name : names) {
    hists.push_back( (TH1D*) in -> Get(name) );
    hists.back() -> GetZaxis() -> SetRangeUser(0.00003, 0.7);
  }
  std::cout << "Collected hists: n hists = " << hists.size() << std::endl;

  std::array<TLegend*, 4> legs;
  for (auto& leg : legs) {
    leg = new TLegend(0.02, 0.02, 0.98, 0.98);
    leg -> SetFillColor(0);
    leg -> SetLineColor(1);
    leg -> SetFillStyle(0);
    leg -> SetLineStyle(0);
    leg -> SetNColumns(3);
  }
  std::cout << "Made legends" << std::endl;

  TCanvas* cRecoPP  = new TCanvas("cEECxDiFF_recoPP", "", 950, 950);
  TPad*    pInfoRPP = new TPad("pInfoRPP", "", 0.0, 0.9, 1.0, 1.0);
  TPad*    pHistRPP = new TPad("pHistRPP", "", 0.0, 0.0, 1.0, 0.9);
  pInfoRPP -> SetTopMargin(0.02);
  pInfoRPP -> SetBottomMargin(0.005);
  pHistRPP -> SetTopMargin(0.005);
  pHistRPP -> SetLogz(1);
  cRecoPP  -> cd();
  pInfoRPP -> Draw();
  pHistRPP -> Draw();
  pHistRPP -> cd();
  hists[H::RPP] -> Draw("SURF1Z");
  pInfoRPP -> cd();
  legs[0]  -> AddEntry((TObject*) 0x0, "PHENIX simulation", "");
  legs[0]  -> AddEntry((TObject*) 0x0, "p+p, #sqrt{s} = 200 GeV", "");
  legs[0]  -> AddEntry((TObject*) 0x0, "anti-k_{T}, R = 0.3", "");
  legs[0]  -> AddEntry((TObject*) 0x0, "|#eta^{jet}| < 0.15", "");
  legs[0]  -> AddEntry((TObject*) 0x0, "p_{T}^{jet} #in (10, 15) GeV/c", ""); 
  legs[0]  -> AddEntry((TObject*) 0x0, "#bf{Reconstructed}", "");
  legs[0]  -> Draw();
  out      -> cd();
  cRecoPP  -> Write();
  cRecoPP  -> Close();
  std::cout << "Made reco pp canvas" << std::endl;

  TCanvas* cTruePP  = new TCanvas("cEECxDiFF_truePP", "", 950, 950);
  TPad*    pInfoTPP = new TPad("pInfoTPP", "", 0.0, 0.9, 1.0, 1.0);
  TPad*    pHistTPP = new TPad("pHistTPP", "", 0.0, 0.0, 1.0, 0.9);
  pInfoTPP -> SetTopMargin(0.02);
  pInfoTPP -> SetBottomMargin(0.005);
  pHistTPP -> SetTopMargin(0.005);
  pHistTPP -> SetLogz(1);
  cTruePP  -> cd();
  pInfoTPP -> Draw();
  pHistTPP -> Draw();
  pHistTPP -> cd();
  hists[H::TPP] -> Draw("SURF1Z");
  pInfoTPP -> cd();
  legs[1]  -> AddEntry((TObject*) 0x0, "PHENIX simulation", "");
  legs[1]  -> AddEntry((TObject*) 0x0, "p+p, #sqrt{s} = 200 GeV", "");
  legs[1]  -> AddEntry((TObject*) 0x0, "anti-k_{T}, R = 0.3", "");
  legs[1]  -> AddEntry((TObject*) 0x0, "|#eta^{jet}| < 0.15", "");
  legs[1]  -> AddEntry((TObject*) 0x0, "p_{T}^{jet} #in (10, 15) GeV/c", ""); 
  legs[1]  -> AddEntry((TObject*) 0x0, "#bf{Truth}", "");
  legs[1]  -> Draw();
  out      -> cd();
  cTruePP  -> Write();
  cTruePP  -> Close();
  std::cout << "Made true pp canvas" << std::endl;

  TCanvas* cRecoPA  = new TCanvas("cEECxDiFF_recoPA", "", 950, 950);
  TPad*    pInfoRPA = new TPad("pInfoRPA", "", 0.0, 0.9, 1.0, 1.0);
  TPad*    pHistRPA = new TPad("pHistRPA", "", 0.0, 0.0, 1.0, 0.9);
  pInfoRPA -> SetTopMargin(0.02);
  pInfoRPA -> SetBottomMargin(0.005);
  pHistRPA -> SetTopMargin(0.005);
  pHistRPA -> SetLogz(1);
  cRecoPA  -> cd();
  pInfoRPA -> Draw();
  pHistRPA -> Draw();
  pHistRPA -> cd();
  hists[H::RPA] -> Draw("SURF1Z");
  pInfoRPA -> cd();
  legs[2]  -> AddEntry((TObject*) 0x0, "PHENIX simulation", "");
  legs[2]  -> AddEntry((TObject*) 0x0, "p+Au, #sqrt{s} = 200 GeV", "");
  legs[2]  -> AddEntry((TObject*) 0x0, "anti-k_{T}, R = 0.3", "");
  legs[2]  -> AddEntry((TObject*) 0x0, "|#eta^{jet}| < 0.15", "");
  legs[2]  -> AddEntry((TObject*) 0x0, "p_{T}^{jet} #in (10, 15) GeV/c", ""); 
  legs[2]  -> AddEntry((TObject*) 0x0, "#bf{Reconstructed}", "");
  legs[2]  -> Draw();
  out      -> cd();
  cRecoPA  -> Write();
  cRecoPA  -> Close();
  std::cout << "Made reco pa canvas" << std::endl;

  TCanvas* cTruePA  = new TCanvas("cEECxDiFF_truePA", "", 950, 950);
  TPad*    pInfoTPA = new TPad("pInfoTPA", "", 0.0, 0.9, 1.0, 1.0);
  TPad*    pHistTPA = new TPad("pHistTPA", "", 0.0, 0.0, 1.0, 0.9);
  pInfoTPA -> SetTopMargin(0.02);
  pInfoTPA -> SetBottomMargin(0.005);
  pHistTPA -> SetTopMargin(0.005);
  pHistTPA -> SetLogz(1);
  cTruePA  -> cd();
  pInfoTPA -> Draw();
  pHistTPA -> Draw();
  pHistTPA -> cd();
  hists[H::TPA] -> Draw("SURF1Z");
  pInfoTPA -> cd();
  legs[3]  -> AddEntry((TObject*) 0x0, "PHENIX simulation", "");
  legs[3]  -> AddEntry((TObject*) 0x0, "p+Au, #sqrt{s} = 200 GeV", "");
  legs[3]  -> AddEntry((TObject*) 0x0, "anti-k_{T}, R = 0.3", "");
  legs[3]  -> AddEntry((TObject*) 0x0, "|#eta^{jet}| < 0.15", "");
  legs[3]  -> AddEntry((TObject*) 0x0, "p_{T}^{jet} #in (10, 15) GeV/c", ""); 
  legs[3]  -> AddEntry((TObject*) 0x0, "#bf{Truth}", "");
  legs[3]  -> Draw();
  out      -> cd();
  cTruePA  -> Write();
  cTruePA  -> Close();
  std::cout << "Made true pa canvas" << std::endl;

  out -> cd();
  for (auto& hist : hists) {
    hist -> Write();
  }
  out -> Close();
  in  -> cd();
  in  -> Close();
  std::cout << "Closed files" << std::endl;

  return;

}

// end ========================================================================
