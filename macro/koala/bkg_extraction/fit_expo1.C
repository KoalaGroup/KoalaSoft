#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

void fit_expo1(
               const char* filename,
               const char* dirname = "rec_cluster_energy_FirstHit",
               const char* suffix = "cluster_energy_firstHit"
)
{
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto h1s = getHistosByRecTdcChannelId<TH1D>(hdir, suffix);

  // rebin
  int rebin = 5;
  for(auto item: h1s){
    auto hist = item.second;
    hist->Rebin(rebin);
  }

  // book output histograms
  auto htemp = h1s[0];
  auto xbins = htemp->GetNbinsX();
  auto xaxis = htemp->GetXaxis();
  auto xlow = xaxis->GetBinLowEdge(1);
  auto xup = xaxis->GetBinUpEdge(xbins);
  auto hsub = bookH1dByRecTdcChannelId("noexpo","Substract exponential bkg1",
                                       xbins, xlow, xup, kBlue);

  // book output parameters
  ParameterList<double> OutputParameters;
  auto& output_p0 = addValueContainer(OutputParameters, "Expo_p0");
  auto& output_p1 = addValueContainer(OutputParameters, "Expo_lambda");

  double fit_low = 0.12, fit_high = 0.25;
  for(auto item: h1s){
    auto id = item.first;
    auto hist = item.second;

    // fit with expo
    hist->Fit("expo", "q", "", fit_low, fit_high);
    auto fexpo = (TF1*)hist->GetFunction("expo");
    fexpo->SetRange(0,xup);
    fexpo->SetNpx(1000);
    output_p0.emplace(id, fexpo->GetParameter(0));
    output_p1.emplace(id, fexpo->GetParameter(1));

    xaxis = hsub[id].GetXaxis();
    xbins = hsub[id].GetNbinsX();
    for(int i=1;i<xbins;i++){
      auto x = xaxis->GetBinCenter(i);
      auto y = hist->GetBinContent(i);
      auto calc = fexpo->Eval(x);
      if(x > fit_low)
        hsub[id].SetBinContent(i, y-calc);
    }
  }

  //
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_bkg.root");
  auto fout = TFile::Open(outfilename, "update");
  auto dir_out = getDirectory(fout, "no_expo");
  writeHistos<TH1D>(dir_out, hsub);

  TString pdffilename(filename);
  pdffilename.ReplaceAll(".root", "_BkgNoExpo.pdf");
  printHistos<TH1D>(hsub, pdffilename.Data());
  pdffilename.ReplaceAll("_BkgNoExpo.pdf","_BkgExpoFit.pdf");
  printHistos<TH1D*>(h1s, pdffilename.Data(), "", true);

  TString outfile_txt(filename);
  outfile_txt.ReplaceAll(".root","_BkgExpoFit.txt");
  printValueList<double>(OutputParameters, outfile_txt.Data());

  //
  delete fin, fout;
}
