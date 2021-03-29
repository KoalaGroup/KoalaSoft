void drawMCEnergy(const char* primaryFile)
{
  //
  TStopwatch timer;
  TH1::AddDirectory(false);
  
  //
  auto h1_energy = new TH1D("h1_energy","Recoil Proton Energy",7000,0,70);

  // input
  TFile* fPrimary = new TFile(primaryFile);
  TTree* tPrimary = (TTree*)fPrimary->Get("koalasim");
  TClonesArray *MCTracks  = new TClonesArray("KoaMCTrack",10);
  tPrimary->SetBranchAddress("MCTrack", &MCTracks);

  Long64_t entries = tPrimary->GetEntriesFast();
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

    //
    h1_energy->Fill(1000*(recoilParticle->GetEnergy()-recoilParticle->GetMass()));
  }

  delete fPrimary;

  h1_energy->Draw();
}
