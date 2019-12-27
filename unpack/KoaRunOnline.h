#ifndef KOA_RUNONLINE_H
#define KOA_RUNONLINE_H

#include "FairRun.h"
#include "FairLogger.h"
#include "FairRunInfo.h"
#include "TString.h"

class FairSource;
class TFile;
class FairField;
class TObject;
class THttpServer;

class KoaRunOnline : public FairRun
{
 public:
  static KoaRunOnline* Instance();
  virtual ~KoaRunOnline();
  KoaRunOnline();

  void Init();
  void Run(Int_t Ev_start = -1, Int_t Ev_end = -1);
  /** Re-read all parameters in case run id changed **/
  void Reinit(UInt_t runId);

  /** Set if the run should be closed automatically after executing the run functuion **/
  void SetAutoFinish(Bool_t val) { fAutomaticFinish = val; }
  /** Set the source which should be used **/
  void SetSource(FairSource* source) { fRootManager->SetSource(source); }
  /** Return pointer to source **/
  FairSource* GetSource() { return fRootManager->GetSource(); }

  /** Set external geometry file */
  void SetGeomFile(const char* GeoFileName);
  /** Return a pointer to the geometry file */
  TFile* GetGeoFile() { return fInputGeoFile; }

  /** Initialization of parameter container is set to static **/
  //  i.e: param continers will not be reinit if the run id changes in the same session
  void        SetContainerStatic(Bool_t tempBool=kTRUE);
  Bool_t      GetContainerStatic() { return fStaticParamContainer; };

  /// The following function is the interface of FairRun, it's meaningless in KoalaSoft ///
  FairField*  GetField() {
    LOG(WARN) << "There is no magnetic field in KOALA experiment";
    return 0;
  }

  /** Add histogram to be displayed using THttpServer.*/
  void AddObject(TObject* object);
  /** Register a command on the http server.
   * @param name a command name starting with /
   * @param command a call to method "/object_name/->Method()"
   */
  void RegisterHttpCommand(TString name, TString command);
  /** Activate http server on defined host port. To be called before Init.
   * @param refreshRate an interval in number of events for server update.
   * @param httpPort the port which is used by the http server
   */
  void ActivateHttpServer(Int_t refreshRate = 10000, Int_t httpPort=8080);
  /** Get direct access to the http server. */
  THttpServer* GetHttpServer() { return fServer; }

 private:
  KoaRunOnline(const KoaRunOnline& rhs);
  KoaRunOnline& operator=(const KoaRunOnline& rhs) { return *this; }

  /** Event Loop Implementation **/
  Int_t EventLoop();
  /** Fill operation after each event **/
  void Fill();
  /** Write last data to file, close input and output **/
  void Finish();
  
 private:
  static KoaRunOnline* fgRinstance;

  Bool_t fIsInitialized;
  Bool_t fAutomaticFinish;
  Bool_t fStaticParamContainer;

  FairRunInfo fRunInfo;//!

  /** Geometry file related **/
  TFile* fInputGeoFile;
  Bool_t fLoadGeo;

  /** Http Server related **/
  Int_t fNevents;      //!
  THttpServer* fServer;             //!
  Int_t fServerRefreshRate;  //!
};

#endif
