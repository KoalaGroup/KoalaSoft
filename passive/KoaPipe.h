/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    KoaPipe file                                -----
// -----                Created by M. Al-Turany  June 2014             -----
// -------------------------------------------------------------------------

#ifndef PIPE_H
#define PIPE_H

#include "FairModule.h"

class KoaPipe : public FairModule {
  public:
    KoaPipe(const char * name, const char *Title="Koa Pipe");
    KoaPipe();

    virtual ~KoaPipe();
    virtual void ConstructGeometry();
   
 private:
    void ConstructDefaultGeometry();

  ClassDef(KoaPipe,1) //KoaPIPE

};

#endif //PIPE_H

