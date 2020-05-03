#ifndef KOA_RECREARRECON_H
#define KOA_RECREARRECON_H

#include "FairTask.h"

class TClonesArray;

/* A simple bridge to tranfer Recoil Rear side  digis from Raw file to reconstructed file without any changes.
 */
class KoaRecRearRecon : public FairTask
{
public:
  /** Default constructor **/
  KoaRecRearRecon();

  /** Destructor **/
  ~KoaRecRearRecon();

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

private:
  // Input digit branch name
  std::string fInputName = "KoaRecRearDigi";
  // Output digit branch name
  std::string fOutputName = "KoaRecRearDigi";

  /** Input array from previous already existing data level **/
  TClonesArray* fInputDigis = nullptr;

  KoaRecRearRecon(const KoaRecRearRecon&);
  KoaRecRearRecon operator=(const KoaRecRearRecon&);

  ClassDef(KoaRecRearRecon,1);
};


#endif
