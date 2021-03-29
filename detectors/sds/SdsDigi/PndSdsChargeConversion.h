#ifndef PNDSDSCHARGECONVERSION_H
#define PNDSDSCHARGECONVERSION_H

//! base class for energy loss <-> digi value conversion
//! @author D.-L.Pohl <d.pohl@fz-juelich.de>

#include <map>
#include "TObject.h"
#include "TString.h"
#include "PndSdsDigi.h"

enum ConvType{kUndefined,kIdeal,kToT,kADC};

class PndSdsChargeConversion : public TObject
  {
    public :
    
    PndSdsChargeConversion(ConvType type):  fParams(), it(), fConvType(type){};
    virtual ~PndSdsChargeConversion(){};
    virtual void StartExecute(){};
    virtual void EndExecute(){};
    virtual Double_t ChargeToDigiValue(Double_t Charge) = 0;		///< Converts a given charge in electrons into the electronics answer e.g. ToT [ns]
    virtual Double_t DigiValueToCharge(Double_t digi) = 0;			///< Converts a given digitized charge into charge in electrons
    virtual Double_t DigiValueToCharge(PndSdsDigi &digi);
    virtual Double_t GetRelativeError(Double_t Charge) = 0;
    virtual Double_t GetTimeStamp(Double_t tof, Double_t charge, Double_t MCEventTime) = 0;	///< absolute time stamp of a hit in ns (clock is taken into account)
    virtual Double_t GetTimeWalk(Double_t ){return 0;}; //charge //[R.K.03/2017] unused variable(s) ///< Time between hit in detector and the time stamp assigned to the hit
//    virtual Double_t GetTimeWalk(Int_t tot){
//    	return GetTimeWalk(DigiValueToCharge(tot));
//    }
    virtual Double_t GetTimeStampErrorAfterCorrection(){
    	return 1;
    }
    
    virtual Double_t GetTimeStep(){return 0;};

    Double_t GetParameter(TString param){
      it=fParams.find(param);
      if (it == fParams.end()){
        Error("GetParameter(TString param)","No parameter named: %s",param.Data());
        return -1;
      }
      return it->second;
    };
    void SetParameter(TString param, Double_t value){
      if (value < 0 ) Error("SetParameter(TString param, Double_t value)","invalid value for param: %s", param.Data());
      fParams.insert(std::pair<TString, Double_t>(param, value));
    };
    
    private :
    std::map<TString, Double_t> fParams;
    std::map<TString, Double_t>::iterator it;
    ConvType fConvType;
    
    
    ClassDef(PndSdsChargeConversion,2);
  };
#endif /* PNDSDSCHARGECONVERSION_H */
