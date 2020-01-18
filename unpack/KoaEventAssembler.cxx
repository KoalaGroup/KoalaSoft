#include "KoaEventAssembler.h"

void KoaEventAssembler::Init()
{
  // 1. Get module table config
  auto emsConfig = KoaEmsConfig::Instance();
  if (!emsConfig) {
    LOG(fatal) << "KoaEventAssembler::Init : no valid EMS configuration information exists,"
               << "instantiate an instance of KoaEmsConfig first!";
    return false;
  }
  fModuleTable = emsConfig->GetModuleTable();

  // 2. Init module buffers
  auto bufferManager = KoaMxdc32BufferManager::Instance();
  for ( auto module : fModuleTable ) {
    auto module_id = module.first;
    auto module_info = module.second;

    auto module_buffer = bufferManager->GetBuffer(module_info.name);
    fModuleBuffer.emplace(module_id, module_buffer);
  }

  // 3. Init koala event buffer
  auto koabufferManager = KoaEventBufferManager::Instance();
  fKoalaBuffer = koabufferManager->GetBuffer("KOALA");
}

void KoaEventAssembler::Assemble()
{
  
  while ( IsFull() ) {
    auto koala_cur = fKoalaBuffer->PrepareNewItem();
    for ( auto module : fModuleBuffer ) {
      koala_cur->modules.empalce(module.first, module.second->PopTopItem());
    }
    fKoalaBuffer->StoreNewItem();
  }
}

ClassImp(KoaEventAnalyzer)
