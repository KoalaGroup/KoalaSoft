/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    KoaPipe  file                               -----
// -----                Created by M. Al-Turany  June 2014             -----
// -------------------------------------------------------------------------

#include "KoaPipe.h"
#include "TList.h"
#include "TObjArray.h"

#include "TGeoPcon.h"
#include "TGeoTube.h"
#include "TGeoMaterial.h"
#include "TGeoMedium.h"
#include "TGeoCompositeShape.h"
#include "TGeoMatrix.h"
#include "TGeoManager.h"
#include "TROOT.h"
#include "FairGeoLoader.h"
#include "FairGeoBuilder.h"
#include "FairGeoMedia.h"
#include "FairGeoMedium.h"
#include "FairGeoInterface.h"


KoaPipe::~KoaPipe()
{
}
KoaPipe::KoaPipe()
  : FairModule()
{
}

KoaPipe::KoaPipe(const char * name, const char * title)
  : FairModule(name ,title)
{
}


// -----  ConstructGeometry  --------------------------------------------------
void KoaPipe::ConstructGeometry()
{
  TString notdefined("Not defined");
  TString fileName=GetGeometryFileName();
  if (fileName.EqualTo(notdefined)) {
    LOG(INFO)<<"Constructing default KoaPipe geometry"<<fileName<<FairLogger::endl;
    ConstructDefaultGeometry();
  } else if (fileName.EndsWith(".root")) {
    LOG(INFO)<<"Constructing KoaPipe geometry from ROOT file "<<fileName<<FairLogger::endl;
    ConstructRootGeometry();
  // } else if (fileName.EndsWith(".geo")){
    // LOG(INFO)<<"Constructing KoaPipe geometry from ASCII file"<<fileName<<FairLogger::endl;
    // ConstructASCIIGeometry();
  } else{
    LOG(FATAL) << "Geometry format not supported." << FairLogger::endl;
  }
}
// ----------------------------------------------------------------------------

void KoaPipe::ConstructDefaultGeometry()
{
      TGeoVolume *top=gGeoManager->GetTopVolume();
    
      // Materials
      TGeoManager* gGeoMan = (TGeoManager*)gROOT->FindObject("FAIRGeom");
     FairGeoLoader* loader=FairGeoLoader::Instance();
     FairGeoInterface* GeoInterface =loader->getGeoInterface();
     FairGeoMedia*     GeoMedia = GeoInterface->getMedia();
     FairGeoBuilder*   GeoBuild = loader->getGeoBuilder();

     FairGeoMedium* FairVacuum = GeoMedia->getMedium("vacuum");
     FairGeoMedium* FairAluminum = GeoMedia->getMedium("Aluminum");
     FairGeoMedium* FairMylar = GeoMedia->getMedium("mylar");

     GeoBuild->createMedium(FairVacuum);
     GeoBuild->createMedium(FairAluminum);
     GeoBuild->createMedium(FairMylar);

     TGeoMedium* Vacuum = gGeoMan->GetMedium("vacuum");
     TGeoMedium* Aluminum = gGeoMan->GetMedium("Aluminum");
     TGeoMedium* Mylar = gGeoMan->GetMedium("mylar");

     // Geometry
     /* Target Chamber
      */
     Double_t chamber_thickness = 0.5;  // thickness of target chamber [cm]
     Double_t chamber_x,chamber_y,chamber_z;
     chamber_x = 30./2;
     chamber_y = 25./2;
     chamber_z = 50./2;

     Double_t front_pipe_z = 40;
     Double_t target_flange_radius = 5./2;
     Double_t front_pipe_radius = 9./2;
     Double_t rec_flange_radius = 20./2;
     Double_t rec_center_offset = 5;
     TGeoBBox* shape_chamber = new TGeoBBox("shape_chamber", chamber_x+chamber_thickness, chamber_y+chamber_thickness, chamber_z+chamber_thickness);
     TGeoBBox* vshape_chamber = new TGeoBBox("vshape_chamber", chamber_x, chamber_y, chamber_z);
     TGeoTube* sshape_front_pipe = new TGeoTube("sshape_front_pipe", 0, front_pipe_radius, chamber_z+10);
     TGeoTube* sshape_target_pipe = new TGeoTube("sshape_target_pipe", 0, target_flange_radius, chamber_y+10);
     TGeoTube* sshape_flange = new TGeoTube("sshape_flange", 0, rec_flange_radius, chamber_x);

     TGeoRotation *rot_sshape_target_pipe = new TGeoRotation("rot_sshape_target_pipe",90,0,180,0,90,90);
     TGeoCombiTrans* ct_sshape_target_pipe = new TGeoCombiTrans("ct_sshape_target_pipe",0,0,chamber_z-front_pipe_z,rot_sshape_target_pipe);
     ct_sshape_target_pipe->RegisterYourself();
     TGeoRotation *rot_sshape_flange = new TGeoRotation("rot_sshape_flange", 180, 90, 90, 90, 90, 0);
     TGeoCombiTrans* ct_sshape_flange = new TGeoCombiTrans("ct_sshape_flange", 10, 0, chamber_z-front_pipe_z+rec_center_offset, rot_sshape_flange);
     ct_sshape_flange->RegisterYourself();

     TGeoCompositeShape* cs_target_chamber = new TGeoCompositeShape("cs_target_chamber","shape_chamber-vshape_chamber-(sshape_target_pipe:ct_sshape_target_pipe)-sshape_front_pipe-(sshape_flange:ct_sshape_flange)");
     TGeoVolume* target_chamber = new TGeoVolume("KoaPipe_TargetChamber", cs_target_chamber, Aluminum);
     target_chamber->SetLineColor(15);
     TGeoVolume* target_chamber_vacuum = new TGeoVolume("KoaVPipe_TargetChamber",vshape_chamber, Vacuum);
     target_chamber_vacuum->SetTransparency(100);

     TGeoTranslation *trans_target_chamber = new TGeoTranslation(0, 0, front_pipe_z-chamber_z);
     top->AddNode(target_chamber, 1, trans_target_chamber);
     top->AddNode(target_chamber_vacuum, 1, trans_target_chamber);

     /* Pipe: target to cone
      */
    Int_t nSects=4;
    Double_t pipe_thickness = 0.5;     // thickness of beam pipe [cm]
    Double_t l_target,l_snake;
    l_target = 210; //in cm
    l_snake  = 257.3; //in cm, corresponding to acceptance 0.0214 rad(the acceptance of the first segment of the pipe).
    Double_t z_target_to_cone[] = { front_pipe_z + chamber_thickness, l_target, l_target, l_target+l_snake};    // in cm
    Double_t r_target_to_cone[] = { 4.5, 4.5, 10, 10};    // in cm
    TGeoPcon* shape_target_to_cone = new TGeoPcon(0., 360., nSects);
    for (Int_t iSect = 0; iSect < nSects; iSect++) {
        shape_target_to_cone->DefineSection(iSect, z_target_to_cone[iSect], r_target_to_cone[iSect], r_target_to_cone[iSect]+pipe_thickness);
    }
    TGeoVolume* pipe_target_to_cone = new TGeoVolume("KoaPipe_TarToCone", shape_target_to_cone, Aluminum);
    pipe_target_to_cone->SetLineColor(14);

    Double_t z_vtarget_to_cone[] = { front_pipe_z , l_target, l_target, l_target+l_snake};    // in cm
    TGeoPcon* vshape_target_to_cone = new TGeoPcon(0.,360.,nSects);
    for(Int_t iSect = 0; iSect < nSects; iSect++){
      vshape_target_to_cone->DefineSection(iSect, z_vtarget_to_cone[iSect], 0., r_target_to_cone[iSect]);
    }
    TGeoVolume* vpipe_target_to_cone = new TGeoVolume("KoaVPipe_TarToCone", vshape_target_to_cone, Vacuum);
    vpipe_target_to_cone->SetTransparency(100);

    // add to world
    top->AddNode(pipe_target_to_cone, 1);
    top->AddNode(vpipe_target_to_cone, 1);

    /* Pipe: cone */
    nSects = 2;
    Double_t cone_thickness = 0.003; // in cm, 30um
    Double_t l_cone = 32; // in cm
    Double_t z_cone[] = {l_target+l_snake, l_target+l_snake+l_cone};
    Double_t r_cone[] = {10, 3};
    TGeoPcon* shape_cone = new TGeoPcon(0., 360., nSects);
    for(Int_t iSect = 0; iSect < nSects; iSect++){
      shape_cone->DefineSection(iSect, z_cone[iSect], r_cone[iSect], r_cone[iSect]+cone_thickness);
    }
    TGeoVolume* pip_cone = new TGeoVolume("KoaPipe_Cone", shape_cone, Mylar);
    pip_cone->SetLineColor(14);

    TGeoPcon* vshape_cone = new TGeoPcon(0., 360., nSects);
    for(Int_t iSect = 0; iSect < nSects; iSect++){
      vshape_cone->DefineSection(iSect, z_cone[iSect], 0., r_cone[iSect]);
    }
    TGeoVolume* vpip_cone = new TGeoVolume("KoaVPipe_Cone", vshape_cone, Vacuum);
    vpip_cone->SetTransparency(100);

    // add to world
    top->AddNode(pip_cone, 1);
    top->AddNode(vpip_cone, 1);

    /* Pipe: end */
    nSects = 2;
    Double_t z_end[] = {l_target+l_snake+l_cone, 600};
    Double_t r_end[] = {3, 3};
    TGeoPcon* shape_end = new TGeoPcon(0., 360., nSects);
    for(Int_t iSect = 0; iSect < nSects; iSect++){
      shape_end->DefineSection(iSect, z_end[iSect], r_end[iSect], r_end[iSect]+pipe_thickness);
    }
    TGeoVolume* pip_end = new TGeoVolume("KoaPipe_End", shape_end, Aluminum);
    pip_end->SetLineColor(14);

    TGeoPcon* vshape_end = new TGeoPcon(0., 360., nSects);
    for(Int_t iSect = 0; iSect < nSects; iSect++){
      vshape_end->DefineSection(iSect, z_end[iSect], 0., r_end[iSect]);
    }
    TGeoVolume* vpip_end = new TGeoVolume("KoaVPipe_End", vshape_end, Vacuum);
    vpip_end->SetTransparency(100);

    // add to world
    top->AddNode(pip_end, 1);
    top->AddNode(vpip_end, 1);
}

ClassImp(KoaPipe)

