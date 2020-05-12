#include "checkRecUtility.C"

void drawEnergyVsTimeOnFwdHit(const char* filename, const char* suffix = "_calib.root")
{
  TString outfile = filename;
  outfile.ReplaceAll(suffix, "_result.root");

  TString elistfile = filename;
  elistfile.ReplaceAll(suffix, "_EntryList.root");

  checkAmpVsTime_Imp(filename,
                     outfile.Data(),
                     "koalasim", "KoaRecDigi",
                     false,
                     200, 0, 10,
                     3000, 1100, 1700,
                     elistfile.Data()
                     );
}
