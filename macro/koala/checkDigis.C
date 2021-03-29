#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"

using namespace KoaUtility;

void checkDigi(const char* filename,
               const char* branchName = "KoaRecDigi",
               const char* geoFile = "geo_standard.root")
{
  auto fin = TFile::Open(filename);
  TTree* tin; fin->GetObject("koalasim", tin);

  auto recDigis = new TClonesArray("KoaRecDigi", 200);
  tin->SetBranchAddress(branchName, &recDigis);

  //
  double zoffset[4] = {0.}; // in cm
  double yoffset[4] = {0, 0, 0, 0}; // in cm
  auto Positions = getStripGlobalPosition(geoFile, zoffset);
  auto Alphas = getStripAlphas(geoFile, yoffset, zoffset);

  //
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  auto first_id = encoder->EncodeChannelID(0,0);
  auto last_id = encoder->EncodeChannelID(3,31);
  int nbin = (Positions[last_id] - Positions[first_id])/0.12;
  auto h2map = new TH2D("EvsZ","Energy vs Z;mm;MeV",
                        nbin+1, Positions[first_id]*10-0.6, Positions[last_id]*10+0.6,
                        7100, -1, 70);

  //
  auto entries = tin->GetEntries();
  std::cout<< "Entries: " << entries << std::endl;
  for(auto entry=0; entry < entries; entry++) {
    tin->GetEntry(entry);

    auto digis = recDigis->GetEntries();
    for(int pt=0; pt < digis; pt++) {
      KoaRecDigi* digi= static_cast<KoaRecDigi*>(recDigis->At(pt));

      auto id = digi->GetDetID();
      h2map->Fill(Positions[id]*10, digi->GetCharge()/1000.);
    }
  }

  h2map->Draw("colz");
}
