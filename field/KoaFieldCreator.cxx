/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                    KoaConstField header file                  -----
// -----                Created 25/03/14  by M. Al-Turany              -----
// -------------------------------------------------------------------------

#include "KoaFieldCreator.h"

#include "KoaFieldPar.h"
#include "KoaConstField.h"

#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairField.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

static KoaFieldCreator gKoaFieldCreator;

KoaFieldCreator::KoaFieldCreator()
  :FairFieldFactory(),
   fFieldPar(NULL)
{
	fCreator=this;
}

KoaFieldCreator::~KoaFieldCreator()
{
}

void KoaFieldCreator::SetParm()
{
  FairRunAna *Run = FairRunAna::Instance();
  FairRuntimeDb *RunDB = Run->GetRuntimeDb();
  fFieldPar = (KoaFieldPar*) RunDB->getContainer("KoaFieldPar");

}

FairField* KoaFieldCreator::createFairField()
{ 
  FairField *fMagneticField=0;

  if ( ! fFieldPar ) {
    cerr << "-E-  No field parameters available!"
	 << endl;
  }else{
	// Instantiate correct field type
	Int_t fType = fFieldPar->GetType();
	if      ( fType == 0 ) fMagneticField = new KoaConstField(fFieldPar);
    else cerr << "-W- FairRunAna::GetField: Unknown field type " << fType
		<< endl;
	cout << "New field at " << fMagneticField << ", type " << fType << endl;
	// Initialise field
	if ( fMagneticField ) {
		fMagneticField->Init();
		fMagneticField->Print(0);
    // FairField's Print function need an argument. Argument "0" in this case is meaningless.
	}
  }
  return fMagneticField;
}


ClassImp(KoaFieldCreator)
