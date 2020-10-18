#include "KoaEmsSource.h"
#include "KoaRawEventAnalyzer.h"
#include "KoaEventAssembler.h"
#include "KoaUnpack.h"
#include "KoaEmsEventData.h"
#include "FairLogger.h"

KoaEmsSource::~KoaEmsSource()
{
  // delete unpackers
  for (auto unpacker : fUnpackers) {
    if( unpacker.second )
      delete unpacker.second;
  }
  fUnpackers.clear();

  // delete assembler
  if (fAssembler) delete fAssembler;

  // delete raw event analyzers
  if (fKoaEvtAnalyzer) delete fKoaEvtAnalyzer;
  if (fEmsEvtAnalyzer) delete fEmsEvtAnalyzer;
}

Bool_t KoaEmsSource::Init()
{
  // 1. assembler
  if ( !fAssembler ) {
    LOG(fatal) << "KoaEmsSource::Init : no assembler assgined!";
    return false;
  }
  fAssembler->Init();

  // 2. event analyzers
  if ( !fEmsEvtAnalyzer ) {
    LOG(fatal) << "KoaEmsSource::Init : no analyzer for ems event assgined!";
    return false;
  }
  fEmsEvtAnalyzer->Init();

  if ( !fKoaEvtAnalyzer ) {
    LOG(fatal) << "KoaEmsSource::Init : no analyzer for koala event assgined!";
    return false;
  }
  fKoaEvtAnalyzer->Init();

  // 4. set up input file descriptor
  if ( fInput < 0 ) {
    LOG(fatal) << "KoaEmsSource::Init : no valid input stream available, invoking SetupInput first!";
    return false;
  }
  fCluster.set_input(fInput);

  // 5. TODO other init jobs

  return true;
}

void KoaEmsSource::SetParUnpackers()
{
  for (auto unpacker : fUnpackers) {
    unpacker.second->SetParContainers();
  }
}

Bool_t KoaEmsSource::InitUnpackers()
{
  for (auto unpacker : fUnpackers) {
    unpacker.second->Init();
  }

  return true;
}

Int_t KoaEmsSource::ReadEvent(UInt_t value)
{
  // 1) Get the next assembled koala event from previous cluster
  if ( fKoaEvtAnalyzer->Analyze() ) {
    return 0;
  }

  // 2) process all EMS events in previous cluster before reading new cluster
  fEmsEvtAnalyzer->Analyze();

  // 3) If no more assembled event, get the next cluster
  if ( !NextCluster() ) {
    // error occured or interrupted by user during cluster reading
    return 1;
  }

  // 4) parsing the new cluster
  Int_t status = DecodeCluster();
  if ( status < 0 ) {
    // cluster structure not correct, skip this cluster
    return 2;
  }
  else if ( status == 0 ) {
    // the last cluster encountered
    return 3;
  }

  // 6) assemble the new module events and fill in the koala event buffer
  fAssembler->Assemble();

  // 7) go to the koala event loop for this cluster
  ReadEvent();
}

// TODO read in next cluster and saved in fCluster from input stream
Bool_t KoaEmsSource::NextCluster()
{
  // reading process deployed to fCluster by passing file descriptor to ems_cluster

  // 1. clear buffer
  fCluster.clear_buffer();

  // 2. read header
  if ( fCluster.read_header() ) {
    return false;
  }

  // 3. read body
  if ( fCluster.read_body() ) {
    return false;
  }

  return true;
}

// return value:
// -1 : cluster structure not correct, invalid cluster
//  0 : success and no more cluster coming
//  1 : success and there is more cluster coming
Int_t KoaEmsSource::DecodeCluster()
{
  Int_t idx=0;
  clustertypes clustertype;
  ems_u32* buf = reinterpret_cast<ems_u32*>(fCluster.buffer.data);
  Int_t size = static_cast<int>(fCluster.size/sizeof(ems_u32));

  // 1) size and endiantest are already known, skip them
  idx+=2;
  if (CheckSize("KoaEmsSource::DecodeCluster :", idx, size, 1)<0)
    return -1; // invalid cluster, which value to return

  // 2) parse the cluster based on the type
  clustertype = static_cast<clustertypes>(buf[idx++]);

  switch (clustertype) {
  case clustertypes::clusterty_events: // event type
    {
      // TODO statistics
      // fStatistics.evclusters++;
      // LOG(INFO) << "cluster: events No."<< fStatistics.evclusters;

      if (ParseEvents(buf+idx, size-idx) < 0)
        return -1; // invalid cluster, which value to return
      break;
    }
  case clustertypes::clusterty_ved_info:
    {
      // currently ignored
      LOG(INFO)<<"cluster: ved_info";
      break;
    }
  case clustertypes::clusterty_text:
    {
      // currently ignored
      LOG(INFO)<<"cluster: text";
      break;
    }
  case clustertypes::clusterty_file:
    {
      // currently ignored
      LOG(INFO)<<"cluster: file";
      break;
    }
  case clustertypes::clusterty_no_more_data: // the last cluster in a file
    {
      LOG(INFO)<<"cluster: no more data";
      break;
    }
  case clustertypes::clusterty_wendy_setup:  // unknown types
  case clustertypes::clusterty_async_data:   // unknown types
  case clustertypes::clusterty_async_data2:  // unknown types
  default:
    {
      LOG(ERROR) << "unknown or unhandled clustertype " << static_cast<ems_u32>(clustertype);
      return -1; // invalid cluster, which value to return
    }
  }

return clustertype == clustertypes::clusterty_no_more_data ? 0 : 1; // whether there is more cluster to come, which value to return
}

// return:
// -1 : parsing error occured
//  0 : success
Int_t KoaEmsSource::ParseEvents(const ems_u32 *buf, Int_t size)
{
  Int_t num, nr_events, idx=0;

  // parse option words first
  if ((num=ParseOptions(buf, idx+size)) < 0)
    return -1;
  idx += num;

  // we need flags, VED_ID, fragment_id and number_of_events
  if (CheckSize("KoaEmsSource::ParseEvents :", idx, size, 4)<0)
    return -1;

  // skip flags, VED_ID, fragment_id
  idx+=3;

  // get number_of_events
  nr_events=buf[idx++];
  for (Int_t i=0; i<nr_events; i++) {
    // we need the event size
    if (CheckSize("KoaEmsSource::ParseEvents :", idx, size, 1)<0)
      return -1;
    Int_t ev_size=buf[idx++];

    // and we need ev_size words
    if (CheckSize("KoaEmsSource::ParseEvents :", idx, size, ev_size)<0)
      return -1;

    // parse event
    if ( ParseEvent(buf+idx, ev_size) < 0)
      return -1;

    idx+=ev_size;
  }

  if (idx != size) {
    LOG(ERROR) << "parse_events: size=" << size << ", used words=" << idx;
    return -1;
  }

  // TODO statistics
  // fStatistics.events+=nr_events;

  return 0; //
}

// return:
// -1 : parse error occurs
// number_of_option_words : success
Int_t KoaEmsSource::ParseOptions(const ems_u32 *buf, Int_t size)
{
  Int_t idx=0;
  Int_t optsize;

  if (CheckSize("KoaEmsSource::ParseOptions :", idx, size, 1)<0)
    return -1;

  optsize=buf[idx++];
  if (CheckSize("KoaEmsSource::ParseOptions :", idx, size, optsize)<0)
    return -1;

  return optsize+1;
}

// return:
// -1 : parse error occurs
//  0 : success
Int_t KoaEmsSource::ParseEvent(const ems_u32 *buf, Int_t size)
{
  int nr_sev, idx=0;
  int res;

  // EmsEventData initialize
  KoaEmsEventBufferManager* event_manager = KoaEmsEventBufferManager::Instance();
  // 'EMS' is the key label of the ems event buffer
  auto event_buffer = event_manager->GetBuffer("EMS");
  auto event_data = event_buffer->PrepareNewItem();

  // we need event_number, trigger id and number of subevents
  if (CheckSize("KoaEmsSource::ParseEvent :", idx, size, 3)<0)
    return -1;

  // store event_number
  event_data->fData.event_nr = buf[idx++];
  event_data->fData.evnr_valid = true;

  // skip trigger id
  idx++;

  // get number_of_subevents
  nr_sev=buf[idx++];

  for (int i=0; i<nr_sev; i++) {
    int sev_size;
    ems_u32 sev_id;

    // we need instrumentation systen ID (==subevent ID) and the size
    if (CheckSize("KoaEmsSource::ParseEvent :", idx, size, 2)<0)
      return -1;

    sev_id=buf[idx++]; // IS id
    sev_size=buf[idx++]; // size of subevent

    // and we need sev_size words
    if (CheckSize("KoaEmsSource::ParseEvent :", idx, size, sev_size)<0)
      return -1;

    // parse subevent
    if ( ParseSubevent(buf+idx, sev_size, sev_id) < 0 )
      return -1;

    idx+=sev_size;
  }

  if (idx!=size) {
    LOG(ERROR) << "parse_events: size=" << size << ", used words=" << idx;
    return -1;
  }

  // TODO statistics
  // fStatistics.subevents+=nr_sev;

  // EmsEventData storage
  event_buffer->StoreNewItem();

  return 0;
}

// return:
// 
Int_t KoaEmsSource::ParseSubevent(const ems_u32 *buf, Int_t size, ems_u32 is_id)
{
  auto search = fUnpackers.find(is_id);
  if ( search == fUnpackers.end() ) {
    LOG(error) << "KoaEmsSource::ParseSubevent : No Unpacker for IS id " << is_id;
    return -1;
  }

  if ( search->second->DoUnpack(buf, size) < 0 )
    return -1;

  return 0;
}

//
void KoaEmsSource::Close()
{
  // 2. close input stream
  if ( fInput >= 0 ) {
    LOG(info) << "KoaEmsSource::Close : close input stream";
    close(fInput);
  }

  // 3. TODO other
  fAssembler->Finish();

  // 1. event analyzers
  fKoaEvtAnalyzer->Finish();
  fEmsEvtAnalyzer->Finish(); // ems analyzer must be at last
}

Bool_t KoaEmsSource::ReInitUnpackers()
{
  for (auto unpacker : fUnpackers) {
    unpacker.second->ReInit();
  }
}

void KoaEmsSource::Reset()
{
  for (auto unpacker : fUnpackers) {
    unpacker.second->Reset();
  }
}
