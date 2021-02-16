#include "KoaTextUtility.h"
#include "KoaUtility.h"

using namespace KoaUtility;
using namespace std;

void aggregate_channel_paramter_unique(const char* outfilename)
{
  vector<string> list_file = {"P_2.2_calib_cluster_purification_multiple_Purification_smear_TofE_cut_Energy_All_Individual_-5.0_5.0_SubstractBkgHistPdf_FitOnlyCB2.txt", // Si1: 17-29
                      "P_2.2_calib_cluster_purification_multiple_Purification_smear_TofE_cut_Energy_Individual_-5.0_5.0_FitCoulombCB2.txt", // Si1: 30-31, Si2: 2-6
                      "P_2.2_calib_cluster_purification_multiple_Purification_smear_TofE_cut_Energy_All_Individual_-5.0_5.0_FitHistPdfCB2.txt", // Si1: 32-47, Si2: 7-26
                      "P_2.2_calib_cluster_purification_multiple_Purification_smear_result_rec_cluster_energy_FirstHit_FitExpoCB2.txt", // Si2: 27-63
                      "P_2.2_calib_cluster_purification_multiple_Purification_smear_TofE_cut_bkg_no_mip_Ge1Ge2_FitExpoCB2_Channels.txt"}; // Ge1 & Ge2

  //
  ParameterList<double> ChannelParams;
  auto& output_e = addValueContainer(ChannelParams, "Energy");
  auto& output_e_err = addValueContainer(ChannelParams, "Energy(Error)");
  auto& output_evt = addValueContainer(ChannelParams, "Evt");
  auto& output_evt_err = addValueContainer(ChannelParams, "Evt(Error)");
  auto& output_sigma = addValueContainer(ChannelParams, "Sigma");

  auto& output_cb_alpha1 = addValueContainer(ChannelParams, "CB_alpha1");
  auto& output_cb_alpha2 = addValueContainer(ChannelParams, "CB_alpha2");
  auto& output_cb_n1 = addValueContainer(ChannelParams, "CB_n1");
  auto& output_cb_n2 = addValueContainer(ChannelParams, "CB_n2");
  auto& output_chi2ndf = addValueContainer(ChannelParams, "chi2/ndf");

  //
  for(auto file: list_file){
    auto fit_params = readParameterList<double>(file.data());

    auto it = findValueContainer(fit_params, "EvtNr");
    if( it == fit_params.end() ) {
      cout << "EvtNr not available in config file: " << file << endl;
      return;
    }
    auto evtNr = it->second;

    it = findValueContainer(fit_params, "CB_mean");
    if( it == fit_params.end() ) {
      cout << "CB_mean not available in config file: " << file << endl;
      return;
    }
    auto mean = it->second;

    it = findValueContainer(fit_params, "CB_sigma");
    if( it == fit_params.end() ) {
      cout << "CB_sigma not available in config file: " << file << endl;
      return;
    }
    auto sigma = it->second;

    it = findValueContainer(fit_params, "CB_alpha1");
    if( it == fit_params.end() ) {
      cout << "CB_alpha1 not available in config file: " << file << endl;
      return;
    }
    auto cb_alpha1 = it->second;

    it = findValueContainer(fit_params, "CB_alpha2");
    if( it == fit_params.end() ) {
      cout << "CB_alpha2 not available in config file: " << file << endl;
      return;
    }
    auto cb_alpha2 = it->second;

    it = findValueContainer(fit_params, "CB_n1");
    if( it == fit_params.end() ) {
      cout << "CB_n1 not available in config file: " << file << endl;
      return;
    }
    auto cb_n1 = it->second;

    it = findValueContainer(fit_params, "CB_n2");
    if( it == fit_params.end() ) {
      cout << "CB_n2 not available in config file: " << file << endl;
      return;
    }
    auto cb_n2 = it->second;

    it = findValueContainer(fit_params, "chi2/ndf");
    if( it == fit_params.end() ) {
      cout << "chi2/ndf not available in config file: " << file << endl;
      return;
    }
    auto chi2_over_ndf = it->second;

    it = findValueContainer(fit_params, "Err(EvtNr)");
    if( it == fit_params.end() ) {
      cout << "Err(EvtNr) not available in config file: " << file << endl;
      return;
    }
    auto evtNr_err = it->second;

    it = findValueContainer(fit_params, "Err(CB_mean)");
    if( it == fit_params.end() ) {
      cout << "Err(CB_mean) not available in config file: " << file << endl;
      return;
    }
    auto mean_err = it->second;

    // fill in the buffer
    for(auto item : evtNr){
      auto id = item.first;

      auto search = output_e.find(id);
      if(search != output_e.end()){
        cout << "Error! Duplicate channel ID found!" <<endl;
        return;
      }

      output_evt.emplace(id, evtNr[id]);
      output_evt_err.emplace(id, evtNr_err[id]);
      output_e.emplace(id, mean[id]);
      output_e_err.emplace(id, mean_err[id]);
      output_sigma.emplace(id, sigma[id]);
      output_chi2ndf.emplace(id, chi2_over_ndf[id]);

      output_cb_alpha1.emplace(id, cb_alpha1[id]);
      output_cb_alpha2.emplace(id, cb_alpha2[id]);
      output_cb_n1.emplace(id, cb_n1[id]);
      output_cb_n2.emplace(id, cb_n2[id]);
    }
  }

  //
  TString outfile_txt(outfilename);
  printValueList<double>(ChannelParams, outfile_txt.Data());
}
