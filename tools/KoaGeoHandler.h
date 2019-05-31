/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                 KoaGeoHandler header file                    ------
// -----                 Modified from FairRoot Tutorial4 GeeHandler   -----
// -----                 Created 31/05/19  by Y. Zhou                 -----
// -------------------------------------------------------------------------


/** KoaGeoHandler.h
 ** Helper class to extract information from the GeoManager which is
 ** needed in many other classes.. This helper class should be a
 ** single place to hold all these functions.
 ** @author Y.Zhou <y.zhou@fz-juelich.de>
 **/
/* TODO: 1. MasterToLocal
         2. CMakeList
         3. Check Volume ID and Unique ID
 */

#ifndef KOAGEOHANDLER_H
#define KOAGEOHANDLER_H 1

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Int_t, Double_t, Bool_t, etc
#include "TString.h"                    // for TString

class TGeoBBox;
class TGeoVolume;
class TGeoHMatrix;

class KoaGeoHandler : public TObject
{
  public:

    /** Constructor **/
    KoaGeoHandler();


    /** Destructor **/
    ~KoaGeoHandler() {};

    Int_t GetUniqueDetectorId();
    Int_t GetUniqueDetectorId(TString volName);

//  Int_t GetDetectorId(Int_t uniqueId);

    Int_t Init(Bool_t isSimulation=kFALSE);

    void FillDetectorInfoArray(Int_t uniqueId);
    void NavigateTo(TString volName);

    // Implement Interface functions to the TGeoManager to be
    // the same as for the VMC
    Int_t CurrentVolOffID(Int_t off, Int_t& copy) const;
    Int_t CurrentVolID(Int_t& copy) const;
    Int_t VolId(const Text_t* name) const;
    Int_t VolIdGeo(const char* name) const;
    const char* CurrentVolName() const;
    const char* CurrentVolOffName(Int_t off) const;

    void LocalToGlobal(Double_t* local, Double_t* global, Int_t detID);

//  Int_t CheckGeometryVersion();

  private:

    Bool_t fIsSimulation; //!

    Int_t fLastUsedDetectorID;  //!

    UInt_t fGeoPathHash;        //!
    TGeoVolume* fCurrentVolume; //!
    TGeoBBox* fVolumeShape;     //!
    Double_t fGlobal[3];        //! Global centre of volume
    TGeoHMatrix* fGlobalMatrix; //!


    TString ConstructFullPathFromDetID(Int_t detID);

    KoaGeoHandler(const KoaGeoHandler&);
    KoaGeoHandler operator=(const KoaGeoHandler&);

    ClassDef(KoaGeoHandler,1)

};


#endif //KOAGEOHANDLER_H

