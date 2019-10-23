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

KoaPipe::KoaPipe(const KoaPipe& right)
  : FairModule(right)
{
}

// -----  ConstructGeometry  --------------------------------------------------
void KoaPipe::ConstructGeometry()
{
  TString notdefined("Not defined");
  TString fileName=GetGeometryFileName();
  if (fileName.EqualTo(notdefined)) {
    LOG(info)<<"Constructing default KoaPipe geometry"<<fileName;
    ConstructDefaultGeometry();
  } else if (fileName.EndsWith(".root")) {
    LOG(info)<<"Constructing KoaPipe geometry from ROOT file "<<fileName;
    ConstructRootGeometry();
  // } else if (fileName.EndsWith(".geo")){
    // LOG(info)<<"Constructing KoaPipe geometry from ASCII file"<<fileName;
    // ConstructASCIIGeometry();
  } else{
    LOG(fatal) << "Geometry format not supported." ;
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
     Double_t chamber_thickness = 1;  // thickness of target chamber [cm]
     Double_t chamber_x,chamber_y,chamber_z;
     chamber_x = 30./2;
     chamber_y = 25./2;
     chamber_z = 50./2;

     Double_t front_pipe_positioin = 40;
     Double_t target_flange_radius = 5./2;
     Double_t front_pipe_radius = 9./2;
     Double_t rec_flange_radius = 20./2;
     Double_t rec_center_offset = 5; // distance between IP and recoil adapter center

     // chamber and chamber_vacuum shape
     TGeoBBox* shape_chamber = new TGeoBBox("shape_chamber", chamber_x+chamber_thickness, chamber_y+chamber_thickness, chamber_z+chamber_thickness);
     TGeoBBox* vshape_chamber = new TGeoBBox("vshape_chamber", chamber_x, chamber_y, chamber_z);

     // shapes for substracting
     TGeoTube* sshape_front_pipe = new TGeoTube("sshape_front_pipe", 0, front_pipe_radius, chamber_z+10);
     TGeoTube* sshape_target_pipe = new TGeoTube("sshape_target_pipe", 0, target_flange_radius, chamber_y+10);
     TGeoTube* sshape_flange = new TGeoTube("sshape_flange", 0, rec_flange_radius, chamber_x);

     TGeoRotation *rot_sshape_target_pipe = new TGeoRotation("rot_sshape_target_pipe",90,0,180,0,90,90);
     TGeoCombiTrans* ct_sshape_target_pipe = new TGeoCombiTrans("ct_sshape_target_pipe",0,0,chamber_z-front_pipe_positioin,rot_sshape_target_pipe);
     ct_sshape_target_pipe->RegisterYourself();

     TGeoRotation *rot_sshape_flange = new TGeoRotation("rot_sshape_flange", 0, 0, 90, 90, 90, 180);
     TGeoCombiTrans* ct_sshape_flange = new TGeoCombiTrans("ct_sshape_flange", -10, 0, chamber_z-front_pipe_positioin+rec_center_offset, rot_sshape_flange);
     ct_sshape_flange->RegisterYourself();

     // volumes of chamber and chamber vacuum
     TGeoCompositeShape* cs_target_chamber = new TGeoCompositeShape("cs_target_chamber","shape_chamber-vshape_chamber-(sshape_target_pipe:ct_sshape_target_pipe)-sshape_front_pipe-(sshape_flange:ct_sshape_flange)");
     TGeoVolume* target_chamber = new TGeoVolume("KoaPipe_TargetChamber", cs_target_chamber, Aluminum);
     target_chamber->SetLineColor(15);
     TGeoVolume* target_chamber_vacuum = new TGeoVolume("KoaVPipe_TargetChamber",vshape_chamber, Vacuum);
     target_chamber_vacuum->SetTransparency(100);

     // move chamber to real position so that IP in origin point
     TGeoTranslation *trans_target_chamber = new TGeoTranslation(0, 0, front_pipe_positioin-chamber_z);
     top->AddNode(target_chamber, 1, trans_target_chamber);
     top->AddNode(target_chamber_vacuum, 1, trans_target_chamber);

     /* Pipe: target to cone
      */
    Int_t nSects=6;
    Double_t pipe_thickness = 0.5;     // thickness of beam pipe [cm]
    Double_t r_target_to_cone[] = { 4.5, 4.5, 10, 10};    // in cm
    Double_t l_fwd = 460; // distance between IP and first fwd surface
    Double_t fwd_chamber_gap = 10; //distance between fwd chamber edge and first fwd scintillator
    Double_t l_target,l_snake;
    l_target = 210; // [TODO] in cm
    l_snake  = l_fwd - fwd_chamber_gap - l_target; //in cm, corresponding to acceptance 0.0214 rad(the acceptance of the first segment of the pipe).
    Double_t z_target_to_cone[] = { front_pipe_positioin + chamber_thickness, l_target, l_target, l_target+pipe_thickness, l_target+pipe_thickness, l_target+l_snake};    // in cm
    TGeoPcon* shape_target_to_cone = new TGeoPcon(0., 360., nSects);
    for (Int_t iSect = 0; iSect < 2; iSect++) {
        shape_target_to_cone->DefineSection(iSect, z_target_to_cone[iSect], r_target_to_cone[iSect], r_target_to_cone[iSect]+pipe_thickness);
    }
    shape_target_to_cone->DefineSection(2, z_target_to_cone[2], r_target_to_cone[1], r_target_to_cone[2]+pipe_thickness);
    shape_target_to_cone->DefineSection(3, z_target_to_cone[3], r_target_to_cone[1], r_target_to_cone[2]+pipe_thickness);
    for (Int_t iSect = 4; iSect < 6; iSect++) {
      shape_target_to_cone->DefineSection(iSect, z_target_to_cone[iSect], r_target_to_cone[iSect-2], r_target_to_cone[iSect-2]+pipe_thickness);
    }
    TGeoVolume* pipe_target_to_cone = new TGeoVolume("KoaPipe_TarToCone", shape_target_to_cone, Aluminum);
    pipe_target_to_cone->SetLineColor(14);

    nSects=4;
    Double_t z_vtarget_to_cone[] = { front_pipe_positioin, l_target+pipe_thickness, l_target+pipe_thickness, l_target+l_snake};    // in cm
    TGeoPcon* vshape_target_to_cone = new TGeoPcon(0.,360.,nSects);
    for(Int_t iSect = 0; iSect < nSects; iSect++){
      vshape_target_to_cone->DefineSection(iSect, z_vtarget_to_cone[iSect], 0., r_target_to_cone[iSect]);
    }
    TGeoVolume* vpipe_target_to_cone = new TGeoVolume("KoaVPipe_TarToCone", vshape_target_to_cone, Vacuum);
    vpipe_target_to_cone->SetTransparency(100);

    // add to world
    top->AddNode(pipe_target_to_cone, 1);
    top->AddNode(vpipe_target_to_cone, 1);

    // cluster-target pipe
    Double_t l_cluster_pipe_up = 100.;
    Double_t l_cluster_pipe_down = 50.;
    TGeoBBox* shape_cluster_box = new TGeoBBox("shape_cluster_box", 15,15,15);
    TGeoVolume* cluster_box = new TGeoVolume("KoaPipe_Cluster_Box", shape_cluster_box, Aluminum);
    cluster_box->SetLineColor(14);
    TGeoTranslation* ct_cluster_box = new TGeoTranslation("ct_cluster_box", 0, 15+l_cluster_pipe_up+chamber_y+chamber_thickness, 0);
    top->AddNode(cluster_box, 1, ct_cluster_box);

    TGeoTube* shape_cluster_pipe_up = new TGeoTube("shape_cluster_pipe_up", target_flange_radius, target_flange_radius+chamber_thickness, l_cluster_pipe_up/2);
    TGeoVolume* cluster_pipe_up = new TGeoVolume("cluster_pipe_up", shape_cluster_pipe_up, Aluminum);
    cluster_pipe_up->SetLineColor(14);
    TGeoTube* vshape_cluster_pipe_up = new TGeoTube("vshape_cluster_pipe_up", 0, target_flange_radius, (l_cluster_pipe_up+chamber_thickness)/2);
    TGeoVolume* vcluster_pipe_up = new TGeoVolume("vcluster_pipe_up", vshape_cluster_pipe_up, Vacuum);
    vcluster_pipe_up->SetTransparency(100);
    TGeoCombiTrans* ct_cluster_pipe_up = new TGeoCombiTrans("ct_cluster_pipe_up", 0, l_cluster_pipe_up/2+chamber_y+chamber_thickness,0, rot_sshape_target_pipe);
    TGeoCombiTrans* ct_vcluster_pipe_up = new TGeoCombiTrans("ct_vcluster_pipe_up", 0, (l_cluster_pipe_up+chamber_thickness)/2+chamber_y,0,rot_sshape_target_pipe);
    top->AddNode(cluster_pipe_up, 1, ct_cluster_pipe_up);
    top->AddNode(vcluster_pipe_up, 1, ct_vcluster_pipe_up);

    TGeoTube* shape_cluster_pipe_down = new TGeoTube("shape_cluster_pipe_down", target_flange_radius, target_flange_radius+chamber_thickness, l_cluster_pipe_down/2);
    TGeoVolume* cluster_pipe_down = new TGeoVolume("cluster_pipe_down",shape_cluster_pipe_down,Aluminum);
    cluster_pipe_down->SetLineColor(14);
    TGeoTube* vshape_cluster_pipe_down = new TGeoTube("vshape_cluster_pipe_down", 0, target_flange_radius, (l_cluster_pipe_down+chamber_thickness)/2);
    TGeoVolume* vcluster_pipe_down = new TGeoVolume("vcluster_pipe_down", vshape_cluster_pipe_down, Vacuum);
    vcluster_pipe_down->SetTransparency(100);

    TGeoCombiTrans* ct_cluster_pipe_down = new TGeoCombiTrans("ct_cluster_pipe_down", 0, -l_cluster_pipe_down/2-chamber_y-chamber_thickness,0, rot_sshape_target_pipe);
    TGeoCombiTrans* ct_vcluster_pipe_down = new TGeoCombiTrans("ct_vcluster_pipe_down", 0, -(l_cluster_pipe_down+chamber_thickness)/2-chamber_y,0,rot_sshape_target_pipe);
    top->AddNode(cluster_pipe_down, 1, ct_cluster_pipe_down);
    top->AddNode(vcluster_pipe_down, 1, ct_vcluster_pipe_down);
}

FairModule* KoaPipe::CloneModule() const
{
  return new KoaPipe(*this);
}

ClassImp(KoaPipe)

