#include "PndSdsGeoPar.h"
#include "FairParamList.h"
#include <iostream>
#include <iomanip>
#include "TObjArray.h"

ClassImp(PndSdsGeoPar)

PndSdsGeoPar::PndSdsGeoPar(const char* name,const char* title,const char* context)
           : FairParGenericSet(name,title,context) ,
    fGeoSensNodes(new TObjArray()),
    fGeoPassNodes(new TObjArray())
{
  //fGeoSensNodes = new TObjArray();
  //fGeoPassNodes = new TObjArray();
}

PndSdsGeoPar::~PndSdsGeoPar(void) 
{
}

void PndSdsGeoPar::clear(void)
{
  if(fGeoSensNodes) 
    delete fGeoSensNodes;
  if(fGeoPassNodes) 
    delete fGeoPassNodes;
}

void PndSdsGeoPar::putParams(FairParamList* l) 
{
  if (!l) 
    return;
  
 // l->addObject("FairGeoNodes Sensitive List", fGeoSensNodes);
 // l->addObject("FairGeoNodes Passive List", fGeoPassNodes);
}

Bool_t PndSdsGeoPar::getParams(FairParamList* l) 
{
  if (!l)  return kFALSE;
//  if (!l->fillObject("FairGeoNodes Sensitive List", fGeoSensNodes))   return kFALSE;
//  if (!l->fillObject("FairGeoNodes Passive List", fGeoPassNodes)) return kFALSE;

  return kTRUE;
}
