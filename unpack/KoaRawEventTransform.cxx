#include "KoaRawEventTransform.h"
#include "KoaRawEvent.h"
#include "KoaRecDigi.h"
#include "KoaFwdDigi.h"
#include "TClonesArray.h"
#include "FairRootManager.h"

InitStatus KoaRawEventTransform::Init()
{
  LOG(info) << "KoaRawEventTransform::Init";

  // Get a handle from the IO manager
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) LOG(fatal) << "No FairRootManager";

  // Get raw event object from memory
  fRawEvent = static_cast<KoaRawEvent*>(ioman->GetObject("KoaRawEvent"));
  if ( ! fRawEvent ) {
    LOG(error) << "KoaRawEventTransform::Init : no input KoaRawEvent, choose correct Source!";
    return kERROR;
  }

  // Retrieve value maps
  fRecAmplitudeValueMap = fRawEvent->GetRecAmplitudeValueMap();
  fRecTimeValueMap = fRawEvent->GetRecTimeValueMap();

  fFwdAmplitudeValueMap = fRawEvent->GetFwdAmplitudeValueMap();
  fFwdTimeValueMap = fRawEvent->GetFwdTimeValueMap();

  fRecRearAmplitudeValueMap = fRawEvent->GetRecRearAmplitudeValueMap();
  fRecRearTimeValueMap = fRawEvent->GetRecRearTimeValueMap();

  // Create other new output branches
  if ( fPersistence ) {
    ioman->RegisterAny("KoaRawEvent", fRawEvent, kTRUE);
  }

  fRecDigis = new TClonesArray("KoaRecDigi", 300);
  ioman->Register("KoaRecDigi","KoaRec",fRecDigis,kTRUE);

  fRecRearDigis = new TClonesArray("KoaRecDigi", 4);
  ioman->Register("KoaRecRearDigi","KoaRec",fRecRearDigis,kTRUE);

  fFwdDigis = new TClonesArray("KoaFwdDigi", 4);
  ioman->Register("KoaFwdDigi","KoaFwd",fFwdDigis,kTRUE);

  return kSUCCESS;
}

InitStatus KoaRawEventTransform::ReInit()
{
  LOG(debug) << "KoaRawEventTransform::ReInit";

  Reset();

  return kSUCCESS;
}

void KoaRawEventTransform::SetParContainers()
{
  LOG(debug) << "KoaRawEventTransform::SetParContainers";
}

void KoaRawEventTransform::Exec(Option_t* opt)
{
  Int_t index = 0;
  // recoil front side
  for ( auto value_map : fRecAmplitudeValueMap ) {
    auto encoded_id = value_map.first;
    auto amplitude = value_map.second;
    auto time = fRecTimeValueMap[encoded_id];
    if (!time) {
      LOG(error) << "KoaRawEventTransform::Exec : unavailable time value";
    }

    KoaRecDigi* digi = new ((*fRecDigis)[index++]) KoaRecDigi();
    digi->SetDetectorID(encoded_id);
    digi->SetCharge(*amplitude);
    digi->SetTimeStamp(*time);
  }

  // fwd 
  index = 0;
  for ( auto value_map : fFwdAmplitudeValueMap ) {
    auto encoded_id = value_map.first;
    auto amplitude = value_map.second;
    auto time = fFwdTimeValueMap[encoded_id];
    if (!time) {
      LOG(error) << "KoaRawEventTransform::Exec : unavailable time value";
    }

    KoaFwdDigi* digi = new ((*fFwdDigis)[index++]) KoaFwdDigi();
    digi->SetDetectorID(encoded_id);
    digi->SetCharge(*amplitude);
    digi->SetTimeStamp(*time);
  }

  // recoil rear side
  index = 0;
  for ( auto value_map : fRecRearAmplitudeValueMap ) {
    auto encoded_id = value_map.first;
    auto amplitude = value_map.second;
    auto time = fRecRearTimeValueMap[encoded_id];
    if (!time) {
      LOG(error) << "KoaRawEventTransform::Exec : unavailable time value";
    }

    KoaRecDigi* digi = new ((*fRecRearDigis)[index++]) KoaRecDigi();
    digi->SetDetectorID(encoded_id);
    digi->SetCharge(*amplitude);
    digi->SetTimeStamp(*time);
  }
}

void KoaRawEventTransform::Finish()
{
  LOG(debug) << "KoaRawEventTransform::Finish";
}

void KoaRawEventTransform::Reset()
{
  LOG(debug) << "KoaRawEventTransform::Reset";

  fRecDigis->Clear();
  fFwdDigis->Clear();
  fRecRearDigis->Clear();
}
