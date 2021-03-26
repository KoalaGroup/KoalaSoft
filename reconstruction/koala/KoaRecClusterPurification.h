#ifndef KOAREC_CLUSTERPURIFICATIOIN_H
#define KOAREC_CLUSTERPURIFICATIOIN_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <string>

class TClonesArray;

using namespace KoaUtility;

/*
 * Mode of threshold setting
 */
enum class ClusterPurificationMode { Absolute, Percentage, Multiple };

/* Filter out clusters which have energy below threshold
 */
class KoaRecClusterPurification : public FairTask
{
public:
  /** Default constructor **/
  KoaRecClusterPurification();

  /** Destructor **/
  ~KoaRecClusterPurification();


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

  void SetMode(ClusterPurificationMode mode) {
    fThreshMode = mode;
  }
  void SetThresholdFile(const char* name) {
    fThreshFile = name;
  }
  void SetThreshold(double size) {
    fThresh = size;
  }
  void SetPedestalFile(const char* name) {
    fPedestalFileName = name;
  }
  void SetAdcParaFile(const char* name) {
    fAdcParaFile = name;
  }

 private:
  void PurifyByAbsoluteValue();
  void PurifyByRelativeValue();

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

  // Flag indicates the meaning of threshold setting:
  // 1. multiples of noise sigma: Multiple
  // 2. percentil of cluster total energy: Percentage
  // 3. absolute value of threshold in energy (keV): Absolute
  ClusterPurificationMode fThreshMode = ClusterPurificationMode::Multiple;

  // In each case, two kinds configurations are possible:
  // 1. a global setting for all channels
  // 2. Channel-wise setting from parameter file

  // Adc calibrated paramter: from Adc to Energy (keV)
  // Noise parameter from text file using KoaTextUtility
  // These files are needed Multiple mode
  std::string fAdcParaFile = "";
  std::string fPedestalFileName = "";

  // Global setting of threshold:
  // 1. In Multiple mode, fThresh is the multiple of noise sigma
  // 2. In Percentage mode, fThresh is the percentage of cluster energy
  // 3. In Absolute mode, fThresh is the energy equivalent of threshold in keV
  double fThresh = 5;

  // Parameter file containing one column named 'Threshold',
  // which is the channel-wise setting of thresholds.
  // The meaning of the thresholds are the same as global setting scenario.
  std::string fThreshFile = "";

  // An array of final thresholds to be compared directly with data.
  ValueContainer<double> fNoiseThreshold;

  KoaRecClusterPurification(const KoaRecClusterPurification&);
  KoaRecClusterPurification operator=(const KoaRecClusterPurification&);

  ClassDef(KoaRecClusterPurification,1);
};

#endif
