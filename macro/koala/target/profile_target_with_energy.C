#include "KoaHistUtility.h"
#include "KoaGraphUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaTextUtility.h"

using namespace KoaUtility;

void profile_target_with_energy(const char* filename, // *_TofE_cut.root
                                const char* dirname = "Energy_Individual_-5.0_5.0",
                                const char* suffix = "Energy",
                                double mom = 2.2, // in GeV
                                double e_ref = 0.12, // in MeV
                                int si1_low = 20, int si1_high = 47,
                                int si2_low = 2, int si2_high = 38,
                                double e_width = 0.01, // in MeV
                                const char* geoFile = "geo_standard.root"
                                )
{
  // get id ranges
  auto encoder = KoaMapEncoder::Instance();
  int si1_id = encoder->VolNameToDetectorID("SensorSi1");
  int si2_id = encoder->VolNameToDetectorID("SensorSi2");

  int si1_id_low = -1, si1_id_high = -1, si2_id_low = -1, si2_id_high = -1;
  if(si1_low != -1)  si1_id_low =  encoder->EncodeChannelID(si1_id, si1_low-1);
  if(si1_high != -1) si1_id_high = encoder->EncodeChannelID(si1_id, si1_high-1);
  if(si2_low != -1)  si2_id_low =  encoder->EncodeChannelID(si2_id, si2_low-1);
  if(si2_high != -1) si2_id_high = encoder->EncodeChannelID(si2_id, si2_high-1);

  int si1_id_dbout = encoder->EncodeChannelID(si1_id, 16); // Si1 1-16 is double-strip readout

  // Ideal strip center position in Z-axis
  double zoffset[4] = {0}; // in cm
  double yoffset[4] ={0};
  auto positions = getChannelGlobalPosition(geoFile,zoffset); // in cm, strip position along z-axis

  // input of the spectrum from the selected elastic events
  auto fin = TFile::Open(filename);
  TDirectory* hdir = getDirectory(fin, dirname);
  auto h1map = getHistosByRecTdcChannelId<TH1D>(hdir, suffix);
  
  // elastic calculator
  KoaElasticCalculator calculator(mom);
  auto z_ref = calculator.GetRecZByEnergy(e_ref); // in mm
  std::map<Int_t, double> CalculatedEnergies;
  for(auto item: positions ){
    auto id = item.first;
    auto pos = item.second;
    if(pos>0){
      auto energy = calculator.GetEnergyByRecZ(pos*10);
      CalculatedEnergies.emplace(id, energy);
    }
  }

  // output parameters
  ParameterList<double> OutputParameters;
  auto& output_z_strip = addValueContainer(OutputParameters, "Z_strip(mm)");

  auto& output_e_ref = addValueContainer(OutputParameters, "E_ref(MeV)");
  auto& output_z_ref = addValueContainer(OutputParameters, "Z_ref(mm)");
  auto& output_evt_ref = addValueContainer(OutputParameters, "Events_ref");
  auto& output_width_ref = addValueContainer(OutputParameters, "Width_ref(MeV)");

  auto& output_e_peak = addValueContainer(OutputParameters, "E_peak(MeV)");
  auto& output_z_peak = addValueContainer(OutputParameters, "Z_peak(mm)");
  auto& output_evt_peak = addValueContainer(OutputParameters, "Events_peak");
  auto& output_width_peak = addValueContainer(OutputParameters, "Width_peak(MeV)");

  //
  for(auto item: h1map){
    auto id = item.first;
    auto h1 = item.second;

    auto xaxis = h1->GetXaxis();
    auto bin_width = xaxis->GetBinWidth(1);
    int bin_size = e_width/bin_width;
    auto bin_start = xaxis->FindBin(e_ref);

    output_z_strip[id] = positions[id]*10;

    output_width_ref[id] = bin_width*bin_size;
    output_e_ref[id] = e_ref;
    output_z_ref[id] = z_ref;
    output_evt_ref[id] = 0;

    output_e_peak[id] = -1;
    output_z_peak[id] = -1;
    output_width_peak[id] = -1;
    output_evt_peak[id] = 0;


    // lower edge event counts
    for(int i = 0;i<bin_size;i++){
      output_evt_ref[id] += h1->GetBinContent(bin_start+i);
    }

    if(id < si1_id_dbout){
      output_evt_ref[id] = output_evt_ref[id]/2.;
    }

    // peak event counts
    if( (id >= si1_id_low && id <= si1_id_high)
        || ( id >= si2_id_low && id <= si2_id_high))
      {
        TSpectrum s(1);
        if(CalculatedEnergies[id]>1.5)
          xaxis->SetRangeUser(CalculatedEnergies[id]-0.5, CalculatedEnergies[id]+0.5);

        auto npeaks = s.Search(h1, 1, "nobackground", 0.2);

        if(npeaks>0) {
          Double_t *xpeaks = s.GetPositionX();
          auto peak_bin = xaxis->FindBin(xpeaks[0]);

          output_e_peak[id] = xpeaks[0];
          output_z_peak[id] = calculator.GetRecZByEnergy(xpeaks[0]);
          output_width_peak[id] = 3*bin_width;
          for(int bin=peak_bin-1;bin<peak_bin+2;bin++){
            output_evt_peak[id] += h1->GetBinContent(bin);
          }

          if(id < si1_id_dbout){
            output_evt_peak[id] = output_evt_peak[id]/2.;
          }
        }
      }
  }

  // output txt
  TString outfile_txt(filename);
  outfile_txt.ReplaceAll(".root","_target_profile.txt");
  printValueList<double>(OutputParameters, outfile_txt.Data());

  //
  TString outfile_pdf(filename);
  outfile_pdf.ReplaceAll(".root","_target_fit.pdf");
  printHistos<TH1D*>(h1map, outfile_pdf.Data());
  
  //
  delete fin;
}
