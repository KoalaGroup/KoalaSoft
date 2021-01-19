#include "KoaHistUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

void resolution_TofE_Corrected(const char* filename,
                               const char* dirname = "TofE_TofCorrected_Individual_-5.0_5.0",
                               const char* suffix = "TofE_TofCorrected",
                               double tof_offset = 480)
{
  auto encoder = KoaMapEncoder::Instance();
  auto ip_id = encoder->EncodeChannelID(0,12);
  auto si1_edge = encoder->EncodeChannelID(0,47);
  auto si2_edge = encoder->EncodeChannelID(1,0);

  //
  auto fin = TFile::Open(filename, "update");

  TDirectory* hdir_tof = getDirectory(fin, dirname);
  auto h2map_tof = getHistosByRecTdcChannelId<TH2D>(hdir_tof, suffix);

  TString ecorrected_suffix(suffix);
  ecorrected_suffix.ReplaceAll("TofCorrected","ECorrected");
  TString ecorrected_dir(dirname);
  ecorrected_dir.ReplaceAll("TofCorrected","ECorrected");
  TDirectory* hdir_e = getDirectory(fin, ecorrected_dir.Data());
  auto h2map_e = getHistosByRecTdcChannelId<TH2D>(hdir_e, ecorrected_suffix.Data());

  //
  auto xaxis = h2map_tof[ip_id]->GetXaxis();
  auto yaxis = h2map_tof[ip_id]->GetYaxis();
  auto xbins = h2map_tof[ip_id]->GetNbinsX();
  auto ybins = h2map_tof[ip_id]->GetNbinsY();

  auto xlow = xaxis->GetBinLowEdge(1);
  auto xup = xaxis->GetBinUpEdge(xbins);
  auto ylow = yaxis->GetBinLowEdge(1);
  auto yup = yaxis->GetBinUpEdge(ybins);
  auto h2map_tof_offset = bookH2dByRecTdcChannelId(Form("%s_Offset",suffix),
                                                   Form("%s_Offset",suffix),
                                                   xbins, xlow, xup,
                                                   ybins, ylow-tof_offset, yup-tof_offset);
  auto h2_sum_tof = new TH2D(Form("h2_%s_Offset", suffix),
                             Form("TOF VS E (with TOF offset to 0)"),
                             xbins, xlow, xup,
                             ybins, ylow-tof_offset, yup-tof_offset
                             );

  xaxis = h2map_e[ip_id]->GetXaxis();
  yaxis = h2map_e[ip_id]->GetYaxis();
  xbins = h2map_e[ip_id]->GetNbinsX();
  ybins = h2map_e[ip_id]->GetNbinsY();

  xlow = xaxis->GetBinLowEdge(1);
  xup = xaxis->GetBinUpEdge(xbins);
  ylow = yaxis->GetBinLowEdge(1);
  yup = yaxis->GetBinUpEdge(ybins);
  auto h2map_e_offset = bookH2dByRecTdcChannelId(Form("%s_Offset",ecorrected_suffix.Data()),
                                                 Form("%s_Offset",ecorrected_suffix.Data()),
                                                 xbins, xlow, xup,
                                                 ybins, ylow, yup);
  auto h2_sum_e = new TH2D(Form("h2_%s_Offset", ecorrected_suffix.Data()),
                           Form("TOF VS E (with E offset to 0)"),
                           xbins, xlow, xup,
                           ybins, ylow, yup);

  //
  for(auto item: h2map_tof){
    auto id = item.first;
    auto h2 = item.second;
    auto& h2_offset = h2map_tof_offset[id];

    auto pf = h2->ProfileX();
    pf->SetErrorOption("s");
    auto xaxis = h2->GetXaxis();
    auto yaxis = h2->GetYaxis();
    auto xbins = h2->GetNbinsX();
    auto ybins = h2->GetNbinsY();

    //
    for(int x=1; x<=xbins; x++){
      auto pf_mean = pf->GetBinContent(x);
      for(int y=1; y<=ybins; y++){
        auto tof = yaxis->GetBinCenter(y);
        auto e = xaxis->GetBinCenter(x);
        auto value = h2->GetBinContent(x,y);
        h2_offset.Fill(e,tof-pf_mean,value);
      }
    }
    if(id > ip_id && id != si1_edge && id != si2_edge)
      h2_sum_tof->Add(&h2_offset);
  }

  //
  for(auto item: h2map_e){
    auto id = item.first;
    auto h2 = item.second;
    auto& h2_offset = h2map_e_offset[id];

    auto pf = h2->ProfileY();
    pf->SetErrorOption("s");
    auto xaxis = h2->GetXaxis();
    auto yaxis = h2->GetYaxis();
    auto xbins = h2->GetNbinsX();
    auto ybins = h2->GetNbinsY();

    //
    for(int y=1; y<=ybins; y++){
      auto pf_mean = pf->GetBinContent(y);
      auto tof = yaxis->GetBinCenter(y);
      for(int x=1; x<=xbins; x++){
        auto e = xaxis->GetBinCenter(x);
        auto value = h2->GetBinContent(x,y);
        h2_offset.Fill(e-pf_mean,tof,value);
      }
    }
    if(id > ip_id && id != si1_edge && id != si2_edge)
      h2_sum_e->Add(&h2_offset);
  }

  //
  TGraph* gr_sigma_tof = new TGraph();
  gr_sigma_tof->SetName("gr_sigma_individual");
  gr_sigma_tof->SetTitle(Form("Offset TOF Individual Sigma Aggregated"));
  gr_sigma_tof->SetMarkerStyle(20);
  gr_sigma_tof->SetMarkerSize(0.4);
  gr_sigma_tof->SetMarkerColor(kBlack);

  TGraph* gr_sigma_e = new TGraph();
  gr_sigma_e->SetName("gr_sigma_individual");
  gr_sigma_e->SetTitle(Form("Offset TOF Individual Sigma Aggregated"));
  gr_sigma_e->SetMarkerStyle(20);
  gr_sigma_e->SetMarkerSize(0.4);
  gr_sigma_e->SetMarkerColor(kBlack);

  auto pf_tof = h2_sum_tof->ProfileX();
  pf_tof->SetErrorOption("s");
  int npx = pf_tof->GetNbinsX();
  int gindex = 0;
  for(int i=1;i<=npx;i++){
    auto evtnr = pf_tof->GetBinEntries(i);
    auto e = pf_tof->GetBinCenter(i);
    auto sigma = pf_tof->GetBinError(i);

    if(evtnr > 20){
      gr_sigma_tof->SetPoint(gindex, e, sigma);
      gindex++;
    }
  }

  auto pf_e = h2_sum_e->ProfileY();
  pf_e->SetErrorOption("s");
  pf_e->Rebin(5);
  npx = pf_e->GetNbinsX();
  gindex = 0;
  for(int i=1;i<=npx;i++){
    auto evtnr = pf_e->GetBinEntries(i);
    auto tof = pf_e->GetBinCenter(i);
    auto sigma = pf_e->GetBinError(i);

    if(evtnr > 20){
      gr_sigma_e->SetPoint(gindex, sigma, tof);
      gindex++;
    }
  }

  //
  hdir_tof->WriteTObject(gr_sigma_tof, "", "WriteDelete");
  writeHistos<TH2D>(hdir_tof, h2map_tof_offset);
  hdir_tof->WriteTObject(h2_sum_tof, "", "WriteDelete");

  hdir_e->WriteTObject(gr_sigma_e, "", "WriteDelete");
  writeHistos<TH2D>(hdir_e, h2map_e_offset);
  hdir_e->WriteTObject(h2_sum_e, "", "WriteDelete");

  //
  delete fin;
}
