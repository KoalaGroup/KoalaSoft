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

  std::map<int, double> getStripGlobalPosition(const char* geoFile)
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
      positions.emplace(id, global_pos[2]);
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

  std::map<int, double> getStripAlphas(const char* geoFile)
  {
    auto geoHandler = getGeometryHandler(geoFile);

    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs = encoder->GetRecChIDs();

    Double_t pos_low, pos_high, pos_center;
    Double_t global_pos[3] = {0};
    Double_t local_pos[3] = {0};

    std::map<int, double> alphas;
    Int_t ch_id, det_id;
    double pi = TMath::Pi();

    for(auto id : ChIDs) {
      ch_id = encoder->DecodeChannelID(id, det_id);

      pos_center = geoHandler->RecDetChToPosition(id, pos_low, pos_high);

      local_pos[2] = pos_center;
      geoHandler->LocalToGlobal(local_pos, global_pos, det_id);

      TVector3 vec(global_pos);
      alphas.emplace(id, 90 - vec.Theta()/pi*180);
    }

    delete geoHandler;

    return alphas;
  }
}

#endif
