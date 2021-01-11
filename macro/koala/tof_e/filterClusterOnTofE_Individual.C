#include "KoaHistUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

void filterClusterOnTofE_Individual(const char* filename,
                                    const char* cut_filename,
                                    const char* fwdhitFileName,
                                    const char* brName_cluster = "KoaRecCluster_Smear",
                                    const char* cut_dirname = "TofE_profile_MoreThan10Evts",
                                    const char* fwdhitTreeName = "fwdhit_time",
                                    double low = -5, double high = 5,
                                    int amp_nbin = 700, double amp_low = 0, double amp_high = 7,
                                    int time_nbin = 1500, double time_low = 450, double time_high = 750
                         )
{
  TFile* fcluster = new TFile(filename);
  TTree* tree = (TTree*)fcluster->Get("koalasim");
  TClonesArray* RecClusters = new TClonesArray("KoaRecCluster");
  tree->SetBranchAddress(brName_cluster, &RecClusters);

  TFile* ftime = new TFile(fwdhitFileName);
  TTree* tree_time = (TTree*)ftime->Get(fwdhitTreeName);
  Float_t fwdhit_timestamp;
  tree_time->SetBranchAddress(fwdhitTreeName,&fwdhit_timestamp);
  tree->AddFriend(tree_time);

  // compose graph for the filtering
  auto fgraph = TFile::Open(cut_filename);
  auto gdir = getDirectory(fgraph, cut_dirname);

  auto gr_mean = getGraphsByRecTdcChannelId(gdir, "mean");
  auto gr_sigma = getGraphsByRecTdcChannelId(gdir, "sigma");

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
    gr_up[id].SetLineWidth(2);
    gr_up[id].SetLineColor(kRed);
    gr_down[id].SetLineWidth(2);
    gr_down[id].SetLineColor(kRed);
  }

  //
  auto h2map_tofe = bookH2dByRecTdcChannelId("TofE",
                                             "Cluster Energy VS TOF; E (MeV); TOF (ns)",
                                             amp_nbin, amp_low, amp_high,
                                             time_nbin, time_low, time_high);
  auto h2map_tofe_inv = bookH2dByRecTdcChannelId("TofE_Inverse",
                                             "Cluster 1/E VS TOF; 1/E (MeV); TOF (ns)",
                                             200, 0.5, 20.5,
                                             300, time_low, time_high);
  auto h1map_tof = bookH1dByRecTdcChannelId("Tof",
                                            "Cluster TOF (after cut)",
                                            time_nbin, time_low, time_high);
  auto h1map_energy = bookH1dByRecTdcChannelId("Energy",
                                            "Cluster Energy (after cut)",
                                            amp_nbin, amp_low, amp_high);
  auto h1map_energy_all = bookH1dByRecTdcChannelId("Energy_All",
                                                   "Cluster Energy (after cut)",
                                                   amp_nbin, amp_low, amp_high);

  TH2D h2_tofe("h2_TofE", "Cluster Energy VS TOF (all strips); E (MeV); TOF (ns)",
               amp_nbin, amp_low, amp_high,
               time_nbin, time_low, time_high);
  TH2D h2_si1_tofe("h2_Si1_TofE", "Cluster Energy VS TOF (Si1); E (MeV); TOF (ns)",
                   amp_nbin, amp_low, amp_high,
                   time_nbin, time_low, time_high);
  TH2D h2_si2_tofe("h2_Si2_TofE", "Cluster Energy VS TOF (Si2); E (MeV); TOF (ns)",
                   amp_nbin, amp_low, amp_high,
                   time_nbin, time_low, time_high);
  TH2D h2_tofe_inv("h2_TofE_Inverse", "1/E VS TOF (all strips); 1/E (1/MeV); TOF (ns)",
                   200, 0.5, 20.5,
                   300, time_low, time_high);
  TH1D h1_si1_energy("h1_Si1_Energy","Cluster Energy (Si1)",amp_nbin, amp_low, amp_high);
  TH1D h1_si2_energy("h1_Si2_Energy","Cluster Energy (Si2)",amp_nbin, amp_low, amp_high);
  TH1D h1_si1_energy_all("h1_Si1_Energy_All","Cluster Energy (Si1)",amp_nbin, amp_low, amp_high);
  TH1D h1_si2_energy_all("h1_Si2_Energy_All","Cluster Energy (Si2)",amp_nbin, amp_low, amp_high);

  // event loop
  auto encoder = KoaMapEncoder::Instance();
  Long_t entries = tree->GetEntries();
  for(auto entry=0;entry<entries;entry++){
    tree->GetEntry(entry);

    Int_t clusters = RecClusters->GetEntriesFast();
    for (int i=0;i<clusters;i++){
      KoaRecCluster* cluster = (KoaRecCluster*)RecClusters->At(i);
      auto cluster_e = cluster->Energy()/1000.;

      int cluster_id, det_id, ch_id;
      ch_id = encoder->DecodeChannelID(cluster_id, det_id);
      cluster_id = cluster->GetFirstChId();

      if(det_id==0){
        h1_si1_energy_all.Fill(cluster_e);
      }
      else if (det_id==1){
        h1_si2_energy_all.Fill(cluster_e);
      }

      h1map_energy_all[cluster_id].Fill(cluster_e);
    }

    //
    if (fwdhit_timestamp > 0) {
      Int_t clusters = RecClusters->GetEntriesFast();

      for (int i=0;i<clusters;i++){
        KoaRecCluster* cluster = (KoaRecCluster*)RecClusters->At(i);

        int cluster_id, det_id, ch_id;
        cluster_id = cluster->GetFirstChId();
        ch_id = encoder->DecodeChannelID(cluster_id, det_id);

        auto cluster_e = cluster->Energy()/1000.;
        auto cluster_t = cluster->Time();
        auto tof = cluster_t - fwdhit_timestamp;
        auto tof_low = gr_down[cluster_id].Eval(cluster_e);
        auto tof_high = gr_up[cluster_id].Eval(cluster_e);

        if (tof > tof_high) {
          continue;
        }

        if(tof < tof_low){
          h2map_tofe_inv[cluster_id].Fill(1/cluster_e, tof);
          h2_tofe_inv.Fill(1/cluster_e, tof);
        }
        else{
          h2map_tofe[cluster_id].Fill(cluster_e, tof);
          h2_tofe.Fill(cluster_e, tof);
          if(det_id==0){
            h2_si1_tofe.Fill(cluster_e, tof);
            h1_si1_energy.Fill(cluster_e);
          }
          else if (det_id==1){
            h2_si2_tofe.Fill(cluster_e, tof);
            h1_si2_energy.Fill(cluster_e);
          }

          h1map_tof[cluster_id].Fill(tof);
          h1map_energy[cluster_id].Fill(cluster_e);
        }
      }
    }
  }
  std::cout << "Events processed : "<< entries << std::endl;

  //
  TString outfilename(filename);
  outfilename.ReplaceAll(".root", "_TofE_cut.root");
  TFile* fout = TFile::Open(outfilename.Data(), "update");

  auto tof_e_dir = getDirectory(fout, Form("TofE_Individual_%.1f_%.1f", low, high));
  writeHistos<TH2D>(tof_e_dir, h2map_tofe);
  tof_e_dir->WriteTObject(&h2_tofe, "", "WriteDelete");
  tof_e_dir->WriteTObject(&h2_si1_tofe, "", "WriteDelete");
  tof_e_dir->WriteTObject(&h2_si2_tofe, "", "WriteDelete");

  auto tof_einv_dir = getDirectory(fout, Form("TofE_inv_Individual_%.1f_%.1f", low, high));
  writeHistos<TH2D>(tof_einv_dir, h2map_tofe_inv);
  tof_einv_dir->WriteTObject(&h2_tofe_inv, "", "WriteDelete");

  auto tof_dir = getDirectory(fout, Form("Tof_Individual_%.1f_%.1f", low, high));
  writeHistos<TH1D>(tof_dir, h1map_tof);

  auto energy_dir = getDirectory(fout, Form("Energy_Individual_%.1f_%.1f", low, high));
  writeHistos<TH1D>(energy_dir, h1map_energy);
  energy_dir->WriteTObject(&h1_si1_energy, "", "WriteDelete");
  energy_dir->WriteTObject(&h1_si2_energy, "", "WriteDelete");

  auto energy_all_dir = getDirectory(fout, Form("Energy_All_Individual_%.1f_%.1f", low, high));
  writeHistos<TH1D>(energy_all_dir, h1map_energy_all);
  energy_all_dir->WriteTObject(&h1_si1_energy_all, "", "WriteDelete");
  energy_all_dir->WriteTObject(&h1_si2_energy_all, "", "WriteDelete");

  //
  delete fout;
  delete fcluster;
  delete ftime;
  delete fgraph;
}
