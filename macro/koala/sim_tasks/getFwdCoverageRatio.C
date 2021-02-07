#include "KoaColors.h"
#include "KoaHistUtility.h"

using namespace KoaUtility;

// this macro can only be used for two-body elastic scattering events
void getFwdCoverageRatio(const char* primaryFile, // root file from simulation macro, containing MCTrack tree
                         const char* geoFile = "../calib_para/geo_standard.root",
                         double fwd_offset = 0, // fwd y position offset in mm
                         int nbins = 300,
                         double xlow = 0,
                         double xhigh = 3,
                         long entries = -1) // the detector geometry to be checked
{
  //
  TStopwatch timer;
  using PointArray = std::vector<TVector3>;

  // get the boundaryPoints
  auto fgeo = TFile::Open(geoFile);
  TGeoManager* geoMan=(TGeoManager*)fgeo->Get("FAIRGeom");
  auto geoHandler = new KoaGeoHandler(kFALSE);
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();

  // rec
  Double_t rec_distance = geoHandler->GetDetPositionById(0);
  std::cout << "rec distance: " << rec_distance << std::endl;

  Int_t RecIdRange[2];
  encoder->GetRecDetIDRange(RecIdRange[0], RecIdRange[1]);

  std::map<int, TCutG> rec_cutg;
  for(auto sensor : ROOT::TSeqI(RecIdRange[0],RecIdRange[1]+1)){
    TString volName = encoder->DetectorIDToVolName(sensor);
    volName.ReplaceAll("Sensor", "");

    rec_cutg[sensor].SetName(Form("rec_cutg_%s", volName.Data()));
    auto rec_boundaries = geoHandler->GetDetBoundaryPointsById(sensor);
    for ( auto point=0; point < 4; point++ ) {
      rec_cutg[sensor].SetPoint(point, rec_boundaries[point].z(), rec_boundaries[point].y());
    }
    rec_cutg[sensor].SetPoint(4, rec_boundaries[0].z(), rec_boundaries[0].y());
  }

  // fwd
  Int_t FwdIdRange[2];
  encoder->GetFwdDetIDRange(FwdIdRange[0], FwdIdRange[1]);
  FwdIdRange[1] = FwdIdRange[0]+1; // now FwdIdRange represent the two fwd scintillators we're interested

  Double_t fwd_distance_1 = geoHandler->GetDetPositionById(FwdIdRange[0]);
  Double_t fwd_distance_2 = geoHandler->GetDetPositionById(FwdIdRange[1]);
  std::cout << "fwd distance: " << fwd_distance_1 << ", " << fwd_distance_2
            << std::endl;

  PointArray fwd_boundaries_1 = geoHandler->GetDetBoundaryPointsById(FwdIdRange[0]);
  PointArray fwd_boundaries_2 = geoHandler->GetDetBoundaryPointsById(FwdIdRange[1]);

  TCutG fwd_cutg_1("fwd_cutg_1"); fwd_cutg_1.SetLineWidth(2); fwd_cutg_1.SetLineColor(kRed);
  TCutG fwd_cutg_2("fwd_cutg_2"); fwd_cutg_2.SetLineWidth(2); fwd_cutg_2.SetLineColor(kRed);
  for( auto point=0; point < 4; point++ ) {
    fwd_cutg_1.SetPoint(point, fwd_boundaries_1[point].x(), fwd_boundaries_1[point].y()+fwd_offset/10.);
    fwd_cutg_2.SetPoint(point, fwd_boundaries_2[point].x(), fwd_boundaries_2[point].y()+fwd_offset/10.);
    std::cout << "fwd boundary " << point+1 << ": x = " << fwd_boundaries_1[point].x() << ", y = " << fwd_boundaries_1[point].y()+(double)fwd_offset/10. << std::endl;
  }
  fwd_cutg_1.SetPoint(4, fwd_boundaries_1[0].x(), fwd_boundaries_1[0].y()+fwd_offset/10.);
  fwd_cutg_2.SetPoint(4, fwd_boundaries_2[0].x(), fwd_boundaries_2[0].y()+fwd_offset/10.);

  // output txt paramaeters
  ParameterList<double> CountsParameter;
  auto& output_total = addValueContainer(CountsParameter, "Total");
  auto& output_covered = addValueContainer(CountsParameter, "FwdCovered");
  auto& output_ratio = addValueContainer(CountsParameter, "Ratio");

  auto ChIDs = encoder->GetRecChIDs();
  for(auto id: ChIDs) {
    output_total.emplace(id, 0);
    output_covered.emplace(id, 0);
  }

  //
  auto h1_total = bookH1dByDetectorId("total","Event Counts (Total);E (MeV); EvtNr",
                                      nbins, xlow, xhigh);
  auto h1_covered = bookH1dByDetectorId("covered","Event Counts (Fwd Covered);E (MeV); EvtNr",
                                         nbins, xlow, xhigh);

  std::map<int, TEfficiency*> eff;
  for(auto sensor : ROOT::TSeqI(RecIdRange[0],RecIdRange[1]+1)){
    TString volName = encoder->DetectorIDToVolName(sensor);
    volName.ReplaceAll("Sensor", "");

    eff[sensor] = new TEfficiency(Form("ratio_%s",volName.Data()), Form("Ratio of Fwd-Covered Events (%s); E (MeV);Ratio", volName.Data()),
                                  nbins, xlow, xhigh);
    eff[sensor]->SetStatisticOption(TEfficiency::kFAC);
    eff[sensor]->SetConfidenceLevel(0.95);
    eff[sensor]->SetFillColor(kBlue);
    eff[sensor]->SetFillStyle(3005);
    eff[sensor]->SetMarkerColor(kBlue);
    eff[sensor]->SetMarkerStyle(20);
    eff[sensor]->SetMarkerSize(0.3);
  }


  // input
  TFile* fPrimary = new TFile(primaryFile);
  TTree* tPrimary = (TTree*)fPrimary->Get("koalasim");
  TClonesArray *MCTracks  = new TClonesArray("KoaMCTrack",10);
  tPrimary->SetBranchAddress("MCTrack", &MCTracks);

  if(entries<0)
    entries = tPrimary->GetEntriesFast();
  for( auto entry=0; entry < entries; entry++ ) {
    tPrimary->GetEntry(entry);

    // pick out beam and recoil particle
    Int_t ntracks = MCTracks->GetEntries();
    std::vector<Int_t> indexes;
    Int_t beam_index;
    Double_t maxPz = 0;
    for( auto track=0; track < ntracks; track++ ) {
      KoaMCTrack* MCTrack = (KoaMCTrack*)MCTracks->At(track);
      if( MCTrack->GetMotherId() == -1 ) {
        auto Pz = MCTrack->GetPz();
        if( Pz > maxPz ) {
          maxPz = Pz;
          beam_index = track;
        }
        indexes.emplace_back(track);
      }
    }

    if ( indexes.size() !=2 ) {
      std::cout << "The macro is only useful for two-body elastic scattering " << std::endl;
      break;
    }

    KoaMCTrack* recoilParticle = nullptr;
    KoaMCTrack* beamParticle = nullptr;
    if( indexes[0] == beam_index ) {
      beamParticle = (KoaMCTrack*)MCTracks->At(indexes[0]);
      recoilParticle = (KoaMCTrack*)MCTracks->At(indexes[1]);
    }
    else {
      recoilParticle = (KoaMCTrack*)MCTracks->At(indexes[0]);
      beamParticle = (KoaMCTrack*)MCTracks->At(indexes[1]);
    }

    // calculate the hit position 
    // rec
    Double_t recoil_ratio = rec_distance*recoilParticle->GetPx();
    if( recoil_ratio < 0 ) {
      std::cout << "Error: incorrect recoil particle picked!" << std::endl;
      break;
    }

    recoil_ratio = (rec_distance-recoilParticle->GetStartX())/recoilParticle->GetPx();
    Double_t recoil_hit_y = recoil_ratio * recoilParticle->GetPy() + recoilParticle->GetStartY();
    Double_t recoil_hit_z = recoil_ratio * recoilParticle->GetPz() + recoilParticle->GetStartZ();

    // fwd
    Double_t fwd_ratio_1 = fwd_distance_1*beamParticle->GetPz();
    Double_t fwd_ratio_2 = fwd_distance_2*beamParticle->GetPz();
    if( fwd_ratio_1 < 0 || fwd_ratio_2 < 0 ) {
      std::cout << "Error: incorrect beam particle picked!" << std::endl;
      break;
    }

    fwd_ratio_1 = (fwd_distance_1-beamParticle->GetStartZ())/beamParticle->GetPz();
    fwd_ratio_2 = (fwd_distance_2-beamParticle->GetStartZ())/beamParticle->GetPz();
    Double_t fwd_hit_x_1 = fwd_ratio_1 * beamParticle->GetPx() + beamParticle->GetStartX();
    Double_t fwd_hit_y_1 = fwd_ratio_1 * beamParticle->GetPy() + beamParticle->GetStartY();
    Double_t fwd_hit_x_2 = fwd_ratio_2 * beamParticle->GetPx() + beamParticle->GetStartX();
    Double_t fwd_hit_y_2 = fwd_ratio_2 * beamParticle->GetPy() + beamParticle->GetStartY();

    // checking whether the hits are in acceptance and fill the histograms
    // rec
    for( auto item : rec_cutg ) {
      auto det_id = item.first;
      auto& cutg = item.second;

      if ( cutg.IsInside(recoil_hit_z, recoil_hit_y) ) {
        Double_t global[3], local[3];
        global[0] = -rec_distance;
        global[1] = recoil_hit_y;
        global[2] = recoil_hit_z;
        geoHandler->GlobalToLocal(global,local,det_id);

        Int_t id = geoHandler->RecLocalPositionToDetCh(local,det_id);
        auto e = (recoilParticle->GetEnergy()-recoilParticle->GetMass())*1e3;
        h1_total[det_id].Fill(e);
        output_total[id]++;
        if ( fwd_cutg_1.IsInside(fwd_hit_x_1, fwd_hit_y_1)
             &&  fwd_cutg_2.IsInside(fwd_hit_x_2, fwd_hit_y_2)
             ) {
          h1_covered[det_id].Fill(e);
          eff[det_id]->Fill(true, e);
          output_covered[id]++;
        }
        else{
          eff[det_id]->Fill(false, e);
        }
        break;
      }
    }
  }

  // root
  TString outputfilename(primaryFile);
  outputfilename.ReplaceAll(".root", "_FwdCovered.root");
  auto fout = TFile::Open(outputfilename.Data(), "update");
  auto dirout = getDirectory(fout, Form("fwd_offset_%.1fmm",fwd_offset));
  writeHistos<TH1D>(dirout, h1_total);
  writeHistos<TH1D>(dirout, h1_covered);

  // txt file
  TString txtfile(primaryFile);
  txtfile.ReplaceAll(".root", Form("_FwdCovered_FwdOffset_%.1fmm.txt", fwd_offset));
  calcValueContainer<double>(output_covered, output_total, output_ratio);
  printValueList<double>(CountsParameter, txtfile.Data());

  // Compute and save coverage ratio
  for(auto sensor : ROOT::TSeqI(RecIdRange[0],RecIdRange[1]+1)){
    // TString volName = encoder->DetectorIDToVolName(sensor);
    // volName.ReplaceAll("Sensor", "");
    // txtfile = primaryFile;
    // txtfile.ReplaceAll(".root",Form("_FwdCoveredRatio_%s",volName.Data()));

    dirout->WriteTObject(eff[sensor],"","WriteDelete");
  }

  // cleanning
  delete fgeo;
  delete fPrimary;
  delete fout;

  //
  timer.Stop();
  timer.Print();
}
