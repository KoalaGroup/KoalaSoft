/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// in root all sizes are given in cm

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

// Name of geometry version and output file
const TString geoVersion = "rec";
const TString FileName = geoVersion + ".root";
const TString FileName1 = geoVersion + "_geomanager.root";

// Names of the different used materials which are used to build the modules
// The materials are defined in the global media.geo file 
const TString KeepingVolumeMedium     = "air";
const TString BoxVolumeMedium         = "silicon";

// some global variables
TGeoManager* gGeoMan = NULL;  // Pointer to TGeoManager instance

// Forward declarations
void create_materials_from_media_file();

void build_geom() {
  // Load the necessary FairRoot libraries 
//  gROOT->LoadMacro("$VMCWORKDIR/gconfig/basiclibs.C");
//  basiclibs();
//  gSystem->Load("libGeoBase");
//  gSystem->Load("libParBase");
//  gSystem->Load("libBase");

  TStopwatch timer;
  timer.Start();
  // Load needed material definition from media.geo file
  create_materials_from_media_file();

  // Get the GeoManager for later usage
  gGeoMan = (TGeoManager*) gROOT->FindObject("FAIRGeom");
  gGeoMan->SetVisLevel(7);  
  
  // Medium
  TGeoMedium* AirVolMed   = gGeoMan->GetMedium("air");
  TGeoMedium* SiVolMed   = gGeoMan->GetMedium("silicon");
  TGeoMedium* GeVolMed   = gGeoMan->GetMedium("germanium");

  // Create the top volume 
  TGeoVolume* top = gGeoMan->MakeBox("cave", AirVolMed,20000., 20000.,20000.);
  gGeoMan->SetTopVolume(top);

  // Dimensions of the detecors (x,y,z), unit: cm
  Float_t si_size[3]={0.1/2,5./2,7.68/2};
  Float_t ge1_size[3]={0.5/2,5.0/2,8.04/2};
  Float_t ge2_size[3]={1.1/2,5.0/2,8.04/2};
  Float_t envelop[3]={2.0/2,14.65/2,29.9/2};
  TGeoVolume* Si1 = gGeoMan->MakeBox("Si1", SiVolMed, si_size[0],si_size[1],si_size[2]);
  Si1->SetLineColor(kBlue); // set line color 
  Si1->SetTransparency(70); // set transparency 
  TGeoVolume* Si2 = gGeoMan->MakeBox("Si2", SiVolMed, si_size[0],si_size[1],si_size[2]);
  Si2->SetLineColor(kBlue); // set line color 
  Si2->SetTransparency(70); // set transparency 
  TGeoVolume* Ge1 = gGeoMan->MakeBox("Ge1", GeVolMed, ge1_size[0],ge1_size[1],ge1_size[2]);
  Ge1->SetLineColor(kRed); // set line color 
  Ge1->SetTransparency(70); // set transparency 
  TGeoVolume* Ge2 = gGeoMan->MakeBox("Ge2", GeVolMed, ge2_size[0],ge2_size[1],ge2_size[2]);
  Ge2->SetLineColor(kRed); // set line color 
  Ge2->SetTransparency(70); // set transparency 
  TGeoVolume* Envelope = gGeoMan->MakeBox("MasterRec", AirVolMed, envelop[0], envelop[1], envelop[2]);
  Envelope->SetVisibility(kFALSE);

  // Placement
  Float_t si1_align[3]={-0.1/2,0.575+5./2,-29.9/2+7.68/2+1.66};
  Float_t si2_align[3]={-0.1/2,-0.575-5./2,-29.9/2+7.68/2+1.66+5.28};
  Float_t ge1_align[3]={-0.5/2,0.575_5./2,-29.9/2+7.68/2+1.66+5.28+7.68/2-1.09+8.04/2};
  Float_t ge2_align[3]={-1.1/2,-0.575-5./2,-29.9/2+7.68/2+1.66+5.28+7.68/2-1.09+8.04/2-1.2+8.04/2};

  TGeoTranslation *trans_si1=new TGeoTranslation(si1_align[0],si1_align[1],si1_align[2]);
  Envelope->AddNode(Si1, 1, trans_si1);
  TGeoTranslation *trans_si2=new TGeoTranslation(si2_align[0],si2_align[1],si2_align[2]);
  Envelope->AddNode(Si2, 1, trans_si2);
  TGeoTranslation *trans_ge1=new TGeoTranslation(ge1_align[0],ge1_align[1],ge1_align[2]);
  Envelope->AddNode(Ge1, 1, trans_ge1);
  TGeoTranslation *trans_ge2=new TGeoTranslation(ge2_align[0],ge2_align[1],ge2_align[2]);
  Envelope->AddNode(Ge2, 1, trans_ge2);

  // Align
  Float_t z_offset=-0.12*5;//5 strips offset
  TGeoTranslation *trans_zoffset=new TGeoTranslation(0.,0.,29.9/2-1.66+z_offset);
  top->AddNode(Envelope, 1, trans_zoffset);

  cout<<"Voxelizing."<<endl;
  top->Voxelize("");
  gGeoMan->CloseGeometry();

  gGeoMan->CheckOverlaps(0.001);
  gGeoMan->PrintOverlaps();
  gGeoMan->Test();

  TFile* outfile = TFile::Open(FileName,"RECREATE");
  top->Write();
  outfile->Close();

  TFile* outfile = TFile::Open(FileName1,"RECREATE");
  gGeoMan->Write();
  outfile->Close();

  //  top->Draw("ogl");
  //top->Raytrace();

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
  // include check if all media are found

  geoBuild->createMedium(air);
  geoBuild->createMedium(silicon);
  geoBuild->createMedium(germanium);
}

