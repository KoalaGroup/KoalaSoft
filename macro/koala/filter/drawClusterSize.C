#include "KoaHistUtility.h"

using namespace KoaUtility;

void drawClusterSize(const char* filename,
                     const char* outFileName,
                     const char* treename = "koalasim",
                     const char* brName_cluster = "KoaRecCluster",
                     bool useThreshold =false,
                     bool UseTimeValidCut = false,
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
  
  // input filter based on TEntryList
  TFile* felist = nullptr;
  TDirectory* eDir = nullptr;
  TEventList* eList = nullptr;
  if ( elistFileName ) {
    felist = new TFile(elistFileName);
    eDir = getDirectory(felist, edirName);
    eList = getObject<TEventList>(eDir, elistName);
  }

  // histograms
  TString h1name("cluster_size");
  TString h1title("Cluster Size");
  TString hDirName = "cluster_size";
  TString eListName = elistName;
  eListName.ReplaceAll("elist_","");

  if (elistFileName) {
    h1name.Append(Form("_%s",eListName.Data()));
    h1title.Prepend(Form("(%s cut) ", eListName.Data()));
    hDirName.Append(Form("_%s",eListName.Data()));
  }

  if(UseTimeValidCut) {
    h1name.Append("_TimeValid");
    h1title.Prepend("(T_{rec}>0)");
    hDirName.Append("_TimeValid");
  }

  if(useThreshold) {
    h1name.Append("_AboveThresh");
    h1title.Prepend("(Above Threshold)");
    hDirName.Append("_AboveThresh");
  }

  auto h1map = bookH1dByDetectorId(h1name.Data(),
                                   h1title.Data(),
                                   10, -0.5, 9.5,
                                   true,
                                   kBlack
                                   );
  //
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

    int cluster_id, det_id, ch_id, nr_digis;

    Int_t clusters = RecClusters->GetEntriesFast();
    for (int i=0;i<clusters;i++){
      KoaRecCluster* cluster = (KoaRecCluster*)RecClusters->At(i);
      det_id = cluster->GetDetId();

      if(useThreshold) {
        cluster->SetThreshold(pedestal_threshold[det_id]);
        nr_digis = cluster->NumberOfDigisAboveThresh();
      }
      else{
        nr_digis = cluster->NumberOfDigis();
      }

      if (UseTimeValidCut && cluster->Time() < 0 ) {
        continue;
      }

      h1map[det_id].Fill(nr_digis);
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
