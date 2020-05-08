#include "checkRecUtility.C"

void drawRecAdcOnFwdHitAndTimeValid(const char* filename, const char* suffix = ".root")
{
  TString outfile = filename;
  outfile.ReplaceAll(suffix, "_result.root");

  TString elistfile = filename;
  elistfile.ReplaceAll(suffix, "_EntryList.root");

  checkRecAmplitude_Imp(filename,
                        outfile.Data(),
                        "koalasim",
                        "KoaRecDigi",
                        true,
                        8000, 0, 8000, kRed,
                        true,
                        elistfile.Data()
                        );
}
