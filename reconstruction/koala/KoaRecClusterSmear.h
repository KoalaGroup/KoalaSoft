#ifndef KOAREC_CLUSTERSMEAR_H
#define KOAREC_CLUSTERSMEAR_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include "TRandom3.h"
#include <string>

class TClonesArray;

using namespace KoaUtility;

/* Smear the each digi's energy in the cluster.
 * The raw ADC count is discrete value. This brings the binning problem when
 * ADC value is converted to float energy value. A proper binning is needed
 * to prevent zig-zag pattern in the histograms. Moreover, for digis in the
 * cluster, they come from different channels with different calibration pa-
 * rameters. Thus, it's impossible to find a common bin width to smooth the
 * energy spectrum of cluster.
 *
 * Smearing means for each digi's energy value, it is smeared as a uniform
 * distribution in the minimum bin width range. Assuming the each ADC count cor-
 * responds to dE energy value and the converted energy is E. Then, the sme-
 * ared value is E + Uniform(E-1/2*dE, E+1/2*dE).
 */

class KoaRecClusterSmear : public FairTask
{
public:
  /** Default constructor **/
  KoaRecClusterSmear();

  /** Destructor **/
  ~KoaRecClusterSmear();


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
  void SetAdcParaFile(const char* name) {
    fAdcParaFile = name;
  }
  void SetTdcResolution(double value) {
    fTdcBinWidth = value;
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

  // Adc calibrated paramter: from Adc to Energy (keV)
  // Noise parameter from text file using KoaTextUtility
  // These files are needed Multiple mode
  std::string fAdcParaFile = "";

  // An array of final thresholds to be compared directly with data.
  ValueContainer<double> fAdcBinWidth;
  TRandom3 fRndEngine;
  double fTdcBinWidth=8./256; // TDC resolution, default is 32 ps

  KoaRecClusterSmear(const KoaRecClusterSmear&);
  KoaRecClusterSmear operator=(const KoaRecClusterSmear&);

  ClassDef(KoaRecClusterSmear,1);
};

#endif
