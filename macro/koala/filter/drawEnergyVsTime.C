#include "checkRecUtility.C"

void drawEnergyVsTime(const char* filename, const char* suffix = "_calib.root")
{
  TString outfile = filename;
  outfile.ReplaceAll(suffix, "_result.root");

  checkAmpVsTime_Imp(filename,
                     outfile.Data(),
                     "koalasim", "KoaRecDigi",
                     false,
                     200, 0, 10,
                     3000, 1100, 1700,
                     nullptr
                     );
}
