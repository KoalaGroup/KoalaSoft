#include "checkRecUtility.C"

void drawAdcVsTime(const char* filename, const char* suffix = ".root")
{
  TString outfile = filename;
  outfile.ReplaceAll(suffix, "_result.root");

  checkAmpVsTime_Imp(filename,
                     outfile.Data(),
                     "koalasim", "KoaRecDigi",
                     true,
                     5000, 0, 5000,
                     3000, 1100, 1700,
                     nullptr
                     );
}
