#ifndef KOARECCLUSTERCOLLECT_H
#define KOARECCLUSTERCOLLECT_H

#include "FairTask.h"
#include <string>

class TClonesArray;
class KoaMapEncoder;

/* Clustering of Recoil strip digis
 */
class KoaRecClusterCollect : public FairTask
{
public:
  /** Default constructor **/
  KoaRecClusterCollect();

  /** Destructor **/
  ~KoaRecClusterCollect();


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

  // Map Encoder
  KoaMapEncoder *fEncoder;

  KoaRecClusterCollect(const KoaRecClusterCollect&);
  KoaRecClusterCollect operator=(const KoaRecClusterCollect&);

  ClassDef(KoaRecClusterCollect,1);
};

#endif
