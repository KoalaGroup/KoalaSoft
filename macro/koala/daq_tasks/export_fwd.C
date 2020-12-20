#include "KoaUtility.h"

using namespace KoaUtility;
using namespace std;

void export_fwd(const char* finname,
                const char* fclustername,
                const char* br_cluster = "KoaRecCluster_ThresholdFilter"
                )
{
  TFile* fin=new TFile(finname);

  // Retrieve the EMS raw event tree
  TTree* tin=(TTree*)fin->Get("koalasim");
  TClonesArray *evt=new TClonesArray("KoaFwdDigi");
  tin->SetBranchAddress("KoaFwdDigi", &evt);

  //
  TFile* fcluster = new TFile(fclustername);
  TTree* tcluster = (TTree*)fcluster->Get("koalasim");
  TClonesArray *clusters = new TClonesArray("KoaRecCluster");
  tcluster->SetBranchAddress(br_cluster, &clusters);
  tin->AddFriend(tcluster);

  // Define output columns
  TString foutname = finname;
  foutname.ReplaceAll(".root","_fwd.csv");

  ofstream fout;
  fout.open(foutname);
  fout << "amp1\tamp2\tt1\tt2\tclusters" << endl;

  // Export Fwd data
  double fwd_amp[2], fwd_time[2];

  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  Int_t fwd_low, fwd_high;
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);

  Long_t entries = tin->GetEntries();
  for(int entry=0;entry<entries;entry++){
    tin->GetEntry(entry);

    //
    int digis = evt->GetEntriesFast();
    for(int i=0;i<digis;i++){
      KoaFwdDigi* digi = (KoaFwdDigi*)evt->At(i);
      auto id = digi->GetDetID();
      if(id == index0){
        fwd_amp[0]=digi->GetCharge();
        fwd_time[0]=digi->GetTimeStamp();
      }
      else if(id == index1){
        fwd_amp[1]=digi->GetCharge();
        fwd_time[1]=digi->GetTimeStamp();
      }
    }

    // number of clusters in recoil
    int cl_num = clusters->GetEntriesFast();

    //
    fout << fwd_amp[0] << "\t" << fwd_amp[1] << "\t"
         << fwd_time[0] << "\t" << fwd_time[1] << "\t"
         << cl_num
         << endl;
  }
  cout << "events: " << entries << endl;

  // Clean up
  delete fin;
  delete fcluster;
  fout.close();
}
