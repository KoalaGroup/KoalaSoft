void calc_calib_param(const char *filePulserBeamGain,
                      const char *filePulserCommonGain,
                      const char *fileSourceCommonGain,
                      const char *measured_file,
                      const char *fileOut)
{
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();

  std::map<Int_t, Double_t> pulserBG_p0, pulserBG_p1;
  std::map<Int_t, Double_t> pulserCG_p0, pulserCG_p1;
  std::map<Int_t, Double_t> sourceCG_p0, sourceCG_p1;
  std::map<Int_t, Double_t> sourceBG_p0, sourceBG_p1;
  std::map<Int_t, Double_t> calcBG_p0,   calcBG_p1;
  std::map<Int_t, Double_t> calcBG_inverse_p0,   calcBG_inverse_p1;

  // read in beam gain paramters
  std::ifstream fin_PulserBeamGain;
  fin_PulserBeamGain.open(filePulserBeamGain);
  if(!fin_PulserBeamGain.is_open()){
    std::cerr << "Error : can't open file " << filePulserBeamGain << std::endl;
    return false;
  }

  std::string line, word;
  std::string name;
  Int_t id;
  Double_t p0, p1;

  std::getline(fin_PulserBeamGain, line);
  while ( !fin_PulserBeamGain.eof() ) {
    std::getline(fin_PulserBeamGain, line);
    std::stringstream ss(line);
    ss >> name >> id >> p0 >> p1;

    pulserBG_p0.emplace(id, p0);
    pulserBG_p1.emplace(id, p1);
  }

  fin_PulserBeamGain.close();
  
  // read in common gain paramters
  std::ifstream fin_PulserCommonGain;
  fin_PulserCommonGain.open(filePulserCommonGain);
  if(!fin_PulserCommonGain.is_open()){
    std::cerr << "Error : can't open file " << filePulserCommonGain << std::endl;
    return false;
  }

  std::getline(fin_PulserCommonGain, line);
  while ( !fin_PulserCommonGain.eof() ) {
    std::getline(fin_PulserCommonGain, line);
    std::stringstream ss(line);
    ss >> name >> id >> p0 >> p1;

    pulserCG_p0.emplace(id, p0);
    pulserCG_p1.emplace(id, p1);
  }

  fin_PulserCommonGain.close();

  // read in common gain paramters
  std::ifstream fin_SourceCommonGain;
  fin_SourceCommonGain.open(fileSourceCommonGain);
  if(!fin_SourceCommonGain.is_open()){
    std::cerr << "Error : can't open file " << fileSourceCommonGain << std::endl;
    return false;
  }

  std::getline(fin_SourceCommonGain, line);
  while ( !fin_SourceCommonGain.eof() ) {
    std::getline(fin_SourceCommonGain, line);
    std::stringstream ss(line);
    ss >> name >> id >> p0 >> p1;

    sourceCG_p0.emplace(id, p0);
    sourceCG_p1.emplace(id, p1);
  }
  
  fin_SourceCommonGain.close();

  // read in beam gain paramters
  std::ifstream fin_SourceBeamGain;
  fin_SourceBeamGain.open(measured_file);
  if(!fin_SourceBeamGain.is_open()){
    std::cerr << "Error : can't open file " << measured_file << std::endl;
    return false;
  }

  std::getline(fin_SourceBeamGain, line);
  while ( !fin_SourceBeamGain.eof() ) {
    std::getline(fin_SourceBeamGain, line);
    std::stringstream ss(line);
    ss >> name >> id >> p0 >> p1;

    sourceBG_p0.emplace(id, p0);
    sourceBG_p1.emplace(id, p1);
  }
  
  fin_SourceBeamGain.close();

  // calculate source beam gain parameters
  std::ofstream fout(fileOut);
  fout << "# calclulated calibration parameter : name id ADC->E E->ADC" << std::endl;
  std::vector<Int_t> ChIDs = encoder->GetRecChIDs();
  for ( auto& ChID : ChIDs ) {
    TString volName;
    Int_t ch = encoder->DecodeChannelID(ChID, volName);
    volName.ReplaceAll("Sensor","");
    volName.Append("_").Append(Form("%d",ch+1));

    // calculate
    auto p0 = pulserBG_p0[ChID] -
              pulserBG_p1[ChID]*pulserCG_p0[ChID]/pulserCG_p1[ChID] +
              pulserBG_p1[ChID]*sourceCG_p0[ChID]/pulserCG_p1[ChID];
    auto p1 = pulserBG_p1[ChID]*sourceCG_p1[ChID]/pulserCG_p1[ChID];
    calcBG_p0.emplace(ChID, p0);
    calcBG_p1.emplace(ChID, p1);

    auto p0_inverse = - sourceCG_p0[ChID]/sourceCG_p1[ChID] +
                      pulserCG_p0[ChID]/sourceCG_p1[ChID]   -
                      pulserCG_p1[ChID]*pulserBG_p0[ChID]/sourceCG_p1[ChID]/pulserBG_p1[ChID];
    auto p1_inverse = pulserCG_p1[ChID]/sourceCG_p1[ChID]/pulserBG_p1[ChID];
    calcBG_inverse_p0.emplace(ChID, p0_inverse);
    calcBG_inverse_p1.emplace(ChID, p1_inverse);

    // output
    // inverse is ADC-->Energy
    // name id calc_inverse_p0 calc_inverse_p1 calc_p0 calc_p1
    fout << std::setw(10) << std::left << volName
         << std::setw(10) << std::left << ChID
         << std::setw(10) << std::left << calcBG_inverse_p0[ChID]
         << std::setw(10) << std::left << calcBG_inverse_p1[ChID]
         << std::setw(10) << std::left << calcBG_p0[ChID]
         << std::setw(10) << std::left << calcBG_p1[ChID]
         << std::endl;
  }

  fout.close();

  //
  return true;
}

void check_calib_param(const char* calc_file,
                       const char* measured_file,
                       const char* source_setting_file,
                       const char* check_file="calib_check.txt")
{
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();

  using doubles = ROOT::VecOps::RVec<Double_t>;
  doubles   pulsers;
  std::map<Int_t, doubles> source_energies;

  std::map<Int_t, Double_t> sourceBG_p0, sourceBG_p1;
  std::map<Int_t, Double_t> calcBG_p0,   calcBG_p1;
  std::map<Int_t, Double_t> calcBG_inverse_p0,   calcBG_inverse_p1;
  ////////////////////////////////////////////////////////////////////////////////////
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
      for ( auto i=0; i<length; i++) {
        std::vector<Int_t> ChIDs = encoder->GetRecChIDs();
        for ( auto& ChID : ChIDs ) {

          auto& id = ChID;
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

      std::cout << "Energy setting from : " << infile << std::endl;
      convertSourceEnergy();

      fin.close();
    };

  ///////////////////
  readPulserSetting(source_setting_file);

  ///////////////////////
  // read in beam gain paramters
  std::ifstream fin_SourceBeamGain;
  fin_SourceBeamGain.open(measured_file);
  if(!fin_SourceBeamGain.is_open()){
    std::cerr << "Error : can't open file " << measured_file << std::endl;
    return false;
  }

  std::string line, word;
  std::string name;
  Int_t id;
  Double_t p0, p1;

  std::getline(fin_SourceBeamGain, line);
  while ( !fin_SourceBeamGain.eof() ) {
    std::getline(fin_SourceBeamGain, line);
    std::stringstream ss(line);
    ss >> name >> id >> p0 >> p1;

    sourceBG_p0.emplace(id, p0);
    sourceBG_p1.emplace(id, p1);
  }
  
  fin_SourceBeamGain.close();

  ////////////////////////
  std::ifstream fin_calc;
  fin_calc.open(calc_file);
  if(!fin_calc.is_open()){
    std::cerr << "Error : can't open file " << measured_file << std::endl;
    return false;
  }

  double p1_inverse, p0_inverse;
  std::getline(fin_calc, line);
  while ( !fin_calc.eof() ) {
    std::getline(fin_calc, line);
    std::stringstream ss(line);
    ss >> name >> id >> p0_inverse >> p1_inverse >> p0 >> p1;

    calcBG_inverse_p0.emplace(id, p0_inverse);
    calcBG_inverse_p1.emplace(id, p1_inverse);
    calcBG_p0.emplace(id, p0);
    calcBG_p1.emplace(id, p1);
    // std::cout << name << " " << id << " " << p0_inverse << " " << p1_inverse << " " << p0 << " " << p1 << std::endl;
  }
  
  fin_calc.close();

  ////////////////////////
  // checking output
  std::ofstream fout(check_file);
  fout << "Checking the calib paramter: energy adc_measured adc_calculated ... " << std::endl;
  std::vector<Int_t> ChIDs = encoder->GetRecChIDs();
  for ( auto& ChID : ChIDs ) {
    TString volName;
    Int_t ch = encoder->DecodeChannelID(ChID, volName);
    volName.ReplaceAll("Sensor","");
    volName.Append("_").Append(Form("%d",ch+1));

    auto energies = source_energies[ChID];
    fout << std::setw(10) << std::left << volName;
    for( auto energy : energies ) {
      fout << std::setw(10) << std::left << energy
           << std::setw(10) << std::left << sourceBG_p0[ChID] + sourceBG_p1[ChID] * energy
           << std::setw(10) << std::left << calcBG_p0[ChID]   + calcBG_p1[ChID] * energy ;
    }
    fout << std::endl;

  }
  fout.close();
}
