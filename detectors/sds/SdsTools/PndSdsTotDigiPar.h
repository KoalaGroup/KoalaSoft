//
// C++ Interface: PndSdsChargeConvDigiPar
//
#ifndef PNDSDSTOTDIGIPAR_H
#define PNDSDSTOTDIGIPAR_H

#include <TVector2.h>
#include "FairParGenericSet.h"
#include "FairParamList.h"

#include <iostream>

//! Charge Digitization Parameter Class for SDS

class PndSdsTotDigiPar : public FairParGenericSet
{
  public :
    PndSdsTotDigiPar (const char* name="PndSdsParCharConv",
          const char* title="PndSds charge digi parameter",
          const char* context="TestDefaultContext");
    ~PndSdsTotDigiPar(void){};
    void clear(void){};
    void putParams(FairParamList* list);
    Bool_t getParams(FairParamList* list);

    virtual void Print(std::ostream& out = std::cout) const;

    friend std::ostream& operator<<(std::ostream& out, const PndSdsTotDigiPar& dt){
    	dt.Print(out);
    	return out;
    }

    Double_t GetChargingTime() const {return fChargingTime;}
    Double_t GetConstCurrent() const {return fConstCurrent;}
    Double_t GetClockFrequency() const {return fClockFrequency;}

    void SetChargingTime(Double_t x){fChargingTime = x;}
    void SetConstCurrent(Double_t x){fConstCurrent = x;}
    void SetClockFrequency(Double_t x){fClockFrequency = x;};


  private:
    // Parameters
    Double_t fChargingTime;		// time until capacitor is loaded [ns]
    Double_t fConstCurrent;		// current unloading the capacitor [e/ns]
    Double_t fClockFrequency;	// clockfrequency of the readout chip [MHz]


  ClassDef(PndSdsTotDigiPar,1);
};

#endif /*!PNDSDSTOTDIGIPAR_H*/
