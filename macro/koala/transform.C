#include "KoaHistUtility.h"

using namespace KoaUtility;

void transform(const char* filename)
{
  // setup color scheme
  TH1::AddDirectory(false);

  auto file = TFile::Open(filename);
  TDirectory *hdir = file->GetDirectory("histograms");
  //
  auto encoder = KoaMapEncoder::Instance();
  auto RecChIDs = encoder->GetRecChIDs();
  auto RecTdcChIDs = encoder->GetRecTdcChIDs();

  auto getHist = [&] (std::string prefix, std::vector<Int_t> ChIDs) -> std::vector<TH1D*>
                 {
                   std::vector<TH1D*> histograms;
                   TH1D* hist = nullptr;
                   for(auto& id: ChIDs){
                     TString volName; Int_t ch_id = encoder->DecodeChannelID(id, volName);
                     TString hname(Form("h1_%s_%s_%d", prefix.data(), volName.Data(), ch_id+1));
                     hdir->GetObject(hname, hist);
                     if ( !hist ) {
                       std::cerr << "Error: no histogram " << hname << std::endl;
                     }

                     // rename
                     volName.ReplaceAll("Sensor", "");
                     hist->SetName(Form("h1_%s_%s_%d", volName.Data(), prefix.data(), ch_id + 1));
                     histograms.emplace_back(hist);
                   }

                   return histograms;
                 };

  std::vector<TH1D*> histo_energy = getHist("energy", RecChIDs);
  std::vector<TH1D*> histo_cut = getHist("energy_cut", RecTdcChIDs);
  std::vector<TH1D*> histo_tof = getHist("energy_tof", RecTdcChIDs);

  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_old.root");
  TFile *fout = new TFile(outfilename.Data(),"recreate");
  TDirectory *houtdir = getDirectory(fout, "energy_spectrum");
  for(auto& hist : histo_energy) {
    houtdir->WriteTObject(hist, "", "Overwrite");
  }
  for(auto& hist : histo_tof) {
    houtdir->WriteTObject(hist, "", "Overwrite");
  }
  for(auto& hist : histo_cut) {
    houtdir->WriteTObject(hist, "", "Overwrite");
  }

  //
  delete file;
  delete fout;
}
