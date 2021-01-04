#include "KoaHistUtility.h"
using namespace KoaUtility;

void checkClusterVsTof(const char* filename,
                      const char* treename, const char* brName_cluster,
                      const char* fwdhitFileName, const char* fwdhitTreeName = "fwdhit_time",
                       int nr_cl_threshold = -1,
                      int amp_nbin = 3000, double amp_low = 0, double amp_high = 6,
                      int time_nbin = 1500, double time_low = 450, double time_high = 750,
                       const char* geoFile="./geo_standard.root",
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
  TString hDirName = "cluster_vs_tof";
  TString hName = "cluster_vs_tof";
  TString hTitle = "Cluster Energy VS TOF;Energy (MeV);TOF (ns)";

  if(nr_cl_threshold>0){
    hDirName.Append(Form("_%dcluster", nr_cl_threshold));
    hName.Append(Form("_%dcluster", nr_cl_threshold));
    hTitle.Prepend(Form("(NrCluster <= %d)", nr_cl_threshold));
  }

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
  // geom
  auto fgeo = TFile::Open(geoFile);
  TGeoManager* geoMan=(TGeoManager*)fgeo->Get("FAIRGeom");
  auto geoHandler = new KoaGeoHandler(kFALSE);

  //
  TString hdigiName = hName; hdigiName.ReplaceAll("cluster","digi");
  TString hdigiTitle = hTitle; hdigiTitle.ReplaceAll("Cluster","Digi");
  TString hdigiDirName = hDirName; hdigiDirName.ReplaceAll("cluster","digi");
  auto h2_cluster = new TH2D(Form("h2_%s", hName.Data()), hTitle.Data(),
                     amp_nbin, amp_low, amp_high, time_nbin, time_low, time_high);
  auto h2_digi = new TH2D(Form("h2_%s", hdigiName.Data()), hdigiTitle.Data(),
                          amp_nbin, amp_low, amp_high, time_nbin, time_low, time_high);

  auto h2map_cluster = bookH2dByRecTdcChannelId(hName.Data(),
                                                hTitle.Data(),
                                                amp_nbin, amp_low, amp_high, time_nbin, time_low, time_high);
  auto h2map_digi = bookH2dByRecTdcChannelId(hdigiName.Data(),
                                             hdigiTitle.Data(),
                                             amp_nbin, amp_low, amp_high, time_nbin, time_low, time_high);

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
      if(clusters > nr_cl_threshold) continue;

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
        if(cluster->Time() < 0) continue;
        if(useSingle && cluster->NumberOfDigis()>1) continue;

        //
        auto cluster_e = cluster->Energy()/1000.;
        auto cluster_tof = cluster->Time() - fwdhit_timestamp;

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
  hdir = getDirectory(fout, hDirName.Data());
  hdir->WriteTObject(h2_cluster,"","Overwrite");
  writeHistos(hdir, h2map_cluster);

  hdir = getDirectory(fout, hdigiDirName.Data());
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
