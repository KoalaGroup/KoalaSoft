/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaRecPoint.h"

#include <iostream>
using std::cout;
using std::endl;


// -----   Default constructor   -------------------------------------------
KoaRecPoint::KoaRecPoint()
  : FairMCPoint(),
    fXfOut(0.), fYfOut(0.), fZfOut(0.), 
  fPxfOut(0.), fPyfOut(0.), fPzfOut(0)
{
}
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
KoaRecPoint::KoaRecPoint(Int_t trackID, Int_t detID,
                         TVector3 pos, TVector3 posOut,
                         TVector3 mom, TVector3 momOut,
                                   Double_t tof, Double_t length,
                                   Double_t eLoss)
  : FairMCPoint(trackID, detID, pos, mom, tof, length, eLoss),
    fXfOut(posOut.X()),
  fYfOut(posOut.Y()),
  fZfOut(posOut.Z()),
  fPxfOut(momOut.Px()),
  fPyfOut(momOut.Py()),
  fPzfOut(momOut.Pz())
{
}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
KoaRecPoint::~KoaRecPoint() { }
// -------------------------------------------------------------------------

// -----   Public method Print   -------------------------------------------
void KoaRecPoint::Print(const Option_t* /*opt*/) const
{
  cout << "-I- KoaRecPoint: KoaRec point for track " << fTrackID
       << " in detector " << fDetectorID << endl;
  cout << "    Position (" << fX << ", " << fY << ", " << fZ
       << ") cm" << endl;
  cout << "    Momentum (" << fPx << ", " << fPy << ", " << fPz
       << ") GeV" << endl;
  cout << "    Time " << fTime << " ns,  Length " << fLength
       << " cm,  Energy loss " << fELoss*1.0e06 << " keV" << endl;
}
// -------------------------------------------------------------------------

ClassImp(KoaRecPoint)

