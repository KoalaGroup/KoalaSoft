#include "KoaHistUtility.h"

using namespace KoaUtility;

void fitHistogram(const char* inFileName, const char* outDir)
{
  inFileName = gSystem->ExpandPathName(inFileName);
  auto fin = TFile::Open(inFileName, "update");

  // amplitude
  auto hDirIn = getDirectory(fin, "rec_adc");
  auto h1map_amp = getHistosByRecTdcChannelId<TH1D>(hDirIn, "adc");

  // fitting
  fitHistos(h1map_amp);

  // fetch parameters
  ParameterList<double> ampParameters;
  auto& mean_amp = addValueContainer(ampParameters, "Mean");
  auto& sigma_amp = addValueContainer(ampParameters, "Sigma");
  auto& err_mean_amp = addValueContainer(ampParameters, "Err(mean)");
  auto& err_sigma_amp = addValueContainer(ampParameters, "Err(sigma)");

  for(auto h1 : h1map_amp) {
    auto id = h1.first;
    TF1* f1 = h1.second->GetFunction("gaus");
    mean_amp.emplace(id, f1->GetParameter(1));
    err_mean_amp.emplace(id, f1->GetParError(1));
    sigma_amp.emplace(id, f1->GetParameter(2));
    err_sigma_amp.emplace(id, f1->GetParError(2));
  }

  // timestamp
  hDirIn = getDirectory(fin, "rec_time");
  auto h1map_time = getHistosByRecTdcChannelId<TH1D>(hDirIn, "time");

  // fitting
  fitHistos(h1map_time);

  // fetch prameters
  ParameterList<double> timeParameters;
  auto& mean_time = addValueContainer(timeParameters, "Mean");
  auto& sigma_time = addValueContainer(timeParameters, "Sigma");
  auto& err_mean_time = addValueContainer(timeParameters, "Err(mean)");
  auto& err_sigma_time = addValueContainer(timeParameters, "Err(sigma)");

  for(auto h1 : h1map_time) {
    auto id = h1.first;
    TF1* f1 = h1.second->GetFunction("gaus");
    mean_time.emplace(id, f1->GetParameter(1));
    err_mean_time.emplace(id, f1->GetParError(1));
    sigma_time.emplace(id, f1->GetParameter(2));
    err_sigma_time.emplace(id, f1->GetParError(2));
  }

  // output
  TString outFileName = gSystem->BaseName(inFileName);
  TString ampTxtFile = gSystem->ConcatFileName(outDir, outFileName);
  ampTxtFile.ReplaceAll(".root","_amp.txt");
  TString timeTxtFile = gSystem->ConcatFileName(outDir, outFileName);
  timeTxtFile.ReplaceAll(".root","_time.txt");
  TString ampPdfFile = gSystem->ConcatFileName(outDir, outFileName);
  ampPdfFile.ReplaceAll(".root","_amp.pdf");
  TString timePdfFile = gSystem->ConcatFileName(outDir, outFileName);
  timePdfFile.ReplaceAll(".root","_time.pdf");

  // save parameters to text file
  printValueList<double>(ampParameters, ampTxtFile.Data());
  printValueList<double>(timeParameters, timeTxtFile.Data());

  // print histograms to pdf file
  printH1Ds(h1map_amp, ampPdfFile.Data());
  printH1Ds(h1map_time, timePdfFile.Data());

  // save histograms to root file
  auto hDirOut = getDirectory(fin, "rec_adc_fit");
  writeHistos<TH1D*>(hDirOut, h1map_amp);

  hDirOut = getDirectory(fin, "rec_time_fit");
  writeHistos<TH1D*>(hDirOut, h1map_time);

  // cleanup
  delete fin;
}
