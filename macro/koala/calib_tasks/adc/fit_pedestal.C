#include "KoaHistUtility.h"

using namespace KoaUtility;

void fit_pedestal(const char* infile,
                  const char* dirname = "rec_adc",
                  const char* suffix = "adc",
                  const char* outfile = "pedestal_fitresult.txt",
                  const char* seedfile = "adc_pedestal_20190902_003449.txt"
                  )
{
  //
  TString infile_name = gSystem->ExpandPathName(infile);
  auto filein = TFile::Open(infile_name, "Update");

  auto hdir = getDirectory(filein, dirname);
  auto h1s_ptr = getHistosByChannelId<TH1D>(hdir, suffix, true);

  // read pedestal seed parameters
  TString vmc_dir = getenv("VMCWORKDIR");
  TString param_dir = vmc_dir+"/parameters/";
  TString seed_file = param_dir + seedfile;
  auto seed_params = readParameterList<double>(seed_file.Data());

  auto it = findValueContainer(seed_params, "Mean");
  auto seed_means = it->second;
  it = findValueContainer(seed_params, "Sigma");
  auto seed_sigmas = it->second;

  // output parameters
  ParameterList<double> OutputParameters;
  auto& output_means = addValueContainer(OutputParameters, "Mean");
  auto& output_sigmas = addValueContainer(OutputParameters, "Sigma");
  auto& output_compare_means = addValueContainer(OutputParameters, "Mean(Fit/Seed)");
  auto& output_compare_sigmas = addValueContainer(OutputParameters, "Sigma(Fit/Seed)");

  // fit
  auto encoder = KoaMapEncoder::Instance();
  auto fitPeak = [&] ()
                 {
                   // loop through all hists
                   for ( auto& hist : h1s_ptr ) {
                     auto id = hist.first;
                     auto h1 = hist.second;
                     h1->GetXaxis()->SetRangeUser(0, 200);

                     //
                     Int_t det_id, ch_id;
                     ch_id = encoder->DecodeChannelID(id, det_id);

                     //
                     auto seed_mean = seed_means[id];
                     auto seed_sigma = seed_sigmas[id];
                     auto low = seed_mean - 10*seed_sigma;
                     auto high = seed_mean + 10*seed_sigma;

                     auto result = h1->Fit("gaus", "qs", "", low, high);
                     double fit_mean = result->Parameter(1);
                     double fit_sigma = result->Parameter(2);

                     output_means.emplace(id, fit_mean);
                     output_sigmas.emplace(id, fit_sigma);
                     output_compare_means.emplace(id, fit_mean/seed_mean);
                     output_compare_sigmas.emplace(id, fit_sigma/seed_sigma);
                   }
                 };
  fitPeak();

  //
  TString outdir_name = dirname;
  outdir_name.Append("_pedestal_fitted");
  auto hDirOut = getDirectory(filein, outdir_name.Data());
  writeHistos<TH1D*>(hDirOut, h1s_ptr);

  //
  TString outfile_pdf(outfile);
  outfile_pdf.ReplaceAll(".txt",".pdf");
  printH1Ds(h1s_ptr, outfile_pdf.Data());

  //
  printValueList<double>(OutputParameters, outfile);

  //
  delete filein;
}
