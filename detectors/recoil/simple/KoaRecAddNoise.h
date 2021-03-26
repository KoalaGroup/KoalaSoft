/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_ADDNOISE_H
#define KOA_REC_ADDNOISE_H

#include "FairTask.h"
#include "TRandom3.h"
#include "KoaTextUtility.h"
#include <map>

class TClonesArray;
class KoaRecDigi;
class KoaRecNoisePar;
class KoaMapEncoder;

using namespace KoaUtility;

/* Add pedestal noise to all digi channels. Noises are equivalent energy (in keV)
 *
 * Two alternative input parameter sources:
 * 1. FairRoot style paramter file. In this case, all channels share the same parameter.
 * 2. User-provides text parameter file based on KoaTextUtility, where noises in ADC counts
 *    obtained from beam test are used.
 */

class KoaRecAddNoise : public FairTask
{
  public:

    /** Default constructor **/
    KoaRecAddNoise();

    /** Destructor **/
    ~KoaRecAddNoise();


    /** Initiliazation of task at the beginning of a run **/
    virtual InitStatus Init();

    /** ReInitiliazation of task when the runID changes **/
    virtual InitStatus ReInit();

    /** Executed for each event. **/
    virtual void Exec(Option_t* opt);

    /** Load the parameter container from the runtime database **/
    virtual void SetParContainers();

    /** Finish task called at the end of the run **/
    virtual void Finish();

    /** Reset eventwise counters **/
    void Reset();

 public:
  void SetInputDigiName(const char* name) {
    fInputName = name;
  }
  void SetOutputDigiName(const char* name) {
    fOutputName = name;
  }
  void SaveOutputDigi(bool flag = true) {
    fSaveOutput = flag;
  }
  void SetPedestalFile(const char* name) {
    fPedestalFileName = name;
  }
  void SetAdcParaFile(const char* name) {
    fAdcParaFile = name;
  }

 private:
    void AddNoise();

 private:
    // Input digit branch name
    std::string fInputName;
  // Output digit branch name
    std::string fOutputName;
    // Flag indicate save output branch to file or in memory
    bool fSaveOutput;

    /** Input array from previous already existing data level **/
    TClonesArray* fInputDigis;
    /** Output array to  new data level**/
    TClonesArray* fOutputDigis;

    // Noise parameter from FairRoot type parameter file, i.e. 'rec.par'
  KoaRecNoisePar* fNoisePar;
  // Noise parameter from text file using KoaTextUtility
  std::string fPedestalFileName = "";

  TRandom3 fRndEngine;
  ValueContainer<double> fNoiseMeans;
  ValueContainer<double> fNoiseSigmas;

  // Adc calibrated paramter: from Adc to Energy (keV)
  std::string fAdcParaFile = "";
  ValueContainer<double> fP0;
  ValueContainer<double> fP1;

  // MapEncoder
  KoaMapEncoder *fEncoder;

    KoaRecAddNoise(const KoaRecAddNoise&);
    KoaRecAddNoise operator=(const KoaRecAddNoise&);

    ClassDef(KoaRecAddNoise,1);
};

#endif
