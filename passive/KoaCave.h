/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    KoaCave  file                               -----
// -----                Created 26/03/14  by M. Al-Turany              -----
// -------------------------------------------------------------------------


#ifndef Cave_H
#define Cave_H

#include "FairModule.h"                 // for FairModule

#include "Rtypes.h"                     // for KoaCave::Class, ClassDef, etc

class KoaCave : public FairModule
{
  public:
    KoaCave(const char* name, const char* Title="Exp Cave");
    KoaCave();
    virtual ~KoaCave();
    virtual void ConstructGeometry();


  private:
    Double_t world[3];
    ClassDef(KoaCave,1) //PNDCaveSD
};

#endif //Cave_H

