#include "KoaCutList.h"
#include "KoaHistUtility.h"

using namespace KoaUtility;

void checkRecTimeOnFilter(const char* filename,  const char* treename,
                          const char* elistFileName, const char* edirName = "fwd", const char* elistName = "elist_fwdhit",
                          const char* brName_rec = "KoaRecDigi", //const char* brName_fwd = "KoaFwdDigi",
                          // bool IsAdc = true,
                          // int amp_nbin = 4000, double amp_low = 0, double amp_high = 4000,
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
  // TClonesArray* FwdDigis = new TClonesArray("KoaFwdDigi");
  // tree->SetBranchAddress(brName_fwd, &FwdDigis);

  // histograms definition
  auto h1map_time_cut = bookH1dByRecTdcChannelId("time_cut", "Timestamp (Coincidence Cut);Timestamp(ns)",
                                                 time_nbin, time_low, time_high, kBlue);
  // auto h2map_EnergyVsTime_cut = bookH2dByRecTdcChannelId("amplitude_vs_time_cut",
  //                                                        "Amplitude VS Timestamp (Coincidence Cut);Amplitude;Timestamp(ns)",
  //                                                        amp_nbin, amp_low, amp_high, time_nbin, time_low, time_high);

  // event list
  TFile *felist = new TFile(elistFileName);
  auto eDir = getDirectory(felist, edirName);
  auto fwdhit_elist = getObject<TEventList>(eDir, elistName);

  // Parameters used in event loop
  // double fwd_time[2], fwd_amp[2];

  // Int_t fwd_low, fwd_high;
  // auto encoder = KoaMapEncoder::Instance();
  // encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  // Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  // Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);

  // event loop
  Long_t entries = fwdhit_elist->GetN();
  for(auto entry=0;entry<entries;entry++){
    auto tree_index = fwdhit_elist->GetEntry(entry);
    tree->GetEntry(tree_index);

    // fwd digis
    // Int_t fwddigis = FwdDigis->GetEntriesFast();
    // for (int i=0;i<fwddigis;i++){
    //   KoaFwdDigi* digi = (KoaFwdDigi*)FwdDigis->At(i);
    //   auto id = digi->GetDetID();
    //   switch (id) {
    //     case index0:
    //       {
    //         fwd_time[0] = digi->GetTimeStamp();
    //         fwd_amp[0]  = digi->GetCharge();
    //       }
    //     case index1:
    //       {
    //         fwd_time[1] = digi->GetTimeStamp();
    //         fwd_amp[1]  = digi->GetCharge();
    //         break;
    //       }
    //     default:
    //       break;
    //   }
    // }

    // check cut condition
    // rec digis
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      auto id = digi->GetDetID();

      if ( h1map_time_cut.find(id) == h1map_time_cut.end() )
        continue;

      // rec enerty and timestamp
      // auto rec_charge = digi->GetCharge(); // for ADC
      // if ( !IsAdc ) rec_charge = rec_charge/100.;
      auto rec_timestamp = digi->GetTimeStamp();

      //
      h1map_time_cut[id].Fill(rec_timestamp);
      // h2map_EnergyVsTime_cut[id].Fill(rec_charge, rec_timestamp);
    }
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  // output file
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(), "update");

  TDirectory* hdir = getDirectory(fout, Form("rec_time_%s", fwdhit_elist->GetName()));
  writeHistos(hdir, h1map_time_cut);
  // writeHistos(hdir, h2map_EnergyVsTime_cut);

  delete f;
  delete fout;

  delete fwdhit_elist;
  delete felist;

  // timer stat
  timer.Stop();
  timer.Print();
}
