#include "KoaEventAssembler.h"

void KoaEventAssembler::Init()
{
  // 1. Get module table config
  auto emsConfig = KoaEmsConfig::Instance();
  if (!emsConfig) {
    LOG(fatal) << "KoaEventAssembler::Init : no valid EMS configuration information exists,"
               << "instantiate an instance of KoaEmsConfig first!";
    return;
  }
  fModuleTable = emsConfig->GetModuleTable();

  // 2. Init module buffers
  auto bufferManager = KoaMxdc32BufferManager::Instance();
  for ( auto module : fModuleTable ) {
    auto module_id = module.first;
    auto module_info = module.second;

    auto module_buffer = bufferManager->GetBuffer(module_info.name);
    fModuleBuffer.emplace(module_id, module_buffer);
    auto module_stat = bufferManager->GetStatistic(module_info.name);
    fModuleStat.emplace(module_id, module_stat);
  }
  fModuleNr = fModuleBuffer.size();

  // 3. Init koala event buffer
  auto koabufferManager = KoaEventBufferManager::Instance();
  fKoalaBuffer = koabufferManager->GetBuffer("KOALA");
  fKoalaStat = koabufferManager->GetStatistic("KOALA");
}

void KoaEventAssembler::Assemble()
{
  while ( NextEvent() ) {
    // pop out modules and assemble
    auto koala_cur = fKoalaBuffer->PrepareNewItem();
    for ( auto module : fModuleBuffer ) {
      koala_cur->fData.modules.emplace(module.first, module.second->PopTopItem());
    }
    fKoalaBuffer->StoreNewItem();
    fKoalaStat->events++;
  }
}

void KoaEventAssembler::Finish()
{
  for( auto module : fModuleBuffer ){
    auto buffer = module.second;
    while (auto item = buffer->PopTopItem()) {
      item->Recycle();
      fModuleStat[module.first]->remaining++;
    }
  }
}

ClassImp(KoaEventAssembler)
