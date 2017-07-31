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

#include <iostream>

// some global variables
TGeoManager* gGeoMan = NULL;  // Pointer to TGeoManager instance

// Forward declarations
void create_materials_from_media_file();

// build function for RecArm, default output file is rec.root
void build_rec(TString FileName="rec.root", Bool_t WithChamber=true) {
  TStopwatch timer;
  timer.Start();
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

  // Create the top volume
  // Cave is exactly the same as the KoaCave
  TGeoVolume* top = gGeoMan->MakeBox("cave", AirVolMed,20000., 20000.,20000.);
  gGeoMan->SetTopVolume(top);

  // Chamber:
  Double_t target_chamber_x = 30./2;
  Double_t chamber_thickness = 0.5;
  Double_t adapter_z = 40. - target_chamber_x;
  Double_t adapter_r = 20./2;
  Double_t chamber_z = 95.;
  Double_t chamber_r = 45./2;
  Double_t rec_center_offset = 5.;

  Int_t nSects = 4;
  Double_t half_z = (135-target_chamber_x)/2;
  Double_t z_chamber[] = {-half_z+chamber_thickness, -half_z+adapter_z-chamber_thickness, -half_z+adapter_z-chamber_thickness, -half_z+adapter_z+chamber_z+chamber_thickness};    // in cm
  Double_t r_chamber[] = {adapter_r,adapter_r,chamber_r,chamber_r};    // in cm
  TGeoPcon* shape_chamber = new TGeoPcon("shape_chamber", 0., 360., nSects);
  for (Int_t iSect = 0; iSect < nSects; iSect++) {
    shape_chamber->DefineSection(iSect, z_chamber[iSect], 0, r_chamber[iSect]+chamber_thickness);
  }

  Double_t z_vchamber[] = {-half_z, -half_z+adapter_z, -half_z+adapter_z, -half_z+adapter_z+chamber_z};    // in cm
  TGeoPcon* shape_vchamber = new TGeoPcon("shape_vchamber", 0., 360., nSects);
  for (Int_t iSect = 0; iSect < nSects; iSect++) {
    shape_vchamber->DefineSection(iSect, z_vchamber[iSect], 0, r_chamber[iSect]);
  }

  TGeoCompositeShape* cs_chamber = new TGeoCompositeShape("cs_chamber","shape_chamber-shape_vchamber");
  TGeoVolume* ChamberVacuum = new TGeoVolume("RecArm_Vacuum", shape_vchamber, VacuumVolMed);
  TGeoVolume* Chamber = new TGeoVolume("RecArm_Chamber", cs_chamber, ChamberVolMed);
  Chamber->SetLineColor(16);
  Chamber->SetTransparency(60);

  // Detectors: Dimensions of the detecors (x,y,z), unit: cm
  Double_t si_size[3]={0.1/2,5./2,7.68/2};// 64ch, 76.8mm x 50mm x 1mm
  Double_t ge1_size[3]={0.5/2,5.0/2,8.04/2};// 67ch, 80.4mm x 50mm x 5mm
  Double_t ge2_size[3]={1.1/2,5.0/2,8.04/2};// 67ch, 80.4mm x 50mm x 11mm
  Double_t envelop[3]={2.5/2,14.65/2,29.9/2};// envelop based on technical drawing
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

  // Placement
  Double_t si1_align[3]={0.1/2,0.575+0.1+5./2,-29.9/2+1.66+7.68/2};
  Double_t si2_align[3]={0.1/2,-0.575-0.1-5./2,-29.9/2+1.66+7.68/2+5.28};
  Double_t ge1_align[3]={0.5/2,0.575+0.1+5./2,-29.9/2+1.66+8.04/2+5.28+7.68-1.08};
  Double_t ge2_align[3]={1.1/2,-0.575-0.1-5./2,-29.9/2+1.66+8.04/2+5.28+7.68-1.08-1.2+8.04};

  TGeoTranslation *trans_si1=new TGeoTranslation(si1_align[0],si1_align[1],si1_align[2]);
  TGeoTranslation *trans_si2=new TGeoTranslation(si2_align[0],si2_align[1],si2_align[2]);
  TGeoTranslation *trans_ge1=new TGeoTranslation(ge1_align[0],ge1_align[1],ge1_align[2]);
  TGeoTranslation *trans_ge2=new TGeoTranslation(ge2_align[0],ge2_align[1],ge2_align[2]);

  // alternative way: assemblyvolume
  TGeoVolumeAssembly* DetectorAssembly = new TGeoVolumeAssembly("RecArm_Detectors");
  DetectorAssembly->AddNode(Si1, 1, trans_si1);
  DetectorAssembly->AddNode(Si2, 1, trans_si2);
  DetectorAssembly->AddNode(Ge1, 1, trans_ge1);
  DetectorAssembly->AddNode(Ge2, 1, trans_ge2);

  // Align
  // RecArm in +x direction
  Double_t z_offset=29.9/2-1.66-0.12*22;//22 strips offset
  Double_t x_offset=100.;

  Double_t chamber_offset_x = (adapter_z+chamber_z)/2 + target_chamber_x ;
  Double_t chamber_offset_z = rec_center_offset;
  Double_t detector_offset_z = x_offset - chamber_offset_x;
  Double_t detector_offset_x = chamber_offset_z - z_offset;
  TGeoRotation *rot_chamber=new TGeoRotation("rot_chamber",180,90,90,90,90,0);
  TGeoRotation *rot_detector=new TGeoRotation("rot_detector",0,90,90,90,90,180);
  TGeoCombiTrans* ct_chamber=new TGeoCombiTrans("ct_chamber", chamber_offset_x,0,chamber_offset_z,rot_chamber);
  TGeoCombiTrans* ct_detector=new TGeoCombiTrans("ct_detector", detector_offset_x,0,detector_offset_z,rot_detector);
  ct_chamber->RegisterYourself();
  ct_detector->RegisterYourself();

  // add to world
  ChamberVacuum->AddNode(DetectorAssembly, 1, ct_detector);

  TGeoVolumeAssembly* RecArm = new TGeoVolumeAssembly("RecArm");
  RecArm->AddNode(ChamberVacuum, 1, ct_chamber);
  if(WithChamber){
    RecArm->AddNode(Chamber, 1, ct_chamber);
  }
  top->AddNode(RecArm, 1);
  //

  cout<<"Voxelizing."<<endl;
  top->Voxelize("");
  gGeoMan->CloseGeometry();

  gGeoMan->CheckOverlaps(0.001);
  gGeoMan->PrintOverlaps();
  gGeoMan->Test();

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
void build_fwd(TString FileName="fwd.root", Bool_t WithMonitor=false, Bool_t WithChamber=true) {
  TStopwatch timer;
  timer.Start();
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

  // Create the top volume
  // Cave is exactly the same as the KoaCave
  TGeoVolume* top = gGeoMan->MakeBox("cave", AirVolMed,20000., 20000.,20000.);
  gGeoMan->SetTopVolume(top);

  // Fwd-chamber: unit: cm
  Double_t chamber_x, chamber_y, chamber_z, chamber_thickness;
  chamber_x = 50./2; // to be defined
  chamber_y = 40./2;// to be defined
  chamber_z = 90./2; // to be defined 
  chamber_thickness = 0.5; // to be defined 

  // Substracted shape: Cone + EndPipe
  Int_t nSects = 4;
  Double_t l_cone = 32; // in cm
  Double_t cone_thickness = 0.003; // in cm, 30um
  Double_t pipe_thickness = 0.5;
  Double_t z_cone[] = {-chamber_z-l_cone, -chamber_z+l_cone, -chamber_z+l_cone, chamber_z+1};
  Double_t r_cone[] = {10+cone_thickness+10-3, 3+cone_thickness, 3+pipe_thickness, 3+pipe_thickness};
  TGeoPcon* shape_sub = new TGeoPcon("shape_sub", 0., 360., nSects);
  for(Int_t iSect = 0; iSect < nSects; iSect++){
    shape_sub->DefineSection(iSect, z_cone[iSect], 0, r_cone[iSect]);
  }

  // Chamber shape:
  TGeoBBox* shape_chamber = new TGeoBBox("shape_chamber", chamber_x, chamber_y, chamber_z);
  TGeoBBox* shape_vacuum  = new TGeoBBox("shape_vacuum", chamber_x-chamber_thickness, chamber_y-chamber_thickness, chamber_z-chamber_thickness);

  TGeoCompositeShape* cs_chamber = new TGeoCompositeShape("cs_chamber", "shape_chamber-shape_sub-shape_vacuum");
  TGeoCompositeShape* cs_vacuum = new TGeoCompositeShape("cs_vacuum", "shape_vacuum-shape_sub");

  TGeoVolume* FwdChamber = new TGeoVolume("Fwd_Chamber", cs_chamber, ChamberVolMed);
  FwdChamber->SetLineColor(16);
  FwdChamber->SetTransparency(60);
  TGeoVolume* FwdVacuum  = new TGeoVolume("Fwd_Vacuum", cs_vacuum, VacuumVolMed);
  // FwdVacuum->SetLineColor(kGreen);
  // FwdVacuum->SetVisibility(kFALSE);

  // Fwd dectectors: Dimensions of the detecors (x,y,z), unit: cm
  Double_t fwd_x,fwd_y,fwd_z;
  fwd_x = 12./2;// larger than 12cm, to be defined
  fwd_y = 10./2;
  fwd_z = 2./2;
  TGeoVolume* SensorSc1 = gGeoMan->MakeBox("SensorSc1", ScintillatorVolMed, fwd_x, fwd_y, fwd_z);
  SensorSc1->SetLineColor(38);
  TGeoVolume* SensorSc2 = gGeoMan->MakeBox("SensorSc2", ScintillatorVolMed, fwd_x, fwd_y, fwd_z);
  SensorSc2->SetLineColor(38);

  Double_t sc_gap  = 10; // gap between Sc1 and Sc2
  Double_t sc_align_z = -chamber_z + fwd_z + l_cone;
  Double_t sc_align_x = -fwd_x-3-1; // 3 is radius of the pipe, 1 is the gap between detector and the pipe
  TGeoTranslation *trans_sc1=new TGeoTranslation(sc_align_x, 0, sc_align_z);
  TGeoTranslation *trans_sc2=new TGeoTranslation(sc_align_x, 0, sc_align_z + sc_gap);

  TGeoVolumeAssembly *Fwd_Detectors = new TGeoVolumeAssembly("Fwd_Detectors");
  Fwd_Detectors->AddNode(SensorSc1, 1);
  Fwd_Detectors->AddNode(SensorSc2, 1, new TGeoTranslation(0,0,sc_gap));
  FwdVacuum->AddNode(Fwd_Detectors, 1, trans_sc1);

  // FwdVacuum->AddNode(SensorSc1, 1, trans_sc1);
  // FwdVacuum->AddNode(SensorSc2, 1, trans_sc2);

  // Add FwdChamber to the top volume
  Double_t l_target = 210; // from KoaPipe, unit in cm
  Double_t l_snake  = 257.3;
  Double_t z_offset= l_target + l_snake + chamber_z;
  TGeoTranslation *trans_zoffset=new TGeoTranslation(0., 0., z_offset);

  /* Beam Profile Monitor detector*/
  if(WithMonitor){
    TGeoVolume* MonitorSc1 = gGeoMan->MakeBox("MonitorSc1", ScintillatorVolMed, fwd_x, fwd_y, fwd_z);
    MonitorSc1->SetLineColor(kRed);
    TGeoVolume* MonitorSc2 = gGeoMan->MakeBox("MonitorSc2", ScintillatorVolMed, fwd_x, fwd_y, fwd_z);
    MonitorSc2->SetLineColor(kRed);

    TGeoTranslation *trans_monitor_sc1=new TGeoTranslation(-sc_align_x, 0, sc_align_z);
    TGeoTranslation *trans_monitor_sc2=new TGeoTranslation(-sc_align_x, 0, sc_align_z + sc_gap);

    TGeoVolumeAssembly *Fwd_Monitors = new TGeoVolumeAssembly("Fwd_Monitors");
    Fwd_Monitors->AddNode(MonitorSc1, 1);
    Fwd_Monitors->AddNode(MonitorSc2, 1, new TGeoTranslation(0,0,sc_gap));
    FwdVacuum->AddNode(Fwd_Monitors, 1, trans_monitor_sc1);
    // FwdVacuum->AddNode(MonitorSc1, 1, trans_monitor_sc1);
    // FwdVacuum->AddNode(MonitorSc2, 1, trans_monitor_sc2);
  }

  // // alternative way: assemblyvolume
  TGeoVolumeAssembly* FwdArm = new TGeoVolumeAssembly("Fwd");
  FwdArm->AddNode(FwdVacuum, 1);
  if(WithChamber){
    FwdArm->AddNode(FwdChamber, 1);
  }
  top->AddNode(FwdArm, 1, trans_zoffset);

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

