#ifndef KOAREC_CLUSTERSEEDFILTER_H
#define KOAREC_CLUSTERSEEDFILTER_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <map>
#include <string>

class TClonesArray;
class KoaRecDigi;
class KoaMapEncoder;

using namespace KoaUtility;

/* Function:
 *   Filter out clusters without seed digi and clusters with overflow digis.
 *
 * Steps:
 *   1. Collect digis into cluster first.
 *   2. Then, filter out clusters in which the max-energy digi is smaller than threshold
 *   3. Menatime, filter out clusters in which an overflow digi exists.
 *   4. The digis in the the left clusters are pushed into the output TClonesArray
 *      for usage in later tasks.
 * CAVEAT: digi array instead of cluster array output
 *
 * Input parameters in Pedestal mode:
 * 1. Pedestal parameter file
 * 2. Threshold: fThresh*PedSigma + PedMean
 *
 * Or use absolute ADC values in Trigger Mode:
 * 1. cluster seed threshold file for each channel
 * 2. Threshold: absolute ADC value for all channels
 */

enum class ClusterSeedMode { Trigger, Pedestal};

class KoaRecClusterSeedFilter : public FairTask
{
public:
  /** Default constructor **/
  KoaRecClusterSeedFilter();

  /** Destructor **/
  ~KoaRecClusterSeedFilter();


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

  void SetMode(ClusterSeedMode mode) {
    fThreshMode = mode;
  }
  void SetPedestalFile(const char* name) {
    fPedestalFile = name;
  }
  void SetThresholdFile(const char* name) {
    fThreshFile = name;
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
  /** Buffer array for intermediate clustesrs **/
  TClonesArray* fClusters = nullptr;

  ClusterSeedMode fThreshMode = ClusterSeedMode::Trigger;

  // Threshold parameters//

  // In Pedestal mode:
  //    fPedestalFile is the parameter file of pedestal fitting
  //    And together, fThresh is the multiple of pdestal noise sigma
  // In Trigger mode:
  //    fThreshFile is the absolute ADC value for each channel, typically from
  //    trigger threshold setting.
  //    Or alternative, set a global value for all channels using fThresh
  std::string fPedestalFile = "";
  double fThresh = 3.;

  std::string fThreshFile = "";

  // The array of final thresholds to be compared directly with data
  ValueContainer<double> fSeedThreshold;

  // Map Encoder
  KoaMapEncoder *fEncoder;

  KoaRecClusterSeedFilter(const KoaRecClusterSeedFilter&);
  KoaRecClusterSeedFilter operator=(const KoaRecClusterSeedFilter&);

  ClassDef(KoaRecClusterSeedFilter,1);
};


#endif
