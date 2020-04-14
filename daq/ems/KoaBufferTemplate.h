#ifndef KOA_BUFFER_TEMPLATE
#define KOA_BUFFER_TEMPLATE

#include "FairLogger.h"
#include <cstdint>
#include <iostream>
#include <map>
#include <string>

/************** KoaBufferStatistic Begin ********************/
struct KoaBufferStatistic
{
  KoaBufferStatistic() : events(0), words(0) {}
  void Reset() {
    events = 0;
    words  = 0;
  }

  std::uint64_t events;
  std::uint64_t words;
};

/************** KoaBufferStatist End ********************/

/************** KoaBufferItem Begin ********************/
template<typename> class KoaBufferDepot; // forward-declaration

// This is the class template  which will store the real information from user
// User should define a pure data type and use that type to instantiate this data class template
template<typename DataType>
class KoaBufferItem
{
public:
  void Initialize(); // clean the space in this item, item space has already been assigned at this stage
  void Recycle(); // recycle this item space to depot, including the Buffer Items which may be used in  fData

public:
  KoaBufferItem* fNext; // link to next item in linked-list
  DataType  fData; // the real data underneath

private:
  // The buffer item can only be constructed or deleted by corresponding Depot
  friend class KoaBufferDepot<DataType>;

  KoaBufferItem();
  ~KoaBufferItem() {}
};

template<typename DataType>
KoaBufferItem<DataType>::KoaBufferItem() :
  fData(),
  fNext(nullptr)
{
}

template<typename DataType>
void KoaBufferItem<DataType>::Initialize()
{
  // Init data inside
  fData.Initialize();

  // Set the next to null
  fNext = nullptr;
}

template<typename DataType>
void KoaBufferItem<DataType>::Recycle()
{
  // Recycle the Items inside  fData
  fData.Recycle();

  // Recycle itself
  auto Depot = KoaBufferDepot<DataType>::Instance();
  Depot->Put(this);
}

/************** KoaBufferItem End ********************/

/************** KoaBufferDepotCleaner Begin ********************/
template<typename> class KoaBufferDepot; // forward-declaration

// This class is used to destruct the singleton class KoaBufferDepot at the end of program
template<typename DataType>
class KoaBufferDepotCleaner
{
  using DepotType = KoaBufferDepot<DataType>;

public:
  KoaBufferDepotCleaner() : fDepot(nullptr) {}
  ~KoaBufferDepotCleaner() {
    if(fDepot) {
      delete fDepot;
    }
  }

  // Set the target depot to be destructed
  void SetDepot(DepotType* depot) {
    fDepot = depot;
  }

private:
  DepotType* fDepot;
};
/************** KoaBufferDepotCleaner End ********************/

/************** KoaBufferDepot Begin ********************/
template<typename DataType>
class KoaBufferDepot
{
  using ItemType = KoaBufferItem<DataType>;
  using CleanerType = KoaBufferDepotCleaner<DataType>;

public:
  static KoaBufferDepot* Instance() {
    if( !fInstance ) {
      fInstance = new KoaBufferDepot();
      fDepotCleaner.SetDepot(fInstance);
    }

    return fInstance;
  }

  // Pop out a new item space
  ItemType* Get() {
    ItemType* item = nullptr;

    if( fTop ) {
      item = fTop;
      fTop = item->fNext;
    }
    else {
      item = new ItemType();
    }

    if( !item ) {
      LOG(fatal) << "KoaBufferDepot::Get: Can't allocate new item space";
    }

    return item;
  }

  // Recycle back a new item
  void Put(ItemType* item) {
    if( !item ) {
      LOG(warn) << "KoaBufferDepot::Put: the item to be inserted is invalid";
      return;
    }

    item->fNext = fTop;
    fTop = item;
    return;
  }

protected:
  /* friend class CleanerType; */
  friend class KoaBufferDepotCleaner<DataType>;

  KoaBufferDepot() : fTop(nullptr) {}
  ~KoaBufferDepot() {
    ItemType* current = fTop;
    while( current ) {
      current = fTop->fNext;
      delete fTop;
      fTop = current;
    }
  }

private:
  static KoaBufferDepot* fInstance;
  static CleanerType fDepotCleaner;

  ItemType* fTop;
};

template<typename DataType>
KoaBufferDepot<DataType>* KoaBufferDepot<DataType>::fInstance = nullptr;

template<typename DataType>
KoaBufferDepotCleaner<DataType> KoaBufferDepot<DataType>::fDepotCleaner;
/************** KoaBufferDepot End ********************/

/************** KoaBuffer Begin ********************/
// This class is the interface to the underlying buffer
template<typename DataType>
class KoaBuffer
{
  using ItemType = KoaBufferItem<DataType>;
  using DepotType = KoaBufferDepot<DataType>;

public:
  KoaBuffer() : fPrepared(nullptr), fTop(nullptr), fBottom(nullptr), fCurrent(nullptr) {
    fDepot = DepotType::Instance();
  }

  ~KoaBuffer() {
    if( fPrepared )
      fPrepared->Recycle();

    fCurrent = fTop;
    while( fCurrent ) {
      fCurrent = fTop->fNext;
      fTop->Recycle();
      fTop = fCurrent;
    }
  }

  // Get an empty item object from depot and initialize it for later usage
  // Normally, the code getting the new item pointer will fill new data into it
  // Invoke it first before StoreNewItem and GetNewItem
  ItemType* PrepareNewItem() {
    if( !fPrepared )
      fPrepared = fDepot->Get();

    fPrepared->Initialize();
    return fPrepared;
  }

  // Just get the prepared item pointer for usage in other places
  ItemType* GetNewItem() {
    if( !fPrepared ) {
      LOG(fatal) << "KoaBuffer::GetNewItem: Invalid prepared item, invoke PrepareNewItem first";
      exit(1);
    }
    return fPrepared;
  }

  // Push the prepared item into the bottom of the buffer
  void StoreNewItem() {
    if ( !fPrepared ) {
      LOG(fatal) << "KoaBuffer::StoreNewItem: Invalid prepared item, invoke PrepareNewItem first";
      exit(1);
    }

    if ( fBottom ) {
      fBottom->fNext = fPrepared;
      fBottom = fPrepared;
    }
    else {
      fBottom = fPrepared;
      fTop = fPrepared;
      fCurrent = fPrepared;
    }

    fPrepared = nullptr;
  }

  // Pop out the first item in the buffer, which is also the oldest one inserted
  // The ownership changed in this operation, the code getting the returned pointer is in charge of the ownership
  ItemType* PopTopItem() {
    ItemType* top;

    if( !fTop )
      return nullptr;

    if( fBottom == fTop ) {
      fBottom = nullptr;
    }
    top = fTop;
    fTop = fTop->fNext;
    fCurrent = fTop;

    return top;
  }

  // checking whether the buffer is empty
  Bool_t IsEmpty() {
    if ( !fTop )
      return true;
    return false;
  }

  // Return the next item in the buffer, nullptr if reaching to the bottom
  // The ownership is not tranfered after return, just for usage of the item in other places
  // It works as an iterator, which is useful for sweep through the buffer list
  const ItemType* NextItem() {
    const ItemType* item = nullptr;
    if ( !fCurrent ) {
      item = fCurrent;
      fCurrent = fCurrent->fNext;
    }

    return item;
  }

  // Move the current pointer to the next item in the buffer
  void Next() {
    if ( !fCurrent ) {
      LOG(warn) << "KoaBuffer::Next: current position is already the end of buffer";
      return;
    }
    fCurrent = fCurrent->fNext;
  }

  // Get the current item
  const ItemType* Current() {
    return fCurrent;
  }

  // Reset the current pointer to the top of the buffer
  void Reset() {
    fCurrent = fTop;
  }

  // Recycle all item space from top to current item
  void RecycleUptoCurrent() {
    ItemType* temp;
    while ( fTop != fCurrent ) {
      temp = fTop;
      fTop = fTop->fNext;
      temp->Recycle();
    }
  }

private:
  DepotType* fDepot;
  ItemType* fPrepared;
  ItemType* fTop;
  ItemType* fBottom;
  ItemType* fCurrent;

public:
  ULong64_t fNrItem; // number of items ever stored in this buffer until current time
};
/************** KoaBuffer End ********************/

/************** KoaBufferManagerCleaner Begin ********************/
template<typename> class KoaBufferManager; // forward-declaration

// This class is used to destruct the singleton class KoaBufferDepot at the end of program
template<typename DataType>
class KoaBufferManagerCleaner
{
  using ManagerType = KoaBufferManager<DataType>;

public:
  KoaBufferManagerCleaner() : fManager(nullptr) {}
  ~KoaBufferManagerCleaner() {
    if(fManager) {
      delete fManager;
    }
  }

  // Set the target depot to be destructed
  void SetManager(ManagerType* depot) {
    fManager = depot;
  }

private:
  ManagerType* fManager;
};
/************** KoaBufferManagerCleaner End ********************/

/************** KoaBufferManager Begin ********************/
// This class is the central repository for all the buffers used.
// It managers the buffer creation and destruction. User should always create a new buffer or get an existing
// buffer through this class.
template<typename DataType>
class KoaBufferManager
{
  using BufferType = KoaBuffer<DataType>;
  using CleanerType = KoaBufferManagerCleaner<DataType>;

public:
  static KoaBufferManager* Instance() {
    if( !fInstance ) {
      fInstance = new KoaBufferManager();
      fManagerCleaner.SetManager(fInstance);
    }

    return fInstance;
  }

  BufferType* GetBuffer(std::string name) {
    BufferType* buffer;
    auto search = fBufferList.find(name);
    if (search != fBufferList.end()) {
      buffer = search->second;
    }
    else {
      buffer = new BufferType();
      fBufferList.emplace(name, buffer);
    }
    return buffer;
  }

  KoaBufferStatistic* GetStatistic(std::string name) {
    KoaBufferStatistic* buffer;
    auto search = fStatistList.find(name);
    if (search != fStatistList.end()) {
      buffer = search->second;
    }
    else {
      buffer = new KoaBufferStatistic();
      fStatistList.emplace(name, buffer);
    }
    return buffer;
  }

private:
  /* friend class CleanerType; */
  friend class KoaBufferManagerCleaner<DataType>;

  KoaBufferManager() {}
  ~KoaBufferManager() {
    for( auto buffer : fBufferList ) {
      delete buffer.second;
    }
    fBufferList.clear();

    for ( auto statist : fStatistList ) {
      delete statist.second;
    }
    fStatistList.clear();
  }

  static KoaBufferManager* fInstance;
  static CleanerType fManagerCleaner;

  std::map<std::string, BufferType*> fBufferList;
  std::map<std::string, KoaBufferStatistic*> fStatistList;
};

template<typename DataType>
KoaBufferManager<DataType>* KoaBufferManager<DataType>::fInstance = nullptr;

template<typename DataType>
KoaBufferManagerCleaner<DataType> KoaBufferManager<DataType>::fManagerCleaner;
/************** KoaBufferManager End ********************/
#endif
