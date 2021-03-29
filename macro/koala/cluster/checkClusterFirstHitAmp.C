#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"

using namespace KoaUtility;

void checkClusterFirstHitAmp(const char* infile,
                             const char* treename,
                             const char* brName_cluster,
                             const char* outfile,
                             double mom = 2.6,
                             const char* geoFile="../calib_para/geo_standard.root",
                             const char* pedestal_file = "adc_pedestal_20190902_003449.txt",
                             const char* adcpara_file = "adc_calib_energy.txt"
                             )
{
  // read in pedestals and ADC calib params and compute 2*sigma threshold
  auto compute_noise_thresholds = [&] (int thresh) -> std::map<int, double> // in MeV
                                  {
                                    TString vmc_dir = getenv("VMCWORKDIR");
                                    TString param_dir = vmc_dir+"/parameters/";

                                    auto noise_params = readParameterList<double>((param_dir+pedestal_file).Data());
                                    auto it = findValueContainer(noise_params, "Mean");
                                    auto noise_means = it->second;
                                    it = findValueContainer(noise_params, "Sigma");
                                    auto noise_sigmas = it->second;

                                    auto adc_params = readParameterList<double>((param_dir+adcpara_file).Data());
                                    it = findValueContainer(adc_params, "AdcToE_p0");
                                    auto adc_p0s = it->second;
                                    it = findValueContainer(adc_params, "AdcToE_p1");
                                    auto adc_p1s = it->second;

                                    //
                                    std::map<int, double> noise_thresholds;
                                    for(auto item: noise_means) {
                                      auto id = item.first;
                                      auto ped_mean = item.second;
                                      auto ped_sigma = noise_sigmas[id];
                                      auto p0 = adc_p0s[id];
                                      auto p1 = adc_p1s[id];

                                      noise_thresholds.emplace(id, (p0 + p1*(ped_mean + thresh*ped_sigma))/1000.);
                                    }

                                    return noise_thresholds;
                                  };

  // get the expected energy in each channel
  double zoffset[4] = {0}; // in cm
  double yoffset[4] = {0}; // in cm
  auto expected_energies = getChannelEnergies(2.6, geoFile, yoffset, zoffset); // in MeV

  // input
  TFile* f = new TFile(infile);
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* RecClusters = new TClonesArray("KoaRecCluster");
  tree->SetBranchAddress(brName_cluster, &RecClusters);

  // histogram definition
  TString hDirName = "cluster_FirstHitAmplitude";
  TString hName = "cluster_FirstHitAmplitude";
  TString hTitle = "Cluster Energy;Energy(MeV)";

  auto h1map = bookH1dByChannelId(hName.Data(), hTitle.Data(),
                                  7000, 0, 70,
                                  true, kBlack);

  // loop
  Long_t entries = tree->GetEntries();
  for(auto entry=0;entry<entries;entry++){
    tree->GetEntry(entry);

    //
    Int_t clusters = RecClusters->GetEntriesFast();

    for (int i=0;i<clusters;i++){
      KoaRecCluster* cluster = (KoaRecCluster*)RecClusters->At(i);

      auto cluster_e = cluster->Energy()/1000.;
      auto cluster_id = cluster->GetFirstChId();

      if( cluster_e < (expected_energies[cluster_id]*0.8))
        continue;
      
      auto ids = cluster->GetIds();
      auto energies = cluster->GetEnergies();
      auto size = cluster->NumberOfDigis();
      for(auto index = 0; index < size; index++) {
        if(ids[index] == cluster_id) {
          h1map[cluster_id].Fill(energies[index]/1000.);
          break;
        }
      }
    }
  }
  std::cout << "Events processed : "<< entries << std::endl;

  // output
  TFile *fout = new TFile(outfile, "update");

  TDirectory* hdir = nullptr;
  hdir = getDirectory(fout, hDirName.Data());
  writeHistos<TH1D>(hdir, h1map);

  TString pdfFileName = outfile;
  pdfFileName.ReplaceAll(".root", "_checkFirstHitAmp.pdf");
  printH1Ds<TH1D>(h1map, pdfFileName.Data(), true, true);

  //
  delete f;
  delete fout;
}
