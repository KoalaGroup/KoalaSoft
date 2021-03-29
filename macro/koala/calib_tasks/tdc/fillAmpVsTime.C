#include "filter/checkRecUtility.C"

/*
 | Summary:
 | -------
 | Fill the raw spectrum: ADC, Timestamp, ADV VS Timestamp.
 | The output file name have a suffix "_result.root"
 |
 | Arguments:
 | ---------
 | *) inFileName : input root file name
 | *) outDir : directory for the output root file
 */

void fillAmpVsTime(const char* inFileName, const char* outDir)
{
  TString outFileName = gSystem->BaseName(inFileName);
  outFileName = gSystem->ConcatFileName(outDir, outFileName.Data());
  outFileName.ReplaceAll(".root","_result.root");

  checkAmpVsTime_Imp(inFileName,
                     outFileName.Data(),
                     "koalasim",
                     "KoaRecDigi",
                     true,
                     4010, -9.5, 4000.5,
                     6000, 1400, 2000,
                     nullptr
                     );
}
