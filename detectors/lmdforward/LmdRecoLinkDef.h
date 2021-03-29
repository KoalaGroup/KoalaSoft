// $Id: LmdLinkDef.h,v 1.0 M. Michel $

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;


//data

//reco
//#pragma link C++ class PndLmdIdealRecoTask+;
//#pragma link C++ class PndLmdIdealClusterTask+;
#pragma link C++ class PndLmdStripClusterTask+;
#pragma link C++ class PndLmdPixelClusterTask+;
#pragma link C++ class KoaPixelClusterTask+;
#pragma link C++ class PndLmdHitMergeTask+;
#pragma link C++ class KoaHitMergeTask+;
#pragma link C++ class PndSdsMergedHit+;
#pragma link C++ class PndSdsCell+;
#endif

