#include "KoaCutList.h"
#include "KoaHistUtility.h"

using namespace KoaUtility;

void checkAmpVsTof(const char* filename,  const char* treename,
                   const char* elistFileName, const char* edirName = "fwd", const char* elistName = "elist_fwdhit",
                   const char* brName_rec = "KoaRecDigi", const char* brName_fwd = "KoaFwdDigi",
                   bool IsAdc = false,
                   int amp_nbin = 100, double amp_low = 0, double amp_high = 10,
                   int time_nbin = 1500, double time_low = 400, double time_high = 700
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
  TString hname = "energy_vs_tof_cut";
  TString htitle = "Energy VS TOF (Coincidence Cut);Energy(MeV);TOF(ns)";
  if (IsAdc) {
    hname = "amplitude_vs_tof_cut";
    htitle = "Amplitude VS TOF (Coincidence Cut);ADC counts;TOF(ns)";
  }
  auto h2map_EnergyVsTime_cut = bookH2dByRecTdcChannelId(hname.Data(),
                                                         htitle.Data(),
                                                         amp_nbin, amp_low, amp_high, time_nbin, time_low, time_high);

  // event list
  TFile *felist = new TFile(elistFileName);
  auto eDir = getDirectory(felist, edirName);
  auto fwdhit_elist = getObject<TEventList>(eDir, elistName);

  // Parameters used in event loop
  std::map<Int_t, Double_t> fwd_time;
  std::map<Int_t, Double_t> fwd_amp;
  double fwd_timestamp;

  Int_t fwd_low, fwd_high;
  auto encoder = KoaMapEncoder::Instance();
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);

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

    // calculate fwd hit time
    switch (time_cut.GetType(fwd_time[index0], fwd_time[index1])) {
      case RegionType::FwdTimeBand3:
      case RegionType::FwdTimeMain: {
        fwd_timestamp = (fwd_time[index0] + fwd_time[index1])/2.;
        break;
      }
      case RegionType::FwdTimeBand1: {
        fwd_timestamp = fwd_time[index0];
        break;
      }
      case RegionType::FwdTimeBand2: {
        fwd_timestamp = fwd_time[index1];
        break;
      }
      default:
        passed = false;
        break;
    }

    // check cut condition
    // rec digis
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      auto id = digi->GetDetID();

      if ( h2map_EnergyVsTime_cut.find(id) == h2map_EnergyVsTime_cut.end() )
        continue;

      // rec enerty and timestamp
      auto rec_charge = digi->GetCharge(); // for ADC
      if ( !IsAdc ) rec_charge = rec_charge/100.;
      auto rec_timestamp = digi->GetTimeStamp();

      //
      if (rec_timestamp > 0)
        h2map_EnergyVsTime_cut[id].Fill(rec_charge, rec_timestamp-fwd_timestamp);
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
    hdir = getDirectory(fout, Form("adc_vs_tof_%s", fwdhit_elist->GetName()));
  else
    hdir = getDirectory(fout, Form("energy_vs_tof_%s", fwdhit_elist->GetName()));
  writeHistos(hdir, h2map_EnergyVsTime_cut);

  delete f;
  delete fout;

  delete fwdhit_elist;
  delete felist;

  // timer stat
  timer.Stop();
  timer.Print();
}
