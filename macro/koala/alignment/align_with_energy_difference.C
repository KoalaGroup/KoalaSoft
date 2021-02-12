#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;
using namespace std;

void align_with_energy_difference(const char* param_file,
                                  double mom,
                                  const char* geoFile,
                                  double start_si1 = 0.18, double start_si2 = 0.13, double start_ge1 = 0.13, double start_ge2 = 0.13
)
{
  // read in fitting parameter of CB_mean and associated error from aggregated results
  ValueContainer<double> e;
  ValueContainer<double> e_err;

  auto fit_params = readParameterList<double>(param_file);
  auto it = findValueContainer(fit_params, "Energy");
  if( it == fit_params.end() ) {
    cout << "Energy not available in config file: " << param_file << endl;
    return;
  }
  e = it->second;

  it = findValueContainer(fit_params, "Energy(Error)");
  if( it == fit_params.end() ) {
    cout << "Energy(Error) not available in config file: " << param_file << endl;
    return;
  }
  e_err = it->second;

  //
  auto calculator = new KoaElasticCalculator(mom);

  // par[0] : zoffset si1
  // par[1] : zoffset si2
  // par[2] : zoffset ge1
  // par[3] : zoffset ge2
  auto chi2Function = [&](const double* par) {
                        double zoffset[4] = {par[0], par[1], par[2], par[3]}; // in cm
                        double yoffset[4] = {0, 0, 0, 0}; // in cm
                        auto Alphas = getChannelAlphas(geoFile, yoffset, zoffset);

                        double chi2 = 0;
                        for(auto item: e){
                          auto id = item.first;
                          auto cal_e = calculator->GetEnergyByAlpha(Alphas[id]);
                          auto diff = (e[id]-calc_e)/e_err[d];
                          chi2 += diff*diff;
                        }

                        return chi2;
                      };

  //
  ROOT::Math::Functor fcn(chi2Function, 4);
  ROOT::Fit::Fitter fitter;

  double pStart[4] = {start_si1, start_si2, start_ge1, start_ge2};
  fitter.SetFCN(fcn, pStart);

  fitter.Config().ParSettings(0).SetName("zoffset_si1");
  fitter.Config().ParSettings(0).SetLimits(0 ,start_si1+0.2);
  fitter.Config().ParSettings(1).SetName("zoffset_si2");
  fitter.Config().ParSettings(1).SetLimits(start_si2-0.1,start_si2+0.1);
  fitter.Config().ParSettings(2).SetName("zoffset_ge1");
  fitter.Config().ParSettings(2).SetLimits(start_ge1-0.1, start_ge1+0.1);
  fitter.Config().ParSettings(3).SetName("zoffset_ge2");
  fitter.Config().ParSettings(3).SetLimits(start_ge2-0.1, start_ge2+0.1);

  //
  bool ok = fitter.FitFCN();
  if(ok != true) {
    Error("alignment", "Fitting failed");
  }

  auto result = fitter.Result();
  result.Print(std::cout);
}
