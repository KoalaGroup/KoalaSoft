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
  /* Only the distance of the sensor surface to IP is provided.
     Using this constructor, the class object is used only as a interface to calculate the elastic
     scattering kinematic parameters, such deposited energy at specific z and momentum.
     It has nothing to do with the sensor topology.
     mom in GeV, distance in cm
  */
  KoaElasticCalculator(Double_t mom, Double_t distance);
  ~KoaElasticCalculator();

  /* functor interface, which can be used to form TF1 in ROOT.
     It is relative independant and valid under both GeoModel and Non-GeoModel modes.
     x[0] is the z-position, p[0] is incident proton momentum, p[1] is distance to IP
     x[0] in mm, p[0] in GeV, p[1] in cm
   */
  Double_t operator() (Double_t *x, Double_t *p);

  /* Get-ers */

  /* Get deposited energy based on position along beam axis.
     It's valid both in GeoModel and Non-GeoModel modes. zposition in mm, return value in MeV */
  Double_t GetEnergyByZ(Double_t zposition);
  /* Get T of recoil proton by alpha. alpha is the angle between recoil proton momentum and axis perpendicular to beam axis. alpha in radian, return value in MeV */
  Double_t GetEnergyByAlpha(Double_t alpha);

 private:
  Double_t fMom; // momentum of incident proton, in GeV
  Double_t fDistance; // distance of strip center to IP, in cm

  static Double_t fProtonMass;
  Double_t fKappa;

  ClassDef(KoaElasticCalculator, 1)
};

#endif
