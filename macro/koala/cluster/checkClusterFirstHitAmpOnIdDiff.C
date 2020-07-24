#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"

using namespace KoaUtility;

void checkClusterFirstHitAmpOnIdDiff(const char* infile,
                                     const char* treename,
                                     const char* brName_cluster,
                                     const char* outfile,
                                     int max_IdDiff = 1,
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
  TString hDirName = Form("cluster_FirstHitAmplitude_%dMaxIdDiff", max_IdDiff);
  TString hName = Form("cluster_FirstHitAmplitude_%dMaxIdDiff", max_IdDiff);
  TString hTitle = Form("Energy of FirstHit of Cluster with IdDiff > %d;Energy(MeV)", max_IdDiff);

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

      auto first_id = cluster->GetFirstChId();
      auto max_id = cluster->GetMaximaChId();
      auto energies = cluster->GetEnergies();

      if( (max_id-first_id) > max_IdDiff ) {
        h1map[first_id].Fill(energies[0]/1000.);
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
  pdfFileName.ReplaceAll(".root", Form("_checkFirstHitAmpOnIdDiff_%d.pdf", max_IdDiff));
  printHistos<TH1D>(h1map, pdfFileName.Data(), true, true);

  //
  delete f;
  delete fout;
}
