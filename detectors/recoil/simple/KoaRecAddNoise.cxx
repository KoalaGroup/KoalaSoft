/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "TClonesArray.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairLogger.h"
#include "KoaRecDigi.h"
#include "KoaRecAddNoise.h"
#include "KoaRecNoisePar.h"
#include "KoaMapEncoder.h"
#include "TRandom3.h"

// ---- Default constructor -------------------------------------------
KoaRecAddNoise::KoaRecAddNoise()
    :FairTask("KoaRecAddNoise"),
     fSaveOutput(true),
     fNoisePar(nullptr),
     fRndEngine(0)
{
  LOG(debug) << "Defaul Constructor of KoaRecAddNoise";
  fEncoder = KoaMapEncoder::Instance();
}

// ---- Destructor ----------------------------------------------------
KoaRecAddNoise::~KoaRecAddNoise()
{
  LOG(debug) << "Destructor of KoaRecAddNoise";

  if ( fOutputDigis ) {
    fOutputDigis->Delete();
    delete fOutputDigis;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecAddNoise::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecAddNoise";
  // Load all necessary parameter containers from the runtime data base
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  if (fPedestalFileName.empty()){
    LOG(info) << "Default pedestal noise parameters are used";
    fNoisePar = static_cast<KoaRecNoisePar*>(rtdb->getContainer("KoaRecNoisePar"));
  }
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecAddNoise::Init()
{
  LOG(debug) << "Initilization of KoaRecAddNoise";

  // Get a handle from the IO manager
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) LOG(fatal) << "No FairRootManager";

  if (fInputName.empty()) LOG(fatal) << "No input branch name set";
  fInputDigis = static_cast<TClonesArray*>(ioman->GetObject(fInputName.data()));
  if ( ! fInputDigis ) {
    LOG(error) << "No input branch " << fInputName;
    return kERROR;
  }

  // Create the TClonesArray for the output data and register it in the IO manager
  if (fOutputName.empty()) LOG(fatal) << "No output branch name set";
  fOutputDigis = new TClonesArray("KoaRecDigi", 300);
  ioman->Register(fOutputName.data(),"KoaRec",fOutputDigis,fSaveOutput);

  // initialize pedestal noise parameters

  // 1. read ADC calibration paramters
  if (fAdcParaFile.empty()) LOG(fatal) << "No ADC parameters found";
  auto adc_params = readParameterList<double>( fAdcParaFile);

  auto it = findValueContainer(adc_params, "AdcToE_p0");
  if ( it == adc_params.end()) {
    LOG(error) << "No \'AdcToE_p0\' parameter found in the ADC parameter file";
    return kERROR;
  }
  fP0 = it->second;

  it = findValueContainer(adc_params, "AdcToE_p1");
  if ( it == adc_params.end()) {
    LOG(error) << "No \'AdcToE_p1\' parameter found in the ADC parameter file";
    return kERROR;
  }
  fP1 = it->second;

  // 2. read pedestal parameters in ADC counts
  if (fPedestalFileName.empty()) {
    LOG(info) << "Default pedestal noise parameters are used";

    auto mean = fNoisePar->GetMean();
    auto sigma = fNoisePar->GetSigma();

    auto ChIDs = fEncoder->GetRecChIDs();
    for(auto id: ChIDs) {
      fNoiseMeans.emplace(id, mean);
      fNoiseSigmas.emplace(id, sigma);
    }
  }
  else {
    LOG(info) << "Pedestal noise parameters from " << fPedestalFileName << " are used";

    auto params = readParameterList<double>(fPedestalFileName);
    it = findValueContainer(params, "Mean");
    if ( it == params.end()) {
      LOG(error) << "No \'Mean\' parameter found in the pedestal file";
      return kERROR;
    }
    fNoiseMeans = it->second;

    it = findValueContainer(params, "Sigma");
    if ( it == params.end()) {
      LOG(error) << "No \'Sigma\' parameter found in the pedestal file";
      return kERROR;
    }
    fNoiseSigmas = it->second;
  }

  // 3. convert noise paramters from ADC value to Energy (keV)
  for(auto& item: fNoiseMeans) {
    auto& id = item.first;
    auto& mean = item.second;

    auto p0 = fP0[id];
    auto p1 = fP1[id];

    mean = p0 + p1*mean; // in keV
    fNoiseSigmas[id] *= p1; // in keV
  }

  // test
  // ParameterList<double> timeParameters;
  // auto& mean_time = addValueContainer(timeParameters, "Mean");
  // auto& sigma_time = addValueContainer(timeParameters, "Sigma");
  // mean_time = fNoiseMeans;
  // sigma_time = fNoiseSigmas;
  // printValueList(timeParameters,"test.txt");

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecAddNoise::ReInit()
{
  LOG(debug) << "Initilization of KoaRecAddNoise";

  // Load all necessary parameter containers from the runtime data base
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fNoisePar = static_cast<KoaRecNoisePar*>(rtdb->getContainer("KoaRecNoisePar"));

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecAddNoise::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecAddNoise";

  Reset();

  //
  AddNoise();
}

// ---- Finish --------------------------------------------------------
void KoaRecAddNoise::Finish()
{
  LOG(debug) << "Finish of KoaRecAddNoise";

}

// ---- Reset --------------------------------------------------------
void KoaRecAddNoise::Reset()
{
  LOG(debug) << "Reset of KoaRecAddNoise";

  fOutputDigis->Clear();
}

// ---- AddNoise --------------------------------------------------------
void KoaRecAddNoise::AddNoise()
{
  // temp buffer for input digs
  struct digi_type
  {
    double timestamp;
    double charge;

    digi_type(): timestamp(-1), charge(-1) {}
    digi_type(double ts, double ch): timestamp(ts), charge(ch) {}
  };

  std::map<int, digi_type> digi_map;

  //
  Int_t fNrDigits = fInputDigis->GetEntriesFast();
  for(Int_t iNrDigit =0; iNrDigit<fNrDigits; iNrDigit++){
    KoaRecDigi* curDigi = (KoaRecDigi*)fInputDigis->At(iNrDigit);
    auto ts = curDigi->GetTimeStamp();
    auto id = curDigi->GetDetID();
    auto charge = curDigi->GetCharge();

    auto insterted = digi_map.emplace(std::piecewise_construct,
                                   std::forward_as_tuple(id),
                                   std::forward_as_tuple(ts, charge));

    if( !insterted.second )
      LOG(fatal) << "KoaRecAddNoise: pre-existing digi in digi_map";

    if (digi_map[id].timestamp != ts || digi_map[id].charge != charge) {
      LOG(fatal) << "digi_map incorrect " << digi_map[id].timestamp << "/" << ts << "\t"
                 << digi_map[id].charge << "/" << charge;
    }

  }

  // Add noises to each channel
  int counter = 0;
  for(auto& item: fNoiseMeans){
    auto id = item.first;
    auto noise = fRndEngine.Gaus(item.second, fNoiseSigmas[id]);

    KoaRecDigi* outDigi = new ((*fOutputDigis)[counter++]) KoaRecDigi();
    outDigi->SetDetectorID(id);

    if( digi_map.find(id) != digi_map.end() ) {
      outDigi->SetTimeStamp(digi_map[id].timestamp);
      outDigi->SetCharge(digi_map[id].charge + noise);
    }
    else{
      outDigi->SetTimeStamp(-1);
      outDigi->SetCharge(noise);
    }
  }
}

ClassImp(KoaRecAddNoise)
