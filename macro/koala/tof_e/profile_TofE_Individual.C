#include "KoaHistUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;
using namespace std;

// window: 10 keV, 1 ns
void profile_TofE_Individual(const char* filename,
                             const char* dirname = "TofE",
                             const char* suffix = "TofE",
                             int evt_limit = 10,
                             bool approx = false
                             )
{
  TProfile::Approximate(approx);

  //
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto h2map = getHistosByRecTdcChannelId<TH2D>(hdir, suffix);
  auto h2all = (TH2D*)hdir->Get(Form("h2_%s", suffix));

  auto e_bins = h2all->GetNbinsX();
  auto e_low = h2all->GetXaxis()->GetBinLowEdge(1);
  auto e_high = h2all->GetXaxis()->GetBinUpEdge(e_bins);
  auto tof_bins = h2all->GetNbinsY();
  auto tof_low = h2all->GetYaxis()->GetBinLowEdge(1);
  auto tof_high = h2all->GetYaxis()->GetBinUpEdge(tof_bins);

  TProfile *pf_tof_mean_agt = new TProfile("pf_tof_mean_agt",
                                              "Aggregation of Tof Means (Weight)",
                                              e_bins/2, e_low, e_high,
                                              tof_low, tof_high);
  TProfile *pf_tof_sigma_agt = new TProfile("pf_tof_sigma_agt",
                                            "Aggregation of Tof Sigmas (Weight)",
                                            e_bins/2, e_low, e_high,
                                            0, 30);
  pf_tof_mean_agt->SetMarkerStyle(20);
  pf_tof_sigma_agt->SetMarkerStyle(20);
  pf_tof_mean_agt->SetMarkerSize(0.4);
  pf_tof_sigma_agt->SetMarkerSize(0.4);
  pf_tof_mean_agt->SetMarkerColor(kBlue);
  pf_tof_sigma_agt->SetMarkerColor(kBlue);

  TProfile *pf_tof_mean_agt_noweight = new TProfile("pf_tof_mean_agt_noweight",
                                           "Aggregation of Tof Means (No Weight)",
                                           e_bins/2, e_low, e_high,
                                           tof_low, tof_high);
  TProfile *pf_tof_sigma_agt_noweight = new TProfile("pf_tof_sigma_agt_noweight",
                                            "Aggregation of Tof Sigmas (No Weight)",
                                            e_bins/2, e_low, e_high,
                                            0, 30);
  pf_tof_mean_agt_noweight->SetMarkerStyle(20);
  pf_tof_sigma_agt_noweight->SetMarkerStyle(20);
  pf_tof_mean_agt_noweight->SetMarkerSize(0.4);
  pf_tof_sigma_agt_noweight->SetMarkerSize(0.4);
  pf_tof_mean_agt_noweight->SetMarkerColor(kBlue);
  pf_tof_sigma_agt_noweight->SetMarkerColor(kBlue);

  /* TProfile *pf_energy_sigma_agt = new TProfile("pf_energy_sigma_agt", */
  /*                                              "Aggregation of Energy Sigmas", */
  /*                                              tof_bins, tof_low, tof_high, */
  /*                                              0, 2, */
  /*                                              "s"); */

  // key: bin index
  map<int, double> sum_evt;
  map<int, double> sum_mean;
  map<int, double> sum_variance;
  map<int, double> sum_deviation;
  map<int, double> sum_mean_squared;
  map<int, double> e_centers;

  map<int, double> sum_evt_tof;
  map<int, double> sum_mean_tof;
  map<int, double> sum_variance_tof;
  map<int, double> sum_deviation_tof;
  map<int, double> sum_mean_squared_tof;

  //
  map<int, TProfile*> profile_x;
  map<int, TProfile*> profile_y;

  auto gr_mean = bookGraphByRecTdcChannelId("mean", "E VS TOF-Mean;E (MeV); TOF (ns)",
                                            kBlack, 20, 0.4);
  auto gr_sigma = bookGraphByRecTdcChannelId("sigma", "E VS TOF-Sigma;E (MeV); #sigma_{TOF} (ns)",
                                             kBlack, 20, 0.4);

  //
  KoaMapEncoder *encoder = KoaMapEncoder::Instance();
  for(auto item: h2map){
    auto id = item.first;
    auto h2 = item.second;

    TString volName;
    Int_t ch = encoder->DecodeChannelID(id, volName);
    volName.ReplaceAll("Sensor", "");

    auto hpfx = h2->ProfileX();
    hpfx->BuildOptions(0, 0 , "s");
    // hpfx->Rebin(2);

    auto xbins = hpfx->GetNbinsX();
    int gindex = 0;
    for(int i=1;i<=xbins;i++){
      auto evtnr = hpfx->GetBinEntries(i);
      auto x = hpfx->GetBinCenter(i);
      auto y = hpfx->GetBinContent(i);
      auto err = hpfx->GetBinError(i);

      if(evtnr > evt_limit){
        pf_tof_mean_agt->Fill(x, y, evtnr);
        pf_tof_sigma_agt->Fill(x, err, evtnr);
        pf_tof_mean_agt_noweight->Fill(x, y);
        pf_tof_sigma_agt_noweight->Fill(x, err);

        sum_evt[i] += evtnr;
        sum_mean[i] += y*evtnr;
        sum_variance[i] += err*err*evtnr;
        sum_deviation[i] += err*evtnr;
        sum_mean_squared[i] += y*y*evtnr;
        e_centers[i] = x;

        gr_mean[id].SetPoint(gindex, x, y);
        gr_sigma[id].SetPoint(gindex, x, err);
        gindex++;
      }
    }

    auto hpfy = h2->ProfileY();
    hpfy->BuildOptions(0, 0 , "s");
    hpfy->Rebin(5); // 1 ns
    xbins = hpfy->GetNbinsX();
    gindex = 0;
    for(int i=1;i<=xbins;i++){
      auto evtnr = hpfy->GetBinEntries(i);
      auto x = hpfy->GetBinCenter(i);
      auto y = hpfy->GetBinContent(i);
      auto err = hpfy->GetBinError(i);

      if(evtnr > evt_limit){
        sum_evt_tof[i] += evtnr;
        sum_mean_tof[i] += y*evtnr;
        sum_variance_tof[i] += err*err*evtnr;
        sum_deviation_tof[i] += err*evtnr;
        sum_mean_squared_tof[i] += y*y*evtnr;
      }
    }

    //
    profile_x.emplace(id, hpfx);
    profile_y.emplace(id, hpfy);
  }

  // Aggregated E-TOF
  TGraph* gr_E_TofSigma_Agt = new TGraph();
  gr_E_TofSigma_Agt->SetName("gr_E_TofSigma_Agt");
  gr_E_TofSigma_Agt->SetTitle(Form("Aggregated #sigma_{TOF} (Real)"));
  gr_E_TofSigma_Agt->SetMarkerStyle(20);
  gr_E_TofSigma_Agt->SetMarkerSize(0.4);
  gr_E_TofSigma_Agt->SetMarkerColor(kBlack);
  TGraph* gr_E_TofSigma_Agt_Ideal = new TGraph();
  gr_E_TofSigma_Agt_Ideal->SetName("gr_E_TofSigma_Agt_ideal");
  gr_E_TofSigma_Agt_Ideal->SetTitle(Form("Aggregated #sigma_{TOF} (Ideal)"));
  gr_E_TofSigma_Agt_Ideal->SetMarkerStyle(20);
  gr_E_TofSigma_Agt_Ideal->SetMarkerSize(0.4);
  gr_E_TofSigma_Agt_Ideal->SetMarkerColor(kBlue);
  TGraph* gr_E_TofSigma_Agt_WeightedMean = new TGraph();
  gr_E_TofSigma_Agt_WeightedMean->SetName("gr_E_TofSigma_Agt_WeightedMean");
  gr_E_TofSigma_Agt_WeightedMean->SetTitle(Form("Aggregated #sigma_{TOF} (Weighted Mean)"));
  gr_E_TofSigma_Agt_WeightedMean->SetMarkerStyle(20);
  gr_E_TofSigma_Agt_WeightedMean->SetMarkerSize(0.4);
  gr_E_TofSigma_Agt_WeightedMean->SetMarkerColor(kRed);

  int gindex = 0;
  for(auto item: e_centers){
    auto id = item.first;
    auto energy = item.second;
    auto evts = sum_evt[id];

    auto variance = sum_variance[id]/evts;
    auto mean_squared = sum_mean_squared[id]/evts;
    auto mean = sum_mean[id]/evts;
    auto deviation = sum_deviation[id]/evts;

    gr_E_TofSigma_Agt->SetPoint(gindex, energy, TMath::Sqrt(variance+mean_squared-mean*mean));
    gr_E_TofSigma_Agt_Ideal->SetPoint(gindex, energy, TMath::Sqrt(variance));
    gr_E_TofSigma_Agt_WeightedMean->SetPoint(gindex, energy, deviation);

    gindex++;
  }

  // Aggregated E-Esigma
  TGraph* gr_E_ESigma_Agt = new TGraph();
  gr_E_ESigma_Agt->SetName("gr_E_ESigma_Agt");
  gr_E_ESigma_Agt->SetTitle(Form("Aggregated #sigma_{E} (Real)"));
  gr_E_ESigma_Agt->SetMarkerStyle(20);
  gr_E_ESigma_Agt->SetMarkerSize(0.4);
  gr_E_ESigma_Agt->SetMarkerColor(kBlack);
  TGraph* gr_E_ESigma_Agt_Ideal = new TGraph();
  gr_E_ESigma_Agt_Ideal->SetName("gr_E_ESigma_Agt_ideal");
  gr_E_ESigma_Agt_Ideal->SetTitle(Form("Aggregated #sigma_{E} (Ideal)"));
  gr_E_ESigma_Agt_Ideal->SetMarkerStyle(20);
  gr_E_ESigma_Agt_Ideal->SetMarkerSize(0.4);
  gr_E_ESigma_Agt_Ideal->SetMarkerColor(kBlue);
  TGraph* gr_E_ESigma_Agt_WeightedMean = new TGraph();
  gr_E_ESigma_Agt_WeightedMean->SetName("gr_E_ESigma_Agt_WeightedMean");
  gr_E_ESigma_Agt_WeightedMean->SetTitle(Form("Aggregated #sigma_{E} (Weighted Mean)"));
  gr_E_ESigma_Agt_WeightedMean->SetMarkerStyle(20);
  gr_E_ESigma_Agt_WeightedMean->SetMarkerSize(0.4);
  gr_E_ESigma_Agt_WeightedMean->SetMarkerColor(kRed);

  gindex = 0;
  for(auto item: sum_mean_tof){
    auto id = item.first;
    auto evts = sum_evt_tof[id];
    auto mean = item.second/evts;

    auto variance = sum_variance_tof[id]/evts;
    auto mean_squared = sum_mean_squared_tof[id]/evts;
    auto deviation = sum_deviation_tof[id]/evts;

    gr_E_ESigma_Agt->SetPoint(gindex, mean, TMath::Sqrt(variance+mean_squared-mean*mean));
    gr_E_ESigma_Agt_Ideal->SetPoint(gindex, mean, TMath::Sqrt(variance));
    gr_E_ESigma_Agt_WeightedMean->SetPoint(gindex, mean, deviation);

    gindex++;
  }

  //
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_profile.root");
  auto fout = TFile::Open(outfilename.Data(), "update");
  TDirectory* dir_out;
  if(evt_limit == 0){
    if(approx)
      dir_out = getDirectory(fout, Form("%s_profile_approx", dirname));
    else
      dir_out = getDirectory(fout, Form("%s_profile", dirname));
  }
  else{
    if(approx)
      dir_out = getDirectory(fout, Form("%s_profile_MoreThan%dEvts_approx", dirname, evt_limit));
    else
      dir_out = getDirectory(fout, Form("%s_profile_MoreThan%dEvts", dirname, evt_limit));
  }

  dir_out->WriteTObject(pf_tof_sigma_agt, "", "WriteDelete");
  dir_out->WriteTObject(pf_tof_mean_agt, "", "WriteDelete");
  dir_out->WriteTObject(pf_tof_sigma_agt_noweight, "", "WriteDelete");
  dir_out->WriteTObject(pf_tof_mean_agt_noweight, "", "WriteDelete");

  dir_out->WriteTObject(gr_E_TofSigma_Agt, "", "WriteDelete");
  dir_out->WriteTObject(gr_E_TofSigma_Agt_Ideal, "", "WriteDelete");
  dir_out->WriteTObject(gr_E_TofSigma_Agt_WeightedMean, "", "WriteDelete");

  dir_out->WriteTObject(gr_E_ESigma_Agt, "", "WriteDelete");
  dir_out->WriteTObject(gr_E_ESigma_Agt_Ideal, "", "WriteDelete");
  dir_out->WriteTObject(gr_E_ESigma_Agt_WeightedMean, "", "WriteDelete");

  writeGraphs<TGraphErrors>(dir_out, gr_mean);
  writeGraphs<TGraphErrors>(dir_out, gr_sigma);

  for(auto item: profile_x){
    dir_out->WriteTObject(item.second, "", "WriteDelete");
  }
  for(auto item: profile_y){
    dir_out->WriteTObject(item.second, "", "WriteDelete");
  }

  //
  delete fin;
  delete fout;
}
