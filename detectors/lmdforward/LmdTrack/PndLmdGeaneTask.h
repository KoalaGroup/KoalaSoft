// -------------------------------------------------------------------------
// -----                   PndLmdGeaneTask header file                 -----
// -----                  Created 20/03/07  by R.Kliemt                -----
// -----                  modified for Lmd by M. Michel & A.Karavdina  -----
// -------------------------------------------------------------------------

/** PndLmdGeaneTask.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Displays all available informations for a given event
 **/

#ifndef PndLmdGeaneTask_H
#define PndLmdGeaneTask_H

// framework includes
#include "FairTask.h"
#include "TH1.h"
//#include "GFTrackCand.h"
#include "FairGeanePro.h"
#include "FairTrackParP.h"
#include "TMatrixD.h"
#include "TNtuple.h"
#include "TVector3.h"
//#include "PndSdsGeoHandling.h"
#include <map>
#include <vector>
#include "PndGeoHandling.h"
class TClonesArray;
class PndSdsCluster;
// class TGeant3;//GEANE uses Geant3!
// class TGeant4;

class PndLmdGeaneTask : public FairTask {
 public:
  /** Default constructor **/
  PndLmdGeaneTask();

  /// Set up beam momuntum value and position of interaction point
  PndLmdGeaneTask(Double_t pBeam, TVector3 IP, bool is_prefiltered = true);

  /** Destructor **/
  ~PndLmdGeaneTask();

  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  virtual void Finish();

  FairTrackParP* PropToPlane(FairTrackParP* fStartPst, double zpos, int dir,
                             bool& isProp);  // propagation between planes
 private:
  FairGeanePro* fPro;
  PndGeoHandling* fGeoH;
  int fEventNr;
  bool fUseMVDPoint;
  Double_t fPbeam;
  Int_t fPDGid;
  TVector3 vtx;
  FairField* pndField;
  std::map<int, std::vector<int> > fTrackPixHitIdMap;    // Track -> PixHitId
  std::map<int, std::vector<int> > fTrackStripHitIdMap;  // Track -> StripHitId

  std::string track_branch_name;

  // Input Data ----------
  TClonesArray* fTracks;  // Real tracks

  // Output Data -------
  TClonesArray* fTrackParGeane;
  TClonesArray* fTrackParIni;
  TClonesArray* fTrackParFinal;
  TClonesArray* fDetName;

  //----------------------------------------

  void Register();

  void Reset();

  void ProduceHits();

  ClassDef(PndLmdGeaneTask, 2);
};

#endif
