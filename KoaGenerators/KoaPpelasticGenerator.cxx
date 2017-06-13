// -------------------------------------------------------------------------
// -----                KoaPpelasticGenerator source file                  -----
// -------------------------------------------------------------------------
#include <iostream>
#include "TClonesArray.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TVector3.h"
#include "TParticle.h"
#include "KoaPpelasticGenerator.h"
#include "FairPrimaryGenerator.h"

using namespace std;

PPElastic::PPElastic()
{
  fBeta = 0.;
  fTetaCMS = 0.; 
  fRa = 0.;
  fRef = 0.;
  fceff = 0.;
  rho=0.;
  Pcms = 0.;
  fTmax = 0.;
  fThetaLab = 0.;
  cs_tot=0;
  cs_el=0;
  fnt=0;
  Mn=0.938;
  //-----------------
  Pcms=0;
  Ecms=0;
  SqrtS=0;
  Vcms=0;
  Gamma=0;
  prob_col=0;
  prob_int=0;
  prob_had=0;
  aelm = 1./137.03;
 
  B = 0;
  A1=0;
  A2=0;
  sigma_tot = 0;
  fNdiv=300000;
  fdto=0;
}

void  PPElastic::Init(Double_t Plab, Double_t tetmin)
{
  TLorentzVector  Pproj(0.,0.,Plab,sqrt(Plab*Plab+Mn*Mn));

  Double_t Elab=Pproj.E()-Mn;  

  //transform to CMS

  TLorentzVector lv(0.0,0.0,0.0,Mn);
  lv += Pproj;
  S = lv.Mag2() ;
  SqrtS=sqrt(S);
  Ecms=SqrtS/2.;

  TVector3 bst = lv.BoostVector();
  Pproj.Boost(-bst);

  TVector3  p1 = Pproj.Vect();
  Double_t ptot = p1.Mag();

  fbst = bst;
// fTmax = 4.0*ptot*ptot;
  Pcms= ptot;
  Vcms=Plab/(Elab+0.938) ;
  Gamma=(Elab+0.938)/SqrtS ;
  fBeta=CalculateParticleBeta(Plab);
  if(Plab<1.5) 
    { sigma_tot = 23.5+24.6/(1.+exp(-(Plab-1.2)/0.1));}
  else
    { sigma_tot = 41.+60.*(Plab-0.9)*exp(-1.2*Plab); }

  Double_t Pfix[78]={1.139,1.168,1.197,1.225,1.254,1.283,1.312,1.341,
   1.369,1.398,1.427,1.456,1.485,1.513,1.542,1.571,1.6,1.628,
     1.657,1.686,1.715,1.743,1.772,1.801,1.83,1.859,1.887,1.916,
     1.945,1.974,2.003,2.031,2.06,2.089,2.118,2.146,2.175,2.204,
     2.233,2.261,2.29,2.319,2.348,2.377,2.405,2.434,2.463,2.492,
     2.521,2.549,2.578,2.607,2.636,2.664,2.693,2.722,2.751,2.78,
     2.808,2.837,2.866,2.895,2.924,2.952,2.981,3.01,3.039,3.067,
     3.096,3.125,3.154,3.182,3.211,3.24,3.269,3.298,3.326, 5.5};

  Double_t A1fix[78]={41.31, 49.79, 58.58, 67.36, 75.73, 82.73, 89.58, 95.98,
    101.4, 105.3, 108.3, 110.5, 112.3, 113.0, 113.2, 112.8, 112.8, 112.5, 
    112.5, 112.1, 112.0, 111.8, 111.6, 111.5, 111.3, 111.2, 111.1, 111.0,
    110.9, 110.8, 110.7, 110.7, 110.6, 110.5, 110.4, 110.3, 110.2, 110.2,
    110.0, 110.0, 109.8, 109.7, 109.6, 109.5, 109.4, 109.3, 109.2, 109.0,
    108.9, 108.8, 108.6, 108.5, 108.3, 108.2, 108.1, 107.9, 107.8, 107.7,
    107.5, 107.4, 107.2, 107.1, 106.9, 106.8, 106.7, 106.5, 106.4, 106.2,
    106.1, 105.9, 105.8, 105.6, 105.5, 105.3, 105.2, 105.1, 104.9, 98.25};

 Double_t A2fix[78]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.3, 0.5, 0.65, 0.75, 0.87, 0.97, 1.07, 1.15, 1.23, 1.313, 1.359,
        1.401, 1.44, 1.465, 1.489, 1.49, 1.47, 1.462, 1.453, 1.437, 1.42,
        1.396, 1.385, 1.355, 1.345, 1.323, 1.289, 1.263, 1.24, 1.218, 1.207,
        1.201, 1.17, 1.162, 1.126, 1.12, 1.092, 1.093, 1.074, 1.042, 1.03,
  1.003, 0.9943, 0.9777, 0.9546, 0.9411, 0.9245, 0.8983, 0.8817, 0.8589, 0.8554,
  0.841, 0.8243, 0.8028, 0.7785, 0.76, 0.7503, 0.725, 0.7054, 0.7039, 0.6841,
  0.6672, 0.6498, 0.6356, 0.6244, 0.6077, 0.5949, 0.1155 };

  Double_t Bfix[78]=
{1.375, 1.6, 1.799, 1.972, 2.117, 2.276, 2.392, 2.459, 2.493, 2.541,
          2.591, 2.623, 2.633, 2.66, 2.66, 2.714, 2.717, 2.751, 2.745, 2.791,
           2.822, 2.843, 2.86, 2.883, 2.926, 2.948, 2.969, 2.989, 3.02, 3.042,
           3.083, 3.071, 3.105, 3.132, 3.145, 3.16, 3.164, 3.194, 3.2, 3.202,
           3.215, 3.225, 3.245, 3.256, 3.252, 3.277, 3.273, 3.3, 3.311, 3.313,
           3.33, 3.346, 3.343, 3.35, 3.35, 3.355, 3.36, 3.37, 3.384, 3.407,
           3.412, 3.425, 3.413, 3.41, 3.41, 3.395, 3.409, 3.408, 3.414, 3.411,
           3.416, 3.398, 3.4, 3.38, 3.36, 3.34, 3.33, 3.306 };

  Int_t ii=0;
  while(Plab>Pfix[ii]){ii++;}
  ii=ii-1;
  A1 = A1fix[ii]+(A1fix[ii+1]-A1fix[ii])*(Plab-Pfix[ii])/(Pfix[ii+1]-Pfix[ii]);
  A2 = A2fix[ii]+(A2fix[ii+1]-A2fix[ii])*(Plab-Pfix[ii])/(Pfix[ii+1]-Pfix[ii]);
  B = Bfix[ii]+(Bfix[ii+1]-Bfix[ii])*(Plab-Pfix[ii])/(Pfix[ii+1]-Pfix[ii]);
  B *= 2.0; 
  cout<<" nomer " <<ii<< " A1 "<<A1<<" A2 " <<A2<<" B "<<B<<endl;

  //rho=A2/sqrt(A1);            //- -> +
  //rho = -0.2;
  //rho = -0.3902;
  rho=-0.1;
  cout<<" rho = " <<rho<<endl;
 
  Double_t Elastic;

  Double_t Tmax = -4.*Pcms*Pcms ;
  fTmax=Tmax;

  Double_t T11, T22, dto, dt;

  if(tetmin<0.) { Elastic=0.; }
          else { Elastic=1.; }
 
  if(Elastic==0.) {
    // only hadron part of elastic
    prob_had=1.; 
    Fun_inv[0]=0;
    // fNdiv=300000;
    dto=Tmax/(double)fNdiv/2.;           //  /2.   aida
    fdto=dto;
    Double_t SIG_Had=0;
    for(int k=1; k<fNdiv; k++)
   {
     T11=k*dto;
     T22=T11+dto;
     dt=(T22-T11)/2.0;
     SIG_Had=fabs(dt)*(1./3.*DSIG_HAD(T11)+
     4./3.*DSIG_HAD(T11+dt)+1./3.*DSIG_HAD(T22)) ;
     Fun_inv[k] =  Fun_inv[k-1]+SIG_Had;
    }
    cs_el=Fun_inv[fNdiv-1]; 
    for(int k=1; k<fNdiv; k++){Fun_inv[k]/=Fun_inv[fNdiv-1];}

  }

  if(Elastic>0.) 
    { // simulation of hadron, interference and Coulomb parts 
      // calculation of XS of Hadron, Coulomb, Interference parts

      Double_t Tetmin = tetmin*3.1416/180. ;

 Double_t Tmin = 2.*(Plab*Plab)*(1.-cos(Tetmin));
 Tmin=-Tmin;
 fTmin=Tmin;

 Int_t      Ndiv=fNdiv;   
  dto=(Tmax/2.-Tmin)/(double)Ndiv;            //  /2.

 Double_t   SIG_Had=0.;
 for(int k=1; k<=Ndiv; k++){
   T11=Tmin+(k-1)*dto;
   T22=T11+dto;
   dt=(T22-T11)/2.0;
SIG_Had=SIG_Had+fabs(dt)*(1./3.*DSIG_HAD(T11)+4./3.*DSIG_HAD(T11+dt)+1./3.*DSIG_HAD(T22)) ;

                             }
 Double_t   SIG_COL=0.;
 for(int k=1; k<=Ndiv; k++){
           T11=Tmin+(k-1)*dto;
           T22=T11+dto;
           dt=(T22-T11)/2.0;
           SIG_COL=SIG_COL+fabs(dt)*(1./3.*DSIG_COL(T11)+
           4./3.*DSIG_COL(T11+dt)+1./3.*DSIG_COL(T22));
                          }

Double_t   SIG_INTER=0. ;
 for(int k=1; k<=Ndiv; k++){
          T11=Tmin+(k-1)*dto;
          T22=T11+dto;
          dt=(T22-T11)/2.0;
         SIG_INTER=SIG_INTER+fabs(dt)*(1./3.*DSIG_INT(T11)+
        4./3.*DSIG_INT(T11+dt)+1./3.*DSIG_INT(T22)) ;

                         }

cout<<"  sig_had  "<<SIG_Had<<" Sig_col " <<SIG_COL<<" Sig_inter "<< SIG_INTER<< endl; 

  dto=(Tmax/2.-Tmin)/(double)fNdiv;       //  /2.
  fdto=dto;
 SIG_COL=0.;
 SIG_INTER=0.;
 SIG_Had=0.;
 Fun_inv[0]=0; 
 for(int k=1; k<fNdiv; k++)
   {
       T11=Tmin+(k-1)*dto;
          T22=T11+dto;
          dt=(T22-T11)/2.0;
         SIG_COL=fabs(dt)*(1./3.*DSIG_COL(T11)+
           4./3.*DSIG_COL(T11+dt)+1./3.*DSIG_COL(T22));

    SIG_INTER=fabs(dt)*(1./3.*DSIG_INT(T11)+
        4./3.*DSIG_INT(T11+dt)+1./3.*DSIG_INT(T22)) ;

     SIG_Had=fabs(dt)*(1./3.*DSIG_HAD(T11)+
     4./3.*DSIG_HAD(T11+dt)+1./3.*DSIG_HAD(T22)) ;

 Fun_inv[k] = Fun_inv[k-1]+SIG_COL-SIG_INTER+SIG_Had;

    }
  cs_el=Fun_inv[fNdiv-1];  
  for(int k=1; k<fNdiv; k++){Fun_inv[k]/=Fun_inv[fNdiv-1];}
  
   
/*
/////testing
 for(int kk=1; kk<20; kk++){
 Double_t t1=-0.01*kk;
 cout <<" T " <<t1<<" Colon " <<DSIG_COL(t1)<<" Int "<<DSIG_INT(t1)<<" Hadron "
<< DSIG_HAD(t1)<<endl;
 }  /////end testing
 */ 
 
 }

 }
/////////////////////////////////////////////////////////////


// -----   Default constructor   ------------------------------------------
KoaPpelasticGenerator::KoaPpelasticGenerator() {
  iEvent     = 0;
  fInputFile = NULL;
  fInputTree = NULL;
}

KoaPpelasticGenerator::KoaPpelasticGenerator(Double_t p){
  
}
// ------------------------------------------------------------------------



// -----   Standard constructor   -----------------------------------------
KoaPpelasticGenerator::KoaPpelasticGenerator(const Char_t* fileName) {
  iEvent     = 0;
  fFileName  = fileName;
  fInputFile = new TFile(fFileName);
  fInputTree = (TTree*) fInputFile->Get("data");
  fParticles = new TClonesArray("TParticle",100);
  fInputTree->SetBranchAddress("Particles", &fParticles);
}
// ------------------------------------------------------------------------



// -----   Destructor   ---------------------------------------------------
KoaPpelasticGenerator::~KoaPpelasticGenerator() {
  CloseInput();
}
// ------------------------------------------------------------------------



// -----   Public method ReadEvent   --------------------------------------
Bool_t KoaPpelasticGenerator::ReadEvent(FairPrimaryGenerator* primGen) {

  // Check for input file
  if ( ! fInputFile ) {
    cout << "-E KoaPpelasticGenerator: Input file nor open!" << endl;
    return kFALSE;
  }

  // Check for number of events in input file
  if ( iEvent > fInputTree->GetEntries() ) {
    cout << "-E KoaPpelasticGenerator: No more events in input file!" << endl;
    CloseInput();
    return kFALSE;
  }
  TFile  *g=gFile;
  fInputFile->cd();
  fInputTree->GetEntry(iEvent++);
  g->cd();

   // Get number of particle in TClonesrray
  Int_t nParts = fParticles->GetEntriesFast();

  // Loop over particles in TClonesArray
  for (Int_t iPart=0; iPart < nParts; iPart++) {
    TParticle* part = (TParticle*) fParticles->At(iPart);
    Int_t pdgType = part->GetPdgCode();

    // Check if particle type is known to database
    if ( ! pdgType ) {
      cout << "-W KoaPpelasticGenerator: Unknown type " << part->GetPdgCode()
	   << ", skipping particle." << endl;
      continue;
    }

    Double_t px = part->Px();
    Double_t py = part->Py();
    Double_t pz = part->Pz();

    Double_t vx = part->Vx();
    Double_t vy = part->Vy();
    Double_t vz = part->Vz();

    // Give track to PrimaryGenerator
    primGen->AddTrack(pdgType, px, py, pz, vx, vy, vz);

  }        //  Loop over particle in event

  return kTRUE;

}
// ------------------------------------------------------------------------




// -----   Private method CloseInput   ------------------------------------
void KoaPpelasticGenerator::CloseInput() {
  if ( fInputFile ) {
    cout << "-I KoaPpelasticGenerator: Closing input file " << fFileName
	 << endl;
    fInputFile->Close();
    delete fInputFile;
  }
  fInputFile = NULL;
}
// ------------------------------------------------------------------------



ClassImp(KoaPpelasticGenerator)
