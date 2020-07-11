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

/* Collect digis into cluster first.
 * Then, filter out clusters in which the max-energy digi is smaller than threshold
 * The digis in the the remaining clusters are pushed into the output TClonesArray
 * for usage in later tasks.
 *
 * Input parameters:
 * 1. Pedestal parameter file
 * 2. Threshold: fThresh*PedSigma + PedMean
 */

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
  double fThresh = 3.;
  ValueContainer<double> fPedThresh;

  // Map Encoder
  KoaMapEncoder *fEncoder;

  KoaRecClusterSeedFilter(const KoaRecClusterSeedFilter&);
  KoaRecClusterSeedFilter operator=(const KoaRecClusterSeedFilter&);

  ClassDef(KoaRecClusterSeedFilter,1);
};


#endif
