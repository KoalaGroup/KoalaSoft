/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id: CB2Shape.h,v 1.11 2007/07/12 20:30:49 wouter Exp $
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
#ifndef CB2_SHAPE
#define CB2_SHAPE

#include "RooAbsPdf.h"
#include "RooRealProxy.h"

// class RooRealVar;

class CB2Shape : public RooAbsPdf {
public:
  CB2Shape() {} ;
  CB2Shape(const char *name, const char *title, RooAbsReal& _m,
           RooAbsReal& _m0, RooAbsReal& _sigma,
           RooAbsReal& _alpha_leading, RooAbsReal& _n_leading,
           RooAbsReal& _alpha_trailing, RooAbsReal& _n_tailing);

  CB2Shape(const CB2Shape& other, const char* name = 0);
  virtual TObject* clone(const char* newname) const { return new CB2Shape(*this,newname); }

  inline virtual ~CB2Shape() { }

  virtual Int_t getAnalyticalIntegral( RooArgSet& allVars,  RooArgSet& analVars, const char* rangeName=0 ) const;
  virtual Double_t analyticalIntegral( Int_t code, const char* rangeName=0 ) const;

  // Optimized accept/reject generator support
  virtual Int_t getMaxVal(const RooArgSet& vars) const ;
  virtual Double_t maxVal(Int_t code) const ;

protected:

  Double_t ApproxErf(Double_t arg) const ;

  RooRealProxy m;
  RooRealProxy m0;
  RooRealProxy sigma;
  RooRealProxy alpha_leading;
  RooRealProxy n_leading;
  RooRealProxy alpha_trailing;
  RooRealProxy n_trailing;

  Double_t evaluate() const;
  /* RooSpan<double> evaluateBatch(std::size_t begin, std::size_t batchSize) const; */

private:

  ClassDef(CB2Shape,1) // Crystal Ball lineshape PDF, with leading and trailing tail
};

#endif
