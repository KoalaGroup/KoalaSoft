/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                  KoaMCTrack header file                  -----
// -----                  M. Al-Turany   June 2014                     -----
// -------------------------------------------------------------------------

/** KoaMCTrack.h
 ** Data class for storing Monte Carlo tracks processed by the KoaStack.
 ** A KoaMCTrack can be a primary track put into the simulation or a
 ** secondary one produced by the transport through decay or interaction.
 **/

#ifndef KoaMCTrack_H
#define KoaMCTrack_H 1

#include "TObject.h"         // for TObject
#include "KoaDetectorList.h" // for DetectorId
#include "Rtypes.h"          // for Double_t, Int_t, Double32_t, etc
#include "TLorentzVector.h"  // for TLorentzVector
#include "TMath.h"           // for Sqrt
#include "TVector3.h"        // for TVector3

class TParticle;

class KoaMCTrack : public TObject
{

public:
  /**  Default constructor  **/
  KoaMCTrack();

  // /**  Standard constructor  **/
  // KoaMCTrack(Int_t pdgCode, Int_t motherID, Double_t px, Double_t py,
  //             Double_t pz, Double_t x, Double_t y, Double_t z,
  //             Double_t t, Int_t nPoints);

  /**  Copy constructor  **/
  KoaMCTrack(const KoaMCTrack &track);

  /**  Constructor from TParticle  **/
  KoaMCTrack(TParticle *particle);

  /**  Destructor  **/
  virtual ~KoaMCTrack() = default;

  /**  Output to screen  **/
  void Print(Int_t iTrack = 0) const;

  /**  Accessors  **/
  Int_t GetPdgCode() const { return fPdgCode; }
  Int_t GetMotherId() const { return fMotherId; }
  Double_t GetPx() const { return fPx; }
  Double_t GetPy() const { return fPy; }
  Double_t GetPz() const { return fPz; }
  Double_t GetStartX() const { return fStartX; }
  Double_t GetStartY() const { return fStartY; }
  Double_t GetStartZ() const { return fStartZ; }
  Double_t GetStartT() const { return fStartT; }
  Double_t GetMass() const;
  // Double_t GetEnergy() const {return fE;};
  Double_t GetE() const { return fE; };
  Double_t GetPt() const { return TMath::Sqrt(fPx * fPx + fPy * fPy); }
  Double_t GetP() const { return TMath::Sqrt(fPx * fPx + fPy * fPy + fPz * fPz); }
  Double_t GetRapidity() const;
  TVector3 GetMomentum() const { return TVector3(fPx, fPy, fPz); }
  TLorentzVector Get4Momentum() const;
  TVector3 GetStartVertex() const;

  /** Accessors to the number of MCPoints in the detectors **/
  // Int_t GetNPoints(DetectorId detId) const;

  /**  Modifiers  **/
  void SetMotherId(Int_t id) { fMotherId = id; }
  // void SetNPoints(Int_t iDet, Int_t np);

private:
  /**  PDG particle code  **/
  Int_t fPdgCode;

  /**  Index of mother track. -1 for primary particles.  **/
  Int_t fMotherId;

  /** Momentum components at start vertex [GeV]  **/
  Double32_t fPx, fPy, fPz, fE;

  /** Coordinates of start vertex [cm, ns]  **/
  Double32_t fStartX, fStartY, fStartZ, fStartT;

  ClassDef(KoaMCTrack, 2);
};

// ==========   Inline functions   ========================================

inline TLorentzVector KoaMCTrack::Get4Momentum() const
{
  return TLorentzVector(fPx, fPy, fPz, fE);
}

inline TVector3 KoaMCTrack::GetStartVertex() const
{
  return TVector3(fStartX, fStartY, fStartZ);
}

#endif
