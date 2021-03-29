const Double_t fYMin=-10;
const Double_t fYMax=10;
const Double_t fZMax=40;
const Double_t fZMin=-10;
const Double_t fYHigLim[]={-0.675, 0.675+5, -0.675, 0.675+5};
const Double_t fYLowLim[]={-0.675-5, 0.675, -0.675-5, 0.675};
// interaction point starts from strip_12 of Si1, NOTE: the first 16 strips in Si1 are 2-in-1
const Double_t fZLowLim[]={-2.64, 5.28-2.64, 11.88-2.64, 18.72-2.64};
const Double_t fZHigLim[]={-2.64+7.68, 5.28-2.64+7.68, 11.88-2.64+8.04, 18.72-2.64+8.04};

void check_primary(Int_t entry=1000)
{
  TH2D* h2beam=new TH2D("h2beam","beam proton",100,-30,0,100,-7.5,7.5);
  TH2D* h2recoil=new TH2D("h2recoil","scat proton",100,-10,30,100,-7.5,7.5);
  TH2D* h2scatPvsE=new TH2D("h2scatPvsE","h2scatPvsE", 400,-10,30,1000,0,70);
  TH1D* h1scatE = new TH1D("h1scatE","h1scatE",1000,0,1000);

  //
  TFile* f=new TFile("PPelast.root");
  TTree* t=(TTree*)f->Get("data");
  TClonesArray* fParticles = new TClonesArray("TParticle",100);
  t->SetBranchAddress("Particles",&fParticles);

  Int_t nParts;
  Double_t Ybeam,Yrecoil;
  Double_t Zbeam,Zrecoil;

  Int_t beamCount,recoilCount;
  Int_t beamTotal,recoilTotal;
  Int_t trueCount;
  trueCount = 0;
  beamCount=0;recoilCount=0;
  beamTotal=0;recoilTotal=0;

  Int_t entries=t->GetEntriesFast();
  for(Int_t id=0;id<entries;id++){
    // for(Int_t id=0;id<entry;id++){
    // for(Int_t id=9982;id<10000;id++){
    t->GetEntry(id);

    nParts = fParticles->GetEntriesFast();

    TParticle* beamPart=(TParticle*) fParticles->At(0);
    TParticle* recoilPart=(TParticle*) fParticles->At(1);

    //
    // if(beamPart->Px()>0){
    //   Ybeam = 100*(beamPart->Py()/beamPart->Px());
    //   Zbeam = 100*(beamPart->Pz()/beamPart->Px());
    //   h2beam->Fill(Zbeam,Ybeam);
    //   beamTotal++;

    //     if((fYMin <= Ybeam) &&
    //        (fYMax >= Ybeam) &&
    //        (fZMin <= Zbeam) &&
    //        (fZMax >= Zbeam)){
    //       beamCount++;
    //     }
    // }
    if(recoilPart->Px()<0){
      Yrecoil = -100*(recoilPart->Py()/recoilPart->Px());
      Zrecoil = -100*(recoilPart->Pz()/recoilPart->Px());
      // h2recoil->Fill(Zrecoil,Yrecoil);
      recoilTotal++;

      if((fYMin <= Yrecoil) &&
         (fYMax >= Yrecoil) &&
         (fZMin <= Zrecoil) &&
         (fZMax >= Zrecoil)){
        recoilCount++;
        // std::cout<<recoilCount<< "of" << id+1<< std::endl;
      }
      for(int i=0;i<4;i++){
        if(fYLowLim[i] <= Yrecoil &&
           fYHigLim[i] >= Yrecoil &&
           fZLowLim[i] <= Zrecoil &&
           fZHigLim[i] >= Zrecoil){
          h2recoil->Fill(Zrecoil,Yrecoil);
          trueCount++;
          // std::cout<<"(Y,Z)=("<<Yrecoil<<","<<Zrecoil<<")"<<std::endl;

          recoilPart->Print();
          Double_t mass=recoilPart->GetMass();
          Double_t p[3];
          p[0]=recoilPart->Px();
          p[1]=recoilPart->Py();
          p[2]=recoilPart->Pz();
          mass=TMath::Sqrt(mass*mass+p[0]*p[0]+p[1]*p[1]+p[2]*p[2]);
          // std::cout<<"Ek="<<mass-recoilPart->GetMass()<<std::endl;
          h2scatPvsE->Fill(Zrecoil,(mass-recoilPart->GetMass())*1e3);
          h1scatE->Fill((mass-recoilPart->GetMass())*1e6);

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
  h2recoil->Draw("colz");
  TCanvas* cscatPvsE = new TCanvas("cscatPvsE");
  h2scatPvsE->Draw("colz");
  TCanvas* cscatE = new TCanvas("cscatE");
  h1scatE->Draw();

//   //
//   std::cout<<"beam proton: "<<beamCount<<"("<<beamTotal<<")"<<std::endl;
//   std::cout<<"scat proton: "<<recoilCount<<"("<<recoilTotal<<")"<<std::endl;
//   std::cout<<"scat proton hit detectors: "<<trueCount<<"("<<recoilCount<<")"<<std::endl;
}

void check_fwd()
{
  TH2D* h2Range=new TH2D("h2Range","Beam Proton Distribution within Range Y[-10,10] Z[-10,40]",200,0,100,200,-10,10);
  TH2D* h2Detector1=new TH2D("h2Detector1","Beam Proton Distribution in Fwd Detectors",500,0,55,200,-4,3);
  //
  TFile* f=new TFile("PPelast.root");
  TTree* t=(TTree*)f->Get("data");
  TClonesArray* fParticles = new TClonesArray("TParticle",100);
  t->SetBranchAddress("Particles",&fParticles);

  Double_t Yrecoil, Zrecoil;
  Double_t Xbeam1, Ybeam1;
  Double_t Xbeam2, Ybeam2;
  Double_t rec_x=-100;
  Double_t fwd_z=460;

  Int_t entries=t->GetEntries();
  for(Int_t id=0;id<entries;id++){
    t->GetEntry(id);
    //
    TParticle* beamPart=(TParticle*) fParticles->At(0);
    TParticle* recoilPart=(TParticle*) fParticles->At(1);

    if(recoilPart->Px()<0){
      Yrecoil = rec_x*(recoilPart->Py()/recoilPart->Px());
      Zrecoil = rec_x*(recoilPart->Pz()/recoilPart->Px());
      Xbeam1 = fwd_z*(beamPart->Px()/beamPart->Pz());
      Ybeam1 = fwd_z*(beamPart->Py()/beamPart->Pz());

      if((fYMin <= Yrecoil) &&
         (fYMax >= Yrecoil) &&
         (fZMin <= Zrecoil) &&
         (fZMax >= Zrecoil)){
        h2Range->Fill(Xbeam1,Ybeam1);
      }
      for(int i=0;i<4;i++){
        if(fYLowLim[i] <= Yrecoil &&
           fYHigLim[i] >= Yrecoil &&
           fZLowLim[i] <= Zrecoil &&
           fZHigLim[i] >= Zrecoil){
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
