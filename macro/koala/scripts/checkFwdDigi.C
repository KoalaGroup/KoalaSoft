#include "KoaHistUtility.h"
#include "KoaCutList.h"
#include "KoaColors.h"
#include "KoaCutObject.h"

using namespace KoaUtility;

void checkFwdDigi(const char* filename, const char* treename,
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
  TClonesArray* FwdDigis = new TClonesArray("KoaFwdDigi");
  tree->SetBranchAddress(brName_fwd, &FwdDigis);

  // histograms definition
  Int_t nbin_amp=2500;
  Double_t low_amp=0, high_amp=2500;

  Int_t nbin_time = 10000;
  Double_t low_time = 0, high_time = 2000;

  auto h1map_amp = bookH1dByDetectorId("amp", "Amplitude;QDC counts",
                                       nbin_amp, low_amp, high_amp, false);
  TH2D h2map_amp("h2map_amp", "Amplitude: Fwd1 Vs Fwd2;Fwd1 (QDC counts);Fwd2 (QDC counts)",
                 nbin_amp, low_amp, high_amp, nbin_amp, low_amp, high_amp);

  auto h1map_time = bookH1dByDetectorId("time","Time;ns",nbin_time,low_time,high_time,false);
  TH2D h2map_time("h2map_time","Timestamp: Fwd1 Vs Fwd2;Fwd1 (ns);Fwd2 (ns)",
                  2000, 0, 2000, 2000, 0, 2000);
  TH1D h1_deltaT_zoom("deltaT_zoom","Fwd2 - Fwd1;#Delta T(ns)", 1000,-50, 50);
  TH1D h1_deltaT("deltaT","Fwd2 - Fwd1;#Delta T ( ns )", 4000, -2000, 2000);

  auto h2map_amp_vs_time = bookH2dByDetectorId("amp_vs_time", "Amplitude VS Timestamp; Amplitude (QDC counts);Timestamp (ns)",
                                               nbin_amp, low_amp, high_amp, 2000, 0, 2000, false);
  auto h2map_amp_vs_time_zoom = bookH2dByDetectorId("amp_vs_time_zoom", "Amplitude VS Timestamp; Amplitude (QDC counts);Timestamp (ns)",
                                                    nbin_amp, low_amp, high_amp, 2500, 700, 1200, false);

  TH2D h2map_amp1_vs_time2_zoom("amp1_vs_time2_zoom", "Amplitude VS Timestamp; Fwd1 Amplitude (QDC counts); Fwd2 Timestamp (ns)",
                                                      nbin_amp, low_amp, high_amp, 2500, 700, 1200);
  TH2D h2map_amp2_vs_time1_zoom("amp2_vs_time1_zoom", "Amplitude VS Timestamp; Fwd2 Amplitude (QDC counts); Fwd1 Timestamp (ns)",
                                                      nbin_amp, low_amp, high_amp, 2500, 700, 1200);

  // Parameters used in event loop
  Int_t det_id, ch_id, id;

  std::map<Int_t, Double_t> fwd_time;
  std::map<Int_t, Double_t> fwd_amp;
  Int_t fwd_low, fwd_high;

  auto encoder = KoaMapEncoder::Instance();
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);

  // event loop
  auto entries = tree->GetEntries();
  for(auto entry=0;entry<entries;entry++){
    tree->GetEntry(entry);

    // fwd digis
    Int_t fwddigis = FwdDigis->GetEntriesFast();
    for (int i=0;i<fwddigis;i++){
      KoaFwdDigi* digi = (KoaFwdDigi*)FwdDigis->At(i);
      id = digi->GetDetID();
      ch_id = encoder->DecodeChannelID(id, det_id);

      fwd_time[id] = digi->GetTimeStamp();
      fwd_amp[id]  = digi->GetCharge();

      h1map_amp[det_id].Fill(fwd_amp[id]);
      h1map_time[det_id].Fill(fwd_time[id]);
      h2map_amp_vs_time[det_id].Fill(fwd_amp[id], fwd_time[id]);
      h2map_amp_vs_time_zoom[det_id].Fill(fwd_amp[id], fwd_time[id]);
    }
    h2map_amp.Fill(fwd_amp[index0], fwd_amp[index1]);
    h2map_time.Fill(fwd_time[index0], fwd_time[index1]);
    h2map_amp1_vs_time2_zoom.Fill(fwd_amp[index0], fwd_time[index1]);
    h2map_amp2_vs_time1_zoom.Fill(fwd_amp[index1], fwd_time[index0]);
    if (fwd_time[index0] > 0 && fwd_time[index1] > 0) {
      h1_deltaT.Fill(fwd_time[index1] - fwd_time[index0]);
      h1_deltaT_zoom.Fill(fwd_time[index1] - fwd_time[index0]);
    }

    //
    fwd_time.clear();
    fwd_amp.clear();
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(),"update");

  TDirectory* hdir = getDirectory(fout, "fwd");
  writeHistos(hdir, h1map_amp);
  writeHistos(hdir, h1map_time);
  writeHistos(hdir, h2map_amp_vs_time);
  writeHistos(hdir, h2map_amp_vs_time_zoom);

  hdir->WriteTObject(&h2map_amp, "", "Overwrite");
  hdir->WriteTObject(&h2map_time, "", "Overwrite");
  hdir->WriteTObject(&h1_deltaT, "", "Overwrite");
  hdir->WriteTObject(&h1_deltaT_zoom, "", "Overwrite");
  hdir->WriteTObject(&h2map_amp1_vs_time2_zoom, "", "Overwrite");
  hdir->WriteTObject(&h2map_amp2_vs_time1_zoom, "", "Overwrite");

  //
  delete f;
  delete fout;

  // timer stop
  timer.Stop();
  timer.Print();
}
