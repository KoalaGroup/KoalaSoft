#include "KoaHistUtility.h"
#include "KoaGraphUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaTextUtility.h"

using namespace KoaUtility;

void align_spectrum(
                    const char* profile_txtfile,
                    const char* filename,
                    const char* dirname = "Energy_Individual_-5.0_5.0",
                    const char* suffix = "Energy",
                    double mom = 2.2, // in GeV
                    double zoffset_si1 = 0., double zoffset_si2 = 0. // in mm
                    )
{
  auto profile_params = readParameterList<double>(profile_txtfile);

  auto it = findValueContainer(profile_params, "Z_strip(mm)");
  auto z_strips = it->second;
  it = findValueContainer(profile_params, "Z_ref(mm)");
  auto z_refs = it->second;
  it = findValueContainer(profile_params, "Z_peak(mm)");
  auto z_peaks = it->second;
  it = findValueContainer(profile_params, "Events_ref");
  auto evt_refs = it->second;
  it = findValueContainer(profile_params, "Width_ref(MeV)");
  auto width_refs = it->second;
  
  // input of the spectrum from the selected elastic events
  auto fin = TFile::Open(filename);
  TDirectory* hdir = getDirectory(fin, dirname);
  auto h1map = getHistosByRecTdcChannelId<TH1D>(hdir, suffix);

  for(auto item: h1map) {
    auto id = item.first;
    auto h1 = item.second;

    auto bins
  }
}
