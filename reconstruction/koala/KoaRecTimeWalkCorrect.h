#ifndef KOARECTIMEWALKCORRECT_H
#define KOARECTIMEWALKCORRECT_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <map>
#include <string>

class TClonesArray;
class KoaRecDigi;

using namespace KoaUtility;

/* Correct the time walk effect based on ADC value
 *
 * Input parameters:
 * 1. TDC time walk parameter file
 */
class KoaRecTimeWalkCorrect : public FairTask
{
public:
  /** Default constructor **/
  KoaRecTimeWalkCorrect();

  /** Destructor **/
  ~KoaRecTimeWalkCorrect();


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

  void SetTdcParaFile(const char* name) {
    fTdcParaFile = name;
  }

  void SetTdcParaName(const char* name) {
    fTdcParaName = name;
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
  std::string fTdcParaFile = "";
  std::string fTdcParaName = "p0";
  ValueContainer<double> fP0;

  KoaRecTimeWalkCorrect(const KoaRecTimeWalkCorrect&);
  KoaRecTimeWalkCorrect operator=(const KoaRecTimeWalkCorrect&);

  ClassDef(KoaRecTimeWalkCorrect,1);
};



#endif
