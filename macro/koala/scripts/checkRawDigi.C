#include "KoaHistUtility.h"

using namespace KoaUtility;

void checkRecRawDigi(const char* filename,  const char* treename,
                     const char* brName_rec = "KoaRecDigi", const char* brName_fwd = "KoaFwdDigi")
{
  // timer
  TStopwatch timer;

  // use koala color
  // init_KoaColors();

  // input
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress(brName_rec, &RecDigis);

  // histograms definition
  Int_t adc_nbin=7010;
  Float_t adc_xlow=-10,adc_xhigh=7000;

  auto h1map_Energy = bookH1dByChannelId("adc", "ADC", adc_nbin, adc_xlow, adc_xhigh);
  // auto h2map_EnergyVsStripId = bookH2dByRecDetectorId("adc_vs_strip","ADC VS Strip_id;Strip id;ADC", adc_nbin, adc_xlow, adc_xhigh);

  //
  Int_t tdc_nbin = 2000;
  Float_t tdc_xlow = 1400, tdc_xhigh = 1800;

  auto h1map_time = bookH1dByRecTdcChannelId("time","Timestamp", tdc_nbin, tdc_xlow, tdc_xhigh);
  auto h2map_EnergyVsTime = bookH2dByRecTdcChannelId("adc_vs_time", "ADC VS Time;ADC counts;Timestamp(ns)",
                                                     3500, 0, 7000,
                                                     1000, 1500, 1700);

  // Parameters used in event loop
  Int_t det_id, ch_id, id;
  Double_t rec_adc;
  Double_t rec_timestamp;

  auto encoder = KoaMapEncoder::Instance();

  // event loop
  Long_t entries = tree->GetEntries();
  for(auto entry=0;entry<entries;entry++){
    tree->GetEntry(entry);

    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      id = digi->GetDetID();
      ch_id = encoder->DecodeChannelID(id, det_id);

      // rec enerty and timestamp
      rec_adc = digi->GetCharge();
      rec_timestamp = digi->GetTimeStamp();

      //
      // h2map_EnergyVsStripId[det_id].Fill(ch_id+1, rec_adc);
      h1map_Energy[id].Fill(rec_adc);
      if ( h1map_time.find(id) != h1map_time.end() ) {
        h1map_time[id].Fill(rec_timestamp);
        h2map_EnergyVsTime[id].Fill(rec_adc, rec_timestamp);
      }
    }
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  // output file
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","");
  outfilename.Append("_result.root");
  TFile *fout = new TFile(outfilename.Data(),"update");

  TDirectory* hdir = getDirectory(fout, "raw_adc");
  // writeHistos(hdir, h2map_EnergyVsStripId);
  writeHistos(hdir, h1map_Energy);

  hdir = getDirectory(fout, "rec_time");
  writeHistos(hdir, h1map_time);

  hdir = getDirectory(fout, "energy_vs_time");
  writeHistos(hdir, h2map_EnergyVsTime);

  delete f;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}
