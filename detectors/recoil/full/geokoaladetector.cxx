#include "geokoaladetector.h"

#include "FairGeoBuilder.h"
#include "FairGeoInterface.h"
#include "FairGeoLoader.h"
#include "FairGeoMedia.h"
#include "FairLogger.h"

#include "TGeoCompositeShape.h"
#include "TGeoCone.h"
#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "TGeoPcon.h"
#include "TGeoTube.h"
#include "TGeoVolume.h"
#include "TMath.h"
#include "TROOT.h"

#include <iostream>
#include <sstream>

using boost::property_tree::ptree;
        
geokoaladetector::geokoaladetector(const ptree& geometry_property_tree_) :
		geometry_property_tree(geometry_property_tree_), gGeoMan(
		    (TGeoManager*) gROOT->FindObject("FAIRGeom")) {
	auto pt_general = geometry_property_tree.get_child("general");
	for (ptree::value_type& nav_path : pt_general.get_child("navigation_paths")) {
		navigation_paths.push_back(
		    std::make_pair(nav_path.second.get<std::string>("name"),
		        nav_path.second.get<bool>("is_alignable")));
	}
}

geokoaladetector::~geokoaladetector() {
}

void geokoaladetector::init(FairGeoLoader* geoLoad) {
	retrieveMaterial(geoLoad);
}
void geokoaladetector::retrieveMaterial(FairGeoLoader* geoLoad) {
	FairGeoMedia* Media2 = geoLoad->getGeoInterface()->getMedia();
	FairGeoBuilder* geobuild2 = geoLoad->getGeoBuilder();

	// retrieve available media
	FairGeoMedium* FairMediumAir = Media2->getMedium("air");
	FairGeoMedium* FairMediumSteel = Media2->getMedium("steel");
	FairGeoMedium* FairMediumAl = Media2->getMedium("Aluminum");
	FairGeoMedium* FairMediumDiamond = Media2->getMedium("HYPdiamond");
	FairGeoMedium* FairMediumSilicon = Media2->getMedium("silicon");      
	FairGeoMedium* FairMediumVacuum = Media2->getMedium("vacuum7");
	FairGeoMedium* FairMediumKapton = Media2->getMedium("kapton");
	FairGeoMedium* FairMediumCopper = Media2->getMedium("copper");
	FairGeoMedium* FairMediumGlassFiber = Media2->getMedium("GlassFiber");

	if (!FairMediumAir || !FairMediumSteel || !FairMediumAl || !FairMediumSilicon
	    || !FairMediumVacuum) {
		LOG(ERROR) << "geokoaladetector::retrieveMaterial: not all media found ";
		return;
	}
	geobuild2->createMedium(FairMediumAir);
	geobuild2->createMedium(FairMediumSteel);
	geobuild2->createMedium(FairMediumAl);
	geobuild2->createMedium(FairMediumSilicon);
	geobuild2->createMedium(FairMediumVacuum);
	geobuild2->createMedium(FairMediumDiamond);
	geobuild2->createMedium(FairMediumCopper);
	geobuild2->createMedium(FairMediumGlassFiber);
}
TGeoVolumeAssembly* geokoaladetector::generateLmdGeometry() const {
	auto pt_general = geometry_property_tree.get_child("general");
	auto pt_sensors = geometry_property_tree.get_child("sensors_vert");
	auto pt_sensorsger = geometry_property_tree.get_child("sensors_ger");
	auto pt_active_part = pt_sensors.get_child("active_part");
	auto pt_vac_box = geometry_property_tree.get_child("vacuum_box");
	double box_dim_zsensor = pt_vac_box.get<double>("dimension_z");
	auto pt_beam_tpiece = geometry_property_tree.get_child("beam_tpiece");
	auto pt_ent_tpiece = pt_beam_tpiece.get_child("entrance_tpiece");
	auto pt_koala_pos = geometry_property_tree.get_child("Koala_pos");
	auto pt_beam_tpiecevert = geometry_property_tree.get_child("beam_tpiecevert");
	auto pt_ent_tpiecevert = pt_beam_tpiecevert.get_child("entrance_tpiecevert");

	double tpvlength(pt_ent_tpiecevert.get<double>("length"));
	double sensor_dim_x(pt_sensors.get<double>("dimension_x"));
	double sensor_dim_y(pt_sensors.get<double>("dimension_y"));
	double upper_sensorger_zg(pt_sensorsger.get<double>("upper_sensor_z"));
	double upper_sensorger_yg(pt_sensorsger.get<double>("upper_sensor_y"));
	double upper_sensor_zg(pt_sensors.get<double>("upper_sensor_z"));
	double upper_sensor_yg(pt_sensors.get<double>("upper_sensor_y"));
	double thickness(pt_sensors.get<double>("thickness"));
	double sensor_placement(pt_sensors.get<double>("sensor_placement")); //is X-Position of Sensors
	double Koala_placement(pt_koala_pos.get<double>("Koala_placement")); // is difference between ip and center of the entrace to KOALA on z-axis was 5.5
	double Koala_height(pt_koala_pos.get<double>("Koala_height")); // 0 means centered
	double active_part_dim_x(pt_active_part.get<double>("dimension_x"));
	double active_part_dim_y(pt_active_part.get<double>("dimension_y"));
	double active_part_offset_x(pt_active_part.get<double>("offset_x"));
	double active_part_offset_y(pt_active_part.get<double>("offset_y"));

	double pipe_bend_segment_phi(pt_general.get<double>("pipe_bend_segment_phi"));

		TGeoRotation* lmd_rotsensof = new TGeoRotation("lmd_rotsensor");
        lmd_rotsensof->RotateX(0.0);
	lmd_rotsensof->RotateY(90.0);
	lmd_rotsensof->RotateZ(0.0);

	TGeoRotation* lmd_rot = new TGeoRotation("lmd_rot");
	lmd_rot->RotateX(0.0);
	lmd_rot->RotateY(0.0);
	//lmd_rot->RotateY(pipe_bend_segment_phi / 3.14 * 180.);
	lmd_rot->RotateZ(0.0);

	double box_center_position_z(
	    pt_general.get<double>("upstream_beampipe_connection_z_position")
	        + geometry_property_tree.get<double>("vacuum_box.dimension_z") / 2.0
	        + geometry_property_tree.get<double>("beam_pipe.entrance_pipe.length"));

	// calculate shift in x from dipole
	double pipe_bend_start_position_z(pt_general.get<double>("pipe_bend_start_position_z"));
	double pipe_bend_radius(pt_general.get<double>("pipe_bend_radius"));

	double dx_from_bending(pipe_bend_radius * (1.0 - std::cos(pipe_bend_segment_phi)));
	double dx_from_displacement_afterwards(
	    (box_center_position_z - pipe_bend_start_position_z
	        - pipe_bend_radius * std::sin(pipe_bend_segment_phi)) * std::tan(pipe_bend_segment_phi));
	double shift_x_from_dipole(dx_from_bending + dx_from_displacement_afterwards);
	
	//moves beampipe to detector
	double detectorposition(geometry_property_tree.get<double>("vacuum_box.dimension_z") / 2.0
	        + geometry_property_tree.get<double>("beam_pipe.entrance_pipe.length"));

	TGeoVolumeAssembly* bottom = new TGeoVolumeAssembly("lmd_top");
		TGeoVolumeAssembly* lmd_detectorp = new TGeoVolumeAssembly(navigation_paths[0].first.c_str());
	TGeoCombiTrans* lmd_detectortrans = new TGeoCombiTrans("lmd_detectortrans", 0.0,
							       0.,detectorposition,0 );

	TGeoCombiTrans* comb_trans_sensor_passive_side= new TGeoCombiTrans("comb_trans_sensor_passive_side", sensor_placement, 3.2 + upper_sensor_yg + Koala_height ,-3.51 +3.7  + Koala_placement + upper_sensor_zg , lmd_rotsensof);

	TGeoCombiTrans* comb_trans_sensor_passive_side_ger= new TGeoCombiTrans("comb_trans_sensor_passive_side_ger", sensor_placement, 3.2 + upper_sensorger_yg + Koala_height ,  13.62 -3.51 + 3.7  + Koala_placement + upper_sensorger_zg   , lmd_rotsensof);


TGeoTranslation* comb_koala_box_trans = new TGeoTranslation("comb_koala_box_trans", tpvlength /2.0 +  geometry_property_tree.get<double>("koalabase_box.dimension_x") /2.0 ,  Koala_height ,  Koala_placement  );

 TGeoTranslation* comb_koala_stand_trans = new TGeoTranslation("comb_koala_stand_trans",tpvlength /2.0 + geometry_property_tree.get<double>("koala_beam_hole.entrance_piece.inner_length")  + geometry_property_tree.get<double>("koalastandpipe.length") /2.0  , Koala_height, Koala_placement);

TGeoTranslation* comb_koala_cham_ent_trans = new TGeoTranslation("comb_koala_cham_ent_trans", tpvlength /2.0 + geometry_property_tree.get<double>("koala_beam_hole.entrance_piece.inner_length")  + geometry_property_tree.get<double>("koalastandpipe.length") + geometry_property_tree.get<double>("koalachamber_ent.ring.length")/2.0 , Koala_height, Koala_placement);

TGeoTranslation* comb_koala_chamber_trans = new TGeoTranslation("comb_koala_chamber_trans", tpvlength /2.0 + geometry_property_tree.get<double>("koala_beam_hole.entrance_piece.inner_length")  + geometry_property_tree.get<double>("koalastandpipe.length") + geometry_property_tree.get<double>("koalachamber_ent.ring.length") + geometry_property_tree.get<double>("koalachamber_ent.entrance_pipe.length")  + geometry_property_tree.get<double>("koalachamber_ent.cone_entrance.length")  + geometry_property_tree.get<double>("koalachamber_ent.cone_exit.length") + geometry_property_tree.get<double>("koalachamber_ent.cone.length") + geometry_property_tree.get<double>("koalachamber.chamber_entrance.length")/2.0 , Koala_height,  Koala_placement);

 TGeoTranslation* comb_koala_inner_chamber_trans = new TGeoTranslation("comb_koala_inner_chamber_trans", tpvlength /2.0 + geometry_property_tree.get<double>("koala_beam_hole.entrance_piece.inner_length")  + geometry_property_tree.get<double>("koalastandpipe.length") + geometry_property_tree.get<double>("koalachamber_ent.ring.length") + geometry_property_tree.get<double>("koalachamber_ent.entrance_pipe.length")  + geometry_property_tree.get<double>("koalachamber_ent.cone_entrance.length")  + geometry_property_tree.get<double>("koalachamber_ent.cone_exit.length") + geometry_property_tree.get<double>("koalachamber_ent.cone.length") + geometry_property_tree.get<double>("koalachamber.chamber_entrance.length") +1.99  , Koala_height, - geometry_property_tree.get<double>("koalachamber.chamber_entrance.inner_radius") + geometry_property_tree.get<double>("koalachamber.chamber_entrance.outer_radius") - geometry_property_tree.get<double>("koalachamber.chamber_entrance.position_hole") + Koala_placement);

 TGeoCombiTrans* comb_koala_sensor_plate_build = new TGeoCombiTrans("comb_koala_sensor_plate_build",  sensor_placement  + geometry_property_tree.get<double>("Koala_sensor_pipe.sensor_box.thickness") + geometry_property_tree.get<double>("Koala_sensor_pipe.plate.thickness")/2.0 , Koala_height,  - geometry_property_tree.get<double>("koalachamber.chamber_entrance.inner_radius") + geometry_property_tree.get<double>("koalachamber.chamber_entrance.outer_radius") - geometry_property_tree.get<double>("koalachamber.chamber_entrance.position_hole") + Koala_placement,lmd_rotsensof );

// was -box_dim_zsensor  - pt_ent_tpiece.get<double>("length") / 2.0 + pt_general.get<double>("upstream_beampipe_connection_z_position") -15.13 -333.28

	

	// create the reference system of the lmd


	// generate vacuum box




	// create lmd box vacuum
	//	 lmd_vol->AddNode(generateBoxVacuum(lmd_vol), 0);
	//generate beam pipe t-Piece
	gGeoMan->SetTopVolume(bottom);
	//lmd_detectorp->AddNode(generateLmdBoxsecondary(),0);
			lmd_detectorp->AddNode(generateBeamTPiece(),0);
				lmd_detectorp->AddNode(generateKoalabase(),0,comb_koala_box_trans);
		lmd_detectorp->AddNode(generateKoalastand(),0,comb_koala_stand_trans);
		lmd_detectorp->AddNode(generateKoalaChamberEnt(),0, comb_koala_cham_ent_trans);
		lmd_detectorp->AddNode(generateKoalaChamber(),0, comb_koala_chamber_trans);
		lmd_detectorp->AddNode(generateKoalaInnerChamber(),0, comb_koala_inner_chamber_trans);
		lmd_detectorp->AddNode(generateKoalaSensorMount(),0,comb_koala_sensor_plate_build );
		lmd_detectorp->AddNode(generateSensorVertBox(),0, comb_trans_sensor_passive_side);
		lmd_detectorp->AddNode(generateSensorGerBox(),0, comb_trans_sensor_passive_side_ger);
	
	// generate sensor
	lmd_detectorp->AddNode(generateSensorVert(),0, comb_trans_sensor_passive_side);
		lmd_detectorp->AddNode(generateSensorGer(),0, comb_trans_sensor_passive_side_ger);
	//	generate secondary vacuum 
	//	lmd_detectorp->AddNode(generateLmdBoxsecondary(), 0);
	

		// place sidedetector in right position
	bottom->AddNode(lmd_detectorp, 0, lmd_rot);

	gGeoMan->CloseGeometry();

	makeNodesAlignable();
	std::cout << "Number of alignable volumes: " << gGeoMan->GetNAlignable() << std::endl;

return bottom;

	
}





TGeoVolume* geokoaladetector::generateLmdBoxsecondary() const {
	auto pt_general = geometry_property_tree.get_child("general");
	auto pt_vac_box = geometry_property_tree.get_child("vacuum_box");

	// general remark: watch out! TGeoShape values are often given has half sizes!
	double box_dim_x(pt_vac_box.get<double>("dimension_x_sec"));
	double box_dim_y(pt_vac_box.get<double>("dimension_y"));
	double box_dim_z(pt_vac_box.get<double>("dimension_z"));
	double box_thickness(pt_vac_box.get<double>("wall_thickness"));

	// the lmd box
	new TGeoBBox("lmd_box_outer", box_dim_x / 2.0 , box_dim_y / 2.0, box_dim_z / 2.0);
	new TGeoBBox("lmd_box_inner", box_dim_x / 2.0 - box_thickness , box_dim_y / 2.0 - box_thickness,
	    box_dim_z / 2.0 - box_thickness);

	// the two beampipe holes
		new TGeoTube("box_hole_upstream", 0.0,
		    geometry_property_tree.get_child("beam_pipe.entrance_pipe").get<double>("inner_radius"),
		    box_thickness / 2.0 + 0.1);  // 0.1 safety margin
	// move the cut pipe upstream
	TGeoTranslation* comb_trans_cut_pipe_upstream = new TGeoTranslation("comb_trans_cut_pipe_upstream", 100.,
	    0., -box_dim_z / 2.0 + box_thickness / 2.0);
	comb_trans_cut_pipe_upstream->RegisterYourself();

		new TGeoTube("box_hole_downstream", 0.0,
		    geometry_property_tree.get_child("beam_pipe.exit_pipe").get<double>("inner_radius"),
		    box_thickness / 2.0 + 0.1);
	// move the cut pipe downstream
	TGeoTranslation* comb_trans_cut_pipe_downstream = new TGeoTranslation("comb_trans_cut_pipe_downstream",
	    100., 0., +box_dim_z / 2.0 - box_thickness / 2.0);
	comb_trans_cut_pipe_downstream->RegisterYourself();

	// the z-plane reinforcement rib
	double rib_thickness = pt_vac_box.get_child("zplane_reinforcement_rib").get<double>("thickness");
	new TGeoBBox("lmd_box_rib", box_dim_x / 2.0 - box_thickness, box_dim_y / 2.0 - box_thickness,
	    rib_thickness / 2.);
	new TGeoTube("rib_hole", 0.0,
	    geometry_property_tree.get_child("beam_pipe.entrance_pipe").get<double>("inner_radius"),
	    rib_thickness / 2.0 + 0.1);
	// move rib upstream
	double rib_inner_distance_to_front_plate =
	    pt_vac_box.get_child("zplane_reinforcement_rib").get<double>("inner_distance_to_box_front_plate");
	TGeoTranslation* comb_trans_rib = new TGeoTranslation("comb_trans_rib", 100., 0.,
	    -box_dim_z / 2.0 + box_thickness + rib_inner_distance_to_front_plate + rib_thickness / 2.0);
	comb_trans_rib->RegisterYourself();

	// the horizontal clash plates for the detector halves
	auto pt_clash_plates = geometry_property_tree.get_child(
	    "vacuum_box.horizontal_detector_half_clash_plates");
	double clash_plate_dim_x = pt_clash_plates.get<double>("width");
	double clash_plate_dim_y = pt_clash_plates.get<double>("thickness");
	double clash_plate_dim_z = box_dim_z - rib_inner_distance_to_front_plate - rib_thickness
	    - box_thickness;

	double origin_left[3] =
	    { -box_dim_x / 2.0 + clash_plate_dim_x / 2.0 + box_thickness, 0., -box_dim_z / 2.0 + box_thickness
	        + rib_inner_distance_to_front_plate + rib_thickness + clash_plate_dim_z / 2.0 };
	new TGeoBBox("lmd_box_clash_plate_left", clash_plate_dim_x / 2.0, clash_plate_dim_y / 2.0,
	    clash_plate_dim_z / 2.0, origin_left);
	double origin_right[3] =
	    { +box_dim_x / 2.0 - clash_plate_dim_x / 2.0 - box_thickness, 0., -box_dim_z / 2.0 + box_thickness
	        + rib_inner_distance_to_front_plate + rib_thickness + clash_plate_dim_z / 2.0 };
	new TGeoBBox("lmd_box_clash_plate_right", clash_plate_dim_x / 2.0, clash_plate_dim_y / 2.0,
	    clash_plate_dim_z / 2.0, origin_right);

	// compose all the parts into one luminosity vacuum box
	TGeoCompositeShape* shape_lmd_box = new TGeoCompositeShape("shape_lmd_box",
	    "(lmd_box_outer-lmd_box_inner)"
								   /* + ((lmd_box_rib-rib_hole):comb_trans_rib))"*/
								    "-box_hole_upstream:comb_trans_cut_pipe_upstream"
			    "-box_hole_downstream:comb_trans_cut_pipe_downstream"
			    "+lmd_box_clash_plate_left+lmd_box_clash_plate_right");

		TGeoVolume* lmd_vol_box_sec = new TGeoVolume("lmd_vol_box_sec", shape_lmd_box, gGeoMan->GetMedium("steel"));
	lmd_vol_box_sec->SetLineColor(11);

	return lmd_vol_box_sec;
}



TGeoVolume* geokoaladetector::generateSensorVert() const {
  TGeoVolumeAssembly* lmd_vol_sensor_vert = new TGeoVolumeAssembly("lmd_vol_sensor_vert");
  TGeoVolumeAssembly* sensor_vert = new TGeoVolumeAssembly("sensor_vert");
  TGeoVolumeAssembly* sensor_box_vert = new TGeoVolumeAssembly("sensor_box_vert");

	auto pt_general = geometry_property_tree.get_child("general");
	auto pt_sensors = geometry_property_tree.get_child("sensors_vert");
	auto pt_active_part = pt_sensors.get_child("active_part");
	auto pt_vac_box = geometry_property_tree.get_child("vacuum_box");
	double box_dim_zsensor = pt_vac_box.get<double>("dimension_z");
	auto pt_beam_tpiece = geometry_property_tree.get_child("beam_tpiece");
	auto pt_ent_tpiece = pt_beam_tpiece.get_child("entrance_tpiece");
	auto pt_sensor_pipe = geometry_property_tree.get_child("Koala_sensor_pipe");
	auto pt_sensor_box =  pt_sensor_pipe.get_child("sensor_box");

	double sensor_dim_x(pt_sensors.get<double>("dimension_x"));
	double sensor_dim_y(pt_sensors.get<double>("dimension_y"));
	double thickness(pt_sensors.get<double>("thickness"));
	double sensor_placement(pt_sensors.get<double>("sensor_placement")); 
	double lower_sensor_y(pt_sensors.get<double>("lower_sensor_y"));
	double upper_sensor_y(pt_sensors.get<double>("upper_sensor_y"));
	double lower_sensor_z(pt_sensors.get<double>("lower_sensor_z"));
	double upper_sensor_z(pt_sensors.get<double>("upper_sensor_z"));

	double active_part_dim_x(pt_active_part.get<double>("dimension_x"));
	double active_part_dim_y(pt_active_part.get<double>("dimension_y"));
	double active_part_offset_x(pt_active_part.get<double>("offset_x"));
	double active_part_offset_y(pt_active_part.get<double>("offset_y"));

	double sensor_box_dim_x(pt_sensor_box.get<double>("x-length"));
	double sensor_box_dim_y(pt_sensor_box.get<double>("y-length"));
	double sensor_box_thickness(pt_sensor_box.get<double>("thickness"));

	new TGeoBBox("sensor_full_centered_side", sensor_dim_x / 2.0, sensor_dim_y / 2.0, thickness / 2.0);
	
	TGeoBBox* sensor_active_centered_side = new TGeoBBox("sensor_active_centered_side", active_part_dim_x / 2.0,
	    active_part_dim_y / 2.0, thickness / 2.0);
	new TGeoBBox("sensor_active_centered_cutout_side", active_part_dim_x / 2.0, active_part_dim_y / 2.0,
	    thickness / 2.0 + 0.1);

        

	new TGeoBBox("Sensor_box", sensor_box_dim_x / 2.0 , sensor_box_dim_y / 2.0 ,
		     ( (sensor_box_thickness  - (thickness) )/2.0 ));

	TGeoTranslation* trans_sensor_active_cutout_side = new TGeoTranslation("trans_sensor_active_cutout_side",
									  -sensor_dim_x / 2.0 + active_part_dim_x / 2.0 + active_part_offset_x , -sensor_dim_y / 2.0 + active_part_dim_y / 2.0 + active_part_offset_y,0.0);
	trans_sensor_active_cutout_side->RegisterYourself();

TGeoTranslation* mvsecondsensor = new TGeoTranslation("mvsecondsensor",
						      5.28 + lower_sensor_z - upper_sensor_z ,-6.57 +lower_sensor_y - upper_sensor_y,0.0);
	mvsecondsensor->RegisterYourself();

	TGeoTranslation* mvsensorbox = new TGeoTranslation("mvsensorbox",
						      0.0,0.0, sensor_box_thickness / 2.0 + (thickness/4.0) );
	mvsensorbox->RegisterYourself();
	
	TGeoCompositeShape* sensor_passive_centered_side = new TGeoCompositeShape("sensor_passive_centered_side",
	    "(sensor_full_centered_side-sensor_active_centered_cutout_side:trans_sensor_active_cutout_side)");

	TGeoCompositeShape* sensor_box_s = new TGeoCompositeShape("sensor_box_s",
	    "(Sensor_box:mvsensorbox - sensor_active_centered_cutout_side:trans_sensor_active_cutout_side )");

	TGeoVolume* passive_sensor_volume_side = new TGeoVolume("LumPassiveRect_side", sensor_passive_centered_side,
	    gGeoMan->GetMedium("silicon"));
	passive_sensor_volume_side->SetLineColor(kYellow);
	

	TGeoVolume* active_sensor_volume_side = new TGeoVolume("KoalaActivePixel",
	    sensor_active_centered_side, gGeoMan->GetMedium("silicon"));
	active_sensor_volume_side->SetLineColor(kViolet);

	TGeoVolume* KoalaSensorBox = new TGeoVolume("KoalaSensorBox",sensor_box_s, gGeoMan->GetMedium("steel"));
	KoalaSensorBox->SetLineColor(kGreen);
	
        sensor_vert->AddNode(active_sensor_volume_side, 0, trans_sensor_active_cutout_side);
        sensor_vert->AddNode(passive_sensor_volume_side, 0);
	//sensor_box_vert->AddNode(KoalaSensorBox, 0 );
	//sensor_vert->AddNode(sensor_box_vert, 0);

	lmd_vol_sensor_vert->AddNode(sensor_vert,0);
	lmd_vol_sensor_vert->AddNode(sensor_vert,1,mvsecondsensor);
        
	return lmd_vol_sensor_vert;
}








TGeoVolume* geokoaladetector::generateSensorGer() const {
  TGeoVolumeAssembly* lmd_vol_sensor_ger = new TGeoVolumeAssembly("lmd_vol_sensor_ger");
  TGeoVolumeAssembly* sensor_ger = new TGeoVolumeAssembly("sensor_ger");
  TGeoVolumeAssembly* sensor_box_vert_ger= new TGeoVolumeAssembly("sensor_box_vert_ger");

	auto pt_general = geometry_property_tree.get_child("general");
	auto pt_sensorsger = geometry_property_tree.get_child("sensors_ger");
	auto pt_active_partger = pt_sensorsger.get_child("active_partger");
	auto pt_vac_box = geometry_property_tree.get_child("vacuum_box");
	double box_dim_zsensor = pt_vac_box.get<double>("dimension_z");
	auto pt_beam_tpiece = geometry_property_tree.get_child("beam_tpiece");
	auto pt_ent_tpiece = pt_beam_tpiece.get_child("entrance_tpiece");
	auto pt_sensor_pipe_ger = geometry_property_tree.get_child("Koala_sensor_pipe");
	auto pt_sensor_box_ger =  pt_sensor_pipe_ger.get_child("sensor_box");

	double sensor_dim_xger(pt_sensorsger.get<double>("dimension_xger"));
	double sensor_dim_yger(pt_sensorsger.get<double>("dimension_yger"));
	double thicknessger(pt_sensorsger.get<double>("thicknessger"));
	double lower_sensorger_y(pt_sensorsger.get<double>("lower_sensor_y"));
	double upper_sensorger_y(pt_sensorsger.get<double>("upper_sensor_y"));
	double lower_sensorger_z(pt_sensorsger.get<double>("lower_sensor_z"));
	double upper_sensorger_z(pt_sensorsger.get<double>("upper_sensor_z"));
	double sensor_placement(pt_sensorsger.get<double>("sensor_placement")); 

	double active_part_dim_xger(pt_active_partger.get<double>("dimension_xger"));
	double active_part_dim_yger(pt_active_partger.get<double>("dimension_yger"));
	double active_part_offset_xger(pt_active_partger.get<double>("offset_xger"));
	double active_part_offset_yger(pt_active_partger.get<double>("offset_yger"));

	double sensor_box_dim_x_ger(pt_sensor_box_ger.get<double>("x-length"));
	double sensor_box_dim_y_ger(pt_sensor_box_ger.get<double>("y-length"));
	double sensor_box_thickness_ger(pt_sensor_box_ger.get<double>("thickness"));

	new TGeoBBox("sensor_full_centered_side_ger", sensor_dim_xger / 2.0, sensor_dim_yger / 2.0, thicknessger / 2.0);
	
	TGeoBBox* sensor_active_centered_side_ger = new TGeoBBox("sensor_active_centered_side_ger", active_part_dim_xger / 2.0,
	    active_part_dim_yger / 2.0, thicknessger / 2.0);
	new TGeoBBox("sensor_active_centered_cutout_side_ger", active_part_dim_xger / 2.0, active_part_dim_yger / 2.0,
	    thicknessger / 2.0 + 0.1);

	new TGeoBBox("Sensor_box_ger", sensor_box_dim_x_ger / 2.0 , sensor_box_dim_y_ger / 2.0 ,
		     ( (sensor_box_thickness_ger  - (thicknessger) )/2.0 ));

	TGeoTranslation* trans_sensor_active_cutout_side_ger = new TGeoTranslation("trans_sensor_active_cutout_side_ger",
									  -sensor_dim_xger / 2.0 + active_part_dim_xger / 2.0 + active_part_offset_xger , -sensor_dim_yger / 2.0 + active_part_dim_yger / 2.0 + active_part_offset_yger,0.0);
	trans_sensor_active_cutout_side_ger->RegisterYourself();

TGeoTranslation* mvsecondsensorger = new TGeoTranslation("mvsecondsensorger",
						     +6.84 + lower_sensorger_z - upper_sensorger_z,-6.4 + lower_sensorger_y - upper_sensorger_y,0.0);
	mvsecondsensorger->RegisterYourself();

	TGeoTranslation* mvsensorboxger = new TGeoTranslation("mvsensorboxger",
						      0.0,0.0, sensor_box_thickness_ger / 2.0 + (thicknessger/4.0) );
	mvsensorboxger->RegisterYourself();

	
	TGeoCompositeShape* sensor_passive_centered_side_ger = new TGeoCompositeShape("sensor_passive_centered_side_ger",
	    "(sensor_full_centered_side_ger-sensor_active_centered_cutout_side_ger:trans_sensor_active_cutout_side_ger)");


	TGeoCompositeShape* sensor_box_s_ger = new TGeoCompositeShape("sensor_box_s_ger",
	    "(Sensor_box_ger:mvsensorboxger - sensor_active_centered_cutout_side_ger:trans_sensor_active_cutout_side_ger )");

	TGeoVolume* passive_sensor_volume_side_ger = new TGeoVolume("LumPassiveRect_side_ger", sensor_passive_centered_side_ger,
	    gGeoMan->GetMedium("silicon"));
	passive_sensor_volume_side_ger->SetLineColor(kYellow);

	TGeoVolume* KoalaSensorBoxGer = new TGeoVolume("KoalaSensorBoxGer",sensor_box_s_ger, gGeoMan->GetMedium("steel"));
	KoalaSensorBoxGer->SetLineColor(kGreen);
	

	TGeoVolume* active_sensor_volume_side_ger = new TGeoVolume("KoalaActive_gerPixel",
	    sensor_active_centered_side_ger, gGeoMan->GetMedium("silicon"));
	active_sensor_volume_side_ger->SetLineColor(kViolet);
	
        sensor_ger->AddNode(active_sensor_volume_side_ger, 0, trans_sensor_active_cutout_side_ger);
        sensor_ger->AddNode(passive_sensor_volume_side_ger, 0);
	//	sensor_box_vert_ger->AddNode(KoalaSensorBoxGer, 0 );
	//sensor_ger->AddNode(sensor_box_vert_ger, 0);

	lmd_vol_sensor_ger->AddNode(sensor_ger,0);
	lmd_vol_sensor_ger->AddNode(sensor_ger,1,mvsecondsensorger);
        
	return lmd_vol_sensor_ger;
}


TGeoVolume* geokoaladetector::generateSensorVertBox() const {
  TGeoVolumeAssembly* lmd_vol_sensor_vert_box = new TGeoVolumeAssembly("lmd_vol_sensor_vert_box");
  TGeoVolumeAssembly* sensor_vert_box = new TGeoVolumeAssembly("sensor_vert_box");
  TGeoVolumeAssembly* sensor_box_vert_box = new TGeoVolumeAssembly("sensor_box_vert_box");

	auto pt_general = geometry_property_tree.get_child("general");
	auto pt_sensors = geometry_property_tree.get_child("sensors_vert");
	auto pt_active_part = pt_sensors.get_child("active_part");
	auto pt_vac_box = geometry_property_tree.get_child("vacuum_box");
	double box_dim_zsensor_box = pt_vac_box.get<double>("dimension_z");
	auto pt_beam_tpiece = geometry_property_tree.get_child("beam_tpiece");
	auto pt_ent_tpiece = pt_beam_tpiece.get_child("entrance_tpiece");
	auto pt_sensor_pipe = geometry_property_tree.get_child("Koala_sensor_pipe");
	auto pt_sensor_box =  pt_sensor_pipe.get_child("sensor_box");

	double sensor_dim_x_box(pt_sensors.get<double>("dimension_x"));
	double sensor_dim_y_box(pt_sensors.get<double>("dimension_y"));
	double thickness_box(pt_sensors.get<double>("thickness"));
	double sensor_placement_box(pt_sensors.get<double>("sensor_placement")); 
	double lower_sensor_y_box(pt_sensors.get<double>("lower_sensor_y"));
	double upper_sensor_y_box(pt_sensors.get<double>("upper_sensor_y"));
	double lower_sensor_z_box(pt_sensors.get<double>("lower_sensor_z"));
	double upper_sensor_z_box(pt_sensors.get<double>("upper_sensor_z"));

	double active_part_dim_x_box(pt_active_part.get<double>("dimension_x"));
	double active_part_dim_y_box(pt_active_part.get<double>("dimension_y"));
	double active_part_offset_x_box(pt_active_part.get<double>("offset_x"));
	double active_part_offset_y_box(pt_active_part.get<double>("offset_y"));

	double sensor_box_dim_x_box(pt_sensor_box.get<double>("x-length"));
	double sensor_box_dim_y_box(pt_sensor_box.get<double>("y-length"));
	double sensor_box_thickness_box(pt_sensor_box.get<double>("thickness"));

	new TGeoBBox("sensor_full_centered_side_box", sensor_dim_x_box / 2.0, sensor_dim_y_box / 2.0, thickness_box / 2.0);
	
	TGeoBBox* sensor_active_centered_side_box = new TGeoBBox("sensor_active_centered_side_box", active_part_dim_x_box / 2.0,
	    active_part_dim_y_box / 2.0, thickness_box / 2.0);
	new TGeoBBox("sensor_active_centered_cutout_side_box", active_part_dim_x_box / 2.0, active_part_dim_y_box / 2.0,
	    thickness_box / 2.0 + 0.1);

        

	new TGeoBBox("Sensor_box_box", sensor_box_dim_x_box / 2.0 , sensor_box_dim_y_box / 2.0 ,
		     ( (sensor_box_thickness_box  - (thickness_box) )/2.0 ));

	TGeoTranslation* trans_sensor_active_cutout_side_box = new TGeoTranslation("trans_sensor_active_cutout_side_box",
									  -sensor_dim_x_box / 2.0 + active_part_dim_x_box / 2.0 + active_part_offset_x_box , -sensor_dim_y_box / 2.0 + active_part_dim_y_box / 2.0 + active_part_offset_y_box,0.0);
	trans_sensor_active_cutout_side_box->RegisterYourself();

TGeoTranslation* mvsecondsensor_box = new TGeoTranslation("mvsecondsensor_box",
						      5.28 + lower_sensor_z_box - upper_sensor_z_box ,-6.57 +lower_sensor_y_box - upper_sensor_y_box,0.0);
	mvsecondsensor_box->RegisterYourself();

	TGeoTranslation* mvsensorbox_box = new TGeoTranslation("mvsensorbox_box",
						      0.0,0.0, sensor_box_thickness_box / 2.0 + (thickness_box/4.0) );
	mvsensorbox_box->RegisterYourself();
	
	TGeoCompositeShape* sensor_passive_centered_side_box = new TGeoCompositeShape("sensor_passive_centered_side_box",
	    "(sensor_full_centered_side_box-sensor_active_centered_cutout_side_box:trans_sensor_active_cutout_side_box)");

	TGeoCompositeShape* sensor_box_s_box = new TGeoCompositeShape("sensor_box_s_box",
	    "(Sensor_box_box:mvsensorbox_box - sensor_active_centered_cutout_side_box:trans_sensor_active_cutout_side_box )");



	TGeoVolume* KoalaSensorBox_box = new TGeoVolume("KoalaSensorBox_box",sensor_box_s_box, gGeoMan->GetMedium("steel"));
	KoalaSensorBox_box->SetLineColor(kGreen);
	
     
	sensor_box_vert_box->AddNode(KoalaSensorBox_box, 0 );
	sensor_vert_box->AddNode(sensor_box_vert_box, 0);

	lmd_vol_sensor_vert_box->AddNode(sensor_vert_box,0);
	lmd_vol_sensor_vert_box->AddNode(sensor_vert_box,1,mvsecondsensor_box);
        
	return lmd_vol_sensor_vert_box;
}








TGeoVolume* geokoaladetector::generateSensorGerBox() const {
  TGeoVolumeAssembly* lmd_vol_sensor_ger_box = new TGeoVolumeAssembly("lmd_vol_sensor_ger_box");
  TGeoVolumeAssembly* sensor_ger_box = new TGeoVolumeAssembly("sensor_ger_box");
  TGeoVolumeAssembly* sensor_box_vert_ger_box= new TGeoVolumeAssembly("sensor_box_vert_ger_box");

	auto pt_general = geometry_property_tree.get_child("general");
	auto pt_sensorsger = geometry_property_tree.get_child("sensors_ger");
	auto pt_active_partger = pt_sensorsger.get_child("active_partger");
	auto pt_vac_box = geometry_property_tree.get_child("vacuum_box");
	double box_dim_zsensor = pt_vac_box.get<double>("dimension_z");
	auto pt_beam_tpiece = geometry_property_tree.get_child("beam_tpiece");
	auto pt_ent_tpiece = pt_beam_tpiece.get_child("entrance_tpiece");
	auto pt_sensor_pipe_ger = geometry_property_tree.get_child("Koala_sensor_pipe");
	auto pt_sensor_box_ger =  pt_sensor_pipe_ger.get_child("sensor_box");

	double sensor_dim_xger(pt_sensorsger.get<double>("dimension_xger"));
	double sensor_dim_yger(pt_sensorsger.get<double>("dimension_yger"));
	double thicknessger(pt_sensorsger.get<double>("thicknessger"));
	double lower_sensorger_y(pt_sensorsger.get<double>("lower_sensor_y"));
	double upper_sensorger_y(pt_sensorsger.get<double>("upper_sensor_y"));
	double lower_sensorger_z(pt_sensorsger.get<double>("lower_sensor_z"));
	double upper_sensorger_z(pt_sensorsger.get<double>("upper_sensor_z"));
	double sensor_placement(pt_sensorsger.get<double>("sensor_placement")); 

	double active_part_dim_xger(pt_active_partger.get<double>("dimension_xger"));
	double active_part_dim_yger(pt_active_partger.get<double>("dimension_yger"));
	double active_part_offset_xger(pt_active_partger.get<double>("offset_xger"));
	double active_part_offset_yger(pt_active_partger.get<double>("offset_yger"));

	double sensor_box_dim_x_ger(pt_sensor_box_ger.get<double>("x-length"));
	double sensor_box_dim_y_ger(pt_sensor_box_ger.get<double>("y-length"));
	double sensor_box_thickness_ger(pt_sensor_box_ger.get<double>("thickness"));

	new TGeoBBox("sensor_full_centered_side_ger", sensor_dim_xger / 2.0, sensor_dim_yger / 2.0, thicknessger / 2.0);
	
	TGeoBBox* sensor_active_centered_side_ger = new TGeoBBox("sensor_active_centered_side_ger", active_part_dim_xger / 2.0,
	    active_part_dim_yger / 2.0, thicknessger / 2.0);
	new TGeoBBox("sensor_active_centered_cutout_side_ger", active_part_dim_xger / 2.0, active_part_dim_yger / 2.0,
	    thicknessger / 2.0 + 0.1);

	new TGeoBBox("Sensor_box_ger", sensor_box_dim_x_ger / 2.0 , sensor_box_dim_y_ger / 2.0 ,
		     ( (sensor_box_thickness_ger  - (thicknessger) )/2.0 ));

	TGeoTranslation* trans_sensor_active_cutout_side_ger = new TGeoTranslation("trans_sensor_active_cutout_side_ger",
									  -sensor_dim_xger / 2.0 + active_part_dim_xger / 2.0 + active_part_offset_xger , -sensor_dim_yger / 2.0 + active_part_dim_yger / 2.0 + active_part_offset_yger,0.0);
	trans_sensor_active_cutout_side_ger->RegisterYourself();

TGeoTranslation* mvsecondsensorger = new TGeoTranslation("mvsecondsensorger",
						     +6.84 + lower_sensorger_z - upper_sensorger_z,-6.4 + lower_sensorger_y - upper_sensorger_y,0.0);
	mvsecondsensorger->RegisterYourself();

	TGeoTranslation* mvsensorboxger = new TGeoTranslation("mvsensorboxger",
						      0.0,0.0, sensor_box_thickness_ger / 2.0 + (thicknessger/4.0) );
	mvsensorboxger->RegisterYourself();

	
	TGeoCompositeShape* sensor_passive_centered_side_ger = new TGeoCompositeShape("sensor_passive_centered_side_ger",
	    "(sensor_full_centered_side_ger-sensor_active_centered_cutout_side_ger:trans_sensor_active_cutout_side_ger)");


	TGeoCompositeShape* sensor_box_s_ger = new TGeoCompositeShape("sensor_box_s_ger",
	    "(Sensor_box_ger:mvsensorboxger - sensor_active_centered_cutout_side_ger:trans_sensor_active_cutout_side_ger )");

	TGeoVolume* passive_sensor_volume_side_ger = new TGeoVolume("LumPassiveRect_side_ger", sensor_passive_centered_side_ger,
	    gGeoMan->GetMedium("silicon"));
	passive_sensor_volume_side_ger->SetLineColor(kYellow);

	TGeoVolume* KoalaSensorBoxGer = new TGeoVolume("KoalaSensorBoxGer",sensor_box_s_ger, gGeoMan->GetMedium("steel"));
	KoalaSensorBoxGer->SetLineColor(kGreen);
	

	TGeoVolume* active_sensor_volume_side_ger = new TGeoVolume("KoalaActive_gerPixel",
	    sensor_active_centered_side_ger, gGeoMan->GetMedium("silicon"));
	active_sensor_volume_side_ger->SetLineColor(kViolet);
	
        
		sensor_box_vert_ger_box->AddNode(KoalaSensorBoxGer, 0 );
	sensor_ger_box->AddNode(sensor_box_vert_ger_box, 0);

	lmd_vol_sensor_ger_box->AddNode(sensor_ger_box,0);
	lmd_vol_sensor_ger_box->AddNode(sensor_ger_box,1,mvsecondsensorger);
        
	return lmd_vol_sensor_ger_box;
}





TGeoVolume* geokoaladetector::generateBoxVacuum(const TGeoVolume* lmd_vol) const {
	auto pt_vac_box = geometry_property_tree.get_child("vacuum_box");
	// general remark: watch out! TGeoShape values are often given has half sizes!
	double box_dim_x(pt_vac_box.get<double>("dimension_x"));
	double box_dim_y(pt_vac_box.get<double>("dimension_y"));
	double box_dim_z(pt_vac_box.get<double>("dimension_z"));
	double box_thickness(pt_vac_box.get<double>("wall_thickness"));

	new TGeoBBox("lmd_box_vac", box_dim_x / 2.0 - box_thickness, box_dim_y / 2.0 - box_thickness,
	    box_dim_z / 2.0 - box_thickness);

	std::stringstream ss;
	ss << "lmd_box_vac";
	// recursively loop over all nodes in the assembly and subtract all these
	// nodes
	for (int i = 0; i < lmd_vol->GetNdaughters(); ++i) {
		recursiveNodeSubtraction(ss, lmd_vol->GetNode(i));
	}

	TGeoCompositeShape* shape_box_vac = new TGeoCompositeShape("shape_box_vac", ss.str().c_str());

	std::cout << ss.str() << std::endl;
	TGeoVolume* lmd_vol_vac = new TGeoVolume("lmd_vol_vac", shape_box_vac, gGeoMan->GetMedium("vacuum7"));
	lmd_vol_vac->SetLineColor(kCyan);
	lmd_vol_vac->SetTransparency(50);
	return lmd_vol_vac;
}



TGeoVolume* geokoaladetector::generateBeamTPiece() const {
  TGeoVolumeAssembly* lmd_beam_tpiece = new TGeoVolumeAssembly("lmd_beam_tpiece"); //Endergebnis
  
  
  auto pt_general = geometry_property_tree.get_child("general");
  auto pt_vac_box = geometry_property_tree.get_child("vacuum_box");
  auto pt_beam_tpiece = geometry_property_tree.get_child("beam_tpiece");
  auto pt_beam_tpiecevert = geometry_property_tree.get_child("beam_tpiecevert");
  auto pt_koala_pos = geometry_property_tree.get_child("Koala_pos");
  auto pt_ent_tpiece = pt_beam_tpiece.get_child("entrance_tpiece");
  auto pt_ent_tpiecevert = pt_beam_tpiecevert.get_child("entrance_tpiecevert");
  auto pt_close_tpiecevert = pt_beam_tpiecevert.get_child("close_tpiecevert");
  double Koala_placement(pt_koala_pos.get<double>("Koala_placement"));
  double beam_pipe_length( pt_ent_tpiece.get<double>("length"));
  double beam_pipe_inner_radius( pt_ent_tpiece.get<double>("inner_radius"));
  double beam_pipe_thickness( pt_ent_tpiece.get<double>("thickness"));
  double vert_pipe_length(  pt_ent_tpiecevert.get<double>("length"));
  double vert_pipe_cutout( pt_ent_tpiecevert.get<double>("length_cutout"));
  double vert_pipe_radius(  pt_ent_tpiecevert.get<double>("radius"));
  double vert_pipe_inner_radius(  pt_ent_tpiecevert.get<double>("inner_radius"));
   double lmd_distance( pt_general.get<double>("upstream_beampipe_connection_z_position"));
  double vert_pipe_length_close(  pt_close_tpiecevert.get<double>("length"));
  double vert_pipe_radius_close(  pt_close_tpiecevert.get<double>("radius"));
  
  
  // general remark: watch out! TGeoShape values are often given has half sizes!
  double box_dim_x(pt_vac_box.get<double>("dimension_x_sec"));
  double box_dim_y(pt_vac_box.get<double>("dimension_y"));
  double box_dim_z(pt_vac_box.get<double>("dimension_z"));
  double box_thickness(pt_vac_box.get<double>("wall_thickness"));
  
  new TGeoBBox("beam_pipe_outer_box", box_dim_x / 2.0 , box_dim_y / 2.0, box_dim_z / 2.0);
  new TGeoBBox("beam_pipe_inner_box", box_dim_x / 2.0 -box_thickness  , box_dim_y / 2.0 - box_thickness, box_dim_z / 2.0 - box_thickness);
  
  TGeoTube* beampipe = new TGeoTube("beampipe",  beam_pipe_inner_radius, beam_pipe_inner_radius + beam_pipe_thickness , beam_pipe_length/ 2.0);
  TGeoTube* box_cutout = new TGeoTube("box_cutout", 0.0 , beam_pipe_inner_radius + beam_pipe_thickness , beam_pipe_length/ 2.0);
  
  TGeoTube* vert_box_cutout = new TGeoTube("vert_box_cutout", 0.0 , vert_pipe_radius  , vert_pipe_cutout/ 2.0);

  TGeoTube* vert_pipe = new TGeoTube("vert_pipe", vert_pipe_inner_radius , vert_pipe_radius, vert_pipe_length/ 2.0);

   TGeoTube* vert_pipe_close = new TGeoTube("vert_pipe_close", 0.0 , vert_pipe_radius_close  , vert_pipe_length_close / 2.0);
  
  TGeoRotation* lmd_rot = new TGeoRotation("lmd_rot");
  lmd_rot->RotateX(0.0);
  lmd_rot->RotateY(90.0);
  lmd_rot->RotateZ(0.0);
  
  
  TGeoCombiTrans* comb_trans_vert_pipe = new TGeoCombiTrans("comb_trans_vert_pipe", 0.  ,  0.,  5.5  , lmd_rot);

  TGeoCombiTrans* comb_trans_vert_pipe_close = new TGeoCombiTrans("comb_trans_vert_pipe_close",  - vert_pipe_length_close / 2.0 - vert_pipe_length/ 2.0 ,  0.,  5.5  , lmd_rot);

  TGeoTranslation* comb_trans_beampipe = new TGeoTranslation("comb_trans_beampipe", 0.  ,  0., lmd_distance - (beam_pipe_length/ 2.0)  );
  
  comb_trans_vert_pipe->RegisterYourself();
  comb_trans_beampipe->RegisterYourself();
  
  
  TGeoCompositeShape* beam_pipe = new TGeoCompositeShape("beam_pipe","(beampipe:comb_trans_beampipe) - ( vert_box_cutout:comb_trans_vert_pipe)");
  
  TGeoCompositeShape* beam_pipe_box = new TGeoCompositeShape("beam_pipe_box","( vert_pipe:comb_trans_vert_pipe) - (box_cutout)");

   
 

  
  
  
  TGeoVolume* beam_pipe_box_v = new TGeoVolume("beam_pipe_box_v", beam_pipe_box, gGeoMan->GetMedium("steel"));
  
  TGeoVolume* beam_pipe_v = new TGeoVolume("beam_pipe_v", beam_pipe, gGeoMan->GetMedium("steel"));
  beam_pipe_v->SetLineColor(kBlue);

  TGeoVolume* vert_pipe_close_v = new TGeoVolume("vert_pipe_close_v", vert_pipe_close, gGeoMan->GetMedium("steel"));
  beam_pipe_v->SetLineColor(kBlue);
  
   lmd_beam_tpiece->AddNode(beam_pipe_box_v,0);
   lmd_beam_tpiece->AddNode(beam_pipe_v,0);
   lmd_beam_tpiece->AddNode(vert_pipe_close_v,0, comb_trans_vert_pipe_close);
  
  
  
  
  return lmd_beam_tpiece;
}

TGeoVolume* geokoaladetector::generateKoalabase() const {
 TGeoVolumeAssembly* Koala_entrance = new TGeoVolumeAssembly("Koala_entrance"); //Endergebnis
  auto pt_general = geometry_property_tree.get_child("general");
  auto pt_vac_box = geometry_property_tree.get_child("vacuum_box");
  auto pt_base_box = geometry_property_tree.get_child("koalabase_box");
  auto pt_koala_beam = geometry_property_tree.get_child("koala_beam_hole");
  auto pt_koala_ent_piece = pt_koala_beam.get_child("entrance_piece");
  auto pt_koala_exit_piece = pt_koala_beam.get_child("exit_piece");


	// general remark: watch out! TGeoShape values are often given has half sizes!
	double box_dim_x(pt_base_box.get<double>("dimension_x"));
	double box_dim_y(pt_base_box.get<double>("dimension_y"));
	double box_dim_z(pt_base_box.get<double>("dimension_z"));
	double beam_pipe_distance(pt_vac_box.get<double>("dimension_x_sec"));
	double box_holedist_z(pt_base_box.get<double>("hole_distance"));
	double koala_inner_radius(pt_koala_ent_piece.get<double>("inner_radius"));
	double koala_outer_radius_ent(pt_koala_ent_piece.get<double>("outer_radius"));
	double koala_outer_radius_exit(pt_koala_exit_piece.get<double>("outer_radius"));

	new TGeoBBox("koala_base_box", box_dim_x / 2.0 , box_dim_y / 2.0, box_dim_z / 2.0);    

	TGeoTube* koalainnertube = new TGeoTube("koalainnertube", 0,
	    koala_inner_radius,
	    pt_koala_ent_piece.get<double>("inner_length") / 2.0);
	
		TGeoTube* koala_base_entrancetube = new TGeoTube("koala_base_entrancetube", koala_inner_radius,
							 koala_outer_radius_ent,
							 pt_koala_ent_piece.get<double>("outer_length")/ 2.0);
	
	TGeoTube* koala_base_exittube = new TGeoTube("koala_base_exittube", koala_inner_radius,
						     koala_outer_radius_exit,
						     pt_koala_exit_piece.get<double>("outer_length") / 2.0);
	
	
       

	TGeoRotation* koala_rot = new TGeoRotation("koala_rot");
	koala_rot->RotateX(0.0);
	koala_rot->RotateY(90.0);
	koala_rot->RotateZ(0.0);

	TGeoCombiTrans* comb_trans_koala_base = new TGeoCombiTrans("comb_trans_koala_base", 0.  ,  0.,0. , koala_rot);
	TGeoTranslation* comb_trans_platepos = new TGeoTranslation("comb_trans_platepos", 0.  ,  0., + box_dim_z /2.0 -  box_holedist_z -5 );
		TGeoCombiTrans* comb_trans_koala_base_ent = new TGeoCombiTrans("comb_trans_koala_base_ent", box_dim_x /2.0 +  pt_koala_ent_piece.get<double>("outer_length")/ 2.0 ,  0., 0. , koala_rot);
		TGeoCombiTrans* comb_trans_koala_base_exit = new TGeoCombiTrans("comb_trans_koala_base_exit",box_dim_x /2.0 +  pt_koala_ent_piece.get<double>("outer_length") + pt_koala_exit_piece.get<double>("outer_length")/ 2.0 ,  0., 0. , koala_rot);

	comb_trans_koala_base->RegisterYourself();
	comb_trans_platepos->RegisterYourself();
	comb_trans_koala_base_ent->RegisterYourself();
	comb_trans_koala_base_exit->RegisterYourself();
	

	TGeoCompositeShape* koala_base_test = new TGeoCompositeShape("koala_base_test","(koala_base_entrancetube:comb_trans_koala_base_ent)+(koala_base_exittube:comb_trans_koala_base_exit)+(koala_base_box:comb_trans_platepos)-(koalainnertube:comb_trans_koala_base)");
	
 
	TGeoVolume* koala_base = new TGeoVolume("koala_base", koala_base_test, gGeoMan->GetMedium("steel"));
	
	//koala_base->SetLineColor(kCyan);
	Koala_entrance->AddNode(koala_base,0);
	return Koala_entrance;
}




TGeoVolume* geokoaladetector::generateKoalastand() const {             //Is this the work of an enemy stand?
 TGeoVolumeAssembly* Koala_stand = new TGeoVolumeAssembly("Koala_stand"); //Endergebnis
  auto pt_general = geometry_property_tree.get_child("general");
  auto pt_stand_box = geometry_property_tree.get_child("koalastandbox");
  auto pt_stand_pipe = geometry_property_tree.get_child("koalastandpipe");



	double box_dim_x(pt_stand_box.get<double>("dimension_x"));
	double box_dim_y(pt_stand_box.get<double>("dimension_y"));
	double box_dim_z(pt_stand_box.get<double>("dimension_z"));
	double box_dim_x_inner(pt_stand_box.get<double>("dimension_x_inner"));
	double box_dim_y_inner(pt_stand_box.get<double>("dimension_y_inner"));
	double box_dim_z_inner(pt_stand_box.get<double>("dimension_z_inner"));
	double hole_distance(pt_stand_box.get<double>("hole_distance"));  // is y-axis from top of box to center of hole
	double pipe_lenght(pt_stand_pipe.get<double>("length"));
	double pipe_thickness(pt_stand_pipe.get<double>("thickness"));
	double pipe_radius(pt_stand_pipe.get<double>("inner_radius"));


	new TGeoBBox("koala_stand_box", box_dim_x / 2.0 , box_dim_y / 2.0, box_dim_z / 2.0);
	
	new TGeoBBox("koala_stand_box_cutout", box_dim_x_inner / 2.0 , box_dim_y_inner / 2.0, box_dim_z_inner / 2.0);

	TGeoTube* koala_stand_pipe = new TGeoTube("koala_stand_pipe", pipe_radius , pipe_radius + pipe_thickness, pipe_lenght/ 2.0);

	TGeoTube* koala_stand_pipe_cutout = new TGeoTube("koala_stand_pipe_cutout", 0.0 , pipe_radius + pipe_thickness, pipe_lenght/ 2.0);


	TGeoRotation* koala_stand_rot = new TGeoRotation("koala_stand_rot");
	koala_stand_rot->RotateX(0.0);
	koala_stand_rot->RotateY(90.0);
	koala_stand_rot->RotateZ(0.0);

	koala_stand_rot->RegisterYourself();


TGeoCompositeShape* koala_stand_compbox = new TGeoCompositeShape("koala_stand_compbox","((koala_stand_box)-(koala_stand_box_cutout))-(koala_stand_pipe_cutout:koala_stand_rot)");

TGeoCompositeShape* koala_stand_comppipe = new TGeoCompositeShape("koala_stand_comppipe","(koala_stand_pipe:koala_stand_rot)-(koala_stand_box)");


TGeoVolume* koala_stand_box_v = new TGeoVolume("koala_stand_box_v", koala_stand_compbox, gGeoMan->GetMedium("steel"));
	koala_stand_box_v->SetLineColor(kGreen);

TGeoVolume* koala_stand_pipe_v = new TGeoVolume("koala_stand_pipe_v", koala_stand_comppipe, gGeoMan->GetMedium("steel"));
	koala_stand_pipe_v->SetLineColor(kGreen);


	Koala_stand->AddNode(koala_stand_box_v,0);
	Koala_stand->AddNode(koala_stand_pipe_v,0);
	return Koala_stand;
}
TGeoVolume* geokoaladetector::generateKoalaChamberEnt() const {       
 TGeoVolumeAssembly* Koala_Cham_ent = new TGeoVolumeAssembly("Koala_Cham_ent"); //Endergebnis

 auto pt_cham_ent = geometry_property_tree.get_child("koalachamber_ent");
 auto pt_koala_ent_pipe = pt_cham_ent.get_child("entrance_pipe");
 auto pt_koala_ent_ring = pt_cham_ent.get_child("ring");
 auto pt_koala_cone = pt_cham_ent.get_child("cone");
 auto pt_koala_ent_cone = pt_cham_ent.get_child("cone_entrance");
 auto pt_koala_exit_cone = pt_cham_ent.get_child("cone_exit");
 

TGeoTube* koala_cham_ring = new TGeoTube("koala_cham_ring", pt_koala_ent_ring.get<double>("inner_radius"), pt_koala_ent_ring.get<double>("outer_radius"), pt_koala_ent_ring.get<double>("length")/ 2.0);

TGeoTube* koala_cham_ent_pipe = new TGeoTube("koala_cham_ent_pipe", pt_koala_ent_pipe.get<double>("inner_radius"), pt_koala_ent_pipe.get<double>("outer_radius"), pt_koala_ent_pipe.get<double>("length")/ 2.0);

TGeoTube* koala_cham_ent_cone = new TGeoTube("koala_cham_ent_cone", pt_koala_ent_cone.get<double>("inner_radius"),pt_koala_ent_cone.get<double>("outer_radius"), pt_koala_ent_cone.get<double>("length")/ 2.0);

TGeoTube* koala_cham_exit_cone = new TGeoTube("koala_cham_exit_cone", pt_koala_exit_cone.get<double>("inner_radius"), pt_koala_exit_cone.get<double>("outer_radius"), pt_koala_exit_cone.get<double>("length")/ 2.0);


TGeoRotation* koala_cham_ent_rot = new TGeoRotation("koala_cham_ent_rot");
	koala_cham_ent_rot->RotateX(0.0);
	koala_cham_ent_rot->RotateY(90.0);
	koala_cham_ent_rot->RotateZ(0.0);

TGeoCombiTrans* comb_trans_koala_cham_ent_pipe = new TGeoCombiTrans("comb_trans_koala_cham_ent_pipe", pt_koala_ent_ring.get<double>("length")/2.0 +  pt_koala_ent_pipe.get<double>("length")/ 2.0   ,  0.,0. , koala_cham_ent_rot);

TGeoCombiTrans* comb_trans_koala_cham_ent_cone = new TGeoCombiTrans("comb_trans_koala_cham_ent_cone", pt_koala_ent_ring.get<double>("length")/2.0 +  pt_koala_ent_pipe.get<double>("length") + pt_koala_ent_cone.get<double>("length") /2.0   ,  0.,0. , koala_cham_ent_rot);



 TGeoCombiTrans* comb_trans_koala_cham_exit_cone = new TGeoCombiTrans("comb_trans_koala_cham_exit_cone", pt_koala_ent_ring.get<double>("length")/2.0 +  pt_koala_ent_pipe.get<double>("length") + pt_koala_ent_cone.get<double>("length") + pt_koala_cone.get<double>("length")+ pt_koala_exit_cone.get<double>("length") /2.0   ,  0.,0. , koala_cham_ent_rot);
 
 
 koala_cham_ent_rot->RegisterYourself();
 



TGeoVolume* koala_cham_ring_v = new TGeoVolume("koala_cham_ring_v", koala_cham_ring, gGeoMan->GetMedium("copper"));
	koala_cham_ring_v->SetLineColor(kPink);

TGeoVolume* koala_cham_pipe_v = new TGeoVolume("koala_cham_pipe_v", koala_cham_ent_pipe, gGeoMan->GetMedium("steel"));
	koala_cham_pipe_v->SetLineColor(kBlue);

TGeoVolume* koala_cham_cone_ent_v = new TGeoVolume("koala_cham_cone_ent_v", koala_cham_ent_cone, gGeoMan->GetMedium("steel"));
	koala_cham_cone_ent_v->SetLineColor(kBlue);

TGeoVolume* koala_cham_cone_exit_v = new TGeoVolume("koala_cham_pipe_v", koala_cham_exit_cone, gGeoMan->GetMedium("steel"));
	koala_cham_cone_exit_v->SetLineColor(kBlue);

	Koala_Cham_ent->AddNode(koala_cham_ring_v,0,koala_cham_ent_rot);
	Koala_Cham_ent->AddNode(koala_cham_pipe_v,0,comb_trans_koala_cham_ent_pipe);
	Koala_Cham_ent->AddNode(koala_cham_cone_ent_v,0, comb_trans_koala_cham_ent_cone);
	Koala_Cham_ent->AddNode(koala_cham_cone_exit_v,0, comb_trans_koala_cham_exit_cone);


	// transition cone
	auto pt_cone =  pt_cham_ent.get_child("cone");
	double cone_thickness(pt_cone.get<double>("thickness"));
	double cone_angle = pt_cone.get<double>("angle_in_rad");
	double cone_length = pt_cone.get<double>("length");
	auto pt_ent_pipe =   pt_cham_ent.get_child("cone_entrance");
	double ent_pipe_inner_radius(pt_ent_pipe.get<double>("inner_radius"));
	auto pt_exit_pipe =   pt_cham_ent.get_child("cone_exit");
	double exit_pipe_inner_radius(pt_exit_pipe.get<double>("inner_radius"));
	auto pt_cone_tube =   pt_cham_ent.get_child("cone_tube");
	double cone_tube_inner_radius(pt_cone_tube.get<double>("inner_radius"));
	double cone_tube_thickness(pt_cone_tube.get<double>("thickness"));
	double cone_tube_length(pt_cone_tube.get<double>("length"));
	auto pt_cone_tube_cap =   pt_cham_ent.get_child("cone_tube_cap");
	double cone_tube_cap_radius(pt_cone_tube_cap.get<double>("radius"));
	double cone_tube_cap_length(pt_cone_tube_cap.get<double>("length"));
       

	TGeoCone* koala_cone = new TGeoCone("koala_cone", cone_length / 2.0, ent_pipe_inner_radius,
					    ent_pipe_inner_radius + cone_thickness, exit_pipe_inner_radius,
					    exit_pipe_inner_radius + cone_thickness);

	TGeoCone* koala_solid_cone = new TGeoCone("koala_solid_cone", cone_length / 2.0, 0.0,
					    ent_pipe_inner_radius + cone_thickness, 0.0,
					    exit_pipe_inner_radius + cone_thickness);

TGeoTube* koala_cone_tube_solid = new TGeoTube("koala_cone_tube_solid",0.0 ,cone_tube_inner_radius , cone_tube_length/ 2.0);

TGeoTube* koala_cone_tube = new TGeoTube("koala_cone_tube",cone_tube_inner_radius ,cone_tube_inner_radius + cone_tube_thickness , cone_tube_length/ 2.0);

TGeoTube* koala_cone_tube_cap = new TGeoTube("koala_cone_tube_cap",0.0 ,cone_tube_cap_radius , cone_tube_cap_length/ 2.0);

TGeoRotation* koala_cone_tube_rot = new TGeoRotation("koala_cone_tube_rot");
        koala_cone_tube_rot->RotateX(90.0);
        koala_cone_tube_rot->RotateY(0.0);
        koala_cone_tube_rot->RotateZ(0.0);

	TGeoCombiTrans* comb_trans_koala_cham_cone = new TGeoCombiTrans("comb_trans_koala_cham_cone", pt_koala_ent_ring.get<double>("length")/2.0 +  pt_koala_ent_pipe.get<double>("length") + pt_koala_ent_cone.get<double>("length") + pt_koala_cone.get<double>("length") /2.0   ,  0.,0. , koala_cham_ent_rot);

	TGeoCombiTrans* comb_cone_tube = new TGeoCombiTrans("comb_cone_tube", -3.5 , 7., 0.0 , koala_cone_tube_rot);

TGeoCombiTrans* comb_cone_tube_cap = new TGeoCombiTrans("comb_cone_tube_cap",pt_koala_ent_ring.get<double>("length")/2.0 +  pt_koala_ent_pipe.get<double>("length") + pt_koala_ent_cone.get<double>("length") + pt_koala_cone.get<double>("length") /2.0  , 17. + cone_tube_cap_length /2.0,  3.5, koala_cone_tube_rot);

	comb_cone_tube->RegisterYourself();

TGeoCompositeShape* koala_cone_tube_hole = new TGeoCompositeShape("koala_cone_tube_hole","(koala_cone_tube:comb_cone_tube)-(koala_solid_cone)");

TGeoCompositeShape* koala_cone_hole = new TGeoCompositeShape("koala_cone_hole","(koala_cone)-(koala_cone_tube_solid:comb_cone_tube)");

	TGeoVolume* koala_cone_v = new TGeoVolume("koala_cone_v", koala_cone_hole, gGeoMan->GetMedium("Aluminum"));
	koala_cone_v->SetLineColor(kGray);

	TGeoVolume* koala_cone_tube_v = new TGeoVolume("koala_cone_tube_v", koala_cone_tube_hole, gGeoMan->GetMedium("Aluminum"));
	koala_cone_tube_v->SetLineColor(kGray);

TGeoVolume* koala_cone_tube_cap_v = new TGeoVolume("koala_cone_tube_cap_v", koala_cone_tube_cap, gGeoMan->GetMedium("Aluminum"));
	koala_cone_tube_cap_v->SetLineColor(kGray);
	
	Koala_Cham_ent->AddNode(koala_cone_v,0,comb_trans_koala_cham_cone);
	Koala_Cham_ent->AddNode(koala_cone_tube_v,0,comb_trans_koala_cham_cone);
	Koala_Cham_ent->AddNode(koala_cone_tube_cap_v,0,comb_cone_tube_cap);


	return Koala_Cham_ent;
}

TGeoVolume* geokoaladetector::generateKoalaChamber() const {       
 TGeoVolumeAssembly* Koala_Cham = new TGeoVolumeAssembly("Koala_Cham"); //Endergebnis
 

 auto pt_cham = geometry_property_tree.get_child("koalachamber");
 auto pt_cham_entrance_tube =  pt_cham.get_child("chamber_entrance");
 double cham_ent_tube_inner_radius(pt_cham_entrance_tube.get<double>("inner_radius"));
 double cham_ent_tube_outer_radius(pt_cham_entrance_tube.get<double>("outer_radius"));
 double cham_ent_tube_length(pt_cham_entrance_tube.get<double>("length"));
 double cham_pos(pt_cham_entrance_tube.get<double>("position_hole"));
 auto pt_cham_cone =  pt_cham.get_child("chamber_cone");
 double cham_cone_length(pt_cham_cone.get<double>("length"));
 double cham_cone_ent_inner_radius(pt_cham_cone.get<double>("inner_radius_ent"));
 double cham_cone_ent_outer_radius(pt_cham_cone.get<double>("outer_radius_ent"));
 double cham_cone_exit_inner_radius(pt_cham_cone.get<double>("inner_radius_exit"));
 double cham_cone_exit_outer_radius(pt_cham_cone.get<double>("outer_radius_exit"));
 auto pt_chamber =  pt_cham.get_child("chamber");
 double cham_inner_radius(pt_chamber.get<double>("inner_radius"));
 double cham_outer_radius(pt_chamber.get<double>("outer_radius"));
 double cham_length(pt_chamber.get<double>("length"));
 auto pt_chamber_end =  pt_cham.get_child("chamber_end");
 double cham_inner_end(pt_chamber_end.get<double>("inner_plate_radius"));
 double cham_middle_end(pt_chamber_end.get<double>("middle_plate_radius"));
 double cham_outer_end(pt_chamber_end.get<double>("outer_plate_radius"));
 double cham_inner_length(pt_chamber_end.get<double>("inner_plate_length"));
 double cham_middle_length(pt_chamber_end.get<double>("middle_plate_length"));
 double cham_outer_length(pt_chamber_end.get<double>("outer_plate_length"));
 auto pt_chamber_tube =  pt_cham.get_child("chamber_tube");
 double cham_inner_tube_radius(pt_chamber_tube.get<double>("inner_radius"));
 double cham_outer_tube_radius(pt_chamber_tube.get<double>("outer_radius"));
 double cham_tube_length(pt_chamber_tube.get<double>("length"));
 double cham_tube_position(pt_chamber_tube.get<double>("hole_position"));
 auto pt_chamber_tube_end =  pt_cham.get_child("chamber_tube_end");
 double cham_inner_tube_end_radius(pt_chamber_tube_end.get<double>("radius"));
 double cham_tube_thickness(pt_chamber_tube_end.get<double>("thickness"));
 

TGeoTube* koala_chamber_ent = new TGeoTube("koala_chamber_ent", 0.0 ,cham_ent_tube_outer_radius ,  cham_ent_tube_length/ 2.0);

TGeoTube* koala_chamber_ent_cutout = new TGeoTube("koala_chamber_ent_cutout", 0.0 ,cham_ent_tube_inner_radius ,  cham_ent_tube_length);

TGeoCone* koala_chamber_ent_cone = new TGeoCone("koala_chamber_ent_cone", cham_cone_length / 2.0, 0.0,
					    cham_cone_ent_outer_radius, 0.0,
					   cham_cone_exit_outer_radius);

TGeoCone* koala_chamber_ent_cone_cutout = new TGeoCone("koala_chamber_ent_cone_cutout", cham_cone_length / 2.0, 0.0,
					    cham_cone_ent_inner_radius, 0.0,
					   cham_cone_exit_inner_radius);



 TGeoTube* koala_chamber = new TGeoTube("koala_chamber", cham_inner_radius , cham_outer_radius ,  cham_length/ 2.0);

 TGeoTube* koala_chamber_cutout = new TGeoTube("koala_chamber_cutout", 0.0 , cham_outer_radius ,  cham_length/ 2.0);
 
 TGeoTube* koala_chamber_tube = new TGeoTube("koala_chamber_tube", cham_inner_tube_radius ,  cham_outer_tube_radius ,  cham_tube_length/ 2.0);
 
 TGeoTube* koala_chamber_tube_cutout = new TGeoTube("koala_chamber_tube_cutout", 0.0 ,  cham_outer_tube_radius , cham_tube_length/ 2.0);
 
 TGeoTube* koala_chamber_tube_end = new TGeoTube("koala_chamber_tube_end", 0.0 , cham_inner_tube_end_radius , cham_tube_thickness/ 2.0);
 
 TGeoTube* koala_end_in = new TGeoTube("koala_end_in", 0.0 , cham_inner_end ,   cham_inner_length/ 2.0);
 TGeoTube* koala_end_mid = new TGeoTube("koala_end_mid", 0.0 , cham_middle_end ,   cham_middle_length/ 2.0);
 TGeoTube* koala_end_out = new TGeoTube("koala_end_out", 0.0 , cham_outer_end ,   cham_outer_length/ 2.0);
 
 
 TGeoRotation* koala_chamber_rot = new TGeoRotation("koala_chamber_rot");
 koala_chamber_rot->RotateX(0.0);
 koala_chamber_rot->RotateY(90.0);
 koala_chamber_rot->RotateZ(0.0);
 
 TGeoRotation* koala_outer_tube_rot = new TGeoRotation("koala_outer_tube_rot");
 koala_outer_tube_rot->RotateX(90.0);
 koala_outer_tube_rot->RotateY(0.0);
 koala_outer_tube_rot->RotateZ(0.0);
 
 TGeoTranslation* comb_chamber_ent = new TGeoTranslation("comb_chamber_ent", - cham_ent_tube_outer_radius + cham_pos + cham_ent_tube_inner_radius , 0.0 , 0.0);
 
 TGeoCombiTrans* comb_cham_cone = new TGeoCombiTrans("comb_cham_cone",cham_ent_tube_length /2.0 + cham_cone_length /2.0 ,  0., cham_ent_tube_outer_radius - cham_pos -  cham_ent_tube_inner_radius , koala_chamber_rot);
 TGeoCombiTrans* comb_cham_cone_cutout = new TGeoCombiTrans("comb_cham_cone_cutout",cham_ent_tube_length /2.0 + cham_cone_length /2.0 ,0.0 , 0.0 , koala_chamber_rot);

	TGeoCombiTrans* comb_cham = new TGeoCombiTrans("comb_cham",cham_ent_tube_length /2.0 + cham_length /2.0 ,  0., cham_ent_tube_outer_radius - cham_pos -  cham_ent_tube_inner_radius , koala_chamber_rot);

	TGeoCombiTrans* comb_cham_end_in = new TGeoCombiTrans("comb_cham_end_in",cham_ent_tube_length /2.0 + cham_length + cham_inner_length /2.0 ,  0., cham_ent_tube_outer_radius - cham_pos - cham_ent_tube_inner_radius , koala_chamber_rot);

TGeoCombiTrans* comb_cham_end_mid = new TGeoCombiTrans("comb_cham_end_mid",cham_ent_tube_length /2.0 + cham_length + cham_inner_length+ cham_middle_length /2.0 ,  0., cham_ent_tube_outer_radius - cham_pos  - cham_ent_tube_inner_radius  , koala_chamber_rot);

 TGeoCombiTrans* comb_cham_end_out = new TGeoCombiTrans("comb_cham_end_out",cham_ent_tube_length /2.0 + cham_length + cham_inner_length + cham_middle_length + cham_outer_length /2.0 ,  0., cham_ent_tube_outer_radius - cham_pos  - cham_ent_tube_inner_radius  , koala_chamber_rot);


 TGeoCombiTrans* comb_cham_tube = new TGeoCombiTrans("comb_cham_tube", 0., cham_tube_length/ 2.0  + cham_outer_radius -1 , cham_length/ 2.0 - cham_tube_position   , koala_outer_tube_rot);

 TGeoCombiTrans* comb_cham_tube_end = new TGeoCombiTrans("comb_cham_tube_end",0., cham_tube_length  +  cham_outer_radius + cham_tube_thickness/ 2.0 -1 , cham_length/ 2.0 - cham_tube_position  , koala_outer_tube_rot);

        

comb_chamber_ent->RegisterYourself();
comb_cham_cone->RegisterYourself();
comb_cham_cone_cutout->RegisterYourself();
 comb_cham_tube->RegisterYourself();
 comb_cham_tube_end->RegisterYourself();


TGeoCompositeShape* koala_chamber_ent_hole = new TGeoCompositeShape("koala_chamber_ent_hole","(koala_chamber_ent:comb_chamber_ent)-(koala_chamber_ent_cutout)");

 TGeoCompositeShape* koala_chamber_cutout_hole = new TGeoCompositeShape("koala_chamber_cutout_hole","(koala_chamber)-(koala_chamber_tube_cutout:comb_cham_tube)");

 TGeoCompositeShape* koala_tube_cutout_hole = new TGeoCompositeShape("koala_tube_cutout_hole","(koala_chamber_tube:comb_cham_tube) + (koala_chamber_tube_end:comb_cham_tube_end) -(koala_chamber_cutout)");

TGeoCompositeShape* koala_chamber_cone_hole = new TGeoCompositeShape("koala_chamber_cone_hole","(koala_chamber_ent_cone:comb_cham_cone)-(koala_chamber_ent_cone_cutout:comb_cham_cone_cutout)");

TGeoVolume* koala_chamber_ent_v = new TGeoVolume("koala_chamber_ent_v",  koala_chamber_ent_hole, gGeoMan->GetMedium("steel"));
	koala_chamber_ent_v->SetLineColor(kGray);

TGeoVolume* koala_chamber_cone_v = new TGeoVolume("koala_chamber_cone_v", koala_chamber_cone_hole, gGeoMan->GetMedium("steel"));
	koala_chamber_cone_v->SetLineColor(kGray);

TGeoVolume* koala_chamber_v = new TGeoVolume("koala_chamber_v",  koala_chamber_cutout_hole, gGeoMan->GetMedium("steel"));
 koala_chamber_v->SetLineColor(kGray);
 
 TGeoVolume* koala_chamber_tube_v = new TGeoVolume("koala_chamber_tube_v",  koala_tube_cutout_hole, gGeoMan->GetMedium("steel"));
 koala_chamber_v->SetLineColor(kRed);

TGeoVolume* koala_chamber_end_in_v = new TGeoVolume("koala_chamber_end_in_v",  koala_end_in, gGeoMan->GetMedium("steel"));
	koala_chamber_end_in_v->SetLineColor(kGray);

TGeoVolume* koala_chamber_end_mid_v = new TGeoVolume("koala_chamber_end_mid_v",  koala_end_mid, gGeoMan->GetMedium("steel"));
	koala_chamber_end_mid_v->SetLineColor(kGray);

TGeoVolume* koala_chamber_end_out_v = new TGeoVolume("koala_chamber_end_out_v",  koala_end_out, gGeoMan->GetMedium("steel"));
	koala_chamber_end_out_v->SetLineColor(kGray);


Koala_Cham->AddNode(koala_chamber_ent_v,0,koala_chamber_rot);
Koala_Cham->AddNode(koala_chamber_cone_v,0);
Koala_Cham->AddNode(koala_chamber_v,0, comb_cham);
 Koala_Cham->AddNode(koala_chamber_tube_v,0, comb_cham);
Koala_Cham->AddNode(koala_chamber_end_in_v,0, comb_cham_end_in);
 Koala_Cham->AddNode(koala_chamber_end_mid_v,0, comb_cham_end_mid);
 Koala_Cham->AddNode(koala_chamber_end_out_v,0, comb_cham_end_out);

return Koala_Cham;
}

TGeoVolume* geokoaladetector::generateKoalaInnerChamber() const {       
 TGeoVolumeAssembly* Koala_Inner_Cham = new TGeoVolumeAssembly("Koala_Inner_Cham"); //Endergebnis
  auto pt_cham_in = geometry_property_tree.get_child("koala_inner_chamber");
 auto pt_cham1 =  pt_cham_in.get_child("chamber1");
 double cham1_inner_radius(pt_cham1.get<double>("inner_radius"));
 double cham1_outer_radius(pt_cham1.get<double>("outer_radius"));
 double cham1_length(pt_cham1.get<double>("length"));
 auto pt_cham2 =  pt_cham_in.get_child("chamber2");
 double cham2_inner_radius(pt_cham2.get<double>("inner_radius"));
 double cham2_outer_radius(pt_cham2.get<double>("outer_radius"));
 double cham2_length(pt_cham2.get<double>("length"));
 auto pt_cham3 =  pt_cham_in.get_child("chamber3");
 double cham3_inner_radius(pt_cham3.get<double>("inner_radius"));
 double cham3_outer_radius(pt_cham3.get<double>("outer_radius"));
 double cham3_length(pt_cham3.get<double>("length"));
 auto pt_cham4 =  pt_cham_in.get_child("chamber4");
 double cham4_inner_radius(pt_cham4.get<double>("inner_radius"));
 double cham4_outer_radius(pt_cham4.get<double>("outer_radius"));
 double cham4_length(pt_cham4.get<double>("length"));
 auto pt_cham_copper_plate_ent =  pt_cham_in.get_child("copper_plate_ent");
 double ent_copper_plate_radius(pt_cham_copper_plate_ent.get<double>("radius"));
 double ent_copper_plate_thickness(pt_cham_copper_plate_ent.get<double>("thickness"));
 auto pt_cham_alu_plate_ent =  pt_cham_in.get_child("alu_plate_ent");
 double ent_alu_plate_radius(pt_cham_alu_plate_ent.get<double>("radius"));
 double ent_alu_plate_thickness(pt_cham_alu_plate_ent.get<double>("thickness"));
 auto pt_plate_ent_cutout =  pt_cham_in.get_child("plate_ent_cutout");
 double plate_cutout_x(pt_plate_ent_cutout.get<double>("x_length"));
 double plate_cutout_y(pt_plate_ent_cutout.get<double>("y_length"));
 double plate_cutout_centerdisance_x(pt_plate_ent_cutout.get<double>("centerdistance_x"));
 auto pt_cham_copper_plate_exit =  pt_cham_in.get_child("copper_plate_exit");
 double exit_copper_plate_inner_radius(pt_cham_copper_plate_exit.get<double>("inner_radius"));
 double exit_copper_plate_outer_radius(pt_cham_copper_plate_exit.get<double>("outer_radius"));
 double exit_copper_plate_thickness(pt_cham_copper_plate_exit.get<double>("thickness"));
 auto pt_cham_alu_plate_exit =  pt_cham_in.get_child("alu_plate_exit");
 double exit_alu_plate_inner_radius(pt_cham_alu_plate_exit.get<double>("inner_radius"));
 double exit_alu_plate_outer_radius(pt_cham_alu_plate_exit.get<double>("outer_radius"));
 double exit_alu_plate_thickness(pt_cham_alu_plate_exit.get<double>("thickness"));
 auto pt_chamber_ring =  pt_cham_in.get_child("chamberring");
 double chamber_ring_inner_radius(pt_chamber_ring.get<double>("inner_radius"));
 double chamber_ring_outer_radius(pt_chamber_ring.get<double>("outer_radius"));
 double chamber_ring_thickness(pt_chamber_ring.get<double>("thickness"));
 auto pt_in_chamber_tube_alu =  pt_cham_in.get_child("inner_chamber_tube_alu");
 double chamber_alu_tube_inner_radius( pt_in_chamber_tube_alu.get<double>("inner_radius"));
 double chamber_alu_tube_outer_radius( pt_in_chamber_tube_alu.get<double>("outer_radius"));
 double chamber_alu_tube_length( pt_in_chamber_tube_alu.get<double>("length"));
 double chamber_alu_tube_end_radius( pt_in_chamber_tube_alu.get<double>("endpiece_radius"));
 double chamber_alu_tube_end_thickness( pt_in_chamber_tube_alu.get<double>("endpiece_thickness"));
 double chamber_alu_tube_hole_pos( pt_in_chamber_tube_alu.get<double>("hole_position"));
 auto pt_in_chamber_tube_steel_1 =  pt_cham_in.get_child("inner_chamber_tube_steel_1");
 double chamber_steel_1_tube_inner_radius( pt_in_chamber_tube_steel_1.get<double>("inner_radius"));
 double chamber_steel_1_tube_outer_radius( pt_in_chamber_tube_steel_1.get<double>("outer_radius"));
 double chamber_steel_1_tube_length( pt_in_chamber_tube_steel_1.get<double>("length"));
 auto pt_in_chamber_tube_steel_2 =  pt_cham_in.get_child("inner_chamber_tube_steel_2");
 double chamber_steel_2_tube_inner_radius( pt_in_chamber_tube_steel_2.get<double>("inner_radius"));
 double chamber_steel_2_tube_outer_radius( pt_in_chamber_tube_steel_2.get<double>("outer_radius"));
 double chamber_steel_2_tube_length( pt_in_chamber_tube_steel_2.get<double>("length"));
 auto pt_in_chamber_tube_steel_3 =  pt_cham_in.get_child("inner_chamber_tube_steel_3");
 double chamber_steel_3_tube_inner_radius( pt_in_chamber_tube_steel_3.get<double>("inner_radius"));
 double chamber_steel_3_tube_outer_radius( pt_in_chamber_tube_steel_3.get<double>("outer_radius"));
 double chamber_steel_3_tube_length( pt_in_chamber_tube_steel_3.get<double>("length"));



 TGeoTube* koala_chamber_1 = new TGeoTube("koala_chamber_1", cham1_inner_radius , cham1_outer_radius, cham1_length/ 2.0);
 
 TGeoTube* koala_chamber_2 = new TGeoTube("koala_chamber_2", cham2_inner_radius , cham2_outer_radius, cham2_length/ 2.0);
 
 TGeoTube* koala_chamber_3 = new TGeoTube("koala_chamber_3", cham3_inner_radius , cham3_outer_radius, cham3_length/ 2.0);
 
 TGeoTube* koala_chamber_4 = new TGeoTube("koala_chamber_4", cham4_inner_radius , cham4_outer_radius, cham4_length/ 2.0);

 TGeoTube* koala_in_chamber_tube_cutout = new TGeoTube("koala_in_chamber_tube_cutout", 0.0 , chamber_alu_tube_end_radius, chamber_alu_tube_length/ 2.0);

 TGeoTube* koala_in_chamber_steel_tube_1 = new TGeoTube(" koala_in_chamber_steel_tube_1", chamber_steel_1_tube_inner_radius , chamber_steel_1_tube_outer_radius , chamber_steel_1_tube_length/ 2.0);

 TGeoTube* koala_in_chamber_steel_tube_2 = new TGeoTube(" koala_in_chamber_steel_tube_2", chamber_steel_2_tube_inner_radius , chamber_steel_2_tube_outer_radius , chamber_steel_2_tube_length/ 2.0);
 
 TGeoTube* koala_in_chamber_steel_tube_3 = new TGeoTube(" koala_in_chamber_steel_tube_3", chamber_steel_3_tube_inner_radius , chamber_steel_3_tube_outer_radius , chamber_steel_3_tube_length/ 2.0);

  TGeoTube* koala_in_chamber_alu_tube = new TGeoTube("koala_in_chamber_alu_tube", chamber_alu_tube_inner_radius ,chamber_alu_tube_outer_radius  , chamber_alu_tube_length/ 2.0);

  TGeoTube* koala_in_chamber_alu_tube_end = new TGeoTube("koala_in_chamber_alu_tube_end", chamber_alu_tube_inner_radius ,chamber_alu_tube_end_radius, chamber_alu_tube_end_thickness/ 2.0);

 TGeoTube* koala_copper_plate_ent = new TGeoTube("koala_copper_plate_ent", 0.0 , ent_copper_plate_radius , ent_copper_plate_thickness/ 2.0);
 TGeoTube* koala_alu_plate_ent = new TGeoTube("koala_alu_plate_ent", 0.0 , ent_alu_plate_radius , ent_alu_plate_thickness/ 2.0);
 new TGeoBBox("koala_plate_ent_cutout", plate_cutout_x/ 2.0 , plate_cutout_y / 2.0, 100 / 2.0);

 TGeoTube* koala_copper_plate_exit = new TGeoTube("koala_copper_plate_exit", exit_copper_plate_inner_radius , exit_copper_plate_outer_radius, exit_copper_plate_thickness/ 2.0);
 TGeoTube* koala_alu_plate_exit = new TGeoTube("koala_alu_plate_exit", exit_alu_plate_inner_radius , exit_alu_plate_outer_radius ,  exit_alu_plate_thickness/ 2.0);

 TGeoTube* chamber_ring = new TGeoTube("chamber_ring", chamber_ring_inner_radius , chamber_ring_outer_radius ,  chamber_ring_thickness/ 2.0);
 
 TGeoRotation* koala_inner_rot = new TGeoRotation("koala_inner_rot");
 koala_inner_rot->RotateX(0.0);
 koala_inner_rot->RotateY(90.0);
 koala_inner_rot->RotateZ(0.0);
 
 TGeoRotation* koala_inner_tube_rot = new TGeoRotation("koala_inner_tube_rot");
 koala_inner_tube_rot->RotateX(90.0);
 koala_inner_tube_rot->RotateY(0.0);
 koala_inner_tube_rot->RotateZ(0.0);


 TGeoCombiTrans* comb_inner_cham = new TGeoCombiTrans("comb_inner_cham", cham2_length/ 2.0 ,  0., 0. , koala_inner_rot);

 TGeoCombiTrans* comb_inner_tube = new TGeoCombiTrans("comb_inner_tube", cham2_length - chamber_alu_tube_hole_pos ,   cham4_outer_radius -0.5, 0. , koala_inner_tube_rot);


 TGeoCombiTrans* comb_copper_plate_1 = new TGeoCombiTrans("comb_copper_plate_1", ent_copper_plate_thickness/ 2.0 ,  0., 0. , koala_inner_rot);
 TGeoCombiTrans* comb_copper_plate_2 = new TGeoCombiTrans("comb_copper_plate_2", ent_copper_plate_thickness + ent_copper_plate_thickness/ 2.0 ,  0., 0. , koala_inner_rot);
 TGeoCombiTrans* comb_copper_plate_3 = new TGeoCombiTrans("comb_copper_plate_3", ent_copper_plate_thickness + ent_copper_plate_thickness + ent_copper_plate_thickness/ 2.0 ,  0., 0. , koala_inner_rot);
 TGeoCombiTrans* comb_alu_plate = new TGeoCombiTrans("comb_alu_plate", ent_copper_plate_thickness + ent_copper_plate_thickness + ent_copper_plate_thickness +  ent_alu_plate_thickness/ 2.0 ,  0., 0. , koala_inner_rot);

 TGeoTranslation* comb_cham_tube_1 = new TGeoTranslation("comb_cham_tube_1", 0.  ,  0.,   chamber_alu_tube_length/ 2.0 + chamber_alu_tube_end_thickness /2.0 );
 TGeoTranslation* comb_cham_tube_2 = new TGeoTranslation("comb_cham_tube_2", 0.  ,  0., - chamber_alu_tube_length/ 2.0 - chamber_alu_tube_end_thickness /2.0 );

  TGeoTranslation* comb_cham_plate = new TGeoTranslation("comb_cham_plate",  plate_cutout_centerdisance_x - plate_cutout_x/2.0  ,  0., 0. );

  TGeoCombiTrans* comb_copper_plate_1_exit = new TGeoCombiTrans("comb_copper_plate_1_exit",  cham2_length - ent_copper_plate_thickness/ 2.0 ,  0., 0. , koala_inner_rot);
  TGeoCombiTrans* comb_copper_plate_2_exit = new TGeoCombiTrans("comb_copper_plate_2_exit",  cham2_length - ent_copper_plate_thickness - ent_copper_plate_thickness/ 2.0 ,  0., 0. , koala_inner_rot);
  TGeoCombiTrans* comb_copper_plate_3_exit = new TGeoCombiTrans("comb_copper_plate_3_exit",  cham2_length - ent_copper_plate_thickness - ent_copper_plate_thickness - ent_copper_plate_thickness/ 2.0 ,  0., 0. , koala_inner_rot);
  TGeoCombiTrans* comb_alu_plate_exit = new TGeoCombiTrans("comb_alu_plate_exit",  cham2_length - ent_copper_plate_thickness - ent_copper_plate_thickness - ent_copper_plate_thickness- ent_alu_plate_thickness/ 2.0 ,  0., 0. , koala_inner_rot);

  TGeoCombiTrans* comb_chamber_ring_1 = new TGeoCombiTrans("comb_chamber_ring_1",  cham2_length/2.0 - cham1_length/2.0 +  chamber_ring_thickness/2.0 ,  0., 0. , koala_inner_rot);
   TGeoCombiTrans* comb_chamber_ring_2 = new TGeoCombiTrans("comb_chamber_ring_2",  cham2_length/2.0 + cham1_length/2.0 -  chamber_ring_thickness/2.0 ,  0., 0. , koala_inner_rot);

 comb_cham_plate->RegisterYourself();
 comb_inner_cham->RegisterYourself();
 comb_inner_tube->RegisterYourself();
 comb_cham_tube_1->RegisterYourself();
 comb_cham_tube_2->RegisterYourself();
 

  TGeoCompositeShape* koala_steel_chamber_hole = new TGeoCompositeShape("koala_steel_chamber_hole","(koala_chamber_2:comb_inner_cham) + (koala_chamber_3:comb_inner_cham) + (koala_chamber_4:comb_inner_cham)-(koala_in_chamber_tube_cutout:comb_inner_tube)");

   TGeoCompositeShape* koala_alu_chamber_hole = new TGeoCompositeShape("koala_alu_chamber_hole","(koala_chamber_1:comb_inner_cham) -(koala_in_chamber_tube_cutout:comb_inner_tube)");

   TGeoCompositeShape* koala_alu_tube_comp = new TGeoCompositeShape("koala_alu_tube_comp","(koala_in_chamber_alu_tube) + (koala_in_chamber_alu_tube_end:comb_cham_tube_1) + (koala_in_chamber_alu_tube_end:comb_cham_tube_2) ");


 TGeoCompositeShape* koala_copper_plate_hole = new TGeoCompositeShape("koala_copper_plate_hole","(koala_copper_plate_ent)-(koala_plate_ent_cutout:comb_cham_plate)");

 TGeoCompositeShape* koala_alu_plate_hole = new TGeoCompositeShape("koala_alu_plate_hole","(koala_alu_plate_ent)-(koala_plate_ent_cutout:comb_cham_plate)");

 TGeoVolume* koala_copper_plate_v = new TGeoVolume("koala_copper_plate_v",  koala_copper_plate_hole, gGeoMan->GetMedium("copper"));
 koala_copper_plate_v->SetLineColor(kRed);

 TGeoVolume* koala_alu_plate_v = new TGeoVolume("koala_alu_plate_v",  koala_alu_plate_hole, gGeoMan->GetMedium("Aluminum"));
 koala_alu_plate_v->SetLineColor(kGreen);

 TGeoVolume* koala_copper_plate_exit_v = new TGeoVolume("koala_copper_plate_exit_v",  koala_copper_plate_exit, gGeoMan->GetMedium("copper"));
 koala_copper_plate_exit_v->SetLineColor(kRed);

  TGeoVolume* koala_alu_plate_exit_v = new TGeoVolume("koala_alu_plate_exit_v", koala_alu_plate_exit, gGeoMan->GetMedium("Aluminum"));
 koala_alu_plate_exit_v->SetLineColor(kGreen);

 TGeoVolume* koala_chamber_ring_v = new TGeoVolume("koala_chamber_ring_v",  chamber_ring, gGeoMan->GetMedium("steel"));
 koala_chamber_ring_v->SetLineColor(kBlue);


TGeoVolume* koala_chamber_1_v = new TGeoVolume("koala_chamber_1_v",  koala_steel_chamber_hole, gGeoMan->GetMedium("Aluminum"));
 koala_chamber_1_v->SetLineColor(kGray);
 
 TGeoVolume* koala_steel_chamber_v = new TGeoVolume("koala_steel_chamber_v",  koala_steel_chamber_hole, gGeoMan->GetMedium("steel"));
 koala_steel_chamber_v->SetLineColor(kBlue);

 TGeoVolume* koala_alu_tube_v = new TGeoVolume("koala_alu_tube_v",   koala_alu_tube_comp, gGeoMan->GetMedium("Aluminum"));
 koala_alu_tube_v->SetLineColor(kPink);

 TGeoVolume* koala_steel_tube_1_v = new TGeoVolume("koala_steel_tube_1_v",   koala_in_chamber_steel_tube_1, gGeoMan->GetMedium("steel"));
 koala_steel_tube_1_v->SetLineColor(kGreen);

 TGeoVolume* koala_steel_tube_2_v = new TGeoVolume("koala_steel_tube_2_v",   koala_in_chamber_steel_tube_2, gGeoMan->GetMedium("steel"));
 
 TGeoVolume* koala_steel_tube_3_v = new TGeoVolume("koala_steel_tube_3_v",   koala_in_chamber_steel_tube_3, gGeoMan->GetMedium("steel"));
 koala_steel_tube_3_v->SetLineColor(kGreen);
 


 Koala_Inner_Cham->AddNode(koala_chamber_1_v,0, 0);
 Koala_Inner_Cham->AddNode(koala_steel_chamber_v,0, 0);
 Koala_Inner_Cham->AddNode(koala_alu_tube_v,0, comb_inner_tube);
 Koala_Inner_Cham->AddNode(koala_steel_tube_1_v,0, comb_inner_tube);
 Koala_Inner_Cham->AddNode(koala_steel_tube_2_v,0, comb_inner_tube);
 Koala_Inner_Cham->AddNode(koala_steel_tube_3_v,0, comb_inner_tube);
 Koala_Inner_Cham->AddNode(koala_copper_plate_v,0, comb_copper_plate_1);
 Koala_Inner_Cham->AddNode(koala_copper_plate_v,0, comb_copper_plate_2);
 Koala_Inner_Cham->AddNode(koala_copper_plate_v,0, comb_copper_plate_3);
 Koala_Inner_Cham->AddNode(koala_alu_plate_v,0, comb_alu_plate);
 Koala_Inner_Cham->AddNode(koala_copper_plate_exit_v,0, comb_copper_plate_1_exit);
 Koala_Inner_Cham->AddNode(koala_copper_plate_exit_v,0, comb_copper_plate_2_exit);
 Koala_Inner_Cham->AddNode(koala_copper_plate_exit_v,0, comb_copper_plate_3_exit);
 Koala_Inner_Cham->AddNode(koala_alu_plate_exit_v,0, comb_alu_plate_exit);
 Koala_Inner_Cham->AddNode(koala_chamber_ring_v,0, comb_chamber_ring_1);
 Koala_Inner_Cham->AddNode(koala_chamber_ring_v,0, comb_chamber_ring_2);



 return Koala_Inner_Cham;
}

TGeoVolume* geokoaladetector::generateKoalaSensorMount() const {       
 TGeoVolumeAssembly* Koala_Sensor_Mount = new TGeoVolumeAssembly("Koala_Sensor_Mount"); //Endergebnis


 auto pt_sensor_mount = geometry_property_tree.get_child("Koala_sensor_pipe");
 auto pt_sensor_outer_pipe =  pt_sensor_mount.get_child("outer_pipe");
 double sens_outer_pipe_inner_radius(pt_sensor_outer_pipe.get<double>("inner_radius"));
double sens_outer_pipe_outer_radius(pt_sensor_outer_pipe.get<double>("outer_radius"));
double sens_outer_pipe_outer_radius_thick(pt_sensor_outer_pipe.get<double>("outer_radius_thicc"));
double sens_outer_pipe_length_start(pt_sensor_outer_pipe.get<double>("length_start"));
 double sens_outer_pipe_length_end(pt_sensor_outer_pipe.get<double>("length_end"));
double sens_outer_pipe_length_thick(pt_sensor_outer_pipe.get<double>("thicc_length"));
 auto pt_sensor_plate_m =  pt_sensor_mount.get_child("plate");
 double sens_plate_x_length(pt_sensor_plate_m.get<double>("x_length"));
  double sens_plate_y_length(pt_sensor_plate_m.get<double>("y_length"));
  double sens_plate_thickness(pt_sensor_plate_m.get<double>("thickness"));
   double sens_plate_side_length(pt_sensor_plate_m.get<double>("side_length"));
  double sens_plate_side_thickness(pt_sensor_plate_m.get<double>("side_thickness"));
  auto pt_cham_plate_i = geometry_property_tree.get_child("koala_inner_chamber");
  auto pt_sens_plate_cutout =  pt_cham_plate_i.get_child("chamber1");
  double sens_plate_cutout(pt_sens_plate_cutout.get<double>("inner_radius"));


  TGeoTube* koala_sensor_plate_pipe= new TGeoTube("koala_sensor_plate_pipe",   sens_outer_pipe_inner_radius ,  sens_outer_pipe_outer_radius , (sens_outer_pipe_length_start - sens_outer_pipe_length_end) /2.0 );
  
  TGeoTube* koala_sensor_plate_pipe_thick= new TGeoTube("koala_sensor_plate_pipe_thick",   sens_outer_pipe_inner_radius ,  sens_outer_pipe_outer_radius_thick , sens_outer_pipe_length_thick /2.0 );
  TGeoTube* koala_sensor_plate_cut= new TGeoTube("koala_sensor_plate_cut",  sens_plate_cutout ,  sens_plate_cutout + 200.0 , sens_plate_side_thickness + 200 );
  new TGeoBBox("koala_sensor_plate", sens_plate_x_length/ 2.0 , sens_plate_y_length / 2.0,  sens_plate_thickness / 2.0);
  new TGeoBBox("koala_sensor_plate_side", sens_plate_side_length/ 2.0 , sens_plate_y_length / 2.0 ,  sens_plate_side_thickness / 2.0);

  TGeoTranslation* comb_sens_plate_r = new TGeoTranslation("comb_sens_plate_r",  sens_plate_x_length/ 2.0 + sens_plate_side_length/ 2.0   ,  0.,  sens_plate_side_thickness / 2.0  - sens_plate_thickness / 2.0 );
   TGeoTranslation* comb_sens_plate_l = new TGeoTranslation("comb_sens_plate_l", - sens_plate_x_length/ 2.0 - sens_plate_side_length/ 2.0   ,  0.,  sens_plate_side_thickness / 2.0  - sens_plate_thickness / 2.0 );
   TGeoTranslation* comb_sens_plate_pipe_thick = new TGeoTranslation("comb_sens_plate_pipe_thick",  0.  ,  0., sens_plate_thickness / 2.0 + sens_outer_pipe_length_thick /2.0 );
    TGeoTranslation* comb_sens_plate_pipe = new TGeoTranslation("comb_sens_plate_pipe",  0.  ,  0., sens_plate_thickness / 2.0 + sens_outer_pipe_length_thick + (sens_outer_pipe_length_start - sens_outer_pipe_length_end) /2.0 );

    comb_sens_plate_r->RegisterYourself();
    comb_sens_plate_l->RegisterYourself();
  
  
   TGeoCompositeShape* koala_sensor_plate_cut_f = new TGeoCompositeShape("koala_sensor_plate_cut_f","(koala_sensor_plate) +(koala_sensor_plate_side:comb_sens_plate_l) +(koala_sensor_plate_side:comb_sens_plate_r) - (koala_sensor_plate_cut)");

   
TGeoVolume* koala_sens_plate_v = new TGeoVolume("koala_sens_plate_v",  koala_sensor_plate_cut_f , gGeoMan->GetMedium("copper"));
 koala_sens_plate_v->SetLineColor(kCyan);

 TGeoVolume* koala_sens_plate_pipe_v = new TGeoVolume("koala_sens_plate_pipe_v",  koala_sensor_plate_pipe , gGeoMan->GetMedium("copper"));
 koala_sens_plate_pipe_v->SetLineColor(kCyan);

 TGeoVolume* koala_sens_plate_pipe_thick_v = new TGeoVolume("koala_sens_plate_pipe_thick_v",  koala_sensor_plate_pipe_thick , gGeoMan->GetMedium("copper"));
 koala_sens_plate_pipe_thick_v->SetLineColor(kCyan);

  Koala_Sensor_Mount->AddNode(koala_sens_plate_v,0, 0);
  Koala_Sensor_Mount->AddNode(koala_sens_plate_pipe_v,0, comb_sens_plate_pipe);
   Koala_Sensor_Mount->AddNode(koala_sens_plate_pipe_thick_v,0, comb_sens_plate_pipe_thick);

 return Koala_Sensor_Mount;
}

void geokoaladetector::recursiveNodeSubtraction(std::stringstream& ss, TGeoNode* node) const {
	if (node->GetNdaughters() == 0) {
		ss << "-" << node->GetVolume()->GetName() << ":" << node->GetMatrix()->GetName();
	}
	else {
		for (int i = 0; i < node->GetNdaughters(); ++i) {
			recursiveNodeSubtraction(ss, node->GetDaughter(i));
		}
	}
}

void geokoaladetector::makeNodesAlignable() const {
	TGeoNode* node = gGeoMan->GetTopNode();
	gGeoMan->CdTop();
	for (int i = 0; i < node->GetNdaughters(); ++i) {
		makeNodesAlignable(node->GetDaughter(i), 0);
	}
}

void geokoaladetector::makeNodesAlignable(TGeoNode* node,
    unsigned int current_navigation_path_index) const {
	// make this volume alignable
	std::stringstream full_path;
	full_path << gGeoMan->GetPath() << "/" << node->GetName();
	gGeoMan->cd(full_path.str().c_str());

	bool found(false);
	// first check if this node name is found in any of the navigation paths
	for (auto const& path_part : navigation_paths) {
		if (std::string(node->GetName()).find(path_part.first) != std::string::npos) {
			found = true;
			break;
		}
	}

	if (found) {
		if (std::string(node->GetName()).find(navigation_paths[current_navigation_path_index].first)
		    != std::string::npos) {
			if (navigation_paths[current_navigation_path_index].second) gGeoMan->SetAlignableEntry(
			    full_path.str().c_str(), full_path.str().c_str());
		}
		else {
			std::runtime_error("geokoaladetector::makeNodesAlignable(): Volume path structure "
					"is mismatching!");
		}
	}

	for (int i = 0; i < node->GetNdaughters(); ++i) {
		makeNodesAlignable(node->GetDaughter(i), current_navigation_path_index + 1);
	}
	gGeoMan->CdUp();
}












