#include "KoaHistUtility.h"
#include "KoaCutList.h"
#include "KoaCutObject.h"

using namespace KoaUtility;

void checkRecDigiTime(const char* filename,  const char* treename,
                      const char* brName_rec = "KoaRecDigi", const char* brName_fwd = "KoaFwdDigi",
                      int fwd1_tlow=915, int fwd1_thigh = 930,
                      int fwd2_tlow=915, int fwd2_thigh = 930,
                      double window_tlow = -10, double window_thigh = 10,
                      int fwd1_alow=790, int fwd1_ahigh = 1050,
                      int fwd2_alow=780, int fwd2_ahigh = 1030)
{
  // timer
  TStopwatch timer;

  // use koala color
  // init_KoaColors();

  // input
  TFile* f = new TFile(filename,"update");
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress(brName_rec, &RecDigis);
  TClonesArray* FwdDigis = new TClonesArray("KoaFwdDigi");
  tree->SetBranchAddress(brName_fwd, &FwdDigis);

  // histograms definition
  Int_t nbinx=10000;
  Float_t xlow=0,xhigh=2000;

  Int_t nbiny=2500;
  Float_t ylow=0,yhigh=2500; // in ns

  // hit flag in determined by the timestamp value of recoil strip
  auto h1map_multiHit = bookH1dByRecDetectorId("multiHit","Multi-Hits");
  auto h1map_multiHit_cut = bookH1dByRecDetectorId("multiHit_cut","Multi-Hits (Coincidence Cut)", kBlue);
  TH1D h1_multiHit("h1_multiHit", "Multi-Hits", 64, 0.5, 64.5);
  TH1D h1_multiHit_cut("h1_multiHit_cut", "Multi-Hits (Coincidence Cut)", 64, 0.5, 64.5);

  auto h1map_time = bookH1dByRecTdcChannelId("time","Timestamp",nbinx,xlow,xhigh);
  auto h1map_time_cut = bookH1dByRecTdcChannelId("time_cut","Timestamp (Coincidence Cut)",nbinx,xlow,xhigh, kBlue);
  // auto h2map_EnergyVsTime = bookH2dByRecTdcChannelId("energy_vs_time", "Energy VS Time (no cut);Energy(MeV);Timestamp(ns)", 90, 0 , 9, 5000, 800 ,1800);
  // auto h2map_EnergyVsTime_cut = bookH2dByRecTdcChannelId("energy_vs_time_cut", "Energy VS Time (no cut);Energy(MeV);Timestamp(ns)", 90, 0 ,9, 5000, 800 ,1800);
  // auto h2map_EnergyVsTime = bookH2dByRecTdcChannelId("energy_vs_time", "Energy VS Time (no cut);Energy(MeV);Timestamp(ns)", 90, 0 , 9, 3000, 0 ,300);
  // auto h2map_EnergyVsTime_cut = bookH2dByRecTdcChannelId("energy_vs_time_cut", "Energy VS Time (no cut);Energy(MeV);Timestamp(ns)", 90, 0 ,9, 3000, 0 ,300);
  auto h2map_EnergyVsTime = bookH2dByRecTdcChannelId("energy_vs_time", "Energy VS Time (no cut);Energy(MeV);Timestamp(ns)", 4000, 0 , 4000, 3000, 1100 ,1700);
  auto h2map_EnergyVsTime_cut = bookH2dByRecTdcChannelId("energy_vs_time_cut", "Energy VS Time (no cut);Energy(MeV);Timestamp(ns)", 4000, 0 ,4000, 1500, 1400 ,1700);

  // cut object
  KoaFwdTimeCut time_cut(fwd1_tlow, fwd1_thigh, fwd2_tlow, fwd2_thigh, window_tlow, window_thigh);
  KoaFwdAmpCut amp_cut(fwd1_alow, fwd1_ahigh, fwd2_alow, fwd2_ahigh);

  std::vector<RegionType> cut_condition = {RegionType::FwdTimeMain, RegionType::FwdTimeBand1, RegionType::FwdTimeBand2, RegionType::FwdTimeBand3, RegionType::FwdAmpMain, RegionType::FwdAmpLow1, RegionType::FwdAmpLow2, RegionType::FwdAmpLow};

  auto IfCut = [&] (RegionType  region) -> bool
               {
                 if ( std::find(cut_condition.begin(), cut_condition.end(), region) != cut_condition.end() )
                   return true;
                 return false;
               };

  // Parameters used in event loop
  Int_t det_id, ch_id, id;
  Double_t rec_charge;
  Double_t rec_timestamp;
  std::map<int, int> multiHits;
  int totalHits=0;

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
    tree->GetEntry(entry);

    // fwd digis
    Int_t fwddigis = FwdDigis->GetEntriesFast();
    for (int i=0;i<fwddigis;i++){
      KoaFwdDigi* digi = (KoaFwdDigi*)FwdDigis->At(i);
      id = digi->GetDetID();
      fwd_time[id] = digi->GetTimeStamp();
      fwd_amp[id]  = digi->GetCharge();
    }

    // check cut condition
    auto passed =  IfCut(time_cut.GetType(fwd_time[index0], fwd_time[index1]))
                   && IfCut(amp_cut.GetType(fwd_amp[index0], fwd_amp[index1]));

    // rec digis
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      id = digi->GetDetID();
      ch_id = encoder->DecodeChannelID(id, det_id);

      // rec enerty and timestamp
      // rec_charge = digi->GetCharge()/1000.; // in MeV
      rec_charge = digi->GetCharge(); // for ADC
      rec_timestamp = digi->GetTimeStamp();

      //
      if ( h1map_time.find(id) != h1map_time.end()
           && rec_timestamp > 0 ) {
        h1map_time[id].Fill(rec_timestamp);
        h2map_EnergyVsTime[id].Fill(rec_charge, rec_timestamp);
        if ( passed ) {
          h1map_time_cut[id].Fill(rec_timestamp);
          h2map_EnergyVsTime_cut[id].Fill(rec_charge, rec_timestamp);
        }

        multiHits[det_id]++;
      }
    }

    // fill multi hits
    for( auto hit: multiHits ) {
      h1map_multiHit[hit.first].Fill(hit.second);
      if (passed) {
        h1map_multiHit_cut[hit.first].Fill(hit.second);
      }

      totalHits += hit.second;
    }

    h1_multiHit.Fill(totalHits);
    if ( passed ) {
      h1_multiHit_cut.Fill(totalHits);
    }

    //
    totalHits = 0;
    multiHits.clear();
    fwd_time.clear();
    fwd_amp.clear();
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  // output file
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","");
  outfilename.Append("_result.root");
  TFile *fout = new TFile(outfilename.Data(),"update");

  TDirectory* hdir = getDirectory(fout, "rec_time");
  writeHistos(hdir, h1map_time);
  writeHistos(hdir, h1map_time_cut);
  writeHistos(hdir, h1map_multiHit);
  writeHistos(hdir, h1map_multiHit_cut);
  writeHistos(hdir, h2map_EnergyVsTime);
  writeHistos(hdir, h2map_EnergyVsTime_cut);
  hdir->WriteTObject(&h1_multiHit, "", "Overwrite");
  hdir->WriteTObject(&h1_multiHit_cut, "", "Overwrite");

  delete f;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}

void checkSingleRecDigiTime(const char* filename,  const char* treename, const char* sensorname, int sensorid,
                            const char* brName_rec = "KoaRecDigi", const char* brName_fwd = "KoaFwdDigi",
                            int fwd1_tlow=915, int fwd1_thigh = 930,
                            int fwd2_tlow=915, int fwd2_thigh = 930,
                            double window_tlow = -10, double window_thigh = 10,
                            int fwd1_alow=790, int fwd1_ahigh = 1050,
                            int fwd2_alow=780, int fwd2_ahigh = 1030)
{
  // timer
  TStopwatch timer;

  // use koala color
  // init_KoaColors();

  // input
  TFile* f = new TFile(filename,"update");
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress(brName_rec, &RecDigis);
  TClonesArray* FwdDigis = new TClonesArray("KoaFwdDigi");
  tree->SetBranchAddress(brName_fwd, &FwdDigis);

  // histograms definition
  Int_t nbinx=10000;
  Float_t xlow=0,xhigh=2000;

  Int_t nbiny=2500;
  Float_t ylow=0,yhigh=2500; // in ns

  // hit flag in determined by the timestamp value of recoil strip
  TH1D h1map_time("time","Timestamp",nbinx,xlow,xhigh);
  TH1D h1map_time_cut("time_cut","Timestamp (Coincidence Cut)",nbinx,xlow,xhigh);
  TH2D h2map_EnergyVsTime("energy_vs_time", "Energy VS Time (no cut);Energy(MeV);Timestamp(ns)", 4000, 0 , 4000, 3000, 1100 ,1700);
  TH2D h2map_EnergyVsTime_cut("energy_vs_time_cut", "Energy VS Time (no cut);Energy(MeV);Timestamp(ns)", 4000, 0 ,4000, 1500, 1400 ,1700);

  // cut object
  KoaFwdTimeCut time_cut(fwd1_tlow, fwd1_thigh, fwd2_tlow, fwd2_thigh, window_tlow, window_thigh);
  KoaFwdAmpCut amp_cut(fwd1_alow, fwd1_ahigh, fwd2_alow, fwd2_ahigh);

  std::vector<RegionType> cut_condition = {RegionType::FwdTimeMain, RegionType::FwdTimeBand1, RegionType::FwdTimeBand2, RegionType::FwdTimeBand3, RegionType::FwdAmpMain, RegionType::FwdAmpLow1, RegionType::FwdAmpLow2, RegionType::FwdAmpLow};

  auto IfCut = [&] (RegionType  region) -> bool
               {
                 if ( std::find(cut_condition.begin(), cut_condition.end(), region) != cut_condition.end() )
                   return true;
                 return false;
               };

  // Parameters used in event loop
  Int_t det_id, ch_id, id;
  Double_t rec_charge;
  Double_t rec_timestamp;

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
  Long_t entries = tree->GetEntries();
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

    // check cut condition
    auto passed =  IfCut(time_cut.GetType(fwd_time[index0], fwd_time[index1]))
                   && IfCut(amp_cut.GetType(fwd_amp[index0], fwd_amp[index1]));

    // rec digis
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      id = digi->GetDetID();
      if ( id != rec_id )
        continue;

      // rec enerty and timestamp
      // rec_charge = digi->GetCharge()/1000.; // in MeV
      rec_charge = digi->GetCharge(); // for ADC
      rec_timestamp = digi->GetTimeStamp();

      //
      h1map_time.Fill(rec_timestamp);
      h2map_EnergyVsTime.Fill(rec_charge, rec_timestamp);
      if ( passed ) {
        h1map_time_cut.Fill(rec_timestamp);
        h2map_EnergyVsTime_cut.Fill(rec_charge, rec_timestamp);
      }
    }

    fwd_time.clear();
    fwd_amp.clear();
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  // output file
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","");
  outfilename.Append("_result.root");
  TFile *fout = new TFile(outfilename.Data(),"update");

  TDirectory* hdir = getDirectory(fout, Form("%s_%d", sensorname, sensorid));
  hdir->WriteTObject(&h1map_time, "", "Overwrite");
  hdir->WriteTObject(&h1map_time_cut, "", "Overwrite");
  hdir->WriteTObject(&h2map_EnergyVsTime, "", "Overwrite");
  hdir->WriteTObject(&h2map_EnergyVsTime_cut, "", "Overwrite");

  delete f;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}
