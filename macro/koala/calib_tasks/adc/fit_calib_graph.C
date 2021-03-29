void fit_calib_graph(const char* infile, const char* outfile)
{
  /***************************************************************************/
  using GraphPtrs = std::map<Int_t, TGraphErrors*>;
  GraphPtrs graphs;
  GraphPtrs graphs_inverse;

  using FitResult = std::map<Int_t, TFitResultPtr>;
  FitResult lines;
  FitResult lines_inverse;

  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  constexpr Int_t ADC_MAXRANGE = 7680;

  /***************************************************************************/
  auto filein = TFile::Open(infile);

  TDirectory *gdir = nullptr;
  filein->GetObject("graphs", gdir);
  if( !gdir ) {
    std::cerr << "Error: no directory graphs in file " << infile << std::endl;
    return false;
  }

  auto getGraph = [&] ( const char* hname ) -> TGraphErrors*
    {
      TGraphErrors *grah = nullptr;
      gdir->GetObject(hname, grah);
      if ( !grah ) {
        std::cerr << "Error: no graph " << hname << std::endl;
        return nullptr;
      }
      return grah;
    };

  /***************************************************************************/
  std::vector<Int_t> ChIDs = encoder->GetRecChIDs();

  for ( auto& ChID : ChIDs ) {
    TString volName;
    Int_t ch = encoder->DecodeChannelID(ChID, volName);
    volName.ReplaceAll("Sensor","");

    if ( auto grah = getGraph(Form("g_%s_%d", volName.Data(), ch+1)) ) {
      graphs.emplace(ChID, grah);
    }
    if ( auto grah_inverse = getGraph(Form("g_inverse_%s_%d", volName.Data(), ch+1)) ) {
      graphs_inverse.emplace(ChID, grah_inverse);
    }
  }

  delete filein;

  /***************************************************************************/
  for ( auto graph : graphs ) {
    auto& id = graph.first;
    auto& gptr = graph.second;
    
    // TF1 *fpol1 = new TF1("fpol1", "1++x", -10, ADC_MAXRANGE);
    TF1 *fpol1 = new TF1("fpol2", "[0]+[1]*x+[2]*x*x", -10, ADC_MAXRANGE);
    fpol1->SetLineColor(kBlue);
    TFitResultPtr result = gptr->Fit(fpol1, "qs", "", 1, ADC_MAXRANGE);
    lines.emplace(id, result);
    delete fpol1;

  }

  /***************************************************************************/
  TString prefix(outfile);
  prefix.ReplaceAll(".root","");
  TString pdfname_fit = prefix+"_graph.pdf";
  TString txtname_fit = prefix+"_graph_param.txt";

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
    graph.second->Draw("A*");
    grdir->WriteTObject( graph.second, "", "WriteDelete");

    cgr->cd(2);
    graphs_inverse[id]->Draw("A*");
    grdir->WriteTObject( graphs_inverse[id], "", "WriteDelete");

    cgr->Print(pdfname_fit);
  }
  cgr->Print(pdfname_fit+"]");

  delete cgr;
  delete fout_gr;

  /***************************************************************************/
  std::ofstream flines(txtname_fit);
  if ( flines.is_open() ) {
    std::cout << "Fit result of graph saved in file : " << txtname_fit << '\n';
  }
  else {
    std::cerr << "Error: can't open text file : " << txtname_fit << '\n';
    return false;
  }

  flines << "# Fit parameters for file : " << infile << std::endl;
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
           << std::setw(10) << std::left << line->Parameter(1)
           << std::setw(10) << std::left << line->Parameter(2)
           << std::endl;
  }
  
  flines.close();
}
