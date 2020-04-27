#include "KoaHistUtility.h"
#include "KoaCutList.h"

using namespace KoaUtility;

void checkDigiTof(const char* filename,   const char* treename, bool isSimulation = false)
{
  // timer
  TStopwatch timer;

  // parameters
  Int_t nbiny=1500;
  Float_t ylow=450,yhigh=750;

  Int_t nbinx=200;
  Float_t xlow=0,xhigh=8;

  // histograms definition
  TH2D h2("h2_TofVsE","TOF VS Energy;MeV;ns", nbinx, xlow, xhigh, nbiny, ylow, yhigh);

  auto h1map_tof = bookH1dByRecTdcChannelId("tof", "Time of flight;ns", nbiny, ylow, yhigh);
  auto h2map_TofVsEnergy = bookH2dByRecTdcChannelId("TofVsEnergy", "TOF Vs Energy;MeV;ns", nbinx, xlow, xhigh, nbiny, ylow, yhigh);

  // input
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress("KoaRecDigi",&RecDigis);
  TClonesArray* FwdDigis = new TClonesArray("KoaFwdDigi");
  tree->SetBranchAddress("KoaFwdDigi",&FwdDigis);

  // output/input entry list 
  TDirectory *edir = getDirectory(f, "elists");
  std::string listName = getCutListName("fwdhit");

  TEntryList *cutlist;
  edir->GetObject(listName.data(), cutlist);
  if(!cutlist){
    std::cout << "Error: no list found in file: " << filename << std::endl;
    return;
  }
  tree->SetEntryList(cutlist);

  // event loop
  Long_t entries;
  entries = cutlist->GetN();

  Int_t det_id, ch_id, id;
  Double_t charge;
  Double_t timestamp, tof;

  std::map<Int_t, Double_t> fwd_time;
  std::map<Int_t, Double_t> fwd_amp;
  Int_t fwd_low, fwd_high;

  auto encoder = KoaMapEncoder::Instance();
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);

  for(auto entry=0;entry<entries;entry++){
    auto entrynum = tree->GetEntryNumber(entry);
    tree->GetEntry(entrynum);

    // fwd digis
    Int_t fwddigis = FwdDigis->GetEntriesFast();
    for (int i=0;i<fwddigis;i++){
      KoaFwdDigi* digi = (KoaFwdDigi*)FwdDigis->At(i);
      id = digi->GetDetID();
      fwd_time[id] = digi->GetTimeStamp();
      fwd_amp[id]  = digi->GetCharge();
    }

    //
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      // rec digis
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      id = digi->GetDetID();
      ch_id = encoder->DecodeChannelID(id, det_id);

      if (isSimulation) {
        charge = 1000*digi->GetCharge();
      }
      else {
        charge = digi->GetCharge()/1000.;
      }

      // timestamp
      timestamp = digi->GetTimeStamp();

      //
      if ( timestamp > 0 ) {
        auto search = h1map_tof.find(id);
        if( search != h1map_tof.end()) {
          if ( fwd_time[index0] > 923 && fwd_time[index0] < 927 ) {
            if ( fwd_time[index1] > 923 && fwd_time[index1] < 927 ) {
              tof = timestamp - (fwd_time[index0]+fwd_time[index1])/2;
            }
            else {
              tof = timestamp - fwd_time[index0];
            }
          }
          else {
            tof = timestamp - fwd_time[index1];
          }

          h1map_tof[id].Fill(tof);
          h2map_TofVsEnergy[id].Fill(charge, tof);
          h2.Fill(charge, tof);
        }
      }
    }

    fwd_time.clear();
    fwd_amp.clear();
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  // output file
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(),"update");

  TDirectory* hdir = getDirectory(fout, "tof_spectrum");
  hdir->WriteTObject(&h2, "", "Overwrite");
  writeHistos(hdir, h1map_tof);
  writeHistos(hdir, h2map_TofVsEnergy);

  //
  delete f;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}
