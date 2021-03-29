#include "KoaHistUtility.h"
#include "KoaTextUtility.h"

using namespace KoaUtility;

void substract_bkg_withFitExpo(
                               const char* filename,
                               int ref_ch = 3,
                               double e_ref = 0.12,
                               const char* dirname = "rec_cluster_energy_FirstHit",
                               const char* suffix = "cluster_energy_firstHit"
                               )
{
  // get ref ch id
  auto encoder = KoaMapEncoder::Instance();
  auto ref_id = encoder->EncodeChannelID(0, ref_ch-1);

  // read in fitted paramater of expo1
  TString param_file(filename);
  param_file.ReplaceAll(".root", "_BkgExpoFit.txt");
  auto expo_params = readParameterList<double>(param_file.Data());

  auto it = findValueContainer(expo_params, "Expo_p0");
  auto p0 = it->second;
  it = findValueContainer(expo_params, "Expo_lambda");
  auto p1 = it->second;

  // compute the scale factors
  double ref_count = TMath::Exp(p0[ref_id]+p1[ref_id]*e_ref);
  ValueContainer<double> scale_factor;
  for(auto item: p0){
    auto id = item.first;
    auto count = TMath::Exp(p0[id]+p1[id]*e_ref);
    scale_factor[id] = count/ref_count;
  }

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
  auto dir_out = getDirectory(fout, Form("no_bkg_withFitExpo_refCh%d_refE%.2f", ref_ch, e_ref));
  writeHistos<TH1D>(dir_out, hsub);

  TString pdffilename(filename);
  pdffilename.ReplaceAll(".root", Form("_NoBkgWithFitExpo_refCh%d_refE%.2f.pdf", ref_ch, e_ref));
  printHistos<TH1D>(hsub, pdffilename.Data());

  //
  delete fin, fout;
}
