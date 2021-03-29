
/** PndSdsIdealClusterTask.h
 *@author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Ideal cluster finding task 
 */


#ifndef PndSdsIdealClusterTASK_H
#define PndSdsIdealClusterTASK_H 

#include "PndSdsTask.h"
//#include "PndSdsGeoPar.h"
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "PndSdsPixel.h"
#include "PndSdsIdealPixelClusterFinder.h"
#include "FairGeoVector.h"
#include "FairGeoTransform.h"
#include "TVector3.h"
#include "TRandom.h"
#include "TGeoMatrix.h"
#include "TGeoBBox.h"
#include "PndSdsHybridHitProducer.h"
#include "PndGeoHandling.h"
#include "PndSdsSimplePixelClusterFinder.h"
#include "PndSdsChargeWeightedPixelMapping.h"

#include <string>
#include <vector>
 
class TClonesArray;

class PndSdsIdealClusterTask : public PndSdsTask
{
 public:

    /** Default constructor **/  
    PndSdsIdealClusterTask();
    PndSdsIdealClusterTask(Double_t radius, Int_t FEcolumns, Int_t FErows, TString geoFile);
    PndSdsIdealClusterTask(PndSdsIdealClusterTask& other) :
      PndSdsTask(),
      fDigiArray(other.fDigiArray),
      fClustBranchName(other.fClustBranchName),
      fClusterType(other.fClusterType),
      fClusterArray(other.fClusterArray),
      fHitArray(other.fHitArray),
      fGeoH(other.fGeoH),
      fRadius(other.fRadius),
      fFEcolumns(other.fFEcolumns),
      fFErows(other.fFErows),
      fGeoFile(other.fGeoFile),
      finder(other.finder),
      mapping(other.mapping)
    {};
    /** Destructor **/
    virtual ~PndSdsIdealClusterTask();
    PndSdsIdealClusterTask& operator=(PndSdsIdealClusterTask& other)
    {
      fDigiArray=other.fDigiArray;
      fClustBranchName=other.fClustBranchName;
      fClusterType=other.fClusterType;
      fClusterArray=other.fClusterArray;
      fHitArray=other.fHitArray;
      fGeoH=other.fGeoH;
      fRadius=other.fRadius;
      fFEcolumns=other.fFEcolumns;
      fFErows=other.fFErows;
      fGeoFile=other.fGeoFile;
      finder=other.finder;
      mapping=other.mapping;
    return *this;
    };
   /** pure virtual method SetBranchNames
   **
   ** called by Init()
   ** function to set individual branch names
   **/
    /** Virtual method Init **/
    virtual void SetParContainers();
    virtual InitStatus Init();
    virtual InitStatus ReInit();

    virtual void SetInBranchId(){
 		  FairRootManager *ioman = FairRootManager::Instance();
 		  fInBranchId = ioman->GetBranchId(fInBranchName);
 		  std::cout << "InBranchId: " << fInBranchId << " for Branch: " << fInBranchName.Data() << std::endl;
 		  fClusterType = ioman->GetBranchId(fClustBranchName);
 	  }

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);
  
protected:

    /** Input array of PndSdsDigis **/
     TClonesArray* fDigiArray;

    TString fClustBranchName;
    Int_t fClusterType;

  /** Output array of PndSdsHits **/
      TClonesArray* fClusterArray;
      TClonesArray* fHitArray;
//   TClonesArray* fPixelArray;
//   TClonesArray* fFePixelArray;

      PndGeoHandling* fGeoH;
  
  void Register();
  void Reset();  
  void ProduceHits();

  Double_t fRadius;
  Int_t fFEcolumns;
  Int_t fFErows;
  TString fGeoFile;
  
//   TGeoHMatrix GetTransformation (std::string detName);
//   void GetLocalHitPoints(PndSdsMCPoint* myPoint, FairGeoVector& myHitIn, FairGeoVector& myHitOut);
//   PndSdsHit CalcGlobalPoint(std::vector<PndSdsPixel> pixels);
//   TVector3 GetSensorDimensions(std::string detName);  

  PndSdsIdealPixelClusterFinder* finder;
  PndSdsChargeWeightedPixelMapping* mapping;

  ClassDef(PndSdsIdealClusterTask,1);

};

#endif /* PndSdsIdealClusterTASK_H */

