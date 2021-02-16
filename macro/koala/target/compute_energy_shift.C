#include "KoaHistUtility.h"

using namespace KoaUtility;

void compute_energy_shift(const char* filename,
                          const char* dirname,
                          double mom,
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
  gr_ediff_vs_eref->SetTitle("Energy difference between corrected and reference energy VS Reference Energy;E_{ref} (keV);E_{corrected} - E_{ref} (keV)");
  gr_ediff_vs_eref->SetMarkerStyle(20);
  gr_ediff_vs_eref->SetMarkerSize(0.6);

  auto gr_ediff_vs_ecorrected = new TGraph();
  gr_ediff_vs_ecorrected->SetName("gr_ediff_vs_ecorrected");
  gr_ediff_vs_ecorrected->SetTitle("Energy difference between corrected and reference energy VS Corrected Energy;E_{corrected} (keV);E_{corrected} - E_{ref} (keV)");
  gr_ediff_vs_ecorrected->SetMarkerStyle(20);
  gr_ediff_vs_ecorrected->SetMarkerSize(0.6);

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

    gr_zpeak_vs_eref->SetPoint(index, e_measured, z0[id]);
    gr_ecorrected_vs_eref->SetPoint(index, e_measured, e_corrected);
    gr_ediff_vs_eref->SetPoint(index, e_measured, e_corrected-e_measured);
    gr_ediff_vs_ecorrected->SetPoint(index, e_corrected, e_corrected-e_measured);

    index++;
  }

  //
  auto fout = TFile::Open(Form("%s/aggregate_profiles.root", dirname), "update");
  auto dir = getDirectory(fout, Form("e_correction_%.2f", zoffset));
  dir->WriteTObject(gr_zpeak_vs_eref, "", "WriteDelete");
  dir->WriteTObject(gr_ecorrected_vs_eref, "", "WriteDelete");
  dir->WriteTObject(gr_ediff_vs_eref, "", "WriteDelete");
  dir->WriteTObject(gr_ediff_vs_ecorrected, "", "WriteDelete");

  delete fout;
  delete calculator;
}
