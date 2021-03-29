#include "KoaHistUtility.h"

using namespace KoaUtility;

void alignHistos(
                 const char* filename,
                 const char* dirname = "Energy_Individual_-5.0_5.0",
                 const char* suffix = "Energy",
                 int si1_low = 18, int si1_high = 47,
                 int si2_low = 2, int si2_high = 13
                 )
{
  auto encoder = KoaMapEncoder::Instance();
  int si1_id = encoder->VolNameToDetectorID("SensorSi1");
  int si2_id = encoder->VolNameToDetectorID("SensorSi2");
  int si1_id_low = -1, si1_id_high = -1, si2_id_low = -1, si2_id_high = -1;
  if(si1_low != -1)  si1_id_low =  encoder->EncodeChannelID(si1_id, si1_low-1);
  if(si1_high != -1) si1_id_high = encoder->EncodeChannelID(si1_id, si1_high-1);
  if(si2_low != -1)  si2_id_low =  encoder->EncodeChannelID(si2_id, si2_low-1);
  if(si2_high != -1) si2_id_high = encoder->EncodeChannelID(si2_id, si2_high-1);
  int si1_id_dbout = encoder->EncodeChannelID(si1_id, 15);

  //
  auto fin = TFile::Open(filename, "update");
  auto hdir = getDirectory(fin, dirname);
  auto histPtrs = getHistosByRecTdcChannelId<TH1D>(hdir,suffix);

  auto htemp = histPtrs[0];
  auto xbins = htemp->GetNbinsX();
  auto xaxis = htemp->GetXaxis();
  auto xlow = xaxis->GetBinLowEdge(1);
  auto xup = xaxis->GetBinUpEdge(xbins);
  auto haligned = bookH1dByRecTdcChannelId(suffix, Form("%s_Aligned",suffix),
                                           xbins, -(xup-xlow)/2., (xup-xlow)/2.
                                           );
  auto haligned_norm = bookH1dByRecTdcChannelId(suffix, Form("%s_PeakNormalized",suffix),
                                                xbins, -(xup-xlow)/2., (xup-xlow)/2.
                                                );
  auto hstack_si1 = new THStack("hstack_Si1","Si1: Stack of Aligned Histograms");
  auto hstack_si2 = new THStack("hstack_Si2","Si2: Stack of Aligned Histograms");
  auto hstack_si1_norm = new THStack("hstack_Si1_PeakNormalized","Si1: Stack of Aligned Histograms (Normalized to Peak)");
  auto hstack_si2_norm = new THStack("hstack_Si2_PeakNormalized","Si2: Stack of Aligned Histograms (Normalized to Peak)");

  auto align_peak = [&](TH1D* hist, int id) -> bool
                    {
                      TSpectrum s(1);
                      auto npeaks = s.Search(hist, 0.05, "", 0.5);

                     if(npeaks>0) {
                       Double_t *xpeaks = s.GetPositionX();
                       auto xaxis = hist->GetXaxis();
                       auto peak_bin = xaxis->FindBin(xpeaks[0]);
                       auto scale = hist->GetBinContent(peak_bin);
                       for(int i=1;i<=xbins;i++){
                         auto x = xaxis->GetBinCenter(i);
                         auto y = hist->GetBinContent(i);
                         auto delta = xpeaks[0]-x;

                         auto newbin = haligned[id].FindBin(delta);
                         if(id <= si1_id_dbout){
                           haligned[id].SetBinContent(newbin,y/2);
                         }
                         else{
                           haligned[id].SetBinContent(newbin,y);
                         }
                         haligned_norm[id].SetBinContent(newbin, y/scale);
                       }
                     }
                     else{
                       std::cout << "No peak is found : " << hist->GetName() << std::endl;
                       return false;
                     }
                     return true;
                     };

  for(auto item: histPtrs){
    auto id = item.first;
    auto hist = item.second;
    align_peak(hist, id);

    int det_id, ch_id;
    ch_id = encoder->DecodeChannelID(id, det_id);
    if(det_id == si1_id &&
       id >= si1_id_low &&
       id <= si1_id_high
       ){
      hstack_si1->Add(&haligned[id]);
      hstack_si1_norm->Add(&haligned_norm[id]);
    }
    if(det_id == si2_id &&
       id >= si2_id_low &&
       id <= si2_id_high
       ){
      hstack_si2->Add(&haligned[id]);
      hstack_si2_norm->Add(&haligned_norm[id]);
    }
  }

  //
  TString pdffilename(filename);
  pdffilename.ReplaceAll(".root",Form("_aligned_%s.pdf",suffix));

  gStyle->SetPalette(kDeepSea);
  TCanvas c("c","c", 900,450);
  c.Divide(2,1);
  c.Print(Form("%s[", pdffilename.Data()));

  c.cd(1);
  hstack_si1->Draw("pfc nostack");
  c.cd(2);
  hstack_si1_norm->Draw("pfc nostack");
  c.Print(Form("%s", pdffilename.Data()));

  c.cd(1);
  hstack_si2->Draw("pfc nostack");
  c.cd(2);
  hstack_si2_norm->Draw("pfc nostack");
  c.Print(Form("%s", pdffilename.Data()));

  c.Print(Form("%s]", pdffilename.Data()));

  //
  auto dir_out = getDirectory(fin, Form("Aligned_%s", suffix));
  writeHistos<TH1D>(dir_out, haligned);
  dir_out->WriteTObject(hstack_si1, "", "WriteDelete");
  dir_out->WriteTObject(hstack_si2, "", "WriteDelete");
  dir_out->WriteTObject(hstack_si1_norm, "", "WriteDelete");
  dir_out->WriteTObject(hstack_si2_norm, "", "WriteDelete");

  //
  delete fin;
}
