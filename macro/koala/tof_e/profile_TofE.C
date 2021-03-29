#include "KoaHistUtility.h"

using namespace KoaUtility;

void profile_TofE(const char* filename,
                  const char* dirname = "cluster_vs_tof",
                  const char* suffix = "cluster_vs_tof_middle",
                  double e_rebin = 10, // 20 keV bin width
                  double tof_rebin = 10, // 1 ns bin width
                  double e_low = 0.03, double e_high = 5,
                  double e_limit_low = 0.01, double e_limit_high = 2,
                  double default_tof_sigma = 1.6,
                  double min_bins = 20
                  )
{
  //
  auto fin = TFile::Open(filename, "update");
  auto hdir = getDirectory(fin, dirname);
  auto h2 = (TH2D*)hdir->Get(Form("h2_%s",suffix));

  //
  auto h2_pfx = h2->ProfileX(Form("h2_%s_pfx",suffix), 1, -1, "s"); // std dev as error
  auto h2_pfy = h2->ProfileY(Form("h2_%s_pfy",suffix), 1, -1, "s"); // std dev as error

  //
  TGraph *gr_TofE = new TGraph();
  gr_TofE->SetName("gr_TofE");
  gr_TofE->SetTitle("TOF-E;E (MeV);TOF (ns)");
  gr_TofE->SetLineWidth(0);
  gr_TofE->SetMarkerSize(0.6);
  gr_TofE->SetMarkerStyle(20);
  TGraphErrors *gre_TofE = new TGraphErrors();
  gre_TofE->SetName("gre_TofE");
  gre_TofE->SetTitle("TOF-E (with 5#sigma);E (MeV);TOF (ns)");
  gre_TofE->SetLineWidth(0);
  gre_TofE->SetMarkerSize(0.4);
  gre_TofE->SetMarkerStyle(20);
  gre_TofE->SetFillColor(kRed);
  gre_TofE->SetFillStyle(3005);
  TGraph *gr_E_TofSigma = new TGraph();
  gr_E_TofSigma->SetName("gr_E_TofSigma");
  gr_E_TofSigma->SetTitle("Energy VS Sigma(TOF);E (MeV);#sigma_{TOF} (ns)");
  gr_E_TofSigma->SetLineWidth(0);
  gr_E_TofSigma->SetMarkerSize(0.6);
  gr_E_TofSigma->SetMarkerStyle(20);
  TGraph *gr_Tof_TofSigma = new TGraph();
  gr_Tof_TofSigma->SetName("gr_Tof_TofSigma");
  gr_Tof_TofSigma->SetTitle("ToF VS Sigma(TOF);Tof (ns);#sigma_{TOF} (ns)");
  gr_Tof_TofSigma->SetLineWidth(0);
  gr_Tof_TofSigma->SetMarkerSize(0.6);
  gr_Tof_TofSigma->SetMarkerStyle(20);
  TGraph *gr_E_ESigma = new TGraph();
  gr_E_ESigma->SetName("gr_E_ESigma");
  gr_E_ESigma->SetTitle("Energy VS Sigma(E);E (MeV);#sigma_{E} (MeV)");
  gr_E_ESigma->SetLineWidth(0);
  gr_E_ESigma->SetMarkerSize(0.6);
  gr_E_ESigma->SetMarkerStyle(20);

  TGraph *gr_TofE_up = new TGraph();
  gr_TofE_up->SetName("gr_TofE_up");
  gr_TofE_up->SetTitle("TOF-E;E (MeV);TOF (ns)");
  gr_TofE_up->SetLineWidth(0);
  gr_TofE_up->SetMarkerSize(0.4);
  gr_TofE_up->SetMarkerStyle(20);
  TGraph *gr_TofE_down = new TGraph();
  gr_TofE_down->SetName("gr_TofE_down");
  gr_TofE_down->SetTitle("TOF-E;E (MeV);TOF (ns)");
  gr_TofE_down->SetLineWidth(0);
  gr_TofE_down->SetMarkerSize(0.4);
  gr_TofE_down->SetMarkerStyle(20);
  TGraph *gr_E_TofSigma_Smooth = new TGraph();
  gr_E_TofSigma_Smooth->SetName("gr_E_TofSigma_Smooth");
  gr_E_TofSigma_Smooth->SetTitle("Energy VS Sigma(TOF);E (MeV);#sigma_{TOF} (ns)");
  gr_E_TofSigma_Smooth->SetLineWidth(0);
  gr_E_TofSigma_Smooth->SetMarkerSize(0.4);
  gr_E_TofSigma_Smooth->SetMarkerStyle(20);

  // find the upper limit of TOF sigma
  h2_pfx->Rebin(e_rebin);
  int xbins = h2_pfx->GetNbinsX();
  int gindex = 0;
  double thresh = default_tof_sigma;
  double tof_sigma_uplimit;
  for(int i=1;i<=xbins;i++){
    auto x = h2_pfx->GetBinCenter(i);
    auto sigma = h2_pfx->GetBinError(i);

    if(x > e_limit_low){
      tof_sigma_uplimit = sigma;
      break;
    }
  }

  //
  for(int i=1;i<=xbins;i++){
    auto evtnr = h2_pfx->GetBinEntries(i);
    auto x = h2_pfx->GetBinCenter(i);
    auto y = h2_pfx->GetBinContent(i);
    auto sigma = h2_pfx->GetBinError(i);

    if(evtnr > min_bins && x > e_low && x < e_high){
      gr_TofE->SetPoint(gindex, x, y);
      gr_E_TofSigma->SetPoint(gindex, x, sigma);
      gr_Tof_TofSigma->SetPoint(gindex, y, sigma);

      gre_TofE->SetPoint(gindex, x, y);

      // cut region
      if ( x < e_limit_low){
        thresh = tof_sigma_uplimit;
      }
      else if(x < e_limit_high){
        thresh = sigma;
      }
      else if(thresh > default_tof_sigma){
        thresh = default_tof_sigma;
      }

      gre_TofE->SetPointError(gindex, 0, 4*thresh);
      gr_TofE_up->SetPoint(gindex, x, y+4*thresh);
      gr_TofE_down->SetPoint(gindex, x, y-4*thresh);
      gr_E_TofSigma_Smooth->SetPoint(gindex, x, thresh);

      gindex++;
    }
  }

  //
  h2_pfy->Rebin(tof_rebin);
  xbins = h2_pfy->GetNbinsX();
  gindex = 0;
  for(int i=1;i<=xbins;i++){
    auto evtnr = h2_pfy->GetBinEntries(i);
    auto y = h2_pfy->GetBinContent(i);
    auto sigma = h2_pfy->GetBinError(i);

    if(evtnr > min_bins){
      gr_E_ESigma->SetPoint(gindex, y, sigma);
      gindex++;
    }
  }

  //
  hdir->WriteTObject(gr_TofE, "", "WriteDelete");
  hdir->WriteTObject(gre_TofE, "", "WriteDelete");
  hdir->WriteTObject(gr_E_TofSigma, "", "WriteDelete");
  hdir->WriteTObject(gr_Tof_TofSigma, "", "WriteDelete");
  hdir->WriteTObject(gr_E_ESigma, "", "WriteDelete");
  hdir->WriteTObject(gr_TofE_up, "", "WriteDelete");
  hdir->WriteTObject(gr_TofE_down, "", "WriteDelete");
  hdir->WriteTObject(gr_E_TofSigma_Smooth, "", "WriteDelete");

  delete gr_TofE;
  delete gre_TofE;
  delete gr_E_TofSigma;
  delete gr_Tof_TofSigma;
  delete gr_E_ESigma;
  delete gr_TofE_up;
  delete gr_TofE_down;
  delete gr_E_TofSigma_Smooth;

  //
  delete fin;
}
