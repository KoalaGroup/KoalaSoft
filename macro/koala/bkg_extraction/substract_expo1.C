#include "KoaHistUtility.h"
#include "KoaTextUtility.h"

using namespace KoaUtility;

void substract_expo1(
                     const char* filename,
                     const char* dirname = "rec_cluster_energy_FirstHit",
                     const char* suffix = "cluster_energy_firstHit",
                     double rg_low = 0.12
                     )
{
  // read in fitted paramater of expo1
  TString param_file(filename);
  param_file.ReplaceAll(".root", "_BkgExpoFit.txt");
  auto expo_params = readParameterList<double>(param_file.Data());

  auto it = findValueContainer(expo_params, "Expo_p0");
  auto p0 = it->second;
  it = findValueContainer(expo_params, "Expo_lambda");
  auto p1 = it->second;

  //
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto h1s = getHistosByRecTdcChannelId<TH1D>(hdir, suffix);

  // rebin
  // int rebin = 5;
  // for(auto item: h1s){
  //   auto hist = item.second;
  //   hist->Rebin(rebin);
  // }

  // book output histograms
  auto htemp = h1s[0];
  auto xbins = htemp->GetNbinsX();
  auto xaxis = htemp->GetXaxis();
  auto xlow = xaxis->GetBinLowEdge(1);
  auto xup = xaxis->GetBinUpEdge(xbins);
  auto hsub = bookH1dByRecTdcChannelId("noexpo1",
                                       Form("Substract Expo1 Bkg"),
                                       xbins, xlow, xup);

  // substract the expo1 bkg spectrum
  for(auto item: h1s){
    auto id = item.first;
    auto hist = item.second;
    xaxis = hist->GetXaxis();
    auto bin_low = xaxis->FindBin(rg_low); // start from 0.12
    for(int i=bin_low;i<=xbins;i++){
      auto x = xaxis->GetBinCenter(i);
      auto y = hist->GetBinContent(i);
      auto expo1 = TMath::Exp(p0[id]+p1[id]*x);
      hsub[id].SetBinContent(i, y-expo1);
    }
  }

  //
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_bkg.root");
  auto fout = TFile::Open(outfilename, "update");
  auto dir_out = getDirectory(fout, Form("no_expo1"));
  writeHistos<TH1D>(dir_out, hsub);

  TString pdffilename(filename);
  pdffilename.ReplaceAll(".root", Form("_NoExpo1.pdf"));
  printHistos<TH1D>(hsub, pdffilename.Data());

  //
  delete fin, fout;
}
