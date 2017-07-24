/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaFwdGeo.h"
#include "FairGeoNode.h"

ClassImp(KoaFwdGeo)

// -----   Default constructor   -------------------------------------------
KoaFwdGeo::KoaFwdGeo()
  : FairGeoSet()
{
  // Constructor
  // fName has to be the name used in the geometry for all volumes.
  // If there is a mismatch the geometry cannot be build.
  fName="KoaFwd";
  maxSectors=0;
  maxModules=10;
}

// -------------------------------------------------------------------------

const char* KoaFwdGeo::getModuleName(Int_t m)
{
  /** Returns the module name of KoaFwd number m
      Setting KoaFwd here means that all modules names in the
      ASCII file should start with KoaFwd otherwise they will
      not be constructed
  */
  sprintf(modName,"KoaFwd%i",m+1);
  return modName;
}

const char* KoaFwdGeo::getEleName(Int_t m)
{
  /** Returns the element name of Det number m */
  sprintf(eleName,"KoaFwd%i",m+1);
  return eleName;
}
