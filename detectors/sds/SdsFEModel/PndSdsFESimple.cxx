/*
 * SdsFE.cpp
 *
 *  Created on: Apr 4, 2011
 *      Author: esch
 */

#include "PndSdsFESimple.h"
#include <vector>
#include "Math/Interpolator.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"

PndSdsFESimple::PndSdsFESimple() {
	fFrontEndModel = new PndSdsFEAmpModelSimple();
	fFunctionRange = 22000;
	fFunction = new TF1("fFunction",fFrontEndModel,&PndSdsFEAmpModelSimple::Definition,0,fFunctionRange,3);
	fFunction->SetNpx(20000);

	fFunction->SetParName(0,"chargetime");
	fFunction->SetParName(1,"constantcurrent");
	fFunction->SetParName(2,"charge");

	fFunction->SetParameter("chargetime",100);
	fFunction->SetParameter("constcurrent",60);

	fTimeStep = 1. / 150 * 1000.; // Dont forget to change the frequency here if you change it above
	fThreshold = 1000;

	GetInterpolatorList();

}

PndSdsFESimple::PndSdsFESimple(double chargetime, double constcurrent, double threshold, double frequency) {
	fFrontEndModel = new PndSdsFEAmpModelSimple();
	fFunctionRange = 22000;
	fFunction = new TF1("fFunction",fFrontEndModel,&PndSdsFEAmpModelSimple::Definition,0,fFunctionRange,3);
	fFunction->SetNpx(20000);

	fFunction->SetParName(0,"chargetime");
	fFunction->SetParName(1,"constantcurrent");
	fFunction->SetParName(2,"charge");

	fFunction->SetParameter(0,chargetime);
	fFunction->SetParameter(1,constcurrent);

	fTimeStep = 1. / frequency * 1000.;
	fThreshold = threshold;

	GetInterpolatorList();

}

void PndSdsFESimple::SetParameter(double chargingtime, double constcurrent, double threshold, double frequency)
{
  if(fFunction)
  {
    fFunction->SetParameter(0,chargingtime);
    fFunction->SetParameter(1,constcurrent);
  }
  fThreshold = threshold;
  fTimeStep = 1. / frequency * 1000.;
  return;
}

PndSdsFESimple::~PndSdsFESimple() {
}
ClassImp(PndSdsFESimple);


