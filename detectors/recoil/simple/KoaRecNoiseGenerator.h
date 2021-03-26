#ifndef KOAREC_NOISEGENERATOR_H
#define KOAREC_NOISEGENERATOR_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include "TRandom3.h"
#include <map>
#include <string>

class TClonesArray;

using namespace KoaUtility;

/* Generate ADC pedestal noise in ADC counts based on pedestal parameters
 *
 * Input parameter file:
 *   ADC pedestal fitting result
 */

class KoaRecNoiseGenerator : public FairTask
{
public:
  /** Default constructor **/
  KoaRecNoiseGenerator();

  /** Destructor **/
  ~KoaRecNoiseGenerator();


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
  void SetOutputDigiName(const char* name) {
    fOutputName = name;
  }

  void SetPedestalFile(const char* name) {
    fPedestalFileName = name;
  }

private:
  // Output digit branch name
  std::string fOutputName = "";

  /** Output array to  new data level**/
  TClonesArray* fOutputDigis = nullptr;

  // Noise parameter
  std::string fPedestalFileName = "";
  ValueContainer<double> fMeans;
  ValueContainer<double> fSigmas;

  TRandom3 fRndEngine;

  KoaRecNoiseGenerator(const KoaRecNoiseGenerator&);
  KoaRecNoiseGenerator operator=(const KoaRecNoiseGenerator&);

  ClassDef(KoaRecNoiseGenerator,1);
};


#endif
