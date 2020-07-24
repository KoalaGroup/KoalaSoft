// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_jensdIdetectorsdIrecoildIsimpledIG__KoaSimpleRecDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "KoaRec.h"
#include "KoaRecContFact.h"
#include "KoaRecGeo.h"
#include "KoaRecGeoPar.h"
#include "KoaRecMisalignPar.h"
#include "KoaRecPoint.h"
#include "KoaRecDigi.h"
#include "KoaRecDigitizationIdeal.h"
#include "KoaRecChargeDivisionIdeal.h"
#include "KoaRecAddNoise.h"
#include "KoaRecNoisePar.h"
#include "KoaRecAddFano.h"
#include "KoaRecFanoPar.h"
#include "KoaRecChargeCollection.h"
#include "KoaRecChargeCollectionPar.h"
#include "KoaRecAddTimeWalk.h"
#include "KoaRecTimeWalkPar.h"
#include "KoaRecAddTimeJitter.h"
#include "KoaRecTimeJitterPar.h"
#include "KoaRecCluster.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_KoaRec(void *p = 0);
   static void *newArray_KoaRec(Long_t size, void *p);
   static void delete_KoaRec(void *p);
   static void deleteArray_KoaRec(void *p);
   static void destruct_KoaRec(void *p);
   static void streamer_KoaRec(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRec*)
   {
      ::KoaRec *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRec >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRec", ::KoaRec::Class_Version(), "", 28,
                  typeid(::KoaRec), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRec::Dictionary, isa_proxy, 16,
                  sizeof(::KoaRec) );
      instance.SetNew(&new_KoaRec);
      instance.SetNewArray(&newArray_KoaRec);
      instance.SetDelete(&delete_KoaRec);
      instance.SetDeleteArray(&deleteArray_KoaRec);
      instance.SetDestructor(&destruct_KoaRec);
      instance.SetStreamerFunc(&streamer_KoaRec);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRec*)
   {
      return GenerateInitInstanceLocal((::KoaRec*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRec*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecContFact(void *p = 0);
   static void *newArray_KoaRecContFact(Long_t size, void *p);
   static void delete_KoaRecContFact(void *p);
   static void deleteArray_KoaRecContFact(void *p);
   static void destruct_KoaRecContFact(void *p);
   static void streamer_KoaRecContFact(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecContFact*)
   {
      ::KoaRecContFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecContFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecContFact", ::KoaRecContFact::Class_Version(), "", 167,
                  typeid(::KoaRecContFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecContFact::Dictionary, isa_proxy, 16,
                  sizeof(::KoaRecContFact) );
      instance.SetNew(&new_KoaRecContFact);
      instance.SetNewArray(&newArray_KoaRecContFact);
      instance.SetDelete(&delete_KoaRecContFact);
      instance.SetDeleteArray(&deleteArray_KoaRecContFact);
      instance.SetDestructor(&destruct_KoaRecContFact);
      instance.SetStreamerFunc(&streamer_KoaRecContFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecContFact*)
   {
      return GenerateInitInstanceLocal((::KoaRecContFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecContFact*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecGeo(void *p = 0);
   static void *newArray_KoaRecGeo(Long_t size, void *p);
   static void delete_KoaRecGeo(void *p);
   static void deleteArray_KoaRecGeo(void *p);
   static void destruct_KoaRecGeo(void *p);
   static void streamer_KoaRecGeo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecGeo*)
   {
      ::KoaRecGeo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecGeo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecGeo", ::KoaRecGeo::Class_Version(), "", 192,
                  typeid(::KoaRecGeo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecGeo::Dictionary, isa_proxy, 16,
                  sizeof(::KoaRecGeo) );
      instance.SetNew(&new_KoaRecGeo);
      instance.SetNewArray(&newArray_KoaRecGeo);
      instance.SetDelete(&delete_KoaRecGeo);
      instance.SetDeleteArray(&deleteArray_KoaRecGeo);
      instance.SetDestructor(&destruct_KoaRecGeo);
      instance.SetStreamerFunc(&streamer_KoaRecGeo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecGeo*)
   {
      return GenerateInitInstanceLocal((::KoaRecGeo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecGeo*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecGeoPar(void *p = 0);
   static void *newArray_KoaRecGeoPar(Long_t size, void *p);
   static void delete_KoaRecGeoPar(void *p);
   static void deleteArray_KoaRecGeoPar(void *p);
   static void destruct_KoaRecGeoPar(void *p);
   static void streamer_KoaRecGeoPar(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecGeoPar*)
   {
      ::KoaRecGeoPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecGeoPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecGeoPar", ::KoaRecGeoPar::Class_Version(), "", 234,
                  typeid(::KoaRecGeoPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecGeoPar::Dictionary, isa_proxy, 16,
                  sizeof(::KoaRecGeoPar) );
      instance.SetNew(&new_KoaRecGeoPar);
      instance.SetNewArray(&newArray_KoaRecGeoPar);
      instance.SetDelete(&delete_KoaRecGeoPar);
      instance.SetDeleteArray(&deleteArray_KoaRecGeoPar);
      instance.SetDestructor(&destruct_KoaRecGeoPar);
      instance.SetStreamerFunc(&streamer_KoaRecGeoPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecGeoPar*)
   {
      return GenerateInitInstanceLocal((::KoaRecGeoPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecGeoPar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecMisalignPar(void *p = 0);
   static void *newArray_KoaRecMisalignPar(Long_t size, void *p);
   static void delete_KoaRecMisalignPar(void *p);
   static void deleteArray_KoaRecMisalignPar(void *p);
   static void destruct_KoaRecMisalignPar(void *p);
   static void streamer_KoaRecMisalignPar(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecMisalignPar*)
   {
      ::KoaRecMisalignPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecMisalignPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecMisalignPar", ::KoaRecMisalignPar::Class_Version(), "", 281,
                  typeid(::KoaRecMisalignPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecMisalignPar::Dictionary, isa_proxy, 16,
                  sizeof(::KoaRecMisalignPar) );
      instance.SetNew(&new_KoaRecMisalignPar);
      instance.SetNewArray(&newArray_KoaRecMisalignPar);
      instance.SetDelete(&delete_KoaRecMisalignPar);
      instance.SetDeleteArray(&deleteArray_KoaRecMisalignPar);
      instance.SetDestructor(&destruct_KoaRecMisalignPar);
      instance.SetStreamerFunc(&streamer_KoaRecMisalignPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecMisalignPar*)
   {
      return GenerateInitInstanceLocal((::KoaRecMisalignPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecMisalignPar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecPoint(void *p = 0);
   static void *newArray_KoaRecPoint(Long_t size, void *p);
   static void delete_KoaRecPoint(void *p);
   static void deleteArray_KoaRecPoint(void *p);
   static void destruct_KoaRecPoint(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecPoint*)
   {
      ::KoaRecPoint *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecPoint >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecPoint", ::KoaRecPoint::Class_Version(), "", 335,
                  typeid(::KoaRecPoint), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecPoint::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecPoint) );
      instance.SetNew(&new_KoaRecPoint);
      instance.SetNewArray(&newArray_KoaRecPoint);
      instance.SetDelete(&delete_KoaRecPoint);
      instance.SetDeleteArray(&deleteArray_KoaRecPoint);
      instance.SetDestructor(&destruct_KoaRecPoint);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecPoint*)
   {
      return GenerateInitInstanceLocal((::KoaRecPoint*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecPoint*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecDigi(void *p = 0);
   static void *newArray_KoaRecDigi(Long_t size, void *p);
   static void delete_KoaRecDigi(void *p);
   static void deleteArray_KoaRecDigi(void *p);
   static void destruct_KoaRecDigi(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecDigi*)
   {
      ::KoaRecDigi *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecDigi >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecDigi", ::KoaRecDigi::Class_Version(), "", 430,
                  typeid(::KoaRecDigi), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecDigi::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecDigi) );
      instance.SetNew(&new_KoaRecDigi);
      instance.SetNewArray(&newArray_KoaRecDigi);
      instance.SetDelete(&delete_KoaRecDigi);
      instance.SetDeleteArray(&deleteArray_KoaRecDigi);
      instance.SetDestructor(&destruct_KoaRecDigi);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecDigi*)
   {
      return GenerateInitInstanceLocal((::KoaRecDigi*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecDigi*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecDigitizationIdeal(void *p = 0);
   static void *newArray_KoaRecDigitizationIdeal(Long_t size, void *p);
   static void delete_KoaRecDigitizationIdeal(void *p);
   static void deleteArray_KoaRecDigitizationIdeal(void *p);
   static void destruct_KoaRecDigitizationIdeal(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecDigitizationIdeal*)
   {
      ::KoaRecDigitizationIdeal *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecDigitizationIdeal >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecDigitizationIdeal", ::KoaRecDigitizationIdeal::Class_Version(), "", 524,
                  typeid(::KoaRecDigitizationIdeal), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecDigitizationIdeal::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecDigitizationIdeal) );
      instance.SetNew(&new_KoaRecDigitizationIdeal);
      instance.SetNewArray(&newArray_KoaRecDigitizationIdeal);
      instance.SetDelete(&delete_KoaRecDigitizationIdeal);
      instance.SetDeleteArray(&deleteArray_KoaRecDigitizationIdeal);
      instance.SetDestructor(&destruct_KoaRecDigitizationIdeal);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecDigitizationIdeal*)
   {
      return GenerateInitInstanceLocal((::KoaRecDigitizationIdeal*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecDigitizationIdeal*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecChargeDivisionIdeal(void *p = 0);
   static void *newArray_KoaRecChargeDivisionIdeal(Long_t size, void *p);
   static void delete_KoaRecChargeDivisionIdeal(void *p);
   static void deleteArray_KoaRecChargeDivisionIdeal(void *p);
   static void destruct_KoaRecChargeDivisionIdeal(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecChargeDivisionIdeal*)
   {
      ::KoaRecChargeDivisionIdeal *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecChargeDivisionIdeal >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecChargeDivisionIdeal", ::KoaRecChargeDivisionIdeal::Class_Version(), "", 609,
                  typeid(::KoaRecChargeDivisionIdeal), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecChargeDivisionIdeal::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecChargeDivisionIdeal) );
      instance.SetNew(&new_KoaRecChargeDivisionIdeal);
      instance.SetNewArray(&newArray_KoaRecChargeDivisionIdeal);
      instance.SetDelete(&delete_KoaRecChargeDivisionIdeal);
      instance.SetDeleteArray(&deleteArray_KoaRecChargeDivisionIdeal);
      instance.SetDestructor(&destruct_KoaRecChargeDivisionIdeal);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecChargeDivisionIdeal*)
   {
      return GenerateInitInstanceLocal((::KoaRecChargeDivisionIdeal*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecChargeDivisionIdeal*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecAddNoise(void *p = 0);
   static void *newArray_KoaRecAddNoise(Long_t size, void *p);
   static void delete_KoaRecAddNoise(void *p);
   static void deleteArray_KoaRecAddNoise(void *p);
   static void destruct_KoaRecAddNoise(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecAddNoise*)
   {
      ::KoaRecAddNoise *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecAddNoise >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecAddNoise", ::KoaRecAddNoise::Class_Version(), "", 706,
                  typeid(::KoaRecAddNoise), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecAddNoise::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecAddNoise) );
      instance.SetNew(&new_KoaRecAddNoise);
      instance.SetNewArray(&newArray_KoaRecAddNoise);
      instance.SetDelete(&delete_KoaRecAddNoise);
      instance.SetDeleteArray(&deleteArray_KoaRecAddNoise);
      instance.SetDestructor(&destruct_KoaRecAddNoise);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecAddNoise*)
   {
      return GenerateInitInstanceLocal((::KoaRecAddNoise*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecAddNoise*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecNoisePar(void *p = 0);
   static void *newArray_KoaRecNoisePar(Long_t size, void *p);
   static void delete_KoaRecNoisePar(void *p);
   static void deleteArray_KoaRecNoisePar(void *p);
   static void destruct_KoaRecNoisePar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecNoisePar*)
   {
      ::KoaRecNoisePar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecNoisePar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecNoisePar", ::KoaRecNoisePar::Class_Version(), "", 795,
                  typeid(::KoaRecNoisePar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecNoisePar::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecNoisePar) );
      instance.SetNew(&new_KoaRecNoisePar);
      instance.SetNewArray(&newArray_KoaRecNoisePar);
      instance.SetDelete(&delete_KoaRecNoisePar);
      instance.SetDeleteArray(&deleteArray_KoaRecNoisePar);
      instance.SetDestructor(&destruct_KoaRecNoisePar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecNoisePar*)
   {
      return GenerateInitInstanceLocal((::KoaRecNoisePar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecNoisePar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecAddFano(void *p = 0);
   static void *newArray_KoaRecAddFano(Long_t size, void *p);
   static void delete_KoaRecAddFano(void *p);
   static void deleteArray_KoaRecAddFano(void *p);
   static void destruct_KoaRecAddFano(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecAddFano*)
   {
      ::KoaRecAddFano *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecAddFano >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecAddFano", ::KoaRecAddFano::Class_Version(), "", 848,
                  typeid(::KoaRecAddFano), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecAddFano::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecAddFano) );
      instance.SetNew(&new_KoaRecAddFano);
      instance.SetNewArray(&newArray_KoaRecAddFano);
      instance.SetDelete(&delete_KoaRecAddFano);
      instance.SetDeleteArray(&deleteArray_KoaRecAddFano);
      instance.SetDestructor(&destruct_KoaRecAddFano);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecAddFano*)
   {
      return GenerateInitInstanceLocal((::KoaRecAddFano*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecAddFano*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecFanoPar(void *p = 0);
   static void *newArray_KoaRecFanoPar(Long_t size, void *p);
   static void delete_KoaRecFanoPar(void *p);
   static void deleteArray_KoaRecFanoPar(void *p);
   static void destruct_KoaRecFanoPar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecFanoPar*)
   {
      ::KoaRecFanoPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecFanoPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecFanoPar", ::KoaRecFanoPar::Class_Version(), "", 938,
                  typeid(::KoaRecFanoPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecFanoPar::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecFanoPar) );
      instance.SetNew(&new_KoaRecFanoPar);
      instance.SetNewArray(&newArray_KoaRecFanoPar);
      instance.SetDelete(&delete_KoaRecFanoPar);
      instance.SetDeleteArray(&deleteArray_KoaRecFanoPar);
      instance.SetDestructor(&destruct_KoaRecFanoPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecFanoPar*)
   {
      return GenerateInitInstanceLocal((::KoaRecFanoPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecFanoPar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecChargeCollection(void *p = 0);
   static void *newArray_KoaRecChargeCollection(Long_t size, void *p);
   static void delete_KoaRecChargeCollection(void *p);
   static void deleteArray_KoaRecChargeCollection(void *p);
   static void destruct_KoaRecChargeCollection(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecChargeCollection*)
   {
      ::KoaRecChargeCollection *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecChargeCollection >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecChargeCollection", ::KoaRecChargeCollection::Class_Version(), "", 994,
                  typeid(::KoaRecChargeCollection), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecChargeCollection::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecChargeCollection) );
      instance.SetNew(&new_KoaRecChargeCollection);
      instance.SetNewArray(&newArray_KoaRecChargeCollection);
      instance.SetDelete(&delete_KoaRecChargeCollection);
      instance.SetDeleteArray(&deleteArray_KoaRecChargeCollection);
      instance.SetDestructor(&destruct_KoaRecChargeCollection);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecChargeCollection*)
   {
      return GenerateInitInstanceLocal((::KoaRecChargeCollection*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecChargeCollection*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecChargeCollectionPar(void *p = 0);
   static void *newArray_KoaRecChargeCollectionPar(Long_t size, void *p);
   static void delete_KoaRecChargeCollectionPar(void *p);
   static void deleteArray_KoaRecChargeCollectionPar(void *p);
   static void destruct_KoaRecChargeCollectionPar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecChargeCollectionPar*)
   {
      ::KoaRecChargeCollectionPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecChargeCollectionPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecChargeCollectionPar", ::KoaRecChargeCollectionPar::Class_Version(), "", 1085,
                  typeid(::KoaRecChargeCollectionPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecChargeCollectionPar::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecChargeCollectionPar) );
      instance.SetNew(&new_KoaRecChargeCollectionPar);
      instance.SetNewArray(&newArray_KoaRecChargeCollectionPar);
      instance.SetDelete(&delete_KoaRecChargeCollectionPar);
      instance.SetDeleteArray(&deleteArray_KoaRecChargeCollectionPar);
      instance.SetDestructor(&destruct_KoaRecChargeCollectionPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecChargeCollectionPar*)
   {
      return GenerateInitInstanceLocal((::KoaRecChargeCollectionPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecChargeCollectionPar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecAddTimeWalk(void *p = 0);
   static void *newArray_KoaRecAddTimeWalk(Long_t size, void *p);
   static void delete_KoaRecAddTimeWalk(void *p);
   static void deleteArray_KoaRecAddTimeWalk(void *p);
   static void destruct_KoaRecAddTimeWalk(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecAddTimeWalk*)
   {
      ::KoaRecAddTimeWalk *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecAddTimeWalk >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecAddTimeWalk", ::KoaRecAddTimeWalk::Class_Version(), "", 1140,
                  typeid(::KoaRecAddTimeWalk), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecAddTimeWalk::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecAddTimeWalk) );
      instance.SetNew(&new_KoaRecAddTimeWalk);
      instance.SetNewArray(&newArray_KoaRecAddTimeWalk);
      instance.SetDelete(&delete_KoaRecAddTimeWalk);
      instance.SetDeleteArray(&deleteArray_KoaRecAddTimeWalk);
      instance.SetDestructor(&destruct_KoaRecAddTimeWalk);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecAddTimeWalk*)
   {
      return GenerateInitInstanceLocal((::KoaRecAddTimeWalk*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecAddTimeWalk*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecTimeWalkPar(void *p = 0);
   static void *newArray_KoaRecTimeWalkPar(Long_t size, void *p);
   static void delete_KoaRecTimeWalkPar(void *p);
   static void deleteArray_KoaRecTimeWalkPar(void *p);
   static void destruct_KoaRecTimeWalkPar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecTimeWalkPar*)
   {
      ::KoaRecTimeWalkPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecTimeWalkPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecTimeWalkPar", ::KoaRecTimeWalkPar::Class_Version(), "", 1228,
                  typeid(::KoaRecTimeWalkPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecTimeWalkPar::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecTimeWalkPar) );
      instance.SetNew(&new_KoaRecTimeWalkPar);
      instance.SetNewArray(&newArray_KoaRecTimeWalkPar);
      instance.SetDelete(&delete_KoaRecTimeWalkPar);
      instance.SetDeleteArray(&deleteArray_KoaRecTimeWalkPar);
      instance.SetDestructor(&destruct_KoaRecTimeWalkPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecTimeWalkPar*)
   {
      return GenerateInitInstanceLocal((::KoaRecTimeWalkPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecTimeWalkPar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecAddTimeJitter(void *p = 0);
   static void *newArray_KoaRecAddTimeJitter(Long_t size, void *p);
   static void delete_KoaRecAddTimeJitter(void *p);
   static void deleteArray_KoaRecAddTimeJitter(void *p);
   static void destruct_KoaRecAddTimeJitter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecAddTimeJitter*)
   {
      ::KoaRecAddTimeJitter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecAddTimeJitter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecAddTimeJitter", ::KoaRecAddTimeJitter::Class_Version(), "", 1277,
                  typeid(::KoaRecAddTimeJitter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecAddTimeJitter::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecAddTimeJitter) );
      instance.SetNew(&new_KoaRecAddTimeJitter);
      instance.SetNewArray(&newArray_KoaRecAddTimeJitter);
      instance.SetDelete(&delete_KoaRecAddTimeJitter);
      instance.SetDeleteArray(&deleteArray_KoaRecAddTimeJitter);
      instance.SetDestructor(&destruct_KoaRecAddTimeJitter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecAddTimeJitter*)
   {
      return GenerateInitInstanceLocal((::KoaRecAddTimeJitter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecAddTimeJitter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecTimeJitterPar(void *p = 0);
   static void *newArray_KoaRecTimeJitterPar(Long_t size, void *p);
   static void delete_KoaRecTimeJitterPar(void *p);
   static void deleteArray_KoaRecTimeJitterPar(void *p);
   static void destruct_KoaRecTimeJitterPar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecTimeJitterPar*)
   {
      ::KoaRecTimeJitterPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecTimeJitterPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecTimeJitterPar", ::KoaRecTimeJitterPar::Class_Version(), "", 1365,
                  typeid(::KoaRecTimeJitterPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecTimeJitterPar::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecTimeJitterPar) );
      instance.SetNew(&new_KoaRecTimeJitterPar);
      instance.SetNewArray(&newArray_KoaRecTimeJitterPar);
      instance.SetDelete(&delete_KoaRecTimeJitterPar);
      instance.SetDeleteArray(&deleteArray_KoaRecTimeJitterPar);
      instance.SetDestructor(&destruct_KoaRecTimeJitterPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecTimeJitterPar*)
   {
      return GenerateInitInstanceLocal((::KoaRecTimeJitterPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecTimeJitterPar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecCluster(void *p = 0);
   static void *newArray_KoaRecCluster(Long_t size, void *p);
   static void delete_KoaRecCluster(void *p);
   static void deleteArray_KoaRecCluster(void *p);
   static void destruct_KoaRecCluster(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecCluster*)
   {
      ::KoaRecCluster *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecCluster >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecCluster", ::KoaRecCluster::Class_Version(), "", 1415,
                  typeid(::KoaRecCluster), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecCluster::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecCluster) );
      instance.SetNew(&new_KoaRecCluster);
      instance.SetNewArray(&newArray_KoaRecCluster);
      instance.SetDelete(&delete_KoaRecCluster);
      instance.SetDeleteArray(&deleteArray_KoaRecCluster);
      instance.SetDestructor(&destruct_KoaRecCluster);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecCluster*)
   {
      return GenerateInitInstanceLocal((::KoaRecCluster*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecCluster*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr KoaRec::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRec::Class_Name()
{
   return "KoaRec";
}

//______________________________________________________________________________
const char *KoaRec::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRec*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRec::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRec*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRec::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRec*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRec::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRec*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecContFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecContFact::Class_Name()
{
   return "KoaRecContFact";
}

//______________________________________________________________________________
const char *KoaRecContFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecContFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecContFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecContFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecContFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecContFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecContFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecContFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecGeo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecGeo::Class_Name()
{
   return "KoaRecGeo";
}

//______________________________________________________________________________
const char *KoaRecGeo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecGeo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecGeo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecGeo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecGeo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecGeo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecGeo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecGeo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecGeoPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecGeoPar::Class_Name()
{
   return "KoaRecGeoPar";
}

//______________________________________________________________________________
const char *KoaRecGeoPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecGeoPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecGeoPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecGeoPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecGeoPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecGeoPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecGeoPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecGeoPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecMisalignPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecMisalignPar::Class_Name()
{
   return "KoaRecMisalignPar";
}

//______________________________________________________________________________
const char *KoaRecMisalignPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecMisalignPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecMisalignPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecMisalignPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecMisalignPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecMisalignPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecMisalignPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecMisalignPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecPoint::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecPoint::Class_Name()
{
   return "KoaRecPoint";
}

//______________________________________________________________________________
const char *KoaRecPoint::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecPoint*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecPoint::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecPoint*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecPoint::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecPoint*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecPoint::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecPoint*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecDigi::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecDigi::Class_Name()
{
   return "KoaRecDigi";
}

//______________________________________________________________________________
const char *KoaRecDigi::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecDigi*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecDigi::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecDigi*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecDigi::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecDigi*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecDigi::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecDigi*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecDigitizationIdeal::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecDigitizationIdeal::Class_Name()
{
   return "KoaRecDigitizationIdeal";
}

//______________________________________________________________________________
const char *KoaRecDigitizationIdeal::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecDigitizationIdeal*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecDigitizationIdeal::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecDigitizationIdeal*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecDigitizationIdeal::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecDigitizationIdeal*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecDigitizationIdeal::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecDigitizationIdeal*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecChargeDivisionIdeal::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecChargeDivisionIdeal::Class_Name()
{
   return "KoaRecChargeDivisionIdeal";
}

//______________________________________________________________________________
const char *KoaRecChargeDivisionIdeal::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecChargeDivisionIdeal*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecChargeDivisionIdeal::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecChargeDivisionIdeal*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecChargeDivisionIdeal::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecChargeDivisionIdeal*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecChargeDivisionIdeal::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecChargeDivisionIdeal*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecAddNoise::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecAddNoise::Class_Name()
{
   return "KoaRecAddNoise";
}

//______________________________________________________________________________
const char *KoaRecAddNoise::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddNoise*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecAddNoise::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddNoise*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecAddNoise::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddNoise*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecAddNoise::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddNoise*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecNoisePar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecNoisePar::Class_Name()
{
   return "KoaRecNoisePar";
}

//______________________________________________________________________________
const char *KoaRecNoisePar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecNoisePar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecNoisePar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecNoisePar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecNoisePar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecNoisePar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecNoisePar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecNoisePar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecAddFano::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecAddFano::Class_Name()
{
   return "KoaRecAddFano";
}

//______________________________________________________________________________
const char *KoaRecAddFano::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddFano*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecAddFano::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddFano*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecAddFano::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddFano*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecAddFano::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddFano*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecFanoPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecFanoPar::Class_Name()
{
   return "KoaRecFanoPar";
}

//______________________________________________________________________________
const char *KoaRecFanoPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecFanoPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecFanoPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecFanoPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecFanoPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecFanoPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecFanoPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecFanoPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecChargeCollection::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecChargeCollection::Class_Name()
{
   return "KoaRecChargeCollection";
}

//______________________________________________________________________________
const char *KoaRecChargeCollection::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecChargeCollection*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecChargeCollection::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecChargeCollection*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecChargeCollection::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecChargeCollection*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecChargeCollection::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecChargeCollection*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecChargeCollectionPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecChargeCollectionPar::Class_Name()
{
   return "KoaRecChargeCollectionPar";
}

//______________________________________________________________________________
const char *KoaRecChargeCollectionPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecChargeCollectionPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecChargeCollectionPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecChargeCollectionPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecChargeCollectionPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecChargeCollectionPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecChargeCollectionPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecChargeCollectionPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecAddTimeWalk::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecAddTimeWalk::Class_Name()
{
   return "KoaRecAddTimeWalk";
}

//______________________________________________________________________________
const char *KoaRecAddTimeWalk::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddTimeWalk*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecAddTimeWalk::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddTimeWalk*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecAddTimeWalk::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddTimeWalk*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecAddTimeWalk::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddTimeWalk*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecTimeWalkPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecTimeWalkPar::Class_Name()
{
   return "KoaRecTimeWalkPar";
}

//______________________________________________________________________________
const char *KoaRecTimeWalkPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeWalkPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecTimeWalkPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeWalkPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecTimeWalkPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeWalkPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecTimeWalkPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeWalkPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecAddTimeJitter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecAddTimeJitter::Class_Name()
{
   return "KoaRecAddTimeJitter";
}

//______________________________________________________________________________
const char *KoaRecAddTimeJitter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddTimeJitter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecAddTimeJitter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddTimeJitter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecAddTimeJitter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddTimeJitter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecAddTimeJitter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecAddTimeJitter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecTimeJitterPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecTimeJitterPar::Class_Name()
{
   return "KoaRecTimeJitterPar";
}

//______________________________________________________________________________
const char *KoaRecTimeJitterPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeJitterPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecTimeJitterPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeJitterPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecTimeJitterPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeJitterPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecTimeJitterPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeJitterPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecCluster::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecCluster::Class_Name()
{
   return "KoaRecCluster";
}

//______________________________________________________________________________
const char *KoaRecCluster::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecCluster*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecCluster::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecCluster*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecCluster::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecCluster*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecCluster::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecCluster*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void KoaRec::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRec.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairDetector::Streamer(R__b);
      {
         vector<string> &R__stl =  fListOfSensitives;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            string R__t;
            {TString R__str;
             R__str.Streamer(R__b);
             R__t = R__str.Data();}
            R__stl.push_back(R__t);
         }
      }
      R__b >> fModifyGeometry;
      R__b >> fMisalignPar;
      R__b >> fNrOfSensors;
      fSensorShiftX.Streamer(R__b);
      fSensorShiftY.Streamer(R__b);
      fSensorShiftZ.Streamer(R__b);
      fSensorRotPhi.Streamer(R__b);
      fSensorRotTheta.Streamer(R__b);
      fSensorRotPsi.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, KoaRec::IsA());
   } else {
      R__c = R__b.WriteVersion(KoaRec::IsA(), kTRUE);
      FairDetector::Streamer(R__b);
      {
         vector<string> &R__stl =  fListOfSensitives;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<string>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            {TString R__str((*R__k).c_str());
             R__str.Streamer(R__b);};
            }
         }
      }
      R__b << fModifyGeometry;
      R__b << fMisalignPar;
      R__b << fNrOfSensors;
      fSensorShiftX.Streamer(R__b);
      fSensorShiftY.Streamer(R__b);
      fSensorShiftZ.Streamer(R__b);
      fSensorRotPhi.Streamer(R__b);
      fSensorRotTheta.Streamer(R__b);
      fSensorRotPsi.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRec(void *p) {
      return  p ? new(p) ::KoaRec : new ::KoaRec;
   }
   static void *newArray_KoaRec(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRec[nElements] : new ::KoaRec[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRec(void *p) {
      delete ((::KoaRec*)p);
   }
   static void deleteArray_KoaRec(void *p) {
      delete [] ((::KoaRec*)p);
   }
   static void destruct_KoaRec(void *p) {
      typedef ::KoaRec current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_KoaRec(TBuffer &buf, void *obj) {
      ((::KoaRec*)obj)->::KoaRec::Streamer(buf);
   }
} // end of namespace ROOT for class ::KoaRec

//______________________________________________________________________________
void KoaRecContFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecContFact.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairContFact::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, KoaRecContFact::IsA());
   } else {
      R__c = R__b.WriteVersion(KoaRecContFact::IsA(), kTRUE);
      FairContFact::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecContFact(void *p) {
      return  p ? new(p) ::KoaRecContFact : new ::KoaRecContFact;
   }
   static void *newArray_KoaRecContFact(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecContFact[nElements] : new ::KoaRecContFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecContFact(void *p) {
      delete ((::KoaRecContFact*)p);
   }
   static void deleteArray_KoaRecContFact(void *p) {
      delete [] ((::KoaRecContFact*)p);
   }
   static void destruct_KoaRecContFact(void *p) {
      typedef ::KoaRecContFact current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_KoaRecContFact(TBuffer &buf, void *obj) {
      ((::KoaRecContFact*)obj)->::KoaRecContFact::Streamer(buf);
   }
} // end of namespace ROOT for class ::KoaRecContFact

//______________________________________________________________________________
void KoaRecGeo::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecGeo.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairGeoSet::Streamer(R__b);
      R__b.ReadStaticArray((char*)modName);
      R__b.ReadStaticArray((char*)eleName);
      R__b.CheckByteCount(R__s, R__c, KoaRecGeo::IsA());
   } else {
      R__c = R__b.WriteVersion(KoaRecGeo::IsA(), kTRUE);
      FairGeoSet::Streamer(R__b);
      R__b.WriteArray(modName, 20);
      R__b.WriteArray(eleName, 20);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecGeo(void *p) {
      return  p ? new(p) ::KoaRecGeo : new ::KoaRecGeo;
   }
   static void *newArray_KoaRecGeo(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecGeo[nElements] : new ::KoaRecGeo[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecGeo(void *p) {
      delete ((::KoaRecGeo*)p);
   }
   static void deleteArray_KoaRecGeo(void *p) {
      delete [] ((::KoaRecGeo*)p);
   }
   static void destruct_KoaRecGeo(void *p) {
      typedef ::KoaRecGeo current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_KoaRecGeo(TBuffer &buf, void *obj) {
      ((::KoaRecGeo*)obj)->::KoaRecGeo::Streamer(buf);
   }
} // end of namespace ROOT for class ::KoaRecGeo

//______________________________________________________________________________
void KoaRecGeoPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecGeoPar.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairParGenericSet::Streamer(R__b);
      R__b >> fGeoSensNodes;
      R__b >> fGeoPassNodes;
      R__b.CheckByteCount(R__s, R__c, KoaRecGeoPar::IsA());
   } else {
      R__c = R__b.WriteVersion(KoaRecGeoPar::IsA(), kTRUE);
      FairParGenericSet::Streamer(R__b);
      R__b << fGeoSensNodes;
      R__b << fGeoPassNodes;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecGeoPar(void *p) {
      return  p ? new(p) ::KoaRecGeoPar : new ::KoaRecGeoPar;
   }
   static void *newArray_KoaRecGeoPar(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecGeoPar[nElements] : new ::KoaRecGeoPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecGeoPar(void *p) {
      delete ((::KoaRecGeoPar*)p);
   }
   static void deleteArray_KoaRecGeoPar(void *p) {
      delete [] ((::KoaRecGeoPar*)p);
   }
   static void destruct_KoaRecGeoPar(void *p) {
      typedef ::KoaRecGeoPar current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_KoaRecGeoPar(TBuffer &buf, void *obj) {
      ((::KoaRecGeoPar*)obj)->::KoaRecGeoPar::Streamer(buf);
   }
} // end of namespace ROOT for class ::KoaRecGeoPar

//______________________________________________________________________________
void KoaRecMisalignPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecMisalignPar.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairParGenericSet::Streamer(R__b);
      R__b >> fNrOfSensors;
      fSensorShiftX.Streamer(R__b);
      fSensorShiftY.Streamer(R__b);
      fSensorShiftZ.Streamer(R__b);
      fSensorRotPhi.Streamer(R__b);
      fSensorRotTheta.Streamer(R__b);
      fSensorRotPsi.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, KoaRecMisalignPar::IsA());
   } else {
      R__c = R__b.WriteVersion(KoaRecMisalignPar::IsA(), kTRUE);
      FairParGenericSet::Streamer(R__b);
      R__b << fNrOfSensors;
      fSensorShiftX.Streamer(R__b);
      fSensorShiftY.Streamer(R__b);
      fSensorShiftZ.Streamer(R__b);
      fSensorRotPhi.Streamer(R__b);
      fSensorRotTheta.Streamer(R__b);
      fSensorRotPsi.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecMisalignPar(void *p) {
      return  p ? new(p) ::KoaRecMisalignPar : new ::KoaRecMisalignPar;
   }
   static void *newArray_KoaRecMisalignPar(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecMisalignPar[nElements] : new ::KoaRecMisalignPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecMisalignPar(void *p) {
      delete ((::KoaRecMisalignPar*)p);
   }
   static void deleteArray_KoaRecMisalignPar(void *p) {
      delete [] ((::KoaRecMisalignPar*)p);
   }
   static void destruct_KoaRecMisalignPar(void *p) {
      typedef ::KoaRecMisalignPar current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_KoaRecMisalignPar(TBuffer &buf, void *obj) {
      ((::KoaRecMisalignPar*)obj)->::KoaRecMisalignPar::Streamer(buf);
   }
} // end of namespace ROOT for class ::KoaRecMisalignPar

//______________________________________________________________________________
void KoaRecPoint::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecPoint.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecPoint::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecPoint::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecPoint(void *p) {
      return  p ? new(p) ::KoaRecPoint : new ::KoaRecPoint;
   }
   static void *newArray_KoaRecPoint(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecPoint[nElements] : new ::KoaRecPoint[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecPoint(void *p) {
      delete ((::KoaRecPoint*)p);
   }
   static void deleteArray_KoaRecPoint(void *p) {
      delete [] ((::KoaRecPoint*)p);
   }
   static void destruct_KoaRecPoint(void *p) {
      typedef ::KoaRecPoint current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecPoint

//______________________________________________________________________________
void KoaRecDigi::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecDigi.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecDigi::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecDigi::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecDigi(void *p) {
      return  p ? new(p) ::KoaRecDigi : new ::KoaRecDigi;
   }
   static void *newArray_KoaRecDigi(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecDigi[nElements] : new ::KoaRecDigi[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecDigi(void *p) {
      delete ((::KoaRecDigi*)p);
   }
   static void deleteArray_KoaRecDigi(void *p) {
      delete [] ((::KoaRecDigi*)p);
   }
   static void destruct_KoaRecDigi(void *p) {
      typedef ::KoaRecDigi current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecDigi

//______________________________________________________________________________
void KoaRecDigitizationIdeal::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecDigitizationIdeal.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecDigitizationIdeal::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecDigitizationIdeal::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecDigitizationIdeal(void *p) {
      return  p ? new(p) ::KoaRecDigitizationIdeal : new ::KoaRecDigitizationIdeal;
   }
   static void *newArray_KoaRecDigitizationIdeal(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecDigitizationIdeal[nElements] : new ::KoaRecDigitizationIdeal[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecDigitizationIdeal(void *p) {
      delete ((::KoaRecDigitizationIdeal*)p);
   }
   static void deleteArray_KoaRecDigitizationIdeal(void *p) {
      delete [] ((::KoaRecDigitizationIdeal*)p);
   }
   static void destruct_KoaRecDigitizationIdeal(void *p) {
      typedef ::KoaRecDigitizationIdeal current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecDigitizationIdeal

//______________________________________________________________________________
void KoaRecChargeDivisionIdeal::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecChargeDivisionIdeal.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecChargeDivisionIdeal::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecChargeDivisionIdeal::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecChargeDivisionIdeal(void *p) {
      return  p ? new(p) ::KoaRecChargeDivisionIdeal : new ::KoaRecChargeDivisionIdeal;
   }
   static void *newArray_KoaRecChargeDivisionIdeal(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecChargeDivisionIdeal[nElements] : new ::KoaRecChargeDivisionIdeal[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecChargeDivisionIdeal(void *p) {
      delete ((::KoaRecChargeDivisionIdeal*)p);
   }
   static void deleteArray_KoaRecChargeDivisionIdeal(void *p) {
      delete [] ((::KoaRecChargeDivisionIdeal*)p);
   }
   static void destruct_KoaRecChargeDivisionIdeal(void *p) {
      typedef ::KoaRecChargeDivisionIdeal current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecChargeDivisionIdeal

//______________________________________________________________________________
void KoaRecAddNoise::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecAddNoise.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecAddNoise::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecAddNoise::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecAddNoise(void *p) {
      return  p ? new(p) ::KoaRecAddNoise : new ::KoaRecAddNoise;
   }
   static void *newArray_KoaRecAddNoise(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecAddNoise[nElements] : new ::KoaRecAddNoise[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecAddNoise(void *p) {
      delete ((::KoaRecAddNoise*)p);
   }
   static void deleteArray_KoaRecAddNoise(void *p) {
      delete [] ((::KoaRecAddNoise*)p);
   }
   static void destruct_KoaRecAddNoise(void *p) {
      typedef ::KoaRecAddNoise current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecAddNoise

//______________________________________________________________________________
void KoaRecNoisePar::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecNoisePar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecNoisePar::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecNoisePar::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecNoisePar(void *p) {
      return  p ? new(p) ::KoaRecNoisePar : new ::KoaRecNoisePar;
   }
   static void *newArray_KoaRecNoisePar(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecNoisePar[nElements] : new ::KoaRecNoisePar[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecNoisePar(void *p) {
      delete ((::KoaRecNoisePar*)p);
   }
   static void deleteArray_KoaRecNoisePar(void *p) {
      delete [] ((::KoaRecNoisePar*)p);
   }
   static void destruct_KoaRecNoisePar(void *p) {
      typedef ::KoaRecNoisePar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecNoisePar

//______________________________________________________________________________
void KoaRecAddFano::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecAddFano.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecAddFano::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecAddFano::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecAddFano(void *p) {
      return  p ? new(p) ::KoaRecAddFano : new ::KoaRecAddFano;
   }
   static void *newArray_KoaRecAddFano(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecAddFano[nElements] : new ::KoaRecAddFano[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecAddFano(void *p) {
      delete ((::KoaRecAddFano*)p);
   }
   static void deleteArray_KoaRecAddFano(void *p) {
      delete [] ((::KoaRecAddFano*)p);
   }
   static void destruct_KoaRecAddFano(void *p) {
      typedef ::KoaRecAddFano current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecAddFano

//______________________________________________________________________________
void KoaRecFanoPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecFanoPar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecFanoPar::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecFanoPar::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecFanoPar(void *p) {
      return  p ? new(p) ::KoaRecFanoPar : new ::KoaRecFanoPar;
   }
   static void *newArray_KoaRecFanoPar(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecFanoPar[nElements] : new ::KoaRecFanoPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecFanoPar(void *p) {
      delete ((::KoaRecFanoPar*)p);
   }
   static void deleteArray_KoaRecFanoPar(void *p) {
      delete [] ((::KoaRecFanoPar*)p);
   }
   static void destruct_KoaRecFanoPar(void *p) {
      typedef ::KoaRecFanoPar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecFanoPar

//______________________________________________________________________________
void KoaRecChargeCollection::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecChargeCollection.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecChargeCollection::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecChargeCollection::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecChargeCollection(void *p) {
      return  p ? new(p) ::KoaRecChargeCollection : new ::KoaRecChargeCollection;
   }
   static void *newArray_KoaRecChargeCollection(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecChargeCollection[nElements] : new ::KoaRecChargeCollection[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecChargeCollection(void *p) {
      delete ((::KoaRecChargeCollection*)p);
   }
   static void deleteArray_KoaRecChargeCollection(void *p) {
      delete [] ((::KoaRecChargeCollection*)p);
   }
   static void destruct_KoaRecChargeCollection(void *p) {
      typedef ::KoaRecChargeCollection current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecChargeCollection

//______________________________________________________________________________
void KoaRecChargeCollectionPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecChargeCollectionPar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecChargeCollectionPar::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecChargeCollectionPar::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecChargeCollectionPar(void *p) {
      return  p ? new(p) ::KoaRecChargeCollectionPar : new ::KoaRecChargeCollectionPar;
   }
   static void *newArray_KoaRecChargeCollectionPar(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecChargeCollectionPar[nElements] : new ::KoaRecChargeCollectionPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecChargeCollectionPar(void *p) {
      delete ((::KoaRecChargeCollectionPar*)p);
   }
   static void deleteArray_KoaRecChargeCollectionPar(void *p) {
      delete [] ((::KoaRecChargeCollectionPar*)p);
   }
   static void destruct_KoaRecChargeCollectionPar(void *p) {
      typedef ::KoaRecChargeCollectionPar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecChargeCollectionPar

//______________________________________________________________________________
void KoaRecAddTimeWalk::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecAddTimeWalk.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecAddTimeWalk::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecAddTimeWalk::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecAddTimeWalk(void *p) {
      return  p ? new(p) ::KoaRecAddTimeWalk : new ::KoaRecAddTimeWalk;
   }
   static void *newArray_KoaRecAddTimeWalk(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecAddTimeWalk[nElements] : new ::KoaRecAddTimeWalk[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecAddTimeWalk(void *p) {
      delete ((::KoaRecAddTimeWalk*)p);
   }
   static void deleteArray_KoaRecAddTimeWalk(void *p) {
      delete [] ((::KoaRecAddTimeWalk*)p);
   }
   static void destruct_KoaRecAddTimeWalk(void *p) {
      typedef ::KoaRecAddTimeWalk current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecAddTimeWalk

//______________________________________________________________________________
void KoaRecTimeWalkPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecTimeWalkPar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecTimeWalkPar::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecTimeWalkPar::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecTimeWalkPar(void *p) {
      return  p ? new(p) ::KoaRecTimeWalkPar : new ::KoaRecTimeWalkPar;
   }
   static void *newArray_KoaRecTimeWalkPar(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecTimeWalkPar[nElements] : new ::KoaRecTimeWalkPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecTimeWalkPar(void *p) {
      delete ((::KoaRecTimeWalkPar*)p);
   }
   static void deleteArray_KoaRecTimeWalkPar(void *p) {
      delete [] ((::KoaRecTimeWalkPar*)p);
   }
   static void destruct_KoaRecTimeWalkPar(void *p) {
      typedef ::KoaRecTimeWalkPar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecTimeWalkPar

//______________________________________________________________________________
void KoaRecAddTimeJitter::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecAddTimeJitter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecAddTimeJitter::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecAddTimeJitter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecAddTimeJitter(void *p) {
      return  p ? new(p) ::KoaRecAddTimeJitter : new ::KoaRecAddTimeJitter;
   }
   static void *newArray_KoaRecAddTimeJitter(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecAddTimeJitter[nElements] : new ::KoaRecAddTimeJitter[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecAddTimeJitter(void *p) {
      delete ((::KoaRecAddTimeJitter*)p);
   }
   static void deleteArray_KoaRecAddTimeJitter(void *p) {
      delete [] ((::KoaRecAddTimeJitter*)p);
   }
   static void destruct_KoaRecAddTimeJitter(void *p) {
      typedef ::KoaRecAddTimeJitter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecAddTimeJitter

//______________________________________________________________________________
void KoaRecTimeJitterPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecTimeJitterPar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecTimeJitterPar::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecTimeJitterPar::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecTimeJitterPar(void *p) {
      return  p ? new(p) ::KoaRecTimeJitterPar : new ::KoaRecTimeJitterPar;
   }
   static void *newArray_KoaRecTimeJitterPar(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecTimeJitterPar[nElements] : new ::KoaRecTimeJitterPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecTimeJitterPar(void *p) {
      delete ((::KoaRecTimeJitterPar*)p);
   }
   static void deleteArray_KoaRecTimeJitterPar(void *p) {
      delete [] ((::KoaRecTimeJitterPar*)p);
   }
   static void destruct_KoaRecTimeJitterPar(void *p) {
      typedef ::KoaRecTimeJitterPar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecTimeJitterPar

//______________________________________________________________________________
void KoaRecCluster::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecCluster.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecCluster::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecCluster::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecCluster(void *p) {
      return  p ? new(p) ::KoaRecCluster : new ::KoaRecCluster;
   }
   static void *newArray_KoaRecCluster(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecCluster[nElements] : new ::KoaRecCluster[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecCluster(void *p) {
      delete ((::KoaRecCluster*)p);
   }
   static void deleteArray_KoaRecCluster(void *p) {
      delete [] ((::KoaRecCluster*)p);
   }
   static void destruct_KoaRecCluster(void *p) {
      typedef ::KoaRecCluster current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecCluster

namespace ROOT {
   static TClass *vectorlEstringgR_Dictionary();
   static void vectorlEstringgR_TClassManip(TClass*);
   static void *new_vectorlEstringgR(void *p = 0);
   static void *newArray_vectorlEstringgR(Long_t size, void *p);
   static void delete_vectorlEstringgR(void *p);
   static void deleteArray_vectorlEstringgR(void *p);
   static void destruct_vectorlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<string>*)
   {
      vector<string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<string>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<string>", -2, "vector", 216,
                  typeid(vector<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<string>) );
      instance.SetNew(&new_vectorlEstringgR);
      instance.SetNewArray(&newArray_vectorlEstringgR);
      instance.SetDelete(&delete_vectorlEstringgR);
      instance.SetDeleteArray(&deleteArray_vectorlEstringgR);
      instance.SetDestructor(&destruct_vectorlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<string> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<string>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<string>*)0x0)->GetClass();
      vectorlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string> : new vector<string>;
   }
   static void *newArray_vectorlEstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string>[nElements] : new vector<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEstringgR(void *p) {
      delete ((vector<string>*)p);
   }
   static void deleteArray_vectorlEstringgR(void *p) {
      delete [] ((vector<string>*)p);
   }
   static void destruct_vectorlEstringgR(void *p) {
      typedef vector<string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<string>

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 216,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR_Dictionary();
   static void maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR_TClassManip(TClass*);
   static void *new_maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR(void *p = 0);
   static void *newArray_maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR(Long_t size, void *p);
   static void delete_maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR(void *p);
   static void deleteArray_maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR(void *p);
   static void destruct_maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,KoaRecDigitizationIdeal::KoaRecStrip>*)
   {
      map<int,KoaRecDigitizationIdeal::KoaRecStrip> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,KoaRecDigitizationIdeal::KoaRecStrip>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,KoaRecDigitizationIdeal::KoaRecStrip>", -2, "map", 99,
                  typeid(map<int,KoaRecDigitizationIdeal::KoaRecStrip>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,KoaRecDigitizationIdeal::KoaRecStrip>) );
      instance.SetNew(&new_maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR);
      instance.SetNewArray(&newArray_maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR);
      instance.SetDelete(&delete_maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR);
      instance.SetDestructor(&destruct_maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,KoaRecDigitizationIdeal::KoaRecStrip> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,KoaRecDigitizationIdeal::KoaRecStrip>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,KoaRecDigitizationIdeal::KoaRecStrip>*)0x0)->GetClass();
      maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,KoaRecDigitizationIdeal::KoaRecStrip> : new map<int,KoaRecDigitizationIdeal::KoaRecStrip>;
   }
   static void *newArray_maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,KoaRecDigitizationIdeal::KoaRecStrip>[nElements] : new map<int,KoaRecDigitizationIdeal::KoaRecStrip>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR(void *p) {
      delete ((map<int,KoaRecDigitizationIdeal::KoaRecStrip>*)p);
   }
   static void deleteArray_maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR(void *p) {
      delete [] ((map<int,KoaRecDigitizationIdeal::KoaRecStrip>*)p);
   }
   static void destruct_maplEintcOKoaRecDigitizationIdealcLcLKoaRecStripgR(void *p) {
      typedef map<int,KoaRecDigitizationIdeal::KoaRecStrip> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,KoaRecDigitizationIdeal::KoaRecStrip>

namespace ROOT {
   static TClass *maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR_Dictionary();
   static void maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR_TClassManip(TClass*);
   static void *new_maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR(void *p = 0);
   static void *newArray_maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR(Long_t size, void *p);
   static void delete_maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR(void *p);
   static void deleteArray_maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR(void *p);
   static void destruct_maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,KoaRecChargeDivisionIdeal::KoaRecStrip>*)
   {
      map<int,KoaRecChargeDivisionIdeal::KoaRecStrip> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,KoaRecChargeDivisionIdeal::KoaRecStrip>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,KoaRecChargeDivisionIdeal::KoaRecStrip>", -2, "map", 99,
                  typeid(map<int,KoaRecChargeDivisionIdeal::KoaRecStrip>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,KoaRecChargeDivisionIdeal::KoaRecStrip>) );
      instance.SetNew(&new_maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR);
      instance.SetNewArray(&newArray_maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR);
      instance.SetDelete(&delete_maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR);
      instance.SetDestructor(&destruct_maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,KoaRecChargeDivisionIdeal::KoaRecStrip> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,KoaRecChargeDivisionIdeal::KoaRecStrip>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,KoaRecChargeDivisionIdeal::KoaRecStrip>*)0x0)->GetClass();
      maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,KoaRecChargeDivisionIdeal::KoaRecStrip> : new map<int,KoaRecChargeDivisionIdeal::KoaRecStrip>;
   }
   static void *newArray_maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,KoaRecChargeDivisionIdeal::KoaRecStrip>[nElements] : new map<int,KoaRecChargeDivisionIdeal::KoaRecStrip>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR(void *p) {
      delete ((map<int,KoaRecChargeDivisionIdeal::KoaRecStrip>*)p);
   }
   static void deleteArray_maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR(void *p) {
      delete [] ((map<int,KoaRecChargeDivisionIdeal::KoaRecStrip>*)p);
   }
   static void destruct_maplEintcOKoaRecChargeDivisionIdealcLcLKoaRecStripgR(void *p) {
      typedef map<int,KoaRecChargeDivisionIdeal::KoaRecStrip> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,KoaRecChargeDivisionIdeal::KoaRecStrip>

namespace {
  void TriggerDictionaryInitialization_G__KoaSimpleRecDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/home/yong/fairroot/v18_jun19/include",
"/home/yong/src/KoalaSoft/detectors/recoil/simple",
"/home/yong/src/KoalaSoft/data",
"/home/yong/src/KoalaSoft/data/MCData",
"/home/yong/src/KoalaSoft/tools",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/src/KoalaSoft/build_jens/detectors/recoil/simple/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__KoaSimpleRecDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class KoaRec;
class __attribute__((annotate(R"ATTRDUMP(Factory for all KoaRec parameter containers)ATTRDUMP"))) KoaRecContFact;
class KoaRecGeo;
class KoaRecGeoPar;
class KoaRecMisalignPar;
class KoaRecPoint;
class KoaRecDigi;
class KoaRecDigitizationIdeal;
class KoaRecChargeDivisionIdeal;
class KoaRecAddNoise;
class KoaRecNoisePar;
class KoaRecAddFano;
class KoaRecFanoPar;
class KoaRecChargeCollection;
class KoaRecChargeCollectionPar;
class KoaRecAddTimeWalk;
class KoaRecTimeWalkPar;
class KoaRecAddTimeJitter;
class KoaRecTimeJitterPar;
class KoaRecCluster;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__KoaSimpleRecDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAREC_H
#define KOAREC_H

#include "FairDetector.h"

#include "TVector3.h"
#include "TLorentzVector.h"
#include <string>

class KoaRecPoint;
class FairVolume;
class TClonesArray;
class KoaGeoHandler;
class KoaRecMisalignPar;

class KoaRec: public FairDetector
{

  public:

    /**      Name :  Detector Name
     *       Active: kTRUE for active detectors (ProcessHits() will be called)
     *               kFALSE for inactive detectors
    */
    KoaRec(const char* Name, Bool_t Active);

    /**      default constructor    */
    KoaRec();

    /**       destructor     */
    virtual ~KoaRec();

    /** Switch on/off geometry modification, i.e. whether apply the misalignment matrices **/
    // Reference Tutorial4
    void SetModifyGeometry(Bool_t val) { fModifyGeometry=val; }
    // get the Misalignment Matrices list, mainly used for output and checking
    std::map<std::string, TGeoHMatrix> getMisalignmentMatrices();

    /**      Initialization of the detector is done here    */
    virtual void   Initialize();

    /**Set the parameter containers*/
    void SetParContainers();

    /** Initialize everything which has to be done before the construction and modification
     ** of the geometry. Mostly this is needed to read data from the parameter containers.
     ** Especially for the geometry modification before MC.*/
    virtual void   InitParContainers();

    /**       this method is called for each step during simulation
     *       (see FairMCApplication::Stepping())
    */
    virtual Bool_t ProcessHits( FairVolume* v=0);

    /**       Registers the produced collections in FAIRRootManager.     */
    virtual void   Register();

    /** Gets the produced collections */
    virtual TClonesArray* GetCollection(Int_t iColl) const ;

    /**      has to be called after each event to reset the containers      */
    virtual void   Reset();

    /**      Create the detector geometry        */
    void ConstructGeometry();

    Bool_t CheckIfSensitive(std::string name);
    void ConstructASCIIGeometry();


    /**      This method is an example of how to add your own point
     *       of type KoaRecPoint to the clones array
    */
    KoaRecPoint* AddHit(Int_t trackID, Int_t detID,
                        TVector3 pos, TVector3 posEnd,
                        TVector3 mom, Double_t time,
                        Double_t length, Double_t eLoss);

    /** The following methods can be implemented if you need to make
     *  any optional action in your detector during the transport.
    */

    virtual void   SetSpecialPhysicsCuts() {;}
    virtual void   EndOfEvent();
    virtual void   FinishPrimary() {;}
    virtual void   FinishRun() {;}
    virtual void   BeginPrimary() {;}
    virtual void   PostTrack() {;}
    virtual void   PreTrack() {;}
    virtual void   BeginEvent() {;}

    virtual FairModule* CloneModule() const;

    virtual void RegisterAlignmentMatrices();

  private:
    // Sensitive volume name list, used when importing geometry from ROOT file
    std::vector<std::string> fListOfSensitives;  

    /** Track information to be stored until the track leaves the
    active volume.
    */
    Int_t          fTrackID;           //!  track index
    Int_t          fVolumeID;          //!  volume id
    TLorentzVector fPos;               //!  position at entrance
    TLorentzVector fPosEnd;            //!  position at end
    TLorentzVector fMom;               //!  momentum at entrance
    TLorentzVector fMomOut;            //!  momentum
    Double32_t     fTime;              //!  time
    Double32_t     fLength;            //!  length
    Double32_t     fELoss;             //!  energy loss

    /** container for data points */
    TClonesArray*  fKoaRecPointCollection;  //!

    KoaGeoHandler* fGeoHandler; //!

    /** parameters related to geometry misalignment **/
    Bool_t fModifyGeometry;

    // parameter container
    KoaRecMisalignPar* fMisalignPar;

    // Individual Sensor's misalignment
    Int_t fNrOfSensors;
    TArrayD fSensorShiftX;
    TArrayD fSensorShiftY;
    TArrayD fSensorShiftZ;
    TArrayD fSensorRotPhi;
    TArrayD fSensorRotTheta;
    TArrayD fSensorRotPsi;

    KoaRec(const KoaRec&);
    KoaRec& operator=(const KoaRec&);

    ClassDef(KoaRec,1)
};

#endif //NEWDETECTOR_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOARECCONTFACT_H
#define KOARECCONTFACT_H

#include "FairContFact.h"

class FairContainer;

class KoaRecContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    KoaRecContFact();
    ~KoaRecContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( KoaRecContFact,1) // Factory for all KoaRec parameter containers
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOARECGEO_H
#define KOARECGEO_H

#include "FairGeoSet.h"

class  KoaRecGeo : public FairGeoSet
{

  protected:
    char modName[20];  // name of module
    char eleName[20];  // substring for elements in module
  public:
    KoaRecGeo();
    ~KoaRecGeo() {}
    const char* getModuleName(Int_t);
    const char* getEleName(Int_t);
    inline Int_t getModNumInMod(const TString&);
    ClassDef(KoaRecGeo,1)
};

inline Int_t KoaRecGeo::getModNumInMod(const TString& name)
{
  /** returns the module index from module name
   ?? in name[??] has to be the length of the detector name in the
   .geo file. For example if all nodes in this file starts with
   newdetector ?? has to be 11.
  */
  return (Int_t)(name[6]-'0')-1; //
}

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOARECGEOPAR_H
#define KOARECGEOPAR_H

#include "FairParGenericSet.h"

class TObjArray;
class FairParamList;

class KoaRecGeoPar       : public FairParGenericSet
{
  public:

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoPassNodes;

    KoaRecGeoPar(const char* name="KoaRecGeoPar",
                      const char* title="KoaRec Geometry Parameters",
                      const char* context="TestDefaultContext");
    ~KoaRecGeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray* GetGeoPassiveNodes()   {return fGeoPassNodes;}

  private:
    KoaRecGeoPar(const KoaRecGeoPar&);
    KoaRecGeoPar& operator=(const KoaRecGeoPar&);

    ClassDef(KoaRecGeoPar,1)
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAREC_MISALIGNPAR_H
#define KOAREC_MISALIGNPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet

#include "Rtypes.h"                     // for ClassDef

#include "TArrayD.h"                    // for TArrayD

class FairParamList;

class KoaRecMisalignPar : public FairParGenericSet
{
  public:

    KoaRecMisalignPar(const char* name="KoaRecMisalignPar",
                                const char* title="Missalignment parameter for Koala Recoil Detector Module",
                                const char* context="TestDefaultContext");
    ~KoaRecMisalignPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    Int_t GetNrOfSensors() {return fNrOfSensors;}
    TArrayD GetSensorShiftX() {return fSensorShiftX;}
    TArrayD GetSensorShiftY() {return fSensorShiftY;}
    TArrayD GetSensorShiftZ() {return fSensorShiftZ;}
    TArrayD GetSensorRotPhi() {return fSensorRotPhi;}
    TArrayD GetSensorRotTheta() {return fSensorRotTheta;}
    TArrayD GetSensorRotPsi() {return fSensorRotPsi;}

  private:
    // Individual Sensor's misalignment
    Int_t fNrOfSensors;
    TArrayD fSensorShiftX; // Array to hold the misalignment in x-direction
    TArrayD fSensorShiftY; // Array to hold the misalignment in y-direction
    TArrayD fSensorShiftZ; // Array to hold the misalignment in z-direction
    TArrayD fSensorRotPhi; // Array to hold the rotation in x-direction
    TArrayD fSensorRotTheta; // Array to hold the rotation in y-direction
    TArrayD fSensorRotPsi; // Array to hold the rotation in z-direction

    KoaRecMisalignPar(const KoaRecMisalignPar&);
    KoaRecMisalignPar& operator=(const KoaRecMisalignPar&);

    ClassDef(KoaRecMisalignPar,1)
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOARECPOINT_H
#define KOARECPOINT_H 1


#include "FairMCPoint.h"

#include "TObject.h"
#include "TVector3.h"

class KoaRecPoint : public FairMCPoint
{

  public:

    /** Default constructor **/
    KoaRecPoint();

    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param posIn    Coordinates at entrance to active volume [cm]
     *@param posEnd   Coordinates at exit/end to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    KoaRecPoint(Int_t trackID,
                Int_t detID,
                TVector3 posIn,
                TVector3 posEnd,
                TVector3 mom,
                Double_t tof,
                Double_t length,
                Double_t eLoss);

    /** Destructor **/
    virtual ~KoaRecPoint();

    /** Accessors **/
    Double32_t GetXEnd() const { return fX_End; }
    Double32_t GetYEnd() const { return fY_End; }
    Double32_t GetZEnd() const { return fZ_End; }
    void PositionEnd(TVector3& pos) const { pos.SetXYZ(fX_End, fY_End, fZ_End); }

    /** Modifiers **/
    void SetXEnd(Double32_t x) { fX_End = x; }
    void SetYEnd(Double32_t y) { fY_End = y; }
    void SetZEnd(Double32_t z) { fZ_End = z; }
    void SetXYZEnd(Double32_t x, Double32_t y, Double32_t z){
      fX_End = x;
      fY_End = y;
      fZ_End = z;
    }
    void SetPositionEnd(const TVector3& posEnd){
      fX_End = posEnd.X();
      fY_End = posEnd.Y();
      fZ_End = posEnd.Z();
    }

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;

  private:
    Double32_t fX_End;
    Double32_t fY_End;
    Double32_t fZ_End;

    /** Copy constructor **/
    KoaRecPoint(const KoaRecPoint& point);
    KoaRecPoint operator=(const KoaRecPoint& point);

    ClassDef(KoaRecPoint,2)

};

#endif
// --------------------------------------------------------
// ----			KoaRecDigi header file	---
// ----			Created 09.10.19 by Y.Zhou ---
// ----     Adopted from PndSdsDigi by T.Stockmanns in PandaRoot ---
// --------------------------------------------------------

/** KoaRecDigi.h
 *@author Y.Zhou <y.zhou@fz-juelich.de>
 **
 ** \brief Base class for Digi information
 **
 **
 **/

#ifndef KOARECDIGI_H
#define KOARECDIGI_H

#include "FairTimeStamp.h"
#include "KoaMapEncoder.h"

#include "TObject.h"
#include "TString.h"
#include <iostream>
#include <vector>
#include <boost/serialization/void_cast.hpp>

class KoaRecDigi : public FairTimeStamp
  {
    friend std::ostream& operator<< (std::ostream& out, KoaRecDigi& digi){
      KoaMapEncoder *encoder = KoaMapEncoder::Instance();
      Int_t detId;
      encoder->DecodeChannelID(digi.GetDetID(), detId);
      out << "KoaRecDigi in " << encoder->DetectorIDToVolName(detId) << ": "
      << " charge: " << digi.GetCharge() 
      << " timestamp: "<<digi.GetTimeStamp()
      << ", from Point(s): ";
      std::vector<Int_t> indices = digi.GetIndices();
      for (unsigned int i = 0; i < indices.size(); i++){
        std::cout << digi.GetIndex(i) << " " << std::endl;
      }
      return out;
    }
    
  public: 
    KoaRecDigi();
    KoaRecDigi(std::vector<Int_t> index, Int_t detID, Double_t charge);
    KoaRecDigi(Int_t index, Int_t detID, Double_t charge);
		/**<constructor
     * \param index position of PndSdsMCPoint in TClonesArray
     * \param detID detector ID (from/for CbmPoint/Hit)
     * \param charge deposited charge in electrons
     */
		virtual ~KoaRecDigi(){};
    
		Double_t GetCharge()	 const { return fCharge; }
		Int_t GetDetID() const { return fDetID;}
		std::vector<Int_t> GetIndices() const { return fIndex;}
		Int_t GetIndex(int i = 0) const{ return fIndex[i];}
		Int_t GetNIndices() const { return fIndex.size();}
    
		virtual void AddIndex(int index)
		{
			fIndex.push_back(index);
			AddLink(FairLink(fDetID, index));
		}
    
		virtual void AddIndex(std::vector<Int_t> index)
		{
			fIndex = index;
			AddLinks(FairMultiLinkedData(fDetID, index));
		}

		void SetCharge(double charge){fCharge = charge;}
    void AddCharge(double charge){fCharge += charge;}

    void SetDetectorID(Int_t detID) { fDetID=detID; }

		virtual void Print() {
			std::cout << *this;
		}

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			boost::serialization::void_cast_register<KoaRecDigi, FairTimeStamp>();

			ar & boost::serialization::base_object<FairTimeStamp>(*this);
			ar & fDetID;
			ar & fCharge;
		}

  protected:
		friend class boost::serialization::access;

		std::vector<Int_t> fIndex;   // indice of mc points contributing to this digi
		Int_t fDetID;                // encoded detector channel id
		Double_t fCharge;            // collected charge (eV) or energy (KeV) or ADC counts
    
    ClassDef(KoaRecDigi,1);
  };

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOARECDIGITIZATIONIDEAL_H
#define KOARECDIGITIZATIONIDEAL_H

#include "FairTask.h"
#include <map>

class TClonesArray;
class KoaGeoHandler;
class KoaRecPoint;

class KoaRecDigitizationIdeal : public FairTask
{
  public:

    /** Default constructor **/
    KoaRecDigitizationIdeal();

    /** Constructor with parameters (Optional) **/
    //  KoaRecDigitizationIdeal(Int_t verbose);


    /** Destructor **/
    ~KoaRecDigitizationIdeal();


    /** Initiliazation of task at the beginning of a run **/
    virtual InitStatus Init();

    /** ReInitiliazation of task when the runID changes **/
    virtual InitStatus ReInit();


    /** Executed for each event. **/
    virtual void Exec(Option_t* opt);

    /** Load the parameter container from the runtime database **/
    virtual void SetParContainers();

    /** Finish task called at the end of the run **/
    virtual void Finish();

    /** Reset eventwise counters **/
    void Reset();

 public:
  struct KoaRecStrip{
    Double_t fTimestamp;
    Double_t fCharge;
  };
  using KoaRecStrips = std::map<Int_t, KoaRecStrip>;

 private:
    void FillFiredStrips(KoaRecPoint* McPoint);
    void FillFiredStrip(Int_t DetID, Double_t Timestamp, Double_t Charge);

    void AddDigis();

  private:
    /** Geometry Handler **/
    KoaGeoHandler* fGeoHandler;

    /** Input array from previous already existing data level **/
    TClonesArray* fPoints;

    /** Output array to  new data level**/
    TClonesArray* fDigis;

    KoaRecStrips fFiredStrips;

    KoaRecDigitizationIdeal(const KoaRecDigitizationIdeal&);
    KoaRecDigitizationIdeal operator=(const KoaRecDigitizationIdeal&);

    ClassDef(KoaRecDigitizationIdeal,1);
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_CHARGEDIVISIONIDEAL_H
#define KOA_REC_CHARGEDIVISIONIDEAL_H

#include "FairTask.h"
#include <map>

class TClonesArray;
class KoaGeoHandler;
class KoaRecPoint;


class KoaRecChargeDivisionIdeal : public FairTask
{
  public:

    /** Default constructor **/
    KoaRecChargeDivisionIdeal();

    /** Constructor with parameters (Optional) **/
    //  KoaRecChargeDivisionIdeal(Int_t verbose);


    /** Destructor **/
    ~KoaRecChargeDivisionIdeal();


    /** Initiliazation of task at the beginning of a run **/
    virtual InitStatus Init();

    /** ReInitiliazation of task when the runID changes **/
    virtual InitStatus ReInit();


    /** Executed for each event. **/
    virtual void Exec(Option_t* opt);

    /** Load the parameter container from the runtime database **/
    virtual void SetParContainers();

    /** Finish task called at the end of the run **/
    virtual void Finish();

    /** Reset eventwise counters **/
    void Reset();

 public:
  struct KoaRecStrip{
    Double_t fTimestamp;
    Double_t fCharge;
  };
  using KoaRecStrips = std::map<Int_t, KoaRecStrip>;

  void SetOutputDigiName(const char* name) {
    fOutputName = name;
  }
  void SaveOutputDigi(bool flag = true) {
    fSaveOutput = flag;
  }

 private:
    void FillFiredStrips(KoaRecPoint* McPoint);
    void FillFiredStrip(Int_t DetID, Double_t Timestamp, Double_t Charge);

    void AddDigis();

  private:
    /** Geometry Handler **/
    KoaGeoHandler* fGeoHandler;

  // Output digit branch name
  std::string fOutputName;
  // Flag indicate save output branch to file or in memory
  bool fSaveOutput;

    /** Input array from previous already existing data level **/
    TClonesArray* fPoints;

    /** Output array to  new data level**/
    TClonesArray* fDigis; // fCharge in keV

    KoaRecStrips fFiredStrips;

    KoaRecChargeDivisionIdeal(const KoaRecChargeDivisionIdeal&);
    KoaRecChargeDivisionIdeal operator=(const KoaRecChargeDivisionIdeal&);

    ClassDef(KoaRecChargeDivisionIdeal,1);
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_ADDNOISE_H
#define KOA_REC_ADDNOISE_H

#include "FairTask.h"
#include "TRandom3.h"
#include <map>

class TClonesArray;
class KoaRecDigi;
class KoaRecNoisePar;

class KoaRecAddNoise : public FairTask
{
  public:

    /** Default constructor **/
    KoaRecAddNoise();

    /** Destructor **/
    ~KoaRecAddNoise();


    /** Initiliazation of task at the beginning of a run **/
    virtual InitStatus Init();

    /** ReInitiliazation of task when the runID changes **/
    virtual InitStatus ReInit();

    /** Executed for each event. **/
    virtual void Exec(Option_t* opt);

    /** Load the parameter container from the runtime database **/
    virtual void SetParContainers();

    /** Finish task called at the end of the run **/
    virtual void Finish();

    /** Reset eventwise counters **/
    void Reset();

 public:
  void SetInputDigiName(const char* name) {
    fInputName = name;
  }
  void SetOutputDigiName(const char* name) {
    fOutputName = name;
  }
  void SaveOutputDigi(bool flag = true) {
    fSaveOutput = flag;
  }

 private:
    void AddNoise();

 private:
    // Input digit branch name
    std::string fInputName;
  // Output digit branch name
    std::string fOutputName;
    // Flag indicate save output branch to file or in memory
    bool fSaveOutput;

    /** Input array from previous already existing data level **/
    TClonesArray* fInputDigis;
    /** Output array to  new data level**/
    TClonesArray* fOutputDigis;

    // Noise parameter
  TRandom3 fRndEngine;
  KoaRecNoisePar* fNoisePar;
  Double_t fNoiseMean;
  Double_t fNoiseSigma;

    KoaRecAddNoise(const KoaRecAddNoise&);
    KoaRecAddNoise operator=(const KoaRecAddNoise&);

    ClassDef(KoaRecAddNoise,1);
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_NOISEPAR_H
#define KOA_REC_NOISEPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet
#include "FairLogger.h"

#include "Rtypes.h"                     // for ClassDef

#include "TArrayD.h"                    // for TArrayD

class FairParamList;

class KoaRecNoisePar : public FairParGenericSet
{
  public:

    KoaRecNoisePar(const char* name="KoaRecNoisePar",
                                const char* title="Noise parameter for KOALA recoil detector digitization",
                                const char* context="TestDefaultContext");
    ~KoaRecNoisePar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    Double_t GetMean() {return fMean;}
    Double_t GetSigma() {return fSigma;}
    // TArrayD GetSensorRotPsi() {return fSensorRotPsi;}

  void  printParams() {
    LOG(info) << "Mean: " << fMean << ", Sigma: " << fSigma;
  }

  private:
    Double_t fMean; // Mean of noise, in keV
    Double_t fSigma; // Sigma of noise, in keV
    // TArrayD fSensorRotPsi; // Array to hold the rotation in z-direction

    KoaRecNoisePar(const KoaRecNoisePar&);
    KoaRecNoisePar& operator=(const KoaRecNoisePar&);

    ClassDef(KoaRecNoisePar,1)
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_ADDFANO_H
#define KOA_REC_ADDFANO_H

#include "FairTask.h"
#include "TRandom3.h"
#include "TArrayD.h"
#include <map>

class TClonesArray;
class KoaRecDigi;
class KoaRecFanoPar;
class KoaMapEncoder;

class KoaRecAddFano : public FairTask
{
  public:

    /** Default constructor **/
    KoaRecAddFano();

    /** Destructor **/
    ~KoaRecAddFano();


    /** Initiliazation of task at the beginning of a run **/
    virtual InitStatus Init();

    /** ReInitiliazation of task when the runID changes **/
    virtual InitStatus ReInit();

    /** Executed for each event. **/
    virtual void Exec(Option_t* opt);

    /** Load the parameter container from the runtime database **/
    virtual void SetParContainers();

    /** Finish task called at the end of the run **/
    virtual void Finish();

    /** Reset eventwise counters **/
    void Reset();

 public:
  void SetInputDigiName(const char* name) {
    fInputName = name;
  }
  void SetOutputDigiName(const char* name) {
    fOutputName = name;
  }
  void SaveOutputDigi(bool flag = true) {
    fSaveOutput = flag;
  }

 private:
    void AddFano();

 private:
    // Input digit branch name
    std::string fInputName;
  // Output digit branch name
    std::string fOutputName;
    // Flag indicate save output branch to file or in memory
    bool fSaveOutput;

    /** Input array from previous already existing data level **/
    TClonesArray* fInputDigis;
    /** Output array to  new data level**/
    TClonesArray* fOutputDigis;

    // fano factor parameter
  TRandom3 fRndEngine;
  KoaRecFanoPar* fFanoPar;
  TArrayD  fFanoFactors;

  // MapEncoder
  KoaMapEncoder *fEncoder;

    KoaRecAddFano(const KoaRecAddFano&);
    KoaRecAddFano operator=(const KoaRecAddFano&);

    ClassDef(KoaRecAddFano,1);
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_FANOPAR_H
#define KOA_REC_FANOPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet
#include "FairLogger.h"
#include "Rtypes.h"                     // for ClassDef
#include "TArrayD.h"                    // for TArrayD
#include "KoaMapEncoder.h"

class FairParamList;

class KoaRecFanoPar : public FairParGenericSet
{
  public:

    KoaRecFanoPar(const char* name="KoaRecFanoPar",
                  const char* title="Fano factor for KOALA recoil detector digitization",
                  const char* context="TestDefaultContext");
    ~KoaRecFanoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    TArrayD GetFanoFactors() {return fFanoFactors;}

  void  printParams() {
    LOG(info) << "Fano factors : ";

    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    Int_t low, high;
    encoder->GetRecDetIDRange(low,high);
    for(int detId=low;detId <= high;detId++){
      LOG(info) << encoder->DetectorIDToVolName(detId) << ": " << fFanoFactors[detId-low];
    }
  }

  private:
    TArrayD fFanoFactors; // Array to hold the rotation in z-direction

    KoaRecFanoPar(const KoaRecFanoPar&);
    KoaRecFanoPar& operator=(const KoaRecFanoPar&);

    ClassDef(KoaRecFanoPar,1)
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_ChargeCollection_H
#define KOA_REC_ChargeCollection_H

#include "FairTask.h"
#include "TRandom3.h"
#include "TArrayD.h"
#include <map>

class TClonesArray;
class KoaRecDigi;
class KoaRecChargeCollectionPar;
class KoaMapEncoder;

class KoaRecChargeCollection : public FairTask
{
  public:

    /** Default constructor **/
    KoaRecChargeCollection();

    /** Destructor **/
    ~KoaRecChargeCollection();


    /** Initiliazation of task at the beginning of a run **/
    virtual InitStatus Init();

    /** ReInitiliazation of task when the runID changes **/
    virtual InitStatus ReInit();

    /** Executed for each event. **/
    virtual void Exec(Option_t* opt);

    /** Load the parameter container from the runtime database **/
    virtual void SetParContainers();

    /** Finish task called at the end of the run **/
    virtual void Finish();

    /** Reset eventwise counters **/
    void Reset();

 public:
  void SetInputDigiName(const char* name) {
    fInputName = name;
  }
  void SetOutputDigiName(const char* name) {
    fOutputName = name;
  }
  void SaveOutputDigi(bool flag = true) {
    fSaveOutput = flag;
  }

 private:
    void ChargeCollection();

 private:
    // Input digit branch name
    std::string fInputName;
  // Output digit branch name
    std::string fOutputName;
    // Flag indicate save output branch to file or in memory
    bool fSaveOutput;

    /** Input array from previous already existing data level **/
    TClonesArray* fInputDigis;
    /** Output array to  new data level**/
    TClonesArray* fOutputDigis;

    // fano factor parameter
  TRandom3 fRndEngine;
  KoaRecChargeCollectionPar* fCollectionPar;
  TArrayD  fCollectionEfficiency;
  TArrayD  fCollectionDispersion;

  // MapEncoder
  KoaMapEncoder *fEncoder;

    KoaRecChargeCollection(const KoaRecChargeCollection&);
    KoaRecChargeCollection operator=(const KoaRecChargeCollection&);

    ClassDef(KoaRecChargeCollection,1);
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_ChargeCollectionPar_H
#define KOA_REC_ChargeCollectionPar_H

#include "FairParGenericSet.h"          // for FairParGenericSet
#include "FairLogger.h"
#include "Rtypes.h"                     // for ClassDef
#include "TArrayD.h"                    // for TArrayD
#include "KoaMapEncoder.h"

class FairParamList;

class KoaRecChargeCollectionPar : public FairParGenericSet
{
  public:

    KoaRecChargeCollectionPar(const char* name="KoaRecChargeCollectionPar",
                              const char* title="Charge collection parameters for KOALA recoil detector digitization",
                              const char* context="TestDefaultContext");
    ~KoaRecChargeCollectionPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    TArrayD GetEfficiency() {return fEfficiency;}
    TArrayD GetDispersion() {return fDispersion;}

  void  printParams() {
    LOG(info) << "Charge Collection parameters : ";

    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    Int_t low, high;
    encoder->GetRecDetIDRange(low,high);
    for(int detId=low;detId <= high;detId++){
      LOG(info) << encoder->DetectorIDToVolName(detId) << ": " << fEfficiency[detId-low] << ", " << fDispersion[detId-low] << "keV";
    }
  }

  private:
    TArrayD fEfficiency; // Array to the efficiency of each sensor
    TArrayD fDispersion; // Array to hold the dispersion sigma of each sensor

    KoaRecChargeCollectionPar(const KoaRecChargeCollectionPar&);
    KoaRecChargeCollectionPar& operator=(const KoaRecChargeCollectionPar&);

    ClassDef(KoaRecChargeCollectionPar,1)
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_ADDTIMEWALK_H
#define KOA_REC_ADDTIMEWALK_H

#include "FairTask.h"
#include <map>

class TClonesArray;
class KoaRecDigi;
class KoaRecTimeWalkPar;

class KoaRecAddTimeWalk : public FairTask
{
  public:

    /** Default constructor **/
    KoaRecAddTimeWalk();

    /** Destructor **/
    ~KoaRecAddTimeWalk();


    /** Initiliazation of task at the beginning of a run **/
    virtual InitStatus Init();

    /** ReInitiliazation of task when the runID changes **/
    virtual InitStatus ReInit();

    /** Executed for each event. **/
    virtual void Exec(Option_t* opt);

    /** Load the parameter container from the runtime database **/
    virtual void SetParContainers();

    /** Finish task called at the end of the run **/
    virtual void Finish();

    /** Reset eventwise counters **/
    void Reset();

 public:
  void SetInputDigiName(const char* name) {
    fInputName = name;
  }
  void SetOutputDigiName(const char* name) {
    fOutputName = name;
  }
  void SaveOutputDigi(bool flag = true) {
    fSaveOutput = flag;
  }

 private:
    void AddTimeWalk();

 private:
    // Input digit branch name
    std::string fInputName;
  // Output digit branch name
    std::string fOutputName;
    // Flag indicate save output branch to file or in memory
    bool fSaveOutput;

    /** Input array from previous already existing data level **/
    TClonesArray* fInputDigis;
    /** Output array to  new data level**/
    TClonesArray* fOutputDigis;

    // Noise parameter
  KoaRecTimeWalkPar* fTimeWalkPar;
  Double_t fThreshold;
  Double_t fWidth;

    KoaRecAddTimeWalk(const KoaRecAddTimeWalk&);
    KoaRecAddTimeWalk operator=(const KoaRecAddTimeWalk&);

    ClassDef(KoaRecAddTimeWalk,1);
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_TIMEWALKPAR_H
#define KOA_REC_TIMEWALKPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet
#include "FairLogger.h"

#include "Rtypes.h"                     // for ClassDef

#include "TArrayD.h"                    // for TArrayD

class FairParamList;

class KoaRecTimeWalkPar : public FairParGenericSet
{
  public:

    KoaRecTimeWalkPar(const char* name="KoaRecTimeWalkPar",
                                const char* title="Time-walk parameters for recoil detector",
                                const char* context="TestDefaultContext");
    ~KoaRecTimeWalkPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    Double_t GetThreshold() {return fThreshold;}
    Double_t GetWidth() {return fWidth;}

  void  printParams() {
    LOG(info) << "Threshold: " << fThreshold << ", Half-Width: " << fWidth;
  }

  private:
    Double_t fThreshold; // Threshold for LED, in keV
    Double_t fWidth; // Half-width of Shaper output, in ns

    KoaRecTimeWalkPar(const KoaRecTimeWalkPar&);
    KoaRecTimeWalkPar& operator=(const KoaRecTimeWalkPar&);

    ClassDef(KoaRecTimeWalkPar,1)
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_ADDTIMEJITTER_H
#define KOA_REC_ADDTIMEJITTER_H

#include "FairTask.h"
#include "TRandom3.h"
#include <map>

class TClonesArray;
class KoaRecDigi;
class KoaRecTimeJitterPar;

class KoaRecAddTimeJitter : public FairTask
{
  public:

    /** Default constructor **/
    KoaRecAddTimeJitter();

    /** Destructor **/
    ~KoaRecAddTimeJitter();


    /** Initiliazation of task at the beginning of a run **/
    virtual InitStatus Init();

    /** ReInitiliazation of task when the runID changes **/
    virtual InitStatus ReInit();

    /** Executed for each event. **/
    virtual void Exec(Option_t* opt);

    /** Load the parameter container from the runtime database **/
    virtual void SetParContainers();

    /** Finish task called at the end of the run **/
    virtual void Finish();

    /** Reset eventwise counters **/
    void Reset();

 public:
  void SetInputDigiName(const char* name) {
    fInputName = name;
  }
  void SetOutputDigiName(const char* name) {
    fOutputName = name;
  }
  void SaveOutputDigi(bool flag = true) {
    fSaveOutput = flag;
  }

 private:
    void AddTimeJitter();

 private:
    // Input digit branch name
    std::string fInputName;
  // Output digit branch name
    std::string fOutputName;
    // Flag indicate save output branch to file or in memory
    bool fSaveOutput;

    /** Input array from previous already existing data level **/
    TClonesArray* fInputDigis;
    /** Output array to  new data level**/
    TClonesArray* fOutputDigis;

    // Noise parameter
  TRandom3 fRndEngine;
  KoaRecTimeJitterPar* fJitterPar;
  Double32_t fSigma;

    KoaRecAddTimeJitter(const KoaRecAddTimeJitter&);
    KoaRecAddTimeJitter operator=(const KoaRecAddTimeJitter&);

    ClassDef(KoaRecAddTimeJitter,1);
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_TIMEJITTERPAR_H
#define KOA_REC_TIMEJITTERPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet
#include "FairLogger.h"

#include "Rtypes.h"                     // for ClassDef

#include "TArrayD.h"                    // for TArrayD

class FairParamList;

class KoaRecTimeJitterPar : public FairParGenericSet
{
  public:

    KoaRecTimeJitterPar(const char* name="KoaRecTimeJitterPar",
                        const char* title="Time-jitter parameters for recoil detector",
                        const char* context="TestDefaultContext");
    ~KoaRecTimeJitterPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    Double_t GetSigma() {return fSigma;}

  void  printParams() {
    LOG(info) << "Sigma: " << fSigma;
  }

  private:
    Double_t fSigma; // Jitter sigma, in ns

    KoaRecTimeJitterPar(const KoaRecTimeJitterPar&);
    KoaRecTimeJitterPar& operator=(const KoaRecTimeJitterPar&);

    ClassDef(KoaRecTimeJitterPar,1)
};

#endif
//#pragma once
#ifndef KOA_REC_CLUSTER_H
#define KOA_REC_CLUSTER_H

#include "TObject.h"
#include <vector>
#include "TString.h"
#include <iostream>
#include "KoaMapEncoder.h"

#include <boost/serialization/void_cast.hpp>
#include <boost/serialization/vector.hpp>

class KoaRecDigi;
class KoaMapEncoder;
class KoaGeoHandler;

/**
 * @brief a cluster (group of neighboring crystals) of hit emc crystals
 * @ingroup PndEmc
 */
class KoaRecCluster : public TObject
{
  friend std::ostream& operator<< (std::ostream& out, KoaRecCluster& cluster){
    out << "KoaRecCluster in " << cluster.GetDetName() << ": "
        << " energy: " << cluster.EnergyTotal()
        << " timestamp: "<< cluster.TimeTotal()
        << " position: " << cluster.PositionTotal()
        << ", from  " << cluster.NumberOfDigis() << " digits\n";
    return out;
  }

public:
	// Constructors
	KoaRecCluster();
  KoaRecCluster(Int_t detId);
  KoaRecCluster(Int_t detId, KoaGeoHandler* geoHandler);

	// Destructor
	virtual ~KoaRecCluster();
	
  virtual void Print() {
    std::cout << *this;
  }

	// all digis
  Double_t MaximaTotal() const;
  Double_t EnergyTotal() const; // in keV
  Double_t PositionTotal() const; // in cm
  Double_t TimeTotal() const;

  Int_t ChIdTotal() const; 
  Int_t GetMaximaChId() const;
  Int_t GetFirstChId() const;
  Int_t GetFirstChIdAboveThresh() const;

	// digis above threshold
  Double_t Maxima() const;
	Double_t Energy() const; // in keV
	// Theta centroid of cluster in index units
	Double_t Position() const; // in cm
  Double_t Time() const;

	// Get Module in which cluster is located
	Int_t GetDetId() const { return fDetId; }
	TString GetDetName() const;
  Int_t* GetIds()  { return fIds; }
  Double_t* GetTimestamps() { return fTimestamps; }
  Double_t* GetEnergies()  { return fEnergies; }

	Int_t NumberOfDigis() const { return fNrOfDigis; }
  Int_t NumberOfDigisAboveThresh() const;
	bool isInCluster(KoaRecDigi* theDigi) const;

	// Modifiers
  void Reset(Int_t id) {
    fNrOfDigis=0;
    fThreshold = 0;

    Int_t ch_id, det_id;
    KoaMapEncoder *fEncoder=KoaMapEncoder::Instance();
    ch_id = fEncoder->DecodeChannelID(id, det_id);
    fDetId = det_id;
  }

	void AddDigi(KoaRecDigi* theDigi);
  void SetThreshold(Double_t threshold) { fThreshold = threshold; }
  void SetGeoHandler(KoaGeoHandler* geoHandler) { fGeoHandler = geoHandler; }

 /* protected: */
 /*  template<class Archive> */
 /*  	void serialize(Archive & ar, const unsigned int version) */
 /*  	{ */
 /*  		boost::serialization::void_cast_register<KoaRecCluster, TObject>(); */

 /*  		ar & boost::serialization::base_object<TObject>(*this); */
 /*  		ar & fDetId; */
 /*  		ar & fIds; */
 /*  		ar & fEnergies; */
 /*  		ar & fTimestamps; */
 /*  	} */

private:
  Int_t    fDetId; // detId for this cluster
  Int_t    fNrOfDigis;
  Int_t    fIds[64]; // global ids of the digis
  Double_t   fEnergies[64]; // in keV
  Double_t   fTimestamps[64]; //

  Double_t fThreshold; //! threshold to count digis contributing to this cluster, in keV
  KoaGeoHandler *fGeoHandler; //!
  
	ClassDef(KoaRecCluster,2)
};

#endif // EMCCLUSTER_HH

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"KoaRec", payloadCode, "@",
"KoaRecAddFano", payloadCode, "@",
"KoaRecAddNoise", payloadCode, "@",
"KoaRecAddTimeJitter", payloadCode, "@",
"KoaRecAddTimeWalk", payloadCode, "@",
"KoaRecChargeCollection", payloadCode, "@",
"KoaRecChargeCollectionPar", payloadCode, "@",
"KoaRecChargeDivisionIdeal", payloadCode, "@",
"KoaRecCluster", payloadCode, "@",
"KoaRecContFact", payloadCode, "@",
"KoaRecDigi", payloadCode, "@",
"KoaRecDigitizationIdeal", payloadCode, "@",
"KoaRecFanoPar", payloadCode, "@",
"KoaRecGeo", payloadCode, "@",
"KoaRecGeoPar", payloadCode, "@",
"KoaRecMisalignPar", payloadCode, "@",
"KoaRecNoisePar", payloadCode, "@",
"KoaRecPoint", payloadCode, "@",
"KoaRecTimeJitterPar", payloadCode, "@",
"KoaRecTimeWalkPar", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__KoaSimpleRecDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__KoaSimpleRecDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__KoaSimpleRecDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__KoaSimpleRecDict() {
  TriggerDictionaryInitialization_G__KoaSimpleRecDict_Impl();
}
