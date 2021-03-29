/**  PndSdsMCPoint.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 *
 * Interception of MC track with a SSD detetcor. Holds in addition
 * to the base class the coordinates and momentum at the exit from
 * the active volume.
 **/


#ifndef PNDSDSMCPOINT_H
#define PNDSDSMCPOINT_H


#include "TObject.h"
#include "TVector3.h"
#include "FairMCPoint.h"
#include "TString.h"
#include "KoaDetectorList.h" 

#include <stdio.h>
#include <iostream>

using namespace std;



class PndSdsMCPoint : public FairMCPoint
{
  friend std::ostream& operator<< (std::ostream& out, const PndSdsMCPoint& point){
    out << "-I- PndSdsMCPoint: PndSds Point for track " << point.GetTrackID()
         << " in detector " << point.GetDetectorID() << " with sensor "
       << point.GetSensorID() << std::endl;
    out << "    Position in  (" << point.GetX() << ", " << point.GetY() << ", " << point.GetZ() << ") cm" << std::endl;
    out << "    Position out (" << point.GetXOut() << ", " << point.GetYOut() << ", " << point.GetZOut() << ") cm" << std::endl;
    out << "    Momentum (" << point.GetPx() << ", " << point.GetPy() << ", " << point.GetPz() << ") GeV" << std::endl;
    out << "    Time " << point.GetTime() << " ns,  Length " << point.GetLength() << " cm,  Energy loss " << point.GetEnergyLoss()*1.0e06 << " keV" << std::endl;
    return out;
  }

 public:

  /** Default constructor **/
  PndSdsMCPoint();


  /** Constructor with arguments
   *@param trackID       Index of MCTrack
   *@param detID         Detector ID
   *@param sensorID		   Full nameId of the detector, see PndSdsGeoHandling
   *@param posIn         Coordinates of ingoing point[cm]
   *@param posOut	 Coordinates of outgoing point[cm]
   *@param momIn         Momentum of track at entrance [GeV]
   *@param momOut        Momentum of track at exit [GeV]
   *@param tof           Time since event start [ns]
   *@param length        Track length since creation [cm]
   *@param eLoss         Energy deposit [GeV]
   **/
  PndSdsMCPoint(Int_t trackID, Int_t detID, Int_t sensorID,
  	      TVector3 posIn, TVector3 posOut,
	      TVector3 momIn, TVector3 momOut,
	      Double_t tof, Double_t length, Double_t eLoss);


  /** Copy constructor **/
  PndSdsMCPoint(const PndSdsMCPoint& point) : FairMCPoint(point),
  fXfOut(point.fXfOut),
  fYfOut(point.fYfOut),
  fZfOut(point.fZfOut),
  fPxfOut(point.fPxfOut),
  fPyfOut(point.fPyfOut),
  fPzfOut(point.fPzfOut),
  fSensorID(point.fSensorID)
  { *this = point; };


  /** Destructor **/
  virtual ~PndSdsMCPoint();


  /** Accessors **/
  Double_t GetXOut() const { return fXfOut;};
  Double_t GetYOut() const { return fYfOut;};
  Double_t GetZOut() const { return fZfOut;};

  Double_t GetPxOut() const { return fPxfOut; }
  Double_t GetPyOut() const { return fPyfOut; }
  Double_t GetPzOut() const { return fPzfOut; }
 // TString  GetDetName() const { return fDetName;}
  Int_t GetSensorID() const { return fSensorID;}
  TVector3 GetPosition() const { return TVector3(fX, fY, fZ);}
  TVector3 GetPositionOut() const { return TVector3(fXfOut, fYfOut, fZfOut);}

  void PositionOut(TVector3& pos) const { pos.SetXYZ(fXfOut, fYfOut, fZfOut);};
  void MomentumOut(TVector3& mom) const { mom.SetXYZ(fPxfOut,fPyfOut,fPzfOut); }


  /** Modifiers **/
  void SetPositionOut(TVector3 pos);
  void SetMomentumOut(TVector3 mom);
  //void SetDetName(TString name) {fDetName = name;};
  void SetSensorID(Int_t sensorID){fSensorID = sensorID;}
  virtual void SetTrackID(Int_t id){ 
          //SetLink("MCTrack", id);
          FairMCPoint::SetTrackID(id); 
  }; 


  /** Output to screen **/
  virtual void Print(const Option_t* opt = 0) const;


 protected:

  Double32_t fXfOut, fYfOut, fZfOut;

  Double32_t fPxfOut, fPyfOut, fPzfOut;
  Int_t fSensorID;


  ClassDef(PndSdsMCPoint,6);

};

inline void PndSdsMCPoint::SetPositionOut(TVector3 pos) {
	fXfOut = pos.X();
	fYfOut = pos.Y();
	fZfOut = pos.Z();
}


inline void PndSdsMCPoint::SetMomentumOut(TVector3 mom) {
  fPxfOut = mom.Px();
  fPyfOut = mom.Py();
  fPzfOut = mom.Pz();
}



#endif
