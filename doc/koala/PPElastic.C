//This script is for Proton-Pronton Elastic Scattering Event Generation for Koala experiment in Panda
//The script was developped by Aida. And this is a backup of the original script. The function in this file needs to be integrated in KoaSoft later, as a FairGenerator.
#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TSystem.h>
#include <TMath.h>
#include <time.h>
#include <TRandom.h>
#include <TNtuple.h>
#include <TNamed.h>
#include <TF1.h>
#include <TFile.h>
#include <TObjArray.h>
#include <TString.h>
#include <TEllipse.h>
#include <TClonesArray.h>
#include <TTree.h>
#include <TStopwatch.h>
#include <TParticle.h>
#include <TH2.h>
#include <TGraph.h>
#include <TPad.h>
#include <TVector3.h>
#endif

#ifndef _ppelast_
#if !defined(__CINT__) || defined(__MAKECINT__)
#define _ppelast_
#endif

//--------------------------------------------------------------------------
void runAndSaveTree(Int_t n,                      
                     Double_t Plab=2., Double_t tetmin=-1., 
                     const char *fname="PPelast.root");

//---------------------------------------------------------------------------
class  PPElastic
{
   private:
  TTree *fnt;                    //Tree for results
  Double_t   fTetaCMS;        //  sampled Theta in CMS
  Double_t  fThetaLab;        //sampled Theta in Lab system
  Double_t   fBeta;         // velosity of projectile 


  Double_t  fT;          // T invariant 
  Double_t  fRa;         // Radius of target 
  Double_t fRef;        // Effective radiuse for Calculation of hadron cross-section
  Double_t fceff;       // Effective diffuse parameter  
  Double_t rho;        //ratio of real to imaginary parts of elastic amplitude
  Double_t  Mn;        //mass of nucleon
  TVector3   fbst;          // boost vector
  TLorentzVector   fvect;  //4-vector of produced particle (px,py,pz,E)  
  Double_t           fTmax;          
  Double_t           cs_tot;           //pp - XS_total
  Double_t           cs_el;             //pp - XS_elastic 
  Double_t   Pcms;         // momentum of projectile in CMS system
  Double_t   S;            //  Energy in CMS system
  Double_t   Ecms;         // Energy of 1 proton in CMS system
  Double_t SqrtS;         // sqrt of S
  Double_t Vcms;          // velosity in CMS system 
  Double_t Gamma;         // gamma factor in CMS system

  Double_t  prob_col;  // probability of Coulomb part
  Double_t  prob_int;  // probability of Interf part
  Double_t  prob_had;  // probability of hadron part 

  Double_t  aelm;
  Double_t  sigma_tot;
  Double_t  B;  
  Double_t A1;
  Double_t A2;
  Double_t Fun_inv[300000];
  Int_t fNdiv;  
  Double_t fdto;
  Double_t fTmin; 

public:
PPElastic();
virtual   ~PPElastic()  {Reset();}

void     Run(Double_t Plab=20., Int_t nevents=100, Double_t tetmin=-1.); 
void     Init(Double_t Plab=20., Double_t tetmin=-1.);
Double_t  SampleInvariantT(Double_t Plab=20., Int_t Z=1);

Double_t SampleThetaCMS(Double_t Plab=20., Int_t Z=1);


Double_t SampleThetaLab(Double_t Plab=20., Int_t Z=1);

Double_t CalculateParticleBeta(Double_t momentum);

 
 Double_t DSIG_COL(Double_t T);
 Double_t DSIG_INT(Double_t T);
 Double_t DSIG_HAD(Double_t T); 

  TTree*     GetTree()       const{return fnt;}
  void       Reset()        {delete fnt; fnt=0; }
  void  dSdTDraw(Double_t Plab);                   



ClassDef(PPElastic,1)
};
 
//------------------------------------------------------------------------------------

void runAndSaveTree(Int_t n, Double_t Plab, Double_t tetmin, const char *fname)
{
PPElastic *pp = new PPElastic();
   TStopwatch timer;                        // time loop
   timer.Start();

   TFile out(fname,"recreate","ROOT_Tree",9);
pp->Run(Plab, n, tetmin);
TTree* fTree = pp->GetTree(); 

   if(fTree) fTree->Write();
   out.Close();

  timer.Stop();
 cout << " ----- Realtime: "<<timer.RealTime()<<"sec"<<endl;
 cout << " ----- Cputime:  "<<timer.CpuTime()<<"sec"<<endl;

}

//--------------------------------------------------------------------------------
ClassImp(PPElastic)
//--------------------------------------------------------------------------------

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
//---------------------------------------------------------------------------
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

Double_t PPElastic::DSIG_HAD(Double_t T)
{
 Double_t  U, dShad;
 U=fTmax-T;
 Double_t ImHad, ReHad;  //Imaginary and real parts of el_hadron Amplitude
 ImHad= exp(B*T/2.)+exp(B*U/2.);
 ReHad=-A2 ;
 dShad = A1*ImHad*ImHad+ReHad*ReHad ;
 return dShad;
}
////////////////////////////////////////////////////////////

Double_t PPElastic::DSIG_COL(Double_t T)
{
Double_t G4, pkoef, dScol; 
     G4=pow((1+fabs(T)/0.71),-8); 
      pkoef= 10./(5.0677*5.0677);        //10.
      dScol=4*3.1416*aelm*aelm*G4*pkoef/((fBeta * T)*(fBeta*T));
   return dScol;
}
///////////////////////////////////////////////////////////

Double_t PPElastic::DSIG_INT(Double_t T)
{
 Double_t G2, delT, dSint;
    G2=pow((1+fabs(T)/0.71),-4);
      delT=aelm*(0.577+log(B*fabs(T)/2.+ 4*fabs(T)/0.71)+
       4.*fabs(T)/0.71*log(4.*fabs(T)/0.71)+2.*fabs(T)/0.71);
      dSint=aelm*sigma_tot*G2*exp(0.5*B*T)*
     (rho*cos(delT) + sin(delT))/fBeta/fabs(T) ;  /////// -  ->  + sin
 return dSint;
}
////////////////////////////////////////////////////////////


Double_t PPElastic::SampleInvariantT(Double_t Plab, Int_t Z)
{
Double_t  T;
Double_t Ksi = gRandom->Rndm();

Int_t iS=0;
Int_t iE=fNdiv-1;
Int_t i;  
do 
 { i= (iS+iE)/2; 
   Bool_t left=((Fun_inv[iS]- Ksi)*(Fun_inv[i]- Ksi))<0.;
   if(left) {iE=i;}
   else     {iS=i;}
 } while((iS+1)!=iE);

Double_t Tl, Tm, Yl, Ym;

 Tl=fTmin + iS*fdto;
 Tm=fTmin + iE*fdto;
 Yl=Fun_inv[iS];
 Ym=Fun_inv[iE];
 T=Tl+(Tm-Tl)*(Ksi-Yl)/(Ym-Yl);
 
 fT=T;

Double_t cosTet=1.0+T/(2.*Pcms*Pcms);
if(cosTet >  1.0 ) cosTet= 1.;  
if(cosTet < -1.0 ) cosTet=-1.; 
fTetaCMS=acos(cosTet);

//cout<<" fTmin "<<fTmin<<" fTmax "<<fTmax<<" T " <<T<< " teta_cms " << fTetaCMS*180./3.1416 <<endl;

 return T;
}



///////////////////////////////////////////////////////////////////////
// calculation of Theta in CMS system   /////////////////////
Double_t PPElastic::SampleThetaCMS(Double_t plab, Int_t Z)
{
 Double_t T;
 T =  SampleInvariantT(plab,  Z);

 // NaN finder
if(!(T < 0.0 || T >= 0.0))
{
cout << "Elastic:WARNING: mom= " << plab<< " S-wave will be sampled"<<endl; 
  T=  gRandom->Rndm()*fTmax;
}
 if(Pcms > 0.) 
 {
   Double_t cosTet=1.0+T/(2.*Pcms*Pcms);
   if(cosTet >  1.0 ) cosTet= 1.;   
   if(cosTet < -1.0 ) cosTet=-1.;    
   fTetaCMS=acos(cosTet);   
   return  fTetaCMS;
  } else  
    {  
      return 2.*gRandom->Rndm() - 1.; 
    }
 }
///////////////////////////////////////////////////////////////////////////
//     Sample of Theta in Lab System
Double_t PPElastic::SampleThetaLab(Double_t plab, Int_t Z)
{
 Double_t T;
 T =  SampleInvariantT(plab,  Z);
 // NaN finder
if(!(T < 0.0 || T >= 0.0))
{
cout << "Elastic:WARNING: mom= " << plab<< " S-wave will be sampled"<<endl; 
  T=  gRandom->Rndm()*fTmax;
}
  Double_t phi  = gRandom->Rndm()*TMath::TwoPi( ); 
  Double_t cost(1.);  
  if(fTmax < 0.) {cost = 1. - 2.0*T/fTmax;}   //> --> <
  Double_t sint;
   if( cost >= 1.0 )
     {  
        cost = 1.0;
        sint =  0.0;
     }
  else if( cost <= -1.0)
   {
     cost = -1.0;
     sint = 0.0;
  }
 else
  {
    sint = sqrt((1.0-cost)*(1.0+cost));
  }
 TVector3 v(sint*cos(phi), sint*sin(phi), cost);
 v*=Pcms;  

TLorentzVector nlv(v.X(),v.Y(),v.Z(),sqrt(Pcms*Pcms + Mn*Mn));

nlv.Boost(fbst);

TVector3 np = nlv.Vect(); 
TLorentzVector part(np.X(), np.Y(), np.Z(),sqrt(Mn*Mn+ np.Mag2()));
fvect = part;
Double_t theta = np.Theta();

 fThetaLab = theta;

  return theta;
}


/////////////////////////////////////////////////////////////////////
//  Calculation of particle velocity Beta
Double_t PPElastic::CalculateParticleBeta(Double_t  momentum )
/*
{
 Double_t mass = 0.938;
 Double_t a    = momentum/mass;
  fBeta         = a/sqrt(1+a*a);
return fBeta ;
}
*/

{
 Double_t mass = 0.938;
 Double_t Elab=sqrt(mass*mass+momentum*momentum);
 Double_t S=2.*mass*mass + 2.*mass*Elab;
 Double_t Ecms=sqrt(S)/2.;                 // Energy of projectile in CMS
 Double_t Pcms=sqrt(Ecms*Ecms-mass*mass);  // Momentum of projectile in CMS

 fBeta=Pcms/Ecms;

 return fBeta;
}


///////////////////////////////////////////////////////////////////////
 void PPElastic::Run(Double_t Plab, Int_t nevents, Double_t tetmin)
{
 Int_t   Ieven,  i, npart, Id;
 Double_t px[2],py[2],pz[2],E[2]; 
 Double_t tet=0;
 Double_t weight = 1.0;
 Double_t tinv=0;
 Double_t tinv1=0;
 
 Int_t activeCnt=0;
 
   if (fnt == 0) {
      fnt =  new TTree("data","elasticPP");
// fnt->SetDirectory(0); 
   }
  
 TClonesArray* fEvt;

 fEvt=new TClonesArray("TParticle",100);
 fnt->Branch("Npart",&activeCnt,"Npart/I");
 fnt->Branch("Weigth",&weight,"Weight/D");
 fnt->Branch("Tinv",&tinv,"Tinv/D");
 fnt->Branch("Tinv1",&tinv1,"Tinv1/D");
 fnt->Branch("Particles",&fEvt, 32000,99);

 TLorentzVector Mom; 
 TLorentzVector V(0,0,0,0);

 Init(Plab, tetmin);

 
for(Ieven = 1; Ieven <= nevents; ++Ieven) {
   if( (Ieven%100) == 0 ) 
   std::cout << "Event number = " << Ieven << std::endl; 
   fEvt->Clear();
   Int_t cnt = 0;

 tet=SampleThetaLab(Plab, 1);
  tinv=fabs(fT);
  
  tinv1=fabs(fTmax-fT);
    
 px[0]=fvect.X();
 px[1]=-fvect.X();
 py[0]=fvect.Y();
 py[1]=-fvect.Y(); 
 pz[0]=fvect.Z();
 pz[1]=Plab-fvect.Z();
 E[0]=fvect.E();
 E[1]=sqrt(Plab*Plab+Mn*Mn)+Mn-E[0];

 // px[0], py[0], pz[0] momentum of "forward going" proton
 // px[1], py[1], pz[1] momentum of recoil proton
//  Double_t pt=sqrt(px[0]*px[0]+py[0]*py[0]);
// cout<<" X "<<px[0]<<" Y  "<<py[0]<<" Z  "<< pz[0]<<" E "<< E[0]<<endl;
// cout<<"  Pt  " <<pt<<endl;

  Id=2212;
   npart=2;

   for (i= 0; i< npart; ++i) 
 {       
 Mom.SetPxPyPzE(px[i],py[i],pz[i],E[i]);

  TParticle   fparticle(Id,1,0,0,0,0, Mom, V);
  new((*fEvt)[cnt++]) TParticle(fparticle); 
 }
   activeCnt = cnt;
   fnt->Fill();                     
 } 

 cout<<"elastic cross section mb "<<cs_el<<" sigma_total " <<sigma_tot<< endl;
 cout << endl << "Done!" << endl;
}
//////////////////////////////////////////

void PPElastic::dSdTDraw(Double_t Plab) {
//method to direct Draw of hadronic dS/dT
//Double_t S=1.76+1.88*sqrt(0.88+Plab*Plab);

Double_t T[101], dSdT[101], Q;
 Init(Plab, -1);
 Int_t n=20;
for(Int_t I=0; I<n; I++)
{ T[I]=-0.1*I;
  Q= T[I];
 if(Q<fTmax)break; 
  dSdT[I]= DSIG_HAD(Q);

  cout<<T[I]<<"  "<<dSdT[I]<<endl; }

TGraph *gr1 = new TGraph(n,T,dSdT);
gr1->SetMarkerColor(4);
gr1->SetLineColor(4);
gr1->SetMarkerStyle(22);
gr1->SetLineWidth(2);
gr1->SetTitle("dS/dT");
gr1->Draw("APL");
gPad->SetLogy();
//
}
///////////////////////////////////////////////////////////////////
#endif

