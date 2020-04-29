#include "KoaHistUtility.h"
#include "KoaCutList.h"
#include "KoaCutObject.h"

using namespace KoaUtility;

void checkRecDigiTof(const char* filename,   const char* treename,
                     const char* brName_rec = "KoaRecDigi", const char* brName_fwd = "KoaFwdDigi",
                     int fwd1_low=915, int fwd1_high = 930,
                     int fwd2_low=915, int fwd2_high = 930,
                     double window_low = -10, double window_high = 10)
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
  Int_t nbinx=200;
  Float_t xlow=0,xhigh=8; // in MeV

  Int_t nbiny=3750;
  Float_t ylow=0,yhigh=750; // in ns

  TH2D h2("h2_TofVsE","TOF VS Energy;E (MeV);TOF (ns)", nbinx, xlow, xhigh, nbiny, ylow, yhigh);
  auto h1map_tof = bookH1dByRecTdcChannelId("tof", "Time of flight;ns", nbiny, ylow, yhigh);
  auto h2map_TofVsEnergy = bookH2dByRecTdcChannelId("TofVsEnergy", "TOF Vs Energy;E (MeV);TOF (ns)", nbinx, xlow, xhigh, nbiny, ylow, yhigh);

  // time-cut object
  KoaFwdTimeCut time_cut(fwd1_low, fwd1_high, fwd2_low, fwd2_high, window_low, window_high);

  // Parameters used in event loop
  Int_t det_id, ch_id, id;
  Double_t rec_charge;
  Double_t rec_timestamp, tof;
  Double_t fwd_timestamp;

  std::map<Int_t, Double_t> fwd_time;
  std::map<Int_t, Double_t> fwd_amp;
  Int_t fwd_low, fwd_high;

  auto encoder = KoaMapEncoder::Instance();
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);

  // event loop
  Long_t entries = tree->GetEntries();
  for(auto entry=0;entry<entries;entry++){
    auto entrynum = tree->GetEntryNumber(entry);
    tree->GetEntry(entrynum);

    // fwd digis
    Int_t fwddigis = FwdDigis->GetEntriesFast();
    for (int i=0;i<fwddigis;i++){
      KoaFwdDigi* digi = (KoaFwdDigi*)FwdDigis->At(i);
      id = digi->GetDetID();
      fwd_time[id] = digi->GetTimeStamp();
      fwd_amp[id]  = digi->GetCharge();
    }

    // check conditions
    bool passed = false;
    switch (time_cut.GetType(fwd_time[index0], fwd_time[index1])) {
      case RegionType::FwdTimeBand3:
      case RegionType::FwdTimeMain: {
        fwd_timestamp = (fwd_time[index0] + fwd_time[index1])/2.;
        passed = true;
        break;
      }
      case RegionType::FwdTimeBand1: {
        fwd_timestamp = fwd_time[index0];
        passed = true;
        break;
      }
      case RegionType::FwdTimeBand2: {
        fwd_timestamp = fwd_time[index1];
        passed = true;
        break;
      }
      default:
        break;
    }

    //
    if ( passed ) {
      Int_t digis=RecDigis->GetEntriesFast();
      for(int i=0;i<digis;i++){
        // rec digis
        KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
        id = digi->GetDetID();
        ch_id = encoder->DecodeChannelID(id, det_id);

        // timestamp
        rec_charge = digi->GetCharge()/1000.; // in MeV
        rec_timestamp = digi->GetTimeStamp();

      //
        auto search = h1map_tof.find(id);
        if( search != h1map_tof.end()) {
          if ( rec_timestamp > 0 ) {
            tof = rec_timestamp - fwd_timestamp;

            h1map_tof[id].Fill(tof);
            h2map_TofVsEnergy[id].Fill(rec_charge, tof);
            h2.Fill(rec_charge, tof);
          }
        }
      }
    }

    fwd_time.clear();
    fwd_amp.clear();
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  // output file
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(),"update");

  TDirectory* hdir = getDirectory(fout, "tof_spectrum");
  hdir->WriteTObject(&h2, "", "Overwrite");
  writeHistos(hdir, h1map_tof);
  writeHistos(hdir, h2map_TofVsEnergy);

  //
  delete f;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}

void  checkRecDigiTofWithFwdAmplitudeCut(const char* filename,   const char* treename,
                                         const char* brName_rec = "KoaRecDigi", const char* brName_fwd = "KoaFwdDigi",
                                         int fwd1_tlow=915, int fwd1_thigh = 930,
                                         int fwd2_tlow=915, int fwd2_thigh = 930,
                                         double window_tlow = -10, double window_thigh = 10,
                                         int fwd1_alow=790, int fwd1_ahigh = 1050,
                                         int fwd2_alow=780, int fwd2_ahigh = 1030)
{
  // timer
  TStopwatch timer;

  // input
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress("KoaRecDigi",&RecDigis);
  TClonesArray* FwdDigis = new TClonesArray("KoaFwdDigi");
  tree->SetBranchAddress("KoaFwdDigi",&FwdDigis);

  // parameters
  Int_t nbinx=200;
  Float_t xlow=0,xhigh=8;

  Int_t nbiny=3750;
  Float_t ylow=0,yhigh=750;

  // histograms definition
  TH2D h2("h2_TofVsE","TOF VS Energy;MeV;ns", nbinx, xlow, xhigh, nbiny, ylow, yhigh);
  auto h1map_tof = bookH1dByRecTdcChannelId("tof", "Time of flight;ns", nbiny, ylow, yhigh);
  auto h2map_TofVsEnergy = bookH2dByRecTdcChannelId("TofVsEnergy", "TOF Vs Energy;MeV;ns", nbinx, xlow, xhigh, nbiny, ylow, yhigh);

  // cut objects
  KoaFwdTimeCut time_cut(fwd1_tlow, fwd1_thigh, fwd2_tlow, fwd2_thigh, window_tlow, window_thigh);
  KoaFwdAmpCut amp_cut(fwd1_alow, fwd1_ahigh, fwd2_alow, fwd2_ahigh);

  std::vector<RegionType> cut_condition = {RegionType::FwdAmpMain, RegionType::FwdAmpLow1, RegionType::FwdAmpLow2, RegionType::FwdAmpLow};

  auto IfCut = [&] (RegionType  region) -> bool
               {
                 if ( std::find(cut_condition.begin(), cut_condition.end(), region) != cut_condition.end() )
                   return true;
                 return false;
               };

  // event loop
  Int_t det_id, ch_id, id;
  Double_t rec_charge;
  Double_t rec_timestamp, tof;
  Double_t fwd_timestamp;

  std::map<Int_t, Double_t> fwd_time;
  std::map<Int_t, Double_t> fwd_amp;
  Int_t fwd_low, fwd_high;

  auto encoder = KoaMapEncoder::Instance();
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);

  //
  Long_t entries;
  entries = tree->GetEntries();
  for(auto entry=0;entry<entries;entry++){
    tree->GetEntry(entry);

    // fwd digis
    Int_t fwddigis = FwdDigis->GetEntriesFast();
    for (int i=0;i<fwddigis;i++){
      KoaFwdDigi* digi = (KoaFwdDigi*)FwdDigis->At(i);
      id = digi->GetDetID();
      fwd_time[id] = digi->GetTimeStamp();
      fwd_amp[id]  = digi->GetCharge();
    }

    // check conditions
    auto passed = IfCut(amp_cut.GetType(fwd_amp[index0], fwd_amp[index1]));
    if (passed) {
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
    }

    //
    if (passed) {
      Int_t digis=RecDigis->GetEntriesFast();
      for(int i=0;i<digis;i++){
        // rec digis
        KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
        id = digi->GetDetID();
        ch_id = encoder->DecodeChannelID(id, det_id);

        // timestamp
        rec_charge = digi->GetCharge()/1000.; // in MeV
        rec_timestamp = digi->GetTimeStamp();

        //
        auto search = h1map_tof.find(id);
        if( search != h1map_tof.end()) {
          if ( rec_timestamp > 0 ) {
            tof = rec_timestamp - fwd_timestamp;

            h1map_tof[id].Fill(tof);
            h2map_TofVsEnergy[id].Fill(rec_charge, tof);
            h2.Fill(rec_charge, tof);
          }
        }
      }
    }

    fwd_time.clear();
    fwd_amp.clear();
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  // output file
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(),"update");

  TDirectory* hdir = getDirectory(fout, "tof_spectrum_withFwdAmplitudeCut");
  hdir->WriteTObject(&h2, "", "Overwrite");
  writeHistos(hdir, h1map_tof);
  writeHistos(hdir, h2map_TofVsEnergy);

  //
  delete f;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
  
}
