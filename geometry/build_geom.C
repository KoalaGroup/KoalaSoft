/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// in root all sizes are given in cm

/* ROOT script to build geometry ROOT file. Each module is contained in one ROOT file.
 * And, each ROOT file/module is built by invoking one build function a time.
 * NOTE: You cannot invoke two build functions continuously in the same ROOT session.
 *       Instead, you should quite the previous session and start a new session to invoke
 *       next build function.
 */

#include "TSystem.h"
#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TGeoMaterial.h"
#include "TGeoMedium.h"
#include "TGeoPgon.h"
#include "TGeoMatrix.h"
#include "TGeoCompositeShape.h"
#include "TFile.h"
#include "TString.h"
#include "TList.h"
#include "TROOT.h"
#include "FairSystemInfo.h"
#include "FairGeoLoader.h"
#include "FairGeoInterface.h"
#include "FairGeoBuilder.h"
#include "FairGeoMedium.h"
#include "FairGeoMedia.h"

#include <iostream>

// some global variables
TGeoManager* gGeoMan = NULL;  // Pointer to TGeoManager instance
Double_t cave_size[3]={20000,20000,20000};

// Forward declarations
void create_materials_from_media_file();

// build function for RecArm, default output file is rec.root
// ** List of Volumes **
// - Chamber ("RecArm_Chamber", polycone) : a CompositeShape, only with the recoil chmaber's wall
// - ChamberVacuum ("RecArm_Vacuum", ploycone) : the vacuum space inside the recoil chamber
// - Si1, Si2, Ge1, Ge2 ("Sensor_Si1", "Sensor_Si2", "Sensor_Ge1", "Sensor_Ge2", box) : the four recoil block sensors
// - DetectorAssembly ("RecArm_Detectors", assembly) : a collection of all 4 sensors
// - RecArm ("RecArm", assembly) : a collection of ChamberVaccum and Chamber (DetectorAssembly is put inside ChamberVacuum)
// - Top ("top", box) : the same dimension as the cave in KoalaSoft (RecArm is finally put in the Top volume lazily, i.e. no translation and rotation)
//
// ** The procedure of building RecArm **
// 1) read the KoalaSoft's standard media file, then build and get the TGeoMedium needed in recoil detector
// 2) build the top volume
// 3) build the RecArm_Chamber and RecArm_Vacuum volume
//    * consisting of the adapter and the main recoil_chamber
//    * adapter has an closed region to the target chamber, for alignment of the whole recoil geometry without overlap
//    * the reference dimension are for the vacuum space, the chamber dimension is then deduced based on the vacuum dimension and the wall thickness
//    * the final chamber shape is built by substracting the vacuum space from the bulk chamber, i.e. only the chamber wall left
// 4) build the sensor assembly, including the cold plate
// 5) place the sensor assembly into the RecArm_Vacuum
// 6) add the RecArm_Vacuum [and the RecArm_Chamber] into the RecArm assembly
// 7) add the the RecArm assembly into the top volume
// 8) check overlap

// ** List of parameters that steers the whole alignment [cm] **
// - wall_thickness: chamber thickness
// - si1/si2/ge1/ge2_vertical_offset : the vertical alignment of each sensor
// - si1si2_overlap_offset : small offset added to the nominal value
// - si2ge1_overlap_offset : small offset added to the nominal value
// - ge1ge2_overlap_offset : small offset added to the nominal value
// - ip_offset : the offset of the sensor assembly to align to the interaction point
// - ip_distance : the distance of the sensor assembly to the interaction point
// - sensor_distance: the distance between sensor surface and the inner chamber wall
// - chamber_center_offset : the offset of the chamber center axis to the interaction point
// - coldpalte_offset: the offset between the edges of si1 and coldplate
// - coldplate_gap :   the gap between coldplate surface and the sensors surface
void build_rec(TString FileName="rec.root", Bool_t WithChamber=true, Bool_t WithColdPlate=true) {
  TStopwatch timer;
  timer.Start();

  /////// Step 1: get all the medium material used in RecArm //////
  // Load needed material definition from media.geo file
  create_materials_from_media_file();

  // Get the GeoManager for later usage
  gGeoMan = (TGeoManager*) gROOT->FindObject("FAIRGeom");
  // gGeoMan->SetVisOption(0);
  gGeoMan->SetVisLevel(7);  
  
  // Medium
  TGeoMedium* AirVolMed   = gGeoMan->GetMedium("air");
  TGeoMedium* VacuumVolMed = gGeoMan->GetMedium("vacuum");
  TGeoMedium* SiVolMed   = gGeoMan->GetMedium("silicon");
  TGeoMedium* GeVolMed   = gGeoMan->GetMedium("germanium");
  TGeoMedium* ChamberVolMed = gGeoMan->GetMedium("Aluminum");
  TGeoMedium* CopperVolMed = gGeoMan->GetMedium("copper");

  //// Step 2: the top volume //////
  // Cave is exactly the same as the KoaCave in KoalaSoft
  TGeoVolume* top = gGeoMan->MakeBox("cave", AirVolMed,cave_size[0], cave_size[1], cave_size[2]);
  gGeoMan->SetTopVolume(top);

  //// Step 3: the chamber & its associated vacuum volume ////
  // Chamber consists of two cylinder part: the adapter and the main recoil chamber, and a unclosed gap is left bewtween the adapter and the target chamber for alignment convenience
  // The dimesions are:
  Double_t wall_thickness = 1; // thickness of the chamber wall [cm], it should be the same as the wall thickness in KoaPipe
  Double_t recoil_chamber_z = 95; // estimated length of the main recoil chamber (vacuum space) [cm]
  Double_t recoil_chamber_r = 40./2; // radius of the main recoil chamber (vacuum space) [cm]

  Double_t ip_distance=90.4; //  distance of the sensor place to the interaction point [cm]
  Double_t adapter_r = 10; // radius of the adpater (vacuum space) [cm]
  Double_t adapter_gap=10; // the gap of unclosed region between the adapter and the target chamber
  Double_t sensor_distance = 31.14; // distance between sensor surface to the inner chamber wall in length-direction [cm]
  Double_t target_chamber_r = 30./2; // radius of the target chamber cylinder, used to place  [cm]
  Double_t adapter_z = ip_distance - sensor_distance - target_chamber_r - adapter_gap; // length of the adapter (vacuum space) [cm]
  Double_t half_z = (adapter_z+recoil_chamber_z)/2; // half of total length of the chamber


  // build the Polycone (adapter + recoil_chamber can be represented in one polycone, thus build in one step)
  // The reference dimension defined above is used for the vacuum space
  // For the chamber volume, the dimensions are deduced from the reference dimensions plus the wall thickness
  // The origin is the center of the polycone, the axis of the ploycone is aligned with the z-axis
  // The adapter cylinder is the lower z-axis, and the recoil_chmaber cylinder is the higher z-axis
  Double_t center_distance = 5.49; // distance between the centers of recoil chamber and adapter
  TGeoTranslation* trans_adapter=new TGeoTranslation(center_distance,0,0);
  trans_adapter->SetName("trans_adapter");
  trans_adapter->RegisterYourself();

  // the chamber vaccum shape
  Double_t r_vchamber[] = {adapter_r,adapter_r,recoil_chamber_r,recoil_chamber_r};    // in cm
  Double_t z_vchamber[] = {-half_z, -half_z+adapter_z+0.1, -half_z+adapter_z, -half_z+adapter_z+recoil_chamber_z}; // 0.1 is added to make sure an overlap in union solid computation
  Int_t nSects = 2;
  TGeoPcon* shape_vchamber_adapter = new TGeoPcon("shape_vchamber_adapter", 0., 360., nSects);
  for (Int_t iSect = 0; iSect < nSects; iSect++) {
    shape_vchamber_adapter->DefineSection(iSect, z_vchamber[iSect], 0, r_vchamber[iSect]);
  }
  TGeoPcon* shape_vchamber_chamber = new TGeoPcon("shape_vchamber_chamber", 0., 360., nSects);
  for (Int_t iSect = 0; iSect < nSects; iSect++) {
    shape_vchamber_chamber->DefineSection(iSect, z_vchamber[iSect+2], 0, r_vchamber[iSect+2]);
  }
  TGeoCompositeShape* cs_vchamber = new TGeoCompositeShape("cs_vchamber","shape_vchamber_adapter:trans_adapter+shape_vchamber_chamber");

  // the bulk chamber shape
  Double_t z_chamber[] = {-half_z+wall_thickness, -half_z+adapter_z-wall_thickness+0.1, -half_z+adapter_z-wall_thickness, -half_z+adapter_z+recoil_chamber_z+wall_thickness};   // 0.1 is added to make sure an overlap in union solid computation [cm]
  TGeoPcon* shape_chamber_adapter = new TGeoPcon("shape_chamber_adapter", 0., 360., nSects);
  for (Int_t iSect = 0; iSect < nSects; iSect++) {
    shape_chamber_adapter->DefineSection(iSect, z_chamber[iSect], 0, r_vchamber[iSect]+wall_thickness);
  }
  TGeoPcon* shape_chamber_chamber = new TGeoPcon("shape_chamber_chamber", 0., 360., nSects);
  for (Int_t iSect = 0; iSect < nSects; iSect++) {
    shape_chamber_chamber->DefineSection(iSect, z_chamber[iSect+2], 0, r_vchamber[iSect+2]+wall_thickness);
  }
  TGeoCompositeShape* cs_bulkchamber = new TGeoCompositeShape("cs_bulkchamber","shape_chamber_adapter:trans_adapter+shape_chamber_chamber");

  // the final chamber shape
  // Substract the vacuum from the chamber inner space to get the final chamber shape
  TGeoCompositeShape* cs_chamber = new TGeoCompositeShape("cs_chamber","cs_bulkchamber-cs_vchamber");
  // Build the RecArm_Vaccum and RecArm_Chamber volume
  TGeoVolume* ChamberVacuum = new TGeoVolume("RecArm_Vacuum", cs_vchamber, VacuumVolMed);
  TGeoVolume* Chamber = new TGeoVolume("RecArm_Chamber", cs_chamber, ChamberVolMed);
  Chamber->SetLineColor(16);
  Chamber->SetTransparency(60);

  //// Step 4: build the sensor assembly ////
  // Sensor dimensions [x,y,z]=[thickness,width,lenth] unit: cm
  Double_t si_size[3]={0.1/2,5./2,7.68/2};//  76.8mm x 50mm x 1mm
  Double_t ge1_size[3]={0.5/2,5.0/2,8.04/2};//  80.4mm x 50mm x 5mm
  Double_t ge2_size[3]={1.1/2,5.0/2,8.04/2};//  80.4mm x 50mm x 11mm
  TGeoVolume* Si1 = gGeoMan->MakeBox("SensorSi1", SiVolMed, si_size[0],si_size[1],si_size[2]);
  Si1->SetLineColor(38); // set line color 
  // Si1->SetTransparency(70); // set transparency 
  TGeoVolume* Si2 = gGeoMan->MakeBox("SensorSi2", SiVolMed, si_size[0],si_size[1],si_size[2]);
  Si2->SetLineColor(38); // set line color 
  // Si2->SetTransparency(70); // set transparency 
  TGeoVolume* Ge1 = gGeoMan->MakeBox("SensorGe1", GeVolMed, ge1_size[0],ge1_size[1],ge1_size[2]);
  Ge1->SetLineColor(34); // set line color 
  // Ge1->SetTransparency(70); // set transparency 
  TGeoVolume* Ge2 = gGeoMan->MakeBox("SensorGe2", GeVolMed, ge2_size[0],ge2_size[1],ge2_size[2]);
  Ge2->SetLineColor(34); // set line color 
  // Ge2->SetTransparency(70); // set transparency 

  // Placement of the sensors in to an DetectorAssembly:
  // * Alignment along the z-axis, from -z->z: Si1(+y), Si2(-y), Ge1(+y), Ge2(-y)
  // * The edge of Si1 in coincidence with y axis
  // * The flat plane of the sensor assembly (the side which will face the interaction point) face towards -x
  Double_t si1_vertical_offset = 1.35/2; // distance between each sensor's edge to the middle line [cm]
  Double_t si2_vertical_offset = 1.35/2;
  Double_t ge1_vertical_offset = 1.35/2;
  Double_t ge2_vertical_offset = 1.35/2;
  Double_t si1si2_overlap_offset = -0.03; // [cm]
  Double_t si2ge1_overlap_offset = -0.035; // [cm]
  Double_t ge1ge2_overlap_offset = 0.02; // [cm]
  Double_t si1si2_overlap = 2.4 + si1si2_overlap_offset; // overlap between Si1 & Si2, 2.4 is the nominal value [cm]
  Double_t si2ge1_overlap = 1.08 + si2ge1_overlap_offset; // overlap between Si2 & Ge1, 1.08 is the nominal value [cm]
  Double_t ge1ge2_overlap = 1.2 + ge1ge2_overlap_offset; // overlap between Ge1 & Ge2, 1.2 is the nominal value [cm]

  Double_t si1_align[3]={si_size[0],si1_vertical_offset+si_size[1], si_size[2]};
  Double_t si2_align[3]={si_size[0], -si2_vertical_offset-si_size[1], si_size[2]*3-si1si2_overlap};
  Double_t ge1_align[3]={ge1_size[0], ge1_vertical_offset+ge1_size[1], si_size[2]*4+ge1_size[2]-si1si2_overlap-si2ge1_overlap};
  Double_t ge2_align[3]={ge2_size[0], -ge2_vertical_offset-ge2_size[1], si_size[2]*4+ge1_size[2]*2+ge2_size[2]-si1si2_overlap-si2ge1_overlap-ge1ge2_overlap};
  TGeoTranslation *trans_si1=new TGeoTranslation(si1_align[0],si1_align[1],si1_align[2]);
  TGeoTranslation *trans_si2=new TGeoTranslation(si2_align[0],si2_align[1],si2_align[2]);
  TGeoTranslation *trans_ge1=new TGeoTranslation(ge1_align[0],ge1_align[1],ge1_align[2]);
  TGeoTranslation *trans_ge2=new TGeoTranslation(ge2_align[0],ge2_align[1],ge2_align[2]);

  // Cold plate //
  Double_t coldplate_size[3]={1./2, 14.65/2, 29.9/2}; // 299mm x 146.5mm x 10mm
  TGeoVolume* ColdPlate = gGeoMan->MakeBox("ColdPlate", CopperVolMed, coldplate_size[0], coldplate_size[1], coldplate_size[2]);
  ColdPlate->SetLineColor(2);
  
  Double_t coldplate_offset = 1.66; // estimated gap bewtween coldplate edge and si1 edge, [cm]
  Double_t coldplate_gap    = 1.5; // estimated gap between the surface of the coldplate and sensors, [cm]
  TGeoTranslation *trans_coldpalte = new TGeoTranslation(coldplate_size[0]+coldplate_gap, 0, coldplate_size[2]-coldplate_offset);
  
  TGeoVolumeAssembly* DetectorAssembly = new TGeoVolumeAssembly("RecArm_Detectors");
  DetectorAssembly->AddNode(Si1, 1, trans_si1);
  DetectorAssembly->AddNode(Si2, 1, trans_si2);
  DetectorAssembly->AddNode(Ge1, 1, trans_ge1);
  DetectorAssembly->AddNode(Ge2, 1, trans_ge2);
  if(WithColdPlate){
    DetectorAssembly->AddNode(ColdPlate, 1, trans_coldpalte);
  }

  /// Step 5:  place the sensor assembly into the chamber vacuum ///
  Double_t ip_offset=2.85;// the interaction point offset with respect to the edge of sensor assembly [cm]
  Double_t chamber_center_offset = 10.49; // the center of the recoil chamber is placed with 10.49 cm displacement towards the downstream of the beam line, so that the interaction point is aligned with this displaced center instead of the original axis. Thus, the sensor assembly should also be aligned to this displaced center first, i.e. the interaction point.
  Double_t chamber_offset_x = (adapter_z+recoil_chamber_z)/2 + target_chamber_r + adapter_gap;
  Double_t chamber_offset_z = chamber_center_offset;
  Double_t detector_offset_z = ip_distance - chamber_offset_x; // offset of sensor assembly along z-axis (-x in the final position) in the chamber vacuum
  Double_t detector_offset_x = chamber_offset_z + ip_offset; // offset of sensor assembly along x-axis (z in the final poistion) in the chamber vacuum
  
  // Roatate the sensor assembly against the Y-axis in -90 degree
  TGeoRotation *rot_detector=new TGeoRotation("rot_detector",0,90,90,90,90,180);
  TGeoCombiTrans* ct_detector=new TGeoCombiTrans("ct_detector", detector_offset_x,0,detector_offset_z,rot_detector);
  ct_detector->RegisterYourself();

  ChamberVacuum->AddNode(DetectorAssembly, 1, ct_detector);

  /// Step 6: add the RecArm_Vacuum and RecArm_Chamber into the RecArm assembly
  // the alignment here is already the final position in the setup of the cave
  // * Rotate against Y-axis in -90 degree first, so that the chamber is located in the -x direction
  // * Then rotate against the X-axis in 180 degree to turn the sensors up side down
  TGeoRotation *rot_chamber=new TGeoRotation("rot_chamber",180,90,90,270,90,180);
  TGeoCombiTrans* ct_chamber=new TGeoCombiTrans("ct_chamber", -chamber_offset_x,0,chamber_offset_z,rot_chamber);
  ct_chamber->RegisterYourself();

  TGeoVolumeAssembly* RecArm = new TGeoVolumeAssembly("RecArm");
  RecArm->AddNode(ChamberVacuum, 1, ct_chamber);
  if(WithChamber){
    RecArm->AddNode(Chamber, 1, ct_chamber);
  }

  /// Step 7: add the RecArm in the top volume
  top->AddNode(RecArm, 1);

  cout<<"Voxelizing."<<endl;
  top->Voxelize("");
  gGeoMan->CloseGeometry();

  /// Step 8: check overlap ///
  gGeoMan->CheckOverlaps(0.001);
  gGeoMan->PrintOverlaps();
  gGeoMan->Test();

  /// write to the output file ///
  TFile* outfile = TFile::Open(FileName,"RECREATE");
  top->Write();
  outfile->Close();

   top->Draw("ogl");
  top->Raytrace();

  // -----   Finish   -------------------------------------------------------

  cout << endl << endl;

  // Extract the maximal used memory an add is as Dart measurement
  // This line is filtered by CTest and the value send to CDash
  FairSystemInfo sysInfo;
  Double_t maxMemory=sysInfo.GetMaxMemory();
  cout << "<DartMeasurement name=\"MaxMemory\" type=\"numeric/double\">";
  cout << maxMemory;
  cout << "</DartMeasurement>" << endl;

  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();

  Double_t cpuUsage=ctime/rtime;
  cout << "<DartMeasurement name=\"CpuLoad\" type=\"numeric/double\">";
  cout << cpuUsage;
  cout << "</DartMeasurement>" << endl;

  cout << endl << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime
       << "s" << endl << endl;
  cout << "Macro finished successfully." << endl;

  // ------------------------------------------------------------------------
}

// build function for Fwd detecor, default output file is fwd.root
void build_fwd(TString FileName="fwd.root", Bool_t WithChamber=true, Bool_t WithExtra=true)
{
  TStopwatch timer;
  timer.Start();

  /////// Step 1: get all the medium material used in RecArm //////
  // Load needed material definition from media.geo file
  create_materials_from_media_file();

  // Get the GeoManager for later usage
  gGeoMan = (TGeoManager*) gROOT->FindObject("FAIRGeom");
  gGeoMan->SetVisLevel(7);  
  // gGeoMan->SetVisOption(0);
  
  // Medium
  TGeoMedium* AirVolMed   = gGeoMan->GetMedium("air");
  TGeoMedium* ScintillatorVolMed   = gGeoMan->GetMedium("polyvinyltoluene");
  TGeoMedium* VacuumVolMed = gGeoMan->GetMedium("vacuum");
  TGeoMedium* ChamberVolMed = gGeoMan->GetMedium("Aluminum");

  //// Step 2: the top volume //////
  // Cave is exactly the same as the KoaCave
  TGeoVolume* top = gGeoMan->MakeBox("cave", AirVolMed, cave_size[0], cave_size[1], cave_size[2]);
  gGeoMan->SetTopVolume(top);

  //// Step 3: the chamber volume //////
  // Fwd-vacuum: unit: cm
  Double_t chamber_r = 10; // radious of fwd chamber vacuum [cm]
  Double_t chamber_z = 40./2; // length of fwd chamber [cm]
  Double_t branch_r = 2; // [TODO] radius of the flange holding scintillator [cm]
  Double_t branch_z = 3./2; // [TODO] length of flange holding scintillator [cm]
  Double_t pipe_thickness = 0.5; // thickness of chamber wall

  // scintillator dimension
  Double_t fwd_x_low,fwd_x_high, fwd_y,fwd_z;
  fwd_x_low = 1./2;//  width on the edge
  fwd_x_high = 2./2;// width on the light guide end
  fwd_y = 0.6/2; // thickness
  fwd_z = 9./2; // length

  // alight the surface of first scint to the center of vacuum box
  Double_t sc_gap  = 20; // gap between Sc1 and Sc2, unit: cm
  Double_t sc_align_z = fwd_y;
  Double_t sc_align_x = fwd_z + 2.8; // 2.8 is the distance to the beam center, unit: cm

  TGeoRotation *rot_branch_plus_x = new TGeoRotation("rot_branch_plus_x",90, 90, 0, 0, 90, 0);
  rot_branch_plus_x->RegisterYourself();
  TGeoRotation *rot_branch_minus_x = new TGeoRotation("rot_branch_minus_x",90, 270, 0, 0, 90, 180);
  rot_branch_minus_x->RegisterYourself();
  TGeoRotation *rot_branch_plus_y = new TGeoRotation("rot_branch_plus_y",90, 0, 180, 0, 90, 90);
  rot_branch_plus_y->RegisterYourself();
  TGeoRotation *rot_branch_minus_y = new TGeoRotation("rot_branch_minus_y",90, 0, 0, 0, 90, 270);
  rot_branch_minus_y->RegisterYourself();

  TGeoCombiTrans *ct_branch_x1= new TGeoCombiTrans("ct_branch_x1", 0, 0, -sc_gap/2, rot_branch_plus_x);
  ct_branch_x1->RegisterYourself();
  TGeoCombiTrans *ct_branch_x2= new TGeoCombiTrans("ct_branch_x2", 0, 0, sc_gap/2, rot_branch_plus_x);
  ct_branch_x2->RegisterYourself();
  TGeoCombiTrans *ct_branch_y1= new TGeoCombiTrans("ct_branch_y1", 0, 0, -sc_gap/2, rot_branch_plus_y);
  ct_branch_y1->RegisterYourself();
  TGeoCombiTrans *ct_branch_y2= new TGeoCombiTrans("ct_branch_y2", 0, 0, sc_gap/2, rot_branch_plus_y);
  ct_branch_y2->RegisterYourself();

  // +x direction
  TGeoCombiTrans *ct_sc1=new TGeoCombiTrans("ct_sc1",sc_align_x, 0, sc_align_z, rot_branch_plus_x);
  TGeoCombiTrans *ct_sc2=new TGeoCombiTrans("ct_sc2",sc_align_x, 0, sc_align_z+sc_gap, rot_branch_plus_x);
  ct_sc1->RegisterYourself();
  ct_sc2->RegisterYourself();

  // -x direction
  TGeoCombiTrans *ct_sc3=new TGeoCombiTrans("ct_sc3",-sc_align_x, 0, sc_align_z, rot_branch_minus_x);
  TGeoCombiTrans *ct_sc4=new TGeoCombiTrans("ct_sc4",-sc_align_x, 0, sc_align_z+sc_gap, rot_branch_minus_x);
  ct_sc3->RegisterYourself();
  ct_sc4->RegisterYourself();

  // +y direction
  TGeoCombiTrans *ct_sc5=new TGeoCombiTrans("ct_sc5",0 , sc_align_x, sc_align_z, rot_branch_plus_y);
  TGeoCombiTrans *ct_sc6=new TGeoCombiTrans("ct_sc6",0 , sc_align_x, sc_align_z+sc_gap, rot_branch_plus_y);
  ct_sc5->RegisterYourself();
  ct_sc6->RegisterYourself();

  // -y direction
  TGeoCombiTrans *ct_sc7=new TGeoCombiTrans("ct_sc7",0 , -sc_align_x, sc_align_z, rot_branch_minus_y);
  TGeoCombiTrans *ct_sc8=new TGeoCombiTrans("ct_sc8",0 , -sc_align_x, sc_align_z+sc_gap, rot_branch_minus_y);
  ct_sc7->RegisterYourself();
  ct_sc8->RegisterYourself();

  //
  TGeoTube* shape_vchamber_body = new TGeoTube("shape_vchamber_body", 0, chamber_r, chamber_z);
  TGeoTube* shape_vchamber_branch = new TGeoTube("shape_vchamber_branch", 0, branch_r, 2*branch_z+2*chamber_r);
  TGeoCompositeShape* cs_vchamber = new TGeoCompositeShape("cs_vchamber","shape_vchamber_body+shape_vchamber_branch:ct_branch_x1+shape_vchamber_branch:ct_branch_x2+shape_vchamber_branch:ct_branch_y1+shape_vchamber_branch:ct_branch_y2");

  TGeoTube* shape_chamber_body = new TGeoTube("shape_chamber_body", 0, chamber_r+pipe_thickness, chamber_z);
  TGeoTube* shape_chamber_branch = new TGeoTube("shape_chamber_branch", 0, branch_r+pipe_thickness, 2*branch_z+2*chamber_r);
  TGeoCompositeShape* cs_bulkchamber = new TGeoCompositeShape("cs_bulkchamber","shape_chamber_body+shape_chamber_branch:ct_branch_x1+shape_chamber_branch:ct_branch_x2+shape_chamber_branch:ct_branch_y1+shape_chamber_branch:ct_branch_y2");

  TGeoCompositeShape* cs_chamber = new TGeoCompositeShape("cs_chamber","cs_bulkchamber-cs_vchamber");
  TGeoVolume* FwdVacuum  = new TGeoVolume("FwdArm_Vacuum", cs_vchamber, VacuumVolMed);
  TGeoVolume* FwdChamber = new TGeoVolume("FwdArm_Chamber", cs_chamber, ChamberVolMed);
  FwdChamber->SetLineColor(16);
  FwdChamber->SetTransparency(60);

  //// Step 4: the sensor volume assembly //////
  // Fwd dectectors: Dimensions of the detecors (x_low, x_high, ,y,z), unit: cm
  TGeoVolume* SensorSc1 = gGeoMan->MakeTrd1("SensorSc1", ScintillatorVolMed, fwd_x_low, fwd_x_high, fwd_y, fwd_z);
  SensorSc1->SetLineColor(38);
  TGeoVolume* SensorSc2 = gGeoMan->MakeTrd1("SensorSc2", ScintillatorVolMed, fwd_x_low, fwd_x_high, fwd_y, fwd_z);
  SensorSc2->SetLineColor(38);

  TGeoVolume* SensorSc3 = gGeoMan->MakeTrd1("SensorSc3", ScintillatorVolMed, fwd_x_low, fwd_x_high, fwd_y, fwd_z);
  SensorSc3->SetLineColor(38);
  TGeoVolume* SensorSc4 = gGeoMan->MakeTrd1("SensorSc4", ScintillatorVolMed, fwd_x_low, fwd_x_high, fwd_y, fwd_z);
  SensorSc4->SetLineColor(38);
  TGeoVolume* SensorSc5 = gGeoMan->MakeTrd1("SensorSc5", ScintillatorVolMed, fwd_x_low, fwd_x_high, fwd_y, fwd_z);
  SensorSc5->SetLineColor(38);
  TGeoVolume* SensorSc6 = gGeoMan->MakeTrd1("SensorSc6", ScintillatorVolMed, fwd_x_low, fwd_x_high, fwd_y, fwd_z);
  SensorSc6->SetLineColor(38);
  TGeoVolume* SensorSc7 = gGeoMan->MakeTrd1("SensorSc7", ScintillatorVolMed, fwd_x_low, fwd_x_high, fwd_y, fwd_z);
  SensorSc7->SetLineColor(38);
  TGeoVolume* SensorSc8 = gGeoMan->MakeTrd1("SensorSc8", ScintillatorVolMed, fwd_x_low, fwd_x_high, fwd_y, fwd_z);
  SensorSc8->SetLineColor(38);

  TGeoVolumeAssembly *Fwd_Detectors = new TGeoVolumeAssembly("FwdArm_Detectors");
  Fwd_Detectors->AddNode(SensorSc1, 1, ct_sc1);
  Fwd_Detectors->AddNode(SensorSc2, 1, ct_sc2);
  if(WithExtra){
    Fwd_Detectors->AddNode(SensorSc3, 1, ct_sc3);
    Fwd_Detectors->AddNode(SensorSc4, 1, ct_sc4);
    Fwd_Detectors->AddNode(SensorSc5, 1, ct_sc5);
    Fwd_Detectors->AddNode(SensorSc6, 1, ct_sc6);
    Fwd_Detectors->AddNode(SensorSc7, 1, ct_sc7);
    Fwd_Detectors->AddNode(SensorSc8, 1, ct_sc8);
  }
  TGeoTranslation* trans_detector_assembly = new TGeoTranslation(0, 0, -fwd_y-sc_gap/2);
  FwdVacuum->AddNode(Fwd_Detectors, 1, trans_detector_assembly);

  // Step 5: Add FwdVacuum to the top volume
  Double_t z_offset= 460; // distance of the surface of the first scint to IP
  TGeoTranslation *trans_zoffset=new TGeoTranslation(0., 0., sc_gap/2+fwd_y+z_offset);
  TGeoVolumeAssembly* FwdArm = new TGeoVolumeAssembly("FwdArm");
  FwdArm->AddNode(FwdVacuum, 1, trans_zoffset);
  if(WithChamber){
    FwdArm->AddNode(FwdChamber, 1, trans_zoffset);
  }

  // Step 6: add FwdArm to the top volume
  top->AddNode(FwdArm, 1);

  cout<<"Voxelizing."<<endl;
  top->Voxelize("");
  gGeoMan->CloseGeometry();

  gGeoMan->CheckOverlaps(0.001);
  gGeoMan->PrintOverlaps();
  gGeoMan->Test();

  // Write into file
  TFile* outfile = TFile::Open(FileName,"RECREATE");
  top->Write();
  outfile->Close();

   top->Draw("ogl");
  top->Raytrace();

  TFile* outfile2=new TFile("fwd_manager.root","recreate");
  gGeoMan->Write();
  delete outfile2;

  // -----   Finish   -------------------------------------------------------

  cout << endl << endl;

  // Extract the maximal used memory an add is as Dart measurement
  // This line is filtered by CTest and the value send to CDash
  FairSystemInfo sysInfo;
  Float_t maxMemory=sysInfo.GetMaxMemory();
  cout << "<DartMeasurement name=\"MaxMemory\" type=\"numeric/double\">";
  cout << maxMemory;
  cout << "</DartMeasurement>" << endl;

  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();

  Float_t cpuUsage=ctime/rtime;
  cout << "<DartMeasurement name=\"CpuLoad\" type=\"numeric/double\">";
  cout << cpuUsage;
  cout << "</DartMeasurement>" << endl;

  cout << endl << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime
       << "s" << endl << endl;
  cout << "Macro finished successfully." << endl;

  // ------------------------------------------------------------------------
}
void create_materials_from_media_file()
{
  // Use the FairRoot geometry interface to load the media which are already defined
  FairGeoLoader* geoLoad = new FairGeoLoader("TGeo", "FairGeoLoader");
  FairGeoInterface* geoFace = geoLoad->getGeoInterface();
  TString geoPath = gSystem->Getenv("VMCWORKDIR");
  TString geoFile = geoPath + "/geometry/media.geo";
  geoFace->setMediaFile(geoFile);
  geoFace->readMedia();

  // Read the required media and create them in the GeoManager
  FairGeoMedia* geoMedia = geoFace->getMedia();
  FairGeoBuilder* geoBuild = geoLoad->getGeoBuilder();

  FairGeoMedium* air              = geoMedia->getMedium("air");
  FairGeoMedium* silicon          = geoMedia->getMedium("silicon");
  FairGeoMedium* germanium        = geoMedia->getMedium("germanium");
  FairGeoMedium* mylar            = geoMedia->getMedium("mylar");
  FairGeoMedium* vacuum           = geoMedia->getMedium("vacuum");
  FairGeoMedium* polyvinyltoluene = geoMedia->getMedium("polyvinyltoluene");
  FairGeoMedium* aluminum         = geoMedia->getMedium("Aluminum");

  // include check if all media are found

  geoBuild->createMedium(air);
  geoBuild->createMedium(silicon);
  geoBuild->createMedium(germanium);
  geoBuild->createMedium(mylar);
  geoBuild->createMedium(vacuum);
  geoBuild->createMedium(polyvinyltoluene);
  geoBuild->createMedium(aluminum);
}

