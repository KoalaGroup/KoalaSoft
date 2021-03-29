/*
 * PndLmdGeometryFactory.cxx
 *
 *  Created on: Nov 6, 2017
 *      Author: steve
 */

#include "PndLmdGeometryFactory.h"

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

PndLmdGeometryFactory::PndLmdGeometryFactory(const ptree& geometry_property_tree_) :
		geometry_property_tree(geometry_property_tree_), gGeoMan(
		    (TGeoManager*) gROOT->FindObject("FAIRGeom")) {
	auto pt_general = geometry_property_tree.get_child("general");
	for (ptree::value_type& nav_path : pt_general.get_child("navigation_paths")) {
		navigation_paths.push_back(
		    std::make_pair(nav_path.second.get<std::string>("name"),
		        nav_path.second.get<bool>("is_alignable")));
	}
}

PndLmdGeometryFactory::~PndLmdGeometryFactory() {
}

void PndLmdGeometryFactory::init(FairGeoLoader* geoLoad) {
	retrieveMaterial(geoLoad);
}

void PndLmdGeometryFactory::retrieveMaterial(FairGeoLoader* geoLoad) {
	FairGeoMedia* Media = geoLoad->getGeoInterface()->getMedia();
	FairGeoBuilder* geobuild = geoLoad->getGeoBuilder();

	// retrieve available media
	FairGeoMedium* FairMediumAir = Media->getMedium("air");
	FairGeoMedium* FairMediumSteel = Media->getMedium("steel");
	FairGeoMedium* FairMediumAl = Media->getMedium("Aluminum");
	FairGeoMedium* FairMediumSilicon = Media->getMedium("silicon");
	FairGeoMedium* FairMediumDiamond = Media->getMedium("HYPdiamond");
	FairGeoMedium* FairMediumVacuum = Media->getMedium("vacuum7");
	FairGeoMedium* FairMediumKapton = Media->getMedium("kapton");
	FairGeoMedium* FairMediumCopper = Media->getMedium("copper");
	FairGeoMedium* FairMediumGlassFiber = Media->getMedium("GlassFiber");

	if (!FairMediumAir || !FairMediumSteel || !FairMediumAl || !FairMediumKapton || !FairMediumSilicon
	    || !FairMediumVacuum || !FairMediumCopper) {
		LOG(ERROR) << "PndLmdGeometryFactory::retrieveMaterial: not all media found ";
		return;
	}

	geobuild->createMedium(FairMediumAir);
	geobuild->createMedium(FairMediumSteel);
	geobuild->createMedium(FairMediumAl);
	geobuild->createMedium(FairMediumKapton);
	geobuild->createMedium(FairMediumSilicon);
	geobuild->createMedium(FairMediumDiamond);
	geobuild->createMedium(FairMediumVacuum);
	geobuild->createMedium(FairMediumCopper);
	geobuild->createMedium(FairMediumGlassFiber);
}

TGeoVolumeAssembly* PndLmdGeometryFactory::generateLmdGeometry() const {
	auto pt_general = geometry_property_tree.get_child("general");

	double pipe_bend_segment_phi(pt_general.get<double>("pipe_bend_segment_phi"));

	TGeoRotation* lmd_rot = new TGeoRotation("lmd_rot");
	lmd_rot->RotateX(0.0);
	lmd_rot->RotateY(pipe_bend_segment_phi / 3.14 * 180.);
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
	TGeoCombiTrans* lmd_frame_transformation = new TGeoCombiTrans("lmd_translation", shift_x_from_dipole,
	    0., box_center_position_z, lmd_rot);

	// upstream_beampipe_connection_z_position

	TGeoVolumeAssembly* top = new TGeoVolumeAssembly("lmd_top");
	gGeoMan->SetTopVolume(top);

	// create the reference system of the lmd
	TGeoVolumeAssembly* lmd_vol = new TGeoVolumeAssembly(navigation_paths[0].first.c_str());

	// generate vacuum box
	lmd_vol->AddNode(generateLmdBox(), 0);
	// generate beam pipe segment
	lmd_vol->AddNode(generateBeamPipe(), 0);

	// add half detectors
	lmd_vol->AddNode(generateDetectorHalf(false), 0);
	lmd_vol->AddNode(generateDetectorHalf(true), 1);

	// create lmd box vacuum
	// lmd_vol->AddNode(generateBoxVacuum(lmd_vol), 0);

	// place correctly in mother volume
	top->AddNode(lmd_vol, 0, lmd_frame_transformation);

	gGeoMan->CloseGeometry();

	makeNodesAlignable();
	std::cout << "Number of alignable volumes: " << gGeoMan->GetNAlignable() << std::endl;

	return top;
}

TGeoVolume* PndLmdGeometryFactory::generateLmdBox() const {
	auto pt_general = geometry_property_tree.get_child("general");
	auto pt_vac_box = geometry_property_tree.get_child("vacuum_box");

	// general remark: watch out! TGeoShape values are often given has half sizes!
	double box_dim_x(pt_vac_box.get<double>("dimension_x"));
	double box_dim_y(pt_vac_box.get<double>("dimension_y"));
	double box_dim_z(pt_vac_box.get<double>("dimension_z"));
	double box_thickness(pt_vac_box.get<double>("wall_thickness"));

	// the lmd box
	new TGeoBBox("lmd_box_outer", box_dim_x / 2.0, box_dim_y / 2.0, box_dim_z / 2.0);
	new TGeoBBox("lmd_box_inner", box_dim_x / 2.0 - box_thickness, box_dim_y / 2.0 - box_thickness,
	    box_dim_z / 2.0 - box_thickness);

	// the two beampipe holes
	new TGeoTube("box_hole_upstream", 0.0,
	    geometry_property_tree.get_child("beam_pipe.entrance_pipe").get<double>("inner_radius"),
	    box_thickness / 2.0 + 0.1);  // 0.1 safety margin
	// move the cut pipe upstream
	TGeoTranslation* comb_trans_cut_pipe_upstream = new TGeoTranslation("comb_trans_cut_pipe_upstream", 0.,
	    0., -box_dim_z / 2.0 + box_thickness / 2.0);
	comb_trans_cut_pipe_upstream->RegisterYourself();

	new TGeoTube("box_hole_downstream", 0.0,
	    geometry_property_tree.get_child("beam_pipe.exit_pipe").get<double>("inner_radius"),
	    box_thickness / 2.0 + 0.1);
	// move the cut pipe downstream
	TGeoTranslation* comb_trans_cut_pipe_downstream = new TGeoTranslation("comb_trans_cut_pipe_downstream",
	    0., 0., +box_dim_z / 2.0 - box_thickness / 2.0);
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
	TGeoTranslation* comb_trans_rib = new TGeoTranslation("comb_trans_rib", 0., 0.,
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
	    "(lmd_box_outer-lmd_box_inner + ((lmd_box_rib-rib_hole):comb_trans_rib))"
			    "-box_hole_upstream:comb_trans_cut_pipe_upstream"
			    "-box_hole_downstream:comb_trans_cut_pipe_downstream"
			    "+lmd_box_clash_plate_left+lmd_box_clash_plate_right");

	TGeoVolume* lmd_vol_box = new TGeoVolume("lmd_vol_box", shape_lmd_box, gGeoMan->GetMedium("steel"));
	lmd_vol_box->SetLineColor(11);

	return lmd_vol_box;
}

TGeoVolume* PndLmdGeometryFactory::generateBeamPipe() const {
	TGeoVolumeAssembly* lmd_beam_pipe = new TGeoVolumeAssembly("lmd_beam_pipe");

	auto pt_vac_box = geometry_property_tree.get_child("vacuum_box");
	auto pt_beam_pipe = geometry_property_tree.get_child("beam_pipe");

	double box_dim_z = pt_vac_box.get<double>("dimension_z");

	// upstream pipe part - outside of lmd
	auto pt_ent_pipe = pt_beam_pipe.get_child("entrance_pipe");
	double entrance_inner_radius(pt_ent_pipe.get<double>("inner_radius"));
	TGeoTube* pipe_upstream = new TGeoTube("pipe_upstream", entrance_inner_radius,
	    entrance_inner_radius + pt_ent_pipe.get<double>("thickness"),
	    pt_ent_pipe.get<double>("length") / 2.0);
	TGeoTranslation* comb_trans_pipe_upstream = new TGeoTranslation("comb_trans_pipe_upstream", 0., 0.,
	    -box_dim_z / 2.0 - pt_ent_pipe.get<double>("length") / 2.0);
	TGeoVolume* lmd_vol_pipe_up = new TGeoVolume("lmd_vol_pipe_up", pipe_upstream,
	    gGeoMan->GetMedium("steel"));
	lmd_vol_pipe_up->SetLineColor(11);
	lmd_beam_pipe->AddNode(lmd_vol_pipe_up, 0, comb_trans_pipe_upstream);

	// clamp for transition cone steel and aluminum part
	auto pt_cone_clamp = pt_beam_pipe.get_child("cone_clamp_ring");
	double cone_clamp_outer_radius = pt_cone_clamp.get<double>("outer_radius");
	double steel_part_thickness = pt_cone_clamp.get<double>("steel_part_thickness");
	double alu_part_thickness = pt_cone_clamp.get<double>("aluminum_part_thickness");
	double cone_angle = pt_beam_pipe.get_child("transition_cone").get<double>("angle_in_degrees")
	    * TMath::Pi() / 180;

	TGeoPcon* steel_cone_clamp = new TGeoPcon(0., 360., 4);
	steel_cone_clamp->DefineSection(0, 0.0, entrance_inner_radius, cone_clamp_outer_radius);
	steel_cone_clamp->DefineSection(1, steel_part_thickness, entrance_inner_radius,
	    cone_clamp_outer_radius);
	steel_cone_clamp->DefineSection(2, steel_part_thickness, entrance_inner_radius,
	    entrance_inner_radius + alu_part_thickness * std::tan(cone_angle));
	steel_cone_clamp->DefineSection(3, steel_part_thickness + alu_part_thickness, entrance_inner_radius,
	    entrance_inner_radius);

	TGeoVolume* steel_cone_clamp_vol = new TGeoVolume("steel_cone_clamp_vol", steel_cone_clamp,
	    gGeoMan->GetMedium("steel"));
	steel_cone_clamp_vol->SetLineColor(11);
	double cone_clamp_start_pos_z = -box_dim_z / 2.0 + pt_vac_box.get<double>("wall_thickness");
	TGeoTranslation* lmd_trans_lmd_cone_clamp = new TGeoTranslation("lmd_trans_lmd_cone_clamp", 0., 0.,
	    cone_clamp_start_pos_z);
	lmd_trans_lmd_cone_clamp->RegisterYourself();
	lmd_beam_pipe->AddNode(steel_cone_clamp_vol, 0, lmd_trans_lmd_cone_clamp);

	TGeoPcon* alu_cone_clamp = new TGeoPcon(0., 360., 2);
	alu_cone_clamp->DefineSection(0, steel_part_thickness,
	    entrance_inner_radius + alu_part_thickness * std::tan(cone_angle), cone_clamp_outer_radius);
	alu_cone_clamp->DefineSection(1, steel_part_thickness + alu_part_thickness, entrance_inner_radius,
	    cone_clamp_outer_radius);

	TGeoVolume* alu_cone_clamp_vol = new TGeoVolume("alu_cone_clamp_vol", alu_cone_clamp,
	    gGeoMan->GetMedium("Aluminum"));
	alu_cone_clamp_vol->SetLineColor(kGray);
	lmd_beam_pipe->AddNode(alu_cone_clamp_vol, 0, lmd_trans_lmd_cone_clamp);

	// transition cone
	auto pt_cone = pt_beam_pipe.get_child("transition_cone");
	double alu_cone_thickness(pt_cone.get<double>("aluminum_thickness"));
	double polyamide_cone_thickness(pt_cone.get<double>("polyamide_thickness"));
	auto pt_inner_pipe = pt_beam_pipe.get_child("inner_pipe");
	double inner_beampipe_outer_radius(pt_inner_pipe.get<double>("outer_radius"));
	double inner_beampipe_thickness(pt_inner_pipe.get<double>("thickness"));
	double inner_beampipe_inner_radius(inner_beampipe_outer_radius - inner_beampipe_thickness);
	double cone_length = (entrance_inner_radius - inner_beampipe_inner_radius) / std::tan(cone_angle);

	TGeoCone* lmd_al_cone = new TGeoCone("lmd_al_cone", cone_length / 2.0, entrance_inner_radius,
	    entrance_inner_radius + alu_cone_thickness, inner_beampipe_inner_radius,
	    inner_beampipe_inner_radius + alu_cone_thickness);
	TGeoVolume* vol_al_cone = new TGeoVolume("al_cone", lmd_al_cone, gGeoMan->GetMedium("Aluminum"));
	vol_al_cone->SetLineColor(kGray);  // 39);
	TGeoTranslation* lmd_trans_cone = new TGeoTranslation("lmd_trans_cone", 0., 0.,
	    cone_clamp_start_pos_z + steel_part_thickness + alu_part_thickness + cone_length / 2.0);
	lmd_trans_cone->RegisterYourself();
	lmd_beam_pipe->AddNode(vol_al_cone, 0, lmd_trans_cone);

	TGeoCone* lmd_capton_cone = new TGeoCone("lmd_capton_cone", cone_length / 2.0,
	    entrance_inner_radius + alu_cone_thickness,
	    entrance_inner_radius + alu_cone_thickness + polyamide_cone_thickness,
	    inner_beampipe_inner_radius + alu_cone_thickness,
	    inner_beampipe_inner_radius + alu_cone_thickness + polyamide_cone_thickness);
	TGeoVolume* vol_capton_cone = new TGeoVolume("capton_cone", lmd_capton_cone,
	    gGeoMan->GetMedium("kapton"));
	vol_capton_cone->SetLineColor(kRed);  // 39);
	lmd_beam_pipe->AddNode(vol_capton_cone, 0, lmd_trans_cone);

	// inner beam pipe part
	double inner_beampipe_length(pt_inner_pipe.get<double>("length"));
	double inner_beampipe_cone_foil_attach_segement_length(
	    pt_inner_pipe.get<double>("length_cone_foil_attach_segment"));
	double outer_radius_cone_foil_glue_segment(
	    inner_beampipe_outer_radius
	        + std::tan(cone_angle) * inner_beampipe_cone_foil_attach_segement_length);

	TGeoPcon* lmd_inner_pipe = new TGeoPcon(0.0, 360.0, 3);
	lmd_inner_pipe->DefineSection(0, 0.0, outer_radius_cone_foil_glue_segment - inner_beampipe_thickness,
	    outer_radius_cone_foil_glue_segment);
	lmd_inner_pipe->DefineSection(1, inner_beampipe_cone_foil_attach_segement_length,
	    inner_beampipe_inner_radius, inner_beampipe_outer_radius);
	lmd_inner_pipe->DefineSection(2,
	    inner_beampipe_cone_foil_attach_segement_length + inner_beampipe_length,
	    inner_beampipe_inner_radius, inner_beampipe_outer_radius);

	TGeoVolume* vol_inner_pipe = new TGeoVolume("vol_inner_pipe", lmd_inner_pipe,
	    gGeoMan->GetMedium("steel"));
	vol_inner_pipe->SetLineColor(11);  // 39);
	double inner_pipe_start_position_z(
	    cone_clamp_start_pos_z + steel_part_thickness + alu_part_thickness + cone_length
	        - inner_beampipe_cone_foil_attach_segement_length);
	TGeoTranslation* lmd_trans_inner_pipe = new TGeoTranslation("lmd_trans_inner_pipe", 0., 0.,
	    inner_pipe_start_position_z);
	lmd_trans_inner_pipe->RegisterYourself();
	lmd_beam_pipe->AddNode(vol_inner_pipe, 0, lmd_trans_inner_pipe);

	// bellow
	auto pt_exit_pipe = pt_beam_pipe.get_child("exit_pipe");
	double inner_exit_radius = pt_exit_pipe.get<double>("inner_radius");

	auto pt_bellow = pt_beam_pipe.get_child("bellow");
	double flange_to_inner_pipe_outer_radius(
	    inner_beampipe_inner_radius
	        + pt_bellow.get<double>("flange_to_inner_beampipe.outer_radius_increase"));
	TGeoPcon* beampipe_bellow = new TGeoPcon(0., 360., 6);
	double tempzpos(
	    inner_pipe_start_position_z + inner_beampipe_cone_foil_attach_segement_length
	        + inner_beampipe_length);
	beampipe_bellow->DefineSection(0, tempzpos, inner_beampipe_inner_radius,
	    flange_to_inner_pipe_outer_radius);
	tempzpos += pt_bellow.get<double>("flange_to_inner_beampipe.thickness");
	beampipe_bellow->DefineSection(1, tempzpos, inner_beampipe_inner_radius,
	    flange_to_inner_pipe_outer_radius);
	tempzpos += pt_bellow.get<double>("flange_to_inner_beampipe.outer_radius_increase")
	    / std::tan(pt_bellow.get<double>("inner_angle_in_degrees") / 180 * TMath::Pi());
	beampipe_bellow->DefineSection(2, tempzpos, inner_exit_radius,
	    inner_exit_radius + pt_bellow.get<double>("thickness"));
	tempzpos += (box_dim_z / 2.0 - pt_vac_box.get<double>("wall_thickness") - tempzpos
	    - pt_bellow.get<double>("flange_to_box.thickness"));
	beampipe_bellow->DefineSection(3, tempzpos, inner_exit_radius,
	    inner_exit_radius + pt_bellow.get<double>("thickness"));
	beampipe_bellow->DefineSection(4, tempzpos, inner_exit_radius,
	    inner_exit_radius + pt_bellow.get<double>("thickness")
	        + pt_bellow.get<double>("flange_to_box.outer_radius_increase"));
	tempzpos += pt_bellow.get<double>("flange_to_box.thickness");
	beampipe_bellow->DefineSection(5, tempzpos, inner_exit_radius,
	    inner_exit_radius + pt_bellow.get<double>("thickness")
	        + pt_bellow.get<double>("flange_to_box.outer_radius_increase"));

	TGeoVolume* vol_beampipe_bellow = new TGeoVolume("vol_beampipe_bellow", beampipe_bellow,
	    gGeoMan->GetMedium("steel"));
	vol_beampipe_bellow->SetLineColor(11);  // 39);
	lmd_beam_pipe->AddNode(vol_beampipe_bellow, 0);

	// downstream pipe part - outside of lmd
	double outer_exit_radius = inner_exit_radius + pt_exit_pipe.get<double>("thickness");
	double tube_length = pt_exit_pipe.get<double>("length");
	double flange_outer_radius = pt_exit_pipe.get<double>("flange_outer_radius");
	double flange_thickness = pt_exit_pipe.get<double>("flange_thickness");

	TGeoPcon* shape_pipe_box_do = new TGeoPcon(0., 360., 4);
	shape_pipe_box_do->DefineSection(0, box_dim_z / 2.0, inner_exit_radius, outer_exit_radius);
	shape_pipe_box_do->DefineSection(1, box_dim_z / 2.0 + tube_length - flange_thickness,
	    inner_exit_radius, outer_exit_radius);
	shape_pipe_box_do->DefineSection(2, box_dim_z / 2.0 + tube_length - flange_thickness,
	    inner_exit_radius, flange_outer_radius);
	shape_pipe_box_do->DefineSection(3, box_dim_z / 2.0 + tube_length, inner_exit_radius,
	    flange_outer_radius);

	TGeoVolume* vlum_pipe_box_do = new TGeoVolume("vlum_pipe_box_do", shape_pipe_box_do,
	    gGeoMan->GetMedium("steel"));
	vlum_pipe_box_do->SetLineColor(11);  // 39);
	lmd_beam_pipe->AddNode(vlum_pipe_box_do, 0);

	return lmd_beam_pipe;
}

TGeoVolume* PndLmdGeometryFactory::generateDetectorHalf(bool is_bottom_half) const {
	std::vector<double> plane_z_positions;
	auto pt_general = geometry_property_tree.get_child("general");
	for (ptree::value_type& plane_z : pt_general.get_child("plane_z_positions")) {
		plane_z_positions.push_back(plane_z.second.get_value<double>());
	}

	TGeoVolumeAssembly* lmd_vol_half = new TGeoVolumeAssembly(navigation_paths[1].first.c_str());

	// create a detector plane volume
	TGeoVolume* lmd_vol_plane = generateDetectorHalfPlane(is_bottom_half);
	// now loop over number of planes and make copies of the plane
	// and align them correctly

	// determine shift of planes with respect to box center
	double box_center_position_z(
	    pt_general.get<double>("upstream_beampipe_connection_z_position")
	        + geometry_property_tree.get<double>("vacuum_box.dimension_z") / 2.0
	        + geometry_property_tree.get<double>("beam_pipe.entrance_pipe.length"));
	double z_shift(
	    geometry_property_tree.get<double>("general.first_plane_position_z") - box_center_position_z);
	for (unsigned int i = 0; i < plane_z_positions.size(); ++i) {
		TGeoTranslation* trans_module = new TGeoTranslation(0.0, 0.0, plane_z_positions[i] + z_shift);
		lmd_vol_half->AddNode(lmd_vol_plane, i, trans_module);
	}
	return lmd_vol_half;
}

TGeoVolume* PndLmdGeometryFactory::generateDetectorHalfPlane(bool is_bottom_half) const {
	TGeoVolumeAssembly* lmd_vol_plane = new TGeoVolumeAssembly(navigation_paths[2].first.c_str());

	TGeoVolume* alu_cooling_half_ring = generateAluminumCoolingStructure();
	TGeoVolume* pcb_board_half_ring = generatePCB();
	TGeoRotation* rot_alu_ring = new TGeoRotation();
	TGeoRotation* rot_back_pcb = new TGeoRotation();
	rot_back_pcb->RotateY(180.0);
	if (is_bottom_half) {
		rot_alu_ring->RotateZ(180.0);
		rot_back_pcb->RotateZ(180.0);
	}
	TGeoCombiTrans* trans_pcb_half_ring = new TGeoCombiTrans("trans_pcb_half_ring", 0.0, 0.0,
	    -geometry_property_tree.get<double>("electronics.distance_between_pcb_and_cooling_support")
	        - 0.5
	            * (geometry_property_tree.get<double>("cooling_support.thickness")
	                + geometry_property_tree.get<double>("electronics.pcb_board.thickness_copper")
	                + geometry_property_tree.get<double>("electronics.pcb_board.thickness_glasfiber")),
	    rot_alu_ring);
	TGeoCombiTrans* trans_pcb_half_ring_back = new TGeoCombiTrans("trans_pcb_half_ring", 0.0, 0.0,
	    geometry_property_tree.get<double>("electronics.distance_between_pcb_and_cooling_support")
	        + 0.5 * geometry_property_tree.get<double>("cooling_support.thickness"), rot_back_pcb);
	lmd_vol_plane->AddNode(alu_cooling_half_ring, 0, rot_alu_ring);
	lmd_vol_plane->AddNode(pcb_board_half_ring, 0, trans_pcb_half_ring);
	lmd_vol_plane->AddNode(pcb_board_half_ring, 1, trans_pcb_half_ring_back);

	TGeoVolume* detector_module = generateSensorModule();

	unsigned int num_modules_per_plane(
	    geometry_property_tree.get<double>("general.modules_per_half_plane"));
	double relative_module_shift_z(
	    geometry_property_tree.get<double>("general.relative_module_distance_z") / 2.0);
	unsigned int index_offset(0);
	if (is_bottom_half) {
		index_offset += num_modules_per_plane;
		relative_module_shift_z *= -1;  // lower half modules need relative z shift to top half neighbors
	}
	for (unsigned int i = 0; i < num_modules_per_plane; ++i) {
		TGeoRotation* rot_module = new TGeoRotation();
		rot_module->RotateZ(180.0 / num_modules_per_plane * (i + index_offset));
		relative_module_shift_z *= -1;
		TGeoCombiTrans* rottrans_module = new TGeoCombiTrans(0.0, 0.0, relative_module_shift_z, rot_module);
		lmd_vol_plane->AddNode(detector_module, i, rottrans_module);
	}

	return lmd_vol_plane;
}

TGeoVolume* PndLmdGeometryFactory::generateAluminumCoolingStructure() const {
	auto pt_cool_support = geometry_property_tree.get_child("cooling_support");

	double outer_radius(pt_cool_support.get<double>("outer_radius"));
	double inner_radius(pt_cool_support.get<double>("inner_radius"));

	// NOTE: DO NOT use tgeotubeseg because of "bug" with root in combination with
	// fairroot
	//(only fixed in root 6.10 or higher but not verified)

	// construct first a tube segment
	new TGeoTube("cool_support_tube", inner_radius, outer_radius,
	    pt_cool_support.get<double>("thickness") / 2.0);

	// cut off lower half and bit more to adapt to clash planes
	double clash_plane_thickness(
	    geometry_property_tree.get<double>("vacuum_box.horizontal_detector_half_clash_plates.thickness"));

	// +0.1 are added to make the cutting volume slightly bigger
	// to avoid having tiny edge left overs due to floating point
	new TGeoBBox("cool_support_tube_cutoff", outer_radius + 0.1,
	    outer_radius / 2.0 + clash_plane_thickness / 2.0 + 0.1,
	    pt_cool_support.get<double>("thickness") + 0.1);

	TGeoTranslation* trans_tube_cut = new TGeoTranslation("trans_tube_cut", 0.0,
	    -outer_radius / 2.0 - 0.1 + 0.0001, 0.);
	// 0.0001 make 1mu space between clash plane and alu support to avoid overlap
	trans_tube_cut->RegisterYourself();

	// construct the support from basic shape and it's cut outs
	TGeoCompositeShape* cool_support = new TGeoCompositeShape("cool_support",
	    "cool_support_tube-cool_support_tube_cutoff:trans_tube_cut");

	TGeoVolume* aluminum_support_volume = new TGeoVolume("vol_cool_support", cool_support,
	    gGeoMan->GetMedium("Aluminum"));
	aluminum_support_volume->SetLineColor(kGray);
	return aluminum_support_volume;
}

TGeoVolume* PndLmdGeometryFactory::generatePCB() const {
	TGeoVolumeAssembly* pcb_volume = new TGeoVolumeAssembly("pcb");
	auto pt_electronics = geometry_property_tree.get_child("electronics");

	double outer_radius(pt_electronics.get<double>("pcb_board.outer_radius"));
	double inner_radius(pt_electronics.get<double>("pcb_board.inner_radius"));
	double pcb_copper_thickness(pt_electronics.get<double>("pcb_board.thickness_copper"));
	double pcb_glasfiber_thickness(pt_electronics.get<double>("pcb_board.thickness_glasfiber"));

	// NOTE: DO NOT use tgeotubeseg because of "bug" with root in combination with
	// fairroot
	//(only fixed in root 6.10 or higher but not verified)

	// construct first a tube
	new TGeoTube("pcb_board_tube", inner_radius, outer_radius, pcb_glasfiber_thickness / 2.0);
	new TGeoTube("pcb_copper_tube", inner_radius, outer_radius, pcb_copper_thickness / 2.0);

	// cut off lower half and bit more to adapt to clash planes
	double clash_plane_thickness(
	    geometry_property_tree.get<double>("vacuum_box.horizontal_detector_half_clash_plates.thickness"));
	// we cut a little more than for the cooling support
	double additional_bottom_cutoff(pt_electronics.get<double>("pcb_board.bottom_cutoff"));
	// +0.1 are added to make the cutting volume slightly bigger
	// to avoid having tiny edge left overs due to floating point
	new TGeoBBox("pcb_full_cutoff", outer_radius + 0.1,
	    outer_radius / 2.0 + clash_plane_thickness / 2.0 + additional_bottom_cutoff + 0.1,
	    pcb_glasfiber_thickness + pcb_copper_thickness + 0.1);

	TGeoTranslation* trans_pcb_tube_cut = new TGeoTranslation("trans_pcb_tube_cut", 0.0,
	    -outer_radius / 2.0 - 0.1 + 0.0001, 0.);
	// 0.0001 make 1mu space between clash plane and alu support to avoid overlap
	trans_pcb_tube_cut->RegisterYourself();

	// volume to cut out the holes for the steel mounting screws
	//new TGeoTube("pcb_steel_mount_screw_cutout", 0.0,
	//    pt_electronics.get<double>("steel_mount_screws.diameter") / 2.0,
	//    (pcb_glasfiber_thickness + pcb_copper_thickness) / 2.0);
	TGeoVolume *steel_mount_screw = generatePCBMountScrew();

	std::stringstream ss;
	double start_angle(pt_electronics.get<double>("steel_mount_screws.angle_first_screw"));
	double delta_angle(pt_electronics.get<double>("steel_mount_screws.angle_between_screws"));
	double hole_position_radius(
	    outer_radius - pt_electronics.get<double>("steel_mount_screws.distance_to_outer_support_edge"));
	for (unsigned int i = 0; i < pt_electronics.get<double>("steel_mount_screws.number_of_screws"); ++i) {
		std::string transname("screw_hole_trans_" + i);
		double angle(start_angle + delta_angle * i);
		TGeoTranslation* screw_hole_trans = new TGeoTranslation(transname.c_str(),
		    hole_position_radius * std::cos(angle / 180 * TMath::Pi()),
		    hole_position_radius * std::sin(angle / 180 * TMath::Pi()),
		    -0.5
		        * (pt_electronics.get<double>("distance_between_pcb_and_cooling_support")
		            + pt_electronics.get<double>("steel_mount_screws.screw_head_size"))
		        + pt_electronics.get<double>("distance_between_pcb_and_cooling_support"));
		// subtract the mounting screw from the pcb board
		screw_hole_trans->RegisterYourself();
		ss << "-" << steel_mount_screw->GetShape()->GetName() << ":" << transname;
		// add the mounting screw
		pcb_volume->AddNode(steel_mount_screw, i, screw_hole_trans);
	}

	// construct the support from basic shape and it's cut outs
	TGeoCompositeShape * pcb_shape = new TGeoCompositeShape("pcb_shape",
	    (std::string("pcb_board_tube-pcb_full_cutoff:trans_pcb_tube_cut") + ss.str()).c_str());
	// construct the support from basic shape and it's cut outs
	TGeoCompositeShape* pcb_copper_shape = new TGeoCompositeShape("pcb_copper_shape",
	    (std::string("pcb_copper_tube-pcb_full_cutoff:trans_pcb_tube_cut") + ss.str()).c_str());

	TGeoTranslation* trans_pcb_copper = new TGeoTranslation("trans_pcb_copper", 0.0, 0.0,
	    -0.5 * (pcb_copper_thickness + pcb_glasfiber_thickness + 0.0001));
	// make half mu space between to avoid overlap
	trans_pcb_copper->RegisterYourself();

	TGeoVolume* pcb_glasfiber_volume = new TGeoVolume("vol_pcb_glassfiber", pcb_shape,
	    gGeoMan->GetMedium("GlassFiber"));
	pcb_glasfiber_volume->SetLineColor(30);
	TGeoVolume* pcb_copper_volume = new TGeoVolume("vol_pcb_copper", pcb_copper_shape,
	    gGeoMan->GetMedium("copper"));
	pcb_copper_volume->SetLineColor(kOrange + 1);
	pcb_volume->AddNode(pcb_glasfiber_volume, 0);
	pcb_volume->AddNode(pcb_copper_volume, 0, trans_pcb_copper);

	// add copper plug on the front side, one for each module
	unsigned int modules_per_half_plane(
	    geometry_property_tree.get<double>("general.modules_per_half_plane"));
	TGeoVolume* copper_plug = generatePCBCopperPlug();
	double middle_radius(0.5 * (inner_radius + outer_radius));
	double ang_segment_module(180.0 / modules_per_half_plane);
	for (unsigned int i = 0; i < modules_per_half_plane; ++i) {
		double angle((0.5 + i) * ang_segment_module);
		TGeoRotation *rot = new TGeoRotation();
		rot->RotateZ(angle);
		TGeoCombiTrans *trafo = new TGeoCombiTrans(middle_radius * std::cos(angle / 180.0 * TMath::Pi()),
		    middle_radius * std::sin(angle / 180.0 * TMath::Pi()),
		    -pcb_copper_thickness
		        - 0.5
		            * (pcb_glasfiber_thickness + pt_electronics.get<double>("copper_plugs.thickness")
		                + 0.0001), rot);

		pcb_volume->AddNode(copper_plug, i, trafo);
	}

	// add electronic chips on back side
	TGeoVolume* backside_electronic_chip = generatePCBBacksideElectronics();
	unsigned int segments(pt_electronics.get<double>("backside_electronics.segments"));
	unsigned int chips_per_segment(pt_electronics.get<double>("backside_electronics.chips_per_segment"));
	double be_start_angle(pt_electronics.get<double>("backside_electronics.angle_first_segment"));
	double ang_segment(
	    (pt_electronics.get<double>("backside_electronics.angle_last_segment") - be_start_angle)
	        / (segments-1));
	for (unsigned int i = 0; i < segments; ++i) {
		for (unsigned int j = 0; j < chips_per_segment; ++j) {
			double angle(be_start_angle + i * ang_segment);
			TGeoRotation *rot = new TGeoRotation();
			rot->RotateZ(angle);
			double radius_delta(
			    (-0.5 * (chips_per_segment + 1) + j)
			        * (pt_electronics.get<double>("backside_electronics.dimension_x") + 0.2));
			TGeoCombiTrans *trafo = new TGeoCombiTrans(
			    (middle_radius + radius_delta) * std::cos(angle / 180.0 * TMath::Pi()),
			    (middle_radius + radius_delta) * std::sin(angle / 180.0 * TMath::Pi()),
			    0.5
			        * (pcb_glasfiber_thickness + pt_electronics.get<double>("backside_electronics.thickness")
			            + 0.0001), rot);

			pcb_volume->AddNode(backside_electronic_chip, i * chips_per_segment + j, trafo);
		}
	}

	return pcb_volume;
}

TGeoVolume* PndLmdGeometryFactory::generatePCBMountScrew() const {
	auto pt_mountscrews = geometry_property_tree.get_child("electronics.steel_mount_screws");
	// volume to cut out the holes for the steel mounting screws
	TGeoTube *steel_mount_screw = new TGeoTube("pcb_steel_mount_screw", 0.0,
	    pt_mountscrews.get<double>("diameter") / 2.0,
	    (geometry_property_tree.get<double>("electronics.distance_between_pcb_and_cooling_support")
	        + pt_mountscrews.get<double>("screw_head_size")) / 2.0);
	TGeoVolume* steel_mount_screw_volume = new TGeoVolume("vol_steel_mount_screw", steel_mount_screw,
	    gGeoMan->GetMedium("steel"));
	steel_mount_screw_volume->SetLineColor(11);
	return steel_mount_screw_volume;
}

TGeoVolume* PndLmdGeometryFactory::generatePCBCopperPlug() const {
	auto pt_copperplugs = geometry_property_tree.get_child("electronics.copper_plugs");

	TGeoBBox *pcb_copper_plug = new TGeoBBox("pcb_copper_plug",
	    pt_copperplugs.get<double>("dimension_x") / 2.0, pt_copperplugs.get<double>("dimension_y") / 2.0,
	    pt_copperplugs.get<double>("thickness") / 2.0);

	TGeoVolume* pcb_copper_plug_volume = new TGeoVolume("vol_pcb_copper_plug", pcb_copper_plug,
	    gGeoMan->GetMedium("copper"));
	pcb_copper_plug_volume->SetLineColor(kOrange + 2);
	return pcb_copper_plug_volume;
}

TGeoVolume* PndLmdGeometryFactory::generatePCBBacksideElectronics() const {
	auto pt_be = geometry_property_tree.get_child("electronics.backside_electronics");

	TGeoBBox *pcb_backside_electronic = new TGeoBBox("pcb_backside_electronic",
	    pt_be.get<double>("dimension_x") / 2.0, pt_be.get<double>("dimension_y") / 2.0,
	    pt_be.get<double>("thickness") / 2.0);

	TGeoVolume* pcb_backside_electronic_volume = new TGeoVolume(
	    pt_be.get<std::string>("volume_name").c_str(), pcb_backside_electronic,
	    gGeoMan->GetMedium("silicon"));
	pcb_backside_electronic_volume->SetLineColor(kYellow);
	return pcb_backside_electronic_volume;
}

TGeoVolume* PndLmdGeometryFactory::generateSensorModule() const {
	TGeoVolumeAssembly* lmd_vol_module = new TGeoVolumeAssembly(navigation_paths[3].first.c_str());

	// generate cvd cooling disk
	TGeoVolume* cvd_disc = generateCVDCoolingDisc();
	lmd_vol_module->AddNode(cvd_disc, 0);

	// generate a sensor and replicate it on the module
	TGeoVolume* sensor = generateSensor();

	unsigned int num_modules_per_plane(
	    geometry_property_tree.get<double>("general.modules_per_half_plane"));
	double cvd_disc_inner_radius(
	    geometry_property_tree.get<double>("cooling_support.cvd_disc.inner_radius"));
	double cvd_disc_outer_radius(geometry_property_tree.get<double>("cooling_support.inner_radius"));
	double cvd_disc_thickness(geometry_property_tree.get<double>("cooling_support.cvd_disc.thickness"));
	double sensor_dim_x(geometry_property_tree.get<double>("sensors.dimension_x"));
	double sensor_dim_y(geometry_property_tree.get<double>("sensors.dimension_y"));
	double sensor_thickness(geometry_property_tree.get<double>("sensors.thickness"));

	unsigned int num_sensors_per_module_side(
	    geometry_property_tree.get<unsigned int>("general.sensors_per_module_side"));

	TGeoRotation* rot_all_sensors_front = new TGeoRotation("rot_all_sensors", 0.0, 0.0, 0.0);

	unsigned int column_counter(0);
	double current_row_x_shift(0.0);
	double current_row_y_shift(0.0);
	for (unsigned int i = 0; i < num_sensors_per_module_side; ++i) {
		// check if sensors overlap the cvd disc and if so start a new row
		if (current_row_x_shift + sensor_dim_x * (column_counter + 1)
		    > cvd_disc_outer_radius - cvd_disc_inner_radius) {
			current_row_x_shift += geometry_property_tree.get<double>("general.offset_second_row_sensors_x");
			current_row_y_shift += sensor_dim_y;
			rot_all_sensors_front->RotateZ(
			    geometry_property_tree.get<double>("general.rotation_second_row_sensors_z"));

			// reset column counter
			column_counter = 0;
		}

		TGeoCombiTrans* rottrans_side_offset =
		    new TGeoCombiTrans(
		        (current_row_x_shift + 0.5 * sensor_dim_x + cvd_disc_inner_radius
		            + sensor_dim_x * column_counter), 0.5 * sensor_dim_y + current_row_y_shift,
		        -0.5 * sensor_thickness - 0.5 * cvd_disc_thickness, rot_all_sensors_front);
		lmd_vol_module->AddNode(sensor, i, rottrans_side_offset);

		++column_counter;
	}

	// now sensors on back (they need a flip rotation)
	TGeoRotation* rot_all_sensors_back = new TGeoRotation("rot_all_sensors", 0.0, 0.0, 0.0);
	rot_all_sensors_back->RotateX(180.0);
	rot_all_sensors_back->RotateZ(180.0 / num_modules_per_plane);

	column_counter = 0;
	current_row_x_shift = 0.0;
	current_row_y_shift = 0.0;
	for (unsigned int i = 0; i < num_sensors_per_module_side; ++i) {
		// check if sensors overlap the cvd disc and if so start a new row
		if (current_row_x_shift + sensor_dim_x * (column_counter + 1)
		    > cvd_disc_outer_radius - cvd_disc_inner_radius) {
			current_row_x_shift += geometry_property_tree.get<double>("general.offset_second_row_sensors_x");
			current_row_y_shift -= sensor_dim_y;
			rot_all_sensors_back->RotateZ(
			    geometry_property_tree.get<double>("general.rotation_second_row_sensors_z"));

			// reset column counter
			column_counter = 0;
		}

		// corrections from rotation
		double x_center(
		    current_row_x_shift + cvd_disc_inner_radius + sensor_dim_x * column_counter
		        + 0.5 * sensor_dim_x);

		// calculate corrections
		TGeoHMatrix rot;
		rot.RotateZ(180.0 / num_modules_per_plane);
		TGeoHMatrix trans;
		trans.SetDx(x_center);
		trans.SetDy(-0.5 * sensor_dim_y + current_row_y_shift);
		rot.Multiply(&trans);

		TGeoCombiTrans* rottrans_side_offset = new TGeoCombiTrans(rot.GetTranslation()[0],
		    rot.GetTranslation()[1], 0.5 * sensor_thickness + 0.5 * cvd_disc_thickness,
		    rot_all_sensors_back);
		lmd_vol_module->AddNode(sensor, num_sensors_per_module_side + i, rottrans_side_offset);

		++column_counter;
	}

	return lmd_vol_module;
}

TGeoVolume* PndLmdGeometryFactory::generateCVDCoolingDisc() const {
	auto pt_cool_support = geometry_property_tree.get_child("cooling_support");
	double alu_support_inner_radius(pt_cool_support.get<double>("inner_radius"));
	auto pt_cvd_disc = pt_cool_support.get_child("cvd_disc");
	unsigned int num_modules_per_half_plane(
	    geometry_property_tree.get<double>("general.modules_per_half_plane"));
	double gap_between_disc_and_support_structure(0.0);

	// this code cannot be used at the moment, because of "bug" in root
	// (version 6.10 or higher should have it fixed, but I could not verify this)
	// the "bug" is due to fairroot not importing geometries with the tgeomanager,
	// and the import function performs trigonometric calc (in case of
	// tgeotubeseg)

	/*TGeoTubeSeg* cvd_disc = new TGeoTubeSeg("cvd_disc",
	 pt_cvd_disc.get<double>("inner_radius"),
	 alu_support_inner_radius - gap_between_disc_and_support_structure,
	 pt_cvd_disc.get<double>("thickness") / 2.0, 0.0,
	 180.0 / num_modules_per_half_plane);*/

	new TGeoTube("cvd_disc_tube", pt_cvd_disc.get<double>("inner_radius"),
	    alu_support_inner_radius - gap_between_disc_and_support_structure,
	    pt_cvd_disc.get<double>("thickness") / 2.0);

	new TGeoBBox("cvd_disc_cut", alu_support_inner_radius + 0.1, alu_support_inner_radius / 2.0 + 0.1,
	    pt_cvd_disc.get<double>("thickness") / 2.0 + 0.1);
	TGeoTranslation* trans_bottom = new TGeoTranslation("trans_cvd_cut_bottom", 0.0,
	    -(alu_support_inner_radius / 2.0 + 0.1), 0.0);
	trans_bottom->RegisterYourself();

	TGeoRotation* rot_cvd_cut_top = new TGeoRotation("rot_cvd_cut_top", 0.0, 0.0,
	    180.0 / num_modules_per_half_plane);
	TGeoCombiTrans* trans_top = new TGeoCombiTrans("transrot_cvd_cut_top",
	    -std::sin(TMath::Pi() / num_modules_per_half_plane) * (alu_support_inner_radius / 2.0 + 0.1),
	    std::cos(TMath::Pi() / num_modules_per_half_plane) * (alu_support_inner_radius / 2.0 + 0.1), 0.0,
	    rot_cvd_cut_top);
	trans_top->RegisterYourself();

	TGeoCompositeShape* cvd_disc = new TGeoCompositeShape("cvd_disc",
	    "cvd_disc_tube-cvd_disc_cut:trans_cvd_cut_bottom-"
			    "cvd_disc_cut:transrot_cvd_cut_top");

	TGeoVolume* cvd_disc_volume = new TGeoVolume("lmd_vol_cvd_disc", cvd_disc,
	    gGeoMan->GetMedium("HYPdiamond"));
	cvd_disc_volume->SetLineColor(9);
	return cvd_disc_volume;
}

TGeoVolume* PndLmdGeometryFactory::generateSensor() const {
	TGeoVolumeAssembly* lmd_vol_sensor = new TGeoVolumeAssembly(navigation_paths[4].first.c_str());

	auto pt_sensors = geometry_property_tree.get_child("sensors");
	auto pt_active_part = pt_sensors.get_child("active_part");

	double sensor_dim_x(pt_sensors.get<double>("dimension_x"));
	double sensor_dim_y(pt_sensors.get<double>("dimension_x"));
	double thickness(pt_sensors.get<double>("thickness"));

	double active_part_dim_x(pt_active_part.get<double>("dimension_x"));
	double active_part_dim_y(pt_active_part.get<double>("dimension_y"));
	double active_part_offset_x(pt_active_part.get<double>("offset_x"));
	double active_part_offset_y(pt_active_part.get<double>("offset_y"));

	new TGeoBBox("sensor_full_centered", sensor_dim_x / 2.0, sensor_dim_y / 2.0, thickness / 2.0);

	TGeoBBox* sensor_active_centered = new TGeoBBox("sensor_active_centered", active_part_dim_x / 2.0,
	    active_part_dim_y / 2.0, thickness / 2.0);
	new TGeoBBox("sensor_active_centered_cutout", active_part_dim_x / 2.0, active_part_dim_y / 2.0,
	    thickness / 2.0 + 0.1);

	TGeoTranslation* trans_sensor_active = new TGeoTranslation("trans_sensor_active",
	    -sensor_dim_x / 2.0 + active_part_dim_x / 2.0 + active_part_offset_x,
	    -sensor_dim_y / 2.0 + active_part_dim_y / 2.0 + active_part_offset_y, 0.);
	trans_sensor_active->RegisterYourself();

	TGeoCompositeShape* sensor_passive_centered = new TGeoCompositeShape("sensor_passive_centered",
	    "(sensor_full_centered-sensor_active_centered_"
			    "cutout:trans_sensor_active)");

	TGeoVolume* passive_sensor_volume = new TGeoVolume("LumPassiveRect", sensor_passive_centered,
	    gGeoMan->GetMedium("silicon"));
	passive_sensor_volume->SetLineColor(kViolet);

	TGeoVolume* active_sensor_volume = new TGeoVolume(navigation_paths[5].first.c_str(),
	    sensor_active_centered, gGeoMan->GetMedium("silicon"));
	active_sensor_volume->SetLineColor(kYellow);

	// put cable on top of the sensor
	/*TGeoTubeSeg* shape_kapton_disc = new TGeoTubeSeg("shape_kapton_disc",
	 inner_rad,
	 lmd_cool_sup_inner_rad - gap_between_disc_and_support_structure,
	 kapton_disc_thick_half, -delta_phi / 2. / pi * 180.,
	 +delta_phi / 2. / pi * 180.);

	 TGeoRotation* kapton_rotation = new TGeoRotation("kapton_rotation", 0, 0,
	 0);
	 TGeoTranslation* kapton_translation = new TGeoTranslation(
	 "kapton_translation", -cvd_disc_dist, 0, 0);
	 TGeoCombiTrans* kapton_combtrans = new TGeoCombiTrans(*kapton_translation,
	 *kapton_rotation);
	 kapton_combtrans->SetName("kapton_combtrans");
	 kapton_combtrans->RegisterYourself();

	 //this next line is pretty stupid but it made the work for the better
	 geometry minimal
	 //otherwise I would have to do some deeper digging and reworking...
	 TGeoCompositeShape *shape_kapton_support =
	 new TGeoCompositeShape("shape_kapton_support",
	 "(shape_kapton_disc:kapton_combtrans+shape_kapton_disc:kapton_combtrans)");

	 TGeoVolume* lmd_vol_kapton_disc = new TGeoVolume("lmd_vol_kapton_disc",
	 shape_kapton_support, fgGeoMan->GetMedium("Aluminum"));	//kapton")); //
	 changed to equivalent for glue/flex cable etc.
	 lmd_vol_kapton_disc->SetLineColor(kRed);
	 //lmd_vol_kapton_disc->SetTransparency(50);
	 lmd_vol_kapton_disc->SetVisibility(false);*/

	lmd_vol_sensor->AddNode(passive_sensor_volume, 0);
	lmd_vol_sensor->AddNode(active_sensor_volume, 0, trans_sensor_active);
	return lmd_vol_sensor;
}

TGeoVolume* PndLmdGeometryFactory::generateBoxVacuum(const TGeoVolume* lmd_vol) const {
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

void PndLmdGeometryFactory::recursiveNodeSubtraction(std::stringstream& ss, TGeoNode* node) const {
	if (node->GetNdaughters() == 0) {
		ss << "-" << node->GetVolume()->GetName() << ":" << node->GetMatrix()->GetName();
	}
	else {
		for (int i = 0; i < node->GetNdaughters(); ++i) {
			recursiveNodeSubtraction(ss, node->GetDaughter(i));
		}
	}
}

void PndLmdGeometryFactory::makeNodesAlignable() const {
	TGeoNode* node = gGeoMan->GetTopNode();
	gGeoMan->CdTop();
	for (int i = 0; i < node->GetNdaughters(); ++i) {
		makeNodesAlignable(node->GetDaughter(i), 0);
	}
}

void PndLmdGeometryFactory::makeNodesAlignable(TGeoNode* node,
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
			std::runtime_error("PndLmdGeometryFactory::makeNodesAlignable(): Volume path structure "
					"is mismatching!");
		}
	}

	for (int i = 0; i < node->GetNdaughters(); ++i) {
		makeNodesAlignable(node->GetDaughter(i), current_navigation_path_index + 1);
	}
	gGeoMan->CdUp();
}
