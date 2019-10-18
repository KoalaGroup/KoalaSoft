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
//    * the reference dimension are for the vacuum space, the chamber dimension is then deduced based on the vacuum dimension and the wall thickness
//    * the final chamber shape is built by substracting the vacuum space from the bulk chamber, i.e. only the chamber wall left
// 4) build the sensor assembly
// 5) place the sensor assembly into the RecArm_Vacuum
// 6) add the RecArm_Vacuum [and the RecArm_Chamber] into the RecArm assembly
// 7) add the the RecArm assembly into the top volume
// 8) check overlap

// ** List of parameters that steers the whole alignment [cm] **
// - si1/si2/ge1/ge2_vertical_offset : the vertical alignment of each sensor
// - si1si2_overlap_offset : small offset added to the nominal value
// - si2ge1_overlap_offset : small offset added to the nominal value
// - ge1ge2_overlap_offset : small offset added to the nominal value
// - ip_offset : the offset of the sensor assembly to align to the interaction point
// - ip_distance : the distance of the sensor assembly to the interaction point
// - chamber_center_offset : the offset of the chamber center axis to the interaction point
void build_rec(TString FileName="rec.root", Bool_t WithChamber=true) {
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

  //// Step 2: the top volume //////
  // Cave is exactly the same as the KoaCave in KoalaSoft
  TGeoVolume* top = gGeoMan->MakeBox("cave", AirVolMed,cave_size[0], cave_size[1], cave_size[2]);
  gGeoMan->SetTopVolume(top);

  //// Step 3: the chamber & its associated vacuum volume ////
  // Chamber consists of two cylinder part: the adapter and the main recoil chamber.
  // The dimesions are:
  Double_t wall_thickness = 0.5; // thickness of the chamber wall [cm], it should be the same as the wall thickness in KoaPipe
  Double_t adapter_z = 25; // length of the adapter (vacuum space) [cm]
  Double_t adapter_r = 10; // radius of the adpater (vacuum space) [cm]
  Double_t recoil_chamber_z = 95; // length of the main recoil chamber (vacuum space) [cm]
  Double_t recoil_chamber_r = 45./2; // radius of the main recoil chamber (vacuum space) [cm]
  Double_t half_z = (adapter_z+recoil_chamber_z)/2; // half of total length of the chamber


  // build the Polycone (adapter + recoil_chamber can be represented in one polycone, thus build in one step)
  // The reference dimension defined above is used for the vacuum space
  // For the chamber volume, the dimensions are deduced from the reference dimensions plus the wall thickness
  // The origin is the center of the polycone, the axis of the ploycone is aligned with the z-axis
  // The adapter cylinder is the lower z-axis, and the recoil_chmaber cylinder is the higher z-axis

  // the chamber vaccum shape
  Int_t nSects = 4;
  Double_t r_vchamber[] = {adapter_r,adapter_r,recoil_chamber_r,recoil_chamber_r};    // in cm
  Double_t z_vchamber[] = {-half_z, -half_z+adapter_z, -half_z+adapter_z, -half_z+adapter_z+recoil_chamber_z};
  TGeoPcon* shape_vchamber = new TGeoPcon("shape_vchamber", 0., 360., nSects);
  for (Int_t iSect = 0; iSect < nSects; iSect++) {
    shape_vchamber->DefineSection(iSect, z_vchamber[iSect], 0, r_vchamber[iSect]);
  }
  // the bulk chamber shape
  Double_t z_chamber[] = {-half_z+wall_thickness, -half_z+adapter_z-wall_thickness, -half_z+adapter_z-wall_thickness, -half_z+adapter_z+recoil_chamber_z+wall_thickness};    // in cm
  TGeoPcon* shape_chamber = new TGeoPcon("shape_chamber", 0., 360., nSects);
  for (Int_t iSect = 0; iSect < nSects; iSect++) {
    shape_chamber->DefineSection(iSect, z_chamber[iSect], 0, r_vchamber[iSect]+wall_thickness);
  }
  // the final chamber shape
  // Substract the vacuum from the chamber inner space to get the final chamber shape
  TGeoCompositeShape* cs_chamber = new TGeoCompositeShape("cs_chamber","shape_chamber-shape_vchamber");
  // Build the RecArm_Vaccum and RecArm_Chamber volume
  TGeoVolume* ChamberVacuum = new TGeoVolume("RecArm_Vacuum", shape_vchamber, VacuumVolMed);
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

  // Placement of the sensors:
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

  TGeoVolumeAssembly* DetectorAssembly = new TGeoVolumeAssembly("RecArm_Detectors");
  DetectorAssembly->AddNode(Si1, 1, trans_si1);
  DetectorAssembly->AddNode(Si2, 1, trans_si2);
  DetectorAssembly->AddNode(Ge1, 1, trans_ge1);
  DetectorAssembly->AddNode(Ge2, 1, trans_ge2);

  /// Step 5:  place the sensor assembly into the chamber vacuum ///
  Double_t ip_offset=0.12*22;// the interaction point has 22 strips offset [cm]
  Double_t ip_distance=101.096; //  distance of the sensor place to the interaction point [cm]
  Double_t chamber_center_offset = 5.; // the axis of the recoil chamber is placed with 5 cm displacement towards the downstream of the beam line, so that the interaction point is aligned with this displaced center instead of the original axis. Thus, the sensor assembly should also be aligned to this displaced center, i.e. the interaction point.

  Double_t target_chamber_r = 30./2; // radius of the target chamber cylinder, used to place  [cm]
  Double_t chamber_offset_x = (adapter_z+recoil_chamber_z)/2 + target_chamber_r ;
  Double_t chamber_offset_z = chamber_center_offset;
  Double_t detector_offset_z = ip_distance - chamber_offset_x; // offset of sensor assembly along z-axis (-x in the final position) in the chamber vacuum
  Double_t detector_offset_x = chamber_offset_z + ip_offset; // offset of sensor assembly along x-axis (z in the final poistion) in the chamber vacuum
  
  // Roatate the sensor assembly against the Y-axis in 90 degree
  TGeoRotation *rot_detector=new TGeoRotation("rot_detector",0,90,90,90,90,180);
  TGeoCombiTrans* ct_detector=new TGeoCombiTrans("ct_detector", detector_offset_x,0,detector_offset_z,rot_detector);
  ct_detector->RegisterYourself();

  ChamberVacuum->AddNode(DetectorAssembly, 1, ct_detector);

  /// Step 6: add the RecArm_Vacuum and RecArm_Chamber into the RecArm assembly
  // the alignment here is already the final position in the setup of the cave
  // * Rotate against Y-axis in 90 degree first, so that the chamber is located in the -x direction
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
void build_fwd(TString FileName="fwd.root")//, Bool_t WithMonitor=false, Bool_t WithChamber=true, Bool_t WithExtra=false)
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

  // Fwd-vacuum: unit: cm
  Double_t vacuum_x, vacuum_y, vacuum_z;
  vacuum_x = 50./2; // to be defined
  vacuum_y = 40./2;// to be defined
  vacuum_z = 90./2; // to be defined 

  // Substracted shape: Cone + EndPipe
  // a bit longer than actual size
  // Int_t nSects = 4;
  // Double_t l_cone = 32; // in cm
  // Double_t cone_thickness = 0.003; // in cm, 30um
  // Double_t pipe_thickness = 0.5;
  // Double_t z_cone[] = {-chamber_z-l_cone, -chamber_z+l_cone, -chamber_z+l_cone, chamber_z+1};
  // Double_t r_cone[] = {10+cone_thickness+10-3, 3+cone_thickness, 3+pipe_thickness, 3+pipe_thickness};
  // TGeoPcon* shape_sub = new TGeoPcon("shape_sub", 0., 360., nSects);
  // for(Int_t iSect = 0; iSect < nSects; iSect++){
  //   shape_sub->DefineSection(iSect, z_cone[iSect], 0, r_cone[iSect]);
  // }

  // Chamber shape:
  // TGeoBBox* shape_chamber = new TGeoBBox("shape_chamber", chamber_x, chamber_y, chamber_z);
  TGeoBBox* shape_vacuum  = new TGeoBBox("shape_vacuum", vacuum_x, vacuum_y, vacuum_z);

  // TGeoCompositeShape* cs_chamber = new TGeoCompositeShape("cs_chamber", "shape_chamber-shape_sub-shape_vacuum");
  // TGeoCompositeShape* cs_vacuum = new TGeoCompositeShape("cs_vacuum", "shape_vacuum-shape_sub");

  // TGeoVolume* FwdChamber = new TGeoVolume("Fwd_Chamber", cs_chamber, ChamberVolMed);
  // FwdChamber->SetLineColor(16);
  // FwdChamber->SetTransparency(60);
  TGeoVolume* FwdVacuum  = new TGeoVolume("FwdArm_Vacuum", shape_vacuum, VacuumVolMed);
  // FwdVacuum->SetLineColor(kGreen);
  // FwdVacuum->SetVisibility(kFALSE);

  // Fwd dectectors: Dimensions of the detecors (x_low, x_high, ,y,z), unit: cm
  Double_t fwd_x_low,fwd_x_high, fwd_y,fwd_z;
  fwd_x_low = 1./2;//  width on the edge
  fwd_x_high = 2./2;// width on the light guide end
  fwd_y = 0.6/2; // thickness
  fwd_z = 9./2; // length
  TGeoVolume* SensorSc1 = gGeoMan->MakeTrd1("SensorSc1", ScintillatorVolMed, fwd_x_low, fwd_x_high, fwd_y, fwd_z);
  SensorSc1->SetLineColor(38);
  TGeoVolume* SensorSc2 = gGeoMan->MakeTrd1("SensorSc2", ScintillatorVolMed, fwd_x_low, fwd_x_high, fwd_y, fwd_z);
  SensorSc2->SetLineColor(38);

  // alight the surface of first scint to the center of vacuum box
  Double_t sc_gap  = 20; // gap between Sc1 and Sc2, unit: cm
  Double_t sc_align_z = fwd_y;
  Double_t sc_align_x = fwd_z + 2.8; // 2.8 is the distance to the beam center, unit: cm

  TGeoRotation *rot_sc = new TGeoRotation("rot_sc", 90, 90, 0, 0, 90, 0);
  TGeoCombiTrans *ct_sc1=new TGeoCombiTrans("ct_sc1",sc_align_x, 0, sc_align_z, rot_sc);
  TGeoCombiTrans *ct_sc2=new TGeoCombiTrans("ct_sc2",sc_align_x, 0, sc_align_z+sc_gap, rot_sc);

  TGeoVolumeAssembly *Fwd_Detectors = new TGeoVolumeAssembly("FwdArm_Detectors");
  Fwd_Detectors->AddNode(SensorSc1, 1, ct_sc1);
  Fwd_Detectors->AddNode(SensorSc2, 1, ct_sc2);
  FwdVacuum->AddNode(Fwd_Detectors, 1);

  // Add FwdVacuum to the top volume
  Double_t z_offset= 460; // distance of the surface of the first scint to IP
  TGeoTranslation *trans_zoffset=new TGeoTranslation(0., 0., z_offset);

  /* Beam Profile Monitor detector*/
  // if(WithMonitor){
  //   TGeoVolume* MonitorSc1 = gGeoMan->MakeBox("MonitorSc1", ScintillatorVolMed, fwd_x, fwd_y, fwd_z);
  //   MonitorSc1->SetLineColor(kRed);
  //   TGeoVolume* MonitorSc2 = gGeoMan->MakeBox("MonitorSc2", ScintillatorVolMed, fwd_x, fwd_y, fwd_z);
  //   MonitorSc2->SetLineColor(kRed);

  //   TGeoTranslation *trans_monitor_sc=new TGeoTranslation(-sc_align_x, 0, sc_align_z);

  //   TGeoVolumeAssembly *Fwd_Monitors = new TGeoVolumeAssembly("Fwd_Monitors");
  //   Fwd_Monitors->AddNode(MonitorSc1, 1);
  //   Fwd_Monitors->AddNode(MonitorSc2, 1, new TGeoTranslation(0,0,sc_gap));
  //   FwdVacuum->AddNode(Fwd_Monitors, 1, trans_monitor_sc);
  // }

  /* For explanation */
  // if(WithExtra){
  //   TGeoVolume* ExtraSc1 = gGeoMan->MakeBox("ExtraSc1", ScintillatorVolMed, fwd_y, fwd_x, fwd_z);
  //   ExtraSc1->SetLineColor(kRed);
  //   TGeoVolume* ExtraSc2 = gGeoMan->MakeBox("ExtraSc2", ScintillatorVolMed, fwd_y, fwd_x, fwd_z);
  //   ExtraSc2->SetLineColor(kRed);

  //   TGeoTranslation *trans_extra_sc1=new TGeoTranslation(0, -sc_align_x, sc_align_z);
  //   TGeoTranslation *trans_extra_sc2=new TGeoTranslation(0, sc_align_x, sc_align_z);

  //   TGeoVolumeAssembly *Fwd_Extras = new TGeoVolumeAssembly("Fwd_Extras");
  //   Fwd_Extras->AddNode(ExtraSc1, 1);
  //   Fwd_Extras->AddNode(ExtraSc2, 1, new TGeoTranslation(0,0,sc_gap));
  //   FwdVacuum->AddNode(Fwd_Extras, 1, trans_extra_sc1);
  //   FwdVacuum->AddNode(Fwd_Extras, 2, trans_extra_sc2);
  // }

  // alternative way: assemblyvolume
  TGeoVolumeAssembly* FwdArm = new TGeoVolumeAssembly("FwdArm");
  FwdArm->AddNode(FwdVacuum, 1, trans_zoffset);
  // if(WithChamber){
  //   FwdArm->AddNode(FwdChamber, 1);
  // }
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

