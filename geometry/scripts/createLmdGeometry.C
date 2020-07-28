#include <iostream>

#include "detectors/lmdforward/geolumidetector.h"

#include "FairGeoLoader.h"
#include "FairGeoInterface.h"
#include "FairGeoBuilder.h"
#include "FairGeoMedia.h"

#include "TFile.h"
#include "TROOT.h"
#include "TGeoManager.h"
#include "TGeoVolume.h"

#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;

void createLmdGeometry(std::string output_filename = "LumiDetector.root",
		       
		       std::string geo_params_config_file_url = "../../parameters/lmd-geo-params.json")
{
  // load parameters
  ptree geo_property_tree;
  read_json(geo_params_config_file_url, geo_property_tree);
  
  
  FairGeoLoader *geoLoad = new FairGeoLoader("TGeo", "FairGeoLoader");
  FairGeoInterface *geoFace = geoLoad->getGeoInterface();
  std::string koalasoft_dir(getenv("VMCWORKDIR"));
  geoFace->setMediaFile((koalasoft_dir + "/geometry/media_pnd.geo").c_str());
  geoFace->readMedia();
  FairGeoMedia *Media = geoFace->getMedia();
  FairGeoBuilder *geobuild = geoLoad->getGeoBuilder();
  
  TFile file(output_filename.c_str(), "RECREATE");
  
  TGeoManager *gGeoMan = (TGeoManager *) gROOT->FindObject("FAIRGeom");
  
  geolumidetector lmd_geo_factory(geo_property_tree);
  
  
  lmd_geo_factory.init(geoLoad);
  
		
  TGeoVolumeAssembly *top = lmd_geo_factory.generateLmdGeometry();
  
  
  gGeoMan->CheckOverlaps(0.0001); // 1mu
  gGeoMan->PrintOverlaps();
  
  top->Write();
  
  file.Close();
  
  
  gGeoMan->SetVisLevel(20);

  // top->Draw("ogl");
  
		
}
