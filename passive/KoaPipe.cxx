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
  TString fileName=GetGeometryFileName();
  if (fileName.EndsWith(".root")) {
    LOG(info)<<"Constructing KoaPipe geometry from ROOT file "<<fileName;
    ConstructRootGeometry();
  } else if (fileName.EndsWith(".geo")){
    LOG(info)<<"Constructing KoaPipe geometry from ASCII file"<<fileName;
    ConstructASCIIGeometry();
  } else{
    LOG(fatal) << "Geometry format not supported." ;
  }
}

FairModule* KoaPipe::CloneModule() const
{
  return new KoaPipe(*this);
}

ClassImp(KoaPipe)

