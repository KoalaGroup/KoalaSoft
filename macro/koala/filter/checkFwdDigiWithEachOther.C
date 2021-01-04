#include "KoaHistUtility.h"
#include "KoaCutList.h"
#include "KoaColors.h"
#include "KoaCutObject.h"

using namespace KoaUtility;

void checkFwdDigiWithEachOther(const char* filename,
                               const char* elist_file
                             )
{
  // timer
  TStopwatch timer;

  // input
  TFile* ffwd = new TFile(filename);
  TTree* fwd_tree = (TTree*)ffwd->Get("koalasim");
  TClonesArray* FwdDigis = new TClonesArray("KoaFwdDigi");
  fwd_tree->SetBranchAddress("KoaFwdDigi", &FwdDigis);

  TFile* felist = new TFile(elist_file);
  TDirectory* eDir = getDirectory(felist, "fwd");
  TEventList* eList1 = getObject<TEventList>(eDir, "fwd1_hitted");
  TEventList* eList2 = getObject<TEventList>(eDir, "fwd2_hitted");

  // histograms definition
  Int_t nbin_amp=4000;
  Double_t low_amp=0, high_amp=4000;

  Int_t nbin_time = 10000;
  Double_t low_time = 0, high_time = 2000;

  auto h1map_amp_1 = bookH1dByDetectorId("amp_Fwd1Hitted", "Amplitude (Fwd1 Hitted);QDC counts",
                                       nbin_amp, low_amp, high_amp, false);
  TH2D h2map_amp_1("h2map_amp_Fwd1Hitted", "Fwd1 Vs Fwd2 (Fwd1 Hitted);Fwd1 (QDC counts);Fwd2 (QDC counts)",
                 nbin_amp, low_amp, high_amp, nbin_amp, low_amp, high_amp);

  TH1D h1_deltaT_zoom_1("deltaT_zoom_Fwd1Hitted","Fwd2 - Fwd1 (Fwd1 Hitted);#Delta T(ns)", 1000,-10, 10);

  auto h1map_amp_2 = bookH1dByDetectorId("amp_Fwd2Hitted", "Amplitude (Fwd2 Hitted);QDC counts",
                                         nbin_amp, low_amp, high_amp, false);
  TH2D h2map_amp_2("h2map_amp_Fwd2Hitted", "Fwd1 Vs Fwd2 (Fwd2 Hitted);Fwd1 (QDC counts);Fwd2 (QDC counts)",
                   nbin_amp, low_amp, high_amp, nbin_amp, low_amp, high_amp);

  TH1D h1_deltaT_zoom_2("deltaT_zoom_Fwd2Hitted","Fwd2 - Fwd1 (Fwd2 Hitted);#Delta T(ns)", 1000,-10, 10);

  // Parameters used in event loop
  std::map<Int_t, Double_t> fwd_time;
  std::map<Int_t, Double_t> fwd_amp;
  Int_t fwd_low, fwd_high;

  auto encoder = KoaMapEncoder::Instance();
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);

  // event loop
  auto entries = fwd_tree->GetEntries();
  for(auto entry=0;entry<entries;entry++){
    fwd_tree->GetEntry(entry);

    Int_t fwddigis = FwdDigis->GetEntriesFast();
    for (int i=0;i<fwddigis;i++){
      KoaFwdDigi* digi = (KoaFwdDigi*)FwdDigis->At(i);
      auto id = digi->GetDetID();
      fwd_time[id] = digi->GetTimeStamp();
      fwd_amp[id]  = digi->GetCharge();
    }

    if(eList1->Contains(entry)){
      h1map_amp_1[fwd_low].Fill(fwd_amp[index0]);
      h1map_amp_1[fwd_low+1].Fill(fwd_amp[index1]);
      h2map_amp_1.Fill(fwd_amp[index0], fwd_amp[index1]);
      h1_deltaT_zoom_1.Fill(fwd_time[index1] - fwd_time[index0]);
    }

    if(eList2->Contains(entry)){
      h1map_amp_2[fwd_low].Fill(fwd_amp[index0]);
      h1map_amp_2[fwd_low+1].Fill(fwd_amp[index1]);
      h2map_amp_2.Fill(fwd_amp[index0], fwd_amp[index1]);
      h1_deltaT_zoom_2.Fill(fwd_time[index1] - fwd_time[index0]);
    }

    //
    fwd_time.clear();
    fwd_amp.clear();
  }

  // output
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(),"update");
  TDirectory* hdir = getDirectory(fout, "fwd_hitted");
  writeHistos(hdir, h1map_amp_1);
  writeHistos(hdir, h1map_amp_2);
  hdir->WriteTObject(&h2map_amp_1, "", "Overwrite");
  hdir->WriteTObject(&h2map_amp_2, "", "Overwrite");
  hdir->WriteTObject(&h1_deltaT_zoom_1, "", "Overwrite");
  hdir->WriteTObject(&h1_deltaT_zoom_2, "", "Overwrite");

  //
  delete ffwd;
  delete fout;

  // timer stop
  timer.Stop();
  timer.Print();
}
