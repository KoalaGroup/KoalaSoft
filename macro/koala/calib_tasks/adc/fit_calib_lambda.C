//
using doubles = ROOT::VecOps::RVec<Double_t>;
using floats = ROOT::VecOps::RVec<Float_t>;
using integers = ROOT::VecOps::RVec<Int_t>;
doubles   pulsers;
std::map<Int_t, doubles> source_energies;
std::map<Int_t, double> sigmas_default;
std::map<Int_t, double> pedestals_default;

HistoPtr1D h1s_ptr;

using Graphs = std::map<Int_t, TGraphErrors>;
Graphs graphs;
Graphs graphs_inverse;

using FitResult = std::map<Int_t, TFitResultPtr>;
FitResult lines;
FitResult lines_inverse;

using RawFitResult = std::map<Int_t, doubles>;
RawFitResult peaks, peaks_error, widths, widths_error;

KoaMapEncoder* encoder = KoaMapEncoder::Instance();
constexpr Int_t ADC_MAXRANGE = 7680;

FitResult peaks_tdc;

// lambda definitions //

/** read in the configurations **/

// Convert the source energy into real energy deposition in each strip.
// Each sensor has a dead layer of Aluminium, where the alpha particle from source will lose some energy.
// Also the deal layer depth tranversed is different at different incidence angle.
// This effect is taken into consideration for Ge1 and Ge2, but not for Si1 and Si2
auto convertSourceEnergy = [&] ()
{
  auto length = pulsers.size();
  // each line is one energy point, which have 7 fields :
  // E_alpha, dE_Si1, dE_Si2, dE_Ge1, Step_Ge1, dE_Ge2, Step_Ge2
  if ( length%7 != 0) {
    std::cerr << "Error: incorrect format in energy setting file, please check it!!" << std::endl;
    return false;
  }

  length = length/7;
  std::cout << "Nr of settings : " << length << std::endl;
  std::cout << "E_alpha\t" << "dE_Si1\t" << "dE_Si2\t" << "dE_Ge1\t" << "Step_Ge1\t" << "dE_Ge2\t" << "Step_Ge2" << std::endl;

  for ( auto i=0; i<length; i++) {
    std::cout << pulsers[i*7] << "\t" 
              << pulsers[i*7+1] << "\t"
              << pulsers[i*7+2] << "\t"
              << pulsers[i*7+3] << "\t"
              << pulsers[i*7+4] << "\t"
              << pulsers[i*7+5] << "\t"
              << pulsers[i*7+6] << std::endl;

    for ( auto& hist : h1s_ptr ) {

      auto& id = hist.first;
      auto& energies = source_energies[id];
      Int_t detId, ch;
      ch = encoder->DecodeChannelID(id, detId);

      double energy;
      switch (detId) {
      case 0:
      case 1:
        energy = pulsers[7*i] - pulsers[detId+1+7*i];
        break;
      case 2:
        energy = pulsers[7*i] - pulsers[detId+1+7*i] - pulsers[detId+2+7*i]*(ch+1);
        break;
      case 3:
        energy = pulsers[7*i] - pulsers[detId+2+7*i] - pulsers[detId+3+7*i]*(ch+1);
        break;
      default:
        break;
      }

      energies.emplace_back(energy);
      if ( i == (length-1) ) {
        std::sort(energies.begin(), energies.end());
      }
    }
  }

  return true;
};

// read pulser/energy setting values
auto readPulserSetting = [&] ( const char* infile )
{
  std::ifstream fin;
  fin.open(infile);

  std::string line, word;
  std::getline(fin, line);
  while ( !fin.eof() ) {
    std::getline(fin, line);
    std::stringstream ss(line);

    while ( std::getline(ss, word, ',')) {
      pulsers.emplace_back(std::stod(word));
    }
  }

  //
  if ( isPulser ) {
    std::cout << "Pulser setting from : " << infile << std::endl;
    std::cout << "Nr of settings : " << pulsers.size() << std::endl;
    for (auto& pulser : pulsers ){
      std::cout<< pulser << "\t";
    }
    std::cout << std::endl;
    //
    std::sort(pulsers.begin(), pulsers.end());
  }
  else {
    std::cout << "Energy setting from : " << infile << std::endl;
    convertSourceEnergy();
  }

  fin.close();
};

// read default sigmas of each channel //
auto readDefaultSigma = [&] ( const char* infile )
{
  std::ifstream fin;
  fin.open(infile);
  if(!fin.is_open()){
    std::cerr << "Error : can't open file " << infile << std::endl;
    return false;
  }

  std::string line, word;
  std::string name;
  Int_t id;
  Double_t sigma;

  std::getline(fin, line);
  while ( !fin.eof() ) {
    std::getline(fin, line);
    std::stringstream ss(line);
    ss >> name >> id >> sigma;
    // since bin width is 1, it's not useful to have sigma less than 1
    if(sigma < 1){
      sigma = 2;
    }
    sigmas_default.emplace(id, sigma);
  }
  
  //
  std::cout << "Default sigmas from : " << infile << std::endl;
  for (auto& sigma_default : sigmas_default ){
    TString volName; Int_t ch;
    ch = encoder->DecodeChannelID(sigma_default.first, volName);
    volName.ReplaceAll("Sensor","");
    std::cout<< volName << "_" << ch+1 << " : " << sigma_default.second << std::endl;
  }

  fin.close();
  return true;
};

// read default noise pedestal //
auto readPedestal = [&] ( const char* infile )
{
  std::ifstream fin;
  fin.open(infile);
  if(!fin.is_open()){
    std::cerr << "Error : can't open file " << infile << std::endl;
    return false;
  }

  std::string line, word;
  std::string name;
  Int_t id;
  Double_t pedestal, sigma;

  std::getline(fin, line);
  while ( !fin.eof() ) {
    std::getline(fin, line);
    std::stringstream ss(line);
    ss >> name >> id >> pedestal >> sigma;
    pedestals_default.emplace(id, pedestal);
  }
  
  //
  std::cout << "Default pedestals from : " << infile << std::endl;
  for (auto& pedestal_default : pedestals_default ){
    TString volName; Int_t ch;
    ch = encoder->DecodeChannelID(pedestal_default.first, volName);
    volName.ReplaceAll("Sensor","");
    std::cout<< volName << "_" << ch+1 << " : " << pedestal_default.second << std::endl;
  }

  fin.close();
  return true;
  
};

// readHist
auto readHist = [&] (const char* infile)
{
  TH1::AddDirectory(0);
  auto fin = TFile::Open(infile);
  auto hDir = getDirectory(fin,"rec_adc");
  h1s_ptr = getHistosByChannelId<TH1D>(hDir,"adc");
  std::cout << h1s_ptr.size() << std::endl;
  delete fin;
};

/** search peaks **/
auto searchPeaks = [&] ()
{
  // config the search paramters
  Int_t search_maxpeaks;
  Double_t search_rangelow, search_rangehigh;
  Double_t search_threshold;

  if ( isPulser ) {
    search_maxpeaks = 2*pulsers.size();
    search_rangelow = 1;
    search_rangehigh = ADC_MAXRANGE-1;
    search_threshold = 0.4;

    for ( auto& hist : h1s_ptr ) {
      auto h1 = hist.second;
      h1->GetXaxis()->SetRangeUser(search_rangelow, search_rangehigh);
    }
  }
  else {
    search_maxpeaks = 2*pulsers.size()/7;
    search_rangelow = 300;
    search_rangehigh = ADC_MAXRANGE-1;
    search_threshold = 0.4;
    for ( auto& hist : h1s_ptr ) {
      auto h1 = hist.second;
      h1->GetXaxis()->SetRangeUser(search_rangelow, search_rangehigh);

      auto mean = h1->GetMean();
      if ( mean < 1000 ) {
        h1->GetXaxis()->SetRangeUser(300, mean*2);
      }
      else {
        h1->GetXaxis()->SetRangeUser( 1000, ADC_MAXRANGE-1);
      }
    }
  }

  // loop through all hists
  for ( auto& hist : h1s_ptr ) {
    auto id = hist.first;
    auto h1 = hist.second;

    auto search_sigma = sigmas_default[id];
    TSpectrum s(search_maxpeaks);
    Int_t npeaks = s.Search(h1, search_sigma, "", search_threshold);
    Double_t *xpeaks = s.GetPositionX();
    doubles peaks_found(xpeaks, npeaks);
    std::sort(peaks_found.begin(), peaks_found.end());

    // fit each peak to get more accurate estimation
    auto& means = peaks[id];
    auto& mean_errors = peaks_error[id];
    auto& sigmas = widths[id];
    auto& sigma_errors = widths_error[id];
    for ( auto& peak : peaks_found) {
      // first fit to get rough estimation
      auto result = h1->Fit("gaus", "qns", "", peak-search_sigma, peak+search_sigma);
      double mean = result->Parameter(1);
      double sigma = result->Parameter(2);

      // ignore peak which is not full in the range
      if( (ADC_MAXRANGE-mean) < 3*sigma )
        continue;

      // second fit to get results
      if ( isPulser )
        result = h1->Fit("gaus", "qs+", "", mean-3*sigma, mean+3*sigma);
      else
        result = h1->Fit("gaus", "qs+", "", mean-1*sigma, mean+3*sigma);

      means.emplace_back(result->Parameter(1));
      mean_errors.emplace_back(result->ParError(1));
      sigmas.emplace_back(result->Parameter(2));
      sigma_errors.emplace_back(result->ParError(2));
    }
  }
};

/** fit the ADC_vs_PulserSetting, ADC_vs_Energy **/
auto fitGraph = [&] ()
{
  // fill graphs
  for ( auto& peak : peaks ) {
    auto& id = peak.first;
    auto peak_found = peak.second.AsVector();
    auto peak_error = peaks_error[id].AsVector();

    TString volName;
    Int_t ch = encoder->DecodeChannelID(id, volName);
    volName.ReplaceAll("Sensor","");

    // set up data points
    auto yvalue = pulsers.AsVector();
    if ( !isPulser ) {
      yvalue = source_energies[id].AsVector();
    }

    // filter the data, i.e. get rid of setting value without corresponding peak found
    double init_value = peak_found.at(0);
    double init_setting = yvalue.at(0);
    double init_slope = (peak_found.at(1) - init_value) / (yvalue.at(1) - init_setting); 
    
    // std::cout <<"here\n";
    // std::cout << init_value << " " << init_setting << " " << init_slope << std::endl;

    for ( auto it_value = ++peak_found.begin(), it_setting = ++yvalue.begin() ;
          it_value != peak_found.end() ;
          ++it_value, ++it_setting ) {

      double delta_value = *it_value - init_value;
      double delta_setting = *it_setting - init_setting;
      double ratio = delta_value / delta_setting / init_slope;
      // std::cout << init_value << " " << init_setting << " " << *it_value << " " << *it_setting << " " << ratio << std::endl;

      while ( ratio > 1.9 ) {
        // std::cout<< init_value << " " << *it_value << " " << init_setting << " " << *it_setting << " " << ratio << " herel\n" ;
        std::cout << "Erase setting value " << *it_setting << " from " << volName << "_" << ch+1 << std::endl;
        it_setting = yvalue.erase(it_setting);
        if( it_setting == yvalue.end() )
          break;
        delta_setting = *it_setting - init_setting;
        ratio = delta_value / delta_setting / init_slope;
      }

      while ( ratio < 0.1 ) {
        std::cout << "Erase peak " << *it_value << " from " << volName << "_" << ch+1 << std::endl;
        it_value = peak_found.erase(it_value);
        if( it_value == peak_found.end() )
          break;
        delta_value = *it_value - init_value;
        ratio = delta_value / delta_setting / init_slope;
      }

      init_value = *it_value;
      init_setting = *it_setting;
    }

    // also insert pedestal point
    yvalue.insert(yvalue.begin(), 0);
    peak_found.insert(peak_found.begin(), pedestals_default[id]);
    peak_error.insert(peak_error.begin(), 0);

    // fill the inverse graph
    graphs.emplace(std::piecewise_construct,
                   std::forward_as_tuple(id),
                   std::forward_as_tuple(peak_found.size(), yvalue.data(), peak_found.data(), nullptr,  peak_error.data()));

    auto& graph = graphs[id];
    graph.SetName(Form("g_%s_%d",volName.Data(),ch+1));
    graph.SetTitle(Form("g_%s_%d",volName.Data(),ch+1));
    graph.GetYaxis()->SetTitle("ADC counts");
    if ( isPulser )
      graph.GetXaxis()->SetTitle("Pulser Setting");
    else
      graph.GetXaxis()->SetTitle("Energy (keV)");

    // fill the graph
    graphs_inverse.emplace(std::piecewise_construct,
                           std::forward_as_tuple(id),
                           std::forward_as_tuple(peak_found.size(), peak_found.data(), yvalue.data(), peak_error.data()));

    auto& graph_inverse = graphs_inverse[id];
    graph_inverse.SetName(Form("g_inverse_%s_%d",volName.Data(),ch+1));
    graph_inverse.SetTitle(Form("g_inverse_%s_%d",volName.Data(),ch+1));
    graph_inverse.GetXaxis()->SetTitle("ADC counts");
    if ( isPulser )
      graph_inverse.GetYaxis()->SetTitle("Pulser Setting");
    else
      graph_inverse.GetYaxis()->SetTitle("Energy (keV)");

    // fit graphs with pol1
    TF1 *fpol1 = new TF1("fpol1", "1++x", -10, ADC_MAXRANGE);
    TFitResultPtr result = graph.Fit(fpol1, "qs+", "", 1, ADC_MAXRANGE);
    lines.emplace(id, result);
    delete fpol1;
  }

};

/** output results: histograms, graphs, pdf, paramter text **/ 
auto writeHist = [&] (const char* outfile, const char* directory = "")
{
  TString prefix(outfile);
  prefix.ReplaceAll(".root","");
  TString pdfname_peak = prefix+"_peaks.pdf";
  TString txtname_peak = prefix+"_peaks.txt";
  TString txtname_width = prefix+"_widths.txt";
  TString pdfname_fit = prefix+"_fit.pdf";
  TString txtname_fit = prefix+"_fit_param.txt";

  // output histograms and print pdf 
  // directory
  auto fout = TFile::Open(outfile, "update");
  TDirectory* hdir = gDirectory;

  if ( TString(directory) != "" ) {
    if ( !(hdir = fout->GetDirectory(directory)) ) {
      hdir = fout->mkdir(directory);
    }
  }
  
  TCanvas *c = new TCanvas();
  c->Print(pdfname_peak+"[");
  for ( auto& hist : h1s_ptr ) {
    hist.second->Draw();
    c->Print(pdfname_peak);
    hdir->WriteTObject( hist.second, "", "WriteDelete");
  }
  c->Print(pdfname_peak+"]");

  delete c;
  delete fout;

  // output peak parameters to txt file
  std::ofstream fpeaks(txtname_peak);
  if ( fpeaks.is_open() ) {
    std::cout << "Peaks saved in file : " << txtname_peak << '\n';
  }
  else {
    std::cerr << "Error: can't open text file : " << txtname_peak << '\n';
    return false;
  }

  std::ofstream fwidths(txtname_width);
  if ( fwidths.is_open() ) {
    std::cout << "Peak's widths (i.e. sigma) saved in file : " << txtname_width << '\n';
  }
  else {
    std::cerr << "Error: can't open text file : " << txtname_width << '\n';
    return false;
  }

  for ( auto& peak : peaks ) {
    auto& id = peak.first;
    auto& peaks_found = peak.second;
    auto& widths_found = widths[id];

    Int_t chId; TString volName;
    chId = encoder->DecodeChannelID(id, volName);
    volName.ReplaceAll("Sensor","");

    // column_1 : name, column_2 : id, column_3 : npeaks, column_4 ... : peak1 peak2 ...
    fpeaks << volName << "_" << chId+1 << " " << id << " " << peaks_found.size() << " "; 
    fwidths << volName << "_" << chId+1 << " " << id << " " << peaks_found.size() << " "; 
    std::cout << peaks_found.size() << " peaks found in " << volName << "_" << chId+1 << std::endl;
    int index=0;
    for ( auto& value : peaks_found ) {
      fpeaks << value << " ";
      fwidths << widths_found[index++] << " ";
    }
    fpeaks << std::endl;
    fwidths << std::endl;
  }
  fpeaks.close();
  fwidths.close();

  // output the sigma of the first peak, this sigma can be used for peak search.
  // The output file can be used as an input for peak search next time.
  std::ofstream fsigmas("sigmas.txt");
  for ( auto& width : widths ) {
    auto& id = width.first;
    auto& widths_found = width.second;

    Int_t chId; TString volName;
    chId = encoder->DecodeChannelID(id, volName);
    volName.ReplaceAll("Sensor","");

    volName.Append("_").Append(Form("%d",chId+1));
    fsigmas << std::setw(10) << std::left << volName
            << std::setw(10) << std::left << id
            << std::setw(10) << std::left << widths_found[0] << std::endl;
  }
  fsigmas.close();

  // output the graphs and fit results
  // directory
  auto fout_gr = TFile::Open(outfile, "update");
  TDirectory* grdir = gDirectory;
  if ( !(grdir = fout_gr->GetDirectory("graphs")) ) {
    grdir = fout_gr->mkdir("graphs");
  }
  
  TCanvas *cgr = new TCanvas("cgr","cgr", 1000,500);
  cgr->Divide(2,1);
  cgr->Print(pdfname_fit+"[");
  for ( auto& graph : graphs ) {
    auto& id = graph.first;

    cgr->cd(1);
    graph.second.Draw("A*");
    grdir->WriteTObject( &graph.second, "", "WriteDelete");

    cgr->cd(2);
    graphs_inverse[id].Draw("A*");
    grdir->WriteTObject( &graphs_inverse[id], "", "WriteDelete");

    cgr->Print(pdfname_fit);
  }
  cgr->Print(pdfname_fit+"]");

  delete cgr;
  delete fout_gr;

  std::ofstream flines(txtname_fit);
  if ( flines.is_open() ) {
    std::cout << "Fit result of graph saved in file : " << txtname_fit << '\n';
  }
  else {
    std::cerr << "Error: can't open text file : " << txtname_fit << '\n';
    return false;
  }

  flines << "# Fit parameters : name id intercept slope : " << std::endl;
  for ( auto& result : lines ) {
    auto& id = result.first;
    auto& line = result.second;

    Int_t ch; TString volName;
    ch = encoder->DecodeChannelID(id, volName);
    volName.ReplaceAll("Sensor","");

    volName.Append("_").Append(Form("%d",ch+1));
    // name id p0 p1
    flines << std::setw(10) << std::left << volName
           << std::setw(10) << std::left << id
           << std::setw(10) << std::left << line->Parameter(0)
           << std::setw(10) << std::left << line->Parameter(1) << std::endl;
  }
  
  flines.close();
  return true;
};
