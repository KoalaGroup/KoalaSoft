#include "KoaHistUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

/* Filter out elastic events based on TOF-E using information of one of the fwd.
 * Output: Two list of events fwd1_hitted_elastic, fwd2_hitted_elastic
 * Selection conditions:
 * 1. cluster nr = 1
 * 2. TOF-E relation obtained from individual TOF-E [-5,5]sigma
 * 3. e_low < E < e_high
 * 4. fwd amp > trigger value (MIP traversing value, not DAQ trigger value)
 */
void filterFwdOnTofE_Individual(const char* cluster_filename,
                                const char* cut_filename,
                                const char* fwddigi_filename,
                                const char* elist_filename,
                                const char* branchName = "KoaRecCluster_Smear",
                                const char* cut_dirname = "TofE_profile_MoreThan10Evts",
                                double e_low = 0.1, double e_high = 3,
                                double fwd1_amp_trigger = 1040, double fwd2_amp_trigger=1040
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

  // compose graph for the filtering
  auto fgraph = TFile::Open(cut_filename);
  auto gdir = getDirectory(fgraph, cut_dirname);

  auto gr_mean = getGraphsByRecTdcChannelId(gdir, "mean");
  auto gr_sigma = getGraphsByRecTdcChannelId(gdir, "sigma");

  double high = 5, low = -5;
  auto gr_up = bookGraphByRecTdcChannelId(Form("up_%0.1fsigma",high),
                                          Form("Cut High Threshold with %.1f #sigma",high),
                                          kRed, 20, 0.4);
  auto gr_down = bookGraphByRecTdcChannelId(Form("down_%0.1fsigma",low),
                                            Form("Cut Low Threshold with %.1f #sigma",low),
                                            kRed, 20, 0.4);

  for(auto item: gr_mean){
    auto id = item.first;
    auto gr_mean_tmp = item.second;

    int npoints = gr_mean_tmp->GetN();
    double *e = gr_mean_tmp->GetX();
    double *tof = gr_mean_tmp->GetY();
    double *sigma = gr_sigma[id]->GetY();
    for(int i=0;i<npoints;i++){
      gr_up[id].SetPoint(i, e[i], tof[i]+high*sigma[i]);
      gr_down[id].SetPoint(i, e[i], tof[i]+low*sigma[i]);
    }
  }

  // other variables
  Int_t fwd_low, fwd_high;
  auto encoder = KoaMapEncoder::Instance();
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);

  std::map<Int_t, Double_t> fwd_time;
  std::map<Int_t, Double_t> fwd_amp;

  //
  TEventList elist1("fwd1_hitted_elastic","Elastic events which hit fwd1 and should hit fwd2");
  TEventList elist2("fwd2_hitted_elastic","Elastic events which hit fwd2 and should hit fwd1");

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
    auto cluster_id = cluster->GetFirstChId();
    auto cluster_e = cluster->Energy()/1000.;
    auto cluster_t = cluster->Time();

    if(cluster_t < 0 || cluster_e < e_low || cluster_e > e_high)
      continue;

    auto tof_low = gr_down[cluster_id].Eval(cluster_e);
    auto tof_high = gr_up[cluster_id].Eval(cluster_e);

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
  delete f;
  delete ftime;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}
