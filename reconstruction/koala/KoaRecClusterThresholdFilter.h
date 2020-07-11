#ifndef KOAREC_CLUSTERTHRESHOLDFILTER_H
#define KOAREC_CLUSTERTHRESHOLDFILTER_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <string>

class TClonesArray;

using namespace KoaUtility;

/* Filter out clusters which have energy below threshold
 */
class KoaRecClusterThresholdFilter : public FairTask
{
public:
  /** Default constructor **/
  KoaRecClusterThresholdFilter();

  /** Destructor **/
  ~KoaRecClusterThresholdFilter();


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
  void SetInputClusterName(const char* name) {
    fInputName = name;
  }
  void SetOutputClusterName(const char* name) {
    fOutputName = name;
  }
  void SaveOutputCluster(bool flag = true) {
    fSaveOutput = flag;
  }
  void SetPedestalFile(const char* name) {
    fPedestalFileName = name;
  }
  void SetAdcParaFile(const char* name) {
    fAdcParaFile = name;
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
  TClonesArray* fInputClusters = nullptr;
  /** Output array to  new data level**/
  TClonesArray* fOutputClusters = nullptr;

  // Noise parameter in ADC
  std::string fPedestalFileName = "";

  // adc->E parameter
  std::string fAdcParaFile = "";

  ValueContainer<double> fNoiseThresh;
  double fThresh = 5.;

  KoaRecClusterThresholdFilter(const KoaRecClusterThresholdFilter&);
  KoaRecClusterThresholdFilter operator=(const KoaRecClusterThresholdFilter&);

  ClassDef(KoaRecClusterThresholdFilter,1);
};

#endif
