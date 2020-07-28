// -------------------------------------------------------------------------
// -----                 PndSdsIdealRecoTask header file             -----
// -----                  Created 20/03/07  by R.Kliemt               -----
// -------------------------------------------------------------------------


/** PndSdsIdealRecoTask.h
 *@author R.Kliemt <r.kliemt@physik.tu-dresden.de>
 **
 ** The ideal tracking produces tracks of type PndSdsHit by using MC information
 ** directly, but with the correct data interface.
 **/


#ifndef PNDSDSIDEALRECOTASK_H
#define PNDSDSIDEALRECOTASK_H

// Root includes
#include "TVector3.h"
#include "TRandom.h"
#include "TString.h"
#include "TGeoManager.h"

// framework includes
#include "PndSdsTask.h"

// PndSds includes
#include "PndSdsMCPoint.h"
#include "PndGeoHandling.h"

class TClonesArray;

class PndSdsIdealRecoTask : public PndSdsTask
{
 public:

  /** Default constructor **/
  PndSdsIdealRecoTask();

  PndSdsIdealRecoTask(Double_t sx, Double_t sy, Double_t sz);
  
  PndSdsIdealRecoTask(PndSdsIdealRecoTask& other) :
    PndSdsTask(),
    fGeoH(other.fGeoH),
    fPointArray(other.fPointArray),
    fMctruthArray(other.fMctruthArray),
    fHitOutputArray(other.fHitOutputArray),
    fSigmaX(other.fSigmaX),
    fSigmaY(other.fSigmaY),
    fSigmaZ(other.fSigmaZ),
    fCurrentPndSdsMCPoint(other.fCurrentPndSdsMCPoint),
    fCurrentTransMat(other.fCurrentTransMat),
    fHitCovMatrix(other.fHitCovMatrix)
  {}

  /** Destructor **/
  virtual ~PndSdsIdealRecoTask();

  PndSdsIdealRecoTask& operator=(PndSdsIdealRecoTask& other)
  {
    fGeoH=other.fGeoH;
    fPointArray=other.fPointArray;
    fMctruthArray=other.fMctruthArray;
    fHitOutputArray=other.fHitOutputArray;
    fSigmaX=other.fSigmaX;
    fSigmaY=other.fSigmaY;
    fSigmaZ=other.fSigmaZ;
    fCurrentPndSdsMCPoint=other.fCurrentPndSdsMCPoint;
    fCurrentTransMat=other.fCurrentTransMat;
    fHitCovMatrix=other.fHitCovMatrix;
    return *this;
  };
  
  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();


  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);
  
protected:

  PndGeoHandling* fGeoH;

  /** Input array of Points **/
  TClonesArray* fPointArray;
  TClonesArray* fMctruthArray;

  /** Output array of Hits **/
  TClonesArray* fHitOutputArray;
  /** Properties **/
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

  ClassDef(PndSdsIdealRecoTask,1);

};

#endif
