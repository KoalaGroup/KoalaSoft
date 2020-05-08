#include "checkRecUtility.C"

void drawRecEnergyOnFwdHit(const char* filename, const char* suffix = "_calib.root")
{
  TString outfile = filename;
  outfile.ReplaceAll(suffix, "_result.root");

  TString elistfile = filename;
  elistfile.ReplaceAll(suffix, "_EntryList.root");

  checkRecAmplitude_Imp(filename,
                        outfile.Data(),
                        "koalasim",
                        "KoaRecDigi",
                        false,
                        7000, 0, 70, kBlue,
                        false,
                        elistfile.Data()
                        );
}
