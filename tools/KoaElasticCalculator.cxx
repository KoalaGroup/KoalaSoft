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
#include "TF1.h"
#include "Math/Vector4D.h"
#include "FairLogger.h"

using namespace ROOT::Math;

ClassImp(KoaElasticCalculator)

Double_t KoaElasticCalculator::fProtonMass = 0.938272081;

KoaElasticCalculator::KoaElasticCalculator(Double_t mom, Double_t rec_distance, Double_t fwd_distance) :
  fMom(mom),
  fRecDistance(rec_distance),
  fFwdDistance(fwd_distance)
{
  PxPyPzMVector beam(0,0,fMom,fProtonMass);
  fKappa = (beam.energy()+beam.mass())/(beam.energy()-beam.mass());
}

KoaElasticCalculator::KoaElasticCalculator(Double_t mom) :
  fMom(mom)
{
  PxPyPzMVector beam(0,0,fMom,fProtonMass);
  fKappa = (beam.energy()+beam.mass())/(beam.energy()-beam.mass());
}

KoaElasticCalculator::~KoaElasticCalculator()
{
  
}

Double_t KoaElasticCalculator::GetEnergyByRecZ(Double_t zposition, Double_t yoffset)
{
  if( zposition<0 ) {
    LOG(ERROR) << "fwd z position should be larger than 0";
  }

  double yposition = 3.175 + yoffset/10.; // in cm
  // double yposition = 0;
  double l = TMath::Sqrt(fRecDistance*fRecDistance+yposition*yposition);
  Double_t alpha = 180*TMath::ATan(zposition/10./l)/TMath::Pi();
  return GetEnergyByAlpha(alpha);
}

Double_t KoaElasticCalculator::GetEnergyByAlpha(Double_t alpha)
{
  Double_t sin_alpha = TMath::Sin(alpha/180*TMath::Pi());
  return 1000*2*fProtonMass*sin_alpha*sin_alpha/(fKappa - sin_alpha*sin_alpha);
}

Double_t KoaElasticCalculator::GetEnergyByTheta(Double_t theta)
{
  Double_t alpha = GetAlphaByTheta(theta);
  return GetEnergyByAlpha(alpha);
}

Double_t KoaElasticCalculator::GetEnergyByFwdX(Double_t xposition)
{
  if( xposition<0 ) {
    LOG(ERROR) << "recoil x position should be larger than 0";
  }

  Double_t theta = 180*TMath::ATan(xposition/fFwdDistance)/TMath::Pi();
  return GetEnergyByTheta(theta);
}

Double_t KoaElasticCalculator::GetThetaByAlpha(Double_t alpha)
{
  Double_t T = GetEnergyByAlpha(alpha)/1000.; //in GeV

  Double_t px_abs = TMath::Sqrt(T*T+2*fProtonMass*T)*TMath::Cos(alpha/180*TMath::Pi());
  Double_t pz_abs = fMom - TMath::Sqrt(T*T+2*fProtonMass*T)*TMath::Sin(alpha/180*TMath::Pi());

  Double_t tan_theta=px_abs/pz_abs;

  return TMath::ATan(tan_theta)/TMath::Pi()*180;
}

Double_t KoaElasticCalculator::GetAlphaByTheta(Double_t theta)
{
  auto GetThetaByAlpha_Imp = [] (Double_t* alpha, Double_t* Plab)
    {
      Double_t E_beam=TMath::Sqrt(Plab[0]*Plab[0]+fProtonMass*fProtonMass);
      Double_t Kappa=(E_beam+fProtonMass)/(E_beam-fProtonMass);
      Double_t sin_alpha=TMath::Sin(alpha[0]/180*TMath::Pi());
      Double_t T=2*fProtonMass*sin_alpha*sin_alpha/(Kappa-sin_alpha*sin_alpha);

      Double_t px_abs=TMath::Sqrt(T*T+2*fProtonMass*T)*TMath::Cos(alpha[0]/180*TMath::Pi());
      Double_t pz_abs=Plab[0] - TMath::Sqrt(T*T+2*fProtonMass*T)*TMath::Sin(alpha[0]/180*TMath::Pi());

      Double_t tan_theta=px_abs/pz_abs;

      return TMath::ATan(tan_theta)/TMath::Pi()*180;
    };

  TF1 *f=new TF1("f1", GetThetaByAlpha_Imp, 0,90,1);
  f->SetParameter(0,fMom);
  Double_t alpha=f->GetX(theta);

  delete f;
  return alpha;
}

Double_t KoaElasticCalculator::GetRecZByTheta(Double_t theta)
{
  Double_t alpha = GetAlphaByTheta(theta);
  return 10*fRecDistance*TMath::Tan(alpha/180*TMath::Pi());
}

Double_t KoaElasticCalculator::GetRecZByFwdX(Double_t xposition)
{
  Double_t theta = 180*TMath::ATan(xposition/fFwdDistance)/TMath::Pi();
  return GetRecZByTheta(theta);
}

Double_t KoaElasticCalculator::GetAlphaByEnergy(Double_t T)
{
  auto GetRecTByAlpha_Imp = [] (Double_t* alpha, Double_t* Plab)
    {
      Double_t E_beam=TMath::Sqrt(Plab[0]*Plab[0]+fProtonMass*fProtonMass);
      Double_t Kappa=(E_beam+fProtonMass)/(E_beam-fProtonMass);
      Double_t sin_alpha=TMath::Sin(alpha[0]/180*TMath::Pi());
      Double_t Energy=2*fProtonMass*sin_alpha*sin_alpha/(Kappa-sin_alpha*sin_alpha);
      return Energy*1000;
    };

  TF1* f1 = new TF1("f1", GetRecTByAlpha_Imp, 0,90,1);
  f1->SetParameter(0, fMom);
  Double_t alpha = f1->GetX(T);
  delete f1;
  return alpha;
}

Double_t KoaElasticCalculator::GetRecZByEnergy(Double_t T)
{
  Double_t alpha = GetAlphaByEnergy(T);
  return 10*fRecDistance*TMath::Tan(alpha/180*TMath::Pi());
}

Double_t KoaElasticCalculator::GetFwdXByEnergy(Double_t T)
{
  Double_t alpha = GetAlphaByEnergy(T);
  Double_t theta = GetThetaByAlpha(alpha);
  return fFwdDistance*TMath::Tan(theta/180*TMath::Pi());
}

Double_t KoaElasticCalculator::GetFwdTOFByAlpha(Double_t alpha)
{
  Double_t T = GetEnergyByAlpha(alpha)/1000.; //in GeV

  Double_t pz_abs = fMom - TMath::Sqrt(T*T+2*fProtonMass*T)*TMath::Sin(alpha/180*TMath::Pi());
  Double_t beta_fwd = pz_abs/fMom; //

  double l_unit = 0.01*6.58/1.97; // cm in ns
  double tof = fFwdDistance*l_unit/beta_fwd;
  

  return tof;
}

Double_t KoaElasticCalculator::GetRecTOFByAlpha(Double_t alpha)
{
  Double_t T = GetEnergyByAlpha(alpha)/1000.; //in GeV

  double l_unit = 0.01*6.58/1.97; // cm in ns

  Double_t px_abs = TMath::Sqrt(T*T+2*fProtonMass*T)*TMath::Cos(alpha/180*TMath::Pi());
  double beta_rec = px_abs/(T+fProtonMass);

  // double tof = fRecDistance*l_unit*TMath::Sqrt(fProtonMass/2./T);
  double tof = fRecDistance*l_unit/beta_rec;
  return tof;
}

Double_t KoaElasticCalculator::operator() (Double_t* x, Double_t* p)
{
  Double_t alpha = TMath::ATan(x[0]/p[1]/10.);
  Double_t sin_alpha = TMath::Sin(alpha);

  PxPyPzMVector beam(0,0,p[0],fProtonMass);
  Double_t kappa = (beam.energy()+beam.mass())/(beam.energy()-beam.mass());

  return 1000*2*fProtonMass*sin_alpha*sin_alpha/(kappa - sin_alpha*sin_alpha);
}
