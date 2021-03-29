// -------------------------------------------------------------------------
// -----              PndLmdDigiQTask header file            -----
// -----            Created 19/09/14  by A.Karavdina          -----
// -------------------------------------------------------------------------

/** PndLmdDigiQTask.h
 *@author A.Karavdina <karavdin@kph.uni-mainz.de>
 **
 ** Digi hits separation on signal and noise
 **/


#ifndef PNDLMDDIGIQTASK_H
#define PNDLMDDIGIQTASK_H


// framework includes
#include "FairTask.h"
#include "TH1.h"
#include "TMatrixD.h"
#include "TVector3.h"
#include "PndGeoHandling.h"
#include <vector>
#include <map>
#include "TDatabasePDG.h"
#include "LmdQA/PndLmdDigiQ.h"

class TClonesArray;
class PndSdsCluster;
class PndLmdGeometryHelper;

class PndLmdDigiQTask : public FairTask
{
 public:

  /** Default constructor **/  
  //  PndLmdDigiQTask();
#ifndef __CINT__
  PndLmdDigiQTask(const PndLmdDigiQTask& ) = delete;
#endif
  PndLmdDigiQTask(TString digiBranch="LMDPixelDigis");

  /** Destructor **/
  ~PndLmdDigiQTask();


  /** Virtual method Init **/
  //  virtual void SetParContainers();
  virtual InitStatus Init();


  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);
  
  virtual void Finish();
  void SetWriteMC(bool wr){fWriteAllMC = wr;}
 private:

  // Input Data ----------
  TString fDigiName;
  TClonesArray* fMCHits;
  TClonesArray* fMCTracks;
  TClonesArray* fDigis;
  /* TClonesArray* fClusters; */
  /* TClonesArray* fRecHits; */
  /* TClonesArray* fRecCandTracks; */
  /* TClonesArray* fRecTracks; */
  /* TClonesArray* fRecBPTracks; */
  /* TClonesArray* fMCHeader; */
  // Output Data -------
  TClonesArray*  fDigiQ;		
 
  int fEventNr;
// bool fUseMVDPoint;
  // Double_t fPbeam;
  // Int_t fPDGid;
  // TVector3 vtx;
  bool fWriteAllMC;
  
  PndLmdGeometryHelper &lmd_geo_helper;
  ClassDef(PndLmdDigiQTask,2);

};

#endif
