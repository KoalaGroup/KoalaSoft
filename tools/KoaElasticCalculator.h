/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                 KoaElasticCalculator header file                    ------
// -----                 Created 13/06/19  by Y. Zhou                 -----
// -------------------------------------------------------------------------


/** KoaElasticCalculator.h
 ** Helper class to calculate kinematic related values, functions of proton-proton
 ** elastic scattering.
 ** The mathematical form of elastic scattering is adopted from Aida's code.
 ** [TODO] The correctness of this form is to be checked again.
 ** @author Y.Zhou <y.zhou@fz-juelich.de>
 **/

#ifndef KOA_ELASTICCALCULATOR_H
#define KOA_ELASTICCALCULATOR_H 1

#include "TObject.h"

class KoaElasticCalculator : public TObject
{
 public:
  KoaElasticCalculator();
  ~KoaElasticCalculator();

 private:

  ClassDef(KoaElasticCalculator, 1)
};

#endif
