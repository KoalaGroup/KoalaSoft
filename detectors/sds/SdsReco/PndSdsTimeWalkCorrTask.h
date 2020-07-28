/*
 * PndSdsPixelWimeWalkCorrTask.h
 *
 *  Created on: Aug 27, 2010
 *      Author: Simone Esch
 */

#ifndef PNDSDSTIMEWALKCORRTASK_H_
#define PNDSDSTIMEWALKCORRTASK_H_

#include "PndSdsTask.h"
#include "TClonesArray.h"
#include "PndSdsPixelDigiPar.h"
#include <vector>
#include "PndSdsDigiPixel.h"
#include "PndSdsDigiPixelMCInfo.h"
#include "PndSdsTotDigiPar.h"
#include "PndSdsTimeWalkCorrSimple.h"
#include "PndSdsFE.h"


class PndSdsTimeWalkCorrTask : public PndSdsTask {
public:
	PndSdsTimeWalkCorrTask();
	PndSdsTimeWalkCorrTask(const char* name);
  PndSdsTimeWalkCorrTask(PndSdsTimeWalkCorrTask& other) :
    PndSdsTask(),
	  fDigiArray(other.fDigiArray),
	  fDigiCorrArray(other.fDigiCorrArray),
    fDigiPar(other.fDigiPar),
    fDigiTotPar(other.fDigiTotPar),
    fFEModel(other.fFEModel),
    fVerbose(other.fVerbose)
  {};
	virtual ~PndSdsTimeWalkCorrTask();
  PndSdsTimeWalkCorrTask& operator=(PndSdsTimeWalkCorrTask& other)
  {
	  fDigiArray=other.fDigiArray;
	  fDigiCorrArray=other.fDigiCorrArray;
    fDigiPar=other.fDigiPar;
    fDigiTotPar=other.fDigiTotPar;
    fFEModel=other.fFEModel;
    fVerbose=other.fVerbose;
    return *this;
  };
	InitStatus Init();
	void SetParContainers();
	void Exec(Option_t* opt);
	  virtual void FinishTask();
protected:
	TClonesArray* fDigiArray;
	TClonesArray* fDigiCorrArray;
    PndSdsPixelDigiPar* fDigiPar;
    PndSdsTotDigiPar* fDigiTotPar;
    PndSdsFE* fFEModel;
    Int_t fVerbose;

    ClassDef(PndSdsTimeWalkCorrTask, 1);
};

#endif /* PNDSDSTIMEWALKCORRTASK_H_ */
