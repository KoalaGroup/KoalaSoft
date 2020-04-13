void transform_old(const char* filename, const char* outfile)
{
  auto f = new TFile(filename);
  TTreeReader reader("KoalaEvent", f);

  TTreeReaderArray<Int_t> fSi1Amplitude(reader, "fSi1Amplitude[48]");
  TTreeReaderArray<Int_t> fSi2Amplitude = {reader, "fSi2Amplitude[64]"};
  TTreeReaderArray<Int_t> fGe1Amplitude = {reader, "fGe1Amplitude[32]"};
  TTreeReaderArray<Int_t> fGe2Amplitude = {reader, "fGe2Amplitude[32]"};
  TTreeReaderArray<Int_t> fRecRearAmplitude = {reader, "fRecRearAmplitude[4]"};
  TTreeReaderArray<Int_t> fFwdAmplitude = {reader, "fFwdAmplitude[8]"};
  TTreeReaderArray<Float_t> fSi1Time = {reader, "fSi1Time[48]"};
  TTreeReaderArray<Float_t> fSi2Time = {reader, "fSi2Time[64]"};
  TTreeReaderArray<Float_t> fGe1Time = {reader, "fGe1Time[32]"};
  TTreeReaderArray<Float_t> fGe2Time = {reader, "fGe2Time[32]"};
  TTreeReaderArray<Float_t> fRecRearTime = {reader, "fRecRearTime[2]"};
  TTreeReaderArray<Float_t> fFwdTime = {reader, "fFwdTime[8]"};

  auto fout = new TFile(outfile,"recreate");
  auto tout = new TTree("raw","Raw Event");
  Int_t si1a[48];
  Int_t si2a[64];
  Int_t ge1a[32];
  Int_t ge2a[32];
  Int_t reara[4];
  Int_t fwda[8];
  Float_t si1t[48];
  Float_t si2t[64];
  Float_t ge1t[32];
  Float_t ge2t[32];
  Float_t reart[2];
  Float_t fwdt[8];

  tout->Branch("si1a",si1a,"si1a[48]/I");
  tout->Branch("si2a",si2a,"si2a[64]/I");
  tout->Branch("ge1a",ge1a,"ge1a[32]/I");
  tout->Branch("ge2a",ge2a,"ge2a[32]/I");
  tout->Branch("reara",reara,"reara[4]/I");
  tout->Branch("fwda",fwda,"fwda[8]/I");
  tout->Branch("si1t",si1t,"si1t[48]/F");
  tout->Branch("si2t",si2t,"si2t[64]/F");
  tout->Branch("ge1t",ge1t,"ge1t[32]/F");
  tout->Branch("ge2t",ge1t,"ge2t[32]/F");
  tout->Branch("reart",reart,"reart[2]/F");
  tout->Branch("fwdt",fwdt,"fwdt[8]/F");

  while(reader.Next()){
    for(int i =0; i<48;i++){
      si1a[i] = fSi1Amplitude[i];
    }
    for(int i =0; i<64;i++){
      si2a[i] = fSi2Amplitude[i];
    }
    for(int i =0; i<32;i++){
      ge1a[i] = fGe1Amplitude[i];
    }
    for(int i =0; i<32;i++){
      ge2a[i] = fGe2Amplitude[i];
    }
    for(int i =0; i<4;i++){
      reara[i] = fRecRearAmplitude[i];
    }
    for(int i =0; i<8;i++){
      fwda[i] = fFwdAmplitude[i];
    }

    for(int i =0; i<48;i++){
      si1t[i] = fSi1Time[i];
    }
    for(int i =0; i<64;i++){
      si2t[i] = fSi2Time[i];
    }
    for(int i =0; i<32;i++){
      ge1t[i] = fGe1Time[i];
    }
    for(int i =0; i<32;i++){
      ge2t[i] = fGe2Time[i];
    }
    for(int i =0; i<2;i++){
      reart[i] = fRecRearTime[i];
    }
    for(int i =0; i<8;i++){
      fwdt[i] = fFwdTime[i];
    }
    tout->Fill();
  }
  tout->Write();

  delete f;
  delete fout;
}

void transform_new(const char *filename, const char *outfile) {
  auto f = new TFile(filename);
  TTreeReader reader("koalasim", f);

  TTreeReaderArray<Int_t> fSi1Amplitude(reader, "Si1A[48]");
  TTreeReaderArray<Int_t> fSi2Amplitude = {reader, "Si2A[64]"};
  TTreeReaderArray<Int_t> fGe1Amplitude = {reader, "Ge1A[32]"};
  TTreeReaderArray<Int_t> fGe2Amplitude = {reader, "Ge2A[32]"};
  TTreeReaderArray<Int_t> fRecRearAmplitude = {reader, "RecRearA[4]"};
  TTreeReaderArray<Int_t> fFwdAmplitude = {reader, "FwdA[8]"};
  TTreeReaderArray<Float_t> fSi1Time = {reader, "Si1T[48]"};
  TTreeReaderArray<Float_t> fSi2Time = {reader, "Si2T[64]"};
  TTreeReaderArray<Float_t> fGe1Time = {reader, "Ge1T[32]"};
  TTreeReaderArray<Float_t> fGe2Time = {reader, "Ge2T[32]"};
  TTreeReaderArray<Float_t> fRecRearTime = {reader, "RecRearT[4]"};
  TTreeReaderArray<Float_t> fFwdTime = {reader, "FwdT[8]"};

  auto fout = new TFile(outfile, "recreate");
  auto tout = new TTree("raw", "Raw Event");

  Int_t si1a[48];
  Int_t si2a[64];
  Int_t ge1a[32];
  Int_t ge2a[32];
  Int_t reara[4];
  Int_t fwda[8];
  Float_t si1t[48];
  Float_t si2t[64];
  Float_t ge1t[32];
  Float_t ge2t[32];
  Float_t reart[2];
  Float_t fwdt[8];

  tout->Branch("si1a",si1a,"si1a[48]/I");
  tout->Branch("si2a",si2a,"si2a[64]/I");
  tout->Branch("ge1a",ge1a,"ge1a[32]/I");
  tout->Branch("ge2a",ge2a,"ge2a[32]/I");
  tout->Branch("reara",reara,"reara[4]/I");
  tout->Branch("fwda",fwda,"fwda[8]/I");
  tout->Branch("si1t",si1t,"si1t[48]/F");
  tout->Branch("si2t",si2t,"si2t[64]/F");
  tout->Branch("ge1t",ge1t,"ge1t[32]/F");
  tout->Branch("ge2t",ge1t,"ge2t[32]/F");
  tout->Branch("reart",reart,"reart[2]/F");
  tout->Branch("fwdt",fwdt,"fwdt[8]/F");

  while (reader.Next()) {
    for (int i = 0; i < 48; i++) {
      si1a[i] = fSi1Amplitude[i];
    }
    for (int i = 0; i < 64; i++) {
      si2a[i] = fSi2Amplitude[i];
    }
    for (int i = 0; i < 32; i++) {
      ge1a[i] = fGe1Amplitude[i];
    }
    for (int i = 0; i < 32; i++) {
      ge2a[i] = fGe2Amplitude[i];
    }
    for (int i = 0; i < 4; i++) {
      reara[i] = fRecRearAmplitude[i];
    }
    for (int i = 0; i < 8; i++) {
      fwda[i] = fFwdAmplitude[i];
    }

    for (int i = 0; i < 48; i++) {
      si1t[i] = fSi1Time[i];
    }
    for (int i = 0; i < 64; i++) {
      si2t[i] = fSi2Time[i];
    }
    for (int i = 0; i < 32; i++) {
      ge1t[i] = fGe1Time[i];
    }
    for (int i = 0; i < 32; i++) {
      ge2t[i] = fGe2Time[i];
    }
    for (int i = 0; i < 2; i++) {
      reart[i] = fRecRearTime[i];
    }
    for (int i = 0; i < 8; i++) {
      fwdt[i] = fFwdTime[i];
    }

    tout->Fill();
  }
  tout->Write();

  delete f;
  delete fout;
}

void compare(const char* oldfile, const char* newfile)
{
  auto fold = new TFile(oldfile);
  TTree* told = 0;
  fold->GetObject("raw", told);

  Int_t si1a_old[48];
  Int_t si2a_old[64];
  Int_t ge1a_old[32];
  Int_t ge2a_old[32];
  Int_t reara_old[4];
  Int_t fwda_old[8];
  Float_t si1t_old[48];
  Float_t si2t_old[64];
  Float_t ge1t_old[32];
  Float_t ge2t_old[32];
  Float_t reart_old[2];
  Float_t fwdt_old[8];
  told->SetBranchAddress("si1a",si1a_old);
  told->SetBranchAddress("si2a",si2a_old);
  told->SetBranchAddress("ge1a",ge1a_old);
  told->SetBranchAddress("ge2a",ge2a_old);
  told->SetBranchAddress("reara",reara_old);
  told->SetBranchAddress("fwda",fwda_old);
  told->SetBranchAddress("si1t",si1t_old);
  told->SetBranchAddress("si2t",si2t_old);
  told->SetBranchAddress("ge1t",ge1t_old);
  told->SetBranchAddress("ge2t",ge2t_old);
  told->SetBranchAddress("reart",reart_old);
  told->SetBranchAddress("fwdt",fwdt_old);

  auto fnew = new TFile(newfile);
  TTree *tnew = 0;
  fnew->GetObject("raw", tnew);

  Int_t si1a_new[48];
  Int_t si2a_new[64];
  Int_t ge1a_new[32];
  Int_t ge2a_new[32];
  Int_t reara_new[4];
  Int_t fwda_new[8];
  Float_t si1t_new[48];
  Float_t si2t_new[64];
  Float_t ge1t_new[32];
  Float_t ge2t_new[32];
  Float_t reart_new[2];
  Float_t fwdt_new[8];
  tnew->SetBranchAddress("si1a",si1a_new);
  tnew->SetBranchAddress("si2a",si2a_new);
  tnew->SetBranchAddress("ge1a",ge1a_new);
  tnew->SetBranchAddress("ge2a",ge2a_new);
  tnew->SetBranchAddress("reara",reara_new);
  tnew->SetBranchAddress("fwda",fwda_new);
  tnew->SetBranchAddress("si1t",si1t_new);
  tnew->SetBranchAddress("si2t",si2t_new);
  tnew->SetBranchAddress("ge1t",ge1t_new);
  tnew->SetBranchAddress("ge2t",ge2t_new);
  tnew->SetBranchAddress("reart",reart_new);
  tnew->SetBranchAddress("fwdt",fwdt_new);

  told->AddFriend(tnew);
  auto entries = told->GetEntries();
  for( auto entry = 0; entry<entries; entry++)
  {
    told->GetEntry(entry);

    for(int i = 0;i<48;i++){
      if(si1a_old[i] != si1a_new[i]){
        std::cout<<"Error\n";
        return;
      }
    }
    for(int i =0; i<64;i++){
      if(si2a_old[i] != si2a_new[i]){
        std::cout<<"Error\n";
        return;
      }
    }
    for(int i =0; i<32;i++){
      if(ge1a_old[i] != ge1a_new[i]){
        std::cout<<"Error\n";
        return;
      }
    }
    for(int i =0; i<32;i++){
      if(ge2a_old[i] != ge2a_new[i]){
        std::cout<<"Error\n";
        return;
      }
    }
    for(int i =0; i<4;i++){
      if(reara_old[i] != reara_new[i]){
        std::cout<<"Error\n";
        return;
      }
    }
    for(int i =0; i<8;i++){
      if(fwda_old[i] != fwda_new[i]){
        std::cout<<"Error\n";
        return;
      }
    }

    for(int i = 0;i<48;i++){
      if(si1t_old[i] != si1t_new[i]){
        std::cout<<"Error\n";
        return;
      }
    }
    for(int i =0; i<38;i++){
      if(si2t_old[i] != si2t_new[i]){
        std::cout<<"Error\n";
        return;
      }
    }
    // for(int i =0; i<32;i++){
    //   if(ge1t_old[i] != ge1t_new[i]){
    //     std::cout<<"Error\n";
    //     return;
    //   }
    // }
    // for(int i =0; i<32;i++){
    //   if(ge2t_old[i] != ge2t_new[i]){
    //     std::cout<<"Error\n";
    //     return;
    //   }
    // }
    for(int i =0; i<2;i++){
      if(reart_old[i] != reart_new[i]){
        std::cout<<"Error\n";
        return;
      }
    }
    for(int i =0; i<8;i++){
      if(fwdt_old[i] != fwdt_new[i]){
        std::cout<<"Error\n";
        return;
      }
    }
  }

  delete fold;
  delete fnew;
}
