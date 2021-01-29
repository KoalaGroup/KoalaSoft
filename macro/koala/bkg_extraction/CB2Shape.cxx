/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 * @(#)root/roofit:$Id$
 * Authors:                                                                  *
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu       *
 *   DK, David Kirkby,    UC Irvine,         dkirkby@uci.edu                 *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/

/** \class CB2Shape
    \ingroup Roofit

PDF implementing the Crystal Ball line shape.
**/

#include "CB2Shape.h"

#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooMath.h"
// #include "BatchHelpers.h"
// #include "RooVDTHeaders.h"

#include "TMath.h"

#include <cmath>

using namespace std;

ClassImp(CB2Shape);

////////////////////////////////////////////////////////////////////////////////

CB2Shape::CB2Shape(const char *name, const char *title,
                   RooAbsReal& _m, RooAbsReal& _m0, RooAbsReal& _sigma,
                   RooAbsReal& _alpha_leading, RooAbsReal& _n_leading,
                   RooAbsReal& _alpha_trailing, RooAbsReal& _n_trailing) :
  RooAbsPdf(name, title),
  m("m", "Dependent", this, _m),
  m0("m0", "M0", this, _m0),
  sigma("sigma", "Sigma", this, _sigma),
  alpha_leading("alpha_leading", "Alpha (Leading)", this, _alpha_leading),
  n_leading("n_leading", "Order (Leading)", this, _n_leading),
  alpha_trailing("alpha_trailing", "Alpha (Trailing)", this, _alpha_trailing),
  n_trailing("n_trailing", "Order (Trailing)", this, _n_trailing)
{
  if( alpha_leading < 0 || alpha_trailing < 0)
    throw std::logic_error("alpha_leading and alpha_tailing should > 0");
}

////////////////////////////////////////////////////////////////////////////////

CB2Shape::CB2Shape(const CB2Shape& other, const char* name) :
  RooAbsPdf(other, name),
  m("m", this, other.m),
  m0("m0", this, other.m0),
  sigma("sigma", this, other.sigma),
  alpha_leading("alpha_leading", this, other.alpha_leading),
  n_leading("n_leading", this, other.n_leading),
  alpha_trailing("alpha_trailing", this, other.alpha_trailing),
  n_trailing("n_trailing", this, other.n_trailing)
{
}

////////////////////////////////////////////////////////////////////////////////

Double_t CB2Shape::evaluate() const {
  Double_t t = (m-m0)/sigma;

  Double_t alpha_ld = (Double_t)alpha_leading;
  Double_t alpha_tl = (Double_t)alpha_trailing;

  if( t < -alpha_ld ) {
    Double_t a =  TMath::Power(n_leading/alpha_ld,n_leading)*exp(-0.5*alpha_ld*alpha_ld);
    Double_t b = n_leading/alpha_ld - alpha_ld;

    return a/TMath::Power(b - t, n_leading);
  }
  else if ( t > alpha_tl ) {
    Double_t a =  TMath::Power(n_trailing/alpha_tl,n_trailing)*exp(-0.5*alpha_tl*alpha_tl);
    Double_t b = n_trailing/alpha_tl - alpha_tl;

    return a/TMath::Power(b + t, n_trailing);
  }
  else {
    return exp(-0.5*t*t);
  }
}

////////////////////////////////////////////////////////////////////////////////

// namespace CBShapeBatchEvaluate {
// //Author: Emmanouil Michalainas, CERN 21 August 2019

// template<class Tm, class Tm0, class Tsigma, class Talpha, class Tn>
// void compute(	size_t batchSize,
// 	double * __restrict output,
// 	Tm M, Tm0 M0, Tsigma S, Talpha A, Tn N)
// {
//   for (size_t i=0; i<batchSize; i++) {
//     const double t = (M[i]-M0[i]) / S[i];
//     if ((A[i]>0 && t>=-A[i])   ||   (A[i]<0 && -t>=A[i])) {
//       output[i] = -0.5*t*t;
//     } else {
//       output[i] = N[i] / (N[i] -A[i]*A[i] -A[i]*t);
//       output[i] = _rf_fast_log(output[i]);
//       output[i] *= N[i];
//       output[i] -= 0.5*A[i]*A[i];
//     }
//   }
  
//   for (size_t i=0; i<batchSize; i++) {
//     output[i] = _rf_fast_exp(output[i]);
//   }
// }
// };

// RooSpan<double> CB2Shape::evaluateBatch(std::size_t begin, std::size_t batchSize) const {
//   using namespace BatchHelpers;
//   using namespace CBShapeBatchEvaluate;

//   EvaluateInfo info = getInfo( {&m, &m0, &sigma, &alpha_leading, &n_leading}, begin, batchSize );
//   auto output = _batchData.makeWritableBatchUnInit(begin, batchSize);

//   auto mData = m.getValBatch(begin, info.size);
//   if (info.nBatches == 0) {
//     throw std::logic_error("Requested a batch computation, but no batch data available.");
//   }
//   else if (info.nBatches==1 && !mData.empty()) {
//     compute(info.size, output.data(), mData.data(),
//     BracketAdapter<double> (m0),
//     BracketAdapter<double> (sigma),
//     BracketAdapter<double> (alpha_leading),
//     BracketAdapter<double> (n_leading));
//   }
//   else {
//     compute(info.size, output.data(),
//     BracketAdapterWithMask (m,m.getValBatch(begin,batchSize)),
//     BracketAdapterWithMask (m0,m0.getValBatch(begin,batchSize)),
//     BracketAdapterWithMask (sigma,sigma.getValBatch(begin,batchSize)),
//     BracketAdapterWithMask (alpha_leading,alpha_leading.getValBatch(begin,batchSize)),
//     BracketAdapterWithMask (n_leading,n_leading.getValBatch(begin,batchSize)));
//   }
//   return output;
// }

////////////////////////////////////////////////////////////////////////////////

Int_t CB2Shape::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const
{
  if( matchArgs(allVars,analVars,m) )
    return 1 ;

  return 0;
}

////////////////////////////////////////////////////////////////////////////////

Double_t CB2Shape::analyticalIntegral(Int_t code, const char* rangeName) const
{
  static const double sqrtPiOver2 = 1.2533141373;
  static const double sqrt2 = 1.4142135624;

  R__ASSERT(code==1);

  double result = 0.0;
  bool useLog_ld = false;
  bool useLog_tl = false;

  if( fabs(n_leading-1.0) < 1.0e-05 )
    useLog_ld = true;
  if( fabs(n_trailing-1.0) < 1.0e-05 )
    useLog_tl = true;

  double sig = fabs((Double_t)sigma);
  Double_t alpha_ld = (Double_t)alpha_leading;
  Double_t alpha_tl = (Double_t)alpha_trailing;

  double tmin = (m.min(rangeName)-m0)/sig;
  double tmax = (m.max(rangeName)-m0)/sig;

  // integral lambdas
  auto integral_ld = [&] (double min, double max) {
                       double a = TMath::Power(n_leading/alpha_ld,n_leading)*exp(-0.5*alpha_ld*alpha_ld);
                       double b = n_leading/alpha_ld - alpha_ld;

                       if(useLog_ld) {
                         result += a*sig*( log(b-min) - log(b-max) );
                       }
                       else {
                         result += a*sig/(1.0-n_leading)*(1.0/(TMath::Power(b-min,n_leading-1.0))
                                                          - 1.0/(TMath::Power(b-max,n_leading-1.0)));
                       }
                     };

  auto integral_tl = [&] (double min, double max) {
                       double tmp = -min;
                       min = -max;
                       max = tmp;

                       double a = TMath::Power(n_trailing/alpha_tl,n_trailing)*exp(-0.5*alpha_tl*alpha_tl);
                       double b = n_trailing/alpha_tl - alpha_tl;

                       if(useLog_tl) {
                         result += a*sig*( log(b-min) - log(b-max) );
                       }
                       else {
                         result += a*sig/(1.0-n_trailing)*(1.0/(TMath::Power(b-min,n_trailing-1.0))
                                                          - 1.0/(TMath::Power(b-max,n_trailing-1.0)));
                       }
                     };

  auto integral_md = [&] (double min, double max) {
                       result += sig*sqrtPiOver2*( ApproxErf(max/sqrt2)
                                                   - ApproxErf(min/sqrt2) );
                     };

  // 
  if( tmax < -alpha_ld ) {
    integral_ld(tmin, tmax);
  }
  else if ( tmax <= alpha_tl ) {
    if( tmin < -alpha_ld ) {
      integral_ld(tmin, -alpha_ld);
      integral_md(-alpha_ld, tmax);
    }
    else {
      integral_md(tmin, tmax);
    }
  }
  else {
    if( tmin < -alpha_ld ){
      integral_ld(tmin, -alpha_ld);
      integral_md(-alpha_ld, alpha_tl);
      integral_tl(alpha_tl, tmax);
    }
    else if ( tmin <= alpha_tl ) {
      integral_md(tmin, alpha_tl);
      integral_tl(alpha_tl, tmax);
    }
    else {
      integral_tl(tmin, tmax);
    }
  }

  return result != 0. ? result : 1.E-300;
}

////////////////////////////////////////////////////////////////////////////////
/// Advertise that we know the maximum of self for given (m0,alpha_leading,n_leading,sigma)

Int_t CB2Shape::getMaxVal(const RooArgSet& vars) const
{
  RooArgSet dummy ;

  if (matchArgs(vars,dummy,m)) {
    return 1 ;
  }
  return 0 ;
}

////////////////////////////////////////////////////////////////////////////////

Double_t CB2Shape::maxVal(Int_t code) const
{
  R__ASSERT(code==1) ;

  // The maximum value for given (m0,alpha_leading,n_leading,sigma)
  return 1.0 ;
}

////////////////////////////////////////////////////////////////////////////////

Double_t CB2Shape::ApproxErf(Double_t arg) const
{
  static const double erflim = 5.0;
  if( arg > erflim )
    return 1.0;
  if( arg < -erflim )
    return -1.0;

  return RooMath::erf(arg);
}
