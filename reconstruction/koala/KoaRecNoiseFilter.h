#ifndef KOARECNOISEFILTER_H
#define KOARECNOISEFILTER_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <map>
#include <string>

class TClonesArray;
class KoaRecDigi;
class KoaMapEncoder;

using namespace KoaUtility;

/* Filter out digis with a threshold above electronic noise level for the recoil
 * front channels (based on ADC pedestal)
 *
 * Input parameters:
 * 1. Pedestal parameter file
 * 2. Threshold: fThresh*PedSigma + PedMean
 */
class KoaRecNoiseFilter : public FairTask
{
public:
  /** Default constructor **/
  KoaRecNoiseFilter();

  /** Destructor **/
  ~KoaRecNoiseFilter();


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
  void SetThreshold(double thresh) {
    fThresh = thresh;
  }

private:
  // Input digit branch name
  std::string fInputName = "";
  // Output digit branch name
  std::string fOutputName = "";
  // Flag indicate save output branch to file or in memory
  bool fSaveOutput = false;

  /** Input array from previous already existing data level **/
  TClonesArray* fInputDigis = nullptr;
  /** Output array to  new data level**/
  TClonesArray* fOutputDigis = nullptr;

  // Noise parameter
  std::string fPedestalFileName = "";
  double fThresh = 5.;
  ValueContainer<double> fPedThresh;

  KoaRecNoiseFilter(const KoaRecNoiseFilter&);
  KoaRecNoiseFilter operator=(const KoaRecNoiseFilter&);

  ClassDef(KoaRecNoiseFilter,1);
};


#endif
