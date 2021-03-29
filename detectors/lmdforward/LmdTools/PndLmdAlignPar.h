//
// C++ Interface: PndLmdAlignPar
//
#ifndef PNDLMDALIGNPAR_H
#define PNDLMDALIGNPAR_H

#include <vector>
#include <TVector2.h>
#include <TString.h>
#include <TObjString.h>

#include "FairParGenericSet.h"
#include "FairParamList.h"

using namespace std;
//! Alignment Parameter Class for LMD
class PndLmdAlignPar : public FairParGenericSet
  {
    public :
		PndLmdAlignPar (const char* name="PndLmdAlignPar",
                        const char* title="PndLmd alignment parameter",
                        const char* context="TestDefaultContext");
		~PndLmdAlignPar(void){};
		void clear(void){};
		void putParams(FairParamList* list);
		Bool_t getParams(FairParamList* list);
		
		void Print();
		/** Accessor functions **/
		Double_t GetShiftX(int j) const {return fshift_x[j];}
		Double_t GetShiftY(int j) const {return fshift_y[j];}
		Double_t GetShiftZ(int j) const {return fshift_z[j];}
		Double_t GetRotateX(int j) const {return frotate_x[j];}
		Double_t GetRotateY(int j) const {return frotate_y[j];}
		Double_t GetRotateZ(int j) const {return frotate_z[j];}
		Int_t GetNsensors(){return fsensors;}
		Int_t GetNsides(){return fsides;}
		Int_t GetNplanes(){return fplanes;}
		//for pixel design
		Int_t GetNhalfs(){return fhalfs;}
		Int_t GetNmodules(){return fmodules;}
  private:
    //Planes parameters
    Int_t fsensors;//Number of sensors per module, 1 side
    Int_t fsides;//Number of sides per module
    Int_t fplanes;//Number of planes
    Int_t fhalfs;
    Int_t fmodules;//Number of modules per plane half
    //Sensor parameters
    vector<double> fshift_x;
    vector<double> fshift_y;
    vector<double> fshift_z;
    vector<double> frotate_x;
    vector<double> frotate_y;
    vector<double> frotate_z;  

    ClassDef(PndLmdAlignPar,6);
  };

#endif /* !PNDSDSSTRIPDIGIPAR_H*/

