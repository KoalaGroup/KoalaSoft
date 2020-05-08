#include "checkRecUtility.C"

void drawRecTime(const char* filename, const char* suffix = ".root")
{
  TString outfile = filename;
  outfile.ReplaceAll(suffix, "_result.root");

  checkRecTime_Imp(filename,
                   outfile.Data(),
                   "koalasim",
                   "KoaRecDigi",
                   8000, 1000, 1800, kBlack
                   );
}
