#include "KoaHistUtility.h"

using namespace KoaUtility;

void sumHistos(const char* filename,
               const char* dirname = "Energy",
               const char* suffix = "Energy",
               const char* suffix_out = "FwdCovered",
               int si1_low = 19, int si1_high = 30,
               int si2_low = 2, int si2_high = 3,
               int color = kBlack
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

  //
  auto fin = TFile::Open(filename, "update");
  auto hdir = getDirectory(fin, dirname);

  auto histPtrs = getHistosByRecTdcChannelId<TH1D>(hdir,suffix);
  TH1D* hSi1 =nullptr;
  TH1D* hSi2 =nullptr;

  for(auto item: histPtrs){
    auto id = item.first;
    auto hist = item.second;

    int det_id, ch_id;
    ch_id = encoder->DecodeChannelID(id, det_id);
    if(det_id == si1_id &&
       id >= si1_id_low &&
       id <= si1_id_high
       ){
      if(!hSi1)
        hSi1 = (TH1D*)hist->Clone(Form("h1_Si1_%s_%s",suffix, suffix_out));
      else
        hSi1->Add(hist);
    }
    else if (det_id == si2_id &&
             id >= si2_id_low &&
             id <= si2_id_high
             ){
      if(!hSi2)
        hSi2 = (TH1D*)hist->Clone(Form("h2_Si2_%s_%s",suffix, suffix_out));
      else
        hSi2->Add(hist);
    }
    else{
      continue;
    }
  }

  //
  hSi1->SetTitle(Form("Sum of Si1 %s Channels from %d to %d", suffix_out, si1_low, si1_high));
  hSi2->SetTitle(Form("Sum of Si2 %s Channels from %d to %d", suffix_out, si2_low, si2_high));
  hSi1->SetLineColor(color);
  hSi2->SetLineColor(color-4);
  hdir->WriteTObject(hSi1, "", "WriteDelete");
  hdir->WriteTObject(hSi2, "", "WriteDelete");

  //
  delete fin;
}
