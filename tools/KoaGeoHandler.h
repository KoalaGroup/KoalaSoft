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
 **
 ** Major functions:
 **   1. Keep a list of TGeoHMatrix for coordinate transformation from global to local,
 **      and vice visa.
 **   2. Keep a list of mapping relation between strip id to readout channel id (caveat:
 **      readout channel mapping to electronics channel is save in KoaMapHandler)
 **   3. Keep a list of readout channel id mapping to local position of strip range.
 **   4. Keep a list of normalized detector id, which is the uniquely assigned to each
 **      sensor volume in simulaion and recognized in digitisation (i.e. volID in MCPoint)
 **
 ** This class is designed to be used intensely in simulaion/digitisation/reconstruction/
 ** anaylsis.
 **
 ** @author Y.Zhou <y.zhou@fz-juelich.de>
 **/
/* TODO: 1. MasterToLocal
         2. CMakeList (usage libs like rec, fwd, and mc)
         3. Check Volume ID and Unique ID
         4. Implementation to be done for Fwd detector
 */

#ifndef KOAGEOHANDLER_H
#define KOAGEOHANDLER_H 1

#include "TObject.h"                    // for TObject
#include <map>                          // for map
#include "TGeoMatrix.h"

#include "Rtypes.h"                     // for Int_t, Double_t, Bool_t, etc
#include "TString.h"                    // for TString

class KoaMapEncoder;

class KoaGeoHandler : public TObject
{
  public:
    KoaGeoHandler(Bool_t IsSim=kFALSE);
    ~KoaGeoHandler() {
      for(auto& it: fDetMatrix){
        delete it.second;
      }
    };

    // 
    Int_t GetDetIdByName(const char* volName); // used in simulation run
    TString GetDetNameById(Int_t detId);
    TString GetDetPathById(Int_t detId);
    TString GetDetPathByName(const char* volName);

    //
    Double_t GetDetPositionById(Int_t detId);
    Double_t GetDetPositionByName(const char* volName);
    void GetDetBoundaryById(Int_t detId, Double_t& lower, Double_t& higher); // in cm
    void GetDetBoundaryByName(const char* volName, Double_t& lower, Double_t& higher); // in cm

    //
    void LocalToGlobal(Double_t* local, Double_t* global, Int_t detID);
    void GlobalToLocal(Double_t* global, Double_t* local, Int_t detID);

    // hitPos here is the local coordinate in the sensor volume
    // return value is the encoded ch id
    Int_t RecLocalPositionToDetCh(Double_t* hitPos, Int_t detID);
    // hitPos is the global coordinate 
    // return value is the encoded ch id
    Int_t RecGlobalPositionToDetCh(Double_t* hitPos, Int_t detID);
    // return value is the center position of this channel along z-axis
    // here detChId is the encoded readout channel id
    Double_t RecDetChToPosition(Int_t detChId, Double_t& lower, Double_t& higher);

    typedef struct{
      Double_t center;
      Double_t lower;
      Double_t higher;
    } StripRange;

 private:
    Int_t InitMatrix(); // Init the transformation matrix from gGeoManager, which is not\
                        available immediately in simulation
    Int_t Init(); // Init all the other mappings, which are available both in simulation\
                  and analysis
    void NavigateTo(TString volName); // Navigate to a specific volume\
                                      invoked before coordinate transformation

 private:
    KoaMapEncoder*  fMapEncoder;
    Bool_t fIsSimulation; //! used in simulation task or analysis task

    // data for both recoil and fwd
    TString         fRecPath; // node path for recoil detector
    TString         fFwdPath;
    std::map<Int_t, TString>      fDetPath;
    std::map<Int_t, TGeoHMatrix*> fDetMatrix;

    // data only needed for recoil sensors
    std::map<Int_t, Double_t>     fRecDetPosition; // position of sensor centor in global coordinate
    std::map<Int_t, Double_t>     fRecDetDimension; // half length of sensor size along z-axis
    // mapping from encoded readout channel id to local strip range in sensor volume
    std::map<Int_t, StripRange>   fRecChIdToStripRange;
    // mapping from encoded strip id to encoded readout channel id
    std::map<Int_t, Int_t>        fRecStripIdToChId;

    KoaGeoHandler(const KoaGeoHandler&);
    KoaGeoHandler operator=(const KoaGeoHandler&);

    ClassDef(KoaGeoHandler,1)

};


#endif //KOAGEOHANDLER_H

