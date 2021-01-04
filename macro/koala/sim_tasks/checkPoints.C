#include "KoaHistUtility.h"

using namespace KoaUtility;

// void checkPoints(const char* filename)
// {
//   TH2D* h2Fwd=new TH2D("h2Fwd","h2Fwd",200,0,70,200,-1.5,1.5);
//   TH2D* h2Fwd=new TH2D("h2Fwd","h2Fwd",200,0,70,200,-1.5,1.5);
//   TH2D* h2Rec=new TH2D("h2Rec","h2Rec",600,-20,40,350,-17.5,17.5);
//   TH2D* h2RecEVsPos = new TH2D("h2RecEVsPos","h2RecEVsPos",400,-10,30,1000,0,70);
//   TH1D* h1FwdEloss = new TH1D("h1FwdEloss","h1FwdEloss", 1000,-10,90);
//   TH1D* h1RecEloss = new TH1D("h1RecEloss","h1RecEloss", 1000,0,70);
//   TH2D* h2lowRec=new TH2D("h2lowRec","h2lowRec",400,-10,30,200,-7.5,7.5);

//   TFile* f = new TFile(filename);
//   TTree* tree = (TTree*)f->Get("koalasim");
//   TClonesArray* RecPoints = new TClonesArray("KoaRecPoint");
//   TClonesArray* FwdPoints = new TClonesArray("KoaFwdPoint");
//   tree->SetBranchAddress("KoaRecPoint",&RecPoints);
//   tree->SetBranchAddress("KoaFwdPoint",&FwdPoints);

//   Int_t entries = tree->GetEntries();
//   for(int id=0;id<entries;id++){
//     tree->GetEntry(id);
//     //

//     Int_t recHits = RecPoints->GetEntriesFast();
//     Int_t fwdHits = FwdPoints->GetEntriesFast();
//     if(recHits>0){
//       // std::cout<< "Event No. " << id+1 << std::endl;
//       // std::cout<< "Interesting! More than 1 hits in RecArm" << std::endl;
//       for(int i=0;i<recHits;i++){
//         KoaRecPoint* recpoint = (KoaRecPoint*)RecPoints->At(i);
//         h2Rec->Fill(recpoint->GetZ(),recpoint->GetY());
//         h1RecEloss->Fill(recpoint->GetEnergyLoss()*1e3);
//         h2RecEVsPos->Fill(recpoint->GetZ(), recpoint->GetEnergyLoss()*1e3);
//         if(recpoint->GetEnergyLoss()<1e-3){
//           h2lowRec->Fill(recpoint->GetZ(),recpoint->GetY());
//         }
//       }
//       for(int i=0;i<fwdHits;i++){
//         KoaFwdPoint* fwdpoint = (KoaFwdPoint*)FwdPoints->At(i);
//         h2Fwd->Fill(fwdpoint->GetX(), fwdpoint->GetY());
//         h1FwdEloss->Fill(fwdpoint->GetEnergyLoss()*1000);
//       }
//     }
//   }

//   gStyle->SetOptStat(111111);
//   // TCanvas* cfwd=new TCanvas("cfwd");
//   // h2Fwd->Draw("colz");
//   // TCanvas* crec = new TCanvas("crec");
//   // h2Rec->Draw("colz");
//   // TCanvas* cfwde = new TCanvas("cfwde");
//   // h1FwdEloss->Draw();
//   // TCanvas* crece = new TCanvas("crece");
//   // h1RecEloss->Draw();
//   TCanvas* crecevspos=new TCanvas("crecevspos");
//   h2RecEVsPos->Draw("colz");
//   // TCanvas* clowEPosDist= new TCanvas("clowEPosDist");
//   // h2lowRec->Draw("colz");
//   // output file
//   TString outfilename(filename);
//   outfilename.ReplaceAll(".root", "");
//   outfilename.Append("_result.root");
//   TFile *fout = new TFile(outfilename.Data(),"update");

//   TDirectory* hdir;
//   TString dirname("histograms");
//   if(!(hdir=fout->GetDirectory(dirname.Data())))
//     hdir = fout->mkdir(dirname.Data());
//   hdir->cd();
//   h2Fwd->Write(0,TObject::kOverwrite);
//   h2Rec->Write(0,TObject::kOverwrite);
//   h1FwdEloss->Write(0,TObject::kOverwrite);
//   h1RecEloss->Write(0,TObject::kOverwrite);
//   h2RecEVsPos->Write(0,TObject::kOverwrite);
//   h2lowRec->Write(0,TObject::kOverwrite);
  
//   delete f;
//   delete fout;
// }

// void checkRecSize(const char* filename)
// {
//   TH2D* h2Rec=new TH2D("h2Rec","h2Rec",400,-10,30,200,-7.5,7.5);
//   TH1D* h1Rec=new TH1D("h1Rec","Multiplicity", 10, 0,10);
//   auto f=new TFile(filename);

//   TTree* tree = (TTree*)f->Get("koalasim");
//   TClonesArray* RecPoints = new TClonesArray("KoaRecPoint");
//   tree->SetBranchAddress("KoaRecPoint",&RecPoints);

//   Int_t entries = tree->GetEntries();
//   for(int id=0;id<entries;id++){
//     tree->GetEntry(id);
//     //
//     Int_t recHits = RecPoints->GetEntriesFast();
//     h1Rec->Fill(recHits);

//     if(recHits>0){
//       for(int i=0;i<recHits;i++){
//         KoaRecPoint* recpoint = (KoaRecPoint*)RecPoints->At(i);
//         h2Rec->Fill(recpoint->GetZ(),recpoint->GetY());
//       }
//     }
//   }

//   delete f;
//   gStyle->SetOptStat(111111);
//   TCanvas* crec = new TCanvas("crec");
//   h2Rec->Draw("colz");
//   TCanvas* cmulti = new TCanvas("cmulti");
//   h1Rec->Draw();
// }

void checkFwdEnergy(const char* filename)
{
  auto fin = TFile::Open(filename);
  TTree* tin; fin->GetObject("koalasim", tin);

  auto fwdPts = new TClonesArray("KoaFwdPoint", 200);
  tin->SetBranchAddress("KoaFwdPoint", &fwdPts);

  //
  auto h1map = bookH1dByDetectorId("energy","MC Fwd Point Energy",500, 0, 5, false);

  //
  auto entries = tin->GetEntries();
  for(auto entry=0; entry < entries; entry++) {
    tin->GetEntry(entry);

    auto points = fwdPts->GetEntries();
    std::cout << points << std::endl;
    for(int pt=0; pt < points; pt++) {
      KoaFwdPoint* point = static_cast<KoaFwdPoint*>(fwdPts->At(pt));
      h1map[point->GetDetectorID()].Fill(point->GetEnergyLoss()*1000);
      std::cout << point->GetDetectorID() << std::endl;
    }
  }

  std::cout<< "Entries: " << entries << std::endl;

  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(),"update");

  TDirectory* dir = getDirectory(fout, "fwd");
  writeHistos<TH1D>(dir, h1map);

  delete fin;
  delete fout;
}

void checkRecEnergy(const char* filename)
{
  auto fin = TFile::Open(filename);
  TTree* tin; fin->GetObject("koalasim", tin);

  auto recPts = new TClonesArray("KoaRecPoint", 200);
  tin->SetBranchAddress("KoaRecPoint", &recPts);

  //
  auto h2map_all = new TH2D("h2_recpoint_EvsZ",
                            "Recoil MC Points (All): Energy vs Z;MeV;mm",
                            260, -10, 250,
                            7100, -1, 70);

  auto h2map_single = new TH2D("h2_recpoint_EvsZ_single",
                               "Recoil MC Points (Single Point): Energy vs Z;MeV;mm",
                               260, -10, 250,
                               7100, -1, 70);

  auto h2map_multi = new TH2D("h2_recpoint_EvsZ_multi",
                               "Recoil MC Points (Mulit-Points): Energy vs Z;MeV;mm",
                               260, -10, 250,
                               7100, -1, 70);

  //
  auto entries = tin->GetEntries();
  std::cout<< "Entries: " << entries << std::endl;
  for(auto entry=0; entry < entries; entry++) {
    tin->GetEntry(entry);

    auto points = recPts->GetEntries();
    for(int pt=0; pt < points; pt++) {
      KoaRecPoint* point = static_cast<KoaRecPoint*>(recPts->At(pt));
      h2map_all->Fill(10*point->GetZ(), point->GetEnergyLoss()*1000.);

      if(points == 1) {
        h2map_single->Fill(10*point->GetZ(), point->GetEnergyLoss()*1000.);
      }
      else{
        h2map_multi->Fill(10*point->GetZ(), point->GetEnergyLoss()*1000.);
      }
    }
  }

  auto c = new TCanvas();
  c->Divide(1,3);
  c->cd(1);
  h2map_all->Draw("colz");
  c->cd(2);
  h2map_single->Draw("colz");
  c->cd(3);
  h2map_multi->Draw("colz");
}

void checkRecPointSize(const char* filename)
{
  auto fin = TFile::Open(filename);
  TTree* tin; fin->GetObject("koalasim", tin);

  auto recPts = new TClonesArray("KoaRecPoint", 200);
  tin->SetBranchAddress("KoaRecPoint", &recPts);

  //
  auto h1 = new TH1D("h1_recpoint_size", "Size of Recoil MCPoints", 8, -1.5, 6.5);

  //
  auto entries = tin->GetEntries();
  std::cout<< "Entries: " << entries << std::endl;
  for(auto entry=0; entry < entries; entry++) {
    tin->GetEntry(entry);

    auto points = recPts->GetEntries();
    h1->Fill(points);
  }

  h1->Scale(1/h1->Integral());
  h1->Draw("text0");
}

void checkRecPointTrackId(const char* filename)
{
  auto fin = TFile::Open(filename);
  TTree* tin; fin->GetObject("koalasim", tin);

  auto recPts = new TClonesArray("KoaRecPoint", 200);
  tin->SetBranchAddress("KoaRecPoint", &recPts);

  //
  auto h1 = new TH1D("h1_recpoint_trackid", "Track IDs of Recoil MCPoints", 8, -1.5, 6.5);

  //
  auto entries = tin->GetEntries();
  std::cout<< "Entries: " << entries << std::endl;
  for(auto entry=0; entry < entries; entry++) {
    tin->GetEntry(entry);

    auto points = recPts->GetEntries();
    for(int pt=0; pt < points; pt++) {
      auto* point = static_cast<KoaRecPoint*>(recPts->At(pt));
      h1->Fill(point->GetTrackID());
    }
  }

  h1->Scale(1/h1->Integral());
  h1->Draw("text0");
}
