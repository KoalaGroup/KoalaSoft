#include <iostream>
#include "PndSensorNamePar.h"

PndSensorNamePar::PndSensorNamePar(const char* name, const char* title, const char* context)
  : FairParGenericSet(name,title,context), fSensorNames()
{
  clear();
  fSensorNames = new TObjArray();
  fSensorNames->SetOwner(kTRUE);

}

PndSensorNamePar::PndSensorNamePar(const  PndSensorNamePar& L) :
FairParGenericSet(L)
{
	fSensorNames = new TObjArray(*(L.GetSensorNames()));
}

PndSensorNamePar& PndSensorNamePar::operator= (const  PndSensorNamePar& L)
{
	fSensorNames = new TObjArray(*(L.GetSensorNames()));
	return *this;
}

void PndSensorNamePar::putParams(FairParamList* list)
{
  if(!list) return;
  list->addObject("SensorNames", fSensorNames);
}

Bool_t PndSensorNamePar::getParams(FairParamList* list)
{
  if (!list) return kFALSE;
  if (!list->fillObject("SensorNames",fSensorNames)) return kFALSE;
  FillMap();
  return kTRUE;
}

Int_t  PndSensorNamePar::AddSensorName(TObjString* name)
{
	if (SensorInList(name) < 0) {
		fSensorNames->AddLast(name);
		this->setChanged();
		FairRun *fRun = FairRun::Instance();
		this->setInputVersion(fRun->GetRunId(), 1);
		fMapOfSensorNames[name->GetString()] = fSensorNames->GetEntries() - 1;
		fMapOfSensorIndizes[fSensorNames->GetEntries() - 1] = name->GetString();

		return fSensorNames->GetEntries() - 1;
	} else
		return SensorInList(name);

}

ClassImp(PndSensorNamePar);

void PndSensorNamePar::Print()
{
    std::cout<<"SensorNames:"<<std::endl;
    std::cout<< "Entries: " << fSensorNames->GetEntries() << std::endl;
//    for (int i = 0; i < fSensorNames->GetEntries(); i++){
//    	TObjString* mySensName = (TObjString*)fSensorNames->At(i);
//    	std::cout << i << ": " << mySensName->GetString().Data() << std::endl;
//    }
    for (std::map<Int_t, TString>::iterator iter = fMapOfSensorIndizes.begin(); iter != fMapOfSensorIndizes.end(); iter++){
    	std::cout << iter->first << ": " << iter->second.Data() << std::endl;
    }
}
