#ifndef KOAREC_CLUSTERSIZEFILTER_H
#define KOAREC_CLUSTERSIZEFILTER_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <string>

class TClonesArray;

using namespace KoaUtility;

/* Filter out clusters which have energy below threshold
 */
class KoaRecClusterSizeFilter : public FairTask
{
public:
  /** Default constructor **/
  KoaRecClusterSizeFilter();

  /** Destructor **/
  ~KoaRecClusterSizeFilter();


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
  void SetSizeParaFile(const char* name) {
    fSizeParaFile = name;
  }
  void SetSizeParameter(int size) {
    fThresh = size;
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

  // Cluster Size parameter file
  std::string fSizeParaFile = "";
  // global size parameter, all sensors have same size value
  int fThresh = 5;

  ValueContainer<int> fSizeThresholds;

  KoaRecClusterSizeFilter(const KoaRecClusterSizeFilter&);
  KoaRecClusterSizeFilter operator=(const KoaRecClusterSizeFilter&);

  ClassDef(KoaRecClusterSizeFilter,1);
};

#endif
