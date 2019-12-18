/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                     KoaPPElasticIdealGenerator source file                 -----
// -------------------------------------------------------------------------


#include "KoaPPElasticIdealGenerator.h"
#include "TRandom.h"
#include "TMath.h"
#include "Math/Vector4D.h"
#include "FairLogger.h"
#include "FairPrimaryGenerator.h"

using namespace ROOT::Math;

// -----   Default constructor   -------------------------------------------
KoaPPElasticIdealGenerator::KoaPPElasticIdealGenerator()
  : FairGenerator(), fMass(0.938272081), fP(2.8),
    fAlphaMin(0.), fAlphaMax(90.),
    fPhiMin(90.), fPhiMax(270),
    fIsGeantino(kFALSE)
{ Init(); }
// -------------------------------------------------------------------------



// -----   Constructor with name and title   -------------------------------
KoaPPElasticIdealGenerator::KoaPPElasticIdealGenerator(Double_t mom, Bool_t isGeantino)
  : FairGenerator(), fMass(0.938272081), fP(mom),
    fAlphaMin(0.), fAlphaMax(90.),
    fPhiMin(90.), fPhiMax(270),
    fIsGeantino(isGeantino)
{ Init(); }
// -------------------------------------------------------------------------


// -----   Copy constructor ------------------------------------------------
KoaPPElasticIdealGenerator::KoaPPElasticIdealGenerator(const KoaPPElasticIdealGenerator& rhs)
  : FairGenerator(rhs) {
  fMass = rhs.fMass;
  fP    = rhs.fP;
  fAlphaMin = rhs.fAlphaMin;
  fAlphaMax = rhs.fAlphaMax;
  fPhiMin   = rhs.fPhiMin;
  fPhiMax   = rhs.fPhiMax;
  fKappa    = rhs.fKappa;
  fIsGeantino = rhs.fIsGeantino;
}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
KoaPPElasticIdealGenerator::~KoaPPElasticIdealGenerator() { }
// -------------------------------------------------------------------------

// -----   Assignment   ----------------------------------------------------
KoaPPElasticIdealGenerator& KoaPPElasticIdealGenerator::operator= (const KoaPPElasticIdealGenerator& rhs)
{
  // check assignment to self
  if (this == &rhs) return *this;

  // base class assignment
  FairGenerator::operator=(rhs);

  //
  fMass = rhs.fMass;
  fP    = rhs.fP;
  fAlphaMin = rhs.fAlphaMin;
  fAlphaMax = rhs.fAlphaMax;
  fPhiMin   = rhs.fPhiMin;
  fPhiMax   = rhs.fPhiMax;
  fKappa    = rhs.fKappa;
  fIsGeantino = rhs.fIsGeantino;

  return *this;
}

// -----   Init   ---------------------------------------------
Bool_t KoaPPElasticIdealGenerator::Init()
{
  PxPyPzMVector beam(0,0,fP,fMass);
  fKappa = (beam.energy()+beam.mass())/(beam.energy()-beam.mass());

  // checking
  if(fPhiMax-fPhiMin>360){
    LOG(fatal) << "KoaPPElasticIdealGenerator: phi range is too wide, shoule be 0<phi<360";
  }
  if(fAlphaMin<0 || fAlphaMin>90 || fAlphaMax<0 || fAlphaMax>90){
    LOG(fatal) << "KoaPPElasticIdealGenerator: alpha range is too wide, shoule be 0<alpha<90";
  }

  return true;
}

// -----   ReadEvent   ---------------------------------------------
Bool_t KoaPPElasticIdealGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{
  Double_t alpha, phi;
  alpha = gRandom->Uniform(fAlphaMin, fAlphaMax) * TMath::DegToRad();
  phi = gRandom->Uniform(fPhiMin, fPhiMax) * TMath::DegToRad();

  // 
  Calculate(alpha, phi);

  //
  Int_t pdgid = 2212;
  if ( fIsGeantino ) {
    pdgid = 0;
  }

  primGen->AddTrack(pdgid, fRecoilPx, fRecoilPy, fRecoilPz, 0, 0, 0); // recoil proton
  primGen->AddTrack(pdgid, fScatPx, fScatPy, fScatPz, 0, 0, 0); // scattered proton

  return true;
}

// -----   calculate the energy   ---------------------------------------------
void KoaPPElasticIdealGenerator::Calculate(Double_t alpha, Double_t phi)
{
  // 
  Double_t sin_alpha = TMath::Sin(alpha);
  Double_t recoil_etot = 2*fMass*sin_alpha*sin_alpha/(fKappa - sin_alpha*sin_alpha) + fMass;
  Double_t recoil_mom  = TMath::Sqrt(recoil_etot*recoil_etot - fMass*fMass);

  //
  fRecoilPz = recoil_mom * sin_alpha;
  Double_t Pt = recoil_mom * TMath::Cos(alpha);
  fRecoilPx = Pt * TMath::Cos(phi);
  fRecoilPy = Pt * TMath::Sin(phi);

  //
  PxPyPzMVector beam(0,0,fP,fMass);
  PxPyPzMVector target(0,0,0,fMass);
  PxPyPzMVector recoil(fRecoilPx, fRecoilPy, fRecoilPz, fMass);
  PxPyPzMVector scat = beam + target - recoil;
  fScatPx = scat.Px();
  fScatPy = scat.Py();
  fScatPz = scat.Pz();
  
  return;
}

// -----   Clone this object   ---------------------------------------------
KoaPPElasticIdealGenerator* KoaPPElasticIdealGenerator::CloneGenerator() const
{
  Fatal("CloneGenerator","Has to be overriden in multi-threading applications.");
  return 0;
}

ClassImp(KoaPPElasticIdealGenerator)
