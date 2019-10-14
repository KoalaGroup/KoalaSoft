void checkDigi(const char* filename)
{
  // parameters
  Int_t nbin=7000;
  Float_t xlow=0,xhigh=70;
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  std::vector<Int_t> ChIDs = encoder->GetChIDs();
  Int_t RecIdRange[2];

  // Int_t FwdIdRange[2];
  encoder->GetRecDetIDRange(RecIdRange[0], RecIdRange[1]);

  // input
  TFile* f = new TFile(filename,"update");
  TTree* tree = (TTree*)f->Get("koalasim");
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress("KoaRecDigi",&RecDigis);

  TDirectory* hdir;
  if(!(hdir=f->GetDirectory("histograms")))
    hdir = f->mkdir("histograms");

  // histograms definition
  std::map<Int_t, TH2D*> h2map_EnergyVsPosition;
  TH2D *h2p = nullptr;
  Int_t ChNr;
  for(int id=RecIdRange[0];id<=RecIdRange[1];id++){
    ChNr = encoder->GetChNr(id);
    h2p = new TH2D(Form("h2_EnergyVsPosition_%s",encoder->DetectorIDToVolName(id)),Form("h2_EnergyVsPosition_%s",encoder->DetectorIDToVolName(id)), ChNr, 0.5, 0.5+ChNr, nbin, xlow,xhigh);
    h2map_EnergyVsPosition.emplace(id, h2p);
  }

  std::map<Int_t, TH1D*> h1map_Energy;
  TH1D* h1p = nullptr;
  TString volName;
  Int_t ch_id;
  for(auto id=ChIDs.cbegin();id!=ChIDs.cend();id++){
    ch_id = encoder->DecodeChannelID(*id, volName);
    h1p = new TH1D(Form("h1_energy_%s_%d",volName.Data(), ch_id+1), Form("h1_energy_%s_%d",volName.Data(), ch_id+1), nbin, xlow, xhigh);
    h1map_Energy.emplace(*id, h1p);
  }

  // event loop
  Int_t entries = tree->GetEntries();
  Int_t det_id;
  Double_t charge;
  Double_t timestamp;
  for(int id=0;id<entries;id++){
    tree->GetEntry(id);
    //
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      ch_id = encoder->DecodeChannelID(digi->GetDetID(), det_id);
      charge = digi->GetCharge();

      h2map_EnergyVsPosition[det_id]->Fill(ch_id+1, charge);
      h1map_Energy[digi->GetDetID()]->Fill(charge);
    }
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  hdir->cd();
  for(auto it=h2map_EnergyVsPosition.cbegin();it!=h2map_EnergyVsPosition.cend();it++){
    it->second->Write(0,TObject::kOverwrite);
  }
  for(auto it=h1map_Energy.cbegin();it!=h1map_Energy.cend();it++){
    it->second->Write(0,TObject::kOverwrite);
  }

  delete f;
}
