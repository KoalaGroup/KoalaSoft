/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaRecPoint.h"
#include "FairLogger.h"

// -----   Default constructor   -------------------------------------------
KoaRecPoint::KoaRecPoint()
  : FairMCPoint()
  , fX_End(0)
  , fY_End(0)
  , fZ_End(0)
{
}
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
KoaRecPoint::KoaRecPoint(Int_t trackID, Int_t detID,
                         TVector3 posIn, TVector3 posEnd,
                         TVector3 mom, Double_t tof,
                         Double_t length, Double_t eLoss)
  : FairMCPoint(trackID, detID, posIn, mom, tof, length, eLoss)
  , fX_End(posEnd.X())
  , fY_End(posEnd.Y())
  , fZ_End(posEnd.Z())
{
}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
KoaRecPoint::~KoaRecPoint() { }
// -------------------------------------------------------------------------

// -----   Public method Print   -------------------------------------------
void KoaRecPoint::Print(const Option_t* /*opt*/) const
{
  LOG(info) << "KoaRecPoint: KoaRec point for track " << fTrackID
       << " in detector " << fDetectorID ;
  LOG(info) << "    Position In(" << fX << ", " << fY << ", " << fZ << ") cm" ;
  LOG(info) << "    Position End(" << fX_End << ", " << fY_End << ", " << fZ_End << ") cm" ;
  LOG(info) << "    Momentum (" << fPx << ", " << fPy << ", " << fPz << ") GeV";
  LOG(info) << "    Time " << fTime << " ns,  Length " << fLength
       << " cm,  Energy loss " << fELoss*1.0e06 << " keV" ;
}
// -------------------------------------------------------------------------

ClassImp(KoaRecPoint)

