// ============================================================================
//! \file   PutHistsOnCanvases.C
//! \author Derek Anderson
//! \date   06.14.2025
// ----------------------------------------------------------------------------
//! A short macro to place a few specific histograms
//! on a few canvases.
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
//! Place some histograms on some canvases
// ============================================================================
void PutHistsOnCanvases() {

  TFile* in  = new TFile("histsForJohn.root");
  TFile* out = new TFile("canvasesForJohn.root", "recreate");
  std::cout << "Opened files" << std::endl;

  enum H {
    REECPP,
    TEECPP,
    FEECPP,
    REECPA,
    TEECPA,
    FEECPA,
    RDFFPP,
    TDFFPP,
    FDFFPP,
    RDFFPA,
    TDFFPA,
    FDFFPA
  };

  std::vector<TString> names = {
    "hRecoEECInt_pp",
    "hTrueEECInt_pp",
    "hFracEECInt_pp",
    "hRecoEECInt_pa",
    "hTrueEECInt_pa",
    "hFracEECInt_pa",
    "hRecoDiFFBxBU_pp",
    "hTrueDiFFBxBU_pp",
    "hFracDiFFBxBU_pp",
    "hRecoDiFFBxBU_pa",
    "hTrueDiFFBxBU_pa",
    "hFracDiFFBxBU_pa"
  };
  std::cout << "Collected hist names: n names = " << names.size() << std::endl;

  std::vector<TH1D*> hists;
  for (const auto& name : names) {
    hists.push_back( (TH1D*) in -> Get(name) );
  }
  std::cout << "Collected hists: n hists = " << hists.size() << std::endl;

  std::array<TLegend*, 4> legs;
  for (auto& leg : legs) {
    leg = new TLegend(0.1, 0.1, 0.3, 0.45);
    leg -> SetFillColor(0);
    leg -> SetLineColor(0);
    leg -> SetFillStyle(0);
    leg -> SetLineStyle(0);
  }
  std::cout << "Made legends" << std::endl;

  TCanvas* cEECpp     = new TCanvas("cEEC_pp", "", 750, 1500);
  TPad*    pSpecEECpp = new TPad("pSpecEEC_pp", "", 0.0, 0.3, 1.0, 1.0);
  TPad*    pFracEECpp = new TPad("pFracEEC_pp", "", 0.0, 0.0, 1.0, 0.3);
  pSpecEECpp -> SetTopMargin(0.02);
  pSpecEECpp -> SetRightMargin(0.02);
  pSpecEECpp -> SetBottomMargin(0.005);
  pSpecEECpp -> SetLeftMargin(0.15);
  pFracEECpp -> SetTopMargin(0.005);
  pFracEECpp -> SetRightMargin(0.02);
  pFracEECpp -> SetBottomMargin(0.15);
  pFracEECpp -> SetLeftMargin(0.15);
  cEECpp     -> cd();
  pSpecEECpp -> Draw();
  pFracEECpp -> Draw();
  pSpecEECpp -> cd();
  hists[TEECPP] -> Draw();
  hists[REECPP] -> Draw("same");
  legs[0]    -> AddEntry((TObject*) 0x0, "PHENIX simulation", "");
  legs[0]    -> AddEntry((TObject*) 0x0, "p+p, #sqrt{s} = 200 GeV", "");
  legs[0]    -> AddEntry((TObject*) 0x0, "anti-k_{T}, R = 0.3", "");
  legs[0]    -> AddEntry((TObject*) 0x0, "|#eta^{jet}| < 0.15", "");
  legs[0]    -> AddEntry((TObject*) 0x0, "p_{T}^{jet} #in (10, 15) GeV/c", ""); 
  legs[0]    -> AddEntry(hists[TEECPP], "Truth", "pf");
  legs[0]    -> AddEntry(hists[REECPP], "Reconstructed", "pf");
  legs[0]    -> Draw();
  pFracEECpp -> cd();
  hists[FEECPP] -> Draw();
  out        -> cd();
  cEECpp     -> Write();
  cEECpp     -> Close();
  std::cout << "Made pp EEC canvas" << std::endl;

  TCanvas* cEECpa     = new TCanvas("cEEC_pa", "", 750, 1500);
  TPad*    pSpecEECpa = new TPad("pSpecEEC_pa", "", 0.0, 0.3, 1.0, 1.0);
  TPad*    pFracEECpa = new TPad("pFracEEC_pa", "", 0.0, 0.0, 1.0, 0.3);
  pSpecEECpa -> SetTopMargin(0.02);
  pSpecEECpa -> SetRightMargin(0.02);
  pSpecEECpa -> SetBottomMargin(0.005);
  pSpecEECpa -> SetLeftMargin(0.15);
  pFracEECpa -> SetTopMargin(0.005);
  pFracEECpa -> SetRightMargin(0.02);
  pFracEECpa -> SetBottomMargin(0.15);
  pFracEECpa -> SetLeftMargin(0.15);
  cEECpa     -> cd();
  pSpecEECpa -> Draw();
  pFracEECpa -> Draw();
  pSpecEECpa -> cd();
  hists[TEECPA] -> Draw();
  hists[REECPA] -> Draw("same");
  legs[1]    -> AddEntry((TObject*) 0x0, "PHENIX simulation", "");
  legs[1]    -> AddEntry((TObject*) 0x0, "p+Au, #sqrt{s} = 200 GeV", "");
  legs[1]    -> AddEntry((TObject*) 0x0, "anti-k_{T}, R = 0.3", "");
  legs[1]    -> AddEntry((TObject*) 0x0, "|#eta^{jet}| < 0.15", "");
  legs[1]    -> AddEntry((TObject*) 0x0, "p_{T}^{jet} #in (10, 15) GeV/c", ""); 
  legs[1]    -> AddEntry(hists[TEECPA], "Truth", "pf");
  legs[1]    -> AddEntry(hists[REECPA], "Reconstructed", "pf");
  legs[1]    -> Draw();
  pFracEECpa -> cd();
  hists[FEECPA] -> Draw();
  out        -> cd();
  cEECpa     -> Write();
  cEECpa     -> Close();
  std::cout << "Made pa EEC canvas" << std::endl;

  TCanvas* cDiFFpp     = new TCanvas("cDiFF_pp", "", 750, 1500);
  TPad*    pSpecDiFFpp = new TPad("pSpecDiFF_pp", "", 0.0, 0.3, 1.0, 1.0);
  TPad*    pFracDiFFpp = new TPad("pFracDiFF_pp", "", 0.0, 0.0, 1.0, 0.3);
  pSpecDiFFpp -> SetTopMargin(0.02);
  pSpecDiFFpp -> SetRightMargin(0.02);
  pSpecDiFFpp -> SetBottomMargin(0.005);
  pSpecDiFFpp -> SetLeftMargin(0.15);
  pFracDiFFpp -> SetTopMargin(0.005);
  pFracDiFFpp -> SetRightMargin(0.02);
  pFracDiFFpp -> SetBottomMargin(0.15);
  pFracDiFFpp -> SetLeftMargin(0.15);
  cDiFFpp     -> cd();
  pSpecDiFFpp -> Draw();
  pFracDiFFpp -> Draw();
  pSpecDiFFpp -> cd();
  hists[H::TDFFPP] -> Draw();
  hists[H::RDFFPP] -> Draw("same");
  legs[2]     -> AddEntry((TObject*) 0x0, "PHENIX simulation", "");
  legs[2]     -> AddEntry((TObject*) 0x0, "p+p, #sqrt{s} = 200 GeV", "");
  legs[2]     -> AddEntry((TObject*) 0x0, "anti-k_{T}, R = 0.3", "");
  legs[2]     -> AddEntry((TObject*) 0x0, "|#eta^{jet}| < 0.15", "");
  legs[2]     -> AddEntry((TObject*) 0x0, "p_{T}^{jet} #in (10, 15) GeV/c", ""); 
  legs[2]     -> AddEntry(hists[H::TDFFPP], "Truth", "pf");
  legs[2]     -> AddEntry(hists[H::RDFFPP], "Reconstructed", "pf");
  legs[2]     -> Draw();
  pFracDiFFpp -> cd();
  hists[H::FDFFPP] -> Draw();
  out         -> cd();
  cDiFFpp     -> Write();
  cDiFFpp     -> Close();
  std::cout << "Made pp DiFF canvas" << std::endl;

  TCanvas* cDiFFpa     = new TCanvas("cDiFF_pa", "", 750, 1500);
  TPad*    pSpecDiFFpa = new TPad("pSpecDiFF_pa", "", 0.0, 0.3, 1.0, 1.0);
  TPad*    pFracDiFFpa = new TPad("pFracDiFF_pa", "", 0.0, 0.0, 1.0, 0.3);
  pSpecDiFFpa -> SetTopMargin(0.02);
  pSpecDiFFpa -> SetRightMargin(0.02);
  pSpecDiFFpa -> SetBottomMargin(0.005);
  pSpecDiFFpa -> SetLeftMargin(0.15);
  pFracDiFFpa -> SetTopMargin(0.005);
  pFracDiFFpa -> SetRightMargin(0.02);
  pFracDiFFpa -> SetBottomMargin(0.15);
  pFracDiFFpa -> SetLeftMargin(0.15);
  cDiFFpa     -> cd();
  pSpecDiFFpa -> Draw();
  pFracDiFFpa -> Draw();
  pSpecDiFFpa -> cd();
  hists[H::TDFFPA] -> Draw();
  hists[H::RDFFPA] -> Draw("same");
  legs[3]     -> AddEntry((TObject*) 0x0, "PHENIX simulation", "");
  legs[3]     -> AddEntry((TObject*) 0x0, "p+Au, #sqrt{s} = 200 GeV", "");
  legs[3]     -> AddEntry((TObject*) 0x0, "anti-k_{T}, R = 0.3", "");
  legs[3]     -> AddEntry((TObject*) 0x0, "|#eta^{jet}| < 0.15", "");
  legs[3]     -> AddEntry((TObject*) 0x0, "p_{T}^{jet} #in (10, 15) GeV/c", ""); 
  legs[3]     -> AddEntry(hists[H::TDFFPA], "Truth", "pf");
  legs[3]     -> AddEntry(hists[H::RDFFPA], "Reconstructed", "pf");
  legs[3]     -> Draw();
  pFracDiFFpa -> cd();
  hists[H::FDFFPA] -> Draw();
  out         -> cd();
  cDiFFpa     -> Write();
  cDiFFpa     -> Close();
  std::cout << "Made pa DiFF canvas" << std::endl;

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
