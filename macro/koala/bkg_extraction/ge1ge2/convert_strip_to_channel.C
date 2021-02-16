#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

void convert_strip_to_channel(const char* strip_file,
                              const char* geoFile
                              )
{
  auto strip_params = readParameterList<double>(strip_file);

  auto it = findValueContainer(strip_params, "Mean");
  if( it == strip_params.end() ) {
    cout << "Mean not available in config file: " << strip_file << endl;
    return;
  }
  auto means = it->second;

  it = findValueContainer(strip_params, "EvtNr");
  if( it == strip_params.end() ) {
    cout << "EvtNr not available in config file: " << strip_file << endl;
    return;
  }
  auto evts = it->second;

  it = findValueContainer(strip_params, "Err(Mean)");
  if( it == strip_params.end() ) {
    cout << "Err(Mean) not available in config file: " << strip_file << endl;
    return;
  }
  auto mean_errs = it->second;

  // Map containers for fitting results, with channel id as key
  ParameterList<double> output_params;
  auto& output_mean = addValueContainer(output_params, "CB_mean");
  auto& output_mean_err = addValueContainer(output_params, "Err(CB_mean)");

  //
  auto geoHandler = getGeometryHandler(geoFile);
  auto ChToStripMap = geoHandler->GetChIdToStripIds();

  for(auto item: ChToStripMap){
    auto id = item.first;
    auto strip_ids = item.second;
    auto nr_strips = strip_ids.size();

    auto search = means.find(strip_ids[0]);
    if(search == means.end()) continue;

    auto w = new double[nr_strips];
    double sum = 0;
    for(int i =0;i<nr_strips;i++){
      sum += evts[strip_ids[i]];
    }

    double mean_weighted = 0;
    double err_weighted = 0;
    for(int i =0;i<nr_strips;i++){
      w[i] = evts[strip_ids[i]]/sum;
      mean_weighted += w[i]*means[strip_ids[i]];
      err_weighted += w[i]*w[i]*mean_errs[strip_ids[i]]*mean_errs[strip_ids[i]];
    }
    err_weighted = TMath::Sqrt(err_weighted);

    output_mean.emplace(id, mean_weighted);
    output_mean_err.emplace(id, err_weighted);
  }

  //
  TString outfile_txt(strip_file);
  outfile_txt.ReplaceAll("_Strips.txt","_Channels_WeightedMean.txt");
  printValueList<double>(output_params, outfile_txt.Data());
}
