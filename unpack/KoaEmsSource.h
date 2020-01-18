#ifndef KOA_EMS_SOURCE_H
#define KOA_EMS_SOURCE_H

#include "FairSource.h"
#include "FairLogger.h"
#include "ems_interface.h"
#include <map>
#include "stdio.h"

class KoaUnpack;
class KoaRawEventAnalyzer;
class KoaEventAssembler;

class KoaEmsSource : public FairSource
{
 public:
  KoaEmsSource() : fInput(-1) {}
  KoaEmsSource(const KoaEmsSource& source);
  virtual ~KoaEmsSource();

  virtual Source_Type GetSourceType() { return kONLINE; }

  // setup input file descriptor: ordaniry file or network socket
  virtual Bool_t SetupInput(const char* filename) = 0;
  
  virtual Bool_t Init();
  virtual Int_t ReadEvent(UInt_t=0);// return value: 0: success, 1: end of file, 2: current event not useful skip to next event
  virtual void Close(); // finish jobs at the end of run

  virtual void Reset(); // invoked at the beginning of each readevent

  virtual void SetParUnpackers();
  virtual Bool_t InitUnpackers();
  virtual Bool_t ReInitUnpackers();

  void AddUnpacker(ems_u32 is_id, KoaUnpack* unpacker) {
    auto search = fUnpackers.find(is_id);
    if ( search != fUnpackers.end() ) {
      LOG(error) << "KoaEmsSource::AddUnpacker : Unpacker with IS Id " << is_id << " already exists!";
      return;
    }

    fUnpackers.emplace(is_id, unpacker);
  }

  const KoaUnpack* GetUnpacker(ems_u32 is_id) {
    auto search = fUnpackers.find(is_id);
    if ( search == fUnpackers.end() ) {
      LOG(warn) << "KoaEmsSource::GetUnpacker : Unpacker with IS Id " << is_id << " not found";
      return nullptr;
    }
    else{
      return search->second;
    }
  }

  void SetAssembler(KoaEventAssembler* assembler) {
    if (fAssembler) delete fAssembler;
    fAssembler = assembler;
  }
  void SetKoaEventAnalyzer(KoaRawEventAnalyzer* analyzer) {
    if (fKoaEvtAnalyzer) delete fKoaEvtAnalyzer;
    fKoaEvtAnalyzer = analyzer;
  }
  void SetEmsEventAnalyzer(KoaRawEventAnalyzer* analyzer) {
    if (fEmsEvtAnalyzer) delete fEmsEvtAnalyzer;
    fEmsEvtAnalyzer = analyzer;
  }

 private:
  KoaEmsSource& operator=(const KoaEmsSource&);

  enum class clustertypes {
    clusterty_events=0,
    clusterty_ved_info=1,
    clusterty_text=2,
    clusterty_wendy_setup=3,
    clusterty_file=4,
    clusterty_async_data=5,
    clusterty_async_data2=6, /* includes mqtt */
    clusterty_no_more_data=0x10000000,
  };

  // read in next cluster and saved in fCluster from input stream
  virtual Int_t NextCluster();
  // decode the cluster data saved in fCluster
  virtual Int_t DecodeCluster();

  // parser function for each segment in the cluster, invoked step by step sequentially by DecodeCluster
  Int_t CheckSize(const char* txt, Int_t idx, Int_t size, Int_t needed)
  {
    if ( size >= idx+needed )
      return 0;

    LOG(ERROR) << txt <<" at idx "<< idx <<" too short: "
               << needed <<" words needed, " << size-idx <<" available";
    return -1;
  }
  Int_t ParseOptions(const ems_u32 *buf, Int_t size);
  Int_t ParseEvents(const ems_u32 *buf, Int_t size);
  Int_t ParseEvent(const ems_u32 *buf, Int_t size);
  Int_t ParseSubevent(const ems_u32 *buf, Int_t size, ems_u32 sev_id);

private:
  ems_cluster fCluster; // buffer containing one raw binary EMS cluster, also in charge of cluster read
  std::map<ems_u32, KoaEmsUnpacker*> fUnpackers; // unpackers for each subevent in EMS

  KoaEventAssembler *fAssembler; // in charge of assemblying modules based on same timestamp
  KoaRawEventAnalyzer  *fKoaEvtAnalyzer; // decoding the module data into detector channel data
  KoaRawEventAnalyzer  *fEmsEvtAnalyzer; // decoding ems data

  int fInput; // posix file descriptor for input stream, disk file or network streaming

  ClassDef(KoaEmsSource, 1)
};
