// -------------------------------------------------------------------------
// -----                    PndSdsHit header file                      -----
// -----                  Created by T.Stockmanns            -----
// -------------------------------------------------------------------------


/** PndSdsHit.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** A hit in a silicon sensor. In addition to the base class
 ** FairHit, it holds the number of digis & charge entry.
 ** There is also a bottom index for double sided strip sensors.
 ** All coordinates are in the LAB frame.
 **/

#ifndef PNDSDSHIT_H
#define PNDSDSHIT_H


#include "TVector3.h"
#include "TString.h"
#include "FairHit.h"
#include "KoaDetectorList.h"
#include "TMatrixD.h"
//#include "PndSingleLinkedData.h" 

#include <stdio.h>
#include <iostream>

class PndSdsHit : public FairHit
{
  friend std::ostream& operator<< (std::ostream& out, const PndSdsHit& hit){
    out << "PndSdsHit in " << hit.GetSensorID() << " at" << std::endl;
    out << "(" << hit.GetX() << ", " << hit.GetY() << ", " << hit.GetZ() << ") cm "
        << " with " << hit.GetCharge() << " e" << " at Time: " << hit.GetTimeStamp() << " +/- " << hit.GetTimeStampError() << " , Cluster No. " << hit.GetClusterIndex();
    if (hit.GetBotIndex() > -1)
    	out << " and bottom " << hit.GetBotIndex();
    if (hit.GetRefIndex() > -1)
      out << ", mc point id = " << hit.GetRefIndex();
    else 
      out << ", noise hit without mc poit";
    out << std::endl;

    out <<"hit.GetClusterIndex() "<<hit.GetClusterIndex() <<std::endl;
    out <<"hit.GetBotIndex() "<< hit.GetBotIndex() <<std::endl;
    out <<"hit.GetRefIndex() "<< hit.GetRefIndex()<<std::endl;
    out <<"hit.GetNDigiHits() "<< hit.GetNDigiHits()<<std::endl;
    out <<"hit.GetCharge() "<< hit.GetCharge()<<"("<<hit.GetEloss()<<" GeV)"<<std::endl;
    out <<"hit.GetSensorID() "<< hit.GetSensorID()<<std::endl;
    out <<"Error values in FairHit part: (dx,dy,dz) = ("<< hit.GetDx()<<","<<hit.GetDy()<<","<<hit.GetDz()<<")"<<std::endl;
    return out;
  }

 public:

  /** Default constructor (not for use) **/
  PndSdsHit();


  /** Standard constructor with all paramneters 
   *@param detID   Detector ID
   *@param sensorID Sensor ID
   *@param pos     Position vector [cm]
   *@param dpos    Position error vector [cm]
   *@param index   Array index of ClusterCand
   *@param charge  Charge measured in hit
   *@param NDigiHits Number of pixels fired for this event
   **/
  PndSdsHit(Int_t detID, Int_t sensorID,
  	    TVector3& pos, TVector3& dpos, Int_t clindex, Double_t charge, Int_t NDigiHits, Int_t mcindex);

  //PndSdsHit(PndSdsHit& c);
  /** Destructor **/
  virtual ~PndSdsHit();


  /** Accessors **/
  
  void SetSensorID(Int_t sensorID)  { fSensorID   = sensorID;}
  void SetCharge(Double_t charge){ fCharge    = charge;}
  void SetNDigiHits(Int_t pixel) { fNDigiHits = pixel;}
  void SetClusterIndex(Int_t datasource, Int_t id, Int_t fileId = -1, Int_t evtId = -1) {
	  fClusterIndex = id;
	  SetLink(FairLink(fileId, evtId, datasource, id));
  }
  void SetBotIndex(Int_t id)     { fBotIndex  = id;}
  void SetCov(TMatrixD cov);
  
  //TString 	GetDetName()      const { return fDetName;}
  Int_t     GetSensorID()			const { return fSensorID;}
  Double_t 	GetCharge()       const { return fCharge;}
  Int_t 	  GetNDigiHits()    const { return fNDigiHits;}
  TVector3  GetPosition()	    const { return TVector3(fX,fY,fZ);}
  Int_t     GetClusterIndex() const { return fClusterIndex;}
  Int_t     GetTopIndex()     const { return GetClusterIndex();}
  Int_t     GetBotIndex()     const { return fBotIndex;}
  Double_t  GetEloss()        const { return (fCharge * 3.61e-9);}  // 3.6 eV/Electron in Silicon
  TMatrixD  GetCov()          const { return fCov;}


//  FIXME: CAUTION The errors in the SsdHit are LOCAL, but the coordinates are in the LAB
// 
//   Double_t GetDxLocal() const { return fDx;};
//   Double_t GetDyLocal() const { return fDy;};
//   Double_t GetDzLocal() const { return fDz;};
//   void PositionErrorLocal(TVector3& dpos) const;

//   /** overloaded accessors **/
//   Double_t GetDx() {return GetD(0);};
//   Double_t GetDy() {return GetD(1);};
//   Double_t GetDz() {return GetD(2);};
//   void PositionError(TVector3& dpos);

#ifndef __CINT__ // for BOOST serialization
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  	{
  		ar & boost::serialization::base_object<FairHit>(*this);
  		ar & fSensorID;
  		ar & fCharge;
  		ar & fNDigiHits;
  		ar & fClusterIndex;
  		ar & fBotIndex;
  		//ar & fCov;
  	}
#endif // for BOOST serialization

  /** Screen output **/
  virtual void Print(const Option_t* opt = 0) const;

 private:
//   Double_t GetD(Int_t i);
#ifndef __CINT__ // for BOOST serialization
		friend class boost::serialization::access;

#endif // for BOOST serialization

  //TString fDetName;  // Detector name
  Int_t fSensorID; ///< unique sensor ID
  Double_t fCharge; /// deposited Charge
  Int_t fNDigiHits; /// number of fired Digis for this hit,
  Int_t fClusterIndex; /// top/pixel cluster index
  Int_t fBotIndex; /// bottom side of strip clusters
  TMatrixD fCov; /// Hit covariance Matrix
  ClassDef(PndSdsHit,8);

};

// inline void PndSdsHit::PositionErrorLocal(TVector3& dpos) const {
//   dpos.SetXYZ(fDx, fDy, fDz); 
// }
// 
// inline void PndSdsHit::PositionError(TVector3& dpos) {
//   dpos.SetXYZ(GetDx(), GetDy(), GetDz()); 
// }

#endif
