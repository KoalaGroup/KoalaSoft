// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_jensdIdetectorsdIsdsdIG__SdsDict

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
#include "PndSdsTask.h"
#include "PndPersistencyTask.h"
#include "SdsDigi/PndSdsCalcFePixel.h"
#include "SdsDigi/PndSdsCalcPixel.h"
#include "SdsDigi/PndSdsCalcPixelDif.h"
#include "SdsDigi/PndSdsHybridHitProducer.h"
#include "SdsDigi/PndSdsHitProducerIdeal.h"
#include "SdsDigi/PndSdsNoiseProducer.h"
#include "SdsDigi/PndSdsChargeConversion.h"
#include "SdsDigi/PndSdsIdealChargeConversion.h"
#include "SdsDigi/PndSdsTotChargeConversion.h"
#include "SdsDigi/PndSdsAdcChargeConversion.h"
#include "SdsDigi/PndSdsDigiPixelWriteoutBuffer.h"
#include "SdsDigi/PndSdsDigiPixelSorterTask.h"
#include "SdsDigi/PndSdsDigiPixelRingSorter.h"
#include "SdsFEModel/PndSdsFE.h"
#include "SdsFEModel/PndSdsFESimple.h"
#include "SdsFEModel/PndSdsFEAmpModelSimple.h"
#include "SdsFEModel/PndSdsFESimple.h"
#include "SdsMC/PndSdsDetector.h"
#include "SdsMC/PndSdsGeo.h"
#include "SdsMC/PndSdsGeoPar.h"
#include "SdsTools/PndSdsPixelDigiPar.h"
#include "SdsTools/PndSdsTotDigiPar.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_PndPersistencyTask(void *p = 0);
   static void *newArray_PndPersistencyTask(Long_t size, void *p);
   static void delete_PndPersistencyTask(void *p);
   static void deleteArray_PndPersistencyTask(void *p);
   static void destruct_PndPersistencyTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndPersistencyTask*)
   {
      ::PndPersistencyTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndPersistencyTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndPersistencyTask", ::PndPersistencyTask::Class_Version(), "PndPersistencyTask.h", 22,
                  typeid(::PndPersistencyTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndPersistencyTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndPersistencyTask) );
      instance.SetNew(&new_PndPersistencyTask);
      instance.SetNewArray(&newArray_PndPersistencyTask);
      instance.SetDelete(&delete_PndPersistencyTask);
      instance.SetDeleteArray(&deleteArray_PndPersistencyTask);
      instance.SetDestructor(&destruct_PndPersistencyTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndPersistencyTask*)
   {
      return GenerateInitInstanceLocal((::PndPersistencyTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndPersistencyTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_PndSdsTask(void *p);
   static void deleteArray_PndSdsTask(void *p);
   static void destruct_PndSdsTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsTask*)
   {
      ::PndSdsTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsTask", ::PndSdsTask::Class_Version(), "", 20,
                  typeid(::PndSdsTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsTask) );
      instance.SetDelete(&delete_PndSdsTask);
      instance.SetDeleteArray(&deleteArray_PndSdsTask);
      instance.SetDestructor(&destruct_PndSdsTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsTask*)
   {
      return GenerateInitInstanceLocal((::PndSdsTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *PndSdsCalcFePixel_Dictionary();
   static void PndSdsCalcFePixel_TClassManip(TClass*);
   static void *new_PndSdsCalcFePixel(void *p = 0);
   static void *newArray_PndSdsCalcFePixel(Long_t size, void *p);
   static void delete_PndSdsCalcFePixel(void *p);
   static void deleteArray_PndSdsCalcFePixel(void *p);
   static void destruct_PndSdsCalcFePixel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsCalcFePixel*)
   {
      ::PndSdsCalcFePixel *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::PndSdsCalcFePixel));
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsCalcFePixel", "", 121,
                  typeid(::PndSdsCalcFePixel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &PndSdsCalcFePixel_Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsCalcFePixel) );
      instance.SetNew(&new_PndSdsCalcFePixel);
      instance.SetNewArray(&newArray_PndSdsCalcFePixel);
      instance.SetDelete(&delete_PndSdsCalcFePixel);
      instance.SetDeleteArray(&deleteArray_PndSdsCalcFePixel);
      instance.SetDestructor(&destruct_PndSdsCalcFePixel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsCalcFePixel*)
   {
      return GenerateInitInstanceLocal((::PndSdsCalcFePixel*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsCalcFePixel*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *PndSdsCalcFePixel_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::PndSdsCalcFePixel*)0x0)->GetClass();
      PndSdsCalcFePixel_TClassManip(theClass);
   return theClass;
   }

   static void PndSdsCalcFePixel_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *PndSdsCalcPixel_Dictionary();
   static void PndSdsCalcPixel_TClassManip(TClass*);
   static void *new_PndSdsCalcPixel(void *p = 0);
   static void *newArray_PndSdsCalcPixel(Long_t size, void *p);
   static void delete_PndSdsCalcPixel(void *p);
   static void deleteArray_PndSdsCalcPixel(void *p);
   static void destruct_PndSdsCalcPixel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsCalcPixel*)
   {
      ::PndSdsCalcPixel *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::PndSdsCalcPixel));
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsCalcPixel", "", 174,
                  typeid(::PndSdsCalcPixel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &PndSdsCalcPixel_Dictionary, isa_proxy, 0,
                  sizeof(::PndSdsCalcPixel) );
      instance.SetNew(&new_PndSdsCalcPixel);
      instance.SetNewArray(&newArray_PndSdsCalcPixel);
      instance.SetDelete(&delete_PndSdsCalcPixel);
      instance.SetDeleteArray(&deleteArray_PndSdsCalcPixel);
      instance.SetDestructor(&destruct_PndSdsCalcPixel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsCalcPixel*)
   {
      return GenerateInitInstanceLocal((::PndSdsCalcPixel*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsCalcPixel*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *PndSdsCalcPixel_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::PndSdsCalcPixel*)0x0)->GetClass();
      PndSdsCalcPixel_TClassManip(theClass);
   return theClass;
   }

   static void PndSdsCalcPixel_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *PndSdsCalcPixelDif_Dictionary();
   static void PndSdsCalcPixelDif_TClassManip(TClass*);
   static void *new_PndSdsCalcPixelDif(void *p = 0);
   static void *newArray_PndSdsCalcPixelDif(Long_t size, void *p);
   static void delete_PndSdsCalcPixelDif(void *p);
   static void deleteArray_PndSdsCalcPixelDif(void *p);
   static void destruct_PndSdsCalcPixelDif(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsCalcPixelDif*)
   {
      ::PndSdsCalcPixelDif *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::PndSdsCalcPixelDif));
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsCalcPixelDif", "", 262,
                  typeid(::PndSdsCalcPixelDif), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &PndSdsCalcPixelDif_Dictionary, isa_proxy, 0,
                  sizeof(::PndSdsCalcPixelDif) );
      instance.SetNew(&new_PndSdsCalcPixelDif);
      instance.SetNewArray(&newArray_PndSdsCalcPixelDif);
      instance.SetDelete(&delete_PndSdsCalcPixelDif);
      instance.SetDeleteArray(&deleteArray_PndSdsCalcPixelDif);
      instance.SetDestructor(&destruct_PndSdsCalcPixelDif);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsCalcPixelDif*)
   {
      return GenerateInitInstanceLocal((::PndSdsCalcPixelDif*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsCalcPixelDif*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *PndSdsCalcPixelDif_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::PndSdsCalcPixelDif*)0x0)->GetClass();
      PndSdsCalcPixelDif_TClassManip(theClass);
   return theClass;
   }

   static void PndSdsCalcPixelDif_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsPixelDigiPar(void *p = 0);
   static void *newArray_PndSdsPixelDigiPar(Long_t size, void *p);
   static void delete_PndSdsPixelDigiPar(void *p);
   static void deleteArray_PndSdsPixelDigiPar(void *p);
   static void destruct_PndSdsPixelDigiPar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsPixelDigiPar*)
   {
      ::PndSdsPixelDigiPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsPixelDigiPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsPixelDigiPar", ::PndSdsPixelDigiPar::Class_Version(), "PndSdsPixelDigiPar.h", 15,
                  typeid(::PndSdsPixelDigiPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsPixelDigiPar::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsPixelDigiPar) );
      instance.SetNew(&new_PndSdsPixelDigiPar);
      instance.SetNewArray(&newArray_PndSdsPixelDigiPar);
      instance.SetDelete(&delete_PndSdsPixelDigiPar);
      instance.SetDeleteArray(&deleteArray_PndSdsPixelDigiPar);
      instance.SetDestructor(&destruct_PndSdsPixelDigiPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsPixelDigiPar*)
   {
      return GenerateInitInstanceLocal((::PndSdsPixelDigiPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsPixelDigiPar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_PndSdsChargeConversion(void *p);
   static void deleteArray_PndSdsChargeConversion(void *p);
   static void destruct_PndSdsChargeConversion(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsChargeConversion*)
   {
      ::PndSdsChargeConversion *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsChargeConversion >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsChargeConversion", ::PndSdsChargeConversion::Class_Version(), "PndSdsChargeConversion.h", 14,
                  typeid(::PndSdsChargeConversion), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsChargeConversion::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsChargeConversion) );
      instance.SetDelete(&delete_PndSdsChargeConversion);
      instance.SetDeleteArray(&deleteArray_PndSdsChargeConversion);
      instance.SetDestructor(&destruct_PndSdsChargeConversion);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsChargeConversion*)
   {
      return GenerateInitInstanceLocal((::PndSdsChargeConversion*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsChargeConversion*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsTotDigiPar(void *p = 0);
   static void *newArray_PndSdsTotDigiPar(Long_t size, void *p);
   static void delete_PndSdsTotDigiPar(void *p);
   static void deleteArray_PndSdsTotDigiPar(void *p);
   static void destruct_PndSdsTotDigiPar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsTotDigiPar*)
   {
      ::PndSdsTotDigiPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsTotDigiPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsTotDigiPar", ::PndSdsTotDigiPar::Class_Version(), "PndSdsTotDigiPar.h", 15,
                  typeid(::PndSdsTotDigiPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsTotDigiPar::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsTotDigiPar) );
      instance.SetNew(&new_PndSdsTotDigiPar);
      instance.SetNewArray(&newArray_PndSdsTotDigiPar);
      instance.SetDelete(&delete_PndSdsTotDigiPar);
      instance.SetDeleteArray(&deleteArray_PndSdsTotDigiPar);
      instance.SetDestructor(&destruct_PndSdsTotDigiPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsTotDigiPar*)
   {
      return GenerateInitInstanceLocal((::PndSdsTotDigiPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsTotDigiPar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsTotChargeConversion(void *p = 0);
   static void *newArray_PndSdsTotChargeConversion(Long_t size, void *p);
   static void delete_PndSdsTotChargeConversion(void *p);
   static void deleteArray_PndSdsTotChargeConversion(void *p);
   static void destruct_PndSdsTotChargeConversion(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsTotChargeConversion*)
   {
      ::PndSdsTotChargeConversion *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsTotChargeConversion >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsTotChargeConversion", ::PndSdsTotChargeConversion::Class_Version(), "PndSdsTotChargeConversion.h", 32,
                  typeid(::PndSdsTotChargeConversion), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsTotChargeConversion::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsTotChargeConversion) );
      instance.SetNew(&new_PndSdsTotChargeConversion);
      instance.SetNewArray(&newArray_PndSdsTotChargeConversion);
      instance.SetDelete(&delete_PndSdsTotChargeConversion);
      instance.SetDeleteArray(&deleteArray_PndSdsTotChargeConversion);
      instance.SetDestructor(&destruct_PndSdsTotChargeConversion);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsTotChargeConversion*)
   {
      return GenerateInitInstanceLocal((::PndSdsTotChargeConversion*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsTotChargeConversion*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsFE(void *p = 0);
   static void *newArray_PndSdsFE(Long_t size, void *p);
   static void delete_PndSdsFE(void *p);
   static void deleteArray_PndSdsFE(void *p);
   static void destruct_PndSdsFE(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsFE*)
   {
      ::PndSdsFE *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsFE >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsFE", ::PndSdsFE::Class_Version(), "PndSdsFE.h", 24,
                  typeid(::PndSdsFE), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsFE::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsFE) );
      instance.SetNew(&new_PndSdsFE);
      instance.SetNewArray(&newArray_PndSdsFE);
      instance.SetDelete(&delete_PndSdsFE);
      instance.SetDeleteArray(&deleteArray_PndSdsFE);
      instance.SetDestructor(&destruct_PndSdsFE);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsFE*)
   {
      return GenerateInitInstanceLocal((::PndSdsFE*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsFE*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsDigiPixelWriteoutBuffer(void *p = 0);
   static void *newArray_PndSdsDigiPixelWriteoutBuffer(Long_t size, void *p);
   static void delete_PndSdsDigiPixelWriteoutBuffer(void *p);
   static void deleteArray_PndSdsDigiPixelWriteoutBuffer(void *p);
   static void destruct_PndSdsDigiPixelWriteoutBuffer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsDigiPixelWriteoutBuffer*)
   {
      ::PndSdsDigiPixelWriteoutBuffer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsDigiPixelWriteoutBuffer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsDigiPixelWriteoutBuffer", ::PndSdsDigiPixelWriteoutBuffer::Class_Version(), "PndSdsDigiPixelWriteoutBuffer.h", 16,
                  typeid(::PndSdsDigiPixelWriteoutBuffer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsDigiPixelWriteoutBuffer::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsDigiPixelWriteoutBuffer) );
      instance.SetNew(&new_PndSdsDigiPixelWriteoutBuffer);
      instance.SetNewArray(&newArray_PndSdsDigiPixelWriteoutBuffer);
      instance.SetDelete(&delete_PndSdsDigiPixelWriteoutBuffer);
      instance.SetDeleteArray(&deleteArray_PndSdsDigiPixelWriteoutBuffer);
      instance.SetDestructor(&destruct_PndSdsDigiPixelWriteoutBuffer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsDigiPixelWriteoutBuffer*)
   {
      return GenerateInitInstanceLocal((::PndSdsDigiPixelWriteoutBuffer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsDigiPixelWriteoutBuffer*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_PndSdsHybridHitProducer(void *p);
   static void deleteArray_PndSdsHybridHitProducer(void *p);
   static void destruct_PndSdsHybridHitProducer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsHybridHitProducer*)
   {
      ::PndSdsHybridHitProducer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsHybridHitProducer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsHybridHitProducer", ::PndSdsHybridHitProducer::Class_Version(), "", 344,
                  typeid(::PndSdsHybridHitProducer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsHybridHitProducer::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsHybridHitProducer) );
      instance.SetDelete(&delete_PndSdsHybridHitProducer);
      instance.SetDeleteArray(&deleteArray_PndSdsHybridHitProducer);
      instance.SetDestructor(&destruct_PndSdsHybridHitProducer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsHybridHitProducer*)
   {
      return GenerateInitInstanceLocal((::PndSdsHybridHitProducer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsHybridHitProducer*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_PndSdsHitProducerIdeal(void *p);
   static void deleteArray_PndSdsHitProducerIdeal(void *p);
   static void destruct_PndSdsHitProducerIdeal(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsHitProducerIdeal*)
   {
      ::PndSdsHitProducerIdeal *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsHitProducerIdeal >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsHitProducerIdeal", ::PndSdsHitProducerIdeal::Class_Version(), "", 518,
                  typeid(::PndSdsHitProducerIdeal), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsHitProducerIdeal::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsHitProducerIdeal) );
      instance.SetDelete(&delete_PndSdsHitProducerIdeal);
      instance.SetDeleteArray(&deleteArray_PndSdsHitProducerIdeal);
      instance.SetDestructor(&destruct_PndSdsHitProducerIdeal);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsHitProducerIdeal*)
   {
      return GenerateInitInstanceLocal((::PndSdsHitProducerIdeal*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsHitProducerIdeal*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_PndSdsNoiseProducer(void *p);
   static void deleteArray_PndSdsNoiseProducer(void *p);
   static void destruct_PndSdsNoiseProducer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsNoiseProducer*)
   {
      ::PndSdsNoiseProducer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsNoiseProducer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsNoiseProducer", ::PndSdsNoiseProducer::Class_Version(), "", 616,
                  typeid(::PndSdsNoiseProducer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsNoiseProducer::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsNoiseProducer) );
      instance.SetDelete(&delete_PndSdsNoiseProducer);
      instance.SetDeleteArray(&deleteArray_PndSdsNoiseProducer);
      instance.SetDestructor(&destruct_PndSdsNoiseProducer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsNoiseProducer*)
   {
      return GenerateInitInstanceLocal((::PndSdsNoiseProducer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsNoiseProducer*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsIdealChargeConversion(void *p = 0);
   static void *newArray_PndSdsIdealChargeConversion(Long_t size, void *p);
   static void delete_PndSdsIdealChargeConversion(void *p);
   static void deleteArray_PndSdsIdealChargeConversion(void *p);
   static void destruct_PndSdsIdealChargeConversion(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsIdealChargeConversion*)
   {
      ::PndSdsIdealChargeConversion *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsIdealChargeConversion >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsIdealChargeConversion", ::PndSdsIdealChargeConversion::Class_Version(), "", 805,
                  typeid(::PndSdsIdealChargeConversion), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsIdealChargeConversion::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsIdealChargeConversion) );
      instance.SetNew(&new_PndSdsIdealChargeConversion);
      instance.SetNewArray(&newArray_PndSdsIdealChargeConversion);
      instance.SetDelete(&delete_PndSdsIdealChargeConversion);
      instance.SetDeleteArray(&deleteArray_PndSdsIdealChargeConversion);
      instance.SetDestructor(&destruct_PndSdsIdealChargeConversion);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsIdealChargeConversion*)
   {
      return GenerateInitInstanceLocal((::PndSdsIdealChargeConversion*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsIdealChargeConversion*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsAdcChargeConversion(void *p = 0);
   static void *newArray_PndSdsAdcChargeConversion(Long_t size, void *p);
   static void delete_PndSdsAdcChargeConversion(void *p);
   static void deleteArray_PndSdsAdcChargeConversion(void *p);
   static void destruct_PndSdsAdcChargeConversion(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsAdcChargeConversion*)
   {
      ::PndSdsAdcChargeConversion *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsAdcChargeConversion >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsAdcChargeConversion", ::PndSdsAdcChargeConversion::Class_Version(), "", 921,
                  typeid(::PndSdsAdcChargeConversion), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsAdcChargeConversion::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsAdcChargeConversion) );
      instance.SetNew(&new_PndSdsAdcChargeConversion);
      instance.SetNewArray(&newArray_PndSdsAdcChargeConversion);
      instance.SetDelete(&delete_PndSdsAdcChargeConversion);
      instance.SetDeleteArray(&deleteArray_PndSdsAdcChargeConversion);
      instance.SetDestructor(&destruct_PndSdsAdcChargeConversion);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsAdcChargeConversion*)
   {
      return GenerateInitInstanceLocal((::PndSdsAdcChargeConversion*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsAdcChargeConversion*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsDigiPixelSorterTask(void *p = 0);
   static void *newArray_PndSdsDigiPixelSorterTask(Long_t size, void *p);
   static void delete_PndSdsDigiPixelSorterTask(void *p);
   static void deleteArray_PndSdsDigiPixelSorterTask(void *p);
   static void destruct_PndSdsDigiPixelSorterTask(void *p);
   static void streamer_PndSdsDigiPixelSorterTask(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsDigiPixelSorterTask*)
   {
      ::PndSdsDigiPixelSorterTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsDigiPixelSorterTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsDigiPixelSorterTask", ::PndSdsDigiPixelSorterTask::Class_Version(), "", 1004,
                  typeid(::PndSdsDigiPixelSorterTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsDigiPixelSorterTask::Dictionary, isa_proxy, 16,
                  sizeof(::PndSdsDigiPixelSorterTask) );
      instance.SetNew(&new_PndSdsDigiPixelSorterTask);
      instance.SetNewArray(&newArray_PndSdsDigiPixelSorterTask);
      instance.SetDelete(&delete_PndSdsDigiPixelSorterTask);
      instance.SetDeleteArray(&deleteArray_PndSdsDigiPixelSorterTask);
      instance.SetDestructor(&destruct_PndSdsDigiPixelSorterTask);
      instance.SetStreamerFunc(&streamer_PndSdsDigiPixelSorterTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsDigiPixelSorterTask*)
   {
      return GenerateInitInstanceLocal((::PndSdsDigiPixelSorterTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsDigiPixelSorterTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsDigiPixelRingSorter(void *p = 0);
   static void *newArray_PndSdsDigiPixelRingSorter(Long_t size, void *p);
   static void delete_PndSdsDigiPixelRingSorter(void *p);
   static void deleteArray_PndSdsDigiPixelRingSorter(void *p);
   static void destruct_PndSdsDigiPixelRingSorter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsDigiPixelRingSorter*)
   {
      ::PndSdsDigiPixelRingSorter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsDigiPixelRingSorter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsDigiPixelRingSorter", ::PndSdsDigiPixelRingSorter::Class_Version(), "", 1033,
                  typeid(::PndSdsDigiPixelRingSorter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsDigiPixelRingSorter::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsDigiPixelRingSorter) );
      instance.SetNew(&new_PndSdsDigiPixelRingSorter);
      instance.SetNewArray(&newArray_PndSdsDigiPixelRingSorter);
      instance.SetDelete(&delete_PndSdsDigiPixelRingSorter);
      instance.SetDeleteArray(&deleteArray_PndSdsDigiPixelRingSorter);
      instance.SetDestructor(&destruct_PndSdsDigiPixelRingSorter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsDigiPixelRingSorter*)
   {
      return GenerateInitInstanceLocal((::PndSdsDigiPixelRingSorter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsDigiPixelRingSorter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsFESimple(void *p = 0);
   static void *newArray_PndSdsFESimple(Long_t size, void *p);
   static void delete_PndSdsFESimple(void *p);
   static void deleteArray_PndSdsFESimple(void *p);
   static void destruct_PndSdsFESimple(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsFESimple*)
   {
      ::PndSdsFESimple *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsFESimple >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsFESimple", ::PndSdsFESimple::Class_Version(), "", 1199,
                  typeid(::PndSdsFESimple), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsFESimple::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsFESimple) );
      instance.SetNew(&new_PndSdsFESimple);
      instance.SetNewArray(&newArray_PndSdsFESimple);
      instance.SetDelete(&delete_PndSdsFESimple);
      instance.SetDeleteArray(&deleteArray_PndSdsFESimple);
      instance.SetDestructor(&destruct_PndSdsFESimple);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsFESimple*)
   {
      return GenerateInitInstanceLocal((::PndSdsFESimple*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsFESimple*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_PndSdsDetector(void *p);
   static void deleteArray_PndSdsDetector(void *p);
   static void destruct_PndSdsDetector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsDetector*)
   {
      ::PndSdsDetector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsDetector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsDetector", ::PndSdsDetector::Class_Version(), "", 1316,
                  typeid(::PndSdsDetector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsDetector::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsDetector) );
      instance.SetDelete(&delete_PndSdsDetector);
      instance.SetDeleteArray(&deleteArray_PndSdsDetector);
      instance.SetDestructor(&destruct_PndSdsDetector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsDetector*)
   {
      return GenerateInitInstanceLocal((::PndSdsDetector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsDetector*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsGeo(void *p = 0);
   static void *newArray_PndSdsGeo(Long_t size, void *p);
   static void delete_PndSdsGeo(void *p);
   static void deleteArray_PndSdsGeo(void *p);
   static void destruct_PndSdsGeo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsGeo*)
   {
      ::PndSdsGeo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsGeo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsGeo", ::PndSdsGeo::Class_Version(), "", 1548,
                  typeid(::PndSdsGeo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsGeo::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsGeo) );
      instance.SetNew(&new_PndSdsGeo);
      instance.SetNewArray(&newArray_PndSdsGeo);
      instance.SetDelete(&delete_PndSdsGeo);
      instance.SetDeleteArray(&deleteArray_PndSdsGeo);
      instance.SetDestructor(&destruct_PndSdsGeo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsGeo*)
   {
      return GenerateInitInstanceLocal((::PndSdsGeo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsGeo*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsGeoPar(void *p = 0);
   static void *newArray_PndSdsGeoPar(Long_t size, void *p);
   static void delete_PndSdsGeoPar(void *p);
   static void deleteArray_PndSdsGeoPar(void *p);
   static void destruct_PndSdsGeoPar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsGeoPar*)
   {
      ::PndSdsGeoPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsGeoPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsGeoPar", ::PndSdsGeoPar::Class_Version(), "", 1580,
                  typeid(::PndSdsGeoPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsGeoPar::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsGeoPar) );
      instance.SetNew(&new_PndSdsGeoPar);
      instance.SetNewArray(&newArray_PndSdsGeoPar);
      instance.SetDelete(&delete_PndSdsGeoPar);
      instance.SetDeleteArray(&deleteArray_PndSdsGeoPar);
      instance.SetDestructor(&destruct_PndSdsGeoPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsGeoPar*)
   {
      return GenerateInitInstanceLocal((::PndSdsGeoPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsGeoPar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr PndPersistencyTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndPersistencyTask::Class_Name()
{
   return "PndPersistencyTask";
}

//______________________________________________________________________________
const char *PndPersistencyTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndPersistencyTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndPersistencyTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndPersistencyTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndPersistencyTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndPersistencyTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndPersistencyTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndPersistencyTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsTask::Class_Name()
{
   return "PndSdsTask";
}

//______________________________________________________________________________
const char *PndSdsTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsPixelDigiPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsPixelDigiPar::Class_Name()
{
   return "PndSdsPixelDigiPar";
}

//______________________________________________________________________________
const char *PndSdsPixelDigiPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPixelDigiPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsPixelDigiPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPixelDigiPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsPixelDigiPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPixelDigiPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsPixelDigiPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPixelDigiPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsChargeConversion::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsChargeConversion::Class_Name()
{
   return "PndSdsChargeConversion";
}

//______________________________________________________________________________
const char *PndSdsChargeConversion::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsChargeConversion*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsChargeConversion::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsChargeConversion*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsChargeConversion::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsChargeConversion*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsChargeConversion::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsChargeConversion*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsTotDigiPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsTotDigiPar::Class_Name()
{
   return "PndSdsTotDigiPar";
}

//______________________________________________________________________________
const char *PndSdsTotDigiPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTotDigiPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsTotDigiPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTotDigiPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsTotDigiPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTotDigiPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsTotDigiPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTotDigiPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsTotChargeConversion::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsTotChargeConversion::Class_Name()
{
   return "PndSdsTotChargeConversion";
}

//______________________________________________________________________________
const char *PndSdsTotChargeConversion::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTotChargeConversion*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsTotChargeConversion::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTotChargeConversion*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsTotChargeConversion::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTotChargeConversion*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsTotChargeConversion::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTotChargeConversion*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsFE::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsFE::Class_Name()
{
   return "PndSdsFE";
}

//______________________________________________________________________________
const char *PndSdsFE::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsFE*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsFE::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsFE*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsFE::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsFE*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsFE::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsFE*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsDigiPixelWriteoutBuffer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsDigiPixelWriteoutBuffer::Class_Name()
{
   return "PndSdsDigiPixelWriteoutBuffer";
}

//______________________________________________________________________________
const char *PndSdsDigiPixelWriteoutBuffer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelWriteoutBuffer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsDigiPixelWriteoutBuffer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelWriteoutBuffer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsDigiPixelWriteoutBuffer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelWriteoutBuffer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsDigiPixelWriteoutBuffer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelWriteoutBuffer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsHybridHitProducer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsHybridHitProducer::Class_Name()
{
   return "PndSdsHybridHitProducer";
}

//______________________________________________________________________________
const char *PndSdsHybridHitProducer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsHybridHitProducer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsHybridHitProducer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsHybridHitProducer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsHybridHitProducer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsHybridHitProducer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsHybridHitProducer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsHybridHitProducer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsHitProducerIdeal::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsHitProducerIdeal::Class_Name()
{
   return "PndSdsHitProducerIdeal";
}

//______________________________________________________________________________
const char *PndSdsHitProducerIdeal::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsHitProducerIdeal*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsHitProducerIdeal::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsHitProducerIdeal*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsHitProducerIdeal::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsHitProducerIdeal*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsHitProducerIdeal::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsHitProducerIdeal*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsNoiseProducer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsNoiseProducer::Class_Name()
{
   return "PndSdsNoiseProducer";
}

//______________________________________________________________________________
const char *PndSdsNoiseProducer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsNoiseProducer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsNoiseProducer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsNoiseProducer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsNoiseProducer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsNoiseProducer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsNoiseProducer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsNoiseProducer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsIdealChargeConversion::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsIdealChargeConversion::Class_Name()
{
   return "PndSdsIdealChargeConversion";
}

//______________________________________________________________________________
const char *PndSdsIdealChargeConversion::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsIdealChargeConversion*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsIdealChargeConversion::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsIdealChargeConversion*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsIdealChargeConversion::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsIdealChargeConversion*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsIdealChargeConversion::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsIdealChargeConversion*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsAdcChargeConversion::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsAdcChargeConversion::Class_Name()
{
   return "PndSdsAdcChargeConversion";
}

//______________________________________________________________________________
const char *PndSdsAdcChargeConversion::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsAdcChargeConversion*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsAdcChargeConversion::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsAdcChargeConversion*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsAdcChargeConversion::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsAdcChargeConversion*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsAdcChargeConversion::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsAdcChargeConversion*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsDigiPixelSorterTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsDigiPixelSorterTask::Class_Name()
{
   return "PndSdsDigiPixelSorterTask";
}

//______________________________________________________________________________
const char *PndSdsDigiPixelSorterTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelSorterTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsDigiPixelSorterTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelSorterTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsDigiPixelSorterTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelSorterTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsDigiPixelSorterTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelSorterTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsDigiPixelRingSorter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsDigiPixelRingSorter::Class_Name()
{
   return "PndSdsDigiPixelRingSorter";
}

//______________________________________________________________________________
const char *PndSdsDigiPixelRingSorter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelRingSorter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsDigiPixelRingSorter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelRingSorter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsDigiPixelRingSorter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelRingSorter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsDigiPixelRingSorter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelRingSorter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsFESimple::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsFESimple::Class_Name()
{
   return "PndSdsFESimple";
}

//______________________________________________________________________________
const char *PndSdsFESimple::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsFESimple*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsFESimple::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsFESimple*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsFESimple::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsFESimple*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsFESimple::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsFESimple*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsDetector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsDetector::Class_Name()
{
   return "PndSdsDetector";
}

//______________________________________________________________________________
const char *PndSdsDetector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDetector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsDetector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDetector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsDetector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDetector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsDetector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDetector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsGeo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsGeo::Class_Name()
{
   return "PndSdsGeo";
}

//______________________________________________________________________________
const char *PndSdsGeo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsGeo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsGeo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsGeo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsGeo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsGeo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsGeo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsGeo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsGeoPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsGeoPar::Class_Name()
{
   return "PndSdsGeoPar";
}

//______________________________________________________________________________
const char *PndSdsGeoPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsGeoPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsGeoPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsGeoPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsGeoPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsGeoPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsGeoPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsGeoPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void PndPersistencyTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndPersistencyTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndPersistencyTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndPersistencyTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndPersistencyTask(void *p) {
      return  p ? new(p) ::PndPersistencyTask : new ::PndPersistencyTask;
   }
   static void *newArray_PndPersistencyTask(Long_t nElements, void *p) {
      return p ? new(p) ::PndPersistencyTask[nElements] : new ::PndPersistencyTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndPersistencyTask(void *p) {
      delete ((::PndPersistencyTask*)p);
   }
   static void deleteArray_PndPersistencyTask(void *p) {
      delete [] ((::PndPersistencyTask*)p);
   }
   static void destruct_PndPersistencyTask(void *p) {
      typedef ::PndPersistencyTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndPersistencyTask

//______________________________________________________________________________
void PndSdsTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsTask::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_PndSdsTask(void *p) {
      delete ((::PndSdsTask*)p);
   }
   static void deleteArray_PndSdsTask(void *p) {
      delete [] ((::PndSdsTask*)p);
   }
   static void destruct_PndSdsTask(void *p) {
      typedef ::PndSdsTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsTask

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsCalcFePixel(void *p) {
      return  p ? new(p) ::PndSdsCalcFePixel : new ::PndSdsCalcFePixel;
   }
   static void *newArray_PndSdsCalcFePixel(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsCalcFePixel[nElements] : new ::PndSdsCalcFePixel[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsCalcFePixel(void *p) {
      delete ((::PndSdsCalcFePixel*)p);
   }
   static void deleteArray_PndSdsCalcFePixel(void *p) {
      delete [] ((::PndSdsCalcFePixel*)p);
   }
   static void destruct_PndSdsCalcFePixel(void *p) {
      typedef ::PndSdsCalcFePixel current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsCalcFePixel

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsCalcPixel(void *p) {
      return  p ? new(p) ::PndSdsCalcPixel : new ::PndSdsCalcPixel;
   }
   static void *newArray_PndSdsCalcPixel(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsCalcPixel[nElements] : new ::PndSdsCalcPixel[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsCalcPixel(void *p) {
      delete ((::PndSdsCalcPixel*)p);
   }
   static void deleteArray_PndSdsCalcPixel(void *p) {
      delete [] ((::PndSdsCalcPixel*)p);
   }
   static void destruct_PndSdsCalcPixel(void *p) {
      typedef ::PndSdsCalcPixel current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsCalcPixel

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsCalcPixelDif(void *p) {
      return  p ? new(p) ::PndSdsCalcPixelDif : new ::PndSdsCalcPixelDif;
   }
   static void *newArray_PndSdsCalcPixelDif(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsCalcPixelDif[nElements] : new ::PndSdsCalcPixelDif[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsCalcPixelDif(void *p) {
      delete ((::PndSdsCalcPixelDif*)p);
   }
   static void deleteArray_PndSdsCalcPixelDif(void *p) {
      delete [] ((::PndSdsCalcPixelDif*)p);
   }
   static void destruct_PndSdsCalcPixelDif(void *p) {
      typedef ::PndSdsCalcPixelDif current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsCalcPixelDif

//______________________________________________________________________________
void PndSdsPixelDigiPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsPixelDigiPar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsPixelDigiPar::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsPixelDigiPar::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsPixelDigiPar(void *p) {
      return  p ? new(p) ::PndSdsPixelDigiPar : new ::PndSdsPixelDigiPar;
   }
   static void *newArray_PndSdsPixelDigiPar(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsPixelDigiPar[nElements] : new ::PndSdsPixelDigiPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsPixelDigiPar(void *p) {
      delete ((::PndSdsPixelDigiPar*)p);
   }
   static void deleteArray_PndSdsPixelDigiPar(void *p) {
      delete [] ((::PndSdsPixelDigiPar*)p);
   }
   static void destruct_PndSdsPixelDigiPar(void *p) {
      typedef ::PndSdsPixelDigiPar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsPixelDigiPar

//______________________________________________________________________________
void PndSdsChargeConversion::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsChargeConversion.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsChargeConversion::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsChargeConversion::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_PndSdsChargeConversion(void *p) {
      delete ((::PndSdsChargeConversion*)p);
   }
   static void deleteArray_PndSdsChargeConversion(void *p) {
      delete [] ((::PndSdsChargeConversion*)p);
   }
   static void destruct_PndSdsChargeConversion(void *p) {
      typedef ::PndSdsChargeConversion current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsChargeConversion

//______________________________________________________________________________
void PndSdsTotDigiPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsTotDigiPar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsTotDigiPar::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsTotDigiPar::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsTotDigiPar(void *p) {
      return  p ? new(p) ::PndSdsTotDigiPar : new ::PndSdsTotDigiPar;
   }
   static void *newArray_PndSdsTotDigiPar(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsTotDigiPar[nElements] : new ::PndSdsTotDigiPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsTotDigiPar(void *p) {
      delete ((::PndSdsTotDigiPar*)p);
   }
   static void deleteArray_PndSdsTotDigiPar(void *p) {
      delete [] ((::PndSdsTotDigiPar*)p);
   }
   static void destruct_PndSdsTotDigiPar(void *p) {
      typedef ::PndSdsTotDigiPar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsTotDigiPar

//______________________________________________________________________________
void PndSdsTotChargeConversion::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsTotChargeConversion.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsTotChargeConversion::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsTotChargeConversion::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsTotChargeConversion(void *p) {
      return  p ? new(p) ::PndSdsTotChargeConversion : new ::PndSdsTotChargeConversion;
   }
   static void *newArray_PndSdsTotChargeConversion(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsTotChargeConversion[nElements] : new ::PndSdsTotChargeConversion[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsTotChargeConversion(void *p) {
      delete ((::PndSdsTotChargeConversion*)p);
   }
   static void deleteArray_PndSdsTotChargeConversion(void *p) {
      delete [] ((::PndSdsTotChargeConversion*)p);
   }
   static void destruct_PndSdsTotChargeConversion(void *p) {
      typedef ::PndSdsTotChargeConversion current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsTotChargeConversion

//______________________________________________________________________________
void PndSdsFE::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsFE.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsFE::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsFE::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsFE(void *p) {
      return  p ? new(p) ::PndSdsFE : new ::PndSdsFE;
   }
   static void *newArray_PndSdsFE(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsFE[nElements] : new ::PndSdsFE[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsFE(void *p) {
      delete ((::PndSdsFE*)p);
   }
   static void deleteArray_PndSdsFE(void *p) {
      delete [] ((::PndSdsFE*)p);
   }
   static void destruct_PndSdsFE(void *p) {
      typedef ::PndSdsFE current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsFE

//______________________________________________________________________________
void PndSdsDigiPixelWriteoutBuffer::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsDigiPixelWriteoutBuffer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsDigiPixelWriteoutBuffer::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsDigiPixelWriteoutBuffer::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsDigiPixelWriteoutBuffer(void *p) {
      return  p ? new(p) ::PndSdsDigiPixelWriteoutBuffer : new ::PndSdsDigiPixelWriteoutBuffer;
   }
   static void *newArray_PndSdsDigiPixelWriteoutBuffer(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsDigiPixelWriteoutBuffer[nElements] : new ::PndSdsDigiPixelWriteoutBuffer[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsDigiPixelWriteoutBuffer(void *p) {
      delete ((::PndSdsDigiPixelWriteoutBuffer*)p);
   }
   static void deleteArray_PndSdsDigiPixelWriteoutBuffer(void *p) {
      delete [] ((::PndSdsDigiPixelWriteoutBuffer*)p);
   }
   static void destruct_PndSdsDigiPixelWriteoutBuffer(void *p) {
      typedef ::PndSdsDigiPixelWriteoutBuffer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsDigiPixelWriteoutBuffer

//______________________________________________________________________________
void PndSdsHybridHitProducer::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsHybridHitProducer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsHybridHitProducer::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsHybridHitProducer::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_PndSdsHybridHitProducer(void *p) {
      delete ((::PndSdsHybridHitProducer*)p);
   }
   static void deleteArray_PndSdsHybridHitProducer(void *p) {
      delete [] ((::PndSdsHybridHitProducer*)p);
   }
   static void destruct_PndSdsHybridHitProducer(void *p) {
      typedef ::PndSdsHybridHitProducer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsHybridHitProducer

//______________________________________________________________________________
void PndSdsHitProducerIdeal::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsHitProducerIdeal.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsHitProducerIdeal::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsHitProducerIdeal::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_PndSdsHitProducerIdeal(void *p) {
      delete ((::PndSdsHitProducerIdeal*)p);
   }
   static void deleteArray_PndSdsHitProducerIdeal(void *p) {
      delete [] ((::PndSdsHitProducerIdeal*)p);
   }
   static void destruct_PndSdsHitProducerIdeal(void *p) {
      typedef ::PndSdsHitProducerIdeal current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsHitProducerIdeal

//______________________________________________________________________________
void PndSdsNoiseProducer::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsNoiseProducer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsNoiseProducer::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsNoiseProducer::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_PndSdsNoiseProducer(void *p) {
      delete ((::PndSdsNoiseProducer*)p);
   }
   static void deleteArray_PndSdsNoiseProducer(void *p) {
      delete [] ((::PndSdsNoiseProducer*)p);
   }
   static void destruct_PndSdsNoiseProducer(void *p) {
      typedef ::PndSdsNoiseProducer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsNoiseProducer

//______________________________________________________________________________
void PndSdsIdealChargeConversion::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsIdealChargeConversion.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsIdealChargeConversion::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsIdealChargeConversion::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsIdealChargeConversion(void *p) {
      return  p ? new(p) ::PndSdsIdealChargeConversion : new ::PndSdsIdealChargeConversion;
   }
   static void *newArray_PndSdsIdealChargeConversion(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsIdealChargeConversion[nElements] : new ::PndSdsIdealChargeConversion[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsIdealChargeConversion(void *p) {
      delete ((::PndSdsIdealChargeConversion*)p);
   }
   static void deleteArray_PndSdsIdealChargeConversion(void *p) {
      delete [] ((::PndSdsIdealChargeConversion*)p);
   }
   static void destruct_PndSdsIdealChargeConversion(void *p) {
      typedef ::PndSdsIdealChargeConversion current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsIdealChargeConversion

//______________________________________________________________________________
void PndSdsAdcChargeConversion::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsAdcChargeConversion.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsAdcChargeConversion::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsAdcChargeConversion::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsAdcChargeConversion(void *p) {
      return  p ? new(p) ::PndSdsAdcChargeConversion : new ::PndSdsAdcChargeConversion;
   }
   static void *newArray_PndSdsAdcChargeConversion(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsAdcChargeConversion[nElements] : new ::PndSdsAdcChargeConversion[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsAdcChargeConversion(void *p) {
      delete ((::PndSdsAdcChargeConversion*)p);
   }
   static void deleteArray_PndSdsAdcChargeConversion(void *p) {
      delete [] ((::PndSdsAdcChargeConversion*)p);
   }
   static void destruct_PndSdsAdcChargeConversion(void *p) {
      typedef ::PndSdsAdcChargeConversion current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsAdcChargeConversion

//______________________________________________________________________________
void PndSdsDigiPixelSorterTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsDigiPixelSorterTask.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairRingSorterTask::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, PndSdsDigiPixelSorterTask::IsA());
   } else {
      R__c = R__b.WriteVersion(PndSdsDigiPixelSorterTask::IsA(), kTRUE);
      FairRingSorterTask::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsDigiPixelSorterTask(void *p) {
      return  p ? new(p) ::PndSdsDigiPixelSorterTask : new ::PndSdsDigiPixelSorterTask;
   }
   static void *newArray_PndSdsDigiPixelSorterTask(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsDigiPixelSorterTask[nElements] : new ::PndSdsDigiPixelSorterTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsDigiPixelSorterTask(void *p) {
      delete ((::PndSdsDigiPixelSorterTask*)p);
   }
   static void deleteArray_PndSdsDigiPixelSorterTask(void *p) {
      delete [] ((::PndSdsDigiPixelSorterTask*)p);
   }
   static void destruct_PndSdsDigiPixelSorterTask(void *p) {
      typedef ::PndSdsDigiPixelSorterTask current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_PndSdsDigiPixelSorterTask(TBuffer &buf, void *obj) {
      ((::PndSdsDigiPixelSorterTask*)obj)->::PndSdsDigiPixelSorterTask::Streamer(buf);
   }
} // end of namespace ROOT for class ::PndSdsDigiPixelSorterTask

//______________________________________________________________________________
void PndSdsDigiPixelRingSorter::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsDigiPixelRingSorter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsDigiPixelRingSorter::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsDigiPixelRingSorter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsDigiPixelRingSorter(void *p) {
      return  p ? new(p) ::PndSdsDigiPixelRingSorter : new ::PndSdsDigiPixelRingSorter;
   }
   static void *newArray_PndSdsDigiPixelRingSorter(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsDigiPixelRingSorter[nElements] : new ::PndSdsDigiPixelRingSorter[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsDigiPixelRingSorter(void *p) {
      delete ((::PndSdsDigiPixelRingSorter*)p);
   }
   static void deleteArray_PndSdsDigiPixelRingSorter(void *p) {
      delete [] ((::PndSdsDigiPixelRingSorter*)p);
   }
   static void destruct_PndSdsDigiPixelRingSorter(void *p) {
      typedef ::PndSdsDigiPixelRingSorter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsDigiPixelRingSorter

//______________________________________________________________________________
void PndSdsFESimple::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsFESimple.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsFESimple::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsFESimple::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsFESimple(void *p) {
      return  p ? new(p) ::PndSdsFESimple : new ::PndSdsFESimple;
   }
   static void *newArray_PndSdsFESimple(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsFESimple[nElements] : new ::PndSdsFESimple[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsFESimple(void *p) {
      delete ((::PndSdsFESimple*)p);
   }
   static void deleteArray_PndSdsFESimple(void *p) {
      delete [] ((::PndSdsFESimple*)p);
   }
   static void destruct_PndSdsFESimple(void *p) {
      typedef ::PndSdsFESimple current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsFESimple

//______________________________________________________________________________
void PndSdsDetector::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsDetector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsDetector::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsDetector::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_PndSdsDetector(void *p) {
      delete ((::PndSdsDetector*)p);
   }
   static void deleteArray_PndSdsDetector(void *p) {
      delete [] ((::PndSdsDetector*)p);
   }
   static void destruct_PndSdsDetector(void *p) {
      typedef ::PndSdsDetector current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsDetector

//______________________________________________________________________________
void PndSdsGeo::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsGeo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsGeo::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsGeo::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsGeo(void *p) {
      return  p ? new(p) ::PndSdsGeo : new ::PndSdsGeo;
   }
   static void *newArray_PndSdsGeo(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsGeo[nElements] : new ::PndSdsGeo[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsGeo(void *p) {
      delete ((::PndSdsGeo*)p);
   }
   static void deleteArray_PndSdsGeo(void *p) {
      delete [] ((::PndSdsGeo*)p);
   }
   static void destruct_PndSdsGeo(void *p) {
      typedef ::PndSdsGeo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsGeo

//______________________________________________________________________________
void PndSdsGeoPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsGeoPar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsGeoPar::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsGeoPar::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsGeoPar(void *p) {
      return  p ? new(p) ::PndSdsGeoPar : new ::PndSdsGeoPar;
   }
   static void *newArray_PndSdsGeoPar(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsGeoPar[nElements] : new ::PndSdsGeoPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsGeoPar(void *p) {
      delete ((::PndSdsGeoPar*)p);
   }
   static void deleteArray_PndSdsGeoPar(void *p) {
      delete [] ((::PndSdsGeoPar*)p);
   }
   static void destruct_PndSdsGeoPar(void *p) {
      typedef ::PndSdsGeoPar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsGeoPar

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
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 216,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlEPndSdsPixelgR_Dictionary();
   static void vectorlEPndSdsPixelgR_TClassManip(TClass*);
   static void *new_vectorlEPndSdsPixelgR(void *p = 0);
   static void *newArray_vectorlEPndSdsPixelgR(Long_t size, void *p);
   static void delete_vectorlEPndSdsPixelgR(void *p);
   static void deleteArray_vectorlEPndSdsPixelgR(void *p);
   static void destruct_vectorlEPndSdsPixelgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<PndSdsPixel>*)
   {
      vector<PndSdsPixel> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<PndSdsPixel>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<PndSdsPixel>", -2, "vector", 216,
                  typeid(vector<PndSdsPixel>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEPndSdsPixelgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<PndSdsPixel>) );
      instance.SetNew(&new_vectorlEPndSdsPixelgR);
      instance.SetNewArray(&newArray_vectorlEPndSdsPixelgR);
      instance.SetDelete(&delete_vectorlEPndSdsPixelgR);
      instance.SetDeleteArray(&deleteArray_vectorlEPndSdsPixelgR);
      instance.SetDestructor(&destruct_vectorlEPndSdsPixelgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<PndSdsPixel> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<PndSdsPixel>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPndSdsPixelgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<PndSdsPixel>*)0x0)->GetClass();
      vectorlEPndSdsPixelgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPndSdsPixelgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPndSdsPixelgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<PndSdsPixel> : new vector<PndSdsPixel>;
   }
   static void *newArray_vectorlEPndSdsPixelgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<PndSdsPixel>[nElements] : new vector<PndSdsPixel>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPndSdsPixelgR(void *p) {
      delete ((vector<PndSdsPixel>*)p);
   }
   static void deleteArray_vectorlEPndSdsPixelgR(void *p) {
      delete [] ((vector<PndSdsPixel>*)p);
   }
   static void destruct_vectorlEPndSdsPixelgR(void *p) {
      typedef vector<PndSdsPixel> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<PndSdsPixel>

namespace ROOT {
   static TClass *maplETStringcOdoublegR_Dictionary();
   static void maplETStringcOdoublegR_TClassManip(TClass*);
   static void *new_maplETStringcOdoublegR(void *p = 0);
   static void *newArray_maplETStringcOdoublegR(Long_t size, void *p);
   static void delete_maplETStringcOdoublegR(void *p);
   static void deleteArray_maplETStringcOdoublegR(void *p);
   static void destruct_maplETStringcOdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,double>*)
   {
      map<TString,double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,double>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,double>", -2, "map", 99,
                  typeid(map<TString,double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplETStringcOdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,double>) );
      instance.SetNew(&new_maplETStringcOdoublegR);
      instance.SetNewArray(&newArray_maplETStringcOdoublegR);
      instance.SetDelete(&delete_maplETStringcOdoublegR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOdoublegR);
      instance.SetDestructor(&destruct_maplETStringcOdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<TString,double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,double>*)0x0)->GetClass();
      maplETStringcOdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,double> : new map<TString,double>;
   }
   static void *newArray_maplETStringcOdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,double>[nElements] : new map<TString,double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOdoublegR(void *p) {
      delete ((map<TString,double>*)p);
   }
   static void deleteArray_maplETStringcOdoublegR(void *p) {
      delete [] ((map<TString,double>*)p);
   }
   static void destruct_maplETStringcOdoublegR(void *p) {
      typedef map<TString,double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,double>

namespace ROOT {
   static TClass *maplEPndSdsDigiPixelcOdoublegR_Dictionary();
   static void maplEPndSdsDigiPixelcOdoublegR_TClassManip(TClass*);
   static void *new_maplEPndSdsDigiPixelcOdoublegR(void *p = 0);
   static void *newArray_maplEPndSdsDigiPixelcOdoublegR(Long_t size, void *p);
   static void delete_maplEPndSdsDigiPixelcOdoublegR(void *p);
   static void deleteArray_maplEPndSdsDigiPixelcOdoublegR(void *p);
   static void destruct_maplEPndSdsDigiPixelcOdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<PndSdsDigiPixel,double>*)
   {
      map<PndSdsDigiPixel,double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<PndSdsDigiPixel,double>));
      static ::ROOT::TGenericClassInfo 
         instance("map<PndSdsDigiPixel,double>", -2, "map", 99,
                  typeid(map<PndSdsDigiPixel,double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEPndSdsDigiPixelcOdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(map<PndSdsDigiPixel,double>) );
      instance.SetNew(&new_maplEPndSdsDigiPixelcOdoublegR);
      instance.SetNewArray(&newArray_maplEPndSdsDigiPixelcOdoublegR);
      instance.SetDelete(&delete_maplEPndSdsDigiPixelcOdoublegR);
      instance.SetDeleteArray(&deleteArray_maplEPndSdsDigiPixelcOdoublegR);
      instance.SetDestructor(&destruct_maplEPndSdsDigiPixelcOdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<PndSdsDigiPixel,double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<PndSdsDigiPixel,double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEPndSdsDigiPixelcOdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<PndSdsDigiPixel,double>*)0x0)->GetClass();
      maplEPndSdsDigiPixelcOdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void maplEPndSdsDigiPixelcOdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEPndSdsDigiPixelcOdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<PndSdsDigiPixel,double> : new map<PndSdsDigiPixel,double>;
   }
   static void *newArray_maplEPndSdsDigiPixelcOdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<PndSdsDigiPixel,double>[nElements] : new map<PndSdsDigiPixel,double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEPndSdsDigiPixelcOdoublegR(void *p) {
      delete ((map<PndSdsDigiPixel,double>*)p);
   }
   static void deleteArray_maplEPndSdsDigiPixelcOdoublegR(void *p) {
      delete [] ((map<PndSdsDigiPixel,double>*)p);
   }
   static void destruct_maplEPndSdsDigiPixelcOdoublegR(void *p) {
      typedef map<PndSdsDigiPixel,double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<PndSdsDigiPixel,double>

namespace {
  void TriggerDictionaryInitialization_G__SdsDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/home/yong/src/KoalaSoft/detectors/sds",
"/home/yong/src/KoalaSoft/detectors/sds/",
"/home/yong/src/KoalaSoft/detectors/lmdforward/",
"/home/yong/src/KoalaSoft/detectors/lmdforward/LmdDigi",
"/home/yong/src/KoalaSoft/data/",
"/home/yong/src/KoalaSoft/data/MCData",
"/home/yong/src/KoalaSoft/data/SdsData",
"/home/yong/src/KoalaSoft/tools",
"/home/yong/src/KoalaSoft/detectors/sds/SdsMC",
"/home/yong/src/KoalaSoft/detectors/sds/SdsTools",
"/home/yong/src/KoalaSoft/detectors/sds/SdsDigi",
"/home/yong/src/KoalaSoft/detectors/sds/SdsFEModel",
"/home/yong/src/KoalaSoft/detectors/sds/SdsReco",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include/TGeant3",
"/home/yong/fairroot/v18_jun19/include",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/src/KoalaSoft/build_jens/detectors/sds/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__SdsDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$PndPersistencyTask.h")))  PndPersistencyTask;
class PndSdsTask;
class PndSdsCalcFePixel;
class PndSdsCalcPixel;
class PndSdsCalcPixelDif;
class __attribute__((annotate("$clingAutoload$PndSdsPixelDigiPar.h")))  PndSdsPixelDigiPar;
class __attribute__((annotate("$clingAutoload$PndSdsChargeConversion.h")))  PndSdsChargeConversion;
class __attribute__((annotate("$clingAutoload$PndSdsTotDigiPar.h")))  PndSdsTotDigiPar;
class __attribute__((annotate("$clingAutoload$PndSdsTotChargeConversion.h")))  __attribute__((annotate("$clingAutoload$PndSdsFE.h")))  PndSdsTotChargeConversion;
class __attribute__((annotate("$clingAutoload$PndSdsFE.h")))  PndSdsFE;
class __attribute__((annotate("$clingAutoload$PndSdsDigiPixelWriteoutBuffer.h")))  PndSdsDigiPixelWriteoutBuffer;
class PndSdsHybridHitProducer;
class PndSdsHitProducerIdeal;
class PndSdsNoiseProducer;
class PndSdsIdealChargeConversion;
class PndSdsAdcChargeConversion;
class PndSdsDigiPixelSorterTask;
class PndSdsDigiPixelRingSorter;
class PndSdsFESimple;
class PndSdsDetector;
class __attribute__((annotate(R"ATTRDUMP(Class for PndSds)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Class for PndSds)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Class for PndSds)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Class for PndSds)ATTRDUMP"))) PndSdsGeo;
class PndSdsGeoPar;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__SdsDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
/*
 * PndSdsTask.h
 *
 *  Created on: Jul 7, 2010
 *      Author: stockman
 */

#ifndef PNDSDSTASK_H_
#define PNDSDSTASK_H_
#include <PndPersistencyTask.h>
#include "FairRootManager.h"

#include <iostream>

class PndSdsTask: public PndPersistencyTask {
public:
	PndSdsTask();

	PndSdsTask(const char* name, Int_t iVerbose = 1) : 
  PndPersistencyTask(name, iVerbose),
  fInBranchName(""),
	fOutBranchName(""),
	fFolderName(""),
	fInBranchId(-1),
	fOutBranchId(-1)
  {};
	virtual ~PndSdsTask();

	virtual void SetBranchNames()= 0;
	virtual void SetInBranchId(){
		FairRootManager *ioman = FairRootManager::Instance();
		fInBranchId = ioman->GetBranchId(fInBranchName);
		fOutBranchId = ioman->GetBranchId(fOutBranchName);
		std::cout << "InBranchId: " << fInBranchId << " for Branch: " << fInBranchName.Data() << std::endl;
		std::cout << "OutBranchId: " << fOutBranchId << " for Branch: " << fOutBranchName.Data() << std::endl;
	}

protected:
	TString fInBranchName;
	TString fOutBranchName;
	TString fFolderName;

	Int_t fInBranchId;
	Int_t fOutBranchId;

	ClassDef(PndSdsTask,1);
};

#endif /* PNDSDSTASK_H_ */
// -------------------------------------------------------------------------
// -----                 PndPersistencyTask header file                    -----
// -----           Created 28/02/18  by T. Stockmanns		         -----
// -------------------------------------------------------------------------


/** PndPersistencyTask.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Version 28/02/18 by T.Stockmanns
 **
 ** This class handles the persistency parameter used to define if an output branch is stored in a root file
 ** or not.
 **/


#ifndef PndBranchTask_H
#define PndBranchTask_H

#include "FairTask.h"

class PndPersistencyTask : public FairTask
{

 public:

  PndPersistencyTask();
  PndPersistencyTask(const char* name, Int_t iVerbose = 1);
  virtual ~PndPersistencyTask();

  void SetPersistency(Bool_t val=kTRUE){ fPersistency = val; }
  Bool_t GetPersistency(){ return fPersistency; }

 private:
  Bool_t fPersistency;                    //!   ///< Persistency flag


  ClassDef(PndPersistencyTask,1)


};






#endif
#ifndef PNDSDSCALCFEPIXEL_H
#define PNDSDSCALCFEPIXEL_H

#include <vector>
#include "PndSdsPixel.h"
#include "TVector3.h"

class PndSdsPixelDigiPar;

//! Class to calculate the position of digis on a front-end from the digis on a sensor
/** @author T.Stockmanns <t.stockmanns@fz-juelich.de>
 *
 * This class calculates the column, row and front-end number of a digi
 * from the column, row number on a sensor and vice versa
 */

class PndSdsCalcFePixel
  {
    public :
	///Default constructor
	PndSdsCalcFePixel();
	///Main constructor
	PndSdsCalcFePixel(const PndSdsPixelDigiPar& digi_par);
	~PndSdsCalcFePixel();
    
    /*void SetNCols(Int_t ncols){fNcols = ncols;};
    void SetNRows(Int_t nrows){fNrows = nrows;};
    void SetMaxFE(Int_t maxFE){fMaxFEperCol = maxFE;};
    Int_t GetNCols() const { return fNcols;};
    Int_t GetNRows() const { return fNrows;};
    Int_t GetMaxFE() const { return fMaxFEperCol;};*/

    ///Main function to calculate front-end hits
    std::vector<PndSdsPixel> CalcFEHits(const std::vector<PndSdsPixel>& sensor_hits);
    
    ///Main function to calculate sensor hits
    void CalcSensorColRow(Int_t& col, Int_t& row, const Int_t fe) const;
  protected : 
    Int_t fNcols;       /// number of columns on a front-end chip
    Int_t fNrows;       /// nrows number of rows on a front-end chip
    Int_t fMaxFEperCol; /// maximum number of front-end chip per column on a sensor
    Int_t fMaxFEperRow; /// maximum number of front-end chip per row on a sensor
  };


#endif /*PNDSDSCALCFEPIXEL_H*/
#ifndef PNDSDSCALCPIXEL_H
#define PNDSDSCALCPIXEL_H

#include "PndSdsPixel.h"
#include "FairGeoVector.h"
#include <iostream>
#include <vector>
//#include <XYVector.h>
//#include "CLHEP/Vector/TwoVector.h"
//! Calculates the pixels (digis) fired from a particle hitting the sensor
/**
 *  @author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
 * This class gets as an input the point where the particle enters the sensor,
 * where it leaves the sensor and the deposited energy. It calculates the track
 * of the particle between these two points and determines the pixels lying on the
 * track. The total energy of the particle is then distributed acording to the
 * pathlength to the pixels. The output is a vector<PndSdsPixel> of the fired sensor pixels
 * with the energy deposited in the pixels.
 * If a noise value is given a gausian distributed energy with a sigma of (noise) is added (or substracted) to
 * the energy deposited in one pixel.
 * If a threshold value is given all pixels with energies below threshold are ignored
 */
class PndSdsCalcPixel
{
	public :  
  ///Default constructor
  PndSdsCalcPixel();			
  
  ///Main constructor
  ///@param w width of sensor pixel [cm]
  ///@param l length of sensor pixel [cm]
  ///@param threshold discriminator threshold of pixel [e]
  ///@param noise total noise of pixel [e]
  PndSdsCalcPixel(Double_t w, Double_t l, Double_t threshold = 0, Double_t noise = 0);
  
  ///Main function to calculate the vector<PndSdsPixel> of fired pixel
  std::vector<PndSdsPixel> GetPixels (Double_t inx, Double_t iny,
                                      Double_t outx, Double_t outy, Double_t energy);
  // Alternative in terms of I/O
  Int_t GetPixelsAlternative(Double_t inx, Double_t iny,
                             Double_t outx, Double_t outy,
                             Double_t energy, std::vector<Int_t>& cols, std::vector<Int_t>& rows,
                             std::vector<Double_t>& charges);			   
  void SetVerboseLevel(Int_t level){ fVerboseLevel = level;};
  std::ostream& operator<<(std::ostream& out);
	private :
  std::vector<PndSdsPixel> fPixels;
  Double_t fPixelWidth;
  Double_t fPixelLength;
  Double_t fThreshold;
  Double_t fNoise;
  Double_t fEnergy;
  Int_t fVerboseLevel;
  
  typedef enum {kQuadUNDEF, kUR, kUL, kDL, kDR} EQuadrantType;
  typedef enum {kPixelUNDEF, kU, kD, kL, kR} ENextPixelType;
  
  EQuadrantType fQuad;
  ENextPixelType fNextPixel;
  
  FairGeoVector fIn;	//entry point of particle in sensor
  FairGeoVector fOut;	//exit point of particle out of sensor
  FairGeoVector fDir;	//direction of particle inside sensor
  FairGeoVector fPos;	//actual position of stepping inside sensor
  
  FairGeoVector fCon;
  
  PndSdsPixel fActivePixel;
  Double_t fCperL;		//Charge per Tracklength;
  bool fStop;
  void CalcConMatrix();
  void ApplyConMatrix();
  void CalcQuadrant();
  void CalcCperL(Double_t Energy);
  void CalcStartPixel();		//pixel 0,0 is in lower left corner
  void CalcPixel();
  void ConvertPixels();
  
  Double_t SmearCharge(Double_t charge);

};

#endif
#ifndef PNDSDSCALCPIXELDIF_H
#define PNDSDSCALCPIXELDIF_H

#include "PndSdsPixel.h"
#include "FairGeoVector.h"
#include <iostream>
#include <vector>
//#include <XYVector.h>
//#include "CLHEP/Vector/TwoVector.h"
//! Calculates the pixels (digis) fired from a particle hitting the sensor
/**
 *  @author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
 *  @author Ralf Kliemt, Uni Bonn
 * This class gets as an input the point where the particle enters the sensor,
 * where it leaves the sensor and the deposited energy. It calculates the track
 * of the particle between these two points and determines the pixels lying on the
 * track. The total energy of the particle is then distributed acording to a gaussian widened path
 * to the pixels. The output is a vector<PndSdsPixel> of the fired sensor pixels
 * with the energy deposited in the pixels.
 * If a noise value is given a gausian distributed energy with a sigma of (noise) is added (or substracted) to
 * the energy deposited in one pixel.
 * If a threshold value is given all pixels with energies below threshold are ignored
 */

class PndSdsPixelDigiPar;

class PndSdsCalcPixelDif
  {
  public:
		///Default constructor
		PndSdsCalcPixelDif();

	  ///Main constructor
	  ///@param w width of sensor pixel [cm]
	  ///@param l length of sensor pixel [cm]
    ///@param qspread charge cloud gaussian width
	  ///@param threshold discriminator threshold of pixel [e]
	  ///@param noise total noise of pixel [e]
	  PndSdsCalcPixelDif(Double_t w, Double_t l, Double_t qspread = 0, Double_t threshold = 0, Double_t noise = 0,Double_t nrows=10, Double_t ncols=10);
	  PndSdsCalcPixelDif(const PndSdsPixelDigiPar& digi_par);

	  ///Main function to calculate the vector<PndSdsPixel> of fired pixel
	  std::vector<PndSdsPixel> GetPixels (Double_t inx, Double_t iny,
                                        Double_t outx, Double_t outy,
                                        Double_t energy);

    Int_t GetPixelsAlternative(Double_t inx, Double_t iny,
                               Double_t outx, Double_t outy,
                               Double_t energy, std::vector<Int_t>& cols, std::vector<Int_t>& rows,
                               std::vector<Double_t>& charges);

	  void SetVerboseLevel(Int_t level){ fVerboseLevel = level;};
	  std::ostream& operator<<(std::ostream& out);

  private:
    Double_t ChargeFromEloss(Double_t eloss) const {return eloss/(3.61e-9);}
    void InjectPixelCharge(Int_t col, Int_t row, Double_t charge);

		std::vector<PndSdsPixel> fPixels;
    PndSdsPixel fActivePixel;

		Double_t fPixelSizeX;
		Double_t fPixelSizeY;
		Double_t fRows;
		Double_t fCols;
		Double_t fThreshold;
		Double_t fNoise;
    Double_t fQspread;
		Double_t fEnergy;

    Int_t fVerboseLevel;

  };

#endif

/** PndSdsHybridHitProducer.h
 **
 **/

#ifndef PNDSDSHYBRIDHITPRODUCER_H
#define PNDSDSHYBRIDHITPRODUCER_H

#include "PndSdsTask.h"
#include "PndSdsPixelDigiPar.h"
#include "PndSdsMCPoint.h"
#include "PndSdsPixel.h"
#include "PndSdsDigiPixel.h"
#include "FairGeoVector.h"
#include "FairGeoTransform.h"
#include "FairMCEventHeader.h"
#include "TVector3.h"
#include "TRandom.h"
#include "TGeoMatrix.h"
#include "TGeoBBox.h"
#include "PndGeoHandling.h"
#include "PndSdsChargeConversion.h"
#include "PndSdsTotDigiPar.h"
#include "PndSdsFE.h"

#include "PndSdsDigiPixelWriteoutBuffer.h"

#include <string>
#include <vector>

class TClonesArray;

class PndSdsHybridHitProducer : public PndSdsTask
{
 public:

  /** Default constructor **/
  PndSdsHybridHitProducer();
  
  PndSdsHybridHitProducer(PndSdsHybridHitProducer& other) :
      PndSdsTask(),
      fDigiPixelMCInfo(other.fDigiPixelMCInfo),
      fPointArray(other.fPointArray),
      fPixelArray(other.fPixelArray),
      fPixelMCArray(other.fPixelMCArray),
      fDigiPar(other.fDigiPar),
      fTotDigiPar(other.fTotDigiPar),
      fChargeConverter(other.fChargeConverter),
      fMCEventHeader(other.fMCEventHeader),
      fDataBuffer(other.fDataBuffer),
      flx(other.flx),
      fly(other.fly),
      fthreshold(other.fthreshold),
      fnoise(other.fnoise),
      fqsigma(other.fqsigma),
      fcols(other.fcols),
      frows(other.frows),
      fPixelHits(other.fPixelHits),
      fGeoH(other.fGeoH),
      fEventNr(other.fEventNr),
      fOverwriteParams(other.fOverwriteParams),
      fTimeOrderedDigi(other.fTimeOrderedDigi),
      fPixelList(other.fPixelList)
  {}
  /** Named constructor **/
  PndSdsHybridHitProducer(const char* name);

 PndSdsHybridHitProducer(Double_t lx, Double_t ly, Double_t threshold, Double_t noise);

  /** Destructor **/
  virtual ~PndSdsHybridHitProducer();


  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();
  virtual InitStatus ReInit();

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  virtual void FinishEvent();
  virtual void FinishTask();

  
  void RunTimeBased(){fTimeOrderedDigi = kTRUE;}
  
  PndSdsHybridHitProducer& operator=(PndSdsHybridHitProducer& other)
  {
    if(this != &other) // protect against invalid self-assignment
    {
      fDigiPixelMCInfo=other.fDigiPixelMCInfo;
      fPointArray=other.fPointArray;
      fPixelArray=other.fPixelArray;
      fPixelMCArray=other.fPixelMCArray;
      fDigiPar=other.fDigiPar;
      fTotDigiPar=other.fTotDigiPar;
      fChargeConverter=other.fChargeConverter;
      fMCEventHeader=other.fMCEventHeader;
      fDataBuffer=other.fDataBuffer;
      flx=other.flx;
      fly=other.fly;
      fthreshold=other.fthreshold;
      fnoise=other.fnoise;
      fqsigma=other.fqsigma;
      fcols=other.fcols;
      frows=other.frows;
      fPixelHits=other.fPixelHits;
      fGeoH=other.fGeoH;
      fEventNr=other.fEventNr;
      fOverwriteParams=other.fOverwriteParams;
      fTimeOrderedDigi=other.fTimeOrderedDigi;
      fPixelList=other.fPixelList;
    }
    return *this;
  };

protected:
  
  Bool_t fPersistance; // switch to turn on/off storing the arrays to a file
  Bool_t fDigiPixelMCInfo; // switch to turn on/off storing additional MC Info of Digis
  

  /** Input array of PndSdsMCPoints **/
  TClonesArray* fPointArray;

  /** Output array of PndSdsDigis **/
  TClonesArray* fPixelArray;

  /** Output array of PndSdsDigiPixelMCInfo **/
  TClonesArray* fPixelMCArray;


  PndSdsPixelDigiPar* fDigiPar;
  PndSdsTotDigiPar* fTotDigiPar;
  PndSdsChargeConversion* fChargeConverter;
  FairMCEventHeader* fMCEventHeader;

  PndSdsDigiPixelWriteoutBuffer* fDataBuffer;
 // fDetectorType fMCPointType;

  void Register();
  void Reset();
  void ProduceHits();

  TGeoHMatrix GetTransformation (Int_t sensorID);
  void GetLocalHitPoints(PndSdsMCPoint* myPoint, FairGeoVector& myHitIn, FairGeoVector& myHitOut);
//  PndSdsHit CalcGlobalPoint(std::vector<PndSdsPixel> pixels);
  TVector3 GetSensorDimensions(Int_t sensorID);

  void AddHit(PndSdsPixel& hit, int mcIndex);
  void AddHits(std::vector<PndSdsPixel>* hitList, int mcIndex);

  //PndSdsFE* fFEModel;

  Double_t flx;	//pixel width in x;
  Double_t fly;	//pixel width in y;
  Double_t fthreshold; //pixel threshold in electrons
  Double_t fnoise; //pixel noise in electrons
  Double_t fqsigma; //gaussian charge cloud spread
  Int_t    fcols; //pixel columns in one FE
  Int_t    frows; //pixel rows in one FE
  Int_t fPixelHits;
//  FairMCEventHeader* fMcEventHeader;
  PndGeoHandling* fGeoH; //!
  Int_t fEventNr;
  Bool_t fOverwriteParams;
  Bool_t fTimeOrderedDigi; ///<set to kTRUE to use the time ordering of the output data.

  std::vector<PndSdsPixel> fPixelList;

  ClassDef(PndSdsHybridHitProducer,8);

};

#endif
// -------------------------------------------------------------------------
// -----                 CbmStsHitProducerIdel header file             -----
// -----                  Created 10/01/06  by V. Friese               -----
// -------------------------------------------------------------------------


/** CbmStsHitProducerIdeal.h
 *@author V.Friese <v.friese@gsi.de>
 **
 ** The ideal hit producer produces hits of type CbmStsMapsHit by copying
 ** the MCPoint position. The position error is set to 1 mum, much 
 ** smaller than can be obtained by any detector. Using the hits from 
 ** this HitProducer is thus equivalent to using MC information
 ** directly, but with the correct data interface.
 **/


#ifndef PNDSDSHITPRODUCERIDEAL_H
#define PNDSDSHITPRODUCERIDEAL_H 

#include "PndSdsTask.h"
//#include "PndSdsGeoPar.h"
#include "KoaDetectorList.h"

#include "TVector3.h"
#include "TRandom.h"
 
class TClonesArray;

class PndSdsHitProducerIdeal : public PndSdsTask
{
 public:

  /** Default constructor **/  
  PndSdsHitProducerIdeal();

  PndSdsHitProducerIdeal(PndSdsHitProducerIdeal& other):
      PndSdsTask(),
      fPointArray(other.fPointArray),
      fHitArray(other.fHitArray)
   {};
  /** Named constructor **/  
  PndSdsHitProducerIdeal(const char* name);

  /** Destructor **/
  virtual ~PndSdsHitProducerIdeal();


  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();

  /** pure virtual method SetBranchNames
   **
   ** called by Init()
   ** function to set individual branch names
   **/
  virtual void SetBranchNames()=0;


  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  void SetPersistance(Bool_t p = kTRUE) {SetPersistency(p);};
  
  PndSdsHitProducerIdeal& operator=(PndSdsHitProducerIdeal& other)
  {
    if(this != &other) // protect against invalid self-assignment
    {
      fPointArray=other.fPointArray;
      fHitArray=other.fHitArray;
    }
    return *this;
  }
protected:
  
  /** Input array of PndSdsMCPoints **/
  TClonesArray* fPointArray;

  /** Output array of PndSdsHits **/
  TClonesArray* fHitArray;  

  //PndSdsGeoPar* fGeoPar;
  
  void Register();
  
  void Reset();
  
  void ProduceHits();

  ClassDef(PndSdsHitProducerIdeal,3);

};

#endif
// -------------------------------------------------------------------------
// -----                PndSdsNoiseProducer header file                -----
// -----                  Created 01.07.08  by R.Kliemt                -----
// -------------------------------------------------------------------------


/** PndSdsNoiseProducer.h
 *@author R.Kliemt <r.kliemt@physik.tu-dresden.de>
 **
 ** The Noise Producer adds fake hits to silicon sensor channels (strips and
 ** Pixels)
 **/


#ifndef PNDSDSNOISEPRODUCER_H
#define PNDSDSNOISEPRODUCER_H

#include "PndSdsTask.h"

#include <vector>

#include "TRandom.h"
//#include "PndSdsGeoPar.h"
#include "PndGeoHandling.h"
#include "PndSdsStripDigiPar.h"
#include "PndSdsPixelDigiPar.h"
#include "KoaDetectorList.h"
#include "TString.h"

class TClonesArray;

class PndSdsNoiseProducer : public PndSdsTask
{
 public:

  /** Default constructor **/
  PndSdsNoiseProducer();

  PndSdsNoiseProducer(PndSdsNoiseProducer& other):
      PndSdsTask(),
      fBranchNameStrip(other.fBranchNameStrip),
      fBranchNamePixel(other.fBranchNamePixel),
      fDigiStripArray(other.fDigiStripArray),
      fDigiPixelArray(other.fDigiPixelArray),
      fDigiParRect(other.fDigiParRect),
      fDigiParTrap(other.fDigiParTrap),
      fDigiParPix(other.fDigiParPix),
      fMCPointType(other.fMCPointType),
      fGeoH(other.fGeoH),
      fPixelIds4(other.fPixelIds4),
      fPixelIds6(other.fPixelIds6),
      fPixelIds8(other.fPixelIds8),
      fPixelIds12(other.fPixelIds12),
      fStripRectIds(other.fStripRectIds),
      fStripTrapIds(other.fStripTrapIds),
      fNoiseSpread(other.fNoiseSpread),
      fThreshold(other.fThreshold),
      fIonizationEnergy(other.fIonizationEnergy)
  {};
  
  /** Destructor **/
  virtual ~PndSdsNoiseProducer();


  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();

  /** pure virtual method SetBranchNames
   **
   ** called by Init()
   ** function to set individual branch names
   **/
  virtual void SetBranchNames()=0;
  virtual void SetMCPointType() = 0;

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  Double_t CalcDistFraction(Double_t spread, Double_t threshold);
//   Int_t CalcChanWhite(Int_t chanleft, Double_t frac);
  Int_t CalcChargeAboveThreshold(Double_t spread, Double_t threshold);
  void AddDigiStrip(Int_t &iStrip, Int_t iPoint, Int_t sensorID, Int_t fe, Int_t chan, Double_t charge);
  void AddDigiPixel(Int_t &noisies, Int_t iPoint, Int_t sensorID, Int_t fe, Int_t col, Int_t row, Double_t charge);

  void DiveDownNode(TGeoNode *fN);
  void FillSensorLists();
//   void Finish();

  
  PndSdsNoiseProducer& operator=(PndSdsNoiseProducer& other)
  {
    if(this != &other) // protect against invalid self-assignment
    {
      fBranchNameStrip=other.fBranchNameStrip;
      fBranchNamePixel=other.fBranchNamePixel;
      fDigiStripArray=other.fDigiStripArray;
      fDigiPixelArray=other.fDigiPixelArray;
      fDigiParRect=other.fDigiParRect;
      fDigiParTrap=other.fDigiParTrap;
      fDigiParPix=other.fDigiParPix;
      fMCPointType=other.fMCPointType;
      fGeoH=other.fGeoH;
      fPixelIds4=other.fPixelIds4;
      fPixelIds6=other.fPixelIds6;
      fPixelIds8=other.fPixelIds8;
      fPixelIds12=other.fPixelIds12;
      fStripRectIds=other.fStripRectIds;
      fStripTrapIds=other.fStripTrapIds;
      fNoiseSpread=other.fNoiseSpread;
      fThreshold=other.fThreshold;
      fIonizationEnergy=other.fIonizationEnergy;
    }
    return *this;
  }

 protected:
  TString fBranchNameStrip;
  TString fBranchNamePixel;
  /** In-Output array of PndSdsDigis **/
  TClonesArray* fDigiStripArray;
  TClonesArray* fDigiPixelArray;

  /** Parameter Containers **/
  PndSdsStripDigiPar* fDigiParRect;
  PndSdsStripDigiPar* fDigiParTrap;
  PndSdsPixelDigiPar* fDigiParPix;

  fDetectorType fMCPointType;

  PndGeoHandling* fGeoH;      //! Geometry name handling

  std::vector<Int_t> fPixelIds4;
  std::vector<Int_t> fPixelIds6;
  std::vector<Int_t> fPixelIds8;
  std::vector<Int_t> fPixelIds12;
  std::vector<Int_t> fStripRectIds;
  std::vector<Int_t> fStripTrapIds;

  Int_t fNoiseSpread;
  Int_t fThreshold;

  Double_t fIonizationEnergy; // electrons per GeV (Panda unified units)
//   void Register();
//   void Reset();
//   void ProduceHits();

  ClassDef(PndSdsNoiseProducer,1);

};

#endif
#ifndef PNDSDSCHARGECONVERSION_H
#define PNDSDSCHARGECONVERSION_H

//! base class for energy loss <-> digi value conversion
//! @author D.-L.Pohl <d.pohl@fz-juelich.de>

#include <map>
#include "TObject.h"
#include "TString.h"
#include "PndSdsDigi.h"

enum ConvType{kUndefined,kIdeal,kToT,kADC};

class PndSdsChargeConversion : public TObject
  {
    public :
    
    PndSdsChargeConversion(ConvType type):  fParams(), it(), fConvType(type){};
    virtual ~PndSdsChargeConversion(){};
    virtual void StartExecute(){};
    virtual void EndExecute(){};
    virtual Double_t ChargeToDigiValue(Double_t Charge) = 0;		///< Converts a given charge in electrons into the electronics answer e.g. ToT [ns]
    virtual Double_t DigiValueToCharge(Double_t digi) = 0;			///< Converts a given digitized charge into charge in electrons
    virtual Double_t DigiValueToCharge(PndSdsDigi &digi);
    virtual Double_t GetRelativeError(Double_t Charge) = 0;
    virtual Double_t GetTimeStamp(Double_t tof, Double_t charge, Double_t MCEventTime) = 0;	///< absolute time stamp of a hit in ns (clock is taken into account)
    virtual Double_t GetTimeWalk(Double_t ){return 0;}; //charge //[R.K.03/2017] unused variable(s) ///< Time between hit in detector and the time stamp assigned to the hit
//    virtual Double_t GetTimeWalk(Int_t tot){
//    	return GetTimeWalk(DigiValueToCharge(tot));
//    }
    virtual Double_t GetTimeStampErrorAfterCorrection(){
    	return 1;
    }
    
    virtual Double_t GetTimeStep(){return 0;};

    Double_t GetParameter(TString param){
      it=fParams.find(param);
      if (it == fParams.end()){
        Error("GetParameter(TString param)","No parameter named: %s",param.Data());
        return -1;
      }
      return it->second;
    };
    void SetParameter(TString param, Double_t value){
      if (value < 0 ) Error("SetParameter(TString param, Double_t value)","invalid value for param: %s", param.Data());
      fParams.insert(std::pair<TString, Double_t>(param, value));
    };
    
    private :
    std::map<TString, Double_t> fParams;
    std::map<TString, Double_t>::iterator it;
    ConvType fConvType;
    
    
    ClassDef(PndSdsChargeConversion,2);
  };
#endif /* PNDSDSCHARGECONVERSION_H */
#ifndef PNDSDSIDEALCHARGECONVERSION_H
#define PNDSDSIDEALCHARGECONVERSION_H

//! ideal charge conversion
//! @author D.-L.Pohl <d.pohl@fz-juelich.de>

#include "PndSdsChargeConversion.h"

class PndSdsIdealChargeConversion : public PndSdsChargeConversion{
public:
  
	PndSdsIdealChargeConversion(Double_t noise = 0.) : PndSdsChargeConversion(kIdeal),fNoise(noise){};
	~PndSdsIdealChargeConversion(){};
	virtual Double_t ChargeToDigiValue(Double_t charge){return charge;};
	virtual Double_t DigiValueToCharge(Double_t digi){return digi;};
  virtual Double_t GetRelativeError(Double_t charge){return charge!=0 ? fNoise/charge : 0.;};
  virtual Double_t GetTimeStamp(Double_t time, Double_t , Double_t ){return ( time -1. );}; // charge  mceventtime //[R.K.03/2017] unused variable(s)
  
protected:
  Double_t fNoise;
  
  
  ClassDef(PndSdsIdealChargeConversion, 1);
};
#endif /* PNDSDSIDEALCHARGECONVERSION_H */
#ifndef PNDSDSTOTCHARGECONVERSION_H
#define PNDSDSTOTCHARGECONVERSION_H

#include "TRandom2.h"
#include <iostream>
#include <cmath>
#include "PndSdsChargeConversion.h"

//! Class to calculate the deposited charge in one digi <-> time over threshold
//! and vice versa
/** @author D.-L.Pohl <d.pohl@fz-juelich.de>
 *
 * This class calculates the time over threshold by using the charge
 * of a pixel/strip. To calculate the TOT a simple capacitor model (integrator) is used.
 * The charge time tr [ns] is assumed to be constant. This leads to a rising straight line.
 * A constant current unloads the capacitor with a ratio of: a [e/ns].
 * The distance between the points of intersection between the resulting triangle
 * and the threshold line is the TOT.
 *
 * q
 * |
 * |     /\     a
 * |    /     \
 * |---/----------\--------------- threshold
 * |  /               \
 * ------------------------------- q = 0 (charge)
 *    | tr|                    t[ns]
 *      <-  TOT ->
 */


class PndSdsTotChargeConversion : public PndSdsChargeConversion
{
public:
	///Default constructor
	PndSdsTotChargeConversion(Int_t VerboseLevel = 0);
  
	///Main constructor
	PndSdsTotChargeConversion(Double_t tr, Double_t a, Double_t threshold, Double_t clockfrequency = 0, Int_t VerboseLevel = 0);
  
	///Destructor
	~PndSdsTotChargeConversion(){};
  
	void StartExecute();
  
	virtual Double_t ChargeToDigiValue(Double_t charge);
	virtual Double_t DigiValueToCharge(Double_t digivalue);
	virtual Double_t GetPileUpTime(Double_t charge);		///<returns the time the capacitor is loaded and therefore the time this MVD pixel/strip is blind for other events
	virtual Double_t GetRelativeError(Double_t Charge);
 // virtual Int_t GetTimeStamp(Double_t time);
  virtual Double_t GetTimeStamp(Double_t tof, Double_t charge, Double_t MCEventTime);
  virtual Double_t GetTimeWalk(Double_t Charge);
  virtual Double_t GetTimeStampErrorAfterCorrection(){
  	return ftimestep/sqrt(12);
  }

  virtual Double_t GetTimeStep(){return ftimestep;}


  
  
private:
  Double_t fthreshold;		//[e]
  Double_t Qt;				//threshold charge [e]
  Double_t t1e, t2e;			//exact time point when signal is over threshold/under threshold again [ns]
  Double_t ftimestep;			//one time step of the clock [ns]
  Double_t fstarttime;		//absolute point when TOT begins [ns]
  Double_t fstoptime;			//absolute point when TOT ends [ns]
  Double_t ftimeoffset;		//difference between rising clock edge and when detector gets hit [ns]
  Double_t ftimewalk;        //exact time point when signal is over threshold
  Int_t fVerboseLevel;
  Double_t GetTotWC();		//assumes a clock which results in a quantized TOT
  Double_t DigitizeTime(Double_t time);	///< returns the time in [ns] but binned to clock units
  TRandom2 fRand;
  
  ClassDef(PndSdsTotChargeConversion, 1);
};

#endif /* PNDSDSTOTCHARGECONVERSION_H */
#ifndef PNDSDSADCCHARGECONVERSION_H
#define PNDSDSADCCHARGECONVERSION_H

#include <iostream>
#include <cmath>
#include "PndSdsChargeConversion.h"

//! Class to calculate the deposited charge in one digi <-> digital channel number
//! and vice versa
/** @authors R.Schnell & R. Kliemt (Uni Bonn)
 *
 * This class calculates the ADC channel number for a given resolution
 * 
 * Open issues: Introduce a possible nonlinear behavior/calibration
 *
 */


class PndSdsAdcChargeConversion : public PndSdsChargeConversion
{
public:
  
	/// constructor
  PndSdsAdcChargeConversion(Int_t threshold=0, Int_t adcstep=1, Int_t resolution=8, Int_t VerboseLevel=0);
  
	///Destructor
  ~PndSdsAdcChargeConversion(){};
  
  
	virtual Double_t ChargeToDigiValue(Double_t charge);
	virtual Double_t DigiValueToCharge(Double_t digivalue);
	virtual Double_t GetRelativeError(Double_t Charge);
  virtual Int_t GetTimeStamp(Double_t time);
  virtual Double_t GetTimeStamp(Double_t tof, Double_t charge, Double_t MCEventTime);
  
  
//private:
  Int_t fVerboseLevel;
  Int_t fThreshold;		//[e]
  Int_t fAdcStep;     //[e]
  Int_t fResolution;  //[bit]
  Int_t fMaxADC;      //
  Double_t fTimeStep;     //[ns]
  Double_t DigitizeTime(Double_t time);
  
  ClassDef(PndSdsAdcChargeConversion, 1);
};

#endif /* PndSdsAdcChargeConversion_H */
/*
 * PndSdsDigiPixelWriteoutBuffer.h
 *
 *  Created on: May 10, 2011
 *      Author: stockman
 */

#ifndef PNDSDSDIGIPIXELWRITEOUTBUFFER_H_
#define PNDSDSDIGIPIXELWRITEOUTBUFFER_H_

#include "FairWriteoutBuffer.h"
#include "PndSdsDigiPixel.h"

class FairTimeStamp;

class PndSdsDigiPixelWriteoutBuffer : public FairWriteoutBuffer{

public:
	PndSdsDigiPixelWriteoutBuffer();
	PndSdsDigiPixelWriteoutBuffer(TString branchName, TString folderName, Bool_t persistance);
	void AddNewDataToTClonesArray(FairTimeStamp*);

	virtual ~PndSdsDigiPixelWriteoutBuffer();

	virtual std::vector<std::pair<double, FairTimeStamp*> > Modify(std::pair<double, FairTimeStamp*> oldData, std::pair<double, FairTimeStamp*> newData);
        
	virtual double FindTimeForData(FairTimeStamp* data) ;
	virtual void FillDataMap(FairTimeStamp* data, double activeTime) ;
	virtual void EraseDataFromDataMap(FairTimeStamp* data);
protected:	

	std::map<PndSdsDigiPixel, double> fData_map;
	
	ClassDef(PndSdsDigiPixelWriteoutBuffer, 1);
};

#endif /* PNDSDSDIGIPIXELWRITEOUTBUFFER_H_ */
/*
 * PndSdsDigiPixelSorterTask.h
 *
 *  Created on: Sep 9, 2011
 *      Author: stockman
 */

#ifndef PNDSDSDIGIPIXELSORTERTASK_H_
#define PNDSDSDIGIPIXELSORTERTASK_H_

#include <FairRingSorterTask.h>
#include <FairRingSorter.h>

class PndSdsDigiPixelSorterTask: public FairRingSorterTask {
public:
	PndSdsDigiPixelSorterTask();
	PndSdsDigiPixelSorterTask(const char* name):FairRingSorterTask(name){};
	PndSdsDigiPixelSorterTask(Int_t numberOfCells, Double_t widthOfCells, TString inputBranch, TString outputBranch, TString folderName):
		FairRingSorterTask(numberOfCells, widthOfCells, inputBranch, outputBranch, folderName){};

	virtual ~PndSdsDigiPixelSorterTask();

	virtual void AddNewDataToTClonesArray(FairTimeStamp* data);
	virtual FairRingSorter* InitSorter(Int_t numberOfCells, Double_t widthOfCells) const;

	ClassDef(PndSdsDigiPixelSorterTask, 1);
};

#endif /* PNDSDSDIGIPIXELSORTERTASK_H_ */
/*
 * PndSdsDigiPixelRingSorter.h
 *
 *  Created on: Sep 9, 2011
 *      Author: stockman
 */

#ifndef PNDSDSDIGIPIXELRINGSORTER_H_
#define PNDSDSDIGIPIXELRINGSORTER_H_

#include <FairRingSorter.h>

class PndSdsDigiPixelRingSorter: public FairRingSorter {
public:
	PndSdsDigiPixelRingSorter(int size = 100, double width = 10):FairRingSorter(size, width){};
	virtual ~PndSdsDigiPixelRingSorter();

	virtual FairTimeStamp* CreateElement(FairTimeStamp* data);

	ClassDef (PndSdsDigiPixelRingSorter,1);
};

#endif /* PNDSDSDIGIPIXELRINGSORTER_H_ */
/*
 * SdsFEAmpModel.h
 *
 *  Created on: Apr 4, 2011
 *      Author: esch
 *
 *      Class to calculate ToT, TimeWalk, TimeStamp and Time till the signal is back to baseline from a TF1 amplifier model.
 *
 *
 */

#ifndef PndSdsFE_H_
#define PndSdsFE_H_
#include "TObject.h"
#include "PndSdsFEAmpModelSimple.h"
#include "TMath.h"
#include "TF1.h"
#include "TRandom2.h"
#include "Math/Interpolator.h"
#include "Math/InterpolationTypes.h"
#include "PndSdsTotChargeConversion.h"
#include "TVectorT.h"

class PndSdsFE: public TObject {
public:
	PndSdsFE(): fFrontEndModel(0), fNumberOfSupportPoints(0), fNumberOfMaxElectons(0), fFunction(0), fMaximumAmplitude(0),fThreshold(0), fBaselineEpsilon(1), fToF(0), fEventTime(0),	fTimeOffSet(0), fTimeStep(0),fFunctionRange(0), fRand(0), i(0), stepsize(0), fCharge_list(0), fTot_list(0), inter(0) 
	{
		CalcTimeOffSet();
	};
  
  PndSdsFE(PndSdsFE& other):TObject(other),
      fFrontEndModel(other.fFrontEndModel),
      fNumberOfSupportPoints(other.fNumberOfSupportPoints),
      fNumberOfMaxElectons(other.fNumberOfMaxElectons),
      fFunction(other.fFunction),
      fMaximumAmplitude(other.fMaximumAmplitude),
      fThreshold(other.fThreshold),
      fBaselineEpsilon(other.fBaselineEpsilon),
      fToF(other.fToF),
      fEventTime(other.fEventTime),
  	  fTimeOffSet(other.fTimeOffSet),
      fTimeStep(other.fTimeStep),
      fFunctionRange(other.fFunctionRange),
      fRand(other.fRand),
      i(other.i),
      stepsize(other.stepsize),
      fCharge_list(other.fCharge_list),
      fTot_list(other.fTot_list),
      inter(other.inter)
  {};
//	PndSdsFE(double charingtime, double constcurrent, double threshold, double frequency, int verbose);
	virtual ~PndSdsFE();

	virtual double GetTotFromCharge(Double_t charge);			// Calculates the ToT value from the charge
	virtual double GetChargeFromTot(double tot);				// Calculates the charge from the tot value
	virtual double GetTimeWalkFromCharge(double charge);		// Calculates the TimeWalk from the charge
	virtual double GetTimeWalkFromTot(double tot);				// Calculates the TimeWalk from the TOT value
	virtual double GetTimeBackToBaseline(double charge);		// Calculates the time from start of the signal till the signal is fBaselineEpsilon close to baseline
	virtual double GetTimeStamp(double eventtime, double tof, double charge);  // Calculates the TimeStamp of the signal
	virtual double GetTimeStep(){return fTimeStep;}
	virtual void SetParameter(TString parName, double parValue);
	virtual void SetThreshold(double threshold){fThreshold = threshold;}

  PndSdsFE& operator=(PndSdsFE& other)
  {
    if (this != &other) // protect against invalid self-assignment
    {   
      fFrontEndModel=other.fFrontEndModel;
      fNumberOfSupportPoints=other.fNumberOfSupportPoints;
      fNumberOfMaxElectons=other.fNumberOfMaxElectons;
      fFunction=other.fFunction;
      fMaximumAmplitude=other.fMaximumAmplitude;
      fThreshold=other.fThreshold;
      fBaselineEpsilon=other.fBaselineEpsilon;
      fToF=other.fToF;
      fEventTime=other.fEventTime;
  	  fTimeOffSet=other.fTimeOffSet;
      fTimeStep=other.fTimeStep;
      fFunctionRange=other.fFunctionRange;
      fRand=other.fRand;
      i=other.i;
      stepsize=other.stepsize;
      fCharge_list=other.fCharge_list;
      fTot_list=other.fTot_list;
      inter=other.inter;
    }
    return *this;
  };
protected:

  double DigitizeTime(double time);
	void CalcTimeOffSet();
  void CreateInterpolatorList();  // Creates the Interpolatorlist for GetTotFromCharge calculation
	void SaveInterpolatorList(std::vector<double> charge, std::vector<double> tot);
	void LoadInterpolatorList();
	void GetInterpolatorList();


	PndSdsFEAmpModelSimple *fFrontEndModel;

	int fNumberOfSupportPoints;
	int fNumberOfMaxElectons ;

	TF1 *fFunction;
	double fMaximumAmplitude;      // Saves position of the maximum amplitude of the signal
	double fThreshold;				// Threshold for Signal from Parameter database
	double fBaselineEpsilon;		//
	double fToF;					// Time of Flight from MC
	double fEventTime;				// EventTime from MC
	double fTimeOffSet;				// Random offset
	double fTimeStep;
	double fFunctionRange; 			//Range of the function. max 100 fC => 624 150.9 e => max.tot 10503 ns (with thr.= 1100 e)
	TRandom2 fRand;
	int i;
	double stepsize;

	std::vector<double> fCharge_list;
	std::vector<double> fTot_list;
	ROOT::Math::Interpolator *inter;

private:




	ClassDef(PndSdsFE,1);
};

#endif /* PndSdsFE_H_ */
/*
 * PndSdsFESimple.h
 *
 *  Created on: Apr 4, 2011
 *      Author: esch
 *
 *      Class to calculate ToT, TimeWalk, TimeStamp and Time till the signal is back to baseline from a TF1 amplifier model.
 *
 *
 */

#ifndef PndSdsFESIMPLE_H_
#define PndSdsFESIMPLE_H_
#include "TObject.h"
#include "PndSdsFEAmpModelSimple.h"
#include "TMath.h"
#include "TF1.h"
#include "TRandom2.h"
#include "Math/Interpolator.h"
#include "Math/InterpolationTypes.h"
#include "PndSdsTotChargeConversion.h"
#include "TVectorT.h"
#include "PndSdsFE.h"

class PndSdsFESimple: public PndSdsFE {
public:
	PndSdsFESimple();
	PndSdsFESimple(double charsingtime, double constcurrent, double threshold, double frequency);
	~PndSdsFESimple();


	void SetParameter(double chargingtime, double constcurrent, double threshold, double frequency);

	ClassDef(PndSdsFESimple,1);
};

#endif /* PndSdsFESIMPLE_H_ */
/*
 * SdsFEAmpModelSimple.h
 *
 *  Created on: Apr 4, 2011
 *      Author: esch
 *
 *      Class for the simple amplifier model definition
 *
 */

#ifndef PNDSDSFEAMPMODELSIMPLE_H_
#define PNDSDSFEAMPMODELSIMPLE_H_


class PndSdsFEAmpModelSimple {
public:
	PndSdsFEAmpModelSimple();
	virtual ~PndSdsFEAmpModelSimple();
	double Definition(double *x, double *params);
	int GetModelNumber();

private:
	const int fModelNumber;    // Holds the number of the model - necessary to save the interpolatorlist in PndSdsFE
};

#endif /* PNDSDSFEAMPMODELSIMPLE_H_ */
/*
 * PndSdsFESimple.h
 *
 *  Created on: Apr 4, 2011
 *      Author: esch
 *
 *      Class to calculate ToT, TimeWalk, TimeStamp and Time till the signal is back to baseline from a TF1 amplifier model.
 *
 *
 */

#ifndef PndSdsFESIMPLE_H_
#define PndSdsFESIMPLE_H_
#include "TObject.h"
#include "PndSdsFEAmpModelSimple.h"
#include "TMath.h"
#include "TF1.h"
#include "TRandom2.h"
#include "Math/Interpolator.h"
#include "Math/InterpolationTypes.h"
#include "PndSdsTotChargeConversion.h"
#include "TVectorT.h"
#include "PndSdsFE.h"

class PndSdsFESimple: public PndSdsFE {
public:
	PndSdsFESimple();
	PndSdsFESimple(double charsingtime, double constcurrent, double threshold, double frequency);
	~PndSdsFESimple();


	void SetParameter(double chargingtime, double constcurrent, double threshold, double frequency);

	ClassDef(PndSdsFESimple,1);
};

#endif /* PndSdsFESIMPLE_H_ */
// -------------------------------------------------------------------------
// -----                         PndSdsDetector header file            -----
// -----                          Based on PndMvdDetector              -----
// -----                      Created 6/04/06  by T. Stockmanns        -----
// -------------------------------------------------------------------------

/**  PndSdsDetector.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Defines the active detector PndSdsDetector. Constructs the geometry and
 ** registers MCPoints.
 **/



#ifndef PNDSDSDETECTOR_H
#define PNDSDSDETECTOR_H


//#include "TClonesArray.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "FairDetector.h"
#include "TString.h"
#include "PndGeoHandling.h"
#include "KoaDetectorList.h"

#include <string>
#include <vector>
#include <map>

class TClonesArray;
class TGeoNode;
class PndSdsMCPoint;
class FairVolume;



class PndSdsDetector : public FairDetector
{

 public:

  /** Default constructor **/
  PndSdsDetector();

  PndSdsDetector(PndSdsDetector& other) :
    FairDetector(other),
    fPersistance(other.fPersistance),
    fTrackID(other.fTrackID),
    fVolumeID(other.fVolumeID),
    fPosIn(other.fPosIn),
    fPosOut(other.fPosOut),
    fMomIn(other.fMomIn),
    fMomOut(other.fMomOut),
    fTime(other.fTime),
    fLength(other.fLength),
    fELoss(other.fELoss),
    fGeoH(other.fGeoH),
    fPosIndex(other.fPosIndex),
    fPndSdsCollection(other.fPndSdsCollection),
    fUseRadDamOption(other.fUseRadDamOption),
    fOutBranchName(other.fOutBranchName),
    fFolderName(other.fFolderName),
    fDetectorID(other.fDetectorID),
    fListOfSensitives(other.fListOfSensitives)
  {};
  /** Standard constructor.
   *@param name    detetcor name
   *@param active  sensitivity flag
   **/
  PndSdsDetector(const char* name, Bool_t active);

  /** Destructor **/
  virtual ~PndSdsDetector();

  PndSdsDetector& operator=(PndSdsDetector& other)
  {
    fPersistance=other.fPersistance;
    fTrackID=other.fTrackID;
    fVolumeID=other.fVolumeID;
    fPosIn=other.fPosIn;
    fPosOut=other.fPosOut;
    fMomIn=other.fMomIn;
    fMomOut=other.fMomOut;
    fTime=other.fTime;
    fLength=other.fLength;
    fELoss=other.fELoss;
    fGeoH=other.fGeoH;
    fPosIndex=other.fPosIndex;
    fPndSdsCollection=other.fPndSdsCollection;
    fUseRadDamOption=other.fUseRadDamOption;
    fOutBranchName=other.fOutBranchName;
    fFolderName=other.fFolderName;
    fDetectorID=other.fDetectorID;
    fListOfSensitives=other.fListOfSensitives;
    return *this;
  };

  virtual void Initialize();

  /** pure virtual method SetBranchName
   **
   ** called by Initialize()
   ** function to set individual branch names
   **/
  virtual void SetBranchNames()=0;
  
  /** pure virtual method SetDefaultSensorNames
   **
   ** called by Initialize()
   ** function to set individual sensor type names
   **/
  virtual void SetDefaultSensorNames() = 0;
  void SetExclusiveSensorType(const TString sens);

  /** Virtual method ProcessHits
   **
   ** Defines the action to be taken when a step is inside the
   ** active volume. Creates CbmTrdPoints and adds them to the
   ** collection.
   *@param vol  Pointer to the active volume
   **/
  virtual Bool_t  ProcessHits(FairVolume* vol = 0);


  /** Virtual method EndOfEvent
   **
   ** If verbosity level is set, Print hit collection at the
   ** end of the event and resets it afterwards.
   **/
  virtual void EndOfEvent();

  virtual void   FinishRun();


  /** Virtual method Register
   **
   ** Registers the hit collection in the ROOT manager.
   **/
  virtual void Register();


  /** Accessor to the hit collection **/
  virtual TClonesArray* GetCollection(Int_t iColl) const;


  /** Virtual method Print
   **
   ** Screen output of hit collection.
   **/
  virtual void Print() const;


  /** Virtual Method SetSpecialPhysicsCuts
   **
   ** replaces some Geant initialisation via g3Config.C and so on
   **/
  virtual void SetSpecialPhysicsCuts();
  

  /** Virtual method Reset
   **
   ** Clears the hit collection
   **/
  virtual void Reset();


  /** Virtual method CopyClones
   **
   ** Copies the hit collection with a given track index offset
   *@param cl1     Origin
   *@param cl2     Target
   *@param offset  Index offset
   **/
  virtual void CopyClones(TClonesArray* cl1, TClonesArray* cl2,
			  Int_t offset);


  /** Virtual method Construct geometry
   **
   ** Constructs the PndSdsDetector geometry
   **/
  virtual void ConstructGeometry();
 // void ConstructRootGeometry();
  virtual void ConstructASCIIGeometry();
 // void ExpandNode(TGeoNode *fN);
  
  void SetDetectorID(DetectorId id){fDetectorID = id;fDetId =id;}

  void SetRadDamOption(bool val){fUseRadDamOption = val;};
  bool GetRadDamOption(){return fUseRadDamOption;};

  // overload function from FairModule
  void SetVerboseLevel(Int_t level){fVerboseLevel=level;fGeoH->SetVerbose(level);}
  
  void SetPersistance(Bool_t p = kTRUE) {fPersistance=p;};
  Bool_t GetPersistance() {return fPersistance;};
  
protected:
  
  Bool_t fPersistance; // switch to turn on/off storing the arrays to a file
  
  
  /** Track information to be stored until the track leaves the
      active volume. **/
  Int_t          fTrackID;           //!  track index
  Int_t          fVolumeID;             //!  Det id
  TLorentzVector fPosIn;             //!  entry position in global frame
  TLorentzVector fPosOut;            //!  exit position in global frame
  TLorentzVector fMomIn;             //!  momentum
  TLorentzVector fMomOut;            //!  momentum
  Double32_t     fTime;              //!  time
  Double32_t     fLength;            //!  length
  Double32_t     fELoss;             //!  energy loss
//  std::map<TString, Int_t> fVolumeIDMap;	 //!  map to create a unique Detector ID
  PndGeoHandling* fGeoH;	     //! Gives Access to the Path info of a hit
  Int_t fPosIndex;                   //!
  TClonesArray* fPndSdsCollection;      //! Hit collection
  bool fUseRadDamOption;			//! enables the detection of neutral particles
  TString fOutBranchName;     //! To be set by daughter classes
  TString fFolderName;        //! To be set by daughter classes
  DetectorId fDetectorID;          //! To be set by daughter classes

  std::vector<std::string> fListOfSensitives; //!

  bool CheckIfSensitive(std::string name);

  /** Private method AddHit
   **
   ** Adds a CbmTrdPoint to the HitCollection
   **/
  PndSdsMCPoint* AddHit(Int_t trackID, Int_t detID, Int_t sensorID,
  		      TVector3 posIn, TVector3 posOut,
		      TVector3 momIn, TVector3 momOut,
		      Double_t time, Double_t length, Double_t eLoss);


  /** Private method ResetParameters
   **
   ** Resets the private members for the track parameters
   **/
  void ResetParameters();


  ClassDef(PndSdsDetector,6);

};


inline void PndSdsDetector::ResetParameters() {
  fTrackID = 0;
  fVolumeID = 1;
  fPosIn.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fPosOut.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fMomIn.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fMomOut.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fTime = fLength = fELoss = 0;
  fPosIndex = 0;
}


#endif

#ifndef PNDSDSGEO_H
#define PNDSDSGEO_H

#include "FairGeoSet.h"

class  PndSdsGeo : public FairGeoSet
{
 public:
  PndSdsGeo();
  ~PndSdsGeo() {}
  const char* getModuleName(Int_t m);
  const char* getEleName(Int_t m);
  const char* getKeepinName(Int_t i,Int_t j);
  inline Int_t getModNumInMod(const TString& name) const;
 protected:
  char fModName[20];  // name of module
  char fEleName[20];  // substring for elements in module
  char fKeepinName[20];

  ClassDef(PndSdsGeo,1); // Class for PndSds
};

// TODO: we don't need this?

inline Int_t PndSdsGeo::getModNumInMod(const TString& name) const {
 /// returns the module index from module name
 return (Int_t)(name[3]-'0')-1;
}

#endif  /* !PNDSDSGEO_H */
#ifndef PNDSDSGEOPAR_H
#define PNDSDSGEOPAR_H

#include "FairParGenericSet.h"
#include "TH1F.h"

class PndSdsGeoPar : public FairParGenericSet {
public:
  PndSdsGeoPar(const char* name="PndSdsGeoPar",
	       const char* title="PndSds Geometry Parameters",
	       const char* context="TestDefaultContext");
  PndSdsGeoPar(PndSdsGeoPar& other) : FairParGenericSet(other),
    fGeoSensNodes(other.fGeoSensNodes),
    fGeoPassNodes(other.fGeoPassNodes)
  {};
  ~PndSdsGeoPar(void);
  PndSdsGeoPar& operator=(PndSdsGeoPar& other)
  {
    fGeoSensNodes=other.fGeoSensNodes;
    fGeoPassNodes=other.fGeoPassNodes;
    return *this;
  };
  void clear(void);
  void putParams(FairParamList* l);
  Bool_t getParams(FairParamList* l);
  TObjArray             *GetGeoSensitiveNodes(){return fGeoSensNodes;}
  TObjArray             *GetGeoPassiveNodes(){return fGeoPassNodes;}
private:
  TObjArray            *fGeoSensNodes; // List of FairGeoNodes for sensitive volumes
  TObjArray            *fGeoPassNodes; // List of FairGeoNodes for sensitive volumes

  ClassDef(PndSdsGeoPar,2);
};

#endif /* !PNDSDSGEOPAR_H */
//
// C++ Interface: PndSdsPixelDigiPar
//
#ifndef PNDSDSPIXELDIGIPAR_H
#define PNDSDSPIXELDIGIPAR_H

#include <TVector2.h>
#include "FairParGenericSet.h"
#include "FairParamList.h"

#include <iostream>

//! Digitization Parameter Class for SDS-Pixel part

class PndSdsPixelDigiPar : public FairParGenericSet
  {
    public :
    PndSdsPixelDigiPar (const char* name="PndSdsParTest",
                        const char* title="PndSds pixel digi parameter",
                        const char* context="TestDefaultContext");
    ~PndSdsPixelDigiPar(void){};
    void clear(void){};
    void putParams(FairParamList* list);
    Bool_t getParams(FairParamList* list);
    
    virtual void Print (std::ostream& out = std::cout) const;
    virtual void print(){Print();}

    friend std::ostream& operator<<(std::ostream& out, const PndSdsPixelDigiPar& dt){
    	dt.Print(out);
    	return out;
    }
   
    Double_t GetXPitch()        const {return fDimX;}
    Double_t GetYPitch()        const {return fDimY;}
    Double_t GetThreshold()     const {return fThreshold;}
    Double_t GetNoise()         const {return fNoise;}
    Double_t GetQCloudSigma()   const {return fCSigma;}
    Int_t GetFECols()           const {return fFeCols;}
    Int_t GetFERows()           const {return fFeRows;}
    Int_t GetMaxFEperCol()      const {return fMaxFEperCol;}
    Int_t GetMaxFEperRow()      const {return fMaxFEperRow;}
    Double_t GetClustRadius()   const {return fRadius;}
    Double_t GetFeBusClock()    const {return fFeBusClock;}
    Double_t GetTimeStep()		const {return (1./fFeBusClock * 1000.);} ///< Time step of one clock cycle in ns
    Int_t GetChargeConvMethod() const  {return fChargeConvMethod;}
    Double_t GetPixelSorterCellWidth() const {return fPixelSorterCellWidth;}
    Int_t GetPixelSorterNumberOfCells() const {return fPixelSorterNumberOfCells;}
    
    void SetXPitch(Double_t x)        {fDimX = x;}
    void SetYPitch(Double_t x)        {fDimY = x;}
    void SetThreshold(Double_t x)     {fThreshold = x;}
    void SetNoise(Double_t x)         {fNoise = x;}
    void SetQCloudSigma(Double_t x)   {fCSigma = x;}
    void SetFECols(Int_t x)           {fFeCols = x;}
    void SetFERows(Int_t x)           {fFeRows = x;}
    void SetMaxFEperCol(Int_t x)      {fMaxFEperCol = x;}
    void SetMaxFEperRow(Int_t x)      {fMaxFEperRow = x;}
    void SetClustRadius(Double_t x)   {fRadius=x;}
    void SetFeBusClock(Double_t x)      {fFeBusClock = x;}
    void SetChargeConvMethod(Int_t x) {fChargeConvMethod = x;}

    void SetPixelSorterCellWidth(Double_t x) {fPixelSorterCellWidth = x;}
    void SetPixelSorterNumberOfCells(Int_t x) {fPixelSorterNumberOfCells=x;}
    
  private:
    // Pixel Parameters
    Int_t fFeCols;            // Colums read per Frontend 
    Int_t fFeRows;            // Rows read per Frontend
    Int_t fMaxFEperCol;       // maximum number of front-end chip per column on a sensor
    Int_t fMaxFEperRow;       // maximum number of front-end chip per row on a sensor
    Double_t fDimX;           // Pixel cell size X
    Double_t fDimY;           // Pixel cell size Y
    Double_t fRadius;         // Clusterfinder search radius (channel numbers)
    Double_t fThreshold;      // Discriminator Threshold (electrons)
    Double_t fNoise;          // Gaussian electronics noise including threshold dispersion (electrons)
    Double_t fCSigma;         // Gaussian charge cloud smearing
    Double_t fFeBusClock;   // Frontend bus clock to determin noise rate
    Int_t fChargeConvMethod;	// 0: ideal conversion; 1: TOT calculation
    Double_t fPixelSorterCellWidth;	// Parameter for TimeStamp Sorter
    Int_t fPixelSorterNumberOfCells; // Parameter for TimeStamp Sorter
    //Text_t fSensName;         // Sensor name
    //Text_t fFeName;           // Frontend name
    
    
    ClassDef(PndSdsPixelDigiPar,5);
  };

#endif /*!PNDSDSSTRIPDIGIPAR_H*/
//
// C++ Interface: PndSdsChargeConvDigiPar
//
#ifndef PNDSDSTOTDIGIPAR_H
#define PNDSDSTOTDIGIPAR_H

#include <TVector2.h>
#include "FairParGenericSet.h"
#include "FairParamList.h"

#include <iostream>

//! Charge Digitization Parameter Class for SDS

class PndSdsTotDigiPar : public FairParGenericSet
{
  public :
    PndSdsTotDigiPar (const char* name="PndSdsParCharConv",
          const char* title="PndSds charge digi parameter",
          const char* context="TestDefaultContext");
    ~PndSdsTotDigiPar(void){};
    void clear(void){};
    void putParams(FairParamList* list);
    Bool_t getParams(FairParamList* list);

    virtual void Print(std::ostream& out = std::cout) const;

    friend std::ostream& operator<<(std::ostream& out, const PndSdsTotDigiPar& dt){
    	dt.Print(out);
    	return out;
    }

    Double_t GetChargingTime() const {return fChargingTime;}
    Double_t GetConstCurrent() const {return fConstCurrent;}
    Double_t GetClockFrequency() const {return fClockFrequency;}

    void SetChargingTime(Double_t x){fChargingTime = x;}
    void SetConstCurrent(Double_t x){fConstCurrent = x;}
    void SetClockFrequency(Double_t x){fClockFrequency = x;};


  private:
    // Parameters
    Double_t fChargingTime;		// time until capacitor is loaded [ns]
    Double_t fConstCurrent;		// current unloading the capacitor [e/ns]
    Double_t fClockFrequency;	// clockfrequency of the readout chip [MHz]


  ClassDef(PndSdsTotDigiPar,1);
};

#endif /*!PNDSDSTOTDIGIPAR_H*/

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"PndPersistencyTask", payloadCode, "@",
"PndSdsAdcChargeConversion", payloadCode, "@",
"PndSdsCalcFePixel", payloadCode, "@",
"PndSdsCalcPixel", payloadCode, "@",
"PndSdsCalcPixelDif", payloadCode, "@",
"PndSdsChargeConversion", payloadCode, "@",
"PndSdsDetector", payloadCode, "@",
"PndSdsDigiPixelRingSorter", payloadCode, "@",
"PndSdsDigiPixelSorterTask", payloadCode, "@",
"PndSdsDigiPixelWriteoutBuffer", payloadCode, "@",
"PndSdsFE", payloadCode, "@",
"PndSdsFESimple", payloadCode, "@",
"PndSdsGeo", payloadCode, "@",
"PndSdsGeoPar", payloadCode, "@",
"PndSdsHitProducerIdeal", payloadCode, "@",
"PndSdsHybridHitProducer", payloadCode, "@",
"PndSdsIdealChargeConversion", payloadCode, "@",
"PndSdsNoiseProducer", payloadCode, "@",
"PndSdsPixelDigiPar", payloadCode, "@",
"PndSdsTask", payloadCode, "@",
"PndSdsTotChargeConversion", payloadCode, "@",
"PndSdsTotDigiPar", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__SdsDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__SdsDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__SdsDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__SdsDict() {
  TriggerDictionaryInitialization_G__SdsDict_Impl();
}
