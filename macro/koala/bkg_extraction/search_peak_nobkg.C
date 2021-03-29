#include "KoaHistUtility.h"
#include "KoaTextUtility.h"

using namespace KoaUtility;

void search_peak_nobkg(
                       const char* filename,
                       const char* dirname = "Energy_All_no_seperateBkg_withEnergyRange_low0.12_high0.18",
                       const char* suffix = "nobkg",
                       int start_ch = 21
)
{
  // get ref ch id
  auto encoder = KoaMapEncoder::Instance();
  auto start_id = encoder->EncodeChannelID(0, start_ch-1);

  //
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto h1s = getHistosByRecTdcChannelId<TH1D>(hdir, suffix);
  delete fin;

  // book output parameters
  ParameterList<double> OutputParameters;
  auto& output_mean = addValueContainer(OutputParameters, "Mean");
  auto& output_sigma = addValueContainer(OutputParameters, "Sigma");

  //
  for(auto item: h1s){
    auto id = item.first;
    auto hist = item.second;

    if(id < start_id) continue;

    hist->Rebin(5);
    hist->SetAxisRange(0.2, 8);

    TSpectrum s(1);
    int np = s.Search(hist, 0.2, "", 0.6);
    double *xpeaks = s.GetPositionX();
    if(np == 1){
      output_mean.emplace(id, xpeaks[0]);

      auto result = hist->Fit("gaus", "qs", "", xpeaks[0]-0.2, xpeaks[0]+0.2);
      double sigma = result->Parameter(2);
      output_sigma.emplace(id, sigma);
    }
  }

  //
  TString pdffilename(filename);
  pdffilename.ReplaceAll(".root", "_NoBkgPeaks.pdf");
  printHistos<TH1D*>(h1s, pdffilename.Data());

  TString outfile_txt(filename);
  outfile_txt.ReplaceAll(".root","_NoBkgPeaks.txt");
  printValueList<double>(OutputParameters, outfile_txt.Data());

}
