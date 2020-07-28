// -------------------------------------------------------------------------
// -----                 CbmStsHitProducerIdel header file             -----
// -----                  Created 10/01/06  by V. Friese               -----
// -------------------------------------------------------------------------


/** CbmStsHitProducerIdeal.h
 *@author V.Friese <v.friese@gsi.de>
 **
 ** The ideal hit producer produces hits of type CbmStsMapsHit by copying
 ** the MCPoint position. The position error is set to 1 mum, much 
 ** smaller than can be obtained by any detector. Using the hits from 
 ** this HitProducer is thus equivalent to using MC information
 ** directly, but with the correct data interface.
 **/


#ifndef PNDSDSPIXELCLUSTERTASK_H
#define PNDSDSPIXELCLUSTERTASK_H 

#include "PndSdsTask.h"
//#include "PndSdsGeoPar.h"
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "PndSdsPixel.h"
#include "PndSdsFE.h"
// #include "PndSdsCluster.h"
#include "FairGeoVector.h"
#include "FairGeoTransform.h"
#include "TVector3.h"
#include "TRandom.h"
#include "TGeoMatrix.h"
#include "TGeoBBox.h"
#include "PndSdsHybridHitProducer.h"
#include "PndSdsPixelDigiPar.h"
#include "PndSdsTotDigiPar.h"
#include "PndSdsChargeConversion.h"
#include "KoaDetectorList.h"
#include "PndGeoHandling.h"

#include "PndSdsPixelClusterFinder.h"
#include "PndSdsPixelBackMapping.h"

#include "FairTSBufferFunctional.h"

#include <string>
#include <vector>

class TClonesArray;

class PndSdsPixelClusterTask : public PndSdsTask
  {
  public:
    
    /** Default constructor **/  
    PndSdsPixelClusterTask();
    PndSdsPixelClusterTask(const PndSdsPixelClusterTask& other):
      PndSdsTask(),
      fUseNoiseSuppression(other.fUseNoiseSuppression),
      fFEModel(other.fFEModel),
      fDigiArray(other.fDigiArray),
      fDigiPar(other.fDigiPar),
      fChargeConverter(other.fChargeConverter),
      fGeoH(other.fGeoH),
      fClustBranchName(other.fClustBranchName),
      fClusterArray(other.fClusterArray),
      fHitArray(other.fHitArray),
      fEventHeader(other.fEventHeader),
      fFunctor(other.fFunctor),
      fStartFunctor(other.fStartFunctor), 
      fClusterType(other.fClusterType),
      fEventNr(other.fEventNr),
      fClusterFinder(other.fClusterFinder),
      fBackMapping(other.fBackMapping)
    {};
    /** Named constructor **/  
    PndSdsPixelClusterTask(const char* name);
    
    /** Destructor **/
    virtual ~PndSdsPixelClusterTask();
    PndSdsPixelClusterTask& operator=(PndSdsPixelClusterTask& other)
    {
      fUseNoiseSuppression=other.fUseNoiseSuppression;
      fFEModel=other.fFEModel;
      fDigiArray=other.fDigiArray;
      fDigiPar=other.fDigiPar;
      fChargeConverter=other.fChargeConverter;
      fGeoH=other.fGeoH;
      fClustBranchName=other.fClustBranchName;
      fClusterArray=other.fClusterArray;
      fHitArray=other.fHitArray;
      fEventHeader=other.fEventHeader;
      fFunctor=other.fFunctor;
      fStartFunctor=other.fStartFunctor; 
      fClusterType=other.fClusterType;
      fEventNr=other.fEventNr;
      fClusterFinder=other.fClusterFinder;
      fBackMapping=other.fBackMapping;
      return *this;
    };
   virtual void SetClusterFinder()=0;
   virtual void SetBackMapping()=0;

   void SetNoiseSuppression(Bool_t val){fUseNoiseSuppression = val;}
   Bool_t GetNoiseSuppression() const {return fUseNoiseSuppression;}

   virtual void SetInBranchId(){
		FairRootManager *ioman = FairRootManager::Instance();
		fInBranchId = ioman->GetBranchId(fInBranchName);
		std::cout << "InBranchId: " << fInBranchId << " for Branch: " << fInBranchName.Data() << std::endl;
		fClusterType = ioman->GetBranchId(fClustBranchName);
		std::cout << "fClusterType: " << fClusterType << " for Branch: " << fClustBranchName.Data() << std::endl;
	}
     
    /** Virtual method Init **/
    virtual void SetParContainers();
    virtual InitStatus Init();
    virtual InitStatus ReInit();
    virtual void FinishEvent();
    
	/** Methods to run with MQ **/ 
    virtual void SetClusterFinderMQ(TList*){}; // tempList //[R.K.03/2017] unused variable(s)
	virtual void SetBackMappingMQ(TList* ){}; // tempList //[R.K.03/2017] unused variable(s)
    virtual void InitMQ(TList* tempList);
    virtual void GetParList(TList* tempList);
    virtual void ExecMQ(TList* inputList,TList* outputList);
    
    /** Virtual method Exec **/
    void Exec(Option_t* opt);

    
  protected:
    
    Bool_t fUseNoiseSuppression; // switch to turn on/off noise cancellation by introducing an additional cluster threshold

    PndSdsFE* fFEModel; //!

    /** Input array of PndSdsDigis **/
    TClonesArray* fDigiArray;
    PndSdsPixelDigiPar* fDigiPar;
    PndSdsChargeConversion* fChargeConverter;
    PndGeoHandling* fGeoH; //!
    
    TString fClustBranchName;
    /** Output array of PndSdsHits **/
    TClonesArray* fClusterArray;
    TClonesArray* fHitArray;
    FairEventHeader* fEventHeader;

    BinaryFunctor* fFunctor; //!
    BinaryFunctor* fStartFunctor; //!
    
    Int_t fClusterType;
    Int_t fEventNr;
    
    void Register();
    void Reset();  
    void ProduceHits();
    virtual std::vector<PndSdsDigiPixel> ConvertAndFilter(TClonesArray* digidata); ///< convert TClonesArray into std::vector and remove corrupted data (for test beam analysis)
    
  PndSdsPixelClusterFinder* fClusterFinder; //!
  PndSdsPixelBackMapping* fBackMapping; //!
  
//   TGeoHMatrix GetTransformation (std::string detName);
//   void GetLocalHitPoints(PndSdsMCPoint* myPoint, FairGeoVector& myHitIn, FairGeoVector& myHitOut);
//   PndSdsHit CalcGlobalPoint(std::vector<PndSdsPixel> pixels);
//   TVector3 GetSensorDimensions(std::string detName);  
        
    ClassDef(PndSdsPixelClusterTask,4);
    
  };

#endif /* SDSCLUSTERTASK_H */

