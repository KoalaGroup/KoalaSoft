#include "KoaCutList.h"

using namespace KoaUtility;

void checkSingleRecDigiWithFilter(const char* filename,  const char* treename,
                                  const char* sensorname, int sensorid,
                                  const char* brName_rec = "KoaRecDigi", const char* brName_fwd = "KoaFwdDigi",
                                  bool IsAdc = true,
                                  int amp_nbin = 4000, double amp_low = 0, double amp_high = 4000,
                                  int time_nbin = 1500, double time_low = 1400, double time_high = 1700
                                  )
{
  // timer
  TStopwatch timer;

  // input
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress(brName_rec, &RecDigis);
  TClonesArray* FwdDigis = new TClonesArray("KoaFwdDigi");
  tree->SetBranchAddress(brName_fwd, &FwdDigis);

  // histograms definition
  TH2D h2map_EnergyVsTime_cut("amplitude_vs_time_cut", "Amplitude VS Time (Coincidence Cut);Amplitude;Timestamp(ns)",
                              amp_nbin, amp_low, amp_high, time_nbin, time_low, time_high);

  // event list
  TString elistFileName(filename);
  elistFileName.ReplaceAll(".root","_EntryList.root");
  TFile *felist = new TFile(elistFileName.Data());

  auto eDir = getDirectory(felist, "fwd");
  auto fwdhit_elist = getObject<TEventList>(eDir, "elist_fwdhit");

  // Parameters used in event loop
  std::map<Int_t, Double_t> fwd_time;
  std::map<Int_t, Double_t> fwd_amp;
  Int_t fwd_low, fwd_high;

  auto encoder = KoaMapEncoder::Instance();
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);

  TString volName = TString("Sensor") + sensorname;
  Int_t rec_id = encoder->EncodeChannelID(volName.Data(), sensorid-1);

  // event loop
  Long_t entries = fwdhit_elist->GetN();
  for(auto entry=0;entry<entries;entry++){
    auto tree_index = fwdhit_elist->GetEntry(entry);
    tree->GetEntry(tree_index);

    // fwd digis
    Int_t fwddigis = FwdDigis->GetEntriesFast();
    for (int i=0;i<fwddigis;i++){
      KoaFwdDigi* digi = (KoaFwdDigi*)FwdDigis->At(i);
      auto id = digi->GetDetID();
      fwd_time[id] = digi->GetTimeStamp();
      fwd_amp[id]  = digi->GetCharge();
    }

    // check cut condition
    // rec digis
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      auto id = digi->GetDetID();
      if ( id != rec_id )
        continue;

      // rec enerty and timestamp
      auto rec_charge = digi->GetCharge(); // for ADC
      if ( !IsAdc ) rec_charge = rec_charge/100.;
      auto rec_timestamp = digi->GetTimeStamp();

      //
      h2map_EnergyVsTime_cut.Fill(rec_charge, rec_timestamp);
    }

    // clear up
    fwd_time.clear();
    fwd_amp.clear();
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  // output file
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(), "update");

  TDirectory* hdir = getDirectory(fout, Form("%s_%d", sensorname, sensorid));
  // hdir->WriteTObject(&h1map_time_cut, "", "Overwrite");
  hdir->WriteTObject(&h2map_EnergyVsTime_cut, "", "Overwrite");

  delete f;
  delete fout;

  delete fwdhit_elist;
  delete felist;

  // timer stat
  timer.Stop();
  timer.Print();
  
}
