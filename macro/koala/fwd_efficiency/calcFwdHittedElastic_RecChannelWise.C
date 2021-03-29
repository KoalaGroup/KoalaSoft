#include "KoaHistUtility.h"

using namespace KoaUtility;

/* Filter out elastic events based on TOF-E of each recoil channel
   , using information of one of the fwd.
 * Output: Two histograms for each recoil channel: passed nr of events, total nr of events
 * Selection conditions:
 * 1. cluster nr = 1
 * 2. TOF-E relation within a time window
 * 3. fwd amp > trigger value (MIP traversing value, not DAQ trigger value)
 *
 * Pass (Detection) Threshold of fwd: DAQ trigger value
 *
 */
void calcFwdHittedElastic_RecChannelWise(const char* cluster_filename,
                                         const char* branchName,
                                         const char* fwddigi_filename,
                                         double p0=450, double p1=79.25, double p2=-0.898,
                                         double window = 20,
                                         // double e_low = 0.2, double e_high = 1.0,
                                         double fwd1_thresh_mip = 1040, double fwd2_thresh_mip=1040,
                                         double fwd1_thresh_daq = 780, double fwd2_thresh_daq=790
                                         )
{
  // input
  TFile* fcluster = new TFile(cluster_filename);
  TTree* tree = (TTree*)fcluster->Get("koalasim");
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

  // Histos
  auto h1map_fwd1_passed = bookH1dByRecDetectorId("fwd1_passed","Fwd1 Detected Elastic Event Number");
  auto h1map_fwd1_total = bookH1dByRecDetectorId("fwd1_total","Fwd1 All Elastic Event Number");
  auto h1map_fwd2_passed = bookH1dByRecDetectorId("fwd2_passed","Fwd2 Detected Elastic Event Number");
  auto h1map_fwd2_total = bookH1dByRecDetectorId("fwd2_total","Fwd2 All Elastic Event Number");

  // other variables
  Int_t fwd_low, fwd_high;
  auto encoder = KoaMapEncoder::Instance();
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);

  std::map<Int_t, Double_t> fwd_time;
  std::map<Int_t, Double_t> fwd_amp;

  // event loop
  Long_t fwd1_total=0, fwd2_trigger=0;
  Long_t fwd2_total=0, fwd1_trigger=0;

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

    //
    KoaRecCluster* cluster = (KoaRecCluster*)RecClusters->At(0);
    auto cluster_e = cluster->Energy()/1000.;
    auto cluster_t = cluster->Time();

    if(cluster_t < 0)
      continue;

    auto det_id = cluster->GetDetId();
    auto cluster_id = cluster->GetFirstChIdAboveThresh();
    auto ch_id = encoder->DecodeChannelID(cluster_id, det_id);

    auto tof_low = fTofE->Eval(cluster_e)-window;
    auto tof_high = fTofE->Eval(cluster_e)+window;

    if(fwd_time[index0]>0){
      auto tof1 = cluster_t - fwd_time[index0];
      if( tof1 < tof_high && tof1 > tof_low && fwd_amp[index0]>fwd1_thresh_mip){
        fwd2_total++;
        h1map_fwd2_total[det_id].Fill(ch_id+1);
        if(fwd_amp[index1] > fwd2_thresh_daq){
          fwd2_trigger++;
          h1map_fwd2_passed[det_id].Fill(ch_id+1);
        }
      }
    }

    if(fwd_time[index1]>0){
      auto tof2 = cluster_t - fwd_time[index1];
      if( tof2 < tof_high && tof2 > tof_low && fwd_amp[index1]>fwd2_thresh_mip){
        fwd1_total++;
        h1map_fwd1_total[det_id].Fill(ch_id+1);
        if(fwd_amp[index0] > fwd1_thresh_daq){
          fwd1_trigger++;
          h1map_fwd1_passed[det_id].Fill(ch_id+1);
        }
      }
    }

    //
    fwd_time.clear();
    fwd_amp.clear();
  }

  //
  std::cout << fwd1_trigger << "\t" << fwd1_total << "\t" << (double)fwd1_trigger/fwd1_total << "\t"
            << fwd2_trigger << "\t" << fwd2_total << "\t" << (double)fwd2_trigger/fwd2_total << std::endl;

  // output
  TString outfilename(cluster_filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename, "update");

  TDirectory* hdir = nullptr;
  hdir = getDirectory(fout, "fwd_evtnr_elastic");
  writeHistos<TH1D>(hdir, h1map_fwd1_passed);
  writeHistos<TH1D>(hdir, h1map_fwd2_passed);
  writeHistos<TH1D>(hdir, h1map_fwd1_total);
  writeHistos<TH1D>(hdir, h1map_fwd2_total);

  //
  delete fTofE;
  delete fcluster;
  delete ftime;
  delete fout;
}
