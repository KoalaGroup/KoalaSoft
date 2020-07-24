#include "KoaCutList.h"
#include "KoaHistUtility.h"

using namespace KoaUtility;

void checkRecAmplitude(const char* filename,  const char* treename,
                       const char* brName_rec = "KoaRecDigi",
                       bool IsAdc = false,
                       int amp_nbin = 7000, double amp_low = 0, double amp_high = 70
                       )
{
  // timer
  TStopwatch timer;

  // input
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress(brName_rec, &RecDigis);

  // histograms definition
  TString hname = "energy";
  TString htitle = "Energy;Energy(MeV)";
  if (IsAdc) {
    hname = "adc";
    htitle = "Amplitude;ADC counts";
  }

  auto h1map_energy = bookH1dByRecTdcChannelId(hname.Data(), htitle.Data(),
                                               amp_nbin, amp_low, amp_high, kBlack);

  // event loop
  Long_t entries = tree->GetEntriesFast();
  for(auto entry=0;entry<entries;entry++){
    tree->GetEntry(entry);

    // check cut condition
    // rec digis
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      auto id = digi->GetDetID();

      if ( h1map_energy.find(id) == h1map_energy.end() )
        continue;

      // rec enerty and timestamp
      auto rec_charge = digi->GetCharge(); // for ADC
      if ( !IsAdc ) rec_charge = rec_charge/1000.;

      //
      h1map_energy[id].Fill(rec_charge);
    }
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  // output file
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(), "update");

  TDirectory* hdir = nullptr;
  if (IsAdc)
    hdir = getDirectory(fout, "rec_adc");
  else
    hdir = getDirectory(fout, "rec_energy");
  writeHistos(hdir, h1map_energy);

  delete f;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}
