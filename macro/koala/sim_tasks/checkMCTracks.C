#include "KoaColors.h"
#include "KoaHistUtility.h"

using namespace KoaUtility;

// this macro can only be used for two-body elastic scattering events
void checkAcceptance(const char* primaryFile, // root file from simulation macro, containing MCTrack tree
                     const char* geoFile = "../calib_para/geo_standard.root",
                     long entries = -1) // the detector geometry to be checked
{
  //
  TStopwatch timer;
  TH1::AddDirectory(false);

  using PointArray = std::vector<TVector3>;

  // setup color scheme
  init_KoaColors();
  set_KoaPalette_Sunset(100);

  // book histograms
  // rec
  Int_t nXbinRec = 350;
  Double_t xLowRec = -5, xHighRec = 30; // in cm
  Int_t nYbinRec = 200;
  Double_t yLowRec = -10, yHighRec = 10; // in cm

  TH2D* h2rec_acceptance = new TH2D("h2_Rec_Acceptance", "Recoil Detector Acceptance;Z (cm);Y (cm)",
                                    nXbinRec, xLowRec, xHighRec,
                                    nYbinRec, yLowRec, yHighRec);
  TH2D* h2rec_hitmap = new TH2D("h2_Rec_Hitmap", "Recoil Detector Hitmap; Z(cm);Y (cm)",
                                nXbinRec, xLowRec, xHighRec,
                                nYbinRec, yLowRec, yHighRec);

  // fwd
  Int_t nXbinFwd = 1300;
  Double_t xLowFwd = 0, xHighFwd = 65; // in cm
  Int_t nYbinFwd = 250;
  Double_t yLowFwd = -4, yHighFwd = 4; // in cm

  TH2D* h2fwd_acceptance_1 = new TH2D("h2_Fwd_Acceptance_1", "Fwd_1 Detector Acceptance;X (cm);Y (cm)",
                                      nXbinFwd, xLowFwd, xHighFwd,
                                      nYbinFwd, yLowFwd, yHighFwd);
  TH2D* h2fwd_acceptance_2 = new TH2D("h2_Fwd_Acceptance_2", "Fwd_2 Detector Acceptance;X (cm);Y (cm)",
                                      nXbinFwd, xLowFwd, xHighFwd,
                                      nYbinFwd, yLowFwd, yHighFwd);
  TH2D* h2fwd_hitmap_1 = new TH2D("h2_Fwd_Hitmap_1", "Fwd_1 Detector Hitmap;X (cm);Y (cm)",
                                  nXbinFwd, xLowFwd, xHighFwd,
                                  nYbinFwd, yLowFwd, yHighFwd);
  TH2D* h2fwd_hitmap_2 = new TH2D("h2_Fwd_Hitmap_2", "Fwd_2 Detector Hitmap;X (cm);Y (cm)",
                                  nXbinFwd, xLowFwd, xHighFwd,
                                  nYbinFwd, yLowFwd, yHighFwd);

  // vertex
  TH2D* h2vertex_xy = new TH2D("h2vertex_xy", "Primary Vertex;X(mm);Y(mm)",20,-10,10, 20,-10,10);
  TH1D* h1vertex_z = new TH1D("h1vertex_z", "Primary Vertex;Z(mm)",40,-2,2);

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

  std::vector<TCutG> rec_cutg;
  for(auto sensor : ROOT::TSeqI(RecIdRange[0],RecIdRange[1]+1)){
    TString volName = encoder->DetectorIDToVolName(sensor);
    volName.ReplaceAll("Sensor", "");

    auto cutg = rec_cutg.emplace(rec_cutg.end(), Form("rec_cutg_%s", volName.Data()));
    cutg->SetLineWidth(2);
    cutg->SetLineColor(kRed);
    auto rec_boundaries = geoHandler->GetDetBoundaryPointsById(sensor);
    for ( auto point=0; point < 4; point++ ) {
      cutg->SetPoint(point, rec_boundaries[point].z(), rec_boundaries[point].y());
    }
    cutg->SetPoint(4, rec_boundaries[0].z(), rec_boundaries[0].y());
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
    fwd_cutg_1.SetPoint(point, fwd_boundaries_1[point].x(), fwd_boundaries_1[point].y());
    fwd_cutg_2.SetPoint(point, fwd_boundaries_2[point].x(), fwd_boundaries_2[point].y());
  }
  fwd_cutg_1.SetPoint(4, fwd_boundaries_1[0].x(), fwd_boundaries_1[0].y());
  fwd_cutg_2.SetPoint(4, fwd_boundaries_2[0].x(), fwd_boundaries_2[0].y());

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
    for( auto cutg : rec_cutg ) {
      if ( cutg.IsInside(recoil_hit_z, recoil_hit_y) ) {
        h2fwd_acceptance_1->Fill(fwd_hit_x_1, fwd_hit_y_1);
        h2fwd_acceptance_2->Fill(fwd_hit_x_2, fwd_hit_y_2);

        h2rec_hitmap->Fill(recoil_hit_z, recoil_hit_y);
        break;
      }
    }

    // fwd
    if ( fwd_cutg_1.IsInside(fwd_hit_x_1, fwd_hit_y_1) ) {
      h2fwd_hitmap_1->Fill(fwd_hit_x_1, fwd_hit_y_1);
      if( fwd_cutg_2.IsInside(fwd_hit_x_2, fwd_hit_y_2) ) {
        h2rec_acceptance->Fill(recoil_hit_z, recoil_hit_y);
      }
    }

    if ( fwd_cutg_2.IsInside(fwd_hit_x_2, fwd_hit_y_2) ) {
      h2fwd_hitmap_2->Fill(fwd_hit_x_2, fwd_hit_y_2);
    }

    // vertex
    h2vertex_xy->Fill(beamParticle->GetStartX()*10, beamParticle->GetStartY()*10);
    h1vertex_z->Fill(beamParticle->GetStartZ()*10);
  }

  // drawing and output
  // output 
  TString outFile(primaryFile);
  outFile.ReplaceAll(".root", "_acceptance.root");
  TString pdfFile(primaryFile);
  pdfFile.ReplaceAll(".root", "_acceptance.pdf");

  //
  TCanvas* canpdf = new TCanvas("canpdf");
  canpdf->Print(pdfFile+"[");

  // rec
  h2rec_acceptance->Draw("colz");
  for( auto& cutg: rec_cutg ) {
    cutg.Draw("same");
  }
  canpdf->Print(pdfFile);

  // fwd
  h2fwd_acceptance_1->Draw("colz");
  fwd_cutg_1.Draw("same");
  canpdf->Print(pdfFile);

  h2fwd_acceptance_2->Draw("colz");
  fwd_cutg_2.Draw("same");
  canpdf->Print(pdfFile);

  canpdf->Print(pdfFile+"]");

  //
  TFile* fOutput = new TFile(outFile, "recreate");
  h2rec_acceptance->Write(0,TObject::kOverwrite);
  h2rec_hitmap->Write(0,TObject::kOverwrite);
  h2fwd_acceptance_1->Write(0,TObject::kOverwrite);
  h2fwd_acceptance_2->Write(0,TObject::kOverwrite);
  h2fwd_hitmap_1->Write(0,TObject::kOverwrite);
  h2fwd_hitmap_2->Write(0,TObject::kOverwrite);
  h2vertex_xy->Write(0,TObject::kOverwrite);
  h1vertex_z->Write(0,TObject::kOverwrite);

  for( auto cutg : rec_cutg ) {
    cutg.Write(0, TObject::kOverwrite);
  }
  fwd_cutg_1.Write(0, TObject::kOverwrite);
  fwd_cutg_2.Write(0, TObject::kOverwrite);

  // cleanning
  delete fgeo;
  delete fPrimary;
  delete fOutput;

  //
  timer.Stop();
  timer.Print();
}
