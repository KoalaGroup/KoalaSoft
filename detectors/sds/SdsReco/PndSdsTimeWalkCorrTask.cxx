/*
 * PndSdsTimeWalkCorrTask.cxx
 *
 *  Created on: Aug 27, 2010
 *      Author: Simone Esch
 */

#include "PndSdsTimeWalkCorrTask.h"
#include "PndSdsFESimple.h"


ClassImp(PndSdsTimeWalkCorrTask);

// -----   Default constructor   -------------------------------------------

PndSdsTimeWalkCorrTask::PndSdsTimeWalkCorrTask():
   PndSdsTask("SDS TimeWalkCorrection Task"),
	  fDigiArray(NULL),
	  fDigiCorrArray(NULL),
    fDigiPar(NULL),
    fDigiTotPar(NULL),
    fFEModel(NULL),
    fVerbose(0)
{
	SetPersistency(kTRUE);
}

// -----   Named constructor   ---------------------------------------------
PndSdsTimeWalkCorrTask::PndSdsTimeWalkCorrTask(const char* name):
   PndSdsTask(name),
	  fDigiArray(NULL),
	  fDigiCorrArray(NULL),
    fDigiPar(NULL),
    fDigiTotPar(NULL),
    fFEModel(NULL),
    fVerbose(1)
{
	SetPersistency(kTRUE);
}


PndSdsTimeWalkCorrTask::~PndSdsTimeWalkCorrTask() {
}

// -----   Initialization  of Parameter Containers -------------------------
void PndSdsTimeWalkCorrTask::SetParContainers()
{
  if( ! fDigiPar) Fatal("SetParContainers","No digitiztiopn parameters specified");
  if( ! fDigiTotPar ) Fatal("SetParContainers","No tot digitiztiopn parameters specified");
  if(fVerbose>1) Info("SetParContainers","done.");
  return;
}


// -----   Public method Init   --------------------------------------------
InitStatus PndSdsTimeWalkCorrTask::Init()
{
  SetBranchNames();

  fFEModel = new PndSdsFESimple();

  FairRootManager* ioman = FairRootManager::Instance();

  if ( ! ioman )
  {
     std::cout << "-E- PndSdsTimeWalkCorrTask::Init: "
     << "RootManager not instantiated!" << std::endl;
     return kFATAL;
  }

  // Get input array
  fDigiArray = (TClonesArray*) ioman->GetTClonesArray(fInBranchName);

  if ( ! fDigiArray )
  {
	  std::cout << "-W- PndSdsTimeWalkCorrTask::Init: " << "No SDSDigi array!" << std::endl;
	  return kERROR;
  }

  // Create output array
  fDigiCorrArray = ioman->Register(fOutBranchName, "PndSdsDigiPixel", fFolderName, GetPersistency());

  SetInBranchId();

  fDigiPar->Print();
  fDigiTotPar->Print();

  std::cout << "-I- PndSdsTimeWalkCorrTask: Initialisation successfull" << std::endl;

  return kSUCCESS;
}
// -------------------------------------------------------------------------

void PndSdsTimeWalkCorrTask::Exec(Option_t*)
{

	if ( ! fDigiCorrArray ) Fatal("Exec", "No ClusterArray");
	fDigiCorrArray->Delete();


	Int_t nPoints = fDigiArray->GetEntriesFast();

	  for (Int_t iPoint = 0; iPoint < nPoints; iPoint++)
	  {
		  PndSdsDigiPixel myDigi = *(PndSdsDigiPixel*)(fDigiArray->At(iPoint));
		  myDigi.SetTimeStamp(myDigi.GetTimeStamp() - fFEModel->GetTimeWalkFromTot(myDigi.GetCharge()) - fFEModel->GetTimeStep()/2);
		  new ((*fDigiCorrArray)[iPoint])PndSdsDigiPixel(myDigi);
	  }

}

void PndSdsTimeWalkCorrTask::FinishTask()
{
	if ( ! fDigiCorrArray ) Fatal("Exec", "No ClusterArray");
	fDigiCorrArray->Delete();


	Int_t nPoints = fDigiArray->GetEntriesFast();

	  for (Int_t iPoint = 0; iPoint < nPoints; iPoint++)
	  {
		  PndSdsDigiPixel myDigi = *(PndSdsDigiPixel*)(fDigiArray->At(iPoint));
		  myDigi.SetTimeStamp(myDigi.GetTimeStamp() - fFEModel->GetTimeWalkFromTot(myDigi.GetCharge()) - fFEModel->GetTimeStep()/2);
		  new ((*fDigiCorrArray)[iPoint])PndSdsDigiPixel(myDigi);
	  }
}
