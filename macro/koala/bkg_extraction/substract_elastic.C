#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

void substract_elastic(
                       const char* filename,
                       const char* elastic_filename,
                       const char* bkg_filename,
                       const char* dirname = "Energy_All_Individual_-5.0_5.0",
                       const char* suffix = "Energy_All",
                       const char* elastic_dirname = "Energy_Individual_-5.0_5.0",
                       const char* elastic_suffix = "Energy"
)
{
  //
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto hAll = getHistosByRecTdcChannelId<TH1D>(hdir, suffix);
  delete fin;
  
  auto felastic = TFile::Open(elastic_filename);
  hdir = getDirectory(felastic, elastic_dirname);
  auto hElastic = getHistosByRecTdcChannelId<TH1D>(hdir, elastic_suffix);
  delete felastic;

  // output histograms
  auto htemp = hAll[0];
  auto xbins = htemp->GetNbinsX();
  auto xaxis = htemp->GetXaxis();
  auto xlow = xaxis->GetBinLowEdge(1);
  auto xup = xaxis->GetBinUpEdge(xbins);
  auto hsub = bookH1dByRecTdcChannelId("noelastic",
                                       Form("Substract Elastic Spectrum"),
                                       xbins, xlow, xup);
  //
  for(auto item: hAll) {
    auto id = item.first;
    hsub[id].Add(hAll[id], hElastic[id], 1, -1);
  }

  //
  TString outfilename(bkg_filename);
  auto fout = TFile::Open(outfilename, "update");
  auto dir_out = getDirectory(fout, Form("%s_NoElastic", suffix));
  writeHistos<TH1D>(dir_out, hsub);

  TString pdffilename(filename);
  pdffilename.ReplaceAll(".root", Form("_%s_NoElastic.pdf", suffix));
  printHistos<TH1D>(hsub, pdffilename.Data(), "", true);

  //
  delete fout;
}
