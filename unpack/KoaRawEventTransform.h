#ifndef KOA_RAWEVENT_TRANSFORM_H
#define KOA_RAWEVENT_TRANSFORM_H

#include "FairTask.h"
#include "TClonesArray.h"
#include "FairLogger.h"

class KoaRawEvent;

/* This class is used to transform KOALA raw event to standard simulation output data form.
 * It should be used together with KoaEmsSource.
 * If persistence flag is set, both the original and transformed objects are saved into file.
 * Otherwise, only the transformed objects are saved.
 */
class KoaRawEventTransform : FairTask
{
  /** Default constructor **/
  KoaRawEventTransform() : FairTask("KoaRawEventTransform"), fPersistence(false)
  {
    LOG(debug) << "KoaRawEventTransform : Default Constructor";
  }

  /** Destructor **/
  ~KoaRawEventTransform()
  {
    LOG(debug) << "KoaRawEventTransform : Destructor";

    if ( fRecDigis ) {
      fRecDigis->Delete();
      delete fRecDigis;
    }

    if ( fFwdDigis ) {
      fFwdDigis->Delete();
      delete fFwdDigis;
    }

    if ( fRecRearDigis ) {
      fRecRearDigis->Delete();
      delete fRecRearDigis;
    }
  }


  /** Initiliazation of task at the beginning of a run **/
  virtual InitStatus Init();

  /** ReInitiliazation of task when the runID changes **/
  virtual InitStatus ReInit();


  /** Executed for each event. **/
  virtual void Exec(Option_t* opt);

  /** Load the parameter container from the runtime database **/
  virtual void SetParContainers();

  /** Finish task called at the end of the run **/
  virtual void Finish();

  /** Reset eventwise counters **/
  void Reset();
  
  void SetPersistence(bool flag) { fPersistence = flag; }

private:
  KoaRawEventTransform(const KoaRawEventTransform&);
  KoaRawEventTransform operator=(const KoaRawEventTransform&);

private:
  //
  bool fPersistence;

  // input object
  KoaRawEvent* fRawEvent;

  // output objects
  TClonesArray* fRecDigis;
  TClonesArray* fFwdDigis;
  TClonesArray* fRecRearDigis;

  // value maps
  std::map<Int_t, Int_t*> fRecAmplitudeValueMap;
  std::map<Int_t, Float_t*> fRecTimeValueMap;

  std::map<Int_t, Int_t*> fFwdAmplitudeValueMap;
  std::map<Int_t, Float_t*> fFwdTimeValueMap;

  std::map<Int_t, Int_t*> fRecRearAmplitudeValueMap;
  std::map<Int_t, Float_t*> fRecRearTimeValueMap;

  ClassDef(KoaRawEventTransform,1)
};
#endif
