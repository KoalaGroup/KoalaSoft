#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"

using namespace KoaUtility;

void checkClusters(const char* filename,
                   const char* branchName = "KoaRecCluster",
                   const char* geoFile = "geo_standard.root",
                   bool useThreshold =false
                   )
{
  auto fin = TFile::Open(filename);
  TTree* tin; fin->GetObject("koalasim", tin);

  auto recClusters = new TClonesArray("KoaRecCluster", 200);
  tin->SetBranchAddress(branchName, &recClusters);

  //
  double zoffset[4] = {0.}; // in cm
  double yoffset[4] = {0, 0, 0, 0}; // in cm
  auto Positions = getStripGlobalPosition(geoFile, zoffset);
  auto Alphas = getStripAlphas(geoFile, yoffset, zoffset);

  double pedestal_threshold[4]={100, 100, 500, 1000}; // equivalent pedestal energy threshold

  //
  auto h2map = new TH2D("EvsZ","Energy vs Z;mm;MeV",
                        260, -10, 250,
                        7100, -1, 70);

  //
  auto entries = tin->GetEntries();
  std::cout<< "Entries: " << entries << std::endl;
  for(auto entry=0; entry < entries; entry++) {
    tin->GetEntry(entry);

    int cluster_id, det_id;
    double cluster_e;

    auto clusters = recClusters->GetEntries();
    for(int pt=0; pt < clusters; pt++) {
      KoaRecCluster* cluster= static_cast<KoaRecCluster*>(recClusters->At(pt));
      det_id = cluster->GetDetId();

      if(useThreshold) {
        cluster->SetThreshold(pedestal_threshold[det_id]);
      }
      cluster_id = cluster->GetFirstChIdAboveThresh();
      cluster_e = cluster->Energy()/1000.;

      h2map->Fill(Positions[cluster_id]*10, cluster_e);
    }
  }

  h2map->Draw("colz");
}
