#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
// #include "calc_energy_imp.C"

using namespace KoaUtility;

void calc_energy(const char* infile,
                 Double_t mom = 2.6, Double_t distance = 90.432,
                 Double_t zoffset = 0, const char* geoFile="../calib_para/geo_standard.root", bool useFwd = true)

{
  TStopwatch timer;

  //
  auto calculator = new KoaElasticCalculator(mom);
  // calculator->SetRecDistance(distance);

  KoaMapEncoder* encoder = KoaMapEncoder::Instance();

  //
  std::map<Int_t, double> CalculatedEnergies;
  auto Positions = getStripGlobalPosition(geoFile);
  auto Alphas = getStripAlphas(geoFile);

  for(auto item: Positions ){
    auto id = item.first;
    auto pos = item.second;
    if(pos>0){
      auto energy = calculator->GetEnergyByAlpha(Alphas[id]);

      CalculatedEnergies.emplace(id, energy);
    }
  }
  // KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  // auto RecChIds = encoder->GetRecChIDs();
  // Int_t ch_id, det_id;
  // Double_t center, low, high;
  // Double_t global_pos[3] = {0};
  // Double_t local_pos[3] = {0};
  // Double_t energy;

  // for( auto& id : RecChIds ) {
  //   ch_id = encoder->DecodeChannelID(id, det_id);

  //   center = geoHandler->RecDetChToPosition(id, low, high);
  //   local_pos[2] = center;
  //   geoHandler->LocalToGlobal(local_pos, global_pos,det_id);

  //   Positions.emplace(id, 10*global_pos[2]+zoffset);

  //   //
  //   if(Positions[id]>0
  //      && Alphas[id]>0
  //      ) {
  //     // energy = GetRecTByRecHitPosition(mom, Positions[id], distance);
  //     // energy = calculator->GetEnergyByRecZ(Positions[id]);
  //     energy = calculator->GetEnergyByAlpha(Alphas[id]);

  //     CalculatedEnergies.emplace(id, energy);
  //   }
  // }

  ////////////////////////////////////////
  TString infile_name = gSystem->ExpandPathName(infile);
  auto filein = TFile::Open(infile_name,"Update");

  HistoPtr1D h1s_ptr;

  // readHist
  auto readHist = [&] (Int_t sepid)
    {
      //
      auto hdir_energy = getDirectory(filein, "rec_energy");
      auto hist_energy = getHistosByChannelId<TH1D>(hdir_energy, "energy");

      auto hdir_energy_cut = getDirectory(filein, "rec_energy_fwdhit_TimeValid");
      auto hist_energy_cut = getHistosByChannelId<TH1D>(hdir_energy_cut, "energy_fwdhit_TimeValid");

      //
      std::vector<Int_t> ChIDs = encoder->GetRecChIDs();

      for ( auto& ChID : ChIDs ) {
        if ( useFwd ) {
          if (ChID < sepid){
            h1s_ptr.emplace(ChID, hist_energy_cut[ChID]);
          }
          else{
            h1s_ptr.emplace(ChID, hist_energy[ChID]);
          }
        }
        else{
          h1s_ptr.emplace(ChID, hist_energy[ChID]);
        }
      }

      return true;
    };

  Int_t rangeid = encoder->EncodeChannelID(1,20);
  readHist(rangeid);

  ////////////////////////////////////////
  std::map<Int_t, double> FittedEnergies;
  std::map<Int_t, double> PeakEnergies;

  auto searchPeaks = [&] ()
    {
      // config the search paramters
      Int_t search_maxpeaks=2;
      Double_t search_rangelow, search_rangehigh;
      Double_t search_threshold;
      Int_t rebin_id = encoder->EncodeChannelID(2,0);

  // loop through all hists
      for ( auto& hist : h1s_ptr ) {
        auto id = hist.first;
        auto h1 = hist.second;
        TSpectrum s(search_maxpeaks);
        Int_t npeaks;
        if(id<rangeid){
          h1->GetXaxis()->SetRangeUser(0.1, 4);
          npeaks = s.Search(h1, 0.1, "", 0.5);
        }
        else{
          if(id>=rebin_id){
            h1->Rebin(4);
          }
          if((CalculatedEnergies[id]-4) < 1)
            h1->GetXaxis()->SetRangeUser(1, CalculatedEnergies[id]+4);
          else
            h1->GetXaxis()->SetRangeUser(CalculatedEnergies[id]-4, CalculatedEnergies[id]+4);
          // h1->GetXaxis()->SetRangeUser(3,70);
          npeaks = s.Search(h1, 0.2, "", 0.5);
        }

        if(npeaks>0) {
          Double_t *xpeaks = s.GetPositionX();
          PeakEnergies.emplace(id, xpeaks[0]);
          // first fit to get rough estimation
          auto sigma = 0.1;
          if(h1->GetRMS()>0.2){
            sigma = h1->GetRMS()/2.;
          }
          auto result = h1->Fit("gaus", "qs+", "", xpeaks[0]-sigma, xpeaks[0]+sigma);
          double mean = result->Parameter(1);
          FittedEnergies.emplace(id, mean);
        }
        else{
          PeakEnergies.emplace(id, 0);
          FittedEnergies.emplace(id, 0);
        }
      }
    };
  searchPeaks();

  //////////////////
  using Graphs = std::map<Int_t, TGraph>;
  Graphs graphs;
  Int_t ip_id = encoder->EncodeChannelID(0,21);

  TGraph* graph_calculated = new TGraph();
  graph_calculated->SetName("graph_calculated");
  graph_calculated->SetTitle("Position VS Energy");
  graph_calculated->SetMarkerColor(kBlue);
  graph_calculated->SetMarkerStyle(22);
  graph_calculated->SetMarkerSize(0.6);
  TGraph* graph_calibrated = new TGraph();
  graph_calibrated->SetName("graph_calibrated");
  graph_calibrated->SetTitle("Position VS Energy");
  graph_calibrated->SetMarkerColor(kRed);
  graph_calibrated->SetMarkerStyle(20);
  graph_calibrated->SetMarkerSize(0.6);

  TMultiGraph* mg=new TMultiGraph();
  mg->SetName("graph_position_vs_energy");
  mg->SetTitle("Position VS Energy");
  mg->Add(graph_calculated, "P");
  mg->Add(graph_calibrated, "P");

  TGraph* graph_diff = new TGraph();
  graph_diff->SetName("graph_diff");
  graph_diff->SetMarkerStyle(20);
  graph_diff->SetMarkerSize(0.6);

  TGraph* graph_diff_value = new TGraph();
  graph_diff_value->SetName("graph_diff_value");
  graph_diff_value->SetMarkerStyle(20);
  graph_diff_value->SetMarkerSize(0.6);

  TGraph* graph_diff_search = new TGraph();
  graph_diff_search->SetName("graph_diff_search");
  graph_diff_search->SetMarkerStyle(20);
  graph_diff_search->SetMarkerSize(0.6);

  TGraph* graph_diff_value_search = new TGraph();
  graph_diff_value_search->SetName("graph_diff_value_search");
  graph_diff_value_search->SetMarkerStyle(20);
  graph_diff_value_search->SetMarkerSize(0.6);

  Int_t index =0 ;
  for( auto& energy : CalculatedEnergies ) {
    auto& id = energy.first;
    auto& value = energy.second;
    if(Positions[id]>0 &&
       id > ip_id &&
       // id != encoder->EncodeChannelID(2,28) &&
       // id != encoder->EncodeChannelID(2,29) &&
       // id != encoder->EncodeChannelID(2,30) &&
       // id != encoder->EncodeChannelID(2,31) &&
       // id != encoder->EncodeChannelID(3,29) &&
       // id != encoder->EncodeChannelID(3,30) &&
       // id != encoder->EncodeChannelID(3,31) &&
       FittedEnergies[id] !=0 &&
       std::abs(FittedEnergies[id]-CalculatedEnergies[id]) < 1){
      graph_calibrated->SetPoint(index, Positions[id], FittedEnergies[id]);
      graph_calculated->SetPoint(index, Positions[id], value);
      graph_diff->SetPoint(index, Positions[id], (FittedEnergies[id]-value)/value);
      graph_diff_value->SetPoint(index, Positions[id], (FittedEnergies[id]-value));
      graph_diff_search->SetPoint(index, Positions[id], (PeakEnergies[id]-value)/value);
      graph_diff_value_search->SetPoint(index, Positions[id], (PeakEnergies[id]-value));
      index++;
    }
  }

  // output
  auto hDirOut = getDirectory(filein, "rec_energy_fitted");
  writeHistos<TH1D*>(hDirOut, h1s_ptr);
  hDirOut->WriteTObject( graph_calibrated, "", "WriteDelete");
  hDirOut->WriteTObject( graph_calculated, "", "WriteDelete");
  hDirOut->WriteTObject( mg, "", "WriteDelete");
  hDirOut->WriteTObject( graph_diff, "", "WriteDelete");
  hDirOut->WriteTObject( graph_diff_value, "", "WriteDelete");
  hDirOut->WriteTObject( graph_diff_search, "", "WriteDelete");
  hDirOut->WriteTObject( graph_diff_value_search, "", "WriteDelete");

  TString outfile_pdf(infile_name);
  outfile_pdf.ReplaceAll(".root",".pdf");
  printH1Ds(h1s_ptr, outfile_pdf.Data());

  TString outfile_txt(infile_name);
  outfile_txt.ReplaceAll(".root",".txt");
  // outfile_txt.ReplaceAll(".root",Form("_zoffset%0.1f_distance%0.1f.txt",zoffset,distance));
  std::ofstream ftxt(outfile_txt.Data());
  if ( ftxt.is_open() ) {
    std::cout << "Fit result of graph saved in file : " << outfile_txt.Data() << '\n';
  }
  else {
    std::cerr << "Error: can't open text file : " << outfile_txt.Data() << '\n';
    return false;
  }

  ftxt << "# calculated energy: name id position(mm) calculated_energy(MeV) peak_energy fit_energy" << std::endl;
  for ( auto& result : CalculatedEnergies ) {
    auto& id = result.first;
    auto energy = result.second;

    if(id <= ip_id) continue;

    Int_t ch; TString volName;
    ch = encoder->DecodeChannelID(id, volName);
    volName.ReplaceAll("Sensor","");

    volName.Append("_").Append(Form("%d",ch+1));
    // name id p0 p1
    ftxt << std::setw(10) << std::left << volName
         << std::setw(10) << std::left << id
         << std::setw(10) << std::left << Positions[id]
         << std::setw(10) << std::left << CalculatedEnergies[id]
         << std::setw(10) << std::left << PeakEnergies[id]
         << std::setw(10) << std::left << FittedEnergies[id] << std::endl;
  }
  ftxt.close();

  //
  delete filein;
  delete calculator;

  //
  timer.Stop();
  timer.Print();
}
