// -------------------------------------------------------------------------
// -----       PndLmdBPRungeKuttaTask header file        -----
// -----                  Created 08/04/13  by A.Karavdina    -----
// -------------------------------------------------------------------------

/** PndLmdBPRungeKuttaTask.h
 *@author A.Karavdina<karavdin@kph.uni-mainz.de>
 **
 ** Back propagation with Runge Kutta method
 **/

#ifndef PndLmdBPRungeKuttaTask_H
#define PndLmdBPRungeKuttaTask_H

// framework includes
#include <map>
#include <vector>
#include "FairTask.h"
#include "GFTrackCand.h"
#include "PndGeoHandling.h"
#include "TH1.h"
#include "TH2D.h"
#include "TMatrixD.h"
#include "TVector3.h"

class TClonesArray;
class PndSdsCluster;

class PndLmdBPRungeKuttaTask : public FairTask {
 public:
  /** Default constructor **/
  PndLmdBPRungeKuttaTask();

  /// Set up beam momuntum value and position of interaction point
  PndLmdBPRungeKuttaTask(Double_t pBeam, TVector3 IP);

  /** Destructor **/
  ~PndLmdBPRungeKuttaTask();

  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  virtual void Finish();

 private:
  /* TH1D *hxpull;  */
  /* TH1D *hypull;  */
  /* TH1D *hzpull;  */
  /* TH2D *hxresstep;  */

  TClonesArray* fTrackParGeane;
  TClonesArray* fTrackParIni;
  TClonesArray* fTrackParFinal;
  TClonesArray* fDetName;

  //  FairGeanePro* fPro;
  PndGeoHandling* fGeoH;
  int fEventNr;
  bool fUseMVDPoint;
  Double_t fPbeam;
  Int_t fPDGid;
  TVector3 vtx;

  std::map<int, std::vector<int> > fTrackPixHitIdMap;    // Track -> PixHitId
  std::map<int, std::vector<int> > fTrackStripHitIdMap;  // Track -> StripHitId

  // Input Data ----------
  TClonesArray* fMCHits;
  TClonesArray* fMCTracks;

  TClonesArray* fTracks;  // Real tracks
  TClonesArray* fHits;    // Real hits
  // Output Data -------

  void Register();

  void Reset();

  void ProduceHits();

  std::map<int, std::vector<int> > AssignHitsToTracks();
  ClassDef(PndLmdBPRungeKuttaTask, 1);
};

#endif
