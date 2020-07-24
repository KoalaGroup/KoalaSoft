// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_jensdItoolsdIG__KoaToolsDict

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
#include "KoaGeoHandler.h"
#include "KoaMapHandler.h"
#include "KoaMapEncoder.h"
#include "KoaElasticCalculator.h"
#include "KoaTextUtility.h"
#include "PndGeoHandling.h"
#include "PndSensorNamePar.h"
#include "PndSensorNameContFact.h"
#include "PndStringSeparator.h"

// Header files passed via #pragma extra_include

namespace KoaUtility {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *KoaUtility_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("KoaUtility", 0 /*version*/, "", 412,
                     ::ROOT::Internal::DefineBehavior((void*)0,(void*)0),
                     &KoaUtility_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *KoaUtility_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace ROOT {
   static void *new_KoaGeoHandler(void *p = 0);
   static void *newArray_KoaGeoHandler(Long_t size, void *p);
   static void delete_KoaGeoHandler(void *p);
   static void deleteArray_KoaGeoHandler(void *p);
   static void destruct_KoaGeoHandler(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaGeoHandler*)
   {
      ::KoaGeoHandler *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaGeoHandler >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaGeoHandler", ::KoaGeoHandler::Class_Version(), "", 59,
                  typeid(::KoaGeoHandler), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaGeoHandler::Dictionary, isa_proxy, 4,
                  sizeof(::KoaGeoHandler) );
      instance.SetNew(&new_KoaGeoHandler);
      instance.SetNewArray(&newArray_KoaGeoHandler);
      instance.SetDelete(&delete_KoaGeoHandler);
      instance.SetDeleteArray(&deleteArray_KoaGeoHandler);
      instance.SetDestructor(&destruct_KoaGeoHandler);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaGeoHandler*)
   {
      return GenerateInitInstanceLocal((::KoaGeoHandler*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaGeoHandler*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaMapHandler(void *p = 0);
   static void *newArray_KoaMapHandler(Long_t size, void *p);
   static void delete_KoaMapHandler(void *p);
   static void deleteArray_KoaMapHandler(void *p);
   static void destruct_KoaMapHandler(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaMapHandler*)
   {
      ::KoaMapHandler *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaMapHandler >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaMapHandler", ::KoaMapHandler::Class_Version(), "", 180,
                  typeid(::KoaMapHandler), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaMapHandler::Dictionary, isa_proxy, 4,
                  sizeof(::KoaMapHandler) );
      instance.SetNew(&new_KoaMapHandler);
      instance.SetNewArray(&newArray_KoaMapHandler);
      instance.SetDelete(&delete_KoaMapHandler);
      instance.SetDeleteArray(&deleteArray_KoaMapHandler);
      instance.SetDestructor(&destruct_KoaMapHandler);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaMapHandler*)
   {
      return GenerateInitInstanceLocal((::KoaMapHandler*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaMapHandler*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_KoaMapEncoder(void *p);
   static void deleteArray_KoaMapEncoder(void *p);
   static void destruct_KoaMapEncoder(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaMapEncoder*)
   {
      ::KoaMapEncoder *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaMapEncoder >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaMapEncoder", ::KoaMapEncoder::Class_Version(), "", 231,
                  typeid(::KoaMapEncoder), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaMapEncoder::Dictionary, isa_proxy, 4,
                  sizeof(::KoaMapEncoder) );
      instance.SetDelete(&delete_KoaMapEncoder);
      instance.SetDeleteArray(&deleteArray_KoaMapEncoder);
      instance.SetDestructor(&destruct_KoaMapEncoder);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaMapEncoder*)
   {
      return GenerateInitInstanceLocal((::KoaMapEncoder*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaMapEncoder*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_KoaElasticCalculator(void *p);
   static void deleteArray_KoaElasticCalculator(void *p);
   static void destruct_KoaElasticCalculator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaElasticCalculator*)
   {
      ::KoaElasticCalculator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaElasticCalculator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaElasticCalculator", ::KoaElasticCalculator::Class_Version(), "", 314,
                  typeid(::KoaElasticCalculator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaElasticCalculator::Dictionary, isa_proxy, 4,
                  sizeof(::KoaElasticCalculator) );
      instance.SetDelete(&delete_KoaElasticCalculator);
      instance.SetDeleteArray(&deleteArray_KoaElasticCalculator);
      instance.SetDestructor(&destruct_KoaElasticCalculator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaElasticCalculator*)
   {
      return GenerateInitInstanceLocal((::KoaElasticCalculator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaElasticCalculator*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSensorNamePar(void *p = 0);
   static void *newArray_PndSensorNamePar(Long_t size, void *p);
   static void delete_PndSensorNamePar(void *p);
   static void deleteArray_PndSensorNamePar(void *p);
   static void destruct_PndSensorNamePar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSensorNamePar*)
   {
      ::PndSensorNamePar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSensorNamePar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSensorNamePar", ::PndSensorNamePar::Class_Version(), "PndSensorNamePar.h", 19,
                  typeid(::PndSensorNamePar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSensorNamePar::Dictionary, isa_proxy, 4,
                  sizeof(::PndSensorNamePar) );
      instance.SetNew(&new_PndSensorNamePar);
      instance.SetNewArray(&newArray_PndSensorNamePar);
      instance.SetDelete(&delete_PndSensorNamePar);
      instance.SetDeleteArray(&deleteArray_PndSensorNamePar);
      instance.SetDestructor(&destruct_PndSensorNamePar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSensorNamePar*)
   {
      return GenerateInitInstanceLocal((::PndSensorNamePar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSensorNamePar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndGeoHandling(void *p = 0);
   static void *newArray_PndGeoHandling(Long_t size, void *p);
   static void delete_PndGeoHandling(void *p);
   static void deleteArray_PndGeoHandling(void *p);
   static void destruct_PndGeoHandling(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndGeoHandling*)
   {
      ::PndGeoHandling *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndGeoHandling >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndGeoHandling", ::PndGeoHandling::Class_Version(), "", 699,
                  typeid(::PndGeoHandling), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndGeoHandling::Dictionary, isa_proxy, 4,
                  sizeof(::PndGeoHandling) );
      instance.SetNew(&new_PndGeoHandling);
      instance.SetNewArray(&newArray_PndGeoHandling);
      instance.SetDelete(&delete_PndGeoHandling);
      instance.SetDeleteArray(&deleteArray_PndGeoHandling);
      instance.SetDestructor(&destruct_PndGeoHandling);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndGeoHandling*)
   {
      return GenerateInitInstanceLocal((::PndGeoHandling*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndGeoHandling*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSensorNameContFact(void *p = 0);
   static void *newArray_PndSensorNameContFact(Long_t size, void *p);
   static void delete_PndSensorNameContFact(void *p);
   static void deleteArray_PndSensorNameContFact(void *p);
   static void destruct_PndSensorNameContFact(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSensorNameContFact*)
   {
      ::PndSensorNameContFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSensorNameContFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSensorNameContFact", ::PndSensorNameContFact::Class_Version(), "", 978,
                  typeid(::PndSensorNameContFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSensorNameContFact::Dictionary, isa_proxy, 4,
                  sizeof(::PndSensorNameContFact) );
      instance.SetNew(&new_PndSensorNameContFact);
      instance.SetNewArray(&newArray_PndSensorNameContFact);
      instance.SetDelete(&delete_PndSensorNameContFact);
      instance.SetDeleteArray(&deleteArray_PndSensorNameContFact);
      instance.SetDestructor(&destruct_PndSensorNameContFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSensorNameContFact*)
   {
      return GenerateInitInstanceLocal((::PndSensorNameContFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSensorNameContFact*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *PndStringSeparator_Dictionary();
   static void PndStringSeparator_TClassManip(TClass*);
   static void *new_PndStringSeparator(void *p = 0);
   static void *newArray_PndStringSeparator(Long_t size, void *p);
   static void delete_PndStringSeparator(void *p);
   static void deleteArray_PndStringSeparator(void *p);
   static void destruct_PndStringSeparator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndStringSeparator*)
   {
      ::PndStringSeparator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::PndStringSeparator));
      static ::ROOT::TGenericClassInfo 
         instance("PndStringSeparator", "", 1026,
                  typeid(::PndStringSeparator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &PndStringSeparator_Dictionary, isa_proxy, 4,
                  sizeof(::PndStringSeparator) );
      instance.SetNew(&new_PndStringSeparator);
      instance.SetNewArray(&newArray_PndStringSeparator);
      instance.SetDelete(&delete_PndStringSeparator);
      instance.SetDeleteArray(&deleteArray_PndStringSeparator);
      instance.SetDestructor(&destruct_PndStringSeparator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndStringSeparator*)
   {
      return GenerateInitInstanceLocal((::PndStringSeparator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndStringSeparator*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *PndStringSeparator_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::PndStringSeparator*)0x0)->GetClass();
      PndStringSeparator_TClassManip(theClass);
   return theClass;
   }

   static void PndStringSeparator_TClassManip(TClass* ){
   }

} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr KoaGeoHandler::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaGeoHandler::Class_Name()
{
   return "KoaGeoHandler";
}

//______________________________________________________________________________
const char *KoaGeoHandler::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaGeoHandler*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaGeoHandler::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaGeoHandler*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaGeoHandler::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaGeoHandler*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaGeoHandler::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaGeoHandler*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaMapHandler::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaMapHandler::Class_Name()
{
   return "KoaMapHandler";
}

//______________________________________________________________________________
const char *KoaMapHandler::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaMapHandler*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaMapHandler::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaMapHandler*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaMapHandler::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaMapHandler*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaMapHandler::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaMapHandler*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaMapEncoder::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaMapEncoder::Class_Name()
{
   return "KoaMapEncoder";
}

//______________________________________________________________________________
const char *KoaMapEncoder::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaMapEncoder*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaMapEncoder::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaMapEncoder*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaMapEncoder::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaMapEncoder*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaMapEncoder::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaMapEncoder*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaElasticCalculator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaElasticCalculator::Class_Name()
{
   return "KoaElasticCalculator";
}

//______________________________________________________________________________
const char *KoaElasticCalculator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaElasticCalculator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaElasticCalculator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaElasticCalculator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaElasticCalculator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaElasticCalculator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaElasticCalculator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaElasticCalculator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSensorNamePar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSensorNamePar::Class_Name()
{
   return "PndSensorNamePar";
}

//______________________________________________________________________________
const char *PndSensorNamePar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSensorNamePar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSensorNamePar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSensorNamePar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSensorNamePar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSensorNamePar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSensorNamePar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSensorNamePar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndGeoHandling::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndGeoHandling::Class_Name()
{
   return "PndGeoHandling";
}

//______________________________________________________________________________
const char *PndGeoHandling::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndGeoHandling*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndGeoHandling::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndGeoHandling*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndGeoHandling::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndGeoHandling*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndGeoHandling::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndGeoHandling*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSensorNameContFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSensorNameContFact::Class_Name()
{
   return "PndSensorNameContFact";
}

//______________________________________________________________________________
const char *PndSensorNameContFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSensorNameContFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSensorNameContFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSensorNameContFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSensorNameContFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSensorNameContFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSensorNameContFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSensorNameContFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void KoaGeoHandler::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaGeoHandler.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaGeoHandler::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaGeoHandler::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaGeoHandler(void *p) {
      return  p ? new(p) ::KoaGeoHandler : new ::KoaGeoHandler;
   }
   static void *newArray_KoaGeoHandler(Long_t nElements, void *p) {
      return p ? new(p) ::KoaGeoHandler[nElements] : new ::KoaGeoHandler[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaGeoHandler(void *p) {
      delete ((::KoaGeoHandler*)p);
   }
   static void deleteArray_KoaGeoHandler(void *p) {
      delete [] ((::KoaGeoHandler*)p);
   }
   static void destruct_KoaGeoHandler(void *p) {
      typedef ::KoaGeoHandler current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaGeoHandler

//______________________________________________________________________________
void KoaMapHandler::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaMapHandler.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaMapHandler::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaMapHandler::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaMapHandler(void *p) {
      return  p ? new(p) ::KoaMapHandler : new ::KoaMapHandler;
   }
   static void *newArray_KoaMapHandler(Long_t nElements, void *p) {
      return p ? new(p) ::KoaMapHandler[nElements] : new ::KoaMapHandler[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaMapHandler(void *p) {
      delete ((::KoaMapHandler*)p);
   }
   static void deleteArray_KoaMapHandler(void *p) {
      delete [] ((::KoaMapHandler*)p);
   }
   static void destruct_KoaMapHandler(void *p) {
      typedef ::KoaMapHandler current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaMapHandler

//______________________________________________________________________________
void KoaMapEncoder::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaMapEncoder.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaMapEncoder::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaMapEncoder::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_KoaMapEncoder(void *p) {
      delete ((::KoaMapEncoder*)p);
   }
   static void deleteArray_KoaMapEncoder(void *p) {
      delete [] ((::KoaMapEncoder*)p);
   }
   static void destruct_KoaMapEncoder(void *p) {
      typedef ::KoaMapEncoder current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaMapEncoder

//______________________________________________________________________________
void KoaElasticCalculator::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaElasticCalculator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaElasticCalculator::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaElasticCalculator::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_KoaElasticCalculator(void *p) {
      delete ((::KoaElasticCalculator*)p);
   }
   static void deleteArray_KoaElasticCalculator(void *p) {
      delete [] ((::KoaElasticCalculator*)p);
   }
   static void destruct_KoaElasticCalculator(void *p) {
      typedef ::KoaElasticCalculator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaElasticCalculator

//______________________________________________________________________________
void PndSensorNamePar::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSensorNamePar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSensorNamePar::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSensorNamePar::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSensorNamePar(void *p) {
      return  p ? new(p) ::PndSensorNamePar : new ::PndSensorNamePar;
   }
   static void *newArray_PndSensorNamePar(Long_t nElements, void *p) {
      return p ? new(p) ::PndSensorNamePar[nElements] : new ::PndSensorNamePar[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSensorNamePar(void *p) {
      delete ((::PndSensorNamePar*)p);
   }
   static void deleteArray_PndSensorNamePar(void *p) {
      delete [] ((::PndSensorNamePar*)p);
   }
   static void destruct_PndSensorNamePar(void *p) {
      typedef ::PndSensorNamePar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSensorNamePar

//______________________________________________________________________________
void PndGeoHandling::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndGeoHandling.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndGeoHandling::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndGeoHandling::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndGeoHandling(void *p) {
      return  p ? new(p) ::PndGeoHandling : new ::PndGeoHandling;
   }
   static void *newArray_PndGeoHandling(Long_t nElements, void *p) {
      return p ? new(p) ::PndGeoHandling[nElements] : new ::PndGeoHandling[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndGeoHandling(void *p) {
      delete ((::PndGeoHandling*)p);
   }
   static void deleteArray_PndGeoHandling(void *p) {
      delete [] ((::PndGeoHandling*)p);
   }
   static void destruct_PndGeoHandling(void *p) {
      typedef ::PndGeoHandling current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndGeoHandling

//______________________________________________________________________________
void PndSensorNameContFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSensorNameContFact.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSensorNameContFact::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSensorNameContFact::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSensorNameContFact(void *p) {
      return  p ? new(p) ::PndSensorNameContFact : new ::PndSensorNameContFact;
   }
   static void *newArray_PndSensorNameContFact(Long_t nElements, void *p) {
      return p ? new(p) ::PndSensorNameContFact[nElements] : new ::PndSensorNameContFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSensorNameContFact(void *p) {
      delete ((::PndSensorNameContFact*)p);
   }
   static void deleteArray_PndSensorNameContFact(void *p) {
      delete [] ((::PndSensorNameContFact*)p);
   }
   static void destruct_PndSensorNameContFact(void *p) {
      typedef ::PndSensorNameContFact current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSensorNameContFact

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndStringSeparator(void *p) {
      return  p ? new(p) ::PndStringSeparator : new ::PndStringSeparator;
   }
   static void *newArray_PndStringSeparator(Long_t nElements, void *p) {
      return p ? new(p) ::PndStringSeparator[nElements] : new ::PndStringSeparator[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndStringSeparator(void *p) {
      delete ((::PndStringSeparator*)p);
   }
   static void deleteArray_PndStringSeparator(void *p) {
      delete [] ((::PndStringSeparator*)p);
   }
   static void destruct_PndStringSeparator(void *p) {
      typedef ::PndStringSeparator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndStringSeparator

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
   static TClass *vectorlETStringgR_Dictionary();
   static void vectorlETStringgR_TClassManip(TClass*);
   static void *new_vectorlETStringgR(void *p = 0);
   static void *newArray_vectorlETStringgR(Long_t size, void *p);
   static void delete_vectorlETStringgR(void *p);
   static void deleteArray_vectorlETStringgR(void *p);
   static void destruct_vectorlETStringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TString>*)
   {
      vector<TString> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TString>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TString>", -2, "vector", 216,
                  typeid(vector<TString>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETStringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TString>) );
      instance.SetNew(&new_vectorlETStringgR);
      instance.SetNewArray(&newArray_vectorlETStringgR);
      instance.SetDelete(&delete_vectorlETStringgR);
      instance.SetDeleteArray(&deleteArray_vectorlETStringgR);
      instance.SetDestructor(&destruct_vectorlETStringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TString> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TString>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETStringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TString>*)0x0)->GetClass();
      vectorlETStringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETStringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETStringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TString> : new vector<TString>;
   }
   static void *newArray_vectorlETStringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TString>[nElements] : new vector<TString>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETStringgR(void *p) {
      delete ((vector<TString>*)p);
   }
   static void deleteArray_vectorlETStringgR(void *p) {
      delete [] ((vector<TString>*)p);
   }
   static void destruct_vectorlETStringgR(void *p) {
      typedef vector<TString> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TString>

namespace ROOT {
   static TClass *maplEintcOvectorlEintgRsPgR_Dictionary();
   static void maplEintcOvectorlEintgRsPgR_TClassManip(TClass*);
   static void *new_maplEintcOvectorlEintgRsPgR(void *p = 0);
   static void *newArray_maplEintcOvectorlEintgRsPgR(Long_t size, void *p);
   static void delete_maplEintcOvectorlEintgRsPgR(void *p);
   static void deleteArray_maplEintcOvectorlEintgRsPgR(void *p);
   static void destruct_maplEintcOvectorlEintgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,vector<int> >*)
   {
      map<int,vector<int> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,vector<int> >));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,vector<int> >", -2, "map", 99,
                  typeid(map<int,vector<int> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOvectorlEintgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,vector<int> >) );
      instance.SetNew(&new_maplEintcOvectorlEintgRsPgR);
      instance.SetNewArray(&newArray_maplEintcOvectorlEintgRsPgR);
      instance.SetDelete(&delete_maplEintcOvectorlEintgRsPgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOvectorlEintgRsPgR);
      instance.SetDestructor(&destruct_maplEintcOvectorlEintgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,vector<int> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,vector<int> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOvectorlEintgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,vector<int> >*)0x0)->GetClass();
      maplEintcOvectorlEintgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOvectorlEintgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOvectorlEintgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,vector<int> > : new map<int,vector<int> >;
   }
   static void *newArray_maplEintcOvectorlEintgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,vector<int> >[nElements] : new map<int,vector<int> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOvectorlEintgRsPgR(void *p) {
      delete ((map<int,vector<int> >*)p);
   }
   static void deleteArray_maplEintcOvectorlEintgRsPgR(void *p) {
      delete [] ((map<int,vector<int> >*)p);
   }
   static void destruct_maplEintcOvectorlEintgRsPgR(void *p) {
      typedef map<int,vector<int> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,vector<int> >

namespace ROOT {
   static TClass *maplEintcOintgR_Dictionary();
   static void maplEintcOintgR_TClassManip(TClass*);
   static void *new_maplEintcOintgR(void *p = 0);
   static void *newArray_maplEintcOintgR(Long_t size, void *p);
   static void delete_maplEintcOintgR(void *p);
   static void deleteArray_maplEintcOintgR(void *p);
   static void destruct_maplEintcOintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,int>*)
   {
      map<int,int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,int>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,int>", -2, "map", 99,
                  typeid(map<int,int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOintgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,int>) );
      instance.SetNew(&new_maplEintcOintgR);
      instance.SetNewArray(&newArray_maplEintcOintgR);
      instance.SetDelete(&delete_maplEintcOintgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOintgR);
      instance.SetDestructor(&destruct_maplEintcOintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,int>*)0x0)->GetClass();
      maplEintcOintgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,int> : new map<int,int>;
   }
   static void *newArray_maplEintcOintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,int>[nElements] : new map<int,int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOintgR(void *p) {
      delete ((map<int,int>*)p);
   }
   static void deleteArray_maplEintcOintgR(void *p) {
      delete [] ((map<int,int>*)p);
   }
   static void destruct_maplEintcOintgR(void *p) {
      typedef map<int,int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,int>

namespace ROOT {
   static TClass *maplEintcOdoublegR_Dictionary();
   static void maplEintcOdoublegR_TClassManip(TClass*);
   static void *new_maplEintcOdoublegR(void *p = 0);
   static void *newArray_maplEintcOdoublegR(Long_t size, void *p);
   static void delete_maplEintcOdoublegR(void *p);
   static void deleteArray_maplEintcOdoublegR(void *p);
   static void destruct_maplEintcOdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,double>*)
   {
      map<int,double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,double>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,double>", -2, "map", 99,
                  typeid(map<int,double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,double>) );
      instance.SetNew(&new_maplEintcOdoublegR);
      instance.SetNewArray(&newArray_maplEintcOdoublegR);
      instance.SetDelete(&delete_maplEintcOdoublegR);
      instance.SetDeleteArray(&deleteArray_maplEintcOdoublegR);
      instance.SetDestructor(&destruct_maplEintcOdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,double>*)0x0)->GetClass();
      maplEintcOdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,double> : new map<int,double>;
   }
   static void *newArray_maplEintcOdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,double>[nElements] : new map<int,double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOdoublegR(void *p) {
      delete ((map<int,double>*)p);
   }
   static void deleteArray_maplEintcOdoublegR(void *p) {
      delete [] ((map<int,double>*)p);
   }
   static void destruct_maplEintcOdoublegR(void *p) {
      typedef map<int,double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,double>

namespace ROOT {
   static TClass *maplEintcOTStringgR_Dictionary();
   static void maplEintcOTStringgR_TClassManip(TClass*);
   static void *new_maplEintcOTStringgR(void *p = 0);
   static void *newArray_maplEintcOTStringgR(Long_t size, void *p);
   static void delete_maplEintcOTStringgR(void *p);
   static void deleteArray_maplEintcOTStringgR(void *p);
   static void destruct_maplEintcOTStringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,TString>*)
   {
      map<int,TString> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,TString>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,TString>", -2, "map", 99,
                  typeid(map<int,TString>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOTStringgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,TString>) );
      instance.SetNew(&new_maplEintcOTStringgR);
      instance.SetNewArray(&newArray_maplEintcOTStringgR);
      instance.SetDelete(&delete_maplEintcOTStringgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOTStringgR);
      instance.SetDestructor(&destruct_maplEintcOTStringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,TString> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,TString>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOTStringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,TString>*)0x0)->GetClass();
      maplEintcOTStringgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOTStringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOTStringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,TString> : new map<int,TString>;
   }
   static void *newArray_maplEintcOTStringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,TString>[nElements] : new map<int,TString>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOTStringgR(void *p) {
      delete ((map<int,TString>*)p);
   }
   static void deleteArray_maplEintcOTStringgR(void *p) {
      delete [] ((map<int,TString>*)p);
   }
   static void destruct_maplEintcOTStringgR(void *p) {
      typedef map<int,TString> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,TString>

namespace ROOT {
   static TClass *maplEintcOTGeoHMatrixmUgR_Dictionary();
   static void maplEintcOTGeoHMatrixmUgR_TClassManip(TClass*);
   static void *new_maplEintcOTGeoHMatrixmUgR(void *p = 0);
   static void *newArray_maplEintcOTGeoHMatrixmUgR(Long_t size, void *p);
   static void delete_maplEintcOTGeoHMatrixmUgR(void *p);
   static void deleteArray_maplEintcOTGeoHMatrixmUgR(void *p);
   static void destruct_maplEintcOTGeoHMatrixmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,TGeoHMatrix*>*)
   {
      map<int,TGeoHMatrix*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,TGeoHMatrix*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,TGeoHMatrix*>", -2, "map", 99,
                  typeid(map<int,TGeoHMatrix*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOTGeoHMatrixmUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,TGeoHMatrix*>) );
      instance.SetNew(&new_maplEintcOTGeoHMatrixmUgR);
      instance.SetNewArray(&newArray_maplEintcOTGeoHMatrixmUgR);
      instance.SetDelete(&delete_maplEintcOTGeoHMatrixmUgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOTGeoHMatrixmUgR);
      instance.SetDestructor(&destruct_maplEintcOTGeoHMatrixmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,TGeoHMatrix*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,TGeoHMatrix*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOTGeoHMatrixmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,TGeoHMatrix*>*)0x0)->GetClass();
      maplEintcOTGeoHMatrixmUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOTGeoHMatrixmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOTGeoHMatrixmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,TGeoHMatrix*> : new map<int,TGeoHMatrix*>;
   }
   static void *newArray_maplEintcOTGeoHMatrixmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,TGeoHMatrix*>[nElements] : new map<int,TGeoHMatrix*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOTGeoHMatrixmUgR(void *p) {
      delete ((map<int,TGeoHMatrix*>*)p);
   }
   static void deleteArray_maplEintcOTGeoHMatrixmUgR(void *p) {
      delete [] ((map<int,TGeoHMatrix*>*)p);
   }
   static void destruct_maplEintcOTGeoHMatrixmUgR(void *p) {
      typedef map<int,TGeoHMatrix*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,TGeoHMatrix*>

namespace ROOT {
   static TClass *maplEintcOKoaGeoHandlercLcLStripRangegR_Dictionary();
   static void maplEintcOKoaGeoHandlercLcLStripRangegR_TClassManip(TClass*);
   static void *new_maplEintcOKoaGeoHandlercLcLStripRangegR(void *p = 0);
   static void *newArray_maplEintcOKoaGeoHandlercLcLStripRangegR(Long_t size, void *p);
   static void delete_maplEintcOKoaGeoHandlercLcLStripRangegR(void *p);
   static void deleteArray_maplEintcOKoaGeoHandlercLcLStripRangegR(void *p);
   static void destruct_maplEintcOKoaGeoHandlercLcLStripRangegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,KoaGeoHandler::StripRange>*)
   {
      map<int,KoaGeoHandler::StripRange> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,KoaGeoHandler::StripRange>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,KoaGeoHandler::StripRange>", -2, "map", 99,
                  typeid(map<int,KoaGeoHandler::StripRange>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOKoaGeoHandlercLcLStripRangegR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,KoaGeoHandler::StripRange>) );
      instance.SetNew(&new_maplEintcOKoaGeoHandlercLcLStripRangegR);
      instance.SetNewArray(&newArray_maplEintcOKoaGeoHandlercLcLStripRangegR);
      instance.SetDelete(&delete_maplEintcOKoaGeoHandlercLcLStripRangegR);
      instance.SetDeleteArray(&deleteArray_maplEintcOKoaGeoHandlercLcLStripRangegR);
      instance.SetDestructor(&destruct_maplEintcOKoaGeoHandlercLcLStripRangegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,KoaGeoHandler::StripRange> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,KoaGeoHandler::StripRange>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOKoaGeoHandlercLcLStripRangegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,KoaGeoHandler::StripRange>*)0x0)->GetClass();
      maplEintcOKoaGeoHandlercLcLStripRangegR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOKoaGeoHandlercLcLStripRangegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOKoaGeoHandlercLcLStripRangegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,KoaGeoHandler::StripRange> : new map<int,KoaGeoHandler::StripRange>;
   }
   static void *newArray_maplEintcOKoaGeoHandlercLcLStripRangegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,KoaGeoHandler::StripRange>[nElements] : new map<int,KoaGeoHandler::StripRange>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOKoaGeoHandlercLcLStripRangegR(void *p) {
      delete ((map<int,KoaGeoHandler::StripRange>*)p);
   }
   static void deleteArray_maplEintcOKoaGeoHandlercLcLStripRangegR(void *p) {
      delete [] ((map<int,KoaGeoHandler::StripRange>*)p);
   }
   static void destruct_maplEintcOKoaGeoHandlercLcLStripRangegR(void *p) {
      typedef map<int,KoaGeoHandler::StripRange> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,KoaGeoHandler::StripRange>

namespace ROOT {
   static TClass *maplETStringcOintgR_Dictionary();
   static void maplETStringcOintgR_TClassManip(TClass*);
   static void *new_maplETStringcOintgR(void *p = 0);
   static void *newArray_maplETStringcOintgR(Long_t size, void *p);
   static void delete_maplETStringcOintgR(void *p);
   static void deleteArray_maplETStringcOintgR(void *p);
   static void destruct_maplETStringcOintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,int>*)
   {
      map<TString,int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,int>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,int>", -2, "map", 99,
                  typeid(map<TString,int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplETStringcOintgR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,int>) );
      instance.SetNew(&new_maplETStringcOintgR);
      instance.SetNewArray(&newArray_maplETStringcOintgR);
      instance.SetDelete(&delete_maplETStringcOintgR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOintgR);
      instance.SetDestructor(&destruct_maplETStringcOintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<TString,int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,int>*)0x0)->GetClass();
      maplETStringcOintgR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,int> : new map<TString,int>;
   }
   static void *newArray_maplETStringcOintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,int>[nElements] : new map<TString,int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOintgR(void *p) {
      delete ((map<TString,int>*)p);
   }
   static void deleteArray_maplETStringcOintgR(void *p) {
      delete [] ((map<TString,int>*)p);
   }
   static void destruct_maplETStringcOintgR(void *p) {
      typedef map<TString,int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,int>

namespace {
  void TriggerDictionaryInitialization_G__KoaToolsDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/home/yong/fairroot/v18_jun19/include",
"/home/yong/src/KoalaSoft/tools",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include/TGeant3",
"/home/yong/fairroot/v18_jun19/include",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/src/KoalaSoft/build_jens/tools/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__KoaToolsDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class KoaGeoHandler;
class KoaMapHandler;
class KoaMapEncoder;
class KoaElasticCalculator;
class __attribute__((annotate("$clingAutoload$PndSensorNamePar.h")))  PndSensorNamePar;
class PndGeoHandling;
class __attribute__((annotate(R"ATTRDUMP(Factory for all SensorName parameter containers)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Factory for all SensorName parameter containers)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Factory for all SensorName parameter containers)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Factory for all SensorName parameter containers)ATTRDUMP"))) PndSensorNameContFact;
class PndStringSeparator;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__KoaToolsDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                 KoaGeoHandler header file                    ------
// -----                 Modified from FairRoot Tutorial4 GeeHandler   -----
// -----                 Created 31/05/19  by Y. Zhou                 -----
// -------------------------------------------------------------------------


/** KoaGeoHandler.h
 ** Helper class to extract information from the GeoManager which is
 ** needed in many other classes.. This helper class should be a
 ** single place to hold all these functions.
 **
 ** Major functions:
 **   1. Keep a list of TGeoHMatrix for coordinate transformation from global to local,
 **      and vice visa.
 **   2. Keep a list of mapping relation between strip id to readout channel id (caveat:
 **      readout channel mapping to electronics channel is save in KoaMapHandler)
 **   3. Keep a list of readout channel id mapping to local position of strip range.
 **   4. Keep a list of normalized detector id, which is the uniquely assigned to each
 **      sensor volume in simulaion and recognized in digitisation (i.e. volID in MCPoint)
 **
 ** This class is designed to be used intensely in simulaion/digitisation/reconstruction/
 ** anaylsis.
 **
 ** @author Y.Zhou <y.zhou@fz-juelich.de>
 **/
/* TODO: 1. MasterToLocal
         2. CMakeList (usage libs like rec, fwd, and mc)
         3. Check Volume ID and Unique ID
         4. Implementation to be done for Fwd detector
 */

#ifndef KOAGEOHANDLER_H
#define KOAGEOHANDLER_H 1

#include "TObject.h"                    // for TObject
#include <map>                          // for map
#include <vector>                          // for map
#include "TGeoMatrix.h"

#include "Rtypes.h"                     // for Int_t, Double_t, Bool_t, etc
#include "TString.h"                    // for TString
#include "TVector3.h"

class KoaMapEncoder;

class KoaGeoHandler : public TObject
{
  public:
    KoaGeoHandler(Bool_t IsSim=kFALSE);
    ~KoaGeoHandler() {
      for(auto& it: fDetMatrix){
        delete it.second;
      }
    };

    // 
    Int_t GetDetIdByName(const char* volName); // used in simulation run
    TString GetDetNameById(Int_t detId);
    TString GetDetPathById(Int_t detId);
    TString GetDetPathByName(const char* volName);

    //
    Double_t GetDetPositionById(Int_t detId); // in cm
    Double_t GetDetPositionByName(const char* volName); // in cm
    void GetDetBoundaryById(Int_t detId, Double_t& lower, Double_t& higher); // in cm
    void GetDetBoundaryByName(const char* volName, Double_t& lower, Double_t& higher); // in cm
    std::vector<TVector3> GetDetBoundaryPointsById(Int_t detId); // in cm
    std::vector<TVector3> GetDetBoundaryPointsByName(const char* volName); // in cm

    //
    void LocalToGlobal(Double_t* local, Double_t* global, Int_t detID);
    void GlobalToLocal(Double_t* global, Double_t* local, Int_t detID);

    // hitPos here is the local coordinate in the sensor volume
    // return value is the encoded ch id
    Int_t RecLocalPositionToDetCh(Double_t* hitPos, Int_t detID);
    // hitPos is the global coordinate
    // return value is the encoded ch id
    Int_t RecGlobalPositionToDetCh(Double_t* hitPos, Int_t detID);
    // return value is the center position of this channel along z-axis
    // here detChId is the encoded readout channel id
    Double_t RecDetChToPosition(Int_t detChId, Double_t& lower, Double_t& higher);
    // return value is the center position of this strip along z-axis
    // here stripId is the encoded strip id
    Double_t RecDetStripToPosition(Int_t stripId, Double_t& lower, Double_t& higher);
  // return the vector of encoded strip ids
  std::vector<Int_t> GetStripIds() { return fStripIds; }
  std::map<Int_t, std::vector<Int_t>> GetChIdToStripIds() { return fChIdToStripIds; }

    typedef struct{
      Double_t center;
      Double_t lower;
      Double_t higher;
    } StripRange;

 private:
    Int_t InitMatrix(); // Init the transformation matrix from gGeoManager, which is not\
                        available immediately in simulation
    Int_t Init(); // Init all the other mappings, which are available both in simulation\
                  and analysis
    void NavigateTo(TString volName); // Navigate to a specific volume\
                                      invoked before coordinate transformation

 private:
    KoaMapEncoder*  fMapEncoder;
    Bool_t fIsSimulation; //! used in simulation task or analysis task

    // data for both recoil and fwd
    TString         fRecPath; // node path for recoil detector
    TString         fFwdPath;
    std::map<Int_t, TString>      fDetPath;
    std::map<Int_t, TGeoHMatrix*> fDetMatrix;

    // data only needed for recoil sensors
    std::map<Int_t, Double_t>     fRecDetPosition; // position of sensor centor in global coordinate
    std::map<Int_t, Double_t>     fRecDetDimension; // half length of sensor size along z-axis
    // mapping from encoded readout channel id to local strip range in sensor volume
    std::map<Int_t, StripRange>   fRecChIdToStripRange;
    // mapping from encoded strip id to encoded readout channel id
    std::map<Int_t, Int_t>        fRecStripIdToChId;
    // mapping from encoded strip id to local strip range in sensor volume
    std::map<Int_t, StripRange>   fRecStripIdToStripRange;
  // collection of strip ids
  std::vector<Int_t> fStripIds;
  std::map<Int_t, std::vector<Int_t>> fChIdToStripIds;

    KoaGeoHandler(const KoaGeoHandler&);
    KoaGeoHandler operator=(const KoaGeoHandler&);

    ClassDef(KoaGeoHandler,1)

};


#endif //KOAGEOHANDLER_H

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                 KoaMapHandler header file                    ------
// -----                 Created 13/06/19  by Y. Zhou                 -----
// -------------------------------------------------------------------------


/** KoaMapHandler.h
 ** Helper class to encode the detector channel id and electronics channel id
 ** It is designed to be used for decoding the raw binary data for DAQ
 ** @author Y.Zhou <y.zhou@fz-juelich.de>
 **/

/** As a first step, the mapping relation is hardcoded into the class member.
 ** In the future, a more flexible configuration should be implemented.
 ** TODO:
 **   1. read a mapping configuration file, better based on EMS config file
 **/
#ifndef KOAMAPHANDLER_H
#define KOAMAPHANDLER_H 1

#include "TObject.h"

class KoaMapHandler : public TObject
{
 public:
  KoaMapHandler();
  ~KoaMapHandler();

 private:

  ClassDef(KoaMapHandler, 1)
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                 KoaMapEncoder header file                    ------
// -----                 Created 14/06/19  by Y. Zhou                 -----
// -------------------------------------------------------------------------


/** KoaMapEncoder.h
 ** Helper class to encode the channel id of different sensors in to a single interger
 ** as follows:
 **    id = (detector_id << 24) + (channel_id)
 **
 ** detector_id for different sensors:
 **    SensorSi1 : 0
 **    SensorSi2 : 1
 **    SensorGe1 : 2
 **    SensorGe2 : 3
 **    SensorSc1 : 4
 **    SensorSc2 : 5
 ** 
 ** channel_id starts from 0 for each sensor.
 **
 ** @author Y.Zhou <y.zhou@fz-juelich.de>
 **/

#ifndef KOAMAPENCODER_H
#define KOAMAPENCODER_H 1

#include "TString.h"
#include "TObject.h"
#include <map>

class KoaMapEncoder : public TObject
{
 public:
  ~KoaMapEncoder();

  Int_t VolNameToDetectorID(const char* volName);
  const char* DetectorIDToVolName(Int_t det);

  Int_t EncodeChannelID(const char* volName, Int_t ch);
  Int_t EncodeChannelID(Int_t det, Int_t ch);

  Int_t DecodeChannelID(Int_t id, Int_t& det); // return the channel id
  Int_t DecodeChannelID(Int_t id, TString& volName);

  void  GetRecDetIDRange(Int_t& low, Int_t& high);
  void  GetFwdDetIDRange(Int_t& low, Int_t& high);
  Int_t GetRecRearID() { return fRecRearID; }

  Int_t GetRecSensorNr() { return fRecNrOfSensors; }
  Int_t GetFwdSensorNr() { return fFwdNrOfSensors; }

  std::vector<Int_t> GetChIDs() { return fChIDs; }
  std::vector<Int_t> GetRecChIDs();
  std::vector<Int_t> GetFwdChIDs();
  std::vector<Int_t> GetRecTdcChIDs();
  std::vector<Int_t> GetRecRearChIDs();

  Int_t GetChNr(Int_t detID) { return fDetectorIDToChNr[detID]; }

  static KoaMapEncoder* Instance()
  {
    if(!fpInstance)
      fpInstance = new KoaMapEncoder();
    return fpInstance;
  }

 private:
  KoaMapEncoder();
  void Init();

  std::map<Int_t, TString> fDetectorIDToVolName;
  std::map<TString, Int_t> fVolNameToDetectorID;
  Int_t fRecNrOfSensors;
  Int_t fRecDetIDRange[2];
  Int_t fRecRearID;
  Int_t fFwdNrOfSensors;
  Int_t fFwdDetIDRange[2];
  std::vector<Int_t>       fChIDs;
  std::map<Int_t, Int_t>   fDetectorIDToChNr;

  static KoaMapEncoder *fpInstance;

  ClassDef(KoaMapEncoder,1)
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                 KoaElasticCalculator header file                    ------
// -----                 Created 13/06/19  by Y. Zhou                 -----
// -------------------------------------------------------------------------


/** KoaElasticCalculator.h
 ** Helper class to calculate kinematic related values, functions of proton-proton
 ** elastic scattering.
 ** The mathematical form of elastic scattering is adopted from Aida's code.
 ** [TODO] The correctness of this form is to be checked again.
 ** @author Y.Zhou <y.zhou@fz-juelich.de>
 **/

#ifndef KOA_ELASTICCALCULATOR_H
#define KOA_ELASTICCALCULATOR_H 1

#include "TObject.h"

class KoaElasticCalculator : public TObject
{
 public:
  /* Only the distance of the sensor surface to IP is provided.
     Using this constructor, the class object is used only as a interface to calculate the elastic
     scattering kinematic parameters, such deposited energy at specific z and momentum.
     It has nothing to do with the sensor topology.
     mom in GeV, distance in cm
  */
  KoaElasticCalculator(Double_t mom, Double_t rec_distance, Double_t fwd_distance);
  KoaElasticCalculator(Double_t mom);
  ~KoaElasticCalculator();

  /* functor interface, which can be used to form TF1 in ROOT.
     It is relative independant and valid under both GeoModel and Non-GeoModel modes.
     x[0] is the z-position, p[0] is incident proton momentum, p[1] is distance to IP
     x[0] in mm, p[0] in GeV, p[1] in cm
   */
  Double_t operator() (Double_t *x, Double_t *p);

  /* Set-ers */
  inline void SetRecDistance(Double_t rec_distance) { fRecDistance = rec_distance; }
  inline void SetFwdDistance(Double_t fwd_distance) { fFwdDistance = fwd_distance; }

  /* Get-ers */
  /* Get deposited energy based on position along beam axis.
     It's valid both in GeoModel and Non-GeoModel modes. zposition in mm, return value in MeV */
  Double_t GetEnergyByRecZ(Double_t zposition);
  /* Get T of recoil proton by alpha. alpha is the angle between recoil proton momentum and axis perpendicular to beam axis. alpha in degree, return value in MeV */
  Double_t GetEnergyByAlpha(Double_t alpha);
  /* Get T of recoil proton by theta. theta is the angle between scattering proton momentum and beam axis. theta in degree, return value in MeV */
  Double_t GetEnergyByTheta(Double_t theta);
  /* Get deposited energy based on position in fwd scintillator surface. xposition in cm, return value in MeV */
  Double_t GetEnergyByFwdX(Double_t xposition);

  /* Get beam scattering angle. alpha in degree, return value in degree */
  Double_t GetThetaByAlpha(Double_t alpha);
  /* Get target recoil angle. theta in degree, return value in degree */
  Double_t GetAlphaByTheta(Double_t theta);
  /* Get rec hit position in z-axis based on scattering theta. theta in degree, return value in mm */
  Double_t GetRecZByTheta(Double_t theta);
  /* Get rec hit position in z-axis based on position in fwd scintillator surface. xposition in cm, return value in mm */
  Double_t GetRecZByFwdX(Double_t xposition);

  /* Get recoil angle based on recoil energy. T in MeV, return value in degree */
  Double_t GetAlphaByEnergy(Double_t T);
  /* Get rec hit position in z-axis based on recoil energy. T in MeV, return value in mm */
  Double_t GetRecZByEnergy(Double_t T);
  /* Get fwd hit position in x-axis based on recoil energy. T in MeV, return value in cm */
  Double_t GetFwdXByEnergy(Double_t T);

 private:
  Double_t fMom; // momentum of incident proton, in GeV
  Double_t fRecDistance; // distance of recoil sensor surface to IP, in cm
  Double_t fFwdDistance; // distance of fwd sensor surface to IP, in cm

  static Double_t fProtonMass;
  Double_t fKappa;

  ClassDef(KoaElasticCalculator, 1)
};

#endif
#ifndef KOA_TEXTUTILITY_H
#define KOA_TEXTUTILITY_H

#include "TSystem.h"
#include "KoaMapEncoder.h"
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

/*
 * Text I/O utility for fitting parameters of recoil detector
 * ValueContainer is the basic unit for storing a list of parameters, with the encoded id as key
 *
 * Usage (fitting paramters as an example)
 * // 1. define a ParameterList 
 * using namespace KoaUtility;
 * ParameterList fitParameters;
 * // 2. add parameter value container to this list
 * auto& fitMean = addValueContainer(fitParameters, "Mean");
 * auto& fitSigma = addValueContainer(fitParameters, "Sigma");
 * // 3. fill in the values
 * ....
 * // 4. print out values to text file
 * printValueList(fitParameters, "fit_result.txt");
 * // 5. Read paramter values from text file
 * readParameterList("file.txt")
 * // 6. Binary operation between two set of parameters
 * calcValueContainer<T,operator>(left,right,result)
 */

namespace KoaUtility {

  using IndexContainer = std::vector<Int_t>;

  template<typename T>
  using ValueContainer = std::map<Int_t, T>; // one parameter, the key is chId in Recoil Detector

  template<typename T>
  using Parameter = std::pair<std::string, ValueContainer<T>>; // string is the name of this parameter

  template<typename T>
  using ParameterList = std::list<Parameter<T>>; // a group of parameters which are related will be print out together

  //
  template<typename T>
  typename ParameterList<T>::iterator findValueContainer(ParameterList<T>& paramList, std::string paramName)
  {
    typename ParameterList<T>::iterator it;
    for ( it = paramList.begin() ; it != paramList.end(); it++ ) {
      if (it->first == paramName ) {
        break;
      }
    }

    return it;
  }

  // print one parameter to screen
  template<typename T>
  void printValueContainer(const ValueContainer<T>& valueContainer, std::string paramName)
  {
    std::cout << paramName << ":" << std::endl;
    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    for( const auto& value : valueContainer ) {
      TString volName;
      Int_t ChID = value.first;
      Int_t ch = encoder->DecodeChannelID(ChID, volName);
      volName.ReplaceAll("Sensor", "");
      volName.Append(Form("_%d\t", ch+1));
      std::cout << volName.Data() << value.second << std::endl;
    }
  }

  template<typename T>
  void printValueContainer(ParameterList<T>& paramList, std::string paramName)
  {
    const auto it = findValueContainer<T>(paramList, paramName);
    if (it != paramList.end()) {
      const auto& valueContainer = it->second;

      printValueContainer(valueContainer, paramName);
    }
    else {
      std::cout << "No parameter ValueContainer " << paramName << "exists!" << std::endl;
    }
  }

  template<typename T>
  void printParameter(Parameter<T>& parameter)
  {
    printValueContainer(parameter.second, parameter.first);
  }

  // user should define a ParameterList by himself and then add new ValueContainer into it
  // the return value is a reference to the newly added ValueContainer
  template<typename T>
  ValueContainer<T>& addValueContainer( ParameterList<T>& paramList, // the list where the newly defined ValueContainer is stored
                                        std::string paramName) // the name is the key to the newly booked ValueContainer
  {
    auto inserted = findValueContainer<T>(paramList, paramName);
    if (inserted != paramList.end()) {
      std::cout << "Warning : ValueContainer with name " << paramName << " already exists!" << std::endl;
      return inserted->second;
    }
    else {
      ValueContainer<T> new_container;
      paramList.emplace_back(std::make_pair(paramName, std::move(new_container)));

      auto& back = paramList.back();
      return back.second;
    }
  }

  //
  template<typename T>
  void resetValueContainer(ValueContainer<T>& valueContainer, T resetValue = 0)
  {
    for ( auto& value : valueContainer ) {
      value.second = resetValue;
    }
  }

  //
  template<typename T, template<typename> class BinaryOperator = std::divides>
  void calcValueContainer(ValueContainer<T>& lhsContainer, ValueContainer<T>& rhsContainer, ValueContainer<T>& resultContainer)
  {
    BinaryOperator<T> binaryOperator;

    for ( auto& lhsValue : lhsContainer ) {
      auto chId = lhsValue.first;
      auto& lhs = lhsValue.second;
      auto& rhs = rhsContainer[chId];
      auto& result = resultContainer[chId];
      result = binaryOperator(lhs, rhs);
    }
  }

  // print out a ParameterList, i.e. a group of parameters which are related, for example the fitting parameters such as mean and sigma
  template<typename T>
  void printValueList(const ParameterList<T>& paramList,
                      std::string fileName) // name of the output text file
  {
    //
    auto itFirst = paramList.begin();
    if( itFirst == paramList.end() ) {
      std::cout << "No parameters contained in the paramList" << std::endl;
      return;
    }

    //
    std::ofstream ftxt(gSystem->ExpandPathName(fileName.c_str()));
    if(!ftxt.is_open()){
      std::cout << "Can't open file : " << fileName << '\n';
      return;
    }

    // header row
    ftxt << std::setw(12) << std::left << "Name" ;
    ftxt << std::setw(12) << std::left << "Id";
    for( auto& parameter : paramList ) {
      ftxt << std::setw(12) << std::left << parameter.first;
    }
    ftxt << std::endl;

    // loop through all channels
    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    for( const auto& channel : itFirst->second ) {
      TString volName;
      Int_t ChID = channel.first;
      Int_t ch = encoder->DecodeChannelID(ChID, volName);
      volName.ReplaceAll("Sensor", "");
      volName.Append(Form("_%d", ch+1));
      ftxt << std::setw(12) << std::left << volName.Data();
      ftxt << std::setw(12) << std::left << ChID;
      //
      for( const auto& parameter : paramList ) {
        const auto& values = parameter.second;
        ftxt << std::setw(12) << std::left << values.at(ChID);
      }
      ftxt << std::endl;
    }

    //
    ftxt.close();
  }

  //
  template<typename T>
  void printValueList(const ParameterList<T>& paramList)
  {
    //
    auto itFirst = paramList.begin();
    if( itFirst == paramList.end() ) {
      std::cout << "No parameters contained in the paramList" << std::endl;
      return;
    }

    // header row
    std::cout << std::setw(12) << std::left << "Name";
    std::cout << std::setw(12) << std::left << "Id";
    for( auto& parameter : paramList ) {
      std::cout << std::setw(12) << std::left << parameter.first;
    }
    std::cout << "\n";

    // loop through all channels
    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    for( const auto& channel : itFirst->second ) {
      TString volName;
      Int_t ChID = channel.first;
      Int_t ch = encoder->DecodeChannelID(ChID, volName);
      volName.ReplaceAll("Sensor", "");
      volName.Append(Form("_%d", ch+1));
      std::cout << std::setw(12) << std::left << volName.Data();
      std::cout << std::setw(12) << std::left << ChID;
      //
      for( const auto& parameter : paramList ) {
        const auto& values = parameter.second;
        std::cout << std::setw(12) << std::left << values.at(ChID);
      }
      std::cout << "\n";
    }
  }

  //
  template<typename T>
  ParameterList<T> readParameterList(std::string fileName)
  {
    ParameterList<T> paramList;

    std::ifstream ftxt;
    ftxt.open(gSystem->ExpandPathName(fileName.c_str()));
    if (!ftxt.is_open()) {
      std::cout << "Can't open file : " << fileName << '\n';
    }

    std::vector<std::string> containers;
    std::string line, token;
    std::stringstream ssline;

    // get and analyze the header line
    std::getline(ftxt, line);
    ssline.str(line);
    ssline >> token >> token;
    while (ssline >> token) {
      addValueContainer(paramList, token);
      containers.emplace_back(token);
    }

    std::string name;
    Int_t id;
    T value;
    Int_t index;
    while (!ftxt.eof()) {
      std::getline(ftxt, line);
      std::stringstream ss(line);

      index = 0;
      ss >> name >> id;
      while (ss >> value) {
        auto it = findValueContainer(paramList, containers[index++]);
        auto& container = it->second;
        container[id] = value;
      }
    }

    ftxt.close();

    return paramList;
  }
};

#endif
/**
 * PndGeoHandling.h
 * @author: t.stockmanns <t.stockmans@fz-juelich.de>
 *
 * @brief Class to access the naming information of the MVD
 *
 * To save memory not any longer the full path of a volume is stored
 * in each hit but an encrypted form of it (f.e. /1_1/34_2/101_1/).
 * The first number is the volumeID coming from the GeoManager and
 * the second number is the copy number.
 * This class helps you converting the encrypted ID into the path
 * information and vice versa.
 * It needs the informations of the GeoManager. Therefore one has to
 * ensure that either an initialized TGeoManager pointer is given in the
 * constructor with the correct geometry or a filename with the correct geometry ("FAIRGeom")
 *
 * 30.03.2010: To reduce the data size a shortId is introduced.
 * The shortId is generated with the command CreateUniqueSensorId and the match between the path
 * in the GeoManager and the shortId is stored in the ParameterDatabase.
 * To use the shortID the constructor of the PndGeoHandling has to be called in the method
 * SetParContainers of a Task!
 *
 */

#ifndef PNDGEOHANDLING_H
#define PNDGEOHANDLING_H

#include "PndSensorNamePar.h"

#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairTask.h"

#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "TString.h"
#include "TVector3.h"
#include "TMatrixD.h"

#include <string>
#include <iostream>
#include <vector>

class PndGeoHandling : public FairTask {
public:
  
	/// PndGeoHandling::Instance() has to be called the first time in the constructor of a task
	/// otherwise the Sensor names are not available from the database
  PndGeoHandling(); ///< default constructor. Has to be called in SetParContainers if the support of shortId is needed.
	static PndGeoHandling* Instance();
  
	static void Destroy(){
		if (fInstance){
			delete fInstance;
			fInstance = 0;
		}
	}
  
  //PndGeoHandling(TGeoManager* aGeoMan);
  PndGeoHandling(TString mcFile, TString parFile);
  PndGeoHandling(Int_t runID, TString parFile);
  PndGeoHandling(PndSensorNamePar* SensorNamePar);
  
  virtual ~PndGeoHandling(){};
  
  virtual void SetParContainers();
  
  //  static PndGeoHandling* Instance();
  
  //  TString GetCurrentID(); ///< returns the ID of the current node
  //  TString GetID(TString path); ///< for a given TGeoManager-path the ID is returned
  //  TString GetPath(TString id); ///< for a given ID the path is returned
  
  TString GetPath(Int_t shortID); ///< for a given shortID the path is returned
  Int_t	  GetShortID(TString path); ///< for a given path the (unique) position of the sensor path in the fSensorNamePar-List is given. If it is not found -1 is returned.
  
  TString GetVolumeID(TString name); ///< returns the volume ID for a given volume name
  std::vector<TString> GetNamesLevel(Int_t level, TString startPath = ""); //, bool fullPath = false); //[R.K.03/2017] unused variable
  void GetOUVPath(TString path, TVector3& o, TVector3& u, TVector3& v); ///< for a volume given by its path the o, u, v vectors for the plane are returned
  //  void GetOUVId(TString id, TVector3& o, TVector3& u, TVector3& v); ///< for a volume given by its ID the o, u, v vectors for the plane are returned
  void GetOUVShortId(Int_t shortId, TVector3& o, TVector3& u, TVector3& v){
    if (fSensorNamePar != 0)
      GetOUVPath(GetPath(shortId), o, u, v);
  }
  
  TGeoHMatrix* GetMatrixPath(TString path);
  //  TGeoHMatrix* GetMatrixId(TString id);
  TGeoHMatrix* GetMatrixShortId(Int_t shortId){
	  return GetMatrixPath(GetPath(shortId));
	}
  
  //  TVector3 GetSensorDimensionsId(TString id);
  TVector3 GetSensorDimensionsPath(TString path);
  TVector3 GetSensorDimensionsShortId(Int_t shortId){
    return GetSensorDimensionsPath(GetPath(shortId));
  }
  
  //  TVector3 MasterToLocalId(const TVector3& master, const TString& id);
  TVector3 MasterToLocalPath(const TVector3& master, const TString& id);
  TVector3 MasterToLocalShortId(const TVector3& master, const Int_t& shortId){
 	  return MasterToLocalPath(master, GetPath(shortId));
  }
  
  //  TVector3 LocalToMasterId(const TVector3& local, const TString& id);
  TVector3 LocalToMasterPath(const TVector3& local, const TString& id);
  TVector3 LocalToMasterShortId(const TVector3& local, const Int_t& shortId){
 	  return LocalToMasterPath(local, GetPath(shortId));
  }
  
  // TODO: Recheck the error calculation for 3-vectors
  //  TMatrixD MasterToLocalErrorsId(const TMatrixD& master, const TString& id);
  TMatrixD MasterToLocalErrorsPath(const TMatrixD& master, const TString& id);
  TMatrixD MasterToLocalErrorsShortId(const TMatrixD& master, const Int_t& shortId){
 	  return MasterToLocalErrorsPath(master, GetPath(shortId));
  }
  
  //  TMatrixD LocalToMasterErrorsId(const TMatrixD& local, const TString& id);
  TMatrixD LocalToMasterErrorsPath(const TMatrixD& local, const TString& id);
  TMatrixD LocalToMasterErrorsShortId(const TMatrixD& local, const Int_t& shortId){
    return LocalToMasterErrorsPath(local, GetPath(shortId));
  }
  
  TMatrixD GetCurrentRotationMatrix();
  
  void SetVerbose(Int_t v) { fVerbose = v; }
  void SetGeoManager(TGeoManager* geo){fGeoMan = geo;};
  void SetSensorNamePar(PndSensorNamePar* par){fSensorNamePar = par;}
  
  //Bool_t cd(TString id); ///< as the cd command of TGeoManager just with the ID
  Bool_t cd(Int_t id); ///< as the cd command of TGeoManager just with the ID
  void FillLevelNames(); ///< fills vector<TString> fLevelNames with the names (or the paths) of the volumes down to the level given by fLevel
  
  TString FindNodePath(TGeoNode* node);
  void DiveDownToNode(TGeoNode* node);
  void cd(TGeoNode* node); ///<as cd command with the a node, not performant
  
  void DiveDownToNodeContainingString(TString name); ///< runs through the GeoManager until a path is found with a substring which matches to the given string
  
  void CreateUniqueSensorId(TString startName, std::vector<std::string> listOfSensitives); ///< Has to be called during simulation to create unique sensor id
  bool VolumeIsSensitive(TString& path, std::vector<std::string>& listOfSensitives); ///< Checks if the path contains a substring which matches one of the given strings in listOfSensitives. If not false is returned.
  
  void PrintSensorNames(){
	  if (fSensorNamePar)
		  fSensorNamePar->Print();
  }
  
  TObjArray* GetSensorNames(){
	  if (fSensorNamePar != 0)
		  return fSensorNamePar->GetSensorNames();
	  else
		  return 0;
  }
  
  Int_t GetRunId(TString mcFile);
  void GetGeoManager();
  void GetSensorNamePar();
  void FillSensorMap(){
	  fSensorNamePar->FillMap();
  }
  void InitRuntimeDb(TString parFileName);

  PndGeoHandling& operator= (const  PndGeoHandling&) {return *this;}

protected:
  InitStatus Init(){
	  fSensorNamePar->FillMap();
	  return kSUCCESS;
  }

  virtual InitStatus ReInit() {fGeoMan =0;fGeoMan=gGeoManager;return kSUCCESS;}
 
 private:
  static PndGeoHandling* fInstance;
  PndGeoHandling(PndGeoHandling& gh):
    FairTask(),
    fGeoMan(gh.fGeoMan),
    fSensorNamePar(gh.fSensorNamePar),
    fRtdb(gh.fRtdb),
    fLevelNames(gh.fLevelNames),
    fLevel(gh.fLevel),
    fFullPath(gh.fFullPath),
    fRunId(gh.fRunId),
    fVerbose(gh.fVerbose)
  {}
  
  void DiveDownToFillSensNamePar(std::vector<std::string> listOfSensitives);
  
  TGeoManager* fGeoMan;
  PndSensorNamePar* fSensorNamePar;
  FairRuntimeDb* fRtdb;
  // static PndGeoHandling* fGeoHandlingInstance;
  
  std::vector<TString> fLevelNames;
  Int_t fLevel;
  bool fFullPath;
  Int_t fRunId;
  Int_t fVerbose;
  ClassDef(PndGeoHandling,3);
};

#endif
//
// C++ Interface: PndSensorNamePar
//
#ifndef PNDSENSORNAMEPAR_H
#define PNDSENSORNAMEPAR_H


#include "FairParGenericSet.h"
#include "FairParamList.h"
#include "FairRun.h"

#include "TObjArray.h"
#include "TObjString.h"

#include <iostream>
#include <map>

//! Unique match between SensorID and path in TGeoManager
class PndSensorNamePar : public FairParGenericSet
{
  public :
    PndSensorNamePar (const char* name="PndSensorNamePar",
          const char* title="Match between GeoManager path and SensorId",
          const char* context="TestDefaultContext");
    ~PndSensorNamePar(void){
    	if(fSensorNames) delete fSensorNames;
    };
    void clear(void){};
    void putParams(FairParamList* list);
    Bool_t getParams(FairParamList* list);

    virtual void print(){Print();}
    void Print();

    Int_t AddSensorName(TObjString* name);

    Int_t SensorInList(TObjString* name){
//    	for (int i = 0; i < fSensorNames->GetEntries();i++){
//    		TObjString* SensName = (TObjString*)fSensorNames->At(i);
//    		if (SensName->GetString() == name->GetString())
//    			return i;
//    	}
//    	return -1;
    	std::map<TString, Int_t>::iterator iter;
    	iter = fMapOfSensorNames.find(name->GetString());
    	if (iter != fMapOfSensorNames.end())
    		return iter->second;
    	else
    		return -1;
    }

    void FillMap(){
    	for (int i = 0; i < fSensorNames->GetEntries();i++){
			TObjString* SensName = (TObjString*)fSensorNames->At(i);
			fMapOfSensorNames[SensName->GetString()] = i;
			fMapOfSensorIndizes[i] = SensName->GetString();
		}
    }

    TString GetSensorName(Int_t index){
//    	if (index < fSensorNames->GetEntries()){
//			TObjString* myString = (TObjString*)fSensorNames->At(index);
//			return myString->GetString();
//    	}
//    	else{
//    		std::cout << "-E- PndSensorNamePar::GetSensorName index " << index
//    				  << " out of bounds: " << fSensorNames->GetEntries() << std::endl;
//    		return "";
//    	}
    	std::map<Int_t, TString>::const_iterator iter;
    	iter = fMapOfSensorIndizes.find(index);
    	if (iter != fMapOfSensorIndizes.end()) {
    		return iter->second;
    	} else {
    		std::cout << "-E- PndSensorNamePar::GetSensorName index " << index << " not in list!";
    		return "";
    	}

    }

    TObjArray* GetSensorNames() const{return fSensorNames;}

    PndSensorNamePar(const  PndSensorNamePar& L);
    PndSensorNamePar& operator= (const  PndSensorNamePar& L);

    friend std::ostream &operator<<( std::ostream &output, const PndSensorNamePar &par){
    	 output << "SensorNames:" << std::endl;
    	 output << "Entries: " << par.fSensorNames->GetEntries() << std::endl;

		for (std::map<Int_t, TString>::const_iterator iter = par.fMapOfSensorIndizes.begin(); iter != par.fMapOfSensorIndizes.end(); iter++){
			output << iter->first << ": " << iter->second.Data() << std::endl;
		}
		return output;
    }



  private:
    TObjArray* fSensorNames;
    std::map<TString, Int_t> fMapOfSensorNames; //!
    std::map<Int_t, TString> fMapOfSensorIndizes; //!



  ClassDef(PndSensorNamePar,1);
};

#endif /*!MVDSTRIPDIGIPAR_H*/
#ifndef PNDSENSORNAMECONTFACT_H
#define PNDSENSORNAMECONTFACT_H

#include "FairContFact.h"

#include <vector>
#include <string>

class FairContainer;
//class FairParIo;

class PndSensorNameContFact : public FairContFact {
public:
  PndSensorNameContFact();
  ~PndSensorNameContFact();
  FairParSet* createContainer(FairContainer* c);
  TList* GetSensorParNames() {return fSensorParNames;};
private:
  void setAllContainers();
  TList* fSensorParNames; //!
  std::vector<std::string> fContainerNames;

  PndSensorNameContFact(const  PndSensorNameContFact& L);
  PndSensorNameContFact& operator= (const  PndSensorNameContFact&) {return *this;}

  ClassDef( PndSensorNameContFact,1); // Factory for all SensorName parameter containers
};

#endif  /* !MVDCONTFACT_H */
/// -----------------------------------------------------------------
///
///          PndStringSeparator
///
///          Version 1.0
///            by
///          Tobias Stockmanns
///  Seperates an input string into substrings and stores them in a
///  string vector. The seperation criteria is a string of characters.
///  If no delimiters are given the default delimiter " " is used.
///
///  Example:
///    std::vector<std::string> fOutput
///    TPndStringVector fInput("Column:Row Type: Test ", ": ");
///    fOutput = fInput.GetStringVector();
///
///    fOutput[0] = "Column"
///    fOutput[1] = "Row"
///    fOutput[2] = "Type"
///    fOutput[3] = "Test"
///
#ifndef PNDSTRINGSEPARATOR_H
#define PNDSTRINGSEPARATOR_H

#include <string>
#include <vector>
#include "Rtypes.h"


class PndStringSeparator
{
  public :
       PndStringSeparator():fStartPos(0), fStrings(), fInput(), fDelimiter(), fOutput(), fFirstDel(false),fLastDel(false){};
       ~PndStringSeparator(){};
       PndStringSeparator(std::string AInput, std::string ADelimiter = " ");
       void SetInput (std::string AInput)       {fInput = AInput;};
       void SetDelimiter (std::string ADelimiter) {fDelimiter = ADelimiter;};
       void ResetVector(){fStrings.clear();};
       std::vector<std::string> GetStringVector (void);
       void TestFirst(){if(fInput.find_first_of(fDelimiter)==0) fFirstDel=true; else fFirstDel=false;}
       void TestLast(){if(fInput.find_last_of(fDelimiter)==fInput.size()-1) fLastDel = true; else fLastDel = false;}
       bool GetIfFirst(){return fFirstDel;}
       bool GetIfLast(){return fLastDel;}
       std::string Replace(std::string from, std::string to);
       void Print();

  private :
       std::string::size_type fStartPos;
       std::vector<std::string> fStrings;
       std::string fInput;
       std::string fDelimiter;
       std::string fOutput;
       std::string GetString (void);
       bool fFirstDel;	//first element in the string was a delimiter
       bool fLastDel;	//last element in the string was a delimiter
};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"KoaElasticCalculator", payloadCode, "@",
"KoaGeoHandler", payloadCode, "@",
"KoaMapEncoder", payloadCode, "@",
"KoaMapHandler", payloadCode, "@",
"PndGeoHandling", payloadCode, "@",
"PndSensorNameContFact", payloadCode, "@",
"PndSensorNamePar", payloadCode, "@",
"PndStringSeparator", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__KoaToolsDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__KoaToolsDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__KoaToolsDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__KoaToolsDict() {
  TriggerDictionaryInitialization_G__KoaToolsDict_Impl();
}
