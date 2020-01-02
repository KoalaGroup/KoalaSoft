#include "FairSource.h"
#include "FairLogger.h"
#include "KoaBufferTemplate.h"
#include "ems_interface.h"

class KoaEmsSource : public FairSource
{
 public:
  KoaEmsSource();
  KoaEmsSource(const KoaEmsSource& source);
  virtual ~KoaEmsSource();

  virtual Source_Type GetSourceType() { return kONLINE; }

  virtual Bool_t Init() = 0;
  virtual Int_t ReadEvent(UInt_t=0) = 0;// return value: 0: success, 1: end of file, 2: current event not useful skip to next event
  virtual void Close() = 0;

  virtual void Reset();

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

  void SetAssembler(KoaEmsAssembler* assembler) {
    if (fAssembler) delete fAssembler;
    fAssembler = assembler;
  }
  void SetAnalyzer(KoaEmsAnalyzer* analyzer) {
    if (fAnalyzer) delete fAnalyzer;
    fAnalyzer = analyzer;
  }

 private:
  KoaEmsSource& operator=(const KoaEmsSource&);

  virtual Int_t NextCluster();
  virtual Int_t DecodeCluster();

  Int_t ParseOptions(const ems_u32 *buf, Int_t size);
  Int_t ParseEvents(const ems_u32 *buf, Int_t size);
  Int_t ParseEvent(const ems_u32 *buf, Int_t size);
  Int_t ParseSubevent(const ems_u32 *buf, Int_t size, ems_u32 sev_id);

private:
  ems_cluster fCluster; // buffer containing one raw binary EMS cluster
  KoaBuffer<KoaDetectorData> fKoalaBuffer; // buffer for assembled detector data
  KoaBuffer<KoaEmsEventData> fEmsEventBuffer; // buffer for ems event data

  std::map<ems_u32, KoaEmsUnpacker*> fUnpackers; // unpackers for each subevent in EMS
  KoaEmsAssembler *fAssembler; // assembler for assemblying modules into koala full event
  KoaEmsAnalyzer  *fAnalyzer; // analyzer for generating some histograms or ch id transforamtion

  TClonesArray *fRecDigis; // output of recoil digits
  TClonesArray *fFwdDigis; // output of fwd digits

  FILE* fInput; // posix file descriptor for input stream, disk file or network streaming

  ClassDef(KoaEmsSource, 1)
};
