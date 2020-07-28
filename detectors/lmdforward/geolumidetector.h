#ifndef LMD_LMDMC_GEOMETRYFACTORY_H_
#define LMD_LMDMC_GEOMETRYFACTORY_H_

#include <vector>

#include <boost/property_tree/ptree.hpp>

class TGeoManager;
class TGeoVolume;
class TGeoVolumeAssembly;
class FairGeoLoader;
class TGeoNode;


typedef std::pair<std::string, bool> StringBoolPair;

class geolumidetector {
  boost::property_tree::ptree geometry_property_tree;
  std::vector<StringBoolPair> navigation_paths;
  TGeoManager* gGeoMan;

  void retrieveMaterial(FairGeoLoader* geoLoad);

  TGeoVolume* generateLmdBox() const;
  TGeoVolume* generateLmdBoxsecondary() const;
  TGeoVolume* generateBeamPipe() const;
  TGeoVolume* generateDetectorHalf(bool is_bottom_half) const;
  TGeoVolume* generateDetectorHalfPlane(bool is_bottom_half) const;
  TGeoVolume* generateSensorModule() const;
  TGeoVolume* generateSensor() const;
  TGeoVolume* generateSensorVert() const;
  TGeoVolume* generateBeamTPiece() const;
  TGeoVolume* generateAluminumCoolingStructure() const;
  TGeoVolume* generatePCB() const;
  TGeoVolume* generatePCBMountScrew() const;
  TGeoVolume* generatePCBCopperPlug() const;
  TGeoVolume* generatePCBBacksideElectronics() const;
  TGeoVolume* generateCVDCoolingDisc() const;

  
 

  TGeoVolume* generateBoxVacuum(const TGeoVolume* lmd_vol) const;
  void recursiveNodeSubtraction(std::stringstream& ss, TGeoNode* node) const;

  void makeNodesAlignable() const;
  void makeNodesAlignable(TGeoNode* node,
                          unsigned int current_navigation_path_index) const;

 public:
  geolumidetector(
      const boost::property_tree::ptree& geometry_property_tree_);
  virtual ~geolumidetector();

  void init(FairGeoLoader* geoLoad);

  TGeoVolumeAssembly* generateLmdGeometry() const;
};

#endif
