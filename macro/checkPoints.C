void checkPoints(const char* filename)
{
  TH2D* h2Fwd=new TH2D("h2Fwd","h2Fwd",200,0,70,200,-5,5);
  TH2D* h2Rec=new TH2D("h2Rec","h2Rec",600,-20,40,350,-17.5,17.5);
  TH2D* h2RecEVsPos = new TH2D("h2RecEVsPos","h2RecEVsPos",400,-10,30,1000,0,70);
  TH1D* h1FwdEloss = new TH1D("h1FwdEloss","h1FwdEloss", 1000,-10,90);
  TH1D* h1RecEloss = new TH1D("h1RecEloss","h1RecEloss", 1000,0,70);
  TH2D* h2lowRec=new TH2D("h2lowRec","h2lowRec",400,-10,30,200,-7.5,7.5);

  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get("koalasim");
  TClonesArray* RecPoints = new TClonesArray("KoaRecPoint");
  TClonesArray* FwdPoints = new TClonesArray("KoaFwdPoint");
  tree->SetBranchAddress("KoaRecPoint",&RecPoints);
  tree->SetBranchAddress("KoaFwdPoint",&FwdPoints);

  Int_t entries = tree->GetEntries();
  for(int id=0;id<entries;id++){
    tree->GetEntry(id);
    //

    Int_t recHits = RecPoints->GetEntriesFast();
    Int_t fwdHits = FwdPoints->GetEntriesFast();
    if(recHits>0){
      // std::cout<< "Event No. " << id+1 << std::endl;
      // std::cout<< "Interesting! More than 1 hits in RecArm" << std::endl;
      for(int i=0;i<recHits;i++){
        KoaRecPoint* recpoint = (KoaRecPoint*)RecPoints->At(i);
        h2Rec->Fill(recpoint->GetZ(),recpoint->GetY());
        h1RecEloss->Fill(recpoint->GetEnergyLoss()*1e3);
        h2RecEVsPos->Fill(recpoint->GetZ(), recpoint->GetEnergyLoss()*1e3);
        if(recpoint->GetEnergyLoss()<1e-3){
          h2lowRec->Fill(recpoint->GetZ(),recpoint->GetY());
        }
      }
      for(int i=0;i<fwdHits;i++){
        KoaFwdPoint* fwdpoint = (KoaFwdPoint*)FwdPoints->At(i);
        h2Fwd->Fill(fwdpoint->GetX(), fwdpoint->GetY());
        h1FwdEloss->Fill(fwdpoint->GetEnergyLoss()*1000);
      }
    }
  }

  gStyle->SetOptStat(111111);
  // TCanvas* cfwd=new TCanvas("cfwd");
  // h2Fwd->Draw("colz");
  // TCanvas* crec = new TCanvas("crec");
  // h2Rec->Draw("colz");
  // TCanvas* cfwde = new TCanvas("cfwde");
  // h1FwdEloss->Draw();
  // TCanvas* crece = new TCanvas("crece");
  // h1RecEloss->Draw();
  // TCanvas* crecevspos=new TCanvas("crecevspos");
  // h2RecEVsPos->Draw("colz");
  // TCanvas* clowEPosDist= new TCanvas("clowEPosDist");
  // h2lowRec->Draw("colz");
  // output file
  TString outfilename(filename);
  outfilename.ReplaceAll(".root", "");
  outfilename.Append("_result.root");
  TFile *fout = new TFile(outfilename.Data(),"update");

  TDirectory* hdir;
  TString dirname("histograms");
  if(!(hdir=fout->GetDirectory(dirname.Data())))
    hdir = fout->mkdir(dirname.Data());
  hdir->cd();
  h2Fwd->Write(0,TObject::kOverwrite);
  h2Rec->Write(0,TObject::kOverwrite);
  h1FwdEloss->Write(0,TObject::kOverwrite);
  h1RecEloss->Write(0,TObject::kOverwrite);
  h2RecEVsPos->Write(0,TObject::kOverwrite);
  h2lowRec->Write(0,TObject::kOverwrite);
  
  delete f;
  delete fout;
}

void checkRecSize(const char* filename)
{
  TH2D* h2Rec=new TH2D("h2Rec","h2Rec",400,-10,30,200,-7.5,7.5);
  TH1D* h1Rec=new TH1D("h1Rec","Multiplicity", 10, 0,10);
  auto f=new TFile(filename);

  TTree* tree = (TTree*)f->Get("koalasim");
  TClonesArray* RecPoints = new TClonesArray("KoaRecPoint");
  tree->SetBranchAddress("KoaRecPoint",&RecPoints);

  Int_t entries = tree->GetEntries();
  for(int id=0;id<entries;id++){
    tree->GetEntry(id);
    //
    Int_t recHits = RecPoints->GetEntriesFast();
    h1Rec->Fill(recHits);

    if(recHits>0){
      for(int i=0;i<recHits;i++){
        KoaRecPoint* recpoint = (KoaRecPoint*)RecPoints->At(i);
        h2Rec->Fill(recpoint->GetZ(),recpoint->GetY());
      }
    }
  }

  delete f;
  gStyle->SetOptStat(111111);
  TCanvas* crec = new TCanvas("crec");
  h2Rec->Draw("colz");
  TCanvas* cmulti = new TCanvas("cmulti");
  h1Rec->Draw();
}
