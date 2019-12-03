/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "KoaElasticCalculator.h"
#include "KoaMapEncoder.h"
#include "TMath.h"
#include "Math/Vector4D.h"
#include "FairLogger.h"

using namespace ROOT::Math;

ClassImp(KoaElasticCalculator)

Double_t KoaElasticCalculator::fProtonMass = 0.938272081;

KoaElasticCalculator::KoaElasticCalculator(Double_t mom, Double_t distance) :
  fMom(mom),
  fDistance(distance)
{
  PxPyPzMVector beam(0,0,fMom,fProtonMass);
  fKappa = (beam.energy()+beam.mass())/(beam.energy()-beam.mass());
}

KoaElasticCalculator::~KoaElasticCalculator()
{
  
}

Double_t KoaElasticCalculator::GetEnergyByZ(Double_t zposition)
{
  if( zposition<0 ) {
    LOG(ERROR) << "z position should be larger than 0";
  }

  Double_t alpha = TMath::ATan(zposition/fDistance/10.);
  return GetEnergyByAlpha(alpha);
}

Double_t KoaElasticCalculator::GetEnergyByAlpha(Double_t alpha)
{
  Double_t sin_alpha = TMath::Sin(alpha);
  return 1000*2*fProtonMass*sin_alpha*sin_alpha/(fKappa - sin_alpha*sin_alpha);
}

Double_t KoaElasticCalculator::operator() (Double_t* x, Double_t* p)
{
  Double_t alpha = TMath::ATan(x[0]/p[1]/10.);
  Double_t sin_alpha = TMath::Sin(alpha);

  PxPyPzMVector beam(0,0,p[0],fProtonMass);
  Double_t kappa = (beam.energy()+beam.mass())/(beam.energy()-beam.mass());

  return 1000*2*fProtonMass*sin_alpha*sin_alpha/(kappa - sin_alpha*sin_alpha);
}
