void checkFwdCoverage(Double_t mom, // in GeV
                      const char* geoFile="../calib_para/geo_standard.root")
{
  TFile* fgeo=new TFile(geoFile);
  TGeoManager* geoMan=(TGeoManager*)fgeo->Get("FAIRGeom");
  KoaGeoHandler* geoHandler = new KoaGeoHandler(kFALSE);
  
  // get position boundary
  Double_t fwd_low, fwd_high, temp;
  geoHandler->GetDetBoundaryByName("SensorSc1", fwd_low, temp);
  geoHandler->GetDetBoundaryByName("SensorSc2", temp, fwd_high);
  Double_t si1_low, si1_high;
  geoHandler->GetDetBoundaryByName("SensorSi1", si1_low, si1_high);
  Double_t si2_low, si2_high;
  geoHandler->GetDetBoundaryByName("SensorSi2", si2_low, si2_high);

  KoaElasticCalculator* calculator = new KoaElasticCalculator(mom);
  Double_t rec_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSi1"));
  calculator->SetRecDistance(rec_distance);

  Double_t rec_low, rec_high;
  Double_t e_low, e_high;
  Double_t fwd_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSc1"));
  calculator->SetFwdDistance(fwd_distance);
  rec_low = calculator->GetRecZByFwdX(fwd_low);
  e_low = calculator->GetEnergyByFwdX(fwd_low);

  fwd_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSc2"));
  calculator->SetFwdDistance(fwd_distance);
  rec_high = calculator->GetRecZByFwdX(fwd_high);
  e_high = calculator->GetEnergyByFwdX(fwd_high);

  // get id boundary
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  Double_t global_pos[3] = {-rec_distance, 0, rec_low/10.};
  Int_t id_temp;
  Int_t id_si1_low = encoder->DecodeChannelID(geoHandler->RecGlobalPositionToDetCh(global_pos, 0), id_temp);

  global_pos[2] = rec_high/10.;
  Int_t id_si1_high = 47;
  if ( rec_high/10 < si1_high ) {
    id_si1_high = encoder->DecodeChannelID(geoHandler->RecGlobalPositionToDetCh(global_pos, 0), id_temp);
  }
  Int_t id_si2_low = 0, id_si2_high = -2;
  if ( rec_high/10 < si2_low ) {
    id_si2_low = -2;
  }
  else {
    id_si2_high = encoder->DecodeChannelID(geoHandler->RecGlobalPositionToDetCh(global_pos, 1), id_temp);
  }

  // get physical booundary
  Int_t id_si1_physical;
  global_pos[2] = 0;
  id_si1_physical = encoder->DecodeChannelID(geoHandler->RecGlobalPositionToDetCh(global_pos, 0), id_temp);
  
  // get target |t| boundary 
  // T corresponding to 0.0008 < |t| < 0.001
  double t_low = 0.0008, t_high = 0.001; // in GeV/c
  double et_low = t_low/2./0.938272081*1000; // in MeV
  double et_high = t_high/2./0.938272081*1000;
  double rect_low = calculator->GetRecZByEnergy(et_low); // in mm
  double rect_high = calculator->GetRecZByEnergy(et_high);
  double fwdt_low = calculator->GetFwdXByEnergy(et_low); // in cm
  double fwdt_high = calculator->GetFwdXByEnergy(et_high); 
  double alphat_low = calculator->GetAlphaByEnergy(et_low); // in degree
  double alphat_high = calculator->GetAlphaByEnergy(et_high);
  double thetat_low = calculator->GetThetaByAlpha(alphat_low); // in degree
  double thetat_high = calculator->GetThetaByAlpha(alphat_high);

  // Fwd spread in Y: w = s*d*theta/l
  //   s: recoil sensor spread in Y
  //   l: recoil sensor distance to IP
  //   d: fwd sensor distance to IP
  //theta: scattering angle (confined by the design requirement like |t| range)
  auto pts_si1 = geoHandler->GetDetBoundaryPointsById(0); 
  auto pts_si2 = geoHandler->GetDetBoundaryPointsById(1); 
  double l = rec_distance;
  double d = fwd_distance;
  double s = TMath::Abs(pts_si1[2].Y()-pts_si2[1].Y());
  double fwd_width_min = s*d*thetat_high/180.*3.14151926/l;

  // std::cout << "l: " << l << " d: " << d << " s: " << s << std::endl;

  global_pos[2] = rect_low/10.;
  Int_t idt_si1_low = encoder->DecodeChannelID(geoHandler->RecGlobalPositionToDetCh(global_pos, 0), id_temp);

  global_pos[2] = rect_high/10.;
  Int_t idt_si1_high = 47;
  if ( rect_high/10 < si1_high ) {
    idt_si1_high = encoder->DecodeChannelID(geoHandler->RecGlobalPositionToDetCh(global_pos, 0), id_temp);
  }
  Int_t idt_si2_low = 0, idt_si2_high = -2;
  if ( rect_high/10 < si2_low ) {
    idt_si2_low = -2;
  }
  else {
    idt_si2_high = encoder->DecodeChannelID(geoHandler->RecGlobalPositionToDetCh(global_pos, 1), id_temp);
  }

  // print out
  std::cout << "Forward Sensor:\n";
  std::cout << "\t Distance: " << fwd_distance << " cm" << std::endl;
  std::cout << "\t Boundary: [" << fwd_low << ", " << fwd_high << "] cm" << std::endl;

  std::cout << "\nRecoil Sensor covered by fwd:\n";
  std::cout << "\t Distance: " << rec_distance << " cm" << std::endl;
  std::cout << "\t Boundary (position): [" << rec_low << ", " << rec_high << "] mm" << std::endl;
  std::cout << "\t Boundary (ch id): Si1[" << id_si1_low+1 << ", " << id_si1_high+1 <<"]"
            << ", Si2[" << id_si2_low+1 << ", " << id_si2_high+1 << "]" << std::endl;

  std::cout << "\nValid channel starts from:\n";
  std::cout << "\t Si1 channel : " << id_si1_physical+1 << std::endl;

  std::cout << "\nRecoil energy range with fwd coverage:\n";
  std::cout << "\tT (MeV): [" << e_low << ", " << e_high << "]\n";
  std::cout << "\tt (GeV/c)^2: [" << 2*0.938*e_low/1000 << ", " << 2*0.938*e_high/1000 << "]\n";

  std::cout << "\nRecoil Sensor covered by required |t| range:\n";
  std::cout << "\t Boundary (|t|): [" << t_low << ", " << t_high << "] (GeV/c)^2" << std::endl;
  std::cout << "\t Boundary (T): [" << et_low << ", " << et_high << "] MeV" << std::endl;
  std::cout << "\t Rec Boundary (position): [" << rect_low << ", " << rect_high << "] mm" << std::endl;
  std::cout << "\t Boundary (ch id): Si1[" << idt_si1_low+1 << ", " << idt_si1_high+1 <<"]"
            << ", Si2[" << idt_si2_low+1 << ", " << idt_si2_high+1 << "]" << std::endl;
  std::cout << "\t Fwd Boundary (position): [" << fwdt_low << ", " << fwdt_high << "] cm" << std::endl;
  std::cout << "\t Minmum fwd scintillator width: " << fwd_width_min << " cm\n";

  //
  delete fgeo;
  delete geoHandler;
  delete calculator;
}
