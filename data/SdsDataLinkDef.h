// $Id: ZdcLinkDef+;,v 1.1.1.1
//2005/06/23 07:14:26 dbertini Exp $

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

// #pragma link C++ class PndPersistencyTask + ;

//#pragma link C++ class  PndSdsApvHit+;
#pragma link C++ class PndSdsMCPoint + ;
#pragma link C++ class PndSdsDigi + ;
#pragma link C++ class PndSdsDigiPixel + ;
#pragma link C++ class PndSdsDigiStrip + ;
#pragma link C++ class PndSdsCluster + ;
#pragma link C++ class PndSdsClusterPixel + ;
#pragma link C++ class PndSdsClusterStrip + ;
#pragma link C++ class PndSdsHit + ;
//#pragma link C++ class  PndSdsHitInfo+;
#pragma link C++ class PndSdsPidCand + ;
#pragma link C++ class PndSdsPixel + ;
#pragma link C++ class PndSdsRadDamHit + ;
#pragma link C++ class PndSdsDigiPixelMCInfo + ;

#pragma link C++ class PndTrack + ;
#pragma link C++ class PndTrackCand + ;
#pragma link C++ class PndTrackCandHit + ;

#pragma link C++ class PndRecoCandidate;
#pragma link C++ function operator<< (ostream &, const PndRecoCandidate &);

#endif
