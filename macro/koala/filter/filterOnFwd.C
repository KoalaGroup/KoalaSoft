#include "KoaCutList.h"
#include "KoaCutObject.h"

using namespace KoaUtility;

/*
 | Summary:
 | -------
 | Categorize events into different event lists based on fwd infos and save into file for later usage.
 | A special list called "elist_fwdhit" is also generated to contain events which have fwd hit.
 | In the same time, compute the hit timestamp of the forward detector into a new tree.
 | Two output file will be generated:
 | 1) "xxxxx_EntryList.root" : the file storing the entry lists like 'fwd/elist_fwdhit' ...
 | 2) "xxxxx_FwdHit.root"    : the file storing the fwd hit timestamp
 |
 | Arguments:
 | ---------
 | *) filename : input root file name, should be the raw digi files after unpacking
 | *) treeName   : input tree name
 | *) brName_fwd : name the fwd digi branch
 | *) fwd1_tlow, fwd1_thigh, fwd2_tlow, fwd2_thigh, window_tlow, window_thigh: fwd time cut condition
 | *) fwd1_alow, fwd1_ahigh, fwd2_alow, fwd2_ahigh : fwd amplitude cut condition
 |
 */
void filterOnFwd(const char* filename,
                 const char* treename = "koalasim",
                 const char* brName_fwd = "KoaFwdDigi",
                 int fwd1_tlow=915, int fwd1_thigh = 930,
                 int fwd2_tlow=915, int fwd2_thigh = 930,
                 double window_tlow = -10, double window_thigh = 10,
                 int fwd1_alow=790, int fwd1_ahigh = 1050,
                 int fwd2_alow=780, int fwd2_ahigh = 1030
                 )
{
  // timer
  TStopwatch timer;

  // input
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* FwdDigis = new TClonesArray("KoaFwdDigi");
  tree->SetBranchAddress(brName_fwd, &FwdDigis);

  // fwdhit time tree and out file
  TString outFwdHitFileName(filename);
  outFwdHitFileName.ReplaceAll(".root","_FwdHit.root");
  TFile *foutFwdHit = new TFile(outFwdHitFileName.Data(),"update");

  float fwdhit_timestamp;
  TTree* treeHitTime = new TTree("fwdhit_time","Timestamp of forward hit");
  treeHitTime->Branch("fwdhit_time", &fwdhit_timestamp);

  // entry list definition
  auto amp_elists = bookEListByRegionType(true);
  auto time_elists = bookEListByRegionType(false);

  // fwd hit conditions
  std::vector<RegionType> amp_hit_condition = {RegionType::FwdAmpMain, RegionType::FwdAmpLow1, RegionType::FwdAmpLow2, RegionType::FwdAmpLow};
  TList amp_hit_collection;
  for(auto e : amp_hit_condition) {
    auto id = static_cast<int>(e);
    amp_hit_collection.Add(&amp_elists[id]);
  }

  std::vector<RegionType> time_hit_condition = {RegionType::FwdTimeMain, RegionType::FwdTimeBand1, RegionType::FwdTimeBand2, RegionType::FwdTimeBand3};
  TList time_hit_collection;
  for(auto e : time_hit_condition) {
    auto id = static_cast<int>(e);
    time_hit_collection.Add(&time_elists[id]);
  }

  // cut object
  KoaFwdTimeCut time_cut(fwd1_tlow, fwd1_thigh, fwd2_tlow, fwd2_thigh, window_tlow, window_thigh);
  KoaFwdAmpCut amp_cut(fwd1_alow, fwd1_ahigh, fwd2_alow, fwd2_ahigh);

  // other variables
  Int_t fwd_low, fwd_high;
  auto encoder = KoaMapEncoder::Instance();
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);

  std::map<Int_t, Double_t> fwd_time;
  std::map<Int_t, Double_t> fwd_amp;

  // event loop
  Long_t entries = tree->GetEntries();
  for(auto entry=0;entry<entries;entry++){
    tree->GetEntry(entry);

    // fwd digis
    Int_t fwddigis = FwdDigis->GetEntriesFast();
    for (int i=0;i<fwddigis;i++){
      KoaFwdDigi* digi = (KoaFwdDigi*)FwdDigis->At(i);
      auto id = digi->GetDetID();
      fwd_time[id] = digi->GetTimeStamp();
      fwd_amp[id]  = digi->GetCharge();
    }

    // enter entry into entry list
    auto amp_id = static_cast<int>(amp_cut.GetType(fwd_amp[index0],fwd_amp[index1]));
    amp_elists[amp_id].Enter(entry);

    auto time_id = static_cast<int>(time_cut.GetType(fwd_time[index0],fwd_time[index1]));
    time_elists[time_id].Enter(entry);

    // calculate fwd hit time
    switch (static_cast<RegionType>(time_id)) {
      case RegionType::FwdTimeBand3:
      case RegionType::FwdTimeMain: {
        fwdhit_timestamp = (fwd_time[index0] + fwd_time[index1])/2.;
        break;
      }
      case RegionType::FwdTimeBand1: {
        fwdhit_timestamp = fwd_time[index0];
        break;
      }
      case RegionType::FwdTimeBand2: {
        fwdhit_timestamp = fwd_time[index1];
        break;
      }
      default:
        fwdhit_timestamp = -10;
        break;
    }
    treeHitTime->Fill();

    // clear up
    fwd_time.clear();
    fwd_amp.clear();
  }
  cout << "EventNr processed : "<< entries << endl;

  // compose fwd hit event list
  TEventList amp_hit_elist;
  amp_hit_elist.Merge(&amp_hit_collection);
  TEventList time_hit_elist;
  time_hit_elist.Merge(&time_hit_collection);

  auto fwdhit_elist = amp_hit_elist * time_hit_elist;
  fwdhit_elist.SetName("elist_fwdhit");
  fwdhit_elist.SetTitle("List of events with forward detector hit");

  // output file
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","");
  outfilename.Append("_EntryList.root");
  TFile *fout = new TFile(outfilename.Data(),"update");

  TDirectory* edir = getDirectory(fout, "fwd");
  writeElists(edir,amp_elists,"Overwrite");
  writeElists(edir,time_elists,"Overwrite");
  edir->WriteTObject(&fwdhit_elist, "", "Overwrite");

  // save the fwdhit time tree
  foutFwdHit->WriteTObject(treeHitTime, "", "Overwrite");

  //
  delete f;
  delete fout;
  delete foutFwdHit;

  // timer stat
  timer.Stop();
  timer.Print();
}
