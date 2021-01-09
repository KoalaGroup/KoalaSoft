#include "KoaHistUtility.h"

using namespace KoaUtility;

void sumClusterVsTof(const char* filename,
                     const char* dirname = "cluster_vs_tof",
                     const char* suffix = "cluster_vs_tof"
                     )

{
  auto encoder = KoaMapEncoder::Instance();
  int si1_id = encoder->VolNameToDetectorID("SensorSi1");
  int si2_id = encoder->VolNameToDetectorID("SensorSi2");
  // std::cout << si1_id << " " << si2_id << std::endl;

  //
  auto fin = TFile::Open(filename, "update");
  auto hdir = getDirectory(fin, dirname);

  auto histPtrs = getHistosByRecTdcChannelId<TH2D>(hdir,suffix);
  auto h2all = (TH2D*)hdir->Get(Form("h2_%s",suffix));
  TH2D* hSi1 =nullptr;
  TH2D* hSi2 =nullptr;

  for(auto item: histPtrs){
    auto id = item.first;
    auto hist = item.second;

    int det_id, ch_id;
    ch_id = encoder->DecodeChannelID(id, det_id);
    if(det_id == si1_id){
      // hist->Print();
      if(!hSi1)
        hSi1 = (TH2D*)hist->Clone(Form("h2_Si1_%s",suffix));
      else
        hSi1->Add(hist);
    }
    else if (det_id == si2_id){
      if(!hSi2)
        hSi2 = (TH2D*)hist->Clone(Form("h2_Si2_%s",suffix));
      else
        hSi2->Add(hist);
    }
    else{
      continue;
    }
  }

  //
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_TofE.root");
  auto fout = TFile::Open(outfilename.Data(), "update");
  auto hdir_out = getDirectory(fout, dirname);
  hdir_out->WriteTObject(hSi1, "", "WriteDelete");
  hdir_out->WriteTObject(hSi2, "", "WriteDelete");
  hdir_out->WriteTObject(h2all,"", "WriteDelete");

  hdir->WriteTObject(hSi1, "", "WriteDelete");
  hdir->WriteTObject(hSi2, "", "WriteDelete");
  //
  delete fin;
  delete fout;
}
