/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAFWDGEOPAR_H
#define KOAFWDGEOPAR_H

#include "FairParGenericSet.h"

class TObjArray;
class FairParamList;

class KoaFwdGeoPar       : public FairParGenericSet
{
  public:

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoPassNodes;

    KoaFwdGeoPar(const char* name="KoaFwdGeoPar",
                      const char* title="KoaFwd Geometry Parameters",
                      const char* context="TestDefaultContext");
    ~KoaFwdGeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray* GetGeoPassiveNodes()   {return fGeoPassNodes;}

  private:
    KoaFwdGeoPar(const KoaFwdGeoPar&);
    KoaFwdGeoPar& operator=(const KoaFwdGeoPar&);

    ClassDef(KoaFwdGeoPar,1)
};

#endif
