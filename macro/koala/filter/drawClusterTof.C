#include "KoaHistUtility.h"
using namespace KoaUtility;

void drawClusterTof(const char* filename,
                    const char* treename, const char* brName_cluster,
                    const char* fwdhitFileName, const char* fwdhitTreeName = "fwdhit_time",
                    int time_nbin = 1500, double time_low = 450, double time_high = 750,
                    const char* elistFileName = nullptr, const char* edirName = "fwd", const char* elistName = "elist_fwdhit"
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

  // input filter based on TEntryList
  TFile* felist = nullptr;
  TDirectory* eDir = nullptr;
  TEventList* eList = nullptr;
  if ( elistFileName ) {
    felist = new TFile(elistFileName);
    eDir = getDirectory(felist, edirName);
    eList = getObject<TEventList>(eDir, elistName);
  }

  // string definition
  TString hDirName = "cluster_tof";
  TString hName = "cluster_tof";
  TString hTitle = "Cluster TOF;TOF (ns)";

  bool useSingle = false;
  if(useSingle) {
    hDirName.Append("_SingleDigi");
    hName.Append("_SingleDigi");
    hTitle.Prepend("(Only one digi in cluster)");
  }

  TString eListName = elistName;
  eListName.ReplaceAll("elist_","");

  if (elistFileName) {
    hName.Append(Form("_%s",eListName.Data()));
    hTitle.Prepend(Form("(%s cut) ", eListName.Data()));
    hDirName.Append(Form("_%s",eListName.Data()));
  }

  TString hdigiName = hName; hdigiName.ReplaceAll("cluster","digi");
  TString hdigiTitle = hTitle; hdigiTitle.ReplaceAll("Cluster","Digi");
  TString hdigiDirName = hDirName; hdigiDirName.ReplaceAll("cluster","digi");

  //
  auto h1map_cluster = bookH1dByRecTdcChannelId(hName.Data(),
                                                hTitle.Data(),
                                                time_nbin, time_low, time_high);
  auto h1map_digi = bookH1dByRecTdcChannelId(hdigiName.Data(),
                                             hdigiTitle.Data(),
                                             time_nbin, time_low, time_high);

  // event loop
  auto encoder = KoaMapEncoder::Instance();
  double pedestal_threshold[4]={0, 0, 0, 0}; // equivalent pedestal energy threshold

  Long_t entries = tree->GetEntries();
  if ( elistFileName ) {
    entries = eList->GetN();
  }
  for(auto entry=0;entry<entries;entry++){

    if ( elistFileName ) {
      auto tree_index = eList->GetEntry(entry);
      tree->GetEntry(tree_index);
    }
    else {
      tree->GetEntry(entry);
    }

    //
    if (fwdhit_timestamp > 0) {

      Int_t clusters = RecClusters->GetEntriesFast();
      for (int i=0;i<clusters;i++){
        KoaRecCluster* cluster = (KoaRecCluster*)RecClusters->At(i);

        //
        int det_id, ch_id;
        // auto cluster_id = cluster->GetMaximaChId();
        // auto cluster_id = cluster->ChIdTotal();
        det_id = cluster->GetDetId();
        cluster->SetThreshold(pedestal_threshold[det_id]);
        auto cluster_id = cluster->GetFirstChIdAboveThresh();
        ch_id = encoder->DecodeChannelID(cluster_id, det_id);

        // if(det_id == 0 && (ch_id < 12 || ch_id == 47)) continue;
        // if(det_id == 1 && (ch_id == 0 || ch_id == 63)) continue;
        if(cluster->Time() < 0) continue;
        if(useSingle && cluster->NumberOfDigis()>1) continue;

        //
        auto cluster_tof = cluster->Time() - fwdhit_timestamp;
        h1map_cluster[cluster_id].Fill(cluster_tof);

        //
        auto Nr = cluster->NumberOfDigis();
        auto Ids = cluster->GetIds();
        auto Times = cluster->GetTimestamps();

        for(int j =0; j<Nr; j++) {
          auto digi_tof = Times[j] - fwdhit_timestamp;
          h1map_digi[Ids[j]].Fill(digi_tof);
        }
      }
    }
  }

  //
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(), "update");

  TDirectory* hdir = nullptr;
  hdir = getDirectory(fout, hDirName.Data());
  writeHistos(hdir, h1map_cluster);

  hdir = getDirectory(fout, hdigiDirName.Data());
  writeHistos(hdir, h1map_digi);

  //
  delete f;
  delete ftime;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}
