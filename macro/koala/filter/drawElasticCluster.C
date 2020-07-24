#include "KoaHistUtility.h"

using namespace KoaUtility;

void drawElasticCluster(const char* filename,
                        const char* outFileName,
                        const char* treename,
                        const char* brName_cluster,
                        const char* elistFileName
                       )
{
  // timer
  TStopwatch timer;

  // input
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* RecClusters = new TClonesArray("KoaRecCluster");
  tree->SetBranchAddress(brName_cluster, &RecClusters);
  
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
  TString hName = "cluster_energy";
  TString hTitle = "Cluster Energy;Energy(MeV)";
  TString hDirName = "rec_cluster_energy";
  TString eListName = elistName;
  eListName.ReplaceAll("elist_","");

  if (elistFileName) {
    hName.Append(Form("_%s",eListName.Data()));
    hTitle.Prepend(Form("(%s cut) ", eListName.Data()));
    hDirName.Append(Form("_%s",eListName.Data()));
  }

  if(UseTimeValidCut) {
    hName.Append("_TimeValid");
    hTitle.Prepend("(T_{rec}>0)");
    hDirName.Append("_TimeValid");
  }

  if(useSingle) {
    hName.Append("_SingleDigi");
    hTitle.Prepend("(Only one digi in cluster)");
    hDirName.Append("_SingleDigi");
  }
  else if (!useMaxId) {
    hName.Append("_firstHit");
    hTitle.Prepend("(First hit id)");
    hDirName.Append("_FirstHit");
  }

  // histogram definition
  auto h1map = bookH1dByChannelId(hName.Data(), hTitle.Data(),
                                  amp_nbin, amp_low, amp_high,
                                  true, colorLine);
  // event loop
  auto encoder = KoaMapEncoder::Instance();
  double pedestal_threshold[4]={100, 100, 500, 1000}; // equivalent pedestal energy threshold

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

    Int_t clusters = RecClusters->GetEntriesFast();
    for (int i=0;i<clusters;i++){
      KoaRecCluster* cluster = (KoaRecCluster*)RecClusters->At(i);

      //
      int cluster_id, det_id, ch_id;
      if (useMaxId) {
        cluster_id = cluster->GetMaximaChId();
        // cluster_id = cluster->ChIdTotal();
      }
      else{
        det_id = cluster->GetDetId();
        cluster->SetThreshold(pedestal_threshold[det_id]);
        cluster_id = cluster->GetFirstChIdAboveThresh();
      }
      // ch_id = encoder->DecodeChannelID(cluster_id, det_id);

      // fill
      if (UseTimeValidCut && cluster->TimeTotal() < 0)
        continue;

      if (useSingle && cluster->NumberOfDigis()>1)
        continue;

      auto cluster_e = cluster->Energy()/1000.;
      h1map[cluster_id].Fill(cluster_e);
    }
  }

  if (elistFileName) {
    std::cout << "Use event list : " << eListName << std::endl;
  }
  std::cout << "Events processed : "<< entries << std::endl;

  // output
  TFile *fout = new TFile(outFileName, "update");

  TDirectory* hdir = nullptr;
  hdir = getDirectory(fout, hDirName.Data());
  writeHistos<TH1D>(hdir, h1map);

  //
  delete f;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}
