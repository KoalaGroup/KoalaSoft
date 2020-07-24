// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_digidIgeneratorsdIG__KoaGeneratorDict

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
#include "KoaPythia8Generator.h"
#include "KoaPpelasticGenerator.h"
#include "FairFilteredPrimaryGenerator.h"
#include "FairEvtFilter.h"
#include "FairEvtFilterParams.h"
#include "KoaEvtFilterOnGeometry.h"
#include "KoaPPElasticIdealGenerator.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_KoaPythia8Generator(void *p = 0);
   static void *newArray_KoaPythia8Generator(Long_t size, void *p);
   static void delete_KoaPythia8Generator(void *p);
   static void deleteArray_KoaPythia8Generator(void *p);
   static void destruct_KoaPythia8Generator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaPythia8Generator*)
   {
      ::KoaPythia8Generator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaPythia8Generator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaPythia8Generator", ::KoaPythia8Generator::Class_Version(), "", 56,
                  typeid(::KoaPythia8Generator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaPythia8Generator::Dictionary, isa_proxy, 4,
                  sizeof(::KoaPythia8Generator) );
      instance.SetNew(&new_KoaPythia8Generator);
      instance.SetNewArray(&newArray_KoaPythia8Generator);
      instance.SetDelete(&delete_KoaPythia8Generator);
      instance.SetDeleteArray(&deleteArray_KoaPythia8Generator);
      instance.SetDestructor(&destruct_KoaPythia8Generator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaPythia8Generator*)
   {
      return GenerateInitInstanceLocal((::KoaPythia8Generator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaPythia8Generator*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaPpelasticGeneratorImp(void *p = 0);
   static void *newArray_KoaPpelasticGeneratorImp(Long_t size, void *p);
   static void delete_KoaPpelasticGeneratorImp(void *p);
   static void deleteArray_KoaPpelasticGeneratorImp(void *p);
   static void destruct_KoaPpelasticGeneratorImp(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaPpelasticGeneratorImp*)
   {
      ::KoaPpelasticGeneratorImp *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaPpelasticGeneratorImp >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaPpelasticGeneratorImp", ::KoaPpelasticGeneratorImp::Class_Version(), "", 134,
                  typeid(::KoaPpelasticGeneratorImp), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaPpelasticGeneratorImp::Dictionary, isa_proxy, 4,
                  sizeof(::KoaPpelasticGeneratorImp) );
      instance.SetNew(&new_KoaPpelasticGeneratorImp);
      instance.SetNewArray(&newArray_KoaPpelasticGeneratorImp);
      instance.SetDelete(&delete_KoaPpelasticGeneratorImp);
      instance.SetDeleteArray(&deleteArray_KoaPpelasticGeneratorImp);
      instance.SetDestructor(&destruct_KoaPpelasticGeneratorImp);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaPpelasticGeneratorImp*)
   {
      return GenerateInitInstanceLocal((::KoaPpelasticGeneratorImp*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaPpelasticGeneratorImp*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaPpelasticGenerator(void *p = 0);
   static void *newArray_KoaPpelasticGenerator(Long_t size, void *p);
   static void delete_KoaPpelasticGenerator(void *p);
   static void deleteArray_KoaPpelasticGenerator(void *p);
   static void destruct_KoaPpelasticGenerator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaPpelasticGenerator*)
   {
      ::KoaPpelasticGenerator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaPpelasticGenerator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaPpelasticGenerator", ::KoaPpelasticGenerator::Class_Version(), "", 206,
                  typeid(::KoaPpelasticGenerator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaPpelasticGenerator::Dictionary, isa_proxy, 4,
                  sizeof(::KoaPpelasticGenerator) );
      instance.SetNew(&new_KoaPpelasticGenerator);
      instance.SetNewArray(&newArray_KoaPpelasticGenerator);
      instance.SetDelete(&delete_KoaPpelasticGenerator);
      instance.SetDeleteArray(&deleteArray_KoaPpelasticGenerator);
      instance.SetDestructor(&destruct_KoaPpelasticGenerator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaPpelasticGenerator*)
   {
      return GenerateInitInstanceLocal((::KoaPpelasticGenerator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaPpelasticGenerator*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairEvtFilter(void *p);
   static void deleteArray_FairEvtFilter(void *p);
   static void destruct_FairEvtFilter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairEvtFilter*)
   {
      ::FairEvtFilter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairEvtFilter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairEvtFilter", ::FairEvtFilter::Class_Version(), "FairEvtFilter.h", 37,
                  typeid(::FairEvtFilter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairEvtFilter::Dictionary, isa_proxy, 4,
                  sizeof(::FairEvtFilter) );
      instance.SetDelete(&delete_FairEvtFilter);
      instance.SetDeleteArray(&deleteArray_FairEvtFilter);
      instance.SetDestructor(&destruct_FairEvtFilter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairEvtFilter*)
   {
      return GenerateInitInstanceLocal((::FairEvtFilter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FairEvtFilter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairEvtFilterParams(void *p = 0);
   static void *newArray_FairEvtFilterParams(Long_t size, void *p);
   static void delete_FairEvtFilterParams(void *p);
   static void deleteArray_FairEvtFilterParams(void *p);
   static void destruct_FairEvtFilterParams(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairEvtFilterParams*)
   {
      ::FairEvtFilterParams *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairEvtFilterParams >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairEvtFilterParams", ::FairEvtFilterParams::Class_Version(), "FairEvtFilterParams.h", 28,
                  typeid(::FairEvtFilterParams), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairEvtFilterParams::Dictionary, isa_proxy, 4,
                  sizeof(::FairEvtFilterParams) );
      instance.SetNew(&new_FairEvtFilterParams);
      instance.SetNewArray(&newArray_FairEvtFilterParams);
      instance.SetDelete(&delete_FairEvtFilterParams);
      instance.SetDeleteArray(&deleteArray_FairEvtFilterParams);
      instance.SetDestructor(&destruct_FairEvtFilterParams);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairEvtFilterParams*)
   {
      return GenerateInitInstanceLocal((::FairEvtFilterParams*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FairEvtFilterParams*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairFilteredPrimaryGenerator(void *p = 0);
   static void *newArray_FairFilteredPrimaryGenerator(Long_t size, void *p);
   static void delete_FairFilteredPrimaryGenerator(void *p);
   static void deleteArray_FairFilteredPrimaryGenerator(void *p);
   static void destruct_FairFilteredPrimaryGenerator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairFilteredPrimaryGenerator*)
   {
      ::FairFilteredPrimaryGenerator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairFilteredPrimaryGenerator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairFilteredPrimaryGenerator", ::FairFilteredPrimaryGenerator::Class_Version(), "", 310,
                  typeid(::FairFilteredPrimaryGenerator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairFilteredPrimaryGenerator::Dictionary, isa_proxy, 4,
                  sizeof(::FairFilteredPrimaryGenerator) );
      instance.SetNew(&new_FairFilteredPrimaryGenerator);
      instance.SetNewArray(&newArray_FairFilteredPrimaryGenerator);
      instance.SetDelete(&delete_FairFilteredPrimaryGenerator);
      instance.SetDeleteArray(&deleteArray_FairFilteredPrimaryGenerator);
      instance.SetDestructor(&destruct_FairFilteredPrimaryGenerator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairFilteredPrimaryGenerator*)
   {
      return GenerateInitInstanceLocal((::FairFilteredPrimaryGenerator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FairFilteredPrimaryGenerator*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaEvtFilterOnGeometry(void *p = 0);
   static void *newArray_KoaEvtFilterOnGeometry(Long_t size, void *p);
   static void delete_KoaEvtFilterOnGeometry(void *p);
   static void deleteArray_KoaEvtFilterOnGeometry(void *p);
   static void destruct_KoaEvtFilterOnGeometry(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaEvtFilterOnGeometry*)
   {
      ::KoaEvtFilterOnGeometry *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaEvtFilterOnGeometry >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaEvtFilterOnGeometry", ::KoaEvtFilterOnGeometry::Class_Version(), "", 738,
                  typeid(::KoaEvtFilterOnGeometry), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaEvtFilterOnGeometry::Dictionary, isa_proxy, 4,
                  sizeof(::KoaEvtFilterOnGeometry) );
      instance.SetNew(&new_KoaEvtFilterOnGeometry);
      instance.SetNewArray(&newArray_KoaEvtFilterOnGeometry);
      instance.SetDelete(&delete_KoaEvtFilterOnGeometry);
      instance.SetDeleteArray(&deleteArray_KoaEvtFilterOnGeometry);
      instance.SetDestructor(&destruct_KoaEvtFilterOnGeometry);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaEvtFilterOnGeometry*)
   {
      return GenerateInitInstanceLocal((::KoaEvtFilterOnGeometry*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaEvtFilterOnGeometry*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaPPElasticIdealGenerator(void *p = 0);
   static void *newArray_KoaPPElasticIdealGenerator(Long_t size, void *p);
   static void delete_KoaPPElasticIdealGenerator(void *p);
   static void deleteArray_KoaPPElasticIdealGenerator(void *p);
   static void destruct_KoaPPElasticIdealGenerator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaPPElasticIdealGenerator*)
   {
      ::KoaPPElasticIdealGenerator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaPPElasticIdealGenerator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaPPElasticIdealGenerator", ::KoaPPElasticIdealGenerator::Class_Version(), "", 805,
                  typeid(::KoaPPElasticIdealGenerator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaPPElasticIdealGenerator::Dictionary, isa_proxy, 4,
                  sizeof(::KoaPPElasticIdealGenerator) );
      instance.SetNew(&new_KoaPPElasticIdealGenerator);
      instance.SetNewArray(&newArray_KoaPPElasticIdealGenerator);
      instance.SetDelete(&delete_KoaPPElasticIdealGenerator);
      instance.SetDeleteArray(&deleteArray_KoaPPElasticIdealGenerator);
      instance.SetDestructor(&destruct_KoaPPElasticIdealGenerator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaPPElasticIdealGenerator*)
   {
      return GenerateInitInstanceLocal((::KoaPPElasticIdealGenerator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaPPElasticIdealGenerator*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr KoaPythia8Generator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaPythia8Generator::Class_Name()
{
   return "KoaPythia8Generator";
}

//______________________________________________________________________________
const char *KoaPythia8Generator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPythia8Generator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaPythia8Generator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPythia8Generator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaPythia8Generator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPythia8Generator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaPythia8Generator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPythia8Generator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaPpelasticGeneratorImp::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaPpelasticGeneratorImp::Class_Name()
{
   return "KoaPpelasticGeneratorImp";
}

//______________________________________________________________________________
const char *KoaPpelasticGeneratorImp::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPpelasticGeneratorImp*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaPpelasticGeneratorImp::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPpelasticGeneratorImp*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaPpelasticGeneratorImp::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPpelasticGeneratorImp*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaPpelasticGeneratorImp::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPpelasticGeneratorImp*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaPpelasticGenerator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaPpelasticGenerator::Class_Name()
{
   return "KoaPpelasticGenerator";
}

//______________________________________________________________________________
const char *KoaPpelasticGenerator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPpelasticGenerator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaPpelasticGenerator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPpelasticGenerator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaPpelasticGenerator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPpelasticGenerator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaPpelasticGenerator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPpelasticGenerator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairEvtFilter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairEvtFilter::Class_Name()
{
   return "FairEvtFilter";
}

//______________________________________________________________________________
const char *FairEvtFilter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEvtFilter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairEvtFilter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEvtFilter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairEvtFilter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEvtFilter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairEvtFilter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEvtFilter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairEvtFilterParams::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairEvtFilterParams::Class_Name()
{
   return "FairEvtFilterParams";
}

//______________________________________________________________________________
const char *FairEvtFilterParams::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEvtFilterParams*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairEvtFilterParams::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEvtFilterParams*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairEvtFilterParams::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEvtFilterParams*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairEvtFilterParams::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEvtFilterParams*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairFilteredPrimaryGenerator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairFilteredPrimaryGenerator::Class_Name()
{
   return "FairFilteredPrimaryGenerator";
}

//______________________________________________________________________________
const char *FairFilteredPrimaryGenerator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairFilteredPrimaryGenerator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairFilteredPrimaryGenerator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairFilteredPrimaryGenerator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairFilteredPrimaryGenerator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairFilteredPrimaryGenerator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairFilteredPrimaryGenerator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairFilteredPrimaryGenerator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaEvtFilterOnGeometry::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaEvtFilterOnGeometry::Class_Name()
{
   return "KoaEvtFilterOnGeometry";
}

//______________________________________________________________________________
const char *KoaEvtFilterOnGeometry::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEvtFilterOnGeometry*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaEvtFilterOnGeometry::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEvtFilterOnGeometry*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaEvtFilterOnGeometry::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEvtFilterOnGeometry*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaEvtFilterOnGeometry::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEvtFilterOnGeometry*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaPPElasticIdealGenerator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaPPElasticIdealGenerator::Class_Name()
{
   return "KoaPPElasticIdealGenerator";
}

//______________________________________________________________________________
const char *KoaPPElasticIdealGenerator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPPElasticIdealGenerator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaPPElasticIdealGenerator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPPElasticIdealGenerator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaPPElasticIdealGenerator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPPElasticIdealGenerator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaPPElasticIdealGenerator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPPElasticIdealGenerator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void KoaPythia8Generator::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaPythia8Generator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaPythia8Generator::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaPythia8Generator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaPythia8Generator(void *p) {
      return  p ? new(p) ::KoaPythia8Generator : new ::KoaPythia8Generator;
   }
   static void *newArray_KoaPythia8Generator(Long_t nElements, void *p) {
      return p ? new(p) ::KoaPythia8Generator[nElements] : new ::KoaPythia8Generator[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaPythia8Generator(void *p) {
      delete ((::KoaPythia8Generator*)p);
   }
   static void deleteArray_KoaPythia8Generator(void *p) {
      delete [] ((::KoaPythia8Generator*)p);
   }
   static void destruct_KoaPythia8Generator(void *p) {
      typedef ::KoaPythia8Generator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaPythia8Generator

//______________________________________________________________________________
void KoaPpelasticGeneratorImp::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaPpelasticGeneratorImp.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaPpelasticGeneratorImp::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaPpelasticGeneratorImp::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaPpelasticGeneratorImp(void *p) {
      return  p ? new(p) ::KoaPpelasticGeneratorImp : new ::KoaPpelasticGeneratorImp;
   }
   static void *newArray_KoaPpelasticGeneratorImp(Long_t nElements, void *p) {
      return p ? new(p) ::KoaPpelasticGeneratorImp[nElements] : new ::KoaPpelasticGeneratorImp[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaPpelasticGeneratorImp(void *p) {
      delete ((::KoaPpelasticGeneratorImp*)p);
   }
   static void deleteArray_KoaPpelasticGeneratorImp(void *p) {
      delete [] ((::KoaPpelasticGeneratorImp*)p);
   }
   static void destruct_KoaPpelasticGeneratorImp(void *p) {
      typedef ::KoaPpelasticGeneratorImp current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaPpelasticGeneratorImp

//______________________________________________________________________________
void KoaPpelasticGenerator::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaPpelasticGenerator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaPpelasticGenerator::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaPpelasticGenerator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaPpelasticGenerator(void *p) {
      return  p ? new(p) ::KoaPpelasticGenerator : new ::KoaPpelasticGenerator;
   }
   static void *newArray_KoaPpelasticGenerator(Long_t nElements, void *p) {
      return p ? new(p) ::KoaPpelasticGenerator[nElements] : new ::KoaPpelasticGenerator[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaPpelasticGenerator(void *p) {
      delete ((::KoaPpelasticGenerator*)p);
   }
   static void deleteArray_KoaPpelasticGenerator(void *p) {
      delete [] ((::KoaPpelasticGenerator*)p);
   }
   static void destruct_KoaPpelasticGenerator(void *p) {
      typedef ::KoaPpelasticGenerator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaPpelasticGenerator

//______________________________________________________________________________
void FairEvtFilter::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairEvtFilter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairEvtFilter::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairEvtFilter::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairEvtFilter(void *p) {
      delete ((::FairEvtFilter*)p);
   }
   static void deleteArray_FairEvtFilter(void *p) {
      delete [] ((::FairEvtFilter*)p);
   }
   static void destruct_FairEvtFilter(void *p) {
      typedef ::FairEvtFilter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairEvtFilter

//______________________________________________________________________________
void FairEvtFilterParams::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairEvtFilterParams.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairEvtFilterParams::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairEvtFilterParams::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairEvtFilterParams(void *p) {
      return  p ? new(p) ::FairEvtFilterParams : new ::FairEvtFilterParams;
   }
   static void *newArray_FairEvtFilterParams(Long_t nElements, void *p) {
      return p ? new(p) ::FairEvtFilterParams[nElements] : new ::FairEvtFilterParams[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairEvtFilterParams(void *p) {
      delete ((::FairEvtFilterParams*)p);
   }
   static void deleteArray_FairEvtFilterParams(void *p) {
      delete [] ((::FairEvtFilterParams*)p);
   }
   static void destruct_FairEvtFilterParams(void *p) {
      typedef ::FairEvtFilterParams current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairEvtFilterParams

//______________________________________________________________________________
void FairFilteredPrimaryGenerator::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairFilteredPrimaryGenerator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairFilteredPrimaryGenerator::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairFilteredPrimaryGenerator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairFilteredPrimaryGenerator(void *p) {
      return  p ? new(p) ::FairFilteredPrimaryGenerator : new ::FairFilteredPrimaryGenerator;
   }
   static void *newArray_FairFilteredPrimaryGenerator(Long_t nElements, void *p) {
      return p ? new(p) ::FairFilteredPrimaryGenerator[nElements] : new ::FairFilteredPrimaryGenerator[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairFilteredPrimaryGenerator(void *p) {
      delete ((::FairFilteredPrimaryGenerator*)p);
   }
   static void deleteArray_FairFilteredPrimaryGenerator(void *p) {
      delete [] ((::FairFilteredPrimaryGenerator*)p);
   }
   static void destruct_FairFilteredPrimaryGenerator(void *p) {
      typedef ::FairFilteredPrimaryGenerator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairFilteredPrimaryGenerator

//______________________________________________________________________________
void KoaEvtFilterOnGeometry::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaEvtFilterOnGeometry.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaEvtFilterOnGeometry::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaEvtFilterOnGeometry::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaEvtFilterOnGeometry(void *p) {
      return  p ? new(p) ::KoaEvtFilterOnGeometry : new ::KoaEvtFilterOnGeometry;
   }
   static void *newArray_KoaEvtFilterOnGeometry(Long_t nElements, void *p) {
      return p ? new(p) ::KoaEvtFilterOnGeometry[nElements] : new ::KoaEvtFilterOnGeometry[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaEvtFilterOnGeometry(void *p) {
      delete ((::KoaEvtFilterOnGeometry*)p);
   }
   static void deleteArray_KoaEvtFilterOnGeometry(void *p) {
      delete [] ((::KoaEvtFilterOnGeometry*)p);
   }
   static void destruct_KoaEvtFilterOnGeometry(void *p) {
      typedef ::KoaEvtFilterOnGeometry current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaEvtFilterOnGeometry

//______________________________________________________________________________
void KoaPPElasticIdealGenerator::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaPPElasticIdealGenerator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaPPElasticIdealGenerator::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaPPElasticIdealGenerator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaPPElasticIdealGenerator(void *p) {
      return  p ? new(p) ::KoaPPElasticIdealGenerator : new ::KoaPPElasticIdealGenerator;
   }
   static void *newArray_KoaPPElasticIdealGenerator(Long_t nElements, void *p) {
      return p ? new(p) ::KoaPPElasticIdealGenerator[nElements] : new ::KoaPPElasticIdealGenerator[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaPPElasticIdealGenerator(void *p) {
      delete ((::KoaPPElasticIdealGenerator*)p);
   }
   static void deleteArray_KoaPPElasticIdealGenerator(void *p) {
      delete [] ((::KoaPPElasticIdealGenerator*)p);
   }
   static void destruct_KoaPPElasticIdealGenerator(void *p) {
      typedef ::KoaPPElasticIdealGenerator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaPPElasticIdealGenerator

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
   static TClass *vectorlEboolgR_Dictionary();
   static void vectorlEboolgR_TClassManip(TClass*);
   static void *new_vectorlEboolgR(void *p = 0);
   static void *newArray_vectorlEboolgR(Long_t size, void *p);
   static void delete_vectorlEboolgR(void *p);
   static void deleteArray_vectorlEboolgR(void *p);
   static void destruct_vectorlEboolgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bool>*)
   {
      vector<bool> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bool>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bool>", -2, "vector", 543,
                  typeid(vector<bool>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEboolgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<bool>) );
      instance.SetNew(&new_vectorlEboolgR);
      instance.SetNewArray(&newArray_vectorlEboolgR);
      instance.SetDelete(&delete_vectorlEboolgR);
      instance.SetDeleteArray(&deleteArray_vectorlEboolgR);
      instance.SetDestructor(&destruct_vectorlEboolgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bool> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bool>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEboolgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bool>*)0x0)->GetClass();
      vectorlEboolgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEboolgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEboolgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bool> : new vector<bool>;
   }
   static void *newArray_vectorlEboolgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bool>[nElements] : new vector<bool>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEboolgR(void *p) {
      delete ((vector<bool>*)p);
   }
   static void deleteArray_vectorlEboolgR(void *p) {
      delete [] ((vector<bool>*)p);
   }
   static void destruct_vectorlEboolgR(void *p) {
      typedef vector<bool> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bool>

namespace ROOT {
   static TClass *setlEintgR_Dictionary();
   static void setlEintgR_TClassManip(TClass*);
   static void *new_setlEintgR(void *p = 0);
   static void *newArray_setlEintgR(Long_t size, void *p);
   static void delete_setlEintgR(void *p);
   static void deleteArray_setlEintgR(void *p);
   static void destruct_setlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const set<int>*)
   {
      set<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(set<int>));
      static ::ROOT::TGenericClassInfo 
         instance("set<int>", -2, "set", 93,
                  typeid(set<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &setlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(set<int>) );
      instance.SetNew(&new_setlEintgR);
      instance.SetNewArray(&newArray_setlEintgR);
      instance.SetDelete(&delete_setlEintgR);
      instance.SetDeleteArray(&deleteArray_setlEintgR);
      instance.SetDestructor(&destruct_setlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Insert< set<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const set<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *setlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const set<int>*)0x0)->GetClass();
      setlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void setlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_setlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) set<int> : new set<int>;
   }
   static void *newArray_setlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) set<int>[nElements] : new set<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_setlEintgR(void *p) {
      delete ((set<int>*)p);
   }
   static void deleteArray_setlEintgR(void *p) {
      delete [] ((set<int>*)p);
   }
   static void destruct_setlEintgR(void *p) {
      typedef set<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class set<int>

namespace {
  void TriggerDictionaryInitialization_G__KoaGeneratorDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairroot/v18_jun19/include",
"/home/yong/src/KoalaSoft/generators",
"/home/yong/src/KoalaSoft/data",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/src/KoalaSoft/build_digi/generators/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__KoaGeneratorDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class KoaPythia8Generator;
class KoaPpelasticGeneratorImp;
class KoaPpelasticGenerator;
class __attribute__((annotate("$clingAutoload$FairEvtFilter.h")))  FairEvtFilter;
class __attribute__((annotate("$clingAutoload$FairEvtFilterParams.h")))  FairEvtFilterParams;
class FairFilteredPrimaryGenerator;
class KoaEvtFilterOnGeometry;
class KoaPPElasticIdealGenerator;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__KoaGeneratorDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#ifndef KOA_PYTHIA8_GENERATOR_H
#define KOA_PYTHIA8_GENERATOR_H 1

#include "FairGenerator.h"
#include "Pythia8/Basics.h"  // for RndmEngine
#include "Pythia8/Pythia.h"  // for Pythia
#include "TRandom1.h"
#include "TRandom3.h"
#include <vector>
#include <string>

class FairPrimaryGenerator;

using namespace Pythia8;

class PyTr1Rng : public RndmEngine
{
 public:
  PyTr1Rng() {
    rng = new TRandom1(gRandom->GetSeed());
  };
  virtual ~PyTr1Rng() {};

  Double_t flat() {
    return rng->Rndm();
  };

 private:
  TRandom1 *rng; //!
};

class PyTr3Rng : public RndmEngine
{
 public:
  PyTr3Rng() {
    rng = new TRandom3(gRandom->GetSeed());
  };
  virtual ~PyTr3Rng() {};

  Double_t flat() {
    return rng->Rndm();
  };

 private:
  TRandom3 *rng; //!
};




class KoaPythia8Generator : public FairGenerator
{
 public:

  /** default constructor **/
  KoaPythia8Generator();

  /** destructor **/
  virtual ~KoaPythia8Generator();

  /** public method ReadEvent **/
  Bool_t ReadEvent(FairPrimaryGenerator*);
  void SetParameters(std::string);
  void Print(); //!

  virtual Bool_t Init(); //!

  void SetId(Int_t id) {
    fId  = id;
  };
  void SetMom(Double_t mom) {
    fMom = mom;
  };
  void UseRandom1() {
    fUseRandom1 = kTRUE;
    fUseRandom3 = kFALSE;
  };
  void UseRandom3() {
    fUseRandom1 = kFALSE;
    fUseRandom3 = kTRUE;
  };

 public:
  Pythia fPythia;             //!

 private:
  RndmEngine* fRandomEngine;  //!
  std::vector<std::string> fParams;         //!

 protected:
  Int_t    fId;        // beam particle type
  Double_t fMom;       // pbar momentum
  Bool_t fUseRandom1;  // flag to use TRandom1
  Bool_t fUseRandom3;  // flag to use TRandom3 (default)

  ClassDef(KoaPythia8Generator,1);
};

#endif /* !KOA_PYTHIA8_GENERATOR_H */
// -------------------------------------------------------------------------
// -----                 KoaPpelasticGenerator header file                  -----
// -----               Created 05/02/07  by S.Spataro                 -----
// -------------------------------------------------------------------------

/** KoaPpelasticGenerator.h
 *@author S.Spataro <stefano.spataro@exp2.physik.uni-giessen.de>
 *
 The KoaPpelasticGenerator reads the DPM output file (ROOT format)
 and inserts the tracks into the PndStack via the FairPrimaryGenerator.
 Derived from FairGenerator.
**/


#ifndef KOA_PPELASTICGENERATOR_H
#define KOA_PPELASTICGENERATOR_H


#include "FairGenerator.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TParticle.h"

class TClonesArray;
class TFile;
class TTree;
class FairPrimaryGenerator;

class  KoaPpelasticGeneratorImp
{
 public:
  TParticle fScatteredProton;
  TParticle fRecoilProton;

private:
  Double_t  fPlab;
  Double_t  fTetmin;

  Double_t   fTetaCMS;        //  sampled Theta in CMS
  Double_t  fThetaLab;        //sampled Theta in Lab system
  Double_t   fBeta;         // velosity of projectile 

  Double_t  fT;          // T invariant 
  Double_t  fRa;         // Radius of target 
  Double_t fRef;        // Effective radiuse for Calculation of hadron cross-section
  Double_t fceff;       // Effective diffuse parameter  
  Double_t rho;        //ratio of real to imaginary parts of elastic amplitude
  Double_t  Mn;        //mass of nucleon
  TVector3   fbst;          // boost vector
  TLorentzVector   fvect;  //4-vector of produced particle (px,py,pz,E)  
  Double_t           fTmax;          
  Double_t           cs_tot;           //pp - XS_total
  Double_t           cs_el;             //pp - XS_elastic 
  Double_t   Pcms;         // momentum of projectile in CMS system
  Double_t   S;            //  Energy in CMS system
  /* Double_t   Ecms;         // Energy of 1 proton in CMS system */
  Double_t SqrtS;         // sqrt of S
  Double_t Vcms;          // velosity in CMS system 
  Double_t Gamma;         // gamma factor in CMS system

  Double_t  prob_col;  // probability of Coulomb part
  Double_t  prob_int;  // probability of Interf part
  Double_t  prob_had;  // probability of hadron part 

  Double_t  aelm;
  Double_t  sigma_tot;
  Double_t  B;  
  Double_t A1;
  Double_t A2;
  Double_t Fun_inv[300000];
  Int_t fNdiv;  
  Double_t fdto;
  Double_t fTmin; 

 public:
  KoaPpelasticGeneratorImp();
  KoaPpelasticGeneratorImp(Double_t p);
  virtual   ~KoaPpelasticGeneratorImp()  {Reset();}

  void     SetPlab(Double_t plab) {fPlab=plab;}
  void     SetTetmin(Double_t tetmin) {fTetmin=tetmin;}

  void     InitValue();
  void     Init(Double_t Plab=20., Double_t tetmin=-1.);
  void     NextEvent(); 
  
  Double_t  SampleInvariantT(Double_t Plab=20., Int_t Z=1);
  Double_t SampleThetaCMS(Double_t Plab=20., Int_t Z=1);
  Double_t SampleThetaLab(Double_t Plab=20., Int_t Z=1);
  Double_t CalculateParticleBeta(Double_t momentum);
  Double_t DSIG_COL(Double_t T);
  Double_t DSIG_INT(Double_t T);
  Double_t DSIG_HAD(Double_t T);

  void       Reset()        {}

  ClassDef(KoaPpelasticGeneratorImp,1)
};
 

class KoaPpelasticGenerator : public FairGenerator
{

 public: 

  /** Default constructor (should not be used) **/
  KoaPpelasticGenerator();
  KoaPpelasticGenerator(Double_t p);


  /** Standard constructor
   ** @param fileName The input (PLUTO) file name
   **/
  KoaPpelasticGenerator(const Char_t* fileName);


  /** Destructor **/
  virtual ~KoaPpelasticGenerator();


  /** Reads on event from the input file and pushes the tracks onto
   ** the stack. Abstract method in base class.
   ** @param primGen  pointer to the FairPrimaryGenerator
   **/
  virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);

  void SetStartEvent(Int_t start) { iEvent = start; };
	
 private:

  Int_t iEvent;      //! Event number
  Bool_t fFromFile;
  const Char_t* fFileName;   //! Input file name
  TFile* fInputFile;        //! Pointer to input file
  TTree* fInputTree;        //! Pointer to input tree
  TClonesArray* fParticles;  //! Particle array from PLUTO

  /** Private method CloseInput. Just for convenience. Closes the 
   ** input file properly. Called from destructor and from ReadEvent. **/
  void CloseInput();

  KoaPpelasticGeneratorImp fInternalGenerator;

  ClassDef(KoaPpelasticGenerator,1);

};

#endif
/**
 @class FairFilteredPrimaryGenerator

 @author Martin J. Galuska <martin [dot] j [dot] galuska (at) physik [dot] uni (minus) giessen [dot] de>
 @author Katja Kleeberg

 @brief Primary generator with added event filtering capabilities.

 This class adds event filtering capabilities to FairPrimaryGenerator which is used internally for handling the event generators and so on.
 The event filtering is performed after the event generation and before the particle transport through the detector model.

 From the description of FairPrimaryGenerator:

 The FairFilteredPrimaryGenerator is responsible for the handling of the MC input.
 Several input generators can be registered to it; these have to be
 derived from the FairGenerator class. The FairFilteredPrimaryGenerator defines
 position and (optionally) smearing of the primary vertex.
 This class should be instantiated only once.
 */

/** Added by Yong Zhou
    This file is copied from PandaRoot feb17p1
**/



#ifndef FairFilteredPrimaryGenerator_H
#define FairFilteredPrimaryGenerator_H

#include "FairPrimaryGenerator.h"

#include "FairEvtFilter.h"
#include "FairEvtFilterParams.h"

#include "TNamed.h"                     // for TNamed
#include "TFile.h"                     // for TFile
#include "FairRunSim.h"

#include "FairGenerator.h"              // for FairGenerator

#include <iosfwd>                   // for ostream
#include "Rtypes.h"                     // for Double_t, Bool_t, Int_t, etc
#include "TObjArray.h"                  // for TObjArray
#include "TVector3.h"                   // for TVector3

#include <iostream>                     // for operator<<, basic_ostream, etc
#include <vector>


class FairGenericStack;
class FairMCEventHeader;
class TIterator;



class FairFilteredPrimaryGenerator : public FairPrimaryGenerator
{

public:

	/** @brief Default constructor. **/
	FairFilteredPrimaryGenerator();


	/** @brief Constructor with name and title **/
	FairFilteredPrimaryGenerator(const char* name, const char* title="Filtered Generator");


	/** @brief Destructor. **/
	virtual ~FairFilteredPrimaryGenerator();

	/** @brief Initialize the event generator(s) and the event (veto) filter(s). **/
	virtual Bool_t Init();

	/** @brief Register a non-veto event filter using a logical AND to connect with previously defined non-veto event filters. **/
	void AndFilter(FairEvtFilter* filter) {
		AddFilter(filter, FairEvtFilter::kAnd, kFALSE);
	}

	/** @brief Register a non-veto event filter using a logical AND NOT to connect with previously defined non-veto event filters. **/
	void AndNotFilter(FairEvtFilter* filter) {
		AddFilter(filter, FairEvtFilter::kAnd, kTRUE);
	}

	/** @brief Register a non-veto event filter using a logical OR to connect with previously defined non-veto event filters. **/
	void OrFilter(FairEvtFilter* filter) {
		AddFilter(filter, FairEvtFilter::kOr, kFALSE);
	}

	/** @brief Register a non-veto event filter using a logical OR NOT to connect with previously defined non-veto event filters. **/
	void OrNotFilter(FairEvtFilter* filter) {
		AddFilter(filter, FairEvtFilter::kOr, kTRUE);
	}

	/** @brief Register an event veto filter. Veto filters have higher priority than regular event filters. If the event matches any veto filter, it will be skipped.  **/
	void AddVetoFilter(FairEvtFilter* filter) {
		if ( ! fVetoFilterList ) {
			std::cout << "Empty fFilterList pointer ! \n";
			return;
		}
		fVetoFilterList->Add(filter);
		fEventVetoFilterActive = kTRUE;
	}


	/** @brief Calls event generators and the event filters.
	 *
        To be called at the beginning of each event from FairMCApplication.
        Generates an event vertex and calls the ReadEvent methods from the
        registered generators.
        Calls defined event (veto) filters to decide whether to process the event
        or to call the event generators again.
	 *@param pStack The particle stack
	 *@return kTRUE if successful, kFALSE if not
	 **/
	virtual Bool_t GenerateEvent(FairGenericStack* pStack);


	TObjArray* GetListOfFilters() { return fFilterList;}

	TObjArray* GetListOfVetoFilters() { return fVetoFilterList;}

	/** @brief Define the maximum number of times that this object should try to find an event which suits all event filters. **/
	void SetFilterMaxTries(Int_t maxTries=99999)
	{
		if ( maxTries > 0 ){
			fEvtFilterStat.fFilterMaxTries = maxTries;
			std::cout << "FairFilteredPrimaryGenerator: maxTries is now set to " << fEvtFilterStat.fFilterMaxTries << "\n";
		} else {
			std::cout << "\n\n\n  -WARNING from FairFilteredPrimaryGenerator: maxTries must be a positive number! Check your SetFilterMaxTries call!\n\n\n";
		}
	}

	/** @brief returns the maximum number of times that this object should try to find an event which suits all event filters. */
	Int_t GetNumberOfFilterMaxTries(){
		return fEvtFilterStat.fFilterMaxTries;
	}

	/** @brief returns the total (accepted + rejected) number of events generated by the event generators. If no event filters are used this number is equal to the number of simulated events. */
	Int_t GetNumberOfGeneratedEvents(){
		return fEvtFilterStat.fGeneratedEvents;
	}

	/** @brief Returns the number of cases in which no matching event was found within the set max. tries.
	 *
		 This method returns 0 if everything works fine.
		 If it returns a value >0 it means that you should set a higher limit in SetFilterMaxTries.
		 If it returns a value which is equal to the number of events that you requested, it means that either the max. number of tries is set way too low
		 or that the generator does not create such events that you are interested in
		 or that your event filters cannot be satisfied at all (logical error).
	 */
	Int_t GetNumberOfFilterFailedEvents(){
		return fEvtFilterStat.fFailedFilterEvents;
	}

	/** @brief Writes all relevant event filter information to the output root file */
	void WriteEvtFilterStatsToRootFile(){
		std::cout << "\n\nGenerated Events = " << GetNumberOfGeneratedEvents() << "\n";
		if (0 < GetNumberOfFilterFailedEvents() ) {
			std::cout << "WARNING: Number of events where the event filter FAILED " << GetNumberOfFilterFailedEvents() << "\n\n\n";
			std::cout << "Random events were accepted to avoid infinite loops. \n";
			std::cout <<  "Try increasing the max. number of tries or change your filter (maybe the generators do not produce such events as you want).\n\n";
		}
		TFile* outputFile;
		outputFile = FairRunSim::Instance()->GetOutputFile();
		outputFile->cd();
		outputFile->mkdir("FairEvtFilter");
		outputFile->cd("FairEvtFilter");
		fEvtFilterStat.Write();
		outputFile->cd();
	}

	/**@brief Set the level of commenting output.
	 * @param verbose Level of commenting output, 0 means no output, higher gives more output.
	 */
	void SetVerbose(Int_t verbose=12){
		if ( verbose >= 0 ){
			fVerbose = verbose;
			std::cout << "FairFilteredPrimaryGenerator: fVerbose is now set to " << verbose << "\n";
		} else {
			std::cout << "\n\n\n  -WARNING from FairFilteredPrimaryGenerator: verbose must be a positive number! Check your SetVerbose call!\n\n\n";
		}
	}



protected:
	/** @brief  List of registered veto filters */
	TObjArray*  fVetoFilterList;
	/** @brief  Iterator over veto filter list */
	TIterator*  fVetoFilterIter;      //!
	/** @brief  List of registered filters */
	TObjArray*  fFilterList;
	/** @brief  Iterator over filter list */
	TIterator*  fFilterIter;      //!

	/** @brief Contains the statistics of the event filtering process. */
	FairEvtFilterParams fEvtFilterStat;
	/** @brief Level of commenting output, 0 means no output, higher gives more output. */
	Int_t fVerbose;
	/** @brief returns kTRUE if any event veto filter is registered. */
	Bool_t fEventVetoFilterActive;
	/** @brief returns kTRUE if any non-veto event filter is registerd. */
	Bool_t fEventFilterActive;
	/** @brief Vector containing the results of the EventMatches methods for every registered non-veto event filter in the corresponding order.
	 *
	    The content of the vector is overwritten for each generated event. */
	std::vector<Bool_t> filterAcceptEvent;
	/** @brief vector containing the logical operations with which the outputs of the non-veto event filters should be combined.
	 *
	    The vector grows automatically with every added non-veto event filter.
	    It is used to combine multiple filters via && or ||.
	    The expression is evaluated sequentally from the first registered filter to the last one disregarding operator priorities.
	*/
	std::vector<UInt_t> fLogicalFilterOperation;
	/** @brief vector determining whether the output of a non-veto event filter should be negated or not.
	 *
	 The vector grows automatically with every added non-veto event filter.
	 A kTRUE entry at position i in the vector negates the i. filter's output, kFALSE entries do not negate.
	*/
	std::vector<Bool_t> fFilterNegation;


	/** @brief Event number (Set by the filtered primary generator **/
	Int_t fEventNrFiltered;


	/** @brief Registers a regular (non-veto) filter. This method is not supposed to be directly used by the user. See public methods for user interfaces to this method. */
	void AddFilter(FairEvtFilter* filter, FairEvtFilter::LogicOp op, Bool_t negateFilter) {
		if ( ! fFilterList ) {
			std::cout << "Empty fFilterList pointer ! \n";
			return;
		}
		fFilterList->Add(filter);
		fEventFilterActive = kTRUE;
		// add the settings for every new filter
		if(fFilterList->GetEntriesFast()!=1){
			fLogicalFilterOperation.push_back(op);
		}
		fFilterNegation.push_back(negateFilter);
	}


private:
	FairFilteredPrimaryGenerator(const FairFilteredPrimaryGenerator&);
	FairFilteredPrimaryGenerator& operator=(const  FairFilteredPrimaryGenerator&);


	ClassDef(FairFilteredPrimaryGenerator,1);
};

#endif
// -------------------------------------------------------------------------
// -----                    FairEvtFilter header file                   -----
// -------------------------------------------------------------------------


/** FairEvtFilter.h

Authors: Martin Galuska, Katja Kleeberg

abstract base class for event filters
used to reject generated events which should not be fed into the transport.
Each concrete filter class derived from this one must implement the abstract
method EventMatches, in which the particular filter criteria are realized.

 **/

/** Added by Yong Zhou
    This file is copied from PandaRoot feb17p1
**/

#ifndef FAIREVTFILTER_H
#define FAIREVTFILTER_H

#include "TNamed.h"                     // for TNamed
#include "Rtypes.h"                     // for Bool_t, etc
#include "TClonesArray.h"
#include "TParticle.h"
#include <iostream>
#include <set>
#include "TDatabasePDG.h"


std::ostream& operator <<(std::ostream& os, const std::set<Int_t> & set);



class FairEvtFilter : public TNamed
{

public:

	enum ChargeState { kNeutral=0, kPlus, kMinus, kCharged, kAll, kChargeLastElement };
	enum MomState { kMomTotal=0, kMomTrans, kMomZ, kMomLastElement};
	enum GeomState {kTheta=0, kPhi, kVertexZ, kVertexRho, kVertexRadius, kGeomLastElement};
	enum LogicOp { kAnd=0, kOr, kLogicOpLastElement };

	/** Default constructor. **/
	FairEvtFilter();


	/** Constructor with name and title **/
	FairEvtFilter(const char* name, const char* title="FairEvtFilter");


	/** Destructor. **/
	virtual ~FairEvtFilter();


	//contains the list of particles that should be checked in the EventMatches method
	Bool_t SetListOfParticles(TClonesArray* ParticleList){fParticleList=ParticleList; return kTRUE;};

	// prints all TParticle in event
	void PrintAllTParticleInEvent();


	//Initialize the filter if needed
	Bool_t Init() { return kTRUE;}


	void SetVerbose(Int_t verbose=12){
		if ( verbose >= 0 ){
			fVerbose = verbose;
			std::cout << "FairEvtFilter: fVerbose is now set to " << verbose << "\n";
		} else {
			std::cout << "\n\n\n  -WARNING from FairEvtFilter: verbose must be a positive number! Check your SetVerbose call!\n\n\n";
		}
	}


	void ShowAcceptedEventNumbers(){
		// for QA
		// shows fAcceptedEventNumbers that is filled after running a simulation
		std::cout << "\n fAcceptedEventNumbers" << " = " << fAcceptedEventNumbers;
	}


	void ShowEvtNrsToAccept(){
		// for QA
		//shows fEvtNrsToAccept that has to be set if you want to run your simulation in test mode
		std::cout << "\n fEvtNrsToAccept" << " = " << fEvtNrsToAccept;
	}


	void SetTestMode(Int_t* arrayPtr, Int_t nEntries){
		//turns on the test mode with the declared fEvtNrsToAccept
		fTestMode=kTRUE;
		std::set<Int_t> evtNrsToAccept (arrayPtr,arrayPtr+nEntries);
		fEvtNrsToAccept=evtNrsToAccept;
	}


	Bool_t TestPassed(){
		if(kFALSE==fTestMode){
			std::cout << "\n\n\n WARNING from FairEvtFilter: Test mode not set.\n\n\n";
			return kFALSE;
		}
		if(fAcceptedEventNumbers==fEvtNrsToAccept){
			//std::cout << "\n\n\n FairEvtFilter: Test passed.\n\n\n";
			return kTRUE;
		}else{
			//std::cout << "\n\n\n FairEvtFilter: Test failed. Check your SetTestMode calls. \n\n\n";
			return kFALSE;
		}
	}


	// returning kTRUE indicates that the event satisfies the filter conditions,
	// kFALSE otherwise.
	virtual Bool_t EventMatches(Int_t evtNr)=0;

	virtual Bool_t FilterActive()=0;

	// returns kTRUE if successful
	// pdgCodeCharge will contain the charge of the particle with pdg code inPdgCode
	Bool_t GetCharge ( Int_t inPdgCode, Double_t *pdgCodeCharge );


protected:
	TDatabasePDG* fdbPdg;
	// constant holding a double number which is not a valid charge
	// this serves to indicate that the value has not been specified by the user
	static const Double_t kNoChargeSpecified;

	TClonesArray* fParticleList; // list of particles in the event which was generated
	Int_t fVerbose; // level of commenting output for your filter, between 0 and 12
	Bool_t fTestMode; // is kTRUE if the filter should run in QA test mode
	std::set<Int_t> fAcceptedEventNumbers; // set of event numbers which were accepted by the filter
	std::set<Int_t> fEvtNrsToAccept; // event numbers that SHOULD be accepted by the filter (QA test mode)
	Int_t fEventNr; // current event number

private:
	FairEvtFilter(const FairEvtFilter& G);
	FairEvtFilter& operator= (const FairEvtFilter&) {return *this;}



	ClassDef(FairEvtFilter,1);
};

#endif


// -------------------------------------------------------------------------
// -----             FairEvtFilterParams header file                 -----
// -------------------------------------------------------------------------


/** FairEvtFilterParams.h

 Authors: Martin Galuska, Katja Kleeberg
 Martin dot J dot Galuska at physik dot uni minus giessen dot de

 Helper class for writing settings and statistics of the event filter to the sim root file

 **/

/** Added by Yong Zhou
    This file is copied from PandaRoot feb17p1
**/
/** TODO:
    1. use FairLogger for information output
 **/


#ifndef FAIREVTFILTERPARAMS_H_
#define FAIREVTFILTERPARAMS_H_

#include "TObject.h"

class FairEvtFilterParams : public TObject
{

public:

	// Default constructor.
	FairEvtFilterParams();

	// constructor with parameters
	FairEvtFilterParams(Long_t FailedFilterEvents, Long_t GeneratedEvents, Long_t FilterMaxTries);

	// Destructor.
	virtual ~FairEvtFilterParams();

	// number of failed attempts to find an event that satisfies all event filters
	// events are generated by the registered event generators
	// a value other than 0 indicates that there is something wrong!
	Long_t fFailedFilterEvents;

	// total number of generated events (accepted + rejected)
	Long_t fGeneratedEvents;

	// limiting number for the attempts to find an event that suits all event filters
	// set this to a very high number
	// this number is only used to avoid infinite loops in case no event can be found
	Long_t fFilterMaxTries;

	ClassDef(FairEvtFilterParams,1)
};


#endif /* FAIREVTFILTERPARAMS_H_ */
// -------------------------------------------------------------------------
// -----                 KoaEvtFilterOnGeometry header file                  -----
// -----               Created 27/06/17  by Y.Zhou                 -----
// -------------------------------------------------------------------------

/** KoaEvtFilterOnGeometry.h
 *@author Y.Zhou <y.zhou@fz-juelich.de>
 *
 The KoaEvtFilterOnGeometry will reject the event from transportation in simlation engine
 based on whether the generated tracks will hit the detector.
**/

#ifndef Koa_EvtFilterOnGeometry
#define Koa_EvtFilterOnGeometry

#include "FairEvtFilter.h"

class KoaEvtFilterOnGeometry : public FairEvtFilter
{
 public:
  KoaEvtFilterOnGeometry() : fUnlimitY(false), fUnlimitZ(false) {}
  KoaEvtFilterOnGeometry(const char* name, const char* title="KoaEvtFilterOnGeometry") {}
  virtual ~KoaEvtFilterOnGeometry() {}

  virtual Bool_t EventMatches(Int_t evtNr);
  virtual Bool_t FilterActive() {return kTRUE;}

  void SetX(Double_t range){ fXDistance = range;}
  void SetYRange(Double_t min, Double_t max){
    fYMin = min;
    fYMax = max;
  }
  void SetZRange(Double_t min, Double_t max){
    fZMin = min;
    fZMax = max;
  }
  void SetUnlimitY(Bool_t flag) { fUnlimitY = flag;}
  void SetUnlimitZ(Bool_t flag) { fUnlimitZ = flag;}

 private:
  Double_t fXDistance;
  Double_t fYMin;
  Double_t fYMax;
  Double_t fZMin;
  Double_t fZMax;

  Bool_t   fUnlimitY;
  Bool_t   fUnlimitZ;

  ClassDef(KoaEvtFilterOnGeometry, 1);
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
// -----                    KoaPPElasticIdealGenerator header file                   -----
// -----          Created 16/10/2019  by Y.Zhou
// -------------------------------------------------------------------------


/** KoaPPElasticIdealGenerator.h
 *@author Y.Zhou <y.zhou@fz-juelich.de>
 *
The KoaPPElasticIdealGenerator is the an generator for proton-proton elastic scattering.
It is based on the analytic calculation of elastic kinematics, with a specified recoil angle range.
The distribution within the range is flat, i.e. uniform.
**/


#ifndef KOA_PPELASTICIDEALGENERATOR_H
#define KOA_PPELASTICIDEALGENERATOR_H

#include "FairGenerator.h"


class FairPrimaryGenerator;

class KoaPPElasticIdealGenerator : public FairGenerator
{

  public:

    /** Default constructor. **/
    KoaPPElasticIdealGenerator();


    /** Constructor with name and title **/
    KoaPPElasticIdealGenerator(Double_t mom, Bool_t isGeantino = kFALSE);


    /** Destructor. **/
    virtual ~KoaPPElasticIdealGenerator();

    /** Modifiers. **/
    void SetMomentum(Double_t mom) // in GeV
    { fP = mom; }
    void SetGeantino() // generate geantino instead of proton
    { fIsGeantino = kTRUE; }
    void SetAlphaRange(Double_t min, Double_t max) // in degree
    { fAlphaMin = min; fAlphaMax = max; }
    void SetPhiRange(Double_t min, Double_t max) // in degree
    { fPhiMin = min; fPhiMax = max; }

    /** Abstract method ReadEvent must be implemented by any derived class.
        It has to handle the generation of input tracks (reading from input
        file) and the handing of the tracks to the FairPrimaryGenerator. I
        t is called from FairMCApplication.
        *@param pStack The stack
        *@return kTRUE if successful, kFALSE if not
    **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);


    /**Initialize the generator if needed */
    virtual Bool_t Init();

    /** Clone this object (used in MT mode only) */
    virtual KoaPPElasticIdealGenerator* CloneGenerator() const;

  protected:
    /** Copy constructor */
    KoaPPElasticIdealGenerator(const KoaPPElasticIdealGenerator&);
    /** Assignment operator */
    KoaPPElasticIdealGenerator& operator= (const KoaPPElasticIdealGenerator&);

 private:
    void Calculate(Double_t alpha, Double_t phi);

 private:
    Bool_t   fIsGeantino; // flag, use proton or geantino

    Double_t fMass; // rest mass of proton in GeV, from PDG2018
    Double_t fP; // beam proton momentum
    Double_t fAlphaMin, fAlphaMax; // angle alpha of recoil proton (with respect to x-axis)
    Double_t fPhiMin, fPhiMax; // angle phi of recoil proton
    Double_t fKappa;

    Double_t fRecoilPx, fRecoilPy, fRecoilPz;
    Double_t fScatPx, fScatPy, fScatPz;
    ClassDef(KoaPPElasticIdealGenerator,1);
};

#endif



#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairEvtFilter", payloadCode, "@",
"FairEvtFilterParams", payloadCode, "@",
"FairFilteredPrimaryGenerator", payloadCode, "@",
"KoaEvtFilterOnGeometry", payloadCode, "@",
"KoaPPElasticIdealGenerator", payloadCode, "@",
"KoaPpelasticGenerator", payloadCode, "@",
"KoaPpelasticGeneratorImp", payloadCode, "@",
"KoaPythia8Generator", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__KoaGeneratorDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__KoaGeneratorDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__KoaGeneratorDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__KoaGeneratorDict() {
  TriggerDictionaryInitialization_G__KoaGeneratorDict_Impl();
}
