void checkDigi(const char* filename)
{
  // ROOT::EnableImplicitMT(1);
  TH1::AddDirectory(false);

  // timer
  TStopwatch timer;
  
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
      charge = 1000*digi->GetCharge();

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

  // timer stat
  timer.Stop();
  timer.Print();
}

void checkDigi_rdf(const char* infile, const char* outfile)
{
  ROOT::EnableImplicitMT(6);
  // ROOT::GeImplicitMTPoolSize();
  TH1::AddDirectory(false);

  // timer start
  TStopwatch timer;
  // timer.Start();

  //
  using integers = ROOT::VecOps::RVec<Int_t>;
  using doubles  = ROOT::VecOps::RVec<Double_t>;
  using histo1d = std::map<Int_t, TH1D>;
  using histo2d = std::map<Int_t, TH2D>;

  // book histograms
  Int_t nbin=7000;
  Float_t xlow=0,xhigh=70;

  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  std::vector<Int_t> ChIDs = encoder->GetChIDs();
  Int_t RecIdRange[2]; encoder->GetRecDetIDRange(RecIdRange[0], RecIdRange[1]);

  histo2d h2map_EnergyVsPosition;
  for(int id=RecIdRange[0];id<=RecIdRange[1];id++){
    Int_t ChNr = encoder->GetChNr(id);
    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h2_EnergyVsPosition_%s",encoder->DetectorIDToVolName(id)),Form("h2_EnergyVsPosition_%s",encoder->DetectorIDToVolName(id)), ChNr, 0.5, 0.5+ChNr, nbin, xlow,xhigh);
    h2map_EnergyVsPosition.emplace(std::piecewise_construct, tindex, thist);
  }

  histo1d h1map_Energy;
  for(auto id=ChIDs.cbegin();id!=ChIDs.cend();id++){
    TString volName; Int_t ch_id = encoder->DecodeChannelID(*id, volName);

    auto tindex = std::make_tuple(*id);
    auto thist  = std::make_tuple(Form("h1_energy_%s_%d",volName.Data(), ch_id+1), Form("h1_energy_%s_%d",volName.Data(), ch_id+1), nbin, xlow, xhigh);
    h1map_Energy.emplace(std::piecewise_construct, tindex, thist);
  }

  // define lambda
  auto fillhist = [&] (integers ids, doubles charges){
    charges*=1000;

    const auto size = ids.size();
    // for(const auto& id: ids){
    for(size_t i=0;i<size;i++){
      Int_t det_id, ch_id;
      Double_t charge;
      Double_t timestamp;
      
      ch_id = encoder->DecodeChannelID(ids[i], det_id);
      h2map_EnergyVsPosition[det_id].Fill(ch_id+1,charges[i]);
      h1map_Energy[ids[i]].Fill(charges[i]);
    }
  };

  // rdf process
  ROOT::RDataFrame rdf("koalasim",infile);
  rdf.Foreach(fillhist,{"KoaRecDigi.fDetID","KoaRecDigi.fCharge"});

  // write histograms
  auto fout=TFile::Open(infile,"update");
  TDirectory* hdir;
  if(!(hdir=fout->GetDirectory("histograms")))
    hdir = fout->mkdir("histograms");

  for(auto& hist: h2map_EnergyVsPosition){
    hist.second.Print();
    hdir->WriteTObject(&hist.second,"","WriteDelete");
  }
  for(auto& hist: h1map_Energy){
    hist.second.Print();
    hdir->WriteTObject(&hist.second,"","WriteDelete");
  }

  delete fout;

  // timer stop
  timer.Stop();
  timer.Print();
}

// DataFrame + Threaded Histogram + IMT
void checkDigi_rdf_threaded(const char* infile)
{
  // switches
  ROOT::EnableImplicitMT(6);
  // ROOT::GeImplicitMTPoolSize();
  TH1::AddDirectory(false);

  // timer start
  TStopwatch timer;
  // timer.Start();

  //
  using integers = ROOT::VecOps::RVec<Int_t>;
  using doubles  = ROOT::VecOps::RVec<Double_t>;
  using histo1d = std::map<Int_t, ROOT::TThreadedObject<TH1D>>;
  using histo2d = std::map<Int_t, ROOT::TThreadedObject<TH2D>>;

  // book histograms
  Int_t nbin=7000;
  Float_t xlow=0,xhigh=70;

  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  std::vector<Int_t> ChIDs = encoder->GetChIDs();
  Int_t RecIdRange[2]; encoder->GetRecDetIDRange(RecIdRange[0], RecIdRange[1]);

  histo2d h2map_EnergyVsPosition;
  for(auto id: ROOT::TSeqI(RecIdRange[0],RecIdRange[1]+1)){
    Int_t ChNr = encoder->GetChNr(id);
    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h2_EnergyVsPosition_%s",encoder->DetectorIDToVolName(id)),Form("h2_EnergyVsPosition_%s",encoder->DetectorIDToVolName(id)), ChNr, 0.5, 0.5+ChNr, nbin, xlow,xhigh);
    h2map_EnergyVsPosition.emplace(std::piecewise_construct, tindex, thist);
  }

  histo1d h1map_Energy;
  for(auto& id: ChIDs){
    TString volName; Int_t ch_id = encoder->DecodeChannelID(id, volName);

    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h1_energy_%s_%d",volName.Data(), ch_id+1), Form("h1_energy_%s_%d",volName.Data(), ch_id+1), nbin, xlow, xhigh);
    auto it = h1map_Energy.emplace(std::piecewise_construct, tindex, thist);
    it.first->second->GetName();//lazy init, make sure histogram is constructed
  }

  // define lambda
  auto fillhist = [&] (integers ids, doubles charges){
    charges*=1000;

    const auto size = ids.size();
    // for(const auto& id: ids){
    // for(size_t i=0;i<size;i++){
    for(auto i: ROOT::TSeqI(size)){
      Int_t det_id, ch_id;
      Double_t charge;
      Double_t timestamp;
      
      ch_id = encoder->DecodeChannelID(ids[i], det_id);
      h2map_EnergyVsPosition[det_id]->Fill(ch_id+1,charges[i]);
      h1map_Energy[ids[i]]->Fill(charges[i]);
    }
  };

  // rdf process
  ROOT::RDataFrame rdf("koalasim",infile);
  rdf.Foreach(fillhist,{"KoaRecDigi.fDetID","KoaRecDigi.fCharge"});

  // write histograms
  auto fout=TFile::Open(infile,"update");
  TDirectory* hdir;
  if(!(hdir=fout->GetDirectory("histograms")))
    hdir = fout->mkdir("histograms");

  for(auto& hist: h2map_EnergyVsPosition){
    auto sumed = hist.second.Merge();
    sumed->Print();
    hdir->WriteTObject(sumed.get(),"","WriteDelete");
  }
  for(auto& hist: h1map_Energy){
    auto sumed = hist.second.Merge();
    sumed->Print();
    hdir->WriteTObject(sumed.get(),"","WriteDelete");
  }

  delete fout;

  // timer stop
  timer.Stop();
  timer.Print();
  
}

// TTreeProcessorMT + Threaded Histogram
void checkDigi_processtree_threaded(const char* infile)
{
  // switches
  ROOT::EnableImplicitMT(6);
  // ROOT::GeImplicitMTPoolSize();
  TH1::AddDirectory(false);

  // timer start
  TStopwatch timer;
  // timer.Start();

  //
  using integers = ROOT::VecOps::RVec<Int_t>;
  using doubles  = ROOT::VecOps::RVec<Double_t>;
  using histo1d = std::map<Int_t, ROOT::TThreadedObject<TH1D>>;
  using histo2d = std::map<Int_t, ROOT::TThreadedObject<TH2D>>;

  // book histograms
  Int_t nbin=7000;
  Float_t xlow=0,xhigh=70;

  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  std::vector<Int_t> ChIDs = encoder->GetChIDs();
  Int_t RecIdRange[2]; encoder->GetRecDetIDRange(RecIdRange[0], RecIdRange[1]);

  histo2d h2map_EnergyVsPosition;
  for(auto id: ROOT::TSeqI(RecIdRange[0],RecIdRange[1]+1)){
    Int_t ChNr = encoder->GetChNr(id);
    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h2_EnergyVsPosition_%s",encoder->DetectorIDToVolName(id)),Form("h2_EnergyVsPosition_%s",encoder->DetectorIDToVolName(id)), ChNr, 0.5, 0.5+ChNr, nbin, xlow,xhigh);
    h2map_EnergyVsPosition.emplace(std::piecewise_construct, tindex, thist);
  }

  histo1d h1map_Energy;
  for(auto& id: ChIDs){
    TString volName; Int_t ch_id = encoder->DecodeChannelID(id, volName);

    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h1_energy_%s_%d",volName.Data(), ch_id+1), Form("h1_energy_%s_%d",volName.Data(), ch_id+1), nbin, xlow, xhigh);
    auto it = h1map_Energy.emplace(std::piecewise_construct, tindex, thist);
    it.first->second->GetName();//lazy init, make sure histogram is constructed
  }

  // define lambda
  auto fillhist = [&] (TTreeReader &myreader){
    TTreeReaderArray<KoaRecDigi> digis(myreader, "KoaRecDigi");

    Int_t det_id, ch_id, id;
    Double_t charge;
    while(myreader.Next()){
      for(auto&& digi: digis){
        id=digi.GetDetID();
        charge = 1000*digi.GetCharge();
        ch_id = encoder->DecodeChannelID(id, det_id);
        h2map_EnergyVsPosition[det_id]->Fill(ch_id+1, charge);
        h1map_Energy[id]->Fill(charge);
      }
    }
  };

  // rdf process
  ROOT::TTreeProcessorMT tp(infile, "koalasim");
  tp.Process(fillhist);

  // write histograms
  auto fout=TFile::Open(infile,"update");
  TDirectory* hdir;
  if(!(hdir=fout->GetDirectory("histograms")))
    hdir = fout->mkdir("histograms");

  for(auto& hist: h2map_EnergyVsPosition){
    auto sumed = hist.second.Merge();
    sumed->Print();
    hdir->WriteTObject(sumed.get(),"","WriteDelete");
  }
  for(auto& hist: h1map_Energy){
    auto sumed = hist.second.Merge();
    sumed->Print();
    hdir->WriteTObject(sumed.get(),"","WriteDelete");
  }

  delete fout;

  // timer stop
  timer.Stop();
  timer.Print();
  
}
