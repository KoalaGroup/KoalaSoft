using hist1D = std::map<Int_t, ROOT::TThreadedObject<TH1D>>;
using doubles = ROOT::VecOps::RVec<Double_t>;
using floats = ROOT::VecOps::RVec<Float_t>;
using integers = ROOT::VecOps::RVec<Int_t>;

bool checkTreeValue(ROOT::Internal::TTreeReaderValueBase& value);
hist1D book_hist1D();
bool fit_pedestal(TH1* hist, Double_t& mean, Double_t& sigma);
void write_hist1D(const char* file, hist1D& h1s, const char* directory="");

void fit_bk_pedestal(const char* infile, const char* outfile)
{
  ROOT::EnableImplicitMT(6);

  // timer
  TStopwatch timer;

  // book histograms
  hist1D h1s = book_hist1D();

  // lambda definition
  auto fillhist = [&] (TTreeReader &myreader){
    TTreeReaderArray<Int_t> si1Amp(myreader,"KoalaEvent.fSi1Amplitude[48]");
    TTreeReaderArray<Int_t> si2Amp(myreader,"KoalaEvent.fSi2Amplitude[64]");
    TTreeReaderArray<Int_t> ge1Amp(myreader,"KoalaEvent.fGe1Amplitude[32]");
    TTreeReaderArray<Int_t> ge2Amp(myreader,"KoalaEvent.fGe2Amplitude[32]");
    TTreeReaderArray<Int_t> fwdAmp(myreader,"KoalaEvent.fFwdAmplitude[8]");
    TTreeReaderArray<Float_t> fwdTime(myreader,"KoalaEvent.fFwdTime[8]");

    while (myreader.Next()) {
      if ( fwdAmp[0] > 1000 && fwdAmp[1] > 1000
           && (fwdTime[0] - fwdTime[1]) > -10
           && (fwdTime[0] - fwdTime[1]) < 10) {
        for(const auto& amp : si1Amp) {
          h1s
        }
      }
    }
  };

  // mt tree processor
  ROOT::TTreeProcessorMT tp(infile, "KoalaEvent");
  tp.Process(fillhist);

  // finish
  // write_hist1D(outfile, h1s);

  // 
  timer.Stop();
  timer.Print();
}

bool checkTreeValue(ROOT::Internal::TTreeReaderValueBase& value)
{
  if (value.GetSetupStatus() < 0) {
    std::cerr << "Error" << value.GetSetupStatus()
              << "setting up reader for " << value.GetBranchName() << std::endl;
    return false;
  }
  return true;
}

hist1D book_hist1D()
{
  TH1::AddDirectory(0);

  Int_t nbin = 1000;
  Double_t xlow = 0, xhigh = 1000;

  //
  hist1D hists;

  return hists;
}

bool fit_pedestal(TH1* hist, Double_t& mean, Double_t& sigma)
{
  
  return true;
}

void write_hist1D(const char* file, hist1D& h1s, const char* directory="")
{
  auto fout = TFile::Open(file, "update");
  TDirectory* hdir = gDirectory;

  //
  if ( TString(directory) != "" ) {
    if ( !(hdir = fout->GetDirectory(directory)) ) {
      hdir = fout->mkdir(directory);
    }
  }
  
  //
  for ( auto& hist : h1s ) {
    auto merged = hist.second.Merge();
    merged->Print();
    hdir->WriteTObject( merged.get(), "", "WriteDelete");
  }

  //
  delete fout;
}
