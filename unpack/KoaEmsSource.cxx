#include "KoaEmsSource.h"

KoaEmsSource::KoaEmsSource()
{
  
}

KoaEmsSource::~KoaEmsSource()
{
  // delete unpackers
  for (auto unpacker : fUnpackers) {
    if( unpacker->second )
      delete unpacker->second;
  }
  fUnpackers.clear();
}

Bool_t KoaEmsSource::Init()
{
  
}

Bool_t KoaEmsSource::SetParUnpackers()
{
  
}

Bool_t KoaEmsSource::InitParContainers()
{
  
}

Int_t KoaEmsSource::ReadEvent()
{
  // 1) Get the next assembled koala event
  Int_t status = GetNextEvent();

  // 2) If no more assembled event, get the next cluster

  // 3) parsing the new cluster
  status = DecodeCluster();

  // 4) process the ems event

  // 5) assemble the new module events and fill in the koala event buffer

  // 6) go back to ReadEvent again
  ReadEvent();
}

Bool_t KoaEmsSource::NextCluster()
{
  
}

// return value:
// -1 : cluster structure not correct, invalid cluster
//  0 : success and no more cluster coming
//  1 : success and there is more cluster coming
Int_t KoaEmsSource::DecodeCluster()
{
  Int_t idx=0;
  clustertypes clustertype;
  ems_u32* buf = static_cast<ems_u32*>fCluster.buffer.data;
  Int_t size = fCluster.buffer.size;

  // 1) size and endiantest are already known, skip them
  idx+=2;
  if (check_size("cluster", idx, size, 1)<0)
    return -1; //TODO, invalid cluster, which value to return

  // 2) parse the cluster based on the type
  clustertype=static_cast<clustertypes>(buf[idx++]);

  switch (clustertype) {
  case clusterty_events: // event type
    {
      // TODO statistics
      fStatistics.evclusters++;
      LOG_S(INFO)<<"cluster: events No."<< fStatistics.evclusters;

      if (ParseEvents(buf+idx, size-idx) < 0)
        return -1; //TODO, invalid cluster, which value to return
      break;
    }
  case clusterty_ved_info:
    {
      // currently ignored
      LOG_S(INFO)<<"cluster: ved_info";
      break;
    }
  case clusterty_text:
    {
      // currently ignored
      LOG_S(INFO)<<"cluster: text";
      break;
    }
  case clusterty_file:
    {
      // currently ignored
      LOG_S(INFO)<<"cluster: file";
      break;
    }
  case clusterty_no_more_data: // the last cluster in a file
    {
      LOG_S(INFO)<<"cluster: no more data";
      break;
    }
  case clusterty_wendy_setup:  // unknown types
  case clusterty_async_data:   // unknown types
  case clusterty_async_data2:  // unknown types
  default:
    {
      LOG_S(ERROR)<<"unknown or unhandled clustertype"<<clustertype<<endl;
      return -1; //TODO, invalid cluster, which value to return
    }
  }

  return clustertype == clusterty_no_more_data ? 0 : 1; //TODO, whether there is more cluster to come, which value to return
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
  if (check_size("events", idx, size, 4)<0)
    return -1;

  // skip flags, VED_ID, fragment_id
  idx+=3;

  // get number_of_events
  nr_events=buf[idx++];
  for (Int_t i=0; i<nr_events; i++) {
    // we need the event size
    if (check_size("events", idx, size, 1)<0)
      return -1;
    Int_t ev_size=buf[idx++];

    // and we need ev_size words
    if (check_size("events", idx, size, ev_size)<0)
      return -1;

    // parse event
    if ( ParseEvent(buf+idx, ev_size) < 0)
      return -1;

    idx+=ev_size;
  }

  if (idx != size) {
    LOG_S(ERROR)<<"parse_events: size="<<size<<", used words="<<idx;
    return -1;
  }

  // TODO statistics
  fStatistics.events+=nr_events;

  return 0; // TODO
}

// return:
// -1 : parse error occurs
// number_of_option_words : success
Int_t KoaEmsSource::ParseOptions(const ems_u32 *buf, Int_t size)
{
  Int_t idx=0;
  Int_t optsize;

  if (check_size("options", idx, size, 1)<0)
    return -1;

  optsize=buf[idx++];
  if (check_size("options", idx, size, optsize)<0)
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
  if (check_size("event", idx, size, 3)<0)
    return -1;

  // store event_number
  event_data->event_nr = buf[idx++];
  event_data->evnr_valid = true;

  // skip trigger id
  idx++;

  // get number_of_subevents
  nr_sev=buf[idx++];

  for (int i=0; i<nr_sev; i++) {
    int sev_size;
    ems_u32 sev_id;

    // we need instrumentation systen ID (==subevent ID) and the size
    if (check_size("event", idx, size, 2)<0)
      return -1;

    sev_id=buf[idx++]; // IS id
    sev_size=buf[idx++]; // size of subevent

    // and we need sev_size words
    if (check_size("event", idx, size, sev_size)<0)
      return -1;

    // parse subevent
    if ( ParseSubevent(buf+idx, sev_size, sev_id) < 0 )
      return -1;

    idx+=sev_size;
  }

  if (idx!=size) {
    LOG_S(ERROR)<<"parse_events: size="<<size<<", used words="<<idx;
    return -1;
  }

  // TODO statistics
  fStatistics.subevents+=nr_sev;

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

  if ( it->second->DoUnpack(buf, size) < 0 )
    return -1;

  return 0;
}

Bool_t KoaEmsSource::Close()
{
  
}

Bool_t KoaEmsSource::ReInitUnpackers()
{
  
}

Bool_t KoaEmsSource::Reset()
{
  
}
