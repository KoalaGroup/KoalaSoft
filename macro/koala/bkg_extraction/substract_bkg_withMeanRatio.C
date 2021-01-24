#include "KoaHistUtility.h"
#include "KoaTextUtility.h"

using namespace KoaUtility;

void substract_bkg_withMeanRatio(
                                 const char* filename,
                                 int ref_ch = 3,
                                 double e_low = 0.12, double e_high = 0.2,
                                 const char* dirname = "rec_cluster_energy_FirstHit",
                                 const char* suffix = "cluster_energy_firstHit"
                                 )
{
  // get ref ch id
  auto encoder = KoaMapEncoder::Instance();
  auto ref_id = encoder->EncodeChannelID(0, ref_ch-1);

  //
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto h1s = getHistosByRecTdcChannelId<TH1D>(hdir, suffix);

  // rebin
  int rebin = 5;
  for(auto item: h1s){
    auto hist = item.second;
    hist->Rebin(rebin);
  }

  // compute the scale factors
  auto get_ratio = [&](TH1D* hist) -> double
                   {
                     auto xaxis =  hist->GetXaxis();
                     auto bin_low = xaxis->FindBin(e_low);
                     auto bin_high = xaxis->FindBin(e_high);
                     double sum_ratio = 0;
                     for(int bin = bin_low;bin<bin_high;bin++){
                       double ratio = hist->GetBinContent(bin)/h1s[ref_id]->GetBinContent(bin);
                       sum_ratio += ratio;
                     }
                     return sum_ratio/(bin_high-bin_low);
                   };

  ValueContainer<double> scale_factor;
  for(auto item: h1s){
    auto id = item.first;
    auto ratio = get_ratio(h1s[id]);
    scale_factor[id] = ratio;
  }

  // book output histograms
  auto htemp = h1s[0];
  auto xbins = htemp->GetNbinsX();
  auto xaxis = htemp->GetXaxis();
  auto xlow = xaxis->GetBinLowEdge(1);
  auto xup = xaxis->GetBinUpEdge(xbins);
  auto hsub = bookH1dByRecTdcChannelId("nobkg",
                                       Form("Substract Bkg Spectrum based on Si1_%d", ref_ch),
                                       xbins, xlow, xup);

  // substract the ref bkg spectrum
  auto href = (TH1D*)h1s[ref_id]->Clone("href");
  for(auto item: h1s){
    auto id = item.first;
    hsub[id].Add(h1s[id], href, 1, -scale_factor[id]);
    hsub[id].GetXaxis()->SetRangeUser(0.12, xup);
  }

  //
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_bkg.root");
  auto fout = TFile::Open(outfilename, "update");
  auto dir_out = getDirectory(fout, Form("no_bkg_withMeanRatio_low%.2f_high%.2f", e_low, e_high));
  writeHistos<TH1D>(dir_out, hsub);

  TString pdffilename(filename);
  pdffilename.ReplaceAll(".root", Form("_NoBkgWithMeanRatio_low%.2f_high%.2f.pdf", e_low, e_high));
  printHistos<TH1D>(hsub, pdffilename.Data());

  //
  delete fin, fout;
}
