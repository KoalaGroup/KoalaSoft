#include "KoaHistUtility.h"

using namespace KoaUtility;

void filterFwdOnTofE(const char* cluster_filename,
                     const char* branchName,
                     const char* fwddigi_filename,
                     const char* elist_filename,
                     double p0=450, double p1=79.25, double p2=-0.898, double window = 20,
                     double e_low = 0.2, double e_high = 1.0,
                     double fwd1_amp_trigger = 790, double fwd2_amp_trigger=780
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

  //
  TEventList elist1("fwd1_hitted","Elastic events which hit fwd1 and should hit fwd2");
  TEventList elist2("fwd2_hitted","Elastic events which hit fwd2 and should hit fwd1");

  // event loop
  Long_t entries = tree->GetEntries();
  for(auto entry=0;entry<entries;entry++){
    tree->GetEntry(entry);

    // only check events with nr of clusters = 1
    Int_t clusters = RecClusters->GetEntriesFast();
    if(clusters !=1) continue;

    // fwd digis
    Int_t fwddigis = FwdDigis->GetEntriesFast();
    for (int i=0;i<fwddigis;i++){
      KoaFwdDigi* digi = (KoaFwdDigi*)FwdDigis->At(i);
      auto id = digi->GetDetID();
      fwd_time[id] = digi->GetTimeStamp();
      fwd_amp[id]  = digi->GetCharge();
    }

    KoaRecCluster* cluster = (KoaRecCluster*)RecClusters->At(0);
    auto cluster_e = cluster->Energy()/1000.;
    auto cluster_t = cluster->Time();

    if(cluster_t < 0 || cluster_e < e_low || cluster_e > e_high)
      continue;

    auto tof_low = fTofE->Eval(cluster_e)-window;
    auto tof_high = fTofE->Eval(cluster_e)+window;

    auto tof1 = cluster_t - fwd_time[index0];
    if( tof1 < tof_high && tof1 > tof_low && fwd_amp[index0]>fwd1_amp_trigger){
      elist1.Enter(entry);
    }
    auto tof2 = cluster_t - fwd_time[index1];
    if( tof2 < tof_high && tof2 > tof_low && fwd_amp[index1]>fwd2_amp_trigger){
      elist2.Enter(entry);
    }

    //
    fwd_time.clear();
    fwd_amp.clear();
  }
  std::cout << "Events processed : "<< entries << std::endl;

  // output
  TFile *fout = new TFile(elist_filename, "update");

  TDirectory* hdir = nullptr;
  hdir = getDirectory(fout, "fwd");
  hdir->WriteTObject(&elist1, "", "Overwrite");
  hdir->WriteTObject(&elist2, "", "Overwrite");

  //
  delete fTofE;
  delete f;
  delete ftime;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}
