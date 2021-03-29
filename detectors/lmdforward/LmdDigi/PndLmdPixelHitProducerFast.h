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


#ifndef PNDLMDPIXELHITPRODUCERFAST_H
#define PNDLMDPIXELHITPRODUCERFAST_H 

#include "PndSdsTask.h"
//#include "PndSdsGeoPar.h"
#include "KoaDetectorList.h"

#include "TVector3.h"
#include "TRandom.h"
 
class TClonesArray;

class PndLmdPixelHitProducerFast : public PndSdsTask
{
 public:

  /** Default constructor **/  
  PndLmdPixelHitProducerFast();
  PndLmdPixelHitProducerFast(Double_t pixelx, Double_t pixely);

  /** Named constructor **/  
  PndLmdPixelHitProducerFast(const char* name);

  /** Destructor **/
  virtual ~PndLmdPixelHitProducerFast();


  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();

  /** pure virtual method SetBranchNames
   **
   ** called by Init()
   ** function to set individual branch names
   **/
  virtual void SetBranchNames();
  virtual void SetBranchNames(TString inBranchname, TString outBranchname, TString folderName);

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  void SetPersistance(Bool_t p = kTRUE) {SetPersistency(p);};
  Bool_t GetPersistance() {return GetPersistency();};
  
protected:

  Double_t fPixelSizeX; //to round MC-Hit x-position
  Double_t fPixelSizeY; //to round MC-Hit y-position
  
  
  /** Input array of PndSdsMCPoints **/
  TClonesArray* fPointArray;

  /** Output array of PndSdsHits **/
  TClonesArray* fHitArray;  

  //PndSdsGeoPar* fGeoPar;
  
  void Register();
  
  void Reset();
  
  void ProduceHits();

  ClassDef(PndLmdPixelHitProducerFast,1);

};

#endif
