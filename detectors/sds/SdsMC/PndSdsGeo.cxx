//*-- AUTHOR : Ilse Koenig
//*-- Created : 10/11/2003

/////////////////////////////////////////////////////////////
// CbmGeoTof
//
// Class for geometry of PndSds
//
/////////////////////////////////////////////////////////////

#include "PndSdsGeo.h"
#include "FairGeoNode.h"

ClassImp(PndSdsGeo)

PndSdsGeo::PndSdsGeo()
{
  // Constructor
  fName="sds";
  maxSectors=99;
  maxModules=99;
  //maxKeepinVolumes=99;
}

const char* PndSdsGeo::getModuleName(Int_t m)
{
  if ( m < 0 ) {
  	std::cout <<"-E- CbmGeoSts::getModuleName:: Module number "
  	       << m << " not known!" << std::endl;
	 return "";
	 }
  if ( m < 9 ) sprintf(fModName,"sdsstation0%i",m+1);
  else  sprintf(fModName,"sdsstation%i",m+1);
  return fModName;
}

const char* PndSdsGeo::getEleName(Int_t m)
{
  // Returns the element name of PndSds number m
  if (m < 9)
  	sprintf(fEleName,"sds0%i",m+1);
  else sprintf(fEleName,"sds%i",m+1);

  return fEleName;
}

const char* PndSdsGeo::getKeepinName(Int_t i, Int_t ) // j //[R.K.03/2017] unused variable(s)
{
   sprintf(fKeepinName,"SDSKeepin0%i",i+1);
   return fKeepinName;
}
