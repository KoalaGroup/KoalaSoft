#include "KoaHistUtility.h"
#include "KoaGraphUtility.h"
#include "KoaGeometryUtility.h"

using namespace KoaUtility;

void check_pedestals(const char* pedestal_file,
                     const char* outfile,
                     const char* adcpara_file = "adc_calib_energy.txt"
                     )
{
  // read in ADC calib parameters
  TString vmc_dir = getenv("VMCWORKDIR");
  TString param_dir = vmc_dir+"/parameters/";
  TString adc_calib_file = param_dir + adcpara_file;

  auto adc_params = readParameterList<double>(adc_calib_file.Data());
  auto it = KoaUtility::findValueContainer(adc_params, "AdcToE_p0");
  auto adc_p0s = it->second;
  it = KoaUtility::findValueContainer(adc_params, "AdcToE_p1");
  auto adc_p1s = it->second;

  // read in pedestals
  bool IsCompare = false;
  auto ped_params = KoaUtility::readParameterList<double>(pedestal_file);
  it = KoaUtility::findValueContainer(ped_params, "Mean");
  auto ped_means = it->second;
  it = KoaUtility::findValueContainer(ped_params, "Sigma");
  auto ped_sigmas = it->second;

  printValueContainer(ped_params, "Mean(Fit/Seed)");
  ValueContainer<double> mean_ratios, sigma_ratios;
  it = KoaUtility::findValueContainer(ped_params, "Mean(Fit/Seed)");
  if(it != ped_params.end()){
    IsCompare = true;
    std::cout<< "Comparing to seed pedestals.\n";
    mean_ratios = it->second;

    it = KoaUtility::findValueContainer(ped_params, "Sigma(Fit/Seed)");
    sigma_ratios = it->second;
  }

  // define histograms
  auto h1sigma_adc = bookH1dByDetectorId("ped_sigma_adc",
                                         "Pedestal Sigma Distribution (ADC counts);ADC counts",
                                         30, -2, 13
                                         );

  auto h1sigma_e = bookH1dByDetectorId("ped_sigma_energy",
                                       "Pedestal Sigma Distribution (Energy-equivalent);E (keV)",
                                       30, -2, 13
                                       );

  TH1D h1mean_ratio("h1_ped_mean_ratio",
                    "Pedestal Mean Ratio (Comparison to Seed pedestals);Fitted/Seed",
                    20, 0.9, 1.1
                    );

  TH1D h1sigma_ratio("h1_ped_sigma_ratio",
                    "Pedestal Sigma Ratio (Comparison to Seed pedestals);Fitted/Seed",
                     40, 0.8, 1.2
                     );

  // filling
  auto encoder = KoaMapEncoder::Instance();
  for(auto item: ped_means)
  {
    auto id = item.first;
    int det_id;
    encoder->DecodeChannelID(id, det_id);

    auto adc_sigma = ped_sigmas[id];
    auto e_sigma = adc_p1s[id]*adc_sigma; // in keV

    h1sigma_adc[det_id].Fill(adc_sigma);
    h1sigma_e[det_id].Fill(e_sigma);

    if(IsCompare){
      h1mean_ratio.Fill(mean_ratios[id]);
      h1sigma_ratio.Fill(sigma_ratios[id]);
    }
  }

  // output
  auto fout = new TFile(outfile, "update");
  auto hdir = getDirectory(fout, "rec_pedestal_distribution");

  writeHistos(hdir, h1sigma_adc);
  writeHistos(hdir, h1sigma_e);

  if(IsCompare) {
    hdir->WriteTObject(&h1mean_ratio, "", "WriteDelete");
    hdir->WriteTObject(&h1sigma_ratio, "", "WriteDelete");
  }

  //
  delete fout;
}
