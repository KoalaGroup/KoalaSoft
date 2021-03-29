#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

void count_peaks(const char* infile,
                 const char* peakfile,
                 const char* outfile,
                 const char* hdirname = "elastic_events",
                 const char* hsuffixname = "cluster_energy_elastic"
                 )
{
  TStopwatch timer;

  // 
  Double_t fProtonMass = 0.938272081;

  // input histograms
  TString infile_name = gSystem->ExpandPathName(infile);
  auto filein = TFile::Open(infile_name, "update");

  auto hdir = getDirectory(filein, hdirname);
  auto hist_energy = getHistosByChannelId<TH1D>(hdir, hsuffixname);

  // input peaks
  auto peak_params = readParameterList<double>(peakfile);

  auto it = findValueContainer(peak_params, "Mean");
  auto peak_means = it->second;
  it = findValueContainer(peak_params, "Err(mean)");
  auto peak_mean_errs = it->second;
  it = findValueContainer(peak_params, "Sigma");
  auto peak_sigmas = it->second;
  it = findValueContainer(peak_params, "Alpha");
  auto peak_alphas = it->second;

  //
  HistoPtr1D hist_output;

  ParameterList<double> CountsParameter;
  auto& output_alphas = addValueContainer(CountsParameter, "Alpha");
  auto& output_t = addValueContainer(CountsParameter, "|t|");
  auto& output_counts = addValueContainer(CountsParameter, "Count");
  auto& output_t_errs = addValueContainer(CountsParameter, "Err(|t|)");

  for(auto peak: peak_means) {
    auto id = peak.first;
    auto mean = peak.second;
    auto mean_err = peak_mean_errs[id];
    auto sigma = peak_sigmas[id];
    auto alpha = peak_alphas[id];

    //
    auto hist = hist_energy[id];
    auto low = mean-3*sigma;
    auto high = mean+5*sigma;

    auto fgaus = new TF1(Form("fgaus_%s", hist->GetName()), "gaus", low, high);
    fgaus->SetParameter(1, mean);
    fgaus->SetParameter(2, sigma);

    hist->GetXaxis()->SetRangeUser(low-5*sigma, high+5*sigma);
    hist->Fit(fgaus, "RQ");

    hist_output.emplace(id, hist);

    //
    auto bin_low = hist->FindBin(low);
    auto bin_high = hist->FindBin(high);
    auto counts = hist->Integral(bin_low, bin_high);

    //
    output_alphas.emplace(id, alpha);
    output_t.emplace(id, 2*fProtonMass*mean/1000.);
    output_t_errs.emplace(id, 2*fProtonMass*mean_err/1000.);
    output_counts.emplace(id, counts);
  }

  //output
  printValueList<double>(CountsParameter, outfile);

  TString outfile_pdf(outfile);
  outfile_pdf.ReplaceAll(".txt", ".pdf");
  printH1Ds(hist_output, outfile_pdf);

  auto hdir_output = getDirectory(filein,"peak_ranges");
  writeHistos<TH1D*>(hdir_output,hist_output,"WriteDelete");

  //
  delete filein;

  //
  timer.Stop();
  timer.Print();
}
