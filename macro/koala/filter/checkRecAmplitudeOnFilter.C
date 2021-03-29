#include "KoaCutList.h"
#include "KoaHistUtility.h"

using namespace KoaUtility;

void checkRecAmplitudeOnFilter(const char* filename,  const char* treename,
                               const char* elistFileName, const char* edirName = "fwd", const char* elistName = "elist_fwdhit",
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
  TString hname = "energy_cut";
  TString htitle = "Energy (Coincidence Cut);Energy(MeV)";
  if (IsAdc) {
    hname = "adc_cut";
    htitle = "Amplitude (Coincidence Cut);ADC counts";
  }

  auto h1map_energy_cut = bookH1dByRecTdcChannelId(hname.Data(), htitle.Data(),
                                                   amp_nbin, amp_low, amp_high, kBlue);

  // event list
  TFile *felist = new TFile(elistFileName);
  auto eDir = getDirectory(felist, edirName);
  auto fwdhit_elist = getObject<TEventList>(eDir, elistName);

  // event loop
  Long_t entries = fwdhit_elist->GetN();
  for(auto entry=0;entry<entries;entry++){
    auto tree_index = fwdhit_elist->GetEntry(entry);
    tree->GetEntry(tree_index);

    // check cut condition
    // rec digis
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      auto id = digi->GetDetID();

      if ( h1map_energy_cut.find(id) == h1map_energy_cut.end() )
        continue;

      // rec enerty and timestamp
      auto rec_charge = digi->GetCharge(); // for ADC
      if ( !IsAdc ) rec_charge = rec_charge/1000.;

      //
      h1map_energy_cut[id].Fill(rec_charge);
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
    hdir = getDirectory(fout, Form("rec_adc_%s", fwdhit_elist->GetName()));
  else
    hdir = getDirectory(fout, Form("rec_energy_%s", fwdhit_elist->GetName()));
  writeHistos(hdir, h1map_energy_cut);

  delete f;
  delete fout;

  delete fwdhit_elist;
  delete felist;

  // timer stat
  timer.Stop();
  timer.Print();
}
