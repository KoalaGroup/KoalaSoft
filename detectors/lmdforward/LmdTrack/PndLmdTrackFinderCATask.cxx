// -------------------------------------------------------------------------
// -----                      PndLmdTrackFinderCATask                  -----
// -----                  Created 18/05/11  by A. Karavdina            -----
// -------------------------------------------------------------------------

#include <math.h>
#include "TArrayD.h"
#include "TClonesArray.h"
#include "TGeoManager.h"
#include "TVectorD.h"

#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"

#include "PndLmdTrackFinderCATask.h"

#include "PndLmdGeometryHelper.h"
#include "PndSdsDigiPixel.h"
#include "TStopwatch.h"

// #include "PndSdsPixelCluster.h"

// -----   Default constructor   -------------------------------------------
PndLmdTrackFinderCATask::PndLmdTrackFinderCATask()
    : FairTask("LMD Track Finding Task (Cellular Automation)") {
  missPlAlgo = false;
  flagTrkCandCuts = true;
  fHitBranchPixel = "LMDHitsPixel";

  dXY = 0.5;
  rule_max = 1e-6;
  nSensPP = 4;
  nP = 4;
  flagStipSens = false;
  flagPixelSens = false;
}

// -------------------------------------------------------------------------

// -----   Constructor   -------------------------------------------
PndLmdTrackFinderCATask::PndLmdTrackFinderCATask(const bool missPl,
                                                 const double setdmax,
                                                 int innSensPP, int innP,
                                                 TString hitBranch)
    : FairTask(
          "LMD Track Finding Task (Cellular Automation) with/without <<missing "
          "planes>> algoritm") {
  missPlAlgo = missPl;
  fHitBranchPixel = hitBranch;

  dXY = 0.5;
  rule_max = setdmax;
  nSensPP = innSensPP;
  nP = innP;
  flagStipSens = false;  // default
  flagPixelSens = true;  // default
}

// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
PndLmdTrackFinderCATask::~PndLmdTrackFinderCATask() {}
// -------------------------------------------------------------------------

// -----   Initialization  of Parameter Containers -------------------------
void PndLmdTrackFinderCATask::SetParContainers() {}

InitStatus PndLmdTrackFinderCATask::ReInit() {
  InitStatus stat = kERROR;
  return stat;
}

// -----   Private method SortHitsByDet
// --------------------------------------------
bool PndLmdTrackFinderCATask::SortHitsByDet(
    std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
    Int_t nPixelHits) {
  Int_t nPlanes = 0;

  // sort in plane's
  for (Int_t iHit = 0; iHit < nPixelHits; iHit++) {
    PndSdsHit *myHit = (PndSdsHit *)(fPixelHitArray->At(iHit));

    Int_t sensid = myHit->GetSensorID();  // Sensors: 1..32
    Int_t planeid = floor(
        (sensid) / (double)nSensPP);  // nSensPP sensors/plane => Planes: 0..3
    hitsd.at(planeid).push_back(make_pair(iHit, false));
  }

  for (Int_t iPlane = 0; iPlane < nP; iPlane++) {
    if (hitsd.at(iPlane).size() > 0) nPlanes++;
  }

  //  cout << "Hits: " << nPixelHits << endl;
  if (fVerbose > 2) {
    cout << "Hits: " << nPixelHits << " in " << nPlanes << " plane(s)." << endl;
    for (Int_t idet = 0; idet < nP; idet++)
      cout << "Plane: " << idet << " DiscHits: " << hitsd.at(idet).size()
           << endl;
  }

  if (nPlanes > 2) return true;
  return false;
}
// -------------------------------------------------------------------------

// -----   Private method SortHitsByDet
// --------------------------------------------
bool PndLmdTrackFinderCATask::SortHitsByDetSimple(
    std::vector<std::vector<Int_t> > &hitsd, Int_t nPixelHits) {
  Int_t nPlanes = 0;

  // sort in plane's
  for (Int_t iHit = 0; iHit < nPixelHits; iHit++) {
    PndSdsHit *myHit = (PndSdsHit *)(fPixelHitArray->At(iHit));
    Int_t sensid = myHit->GetSensorID();  // Sensors: 1..32
    Int_t planeid = floor(
        (sensid) / (double)nSensPP);  // nSensPP sensors/plane => Planes: 0..3
    hitsd.at(planeid).push_back(iHit);
  }

  for (Int_t iPlane = 0; iPlane < nP; iPlane++) {
    if (hitsd.at(iPlane).size() > 0) nPlanes++;
  }

  if (fVerbose > 2) {
    cout << "Hits: " << nPixelHits << " in " << nPlanes << " plane(s)." << endl;
    for (Int_t idet = 0; idet < nP; idet++)
      cout << "Plane: " << idet << " DiscHits: " << hitsd.at(idet).size()
           << endl;
  }

  if (nPlanes > 2) return true;
  return false;
}
// -------------------------------------------------------------------------

// -----   Private method SortHitsByDet
// --------------------------------------------
bool PndLmdTrackFinderCATask::SortHitsByDetSimple2(
    std::vector<std::vector<Int_t> > &hitsd, Int_t nPixelHits) {
  Int_t nPlanes = 0;

  auto &lmd_helper(PndLmdGeometryHelper::getInstance());
  // sort in plane's
  for (Int_t iHit = 0; iHit < nPixelHits; iHit++) {
    PndSdsHit *myHit = (PndSdsHit *)(fPixelHitArray->At(iHit));
    Int_t sensid = myHit->GetSensorID();  // Sensors: 1..32

    const PndLmdHitLocationInfo &hit_info =
    		lmd_helper.getHitLocationInfo(sensid);

    int virtplane = hit_info.plane;  // merged hits
    if (nP > 4)
      virtplane = 2 * hit_info.plane + hit_info.module_side;  // single hits
    hitsd.at(virtplane).push_back(iHit);
  }

  for (Int_t iPlane = 0; iPlane < nP; iPlane++) {
    if (hitsd.at(iPlane).size() > 0) nPlanes++;
  }

  if (fVerbose > 2) {
    cout << "Hits: " << nPixelHits << " in " << nPlanes << " plane(s)." << endl;
    for (Int_t idet = 0; idet < nP; idet++)
      cout << "Plane: " << idet << " DiscHits: " << hitsd.at(idet).size()
           << endl;
  }

  if (nPlanes > 2) return true;
  return false;
}
// -------------------------------------------------------------------------

// -----   Private method SortHitsByZ
// --------------------------------------------
bool PndLmdTrackFinderCATask::SortHitsByZ(
    std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
    Int_t nPixelHits) {
  std::vector<Double_t> detZ;

  // find plane positions
  for (Int_t iHit = 0; iHit < nPixelHits; iHit++) {
    Double_t tmp = ((PndSdsHit *)(fPixelHitArray->At(iHit)))->GetZ();
    bool newZ = true;
    for (unsigned int idet = 0; idet < detZ.size(); idet++) {
      if (fabs(tmp - detZ.at(idet)) <
          9.) {  // check if already found [for using with Dipole]
        newZ = false;
      }
    }
    if (newZ) {
      detZ.push_back(tmp);

      // sort positions
      Int_t pos = -1;
      for (int idet = detZ.size() - 1; idet >= 0; idet--) {
        if (tmp < detZ.at(idet)) pos = idet;
      }
      if (pos != -1) {
        Double_t swap = detZ.at(pos);
        detZ.at(pos) = tmp;
        tmp = swap;
        for (unsigned int i = pos + 1; i < detZ.size(); i++) {
          swap = detZ.at(i);
          detZ.at(i) = tmp;
          tmp = swap;
        }
      }
    }
  }

  // sort in plane's
  for (Int_t iHit = 0; iHit < nPixelHits; iHit++) {
    PndSdsHit *myHit = (PndSdsHit *)(fPixelHitArray->At(iHit));

    Double_t z = myHit->GetZ();
    for (unsigned int idet = 0; idet < detZ.size(); idet++) {  // planes

      if (fabs(z - detZ.at(idet)) < 9.) {  //[for using with Dipole]
        hitsd.at(idet).push_back(make_pair(iHit, false));
      }
    }
  }

  if (fVerbose > 2) {
    cout << "Hits: " << nPixelHits << " in " << detZ.size() << " plane(s)."
         << endl;
    for (unsigned int idet = 0; idet < detZ.size(); idet++)
      cout << "Plane: " << idet << " DiscHits: " << hitsd.at(idet).size()
           << endl;
  }

  if (detZ.size() > 3) return true;
  return false;
}
// -------------------------------------------------------------------------

// -----   Public method Init   --------------------------------------------
InitStatus PndLmdTrackFinderCATask::Init() {
  FairRootManager *ioman = FairRootManager::Instance();

  if (!ioman) {
    std::cout << "-E- PndLmdTrackFinderCATask::Init: "
              << "RootManager not instantiated!" << std::endl;
    return kFATAL;
  }

  // Get input array
  fPixelHitArray = (TClonesArray *)ioman->GetObject(fHitBranchPixel);
  if (!fPixelHitArray) {
    std::cout << "-W- PndLmdTrackFinderCATask::Init: "
              << "No fPixelHitArray!" << std::endl;
    return kERROR;
  }

  fTrackCandArray = new TClonesArray("PndTrackCand");
  ioman->Register("LMDTrackCand", "PndLmd", fTrackCandArray, kTRUE);

  fCellArray = new TClonesArray("PndSdsCell");

  std::cout << "-I- PndLmdTrackFinderCATask: Initialisation successfull"
            << std::endl;
  if (missPlAlgo)
    std::cout << "-I- PndLmdTrackFinderCATask: missing plane(s) algorithm will "
                 "be used"
              << std::endl;
  return kSUCCESS;
}
// -------------------------------------------------------------------------

bool PndLmdTrackFinderCATask::Neighbor(int &icell0, int &icell1) {
  PndSdsCell *cell0 = (PndSdsCell *)fCellArray->At(icell0);
  PndSdsCell *cell1 = (PndSdsCell *)fCellArray->At(icell1);

  if ((cell0->GetHitUp()) != (cell1->GetHitDw())) return false;
  // else{
  // check if cells make straight line
  PndSdsHit *hit00 = (PndSdsHit *)fPixelHitArray->At(cell0->GetHitDw());
  PndSdsHit *hit01 = (PndSdsHit *)fPixelHitArray->At(cell0->GetHitUp());
  //	  PndSdsHit *hit10 =(PndSdsHit*)fPixelHitArray->At(cell1->GetHitDw());
  PndSdsHit *hit11 = (PndSdsHit *)fPixelHitArray->At(cell1->GetHitUp());
  TVector3 A(hit01->GetX() - hit00->GetX(), hit01->GetY() - hit00->GetY(),
             hit01->GetZ() - hit00->GetZ());
  TVector3 B(hit11->GetX() - hit01->GetX(), hit11->GetY() - hit01->GetY(),
             hit11->GetZ() - hit01->GetZ());
  double ScalAB = A.Dot(B);
  double cosPsi = ScalAB / (A.Mag() * B.Mag());
  if ((1 - cosPsi) < rule_max) return true;
  //  else
  return false;
  //  }
}

// check if cells can build a straight line
bool PndLmdTrackFinderCATask::Neighbor(PndSdsCell *cell0, PndSdsCell *cell1) {
  // //NOTE: it's assumed ((cell0->GetHitUp())==(cell1->GetHitDw())
  // // if((cell0->GetHitUp())!=(cell1->GetHitDw())) return false;
  // // else{
  //   //check if cells make straight line
  PndSdsHit *hit00 = (PndSdsHit *)fPixelHitArray->At(cell0->GetHitDw());
  PndSdsHit *hit01 = (PndSdsHit *)fPixelHitArray->At(cell0->GetHitUp());
  PndSdsHit *hit11 = (PndSdsHit *)fPixelHitArray->At(cell1->GetHitUp());
  TVector3 A(hit01->GetX() - hit00->GetX(), hit01->GetY() - hit00->GetY(),
             hit01->GetZ() - hit00->GetZ());
  TVector3 B(hit11->GetX() - hit01->GetX(), hit11->GetY() - hit01->GetY(),
             hit11->GetZ() - hit01->GetZ());
  double cosPsi = (A.Dot(B)) / (A.Mag() * B.Mag());
  if ((1 - cosPsi) < rule_max) return true;
  return false;
  // 	  //	  else return false;
  // 	  // double cosPsi = 1 - (A.Dot(B))/(A.Mag()*B.Mag());
  // 	  // if(fabs(cosPsi-rule_max)<0.5*rule_max) return true;
  // 	  // else return false;
  //	  return true;
}

// update cell status in evolution
// TODO: smth buggy here, check it
void PndLmdTrackFinderCATask::Evolution(
    int &pv0, int &pv1, int &pv0_n, int &pv1_n,
    bool) {  // isstop // [R.K.03/2017] unused variable(s)
  // isstop = true; //  // [R.K.03/2017] unused variable
  if (pv0 == pv1) {
    if (pv1 < 0)
      pv0_n = 0;
    else
      pv0_n = pv0;
    pv1_n = pv1 + 1;
    // isstop = false; //  // [R.K.03/2017] unused variable
    if (fVerbose > 2) cout << "pv 0 = " << pv0_n << " pv 1 = " << pv1_n << endl;
  }
}

TClonesArray *PndLmdTrackFinderCATask::ForwardEvolution(
    TClonesArray *tCellArray, int niter) {
  // Find neighbors between cells
  /// Set counters values -----
  std::vector<int> pv_new;
  Int_t nCells = tCellArray->GetEntriesFast();
  for (int icv = 0; icv < nCells; icv++) pv_new.push_back(-1);
  bool stop_itter = true;
  // for(int itt=0;itt<1000;itt++){ //should be infinite loop! due to small
  // number of layers 1000 is close to infinity ;)
  TStopwatch *timer_neighbors_itter = new TStopwatch();
  for (int itt = 0; itt < niter;
       itt++) {  // should be infinite loop! due to small number of layers 1000
                 // is close to infinity ;)
    int ncells_tmp = 0;
    stop_itter = true;

    if (fVerbose > 0) timer_neighbors_itter->Start();
    nCells = tCellArray->GetEntriesFast();
    if (fVerbose > 0)
      cout << " === ITTER === " << itt << " with " << nCells << " cells"
           << endl;
    for (int ic = 0; ic < nCells; ic++) {
      PndSdsCell *cell0 = (PndSdsCell *)tCellArray->At(ic);
      for (int jc = ic + 1; jc < nCells; jc++) {
        PndSdsCell *cell1 = (PndSdsCell *)tCellArray->At(jc);
        if ((cell0->GetHitUp()) != (cell1->GetHitDw())) continue;
        bool isNeighbor = Neighbor(cell0, cell1);
        //	bool isNeighbor = Neighbor(ic,jc);
        if (isNeighbor) {
          // PndSdsCell *cell0 =   (PndSdsCell*)tCellArray->At(ic);
          // PndSdsCell *cell1 =   (PndSdsCell*)tCellArray->At(jc);
          if (itt > 0) {
            if ((cell0->GetPV()) == (cell1->GetPV())) {
              if ((cell1->GetPV()) < 0) pv_new[ic] = 0;
              if ((cell1->GetPV()) > -1) pv_new[ic] = cell0->GetPV();
              pv_new[jc] = cell1->GetPV() + 1;
              stop_itter = false;
              if (fVerbose > 2)
                cout << "pv 0 = " << pv_new[ic] << " pv 1 = " << pv_new[jc]
                     << endl;
            }
          }
          if (itt < 1) {
            pv_new[ic] = 0;
            pv_new[jc] = 0;
            stop_itter = false;
          }
        }
      }
    }

    for (int icv = 0; icv < tCellArray->GetEntriesFast(); icv++) {
      if (pv_new[icv] < 0) {  // clean not used cells
        tCellArray->RemoveAt(icv);
        tCellArray->Compress();
        pv_new.erase(pv_new.begin() + icv);
        icv--;
      } else {
        PndSdsCell *cell = (PndSdsCell *)tCellArray->At(icv);
        if (fVerbose > 2)
          cout << "cell with hitDw = " << cell->GetHitDw()
               << " and hitUp = " << cell->GetHitUp()
               << " gets new PV = " << pv_new[icv] << endl;
        cell->SetPV(pv_new[icv]);
        ncells_tmp++;
      }
    }

    if (fVerbose > 0) {
      cout << "One itter with " << nCells << " cells: " << endl;
      timer_neighbors_itter->Stop();
      timer_neighbors_itter->Print();
    }
    if (fVerbose > 0 && stop_itter)
      cout << "-- CA made " << itt << " itterations --" << endl;
    if (stop_itter) break;
  }
  delete timer_neighbors_itter;
  ///--------------------------
  //  delete  fCellArray_tmp;
  return tCellArray;
}

// create cells between all planes at once
TClonesArray *PndLmdTrackFinderCATask::CookAllCells(
    std::vector<std::vector<Int_t> > hitsd) {
  TClonesArray *tCellArray = new TClonesArray("PndSdsCell");
  // int ncells=0; //[R.K. 01/2017] unused variable
  if (fVerbose > 2) {
    int nPixelHits = fPixelHitArray->GetEntriesFast();
    cout << "Start cell contruction from " << nPixelHits << " hits" << endl;
  }
  for (int pl0 = 0; pl0 < 3; pl0++) {
    int pl1 = pl0 + 1;  // no "missing plane"
    tCellArray = CookCells(hitsd, pl0, pl1, tCellArray);
    if (missPlAlgo && pl0 < 4 - 2) {
      pl1 = pl0 + 2;  // with "missing plane"
      tCellArray = CookCells(hitsd, pl0, pl1, tCellArray);
    }
  }
  return tCellArray;
}

// create cells between particular planes
TClonesArray *PndLmdTrackFinderCATask::CookCells(
    std::vector<std::vector<Int_t> > hitsd, int &pl0, int &pl1,
    TClonesArray *tCellArray) {
  int ncells = tCellArray->GetEntriesFast();
  if (fVerbose > 2) {
    int nPixelHits = fPixelHitArray->GetEntriesFast();
    cout << "Start cell contruction from " << nPixelHits << " hits" << endl;
  }
  for (unsigned int i = 0; i < hitsd.at(pl0).size(); i++) {
    for (unsigned int j = 0; j < hitsd.at(pl1).size(); j++) {
      if (fVerbose > 2)
        cout << "new cell with hits #" << hitsd.at(pl0).at(i) << " and "
             << hitsd.at(pl1).at(j) << endl;
      // PndSdsCell *cell = new PndSdsCell(hitsd.at(pl1).at(j),
      // hitsd.at(pl0).at(i));
      // new((*tCellArray)[ncells]) PndSdsCell(*(cell)); //save Track
      // delete cell;
      new ((*tCellArray)[ncells]) PndSdsCell(hitsd.at(pl1).at(j),
                                             hitsd.at(pl0).at(i));  // save cell
      ncells++;
    }
  }
  return tCellArray;
}

// -----   Public method Exec   --------------------------------------------
void PndLmdTrackFinderCATask::Exec(Option_t *) {
  TStopwatch *timer_array = new TStopwatch();

  if (fVerbose > 0) timer_array->Start();

  // Reset output array
  if (!fTrackCandArray) Fatal("Exec", "No trackCandArray");
  fTrackCandArray->Clear("C");

  Int_t nPixelHits = fPixelHitArray->GetEntriesFast();
  if (nPixelHits < 2) {
    if (fVerbose > 2)
      cout << "Evt finsihed: too less hits-----" << endl << endl;
    return;
  }

  std::vector<std::vector<Int_t> > hitsd(
      nP);  // hit'ids splitted by detectorplane
  bool resSortHits;
  if (flagStipSens)
    resSortHits = SortHitsByDetSimple(hitsd, nPixelHits);  //! strip sensors
  else {
    if (flagPixelSens)
      resSortHits = SortHitsByDetSimple2(hitsd, nPixelHits);  //! pixel sensors
    else {
      std::cout << "Algorithm depend on sensor type! Please, set it via "
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

  // print hits (debug)
  TVector3 start, tmp, vec, dstart, dvec;  // temp-vars
  if (fVerbose > 2) {
    for (Int_t iPlane = 0; iPlane < nP; iPlane++) {
      if (hitsd.at(iPlane).size() > 0) {
        for (unsigned int i = 0; i < hitsd.at(iPlane).size(); i++) {
          PndSdsHit *hit =
              (PndSdsHit *)fPixelHitArray->At(hitsd.at(iPlane).at(i));
          if (fVerbose > 2)
            cout << " Hit#" << hitsd.at(iPlane).at(i) << " Plane" << iPlane
                 << " Hit=(" << hit->GetX() << ", " << hit->GetY() << ", "
                 << hit->GetZ() << ") with err=(" << hit->GetDx() << ", "
                 << hit->GetDy() << ", " << hit->GetDz() << ")"
                 << ", MChitID = " << hit->GetRefIndex() << endl;
        }
      }
    }
  }
  if (fVerbose > 0) {
    cout << "array preparation: " << endl;
    timer_array->Stop();
    timer_array->Print();
  }
  //

  // Build  cells
  fCellArray->Clear();
  // const unsigned int nplanes = nP; //[R.K. 01/2017] unused variable
  TStopwatch *timer_cook_cells = new TStopwatch();
  if (fVerbose > 0) timer_cook_cells->Start();

  /*
   //CA2: all cells at once
   fCellArray = CookAllCells(hitsd);
   */

  // CA3: build cells between 2 pairs of layers
  // ATTENTION: the detector is assumed to have exactly 4 planes!
  // TODO: generalize to nplanes>4
  // PART1: build cells only between first 3 layers ----------------------------
  for (int pl0 = 0; pl0 < 2; pl0++) {
    int pl1 = pl0 + 1;
    fCellArray = CookCells(hitsd, pl0, pl1, fCellArray);
  }

  // if(missPlAlgo){
  //   int pl0 = 1; int pl1 = 3;
  //   fCellArray = CookCells(hitsd, pl0, pl1, fCellArray);
  // }

  fCellArray = ForwardEvolution(fCellArray, 2);  // clean cells without neigbors
  // int prev_st_size = fCellArray->GetEntriesFast() - 1;
  // prev_st_size = 0;
  // cout<<" !!!! prev_st_siz = "<< prev_st_size<<endl;
  int pvd = -1;
  for (int icell0 = 0; icell0 < fCellArray->GetEntries(); icell0++) {
    PndSdsCell *cell0 = (PndSdsCell *)fCellArray->At(icell0);
    cell0->SetPV(pvd);
  }
  //[END] PART1
  //------------------------------------------------------------------

  // PART2: build cells only between last 3 layers ----------------------------
  // if(missPlAlgo){
  //   int pl0 = 0; int pl1 = 2;
  //   fCellArray = CookCells(hitsd, pl0, pl1, fCellArray);
  // }

  for (int pl0 = 1; pl0 < 3; pl0++) {
    int pl1 = pl0 + 1;
    fCellArray = CookCells(hitsd, pl0, pl1, fCellArray);
  }

  fCellArray = ForwardEvolution(fCellArray, 2);  // clean cells without neigbors
  for (int icell0 = 0; icell0 < fCellArray->GetEntries(); icell0++) {
    PndSdsCell *cell0 = (PndSdsCell *)fCellArray->At(icell0);
    cell0->SetPV(pvd);
  }
  //[END] PART2
  //------------------------------------------------------------------

  // //PART3: add combinations for missing planes
  // ---------------------------------
  if (missPlAlgo) {
    // 0-2-3
    int pl0 = 0;
    int pl1 = 2;
    fCellArray = CookCells(hitsd, pl0, pl1, fCellArray);
    pl0 = 2;
    pl1 = 3;
    fCellArray = CookCells(hitsd, pl0, pl1, fCellArray);
    fCellArray =
        ForwardEvolution(fCellArray, 2);  // clean cells without neigbors

    pl0 = 1;
    pl1 = 3;
    fCellArray = CookCells(hitsd, pl0, pl1, fCellArray);
    pl0 = 0;
    pl1 = 1;
    fCellArray = CookCells(hitsd, pl0, pl1, fCellArray);
    fCellArray =
        ForwardEvolution(fCellArray, 2);  // clean cells without neigbors
  }
  // //[END] PART3
  // -----------------------------------------------------------------------

  for (int icell0 = 0; icell0 < fCellArray->GetEntries(); icell0++) {
    PndSdsCell *cell0 = (PndSdsCell *)fCellArray->At(icell0);
    cell0->SetPV(pvd);
  }

  if (fVerbose > 0) {
    cout << "Cells cooking:" << endl;
    timer_cook_cells->Stop();
    timer_cook_cells->Print();
  }

  TStopwatch *timer_neighbors_cells = new TStopwatch();
  if (fVerbose > 0) timer_cook_cells->Start();

  // Find neighbors between cells
  fCellArray = ForwardEvolution(fCellArray, 100);
  int nCells = fCellArray->GetEntriesFast();  // final number of cells [could be
                                              // different from the initial]

  // Build tracks from cells combination --------------------------------
  TStopwatch *timer_build_trk_combinations = new TStopwatch();

  if (fVerbose > 0) timer_build_trk_combinations->Start();

  // find max number of cells in a track
  int pcmax = 0;
  for (int cid = 1; cid < nCells; cid++) {
    PndSdsCell *cell = (PndSdsCell *)fCellArray->At(cid);
    int tag_cur = cell->GetPV();
    if (tag_cur > pcmax) pcmax = tag_cur;
  }
  if (fVerbose > 4) cout << "track can contain " << pcmax << "+1 cells" << endl;
  const unsigned int trk_arr_size = pcmax + 1;
  std::vector<std::vector<int> > trk_cells(trk_arr_size);

  int trk_count = -1;
  for (unsigned int newpcmax = pcmax; newpcmax > 0;
       newpcmax--) {  // loop over possible number of cells in trk
    unsigned int cur_max_tag = newpcmax;
    if (fVerbose > 4)
      cout << "Now we are looking for trk with max " << cur_max_tag + 1
           << " cells among " << nCells << " cells" << endl;
    //    bool newtrk=true;
    for (int icell0 = 0; icell0 < nCells; icell0++) {
      PndSdsCell *cell0 = (PndSdsCell *)fCellArray->At(icell0);
      if (cell0->GetPV() ==
          (int)cur_max_tag) {  // from "upstream" to "downstream"
        for (int icell1 = 0; icell1 < nCells; icell1++) {
          PndSdsCell *cell1 = (PndSdsCell *)fCellArray->At(icell1);
          if ((cell0->GetPV() - cell1->GetPV()) == 1 &&
              ((cell1->GetHitUp()) ==
               (cell0->GetHitDw()))) {  // cells have common point
            bool isNeighbor = Neighbor(cell1, cell0);
            if (isNeighbor) {
              if (fVerbose > 2)
                cout << "trk #" << trk_count << " " << cell0->GetPV() << ", "
                     << cell1->GetPV() << "; ";
              if (cell1->GetPV() > 0) {  // search for the last connected cell;
                                         // TODO: this works only for number of
                                         // planes = 4!!! extend it to infinite
                                         // number of planes?
                for (int icell2 = 0; icell2 < nCells; icell2++) {
                  PndSdsCell *cell2 = (PndSdsCell *)fCellArray->At(icell2);
                  if ((cell1->GetPV() - cell2->GetPV()) == 1 &&
                      (cell2->GetHitUp()) ==
                          (cell1->GetHitDw())) {  // cells have common point
                    bool isNeighbor2 = Neighbor(cell2, cell1);
                    if (isNeighbor2) {
                      trk_count++;
                      trk_cells.at(cell0->GetPV()).push_back(icell0);
                      trk_cells.at(cell1->GetPV()).push_back(icell1);
                      trk_cells.at(cell2->GetPV()).push_back(icell2);
                      if (fVerbose > 2) cout << " " << cell2->GetPV();
                    }
                  }
                }
              } else {
                trk_count++;
                trk_cells.at(cell0->GetPV()).push_back(icell0);
                trk_cells.at(cell1->GetPV()).push_back(icell1);
                if ((cell0->GetPV() + 1) == pcmax) {
                  trk_cells.at(cell0->GetPV() + 1).push_back(-1);
                  if (fVerbose > 2) cout << " -1";
                }
              }
              if (fVerbose > 2) cout << "" << endl;
            }
          }
        }
      }
    }
  }
  if (fVerbose > 0) {
    timer_build_trk_combinations->Stop();
    cout << "Build trks combinations: " << endl;
    timer_build_trk_combinations->Print();
  }
  if (fVerbose > 2)
    cout << "Before filtering number of trk-cands = " << trk_cells.at(0).size()
         << endl;

  // filter ----------------------------------------------------
  TStopwatch *timer_filter_trk_combinations = new TStopwatch();

  if (fVerbose > 0) timer_filter_trk_combinations->Start();

  if (fVerbose > 4) cout << "--- filter trk-cand array: " << endl;
  if (fVerbose > 4)
    cout << " Attention each trk candidate with repeated cells, but smaller "
            "cells number will be deleted!"
         << endl;
  vector<unsigned int> cell_parts;
  vector<bool> trk_accept;
  for (unsigned int itrk = 0; itrk < trk_cells.at(0).size(); itrk++) {
    int maxcellnum = trk_arr_size;
    int curr_arr = trk_arr_size;
    while (curr_arr > 0) {
      curr_arr--;
      if (fVerbose > 4)
        cout << " we have: trk_cells.at(" << curr_arr << ").at(" << itrk
             << ")=" << trk_cells.at(curr_arr).at(itrk) << endl;
      if (trk_cells.at(curr_arr).at(itrk) < 0) maxcellnum--;
    }
    cell_parts.push_back(maxcellnum);
    if (maxcellnum > 0)
      trk_accept.push_back(true);
    else
      trk_accept.push_back(false);
    if (fVerbose > 4) cout << " with:" << maxcellnum << " cells" << endl;
  }

  for (int itrc = (cell_parts.size() - 1); itrc >= 0; itrc--) {
    if (!trk_accept[itrc]) continue;
    int cup = itrc - 1;
    for (int itrc2 = cup; itrc2 >= 0; itrc2--) {
      if (!trk_accept[itrc]) break;
      if (!trk_accept[itrc2]) continue;
      //      cout<<"compare trk#"<<itrc<<" and #"<<itrc2<<endl;

      if (cell_parts[itrc] < cell_parts[itrc2]) {
        unsigned int count_re = 0;
        unsigned int count_hits = 0;
        // reject trk-cand with smaller number of cells and similar cells
        int curr_arr = trk_arr_size;
        while (curr_arr > 0) {
          curr_arr--;
          int cellnum1 = trk_cells.at(curr_arr).at(itrc);
          int cellnum2 = trk_cells.at(curr_arr).at(itrc2);
          // check by cells
          if (cellnum1 < 0 || cellnum2 < 0) continue;
          if (cellnum1 == cellnum2) count_re++;
          // check by cells ends (hits)
          PndSdsCell *cell0 = (PndSdsCell *)fCellArray->At(cellnum1);
          PndSdsCell *cell1 = (PndSdsCell *)fCellArray->At(cellnum2);
          int hit0_0 = cell0->GetHitDw();
          int hit1_0 = cell0->GetHitUp();
          int hit0_1 = cell1->GetHitDw();
          int hit1_1 = cell1->GetHitUp();
          if (hit0_0 == hit0_1) count_hits++;
          if (hit1_0 == hit1_1) count_hits++;
          if (hit0_0 == hit1_1) count_hits++;
          if (hit1_0 == hit0_1) count_hits++;
        }
        if (fVerbose > 3)
          cout << "Cand.No" << itrc
               << ": Number of repeating cells = " << count_re
               << " and cells in tot = " << cell_parts[itrc]
               << " Number of repeating hits = " << count_hits << endl;
        if (count_re > 0.55 * cell_parts[itrc] || count_hits > 2) {
          trk_accept[itrc] = false;
          if (fVerbose > 4) {
            cout << "Delete: trk-cand#" << itrc << " because it contains ("
                 << count_re << ") more then 55% cells from trk-cand#" << itrc2
                 << endl;
          }
        }
      }
    }
  }

  if (fVerbose > 0) {
    timer_filter_trk_combinations->Stop();
    cout << "Filter: " << endl;
    timer_filter_trk_combinations->Print();
  }

  // save trk-cands ----------------------------------------
  int NtrkRec = 0;
  for (unsigned int itrk = 0; itrk < trk_accept.size(); itrk++) {
    if (!trk_accept[itrk]) continue;  // filter
    bool firstHit = true;
    PndTrackCand *myTCand = new PndTrackCand();
    TVector3 dir;
    if (fVerbose > 2) cout << "Trk-cand contains hits:";
    for (unsigned int icell = 0; icell < trk_arr_size; icell++) {
      int cellNum = trk_cells.at(icell).at(itrk);
      if (cellNum < 0) continue;
      //    cout<<"; from cell#"<<cellNum<<": ";
      PndSdsCell *cell = (PndSdsCell *)fCellArray->At(cellNum);
      if (firstHit) {  // fill trk-cand seed
        PndSdsHit *myHit = (PndSdsHit *)fPixelHitArray->At(cell->GetHitDw());
        if (fVerbose > 2) cout << " " << cell->GetHitDw();
        myTCand->AddHit(myHit->GetDetectorID(), cell->GetHitDw(),
                        myHit->GetPosition().Z());
        PndSdsHit *myHit1 = (PndSdsHit *)fPixelHitArray->At(cell->GetHitUp());
        dir = myHit1->GetPosition() - myHit->GetPosition();
        dir *= 1. / dir.Mag();
        firstHit = false;
      }
      if (fVerbose > 2) cout << " " << cell->GetHitUp();
      PndSdsHit *myHit1 = (PndSdsHit *)fPixelHitArray->At(cell->GetHitUp());
      myTCand->AddHit(myHit1->GetDetectorID(), cell->GetHitUp(),
                      myHit1->GetPosition().Z());
    }
    if (fVerbose > 2) cout << " " << endl;

    new ((*fTrackCandArray)[NtrkRec++])
        PndTrackCand(*(myTCand));  // save Track Candidate

    if (fVerbose > 3) cout << "Ntrk No. " << NtrkRec << endl;
    delete myTCand;
  }

  hitsd.erase(hitsd.begin(), hitsd.end());
  if (fVerbose > 2) {
    Int_t ntcandFin = fTrackCandArray->GetEntriesFast();
    cout << "Number of Trk-Cands is " << ntcandFin << endl;
    cout << "Evt finsihed--------------" << endl << endl;
    cout << endl;
  }

  fCellArray->Clear();

  delete timer_array;
  delete timer_cook_cells;
  delete timer_neighbors_cells;
  delete timer_build_trk_combinations;
  delete timer_filter_trk_combinations;

  fPixelHitArray->Clear("C");
}

Double_t PndLmdTrackFinderCATask::GetTrackCurvature(KoaMCTrack *myTrack) {
  TVector3 p = myTrack->GetMomentum();
  return (2 / TMath::Sqrt(p.Px() * p.Px() + p.Py() * p.Py()));
}
// -------------------------------------------------------------------------

Double_t PndLmdTrackFinderCATask::GetTrackDip(KoaMCTrack *myTrack) {
  TVector3 p = myTrack->GetMomentum();
  return (p.Mag() / TMath::Sqrt(p.Px() * p.Px() + p.Py() * p.Py()));
}
void PndLmdTrackFinderCATask::FinishTask() {
  delete fCellArray;
  // delete lmddim;
  // delete fCellArray_tmp;
}
// -------------------------------------------------------------------------
ClassImp(PndLmdTrackFinderCATask)
