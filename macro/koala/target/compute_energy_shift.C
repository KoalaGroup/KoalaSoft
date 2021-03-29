#include "KoaHistUtility.h"

using namespace KoaUtility;

void compute_energy_shift(const char* filename,
                          const char* dirname,
                          double mom,
                          const char* sensor = "si1", // or 'si2'
                          double zoffset = -2.50 // target peak position in geometry model, in mm
                          )
{
  ////////////////////////////////////////
  // Read in the fitting params
  ////////////////////////////////////////

  ValueContainer<double> e_ref;
  ValueContainer<double> zoffset_si1;
  ValueContainer<double> z0;

  auto read_params = [&]() {
                       auto fit_params = readParameterList<double>(filename);

                       auto it = findValueContainer(fit_params, "E_ref(keV)");
                       e_ref = it->second;

                       it = findValueContainer(fit_params, "si1(mm)");
                       zoffset_si1 = it->second;
                       it = findValueContainer(fit_params, "Z0(mm)");
                       z0 = it->second;
                     };
  read_params();
  
  //
  ParameterList<double> OutputParameters;
  auto& output_e_ref = addValueContainer(OutputParameters, "E_ref(keV)");
  auto& output_e_corrected = addValueContainer(OutputParameters, "E_corrected");

  //
  auto gr_zpeak_vs_eref = new TGraph();
  gr_zpeak_vs_eref->SetName("gr_zpeak_vs_eref");
  gr_zpeak_vs_eref->SetTitle("Measured Profile Peak Position VS Reference Energy;E_{ref} (keV);Z_{peak} (mm)");
  gr_zpeak_vs_eref->SetMarkerStyle(20);
  gr_zpeak_vs_eref->SetMarkerSize(0.6);

  auto gr_ecorrected_vs_eref = new TGraph();
  gr_ecorrected_vs_eref->SetName("gr_ecorrected_vs_eref");
  gr_ecorrected_vs_eref->SetTitle("Corrected Energy Value VS Reference Energy;E_{ref} (keV);E_{corrected} (keV)");
  gr_ecorrected_vs_eref->SetMarkerStyle(20);
  gr_ecorrected_vs_eref->SetMarkerSize(0.6);

  auto gr_ediff_vs_eref = new TGraph();
  gr_ediff_vs_eref->SetName("gr_ediff_vs_eref");
  gr_ediff_vs_eref->SetTitle("Energy difference between corrected and reference energy VS Reference Energy;E_{ref} (keV);E_{ref} - E_{corrected} (keV)");
  gr_ediff_vs_eref->SetMarkerStyle(20);
  gr_ediff_vs_eref->SetMarkerSize(0.6);

  auto gr_ediff_vs_ecorrected = new TGraph();
  gr_ediff_vs_ecorrected->SetName("gr_ediff_vs_ecorrected");
  gr_ediff_vs_ecorrected->SetTitle("Energy difference between corrected and reference energy VS Corrected Energy;E_{corrected} (keV);E_{ref} - E_{corrected} (keV)");
  gr_ediff_vs_ecorrected->SetMarkerStyle(20);
  gr_ediff_vs_ecorrected->SetMarkerSize(0.6);

  auto gr_ediff_vs_alpharef = new TGraph();
  gr_ediff_vs_alpharef->SetName("gr_ediff_vs_alpharef");
  gr_ediff_vs_alpharef->SetTitle("Energy difference between corrected and reference energy VS Reference Alpha;#alpha_{ref} (#circ);E_{ref} - E_{corrected} (MeV)");
  gr_ediff_vs_alpharef->SetMarkerStyle(20);
  gr_ediff_vs_alpharef->SetMarkerSize(0.6);

  auto gr_ediff_vs_alphacorrected = new TGraph();
  gr_ediff_vs_alphacorrected->SetName("gr_ediff_vs_alphacorrected");
  gr_ediff_vs_alphacorrected->SetTitle("Energy difference between corrected and reference energy VS Corrected Alpha;#alpha_{corrected} (#circ);E_{ref} - E_{corrected} (MeV)");
  gr_ediff_vs_alphacorrected->SetMarkerStyle(20);
  gr_ediff_vs_alphacorrected->SetMarkerSize(0.6);

  auto gr_estoppwr_vs_ecorrected = new TGraph();
  gr_estoppwr_vs_ecorrected->SetName("gr_estoppwr_vs_ecorrected");
  gr_estoppwr_vs_ecorrected->SetTitle("Stop-power VS Corrected Energy;E_{corrected} (keV);Stop-Power (Arb.)");
  gr_estoppwr_vs_ecorrected->SetMarkerStyle(20);
  gr_estoppwr_vs_ecorrected->SetMarkerSize(0.6);

  //
  auto calculator = new KoaElasticCalculator(mom);

  int index = 0;
  for(auto item: e_ref){
    auto id = item.first;
    auto e_measured = item.second;
    auto  z_peak = zoffset + zoffset_si1[id];
    auto delta_z = z0[id] - z_peak;
    auto ref_z = calculator->GetRecZByEnergy(e_measured/1000.); // in mm
    auto real_z = ref_z + delta_z;
    auto e_corrected = calculator->GetEnergyByRecZ(real_z)*1000.; // in keV
    auto real_alpha = calculator->GetAlphaByEnergy(e_corrected/1000.);
    auto ref_alpha = calculator->GetAlphaByEnergy(e_measured/1000.);

    gr_zpeak_vs_eref->SetPoint(index, e_measured, z0[id]);
    gr_ecorrected_vs_eref->SetPoint(index, e_measured, e_corrected);
    gr_ediff_vs_eref->SetPoint(index, e_measured, e_measured-e_corrected);
    gr_ediff_vs_ecorrected->SetPoint(index, e_corrected, e_measured-e_corrected);
    gr_ediff_vs_alpharef->SetPoint(index, ref_alpha, (e_measured-e_corrected)/1000.);
    gr_ediff_vs_alphacorrected->SetPoint(index, real_alpha, (e_measured-e_corrected)/1000.);

    real_alpha = real_alpha/180.*3.1415926;
    gr_estoppwr_vs_ecorrected->SetPoint(index, e_corrected, (e_corrected-e_measured)*(1-real_alpha*real_alpha));

    output_e_ref.emplace(id, e_measured);
    output_e_corrected.emplace(id, e_corrected);

    index++;
  }

  //
  auto fout = TFile::Open(Form("%s/aggregate_profiles.root", dirname), "update");
  auto dir = getDirectory(fout, Form("e_correction_%.2f_%s", zoffset, sensor));
  dir->WriteTObject(gr_zpeak_vs_eref, "", "WriteDelete");
  dir->WriteTObject(gr_ecorrected_vs_eref, "", "WriteDelete");
  dir->WriteTObject(gr_ediff_vs_eref, "", "WriteDelete");
  dir->WriteTObject(gr_ediff_vs_ecorrected, "", "WriteDelete");
  dir->WriteTObject(gr_ediff_vs_alpharef, "", "WriteDelete");
  dir->WriteTObject(gr_ediff_vs_alphacorrected, "", "WriteDelete");
  dir->WriteTObject(gr_estoppwr_vs_ecorrected, "", "WriteDelete");

  //
  printValueList<double>(OutputParameters, Form("%s/e_corrected_%s_zoffset%.2f.txt", dirname, sensor, zoffset));

  delete fout;
  delete calculator;
}
