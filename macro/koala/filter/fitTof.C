#include "KoaHistUtility.h"

using namespace KoaUtility;

void fitTof(const char* filename,
            const char* dirname,
            const char* histname,
            const char* outfilename
            )
{
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto histPtrs = getHistosByRecTdcChannelId<TH1D>(hdir,histname);

  fitHistos(histPtrs);

  printHistos(histPtrs,outfilename);

  delete fin;
}


