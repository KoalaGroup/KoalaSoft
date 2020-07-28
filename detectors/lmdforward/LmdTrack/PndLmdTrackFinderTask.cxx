// -------------------------------------------------------------------------
// -----                      PndLmdTrackFinderTask                    -----
// -----                  Created 22/10/09  by M. Michel               -----
// -------------------------------------------------------------------------

#include "TArrayD.h"
#include "TClonesArray.h"
#include "TGeoManager.h"

#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"

#include "PndLmdGeometryHelper.h"
#include "PndLmdTrackFinderTask.h"
#include "PndSdsDigiPixel.h"
#include "TStopwatch.h"
// #include "PndSdsPixelCluster.h"

// -----   Default constructor   -------------------------------------------
PndLmdTrackFinderTask::PndLmdTrackFinderTask(Int_t inFinderMode,
                                             TString hitBranch, Int_t innSensPP)
    : FairTask("LMD Track Finding Task"),
      nSensPP(innSensPP) {
  fFinderMode = inFinderMode;
  fHitBranchPixel = hitBranch;
  dXY = 0.01;
  flagStipSens = false;
  flagPixelSens = false;
  //   dXY = 0.01;//TEST
}

// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
PndLmdTrackFinderTask::~PndLmdTrackFinderTask() {}
// -------------------------------------------------------------------------

// -----   Initialization  of Parameter Containers -------------------------
void PndLmdTrackFinderTask::SetParContainers() {}

InitStatus PndLmdTrackFinderTask::ReInit() {
  InitStatus stat = kERROR;
  return stat;
}

// -----   Public method Init   --------------------------------------------
InitStatus PndLmdTrackFinderTask::Init() {
  FairRootManager *ioman = FairRootManager::Instance();

  if (!ioman) {
    std::cout << "-E- PndLmdTrackFinderTask::Init: "
              << "RootManager not instantiated!" << std::endl;
    return kFATAL;
  }

  // Get input array
  fPixelHitArray = (TClonesArray *)ioman->GetObject(fHitBranchPixel);
  if (!fPixelHitArray) {
    std::cout << "-W- PndLmdTrackFinderTask::Init: "
              << "No fPixelHitArray!" << std::endl;
    return kERROR;
  }

  fTrackCandArray = new TClonesArray("PndTrackCand");
  ioman->Register("LMDTrackCand", "PndLmd", fTrackCandArray, kTRUE);

  //  fTruePointArray = new TClonesArray("PndSdsMCPoint");

  std::cout << "-I- PndLmdTrackFinderTask: Initialisation successfull"
            << std::endl;
  return kSUCCESS;
}
// -------------------------------------------------------------------------

// -----   Private method SortHitsByDet
// --------------------------------------------
bool PndLmdTrackFinderTask::SortHitsByDet(
    std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
    Int_t nPixelHits) {
  Int_t nPlanes = 0;

  // sort in plane's
  for (Int_t iHit = 0; iHit < nPixelHits; iHit++) {
    PndSdsHit *myHit = (PndSdsHit *)(fPixelHitArray->At(iHit));

    Int_t sensid = myHit->GetSensorID();  // Sensors: 1..32
    // cout<<"sensid = "<<sensid<<endl;
    Int_t planeid = floor(
        (sensid) / (double)nSensPP);  // nSensPP sensors/plane => Planes: 0..3
    hitsd.at(planeid).push_back(make_pair(iHit, false));
  }

  for (Int_t iPlane = 0; iPlane < 4; iPlane++) {
    if (hitsd.at(iPlane).size() > 0) nPlanes++;
  }

  //  cout << "Hits: " << nPixelHits << endl;
  if (fVerbose > 2) {
    cout << "Hits: " << nPixelHits << " in " << nPlanes << " plane(s)." << endl;
    for (Int_t idet = 0; idet < 4; idet++)
      cout << "Plane: " << idet << " DiscHits: " << hitsd.at(idet).size()
           << endl;
  }

  if (nPlanes > 2) return true;
  return false;
}
// -------------------------------------------------------------------------

// -----   Private method SortHitsByDet2
// --------------------------------------------
bool PndLmdTrackFinderTask::SortHitsByDet2(
    std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
    Int_t nPixelHits) {
  Int_t nPlanes = 0;

  // sort in plane's
  for (Int_t iHit = 0; iHit < nPixelHits; iHit++) {
    PndSdsHit *myHit = (PndSdsHit *)(fPixelHitArray->At(iHit));

    Int_t sensid = myHit->GetSensorID();

    auto& lmd_geo_helper(PndLmdGeometryHelper::getInstance());
    auto const &hit_info = lmd_geo_helper.getHitLocationInfo(sensid);
    // hitsd.at(iplane).push_back(iHit);
    hitsd.at(hit_info.plane).push_back(make_pair(iHit, false));
    // cout<<"sensid = "<<sensid<<endl;
    // Int_t planeid = floor((sensid)/(double)nSensPP); //nSensPP sensors/plane
    // => Planes: 0..3
    // hitsd.at(planeid).push_back( make_pair (iHit,false) );
  }

  for (Int_t iPlane = 0; iPlane < 4; iPlane++) {
    if (hitsd.at(iPlane).size() > 0) nPlanes++;
  }

  //  cout << "Hits: " << nPixelHits << endl;
  if (fVerbose > 2) {
    cout << "Hits: " << nPixelHits << " in " << nPlanes << " plane(s)." << endl;
    for (Int_t idet = 0; idet < 4; idet++)
      cout << "Plane: " << idet << " DiscHits: " << hitsd.at(idet).size()
           << endl;
  }

  if (nPlanes > 2) return true;
  return false;
}
// -------------------------------------------------------------------------

// -----   Private method SortHitsByZ
// --------------------------------------------
bool PndLmdTrackFinderTask::SortHitsByZ(
    std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
    Int_t nPixelHits) {
  std::vector<Double_t> detZ;

  // find plane positions
  for (Int_t iHit = 0; iHit < nPixelHits; iHit++) {
    Double_t tmp = ((PndSdsHit *)(fPixelHitArray->At(iHit)))->GetZ();
    bool newZ = true;
    for (size_t idet = 0; idet < detZ.size(); idet++) {
      //  if(tmp == detZ.at(idet)){ //check if already found
      //   cout<<"tmp = "<<tmp<<" detZ.at(idet) = "<<detZ.at(idet)
      //	  <<" fabs(tmp-detZ.at(idet))="<<fabs(tmp-detZ.at(idet))<<endl;
      if (fabs(tmp - detZ.at(idet)) <
          9.) {  // check if already found [for using with Dipole]
        newZ = false;
      }
    }
    if (newZ) {
      detZ.push_back(tmp);

      // sort positions
      Int_t pos = -1;
      for (Int_t idet = detZ.size() - 1; idet >= 0; idet--) {
        if (tmp < detZ.at(idet)) pos = idet;
      }
      if (pos != -1) {
        Double_t swap = detZ.at(pos);
        detZ.at(pos) = tmp;
        tmp = swap;
        for (size_t i = pos + 1; i < detZ.size(); i++) {
          swap = detZ.at(i);
          detZ.at(i) = tmp;
          tmp = swap;
        }
      }
    }
  }
  //  cout<<"Attention! detZ.size()="<<detZ.size()<<endl;

  // sort in plane's
  for (Int_t iHit = 0; iHit < nPixelHits; iHit++) {
    PndSdsHit *myHit = (PndSdsHit *)(fPixelHitArray->At(iHit));

    Double_t z = myHit->GetZ();
    for (size_t idet = 0; idet < detZ.size(); idet++) {  // planes

      // if( z == detZ.at(idet) ){
      if (fabs(z - detZ.at(idet)) < 9.) {  //[for using with Dipole]
        hitsd.at(idet).push_back(make_pair(iHit, false));
        //	cout<<"detZ.at("<<idet<<")="<<detZ.at(idet)<<" z="<<z<<endl;
      }
    }
  }

  //   cout << "Hits: " << nPixelHits << endl;
  if (fVerbose > 2) {
    cout << "Hits: " << nPixelHits << " in " << detZ.size() << " plane(s)."
         << endl;
    for (size_t idet = 0; idet < detZ.size(); idet++)
      cout << "Plane: " << idet << " DiscHits: " << hitsd.at(idet).size()
           << endl;
  }

  if (detZ.size() > 3) return true;
  return false;
}
// -------------------------------------------------------------------------

// -----   Private method FindHitsIII
// --------------------------------------------
void PndLmdTrackFinderTask::FindHitsIII(
    std::vector<PndTrackCand> &tofill,
    std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
    Int_t)  // nPixelHits //FIXME [R.K.03/2017] unused variable(s)
{
  std::vector<TVector3> trackStart, trackVec;    // pseudo tracks
  std::vector<TVector3> trackStartd, trackVecd;  // save errors
  std::vector<Int_t> trackID2, trackID3;         // for TrackCand

  // iterate first discs-hits with all seconds, save pseudo-tracks
  TVector3 start, tmp, vec, dstart, dvec;  // temp-vars

  if (hitsd.size() < 3) return;
  for (size_t i = 0; i < hitsd.at(1).size(); i++) {
    if (hitsd.at(1).at(i).second) continue;  // if already used
    PndSdsHit *hit1 = (PndSdsHit *)fPixelHitArray->At(hitsd.at(1).at(i).first);
    start.SetXYZ(hit1->GetX(), hit1->GetY(), hit1->GetZ());
    dstart.SetXYZ(hit1->GetDx(), hit1->GetDy(), hit1->GetDz());
    for (size_t k = 0; k < hitsd.at(2).size(); k++) {
      if (hitsd.at(2).at(k).second) continue;  // if already used
      PndSdsHit *hit2 =
          (PndSdsHit *)fPixelHitArray->At(hitsd.at(2).at(k).first);
      tmp.SetXYZ(hit2->GetX(), hit2->GetY(), hit2->GetZ());
      vec = tmp - start;  // calc direction vector for FINDING
      dvec.SetXYZ(hit2->GetDx(), hit2->GetDy(), hit2->GetDz());
      if (vec.Theta() > 0.03 && vec.Theta() < 0.05 && vec.Phi() > -0.25 &&
          vec.Phi() < 0.25) {  // ignore vectors with theta outside 2-9 mrad
        // if(0<1){
        //      if(vec.Theta()<0.01){ //ignore vectors with theta outside 10
        //      mrad
        trackStart.push_back(start);
        trackStartd.push_back(dstart);
        trackVec.push_back(vec);    // save vector from start to second
        trackVecd.push_back(dvec);  // save error of second point for FIT, NOT
                                    // error of direction vector
        // trackID1.push_back(hitsd.at(0).at(i).first);  //save Hit-Id's for
        // TrackCand
        // trackID2.push_back(hitsd.at(1).at(k).first);
        trackID2.push_back(i);  // save Hit-Id's for TrackCand
        trackID3.push_back(k);
      }
    }  // end of disc 2 (or 3 if none in disc 2) hits
  }    // end of disc 1 hits

  if (fVerbose > 1) cout << "Pseudos L2L3: " << trackStart.size() << endl;

  std::vector<Int_t> ids;

  // check if other discs have hits in track, add points for fitting
  // ---------------
  for (size_t i = 0; i < trackStart.size(); i++)  // pseudo-loop
  {
    ids.clear();
    Int_t pntcnt = 2;

    start = trackStart.at(i);
    dstart = trackStartd.at(i);
    vec = trackVec.at(i);
    dvec = trackVecd.at(i);
    ids.push_back(hitsd.at(1).at(trackID2.at(i)).first);
    ids.push_back(hitsd.at(2).at(trackID3.at(i)).first);
    std::vector<std::pair<Int_t, Int_t> > otherIDs;

    for (Int_t idet = 3; idet < 4;
         idet++) {  // i know this is not a loop, but in case we someday will
                    // have more planes
      Double_t distClosest = 2 * idet * dXY;  // just bigger as possible
      Bool_t firstp = true;
      for (size_t ihit = 0; ihit < hitsd.at(idet).size(); ihit++) {
        PndSdsHit *hit =
            (PndSdsHit *)fPixelHitArray->At(hitsd.at(idet).at(ihit).first);
        Double_t scale = (hit->GetZ() - start.z()) / vec.z();
        tmp = start + scale * vec;  // extend search-vector to hit-plane
        Double_t distTmp =
            sqrt((tmp.x() - hit->GetX()) * (tmp.x() - hit->GetX()) +
                 (tmp.y() - hit->GetY()) * (tmp.y() - hit->GetY()));
        if (distTmp < (idet * dXY)) {  // if in diameter
          if (firstp) {
            pntcnt++;
            ids.push_back(hitsd.at(idet).at(ihit).first);
            otherIDs.push_back(make_pair(idet, ihit));
            distClosest = distTmp;
            firstp = false;
          } else {
            if (distTmp < distClosest) {  // change if nearer
              ids.pop_back();
              otherIDs.pop_back();
              ids.push_back(hitsd.at(idet).at(ihit).first);
              otherIDs.push_back(make_pair(idet, ihit));
            }
          }
        }  // endif in diameter
      }    // end of disc n hits
    }      // end of discs

    if (fVerbose > 2)
      cout << "  Track L2L3: " << i << "#Planes: " << ids.size() << endl;

    // create track for fitting
    if (ids.size() > 2) {  // third hit found <=> !track found!
      PndTrackCand *myTCand = new PndTrackCand();

      for (size_t id = 0; id < ids.size(); id++) {
        PndSdsHit *myHit = (PndSdsHit *)(fPixelHitArray->At(ids.at(id)));
        myTCand->AddHit(myHit->GetDetectorID(), ids.at(id),
                        myHit->GetPosition().Mag());
      }

      // mark used hits---------
      hitsd.at(1).at(trackID2.at(i)).second = true;
      hitsd.at(2).at(trackID3.at(i)).second = true;
      for (size_t id = 0; id < otherIDs.size(); id++) {
        hitsd.at(otherIDs.at(id).first).at(otherIDs.at(id).second).second =
            true;
      }

      // ///Add seed information to track------------
      // PndSdsHit* myHit0 = (PndSdsHit*)(fPixelHitArray->At(ids.at(0)));
      // PndSdsHit* myHit1 = (PndSdsHit*)(fPixelHitArray->At(ids.at(1)));
      // TVector3 hit0 = myHit0->GetPosition(); TVector3 hit1 =
      // myHit1->GetPosition();
      // TVector3 posSeed(hit0.X(),hit0.Y(),hit0.Z());
      // vec*=1./vec.Mag();
      // //shift trk out of plane [needed for correct treatment in Kalman
      // Fillter and GEANE]
      // double sh_z = -0.035; //350 mkm
      // double sh_x = vec.X()*sh_z;
      // double sh_y = vec.Y()*sh_y;
      // TVector3 sh_point(sh_x,sh_y,sh_z);
      // posSeed +=sh_point;
      // myTCand->setTrackSeed(posSeed,vec,-1);
      // ///-------------------------------------

      tofill.push_back(*(myTCand));  // save Track Candidate
      // new((*fTrackCandArray)[trackCnt]) PndTrackCand(*(myTCand));
      delete myTCand;
    }  // Track Cand build
  }    // end of pseudo-tracks
}
// -------------------------------------------------------------------------

// -----   Private method FindHitsII
// --------------------------------------------
void PndLmdTrackFinderTask::FindHitsII(
    std::vector<PndTrackCand> &tofill,
    std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
    Int_t)  // nPixelHits //FIXME [R.K.03/2017] unused variable(s)
{
  std::vector<TVector3> trackStart, trackVec;    // pseudo tracks
  std::vector<TVector3> trackStartd, trackVecd;  // save errors
  std::vector<Int_t> trackID1, trackID3;         // for TrackCand

  // iterate first discs-hits with all seconds, save pseudo-tracks
  TVector3 start, tmp, vec, dstart, dvec;  // temp-vars

  if (hitsd.size() < 3) return;
  for (size_t i = 0; i < hitsd.at(0).size(); i++) {
    if (hitsd.at(0).at(i).second) continue;  // if already used
    PndSdsHit *hit1 = (PndSdsHit *)fPixelHitArray->At(hitsd.at(0).at(i).first);
    start.SetXYZ(hit1->GetX(), hit1->GetY(), hit1->GetZ());
    dstart.SetXYZ(hit1->GetDx(), hit1->GetDy(), hit1->GetDz());
    for (size_t k = 0; k < hitsd.at(2).size(); k++) {
      if (hitsd.at(2).at(k).second) continue;  // if already used
      PndSdsHit *hit2 =
          (PndSdsHit *)fPixelHitArray->At(hitsd.at(2).at(k).first);
      tmp.SetXYZ(hit2->GetX(), hit2->GetY(), hit2->GetZ());
      vec = tmp - start;  // calc direction vector for FINDING
      dvec.SetXYZ(hit2->GetDx(), hit2->GetDy(), hit2->GetDz());
      if (vec.Theta() > 0.03 && vec.Theta() < 0.05 && vec.Phi() > -0.25 &&
          vec.Phi() < 0.25) {  // ignore vectors with theta outside 2-9 mrad
        // if(0<1){
        //	if(vec.Theta()<0.01){ //ignore vectors with theta outside 10
        //mrad
        trackStart.push_back(start);
        trackStartd.push_back(dstart);
        trackVec.push_back(vec);    // save vector from start to second
        trackVecd.push_back(dvec);  // save error of second point for FIT, NOT
                                    // error of direction vector
        // trackID1.push_back(hitsd.at(0).at(i).first);  //save Hit-Id's for
        // TrackCand
        // trackID2.push_back(hitsd.at(1).at(k).first);
        trackID1.push_back(i);  // save Hit-Id's for TrackCand
        trackID3.push_back(k);
      }
    }  // end of disc 2 (or 3 if none in disc 2) hits
  }    // end of disc 1 hits

  if (fVerbose > 1) cout << "Pseudos L1L3: " << trackStart.size() << endl;

  std::vector<Int_t> ids;

  // check if other discs have hits in track, add points for fitting
  // ---------------
  for (size_t i = 0; i < trackStart.size(); i++)  // pseudo-loop
  {
    ids.clear();
    Int_t pntcnt = 2;

    start = trackStart.at(i);
    dstart = trackStartd.at(i);
    vec = trackVec.at(i);
    dvec = trackVecd.at(i);
    ids.push_back(hitsd.at(0).at(trackID1.at(i)).first);
    ids.push_back(hitsd.at(2).at(trackID3.at(i)).first);
    std::vector<std::pair<Int_t, Int_t> > otherIDs;

    for (Int_t idet = 3; idet < 4;
         idet++) {  // i know this is not a loop, but in case we someday will
                    // have more planes
      Double_t distClosest = 2 * idet * dXY;  // just bigger as possible
      Bool_t firstp = true;
      for (size_t ihit = 0; ihit < hitsd.at(idet).size(); ihit++) {
        PndSdsHit *hit =
            (PndSdsHit *)fPixelHitArray->At(hitsd.at(idet).at(ihit).first);
        Double_t scale = (hit->GetZ() - start.z()) / vec.z();
        tmp = start + scale * vec;  // extend search-vector to hit-plane
        Double_t distTmp =
            sqrt((tmp.x() - hit->GetX()) * (tmp.x() - hit->GetX()) +
                 (tmp.y() - hit->GetY()) * (tmp.y() - hit->GetY()));
        if (distTmp < (idet * dXY)) {  // if in diameter
          if (firstp) {
            pntcnt++;
            ids.push_back(hitsd.at(idet).at(ihit).first);
            otherIDs.push_back(make_pair(idet, ihit));
            distClosest = distTmp;
            firstp = false;
          } else {
            if (distTmp < distClosest) {  // change if nearer
              ids.pop_back();
              otherIDs.pop_back();
              ids.push_back(hitsd.at(idet).at(ihit).first);
              otherIDs.push_back(make_pair(idet, ihit));
            }
          }
        }  // endif in diameter
      }    // end of disc n hits
    }      // end of discs

    if (fVerbose > 2)
      cout << "  Track L1L3: " << i << "#Planes: " << ids.size() << endl;

    // create track für fitting
    if (ids.size() > 2) {  // third hit found <=> !track found!
      PndTrackCand *myTCand = new PndTrackCand();

      for (size_t id = 0; id < ids.size(); id++) {
        PndSdsHit *myHit = (PndSdsHit *)(fPixelHitArray->At(ids.at(id)));
        myTCand->AddHit(myHit->GetDetectorID(), ids.at(id),
                        myHit->GetPosition().Mag());
      }

      // mark used hits---------
      hitsd.at(0).at(trackID1.at(i)).second = true;
      hitsd.at(2).at(trackID3.at(i)).second = true;
      for (size_t id = 0; id < otherIDs.size(); id++) {
        hitsd.at(otherIDs.at(id).first).at(otherIDs.at(id).second).second =
            true;
      }

      // ///Add seed information to track------------
      // PndSdsHit* myHit0 = (PndSdsHit*)(fPixelHitArray->At(ids.at(0)));
      // PndSdsHit* myHit1 = (PndSdsHit*)(fPixelHitArray->At(ids.at(1)));
      // TVector3 hit0 = myHit0->GetPosition(); TVector3 hit1 =
      // myHit1->GetPosition();
      // TVector3 posSeed(hit0.X(),hit0.Y(),hit0.Z());
      // vec*=1./vec.Mag();
      // 	//shift trk out of plane [needed for correct treatment in Kalman
      // Fillter and GEANE]
      // 	double sh_z = -0.035; //350 mkm
      // 	double sh_x = vec.X()*sh_z;
      // 	double sh_y = vec.Y()*sh_y;
      // 	TVector3 sh_point(sh_x,sh_y,sh_z);
      // 	posSeed +=sh_point;
      // myTCand->setTrackSeed(posSeed,vec,-1);
      // ///-------------------------------------

      tofill.push_back(*(myTCand));  // save Track Candidate
      // new((*fTrackCandArray)[trackCnt]) PndTrackCand(*(myTCand));
      delete myTCand;
    }  // Track Cand build
  }    // end of pseudo-tracks
}
// -------------------------------------------------------------------------

// -----   Private method FindHitsI --------------------------------------------
void PndLmdTrackFinderTask::FindHitsI(
    std::vector<PndTrackCand> &tofill,
    std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
    Int_t)  // nPixelHits //FIXME [R.K.03/2017] unused variable(s)
{
  std::vector<TVector3> trackStart, trackVec;    // pseudo tracks
  std::vector<TVector3> trackStartd, trackVecd;  // save errors
  std::vector<Int_t> trackID1, trackID2;         // for TrackCand

  // iterate first discs-hits with all seconds, save pseudo-tracks
  TVector3 start, tmp, vec, dstart, dvec;  // temp-vars

  if (hitsd.size() < 2) return;
  for (size_t i = 0; i < hitsd.at(0).size(); i++) {
    PndSdsHit *hit1 = (PndSdsHit *)fPixelHitArray->At(hitsd.at(0).at(i).first);
    start.SetXYZ(hit1->GetX(), hit1->GetY(), hit1->GetZ());
    dstart.SetXYZ(hit1->GetDx(), hit1->GetDy(), hit1->GetDz());
    for (size_t k = 0; k < hitsd.at(1).size(); k++) {
      PndSdsHit *hit2 =
          (PndSdsHit *)fPixelHitArray->At(hitsd.at(1).at(k).first);
      tmp.SetXYZ(hit2->GetX(), hit2->GetY(), hit2->GetZ());
      vec = tmp - start;  // calc direction vector for FINDING
      dvec.SetXYZ(hit2->GetDx(), hit2->GetDy(), hit2->GetDz());
      if (vec.Theta() > 0.03 && vec.Theta() < 0.05 && vec.Phi() > -0.25 &&
          vec.Phi() < 0.25) {  // ignore vectors with theta outside 2-9 mrad
        //      if(vec.Theta()<0.01){ //ignore vectors with theta outside 10
        //      mrad
        trackStart.push_back(start);
        trackStartd.push_back(dstart);
        trackVec.push_back(vec);    // save vector from start to second
        trackVecd.push_back(dvec);  // save error of second point for FIT, NOT
                                    // error of direction vector
        // trackID1.push_back(hitsd.at(0).at(i).first);  //save Hit-Id's for
        // TrackCand
        // trackID2.push_back(hitsd.at(1).at(k).first);
        trackID1.push_back(i);  // save Hit-Id's for TrackCand
        trackID2.push_back(k);
      }
    }  // end of disc 2 (or 3 if none in disc 2) hits
  }    // end of disc 1 hits

  if (fVerbose > 1) cout << "Pseudos L1L2: " << trackStart.size() << endl;

  std::vector<Int_t> ids;

  // check if other discs have hits in track, add points for fitting
  // ---------------
  for (size_t i = 0; i < trackStart.size(); i++)  // pseudo-loop
  {
    ids.clear();
    Int_t pntcnt = 2;

    start = trackStart.at(i);
    dstart = trackStartd.at(i);
    vec = trackVec.at(i);
    dvec = trackVecd.at(i);
    ids.push_back(hitsd.at(0).at(trackID1.at(i)).first);
    ids.push_back(hitsd.at(1).at(trackID2.at(i)).first);
    std::vector<std::pair<Int_t, Int_t> > otherIDs;

    for (Int_t idet = 2; idet < 4; idet++) {
      Double_t distClosest = 2 * idet * dXY;  // just bigger as possible
      Bool_t firstp = true;
      for (size_t ihit = 0; ihit < hitsd.at(idet).size(); ihit++) {
        PndSdsHit *hit =
            (PndSdsHit *)fPixelHitArray->At(hitsd.at(idet).at(ihit).first);
        Double_t scale = (hit->GetZ() - start.z()) / vec.z();
        tmp = start + scale * vec;  // extend search-vector to hit-plane
        Double_t distTmp =
            sqrt((tmp.x() - hit->GetX()) * (tmp.x() - hit->GetX()) +
                 (tmp.y() - hit->GetY()) * (tmp.y() - hit->GetY()));
        if (distTmp < (idet * dXY)) {  // if in diameter
          if (firstp) {
            pntcnt++;
            ids.push_back(hitsd.at(idet).at(ihit).first);
            otherIDs.push_back(make_pair(idet, ihit));
            distClosest = distTmp;
            firstp = false;
          } else {
            if (distTmp < distClosest) {  // change if nearer
              ids.pop_back();
              otherIDs.pop_back();
              ids.push_back(hitsd.at(idet).at(ihit).first);
              otherIDs.push_back(make_pair(idet, ihit));
            }
          }
        }  // endif in diameter
      }    // end of disc n hits
    }      // end of discs

    if (fVerbose > 2)
      cout << "  Track L1L2: " << i << "#Planes: " << ids.size() << endl;

    // create track für fitting
    if (ids.size() > 2) {  // third hit found <=> !track found!
      //   if(ids.size()>3){ //4 hits are needed because 6 parameters are used
      //   in trk-fit!
      // // //third hit found <=> !track found!
      // // //check direction for reduction of ghost tracks
      // if(ids.size()>2 &&
      //    fabs(vec.Phi())<0.26 && vec.Theta()>3e-2 && vec.Theta()<5e-2){
      if (fVerbose > 2)
        cout << "  Track: " << i << "#Planes: " << ids.size() << endl;
      PndTrackCand *myTCand = new PndTrackCand();

      for (size_t id = 0; id < ids.size(); id++) {
        PndSdsHit *myHit = (PndSdsHit *)(fPixelHitArray->At(ids.at(id)));
        myTCand->AddHit(myHit->GetDetectorID(), ids.at(id),
                        myHit->GetPosition().Mag());
      }

      // mark used hits---------
      hitsd.at(0).at(trackID1.at(i)).second = true;
      hitsd.at(1).at(trackID2.at(i)).second = true;
      for (size_t id = 0; id < otherIDs.size(); id++) {
        hitsd.at(otherIDs.at(id).first).at(otherIDs.at(id).second).second =
            true;
      }

      /// Add seed information to track------------
      // Double_t Z0 = 1099.;
      // //  Double_t Z0 = 0;
      // PndSdsHit* myHit0 = (PndSdsHit*)(fPixelHitArray->At(ids.at(0)));
      // PndSdsHit* myHit1 = (PndSdsHit*)(fPixelHitArray->At(ids.at(1)));
      // TVector3 hit0 = myHit0->GetPosition(); TVector3 hit1 =
      // myHit1->GetPosition();
      // double p1seed = (hit0.X()-hit1.X())/(hit0.Z()-hit1.Z());
      // double p0seed = hit0.X() - p1seed*(hit0.Z()-Z0);
      // //      double p0seed =
      // 0.5*(hit0.X()+hit1.X()-p1seed*(hit0.Z()+hit1.Z()-2*1099.)); //TO DO:
      // don't use const
      // double p3seed = (hit0.Y()-hit1.Y())/(hit0.Z()-hit1.Z());
      // double p2seed = hit0.Y() - p3seed*(hit0.Z()-Z0);
      // //double p2seed =
      // 0.5*(hit0.Y()+hit1.Y()-p1seed*(hit0.Z()+hit1.Z()-2*1099.)); //TO DO:
      // don't use const
      // TVector3 posSeed(p0seed,p2seed,Z0);
      // TVector3 dirSeed(p1seed,p3seed,1.);
      //   cout<<"posSeed:"<<endl;
      //   posSeed.Print();
      //   cout<<"dirSeed:"<<endl;
      //   dirSeed.Print();

      // //  Double_t Z0 = 1099.;
      // //     TVector3 posSeed(start.X(),start.Y(),Z0);
      // TVector3 posSeed(start.X(),start.Y(),start.Z());
      // // cout<<"Trk cand: pos"<<endl;
      // // posSeed.Print();
      // vec*=1./vec.Mag();
      // //shift trk out of plane [needed for correct treatment in Kalman
      // Fillter and GEANE]
      // double sh_z = -0.035; //350 mkm
      // double sh_x = vec.X()*sh_z;
      // double sh_y = vec.Y()*sh_y;
      // TVector3 sh_point(sh_x,sh_y,sh_z);
      // posSeed +=sh_point;

      // // cout<<"Trk cand: vec"<<endl;
      // // vec.Print();
      // myTCand->setTrackSeed(posSeed,vec,-1);
      // ///-------------------------------------

      tofill.push_back(*(myTCand));  // save Track Candidate
      // new((*fTrackCandArray)[trackCnt]) PndTrackCand(*(myTCand));
      delete myTCand;
    }  // Track Cand build
  }    // end of pseudo-tracks
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void PndLmdTrackFinderTask::Exec(Option_t *) {
  TStopwatch *timer_exec = new TStopwatch();
  if (fVerbose > 2) timer_exec->Start();
  if (fVerbose > 2) cout << "Evt started--------------" << endl << endl;

  // which combinations of planes to build pseudo-vectos
  // Int_t planeFlag=0; //flag=... 0: planes 1-2,   1: 1-2 & 1-3,   2: 1-2 & 1-3
  // & 2-3

  // Reset output array
  if (!fTrackCandArray) Fatal("Exec", "No trackCandArray");
  fTrackCandArray->Clear();

  Int_t nPixelHits = fPixelHitArray->GetEntriesFast();
  if (fVerbose > 2) cout << "# Hits: \t" << nPixelHits << endl << endl;
  // bool usedFlag[nPixelHits]; //for pseudo-vector building //[R.K.03/2017]
  // unused variable
  // for(Int_t seti=0; seti<nPixelHits; seti++) //[R.K.03/2017] unused variable
  // usedFlag[seti]=false; //[R.K.03/2017] unused variable

  if (nPixelHits < 2) {
    if (fVerbose > 2)
      cout << "Evt finsihed: too less hits-----" << endl << endl;
    return;
  }

  //-----do some sorting first----------
  std::vector<std::vector<std::pair<int, bool> > > hitsd(4);
  bool resSortHits;
  if (flagStipSens)
    resSortHits = SortHitsByDet(hitsd, nPixelHits);  //! strip sensors
  else {
    if (flagPixelSens)
      resSortHits = SortHitsByDet2(hitsd, nPixelHits);  //! pixel sensors
    else {
      std::cout << "Algorithm is needed sensor type! Please, set it via "
                   "SetSensPixelFlag(bool fS) or SetSensPixelFlag(bool fS)"
                << std::endl;
      return;
    }
  }
  if (!resSortHits) {
    if (fVerbose > 2)
      cout << "Evt finsihed: too less planes-----" << endl << endl;
    return;
  }

  if (fVerbose > 2) {
    cout << "HitMap size: " << hitsd.size() << endl;
    if (hitsd.size() > 0) {
      for (size_t i = 0; i < hitsd.at(0).size(); i++) {
        PndSdsHit *hit =
            (PndSdsHit *)fPixelHitArray->At(hitsd.at(0).at(i).first);
        cout << "Plane0 Hit=(" << hit->GetX() << ", " << hit->GetY() << ", "
             << hit->GetZ() << ")" << endl;
      }
    }
    if (hitsd.size() > 1) {
      for (size_t i = 0; i < hitsd.at(1).size(); i++) {
        PndSdsHit *hit =
            (PndSdsHit *)fPixelHitArray->At(hitsd.at(1).at(i).first);
        cout << "Plane1 Hit=(" << hit->GetX() << ", " << hit->GetY() << ", "
             << hit->GetZ() << ")" << endl;
      }
    }
    if (hitsd.size() > 2) {
      for (size_t i = 0; i < hitsd.at(2).size(); i++) {
        PndSdsHit *hit =
            (PndSdsHit *)fPixelHitArray->At(hitsd.at(2).at(i).first);
        cout << "Plane2 Hit=(" << hit->GetX() << ", " << hit->GetY() << ", "
             << hit->GetZ() << ")" << endl;
      }
    }
    if (hitsd.size() > 3) {
      for (size_t i = 0; i < hitsd.at(3).size(); i++) {
        PndSdsHit *hit =
            (PndSdsHit *)fPixelHitArray->At(hitsd.at(3).at(i).first);
        cout << "Plane3 Hit=(" << hit->GetX() << ", " << hit->GetY() << ", "
             << hit->GetZ() << ")" << endl;
      }
    }
  }

  std::vector<PndTrackCand> theCands;  // Track Candidates

  //--------find some tracks--------------
  FindHitsI(theCands, hitsd, nPixelHits);
  if (fFinderMode) {
    FindHitsII(theCands, hitsd, nPixelHits);
    FindHitsIII(theCands, hitsd, nPixelHits);
  }

  // fill tracklist für fitting
  for (size_t t = 0; t < theCands.size(); t++)
    new ((*fTrackCandArray)[t]) PndTrackCand(theCands.at(t));

  if (fVerbose > 2) cout << "Evt finsihed--------------" << endl << endl;
  if (fVerbose > 2) {
    timer_exec->Stop();
    Double_t rtime_exec = timer_exec->RealTime();
    Double_t ctime_exec = timer_exec->CpuTime();
    cout << "Real time for Exec:" << rtime_exec << " s, CPU time " << ctime_exec
         << " s" << endl;
    cout << endl;
  }
}
// -------------------------------------------------------------------------

Double_t PndLmdTrackFinderTask::GetTrackCurvature(KoaMCTrack *myTrack) {
  TVector3 p = myTrack->GetMomentum();
  return (2 / TMath::Sqrt(p.Px() * p.Px() + p.Py() * p.Py()));
}
// -------------------------------------------------------------------------

Double_t PndLmdTrackFinderTask::GetTrackDip(KoaMCTrack *myTrack) {
  TVector3 p = myTrack->GetMomentum();
  return (p.Mag() / TMath::Sqrt(p.Px() * p.Px() + p.Py() * p.Py()));
}

// -------------------------------------------------------------------------
ClassImp(PndLmdTrackFinderTask);
