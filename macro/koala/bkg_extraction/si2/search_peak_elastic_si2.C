#include "KoaHistUtility.h"
#include "KoaTextUtility.h"

using namespace KoaUtility;

void search_peak_elastic_si2(
                             const char* filename,
                             const char* sensor_start = "Si2",
                             int ch_start = 26,
                             const char* sensor_stop = "Si2",
                             int ch_stop = 64,
                             const char* dirname = "rec_cluster_energy_FirstHit",
                             const char* suffix = "cluster_energy_firstHit"
                             )
{
  // get ref ch id
  auto encoder = KoaMapEncoder::Instance();
  auto id_start = encoder->EncodeChannelID(Form("Sensor%s", sensor_start), ch_start-1);
  auto id_stop = encoder->EncodeChannelID(Form("Sensor%s", sensor_stop), ch_stop-1);

  //
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto h1s = getHistosByChannelId<TH1D>(hdir, suffix);
  delete fin;

  // book output parameters
  ParameterList<double> OutputParameters;
  auto& output_peak = addValueContainer(OutputParameters, "Peak");
  auto& output_mean = addValueContainer(OutputParameters, "Mean");
  auto& output_sigma = addValueContainer(OutputParameters, "Sigma");

  //
  for(auto item: h1s){
    auto id = item.first;
    auto hist = item.second;

    if(id < id_start) continue;
    if(id > id_stop) continue;

    hist->Rebin(4);
    hist->SetAxisRange(2, 20);

    TSpectrum s(1);
    int np = s.Search(hist, 0.2, "", 0.8);
    double *xpeaks = s.GetPositionX();
    if(np == 1){
      output_peak.emplace(id, xpeaks[0]);

      auto result = hist->Fit("gaus", "qs", "", xpeaks[0]-0.3, xpeaks[0]+0.3);
      double mean = result->Parameter(1);
      double sigma = result->Parameter(2);
      output_mean.emplace(id, mean);
      output_sigma.emplace(id, sigma);

      hist->SetAxisRange(mean-9*sigma, mean+7*sigma);
    }
  }

  //
  TString pdffilename(filename);
  pdffilename.ReplaceAll(".root", "_FitElasticPeak_Si2.pdf");
  printHistos<TH1D*>(h1s, pdffilename.Data());

  TString outfile_txt(filename);
  outfile_txt.ReplaceAll(".root","_FitElasticPeak_Si2.txt");
  printValueList<double>(OutputParameters, outfile_txt.Data());

}
