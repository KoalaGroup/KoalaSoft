const Double_t fYMin=-10;
const Double_t fYMax=10;
const Double_t fZMax=40;
const Double_t fZMin=-10;
const Double_t fYHigLim[]={-0.675, 0.675+5, -0.675, 0.675+5};
const Double_t fYLowLim[]={-0.675-5, 0.675, -0.675-5, 0.675};
const Double_t fZLowLim[]={-2.64, 5.28-2.64, 11.88-2.64, 18.72-2.64};
const Double_t fZHigLim[]={-2.64+7.68, 5.28-2.64+7.68, 11.88-2.64+8.04, 18.72-2.64+8.04};

void check_primary(Int_t entry=1000)
{
  TH2D* h2beam=new TH2D("h2beam","beam proton",100,-30,0,100,-7.5,7.5);
  TH2D* h2scat=new TH2D("h2scat","scat proton",100,-10,30,100,-7.5,7.5);
  TH2D* h2scatPvsE=new TH2D("h2scatPvsE","h2scatPvsE", 400,-10,30,1000,0,70);
  TH1D* h1scatE = new TH1D("h1scatE","h1scatE",1000,0,1000);

  //
  TFile* f=new TFile("PPelast.root");
  TTree* t=(TTree*)f->Get("data");
  TClonesArray* fParticles = new TClonesArray("TParticle",100);
  t->SetBranchAddress("Particles",&fParticles);

  Int_t nParts;
  Double_t Ybeam,Yscat;
  Double_t Zbeam,Zscat;

  Int_t beamCount,scatCount;
  Int_t beamTotal,scatTotal;
  Int_t trueCount;
  trueCount = 0;
  beamCount=0;scatCount=0;
  beamTotal=0;scatTotal=0;

  Int_t entries=t->GetEntriesFast();
  for(Int_t id=0;id<entries;id++){
    // for(Int_t id=0;id<entry;id++){
    // for(Int_t id=9982;id<10000;id++){
    t->GetEntry(id);

    nParts = fParticles->GetEntriesFast();

    TParticle* beamPart=(TParticle*) fParticles->At(0);
    TParticle* scatPart=(TParticle*) fParticles->At(1);

    //
    if(beamPart->Px()>0){
      Ybeam = 100*(beamPart->Py()/beamPart->Px());
      Zbeam = 100*(beamPart->Pz()/beamPart->Px());
      h2beam->Fill(Zbeam,Ybeam);
      beamTotal++;

        if((fYMin <= Ybeam) &&
           (fYMax >= Ybeam) &&
           (fZMin <= Zbeam) &&
           (fZMax >= Zbeam)){
          beamCount++;
        }
    }
    if(scatPart->Px()>0){
      Yscat = 100*(scatPart->Py()/scatPart->Px());
      Zscat = 100*(scatPart->Pz()/scatPart->Px());
      // h2scat->Fill(Zscat,Yscat);
      scatTotal++;

      if((fYMin <= Yscat) &&
         (fYMax >= Yscat) &&
         (fZMin <= Zscat) &&
         (fZMax >= Zscat)){
        scatCount++;
        // std::cout<<scatCount<< "of" << id+1<< std::endl;
      }
      for(int i=0;i<4;i++){
        if(fYLowLim[i] <= Yscat &&
           fYHigLim[i] >= Yscat &&
           fZLowLim[i] <= Zscat &&
           fZHigLim[i] >= Zscat){
          h2scat->Fill(Zscat,Yscat);
          trueCount++;
          // std::cout<<"(Y,Z)=("<<Yscat<<","<<Zscat<<")"<<std::endl;

          scatPart->Print();
          Double_t mass=scatPart->GetMass();
          Double_t p[3];
          p[0]=scatPart->Px();
          p[1]=scatPart->Py();
          p[2]=scatPart->Pz();
          mass=TMath::Sqrt(mass*mass+p[0]*p[0]+p[1]*p[1]+p[2]*p[2]);
          // std::cout<<"Ek="<<mass-scatPart->GetMass()<<std::endl;
          h2scatPvsE->Fill(Zscat,(mass-scatPart->GetMass())*1e3);
          h1scatE->Fill((mass-scatPart->GetMass())*1e6);

          break;
        }
          }
    }
  }

  //
  delete f;
  gStyle->SetOptStat(111111);
  TCanvas* cbeam= new TCanvas("cbeam");
  h2beam->Draw("colz");
  TCanvas* cscat= new TCanvas("cscat");
  h2scat->Draw("colz");
  TCanvas* cscatPvsE = new TCanvas("cscatPvsE");
  h2scatPvsE->Draw("colz");
  TCanvas* cscatE = new TCanvas("cscatE");
  h1scatE->Draw();

//   //
//   std::cout<<"beam proton: "<<beamCount<<"("<<beamTotal<<")"<<std::endl;
//   std::cout<<"scat proton: "<<scatCount<<"("<<scatTotal<<")"<<std::endl;
//   std::cout<<"scat proton hit detectors: "<<trueCount<<"("<<scatCount<<")"<<std::endl;
}

void check_fwd()
{
  TH2D* h2Range=new TH2D("h2Range","Beam Proton Distribution within Range Y[-10,10] Z[-10,40]",200,0,100,200,-10,10);
  TH2D* h2Detector1=new TH2D("h2Detector1","Beam Proton Distribution in Fwd Detectors",500,0,70,200,-5,5);
  //
  TFile* f=new TFile("PPelast.root");
  TTree* t=(TTree*)f->Get("data");
  TClonesArray* fParticles = new TClonesArray("TParticle",100);
  t->SetBranchAddress("Particles",&fParticles);

  Double_t Yscat, Zscat;
  Double_t Xbeam1, Ybeam1;
  Double_t Xbeam2, Ybeam2;
  Double_t rec_x=-100;
  Double_t fwd_z=499;

  Int_t entries=t->GetEntries();
  for(Int_t id=0;id<entries;id++){
    t->GetEntry(id);
    //
    TParticle* beamPart=(TParticle*) fParticles->At(0);
    TParticle* scatPart=(TParticle*) fParticles->At(1);

    if(scatPart->Px()<0){
      Yscat = rec_x*(scatPart->Py()/scatPart->Px());
      Zscat = rec_x*(scatPart->Pz()/scatPart->Px());
      Xbeam1 = fwd_z*(beamPart->Px()/beamPart->Pz());
      Ybeam1 = fwd_z*(beamPart->Py()/beamPart->Pz());

      if((fYMin <= Yscat) &&
         (fYMax >= Yscat) &&
         (fZMin <= Zscat) &&
         (fZMax >= Zscat)){
        h2Range->Fill(Xbeam1,Ybeam1);
      }
      for(int i=0;i<4;i++){
        if(fYLowLim[i] <= Yscat &&
           fYHigLim[i] >= Yscat &&
           fZLowLim[i] <= Zscat &&
           fZHigLim[i] >= Zscat){
          h2Detector1->Fill(Xbeam1,Ybeam1);
          break;
        }
      }
    }
  }
  //
  delete f;
  gStyle->SetOptStat(111111);
  TCanvas* cbeam= new TCanvas("cbeam");
  h2Range->Draw("colz");
  h2Range->GetXaxis()->SetTitle("X (cm)");
  h2Range->GetYaxis()->SetTitle("Y (cm)");
  TCanvas* cscat= new TCanvas("cscat");
  h2Detector1->Draw("colz");
  h2Detector1->GetXaxis()->SetTitle("X (cm)");
  h2Detector1->GetYaxis()->SetTitle("Y (cm)");
}
