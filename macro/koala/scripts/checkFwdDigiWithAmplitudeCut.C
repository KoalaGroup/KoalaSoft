#include "KoaHistUtility.h"
#include "KoaCutList.h"
#include "KoaColors.h"
#include "KoaCutObject.h"

using namespace KoaUtility;

void checkFwdDigiWithAmplitudeCut(const char* filename, const char* treename,
                                  const char* brName_fwd = "KoaFwdDigi",
                                  int fwd1_low=790, int fwd1_high = 1050,
                                  int fwd2_low=780, int fwd2_high = 1030)
{
  // timer
  TStopwatch timer;

  // use koala color
  // init_KoaColors();

  // input
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* FwdDigis = new TClonesArray("KoaFwdDigi");
  tree->SetBranchAddress(brName_fwd, &FwdDigis);

  // time-cut object
  KoaFwdAmpCut amp_cut(fwd1_low, fwd1_high, fwd2_low, fwd2_high);

  // histograms definition
  Int_t nbin_amp=2500;
  Double_t low_amp=0, high_amp=2500;

  Int_t nbin_time = 10000;
  Double_t low_time = 0, high_time = 2000;

  auto h1map_amp1 = bookH1dByRegionType("amp1", "Fwd1 Amplitude", nbin_amp, low_amp, high_amp);
  auto h1map_amp2 = bookH1dByRegionType("amp2", "Fwd2 Amplitude", nbin_amp, low_amp, high_amp);
  auto h2map_amp  = bookH2dByRegionType("amp","Fwd1 VS Fwd2 Amplitude", nbin_amp, low_amp, high_amp, nbin_amp, low_amp, high_amp);

  auto h1map_time1 = bookH1dByRegionType("time1", "Fwd1 Timestamp", nbin_time, low_time, high_time);
  auto h1map_time2 = bookH1dByRegionType("time2", "Fwd2 Timestamp", nbin_time, low_time, high_time);
  auto h2map_time  = bookH2dByRegionType("time","Fwd1 VS Fwd2 Timestamp", 2000, 0, 2000, 2000, 0, 2000);

  // Parameters used in event loop
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
      auto id = digi->GetDetID();

      fwd_time[id] = digi->GetTimeStamp();
      fwd_amp[id]  = digi->GetCharge();
    }

    // fill histograms
    auto e = amp_cut.GetType(fwd_amp[index0], fwd_amp[index1]);
    auto id = static_cast<int>(e);

    h1map_amp1[id].Fill(fwd_amp[index0]);
    h1map_amp2[id].Fill(fwd_amp[index1]);
    h2map_amp[id].Fill(fwd_amp[index0], fwd_amp[index1]);

    h1map_time1[id].Fill(fwd_time[index0]);
    h1map_time2[id].Fill(fwd_time[index1]);
    h2map_time[id].Fill(fwd_time[index0], fwd_time[index1]);

    //
    fwd_time.clear();
    fwd_amp.clear();
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(),"update");

  TDirectory* hdir = getDirectory(fout, "fwd_ampcut");
  writeHistos(hdir, h1map_amp1);
  writeHistos(hdir, h1map_amp2);
  writeHistos(hdir, h2map_amp);

  writeHistos(hdir, h1map_time1);
  writeHistos(hdir, h1map_time2);
  writeHistos(hdir, h2map_time);

  //
  delete f;
  delete fout;

  // timer stop
  timer.Stop();
  timer.Print();
}
