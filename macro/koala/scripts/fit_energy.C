#include "KoaGeometryUtility.h"
#include "KoaHistUtility.h"

using namespace KoaUtility;

void fit_energy(const char* infile,
                const char* dirname = "elastic_events",
                const char* suffix = "cluster_energy_elastic",
                const char* sensorName = "Si1",
                int ch_id = 1,
                double mom = 2.6,
                const char* geoFile = "geo_standard.root",
                double zoffset_si1 = 0, double zoffset_si2 = 0, double zoffset_ge1 = 0, double zoffset_ge2 = 0
                )
{
  double yoffset[4] = {0.};
  double zoffset[4] = {zoffset_si1, zoffset_si2, zoffset_ge1, zoffset_ge2}; // in cm
  auto energies = getStripEnergies(2.6, geoFile,yoffset,zoffset);

  auto geoHandler = getGeometryHandler(geoFile);
  auto ChToStripMap = geoHandler->GetChIdToStripIds();
  delete geoHandler;

  auto encoder = KoaMapEncoder::Instance();
  auto id = encoder->EncodeChannelID(Form("Sensor%s",sensorName), ch_id-1);
  auto strip_ids = ChToStripMap[id];

  //
  auto fin = TFile::Open(infile);
  auto hdir = getDirectory(fin,dirname);
  auto hist = getHisto<TH1D>(hdir,suffix,sensorName,ch_id);
  hist->SetDirectory(0);
  delete fin;

  //
  TF1* ffit = nullptr;
  auto nr_strips = strip_ids.size();
  switch (nr_strips) {
    case 1: {
      auto low = energies[strip_ids[0]] - 3*0.2;
      auto high = energies[strip_ids[0]] + 3*0.2;
      hist->GetXaxis()->SetRangeUser(low, high);
      double integral = hist->Integral();
      auto rms = hist->GetRMS();

      low = energies[strip_ids[0]] - 5*rms;
      high = energies[strip_ids[0]] + 5*rms;
      hist->GetXaxis()->SetRangeUser(low, high);

      ffit = new TF1("ffit", "gaus(0)", low+3*rms, high);
      ffit->SetParameter(0, integral);
      ffit->SetParameter(1, energies[strip_ids[0]]);
      ffit->SetParameter(2, rms);
      break;
    }
    case 2: {
      auto low = energies[strip_ids[0]] - 5*0.2;
      auto high = energies[strip_ids[1]] + 5*0.2;
      hist->GetXaxis()->SetRangeUser(low, high);
      double integral = hist->Integral();
      auto rms = hist->GetRMS()/TMath::Sqrt(2);

      low = energies[strip_ids[0]] - 5*rms;
      high = energies[strip_ids[1]] + 5*rms;
      hist->GetXaxis()->SetRangeUser(low, high);

      auto result1 = hist->Fit("gaus","s+", "", energies[strip_ids[0]]-3*rms,energies[strip_ids[0]]+rms);
      auto result2 = hist->Fit("gaus","s+", "", energies[strip_ids[1]]-rms,energies[strip_ids[1]]+3*rms);

      ffit = new TF1("ffit", "gaus(0)+gaus(3)", low, high);
      ffit->SetParameter(0, result1->Parameter(0));
      ffit->SetParameter(1, result1->Parameter(1));
      ffit->SetParameter(2, result1->Parameter(2));

      ffit->SetParameter(3, result2->Parameter(0));
      ffit->SetParameter(4, result2->Parameter(1));
      ffit->SetParameter(5, result2->Parameter(2));

      break;
    }
    case 3: {
      auto low = energies[strip_ids[0]] - 5*0.2;
      auto high = energies[strip_ids[2]] + 5*0.2;
      hist->GetXaxis()->SetRangeUser(low, high);
      double integral = hist->Integral();
      auto rms = hist->GetRMS()/TMath::Sqrt(3);

      low = energies[strip_ids[0]] - 5*rms;
      high = energies[strip_ids[2]] + 5*rms;
      hist->GetXaxis()->SetRangeUser(low, high);

      auto result1 = hist->Fit("gaus","s+", "", energies[strip_ids[0]]-3*rms,energies[strip_ids[0]]+rms);
      auto result2 = hist->Fit("gaus","s+", "", energies[strip_ids[2]]-rms,energies[strip_ids[2]]+3*rms);

      ffit = new TF1("ffit", "gaus(0)+gaus(3)+gaus(6)", low, high);
      // ffit = new TF1("ffit", "gaus(0)+gaus(3)", low, high);
      // ffit = new TF1("ffit", "gaus(0)+gaus(3)+pol1(6)", low, high);

      ffit->SetParameter(0, result1->Parameter(0));
      ffit->SetParameter(1, result1->Parameter(1));
      ffit->SetParameter(2, result1->Parameter(2));

      // triple gaussian form
      auto p0 = (result2->Parameter(0)+result1->Parameter(0))/2;
      auto p1 = energies[strip_ids[1]];
      // auto p2 = (result2->Parameter(2)+result1->Parameter(2))/2;
      auto p2 = rms;
      ffit->SetParameter(3, p0);
      ffit->SetParameter(4, p1);
      ffit->SetParameter(5, p2);

      ffit->SetParameter(6, result2->Parameter(0));
      ffit->SetParameter(7, result2->Parameter(1));
      ffit->SetParameter(8, result2->Parameter(2));

      // double gaussian form
      // ffit->SetParameter(3, result2->Parameter(0));
      // ffit->SetParameter(4, result2->Parameter(1));
      // ffit->SetParameter(5, result2->Parameter(2));

      // 2-gaussian + linear
      // auto p0 = (result2->Parameter(1)*result1->Parameter(0)-result2->Parameter(0)*result1->Parameter(1))/(result2->Parameter(1)-result1->Parameter(1));
      // auto p1 = (result2->Parameter(0)-result1->Parameter(0))/(result2->Parameter(1)-result1->Parameter(1));
      // ffit->SetParameter(6, p0);
      // ffit->SetParameter(7, p1);
      break;
    }
    default:
      break;
  }

  auto c = new TCanvas();
  hist->Fit(ffit,"r");
  hist->Draw();

  //
  std::cout<< "Nr Strips: " << nr_strips << std::endl;
  int index=0;
  for(auto id: strip_ids){
    auto fitted_value = ffit->GetParameter(1+3*index);
    auto calc_value = energies[id];
    std::cout << "Calculated: " << calc_value << "\t"
              << "Fitted: " <<  fitted_value << "\t"
              << (fitted_value-calc_value)/calc_value
              << std::endl;
    index++;
  }
}
