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
  double zoffset[4] = {0, 0, 0, 0}; // in cm
  auto Positions = getChannelGlobalPosition(geoFile, zoffset);

  // par[0] : zoffset si1
  // par[1] : zoffset si2
  // par[2] : zoffset ge1
  // par[3] : zoffset ge2
  // par[4] : yoffset si1
  // par[5] : yoffset si2
  // par[6] : yoffset ge1
  // par[7] : yoffset ge2
  auto encoder = KoaMapEncoder::Instance();
  int lower_id = encoder->EncodeChannelID(0, 17);
  double yoffset_sign[4]= {-10, 10, -10, 10};
  auto chi2Function = [&](const double* par) {
                        double chi2 = 0;
                        int det_id;
                        for(auto item: e){
                          auto id = item.first;
                          if(id < lower_id) continue;
                          encoder->DecodeChannelID(id, det_id);
                          // auto cal_e = calculator->GetEnergyByRecZ(10*(Positions[id]+par[det_id]));
                          // auto cal_e = calculator->GetEnergyByRecZ(10*(Positions[id]+par[det_id]), par[4]*yoffset_sign[det_id]);
                          auto cal_e = calculator->GetEnergyByRecZ(10*(Positions[id]+par[det_id]), 10*par[4+det_id]);
                          auto diff = (e[id]-cal_e)/e_err[id];
                          chi2 += diff*diff;
                        }

                        return chi2;
                      };

  //
  ROOT::Math::Functor fcn(chi2Function, 8);
  ROOT::Fit::Fitter fitter;

  double pStart[8] = {start_si1, start_si2, start_ge1, start_ge2
  // };
                      // ,0};
                      ,0, 0, 0, 0};
  fitter.SetFCN(fcn, pStart);

  fitter.Config().ParSettings(0).SetName("zoffset_si1");
  fitter.Config().ParSettings(0).SetLimits(0,start_si1+0.2);
  fitter.Config().ParSettings(1).SetName("zoffset_si2");
  fitter.Config().ParSettings(1).SetLimits(0,start_si2+0.2);
  fitter.Config().ParSettings(2).SetName("zoffset_ge1");
  fitter.Config().ParSettings(2).SetLimits(0, start_ge1+0.2);
  fitter.Config().ParSettings(3).SetName("zoffset_ge2");
  fitter.Config().ParSettings(3).SetLimits(0, start_ge2+0.2);
  fitter.Config().ParSettings(4).SetName("yoffset_si1");
  fitter.Config().ParSettings(4).SetLimits(-0.1, 0.1);
  fitter.Config().ParSettings(5).SetName("yoffset_si2");
  fitter.Config().ParSettings(5).SetLimits(-0.1, 0.1);
  fitter.Config().ParSettings(6).SetName("yoffset_ge1");
  fitter.Config().ParSettings(6).SetLimits(-0.1, 0.1);
  fitter.Config().ParSettings(7).SetName("yoffset_ge2");
  fitter.Config().ParSettings(7).SetLimits(-0.1, 0.1);
  fitter.Config().ParSettings(0).SetStepSize(0.001);
  fitter.Config().ParSettings(1).SetStepSize(0.001);
  fitter.Config().ParSettings(2).SetStepSize(0.001);
  fitter.Config().ParSettings(3).SetStepSize(0.001);
  fitter.Config().ParSettings(4).SetStepSize(0.0001);
  fitter.Config().ParSettings(5).SetStepSize(0.0001);
  fitter.Config().ParSettings(6).SetStepSize(0.0001);
  fitter.Config().ParSettings(7).SetStepSize(0.0001);
  fitter.Config().ParSettings(4).Fix();
  fitter.Config().ParSettings(5).Fix();
  fitter.Config().ParSettings(6).Fix();
  fitter.Config().ParSettings(7).Fix();

  //
  bool ok = fitter.FitFCN();
  if(ok != true) {
    Error("alignment", "Fitting failed");
  }

  auto result = fitter.Result();
  result.Print(std::cout);
}
