#include "KoaHistUtility.h"

using namespace KoaUtility;

/**
   Macro for finding the peaks and fit them in adc spectrums from pulser signals, normally in recoil energy calibration.

   Parmaters:
   1. inFile : the root file containing the adc spectrums, normally from script 'drawRecAdc.C'
   2. outFile : the root file where to output the result histograms,
                it also provides prefix for the output pdf and text file
   3. isPulser : flag indicating whether the histograms to be processed is Pulser calib or Source calib
   4. pulserFile : the text file containing the pulser setting ( for pulser calibration ) or
                   the energy peaks ( for alpha source calibration ), default is 'pulserSetting_*.txt' or 'sourceSetting.txt' under directory 'paramters'
   5. sigmaFile :  the text file containing the default sigma for searching peaks
                   default is 'pulserSigma_*.txt' or 'sourceSigma_*.txt' under directory 'parameters'
   6. pedestalFile :  the text file containing the default pedestal mean and sigma

   ****************************************************************************************************
   Procedure of peak search (using TSpectrum):
   1. read in the default sigma of each channel, which will be used as input parameter to TSpectrum
   2. read in the pulser/energy setting values
   3. configure other input parameters of TSpectrum.
      Two sets of parameters are used for pulser calibration and alpha source calibration:
      a) range (search_rangelow, search_rangehigh) : the range within which to search peaks
      b) max number of peaks (search_maxpeaks) : 2 * pulser/energy settings number
      c) threshold : peaks with height smaller than threshold is dismissed
   4. search peaks using TSpectrum and sorting the found peaks
   5. ignore peaks close to boundary
   6. fit each peak with Gaus, iterate 2 times to get more accurate result:
      iter 1: fit with peak value founded within 1 sigma range (the default sigma from config file)
      iter 2: fit with the mean and sigma from iter 1, within a range of [-3,3]*sigma for pulser file
              within [-1,3]*sigma for alpha source file
   7. save mean, mean error, sigma, sigma error from iter 2 as the final result
   
 **/

void fit_calib_adc(const char* inFile, const char* outFile,
                   bool isPulser, const char* pulserFile,
                   const char* sigmaFile, const char* pedestalFile)
{
  // timer
  TStopwatch timer;

  // include lambdas
  #include "fit_calib_lambda.C"

  // book histograms
  readHist(inFile);

  // reading configurations
  readPulserSetting(pulserFile);
  readDefaultSigma(sigmaFile);
  readPedestal(pedestalFile);

  // peak search
  searchPeaks();

  // fit the graphs
  fitGraph();

  // finish: output
  writeHist(outFile, "histograms");

  // 
  timer.Stop();
  timer.Print();
}
