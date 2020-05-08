#include "checkRecUtility.C"

void drawRecEnergy(const char* filename, const char* suffix = "_calib.root")
{
  TString outfile = filename;
  outfile.ReplaceAll(suffix, "_result.root");

  checkRecAmplitude_Imp(filename,
                        outfile.Data(),
                        "koalasim",
                        "KoaRecDigi",
                        false,
                        7000, 0, 70, kBlack,
                        false,
                        nullptr
                        );
}
