#include "checkRecUtility.C"

void drawRecTimeOnFwdHit(const char* filename, const char* suffix = ".root")
{
  TString outfile = filename;
  outfile.ReplaceAll(suffix, "_result.root");

  TString elistfile = filename;
  elistfile.ReplaceAll(suffix, "_EntryList.root");

  checkRecTime_Imp(filename,
                   outfile.Data(),
                   "koalasim",
                   "KoaRecDigi",
                   8000, 1000, 1800, kBlue,
                   elistfile.Data()
                   );
}
