
// -------------------------------------------------------------------------
// -----                  KoaHitMergeTask source file               -----
// -------------------------------------------------------------------------

#include <cmath>
#include <map>
#include <vector>

#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "TClonesArray.h"

#include "KoaHitMergeTask.h"
#include "PndSdsHit.h"
#include "PndSdsMergedHit.h"

#include "TH2D.h"

// -----   Default constructor   -------------------------------------------
KoaHitMergeTask::KoaHitMergeTask()
    : FairTask("KOALA Hit Merging Task"), fHitArray(0), fMergedHitArray(0) {
  fHitBranchName = "KOALAHitsPixel";
  hdxdy = new TH2D("hdxdy", "; #deltax, #mum; #deltay, #mum", 4e2, -100, 100,
                   4e2, -100, 100);
  hdz = new TH1D("hdz", ";#deltaz, #mum", 2e3, -1000, 1000);
}

// -----   Named constructor   -------------------------------------------
KoaHitMergeTask::KoaHitMergeTask(const char* name)
    : FairTask(name), fHitArray(0), fMergedHitArray(0) {
  fHitBranchName = "KOALAHitsPixel";
  hdxdy = new TH2D("hdxdy", "; #deltax, #mum; #deltay, #mum", 4e2, -100, 100,
                   4e2, -100, 100);
  hdz = new TH1D("hdz", ";#deltaz, #mum", 2e3, -1000, 1000);
}

// -----   Destructor   ----------------------------------------------------
KoaHitMergeTask::~KoaHitMergeTask() {}
// -------------------------------------------------------------------------

// -----   Public method Init   --------------------------------------------
InitStatus KoaHitMergeTask::Init() {
  FairRootManager* kioman = FairRootManager::Instance();
  if (!kioman) {
    std::cout << "-E- KoaHitMergeTask::Init: "
              << "RootManager not instantiated!" << std::endl;
    return kFATAL;
  }

  // Get input array
  fHitArray = (TClonesArray*)kioman->GetObject(fHitBranchName);
  //
  if (!fHitArray) {
    std::cout << "-W- KoaHitMergeTask::Init: "
              << "No LmdHitsPixel array!" << std::endl;
    return kERROR;
  }

  // set output arrays
  // fMergedHitArray = new TClonesArray("PndSdsHit");
  fMergedHitArray = new TClonesArray("PndSdsMergedHit");
  kioman->Register("KOALAHitsMerged", "Koa", fMergedHitArray, true);
  Info("Init", "Initialisation successfull");
  return kSUCCESS;
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void KoaHitMergeTask::Exec(Option_t*) {
  if (fVerbose > 2)
    std::cout << " **Starting KoaHitMergeTask::Exec()**" << std::endl;

  // Reset output array
  // fMergedHitArray = FairRootManager::Instance()->GetTClonesArray("LmdHits");
  // if ( ! fMergedHitArray ) Fatal("Exec", "No OutputArray");
  fMergedHitArray->Delete();

  // Get input array
  fHitArray =
      (TClonesArray*)FairRootManager::Instance()->GetObject(fHitBranchName);
  if (!fHitArray) {
    std::cout << "-W- KoaHitMergeTask::Init: "
              << "No Hit array!" << std::endl;
    return;
  }

  // when we have no hits, we can end the event here.
  if (fHitArray->GetEntriesFast() == 0) return;

  // -------   SEARCH Close Hits  ------
  std::vector<unsigned int> mergewithIDs, mergedHits;
  // std::map<unsigned int, std::vector<unsigned int>> backmap;
  //  PndSdsHit* tmphit;
  PndSdsMergedHit* tmphit;
  unsigned int newHits = 0;
  for (Int_t iHit = 0; iHit < fHitArray->GetEntriesFast(); iHit++) {
    if (fVerbose > 2) {
      if (iHit == 0) std::cout << "#### NEW event ####" << std::endl;
    }
    bool skip = false;
    for (unsigned int ijk = 0; ijk < mergedHits.size();
         ijk++)  // check if already merged
      if (iHit == (int)mergedHits.at(ijk)) skip = true;
    if (skip) continue;
    mergewithIDs.clear();
    PndSdsHit* myHit1 = (PndSdsHit*)(fHitArray->At(iHit));

    for (Int_t jHit = iHit + 1; jHit < fHitArray->GetEntriesFast();
         jHit++) {  // check other hits
      PndSdsHit* myHit2 = (PndSdsHit*)(fHitArray->At(jHit));

      double dz = (myHit1->GetZ()) - (myHit2->GetZ());
      //    if(fabs(dz)<0.1 ){  //actually same Hit: merge
      //	if(fabs((myHit1->GetX())-(myHit2->GetX()))<0.016 &&
      //fabs((myHit1->GetY())-(myHit2->GetY()))<0.016){
      double dx = (myHit1->GetX()) - (myHit2->GetX());
      double dy = (myHit1->GetY()) - (myHit2->GetY());

      if (fabs(dx) < 0.0075 &&
          fabs(dy) < 0.0075) {  // 3*sigma_dx, sigma_dx=25mkm
        hdxdy->Fill(1e4 * dx, 1e4 * dy);
        hdz->Fill(1e4 * dz);

        if (dz < 0.01 || dz > 0.1) continue;
        mergewithIDs.push_back(jHit);
        mergedHits.push_back(jHit);
      }
    }

    if (mergewithIDs.size() > 0) {  // merge hits
      if (fVerbose > 4)
        std::cout << "hit merged with: " << mergewithIDs.size() << " hits"
                  << std::endl;
      // tmphit = new((*fMergedHitArray)[newHits]) PndSdsHit(*myHit1);
      tmphit = new ((*fMergedHitArray)[newHits]) PndSdsMergedHit(*myHit1, 0);

      double x = tmphit->GetX(), y = tmphit->GetY(), z = tmphit->GetZ();
      for (unsigned int iMerge = 0; iMerge < mergewithIDs.size();
           iMerge++) {  // loop over hits to merge in
        PndSdsHit* myHit2 =
            (PndSdsHit*)(fHitArray->At(mergewithIDs.at(iMerge)));
        x += myHit2->GetX();
        y += myHit2->GetY();
        z += myHit2->GetZ();
        tmphit->SetSecondMCHit(
            myHit2->GetRefIndex());  //!!! works only in case merging 2 hits
        tmphit->SetIsMerged(true);
      }
      x /= (mergewithIDs.size() + 1);
      y /= (mergewithIDs.size() + 1);
      z /= (mergewithIDs.size() + 1);
      tmphit->SetX(x);
      tmphit->SetY(y);
      tmphit->SetZ(z);
      if (fVerbose > 4) {
        std::cout << "!!! Merged hit !!!" << std::endl;
        tmphit->Print();
      }
    } else {  // dont merge, just use original hit
      //       tmphit = new((*fMergedHitArray)[newHits]) PndSdsHit(*myHit1);
      tmphit = new ((*fMergedHitArray)[newHits]) PndSdsMergedHit(*myHit1, -1);
      tmphit->SetIsMerged(false);
    }

    newHits++;
  }

  if (fVerbose > 1)
    std::cout << "-I- KoaHitMergeTask: out of "
              << fHitArray->GetEntriesFast() << " Hits "
              << fMergedHitArray->GetEntriesFast() << " Hits merged."
              << std::endl;
  return;
}

ClassImp(KoaHitMergeTask);
