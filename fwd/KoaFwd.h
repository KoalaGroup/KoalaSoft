/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAFWD_H
#define KOAFWD_H

#include "FairDetector.h"

#include "TVector3.h"
#include "TLorentzVector.h"
#include <string>

class KoaFwdPoint;
class FairVolume;
class TClonesArray;
class KoaGeoHandler;
class KoaFwdMisalignPar;

class KoaFwd: public FairDetector
{

  public:

    /**      Name :  Detector Name
     *       Active: kTRUE for active detectors (ProcessHits() will be called)
     *               kFALSE for inactive detectors
    */
    KoaFwd(const char* Name, Bool_t Active);

    /**      default constructor    */
    KoaFwd();

    /**       destructor     */
    virtual ~KoaFwd();

    /** Switch on/off geometry modification, i.e. whether apply the misalignment matrices **/
    // Reference Tutorial4
    void SetModifyGeometry(Bool_t val) { fModifyGeometry=val; }
    // get the Misalignment Matrices list, mainly used for output and checking
    std::map<std::string, TGeoHMatrix> getMisalignmentMatrices();

    /**      Initialization of the detector is done here    */
    virtual void   Initialize();

    /**Set the parameter containers*/
    void SetParContainers();

    /** Initialize everything which has to be done before the construction and modification
     ** of the geometry. Mostly this is needed to read data from the parameter containers.
     ** Especially for the geometry modification before MC.*/
    virtual void   InitParContainers();

    /**       this method is called for each step during simulation
     *       (see FairMCApplication::Stepping())
    */
    virtual Bool_t ProcessHits( FairVolume* v=0);

    /**       Registers the produced collections in FAIRRootManager.     */
    virtual void   Register();

    /** Gets the produced collections */
    virtual TClonesArray* GetCollection(Int_t iColl) const ;

    /**      has to be called after each event to reset the containers      */
    virtual void   Reset();

    /**      Create the detector geometry        */
    void ConstructGeometry();

    Bool_t CheckIfSensitive(std::string name);
    void ConstructASCIIGeometry();


    /**      This method is an example of how to add your own point
     *       of type KoaFwdPoint to the clones array
    */
    KoaFwdPoint* AddHit(Int_t trackID, Int_t detID,
                             TVector3 pos, TVector3 mom,
                             Double_t time, Double_t length,
                             Double_t eLoss);

    /** The following methods can be implemented if you need to make
     *  any optional action in your detector during the transport.
    */

    virtual void   SetSpecialPhysicsCuts() {;}
    virtual void   EndOfEvent();
    virtual void   FinishPrimary() {;}
    virtual void   FinishRun() {;}
    virtual void   BeginPrimary() {;}
    virtual void   PostTrack() {;}
    virtual void   PreTrack() {;}
    virtual void   BeginEvent() {;}

    virtual FairModule* CloneModule() const;

    virtual void RegisterAlignmentMatrices();

  private:
    // Sensitive volume name list, used when importing geometry from ROOT file
    std::vector<std::string> fListOfSensitives;  

    /** Track information to be stored until the track leaves the
    active volume.
    */
    Int_t          fTrackID;           //!  track index
    Int_t          fVolumeID;          //!  volume id
    TLorentzVector fPos;               //!  position at entrance
    TLorentzVector fMom;               //!  momentum at entrance
    Double32_t     fTime;              //!  time
    Double32_t     fLength;            //!  length
    Double32_t     fELoss;             //!  energy loss

    /** container for data points */

    TClonesArray*  fKoaFwdPointCollection;  //!

    KoaGeoHandler* fGeoHandler; //!

    /** parameters related to geometry misalignment **/
    Bool_t fModifyGeometry;

    // parameter container
    KoaFwdMisalignPar* fMisalignPar;

    // Individual Sensor's misalignment
    Int_t fNrOfSensors;
    TArrayD fSensorShiftX;
    TArrayD fSensorShiftY;
    TArrayD fSensorShiftZ;
    TArrayD fSensorRotPhi;
    TArrayD fSensorRotTheta;
    TArrayD fSensorRotPsi;
    
    KoaFwd(const KoaFwd&);
    KoaFwd& operator=(const KoaFwd&);

    ClassDef(KoaFwd,1)
};

#endif //NEWDETECTOR_H
