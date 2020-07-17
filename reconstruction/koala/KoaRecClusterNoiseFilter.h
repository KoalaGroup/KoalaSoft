#ifndef KOAREC_CLUSTERNOISEFILTER_H
#define KOAREC_CLUSTERNOISEFILTER_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <string>

class TClonesArray;
class KoaMapEncoder;

using namespace KoaUtility;

/* Filter out digi clusters which have ADC counts below threshold
 */
class KoaRecClusterNoiseFilter : public FairTask
{
public:
  /** Default constructor **/
  KoaRecClusterNoiseFilter();

  /** Destructor **/
  ~KoaRecClusterNoiseFilter();


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

  // set threshold in pedestal sigma
  void SetThreshold(double thresh) {
    fThresh = thresh;
  }

private:
  // Input digit branch name
  std::string fInputName = "";
  // Output digit branch name
  std::string fOutputName = "";
  // Flag indicate save output branch to file or in memory
  bool fSaveOutput = true;

  /** Input array from previous already existing data level **/
  TClonesArray* fInputDigis = nullptr;
  /** Output array to  new data level**/
  TClonesArray* fOutputDigis = nullptr;
  /** Buffer array for intermediate clustesrs **/
  TClonesArray* fClusters = nullptr;

  // Noise parameter in ADC
  std::string fPedestalFileName = "";

  ValueContainer<double> fNoiseMeans;
  ValueContainer<double> fNoiseSigmas;
  double fThresh = 5.;

  // Map Encoder
  KoaMapEncoder *fEncoder;

  KoaRecClusterNoiseFilter(const KoaRecClusterNoiseFilter&);
  KoaRecClusterNoiseFilter operator=(const KoaRecClusterNoiseFilter&);

  ClassDef(KoaRecClusterNoiseFilter,1);
};

#endif
