#ifndef KOARECENERGYRECON_H
#define KOARECENERGYRECON_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <map>
#include <string>

class TClonesArray;
class KoaRecDigi;

using namespace KoaUtility;

/* Transfer ADC counts of recoil front side channels to energy in keV.
 * In the same time, the digis which has energy smaller than the threshold will
 * be filtered out.
 *
 * Input parameters:
 * 1. ADC calibration parameter file
 * 2. Energy threshold
 */
class KoaRecEnergyRecon : public FairTask
{
public:
  /** Default constructor **/
  KoaRecEnergyRecon();

  /** Destructor **/
  ~KoaRecEnergyRecon();


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

  void SetAdcParaFile(const char* name) {
    fAdcParaFile = name;
  }

  // set threshold in unit of keV
  void SetThreshold(double thresh) {
    fThreshold = thresh;
  }

  void SetGeometryFile(const char* name){
    fGeometryFile = name;
  }

  void SetZOffset(double* zoffset){
    fZOffset[0] = zoffset[0];
    fZOffset[1] = zoffset[1];
    fZOffset[2] = zoffset[2];
    fZOffset[3] = zoffset[3];
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
  std::string fAdcParaFile = "";
  double fThreshold = 0.;
  ValueContainer<double> fP0;
  ValueContainer<double> fP1;

  std::string fGeometryFile = "";
  double fZOffset[4] = {0};
  ValueContainer<double> fAlpha;

  KoaRecEnergyRecon(const KoaRecEnergyRecon&);
  KoaRecEnergyRecon operator=(const KoaRecEnergyRecon&);

  ClassDef(KoaRecEnergyRecon,1);
};

#endif
