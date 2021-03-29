// -------------------------------------------------------------------------
// -----                      PndLmdTrackFinderTask                    -----
// -----                  Created 22/10/09  by M. Michel               -----
// -------------------------------------------------------------------------

#ifndef PNDLMDTRACKFINDERTASK_H
#define PNDLMDTRACKFINDERTASK_H

#include "FairTask.h"
#include "KoaMCTrack.h"
#include "PndSdsClusterPixel.h"
#include "PndSdsGeoPar.h"
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "TrackData/PndTrackCand.h"

#include <string>
#include <utility>
#include <vector>

class TClonesArray;

class PndLmdTrackFinderTask : public FairTask {
 public:
  /** Default constructor **/
  PndLmdTrackFinderTask(Int_t inFinderMode = 0,
                        TString hitBranch = "LMDHitsPixel",
                        Int_t innSensPP = 8);
  /** Destructor **/
  virtual ~PndLmdTrackFinderTask();

  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();
  virtual InitStatus ReInit();

  /** Virtual method Exec **/
  virtual void Exec(Option_t *opt);

  void SetVerbose(Int_t verbose) { fVerbose = verbose; };
  void SetInaccuracy(Double_t accu) { dXY = accu; };
  void SetSensStripFlag(bool fS) { flagStipSens = fS; };
  void SetSensPixelFlag(bool fS) { flagPixelSens = fS; };

 private:
  bool flagStipSens;
  bool flagPixelSens;
  Double_t dXY;
  Int_t fFinderMode;
  Int_t nSensPP;

  //    std::vector<Int_t> GetHitPerCluster(PndSdsClusterPixel* clusterCand);
  Double_t GetTrackDip(KoaMCTrack *myTrack);
  Double_t GetTrackCurvature(KoaMCTrack *myTrack);

  TString fHitBranchPixel;

  /** Input array of PndSdsDigis **/
  TClonesArray *fPixelHitArray;

  /** Output array of PndSdsHits **/
  TClonesArray *fTrackCandArray;

  void Register();
  void Reset();
  void ProduceHits();

  bool SortHitsByZ(std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                   Int_t nPixelHits);
  bool SortHitsByDet(std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                     Int_t nPixelHits);
  bool SortHitsByDet2(std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                      Int_t nPixelHits);  // uses PndLmdDim
  void FindHitsI(std::vector<PndTrackCand> &tofill,
                 std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                 Int_t nPixelHits);
  void FindHitsII(std::vector<PndTrackCand> &tofill,
                  std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                  Int_t nPixelHits);
  void FindHitsIII(std::vector<PndTrackCand> &tofill,
                   std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                   Int_t nPixelHits);

  ClassDef(PndLmdTrackFinderTask, 2);
};

#endif /* PndLmdTrackFinderTASK_H */
