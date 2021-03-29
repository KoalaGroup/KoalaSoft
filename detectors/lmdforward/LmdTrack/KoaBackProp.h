//-----------------------------------------------------------
//
// Description:
//      Task to cut backgroundevents by backpropagating hit in the lumi detector to the z=0 plane 
//
// Author:
//	Jens Olaf Frech
//-----------------------------------------------------------

#ifndef KOABACKPROP_H
#define KOABACKPROP_H

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

class KoaBackProp : public FairTask {
 public:
  // Constructors/Destructors ---------
  KoaBackProp();
#ifndef __CINT__
  KoaBackProp(const KoaBackProp&) = delete;
  KoaBackProp& operator=(const KoaBackProp&) = delete;
#endif
  virtual ~KoaBackProp();
  void SetVerboseLevel(int verbose) { verboseLevel = verbose; };
  virtual InitStatus Init();
  virtual void FinishTask();
  
  virtual void Exec(Option_t* opt);
  
  
 protected:
  int verboseLevel;
  
  TClonesArray* fTrkCandArray;
  TClonesArray* fTrkArray;
  TClonesArray* fMCArray;
  TClonesArray* fTrkOutArray;
  
  TString fHitName;
  TString fMCHitName;
  TString fTrkCandName;
  TString fTrkName;
  TString fTrkOutName;
  int fEventNr;




 ClassDef(KoaBackProp, 3);
};

#endif
