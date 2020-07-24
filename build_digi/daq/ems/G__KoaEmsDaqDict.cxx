// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_digidIdaqdIemsdIG__KoaEmsDaqDict

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
#include "KoaRunOnline.h"
#include "KoaEmsConfig.h"
#include "KoaEmsSource.h"
#include "KoaEmsFileSource.h"
#include "KoaEmsStreamSource.h"
#include "KoaUnpack.h"
#include "KoaScalorUnpack.h"
#include "KoaTimeUnpack.h"
#include "KoaMxdc32Unpack.h"
#include "KoaEmsRawEvent.h"
#include "KoaRawEvent.h"
#include "KoaRawEventAnalyzer.h"
#include "KoaEventAnalyzer.h"
#include "KoaEmsEventAnalyzer.h"
#include "KoaEventAssembler.h"
#include "KoaEventLgtAsm.h"
#include "KoaRawEventTransform.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_KoaRunOnline(void *p = 0);
   static void *newArray_KoaRunOnline(Long_t size, void *p);
   static void delete_KoaRunOnline(void *p);
   static void deleteArray_KoaRunOnline(void *p);
   static void destruct_KoaRunOnline(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRunOnline*)
   {
      ::KoaRunOnline *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRunOnline >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRunOnline", ::KoaRunOnline::Class_Version(), "", 20,
                  typeid(::KoaRunOnline), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRunOnline::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRunOnline) );
      instance.SetNew(&new_KoaRunOnline);
      instance.SetNewArray(&newArray_KoaRunOnline);
      instance.SetDelete(&delete_KoaRunOnline);
      instance.SetDeleteArray(&deleteArray_KoaRunOnline);
      instance.SetDestructor(&destruct_KoaRunOnline);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRunOnline*)
   {
      return GenerateInitInstanceLocal((::KoaRunOnline*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRunOnline*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaEmsConfig(void *p = 0);
   static void *newArray_KoaEmsConfig(Long_t size, void *p);
   static void delete_KoaEmsConfig(void *p);
   static void deleteArray_KoaEmsConfig(void *p);
   static void destruct_KoaEmsConfig(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaEmsConfig*)
   {
      ::KoaEmsConfig *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaEmsConfig >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaEmsConfig", ::KoaEmsConfig::Class_Version(), "", 161,
                  typeid(::KoaEmsConfig), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaEmsConfig::Dictionary, isa_proxy, 4,
                  sizeof(::KoaEmsConfig) );
      instance.SetNew(&new_KoaEmsConfig);
      instance.SetNewArray(&newArray_KoaEmsConfig);
      instance.SetDelete(&delete_KoaEmsConfig);
      instance.SetDeleteArray(&deleteArray_KoaEmsConfig);
      instance.SetDestructor(&destruct_KoaEmsConfig);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaEmsConfig*)
   {
      return GenerateInitInstanceLocal((::KoaEmsConfig*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaEmsConfig*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaEventAssembler(void *p = 0);
   static void *newArray_KoaEventAssembler(Long_t size, void *p);
   static void delete_KoaEventAssembler(void *p);
   static void deleteArray_KoaEventAssembler(void *p);
   static void destruct_KoaEventAssembler(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaEventAssembler*)
   {
      ::KoaEventAssembler *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaEventAssembler >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaEventAssembler", ::KoaEventAssembler::Class_Version(), "KoaEventAssembler.h", 16,
                  typeid(::KoaEventAssembler), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaEventAssembler::Dictionary, isa_proxy, 4,
                  sizeof(::KoaEventAssembler) );
      instance.SetNew(&new_KoaEventAssembler);
      instance.SetNewArray(&newArray_KoaEventAssembler);
      instance.SetDelete(&delete_KoaEventAssembler);
      instance.SetDeleteArray(&deleteArray_KoaEventAssembler);
      instance.SetDestructor(&destruct_KoaEventAssembler);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaEventAssembler*)
   {
      return GenerateInitInstanceLocal((::KoaEventAssembler*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaEventAssembler*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_KoaRawEventAnalyzer(void *p);
   static void deleteArray_KoaRawEventAnalyzer(void *p);
   static void destruct_KoaRawEventAnalyzer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRawEventAnalyzer*)
   {
      ::KoaRawEventAnalyzer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRawEventAnalyzer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRawEventAnalyzer", ::KoaRawEventAnalyzer::Class_Version(), "KoaRawEventAnalyzer.h", 9,
                  typeid(::KoaRawEventAnalyzer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRawEventAnalyzer::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRawEventAnalyzer) );
      instance.SetDelete(&delete_KoaRawEventAnalyzer);
      instance.SetDeleteArray(&deleteArray_KoaRawEventAnalyzer);
      instance.SetDestructor(&destruct_KoaRawEventAnalyzer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRawEventAnalyzer*)
   {
      return GenerateInitInstanceLocal((::KoaRawEventAnalyzer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRawEventAnalyzer*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_KoaEmsSource(void *p);
   static void deleteArray_KoaEmsSource(void *p);
   static void destruct_KoaEmsSource(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaEmsSource*)
   {
      ::KoaEmsSource *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaEmsSource >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaEmsSource", ::KoaEmsSource::Class_Version(), "", 249,
                  typeid(::KoaEmsSource), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaEmsSource::Dictionary, isa_proxy, 4,
                  sizeof(::KoaEmsSource) );
      instance.SetDelete(&delete_KoaEmsSource);
      instance.SetDeleteArray(&deleteArray_KoaEmsSource);
      instance.SetDestructor(&destruct_KoaEmsSource);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaEmsSource*)
   {
      return GenerateInitInstanceLocal((::KoaEmsSource*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaEmsSource*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaEmsFileSource(void *p = 0);
   static void *newArray_KoaEmsFileSource(Long_t size, void *p);
   static void delete_KoaEmsFileSource(void *p);
   static void deleteArray_KoaEmsFileSource(void *p);
   static void destruct_KoaEmsFileSource(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaEmsFileSource*)
   {
      ::KoaEmsFileSource *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaEmsFileSource >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaEmsFileSource", ::KoaEmsFileSource::Class_Version(), "", 362,
                  typeid(::KoaEmsFileSource), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaEmsFileSource::Dictionary, isa_proxy, 4,
                  sizeof(::KoaEmsFileSource) );
      instance.SetNew(&new_KoaEmsFileSource);
      instance.SetNewArray(&newArray_KoaEmsFileSource);
      instance.SetDelete(&delete_KoaEmsFileSource);
      instance.SetDeleteArray(&deleteArray_KoaEmsFileSource);
      instance.SetDestructor(&destruct_KoaEmsFileSource);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaEmsFileSource*)
   {
      return GenerateInitInstanceLocal((::KoaEmsFileSource*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaEmsFileSource*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaEmsStreamSource(void *p = 0);
   static void *newArray_KoaEmsStreamSource(Long_t size, void *p);
   static void delete_KoaEmsStreamSource(void *p);
   static void deleteArray_KoaEmsStreamSource(void *p);
   static void destruct_KoaEmsStreamSource(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaEmsStreamSource*)
   {
      ::KoaEmsStreamSource *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaEmsStreamSource >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaEmsStreamSource", ::KoaEmsStreamSource::Class_Version(), "", 387,
                  typeid(::KoaEmsStreamSource), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaEmsStreamSource::Dictionary, isa_proxy, 4,
                  sizeof(::KoaEmsStreamSource) );
      instance.SetNew(&new_KoaEmsStreamSource);
      instance.SetNewArray(&newArray_KoaEmsStreamSource);
      instance.SetDelete(&delete_KoaEmsStreamSource);
      instance.SetDeleteArray(&deleteArray_KoaEmsStreamSource);
      instance.SetDestructor(&destruct_KoaEmsStreamSource);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaEmsStreamSource*)
   {
      return GenerateInitInstanceLocal((::KoaEmsStreamSource*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaEmsStreamSource*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_KoaUnpack(void *p);
   static void deleteArray_KoaUnpack(void *p);
   static void destruct_KoaUnpack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaUnpack*)
   {
      ::KoaUnpack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaUnpack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaUnpack", ::KoaUnpack::Class_Version(), "", 411,
                  typeid(::KoaUnpack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaUnpack::Dictionary, isa_proxy, 4,
                  sizeof(::KoaUnpack) );
      instance.SetDelete(&delete_KoaUnpack);
      instance.SetDeleteArray(&deleteArray_KoaUnpack);
      instance.SetDestructor(&destruct_KoaUnpack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaUnpack*)
   {
      return GenerateInitInstanceLocal((::KoaUnpack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaUnpack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_KoaScalorUnpack(void *p);
   static void deleteArray_KoaScalorUnpack(void *p);
   static void destruct_KoaScalorUnpack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaScalorUnpack*)
   {
      ::KoaScalorUnpack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaScalorUnpack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaScalorUnpack", ::KoaScalorUnpack::Class_Version(), "", 438,
                  typeid(::KoaScalorUnpack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaScalorUnpack::Dictionary, isa_proxy, 4,
                  sizeof(::KoaScalorUnpack) );
      instance.SetDelete(&delete_KoaScalorUnpack);
      instance.SetDeleteArray(&deleteArray_KoaScalorUnpack);
      instance.SetDestructor(&destruct_KoaScalorUnpack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaScalorUnpack*)
   {
      return GenerateInitInstanceLocal((::KoaScalorUnpack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaScalorUnpack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_KoaTimeUnpack(void *p);
   static void deleteArray_KoaTimeUnpack(void *p);
   static void destruct_KoaTimeUnpack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaTimeUnpack*)
   {
      ::KoaTimeUnpack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaTimeUnpack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaTimeUnpack", ::KoaTimeUnpack::Class_Version(), "", 462,
                  typeid(::KoaTimeUnpack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaTimeUnpack::Dictionary, isa_proxy, 4,
                  sizeof(::KoaTimeUnpack) );
      instance.SetDelete(&delete_KoaTimeUnpack);
      instance.SetDeleteArray(&deleteArray_KoaTimeUnpack);
      instance.SetDestructor(&destruct_KoaTimeUnpack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaTimeUnpack*)
   {
      return GenerateInitInstanceLocal((::KoaTimeUnpack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaTimeUnpack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_KoaMxdc32Unpack(void *p);
   static void deleteArray_KoaMxdc32Unpack(void *p);
   static void destruct_KoaMxdc32Unpack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaMxdc32Unpack*)
   {
      ::KoaMxdc32Unpack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaMxdc32Unpack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaMxdc32Unpack", ::KoaMxdc32Unpack::Class_Version(), "", 488,
                  typeid(::KoaMxdc32Unpack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaMxdc32Unpack::Dictionary, isa_proxy, 4,
                  sizeof(::KoaMxdc32Unpack) );
      instance.SetDelete(&delete_KoaMxdc32Unpack);
      instance.SetDeleteArray(&deleteArray_KoaMxdc32Unpack);
      instance.SetDestructor(&destruct_KoaMxdc32Unpack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaMxdc32Unpack*)
   {
      return GenerateInitInstanceLocal((::KoaMxdc32Unpack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaMxdc32Unpack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaEmsRawEvent(void *p = 0);
   static void *newArray_KoaEmsRawEvent(Long_t size, void *p);
   static void delete_KoaEmsRawEvent(void *p);
   static void deleteArray_KoaEmsRawEvent(void *p);
   static void destruct_KoaEmsRawEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaEmsRawEvent*)
   {
      ::KoaEmsRawEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaEmsRawEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaEmsRawEvent", ::KoaEmsRawEvent::Class_Version(), "", 518,
                  typeid(::KoaEmsRawEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaEmsRawEvent::Dictionary, isa_proxy, 4,
                  sizeof(::KoaEmsRawEvent) );
      instance.SetNew(&new_KoaEmsRawEvent);
      instance.SetNewArray(&newArray_KoaEmsRawEvent);
      instance.SetDelete(&delete_KoaEmsRawEvent);
      instance.SetDeleteArray(&deleteArray_KoaEmsRawEvent);
      instance.SetDestructor(&destruct_KoaEmsRawEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaEmsRawEvent*)
   {
      return GenerateInitInstanceLocal((::KoaEmsRawEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaEmsRawEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRawEvent(void *p = 0);
   static void *newArray_KoaRawEvent(Long_t size, void *p);
   static void delete_KoaRawEvent(void *p);
   static void deleteArray_KoaRawEvent(void *p);
   static void destruct_KoaRawEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRawEvent*)
   {
      ::KoaRawEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRawEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRawEvent", ::KoaRawEvent::Class_Version(), "", 559,
                  typeid(::KoaRawEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRawEvent::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRawEvent) );
      instance.SetNew(&new_KoaRawEvent);
      instance.SetNewArray(&newArray_KoaRawEvent);
      instance.SetDelete(&delete_KoaRawEvent);
      instance.SetDeleteArray(&deleteArray_KoaRawEvent);
      instance.SetDestructor(&destruct_KoaRawEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRawEvent*)
   {
      return GenerateInitInstanceLocal((::KoaRawEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRawEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaEventAnalyzer(void *p = 0);
   static void *newArray_KoaEventAnalyzer(Long_t size, void *p);
   static void delete_KoaEventAnalyzer(void *p);
   static void deleteArray_KoaEventAnalyzer(void *p);
   static void destruct_KoaEventAnalyzer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaEventAnalyzer*)
   {
      ::KoaEventAnalyzer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaEventAnalyzer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaEventAnalyzer", ::KoaEventAnalyzer::Class_Version(), "", 949,
                  typeid(::KoaEventAnalyzer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaEventAnalyzer::Dictionary, isa_proxy, 4,
                  sizeof(::KoaEventAnalyzer) );
      instance.SetNew(&new_KoaEventAnalyzer);
      instance.SetNewArray(&newArray_KoaEventAnalyzer);
      instance.SetDelete(&delete_KoaEventAnalyzer);
      instance.SetDeleteArray(&deleteArray_KoaEventAnalyzer);
      instance.SetDestructor(&destruct_KoaEventAnalyzer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaEventAnalyzer*)
   {
      return GenerateInitInstanceLocal((::KoaEventAnalyzer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaEventAnalyzer*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaEmsEventAnalyzer(void *p = 0);
   static void *newArray_KoaEmsEventAnalyzer(Long_t size, void *p);
   static void delete_KoaEmsEventAnalyzer(void *p);
   static void deleteArray_KoaEmsEventAnalyzer(void *p);
   static void destruct_KoaEmsEventAnalyzer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaEmsEventAnalyzer*)
   {
      ::KoaEmsEventAnalyzer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaEmsEventAnalyzer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaEmsEventAnalyzer", ::KoaEmsEventAnalyzer::Class_Version(), "", 1019,
                  typeid(::KoaEmsEventAnalyzer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaEmsEventAnalyzer::Dictionary, isa_proxy, 4,
                  sizeof(::KoaEmsEventAnalyzer) );
      instance.SetNew(&new_KoaEmsEventAnalyzer);
      instance.SetNewArray(&newArray_KoaEmsEventAnalyzer);
      instance.SetDelete(&delete_KoaEmsEventAnalyzer);
      instance.SetDeleteArray(&deleteArray_KoaEmsEventAnalyzer);
      instance.SetDestructor(&destruct_KoaEmsEventAnalyzer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaEmsEventAnalyzer*)
   {
      return GenerateInitInstanceLocal((::KoaEmsEventAnalyzer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaEmsEventAnalyzer*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaEventLgtAsm(void *p = 0);
   static void *newArray_KoaEventLgtAsm(Long_t size, void *p);
   static void delete_KoaEventLgtAsm(void *p);
   static void deleteArray_KoaEventLgtAsm(void *p);
   static void destruct_KoaEventLgtAsm(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaEventLgtAsm*)
   {
      ::KoaEventLgtAsm *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaEventLgtAsm >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaEventLgtAsm", ::KoaEventLgtAsm::Class_Version(), "", 1174,
                  typeid(::KoaEventLgtAsm), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaEventLgtAsm::Dictionary, isa_proxy, 4,
                  sizeof(::KoaEventLgtAsm) );
      instance.SetNew(&new_KoaEventLgtAsm);
      instance.SetNewArray(&newArray_KoaEventLgtAsm);
      instance.SetDelete(&delete_KoaEventLgtAsm);
      instance.SetDeleteArray(&deleteArray_KoaEventLgtAsm);
      instance.SetDestructor(&destruct_KoaEventLgtAsm);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaEventLgtAsm*)
   {
      return GenerateInitInstanceLocal((::KoaEventLgtAsm*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaEventLgtAsm*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRawEventTransform(void *p = 0);
   static void *newArray_KoaRawEventTransform(Long_t size, void *p);
   static void delete_KoaRawEventTransform(void *p);
   static void deleteArray_KoaRawEventTransform(void *p);
   static void destruct_KoaRawEventTransform(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRawEventTransform*)
   {
      ::KoaRawEventTransform *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRawEventTransform >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRawEventTransform", ::KoaRawEventTransform::Class_Version(), "", 1204,
                  typeid(::KoaRawEventTransform), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRawEventTransform::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRawEventTransform) );
      instance.SetNew(&new_KoaRawEventTransform);
      instance.SetNewArray(&newArray_KoaRawEventTransform);
      instance.SetDelete(&delete_KoaRawEventTransform);
      instance.SetDeleteArray(&deleteArray_KoaRawEventTransform);
      instance.SetDestructor(&destruct_KoaRawEventTransform);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRawEventTransform*)
   {
      return GenerateInitInstanceLocal((::KoaRawEventTransform*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRawEventTransform*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr KoaRunOnline::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRunOnline::Class_Name()
{
   return "KoaRunOnline";
}

//______________________________________________________________________________
const char *KoaRunOnline::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRunOnline*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRunOnline::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRunOnline*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRunOnline::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRunOnline*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRunOnline::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRunOnline*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaEmsConfig::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaEmsConfig::Class_Name()
{
   return "KoaEmsConfig";
}

//______________________________________________________________________________
const char *KoaEmsConfig::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsConfig*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaEmsConfig::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsConfig*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaEmsConfig::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsConfig*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaEmsConfig::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsConfig*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaEventAssembler::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaEventAssembler::Class_Name()
{
   return "KoaEventAssembler";
}

//______________________________________________________________________________
const char *KoaEventAssembler::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEventAssembler*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaEventAssembler::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEventAssembler*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaEventAssembler::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEventAssembler*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaEventAssembler::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEventAssembler*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRawEventAnalyzer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRawEventAnalyzer::Class_Name()
{
   return "KoaRawEventAnalyzer";
}

//______________________________________________________________________________
const char *KoaRawEventAnalyzer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRawEventAnalyzer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRawEventAnalyzer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRawEventAnalyzer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRawEventAnalyzer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRawEventAnalyzer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRawEventAnalyzer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRawEventAnalyzer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaEmsSource::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaEmsSource::Class_Name()
{
   return "KoaEmsSource";
}

//______________________________________________________________________________
const char *KoaEmsSource::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsSource*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaEmsSource::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsSource*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaEmsSource::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsSource*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaEmsSource::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsSource*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaEmsFileSource::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaEmsFileSource::Class_Name()
{
   return "KoaEmsFileSource";
}

//______________________________________________________________________________
const char *KoaEmsFileSource::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsFileSource*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaEmsFileSource::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsFileSource*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaEmsFileSource::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsFileSource*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaEmsFileSource::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsFileSource*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaEmsStreamSource::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaEmsStreamSource::Class_Name()
{
   return "KoaEmsStreamSource";
}

//______________________________________________________________________________
const char *KoaEmsStreamSource::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsStreamSource*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaEmsStreamSource::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsStreamSource*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaEmsStreamSource::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsStreamSource*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaEmsStreamSource::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsStreamSource*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaUnpack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaUnpack::Class_Name()
{
   return "KoaUnpack";
}

//______________________________________________________________________________
const char *KoaUnpack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaUnpack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaUnpack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaUnpack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaUnpack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaUnpack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaUnpack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaUnpack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaScalorUnpack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaScalorUnpack::Class_Name()
{
   return "KoaScalorUnpack";
}

//______________________________________________________________________________
const char *KoaScalorUnpack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaScalorUnpack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaScalorUnpack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaScalorUnpack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaScalorUnpack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaScalorUnpack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaScalorUnpack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaScalorUnpack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaTimeUnpack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaTimeUnpack::Class_Name()
{
   return "KoaTimeUnpack";
}

//______________________________________________________________________________
const char *KoaTimeUnpack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaTimeUnpack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaTimeUnpack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaTimeUnpack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaTimeUnpack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaTimeUnpack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaTimeUnpack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaTimeUnpack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaMxdc32Unpack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaMxdc32Unpack::Class_Name()
{
   return "KoaMxdc32Unpack";
}

//______________________________________________________________________________
const char *KoaMxdc32Unpack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaMxdc32Unpack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaMxdc32Unpack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaMxdc32Unpack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaMxdc32Unpack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaMxdc32Unpack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaMxdc32Unpack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaMxdc32Unpack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaEmsRawEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaEmsRawEvent::Class_Name()
{
   return "KoaEmsRawEvent";
}

//______________________________________________________________________________
const char *KoaEmsRawEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsRawEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaEmsRawEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsRawEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaEmsRawEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsRawEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaEmsRawEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsRawEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRawEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRawEvent::Class_Name()
{
   return "KoaRawEvent";
}

//______________________________________________________________________________
const char *KoaRawEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRawEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRawEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRawEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRawEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRawEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRawEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRawEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaEventAnalyzer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaEventAnalyzer::Class_Name()
{
   return "KoaEventAnalyzer";
}

//______________________________________________________________________________
const char *KoaEventAnalyzer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEventAnalyzer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaEventAnalyzer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEventAnalyzer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaEventAnalyzer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEventAnalyzer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaEventAnalyzer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEventAnalyzer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaEmsEventAnalyzer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaEmsEventAnalyzer::Class_Name()
{
   return "KoaEmsEventAnalyzer";
}

//______________________________________________________________________________
const char *KoaEmsEventAnalyzer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsEventAnalyzer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaEmsEventAnalyzer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsEventAnalyzer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaEmsEventAnalyzer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsEventAnalyzer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaEmsEventAnalyzer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEmsEventAnalyzer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaEventLgtAsm::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaEventLgtAsm::Class_Name()
{
   return "KoaEventLgtAsm";
}

//______________________________________________________________________________
const char *KoaEventLgtAsm::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEventLgtAsm*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaEventLgtAsm::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEventLgtAsm*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaEventLgtAsm::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEventLgtAsm*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaEventLgtAsm::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEventLgtAsm*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRawEventTransform::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRawEventTransform::Class_Name()
{
   return "KoaRawEventTransform";
}

//______________________________________________________________________________
const char *KoaRawEventTransform::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRawEventTransform*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRawEventTransform::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRawEventTransform*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRawEventTransform::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRawEventTransform*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRawEventTransform::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRawEventTransform*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void KoaRunOnline::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRunOnline.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRunOnline::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRunOnline::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRunOnline(void *p) {
      return  p ? new(p) ::KoaRunOnline : new ::KoaRunOnline;
   }
   static void *newArray_KoaRunOnline(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRunOnline[nElements] : new ::KoaRunOnline[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRunOnline(void *p) {
      delete ((::KoaRunOnline*)p);
   }
   static void deleteArray_KoaRunOnline(void *p) {
      delete [] ((::KoaRunOnline*)p);
   }
   static void destruct_KoaRunOnline(void *p) {
      typedef ::KoaRunOnline current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRunOnline

//______________________________________________________________________________
void KoaEmsConfig::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaEmsConfig.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaEmsConfig::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaEmsConfig::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaEmsConfig(void *p) {
      return  p ? new(p) ::KoaEmsConfig : new ::KoaEmsConfig;
   }
   static void *newArray_KoaEmsConfig(Long_t nElements, void *p) {
      return p ? new(p) ::KoaEmsConfig[nElements] : new ::KoaEmsConfig[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaEmsConfig(void *p) {
      delete ((::KoaEmsConfig*)p);
   }
   static void deleteArray_KoaEmsConfig(void *p) {
      delete [] ((::KoaEmsConfig*)p);
   }
   static void destruct_KoaEmsConfig(void *p) {
      typedef ::KoaEmsConfig current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaEmsConfig

//______________________________________________________________________________
void KoaEventAssembler::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaEventAssembler.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaEventAssembler::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaEventAssembler::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaEventAssembler(void *p) {
      return  p ? new(p) ::KoaEventAssembler : new ::KoaEventAssembler;
   }
   static void *newArray_KoaEventAssembler(Long_t nElements, void *p) {
      return p ? new(p) ::KoaEventAssembler[nElements] : new ::KoaEventAssembler[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaEventAssembler(void *p) {
      delete ((::KoaEventAssembler*)p);
   }
   static void deleteArray_KoaEventAssembler(void *p) {
      delete [] ((::KoaEventAssembler*)p);
   }
   static void destruct_KoaEventAssembler(void *p) {
      typedef ::KoaEventAssembler current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaEventAssembler

//______________________________________________________________________________
void KoaRawEventAnalyzer::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRawEventAnalyzer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRawEventAnalyzer::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRawEventAnalyzer::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_KoaRawEventAnalyzer(void *p) {
      delete ((::KoaRawEventAnalyzer*)p);
   }
   static void deleteArray_KoaRawEventAnalyzer(void *p) {
      delete [] ((::KoaRawEventAnalyzer*)p);
   }
   static void destruct_KoaRawEventAnalyzer(void *p) {
      typedef ::KoaRawEventAnalyzer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRawEventAnalyzer

//______________________________________________________________________________
void KoaEmsSource::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaEmsSource.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaEmsSource::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaEmsSource::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_KoaEmsSource(void *p) {
      delete ((::KoaEmsSource*)p);
   }
   static void deleteArray_KoaEmsSource(void *p) {
      delete [] ((::KoaEmsSource*)p);
   }
   static void destruct_KoaEmsSource(void *p) {
      typedef ::KoaEmsSource current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaEmsSource

//______________________________________________________________________________
void KoaEmsFileSource::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaEmsFileSource.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaEmsFileSource::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaEmsFileSource::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaEmsFileSource(void *p) {
      return  p ? new(p) ::KoaEmsFileSource : new ::KoaEmsFileSource;
   }
   static void *newArray_KoaEmsFileSource(Long_t nElements, void *p) {
      return p ? new(p) ::KoaEmsFileSource[nElements] : new ::KoaEmsFileSource[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaEmsFileSource(void *p) {
      delete ((::KoaEmsFileSource*)p);
   }
   static void deleteArray_KoaEmsFileSource(void *p) {
      delete [] ((::KoaEmsFileSource*)p);
   }
   static void destruct_KoaEmsFileSource(void *p) {
      typedef ::KoaEmsFileSource current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaEmsFileSource

//______________________________________________________________________________
void KoaEmsStreamSource::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaEmsStreamSource.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaEmsStreamSource::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaEmsStreamSource::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaEmsStreamSource(void *p) {
      return  p ? new(p) ::KoaEmsStreamSource : new ::KoaEmsStreamSource;
   }
   static void *newArray_KoaEmsStreamSource(Long_t nElements, void *p) {
      return p ? new(p) ::KoaEmsStreamSource[nElements] : new ::KoaEmsStreamSource[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaEmsStreamSource(void *p) {
      delete ((::KoaEmsStreamSource*)p);
   }
   static void deleteArray_KoaEmsStreamSource(void *p) {
      delete [] ((::KoaEmsStreamSource*)p);
   }
   static void destruct_KoaEmsStreamSource(void *p) {
      typedef ::KoaEmsStreamSource current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaEmsStreamSource

//______________________________________________________________________________
void KoaUnpack::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaUnpack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaUnpack::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaUnpack::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_KoaUnpack(void *p) {
      delete ((::KoaUnpack*)p);
   }
   static void deleteArray_KoaUnpack(void *p) {
      delete [] ((::KoaUnpack*)p);
   }
   static void destruct_KoaUnpack(void *p) {
      typedef ::KoaUnpack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaUnpack

//______________________________________________________________________________
void KoaScalorUnpack::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaScalorUnpack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaScalorUnpack::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaScalorUnpack::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_KoaScalorUnpack(void *p) {
      delete ((::KoaScalorUnpack*)p);
   }
   static void deleteArray_KoaScalorUnpack(void *p) {
      delete [] ((::KoaScalorUnpack*)p);
   }
   static void destruct_KoaScalorUnpack(void *p) {
      typedef ::KoaScalorUnpack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaScalorUnpack

//______________________________________________________________________________
void KoaTimeUnpack::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaTimeUnpack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaTimeUnpack::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaTimeUnpack::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_KoaTimeUnpack(void *p) {
      delete ((::KoaTimeUnpack*)p);
   }
   static void deleteArray_KoaTimeUnpack(void *p) {
      delete [] ((::KoaTimeUnpack*)p);
   }
   static void destruct_KoaTimeUnpack(void *p) {
      typedef ::KoaTimeUnpack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaTimeUnpack

//______________________________________________________________________________
void KoaMxdc32Unpack::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaMxdc32Unpack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaMxdc32Unpack::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaMxdc32Unpack::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_KoaMxdc32Unpack(void *p) {
      delete ((::KoaMxdc32Unpack*)p);
   }
   static void deleteArray_KoaMxdc32Unpack(void *p) {
      delete [] ((::KoaMxdc32Unpack*)p);
   }
   static void destruct_KoaMxdc32Unpack(void *p) {
      typedef ::KoaMxdc32Unpack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaMxdc32Unpack

//______________________________________________________________________________
void KoaEmsRawEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaEmsRawEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaEmsRawEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaEmsRawEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaEmsRawEvent(void *p) {
      return  p ? new(p) ::KoaEmsRawEvent : new ::KoaEmsRawEvent;
   }
   static void *newArray_KoaEmsRawEvent(Long_t nElements, void *p) {
      return p ? new(p) ::KoaEmsRawEvent[nElements] : new ::KoaEmsRawEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaEmsRawEvent(void *p) {
      delete ((::KoaEmsRawEvent*)p);
   }
   static void deleteArray_KoaEmsRawEvent(void *p) {
      delete [] ((::KoaEmsRawEvent*)p);
   }
   static void destruct_KoaEmsRawEvent(void *p) {
      typedef ::KoaEmsRawEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaEmsRawEvent

//______________________________________________________________________________
void KoaRawEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRawEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRawEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRawEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRawEvent(void *p) {
      return  p ? new(p) ::KoaRawEvent : new ::KoaRawEvent;
   }
   static void *newArray_KoaRawEvent(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRawEvent[nElements] : new ::KoaRawEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRawEvent(void *p) {
      delete ((::KoaRawEvent*)p);
   }
   static void deleteArray_KoaRawEvent(void *p) {
      delete [] ((::KoaRawEvent*)p);
   }
   static void destruct_KoaRawEvent(void *p) {
      typedef ::KoaRawEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRawEvent

//______________________________________________________________________________
void KoaEventAnalyzer::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaEventAnalyzer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaEventAnalyzer::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaEventAnalyzer::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaEventAnalyzer(void *p) {
      return  p ? new(p) ::KoaEventAnalyzer : new ::KoaEventAnalyzer;
   }
   static void *newArray_KoaEventAnalyzer(Long_t nElements, void *p) {
      return p ? new(p) ::KoaEventAnalyzer[nElements] : new ::KoaEventAnalyzer[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaEventAnalyzer(void *p) {
      delete ((::KoaEventAnalyzer*)p);
   }
   static void deleteArray_KoaEventAnalyzer(void *p) {
      delete [] ((::KoaEventAnalyzer*)p);
   }
   static void destruct_KoaEventAnalyzer(void *p) {
      typedef ::KoaEventAnalyzer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaEventAnalyzer

//______________________________________________________________________________
void KoaEmsEventAnalyzer::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaEmsEventAnalyzer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaEmsEventAnalyzer::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaEmsEventAnalyzer::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaEmsEventAnalyzer(void *p) {
      return  p ? new(p) ::KoaEmsEventAnalyzer : new ::KoaEmsEventAnalyzer;
   }
   static void *newArray_KoaEmsEventAnalyzer(Long_t nElements, void *p) {
      return p ? new(p) ::KoaEmsEventAnalyzer[nElements] : new ::KoaEmsEventAnalyzer[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaEmsEventAnalyzer(void *p) {
      delete ((::KoaEmsEventAnalyzer*)p);
   }
   static void deleteArray_KoaEmsEventAnalyzer(void *p) {
      delete [] ((::KoaEmsEventAnalyzer*)p);
   }
   static void destruct_KoaEmsEventAnalyzer(void *p) {
      typedef ::KoaEmsEventAnalyzer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaEmsEventAnalyzer

//______________________________________________________________________________
void KoaEventLgtAsm::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaEventLgtAsm.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaEventLgtAsm::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaEventLgtAsm::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaEventLgtAsm(void *p) {
      return  p ? new(p) ::KoaEventLgtAsm : new ::KoaEventLgtAsm;
   }
   static void *newArray_KoaEventLgtAsm(Long_t nElements, void *p) {
      return p ? new(p) ::KoaEventLgtAsm[nElements] : new ::KoaEventLgtAsm[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaEventLgtAsm(void *p) {
      delete ((::KoaEventLgtAsm*)p);
   }
   static void deleteArray_KoaEventLgtAsm(void *p) {
      delete [] ((::KoaEventLgtAsm*)p);
   }
   static void destruct_KoaEventLgtAsm(void *p) {
      typedef ::KoaEventLgtAsm current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaEventLgtAsm

//______________________________________________________________________________
void KoaRawEventTransform::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRawEventTransform.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRawEventTransform::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRawEventTransform::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRawEventTransform(void *p) {
      return  p ? new(p) ::KoaRawEventTransform : new ::KoaRawEventTransform;
   }
   static void *newArray_KoaRawEventTransform(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRawEventTransform[nElements] : new ::KoaRawEventTransform[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRawEventTransform(void *p) {
      delete ((::KoaRawEventTransform*)p);
   }
   static void deleteArray_KoaRawEventTransform(void *p) {
      delete [] ((::KoaRawEventTransform*)p);
   }
   static void destruct_KoaRawEventTransform(void *p) {
      typedef ::KoaRawEventTransform current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRawEventTransform

namespace ROOT {
   static TClass *vectorlEunsignedsPintgR_Dictionary();
   static void vectorlEunsignedsPintgR_TClassManip(TClass*);
   static void *new_vectorlEunsignedsPintgR(void *p = 0);
   static void *newArray_vectorlEunsignedsPintgR(Long_t size, void *p);
   static void delete_vectorlEunsignedsPintgR(void *p);
   static void deleteArray_vectorlEunsignedsPintgR(void *p);
   static void destruct_vectorlEunsignedsPintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<unsigned int>*)
   {
      vector<unsigned int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<unsigned int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<unsigned int>", -2, "vector", 216,
                  typeid(vector<unsigned int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEunsignedsPintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<unsigned int>) );
      instance.SetNew(&new_vectorlEunsignedsPintgR);
      instance.SetNewArray(&newArray_vectorlEunsignedsPintgR);
      instance.SetDelete(&delete_vectorlEunsignedsPintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEunsignedsPintgR);
      instance.SetDestructor(&destruct_vectorlEunsignedsPintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<unsigned int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<unsigned int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEunsignedsPintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<unsigned int>*)0x0)->GetClass();
      vectorlEunsignedsPintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEunsignedsPintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEunsignedsPintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned int> : new vector<unsigned int>;
   }
   static void *newArray_vectorlEunsignedsPintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned int>[nElements] : new vector<unsigned int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEunsignedsPintgR(void *p) {
      delete ((vector<unsigned int>*)p);
   }
   static void deleteArray_vectorlEunsignedsPintgR(void *p) {
      delete [] ((vector<unsigned int>*)p);
   }
   static void destruct_vectorlEunsignedsPintgR(void *p) {
      typedef vector<unsigned int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<unsigned int>

namespace ROOT {
   static TClass *vectorlElonggR_Dictionary();
   static void vectorlElonggR_TClassManip(TClass*);
   static void *new_vectorlElonggR(void *p = 0);
   static void *newArray_vectorlElonggR(Long_t size, void *p);
   static void delete_vectorlElonggR(void *p);
   static void deleteArray_vectorlElonggR(void *p);
   static void destruct_vectorlElonggR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<long>*)
   {
      vector<long> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<long>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<long>", -2, "vector", 216,
                  typeid(vector<long>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlElonggR_Dictionary, isa_proxy, 0,
                  sizeof(vector<long>) );
      instance.SetNew(&new_vectorlElonggR);
      instance.SetNewArray(&newArray_vectorlElonggR);
      instance.SetDelete(&delete_vectorlElonggR);
      instance.SetDeleteArray(&deleteArray_vectorlElonggR);
      instance.SetDestructor(&destruct_vectorlElonggR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<long> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<long>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlElonggR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<long>*)0x0)->GetClass();
      vectorlElonggR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlElonggR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlElonggR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<long> : new vector<long>;
   }
   static void *newArray_vectorlElonggR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<long>[nElements] : new vector<long>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlElonggR(void *p) {
      delete ((vector<long>*)p);
   }
   static void deleteArray_vectorlElonggR(void *p) {
      delete [] ((vector<long>*)p);
   }
   static void destruct_vectorlElonggR(void *p) {
      typedef vector<long> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<long>

namespace ROOT {
   static TClass *maplEunsignedsPintcOlonggR_Dictionary();
   static void maplEunsignedsPintcOlonggR_TClassManip(TClass*);
   static void *new_maplEunsignedsPintcOlonggR(void *p = 0);
   static void *newArray_maplEunsignedsPintcOlonggR(Long_t size, void *p);
   static void delete_maplEunsignedsPintcOlonggR(void *p);
   static void deleteArray_maplEunsignedsPintcOlonggR(void *p);
   static void destruct_maplEunsignedsPintcOlonggR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<unsigned int,long>*)
   {
      map<unsigned int,long> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<unsigned int,long>));
      static ::ROOT::TGenericClassInfo 
         instance("map<unsigned int,long>", -2, "map", 99,
                  typeid(map<unsigned int,long>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEunsignedsPintcOlonggR_Dictionary, isa_proxy, 0,
                  sizeof(map<unsigned int,long>) );
      instance.SetNew(&new_maplEunsignedsPintcOlonggR);
      instance.SetNewArray(&newArray_maplEunsignedsPintcOlonggR);
      instance.SetDelete(&delete_maplEunsignedsPintcOlonggR);
      instance.SetDeleteArray(&deleteArray_maplEunsignedsPintcOlonggR);
      instance.SetDestructor(&destruct_maplEunsignedsPintcOlonggR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<unsigned int,long> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<unsigned int,long>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEunsignedsPintcOlonggR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<unsigned int,long>*)0x0)->GetClass();
      maplEunsignedsPintcOlonggR_TClassManip(theClass);
   return theClass;
   }

   static void maplEunsignedsPintcOlonggR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEunsignedsPintcOlonggR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<unsigned int,long> : new map<unsigned int,long>;
   }
   static void *newArray_maplEunsignedsPintcOlonggR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<unsigned int,long>[nElements] : new map<unsigned int,long>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEunsignedsPintcOlonggR(void *p) {
      delete ((map<unsigned int,long>*)p);
   }
   static void deleteArray_maplEunsignedsPintcOlonggR(void *p) {
      delete [] ((map<unsigned int,long>*)p);
   }
   static void destruct_maplEunsignedsPintcOlonggR(void *p) {
      typedef map<unsigned int,long> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<unsigned int,long>

namespace ROOT {
   static TClass *maplEunsignedsPintcOModuleInfogR_Dictionary();
   static void maplEunsignedsPintcOModuleInfogR_TClassManip(TClass*);
   static void *new_maplEunsignedsPintcOModuleInfogR(void *p = 0);
   static void *newArray_maplEunsignedsPintcOModuleInfogR(Long_t size, void *p);
   static void delete_maplEunsignedsPintcOModuleInfogR(void *p);
   static void deleteArray_maplEunsignedsPintcOModuleInfogR(void *p);
   static void destruct_maplEunsignedsPintcOModuleInfogR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<unsigned int,ModuleInfo>*)
   {
      map<unsigned int,ModuleInfo> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<unsigned int,ModuleInfo>));
      static ::ROOT::TGenericClassInfo 
         instance("map<unsigned int,ModuleInfo>", -2, "map", 99,
                  typeid(map<unsigned int,ModuleInfo>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEunsignedsPintcOModuleInfogR_Dictionary, isa_proxy, 0,
                  sizeof(map<unsigned int,ModuleInfo>) );
      instance.SetNew(&new_maplEunsignedsPintcOModuleInfogR);
      instance.SetNewArray(&newArray_maplEunsignedsPintcOModuleInfogR);
      instance.SetDelete(&delete_maplEunsignedsPintcOModuleInfogR);
      instance.SetDeleteArray(&deleteArray_maplEunsignedsPintcOModuleInfogR);
      instance.SetDestructor(&destruct_maplEunsignedsPintcOModuleInfogR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<unsigned int,ModuleInfo> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<unsigned int,ModuleInfo>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEunsignedsPintcOModuleInfogR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<unsigned int,ModuleInfo>*)0x0)->GetClass();
      maplEunsignedsPintcOModuleInfogR_TClassManip(theClass);
   return theClass;
   }

   static void maplEunsignedsPintcOModuleInfogR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEunsignedsPintcOModuleInfogR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<unsigned int,ModuleInfo> : new map<unsigned int,ModuleInfo>;
   }
   static void *newArray_maplEunsignedsPintcOModuleInfogR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<unsigned int,ModuleInfo>[nElements] : new map<unsigned int,ModuleInfo>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEunsignedsPintcOModuleInfogR(void *p) {
      delete ((map<unsigned int,ModuleInfo>*)p);
   }
   static void deleteArray_maplEunsignedsPintcOModuleInfogR(void *p) {
      delete [] ((map<unsigned int,ModuleInfo>*)p);
   }
   static void destruct_maplEunsignedsPintcOModuleInfogR(void *p) {
      typedef map<unsigned int,ModuleInfo> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<unsigned int,ModuleInfo>

namespace ROOT {
   static TClass *maplEunsignedsPintcOKoaUnpackmUgR_Dictionary();
   static void maplEunsignedsPintcOKoaUnpackmUgR_TClassManip(TClass*);
   static void *new_maplEunsignedsPintcOKoaUnpackmUgR(void *p = 0);
   static void *newArray_maplEunsignedsPintcOKoaUnpackmUgR(Long_t size, void *p);
   static void delete_maplEunsignedsPintcOKoaUnpackmUgR(void *p);
   static void deleteArray_maplEunsignedsPintcOKoaUnpackmUgR(void *p);
   static void destruct_maplEunsignedsPintcOKoaUnpackmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<unsigned int,KoaUnpack*>*)
   {
      map<unsigned int,KoaUnpack*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<unsigned int,KoaUnpack*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<unsigned int,KoaUnpack*>", -2, "map", 99,
                  typeid(map<unsigned int,KoaUnpack*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEunsignedsPintcOKoaUnpackmUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<unsigned int,KoaUnpack*>) );
      instance.SetNew(&new_maplEunsignedsPintcOKoaUnpackmUgR);
      instance.SetNewArray(&newArray_maplEunsignedsPintcOKoaUnpackmUgR);
      instance.SetDelete(&delete_maplEunsignedsPintcOKoaUnpackmUgR);
      instance.SetDeleteArray(&deleteArray_maplEunsignedsPintcOKoaUnpackmUgR);
      instance.SetDestructor(&destruct_maplEunsignedsPintcOKoaUnpackmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<unsigned int,KoaUnpack*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<unsigned int,KoaUnpack*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEunsignedsPintcOKoaUnpackmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<unsigned int,KoaUnpack*>*)0x0)->GetClass();
      maplEunsignedsPintcOKoaUnpackmUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEunsignedsPintcOKoaUnpackmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEunsignedsPintcOKoaUnpackmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<unsigned int,KoaUnpack*> : new map<unsigned int,KoaUnpack*>;
   }
   static void *newArray_maplEunsignedsPintcOKoaUnpackmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<unsigned int,KoaUnpack*>[nElements] : new map<unsigned int,KoaUnpack*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEunsignedsPintcOKoaUnpackmUgR(void *p) {
      delete ((map<unsigned int,KoaUnpack*>*)p);
   }
   static void deleteArray_maplEunsignedsPintcOKoaUnpackmUgR(void *p) {
      delete [] ((map<unsigned int,KoaUnpack*>*)p);
   }
   static void destruct_maplEunsignedsPintcOKoaUnpackmUgR(void *p) {
      typedef map<unsigned int,KoaUnpack*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<unsigned int,KoaUnpack*>

namespace ROOT {
   static TClass *maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR_Dictionary();
   static void maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR_TClassManip(TClass*);
   static void *new_maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR(void *p = 0);
   static void *newArray_maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR(Long_t size, void *p);
   static void delete_maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR(void *p);
   static void deleteArray_maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR(void *p);
   static void destruct_maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<unsigned int,KoaBuffer<KoaMxdc32Data>*>*)
   {
      map<unsigned int,KoaBuffer<KoaMxdc32Data>*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<unsigned int,KoaBuffer<KoaMxdc32Data>*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<unsigned int,KoaBuffer<KoaMxdc32Data>*>", -2, "map", 99,
                  typeid(map<unsigned int,KoaBuffer<KoaMxdc32Data>*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<unsigned int,KoaBuffer<KoaMxdc32Data>*>) );
      instance.SetNew(&new_maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR);
      instance.SetNewArray(&newArray_maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR);
      instance.SetDelete(&delete_maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR);
      instance.SetDeleteArray(&deleteArray_maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR);
      instance.SetDestructor(&destruct_maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<unsigned int,KoaBuffer<KoaMxdc32Data>*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<unsigned int,KoaBuffer<KoaMxdc32Data>*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<unsigned int,KoaBuffer<KoaMxdc32Data>*>*)0x0)->GetClass();
      maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<unsigned int,KoaBuffer<KoaMxdc32Data>*> : new map<unsigned int,KoaBuffer<KoaMxdc32Data>*>;
   }
   static void *newArray_maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<unsigned int,KoaBuffer<KoaMxdc32Data>*>[nElements] : new map<unsigned int,KoaBuffer<KoaMxdc32Data>*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR(void *p) {
      delete ((map<unsigned int,KoaBuffer<KoaMxdc32Data>*>*)p);
   }
   static void deleteArray_maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR(void *p) {
      delete [] ((map<unsigned int,KoaBuffer<KoaMxdc32Data>*>*)p);
   }
   static void destruct_maplEunsignedsPintcOKoaBufferlEKoaMxdc32DatagRmUgR(void *p) {
      typedef map<unsigned int,KoaBuffer<KoaMxdc32Data>*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<unsigned int,KoaBuffer<KoaMxdc32Data>*>

namespace ROOT {
   static TClass *maplEstringcOintgR_Dictionary();
   static void maplEstringcOintgR_TClassManip(TClass*);
   static void *new_maplEstringcOintgR(void *p = 0);
   static void *newArray_maplEstringcOintgR(Long_t size, void *p);
   static void delete_maplEstringcOintgR(void *p);
   static void deleteArray_maplEstringcOintgR(void *p);
   static void destruct_maplEstringcOintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,int>*)
   {
      map<string,int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,int>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,int>", -2, "map", 99,
                  typeid(map<string,int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOintgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,int>) );
      instance.SetNew(&new_maplEstringcOintgR);
      instance.SetNewArray(&newArray_maplEstringcOintgR);
      instance.SetDelete(&delete_maplEstringcOintgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOintgR);
      instance.SetDestructor(&destruct_maplEstringcOintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,int>*)0x0)->GetClass();
      maplEstringcOintgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,int> : new map<string,int>;
   }
   static void *newArray_maplEstringcOintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,int>[nElements] : new map<string,int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOintgR(void *p) {
      delete ((map<string,int>*)p);
   }
   static void deleteArray_maplEstringcOintgR(void *p) {
      delete [] ((map<string,int>*)p);
   }
   static void destruct_maplEstringcOintgR(void *p) {
      typedef map<string,int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,int>

namespace ROOT {
   static TClass *maplEstringcOdoublegR_Dictionary();
   static void maplEstringcOdoublegR_TClassManip(TClass*);
   static void *new_maplEstringcOdoublegR(void *p = 0);
   static void *newArray_maplEstringcOdoublegR(Long_t size, void *p);
   static void delete_maplEstringcOdoublegR(void *p);
   static void deleteArray_maplEstringcOdoublegR(void *p);
   static void destruct_maplEstringcOdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,double>*)
   {
      map<string,double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,double>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,double>", -2, "map", 99,
                  typeid(map<string,double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,double>) );
      instance.SetNew(&new_maplEstringcOdoublegR);
      instance.SetNewArray(&newArray_maplEstringcOdoublegR);
      instance.SetDelete(&delete_maplEstringcOdoublegR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOdoublegR);
      instance.SetDestructor(&destruct_maplEstringcOdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,double>*)0x0)->GetClass();
      maplEstringcOdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,double> : new map<string,double>;
   }
   static void *newArray_maplEstringcOdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,double>[nElements] : new map<string,double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOdoublegR(void *p) {
      delete ((map<string,double>*)p);
   }
   static void deleteArray_maplEstringcOdoublegR(void *p) {
      delete [] ((map<string,double>*)p);
   }
   static void destruct_maplEstringcOdoublegR(void *p) {
      typedef map<string,double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,double>

namespace ROOT {
   static TClass *maplEpairlEintcOintgRcOpairlEintcOintgRsPgR_Dictionary();
   static void maplEpairlEintcOintgRcOpairlEintcOintgRsPgR_TClassManip(TClass*);
   static void *new_maplEpairlEintcOintgRcOpairlEintcOintgRsPgR(void *p = 0);
   static void *newArray_maplEpairlEintcOintgRcOpairlEintcOintgRsPgR(Long_t size, void *p);
   static void delete_maplEpairlEintcOintgRcOpairlEintcOintgRsPgR(void *p);
   static void deleteArray_maplEpairlEintcOintgRcOpairlEintcOintgRsPgR(void *p);
   static void destruct_maplEpairlEintcOintgRcOpairlEintcOintgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<pair<int,int>,pair<int,int> >*)
   {
      map<pair<int,int>,pair<int,int> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<pair<int,int>,pair<int,int> >));
      static ::ROOT::TGenericClassInfo 
         instance("map<pair<int,int>,pair<int,int> >", -2, "map", 99,
                  typeid(map<pair<int,int>,pair<int,int> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEpairlEintcOintgRcOpairlEintcOintgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(map<pair<int,int>,pair<int,int> >) );
      instance.SetNew(&new_maplEpairlEintcOintgRcOpairlEintcOintgRsPgR);
      instance.SetNewArray(&newArray_maplEpairlEintcOintgRcOpairlEintcOintgRsPgR);
      instance.SetDelete(&delete_maplEpairlEintcOintgRcOpairlEintcOintgRsPgR);
      instance.SetDeleteArray(&deleteArray_maplEpairlEintcOintgRcOpairlEintcOintgRsPgR);
      instance.SetDestructor(&destruct_maplEpairlEintcOintgRcOpairlEintcOintgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<pair<int,int>,pair<int,int> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<pair<int,int>,pair<int,int> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEpairlEintcOintgRcOpairlEintcOintgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<pair<int,int>,pair<int,int> >*)0x0)->GetClass();
      maplEpairlEintcOintgRcOpairlEintcOintgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEpairlEintcOintgRcOpairlEintcOintgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEpairlEintcOintgRcOpairlEintcOintgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<pair<int,int>,pair<int,int> > : new map<pair<int,int>,pair<int,int> >;
   }
   static void *newArray_maplEpairlEintcOintgRcOpairlEintcOintgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<pair<int,int>,pair<int,int> >[nElements] : new map<pair<int,int>,pair<int,int> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEpairlEintcOintgRcOpairlEintcOintgRsPgR(void *p) {
      delete ((map<pair<int,int>,pair<int,int> >*)p);
   }
   static void deleteArray_maplEpairlEintcOintgRcOpairlEintcOintgRsPgR(void *p) {
      delete [] ((map<pair<int,int>,pair<int,int> >*)p);
   }
   static void destruct_maplEpairlEintcOintgRcOpairlEintcOintgRsPgR(void *p) {
      typedef map<pair<int,int>,pair<int,int> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<pair<int,int>,pair<int,int> >

namespace ROOT {
   static TClass *maplEpairlEintcOintgRcOintgR_Dictionary();
   static void maplEpairlEintcOintgRcOintgR_TClassManip(TClass*);
   static void *new_maplEpairlEintcOintgRcOintgR(void *p = 0);
   static void *newArray_maplEpairlEintcOintgRcOintgR(Long_t size, void *p);
   static void delete_maplEpairlEintcOintgRcOintgR(void *p);
   static void deleteArray_maplEpairlEintcOintgRcOintgR(void *p);
   static void destruct_maplEpairlEintcOintgRcOintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<pair<int,int>,int>*)
   {
      map<pair<int,int>,int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<pair<int,int>,int>));
      static ::ROOT::TGenericClassInfo 
         instance("map<pair<int,int>,int>", -2, "map", 99,
                  typeid(map<pair<int,int>,int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEpairlEintcOintgRcOintgR_Dictionary, isa_proxy, 0,
                  sizeof(map<pair<int,int>,int>) );
      instance.SetNew(&new_maplEpairlEintcOintgRcOintgR);
      instance.SetNewArray(&newArray_maplEpairlEintcOintgRcOintgR);
      instance.SetDelete(&delete_maplEpairlEintcOintgRcOintgR);
      instance.SetDeleteArray(&deleteArray_maplEpairlEintcOintgRcOintgR);
      instance.SetDestructor(&destruct_maplEpairlEintcOintgRcOintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<pair<int,int>,int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<pair<int,int>,int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEpairlEintcOintgRcOintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<pair<int,int>,int>*)0x0)->GetClass();
      maplEpairlEintcOintgRcOintgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEpairlEintcOintgRcOintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEpairlEintcOintgRcOintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<pair<int,int>,int> : new map<pair<int,int>,int>;
   }
   static void *newArray_maplEpairlEintcOintgRcOintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<pair<int,int>,int>[nElements] : new map<pair<int,int>,int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEpairlEintcOintgRcOintgR(void *p) {
      delete ((map<pair<int,int>,int>*)p);
   }
   static void deleteArray_maplEpairlEintcOintgRcOintgR(void *p) {
      delete [] ((map<pair<int,int>,int>*)p);
   }
   static void destruct_maplEpairlEintcOintgRcOintgR(void *p) {
      typedef map<pair<int,int>,int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<pair<int,int>,int>

namespace ROOT {
   static TClass *maplEintcOpairlEintcOintgRsPgR_Dictionary();
   static void maplEintcOpairlEintcOintgRsPgR_TClassManip(TClass*);
   static void *new_maplEintcOpairlEintcOintgRsPgR(void *p = 0);
   static void *newArray_maplEintcOpairlEintcOintgRsPgR(Long_t size, void *p);
   static void delete_maplEintcOpairlEintcOintgRsPgR(void *p);
   static void deleteArray_maplEintcOpairlEintcOintgRsPgR(void *p);
   static void destruct_maplEintcOpairlEintcOintgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,pair<int,int> >*)
   {
      map<int,pair<int,int> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,pair<int,int> >));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,pair<int,int> >", -2, "map", 99,
                  typeid(map<int,pair<int,int> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOpairlEintcOintgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,pair<int,int> >) );
      instance.SetNew(&new_maplEintcOpairlEintcOintgRsPgR);
      instance.SetNewArray(&newArray_maplEintcOpairlEintcOintgRsPgR);
      instance.SetDelete(&delete_maplEintcOpairlEintcOintgRsPgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOpairlEintcOintgRsPgR);
      instance.SetDestructor(&destruct_maplEintcOpairlEintcOintgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,pair<int,int> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,pair<int,int> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOpairlEintcOintgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,pair<int,int> >*)0x0)->GetClass();
      maplEintcOpairlEintcOintgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOpairlEintcOintgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOpairlEintcOintgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,pair<int,int> > : new map<int,pair<int,int> >;
   }
   static void *newArray_maplEintcOpairlEintcOintgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,pair<int,int> >[nElements] : new map<int,pair<int,int> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOpairlEintcOintgRsPgR(void *p) {
      delete ((map<int,pair<int,int> >*)p);
   }
   static void deleteArray_maplEintcOpairlEintcOintgRsPgR(void *p) {
      delete [] ((map<int,pair<int,int> >*)p);
   }
   static void destruct_maplEintcOpairlEintcOintgRsPgR(void *p) {
      typedef map<int,pair<int,int> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,pair<int,int> >

namespace ROOT {
   static TClass *maplEintcOintmUgR_Dictionary();
   static void maplEintcOintmUgR_TClassManip(TClass*);
   static void *new_maplEintcOintmUgR(void *p = 0);
   static void *newArray_maplEintcOintmUgR(Long_t size, void *p);
   static void delete_maplEintcOintmUgR(void *p);
   static void deleteArray_maplEintcOintmUgR(void *p);
   static void destruct_maplEintcOintmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,int*>*)
   {
      map<int,int*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,int*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,int*>", -2, "map", 99,
                  typeid(map<int,int*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOintmUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,int*>) );
      instance.SetNew(&new_maplEintcOintmUgR);
      instance.SetNewArray(&newArray_maplEintcOintmUgR);
      instance.SetDelete(&delete_maplEintcOintmUgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOintmUgR);
      instance.SetDestructor(&destruct_maplEintcOintmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,int*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,int*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOintmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,int*>*)0x0)->GetClass();
      maplEintcOintmUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOintmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOintmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,int*> : new map<int,int*>;
   }
   static void *newArray_maplEintcOintmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,int*>[nElements] : new map<int,int*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOintmUgR(void *p) {
      delete ((map<int,int*>*)p);
   }
   static void deleteArray_maplEintcOintmUgR(void *p) {
      delete [] ((map<int,int*>*)p);
   }
   static void destruct_maplEintcOintmUgR(void *p) {
      typedef map<int,int*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,int*>

namespace ROOT {
   static TClass *maplEintcOfloatmUgR_Dictionary();
   static void maplEintcOfloatmUgR_TClassManip(TClass*);
   static void *new_maplEintcOfloatmUgR(void *p = 0);
   static void *newArray_maplEintcOfloatmUgR(Long_t size, void *p);
   static void delete_maplEintcOfloatmUgR(void *p);
   static void deleteArray_maplEintcOfloatmUgR(void *p);
   static void destruct_maplEintcOfloatmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,float*>*)
   {
      map<int,float*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,float*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,float*>", -2, "map", 99,
                  typeid(map<int,float*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOfloatmUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,float*>) );
      instance.SetNew(&new_maplEintcOfloatmUgR);
      instance.SetNewArray(&newArray_maplEintcOfloatmUgR);
      instance.SetDelete(&delete_maplEintcOfloatmUgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOfloatmUgR);
      instance.SetDestructor(&destruct_maplEintcOfloatmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,float*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,float*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOfloatmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,float*>*)0x0)->GetClass();
      maplEintcOfloatmUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOfloatmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOfloatmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,float*> : new map<int,float*>;
   }
   static void *newArray_maplEintcOfloatmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,float*>[nElements] : new map<int,float*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOfloatmUgR(void *p) {
      delete ((map<int,float*>*)p);
   }
   static void deleteArray_maplEintcOfloatmUgR(void *p) {
      delete [] ((map<int,float*>*)p);
   }
   static void destruct_maplEintcOfloatmUgR(void *p) {
      typedef map<int,float*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,float*>

namespace {
  void TriggerDictionaryInitialization_G__KoaEmsDaqDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/home/yong/fairroot/v18_jun19/include",
"/home/yong/src/KoalaSoft/daq/ems",
"/home/yong/src/KoalaSoft/tools",
"/home/yong/src/KoalaSoft/data",
"/home/yong/src/KoalaSoft/detectors/recoil/simple",
"/home/yong/src/KoalaSoft/detectors/scint-forward",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/src/KoalaSoft/build_digi/daq/ems/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__KoaEmsDaqDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class KoaRunOnline;
class KoaEmsConfig;
class __attribute__((annotate("$clingAutoload$KoaEventAssembler.h")))  KoaEventAssembler;
class __attribute__((annotate("$clingAutoload$KoaRawEventAnalyzer.h")))  KoaRawEventAnalyzer;
class KoaEmsSource;
class KoaEmsFileSource;
class KoaEmsStreamSource;
class KoaUnpack;
class KoaScalorUnpack;
class KoaTimeUnpack;
class KoaMxdc32Unpack;
class KoaEmsRawEvent;
class KoaRawEvent;
class KoaEventAnalyzer;
class KoaEmsEventAnalyzer;
class KoaEventLgtAsm;
class KoaRawEventTransform;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__KoaEmsDaqDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#ifndef KOA_RUNONLINE_H
#define KOA_RUNONLINE_H

#include "FairRun.h"
#include "FairLogger.h"
#include "FairRunInfo.h"
#include "TString.h"

class FairSource;
class TFile;
class FairField;
class TObject;
class THttpServer;

class KoaRunOnline : public FairRun
{
 public:
  static KoaRunOnline* Instance();
  virtual ~KoaRunOnline();
  KoaRunOnline();

  void Init();
  void Run(Int_t Ev_start = -1, Int_t Ev_end = -1);
  /** Re-read all parameters in case run id changed **/
  void Reinit(UInt_t runId);

  /** Set if the run should be closed automatically after executing the run functuion **/
  void SetAutoFinish(Bool_t val) { fAutomaticFinish = val; }
  /** Set the source which should be used **/
  void SetSource(FairSource* source) { fRootManager->SetSource(source); }
  /** Return pointer to source **/
  FairSource* GetSource() { return fRootManager->GetSource(); }

  /** Set external geometry file */
  void SetGeomFile(const char* GeoFileName);
  /** Return a pointer to the geometry file */
  TFile* GetGeoFile() { return fInputGeoFile; }

  /** Initialization of parameter container is set to static **/
  //  i.e: param continers will not be reinit if the run id changes in the same session
  void        SetContainerStatic(Bool_t tempBool=kTRUE);
  Bool_t      GetContainerStatic() { return fStaticParamContainer; };

  /// The following function is the interface of FairRun, it's meaningless in KoalaSoft ///
  FairField*  GetField() {
    LOG(WARN) << "There is no magnetic field in KOALA experiment";
    return 0;
  }

  /** Add histogram to be displayed using THttpServer.*/
  void AddObject(TObject* object);
  /** Register a command on the http server.
   * @param name a command name starting with /
   * @param command a call to method "/object_name/->Method()"
   */
  void RegisterHttpCommand(TString name, TString command);
  /** Activate http server on defined host port. To be called before Init.
   * @param refreshRate an interval in number of events for server update.
   * @param httpPort the port which is used by the http server
   */
  void ActivateHttpServer(Int_t refreshRate = 10000, Int_t httpPort=8080);
  /** Get direct access to the http server. */
  THttpServer* GetHttpServer() { return fServer; }

 private:
  KoaRunOnline(const KoaRunOnline& rhs);
  KoaRunOnline& operator=(const KoaRunOnline& rhs) { return *this; }

  /** Event Loop Implementation **/
  Int_t EventLoop();
  /** Fill operation after each event **/
  void Fill();
  /** Write last data to file, close input and output **/
  void Finish();
  
 private:
  static KoaRunOnline* fgRinstance;

  Bool_t fIsInitialized;
  Bool_t fAutomaticFinish;
  Bool_t fStaticParamContainer;

  FairRunInfo fRunInfo;//!

  /** Geometry file related **/
  TFile* fInputGeoFile;
  Bool_t fLoadGeo;

  /** Http Server related **/
  Int_t fNevents;      //!
  THttpServer* fServer;             //!
  Int_t fServerRefreshRate;  //!

  ClassDef(KoaRunOnline, 1)
};

#endif
#ifndef KOA_EMS_CONFIG_H
#define KOA_EMS_CONFIG_H

#include "TObject.h"
#include <cstdint>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

/* Module type enumeration. The value comes from KoalaEms definition, which is not important in KoalaSoft. */
enum class MesytecType : std::uint64_t
{
    MTDC32 = 0x23f10032UL,
    MADC32 = 0x21f10032UL,
    MQDC32 = 0x22f10032UL,
    INVALID = 0x00000000UL
};

/* Module configuration table. Module id as key, Module info as value */
struct ModuleInfo
{
  ModuleInfo() : type(MesytecType::INVALID), name("INVALID") {}
  ModuleInfo(MesytecType& intype, std::string& inname) : type(intype), name(inname) {}

  MesytecType type;
  std::string name;
};

using ModuleId = std::uint32_t;
using ModuleTable = std::map<ModuleId, ModuleInfo>;

/* Types used in Module Channel mapping */
using ChannelInfo = std::pair<Int_t, Int_t>; // for DAQ, it's <ModuleId, ModuleCh>; for detector, it's <DetectorId, DetectorCh>
using ChannelMap = std::map<Int_t, ChannelInfo>; // from encoded detector channel id to DAQ channel info
using ChannelMapReverse = std::map<ChannelInfo, Int_t>; // from DAQ channel info to encoded detector channel id
using ChannelInfoMap = std::map<ChannelInfo, ChannelInfo>; // from channel info pair to channel info map

using ScalorMap = std::map<std::string, int>;

/* This class stores the EMS DAQ configuration information and the mapping table from
   DAQ channel to Detector channel.

   DAQ configuration information is:
   1. Number of Modules used
   2. Type ID of the module
   3. ID of the module
   4. Name of the module

   The mapping table is:
   1. 1-1 mapping from module channel to Koala detector readout channel
   2. Each type of the module has a separate mapping table

   These information is provide by the user as a text configuration file.
   It's a singleton class and should be instantiated once and owned by the user himself.
   After the usage, the user is in charge of the destruction of this singleton.
 */
class KoaEmsConfig : public TObject
{
public:
  KoaEmsConfig();
  ~KoaEmsConfig();

  static KoaEmsConfig* Instance() {
    return fgInstance;
  }

  // Module configuration table

  bool SetEmsConfigFile(const char* filename);
  bool SetAmplitudeChannelMap(const char* filename);
  bool SetTimeChannelMap(const char* filename);
  bool SetScalorChannelMap(const char* filename);

  //
  void PrintModuleTable(const char* filename = nullptr);
  void PrintAmplitudeChannelMap(const char* filename = nullptr);
  void PrintTimeChannelMap(const char* filename = nullptr);
  void PrintScalorChannelMap(const char* filename = nullptr);

  //
  ModuleTable GetModuleTable() { return fModuleTable; }

  ChannelInfoMap GetAmplitudeChMapInfo() { return fChInfoMap_Amplitude; }
  ChannelInfoMap GetTimeChMapInfo() { return fChInfoMap_Time; }

  ChannelInfoMap GetAmplitudeChMapInfoReverse() { return fChInfoMapReverse_Amplitude; }
  ChannelInfoMap GetTimeChMapInfoReverse() { return fChInfoMapReverse_Time; }

  ChannelMap GetAmplitudeChMap() { return fChMap_Amplitude; }
  ChannelMap GetTimeChMap() { return fChMap_Time; }

  ChannelMapReverse GetAmplitudeChMapReverse() { return fChMapReverse_Amplitude; }
  ChannelMapReverse GetTimeChMapReverse() { return fChMapReverse_Time; }

  ScalorMap GetScalorChMap() { return fScalorChMap; }

private:
  bool ReadEmsConfig(std::ifstream& infile);
  bool ReadAmplitudeChannelMapConfig(std::ifstream& infile);
  bool ReadTimeChannelMapConfig(std::ifstream& infile);
  bool ReadScalorChannelMapConfig(std::ifstream& infile);

private:
  std::string fFileEmsConfig;
  std::string fFileAmplitudeMapConfig;
  std::string fFileTimeMapConfig;
  std::string fFileScalorMapConfig;

  ModuleTable fModuleTable; // EMS configuration

  ChannelInfoMap fChInfoMap_Amplitude; // from detector channel info pair to DAQ channel info pair
  ChannelInfoMap fChInfoMap_Time;
  ChannelInfoMap fChInfoMapReverse_Amplitude; // from DAQ channel info pair to detector channel info pair
  ChannelInfoMap fChInfoMapReverse_Time;

  ChannelMap     fChMap_Amplitude; // from encoded detector channel id to DAQ channel info pair
  ChannelMap     fChMap_Time;
  ChannelMapReverse fChMapReverse_Amplitude; // from DAQ channel info pair to encoded channel id
  ChannelMapReverse fChMapReverse_Time;

  ScalorMap fScalorChMap;

  // static instance
  static KoaEmsConfig* fgInstance;

  ClassDef(KoaEmsConfig, 1)
};
#endif
#ifndef KOA_EMS_SOURCE_H
#define KOA_EMS_SOURCE_H

#include "FairSource.h"
#include "FairLogger.h"
#include "ems_interface.h"
#include "KoaEventAssembler.h"
#include "KoaRawEventAnalyzer.h"
#include <map>
#include "stdio.h"

class KoaUnpack;
class KoaRawEventAnalyzer;
class KoaEventAssembler;

class KoaEmsSource : public FairSource
{
 public:
  KoaEmsSource() : fInput(-1), fAssembler(nullptr), fKoaEvtAnalyzer(nullptr), fEmsEvtAnalyzer(nullptr)
  {}
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
  virtual Bool_t NextCluster();
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

protected:
  int fInput; // posix file descriptor for input stream, disk file or network streaming

private:
  ems_cluster fCluster; // buffer containing one raw binary EMS cluster, also in charge of cluster read
  std::map<ems_u32, KoaUnpack*> fUnpackers; // unpackers for each subevent in EMS

  KoaEventAssembler *fAssembler; // in charge of assemblying modules based on same timestamp
  KoaRawEventAnalyzer  *fKoaEvtAnalyzer; // decoding the module data into detector channel data
  KoaRawEventAnalyzer  *fEmsEvtAnalyzer; // decoding ems data

  ClassDef(KoaEmsSource, 1)
};

#endif
#ifndef KOA_EMS_FILE_SOURCE_H
#define KOA_EMS_FILE_SOURCE_H

#include "KoaEmsSource.h"
#include <string>

class KoaEmsFileSource : public KoaEmsSource
{
public:
  KoaEmsFileSource() {}
  KoaEmsFileSource(const char* filename)
  {
    SetupInput(filename);
  }
  ~KoaEmsFileSource() {}

  virtual Bool_t SetupInput(const char* filename);

private:
  std::string fFileName;

  ClassDef(KoaEmsFileSource, 1)
};

#endif
#ifndef KOA_EMS_STREAM_SOURCE_H
#define KOA_EMS_STREAM_SOURCE_H

#include "KoaEmsSource.h"

class KoaEmsStreamSource : public KoaEmsSource
{
public:
  KoaEmsStreamSource() {}
  KoaEmsStreamSource(const char* server)
  {
    SetupInput(server);
  }
  ~KoaEmsStreamSource() {}

  virtual Bool_t SetupInput(const char* server);
  virtual Bool_t SetupInput(std::string ip, std::string port);
  virtual void Close();

  ClassDef(KoaEmsStreamSource, 1)
};
#endif
#ifndef KOA_UNPACK_H
#define KOA_UNPACK_H

#include "TNamed.h"
#include "ems_interface.h"

class KoaUnpack : public TNamed
{
 public:
  KoaUnpack(ems_u32 is_id, const char* name, const char* title) : TNamed(name, title), fISId(is_id) {}
  virtual ~KoaUnpack() {}

  virtual Bool_t Init() = 0;
  virtual Bool_t ReInit() { return kTRUE; }
  virtual Int_t DoUnpack(const ems_u32* buf, Int_t size) = 0;
  virtual void   Reset() = 0;
  virtual void   SetParContainers() {};

  inline ems_u32 GetISId()    const { return fISId; }

 private:
  ems_u32 fISId; // Instrument ID in EMS configuration file

  ClassDef(KoaUnpack, 1)
};
#endif
#ifndef KOA_SCALOR_UNPACK_H
#define KOA_SCALOR_UNPACK_H

#include "KoaUnpack.h"
#include "KoaEmsEventData.h"

class KoaScalorUnpack : public KoaUnpack
{
 public:
 KoaScalorUnpack(ems_u32 is_id) : KoaUnpack(is_id, "ScalorUnpacker", "Unpacker for Scalor Data")
    {}
  ~KoaScalorUnpack() {}

  Bool_t Init();
  Int_t  DoUnpack(const ems_u32* buf, Int_t size);
  void   Reset() {}

 private:
  KoaEmsEventBuffer *fEmsBuffer;
  
  ClassDef(KoaScalorUnpack, 1)
};
#endif
#ifndef KOA_TIME_UNPACK_H
#define KOA_TIME_UNPACK_H

#include "KoaUnpack.h"
#include "KoaEmsEventData.h"

class KoaTimeUnpack : public KoaUnpack
{
 public:
 KoaTimeUnpack(ems_u32 is_id) : KoaUnpack(is_id, "TimeUnpacker", "Unpacker for Ems Time information")
    {}
  ~KoaTimeUnpack() {}

  Bool_t Init();
  Int_t  DoUnpack(const ems_u32* buf, Int_t size);
  void   Reset() {}

 private:
  KoaEmsEventBuffer *fEmsBuffer;

  ClassDef(KoaTimeUnpack, 1)
};
#endif
#ifndef KOA_MXDC32_UNPACK_H
#define KOA_MXDC32_UNPACK_H

#include "KoaUnpack.h"
#include "KoaMxdc32Data.h"
#include "KoaEmsConfig.h"
#include <map>

class KoaMxdc32Unpack : public KoaUnpack
{
 public:
  KoaMxdc32Unpack(ems_u32 is_id) : KoaUnpack(is_id, "Mxdc32Unpacker", "Unpacker for Mxdc32 module data")
  {}
  ~KoaMxdc32Unpack() {}

  Bool_t Init();
  Int_t  DoUnpack(const ems_u32* buf, Int_t size);
  void   Reset() {}

private:
  std::map<ModuleId, KoaMxdc32Buffer*> fModuleBuffer;
  ModuleTable fModuleTable;

  ClassDef(KoaMxdc32Unpack, 1)
};
#endif
#ifndef KOA_EMS_RAWEVENT_H
#define KOA_EMS_RAWEVENT_H

#include "TObject.h"

/* Ems Raw Event format after decoding
 * It contains the timestamp and scalor counts.
 * Scalors are not named. The channel mapping of the scalor is saved in an std::map<std::string,int> object.
 * 
 */

class KoaEmsRawEvent : public TObject
{
public:
  UInt_t Scalor[32];
  Long_t Second;
  Long_t Usecond;
  UInt_t EventNr;

  KoaEmsRawEvent& operator=(const KoaEmsRawEvent& rhs) {
    for ( int i=0; i < 32 ; i++ ) {
      Scalor[i] = rhs.Scalor[i];
    }

    Second = rhs.Second;
    Usecond = rhs.Usecond;
    EventNr = rhs.EventNr;

    return *this;
  }

  ClassDef(KoaEmsRawEvent, 1)
};

ClassImp(KoaEmsRawEvent)
#endif
#ifndef KOA_RAW_EVENT_H
#define KOA_RAW_EVENT_H

#include <map>
#include <utility>
#include "KoaMapEncoder.h"

constexpr Int_t UNDER_THRESHOLD = -5;
constexpr Int_t ADC_OVERFLOW = 0x2000;
constexpr Int_t QDC_OVERFLOW = 0x1000;

/* Raw Event format after decoding.
 * Since it's an unamed class, it can only be registered as a tree branch through:
 * FairRootManager->RegisterAny() but not FairRootManager->Register()
 */
class KoaRawEvent
{
public:
  // Amplitudes
  Int_t     Si1A[48];
  Int_t     Si2A[64];
  Int_t     Ge1A[32];
  Int_t     Ge2A[32];
  Int_t     RecRearA[4];
  Int_t     FwdA[8];

  // Timestamps
  Float_t   Si1T[48];// unit: ns
  Float_t   Si2T[64];// unit: ns
  Float_t   Ge1T[32];// unit: ns
  Float_t   Ge2T[32];// unit: ns
  Float_t   RecRearT[4];// unit: ns
  Float_t   FwdT[8];// unit: ns

  // Mxdc32 Timestamp
  Long64_t  Timestamp; // frq of VME bus, unit: 25 ns

public:
  inline std::map<Int_t, Int_t*> GetAmplitudeValueMap() const;
  inline std::map<Int_t, Int_t*> GetRecAmplitudeValueMap() const;
  inline std::map<Int_t, Int_t*> GetFwdAmplitudeValueMap() const;
  inline std::map<Int_t, Int_t*> GetRecRearAmplitudeValueMap() const;

  inline std::map<Int_t, Float_t*> GetTimeValueMap() const;
  inline std::map<Int_t, Float_t*> GetRecTimeValueMap() const;
  inline std::map<Int_t, Float_t*> GetFwdTimeValueMap() const;
  inline std::map<Int_t, Float_t*> GetRecRearTimeValueMap() const;

  ClassDef(KoaRawEvent, 2)
};

inline std::map<Int_t, Int_t*> KoaRawEvent::GetAmplitudeValueMap() const
{
  //
  std::map<Int_t, Int_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t rec_low, rec_high;
  encoder->GetRecDetIDRange(rec_low, rec_high);
  Int_t fwd_low, fwd_high;
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t rec_rear = encoder->GetRecRearID();

  // recoil front
  for( int i =0; i<48; i++) {
    auto id = encoder->EncodeChannelID(rec_low, i);
    value_map.emplace(id, (Int_t*)Si1A+i);
    // value_map.emplace(std::make_pair(id, (Int_t*)Si1A+i));
    // value_map.emplace(std::make_pair<Int_t,const Int_t*>(id, Si1A+i));
  }
  for( int i =0; i<64; i++) {
    auto id = encoder->EncodeChannelID(rec_low+1, i);
    // value_map.emplace(id, Si2A+i);
    value_map.emplace(std::make_pair(id, (Int_t*)Si2A+i));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+2, i);
    // value_map.emplace(id, Ge1A+i);
    value_map.emplace(std::make_pair(id, (Int_t*)Ge1A+i));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+3, i);
    // value_map.emplace(id, Ge2A+i);
    value_map.emplace(std::make_pair(id, (Int_t*)Ge2A+i));
  }

  // fwd 
  for( int i =0; i<8; i++) {
    auto id = encoder->EncodeChannelID(fwd_low+i, 0);
    value_map.emplace(std::make_pair( id, (Int_t*)FwdA+i ));
  }

  // recoil rear
  for( int i =0; i<4; i++) {
    auto id = encoder->EncodeChannelID(rec_rear, i);
    value_map.emplace(std::make_pair( id, (Int_t*)RecRearA+i ));
  }

  return value_map;
}

inline std::map<Int_t, Int_t*> KoaRawEvent::GetRecAmplitudeValueMap() const
{
  //
  std::map<Int_t, Int_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t rec_low, rec_high;
  encoder->GetRecDetIDRange(rec_low, rec_high);

  // recoil front
  for( int i =0; i<48; i++) {
    auto id = encoder->EncodeChannelID(rec_low, i);
    value_map.emplace(std::make_pair( id, (Int_t*)Si1A+i ));
  }
  for( int i =0; i<64; i++) {
    auto id = encoder->EncodeChannelID(rec_low+1, i);
    value_map.emplace(std::make_pair( id, (Int_t*)Si2A+i ));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+2, i);
    value_map.emplace(std::make_pair( id, (Int_t*)Ge1A+i ));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+3, i);
    value_map.emplace(std::make_pair( id, (Int_t*)Ge2A+i ));
  }

  return value_map;
}

inline std::map<Int_t, Int_t*> KoaRawEvent::GetFwdAmplitudeValueMap() const
{
  //
  std::map<Int_t, Int_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t fwd_low, fwd_high;
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);

  // fwd 
  for( int i =0; i<8; i++) {
    auto id = encoder->EncodeChannelID(fwd_low+i, 0);
    value_map.emplace(std::make_pair( id, (Int_t*)FwdA+i ));
  }

  return value_map;
}

inline std::map<Int_t, Int_t*> KoaRawEvent::GetRecRearAmplitudeValueMap() const
{
  //
  std::map<Int_t, Int_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t rec_rear = encoder->GetRecRearID();

  // recoil rear
  for( int i =0; i<4; i++) {
    auto id = encoder->EncodeChannelID(rec_rear, i);
    value_map.emplace(std::make_pair( id, (Int_t*)RecRearA+i ));
  }

  return value_map;
}

inline std::map<Int_t, Float_t*> KoaRawEvent::GetTimeValueMap() const
{
  //
  std::map<Int_t, Float_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t rec_low, rec_high;
  encoder->GetRecDetIDRange(rec_low, rec_high);
  Int_t fwd_low, fwd_high;
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t rec_rear = encoder->GetRecRearID();

  // recoil front
  for( int i =0; i<48; i++) {
    auto id = encoder->EncodeChannelID(rec_low, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Si1T+i ));
  }
  for( int i =0; i<64; i++) {
    auto id = encoder->EncodeChannelID(rec_low+1, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Si2T+i ));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+2, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Ge1T+i ));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+3, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Ge2T+i ));
  }

  // fwd 
  for( int i =0; i<8; i++) {
    auto id = encoder->EncodeChannelID(fwd_low+i, 0);
    value_map.emplace(std::make_pair( id, (Float_t*)FwdT+i ));
  }

  // recoil rear
  for( int i =0; i<4; i++) {
    auto id = encoder->EncodeChannelID(rec_rear, i);
    value_map.emplace(std::make_pair( id, (Float_t*)RecRearT+i ));
  }

  return value_map;
}

inline std::map<Int_t, Float_t*> KoaRawEvent::GetRecTimeValueMap() const
{
  //
  std::map<Int_t, Float_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t rec_low, rec_high;
  encoder->GetRecDetIDRange(rec_low, rec_high);

  // recoil front
  for( int i =0; i<48; i++) {
    auto id = encoder->EncodeChannelID(rec_low, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Si1T+i ));
  }
  for( int i =0; i<64; i++) {
    auto id = encoder->EncodeChannelID(rec_low+1, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Si2T+i ));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+2, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Ge1T+i ));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+3, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Ge2T+i ));
  }

  return value_map;
}

inline std::map<Int_t, Float_t*> KoaRawEvent::GetFwdTimeValueMap() const
{
  //
  std::map<Int_t, Float_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t fwd_low, fwd_high;
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);

  // fwd 
  for( int i =0; i<8; i++) {
    auto id = encoder->EncodeChannelID(fwd_low+i, 0);
    value_map.emplace(std::make_pair( id, (Float_t*)FwdT+i ));
  }

  return value_map;
}

inline std::map<Int_t, Float_t*> KoaRawEvent::GetRecRearTimeValueMap() const
{
  //
  std::map<Int_t, Float_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t rec_rear = encoder->GetRecRearID();

  // recoil rear
  for( int i =0; i<4; i++) {
    auto id = encoder->EncodeChannelID(rec_rear, i);
    value_map.emplace(std::make_pair( id, (Float_t*)RecRearT+i ));
  }

  return value_map;
}

#endif
#ifndef KOA_RAWEVENT_ANALYZER_H
#define KOA_RAWEVENT_ANALYZER_H

#include "FairLogger.h"
#include "TObject.h"
#include "TFile.h"
#include "TString.h"

class KoaRawEventAnalyzer : public TObject
{
public:
  KoaRawEventAnalyzer() : fPersistence(false), fRootFile(nullptr) {}
  virtual ~KoaRawEventAnalyzer() {
    DeleteHist();

    if (fRootFile) {
      delete fRootFile;
    }
  }

  /* whether save data into array based tree */
  // CAVEAT: should be invoked after setting FairRootFileSink in macro
  void SetPersistence(bool flag) {
    fPersistence = flag;
    fRootFile = nullptr;

    if (fPersistence) {
      fRootFile = InitOutputFile();
    }
  }

  /* initialize */
  void Init() {
    LOG(info) << "KoaRawEventAnalyzer::Init";

    // 1. get channel mapping parameter
    InitChannelMap();

    // 2. get input event buffer
    InitInputBuffer();

    // 3. initialize output buffer
    InitOutputBuffer();

    // 4. initialize output tree
    InitOutputTree();

    // 5. initialize histograms
    InitHist();
  }

  /* analyze */
  bool Analyze() {
    // 1. get the latest event from input buffer
    if (!NextEvent())  return false;

    // 2. decode
    Decode();

    // 3. update
    Update();

    // 4. fill tree
    FillTree();

    // 5. fill histograms
    FillHist();

    // 6. recycle input event buffer
    Recycle();

    return true;
  }

  /* finish */
  void Finish() {
    if ( fPersistence && fRootFile ) {
      fRootFile->Write();
    }
  }


private:
  virtual TFile* InitOutputFile() = 0;

  virtual void InitInputBuffer() = 0;
  virtual void InitChannelMap() = 0;
  virtual void InitOutputBuffer() = 0;
  virtual void InitOutputTree() = 0;

  virtual bool NextEvent() = 0;
  virtual void Decode() = 0;
  virtual void FillTree() = 0;
  virtual void Recycle() = 0;

protected:
  virtual void InitHist() {}
  virtual void FillHist() {}
  virtual void DeleteHist() {}

  virtual void Update() {}

  bool fPersistence;
  TFile* fRootFile;

  ClassDef(KoaRawEventAnalyzer, 1)
};
#endif
#ifndef KOA_EVENT_ANALYZER_H
#define KOA_EVENT_ANALYZER_H

#include "KoaRawEventAnalyzer.h"
#include "KoaEventData.h"
#include "KoaMxdc32Data.h"
#include "KoaRawEvent.h"
#include "KoaEmsConfig.h"
#include <map>

class KoaEventAnalyzer : public KoaRawEventAnalyzer
{
public:
  KoaEventAnalyzer() : fSaveRawEvent(kFALSE) {}
  ~KoaEventAnalyzer();

  void SaveRawEvent(bool flag) { fSaveRawEvent = flag; }

private:
  TFile* InitOutputFile();

  void InitInputBuffer();
  void InitChannelMap();
  void InitOutputBuffer();
  void InitOutputTree();

  bool NextEvent();
  void Decode();
  void FillTree();
  void Recycle() { fCurrentEvent->Recycle(); }

private:
  // whether same KoaRawEvent into disk
  bool fSaveRawEvent;

  // koala event buffer
  KoaEventBuffer* fBuffer; //!
  KoaEventDataItem* fCurrentEvent; //!

  // ems configuration and channel mapping
  ModuleTable fModuleTable; //!
  ChannelMap fAmplitudeChannelMap; //!
  ChannelMap fTimeChannelMap; //!

  // output trees, each module has it's own tree
  std::map<ems_u32, TTree*> fTreeMap; //!

  // Koala Event Data, where the decoded module data are stored
  std::map<ems_u32, Int_t> fIndexMap; //! mapping from module id to array index
  UChar_t *fModuleId; //!
  Char_t  *fResolution; //!
  Short_t   *fNrWords; //!
  Long64_t *fTimestamp; //!
  Int_t (*fData)[34]; //!
  std::map<Int_t, Int_t*> fAmplitudeValueMapInput; //!
  std::map<Int_t, Int_t*> fTimeValueMapInput; //!
  std::map<Int_t, Char_t*> fTimeResolutionMap; //!

  // Output class data, where the channel mapping is resolved
  KoaRawEvent* fRawEvent; //!
  std::map<Int_t, Int_t*> fAmplitudeValueMapOutput; //!
  std::map<Int_t, Float_t*> fTimeValueMapOutput; //!

  /* constexpr static Float_t fTimeUnit[] = {-1,1./256,2./256,4./256,8./256,16./256,32./256,64./256,128./256}; //! unit: ns */
  static const Float_t fTimeUnit[9];

  ClassDef(KoaEventAnalyzer, 1)
};
#endif
#ifndef KOA_EMSEVENT_ANALYZER_H
#define KOA_EMSEVENT_ANALYZER_H

#include "KoaRawEventAnalyzer.h"
#include "KoaEmsEventData.h"
#include <map>

class KoaEmsRawEvent;
class TTree;

class KoaEmsEventAnalyzer : public KoaRawEventAnalyzer
{
 public:
  KoaEmsEventAnalyzer() : fInitialEvent(true) {}
  ~KoaEmsEventAnalyzer();

 private:
  TFile* InitOutputFile();

  void InitInputBuffer();
  void InitChannelMap();
  void InitOutputBuffer();
  void InitOutputTree();

  bool NextEvent();
  void Decode();
  void FillTree();
  void Recycle() { fCurrentEvent->Recycle(); }

  void Update();
  void FillHist();

 private:
  // ems event buffer and current item
  KoaEmsEventBuffer* fBuffer;
  KoaEmsEventDataItem* fCurrentEvent;

  // decoded ems event data
  KoaEmsRawEvent* fCurrentRawEvent;
  KoaEmsRawEvent* fPreviousRawEvent;

  // output tree
  TTree* fTree;
  std::map<std::string, int> fScalorChMap;

  // rate container
  bool fInitialEvent; // flag for the first coming event
  Long_t fCurrentTime; // unit: second

  using RateMap = std::map<std::string, double>; // map from scalor channel name to scalor counter value
  RateMap fRates;
  std::vector<Long_t> fSpareTime; // array of timestamp in a  long period when no event comes

  ClassDef(KoaEmsEventAnalyzer, 1)
};
#endif
#ifndef KOA_EVENT_ASSEMBLER_H
#define KOA_EVENT_ASSEMBLER_H

/* This class will assemble tha koala event from each module into a synchronized event based timestamp
 *
 */

#include "TObject.h"
#include "KoaMxdc32Data.h"
#include "KoaEventData.h"
#include "KoaEmsConfig.h"
#include <map>

constexpr int64_t TS_RANGE = 0x40000000;

class KoaEventAssembler : public TObject
{
public:
  KoaEventAssembler() : fQdcTimeDiff(3), fMaxTimeDiff(4)
  {}
  virtual ~KoaEventAssembler() {}

  virtual void Init();
  virtual void Assemble();
  virtual void Finish() {}
  virtual void PrintStatistics() {}
  

  void SetQdcTimeDiff(int diff){
    fQdcTimeDiff=diff;
  }
  void SetMaxTimeDiff(int diff){
    fMaxTimeDiff = diff;
  }

protected:
  virtual bool NextEvent() { return IsFull(); }

  enum class TSType {Equal, Greater, Less };
  // whether two timestamp are synchronized
  TSType IsSameTS(int64_t first, int64_t second)
  {
    int64_t delta_t = first - second;

    if ( delta_t > TS_RANGE/2 ) delta_t -= TS_RANGE;
    if ( delta_t < -TS_RANGE/2 ) delta_t += TS_RANGE;

    if ( delta_t > fMaxTimeDiff ){
      return TSType::Greater;
    }
    else if ( delta_t < -fMaxTimeDiff ) {
      return TSType::Less;
    }

    return TSType::Equal;
  }

  // whether all of the module have at least one event data available
  Bool_t IsFull()
  {
    for ( auto buffer : fModuleBuffer ) {
      if ( buffer.second->IsEmpty() )
        return false;
    }
    return true;
  }

  // collect the timestamps of current item from all modules
  // in the same time, correct the qdc offset
  void CollectTS()
  {
    for ( auto& module : fModuleTable ) {
      auto module_id = module.first;
      auto ts = fModuleBuffer[module_id]->Current()->fData.timestamp;
      if(module.second.type == MesytecType::MQDC32) {
        ts -= fQdcTimeDiff;
      }
      fTSs[module_id] = ts;
    }
  }

protected:
  int fModuleNr;
  std::map<ModuleId, KoaMxdc32Buffer*> fModuleBuffer;
  ModuleTable fModuleTable;
  KoaEventBuffer* fKoalaBuffer;

  Int_t   fQdcTimeDiff; // correction of QDC timestamp, the width of QDC gate in 62.5ns
  Int_t   fMaxTimeDiff; // the maximum difference of timestamps between module

  std::map<ModuleId,int64_t> fTSs; // collection of current timestamps

  ClassDef(KoaEventAssembler, 1)
};
#endif
#ifndef KOA_EVENT_LIGHTASSEMBLER_H
#define KOA_EVENT_LIGHTASSEMBLER_H

#include "KoaEventAssembler.h"
#include <vector>

/* Assemble algorithms:
 * 1. find the smallest timestamp
 * 2. If all the modules have the same timestamp, pop out all top items and assemble
 * 3. Otherwise, pop out the top item of modules which have the same timestamp as the smallest timestamp
 * 4. Go back to step1 and repeat
 */
class KoaEventLgtAsm : public KoaEventAssembler
{
public:
  KoaEventLgtAsm() {}
  virtual ~KoaEventLgtAsm() {}

private:
  bool NextEvent();

private:
  std::vector<ModuleId> fMinTSs;

  ClassDef(KoaEventLgtAsm, 1)
};
#endif
#ifndef KOA_RAWEVENT_TRANSFORM_H
#define KOA_RAWEVENT_TRANSFORM_H

#include "FairTask.h"
#include "TClonesArray.h"
#include "FairLogger.h"

class KoaRawEvent;

/* This class is used to transform KOALA raw event to standard simulation output data form.
 * It should be used together with KoaEmsSource.
 * If persistence flag is set, both the original and transformed objects are saved into file.
 * Otherwise, only the transformed objects are saved.
 */
class KoaRawEventTransform : public FairTask
{
 public:
  /** Default constructor **/
  KoaRawEventTransform() : FairTask("KoaRawEventTransform"),
                           fRawEvent(nullptr),
                           fFwdDigis(nullptr),
                           fRecDigis(nullptr),
                           fRecRearDigis(nullptr)
  {
    LOG(debug) << "KoaRawEventTransform : Default Constructor";
  }

  /** Destructor **/
  ~KoaRawEventTransform()
  {
    LOG(debug) << "KoaRawEventTransform : Destructor";

    if ( fRecDigis ) {
      fRecDigis->Delete();
      delete fRecDigis;
    }

    if ( fFwdDigis ) {
      fFwdDigis->Delete();
      delete fFwdDigis;
    }

    if ( fRecRearDigis ) {
      fRecRearDigis->Delete();
      delete fRecRearDigis;
    }
  }


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
  
private:
  KoaRawEventTransform(const KoaRawEventTransform&);
  KoaRawEventTransform operator=(const KoaRawEventTransform&);

private:
  // input object
  // KoaRawEvent *fRawEvent;
  KoaRawEvent const *fRawEvent;

  // output objects
  TClonesArray* fRecDigis;
  TClonesArray* fFwdDigis;
  TClonesArray* fRecRearDigis;

  // value maps
  std::map<Int_t, Int_t*> fRecAmplitudeValueMap;
  std::map<Int_t, Float_t*> fRecTimeValueMap;

  std::map<Int_t, Int_t*> fFwdAmplitudeValueMap;
  std::map<Int_t, Float_t*> fFwdTimeValueMap;

  std::map<Int_t, Int_t*> fRecRearAmplitudeValueMap;
  std::map<Int_t, Float_t*> fRecRearTimeValueMap;

  ClassDef(KoaRawEventTransform,1)
};
#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"KoaEmsConfig", payloadCode, "@",
"KoaEmsEventAnalyzer", payloadCode, "@",
"KoaEmsFileSource", payloadCode, "@",
"KoaEmsRawEvent", payloadCode, "@",
"KoaEmsSource", payloadCode, "@",
"KoaEmsStreamSource", payloadCode, "@",
"KoaEventAnalyzer", payloadCode, "@",
"KoaEventAssembler", payloadCode, "@",
"KoaEventLgtAsm", payloadCode, "@",
"KoaMxdc32Unpack", payloadCode, "@",
"KoaRawEvent", payloadCode, "@",
"KoaRawEventAnalyzer", payloadCode, "@",
"KoaRawEventTransform", payloadCode, "@",
"KoaRunOnline", payloadCode, "@",
"KoaScalorUnpack", payloadCode, "@",
"KoaTimeUnpack", payloadCode, "@",
"KoaUnpack", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__KoaEmsDaqDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__KoaEmsDaqDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__KoaEmsDaqDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__KoaEmsDaqDict() {
  TriggerDictionaryInitialization_G__KoaEmsDaqDict_Impl();
}
