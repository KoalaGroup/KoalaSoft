#ifndef KOAGEOMETRYUTILITY_H
#define KOAGEOMETRYUTILITY_H

namespace KoaUtility
{
  KoaGeoHandler* getGeometryHandler(const char* geoFile)
  {
    auto fgeo = TFile::Open(geoFile);
    fgeo->Get("FAIRGeom");
    auto geoHandler = new KoaGeoHandler(kFALSE);

    return geoHandler;
  }

  // zoffset in cm
  std::map<int, double> getChannelGlobalPosition(const char* geoFile, double* zoffset)
  {
    auto geoHandler = getGeometryHandler(geoFile);

    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs = encoder->GetRecChIDs();

    Double_t pos_low, pos_high, pos_center;
    Double_t global_pos[3] = {0};
    Double_t local_pos[3] = {0};

    std::map<int, double> positions;
    Int_t ch_id, det_id;
    for(auto id : ChIDs) {
      ch_id = encoder->DecodeChannelID(id, det_id);

      pos_center = geoHandler->RecDetChToPosition(id, pos_low, pos_high);

      local_pos[2] = pos_center;
      geoHandler->LocalToGlobal(local_pos, global_pos, det_id);
      positions.emplace(id, global_pos[2]+zoffset[det_id]);
    }

    delete geoHandler;

    return positions;
  }

  // zoffset in cm, loffset in cm
  std::map<int, double> getChannelDistances(const char* geoFile, double loffset, double* zoffset)
  {
    auto geoHandler = getGeometryHandler(geoFile);

    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs = encoder->GetRecChIDs();

    Double_t pos_low, pos_high, pos_center;
    Double_t global_pos[3] = {0};
    Double_t local_pos[3] = {0};

    Double_t rec_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSi1"));
    rec_distance += loffset;

    std::map<int, double> positions;
    Int_t ch_id, det_id;
    for(auto id : ChIDs) {
      ch_id = encoder->DecodeChannelID(id, det_id);

      pos_center = geoHandler->RecDetChToPosition(id, pos_low, pos_high);

      local_pos[2] = pos_center;
      geoHandler->LocalToGlobal(local_pos, global_pos, det_id);

      auto z = global_pos[2]+zoffset[det_id];
      positions.emplace(id, TMath::Sqrt(z*z+rec_distance*rec_distance));
    }

    delete geoHandler;

    return positions;
  }

  double getRecoilSensorPosition(const char* geoFile)
  {
    auto geoHandler = getGeometryHandler(geoFile);
    
    Double_t rec_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSi1"));

    delete geoHandler;
    return rec_distance;
  }

  // yoffset, zoffset in cm
  std::map<int, double> getChannelAlphas(const char* geoFile, double* yoffset, double* zoffset)
  {
    auto geoHandler = getGeometryHandler(geoFile);

    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs = encoder->GetRecChIDs();

    Double_t pos_low, pos_high, pos_center;
    Double_t global_pos[3] = {0};
    Double_t local_pos[3] = {0};
    Double_t sensor_thickness[4] = {0.1/2, 0.1/2, 0.5/2, 1.1/2}; // half thickness in cm

    std::map<int, double> alphas;
    Int_t ch_id, det_id;
    double pi = TMath::Pi();

    for(auto id : ChIDs) {
      ch_id = encoder->DecodeChannelID(id, det_id);

      pos_center = geoHandler->RecDetChToPosition(id, pos_low, pos_high);

      local_pos[0] = -sensor_thickness[det_id];
      local_pos[2] = pos_center;
      geoHandler->LocalToGlobal(local_pos, global_pos, det_id);

      global_pos[2] += zoffset[det_id];
      global_pos[1] += yoffset[det_id];
      TVector3 vec(global_pos);
      alphas.emplace(id, 90 - vec.Theta()/pi*180);
    }

    delete geoHandler;

    return alphas;
  }

  // yoffset, zoffset in cm
  std::map<int, double> getChannelEnergies(double mom,
                                           const char* geoFile, double* yoffset, double* zoffset)
  {
    auto geoHandler = getGeometryHandler(geoFile);
    auto calculator = new KoaElasticCalculator(mom);

    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs = encoder->GetRecChIDs();

    Double_t pos_low, pos_high, pos_center;
    Double_t global_pos[3] = {0};
    Double_t local_pos[3] = {0};
    Double_t sensor_thickness[4] = {0.1/2, 0.1/2, 0.5/2, 1.1/2}; // half thickness in cm

    std::map<int, double> energies;
    Int_t ch_id, det_id;
    double pi = TMath::Pi();

    for(auto id : ChIDs) {
      ch_id = encoder->DecodeChannelID(id, det_id);

      pos_center = geoHandler->RecDetChToPosition(id, pos_low, pos_high);

      local_pos[0] = -sensor_thickness[det_id];
      local_pos[2] = pos_center;
      geoHandler->LocalToGlobal(local_pos, global_pos, det_id);

      global_pos[2] += zoffset[det_id];
      global_pos[1] += yoffset[det_id];
      TVector3 vec(global_pos);
      auto alpha =  90 - vec.Theta()/pi*180;

      if (alpha < 0)
        continue;

      energies.emplace(id,calculator->GetEnergyByAlpha(alpha));
    }

    delete geoHandler;

    return energies;
  }
  //
  std::map<int, double> getChannelDeltaT(double mom, //in GeV
                                       const char* geoFile,
                                       double* yoffset, double* zoffset)
  {
    double pi = TMath::Pi();
    Double_t fProtonMass = 0.938272081;
    Double_t sensor_thickness[4] = {0.1/2, 0.1/2, 0.5/2, 1.1/2}; // half thickness in cm

    std::map<int, double> DeltaT;

    //
    auto geoHandler = getGeometryHandler(geoFile);
    auto calculator = new KoaElasticCalculator(mom);

    Double_t pos_low, pos_high, pos_center;
    Int_t ch_id, det_id;

    auto get_alpha = [&] (double z, int det) -> double
                     {
                       Double_t global_pos[3] = {0};
                       Double_t local_pos[3] = {0};

                       local_pos[0] = -sensor_thickness[det];
                       local_pos[2] = z;
                       geoHandler->LocalToGlobal(local_pos, global_pos, det);

                       global_pos[2] += zoffset[det];
                       global_pos[1] += yoffset[det];
                       TVector3 vec(global_pos);
                       return 90 - vec.Theta()/pi*180;
                     };

    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs = encoder->GetRecChIDs();
    for(auto id : ChIDs) {
      ch_id = encoder->DecodeChannelID(id, det_id);

      pos_center = geoHandler->RecDetChToPosition(id, pos_low, pos_high);

      auto alpha_low = get_alpha(pos_low, det_id);
      auto alpha_high = get_alpha(pos_high, det_id);

      auto energy_low = calculator->GetEnergyByAlpha(alpha_low)/1000.;
      auto energy_high = calculator->GetEnergyByAlpha(alpha_high)/1000.;

      if (alpha_low < 0)
        continue;

      DeltaT.emplace(id, 2*fProtonMass*(energy_high-energy_low));
    }

    delete geoHandler;

    return DeltaT;
  }

  //////////////////////////// strip id as index //////////////////////////////
  // zoffset in cm
  std::map<int, double> getStripGlobalPosition(const char* geoFile, double* zoffset)
  {
    auto geoHandler = getGeometryHandler(geoFile);

    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs = geoHandler->GetStripIds();

    Double_t pos_low, pos_high, pos_center;
    Double_t global_pos[3] = {0};
    Double_t local_pos[3] = {0};

    std::map<int, double> positions;
    Int_t ch_id, det_id;
    for(auto id : ChIDs) {
      ch_id = encoder->DecodeChannelID(id, det_id);

      pos_center = geoHandler->RecDetStripToPosition(id, pos_low, pos_high);

      local_pos[2] = pos_center;
      geoHandler->LocalToGlobal(local_pos, global_pos, det_id);
      positions.emplace(id, global_pos[2]+zoffset[det_id]);
    }

    delete geoHandler;

    return positions;
  }

  // zoffset in cm, loffset in cm
  std::map<int, double> getStripDistances(const char* geoFile, double loffset, double* zoffset)
  {
    auto geoHandler = getGeometryHandler(geoFile);

    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs = geoHandler->GetStripIds();

    Double_t pos_low, pos_high, pos_center;
    Double_t global_pos[3] = {0};
    Double_t local_pos[3] = {0};

    Double_t rec_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSi1"));
    rec_distance += loffset;

    std::map<int, double> positions;
    Int_t ch_id, det_id;
    for(auto id : ChIDs) {
      ch_id = encoder->DecodeChannelID(id, det_id);

      pos_center = geoHandler->RecDetStripToPosition(id, pos_low, pos_high);

      local_pos[2] = pos_center;
      geoHandler->LocalToGlobal(local_pos, global_pos, det_id);

      auto z = global_pos[2]+zoffset[det_id];
      positions.emplace(id, TMath::Sqrt(z*z+rec_distance*rec_distance));
    }

    delete geoHandler;

    return positions;
  }

  // yoffset, zoffset in cm
  std::map<int, double> getStripAlphas(const char* geoFile, double* yoffset, double* zoffset)
  {
    auto geoHandler = getGeometryHandler(geoFile);

    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs = geoHandler->GetStripIds();

    Double_t pos_low, pos_high, pos_center;
    Double_t global_pos[3] = {0};
    Double_t local_pos[3] = {0};
    Double_t sensor_thickness[4] = {0.1/2, 0.1/2, 0.5/2, 1.1/2}; // half thickness in cm

    std::map<int, double> alphas;
    Int_t ch_id, det_id;
    double pi = TMath::Pi();

    for(auto id : ChIDs) {
      ch_id = encoder->DecodeChannelID(id, det_id);

      pos_center = geoHandler->RecDetStripToPosition(id, pos_low, pos_high);

      local_pos[0] = -sensor_thickness[det_id];
      local_pos[2] = pos_center;
      geoHandler->LocalToGlobal(local_pos, global_pos, det_id);

      global_pos[2] += zoffset[det_id];
      global_pos[1] += yoffset[det_id];
      TVector3 vec(global_pos);
      alphas.emplace(id, 90 - vec.Theta()/pi*180);
    }

    delete geoHandler;

    return alphas;
  }

  // yoffset, zoffset in cm
  std::map<int, double> getStripEnergies(double mom,
                                         const char* geoFile, double* yoffset, double* zoffset)
  {
    auto geoHandler = getGeometryHandler(geoFile);
    auto calculator = new KoaElasticCalculator(mom);

    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs = geoHandler->GetStripIds();

    Double_t pos_low, pos_high, pos_center;
    Double_t global_pos[3] = {0};
    Double_t local_pos[3] = {0};
    Double_t sensor_thickness[4] = {0.1/2, 0.1/2, 0.5/2, 1.1/2}; // half thickness in cm

    std::map<int, double> energies;
    Int_t ch_id, det_id;
    double pi = TMath::Pi();

    for(auto id : ChIDs) {
      ch_id = encoder->DecodeChannelID(id, det_id);

      pos_center = geoHandler->RecDetStripToPosition(id, pos_low, pos_high);

      local_pos[0] = -sensor_thickness[det_id];
      local_pos[2] = pos_center;
      geoHandler->LocalToGlobal(local_pos, global_pos, det_id);

      global_pos[2] += zoffset[det_id];
      global_pos[1] += yoffset[det_id];
      TVector3 vec(global_pos);
      auto alpha =  90 - vec.Theta()/pi*180;

      if (alpha < 0)
        continue;

      energies.emplace(id,calculator->GetEnergyByAlpha(alpha));
    }

    delete geoHandler;

    return energies;
  }
}

#endif
