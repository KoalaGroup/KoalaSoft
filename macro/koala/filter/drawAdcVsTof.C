#include "checkRecUtility.C"

void drawAdcVsTof(const char* filename, const char* suffix = ".root")
{
  TString outfile = filename;
  outfile.ReplaceAll(suffix, "_result.root");

  TString fwdfile = filename;
  fwdfile.ReplaceAll(suffix, "_FwdHit.root");

  checkAmpVsTof_Imp(filename,
                    fwdfile.Data(),
                    outfile.Data(),
                    "koalasim", "KoaRecDigi",
                    "fwdhit_time", "fwdhit_time",
                    true,
                    4500, 0, 4500,
                    2000, 400, 800,
                    nullptr
                    );
}
