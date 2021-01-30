#include "KoaHistUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

void draw_iteration_result(const char* dirname,
                           int it_nr = 21
                           )
{
  ValueContainer<double> cb_mean;
  ValueContainer<double> cb_sigma;
  ValueContainer<double> cb_alpha1, cb_n1;
  ValueContainer<double> cb_alpha2, cb_n2;
  ValueContainer<double> evt_nr;
  ValueContainer<double> chi2_over_ndf;
  
  auto read_parameters = [&]( const char* filename)
                         {
                           auto fit_params = readParameterList<double>(filename);

                           auto it = findValueContainer(fit_params, "CB_mean");
                           if( it == fit_params.end() ) {
                             cout << "CB_mean not available in config file: " << filename << endl;
                             return;
                           }
                           cb_mean = it->second;

                           it = findValueContainer(fit_params, "CB_sigma");
                           if( it == fit_params.end() ) {
                             cout << "CB_sigma not available in config file: " << filename << endl;
                             return;
                           }
                           cb_sigma = it->second;

                           it = findValueContainer(fit_params, "CB_alpha1");
                           if( it == fit_params.end() ) {
                             cout << "CB_alpha1 not available in config file: " << filename << endl;
                             return;
                           }
                           cb_alpha1 = it->second;

                           it = findValueContainer(fit_params, "CB_alpha2");
                           if( it == fit_params.end() ) {
                             cout << "CB_alpha2 not available in config file: " << filename << endl;
                             return;
                           }
                           cb_alpha2 = it->second;

                           it = findValueContainer(fit_params, "CB_n1");
                           if( it == fit_params.end() ) {
                             cout << "CB_n1 not available in config file: " << filename << endl;
                             return;
                           }
                           cb_n1 = it->second;

                           it = findValueContainer(fit_params, "CB_n2");
                           if( it == fit_params.end() ) {
                             cout << "CB_n2 not available in config file: " << filename << endl;
                             return;
                           }
                           cb_n2 = it->second;

                           it = findValueContainer(fit_params, "EvtNr");
                           if( it == fit_params.end() ) {
                             cout << "EvtNr not available in config file: " << filename << endl;
                             return;
                           }
                           evt_nr = it->second;

                           it = findValueContainer(fit_params, "chi2/ndf");
                           if( it == fit_params.end() ) {
                             cout << "chi2/ndf not available in config file: " << filename << endl;
                             return;
                           }
                           chi2_over_ndf = it->second;
                     };

  //
  auto gr_mean = bookGraphByChannelId("mean",
                                      "CB Mean VS Iterate;Iterate;E (MeV)",
                                      kBlack, 20, 0.5);
  auto gr_sigma = bookGraphByChannelId("sigma",
                                      "CB Sigma VS Iterate;Iterate;E (MeV)",
                                      kBlack, 20, 0.5);
  auto gr_alpha1 = bookGraphByChannelId("alpha1",
                                       "CB alpha1 VS Iterate;Iterate;#alpha_{1}",
                                       kBlack, 20, 0.5);
  auto gr_alpha2 = bookGraphByChannelId("alpha2",
                                       "CB alpha2 VS Iterate;Iterate;#alpha_{2}",
                                       kBlack, 20, 0.5);
  auto gr_n1 = bookGraphByChannelId("n1",
                                    "CB n1 VS Iterate;Iterate;n_{1}",
                                    kBlack, 20, 0.5);
  auto gr_n2 = bookGraphByChannelId("n2",
                                    "CB n1 VS Iterate;Iterate;n_{2}",
                                    kBlack, 20, 0.5);
  auto gr_evt_nr = bookGraphByChannelId("evt_nr",
                                       "Elastic EventNr VS Iterate;Iterate;Event Nr",
                                       kBlack, 20, 0.5);
  auto gr_chi2ndf = bookGraphByChannelId("chi2ndf",
                                         "Chi2/ndf VS Iterate;Iterate;#chi^{2}/ndf",
                                         kBlack, 20, 0.5);

  //
  for(int it = 0; it <= it_nr; it++) {
    TString paraFile = gSystem->ConcatFileName(dirname, Form("channels_%d.txt",it));
    read_parameters(paraFile.Data());

    //
    for(auto item: cb_mean){
      auto id = item.first;

      gr_mean[id].SetPoint(it, it, cb_mean[id]);
      gr_sigma[id].SetPoint(it, it, cb_sigma[id]);
      gr_alpha1[id].SetPoint(it, it, cb_alpha1[id]);
      gr_alpha2[id].SetPoint(it, it, cb_alpha2[id]);
      gr_n1[id].SetPoint(it, it, cb_n1[id]);
      gr_n2[id].SetPoint(it, it, cb_n2[id]);
      gr_evt_nr[id].SetPoint(it, it, evt_nr[id]);
      gr_chi2ndf[id].SetPoint(it, it, chi2_over_ndf[id]);
    }
  }

  //
  TString output_filename = gSystem->ConcatFileName(dirname, "channels_result.root");
  auto fout = TFile::Open(output_filename, "update");
  auto dir_out = getDirectory(fout, "cb_mean");
  writeGraphs(dir_out, gr_mean);
  dir_out = getDirectory(fout, "cb_sigma");
  writeGraphs(dir_out, gr_sigma);
  dir_out = getDirectory(fout, "cb_alpha1");
  writeGraphs(dir_out, gr_alpha1);
  dir_out = getDirectory(fout, "cb_alpha2");
  writeGraphs(dir_out, gr_alpha2);
  dir_out = getDirectory(fout, "cb_n1");
  writeGraphs(dir_out, gr_n1);
  dir_out = getDirectory(fout, "cb_n2");
  writeGraphs(dir_out, gr_n2);
  dir_out = getDirectory(fout, "evt_nr");
  writeGraphs(dir_out, gr_evt_nr);
  dir_out = getDirectory(fout, "chi2ndf");
  writeGraphs(dir_out, gr_chi2ndf);

  TString pdffilename = gSystem->ConcatFileName(dirname, "channels_cb_mean.pdf");
  printGraphs(gr_mean, pdffilename.Data());

  pdffilename.ReplaceAll("cb_mean", "evt_nr");
  printGraphs(gr_evt_nr, pdffilename.Data());

  pdffilename.ReplaceAll("evt_nr", "chi2ndf");
  printGraphs(gr_chi2ndf, pdffilename.Data());

  //
  delete fout;
}
