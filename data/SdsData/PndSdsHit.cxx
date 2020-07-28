// -------------------------------------------------------------------------
// -----                    PndSdsHit source file                -----
// -----                                 -----
// -------------------------------------------------------------------------

#include "stdlib.h"
#include <iostream>
#include "PndSdsHit.h"
#include "TGeoManager.h"
#include "TGeoNode.h"
#include "TGeoVolume.h"
#include "TGeoMatrix.h"


// -----   Default constructor   -------------------------------------------
PndSdsHit::PndSdsHit() : FairHit(),
  fSensorID(-1),
  fCharge(0),
  fNDigiHits(0),
  fClusterIndex(-1),
  fBotIndex(-1),
  fCov(3,3)
{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
PndSdsHit::PndSdsHit(Int_t detID, Int_t sensorID, TVector3& pos, TVector3& dpos,
                     Int_t clindex, Double_t charge, Int_t NDigiHits, Int_t mcindex)
: FairHit(detID, pos, dpos, mcindex), 
  fSensorID(sensorID),
  fCharge(charge),
  fNDigiHits(NDigiHits),
  fClusterIndex(clindex),
  fBotIndex(-1),
  fCov(3,3)
{}

/*PndSdsHit::PndSdsHit(PndSdsHit& c)
 : FairHit()
 {
 fDetName = c.GetDetName();
 fTrackID = c.GetTrackID();
 fCharge  =  c.GetCharge();
 fNDigiHits = c.GetNDigiHits();
 SetPosition(c.GetPosition());
 SetPositionError(c.GetPositionError());
 SetDetectorID(c.GetDetectorID());
 SetRefIndex(c.GetRefIndex());
 
 
 }*/
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
PndSdsHit::~PndSdsHit() {}
// -------------------------------------------------------------------------



// -----   Public method Print   -------------------------------------------
void PndSdsHit::Print(const Option_t* opt) const {
  std::cout << *this<<"opt="<<opt<<std::endl;
}

void PndSdsHit::SetCov(TMatrixD cov)
{ 
  if (cov.GetNcols()==3 && cov.GetNrows()==3)
    fCov = cov; 
  else {
    Error("SetCov","matrix has wrong dimensions!");
    cov.Print();
  }
}




// Double_t PndSdsHit::GetD(Int_t i)
// {
//   if(!gGeoManager){
//     std::cout<<" -E- in PndSdsHit::GetD(): No gGeoManager there. Please use "<<std::endl;
//     abort();
//   }
//
//   // Caution! if there is a point reconstructed OUTSIDE its volume,
//   // then the returned stuff is WRONG!
//   ((TGeoNode*)(gGeoManager->FindNode(fX,fY,fZ)))->cd();
//   TGeoHMatrix* currMatrix = gGeoManager->GetCurrentMatrix();
//
//   const Double_t* rotation = (currMatrix->Inverse()).GetRotationMatrix();
//   Double_t local[3]={fDx,fDy,fDz};
//
//   Double_t result = fabs(rotation[3*i+0]*local[0]) + fabs(rotation[3*i+1]*local[1]) + fabs(rotation[3*i+2]*local[2]);
// std::cout"PndSdsHit::GetD("<<i<<"): dLocal={"<<fDx<<","<<fDy<<","<<fDz<<"} dLab("<<i<<"="<<result<<std::endl;
// return result;
// //   Double_t master[3];
// //   gGeoManager->LocalToMasterVect(local,master);
// //   return master[i];
//
// }

// -------------------------------------------------------------------------
ClassImp(PndSdsHit);
