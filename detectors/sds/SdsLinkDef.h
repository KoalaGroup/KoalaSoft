// $Id: SdsLinkDef.h,v 1.0 Ralf Kliemt 08.Jan.2007 $

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

//data
//#pragma link C++ class PndSdsDigi+;
//#pragma link C++ class PndSdsDigiPixel+;
//#pragma link C++ class PndSdsPixel+;
//#pragma link C++ class PndSdsStrip+;
//#pragma link C++ class PndSdsMCPoint+;
//#pragma link C++ class PndMvdApvHit+;

#pragma link C++ class PndSdsTask + ;
#pragma link C++ class PndPersistencyTask + ;
//mc
#pragma link C++ class PndSdsGeo + ;
#pragma link C++ class PndSdsGeoPar + ;
//#pragma link C++ class PndSdsContFact+;
#pragma link C++ class PndSdsDetector + ;
//#pragma link C++ class PndMvdMaterialDet+;

//digi
#pragma link C++ class PndSdsHybridHitProducer + ;
//#pragma link C++ class PndSdsStripHitProducer+;
//#pragma link C++ class PndSdsStripHitProducerDif+;
#pragma link C++ class PndSdsCalcPixel;
#pragma link C++ class PndSdsCalcPixelDif;
#pragma link C++ class PndSdsCalcFePixel + ;
#pragma link C++ class PndSdsCalcStrip;
//#pragma link C++ class PndSdsCalcStripDif;
//#pragma link C++ class PndSdsDigiTask+;
#pragma link C++ class PndSdsPixelDigiPar + ;
//#pragma link C++ class PndSdsStripDigiPar+;
#pragma link C++ class PndSdsTotDigiPar + ;
//#pragma link C++ class PndMvdDigiAna+;
#pragma link C++ class PndSdsHitProducerIdeal + ;
#pragma link C++ class PndSdsNoiseProducer + ;

#pragma link C++ class PndSdsDigiPixelWriteoutBuffer + ;

#pragma link C++ class PndSdsDigiPixelSorterTask;
#pragma link C++ class PndSdsDigiPixelRingSorter + ;

#pragma link C++ class PndSdsChargeConversion + ;
#pragma link C++ class PndSdsIdealChargeConversion + ;
#pragma link C++ class PndSdsTotChargeConversion + ;
#pragma link C++ class PndSdsTotDigiPar + ;
#pragma link C++ class PndSdsAdcChargeConversion + ;
#pragma link C++ class PndSdsFE + ;
#pragma link C++ class PndSdsFESimple + ;

//#pragma link C++ class PndMvdCalcFePixel+;

#endif
