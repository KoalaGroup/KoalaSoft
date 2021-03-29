#ifndef KOA_FWDRECON_H
#define KOA_FWDRECON_H

#include "FairTask.h"

class TClonesArray;

/* A simple bridge to tranfer Fwd digis from Raw file to reconstructed file without any changes.
 */
class KoaFwdRecon : public FairTask
{
public:
  /** Default constructor **/
  KoaFwdRecon();

  /** Destructor **/
  ~KoaFwdRecon();

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
  std::string fInputName = "KoaFwdDigi";
  // Output digit branch name
  std::string fOutputName = "KoaFwdDigi";

  /** Input array from previous already existing data level **/
  TClonesArray* fInputDigis = nullptr;

  KoaFwdRecon(const KoaFwdRecon&);
  KoaFwdRecon operator=(const KoaFwdRecon&);

  ClassDef(KoaFwdRecon,1);
};


#endif
