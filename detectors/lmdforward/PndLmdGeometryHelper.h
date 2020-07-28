#ifndef LMD_LMDMC_PNDLMDGEOMETRYHELPER_H_
#define LMD_LMDMC_PNDLMDGEOMETRYHELPER_H_

#include <map>
#include <string>
#include <vector>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <TGeoManager.h>
#include <TVector3.h>

struct PndLmdHitLocationInfo {
	// we use small data types here as they can be packed into 8 bytes
	unsigned char detector_half;
	unsigned char plane;
	unsigned char module;
	unsigned char module_side;
	unsigned char module_sensor_id;

	friend std::ostream& operator<<(std::ostream& stream, const PndLmdHitLocationInfo& hit_info) {
		stream << "detector half: " << (unsigned int) hit_info.detector_half << "\n";
		stream << "detector plane: " << (unsigned int) hit_info.plane << "\n";
		stream << "module on half plane: " << (unsigned int) hit_info.module << "\n";
		stream << "side of module: " << (unsigned int) hit_info.module_side << "\n";
		stream << "sensor id: " << (unsigned int) hit_info.module_sensor_id << "\n";

		return stream;
	}

	bool operator <(const PndLmdHitLocationInfo &o) {
		return std::tie(detector_half, plane, module, module_side, module_sensor_id)
		    < std::tie(o.detector_half, o.plane, o.module, o.module_side, o.module_sensor_id);
	}
};

class PndLmdGeometryHelper {
	boost::property_tree::ptree geometry_properties;
	std::vector<std::pair<std::string, bool> > navigation_paths;

	std::map<std::string, PndLmdHitLocationInfo> volume_path_to_hit_info_mapping;
	std::map<int, PndLmdHitLocationInfo> sensor_id_to_hit_info_mapping;

	std::string lmd_root_path;

	TGeoManager* fGeoManager;

	PndLmdGeometryHelper(const std::string& geo_params_config_file_url = "../../parameters/lmd-geo-params.json") :
			fGeoManager(gGeoManager) {
		// load parameters
		read_json(geo_params_config_file_url, geometry_properties);
		auto pt_general = geometry_properties.get_child("general");
		for (boost::property_tree::ptree::value_type &nav_path : pt_general.get_child("navigation_paths")) {
			navigation_paths.push_back(
			    std::make_pair(nav_path.second.get<std::string>("name"),
			        nav_path.second.get<bool>("is_alignable")));
		}

		TString actPath = fGeoManager->GetPath();
		std::stringstream lmd_path;
		fGeoManager->CdTop();
		lmd_path << fGeoManager->GetPath() << "/" << navigation_paths[0].first << "_0";
		lmd_root_path = lmd_path.str();
		if (actPath != "" && actPath != " ") fGeoManager->cd(actPath);

	}

	const PndLmdHitLocationInfo& createMappingEntry(int sensor_id);
	const PndLmdHitLocationInfo& createMappingEntry(const std::string& volume_path);

	PndLmdHitLocationInfo translateVolumePathToHitLocationInfo(const std::string& volume_path) const;

public:
	static PndLmdGeometryHelper& getInstance() {
		static PndLmdGeometryHelper instance;
		return instance;
	}
	virtual ~PndLmdGeometryHelper();

	PndLmdGeometryHelper(const PndLmdGeometryHelper&) = delete;
	void operator=(const PndLmdGeometryHelper&) = delete;

	const PndLmdHitLocationInfo& getHitLocationInfo(const std::string& volume_path);
	// this function with the global sensor id is much faster for lookups
	// so use that if you need speed!

	const PndLmdHitLocationInfo& getHitLocationInfo(int sensor_id);

	static std::vector<int> getAvailableOverlapIDs();
	int getOverlapIdFromSensorIDs(int id1, int id2);

	TVector3 transformPndGlobalToLmdLocal(const TVector3 &vec);
	TVector3 transformPndGlobalToSensor(const TVector3 &vec, int sensorId);

	bool isOverlappingArea(const int id1, const int id2);

	const std::string getPath(unsigned char...);

	const TGeoHMatrix getMatrixPndGlobalToSensor(const int sensorId);
	const TGeoHMatrix getMatrixSensorToPndGlobal(const int sensorId);

	const TGeoHMatrix getMatrixPndGlobalToLmdLocal();
	const TGeoHMatrix getMatrixLmdLocalToPndGlobal();

	// returns all paths to alignable objects, filtered by bools
	    std::vector<std::string> getAllAlignPaths(bool sensors=true, bool modules=false, bool planes=false,
	    bool halfs=false, bool detector=false);

	    std::vector<std::string> getAllAlignableVolumePaths() const;

    };

#endif /* LMD_LMDMC_PNDLMDGEOMETRYHELPER_H_ */
