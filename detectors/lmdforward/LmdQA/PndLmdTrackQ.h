// -------------------------------------------------------------------------
// -----               PndLmdTrackQ header file                  -----
// -----       Created 18/06/2013 by A.Karavdina          -----
// -------------------------------------------------------------------------


/** PndLmdTrackQ.h
 *@author A.Karavdina <karavdin@kph.uni-mainz.de>
 **
 ** Qualified reconstructed track in Luminosity detector
 **/


#ifndef PNDLMDTRACKQ_H
#define PNDLMDTRACKQ_H


#include "TVector3.h"
#include "TString.h"
#include "TObject.h"
#include "TMatrixTSym.h"
#include "TMatrixDSym.h"

#include <stdio.h>
#include <iostream>

//#include "PndTrack.h"

class PndLmdTrackQ: public TObject
{
public:
  /** Default constructor **/
  PndLmdTrackQ();

  PndLmdTrackQ(double Plab);

  /** Destructor **/
  ~PndLmdTrackQ();


  /** Accessors **/

  /** set status of reconstructed trk
  // 0 = good,
  // >0 = ghost: 1 = hit mixture, 2 = doubled trk
  // <0 = missed: -1=trk-search losses,-2=little amount of hits,-3=no MC hits, -10=trk wasn't back-propag **/
  void SetTrkRecStatus(int st){fTrkRecStatus = st;}

  /** get status of reconstructed trk
  // 0 = good,
  // >0 = ghost: 1 = hit mixture, 2 = doubled trk
  // <0 = missed: -1=trk-search losses,-2=little amount of hits,-3=no MC hits, -10=trk wasn't back-propag **/
  int GetTrkRecStatus() const{return fTrkRecStatus;}

  /** set PDG code for MC trk **/
  void SetPDGcode(int pdg){fPDGcode = pdg;}

  /** get PDG code for MC trk 
   // PDG code particle made the main contribution (65 % of hits) to the rec.track, -9999=n/a **/
  int GetPDGcode() const{return fPDGcode;}

  /** set starting point of reconstructed trk [in LMD, before back-propagation] cm **/
  void SetLMDpoint(double x, double y, double z){fXrecLMD=x;fYrecLMD=y;fZrecLMD=z;}

  /** get starting point of reconstructed trk [in LMD, before back-propagation] cm **/
  void GetLMDpoint(TVector3& lmdp){lmdp.SetXYZ(fXrecLMD,fYrecLMD,fZrecLMD);}

  /** set direction of reconstructed trk [in LMD, before back-propagation] rad **/
  void SetLMDdir(double theta, double phi){fThetarecLMD = theta; fPhirecLMD = phi;}

  /** get theta of reconstructed trk [in LMD, before back-propagation] rad **/
  double GetLMDtheta() const{return fThetarecLMD;}

  /** get phi of reconstructed trk [in LMD, before back-propagation] rad **/
  double GetLMDphi() const{return fPhirecLMD;}

  /** set chi2 of reconstructed trk [in LMD, before back-propagation] **/
  void SetLMDchi2(double chi2){fchi2LMD = chi2;}

  /** set chi2 of reconstructed trk [in LMD, before back-propagation] **/
  double GetLMDchi2() const{return fchi2LMD;}

  /** set point of reconstructed trk [in IP, after back-propagation] cm **/
  void SetIPpoint(double x, double y, double z){fXrec=x;fYrec=y;fZrec=z;}

  /** get point of reconstructed trk [in IP, after back-propagation] cm **/
  void GetIPpoint(TVector3& lmdp){lmdp.SetXYZ(fXrec,fYrec,fZrec);}

  /** set momentum vector of reconstructed trk [in IP, after back-propagation] GeV/c **/
  void SetIPmom(double theta, double phi,double mom){fThetarec = theta; fPhirec = phi; fMomrec = mom;}

  /** get theta of reconstructed trk [in IP, after back-propagation] rad **/
  double GetIPtheta() const{return fThetarec;}

  /** get phi of reconstructed trk [in IP, after back-propagation] rad **/
  double GetIPphi() const{return fPhirec;}

  /** get momentum magnitude of reconstructed trk [in IP, after back-propagation] GeV/c **/
  double GetIPmom() const{return fMomrec;}

  /** set point errors of reconstructed trk [in IP, after back-propagation] cm **/
  void SetIPerrpoint(double errx, double erry, double errz){ferrXrec=errx;ferrYrec=erry;ferrZrec=errz;}

  /** get point errors of reconstructed trk [in IP, after back-propagation] cm **/
  void GetIPerrpoint(TVector3& lmdp){lmdp.SetXYZ(ferrXrec,ferrYrec,ferrZrec);}

  /** set momentum vector errors of reconstructed trk [in IP, after back-propagation] GeV/c x=theta, y=phi, z=mom **/
  void SetIPerrmom(double errtheta, double errphi, double errmom){ferrThetarec = errtheta; ferrPhirec = errphi; ferrMomrec = errmom;}

  /** get momentum vector errors of reconstructed trk [in IP, after back-propagation] GeV/c  x=theta, y=phi, z=mom**/
  void GetIPerrmom(TVector3& lmerrdp){lmerrdp.SetXYZ(ferrThetarec,ferrPhirec,ferrMomrec);}

  /** set starting point of MC trk [in IP] cm **/
  void SetMCpoint(double x, double y, double z){fXmc=x;fYmc=y;fZmc=z;}

  /** get starting point of MC trk [in IP] cm **/
  void GetMCpoint(TVector3& lmdp){lmdp.SetXYZ(fXmc,fYmc,fZmc);}

  /** set starting momentum vector of MC trk [in IP] GeV/c **/
  void SetMCmom(double theta, double phi,double mom){fThetamc = theta; fPhimc = phi; fMommc = mom;}

  /** get theta of MC trk [in IP] rad **/
  double GetMCtheta() const{return fThetamc;}

  /** get phi of MC trk [in IP] rad **/
  double GetMCphi() const{return fPhimc;}

  /** get momentum magnitude of MC trk [in IP] GeV/c **/
  double GetMCmom() const{return fMommc;}

  /** get starting point of MC trk [near LMD] cm **/
  void GetMCpointLMD(TVector3& lmdp){lmdp.SetXYZ(fXmcLMD,fYmcLMD,fZmcLMD);}

  /** set starting point of MC trk [near LMD] cm **/
  void SetMCpointLMD(double x, double y, double z){fXmcLMD=x;fYmcLMD=y;fZmcLMD=z;}

  /** set momentum vector of MC trk [near LMD] rad,rad,GeV/c **/
  void SetMCmomLMD(double theta, double phi,double mom){fThetamcLMD = theta; fPhimcLMD = phi; fMommcLMD = mom;}

  /** get theta of momentum vector of MC trk [near LMD] rad **/
  double GetMCthetaLMD() const{return fThetamcLMD;}

  /** get phi of momentum vector of MC trk [near LMD] rad **/
  double GetMCphiLMD() const{return fPhimcLMD;}

  /** get magnitude of momentum vector of MC trk [near LMD] GeV/c **/
  double GetMCmomLMD() const{return fMommcLMD;}

  /** set secondary flag for MC trk  **/
  /** <0 primary, >=0 secondary **/
  void SetSecondary(int sec){fSecondary = sec;}

  /** get secondary flag for MC trk **/
  /** <0 primary, >=0 secondary **/
  int GetSecondary() const{return fSecondary;}

  /** set number of hits from one MC trk in REC trk **/
  void SetNumMChits(int num){fnumMChits = num;}

  /** get number of hits from one MC trk in REC trk **/
  int GetNumMChits() const{return fnumMChits;}

  /** set number of double hits (hit on both sides) from one MC trk in REC trk **/
  void SetNumDoubleMChits(int num){fnumMCdoublehits = num;}

  /** get number of double hits (hit on both sides) from one MC trk in REC trk **/
  int GetNumDoubleMChits() const{return fnumMCdoublehits;}

  /** set sum of PDG codes for final state particles in event **/
  void SetSumEvPDG(int sumid){fsumID=sumid;}

  /** get sum of PDG codes for final state particles in event **/
  int GetSumEvPDG() const{return fsumID;}

  /* void SetTotEvCharge(int totch){ ftotCharge = totch;} */
  /* int GetTotEvCharge() const{return ftotCharge;} */

  /** set number of simulated final state particles in event **/
  void SetEvMCMulti(int tot){ fnumEvparticles = tot;}

  /** get number of simulated final state particles in event **/
  int GetEvMCMulti() const{return fnumEvparticles;}

  /** set number of reconstructed tracks in event **/
 void SetEvRECMulti(int tot){ fnumEvRECparticles = tot;}

  /** get number of reconstructed tracks in event **/
  int GetEvRECMulti() const{return fnumEvRECparticles;}

  /** set and get time info **/
  void SetEvTime(double evtm){ fEvTime = evtm;}
  void SetTrkTime(double trktm){ fTrkTime = trktm;}
  double GetEvTime() const{return fEvTime;}
  double GetTrkTime() const{return fTrkTime;}

  /** set and get module and half of the 1st hit **/
  void SetModule(int mod){fModule = mod;}
  void SetHalf(int hf){fHalf = hf;}
  int GetModule() const{return fModule;}
  int GetHalf() const{return fHalf;}
 private:

  //  Int_t ftotCharge;
  Int_t fsumID, fnumEvparticles,fnumEvRECparticles;
  Double_t fXrecLMD,fYrecLMD,fZrecLMD,fThetarecLMD,fPhirecLMD;
  Double_t fXrec,fYrec,fZrec,fThetarec,fPhirec, fMomrec;
  Double_t ferrXrec,ferrYrec,ferrZrec,ferrThetarec,ferrPhirec, ferrMomrec;
  Double_t fXmc,fYmc,fZmc,fThetamc,fPhimc, fMommc;
  Double_t fXmcLMD,fYmcLMD,fZmcLMD,fThetamcLMD,fPhimcLMD, fMommcLMD;
  Double_t fchi2LMD;
  int fTrkRecStatus;// 0 = good,
  int fSecondary;//0=primary, 1=secondary
  int fPDGcode;// PDG code particle made the main contribution (65 % of hits) to the rec.track, -9999=n/a
  int fnumMChits;//number of MC hits for MC trk
  int fnumMCdoublehits;//number of doubled [diff side of one plane] MC hits for MC trk 
                              // >0 = ghost: 1 = hit mixture, 2 = doubled trk
                              // <0 = missed: -1=trk-search losses,-2=little amount of hits,-3=no MC hits, -10=trk wasn't back-propag
  double fEvTime;//global time for event
  double fTrkTime;//time for 1st hit in the Trk = ToF (flight time from IP to LMD)

  int fModule; //module number of 1st hit
  int fHalf;// half of the plane number of 1st hit
  ClassDef(PndLmdTrackQ,11);
};

#endif
