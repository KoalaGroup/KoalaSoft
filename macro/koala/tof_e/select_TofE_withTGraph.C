#include "KoaHistUtility.h"

using namespace KoaUtility;

void select_TofE_withTGraph(const char* filename,
                            const char* dirname="cluster_vs_tof",
                            const char* suffix = "cluster_vs_tof",
                            double thresh_low = -3, double thresh_high = 3
                            )
{
  //
  auto fin = TFile::Open(filename, "update");
  auto hdir = getDirectory(fin, dirname);
  auto h2 = (TH2D*)hdir->Get(Form("h2_%s",suffix));

  auto gr_mean = (TGraph*)hdir->Get("gr_TofE");
  auto gr_sigma = (TGraph*)hdir->Get("gr_E_TofSigma_Smooth");

  //
  auto xbins = h2->GetNbinsX();
  auto ybins = h2->GetNbinsY();
  TAxis *x_ax = h2->GetXaxis();
  TAxis *y_ax = h2->GetYaxis();

  TH2D *h2_up = (TH2D*)h2->Clone(Form("%s_up", h2->GetName()));
  TH2D *h2_middle = (TH2D*)h2->Clone(Form("%s_middle", h2->GetName()));
  TH2D *h2_down = (TH2D*)h2->Clone(Form("%s_down", h2->GetName()));
  h2_up->Reset();
  h2_middle->Reset();
  h2_down->Reset();

  for(int x=1;x<xbins+1;x++){
    auto energy = x_ax->GetBinCenter(x); // in MeV
    auto tof_calc = gr_mean->Eval(energy); // ns
    auto tof_sigma = gr_sigma->Eval(energy); // ns
    auto tof_low = tof_calc + thresh_low*tof_sigma;
    auto tof_high = tof_calc + thresh_high*tof_sigma;
    for(int y=1;y<ybins+1;y++){
      auto tof = y_ax->GetBinCenter(y); // in MeV
      auto value = h2->GetBinContent(x, y);
      if(tof > tof_high) {
        h2_up->SetBinContent(x,y,value);
      }
      else if(tof < tof_low){
        h2_down->SetBinContent(x,y,value);
      }
      else{
        h2_middle->SetBinContent(x,y,value);
      }
    }
  }

  //
  hdir->WriteTObject(h2_up, "", "WriteDelete");
  hdir->WriteTObject(h2_down, "", "WriteDelete");
  hdir->WriteTObject(h2_middle, "", "WriteDelete");

  delete fin;
}
