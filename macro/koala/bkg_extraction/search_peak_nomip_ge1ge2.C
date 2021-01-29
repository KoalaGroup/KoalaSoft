#include "KoaHistUtility.h"
#include "KoaTextUtility.h"

using namespace KoaUtility;

void search_peak_nomip_ge1ge2(
                              const char* filename,
                              const char* dirname = "no_mip_Ge1Ge2",
                              const char* suffix = "nomip"
                              )
{
  // get ref ch id
  auto encoder = KoaMapEncoder::Instance();
  auto ge1_id_start = encoder->EncodeChannelID(2,0);
  auto ge2_id_start = encoder->EncodeChannelID(3,0);

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

    if(id < ge1_id_start) continue;

    hist->Rebin(4);
    hist->SetAxisRange(6, 60);

    TSpectrum s(1);
    int np = s.Search(hist, 0.2, "", 0.8);
    double *xpeaks = s.GetPositionX();
    if(np == 1){
      output_peak.emplace(id, xpeaks[0]);

      auto result = hist->Fit("gaus", "qs", "", xpeaks[0]-1, xpeaks[0]+1);
      double mean = result->Parameter(1);
      double sigma = result->Parameter(2);
      output_mean.emplace(id, mean);
      output_sigma.emplace(id, sigma);

      hist->SetAxisRange(mean-9*sigma, mean+7*sigma);
    }
  }

  //
  TString pdffilename(filename);
  pdffilename.ReplaceAll(".root", "_FitElasticPeak_Ge1Ge2.pdf");
  printHistos<TH1D*>(h1s, pdffilename.Data());

  TString outfile_txt(filename);
  outfile_txt.ReplaceAll(".root","_FitElasticPeak_Ge1Ge2.txt");
  printValueList<double>(OutputParameters, outfile_txt.Data());

}
