#include "KoaHistUtility.h"

using namespace KoaUtility;

void drawClusterEnergyWithTofE(const char* filename,
                               const char* outFileName,
                               const char* treename,
                               const char* brName_cluster,
                               const char* fwdhitFileName, const char* fwdhitTreeName = "fwdhit_time",
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
  
  TFile* ftime = new TFile(fwdhitFileName);
  TTree* tree_time = (TTree*)ftime->Get(fwdhitTreeName);
  Float_t fwdhit_timestamp;
  tree_time->SetBranchAddress(fwdhitTreeName,&fwdhit_timestamp);

  tree->AddFriend(tree_time);

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

  hName.Append("_TofE");
  hTitle.Prepend("(TOF-E cut)");
  h2Name.Append("_TofE");
  h2Title.Prepend("(TOF-E cut)");
  hDirName.Append("_TofE");

  // range function
  auto flow = new TF1("flow", "[0]+[1]/TMath::Sqrt(x+[2])", 0, 7);
  flow->SetParameters(445, 73.61, 0.5);
  auto fhigh = new TF1("fhigh", "[0]+[1]/TMath::Sqrt(x+[2])", 0.05, 7);
  fhigh->SetParameters(468, 73.61, -0.05);

  // histogram definition
  auto h1map = bookH1dByChannelId(hName.Data(), hTitle.Data(),
                                  amp_nbin, amp_low, amp_high,
                                  true, colorLine);
  auto h2map = bookH2dByRecDetectorId(h2Name.Data(),h2Title.Data(),
                                      amp_nbin, amp_low, amp_high);

  // event loop
  auto encoder = KoaMapEncoder::Instance();
  Long_t entries = tree->GetEntries();
  for(auto entry=0;entry<entries;entry++){
    tree->GetEntry(entry);

    //
    if (fwdhit_timestamp > 0) {
      Int_t clusters = RecClusters->GetEntriesFast();

      for (int i=0;i<clusters;i++){
        KoaRecCluster* cluster = (KoaRecCluster*)RecClusters->At(i);

        auto cluster_e = cluster->Energy()/1000.;
        auto cluster_t = cluster->Time();

        if(cluster_t < 0 || cluster_e < 0.05)
          continue;

        auto tof = cluster_t - fwdhit_timestamp;
        auto tof_low = flow->Eval(cluster_e);
        auto tof_high = fhigh->Eval(cluster_e);

        if(tof < tof_low || tof > tof_high)
          continue;

        //
        int cluster_id, det_id, ch_id;
        if (useMaxId) {
          cluster_id = cluster->GetMaximaChId();
        }
        else{
          det_id = cluster->GetDetId();
          cluster_id = cluster->GetFirstChId();
        }
        ch_id = encoder->DecodeChannelID(cluster_id, det_id);

        // fill
        h1map[cluster_id].Fill(cluster_e);
        h2map[det_id].Fill(ch_id+1, cluster_e);
      }
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
  pdfFileName.ReplaceAll(".root", "_TofE.pdf");
  printH1Ds(h1map, pdfFileName.Data());

  //
  delete flow, fhigh;
  delete f;
  delete ftime;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}
