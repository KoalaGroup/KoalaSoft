/**
 * PndGeoHandling.h
 * @author: t.stockmanns <t.stockmans@fz-juelich.de>
 *
 * @brief Class to access the naming information of the MVD
 *
 * To save memory not any longer the full path of a volume is stored
 * in each hit but an encrypted form of it (f.e. /1_1/34_2/101_1/).
 * The first number is the volumeID coming from the GeoManager and
 * the second number is the copy number.
 * This class helps you converting the encrypted ID into the path
 * information and vice versa.
 * It needs the informations of the GeoManager. Therefore one has to
 * ensure that either an initialized TGeoManager pointer is given in the
 * constructor with the correct geometry or a filename with the correct geometry ("FAIRGeom")
 *
 * 30.03.2010: To reduce the data size a shortId is introduced.
 * The shortId is generated with the command CreateUniqueSensorId and the match between the path
 * in the GeoManager and the shortId is stored in the ParameterDatabase.
 * To use the shortID the constructor of the PndGeoHandling has to be called in the method
 * SetParContainers of a Task!
 *
 */

#ifndef PNDGEOHANDLING_H
#define PNDGEOHANDLING_H

#include "PndSensorNamePar.h"

#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairTask.h"

#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "TString.h"
#include "TVector3.h"
#include "TMatrixD.h"

#include <string>
#include <iostream>
#include <vector>

class PndGeoHandling : public FairTask {
public:
  
	/// PndGeoHandling::Instance() has to be called the first time in the constructor of a task
	/// otherwise the Sensor names are not available from the database
  PndGeoHandling(); ///< default constructor. Has to be called in SetParContainers if the support of shortId is needed.
	static PndGeoHandling* Instance();
  
	static void Destroy(){
		if (fInstance){
			delete fInstance;
			fInstance = 0;
		}
	}
  
  //PndGeoHandling(TGeoManager* aGeoMan);
  PndGeoHandling(TString mcFile, TString parFile);
  PndGeoHandling(Int_t runID, TString parFile);
  PndGeoHandling(PndSensorNamePar* SensorNamePar);
  
  virtual ~PndGeoHandling(){};
  
  virtual void SetParContainers();
  
  //  static PndGeoHandling* Instance();
  
  //  TString GetCurrentID(); ///< returns the ID of the current node
  //  TString GetID(TString path); ///< for a given TGeoManager-path the ID is returned
  //  TString GetPath(TString id); ///< for a given ID the path is returned
  
  TString GetPath(Int_t shortID); ///< for a given shortID the path is returned
  Int_t	  GetShortID(TString path); ///< for a given path the (unique) position of the sensor path in the fSensorNamePar-List is given. If it is not found -1 is returned.
  
  TString GetVolumeID(TString name); ///< returns the volume ID for a given volume name
  std::vector<TString> GetNamesLevel(Int_t level, TString startPath = ""); //, bool fullPath = false); //[R.K.03/2017] unused variable
  void GetOUVPath(TString path, TVector3& o, TVector3& u, TVector3& v); ///< for a volume given by its path the o, u, v vectors for the plane are returned
  //  void GetOUVId(TString id, TVector3& o, TVector3& u, TVector3& v); ///< for a volume given by its ID the o, u, v vectors for the plane are returned
  void GetOUVShortId(Int_t shortId, TVector3& o, TVector3& u, TVector3& v){
    if (fSensorNamePar != 0)
      GetOUVPath(GetPath(shortId), o, u, v);
  }
  
  TGeoHMatrix* GetMatrixPath(TString path);
  //  TGeoHMatrix* GetMatrixId(TString id);
  TGeoHMatrix* GetMatrixShortId(Int_t shortId){
	  return GetMatrixPath(GetPath(shortId));
	}
  
  //  TVector3 GetSensorDimensionsId(TString id);
  TVector3 GetSensorDimensionsPath(TString path);
  TVector3 GetSensorDimensionsShortId(Int_t shortId){
    return GetSensorDimensionsPath(GetPath(shortId));
  }
  
  //  TVector3 MasterToLocalId(const TVector3& master, const TString& id);
  TVector3 MasterToLocalPath(const TVector3& master, const TString& id);
  TVector3 MasterToLocalShortId(const TVector3& master, const Int_t& shortId){
 	  return MasterToLocalPath(master, GetPath(shortId));
  }
  
  //  TVector3 LocalToMasterId(const TVector3& local, const TString& id);
  TVector3 LocalToMasterPath(const TVector3& local, const TString& id);
  TVector3 LocalToMasterShortId(const TVector3& local, const Int_t& shortId){
 	  return LocalToMasterPath(local, GetPath(shortId));
  }
  
  // TODO: Recheck the error calculation for 3-vectors
  //  TMatrixD MasterToLocalErrorsId(const TMatrixD& master, const TString& id);
  TMatrixD MasterToLocalErrorsPath(const TMatrixD& master, const TString& id);
  TMatrixD MasterToLocalErrorsShortId(const TMatrixD& master, const Int_t& shortId){
 	  return MasterToLocalErrorsPath(master, GetPath(shortId));
  }
  
  //  TMatrixD LocalToMasterErrorsId(const TMatrixD& local, const TString& id);
  TMatrixD LocalToMasterErrorsPath(const TMatrixD& local, const TString& id);
  TMatrixD LocalToMasterErrorsShortId(const TMatrixD& local, const Int_t& shortId){
    return LocalToMasterErrorsPath(local, GetPath(shortId));
  }
  
  TMatrixD GetCurrentRotationMatrix();
  
  void SetVerbose(Int_t v) { fVerbose = v; }
  void SetGeoManager(TGeoManager* geo){fGeoMan = geo;};
  void SetSensorNamePar(PndSensorNamePar* par){fSensorNamePar = par;}
  
  //Bool_t cd(TString id); ///< as the cd command of TGeoManager just with the ID
  Bool_t cd(Int_t id); ///< as the cd command of TGeoManager just with the ID
  void FillLevelNames(); ///< fills vector<TString> fLevelNames with the names (or the paths) of the volumes down to the level given by fLevel
  
  TString FindNodePath(TGeoNode* node);
  void DiveDownToNode(TGeoNode* node);
  void cd(TGeoNode* node); ///<as cd command with the a node, not performant
  
  void DiveDownToNodeContainingString(TString name); ///< runs through the GeoManager until a path is found with a substring which matches to the given string
  
  void CreateUniqueSensorId(TString startName, std::vector<std::string> listOfSensitives); ///< Has to be called during simulation to create unique sensor id
  bool VolumeIsSensitive(TString& path, std::vector<std::string>& listOfSensitives); ///< Checks if the path contains a substring which matches one of the given strings in listOfSensitives. If not false is returned.
  
  void PrintSensorNames(){
	  if (fSensorNamePar)
		  fSensorNamePar->Print();
  }
  
  TObjArray* GetSensorNames(){
	  if (fSensorNamePar != 0)
		  return fSensorNamePar->GetSensorNames();
	  else
		  return 0;
  }
  
  Int_t GetRunId(TString mcFile);
  void GetGeoManager();
  void GetSensorNamePar();
  void FillSensorMap(){
	  fSensorNamePar->FillMap();
  }
  void InitRuntimeDb(TString parFileName);

  PndGeoHandling& operator= (const  PndGeoHandling&) {return *this;}

protected:
  InitStatus Init(){
	  fSensorNamePar->FillMap();
	  return kSUCCESS;
  }

  virtual InitStatus ReInit() {fGeoMan =0;fGeoMan=gGeoManager;return kSUCCESS;}
 
 private:
  static PndGeoHandling* fInstance;
  PndGeoHandling(PndGeoHandling& gh):
    FairTask(),
    fGeoMan(gh.fGeoMan),
    fSensorNamePar(gh.fSensorNamePar),
    fRtdb(gh.fRtdb),
    fLevelNames(gh.fLevelNames),
    fLevel(gh.fLevel),
    fFullPath(gh.fFullPath),
    fRunId(gh.fRunId),
    fVerbose(gh.fVerbose)
  {}
  
  void DiveDownToFillSensNamePar(std::vector<std::string> listOfSensitives);
  
  TGeoManager* fGeoMan;
  PndSensorNamePar* fSensorNamePar;
  FairRuntimeDb* fRtdb;
  // static PndGeoHandling* fGeoHandlingInstance;
  
  std::vector<TString> fLevelNames;
  Int_t fLevel;
  bool fFullPath;
  Int_t fRunId;
  Int_t fVerbose;
  ClassDef(PndGeoHandling,3);
};

#endif
