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

void fill(const char* inFileName, const char* outDir)
{
  TString outFileName = gSystem->BaseName(inFileName);
  outFileName = gSystem->ConcatFileName(outDir, outFileName.Data());
  outFileName.ReplaceAll(".root","_result.root");

  checkRecAmplitude_Imp(inFileName,
                        outFileName.Data(),
                        "koalasim",
                        "KoaRecDigi",
                        true,
                        8010, -9.5, 8000.5, kBlack,
                        false,
                        nullptr
                        );

  checkRecTime_Imp(inFileName,
                   outFileName.Data(),
                   "koalasim",
                   "KoaRecDigi",
                   3000, 1400, 1700, kBlack,
                   nullptr
                   );

  // checkAmpVsTime_Imp(inFileName,
  //                    outFileName.Data(),
  //                    "koalasim",
  //                    "KoaRecDigi",
  //                    true,
  //                    695, 50.5, 7000.5,
  //                    150, 1400, 1700,
  //                    nullptr
  //                    );
}
