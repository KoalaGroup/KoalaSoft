//-----------------------------------------------------------
// File and Version Information:
// $Id$
//
// Description:
//      Implementation of class PndLmdKalmanTask
//      see PndLmdKalmanTask.h for details
//
// Environment:
//      Software developed for the PANDA Detector at FAIR.
//
// Author List:
//      Sebastian Neubert    TUM            (original author)
//      Ralf Kliemt, TU Dresden             (Copied for MVD use)
//      Anastasia Karavdina, Uni Mainz      (Copied for LMD use)
//-----------------------------------------------------------

// Panda Headers ----------------------

// This Class' Header ------------------
#include "PndLmdKalmanTask.h"

// C/C++ Headers ----------------------
#include <assert.h>
#include <algorithm>
#include <iostream>

// Collaborating Class Headers --------
#include "FairRootManager.h"
#include "GFTrack.h"
#include "TClonesArray.h"
#include "TDatabasePDG.h"

#include "FairMCPoint.h"
#include "PndSdsHit.h"

#include "FairBaseParSet.h"
#include "FairTrackParH.h"
#include "GFDetPlane.h"
#include "GFException.h"
#include "GFKalman.h"
#include "GFRecoHitFactory.h"
#include "LSLTrackRep.h"
#include "PndGeoHandling.h"
#include "PndSdsRecoHit.h"
#include "TFile.h"
#include "TGeoManager.h"
#include "TGeoTrack.h"
#include "TH1D.h"
#include "TLorentzVector.h"
//#include "GeaneTrackRep2.h"
#include "FairGeanePro.h"
#include "GFAbsTrackRep.h"
#include "GFConstField.h"
#include "GeaneTrackRep.h"
#include "PndDetectorList.h"
//#include "PndSdsRecoHit.h"
#include "PndGenfitAdapters.h"
#include "PndTrack.h"
#include "PndTrackCand.h"
#include "RKTrackRep.h"
#include "TMatrixFSym.h"
//#include "GFPandaField.h"
#include "PndGenfitField.h"
// Class Member definitions -----------

PndLmdKalmanTask::PndLmdKalmanTask()
    : FairTask("Kalman Filter"), fPersistence(kFALSE) {
  //  fTrackBranchName = "GFTrackCandLmd";
  fTrackBranchName = "LMDTrackCand";
  //  fSdsHitBranchName = "LMDHitsStrip";
  fSdsHitBranchName = "LMDHitsPixel";
  PndGeoHandling::Instance();
  // hxpull = new TH1D("hxpull","x/#sigma_{x}",1e2,-10,10.);
  // hypull = new TH1D("hypull","y/#sigma_{y}",1e2,-10,10.);
  // hzpull = new TH1D("hzpull","z/#sigma_{z}",1e2,-10,10.);
  // hpxpull = new TH1D("hpxpull","px/#sigma_{px}",1e2,-10,10.);
  // hpypull = new TH1D("hpypull","x/#sigma_{py}",1e2,-10,10.);
  // hpzpull = new TH1D("hpzpull","pz/#sigma_{pz}",1e2,-10,10.);
  flGEANE = false;
  flRK = false;
  fscaleP = 1;
  fscaleM = 1;
  // rep = NULL;
}

PndLmdKalmanTask::PndLmdKalmanTask(TString HitBranch, TString TrackBranch)
    : FairTask("Kalman Filter"), fPersistence(kFALSE) {
  fTrackBranchName = TrackBranch;
  fSdsHitBranchName = HitBranch;
  PndGeoHandling::Instance();
  flGEANE = false;
  flRK = false;
  fscaleP = 1;
  fscaleM = 1;
  // rep = NULL;
}

PndLmdKalmanTask::~PndLmdKalmanTask() {
  // if(fPH!=NULL)delete fPH;
  // if(fChi2H!=NULL)delete fChi2H;
  //  delete rep;
}

InitStatus PndLmdKalmanTask::Init() {
  fTrackcount = 0;
  fsensType = 0;
  // Get ROOT Manager
  FairRootManager* ioman = FairRootManager::Instance();

  if (ioman == 0) {
    Error("PndLmdKalmanTask::Init", "RootManager not instantiated!");
    return kERROR;
  }

  // Get input collection
  fTrackArray = (TClonesArray*)ioman->GetObject(fTrackBranchName);

  if (fTrackArray == 0) {
    Error("PndLmdKalmanTask::Init", "GFTrackCandLmd array not found!");
    return kERROR;
  }

  fSdsHitsArray = (TClonesArray*)ioman->GetObject(fSdsHitBranchName);

  // Set output collection
  // fTrackTmpArray = new TClonesArray("PndLinTrack");
  // ioman->Register("LMDTrack", "PndLmd", fTrackTmpArray, kTRUE);
  fTrackTmpArray = new TClonesArray("PndTrack");
  fTrkOutArray = new TClonesArray("PndTrack");
  ioman->Register("LMDPndTrackFilt", "PndLmd", fTrkOutArray, kTRUE);

  // Build hit factory -----------------------------
  fTheRecoHitFactory = new GFRecoHitFactory();

  TClonesArray* stripar = (TClonesArray*)ioman->GetObject(fSdsHitBranchName);
  if (stripar == 0) {  // TODO Convention on detector number needed
    Error("PndLmdKalmanTask::Init", "LMDHitsPixel array not found");
  } else {
    int detID = ioman->GetBranchId(fSdsHitBranchName);
    std::cout << "detID = " << detID << std::endl;
    //    fTheRecoHitFactory->addProducer(ioman->GetBranchId(fSdsHitBranchName),new
    //    GFRecoHitProducer<PndSdsHit,PndSdsRecoHit>(stripar));
    fTheRecoHitFactory->addProducer(
        1, new GFRecoHitProducer<PndSdsHit, PndSdsRecoHit>(stripar));
    std::cout << "*** PndLmdKalmanTask::Init"
              << "\t"
              << "fSdsHitBranchName array found" << std::endl;
  }

  // read beam momentum from base
  FairRun* fRun = FairRun::Instance();
  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
  FairBaseParSet* par =
      (FairBaseParSet*)(rtdb->findContainer("FairBaseParSet"));
  fPbeam = par->GetBeamMom();
  // fPbeam -=8.77e-5;//TEST!!! energy loss for 11.91 GeV/c
  // fPbeam -=1e-4;//TEST!!! energy loss for 1.5 GeV/c
  std::cout << "Beam Momentum for this run is " << fPbeam << std::endl;
  fPDGCode = -2212;  // barp
  fCharge = -1;      // barp

  fGeoH = PndGeoHandling::Instance();
  fPro = new FairGeanePro();
  if (flRK) {
    std::cout << "RKTrackRep will be used for track representation"
              << std::endl;
    //  GFFieldManager::getInstance()->init(new GFPandaField());
    GFFieldManager::getInstance()->init(new PndGenfitField());
  }
  if (flGEANE) {
    std::cout << "GeaneTrackRep will be used for track representation"
              << std::endl;
    fPro = new FairGeanePro();
  }

  // //for test purpose
  // fMCHits = (TClonesArray*) ioman->GetObject("LMDPoint");
  // if ( !fMCHits)	{
  //   std::cout << "-W- PndLmdGeaneTask::Init: "<< "No LMDPoint"<<" array!" <<
  //   std::endl;
  //   return kERROR;
  // }

  return kSUCCESS;
}

void PndLmdKalmanTask::Exec(Option_t*) {
  fTrackTmpArray->Delete();
  fTrkOutArray->Delete();
  if (fVerbose > 1)
    std::cout
        << "((((((((((((((((((((( PndLmdKalmanTask::Exec )))))))))))))))))))))"
        << std::endl;
  Int_t counterGeaneTrk = 0;
  Int_t rec_tkr_count = 0;
  Int_t ntracks = fTrackArray->GetEntriesFast();

  // Detailed output
  if (fVerbose > 1)
    std::cout << " -I- PndLmdKalmanTask: contains " << ntracks << " Tracks."
              << std::endl;
  GFKalman fitter;
  int numIttr = 1;
  fitter.setNumIterations(numIttr);
  for (Int_t itr = 0; itr < ntracks; ++itr) {
    if (fVerbose > 1) std::cout << "starting track" << itr << std::endl;

    PndTrackCand* trackCand = (PndTrackCand*)fTrackArray->At(itr);
    const int Ntrkcandhits = trackCand->GetNHits();
    // Read info about 1st plane(sensor)
    PndTrackCandHit theHit = trackCand->GetSortedHit(0);  // get 1st hit
    Int_t hitID = theHit.GetHitId();
    PndSdsHit* myHit = (PndSdsHit*)(fSdsHitsArray->At(hitID));
    TMatrixD hitCov = myHit->GetCov();
    if (fVerbose > 1) std::cout << "hitCov:" << std::endl;
    if (fVerbose > 1) hitCov.Print();
    Int_t id = myHit->GetSensorID();
    TString path = fGeoH->GetPath(id);
    TVector3 oo, uu, vv;
    fGeoH->GetOUVShortId(id, oo, uu, vv);
    if (fVerbose > 1) {
      std::cout << "oo:" << std::endl;
      oo.Print();
      std::cout << "uu:" << std::endl;
      uu.Print();
      std::cout << "vv:" << std::endl;
      vv.Print();
    }

    GFTrackCand* GFtrkCand = PndTrackCand2GenfitTrackCand(trackCand);
    TVector3 StartPos = GFtrkCand->getPosSeed();
    TVector3 StartDir = GFtrkCand->getDirSeed();
    // //shift start point out of plane on 300 mkm
    // double xShift = StartPos.X() - StartDir.X()*0.0300;
    // double yShift = StartPos.Y() - StartDir.Y()*0.0300;
    // double zShift = StartPos.Z() - StartDir.Z()*0.0300;
    // StartPos.SetXYZ(xShift,yShift,zShift);
    TVector3 StartMom = fPbeam * StartDir;
    TVector3 StartPosErr(sqrt(hitCov[0][0]), sqrt(hitCov[1][1]),
                         sqrt(hitCov[2][2]));
    TVector3 StartDirErr(
        0.1 * (sqrt(hitCov[0][0])), 0.1 * (sqrt(hitCov[1][1])),
        0.1 *
            sqrt(hitCov[2]
                       [2]));  // TODO: check this assumption (2*sigma_{x}/20cm)
    TVector3 StartMomErr = fPbeam * StartDirErr;
    // initial errors for Kalman must be large: this is usually done in order to
    // give a low weight to the prefit
    StartPosErr *= fscaleP;
    StartMomErr *= fscaleM;
    //     StartMomErr *=1;
    if (fVerbose > 2) {
      unsigned int detid = 12345, index = 12345;
      std::cout << "GFTrackCand no. " << itr << " has " << GFtrkCand->getNHits()
                << " hits." << std::endl;
      std::cout << "[ ihit | detid | index";
      for (unsigned int ihit = 0; ihit < GFtrkCand->getNHits(); ihit++) {
        GFtrkCand->getHit(ihit, detid,
                          index);  // detid and index are written here
        std::cout << " ]\n[ " << ihit << " | " << detid << " | " << index;
      }
      std::cout << " ]" << std::endl;
    }

    if (fVerbose > 1) {
      std::cout << "*** BEFORE ***" << std::endl;
      std::cout << "StartPos:" << std::endl;
      StartPos.Print();
      std::cout << "StartPosErr:" << std::endl;
      StartPosErr.Print();
      std::cout << "StartMom:" << std::endl;
      StartMom.Print();
      std::cout << "StartMomErr:" << std::endl;
      StartMomErr.Print();
    }

    GFAbsTrackRep* rep;
    // // /// The Runge Kutta trk rep ---------------
    if (flRK) {
      if (fVerbose > 1)
        std::cout << "RKTrackRep will be used for track representation"
                  << std::endl;
      rep = new RKTrackRep(StartPos, StartMom, StartPosErr, StartMomErr,
                           fPDGCode);
    }
    // // /// The Runge Kutta trk rep (END) ---------

    //  /// LinTrk rep ------------------
    // // TVector3 StartPos = GFtrkCand->getPosSeed();
    // // TVector3 StartDir = GFtrkCand->getDirSeed();
    // //     TVector3 StartMom  = fPbeam*StartDir;
    //    LSLTrackRep* rep = new
    //    LSLTrackRep(StartPos.Z(),StartPos.X(),StartPos.Y(),StartDir.X(),StartDir.Y(),1/fPbeam,
    // 				       StartPosErr.X(),StartPosErr.Y(),StartDirErr.X(),StartDirErr.Y(),
    // 				       1e-23,magFieldConst);
    //    //TODO: double siginvp = 1/1e-4 is it correct???

    //    /// LinTrk rep (END) ------------------

    /// GEANE track rep --------------------
    if (flGEANE) {
      GFDetPlane start_pl(StartPos, uu, vv);  //
      rep = new GeaneTrackRep(fPro, start_pl, StartMom, StartPosErr,
                              StartMomErr, fCharge, fPDGCode);
    }
    /// GEANE track rep (END) --------------------

    GFTrack* trk = new GFTrack(rep);
    trk->setCandidate(*GFtrkCand);

    // Load RecoHits
    try {
      trk->addHitVector(fTheRecoHitFactory->createMany(trk->getCand()));
      if (fVerbose > 1) {
        std::cout << trk->getNumHits() << " hits in track " << itr << std::endl;
      }
    } catch (GFException& e) {
      std::cout << " *** PndLmdKalmanTask::Exec "
                << "\t"
                << "Genfit Exception: trk->addHitVector " << e.what()
                << std::endl;
      throw e;
    }

    // Start Fitter
    try {
      if (fVerbose > 1) {
        std::cout << " ... GFtrk BEFORE ..." << std::endl;
        trk->Print();
      }
      fitter.processTrack(trk);
      if (fVerbose > 1) {
        std::cout << " ... GFtrk AFTER ..." << std::endl;
        trk->Print();
      }
    } catch (GFException e) {
      std::cout << "*** FITTER EXCEPTION ***" << std::endl;
      std::cout << e.what() << std::endl;
    }
    if (fVerbose > 1) std::cout << "successful FIT!" << std::endl;

    // --- Get trk in  PndTrack format ---
    PndTrack* trkPnd = GenfitTrack2PndTrack(trk);
    if (fVerbose > 1) {
      std::cout << "trkPnd AFTER GenFit " << std::endl;
      trkPnd->Print();
      std::cout << "Number of hits in trk-cand: " << trackCand->GetNHits()
                << std::endl;
    }
    trkPnd->SetTrackCand(*trackCand);
    trkPnd->SetRefIndex(
        itr);  // TODO: check is it correct set RefIn like ID of trk-cand???
    trkPnd->SetChi2(trk->getChiSqu());
    // --- Save as PndTrack---
    TClonesArray& clref = *fTrackTmpArray;
    Int_t size = clref.GetEntriesFast();
    PndTrack* trackfit = new (clref[size]) PndTrack(*trkPnd);

    delete trkPnd;
    delete GFtrkCand;
    delete trk;
    //  delete rep;
  }

  // //filter trks based on chi2 and hit comparision --------------
  // const unsigned int gll = fTrackTmpArray->GetEntriesFast();
  // int rec_trk=0;
  // if(flagFilter){
  //   //    fTrkOutArray->Delete();
  //     if(fVerbose>4)
  // 	cout<<"trk filter switched on!"<<endl;
  //   //go through all tracks
  //   vector<int> trksH0(gll);//hits on pl#0
  //   vector<int> trksH1(gll);//hits on pl#1
  //   vector<int> trksH2(gll);//hits on pl#2
  //   vector<int> trksH3(gll);//hits on pl#3
  //   vector<unsigned int> trkHn;//number of hits in trk
  //   vector<bool> trk_accept;
  //   vector<double> vchi2;
  //   for (unsigned int i = 0; i<gll;i++){
  //     trksH0[i]=-1;
  //     trksH1[i]=-1;
  //     trksH2[i]=-1;
  //     trksH3[i]=-1;
  //   }
  //   //fill vectors with trks hits
  //   for (unsigned int i = 0; i<gll;i++){
  //     PndTrack* trkpnd = (PndTrack*)(fTrackTmpArray->At(i));
  //     double chi2 = trkpnd->GetChi2();
  //     vchi2.push_back(chi2);
  //     trk_accept.push_back(true);
  //     int candID = trkpnd->GetRefIndex();
  //     PndTrackCand *trkcand = (PndTrackCand*)fTrackArray->At(candID);
  //     const unsigned int Ntrkcandhits= trkcand->GetNHits();
  //     trkHn.push_back(Ntrkcandhits);
  //     for (Int_t iHit = 0; iHit < Ntrkcandhits; iHit++){ // loop over
  //     rec.hits
  // 	PndTrackCandHit candhit =
  // (PndTrackCandHit)(trkcand->GetSortedHit(iHit));
  //     Int_t hitID = candhit.GetHitId();
  //     PndSdsHit* myHit = (PndSdsHit*)(fSdsHitsArray->At(hitID));
  //     Int_t sensid = myHit->GetSensorID();
  //     int ihalf,iplane,imodule,iside,idie,isensor;
  //     lmddim->Get_sensor_by_id(sensid,ihalf,iplane,imodule,iside,idie,isensor);
  //     if(fVerbose>4){
  // 	cout<<"trk# "<<i<<" plane#"<<iplane<<endl;
  //     }
  //     switch(iplane)
  // 	{
  // 	case 0:
  // 	  trksH0[i]=hitID;
  // 	case 1:
  // 	  trksH1[i]=hitID;
  // 	case 2:
  // 	  trksH2[i]=hitID;
  // 	case 3:
  // 	  trksH3[i]=hitID;
  // 	}
  //   }
  // }
  // //compare trks on hit level
  // for (unsigned int i = 0; i<gll;i++){
  //   for (unsigned int j = i+1; j<gll;j++){
  //   int coundduphit=4;//count dublicate hits
  //     if(trksH0[i]!=trksH0[j]) coundduphit--;
  //     if(trksH1[i]!=trksH1[j]) coundduphit--;
  //     if(trksH2[i]!=trksH2[j]) coundduphit--;
  //     if(trksH3[i]!=trksH3[j]) coundduphit--;
  //     if(fVerbose>4){
  // 	cout<<" trk#"<<i<<":"<<trksH0[i]<<" trk#"<<j<<":"<<trksH0[j]<<endl;
  // 	cout<<" trk#"<<i<<":"<<trksH1[i]<<" trk#"<<j<<":"<<trksH1[j]<<endl;
  // 	cout<<" trk#"<<i<<":"<<trksH2[i]<<" trk#"<<j<<":"<<trksH2[j]<<endl;
  // 	cout<<" trk#"<<i<<":"<<trksH3[i]<<" trk#"<<j<<":"<<trksH3[j]<<endl;
  // 	cout<<" dublicate: "<<coundduphit<<endl;
  // 	cout<<""<<endl;
  //     }
  //     if(coundduphit>2){// if 3 and more hits are similar
  // 	if(vchi2[i]>vchi2[j]){
  // 	  if(fVerbose>4){
  // 	    cout<<" trk#"<<i<<": has "<<trkHn[i]<<"hits;  trk#"<<j<<": has
  // "<<trkHn[j]<<" hits"<<endl;
  // 	    cout<<" trk#"<<i<<" has chi2="<<vchi2[i]<<" "<<" trk#"<<j<<" has
  // chi2="<<vchi2[j]<<endl;
  // 	  }
  // 	  trk_accept[i]=false;
  // 	  trk_accept[j]=true;
  // 	}
  // 	else{
  // 	  if(fVerbose>4){
  // 	    cout<<" trk#"<<i<<": has "<<trkHn[i]<<"hits;  trk#"<<j<<": has
  // "<<trkHn[j]<<" hits"<<endl;
  // 	    cout<<" trk#"<<i<<" has chi2="<<vchi2[i]<<" "<<" trk#"<<j<<" has
  // chi2="<<vchi2[j]<<endl;
  // 	  }
  // 	  trk_accept[i]=true;
  // 	  trk_accept[j]=false;
  // 	}
  //     }
  //   }
  // }
  // //save good trks
  // int rec_trk=0;
  // for (unsigned int i = 0; i<gll;i++){
  //   if(trk_accept[i]){
  //     PndTrack* trkpnd = (PndTrack*)(fTrackTmpArray->At(i));
  //     new((*fTrkOutArray)[rec_trk]) PndTrack(*(trkpnd)); //save Track
  //     rec_trk++;
  //   }
  // }
  // cout<<rec_trk<<" trks saved out of "<<gll<<endl;
  // }
  // else{
  //   if(fVerbose>4)
  //     cout<<"trk filter switched off!"<<endl;
  //   for (unsigned int i = 0; i<gll;i++){
  //     PndTrack* trkpnd = (PndTrack*)(fTrackTmpArray->At(i));
  //     new((*fTrkOutArray)[rec_trk]) PndTrack(*(trkpnd)); //save Track
  //     rec_trk++;
  //   }
  // }
  // //filter end ------------------------------------------------------------
  for (unsigned int i = 0; i < fTrackTmpArray->GetEntriesFast(); i++) {
    PndTrack* trkpnd = (PndTrack*)(fTrackTmpArray->At(i));
    TClonesArray& clref = *fTrkOutArray;
    Int_t size = clref.GetEntriesFast();
    new (clref[size]) PndTrack(*(trkpnd));  // save Track
  }
  if (fVerbose > 1)
    std::cout << "Fitting done, result is " << fTrkOutArray->GetEntriesFast()
              << " fitted trks" << std::endl;
  // rep = NULL;
  return;
}
ClassImp(PndLmdKalmanTask);
