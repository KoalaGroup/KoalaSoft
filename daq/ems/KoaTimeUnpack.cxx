#include "KoaTimeUnpack.h"

Bool_t KoaTimeUnpack::Init()
{
  auto bufferManager = KoaEmsEventBufferManager::Instance();
  fEmsBuffer = bufferManager->GetBuffer("EMS");

  return true;
}

Int_t KoaTimeUnpack::DoUnpack(const ems_u32* buf, Int_t size)
{
  if ( size!=2 ) {
    LOG(ERROR) << "KoaTimeUnpack::DoUnpack : timestamp should have 2 words, but found " << size;
    return -1;
  }

  auto* event_data = fEmsBuffer->GetNewItem();
  event_data->fData.time.tv_sec = buf[0];
  event_data->fData.time.tv_usec = buf[1];
  event_data->fData.time_valid = true;

  return 0;
}
