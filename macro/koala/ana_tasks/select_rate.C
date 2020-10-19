void select_rate(const char* ratefile,
                 double ratio_ver_low, double ratio_ver_high,
                 double ratio_hor_low, double ratio_hor_high,
                 double rate_in_low, double rate_in_high,
                 double rate_out_low, double rate_out_high,
                 double rate_up_low, double rate_up_high,
                 double rate_down_low, double rate_down_high
                 )
{
  auto frate = new TFile(ratefile, "update");
  TTreeReader treader("Rates", frate);
  TTreeReaderValue<Long64_t> sec(treader, "Second");
  TTreeReaderValue<Long64_t> usec(treader, "Usecond");
  TTreeReaderValue<Double32_t> rate_in(treader, "Fwd_Inside_Rate");
  TTreeReaderValue<Double32_t> rate_out(treader, "Fwd_Outside_Rate");
  TTreeReaderValue<Double32_t> rate_up(treader, "Fwd_Up_Rate");
  TTreeReaderValue<Double32_t> rate_down(treader, "Fwd_Down_Rate");
  TTreeReaderValue<Double32_t> ratio_hor(treader, "Fwd_InOut_Ratio");
  TTreeReaderValue<Double32_t> ratio_ver(treader, "Fwd_UpDown_Ratio");

  TEventList elist("rate_elist", "List of Rate Selection");

  // output
  TString outfilename(ratefile);
  outfilename.ReplaceAll(".root","_Selected.root");
  auto fout = new TFile(outfilename.Data(), "recreate");
  auto tout = new TTree("Rates_Selected", "Events after selection of Rates condition");

  Long64_t second, usecond;
  double fwd_in, fwd_out, fwd_up, fwd_down;
  double fwd_InOut_ratio, fwd_UpDown_ratio;
  tout->Branch("Second", &second, "Second/L");
  tout->Branch("Usecond", &usecond, "Usecond/L");
  tout->Branch("Fwd_InOut_Ratio", &fwd_InOut_ratio, "Fwd_InOut_Ratio/d");
  tout->Branch("Fwd_UpDown_Ratio", &fwd_UpDown_ratio, "Fwd_UpDown_Ratio/d");
  tout->Branch("Fwd_Inside_Rate", &fwd_in, "Fwd_Inside_Rate/d");
  tout->Branch("Fwd_Outside_Rate", &fwd_out, "Fwd_Outside_Rate/d");
  tout->Branch("Fwd_Up_Rate", &fwd_up, "Fwd_Up_Rate/d");
  tout->Branch("Fwd_Down_Rate", &fwd_down, "Fwd_Down_Rate/d");

  //
  Double_t total=0, selected=0;
  while(treader.Next()){
    total +=1;
    if(    *ratio_ver > ratio_ver_low && *ratio_ver < ratio_ver_high
        && *ratio_hor > ratio_hor_low && *ratio_hor < ratio_hor_high
        && *rate_in   > rate_in_low   && *rate_in   < rate_in_high
        && *rate_out  > rate_out_low  && *rate_out  < rate_out_high
        && *rate_up   > rate_up_low   && *rate_up   < rate_up_high
        && *rate_down > rate_down_low && *rate_down < rate_down_high
        )
    {
      elist.Enter(treader.GetCurrentEntry());
      second = *sec;
      usecond = *usec;
      fwd_in = *rate_in;
      fwd_out = *rate_out;
      fwd_up = *rate_up;
      fwd_down = *rate_down;
      fwd_InOut_ratio = *ratio_hor;
      fwd_UpDown_ratio = *ratio_ver;

      tout->Fill();
      selected +=1;
    }
  }
  std::cout << selected/total*100 << "% ems events selected" << std::endl;

  //
  frate->WriteTObject(&elist, "", "Delete");
  fout->WriteTObject(tout, "", "Delete");

  delete fout, frate;
}
