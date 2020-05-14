
#include "KoaCutList.h"
#include "KoaHistUtility.h"
#include "KoaColors.h"

using namespace KoaUtility;

/*
 | Summary:
 | -------
 | Fill amplitude related histograms of recoil detector.
 | EncodeChannelID mapped histograms are saved into an out file under a directory.
 | Both raw ADC counts and reconstructed energy can be filled.
 | An optional entry list can be imposed to fill only a subset of whole events.
 | Also, a specific cut on the timestamp validivity can be imposed on each channel.
 |
 | Arguments:
 | ---------
 | *) inFileName : input root file name
 | *) outFileName: output root file to store the histograms
 | *) treeName   : input tree name
 | *) brName_rec : name the recoil digi branch
 | *) IsAdc      : whether digi is raw ADC counts or reconstructed energy
 | *) amp_bin, amp_low, amp_high : binning parameters
 | *) colorLine  : line color of the histograms
 | *) UserTimeValidCut : whether filtering out invalid timestamp data
 | *) elistFileName    : name of the file containing the event list, nullptr means all events
 | *) edirName         : name of the directory where the event list locatedin elistFileName
 | *) elistName        : name of the event list used
 |
 */
void checkRecAmplitude_Imp(const char* inFileName, const char* outFileName,
                           const char* treeName = "koalasim",
                           const char* brName_rec = "KoaRecDigi",
                           bool IsAdc = false,
                           int amp_nbin = 7000, double amp_low = 0, double amp_high = 70, int colorLine = kBlack,
                           bool UseTimeValidCut = true,
                           const char* elistFileName = nullptr, const char* edirName = "fwd", const char* elistName = "elist_fwdhit"
                           )
{
  // timer start
  TStopwatch timer;

  // input tree
  TFile* fin = new TFile(inFileName);
  TTree* tree = (TTree*)fin->Get(treeName);
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress(brName_rec, &RecDigis);

  // input filter based on TEntryList
  TFile* felist = nullptr;
  TDirectory* eDir = nullptr;
  TEventList* eList = nullptr;
  if ( elistFileName ) {
    felist = new TFile(elistFileName);
    eDir = getDirectory(felist, edirName);
    eList = getObject<TEventList>(eDir, elistName);
  }

  // string definition
  TString hName = "energy";
  TString hTitle = "Energy;Energy(MeV)";
  TString hDirName = "rec_energy";
  TString eListName = elistName;
  eListName.ReplaceAll("elist_","");

  if (IsAdc) {
    hName = "adc";
    hTitle = "Amplitude;ADC counts";
    hDirName = "rec_adc";
  }

  if (elistFileName) {
    hName.Append(Form("_%s",eListName.Data()));
    hTitle.Prepend(Form("(%s cut) ", eListName.Data()));
    hDirName.Append(Form("_%s",eListName.Data()));
  }

  if(UseTimeValidCut) {
    hName.Append("_TimeValid");
    hTitle.Prepend("(T_{rec}>0)");
    hDirName.Append("_TimeValid");
  }

  // histogram definition
  auto h1map = bookH1dByChannelId(hName.Data(), hTitle.Data(),
                                  amp_nbin, amp_low, amp_high,
                                  true, colorLine);

  // get entry number
  Long_t entries = tree->GetEntriesFast();
  if ( elistFileName ) {
    entries = eList->GetN();
  }

  // event loop
  for(auto entry=0;entry<entries;entry++){

    if ( elistFileName ) {
      auto tree_index = eList->GetEntry(entry);
      tree->GetEntry(tree_index);
    }
    else {
      tree->GetEntry(entry);
    }

    // check cut condition
    // rec digis
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      auto id = digi->GetDetID();

      // rec enerty
      auto rec_charge = digi->GetCharge(); // for ADC
      if ( !IsAdc ) {
        rec_charge = rec_charge/1000.;
      }

      // fill
      if (UseTimeValidCut && digi->GetTimeStamp() < 0)
        continue;

      h1map[id].Fill(rec_charge);
    }
  }
  if (elistFileName) {
    std::cout << "Use event list : " << eListName << std::endl;
  }
  std::cout << "Events processed : "<< entries << std::endl;

  // output
  TFile *fout = new TFile(outFileName, "update");

  TDirectory* hdir = nullptr;
  hdir = getDirectory(fout, hDirName.Data());
  writeHistos<TH1D>(hdir, h1map);

  // clear up
  delete fin;
  delete fout;

  if (elistFileName) {
    delete eList;
    delete felist;
  }

  // timer stat
  timer.Stop();
  timer.Print();
}


/*
 | Summary:
 | -------
 | Fill timestamp related histograms of recoil detector.
 | EncodeChannelID mapped histograms are saved into an out file under a directory.
 | Only strips connected to TDC are filled.
 | Only valid timestamp is filled, i.e. Timestamp > 0
 | An optional entry list can be imposed to fill only a subset of whole events.
 |
 | Arguments:
 | ---------
 | *) inFileName : input root file name
 | *) outFileName: output root file to store the histograms
 | *) treeName   : input tree name
 | *) brName_rec : name the recoil digi branch
 | *) time_bin, time_low, time_high : binning parameters
 | *) colorLine  : line color of the histograms
 | *) elistFileName    : name of the file containing the event list, nullptr means all events
 | *) edirName         : name of the directory where the event list locatedin elistFileName
 | *) elistName        : name of the event list used
 |
 */
void checkRecTime_Imp(const char* inFileName, const char* outFileName,
                           const char* treeName = "koalasim",
                           const char* brName_rec = "KoaRecDigi",
                           int time_nbin = 8000, double time_low = 1000, double time_high = 1800, int colorLine = kBlack,
                           const char* elistFileName = nullptr, const char* edirName = "fwd", const char* elistName = "elist_fwdhit"
                           )
{
  // timer start
  TStopwatch timer;

  // input tree
  TFile* fin = new TFile(inFileName);
  TTree* tree = (TTree*)fin->Get(treeName);
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress(brName_rec, &RecDigis);

  // input filter based on TEntryList
  TFile* felist = nullptr;
  TDirectory* eDir = nullptr;
  TEventList* eList = nullptr;
  if ( elistFileName ) {
    felist = new TFile(elistFileName);
    eDir = getDirectory(felist, edirName);
    eList = getObject<TEventList>(eDir, elistName);
  }

  // string definition
  TString hName = "time";
  TString hTitle = "Timestamp;Timestamp(ns)";
  TString hDirName = "rec_time";
  TString eListName = elistName;
  eListName.ReplaceAll("elist_","");

  if (elistFileName) {
    hName.Append(Form("_%s",eListName.Data()));
    hTitle.Prepend(Form("(%s cut) ", eListName.Data()));
    hDirName.Append(Form("_%s",eListName.Data()));
  }

  // histogram definition
  auto h1map = bookH1dByRecTdcChannelId(hName.Data(), hTitle.Data(),
                                        time_nbin, time_low, time_high,
                                        colorLine);

  // get entry number
  Long_t entries = tree->GetEntriesFast();
  if ( elistFileName ) {
    entries = eList->GetN();
  }

  // event loop
  for(auto entry=0;entry<entries;entry++){

    if ( elistFileName ) {
      auto tree_index = eList->GetEntry(entry);
      tree->GetEntry(tree_index);
    }
    else {
      tree->GetEntry(entry);
    }

    // check cut condition
    // rec digis
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      auto id = digi->GetDetID();

      // rec enerty
      auto rec_timestamp = digi->GetTimeStamp();

      // fill
      if ( rec_timestamp < 0 )
        continue;

      h1map[id].Fill(rec_timestamp);
    }
  }
  if (elistFileName) {
    std::cout << "Use event list : " << eListName << std::endl;
  }
  std::cout << "Events processed : "<< entries << std::endl;

  // output
  TFile *fout = new TFile(outFileName, "update");

  TDirectory* hdir = nullptr;
  hdir = getDirectory(fout, hDirName.Data());
  writeHistos<TH1D>(hdir, h1map);

  // clear up
  delete fin;
  delete fout;

  if (elistFileName) {
    delete eList;
    delete felist;
  }

  // timer stat
  timer.Stop();
  timer.Print();
}


/*
 | Summary:
 | -------
 | Fill 2-d histograms with recoil amplitude and recoil time-of-flight.
 | EncodeChannelID mapped histograms are saved into an out file under a directory.
 | Only strips connected to TDC and both recoil and fwd have valid timestamps are filled.
 | Optional event list can also be applied.
 |
 | Arguments:
 | ---------
 | *) inFileName : input root file name
 | *) fwdhitFileName: input root file containing fwdhit timestamp
 | *) outFileName: output root file to store the histograms
 | *) treeName   : input tree name containing recoil info
 | *) brName_rec : name the recoil digi branch
 | *) fwdhitTreeName : input tree name containing fwdhit info
 | *) IsAdc : whether the recoil digi is raw ADC or energy
 | *) brName_fwdhit : name of the fwdhit branch
 | *) amp_nbin, amp_low, amp_high : amplitude binning parameters
 | *) time_bin, time_low, time_high : tof binning parameters
 | *) elistFileName    : name of the file containing the event list, nullptr means all events
 | *) edirName         : name of the directory where the event list locatedin elistFileName
 | *) elistName        : name of the event list used
 |
 */
void checkAmpVsTof_Imp(const char* inFileName, const char* fwdhitFileName, const char* outFileName,
                        const char* treeName = "koalasim", const char* brName_rec = "KoaRecDigi",
                        const char* fwdhitTreeName = "fwdhit_time", const char* brName_fwdhit = "fwdhit_time",
                        bool IsAdc = false,
                        int amp_nbin = 1000, double amp_low = 0, double amp_high = 10,
                        int time_nbin = 8000, double time_low = 1000, double time_high = 1800,
                        const char* elistFileName = nullptr, const char* edirName = "fwd", const char* elistName = "elist_fwdhit"
                        )
{
  // timer start
  TStopwatch timer;

  // input tree
  TFile* fin = new TFile(inFileName);
  TTree* tree = (TTree*)fin->Get(treeName);
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress(brName_rec, &RecDigis);

  // fwdhit tree
  TFile* ffwdhit = new TFile(fwdhitFileName);
  TTree* treeFwdhit = (TTree*)ffwdhit->Get(fwdhitTreeName);
  float fwdhit_timestamp;
  treeFwdhit->SetBranchAddress(brName_fwdhit, &fwdhit_timestamp);
  tree->AddFriend(treeFwdhit);

  // input filter based on TEntryList
  TFile* felist = nullptr;
  TDirectory* eDir = nullptr;
  TEventList* eList = nullptr;
  if ( elistFileName ) {
    felist = new TFile(elistFileName);
    eDir = getDirectory(felist, edirName);
    eList = getObject<TEventList>(eDir, elistName);
  }

  // string definition
  TString hName = "EnergyVsTof";
  TString hTitle = "Energy VS TOF;Energy(MeV);TOF(ns)";
  TString hDirName = "EnergyVsTOF";
  TString eListName = elistName;
  eListName.ReplaceAll("elist_","");

  if (IsAdc) {
    hName = "AdcVsTof";
    hTitle = "Amplitude VS TOF;ADC counts;TOF(ns)";
    hDirName = "AdcVsTof";
  }

  if (elistFileName) {
    hName.Append(Form("_%s",eListName.Data()));
    hTitle.Prepend(Form("(%s cut) ", eListName.Data()));
    hDirName.Append(Form("_%s",eListName.Data()));
  }

  // histogram definition
  auto h2map = bookH2dByRecTdcChannelId(hName.Data(), hTitle.Data(),
                                        amp_nbin, amp_low, amp_high,
                                        time_nbin, time_low, time_high
                                        );

  // get entry number
  Long_t entries = tree->GetEntriesFast();
  if ( elistFileName ) {
    entries = eList->GetN();
  }

  // event loop
  for(auto entry=0;entry<entries;entry++){

    if ( elistFileName ) {
      auto tree_index = eList->GetEntry(entry);
      tree->GetEntry(tree_index);
    }
    else {
      tree->GetEntry(entry);
    }

    // check cut condition
    // rec digis
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      auto id = digi->GetDetID();

      // rec enerty
      auto rec_charge = digi->GetCharge(); // for ADC
      if ( !IsAdc ) {
        rec_charge = rec_charge/1000.;
      }

      // rec timestamp
      auto rec_timestamp = digi->GetTimeStamp();

      // fill
      if ( rec_timestamp < 0 || fwdhit_timestamp < 0 )
        continue;

      h2map[id].Fill(rec_charge, rec_timestamp - fwdhit_timestamp);
    }
  }
  if (elistFileName) {
    std::cout << "Use event list : " << eListName << std::endl;
  }
  std::cout << "Events processed : "<< entries << std::endl;

  // output
  TFile *fout = new TFile(outFileName, "update");

  TDirectory* hdir = nullptr;
  hdir = getDirectory(fout, hDirName.Data());
  writeHistos<TH2D>(hdir, h2map);

  // clear up
  delete fin;
  delete ffwdhit;
  delete fout;

  if (elistFileName) {
    delete eList;
    delete felist;
  }

  // timer stat
  timer.Stop();
  timer.Print();
}


/*
 | Summary:
 | -------
 | Fill 2-d histograms with recoil amplitude and recoil timestamp.
 | EncodeChannelID mapped histograms are saved into an out file under a directory.
 | Only strips connected to TDC are filled.
 | Optional event list can also be applied.
 |
 | Arguments:
 | ---------
 | *) inFileName : input root file name
 | *) outFileName: output root file to store the histograms
 | *) treeName   : input tree name containing recoil info
 | *) brName_rec : name the recoil digi branch
 | *) IsAdc : whether the recoil digi is raw ADC or energy
 | *) brName_fwdhit : name of the fwdhit branch
 | *) amp_nbin, amp_low, amp_high : amplitude binning parameters
 | *) time_bin, time_low, time_high : tof binning parameters
 | *) elistFileName    : name of the file containing the event list, nullptr means all events
 | *) edirName         : name of the directory where the event list locatedin elistFileName
 | *) elistName        : name of the event list used
 |
 */
void checkAmpVsTime_Imp(const char* inFileName, const char* outFileName,
                        const char* treeName = "koalasim", const char* brName_rec = "KoaRecDigi",
                        bool IsAdc = false,
                        int amp_nbin = 1000, double amp_low = 0, double amp_high = 10,
                        int time_nbin = 8000, double time_low = 1000, double time_high = 1800,
                        const char* elistFileName = nullptr, const char* edirName = "fwd", const char* elistName = "elist_fwdhit"
                        )
{
  // timer start
  TStopwatch timer;

  // input tree
  TFile* fin = new TFile(inFileName);
  TTree* tree = (TTree*)fin->Get(treeName);
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress(brName_rec, &RecDigis);

  // input filter based on TEntryList
  TFile* felist = nullptr;
  TDirectory* eDir = nullptr;
  TEventList* eList = nullptr;
  if ( elistFileName ) {
    felist = new TFile(elistFileName);
    eDir = getDirectory(felist, edirName);
    eList = getObject<TEventList>(eDir, elistName);
  }

  // string definition
  TString hName = "EnergyVsTime";
  TString hTitle = "Energy VS Timestamp;Energy(MeV);Timestamp(ns)";
  TString hDirName = "EnergyVsTime";
  TString eListName = elistName;
  eListName.ReplaceAll("elist_","");

  if (IsAdc) {
    hName = "AdcVsTime";
    hTitle = "Amplitude VS Timestamp;ADC counts;Timestamp(ns)";
    hDirName = "AdcVsTime";
  }

  if (elistFileName) {
    hName.Append(Form("_%s",eListName.Data()));
    hTitle.Prepend(Form("(%s cut) ", eListName.Data()));
    hDirName.Append(Form("_%s",eListName.Data()));
  }

  // histogram definition
  auto h2map = bookH2dByRecTdcChannelId(hName.Data(), hTitle.Data(),
                                        amp_nbin, amp_low, amp_high,
                                        time_nbin, time_low, time_high
                                        );

  // get entry number
  Long_t entries = tree->GetEntriesFast();
  if ( elistFileName ) {
    entries = eList->GetN();
  }

  // event loop
  for(auto entry=0;entry<entries;entry++){

    if ( elistFileName ) {
      auto tree_index = eList->GetEntry(entry);
      tree->GetEntry(tree_index);
    }
    else {
      tree->GetEntry(entry);
    }

    // check cut condition
    // rec digis
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      auto id = digi->GetDetID();

      // rec enerty
      auto rec_charge = digi->GetCharge(); // for ADC
      if ( !IsAdc ) {
        rec_charge = rec_charge/1000.;
      }

      // rec timestamp
      auto rec_timestamp = digi->GetTimeStamp();

      // fill
      if ( rec_timestamp < 0 )
        continue;

      h2map[id].Fill(rec_charge, rec_timestamp);
    }
  }
  if (elistFileName) {
    std::cout << "Use event list : " << eListName << std::endl;
  }
  std::cout << "Events processed : "<< entries << std::endl;

  // output
  TFile *fout = new TFile(outFileName, "update");

  TDirectory* hdir = nullptr;
  hdir = getDirectory(fout, hDirName.Data());
  writeHistos<TH2D>(hdir, h2map);

  // clear up
  delete fin;
  delete fout;

  if (elistFileName) {
    delete eList;
    delete felist;
  }

  // timer stat
  timer.Stop();
  timer.Print();
}
