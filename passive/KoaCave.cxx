
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaCave.h"

#include "KoaGeoCave.h"                // for KoaGeoCave
#include "FairGeoInterface.h"           // for FairGeoInterface
#include "FairGeoLoader.h"              // for FairGeoLoader
#include "FairGeoNode.h"                // for FairGeoNode
#include "FairGeoPassivePar.h"          // for FairGeoPassivePar
#include "FairGeoVolume.h"              // for FairGeoVolume
#include "FairRun.h"                    // for FairRun
#include "FairRuntimeDb.h"              // for FairRuntimeDb

#include "TList.h"                      // for TListIter, TList (ptr only)
#include "TObjArray.h"                  // for TObjArray
#include "TString.h"                    // for TString

#include <stddef.h>                     // for NULL

ClassImp(KoaCave)

void KoaCave::ConstructGeometry()
{
  FairGeoLoader* loader=FairGeoLoader::Instance();
  FairGeoInterface* GeoInterface =loader->getGeoInterface();
  KoaGeoCave* MGeo=new KoaGeoCave();
  MGeo->setGeomFile(GetGeometryFileName());
  GeoInterface->addGeoModule(MGeo);
  Bool_t rc = GeoInterface->readSet(MGeo);
  if ( rc ) { MGeo->create(loader->getGeoBuilder()); }
 
}
KoaCave::KoaCave()
:FairModule()
{
}

KoaCave::~KoaCave()
{

}
KoaCave::KoaCave(const char* name,  const char* Title)
  : FairModule(name ,Title)
{
  world[0] = 0;
  world[1] = 0;
  world[2] = 0;
}

KoaCave::KoaCave(const KoaCave& right)
  : FairModule(right)
{
  world[0] = right.world[0];
  world[1] = right.world[1];
  world[2] = right.world[2];
}

FairModule* KoaCave::CloneModule() const
{
  return new KoaCave(*this);
}

