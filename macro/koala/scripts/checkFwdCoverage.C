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
  Double_t fwd_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSc1"));
  calculator->SetFwdDistance(fwd_distance);
  rec_low = calculator->GetRecZByFwdX(fwd_low);

  fwd_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSc2"));
  calculator->SetFwdDistance(fwd_distance);
  rec_high = calculator->GetRecZByFwdX(fwd_high);

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

  //
  delete fgeo;
  delete geoHandler;
  delete calculator;
}
