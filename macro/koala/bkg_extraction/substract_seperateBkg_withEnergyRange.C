#include "KoaHistUtility.h"
#include "KoaTextUtility.h"

using namespace KoaUtility;

void substract_seperateBkg_withEnergyRange(
                                           const char* filename,
                                           const char* bkg_filename,
                                           int si1_ref_ch = 29,
                                           int si2_ref_ch = 3,
                                           double e_low = 0.12, double e_high = 0.18,
                                           const char* dirname = "Energy_All_Individual_-5.0_5.0",
                                           const char* suffix = "Energy_All",
                                           const char* bkg_dirname = "Energy_All_NoElastic",
                                           const char* bkg_suffix = "noelastic"
                                           )
{
  // get ref ch id
  auto encoder = KoaMapEncoder::Instance();
  auto si1_ref_id = encoder->EncodeChannelID(0, si1_ref_ch-1);
  auto si2_ref_id = encoder->EncodeChannelID(1, si2_ref_ch-1);

  //
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto h1s = getHistosByRecTdcChannelId<TH1D>(hdir, suffix);
  delete fin;

  auto fbkg = TFile::Open(bkg_filename);
  hdir = getDirectory(fbkg, bkg_dirname);
  auto hbkg = getHistosByRecTdcChannelId<TH1D>(hdir, bkg_suffix);
  delete fbkg;

  // rebin
  // int rebin = 5;
  // for(auto item: h1s){
  //   auto hist = item.second;
  //   hist->Rebin(rebin);
  // }

  // compute the scale factors
  auto get_integral = [&](TH1D* hist) -> double
                      {
                        auto xaxis =  hist->GetXaxis();
                        auto bin_low = xaxis->FindBin(e_low);
                        auto bin_high = xaxis->FindBin(e_high);
                        return hist->Integral(bin_low, bin_high);
                      };

  double si1_ref_count = get_integral(hbkg[si1_ref_id]);
  double si2_ref_count = get_integral(hbkg[si2_ref_id]);
  ValueContainer<double> scale_factor;
  for(auto item: h1s){
    auto id = item.first;
    auto count = get_integral(h1s[id]);

    int det_id;
    encoder->DecodeChannelID(id, det_id);
    if(det_id == 0)
      scale_factor[id] = count/si1_ref_count;
    else if (det_id == 1)
      scale_factor[id] = count/si2_ref_count;
  }

  // book output histograms
  auto htemp = h1s[0];
  auto xbins = htemp->GetNbinsX();
  auto xaxis = htemp->GetXaxis();
  auto xlow = xaxis->GetBinLowEdge(1);
  auto xup = xaxis->GetBinUpEdge(xbins);
  auto hsub = bookH1dByRecTdcChannelId("nobkg",
                                       Form("Substract Bkg Spectrum based on Si1_%d and Si2_%d", si1_ref_ch, si2_ref_ch),
                                       xbins, xlow, xup);
  auto hdiv = bookH1dByRecTdcChannelId("divide",
                                       Form("Divide Bkg Spectrum based on Si1_%d and Si2_%d", si1_ref_ch, si2_ref_ch),
                                       xbins, xlow, xup);

  // substract the ref bkg spectrum
  auto href_si1 = (TH1D*)hbkg[si1_ref_id]->Clone("href_Si1");
  auto href_si2 = (TH1D*)hbkg[si2_ref_id]->Clone("href_Si2");
  for(auto item: h1s){
    auto id = item.first;
    int det_id;
    encoder->DecodeChannelID(id, det_id);
    if(det_id == 0) {
      hsub[id].Add(h1s[id], href_si1, 1, -scale_factor[id]);
      // hsub[id].GetXaxis()->SetRangeUser(0.12, xup);

      hdiv[id].Divide(h1s[id], href_si1, 1, scale_factor[id]);
      // hdiv[id].GetXaxis()->SetRangeUser(0.12, xup);
    }
    else if (det_id == 1) {
      hsub[id].Add(h1s[id], href_si2, 1, -scale_factor[id]);
      // hsub[id].GetXaxis()->SetRangeUser(0.12, xup);

      hdiv[id].Divide(h1s[id], href_si2, 1, scale_factor[id]);
      // hdiv[id].GetXaxis()->SetRangeUser(0.12, xup);
    }
  }

  //
  auto fout = TFile::Open(bkg_filename, "update");
  auto dir_out = getDirectory(fout, Form("%s_no_seperateBkg_withEnergyRange_low%.2f_high%.2f", suffix, e_low, e_high));
  writeHistos<TH1D>(dir_out, hsub);
  dir_out = getDirectory(fout, Form("%s_divide_seperateBkg_withEnergyRange_low%.2f_high%.2f", suffix, e_low, e_high));
  writeHistos<TH1D>(dir_out, hdiv);

  TString pdffilename(filename);
  pdffilename.ReplaceAll(".root", Form("_%s_NoSeperateBkgWithEnergyRange_low%.2f_high%.2f.pdf", suffix, e_low, e_high));
  printHistos<TH1D>(hsub, pdffilename.Data());

  pdffilename.ReplaceAll("NoSeperateBkg", "DivideSeperateBkg");
  printHistos<TH1D>(hdiv, pdffilename.Data(), "", true);

  //
  delete fout;
}
