#include "checkRecUtility.C"

void drawEnergyVsTofOnFwdHit(const char* filename, const char* suffix = "_calib.root")
{
  TString outfile = filename;
  outfile.ReplaceAll(suffix, "_result.root");

  TString fwdfile = filename;
  fwdfile.ReplaceAll(suffix, "_FwdHit.root");

  TString elistfile = filename;
  elistfile.ReplaceAll(suffix, "_EntryList.root");

  checkAmpVsTof_Imp(filename,
                    fwdfile.Data(),
                    outfile.Data(),
                    "koalasim", "KoaRecDigi",
                    "fwdhit_time", "fwdhit_time",
                    false,
                    200, 0, 10,
                    2000, 400, 800,
                    elistfile.Data()
                    );
}
