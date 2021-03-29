// -------------------------------------------------------------------------
// -----                 PndSdsRecoTask header file             -----
// -----                  Created 20/03/07  by R.Kliemt               -----
// -------------------------------------------------------------------------


/** PndSdsRecoTask.h
 *@author R.Kliemt <r.kliemt@physik.tu-dresden.de>
 **
 ** The ideal tracking produces tracks of type PndSdsHit by using MC information
 ** directly, but with the correct data interface.
 **/


#ifndef PNDSDSRECOTASK_H
#define PNDSDSRECOTASK_H

// Root includes
#include "TVector3.h"
#include "TRandom.h"
#include "TString.h"
#include "TGeoManager.h"

// framework includes
#include "PndSdsTask.h"

// PndSds includes
#include "PndSdsMCPoint.h"

class TClonesArray;
// class PndSdsHitMaker;

class PndSdsRecoTask : public PndSdsTask
{
 public:

  /** Default constructor **/
  PndSdsRecoTask();

//   PndSdsRecoTask(Double_t sx, Double_t sy, Double_t sz);
  PndSdsRecoTask(std::string type);


  /** Destructor **/
  virtual ~PndSdsRecoTask();

  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();


  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);


 protected:
//   PndSdsHitMaker*      fHitMaker;

  Int_t fevent;

  TString fPixelBranchName;
  TString fStripBranchName;

  /** Input array of Points **/
  TClonesArray* fDigiPixelArray;
  TClonesArray* fDigiStripArray;
//   TClonesArray* fMctruthArray;

  /** Output array of Hits **/
  TClonesArray* fHitOutputArray;
  /** Properties **/
  std::string fMakerType;
  Double_t fSigmaX;       // Variance vector of sensor smearing
  Double_t fSigmaY;       // Variance vector of sensor smearing
  Double_t fSigmaZ;       // Variance vector of sensor smearing
  PndSdsMCPoint* fCurrentPndSdsMCPoint;
  TGeoHMatrix* fCurrentTransMat;
  TMatrixT<Double_t> fHitCovMatrix;
  /** smearing and geometry access **/
  void InitTransMat();
  void smear(TVector3& pos);
  void smearLocal(TVector3& pos);
  void CalcDetPlane(TVector3& o,TVector3& u,TVector3& v);


  void Register();

  void Reset();

  void ProduceHits();

  ClassDef(PndSdsRecoTask,1);

};

#endif
