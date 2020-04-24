#include "KoaHistUtility.h"
#include "KoaCutList.h"

using namespace KoaUtility;

// Checking the energy spectrum from simulation or beam data.
//
// Outputs:
// 1. Three type of histograms of recoil energy:
//    i) all events
//   ii) events with coincidence with forward
//  iii) events with ToF time window cut
// 2. The coincidence events are selected based on a entry list if exists
//    Otherwise, it will be generated on the fly.
void checkDigi(const char* filename,  const char* treename, bool isSimulation=false, bool useList = true)
{
  // timer
  TStopwatch timer;

  // histograms definition
  Int_t nbin=7000;
  Float_t xlow=0,xhigh=70;

  auto h2map_EnergyVsStripId = bookH2dByRecDetectorId("EnergyVsStripId","Energy VS Strip_id;Strip id;Energy(MeV)", nbin, xlow, xhigh);

  auto h1map_Energy = bookH1dByChannelId("energy", "Energy (no cut);MeV", nbin, xlow, xhigh);
  auto h1map_Energy_cut = bookH1dByRecTdcChannelId("energy_CoinCut", "Energy (coincidence cut);MeV", nbin, xlow, xhigh);
  auto h1map_Energy_tof = bookH1dByRecTdcChannelId("energy_TofCut", "Energy (ToF cut);MeV", nbin, xlow, xhigh);

  // input
  TFile* f = new TFile(filename,"update");
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress("KoaRecDigi",&RecDigis);
  TClonesArray* FwdDigis = new TClonesArray("KoaFwdDigi");
  tree->SetBranchAddress("KoaFwdDigi",&FwdDigis);

  // output/input entry list 
  TDirectory *edir = getDirectory(f, "elists");
  std::string listName = getCutListName("fwdhit");

  TEntryList *cutlist;
  TEntryList *elist;
  if (useList) {
    edir->GetObject(listName.data(), cutlist);
    if(!cutlist){
      std::cout << "Error: no list found in file: " << filename << std::endl;
      return;
    }

    tree->SetEntryList(cutlist);
  }
  else {
    elist = new TEntryList(listName.data(),"fwdhit");
    elist->SetTree(tree);
    elist->SetDirectory(edir);
  }

  // Parameters used in event loop
  Int_t det_id, ch_id, id;
  Double_t charge;
  Double_t timestamp;

  std::map<Int_t, Double_t> fwd_time;
  std::map<Int_t, Double_t> fwd_amp;
  Int_t fwd_low, fwd_high;

  auto encoder = KoaMapEncoder::Instance();
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);

  // event loop
  Long_t entries;
  if(useList){
    entries = cutlist->GetN();
  }
  else{
    entries = tree->GetEntries();
  }

  for(auto entry=0;entry<entries;entry++){
    if(useList) {
      Int_t entrynum = tree->GetEntryNumber(entry);
      tree->GetEntry(entrynum);
    }
    else{
      tree->GetEntry(entry);
    }

    // fwd digis
    Int_t fwddigis = FwdDigis->GetEntriesFast();
    for (int i=0;i<fwddigis;i++){
      KoaFwdDigi* digi = (KoaFwdDigi*)FwdDigis->At(i);
      id = digi->GetDetID();
      fwd_time[id] = digi->GetTimeStamp();
      fwd_amp[id]  = digi->GetCharge();
    }

    // recoil digis
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      // rec digis
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      id = digi->GetDetID();
      ch_id = encoder->DecodeChannelID(id, det_id);

      // convert unit to MeV
      if (isSimulation) {
        charge = 1000*digi->GetCharge(); 
      }
      else {
        charge = digi->GetCharge()/1000.;
      }

      // timestamp
      timestamp = digi->GetTimeStamp();

      //
      h2map_EnergyVsStripId[det_id].Fill(ch_id+1, charge);
      h1map_Energy[id].Fill(charge);

      //
      auto fill_at_coincidence = [&] () {
                                   h1map_Energy_cut[id].Fill(charge);
                                   if((timestamp - fwd_time[index0]) > 500 &&
                                       (timestamp - fwd_time[index0]) < 520) {
                                     h1map_Energy_tof[id].Fill(charge);
                                   }
                                 };
      auto search = h1map_Energy_cut.find(id);
      if( search != h1map_Energy_cut.end() && timestamp > 0 ) {
        if (useList) {
          fill_at_coincidence();
        }
        else if ( fwd_amp[index0] > 1000 && fwd_amp[index1] > 1000
                  && ((fwd_time[index0] > 923 && fwd_time[index0] < 927 && fwd_time[index1] < 927)
                      || (fwd_time[index1] > 923 && fwd_time[index1] < 927 && fwd_time[index0] < 927))
                  ) {
          fill_at_coincidence();

          //
          elist->Enter(entry);
        }
      }
    }

    fwd_time.clear();
    fwd_amp.clear();
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  // output file
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","");
  outfilename.Append("_result.root");
  TFile *fout = new TFile(outfilename.Data(),"update");

  TDirectory* hdir = getDirectory(fout, "energy_spectrum");
  writeHistos(hdir, h2map_EnergyVsStripId);
  writeHistos(hdir, h1map_Energy);
  writeHistos(hdir, h1map_Energy_cut);
  writeHistos(hdir, h1map_Energy_tof);
  // for (auto & hist : h2map_EnergyVsStripId ) {
  //   hdir->WriteTObject(&hist.second,"","WriteDelete");
  // }
  // for (auto & hist : h1map_Energy ) {
  //   hdir->WriteTObject(&hist.second,"","WriteDelete");
  // }
  // for (auto & hist : h1map_Energy_cut ) {
  //   hdir->WriteTObject(&hist.second,"","WriteDelete");
  // }
  // for (auto & hist : h1map_Energy_tof ) {
  //   hdir->WriteTObject(&hist.second,"","WriteDelete");
  // }

  //
  if(!useList){
    edir->WriteTObject(elist,"","WriteDelete");
  }

  delete f;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}

// DataFrame + Threaded Histogram + IMT
void checkDigi_rdf_threaded(const char* infile, bool isSimulation, const char* treename)
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
  Int_t nbin=14000;
  Float_t xlow=0,xhigh=70;

  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  std::vector<Int_t> ChIDs = encoder->GetRecChIDs();
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
      if ( isSimulation ) {
        charge = charges[i]*1000;
      }
      else {
        charge = charges[i]/1000.;
      }

      h2map_EnergyVsPosition[det_id]->Fill(ch_id+1, charge);
      h1map_Energy[ids[i]]->Fill(charge);
    }
  };

  // rdf process
  ROOT::RDataFrame rdf(treename, infile);
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
void checkDigi_processtree_threaded(const char* infile, bool isSimulation, const char* treename)
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
  Int_t nbin=14000;
  Float_t xlow=0,xhigh=70;

  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  std::vector<Int_t> ChIDs = encoder->GetRecChIDs();
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

  histo1d h1map_Energy_cut;
  std::vector<Int_t> TdcChIds = encoder->GetRecTdcChIDs();
  for(auto& id: TdcChIds){
    TString volName; Int_t ch_id = encoder->DecodeChannelID(id, volName);

    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h1_energy_cut_%s_%d",volName.Data(), ch_id+1), Form("h1_energy_cut_%s_%d",volName.Data(), ch_id+1), nbin, xlow, xhigh);
    auto it = h1map_Energy_cut.emplace(std::piecewise_construct, tindex, thist);
    it.first->second->GetName();//lazy init, make sure histogram is constructed
  }

  // define lambda
  auto fillhist = [&] (TTreeReader &myreader){
    TTreeReaderArray<KoaRecDigi> digis(myreader, "KoaRecDigi");
    TTreeReaderArray<KoaFwdDigi> fwddigis(myreader, "KoaFwdDigi");

    Int_t det_id, ch_id, id;
    Double_t charge;
    Double_t fwd_time[2], fwd_amp[2];
    while(myreader.Next()){
      // fwd digis
      for(int index=0;index<2;index++){
        fwd_time[index] = fwddigis[index].GetTimeStamp();
        fwd_amp[index]  = fwddigis[index].GetCharge();
      }

      // rec digis
      for(auto&& digi: digis){
        id=digi.GetDetID();
        ch_id = encoder->DecodeChannelID(id, det_id);
        if ( isSimulation ) {
          charge = 1000*digi.GetCharge();
        }
        else {
          charge = digi.GetCharge() / 1000.;
        }

        h2map_EnergyVsPosition[det_id]->Fill(ch_id+1, charge);
        h1map_Energy[id]->Fill(charge);

        //
        if ( digi.GetTimeStamp() > 0 ) {
          if ( fwd_amp[0] > 1000 && fwd_amp[1] > 1000
               && (fwd_time[0]-fwd_time[1]) < 10
               && (fwd_time[0]-fwd_time[1]) > -10) {

            h1map_Energy_cut[id]->Fill(charge);
          }
        }
      }
    }
  };

  // rdf process
  ROOT::TTreeProcessorMT tp(infile, treename);
  tp.Process(fillhist);

  // write histograms
  auto fout=TFile::Open(infile,"update");
  TDirectory* hdir = getDirectory(fout, "histograms");

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
  for(auto& hist: h1map_Energy_cut){
    auto sumed = hist.second.Merge();
    sumed->Print();
    hdir->WriteTObject(sumed.get(),"","WriteDelete");
  }

  delete fout;

  // timer stop
  timer.Stop();
  timer.Print();
  
}
