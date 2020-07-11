#include "KoaGraphUtility.h"

using namespace KoaUtility;

void convertPedestalToEnergy(const char* pedestal_file,
                             const char* adcpara_file,
                             const char* outfile
                             )
{

  auto pedAdc_params = KoaUtility::readParameterList<double>(pedestal_file);
  auto it = KoaUtility::findValueContainer(pedAdc_params, "Mean");
  auto pedAdc_means = it->second;
  it = KoaUtility::findValueContainer(pedAdc_params, "Sigma");
  auto pedAdc_sigmas = it->second;

  auto adc_params = readParameterList<double>(adcpara_file);
  it = KoaUtility::findValueContainer(adc_params, "AdcToE_p0");
  auto adc_p0s = it->second;
  it = KoaUtility::findValueContainer(adc_params, "AdcToE_p1");
  auto adc_p1s = it->second;

  //
  ParameterList<double> OutParameters;
  auto& output_mean = KoaUtility::addValueContainer(OutParameters, "Mean(keV)");
  auto& output_sigma = KoaUtility::addValueContainer(OutParameters, "Sigma");
  auto& output_3sigma = KoaUtility::addValueContainer(OutParameters, "3Sigma");
  auto& output_5sigma = KoaUtility::addValueContainer(OutParameters, "5Sigma");

  for(auto item: pedAdc_means)
  {
    auto id = item.first;
    auto adc_mean = item.second;
    auto adc_sigma = pedAdc_sigmas[id];
    auto p0 = adc_p0s[id];
    auto p1 = adc_p1s[id];

    auto e_mean = p0 + p1*adc_mean;
    auto e_noise = p1*adc_sigma;
    output_mean.emplace(id, e_mean);
    output_sigma.emplace(id, e_noise);
    output_3sigma.emplace(id, 3*e_noise);
    output_5sigma.emplace(id, 5*e_noise);
  }

  //
  KoaUtility::printValueList<double>(OutParameters, outfile);
}
