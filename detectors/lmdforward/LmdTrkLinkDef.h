// $Id: LmdTrkLinkDef.h,v 1.0 M. Michel$

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;


//tracking
//#pragma link C++ class PndLmdMCPointTrackFinderTask+;
#pragma link C++ class PndLmdTrackFinderTask+;
#pragma link C++ class KoaTrackFinderTask+;
#pragma link C++ class PndLmdTrackFinderCATask+;
#pragma link C++ class PndLmdLinFitTask+;
#pragma link C++ class KoaLinFitTask+;
#pragma link C++ class PndLmdLineTask+;
#pragma link C++ class PndLmdIdealFitTask+;
#pragma link C++ class PndLinTrack+;
#pragma link C++ class KoaLinTrack+;
//#pragma link C++ class PndLmdMCPointLinFitTask+;
//#pragma link C++ class PndLmdTrackCandToGFTrackCandConvertorTask+;
#pragma link C++ class PndLmdGeaneTask+;
#pragma link C++ class KoaGeaneTask+;
#pragma link C++ class KoaBackProp+;
#pragma link C++ class KoaComp+;
#pragma link C++ class KoaPloti+;
#pragma link C++ class KoaEffi+;
#pragma link C++ class MomentumVi+;
#pragma link C++ class LmdEffi+;
#pragma link C++ class KoaIPvis+;
#pragma link C++ class PndLmdSigCleanTask+;
#pragma link C++ class PndLmdBPtestTask+;
//PndLmdKalmanTask and PndLmdBPRungeKuttaTask have dependences from genfit -> switched off until movement to gentfit2
//#pragma link C++ class PndLmdKalmanTask+;
//#pragma link C++ class PndLmdBPRungeKuttaTask+;
#pragma link C++ class PndLmdTrksFilterTask+;
#pragma link C++ class KoaTrksFilterTask+;
#pragma link C++ class PndLmdNoiseTrkSuppressionTask+;

#endif

