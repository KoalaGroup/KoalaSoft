//-----------------------------------------------------------
//
// Description:
//      Task to show the origin of detectect Events on the IP-plan
//      Should not be placed in the script for the queue 
//
// Author:
//	Jens Olaf Frech
//-----------------------------------------------------------

#ifndef KOAIPVIS_H
#define KOAIPVIS_H

// Base Class Headers ----------------
#include "FairTask.h"

// Collaborating Class Headers -------
#include <map>
#include "TH1.h"
#include "TH2.h"
#include "TString.h"
#include <TCanvas.h>

// Collaborating Class Declarations --
class TClonesArray;
class TGeoManager;

class KoaIPvis : public FairTask {
 public:
  // Constructors/Destructors ---------
  KoaIPvis();
#ifndef __CINT__
  KoaIPvis(const KoaIPvis&) = delete;
  KoaIPvis& operator=(const KoaIPvis&) = delete;
#endif
  virtual ~KoaIPvis();
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

   TH2F hIPBackProp;
   TH1F hIPBPresi;
   TH1F hIPresix;
   TH1F hIPresiy;
   TH1F hIPresiz;



 ClassDef(KoaIPvis, 3);
};

#endif
