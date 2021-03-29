#include "KoaHistUtility.h"

using namespace KoaUtility;

void drawClusterEnergyWithSize(const char* filename,
                               const char* outFileName,
                               const char* treename,
                               const char* brName_cluster,
                               const int sizeCut,
                               bool useMaxId = false,
                               int amp_nbin = 7000, double amp_low = 0, double amp_high = 70, int colorLine = kBlack
                               )
{
  // timer
  TStopwatch timer;

  // input
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* RecClusters = new TClonesArray("KoaRecCluster");
  tree->SetBranchAddress(brName_cluster, &RecClusters);
  
  // string definition
  TString hDirName = "rec_cluster_energy";

  TString hName = "cluster_energy";
  TString hTitle = "Cluster Energy;Energy(MeV)";
  TString h2Name = "cluster_hitmap";
  TString h2Title = "Cluster Energy HitMap;Channel Id;Energy(MeV)";

  if (!useMaxId) {
    hName.Append("_firstHit");
    hTitle.Prepend("(First hit id)");
    h2Name.Append("_firstHit");
    h2Title.Prepend("(First hit id)");
    hDirName.Append("_FirstHit");
  }

  hName.Append(Form("_%dhit", sizeCut));
  hTitle.Prepend(Form("%d Hits in Cluster", sizeCut));
  h2Name.Append(Form("_%dhit", sizeCut));
  h2Title.Prepend(Form("%d Hits in Cluster", sizeCut));
  hDirName.Append(Form("_%dhit", sizeCut));

  // histogram definition
  auto h1map = bookH1dByChannelId(hName.Data(), hTitle.Data(),
                                  amp_nbin, amp_low, amp_high,
                                  true, colorLine);
  auto h2map = bookH2dByRecDetectorId(h2Name.Data(),h2Title.Data(),
                                      amp_nbin, amp_low, amp_high);

  // event loop
  auto encoder = KoaMapEncoder::Instance();
  // double pedestal_threshold[4]={100, 100, 500, 1000}; // equivalent pedestal energy threshold
  double pedestal_threshold[4]={0, 0, 0, 0}; // equivalent pedestal energy threshold

  Long_t entries = tree->GetEntries();
  for(auto entry=0;entry<entries;entry++){
    tree->GetEntry(entry);

    Int_t clusters = RecClusters->GetEntriesFast();
    for (int i=0;i<clusters;i++){
      KoaRecCluster* cluster = (KoaRecCluster*)RecClusters->At(i);

      auto nr_digis = cluster->NumberOfDigis();
      if(nr_digis != sizeCut) {
        continue;
      }

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
      ch_id = encoder->DecodeChannelID(cluster_id, det_id);

      // fill
      auto cluster_e = cluster->Energy()/1000.;
      h1map[cluster_id].Fill(cluster_e);
      h2map[det_id].Fill(ch_id+1, cluster_e);
    }
  }
  std::cout << "Events processed : "<< entries << std::endl;

  // output
  TFile *fout = new TFile(outFileName, "update");

  TDirectory* hdir = nullptr;
  hdir = getDirectory(fout, hDirName.Data());
  writeHistos<TH1D>(hdir, h1map);
  writeHistos<TH2D>(hdir, h2map);

  TString pdfFileName = outFileName;
  pdfFileName.ReplaceAll(".root", Form("_%dhit.pdf", sizeCut));
  printH1Ds(h1map, pdfFileName.Data());

  //
  delete f;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}
