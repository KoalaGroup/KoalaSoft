#include "KoaGraphUtility.h"
#include "KoaUtility.h"

using namespace KoaUtility;

template<typename ...Ts>
void fillGraph(const char* outFileName, const char* paraFileName, Ts... args)
{
  // timer start
  TStopwatch timer;

  // book graphs
  auto gmap_timewalk = bookGraphByRecTdcChannelId("timewalk","Time Walk", kBlack, 20);
  auto gmap_timeshift = bookGraphByRecTdcChannelId("timeshift","Time Shift", kBlue, 20);

  //
  std::vector<std::string> txtFiles = {paraFileName, args...};

  int idx = 0;
  for(auto txtFile : txtFiles) {

    // read amplitude parameters
    auto amp_params = readParameterList<double>(txtFile);

    auto it = findValueContainer(amp_params, "Mean");
    auto amp_means = it->second;
    it = findValueContainer(amp_params, "Err(mean)");
    auto amp_mean_errs = it->second;
    it = findValueContainer(amp_params, "Sigma");
    // auto amp_sigmas = it->second;
    // it = findValueContainer(amp_params, "Err(sigma)");
    // auto amp_sigma_errs = it->second;

    // read timestamp parameters
    TString timeFile = txtFile.data();
    timeFile.ReplaceAll("amp.txt", "time.txt");

    auto time_params = readParameterList<double>(timeFile.Data());

    it = findValueContainer(time_params, "Mean");
    auto time_means = it->second;
    it = findValueContainer(time_params, "Err(mean)");
    auto time_mean_errs = it->second;
    it = findValueContainer(time_params, "Sigma");
    // auto time_sigmas = it->second;
    // it = findValueContainer(time_params, "Err(sigma)");
    // auto time_sigma_errs = it->second;

    // fill parameters into graph
    auto time_ref = time_means.begin()->second;
    for( auto& graph : gmap_timewalk ) {
      auto id = graph.first;
      auto& gr_timewalk = graph.second;
      auto& gr_timeshift = gmap_timeshift[id];

      // fill time walk
      gr_timewalk.SetPoint(idx, amp_means[id], time_means[id]);
      gr_timewalk.SetPointError(idx, amp_mean_errs[id], time_mean_errs[id]);

      // fill time shift
      gr_timeshift.SetPoint(idx, amp_means[id], time_means[id]-time_ref);
      gr_timeshift.SetPointError(idx, amp_mean_errs[id], 0);
    }

    //
    idx++;
  }

  // output
  TFile* fout = new TFile(outFileName, "update");

  // time walk
  TDirectory* gdir = nullptr;
  gdir = getDirectory(fout, "time_walk");
  writeGraphs(gdir,gmap_timewalk,"Overwrite");

  // time shift
  gdir = getDirectory(fout, "time_shift");
  writeGraphs(gdir,gmap_timeshift,"Overwrite");

  // clean up
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();

  return;
}
