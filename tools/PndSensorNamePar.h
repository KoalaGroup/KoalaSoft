//
// C++ Interface: PndSensorNamePar
//
#ifndef PNDSENSORNAMEPAR_H
#define PNDSENSORNAMEPAR_H


#include "FairParGenericSet.h"
#include "FairParamList.h"
#include "FairRun.h"

#include "TObjArray.h"
#include "TObjString.h"

#include <iostream>
#include <map>

//! Unique match between SensorID and path in TGeoManager
class PndSensorNamePar : public FairParGenericSet
{
  public :
    PndSensorNamePar (const char* name="PndSensorNamePar",
          const char* title="Match between GeoManager path and SensorId",
          const char* context="TestDefaultContext");
    ~PndSensorNamePar(void){
    	if(fSensorNames) delete fSensorNames;
    };
    void clear(void){};
    void putParams(FairParamList* list);
    Bool_t getParams(FairParamList* list);

    virtual void print(){Print();}
    void Print();

    Int_t AddSensorName(TObjString* name);

    Int_t SensorInList(TObjString* name){
//    	for (int i = 0; i < fSensorNames->GetEntries();i++){
//    		TObjString* SensName = (TObjString*)fSensorNames->At(i);
//    		if (SensName->GetString() == name->GetString())
//    			return i;
//    	}
//    	return -1;
    	std::map<TString, Int_t>::iterator iter;
    	iter = fMapOfSensorNames.find(name->GetString());
    	if (iter != fMapOfSensorNames.end())
    		return iter->second;
    	else
    		return -1;
    }

    void FillMap(){
    	for (int i = 0; i < fSensorNames->GetEntries();i++){
			TObjString* SensName = (TObjString*)fSensorNames->At(i);
			fMapOfSensorNames[SensName->GetString()] = i;
			fMapOfSensorIndizes[i] = SensName->GetString();
		}
    }

    TString GetSensorName(Int_t index){
//    	if (index < fSensorNames->GetEntries()){
//			TObjString* myString = (TObjString*)fSensorNames->At(index);
//			return myString->GetString();
//    	}
//    	else{
//    		std::cout << "-E- PndSensorNamePar::GetSensorName index " << index
//    				  << " out of bounds: " << fSensorNames->GetEntries() << std::endl;
//    		return "";
//    	}
    	std::map<Int_t, TString>::const_iterator iter;
    	iter = fMapOfSensorIndizes.find(index);
    	if (iter != fMapOfSensorIndizes.end()) {
    		return iter->second;
    	} else {
    		std::cout << "-E- PndSensorNamePar::GetSensorName index " << index << " not in list!";
    		return "";
    	}

    }

    TObjArray* GetSensorNames() const{return fSensorNames;}

    PndSensorNamePar(const  PndSensorNamePar& L);
    PndSensorNamePar& operator= (const  PndSensorNamePar& L);

    friend std::ostream &operator<<( std::ostream &output, const PndSensorNamePar &par){
    	 output << "SensorNames:" << std::endl;
    	 output << "Entries: " << par.fSensorNames->GetEntries() << std::endl;

		for (std::map<Int_t, TString>::const_iterator iter = par.fMapOfSensorIndizes.begin(); iter != par.fMapOfSensorIndizes.end(); iter++){
			output << iter->first << ": " << iter->second.Data() << std::endl;
		}
		return output;
    }



  private:
    TObjArray* fSensorNames;
    std::map<TString, Int_t> fMapOfSensorNames; //!
    std::map<Int_t, TString> fMapOfSensorIndizes; //!



  ClassDef(PndSensorNamePar,1);
};

#endif /*!MVDSTRIPDIGIPAR_H*/
