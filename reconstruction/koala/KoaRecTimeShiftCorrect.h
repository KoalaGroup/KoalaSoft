#ifndef KOARECTIMESHIFTCORRECT_H
#define KOARECTIMESHIFTCORRECT_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <map>
#include <string>

class TClonesArray;
class KoaRecDigi;

using namespace KoaUtility;

/* Correct the time offset between TDC channels of recoil front channels.
 *
 * Input parameters:
 * 1. TDC time shift parameter file
 */
class KoaRecTimeShiftCorrect : public FairTask
{
public:
  /** Default constructor **/
  KoaRecTimeShiftCorrect();

  /** Destructor **/
  ~KoaRecTimeShiftCorrect();


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
  void CalcTimeShift(int ref_ch = 1);

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
  std::string fTdcParaName = "Mean";
  ValueContainer<double> fMean;
  ValueContainer<double> fTimeShift;

  KoaRecTimeShiftCorrect(const KoaRecTimeShiftCorrect&);
  KoaRecTimeShiftCorrect operator=(const KoaRecTimeShiftCorrect&);

  ClassDef(KoaRecTimeShiftCorrect,1);
};


#endif
