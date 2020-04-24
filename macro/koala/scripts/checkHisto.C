#include "KoaHistUtility.h"

using namespace KoaUtility;

void checkHisto(const char* filename1, const char* dirname1, const char* hname1,
                const char* filename2, const char* dirname2, const char* hname2)
{
  // timer
  TStopwatch timer;

  //
  auto f1 = TFile::Open(filename1);
  auto hdir1 = getDirectory(f1, dirname1);
  auto histo1 = getHistosByChannelId<TH1D>(hdir1,hname1);

  auto f2 = TFile::Open(filename2);
  auto hdir2 = getDirectory(f2, dirname2);
  auto histo2 = getHistosByChannelId<TH1D>(hdir2,hname2);

  if (compareHistos(histo1,histo2)) {
    std::cout << "The two sets of histograms are same\n";
  }
  else {
    std::cout << "The two sets of histograms are different\n";
  }

  delete f1,f2;

  // timer stat
  timer.Stop();
  timer.Print();
}
