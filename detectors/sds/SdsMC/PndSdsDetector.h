// -------------------------------------------------------------------------
// -----                         PndSdsDetector header file            -----
// -----                          Based on PndMvdDetector              -----
// -----                      Created 6/04/06  by T. Stockmanns        -----
// -------------------------------------------------------------------------

/**  PndSdsDetector.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Defines the active detector PndSdsDetector. Constructs the geometry and
 ** registers MCPoints.
 **/



#ifndef PNDSDSDETECTOR_H
#define PNDSDSDETECTOR_H


//#include "TClonesArray.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "FairDetector.h"
#include "TString.h"
#include "PndGeoHandling.h"
#include "KoaDetectorList.h"

#include <string>
#include <vector>
#include <map>

class TClonesArray;
class TGeoNode;
class PndSdsMCPoint;
class FairVolume;



class PndSdsDetector : public FairDetector
{

 public:

  /** Default constructor **/
  PndSdsDetector();

  PndSdsDetector(PndSdsDetector& other) :
    FairDetector(other),
    fPersistance(other.fPersistance),
    fTrackID(other.fTrackID),
    fVolumeID(other.fVolumeID),
    fPosIn(other.fPosIn),
    fPosOut(other.fPosOut),
    fMomIn(other.fMomIn),
    fMomOut(other.fMomOut),
    fTime(other.fTime),
    fLength(other.fLength),
    fELoss(other.fELoss),
    fGeoH(other.fGeoH),
    fPosIndex(other.fPosIndex),
    fPndSdsCollection(other.fPndSdsCollection),
    fUseRadDamOption(other.fUseRadDamOption),
    fOutBranchName(other.fOutBranchName),
    fFolderName(other.fFolderName),
    fDetectorID(other.fDetectorID),
    fListOfSensitives(other.fListOfSensitives)
  {};
  /** Standard constructor.
   *@param name    detetcor name
   *@param active  sensitivity flag
   **/
  PndSdsDetector(const char* name, Bool_t active);

  /** Destructor **/
  virtual ~PndSdsDetector();

  PndSdsDetector& operator=(PndSdsDetector& other)
  {
    fPersistance=other.fPersistance;
    fTrackID=other.fTrackID;
    fVolumeID=other.fVolumeID;
    fPosIn=other.fPosIn;
    fPosOut=other.fPosOut;
    fMomIn=other.fMomIn;
    fMomOut=other.fMomOut;
    fTime=other.fTime;
    fLength=other.fLength;
    fELoss=other.fELoss;
    fGeoH=other.fGeoH;
    fPosIndex=other.fPosIndex;
    fPndSdsCollection=other.fPndSdsCollection;
    fUseRadDamOption=other.fUseRadDamOption;
    fOutBranchName=other.fOutBranchName;
    fFolderName=other.fFolderName;
    fDetectorID=other.fDetectorID;
    fListOfSensitives=other.fListOfSensitives;
    return *this;
  };

  virtual void Initialize();

  /** pure virtual method SetBranchName
   **
   ** called by Initialize()
   ** function to set individual branch names
   **/
  virtual void SetBranchNames()=0;
  
  /** pure virtual method SetDefaultSensorNames
   **
   ** called by Initialize()
   ** function to set individual sensor type names
   **/
  virtual void SetDefaultSensorNames() = 0;
  void SetExclusiveSensorType(const TString sens);

  /** Virtual method ProcessHits
   **
   ** Defines the action to be taken when a step is inside the
   ** active volume. Creates CbmTrdPoints and adds them to the
   ** collection.
   *@param vol  Pointer to the active volume
   **/
  virtual Bool_t  ProcessHits(FairVolume* vol = 0);


  /** Virtual method EndOfEvent
   **
   ** If verbosity level is set, Print hit collection at the
   ** end of the event and resets it afterwards.
   **/
  virtual void EndOfEvent();

  virtual void   FinishRun();


  /** Virtual method Register
   **
   ** Registers the hit collection in the ROOT manager.
   **/
  virtual void Register();


  /** Accessor to the hit collection **/
  virtual TClonesArray* GetCollection(Int_t iColl) const;


  /** Virtual method Print
   **
   ** Screen output of hit collection.
   **/
  virtual void Print() const;


  /** Virtual Method SetSpecialPhysicsCuts
   **
   ** replaces some Geant initialisation via g3Config.C and so on
   **/
  virtual void SetSpecialPhysicsCuts();
  

  /** Virtual method Reset
   **
   ** Clears the hit collection
   **/
  virtual void Reset();


  /** Virtual method CopyClones
   **
   ** Copies the hit collection with a given track index offset
   *@param cl1     Origin
   *@param cl2     Target
   *@param offset  Index offset
   **/
  virtual void CopyClones(TClonesArray* cl1, TClonesArray* cl2,
			  Int_t offset);


  /** Virtual method Construct geometry
   **
   ** Constructs the PndSdsDetector geometry
   **/
  virtual void ConstructGeometry();
 // void ConstructRootGeometry();
  virtual void ConstructASCIIGeometry();
 // void ExpandNode(TGeoNode *fN);
  
  void SetDetectorID(DetectorId id){fDetectorID = id;fDetId =id;}

  void SetRadDamOption(bool val){fUseRadDamOption = val;};
  bool GetRadDamOption(){return fUseRadDamOption;};

  // overload function from FairModule
  void SetVerboseLevel(Int_t level){fVerboseLevel=level;fGeoH->SetVerbose(level);}
  
  void SetPersistance(Bool_t p = kTRUE) {fPersistance=p;};
  Bool_t GetPersistance() {return fPersistance;};
  
protected:
  
  Bool_t fPersistance; // switch to turn on/off storing the arrays to a file
  
  
  /** Track information to be stored until the track leaves the
      active volume. **/
  Int_t          fTrackID;           //!  track index
  Int_t          fVolumeID;             //!  Det id
  TLorentzVector fPosIn;             //!  entry position in global frame
  TLorentzVector fPosOut;            //!  exit position in global frame
  TLorentzVector fMomIn;             //!  momentum
  TLorentzVector fMomOut;            //!  momentum
  Double32_t     fTime;              //!  time
  Double32_t     fLength;            //!  length
  Double32_t     fELoss;             //!  energy loss
//  std::map<TString, Int_t> fVolumeIDMap;	 //!  map to create a unique Detector ID
  PndGeoHandling* fGeoH;	     //! Gives Access to the Path info of a hit
  Int_t fPosIndex;                   //!
  TClonesArray* fPndSdsCollection;      //! Hit collection
  bool fUseRadDamOption;			//! enables the detection of neutral particles
  TString fOutBranchName;     //! To be set by daughter classes
  TString fFolderName;        //! To be set by daughter classes
  DetectorId fDetectorID;          //! To be set by daughter classes

  std::vector<std::string> fListOfSensitives; //!

  bool CheckIfSensitive(std::string name);

  /** Private method AddHit
   **
   ** Adds a CbmTrdPoint to the HitCollection
   **/
  PndSdsMCPoint* AddHit(Int_t trackID, Int_t detID, Int_t sensorID,
  		      TVector3 posIn, TVector3 posOut,
		      TVector3 momIn, TVector3 momOut,
		      Double_t time, Double_t length, Double_t eLoss);


  /** Private method ResetParameters
   **
   ** Resets the private members for the track parameters
   **/
  void ResetParameters();


  ClassDef(PndSdsDetector,6);

};


inline void PndSdsDetector::ResetParameters() {
  fTrackID = 0;
  fVolumeID = 1;
  fPosIn.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fPosOut.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fMomIn.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fMomOut.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fTime = fLength = fELoss = 0;
  fPosIndex = 0;
}


#endif

