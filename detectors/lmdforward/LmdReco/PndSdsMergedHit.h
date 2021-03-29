// -------------------------------------------------------------------------
// -----                 PndSdsMergedHit header file                   -----
// -----                  Created by M. Michel            -----
// -------------------------------------------------------------------------

#ifndef PNDSDSMERGEDHIT_H
#define PNDSDSMERGEDHIT_H

#include "FairHit.h"
#include "KoaDetectorList.h"
#include "TMatrixD.h"
#include "TString.h"
#include "TVector3.h"
//#include "PndSingleLinkedData.h"

#include <stdio.h>
#include <iostream>

#include "PndSdsHit.h"

class PndSdsMergedHit : public PndSdsHit {
  friend std::ostream& operator<<(std::ostream& out,
                                  const PndSdsMergedHit& hit) {
    out << "PndSdsMergedHit in " << hit.GetSensorID() << " at" << std::endl;
    out << "(" << hit.GetX() << ", " << hit.GetY() << ", " << hit.GetZ()
        << ") cm "
        << " with " << hit.GetCharge() << " e"
        << " at Time: " << hit.GetTimeStamp() << " +/- "
        << hit.GetTimeStampError() << " , Cluster No. "
        << hit.GetClusterIndex();
    if (hit.GetBotIndex() > -1) out << " and bottom " << hit.GetBotIndex();
    if (hit.GetRefIndex() > -1) out << ", mc point id = " << hit.GetRefIndex();
    if (hit.GetSecondMCHit() > -1)
      out << ", mc point 2 id = " << hit.GetSecondMCHit();
    else
      out << ", noise hit without mc poit";
    out << std::endl;

    out << "hit.GetClusterIndex() " << hit.GetClusterIndex() << std::endl;
    out << "hit.GetBotIndex() " << hit.GetBotIndex() << std::endl;
    out << "hit.GetRefIndex() " << hit.GetRefIndex() << std::endl;
    out << "hit.GetNDigiHits() " << hit.GetNDigiHits() << std::endl;
    out << "hit.GetCharge() " << hit.GetCharge() << "(" << hit.GetEloss()
        << " GeV)" << std::endl;
    out << "hit.GetSensorID() " << hit.GetSensorID() << std::endl;
    out << "Error values in FairHit part: (dx,dy,dz) = (" << hit.GetDx() << ","
        << hit.GetDy() << "," << hit.GetDz() << ")" << std::endl;
    return out;
  }

 public:
  /** Default constructor (not for use) **/
  PndSdsMergedHit();

  /** Standard constructor with all paramneters
   *@param detID   Detector ID
   *@param sensorID Sensor ID
   *@param pos     Position vector [cm]
   *@param dpos    Position error vector [cm]
   *@param index   Array index of ClusterCand
   *@param charge  Charge measured in hit
   *@param NDigiHits Number of pixels fired for this event
   **/
  PndSdsMergedHit(Int_t detID, Int_t sensorID, TVector3& pos, TVector3& dpos,
                  Int_t clindex, Double_t charge, Int_t NDigiHits,
                  Int_t mcindex, Int_t secMC);

  PndSdsMergedHit(PndSdsHit& c, Int_t secMC);

  // PndSdsHit(PndSdsHit& c);
  /** Destructor **/
  virtual ~PndSdsMergedHit();

  /** Accessors **/

  void SetSecondMCHit(Int_t secMChit) { fsecMC = secMChit; }

  Int_t GetSecondMCHit() const { return fsecMC; }

  void SetIsMerged(bool fflag) { fisMerged = fflag; }
  bool GetIsMerged() const { return fisMerged; }

 private:
  Int_t fsecMC;  ///< unique sensor ID
  bool fisMerged;
  ClassDef(PndSdsMergedHit, 1);
};

#endif
