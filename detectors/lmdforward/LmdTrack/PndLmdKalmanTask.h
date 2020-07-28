//-----------------------------------------------------------
// File and Version Information:
// $Id$
//
// Description:
//      Kalman Filter Task
//
// Environment:
//      Software developed for the PANDA Detector at FAIR.
//
// Author List:
//      Sebastian Neubert    TUM            (original author)
//      Ralf Kliemt, TU Dresden             (Copied for MVD use)
//      Anastasia Karavdina, Uni Mainz      (Copied for Lmd use)
//-----------------------------------------------------------

#ifndef PNDLMDKALMANTASK_H
#define PNDLMDKALMANTASK_H

// Base Class Headers ----------------
#include "FairTask.h"

// Collaborating Class Headers -------
#include <map>
#include "FairGeanePro.h"
#include "GFFieldManager.h"
#include "GFTrack.h"
#include "PndGeoHandling.h"
#include "PndLinTrack.h"
#include "TMatrixD.h"
#include "TString.h"

// Collaborating Class Declarations --
class TClonesArray;
class GFRecoHitFactory;
class TH1D;
class TGeoManager;

class PndLmdKalmanTask : public FairTask {
 public:
  // Constructors/Destructors ---------
  PndLmdKalmanTask();
  PndLmdKalmanTask(TString HitBranch, TString TrackBranch);
  virtual ~PndLmdKalmanTask();

  // Operators

  // Accessors -----------------------

  // Modifiers -----------------------
  void SetTrackBranchName(const TString& name) { fTrackBranchName = name; }
  void SetPersistence(Bool_t opt = kTRUE) { fPersistence = opt; }

  void SetGeaneTrkRep(Bool_t val = kTRUE) { flGEANE = val; }
  void SetRKTrkRep(Bool_t val = kTRUE) { flRK = val; }

  void SetScalePError(double sc) { fscaleP = sc; }
  void SetScaleMError(double sc) { fscaleM = sc; }
  // Operations ----------------------

  virtual InitStatus Init();

  virtual void Exec(Option_t* opt);
  virtual void SetFilterFlag(bool val) { flagFilter = val; };
  // void WriteHistograms(const TString& filename);

 private:
  bool flGEANE;  // if true use GEANE representation
  bool flRK;     // if true use Runge-Kutta representation

  double fscaleP;  // scale factor for test initial Position errors
  double fscaleM;  // scale factor for test initial Momentum errors
  /* TH1D *hxpull; */
  /* TH1D *hypull; */
  /* TH1D *hzpull; */
  /* TH1D *hpxpull; */
  /* TH1D *hpypull; */
  /* TH1D *hpzpull; */

  // Private Data Members ------------
  TClonesArray* fTrackArray;
  // TClonesArray* fGFTrackArray;
  TClonesArray* fTrackTmpArray;
  TClonesArray* fTrkOutArray;
  TClonesArray* fTrackParFinal;
  TClonesArray* fSdsHitsArray;
  TString fTrackBranchName;
  TString fSdsHitBranchName;
  Bool_t fPersistence;

  GFRecoHitFactory* fTheRecoHitFactory;
  PndGeoHandling* fGeoH;

  /* TH1D* fPH; // momentum histo; */
  /* TH1D* fChi2H; // chi2 histo; */
  /* TH1D* fMassV0; // chi2 histo; */
  /* TH1D* fMassETAC; // chi2 histo; */
  /* TH1D* fMasses; // all particle histo; */

  Int_t fTrackcount;

  Int_t fEvent;
  TGeant3* gMC3;
  FairGeanePro* fPro;
  int fsensType;    // 0=strips sensors, 1=Pixel sensors
  Double_t fPbeam;  // beam momentum
  Int_t fPDGCode;
  Double_t fCharge;
  // PndLinTrack* GenfitTrack2PndLinTrack(const GFTrack* tr);
  GFFieldManager* gfMagField;
  bool flagFilter;

  // public:
  ClassDef(PndLmdKalmanTask, 1);
};

#endif

//--------------------------------------------------------------
// $Log$
//--------------------------------------------------------------
