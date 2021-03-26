#include "KoaCutList.h"
#include "KoaHistUtility.h"

using namespace KoaUtility;

void checkAmpVsTof(const char* filename,
                   const char* treename,
                   const char* brName_rec,
                   const char* fwdhitFileName,
                   int amp_nbin = 100, double amp_low = 0, double amp_high = 10,
                   int time_nbin = 1500, double time_low = 400, double time_high = 700,
                   const char* elistFileName = nullptr, const char* edirName = "fwd", const char* elistName = "elist_fwdhit"
                   )
{
  // timer
  TStopwatch timer;

  // input
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress(brName_rec, &RecDigis);

  TFile* ftime = new TFile(fwdhitFileName);
  TTree* tree_time = (TTree*)ftime->Get("fwdhit_time");
  Float_t fwdhit_timestamp;
  tree_time->SetBranchAddress("fwdhit_time",&fwdhit_timestamp);

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

  // histograms definition
  TString hDirName = "digi_energy_vs_tof";
  TString hname = "energy_vs_tof";
  TString htitle = "Digi Energy VS TOF;Energy(MeV);TOF(ns)";
  bool IsAdc = false;
  if(amp_high > 100) IsAdc=true;

  if (IsAdc) {
    hDirName = "digi_amplitude_vs_tof";
    hname = "amplitude_vs_tof";
    htitle = "Digi Amplitude VS TOF;ADC counts;TOF(ns)";
  }

  TString eListName = elistName;
  eListName.ReplaceAll("elist_","");
  if (elistFileName) {
    hname.Append(Form("_%s",eListName.Data()));
    htitle.Prepend(Form("(%s cut) ", eListName.Data()));
    hDirName.Append(Form("_%s",eListName.Data()));
  }
  auto h2map = bookH2dByRecTdcChannelId(hname.Data(),
                                        htitle.Data(),
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

    if (fwdhit_timestamp > 0) {
      // rec digis
      Int_t digis=RecDigis->GetEntriesFast();
      for(int i=0;i<digis;i++){
        KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
        auto id = digi->GetDetID();

        if ( h2map.find(id) == h2map.end() )
          continue;

        // rec enerty and timestamp
        auto rec_charge = digi->GetCharge(); // for ADC
        if ( !IsAdc ) rec_charge = rec_charge/100.;
        auto rec_timestamp = digi->GetTimeStamp();

        //
        if (rec_timestamp > 0)
          h2map[id].Fill(rec_charge, rec_timestamp-fwdhit_timestamp);
      }
    }
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  // output file
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(), "update");

  TDirectory* hdir = nullptr;
  hdir = getDirectory(fout, hDirName.Data());
  writeHistos(hdir, h2map);

  delete f;
  delete ftime;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}
