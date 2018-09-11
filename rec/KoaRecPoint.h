/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOARECPOINT_H
#define KOARECPOINT_H 1


#include "FairMCPoint.h"

#include "TObject.h"
#include "TVector3.h"

class KoaRecPoint : public FairMCPoint
{

  public:

    /** Default constructor **/
    KoaRecPoint();


    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Ccoordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    KoaRecPoint(Int_t trackID, Int_t detID, TVector3 pos, TVector3 posOut,TVector3 mom,  TVector3 momOut, Double_t tof, Double_t length, Double_t eLoss); 
    /** Copy constructor **/
    KoaRecPoint(const KoaRecPoint& point) : FairMCPoint(point),
      fXfOut(point.fXfOut),
      fYfOut(point.fYfOut),
      fZfOut(point.fZfOut),
      fPxfOut(point.fPxfOut),
      fPyfOut(point.fPyfOut),
      fPzfOut(point.fPzfOut)
        { *this = point; };


    /** Destructor **/
    virtual ~KoaRecPoint();

    /** Accessors **/
    Double_t GetXOut() const { return fXfOut;};
    Double_t GetYOut() const { return fYfOut;};
    Double_t GetZOut() const { return fZfOut;};

    Double_t GetPxOut() const { return fPxfOut; }
    Double_t GetPyOut() const { return fPyfOut; }
    Double_t GetPzOut() const { return fPzfOut; }
    TVector3 GetPosition() const { return TVector3(fX, fY, fZ);}
    TVector3 GetPositionOut() const { return TVector3(fXfOut, fYfOut, fZfOut);}
    void PositionOut(TVector3& pos) const { pos.SetXYZ(fXfOut, fYfOut, fZfOut);};
    void MomentumOut(TVector3& mom) const { mom.SetXYZ(fPxfOut,fPyfOut,fPzfOut); }

    /** Modifiers **/
    void SetPositionOut(TVector3 pos);
    void SetMomentumOut(TVector3 mom);
    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;

  private:
    KoaRecPoint operator=(const KoaRecPoint& point);

 protected:
    Double32_t fXfOut, fYfOut, fZfOut;
    Double32_t fPxfOut, fPyfOut, fPzfOut;

    ClassDef(KoaRecPoint,2)

};

inline void KoaRecPoint::SetPositionOut(TVector3 pos) {
	fXfOut = pos.X();
	fYfOut = pos.Y();
	fZfOut = pos.Z();
}


inline void KoaRecPoint::SetMomentumOut(TVector3 mom) {
  fPxfOut = mom.Px();
  fPyfOut = mom.Py();
  fPzfOut = mom.Pz();
}

#endif
