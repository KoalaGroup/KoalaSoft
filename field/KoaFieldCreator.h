/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    KoaFieldCreator header file                  -----
// -----                Created 26/03/14  by M. Al-Turany              -----
// -------------------------------------------------------------------------


#ifndef KoaFieldCreator_H
#define KoaFieldCreator_H

#include "FairFieldFactory.h"

class KoaFieldPar;

class FairField;

class KoaFieldCreator : public FairFieldFactory 
{

 public:
  KoaFieldCreator();
  virtual ~KoaFieldCreator();
  virtual FairField* createFairField();
  virtual void SetParm();
  ClassDef(KoaFieldCreator,1);
  
 protected:
  KoaFieldPar* fFieldPar;
  
 private:
  KoaFieldCreator(const KoaFieldCreator&);
  KoaFieldCreator& operator=(const KoaFieldCreator&);

};
#endif //KoaFieldCreator_H
