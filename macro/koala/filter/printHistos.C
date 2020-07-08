#include "KoaHistUtility.h"

using namespace KoaUtility;

void printHistosByChannelId(const char* filename,
                            const char* dirname,
                            const char* histname,
                            const char* outfilename
                            )
{
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto histPtrs = getHistosByChannelId<TH1D>(hdir,histname,true);

  printH1Ds(histPtrs,outfilename);

  delete fin;
}


void printHistosByTdcChannelId(const char* filename,
                               const char* dirname,
                               const char* histname,
                               const char* outfilename
                               )
{
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto histPtrs = getHistosByRecTdcChannelId<TH2D>(hdir,histname);

  printH2Ds(histPtrs,outfilename);

  delete fin;
}

void printHistosByDetectorId(const char* filename,
                             const char* dirname,
                             const char* histname,
                             const char* outfilename
                             )
{
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto histPtrs = getHistosByDetectorId<TH2D>(hdir,histname,true);

  printH2Ds(histPtrs,outfilename);

  delete fin;
}
