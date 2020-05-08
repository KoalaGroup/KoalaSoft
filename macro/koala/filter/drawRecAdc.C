#include "checkRecUtility.C"

void drawRecAdc(const char* filename, const char* suffix = ".root")
{
  TString outfile = filename;
  outfile.ReplaceAll(suffix, "_result.root");

  checkRecAmplitude_Imp(filename,
                        outfile.Data(),
                        "koalasim",
                        "KoaRecDigi",
                        true,
                        8000, 0, 8000, kBlack,
                        false,
                        nullptr
                        );
}
