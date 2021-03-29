// -------------------------------------------------------------------------
// -----                    PndSdsMergedHit source file                -----
// -----                                 -----
// -------------------------------------------------------------------------

#include "PndSdsMergedHit.h"
#include <iostream>
#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "TGeoNode.h"
#include "TGeoVolume.h"
#include "stdlib.h"

// -----   Default constructor   -------------------------------------------
PndSdsMergedHit::PndSdsMergedHit() {}
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
PndSdsMergedHit::PndSdsMergedHit(Int_t detID, Int_t sensorID, TVector3& pos,
                                 TVector3& dpos, Int_t clindex, Double_t charge,
                                 Int_t NDigiHits, Int_t mcindex, Int_t secMC)
    : PndSdsHit(detID, sensorID, pos, dpos, clindex, charge, NDigiHits,
                mcindex) {
  fsecMC = secMC;
}
// -------------------------------------------------------------------------

PndSdsMergedHit::PndSdsMergedHit(PndSdsHit& c, Int_t secMC) : PndSdsHit(c) {
  fsecMC = secMC;
}

// -----   Destructor   ----------------------------------------------------
PndSdsMergedHit::~PndSdsMergedHit() {}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
ClassImp(PndSdsMergedHit);
