#include "KoaHistUtility.h"
#include "KoaCutList.h"
#include "KoaColors.h"
#include "KoaCutObject.h"

using namespace KoaUtility;

void checkFwdDigiWithCluster(const char* filename,
                             const char* filename_rec,
                             const char* brName_rec = "KoaRecCluster_Smear"
                             )
{
  // timer
  TStopwatch timer;

  // input
  TFile* ffwd = new TFile(filename);
  TTree* fwd_tree = (TTree*)ffwd->Get("koalasim");
  TClonesArray* FwdDigis = new TClonesArray("KoaFwdDigi");
  fwd_tree->SetBranchAddress("KoaFwdDigi", &FwdDigis);

  TFile* frec = new TFile(filename_rec);
  TTree* rec_tree = (TTree*)frec->Get("koalasim");
  TClonesArray* RecClusters = new TClonesArray("KoaRecCluster");
  rec_tree->SetBranchAddress(brName_rec, &RecClusters);
  fwd_tree->AddFriend(rec_tree);

  // histograms definition
  Int_t nbin_amp=4000;
  Double_t low_amp=0, high_amp=4000;

  Int_t nbin_time = 10000;
  Double_t low_time = 0, high_time = 2000;

  auto h1map_amp = bookH1dByDetectorId("amp", "Amplitude;QDC counts",
                                       nbin_amp, low_amp, high_amp, false);
  TH2D h2map_amp("h2map_amp", "Amplitude: Fwd1 Vs Fwd2;Fwd1 (QDC counts);Fwd2 (QDC counts)",
                 nbin_amp, low_amp, high_amp, nbin_amp, low_amp, high_amp);

  TH1D h1_deltaT_zoom("deltaT_zoom","Fwd2 - Fwd1;#Delta T(ns)", 1000,-50, 50);

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
  auto entries = fwd_tree->GetEntries();
  for(auto entry=0;entry<entries;entry++){
    fwd_tree->GetEntry(entry);

    // fwd digis
    int nr_cl = RecClusters->GetEntriesFast();
    if(nr_cl>0){
      Int_t fwddigis = FwdDigis->GetEntriesFast();
      for (int i=0;i<fwddigis;i++){
        KoaFwdDigi* digi = (KoaFwdDigi*)FwdDigis->At(i);
        id = digi->GetDetID();
        ch_id = encoder->DecodeChannelID(id, det_id);

        fwd_time[id] = digi->GetTimeStamp();
        fwd_amp[id]  = digi->GetCharge();

        h1map_amp[det_id].Fill(fwd_amp[id]);
      }
      h2map_amp.Fill(fwd_amp[index0], fwd_amp[index1]);
      if (fwd_time[index0] > 0 && fwd_time[index1] > 0) {
        h1_deltaT_zoom.Fill(fwd_time[index1] - fwd_time[index0]);
      }

      //
      fwd_time.clear();
      fwd_amp.clear();
    }
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(),"update");

  TDirectory* hdir = getDirectory(fout, "fwd_RecTriggered");
  writeHistos(hdir, h1map_amp);

  hdir->WriteTObject(&h2map_amp, "", "Overwrite");
  hdir->WriteTObject(&h1_deltaT_zoom, "", "Overwrite");

  //
  delete ffwd;
  delete frec;
  delete fout;

  // timer stop
  timer.Stop();
  timer.Print();
}
