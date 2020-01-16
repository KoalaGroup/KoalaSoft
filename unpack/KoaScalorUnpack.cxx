#include "KoaScalorUnpack.h"

Bool_t KoaScalorUnpack::Init()
{
  auto bufferManager = KoaEmsEventBufferManager::Instance();
  fEmsBuffer = bufferManager->GetBuffer("EMS");

  return true;
}

Int_t KoaScalorUnpack::DoUnpack(ems_u32* buf, Int_t size)
{
  if ( size!=32 ) {
    LOG(ERROR) << "KoaTimeUnpack::DoUnpack : scalor should have 32 words, but found " << size;
    return -1;
  }

  auto* event_data = fEmsBuffer->GetNewItem();
  for ( int i=0; i<32; i++ ) {
    event_data->fData.scalor[i] = buf[i];
  }
  event_data->scalor_valid = true;

  return 0;
}
