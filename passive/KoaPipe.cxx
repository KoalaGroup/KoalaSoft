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
     Int_t nSects=4;
     /* Pipe: target to cone
      */
    Double_t l_target,l_snake;
    l_target = 210; //in cm
    l_snake  = 257.3; //in cm, corresponding to acceptance 0.0214 rad(the acceptance of the first segment of the pipe).
    Double_t z_target_to_cone[] = { -50, l_target, l_target, l_target+l_snake};    // in cm
    Double_t r_target_to_cone[] = { 4.5, 4.5, 10, 10};    // in cm
    Double_t pipe_thickness = 0.5;     // thickness of beam pipe [cm]
    TGeoPcon* shape_target_to_cone = new TGeoPcon(0., 360., nSects);
    for (Int_t iSect = 0; iSect < nSects; iSect++) {
        shape_target_to_cone->DefineSection(iSect, z_target_to_cone[iSect], r_target_to_cone[iSect], r_target_to_cone[iSect]+pipe_thickness);
    }
    TGeoVolume* pipe_target_to_cone = new TGeoVolume("KoaPipe_TarToCone", shape_target_to_cone, Aluminum);

    TGeoPcon* vshape_target_to_cone = new TGeoPcon(0.,360.,nSects);
    for(Int_t iSect = 0; iSect < nSects; iSect++){
      vshape_target_to_cone->DefineSection(iSect, z_target_to_cone[iSect], 0., r_target_to_cone[iSect]);
    }
    TGeoVolume* vpipe_target_to_cone = new TGeoVolume("KoaVPipe_TarToCone", vshape_target_to_cone, Vacuum);

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

    TGeoPcon* vshape_cone = new TGeoPcon(0., 360., nSects);
    for(Int_t iSect = 0; iSect < nSects; iSect++){
      vshape_cone->DefineSection(iSect, z_cone[iSect], 0., r_cone[iSect]);
    }
    TGeoVolume* vpip_cone = new TGeoVolume("KoaVPipe_Cone", vshape_cone, Vacuum);

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

    TGeoPcon* vshape_end = new TGeoPcon(0., 360., nSects);
    for(Int_t iSect = 0; iSect < nSects; iSect++){
      vshape_end->DefineSection(iSect, z_end[iSect], 0., r_end[iSect]);
    }
    TGeoVolume* vpip_end = new TGeoVolume("KoaVPipe_End", vshape_end, Vacuum);

    // add to world
    top->AddNode(pip_end, 1);
    top->AddNode(vpip_end, 1);
}

ClassImp(KoaPipe)

