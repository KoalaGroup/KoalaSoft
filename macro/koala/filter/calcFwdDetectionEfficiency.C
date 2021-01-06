#include "KoaHistUtility.h"
using namespace KoaUtility;

void calcFwdDetectionEfficiency(const char* digifile,
                                const char* elist_file,
                                double fwd1_amp_trigger = 780, double fwd2_amp_trigger=790
                                )
{
  TFile* file = new TFile(digifile);
  TClonesArray* FwdDigis = new TClonesArray("KoaFwdDigi");
  TTree* tree = (TTree*)file->Get("koalasim");
  tree->SetBranchAddress("KoaFwdDigi", &FwdDigis);
  
  TFile* felist = new TFile(elist_file);
  TDirectory* eDir = getDirectory(felist, "fwd");
  TEventList* eList1 = getObject<TEventList>(eDir, "fwd1_hitted_elastic");
  TEventList* eList2 = getObject<TEventList>(eDir, "fwd2_hitted_elastic");


  // other variables
  Int_t fwd_low, fwd_high;
  auto encoder = KoaMapEncoder::Instance();
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);

  std::map<Int_t, Double_t> fwd_time;
  std::map<Int_t, Double_t> fwd_amp;

  Long_t fwd1_total=0, fwd2_trigger=0;
  Long_t fwd2_total=0, fwd1_trigger=0;

  // event loop
  Long_t entries = tree->GetEntries();
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

    //
    if(eList1->Contains(entry)){
      fwd2_total++;
      if(fwd_amp[index1]>fwd2_amp_trigger)
        fwd2_trigger++;
    }
    if(eList2->Contains(entry)){
      fwd1_total++;
      if(fwd_amp[index0]>fwd1_amp_trigger)
        fwd1_trigger++;
    }

    //
    fwd_time.clear();
    fwd_amp.clear();
  }

  //
  std::cout << fwd1_trigger << "\t" << fwd1_total << "\t" << (double)fwd1_trigger/fwd1_total << "\t"
            << fwd2_trigger << "\t" << fwd2_total << "\t" << (double)fwd2_trigger/fwd2_total << std::endl;

  delete file;
  delete felist;
}
