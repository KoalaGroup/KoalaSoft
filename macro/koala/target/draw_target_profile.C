#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

void draw_target_profile(const char* profile_txtfile,
                         double zoffset_si1 = 0., double zoffset_si2 = 0. // in mm
                         )

{
  auto profile_params = readParameterList<double>(profile_txtfile);

  auto it = findValueContainer(profile_params, "Z_strip(mm)");
  auto z_strips = it->second;
  it = findValueContainer(profile_params, "Z_ref(mm)");
  auto z_refs = it->second;
  it = findValueContainer(profile_params, "Z_peak(mm)");
  auto z_peaks = it->second;
  it = findValueContainer(profile_params, "Events_ref");
  auto evt_refs = it->second;
  it = findValueContainer(profile_params, "Width_ref(MeV)");
  auto width_refs = it->second;
  
  //
  TGraph *gr_strip_si1 = new TGraph();
  gr_strip_si1->SetName("gr_strip_si1");
  gr_strip_si1->SetTitle(Form("Si1 Strip Position based profile (Si1 offset: %.2f, Si2 offset: %.2f)", zoffset_si1, zoffset_si2));
  gr_strip_si1->SetLineColor(kBlack);
  gr_strip_si1->SetMarkerColor(kBlack);
  gr_strip_si1->SetMarkerSize(0.5);
  gr_strip_si1->SetMarkerStyle(20);

  TGraph *gr_strip_si2 = new TGraph();
  gr_strip_si2->SetName("gr_strip_si2");
  gr_strip_si2->SetTitle(Form("Si2 Strip Position based profile (Si1 offset: %.2f, Si2 offset: %.2f)", zoffset_si1, zoffset_si2));
  gr_strip_si2->SetLineColor(kBlue);
  gr_strip_si2->SetMarkerColor(kBlue);
  gr_strip_si2->SetMarkerSize(0.5);
  gr_strip_si2->SetMarkerStyle(20);

  TMultiGraph *mg_strip = new TMultiGraph();
  mg_strip->SetName("mg_strip");
  mg_strip->SetTitle(Form("Si1 offset: %.2f, Si2 offset: %.2f", zoffset_si1, zoffset_si2));
  mg_strip->Add(gr_strip_si1, "P");
  mg_strip->Add(gr_strip_si2, "P");

  TGraph *gr_peak_si1 = new TGraph();
  gr_peak_si1->SetName("gr_peak_si1");
  gr_peak_si1->SetTitle(Form("Si1 Peak Position based profile"));
  gr_peak_si1->SetLineColor(kBlack);
  gr_peak_si1->SetMarkerColor(kBlack);
  gr_peak_si1->SetMarkerSize(0.5);
  gr_peak_si1->SetMarkerStyle(22);

  TGraph *gr_peak_si2 = new TGraph();
  gr_peak_si2->SetName("gr_peak_si2");
  gr_peak_si2->SetTitle(Form("Si2 Peak Position based profile"));
  gr_peak_si2->SetLineColor(kBlue);
  gr_peak_si2->SetMarkerColor(kBlue);
  gr_peak_si2->SetMarkerSize(0.5);
  gr_peak_si2->SetMarkerStyle(22);

  TMultiGraph *mg_peak = new TMultiGraph();
  mg_peak->SetName("mg_peak");
  mg_peak->SetTitle(Form("Si1 offset: %.2f, Si2 offset: %.2f", zoffset_si1, zoffset_si2));
  mg_peak->Add(gr_peak_si1, "P");
  mg_peak->Add(gr_peak_si2, "P");

  TMultiGraph *mg = new TMultiGraph();
  mg->SetName("mg_all");
  mg->SetTitle(Form("Si1 offset: %.2f, Si2 offset: %.2f", zoffset_si1, zoffset_si2));
  mg->Add(gr_peak_si1, "P");
  mg->Add(gr_peak_si2, "P");
  mg->Add(gr_strip_si1, "P");
  mg->Add(gr_strip_si2, "P");

  TH1D *h1_all = new TH1D("h1_all",Form("Si1 offset: %.2f, Si2 offset: %.2f", zoffset_si1, zoffset_si2), 1100,-40,70);
  TGraph *gr_all = new TGraph();
  gr_all->SetName("gr_all");
  gr_all->SetTitle(Form("Si1 offset: %.2f, Si2 offset: %.2f", zoffset_si1, zoffset_si2));
  gr_all->SetLineColor(kBlack);
  gr_all->SetMarkerColor(kBlack);
  gr_all->SetMarkerSize(0.5);
  gr_all->SetMarkerStyle(22);

  //
  auto encoder = KoaMapEncoder::Instance();
  int si1_id = encoder->VolNameToDetectorID("SensorSi1");
  int si2_id = encoder->VolNameToDetectorID("SensorSi2");

  int peak_si1_index =0 , strip_si1_index =0;
  int peak_si2_index =0 , strip_si2_index =0;
  int global_index = 0;
  for(auto item: z_strips){
    auto id = item.first;
    auto z_strip = item.second;

    if(id == 0) // Si1_1 noisy
      continue;

    int ch_id, det_id;
    ch_id = encoder->DecodeChannelID(id, det_id);
    if(det_id == si1_id){
      gr_strip_si1->SetPoint(strip_si1_index++, zoffset_si1+z_strips[id]-z_refs[id], evt_refs[id]/width_refs[id]);
      gr_all->SetPoint(global_index++, zoffset_si1+z_strips[id]-z_refs[id], evt_refs[id]/width_refs[id]);
      h1_all->Fill(zoffset_si1+z_strips[id]-z_refs[id], evt_refs[id]/width_refs[id]);
    }
    else{
      gr_strip_si2->SetPoint(strip_si2_index++, zoffset_si2+z_strips[id]-z_refs[id], evt_refs[id]/width_refs[id]);
      gr_all->SetPoint(global_index++, zoffset_si2+z_strips[id]-z_refs[id], evt_refs[id]/width_refs[id]);
      h1_all->Fill(zoffset_si2+z_strips[id]-z_refs[id], evt_refs[id]/width_refs[id]);
    }

    if(z_peaks[id]>0){
      if(det_id == si1_id)
        gr_peak_si1->SetPoint(peak_si1_index++, z_peaks[id]-z_refs[id], evt_refs[id]/width_refs[id]);
      else
        gr_peak_si2->SetPoint(peak_si2_index++, z_peaks[id]-z_refs[id], evt_refs[id]/width_refs[id]);

      h1_all->Fill(z_peaks[id]-z_refs[id], evt_refs[id]/width_refs[id]);
      gr_all->SetPoint(global_index++, z_peaks[id]-z_refs[id], evt_refs[id]/width_refs[id]);
    }
  }

  //
  TString outfilename(profile_txtfile);
  outfilename.ReplaceAll(".txt",".root");
  auto fout = TFile::Open(outfilename.Data(), "update");
  auto dir_out = getDirectory(fout, Form("profile_si1_%.2f_si2_%.2f",zoffset_si1, zoffset_si2));
  dir_out->WriteTObject(gr_strip_si1, "", "WriteDelete");
  dir_out->WriteTObject(gr_strip_si2, "", "WriteDelete");
  dir_out->WriteTObject(gr_peak_si1, "", "WriteDelete");
  dir_out->WriteTObject(gr_peak_si2, "", "WriteDelete");
  dir_out->WriteTObject(mg_strip, "", "WriteDelete");
  dir_out->WriteTObject(mg_peak, "", "WriteDelete");
  dir_out->WriteTObject(mg, "", "WriteDelete");
  dir_out->WriteTObject(gr_all, "", "WriteDelete");
  dir_out->WriteTObject(h1_all, "", "WriteDelete");

  delete fout;
}
