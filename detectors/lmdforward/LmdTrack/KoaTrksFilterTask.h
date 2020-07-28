//-----------------------------------------------------------
//
// Description:
//      Task to filter fitted tracks based on chi2 and hits comparasion
//
// Author:
//	Anastasia Karavdina
//-----------------------------------------------------------

#ifndef KOATRKSFILTERTASK_H
#define KOATRKSFILTERTASK_H

// Base Class Headers ----------------
#include "FairTask.h"

// Collaborating Class Headers -------
#include <map>
#include "TH1.h"
#include "TH2.h"
#include "TString.h"

// Collaborating Class Declarations --
class TClonesArray;
class TGeoManager;

class KoaTrksFilterTask : public FairTask {
 public:
  // Constructors/Destructors ---------
  KoaTrksFilterTask();
#ifndef __CINT__
  KoaTrksFilterTask(const KoaTrksFilterTask&) = delete;
  KoaTrksFilterTask& operator=(const KoaTrksFilterTask&) = delete;
#endif
  virtual ~KoaTrksFilterTask();
  void SetVerboseLevel(int verbose) { verboseLevel = verbose; };
  virtual InitStatus Init();
  virtual void FinishTask();

  virtual void Exec(Option_t* opt);
  void SetSkipKinFilt(bool fl) { flSkipKinFilt = fl; };
  void SetBOXFilt(bool fl) { flBOXKinFilt = fl; };
  void SetXThFilt(bool fl) { flXThKinFilt = fl; };
  void SetYPhFilt(bool fl) { flYPhKinFilt = fl; };
  void SetDX(double dx) { fdX = dx; }
  void SetDY(double dy) { fdY = dy; }

 protected:
  int verboseLevel;
  // Input Data------------
  TClonesArray* fTrkCandArray;
  TClonesArray* fTrkArray;
  TClonesArray* fTrkOutArray;

  TString fHitName;
  TString fMCHitName;
  TString fTrkCandName;
  TString fTrkName;
  TString fTrkOutName;
  int fEventNr;
  bool flSkipKinFilt;
  bool flBOXKinFilt;
  bool flXThKinFilt;
  bool flYPhKinFilt;

  double fdX;  // beam shift in X
  double fdY;  // beam shift in Y

  ClassDef(KoaTrksFilterTask, 3);
};

#endif
