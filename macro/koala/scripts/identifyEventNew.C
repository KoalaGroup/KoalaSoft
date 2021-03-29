#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"

using namespace KoaUtility;

/* Descriptions:
 * The macro is used to identify the event type based on
 * 1. the characteristics of the cluster ( for strips not covered by Fwd detector ) and
 * 2. the coincidence information of the Fwd detector ( for strips covered by Fwd )
 * 
 * The clusters can be categorized based on the following information:
 * a) number of digits in the cluster : N_digits
 * b) the energy weighted z-position  : to classify whether the cluster is covered by Fwd or not, and to calculate the expected energy loss of elastic proton E_calc
 * c) the difference between the calibrated energy of the cluster and the expected energy loss : E_delta, E_delta = (E_calib - E_calc)/E_calc
 *
 * Three categories of cluster are defined:
 * 1. elastic cluster : |E_delta| <= 30% && N_digits <= 3
 * 2. In-elastic cluster : 30% < |E_delta| <= 80%
 * 3. noise : |E_delta| > 80%
 *
 * Each event is then tagged as one the following 3 types:
 * 1. elastic : elastic scattering event
 *    i) 0 < N_clusters < 4 and there is one elastic cluster in the region not covered by Fwd
 *   ii) 0 < N_clusters < 4 and there are only noise clusters in the region covered by Fwd and at least one cluster in the region covered by Fwd and there is coincidence in Fwd
 * 2. inelastic : inelastic scattering event, which comes from interaction of beam and target and hit the recoil detector. It can be further subdivided into two groups:
 *    i) there are more than 4 clusters in this event, no matter what type of the cluster is
 *   ii) N_clusters < 4 and there is at least one In-elastic cluster 
 * 3. noise : event in which there is no valid hit in recoil detector
 *    i) N_clusters = 0
 *   ii) 0 < N_clusters < 4 and they are all noise clusters
 *
 * The output of this macro is 3 TEventList corresponding to 3 categories of events, saved under 'elists'
 * 1. elastic_elist
 * 2. inelastic_elist
 * 3. noise_elist
 */
void identifyEventNew(const char* filename = "~/workspace/data/calibrated/yong/P_3.0_2019_Aug_30_01_48_39_calib_yong_cluster.root", // root file containing tree 'KoalaClusterEvent'
                      Double_t mom = 3.0, // in GeV, beam momentum
                      const char* elistFileName = nullptr, const char* edirName = "fwd", const char* fwdhit_elist = "elist_fwdhit",
                      Int_t fwdCoveredStripId_Si1 = 33, Double_t fwdCoveredStripId_Si2 = 5,
                      Double_t sepElastic = 0.3, Double_t sepNoise = 0.9, // distinguish cluster type in Fwd-Unconvered region
                      Int_t maxClusers = 3, // the maximum clusters allowed in an elastic event
                      Int_t maxNoiseCluster = 2, // maximum noise clusters allowed in elastic evenGt
                      const char* geoFile = "../calib_para/geo_standard.root", // geometry used to calculate expected energy
                      Bool_t fillHist = true
                      )
{
  TStopwatch timer;

  TH1::AddDirectory(false);
  using IndexContainer = std::vector<Int_t>;

  // thresholds
  double pedestal_threshold[4]={100, 100, 500, 1000}; // equivalent pedestal energy threshold

  // cluster size limit
  int size_limit[4]={4,4,5,6};

  // book histogram
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  Int_t RecIdRange[2];
  encoder->GetRecDetIDRange(RecIdRange[0], RecIdRange[1]);
  
  TH2D h2map("h2map", "Recoil_Energy VS Hit_Position;Z (mm);Energy (MeV)", 25, 0, 25, 3500, 0, 70);
  auto h1RecHits = bookH1dByRecDetectorId("RecHits","Elastic Cluster Statistics;Channel",kBlack);
  auto h2RecHits = bookH2dByRecDetectorId("RecHits","Elastic Cluster Energy;Channel;Energy(MeV)", 3500, 0, 70);

  auto h1map = bookH1dByChannelId("cluster_energy_elastic",
                                  "Cluster Energy (selected single cluster);Energy(MeV)",
                                  7000,0,70,
                                  true, kBlue);

  // geometry
  auto calculator = new KoaElasticCalculator(mom);

  std::map<Int_t, double> CalculatedEnergies;

  double zoffset[4] = {0.}; // in cm
  double yoffset[4] = {0, 0, 0, 0}; // in cm
  auto Positions = getChannelGlobalPosition(geoFile, zoffset);
  auto Alphas = getChannelAlphas(geoFile, yoffset, zoffset);

  for(auto item: Positions ){
    auto id = item.first;
    auto pos = item.second;
    if(pos>0){
      auto energy = calculator->GetEnergyByAlpha(Alphas[id]);

      CalculatedEnergies.emplace(id, energy);
    }
  }

  // covered range id
  auto fwdCoveredId_Si1 = encoder->EncodeChannelID(0, fwdCoveredStripId_Si1-1);
  auto fwdCoveredId_Si2 = encoder->EncodeChannelID(1, fwdCoveredStripId_Si2-1);

  // // Get TGeoManager
  // auto fgeo = TFile::Open(geoFile);
  // TGeoManager* geoMan=(TGeoManager*)fgeo->Get("FAIRGeom");
  // auto geoHandler = new KoaGeoHandler(kFALSE);

  // // get the fwd covered range in recoil detector
  // Double_t fwd_low, fwd_high, temp;
  // geoHandler->GetDetBoundaryByName("SensorSc1", fwd_low, temp);
  // geoHandler->GetDetBoundaryByName("SensorSc2", temp, fwd_high);

  // KoaElasticCalculator* calculator = new KoaElasticCalculator(mom);
  // Double_t rec_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSi1"));
  // calculator->SetRecDistance(rec_distance);

  // Double_t rec_low, rec_high; // in mm
  // Double_t fwd_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSc1"));
  // calculator->SetFwdDistance(fwd_distance);
  // rec_low = calculator->GetRecZByFwdX(fwd_low) + fwdCoveredBoundaryLow;

  // fwd_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSc2"));
  // calculator->SetFwdDistance(fwd_distance);
  // rec_high = calculator->GetRecZByFwdX(fwd_high) - fwdCoveredBoundaryHigh;

  // input
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get("koalasim");
  TClonesArray* RecClusters = new TClonesArray("KoaRecCluster");
  tree->SetBranchAddress("KoaRecCluster",&RecClusters);

  // input filter based on TEventList
  TFile* felist = nullptr;
  TDirectory* eDir = nullptr;
  TEventList* cutlist = nullptr;
  if ( elistFileName ) {
    felist = new TFile(elistFileName, "update");
    eDir = getDirectory(felist, edirName);
    cutlist = getObject<TEventList>(eDir, fwdhit_elist);
  }

  // output elists
  TEventList *elastic_elist = new TEventList("elist_elastic","Elastic scattering event");
  TEventList *elastic_FwdUncovered_elist = new TEventList("elist_elastic_FwdUncovered","Elastic scattering event (FwdUncovered region determined)");
  TEventList *elastic_FwdCovered_elist = new TEventList("elist_elastic_FwdCovered","Elastic scattering event (FwdCovered region determined)");

  TEventList *inelastic_elist = new TEventList("elist_inelastic","In-elastic scattering event");
  TEventList *inelastic_ManyClusters_elist = new TEventList("elist_inelastic_ManyClusters",Form("In-elastic event (with more than %d clusters)", maxClusers));
  TEventList *inelastic_MultiElastic_elist = new TEventList("elist_inelastic_MultiElastic","In-elastic event (more than one elastic clusters)");
  TEventList *inelastic_OnlyInelastic_elist = new TEventList("elist_inelastic_OnlyInelastic","In-elastic event (Only inelastic clusters exist)");
  TEventList *inelastic_ElasticAndInelastic_elist = new TEventList("elist_inelastic_ElasticAndInelastic","In-elastic event (Both elastic and inelastic cluster exist)");
  TEventList *inelastic_ElasticAndManyNoise_elist = new TEventList("elist_inelastic_ElasticAndManyNoise",Form("In-elastic event (Both elastic and more than %d noise cluster exist)", maxNoiseCluster));
  TEventList *inelastic_FwdUncovered_elist = new TEventList("elist_inelastic_FwdUncovered","In-elastic event (FwdUncovered, Total)");
  TEventList *inelastic_FwdCovered_elist = new TEventList("elist_inelastic_FwdCovered",Form("In-elastic event (FwdCovered region, N_cluster > %d)", maxNoiseCluster+1));

  TEventList *noise_elist = new TEventList("elist_noise","Noise event");
  TEventList *noise_FwdCovered_elist = new TEventList("elist_noise_FwdCovered","Noise event (FwdCovered region determined)");
  TEventList *noise_FwdUncovered_elist = new TEventList("elist_noise_FwdUncovered","Noise event (FwdUncovered region determined)");

  // define elastic cluster index tree for elastic events
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","_result.root");
  TFile* fout = new TFile(outfilename.Data(), "update");
  Int_t elastic_index;
  TTree* tindex = new TTree("ElasticIndex","Index of elastic cluster for elastic events");
  tindex->Branch("ElasticIndex", &elastic_index);

  // statistics
  Long64_t num_elastic = 0;
  Long64_t num_elastic_FwdCovered = 0 ;
  Long64_t num_elastic_FwdUncovered = 0 ;

  Long64_t num_inelastic = 0;
  Long64_t num_inelastic_ManyClusters = 0;
  Long64_t num_inelastic_ElasticAndInelastic = 0;
  Long64_t num_inelastic_ElasticAndManyNoise = 0;
  Long64_t num_inelastic_OnlyInelastic = 0;
  Long64_t num_inelastic_MultiElastic = 0;
  Long64_t num_inelastic_FwdUncovered = 0;
  Long64_t num_inelastic_FwdCovered = 0;

  Long64_t num_noise = 0;
  Long64_t num_noise_FwdCovered = 0;
  Long64_t num_noise_FwdUncovered = 0;

  // event loop
  Long64_t entries = tree->GetEntries();
  for(Long64_t entry=0; entry < entries; entry++){
    //
    tree->GetEntry(entry);

    // event identification
    Int_t clusters = RecClusters->GetEntriesFast();

    /*** use N_cluster to identify inelastic ***/

    // 1. identification based on N_cluster
    if ( clusters > maxClusers ) {// N_cluster > maxClusers, it's inelastic event
      inelastic_elist->Enter(entry);
      num_inelastic++;

      inelastic_FwdUncovered_elist->Enter(entry);
      num_inelastic_FwdUncovered++;

      inelastic_ManyClusters_elist->Enter(entry);
      num_inelastic_ManyClusters++;
      continue;
    }
    else if ( clusters == 0 ) {// N_cluster = 0, it's noise event
      noise_elist->Enter(entry);
      num_noise++;

      noise_FwdUncovered_elist->Enter(entry);
      num_noise_FwdUncovered++;
      continue;
    }

    /*** for 1 <= N_cluster <= maxClusers ***/

    // 2. divide the clusters into two groups: fwd_covered and fwd_not_covered
    IndexContainer fwdCovered, fwdUnCovered;
    fwdCovered.clear(); fwdUnCovered.clear();
    for(int cluster = 0; cluster < clusters; cluster++){
      KoaRecCluster* rec_cluster = (KoaRecCluster*)RecClusters->At(cluster);
      auto det_id = rec_cluster->GetDetId();
      rec_cluster->SetThreshold(pedestal_threshold[det_id]);
      auto cluster_id = rec_cluster->GetFirstChIdAboveThresh();

      // ignore noise clusters
      auto nr_digis = rec_cluster->NumberOfDigisAboveThresh();
      if (nr_digis > size_limit[det_id]) {
        continue;
      }

      if (nr_digis == 0) {
        continue;
      }

      //
      switch (det_id) {
        case 0: {
          if(cluster_id <= fwdCoveredId_Si1) {
            fwdCovered.emplace_back(cluster);
          }
          else {
            fwdUnCovered.emplace_back(cluster);
          }
          break;
        }
        case 1: {
          if(cluster_id <= fwdCoveredId_Si2) {
            fwdCovered.emplace_back(cluster);
          }
          else {
            fwdUnCovered.emplace_back(cluster);
          }
          break;
        }
        default:
          fwdUnCovered.emplace_back(cluster);
          break;
      }
    }

    /*** use fwdUnCovered region information for identification ***/

    // 3. identify the categories of each cluster in fwdUnCovered region

    // Currently, only the total energy of cluster is used for categorization.
    // In the future, the hit information (size, position and energy) in the cluster may also be utilized for finer classification.
    IndexContainer elasticClusters, inelasticClusters, noiseClusters;
    elasticClusters.clear(); inelasticClusters.clear(); noiseClusters.clear();

    for( auto& cluster : fwdUnCovered ) {
      KoaRecCluster* rec_cluster = (KoaRecCluster*)RecClusters->At(cluster);
      auto cluster_id = rec_cluster->GetFirstChIdAboveThresh();

      Double_t e_calc = CalculatedEnergies[cluster_id]; // in MeV
      Double_t e_calib = rec_cluster->Energy()/1000.; // in MeV
      Double_t e_delta = (e_calib-e_calc)/e_calc;
      Double_t e_delta_abs = TMath::Abs(e_delta);

      //      -sepNoise       -sepElastic     0    sepElastic 
      //          ^                 ^         ^         ^
      // --noise--|----inelastic----|-elastic-|-elastic-|-----inelastic-----------
      if ( e_delta_abs < sepElastic ) {
        elasticClusters.emplace_back(cluster);
      }
      else if ( e_delta >= sepElastic
                || (e_delta <= -sepElastic && e_delta >= -sepNoise)) {
        inelasticClusters.emplace_back(cluster);
      }
      else {
        noiseClusters.emplace_back(cluster);
      }
    }

    // 4. Event categorization based on FwdUncovered cluster topology
    Int_t n_elastic = elasticClusters.size();
    Int_t n_inelastic = inelasticClusters.size();
    Int_t n_noise = noiseClusters.size();

    if ( n_elastic > 0 ) {
      if ( n_inelastic > 0 ) { //  both elastic and inelastic cluster exist
        inelastic_elist->Enter(entry);
        num_inelastic++;

        inelastic_FwdUncovered_elist->Enter(entry);
        num_inelastic_FwdUncovered++;
        
        inelastic_ElasticAndInelastic_elist->Enter(entry);
        num_inelastic_ElasticAndInelastic++;
        continue;
      }
      else if ( n_elastic == 1 ) {
        if( n_noise <= maxNoiseCluster ){// one elastic cluster or + maxNoiseCluster noise clusters
          elastic_elist->Enter(entry);
          num_elastic++;

          elastic_FwdUncovered_elist->Enter(entry);
          num_elastic_FwdUncovered++;

          // fill the elastic index tree
          elastic_index = elasticClusters.back();
          tindex->Fill();

          // fill histogram
          if (fillHist) {
            KoaRecCluster* rec_cluster = (KoaRecCluster*)RecClusters->At(elasticClusters.back());

            auto cluster_id = rec_cluster->GetFirstChIdAboveThresh();
            Double_t e_calib = rec_cluster->Energy()/1000.; // in MeV

            Int_t detId;
            Int_t chId = encoder->DecodeChannelID(cluster_id, detId);

            h2map.Fill(Positions[cluster_id], e_calib);
            h2RecHits[detId].Fill(chId+1, e_calib);
            h1RecHits[detId].Fill(chId+1);
            h1map[cluster_id].Fill(e_calib);
          }
        }
        else {
          inelastic_elist->Enter(entry);
          num_inelastic++;

          inelastic_FwdUncovered_elist->Enter(entry);
          num_inelastic_FwdUncovered++;

          inelastic_ElasticAndManyNoise_elist->Enter(entry);
          num_inelastic_ElasticAndManyNoise++;
        }

        continue;
      }
      else { // more than 1 elastic cluster, [TODO] to be further invesigated!!
        // std::cout << "\nWarning: More than 1 elastic clusters found! (" << entry << ")" << std::endl;
        // for ( auto& cluster : elasticClusters ){
        //   KoaRecCluster* rec_cluster = (KoaRecCluster*)RecClusters->At(cluster);
        //   auto cluster_id = rec_cluster->GetFirstChIdAboveThresh();
        //   Double_t e_calc = CalculatedEnergies[cluster_id]; // in MeV
        //   Double_t e_calib = rec_cluster->Energy()/1000.; // in MeV
        //   Double_t e_delta = TMath::Abs((e_calib-e_calc)/e_calc);
          
        //   std::cout <<  "\thit_pos(" << Positions[cluster_id] << ") e_calc(" << e_calc << ") e_delta(" << e_delta << ")"
        //             << std::endl;
        // }

        inelastic_elist->Enter(entry);
        num_inelastic++;

        inelastic_FwdUncovered_elist->Enter(entry);
        num_inelastic_FwdUncovered++;

        inelastic_MultiElastic_elist->Enter(entry);
        num_inelastic_MultiElastic++;
        continue;
      }
    }
    else if ( n_inelastic > 0 ) { // only inelastic clusters or + noise cluster exist
      inelastic_elist->Enter(entry);
      num_inelastic++;

      inelastic_FwdUncovered_elist->Enter(entry);
      num_inelastic_FwdUncovered++;

      inelastic_OnlyInelastic_elist->Enter(entry);
      num_inelastic_OnlyInelastic++;
      continue;
    }
    else if (fwdCovered.empty()) { // only noise cluster exist in this event
      // WARNING: [TODO] what if this conflict with fwd information, how does this contribute to detector efficiency?
      noise_elist->Enter(entry);
      num_noise++;

      noise_FwdUncovered_elist->Enter(entry);
      num_noise_FwdUncovered++;
      continue;
    }

    // 5. using fwd information to identify this event
    // WARNING:
    //  i) At this point, all clusters found in fwd-uncovered region are noises and there is cluster above pedestal found in fwd-covered region
    // ii) If the event has already been categorized by FwdUncovered information, the FwdCovered information will be skipped completely. This may bring issues when FwdUncovered and FwdCovered information conflict with each other. For example, FwdUncovered determines the event is inelastic or noise, but FwdCovered determines it to be elastic; Or in another case, both FwdUncovered and FwdCovered determine it to be elastic, but the elastic cluster is lying in different region!! This needs to be further invesigated [TODO]

    // 5.1 fwdCovered elastic event
    if ( cutlist->Contains(entry)
         && (clusters-1) <= maxNoiseCluster ) {// [TODO] to be further categorized and find the correct elastic cluster
      elastic_elist->Enter(entry);
      num_elastic++;

      elastic_FwdCovered_elist->Enter(entry);
      num_elastic_FwdCovered++;

      // fill the elastic index tree, [TODO] how to find the correct elastic cluster
      elastic_index = fwdCovered.back();
      KoaRecCluster* elastic_cluster = (KoaRecCluster*)RecClusters->At(elastic_index);
      Double_t energy = elastic_cluster->Energy();
      Double_t tmp;
      for( auto& cluster : fwdCovered ) {
        KoaRecCluster* rec_cluster = (KoaRecCluster*)RecClusters->At(cluster);
        tmp = rec_cluster->Energy();
        if( tmp > energy ) {
          energy = tmp;
          elastic_index = cluster;
        }
      }

      tindex->Fill();

      // fill histogram
      if (fillHist) {
        KoaRecCluster* rec_cluster = (KoaRecCluster*)RecClusters->At(elastic_index);

        auto cluster_id = rec_cluster->GetFirstChIdAboveThresh();
        Double_t e_calib = rec_cluster->Energy()/1000.; // in MeV

        Int_t detId;
        Int_t chId = encoder->DecodeChannelID(cluster_id, detId);

        h2map.Fill(Positions[cluster_id], e_calib);
        h2RecHits[detId].Fill(chId+1, e_calib);
        h1RecHits[detId].Fill(chId+1);
        h1map[cluster_id].Fill(e_calib);
      }
    }
    // 5.2 fwdCovered inelastic event
    else if ( clusters > (maxNoiseCluster+1) ){ 
        inelastic_elist->Enter(entry);
        num_inelastic++;

        inelastic_FwdCovered_elist->Enter(entry);
        num_inelastic_FwdCovered++;
    }
    // 5.3 fwdCovered noise event
    else {
      noise_elist->Enter(entry);
      num_noise++;

      noise_FwdCovered_elist->Enter(entry);
      num_noise_FwdCovered++;
    }
  }

  // statistics
  std::cout << "\nStatistics (Total events = " << entries << ")\n";

  std::cout << "\tElastic (one elastic cluster or plus " << maxNoiseCluster << " noise clusters): " << num_elastic << std::endl;
  std::cout << "\t\t in Fwd-Uncovered region: " << num_elastic_FwdUncovered << std::endl;
  std::cout << "\t\t in Fwd-Covered region: " << num_elastic_FwdCovered << std::endl;

  std::cout << "\tInelastic Total: " << num_inelastic << std::endl;
  std::cout << "\t\t Inelastic (Fwd-Uncovered, N_cluster > " << maxClusers << "): " << num_inelastic_ManyClusters << std::endl;
  std::cout << "\t\t Inelastic (Fwd-Uncovered, Both elastic and inelastic cluster exist): " << num_inelastic_ElasticAndInelastic << std::endl;
  std::cout << "\t\t Inelastic (Fwd-Uncovered, one elastic and N_noise > " << maxNoiseCluster << " ): " << num_inelastic_ElasticAndManyNoise << std::endl;
  std::cout << "\t\t Inelastic (Fwd-Uncovered, Only inelastic cluster exist): " << num_inelastic_OnlyInelastic << std::endl;
  std::cout << "\t\t Inelastic (Fwd-Uncovered, N_elastic_cluster > 1): " << num_inelastic_MultiElastic << std::endl;
  std::cout << "\t\t Inelastic (Fwd-UnCovered, Total): "  << num_inelastic_FwdUncovered << std::endl;
  std::cout << "\t\t Inelastic (Fwd-Covered, N_cluster > " << maxNoiseCluster+1 << "): " << num_inelastic_FwdCovered << std::endl;

  std::cout << "\tNoise Total: " << num_noise << std::endl;
  std::cout << "\t\t in Fwd-Uncovered region: " << num_noise_FwdUncovered << std::endl;
  std::cout << "\t\t in Fwd-Covered region: " << num_noise_FwdCovered << std::endl;
  std::cout << std::endl;

  // output
  eDir = getDirectory(felist, "events");
  eDir->cd();
  elastic_elist->Write(0, TObject::kOverwrite);
  elastic_FwdUncovered_elist->Write(0, TObject::kOverwrite);
  elastic_FwdCovered_elist->Write(0, TObject::kOverwrite);

  inelastic_elist->Write(0, TObject::kOverwrite);
  inelastic_ManyClusters_elist->Write(0, TObject::kOverwrite);
  inelastic_OnlyInelastic_elist->Write(0, TObject::kOverwrite);
  inelastic_ElasticAndInelastic_elist->Write(0, TObject::kOverwrite);
  inelastic_ElasticAndManyNoise_elist->Write(0, TObject::kOverwrite);
  inelastic_MultiElastic_elist->Write(0, TObject::kOverwrite);
  inelastic_FwdUncovered_elist->Write(0, TObject::kOverwrite);
  inelastic_FwdCovered_elist->Write(0, TObject::kOverwrite);

  noise_elist->Write(0, TObject::kOverwrite);
  noise_FwdUncovered_elist->Write(0, TObject::kOverwrite);
  noise_FwdCovered_elist->Write(0, TObject::kOverwrite);

  // index tree
  fout->cd();
  tindex->Write(0, TObject::kOverwrite);

  // output histogram
  if(fillHist){
    TDirectory* hdir = nullptr;
    hdir = getDirectory(fout, "elastic_events");

    writeHistos<TH1D>(hdir, h1RecHits);
    writeHistos<TH2D>(hdir, h2RecHits);
    writeHistos<TH1D>(hdir, h1map);

    hdir->WriteTObject(&h2map, "", "Overwrite");
  }

  //
  delete calculator;
  delete f;
  delete felist;
  delete fout;

  //
  timer.Stop();
  timer.Print();
}
