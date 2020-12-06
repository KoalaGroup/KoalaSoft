#include "KoaHistUtility.h"
using namespace KoaUtility;

void checkClusterVsTof(const char* filename,
                       const char* treename, const char* brName_cluster,
                       const char* fwdhitFileName, const char* fwdhitTreeName = "fwdhit_time",
                       int amp_nbin = 500, double amp_low = 0, double amp_high = 10,
                       int time_nbin = 1500, double time_low = 450, double time_high = 750,
                       const char* geoFile="./geo_standard.root"
                       )
{
  // timer
  TStopwatch timer;

  // input
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* RecClusters = new TClonesArray("KoaRecCluster");
  tree->SetBranchAddress(brName_cluster, &RecClusters);

  TFile* ftime = new TFile(fwdhitFileName);
  TTree* tree_time = (TTree*)ftime->Get(fwdhitTreeName);
  Float_t fwdhit_timestamp;
  tree_time->SetBranchAddress(fwdhitTreeName,&fwdhit_timestamp);

  tree->AddFriend(tree_time);

  // geom
  auto fgeo = TFile::Open(geoFile);
  TGeoManager* geoMan=(TGeoManager*)fgeo->Get("FAIRGeom");
  auto geoHandler = new KoaGeoHandler(kFALSE);

  //
  auto h2_cluster = new TH2D("h2_cluster_vs_tof", "Cluster Energy VS TOF;Energy(MeV);TOF(ns)",
                     amp_nbin, amp_low, amp_high, time_nbin, time_low, time_high);
  auto h2_digi = new TH2D("h2_digi_vs_tof", "Digi Energy VS TOF;Energy(MeV);TOF(ns)",
                          amp_nbin, amp_low, amp_high, time_nbin, time_low, time_high);

  auto h2map_cluster = bookH2dByRecTdcChannelId("cluster_vs_tof",
                                                "Cluster Energy VS TOF;Energy(MeV);TOF(ns)",
                                                amp_nbin, amp_low, amp_high, time_nbin, time_low, time_high);
  auto h2map_digi = bookH2dByRecTdcChannelId("digi_vs_tof",
                                             "Digi Energy VS TOF;Energy(MeV);TOF(ns)",
                                             amp_nbin, amp_low, amp_high, time_nbin, time_low, time_high);

  // event loop
  auto encoder = KoaMapEncoder::Instance();
  double pedestal_threshold[4]={0, 0, 0, 0}; // equivalent pedestal energy threshold

  Long_t entries = tree->GetEntries();
  for(auto entry=0;entry<entries;entry++){
    tree->GetEntry(entry);

    //
    if (fwdhit_timestamp > 0) {

      Int_t clusters = RecClusters->GetEntriesFast();
      for (int i=0;i<clusters;i++){
        KoaRecCluster* cluster = (KoaRecCluster*)RecClusters->At(i);

        //
        int det_id, ch_id;
        cluster->SetGeoHandler(geoHandler);
        // auto cluster_id = cluster->GetMaximaChId();
        // auto cluster_id = cluster->ChIdTotal();
        det_id = cluster->GetDetId();
        cluster->SetThreshold(pedestal_threshold[det_id]);
        auto cluster_id = cluster->GetFirstChIdAboveThresh();
        ch_id = encoder->DecodeChannelID(cluster_id, det_id);

        if(det_id == 0 && (ch_id < 12 || ch_id == 47)) continue;
        if(det_id == 1 && (ch_id == 0 || ch_id == 63)) continue;
        if(cluster->TimeFirstCh() < 0) continue;

        //
        auto cluster_e = cluster->Energy()/1000.;
        auto cluster_tof = cluster->TimeFirstCh() - fwdhit_timestamp;

        h2_cluster->Fill(cluster_e, cluster_tof);

        h2map_cluster[cluster_id].Fill(cluster_e, cluster_tof);

        //
        auto Nr = cluster->NumberOfDigis();
        auto Ids = cluster->GetIds();
        auto Times = cluster->GetTimestamps();
        auto Energies= cluster->GetEnergies();

        for(int j =0; j<Nr; j++) {
          auto digi_e = Energies[j]/1000.;
          auto digi_tof = Times[j] - fwdhit_timestamp;
          h2_digi->Fill(digi_e, digi_tof);

          h2map_digi[Ids[j]].Fill(digi_e, digi_tof);
        }
      }
    }
  }

  //
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(), "update");

  TDirectory* hdir = nullptr;
  hdir = getDirectory(fout, "cluster_vs_tof");
  hdir->WriteTObject(h2_cluster,"","Overwrite");
  writeHistos(hdir, h2map_cluster);

  hdir = getDirectory(fout, "digi_vs_tof");
  hdir->WriteTObject(h2_digi,"","Overwrite");
  writeHistos(hdir, h2map_digi);

  //
  delete f;
  delete ftime;
  delete fout;
  delete fgeo;

  // timer stat
  timer.Stop();
  timer.Print();
}
