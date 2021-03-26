#include "KoaHistUtility.h"

using namespace KoaUtility;

void checkFwdDigiWithEachOther(const char* cluster_filename,
                               const char* branchName,
                               const char* fwddigi_filename,
                               double p0=450, double p1=79.25, double p2=-0.898,
                               double win_low = -200, double win_high = -20
                             )
{
  // timer
  TStopwatch timer;

  // input
  TFile* f = new TFile(cluster_filename);
  TTree* tree = (TTree*)f->Get("koalasim");
  TClonesArray* RecClusters = new TClonesArray("KoaRecCluster");
  tree->SetBranchAddress(branchName, &RecClusters);
  
  TFile* ftime = new TFile(fwddigi_filename);
  TClonesArray* FwdDigis = new TClonesArray("KoaFwdDigi");
  TTree* tree_time = (TTree*)ftime->Get("koalasim");
  tree_time->SetBranchAddress("KoaFwdDigi", &FwdDigis);
  tree->AddFriend(tree_time);

  // range function
  auto fTofE = new TF1("fTofE", "[0]+[1]*TMath::Power(x,-0.5)+[2]*TMath::Power(x,-1.5)", 0.05, 7);
  fTofE->SetParameters(p0, p1, p2);

  // other variables
  Int_t fwd_low, fwd_high;
  auto encoder = KoaMapEncoder::Instance();
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);

  std::map<Int_t, Double_t> fwd_time;
  std::map<Int_t, Double_t> fwd_amp;

  // histograms definition
  Int_t nbin_amp=4000;
  Double_t low_amp=0, high_amp=4000;

  Int_t nbin_time = 10000;
  Double_t low_time = 0, high_time = 2000;

  auto h1map_amp_1 = bookH1dByDetectorId("amp_Fwd1Hitted", "Amplitude (Fwd1 Hitted);QDC counts",
                                       nbin_amp, low_amp, high_amp, false);
  TH2D h2map_amp_1("h2map_amp_Fwd1Hitted", "Fwd1 Vs Fwd2 (Fwd1 Hitted);Fwd1 (QDC counts);Fwd2 (QDC counts)",
                 nbin_amp, low_amp, high_amp, nbin_amp, low_amp, high_amp);

  auto h1map_amp_2 = bookH1dByDetectorId("amp_Fwd2Hitted", "Amplitude (Fwd2 Hitted);QDC counts",
                                         nbin_amp, low_amp, high_amp, false);
  TH2D h2map_amp_2("h2map_amp_Fwd2Hitted", "Fwd1 Vs Fwd2 (Fwd2 Hitted);Fwd1 (QDC counts);Fwd2 (QDC counts)",
                   nbin_amp, low_amp, high_amp, nbin_amp, low_amp, high_amp);

  // event loop
  auto entries = tree->GetEntries();
  for(auto entry=0;entry<entries;entry++){
    tree->GetEntry(entry);

    Int_t fwddigis = FwdDigis->GetEntriesFast();
    for (int i=0;i<fwddigis;i++){
      KoaFwdDigi* digi = (KoaFwdDigi*)FwdDigis->At(i);
      auto id = digi->GetDetID();
      fwd_time[id] = digi->GetTimeStamp();
      fwd_amp[id]  = digi->GetCharge();
    }

    //
    Int_t clusters = RecClusters->GetEntriesFast();
    for(int i=0;i<clusters;i++){
      KoaRecCluster* cluster = (KoaRecCluster*)RecClusters->At(i);
      auto cluster_e = cluster->Energy()/1000.;
      auto cluster_t = cluster->Time();

      auto tof_low = fTofE->Eval(cluster_e) + win_low;
      auto tof_high = fTofE->Eval(cluster_e) + win_high;

      auto tof1 = cluster_t - fwd_time[index0];
      auto tof2 = cluster_t - fwd_time[index1];
      if( tof1 < tof_high && tof1 > tof_low){
        h1map_amp_1[fwd_low].Fill(fwd_amp[index0]);
        h1map_amp_1[fwd_low+1].Fill(fwd_amp[index1]);
        h2map_amp_1.Fill(fwd_amp[index0], fwd_amp[index1]);
        if( tof2 < tof_high && tof2 > tof_low){
          h1map_amp_2[fwd_low].Fill(fwd_amp[index0]);
          h1map_amp_2[fwd_low+1].Fill(fwd_amp[index1]);
          h2map_amp_2.Fill(fwd_amp[index0], fwd_amp[index1]);
        }
      }
    }

    //
    fwd_time.clear();
    fwd_amp.clear();
  }

  // output
  TString outfilename(fwddigi_filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(),"update");
  TDirectory* hdir = getDirectory(fout, Form("fwd_TofE_%0.f_%0.f", win_low, win_high));
  writeHistos(hdir, h1map_amp_1);
  writeHistos(hdir, h1map_amp_2);
  hdir->WriteTObject(&h2map_amp_1, "", "Overwrite");
  hdir->WriteTObject(&h2map_amp_2, "", "Overwrite");

  //
  delete f;
  delete ftime;
  delete fTofE;
  delete fout;

  // timer stop
  timer.Stop();
  timer.Print();
}
