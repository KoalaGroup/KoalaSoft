#include <iostream>
#include "PndSdsStripDigiPar.h"
#include "TMath.h"

PndSdsStripDigiPar::PndSdsStripDigiPar(const char* name, const char* title, const char* context)
: FairParGenericSet(name,title,context),
    fTopPitch(0.),
    fBotPitch(0.),
    fOrient(0.),
    fSkew(0.),
    fThreshold(0.),
    fNoise(0.),
    fCSigma(0.),
    fChargeCut(0.),
    fSingleChargeCut(0.),
    fFeBusClock(0.),
    fTopAnchor(0.,0.),
    fBotAnchor(0.,0.),
    fFeChannels(0),
    fTopNrFE(0),
    fBotNrFE(0),
    fClusterMod(0),
    fClusterMean(0),
    fRadChannel(0),
    fRadTime(0),
    fSensType(""),
    fFeType(""),
    fChargeConvMethod(0)
{
  clear();
}

void PndSdsStripDigiPar::putParams(FairParamList* list)
{
  if(!list) return;
  
  list->add("top_pitch", fTopPitch);
  list->add("bot_pitch", fBotPitch);
  list->add("orient", fOrient);
  list->add("skew", fSkew);
  list->add("top_anchor_x", (Double_t)fTopAnchor.X());
  list->add("top_anchor_y", (Double_t)fTopAnchor.Y());
  list->add("bottom_anchor_x", (Double_t)fBotAnchor.X());
  list->add("bottom_anchor_y", (Double_t)fBotAnchor.Y());
  list->add("nr_fe_channels", fFeChannels);
  list->add("nr_fe_top", fTopNrFE);
  list->add("nr_fe_bottom", fBotNrFE);
  list->add("charge_threshold", fThreshold);
  list->add("charge_noise", fNoise);
  list->add("QCloudSigma", fCSigma);
  list->add("sens_Type", fSensType); //("sens_Type", fSensType, 's', 1)
  list->add("fe_Type", fFeType); //("fe_Type", fFeType, 's', 1)
  list->add("fe_BusClock", fFeBusClock);
  list->add("cluster_mod", fClusterMod);
  list->add("cluster_mean", fClusterMean);
  list->add("cluster_radchan", fRadChannel);
  list->add("cluster_radtime", fRadTime);
  list->add("cluster_corrchargecut", fChargeCut);
  list->add("cluster_singlechargecut", fSingleChargeCut);
  list->add("chargeconv_method", fChargeConvMethod);
  //TObjString* sens = new TObjString( fSensType.Data() );
  //list->addObject("sens_Type", sens);
  //TObjString* fe = new TObjString( fFeType.Data() );
  //list->addObject("fe_Type", fe);
}

Bool_t PndSdsStripDigiPar::getParams(FairParamList* list)
{
  if (!list) return kFALSE;
  
  if (!list->fill("top_pitch", &fTopPitch)) return kFALSE;
  if (!list->fill("bot_pitch", &fBotPitch)) return kFALSE;
  if (!list->fill("orient",&fOrient)) return kFALSE;
  if (!list->fill("skew",&fSkew)) return kFALSE;
  Double_t x,y;
  if (!list->fill("top_anchor_x", &x)) return kFALSE;
  if (!list->fill("top_anchor_y", &y)) return kFALSE;
  fTopAnchor.Set(x,y);
  if (!list->fill("bot_anchor_x", &x)) return kFALSE;
  if (!list->fill("bot_anchor_y", &y)) return kFALSE;
  fBotAnchor.Set(x,y);
  if (!list->fill("nr_fe_channels", &fFeChannels)) return kFALSE;
  if (!list->fill("nr_fe_top", &fTopNrFE)) return kFALSE;
  if (!list->fill("nr_fe_bottom", &fBotNrFE)) return kFALSE;
  if (!list->fill("charge_threshold",&fThreshold)) return kFALSE;
  if (!list->fill("charge_noise",&fNoise)) return kFALSE;
  if (!list->fill("QCloudSigma",&fCSigma)) return kFALSE;
  Text_t stName[80];
  if (!list->fill("sens_Type",stName,80)) return kFALSE;
  fSensType = stName;
  Text_t feName[80];
  if (!list->fill("fe_Type",feName,80)) return kFALSE;
  fFeType = feName;
  if (!list->fill("fe_BusClock",&fFeBusClock)) return kFALSE;
  if (!list->fill("cluster_mod", &fClusterMod)) return kFALSE;
  if (!list->fill("cluster_mean", &fClusterMean)) return kFALSE;
  if (!list->fill("cluster_radchan", &fRadChannel)) return kFALSE;
  if (!list->fill("cluster_radtime", &fRadTime)) return kFALSE;
  if (!list->fill("cluster_corrchargecut", &fChargeCut)) return kFALSE;
  if (!list->fill("cluster_singlechargecut", &fSingleChargeCut)) return kFALSE;
  
  if (!list->fill("chargeconv_method", &fChargeConvMethod)) return kFALSE;
  
  return kTRUE;
}

ClassImp(PndSdsStripDigiPar);

void PndSdsStripDigiPar::Print()
{
  std::cout<<"MVD Digitization Parameters:"<<std::endl;
  std::cout<<"   Sensor type name is          = "<<fSensType.Data()<<std::endl;
  std::cout<<"   Top Pitch    = "<<fTopPitch<<" cm"<<std::endl;
  std::cout<<"   Bottom Pitch = "<<fBotPitch<<" cm"<<std::endl;
  std::cout<<"   Strip Angle (Top) = "<<fOrient<<"rad = "<<fOrient/TMath::Pi()*180.<<" deg"<<std::endl;
  std::cout<<"   Skew Angle (Top->Bottom) = "<<fSkew<<"rad = "<<fSkew/TMath::Pi()*180.<<" deg"<<std::endl;
  std::cout<<"   Top Anchor   = ("<<fTopAnchor.X()<<","<<fTopAnchor.Y()<<")"<<std::endl;
  std::cout<<"   Bottom Anchor= ("<<fBotAnchor.X()<<","<<fBotAnchor.Y()<<")"<<std::endl;
  std::cout<<"   FE Channels  = "<<fFeChannels<<std::endl;
  std::cout<<"   Nr of Frontends (Top Side)   = "<<fTopNrFE<<std::endl;
  std::cout<<"   Nr of Frontends (Bottom Side)= "<<fBotNrFE<<std::endl;
  std::cout<<"   Charge Threshold (e-)        = "<<fThreshold<<std::endl;
  std::cout<<"   Noise (ENC+Dispersion) (e-)  = "<<fNoise<<std::endl;
  std::cout<<"   Charge cloud sigma  = "<<fCSigma<<" cm"<<std::endl;  
  std::cout<<"   charge conv. (0:ideal, 1:TOT)    = "<<fChargeConvMethod<<std::endl;
  std::cout<<"   Frontend type name is        = "<<fFeType.Data()<<std::endl;
  std::cout<<"   Clusterfinder Mode                    = "<<fClusterMod<<std::endl;
  std::cout<<"   Clusterfinder Mean Algorithm          = "<<fClusterMean<<std::endl;
  std::cout<<"   Clusterfinder Search Radius: Channels = "<<fRadChannel<<std::endl;
  std::cout<<"   Clusterfinder Search Radius: Time     = "<<fRadTime<<std::endl;
  std::cout<<"   Top/Bottom Charge correlation cut     = "<<fChargeCut<<std::endl;
  return;
}
