// -------------------------------------------------------------------------
// -----                 KoaPpelasticGenerator header file                  -----
// -----               Created 05/02/07  by S.Spataro                 -----
// -------------------------------------------------------------------------

/** KoaPpelasticGenerator.h
 *@author S.Spataro <stefano.spataro@exp2.physik.uni-giessen.de>
 *
 The KoaPpelasticGenerator reads the DPM output file (ROOT format)
 and inserts the tracks into the PndStack via the FairPrimaryGenerator.
 Derived from FairGenerator.
**/


#ifndef KOA_PPELASTICGENERATOR_H
#define KOA_PPELASTICGENERATOR_H


#include "FairGenerator.h"
#include "TVector3.h"
#include "TLorentzVector.h"

class TClonesArray;
class TFile;
class TTree;
class FairPrimaryGenerator;

class  KoaPpelasticGeneratorImp
{
private:
  Double_t  fPlab;
  Double_t  fTetmin;

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
  KoaPpelasticGeneratorImp();
  virtual   ~KoaPpelasticGeneratorImp()  {Reset();}

  void     SetPlab(Double_t plab) {fPlab=plab;}
  void     SetTetmin(Double_t tetmin) {fTetmin=tetmin;}

  void     GetEvent(); 
  void     Init(Double_t Plab=20., Double_t tetmin=-1.);
  Double_t  SampleInvariantT(Double_t Plab=20., Int_t Z=1);

  Double_t SampleThetaCMS(Double_t Plab=20., Int_t Z=1);


  Double_t SampleThetaLab(Double_t Plab=20., Int_t Z=1);

  Double_t CalculateParticleBeta(Double_t momentum);

  Double_t DSIG_COL(Double_t T);
  Double_t DSIG_INT(Double_t T);
  Double_t DSIG_HAD(Double_t T);

  void       Reset()        {}

  ClassDef(KoaPpelasticGeneratorImp,1)
};
 

class KoaPpelasticGenerator : public FairGenerator
{

 public: 

  /** Default constructor (should not be used) **/
  KoaPpelasticGenerator();
  KoaPpelasticGenerator(Double_t p);


  /** Standard constructor
   ** @param fileName The input (PLUTO) file name
   **/
  KoaPpelasticGenerator(const Char_t* fileName);


  /** Destructor **/
  virtual ~KoaPpelasticGenerator();


  /** Reads on event from the input file and pushes the tracks onto
   ** the stack. Abstract method in base class.
   ** @param primGen  pointer to the FairPrimaryGenerator
   **/
  virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);

  void SetStartEvent(Int_t start) { iEvent = start; };
	
 private:

  Int_t iEvent;      //! Event number
  Bool_t fFromFile;
  const Char_t* fFileName;   //! Input file name
  TFile* fInputFile;        //! Pointer to input file
  TTree* fInputTree;        //! Pointer to input tree
  TClonesArray* fParticles;  //! Particle array from PLUTO

  /** Private method CloseInput. Just for convenience. Closes the 
   ** input file properly. Called from destructor and from ReadEvent. **/
  void CloseInput();


  ClassDef(KoaPpelasticGenerator,1);

};

#endif
