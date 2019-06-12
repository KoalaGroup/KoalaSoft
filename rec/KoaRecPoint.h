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
     *@param posIn    Coordinates at entrance to active volume [cm]
     *@param posEnd   Coordinates at exit/end to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    KoaRecPoint(Int_t trackID,
                Int_t detID,
                TVector3 posIn,
                TVector3 posEnd,
                TVector3 mom,
                Double_t tof,
                Double_t length,
                Double_t eLoss);

    /** Destructor **/
    virtual ~KoaRecPoint();

    /** Accessors **/
    Double32_t GetXEnd() const { return fX_End; }
    Double32_t GetYEnd() const { return fY_End; }
    Double32_t GetZEnd() const { return fZ_End; }
    void PositionEnd(TVector3& pos) const { pos.SetXYZ(fX_End, fY_End, fZ_End); }

    /** Modifiers **/
    void SetXEnd(Double32_t x) { fX_End = x; }
    void SetYEnd(Double32_t y) { fY_End = y; }
    void SetZEnd(Double32_t z) { fZ_End = z; }
    void SetXYZEnd(Double32_t x, Double32_t y, Double32_t z){
      fX_End = x;
      fY_End = y;
      fZ_End = z;
    }
    void SetPositionEnd(const TVector3& posEnd){
      fX_End = posEnd.X();
      fY_End = posEnd.Y();
      fZ_End = posEnd.Z();
    }

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;

  private:
    Double32_t fX_End;
    Double32_t fY_End;
    Double32_t fZ_End;

    /** Copy constructor **/
    KoaRecPoint(const KoaRecPoint& point);
    KoaRecPoint operator=(const KoaRecPoint& point);

    ClassDef(KoaRecPoint,2)

};

#endif
