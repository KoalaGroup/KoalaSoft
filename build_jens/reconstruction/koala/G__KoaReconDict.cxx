// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_jensdIreconstructiondIkoaladIG__KoaReconDict

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
#include "KoaRecNoiseFilter.h"
#include "KoaRecEnergyRecon.h"
#include "KoaRecTimeShiftCorrect.h"
#include "KoaRecTimeWalkCorrect.h"
#include "KoaRecRearRecon.h"
#include "KoaFwdRecon.h"
#include "KoaRecClusterCollect.h"
#include "KoaRecClusterSeedFilter.h"
#include "KoaRecClusterThresholdFilter.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_KoaRecNoiseFilter(void *p = 0);
   static void *newArray_KoaRecNoiseFilter(Long_t size, void *p);
   static void delete_KoaRecNoiseFilter(void *p);
   static void deleteArray_KoaRecNoiseFilter(void *p);
   static void destruct_KoaRecNoiseFilter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecNoiseFilter*)
   {
      ::KoaRecNoiseFilter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecNoiseFilter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecNoiseFilter", ::KoaRecNoiseFilter::Class_Version(), "", 27,
                  typeid(::KoaRecNoiseFilter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecNoiseFilter::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecNoiseFilter) );
      instance.SetNew(&new_KoaRecNoiseFilter);
      instance.SetNewArray(&newArray_KoaRecNoiseFilter);
      instance.SetDelete(&delete_KoaRecNoiseFilter);
      instance.SetDeleteArray(&deleteArray_KoaRecNoiseFilter);
      instance.SetDestructor(&destruct_KoaRecNoiseFilter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecNoiseFilter*)
   {
      return GenerateInitInstanceLocal((::KoaRecNoiseFilter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecNoiseFilter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecEnergyRecon(void *p = 0);
   static void *newArray_KoaRecEnergyRecon(Long_t size, void *p);
   static void delete_KoaRecEnergyRecon(void *p);
   static void deleteArray_KoaRecEnergyRecon(void *p);
   static void destruct_KoaRecEnergyRecon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecEnergyRecon*)
   {
      ::KoaRecEnergyRecon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecEnergyRecon >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecEnergyRecon", ::KoaRecEnergyRecon::Class_Version(), "", 121,
                  typeid(::KoaRecEnergyRecon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecEnergyRecon::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecEnergyRecon) );
      instance.SetNew(&new_KoaRecEnergyRecon);
      instance.SetNewArray(&newArray_KoaRecEnergyRecon);
      instance.SetDelete(&delete_KoaRecEnergyRecon);
      instance.SetDeleteArray(&deleteArray_KoaRecEnergyRecon);
      instance.SetDestructor(&destruct_KoaRecEnergyRecon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecEnergyRecon*)
   {
      return GenerateInitInstanceLocal((::KoaRecEnergyRecon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecEnergyRecon*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecTimeShiftCorrect(void *p = 0);
   static void *newArray_KoaRecTimeShiftCorrect(Long_t size, void *p);
   static void delete_KoaRecTimeShiftCorrect(void *p);
   static void deleteArray_KoaRecTimeShiftCorrect(void *p);
   static void destruct_KoaRecTimeShiftCorrect(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecTimeShiftCorrect*)
   {
      ::KoaRecTimeShiftCorrect *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecTimeShiftCorrect >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecTimeShiftCorrect", ::KoaRecTimeShiftCorrect::Class_Version(), "", 214,
                  typeid(::KoaRecTimeShiftCorrect), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecTimeShiftCorrect::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecTimeShiftCorrect) );
      instance.SetNew(&new_KoaRecTimeShiftCorrect);
      instance.SetNewArray(&newArray_KoaRecTimeShiftCorrect);
      instance.SetDelete(&delete_KoaRecTimeShiftCorrect);
      instance.SetDeleteArray(&deleteArray_KoaRecTimeShiftCorrect);
      instance.SetDestructor(&destruct_KoaRecTimeShiftCorrect);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecTimeShiftCorrect*)
   {
      return GenerateInitInstanceLocal((::KoaRecTimeShiftCorrect*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecTimeShiftCorrect*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecTimeWalkCorrect(void *p = 0);
   static void *newArray_KoaRecTimeWalkCorrect(Long_t size, void *p);
   static void delete_KoaRecTimeWalkCorrect(void *p);
   static void deleteArray_KoaRecTimeWalkCorrect(void *p);
   static void destruct_KoaRecTimeWalkCorrect(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecTimeWalkCorrect*)
   {
      ::KoaRecTimeWalkCorrect *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecTimeWalkCorrect >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecTimeWalkCorrect", ::KoaRecTimeWalkCorrect::Class_Version(), "", 310,
                  typeid(::KoaRecTimeWalkCorrect), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecTimeWalkCorrect::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecTimeWalkCorrect) );
      instance.SetNew(&new_KoaRecTimeWalkCorrect);
      instance.SetNewArray(&newArray_KoaRecTimeWalkCorrect);
      instance.SetDelete(&delete_KoaRecTimeWalkCorrect);
      instance.SetDeleteArray(&deleteArray_KoaRecTimeWalkCorrect);
      instance.SetDestructor(&destruct_KoaRecTimeWalkCorrect);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecTimeWalkCorrect*)
   {
      return GenerateInitInstanceLocal((::KoaRecTimeWalkCorrect*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecTimeWalkCorrect*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecRearRecon(void *p = 0);
   static void *newArray_KoaRecRearRecon(Long_t size, void *p);
   static void delete_KoaRecRearRecon(void *p);
   static void deleteArray_KoaRecRearRecon(void *p);
   static void destruct_KoaRecRearRecon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecRearRecon*)
   {
      ::KoaRecRearRecon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecRearRecon >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecRearRecon", ::KoaRecRearRecon::Class_Version(), "", 394,
                  typeid(::KoaRecRearRecon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecRearRecon::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecRearRecon) );
      instance.SetNew(&new_KoaRecRearRecon);
      instance.SetNewArray(&newArray_KoaRecRearRecon);
      instance.SetDelete(&delete_KoaRecRearRecon);
      instance.SetDeleteArray(&deleteArray_KoaRecRearRecon);
      instance.SetDestructor(&destruct_KoaRecRearRecon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecRearRecon*)
   {
      return GenerateInitInstanceLocal((::KoaRecRearRecon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecRearRecon*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaFwdRecon(void *p = 0);
   static void *newArray_KoaFwdRecon(Long_t size, void *p);
   static void delete_KoaFwdRecon(void *p);
   static void deleteArray_KoaFwdRecon(void *p);
   static void destruct_KoaFwdRecon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaFwdRecon*)
   {
      ::KoaFwdRecon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaFwdRecon >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaFwdRecon", ::KoaFwdRecon::Class_Version(), "", 456,
                  typeid(::KoaFwdRecon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaFwdRecon::Dictionary, isa_proxy, 4,
                  sizeof(::KoaFwdRecon) );
      instance.SetNew(&new_KoaFwdRecon);
      instance.SetNewArray(&newArray_KoaFwdRecon);
      instance.SetDelete(&delete_KoaFwdRecon);
      instance.SetDeleteArray(&deleteArray_KoaFwdRecon);
      instance.SetDestructor(&destruct_KoaFwdRecon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaFwdRecon*)
   {
      return GenerateInitInstanceLocal((::KoaFwdRecon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaFwdRecon*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecClusterCollect(void *p = 0);
   static void *newArray_KoaRecClusterCollect(Long_t size, void *p);
   static void delete_KoaRecClusterCollect(void *p);
   static void deleteArray_KoaRecClusterCollect(void *p);
   static void destruct_KoaRecClusterCollect(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecClusterCollect*)
   {
      ::KoaRecClusterCollect *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecClusterCollect >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecClusterCollect", ::KoaRecClusterCollect::Class_Version(), "", 520,
                  typeid(::KoaRecClusterCollect), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecClusterCollect::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecClusterCollect) );
      instance.SetNew(&new_KoaRecClusterCollect);
      instance.SetNewArray(&newArray_KoaRecClusterCollect);
      instance.SetDelete(&delete_KoaRecClusterCollect);
      instance.SetDeleteArray(&deleteArray_KoaRecClusterCollect);
      instance.SetDestructor(&destruct_KoaRecClusterCollect);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecClusterCollect*)
   {
      return GenerateInitInstanceLocal((::KoaRecClusterCollect*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecClusterCollect*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecClusterSeedFilter(void *p = 0);
   static void *newArray_KoaRecClusterSeedFilter(Long_t size, void *p);
   static void delete_KoaRecClusterSeedFilter(void *p);
   static void deleteArray_KoaRecClusterSeedFilter(void *p);
   static void destruct_KoaRecClusterSeedFilter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecClusterSeedFilter*)
   {
      ::KoaRecClusterSeedFilter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecClusterSeedFilter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecClusterSeedFilter", ::KoaRecClusterSeedFilter::Class_Version(), "", 607,
                  typeid(::KoaRecClusterSeedFilter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecClusterSeedFilter::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecClusterSeedFilter) );
      instance.SetNew(&new_KoaRecClusterSeedFilter);
      instance.SetNewArray(&newArray_KoaRecClusterSeedFilter);
      instance.SetDelete(&delete_KoaRecClusterSeedFilter);
      instance.SetDeleteArray(&deleteArray_KoaRecClusterSeedFilter);
      instance.SetDestructor(&destruct_KoaRecClusterSeedFilter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecClusterSeedFilter*)
   {
      return GenerateInitInstanceLocal((::KoaRecClusterSeedFilter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecClusterSeedFilter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaRecClusterThresholdFilter(void *p = 0);
   static void *newArray_KoaRecClusterThresholdFilter(Long_t size, void *p);
   static void delete_KoaRecClusterThresholdFilter(void *p);
   static void deleteArray_KoaRecClusterThresholdFilter(void *p);
   static void destruct_KoaRecClusterThresholdFilter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaRecClusterThresholdFilter*)
   {
      ::KoaRecClusterThresholdFilter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaRecClusterThresholdFilter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaRecClusterThresholdFilter", ::KoaRecClusterThresholdFilter::Class_Version(), "", 698,
                  typeid(::KoaRecClusterThresholdFilter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaRecClusterThresholdFilter::Dictionary, isa_proxy, 4,
                  sizeof(::KoaRecClusterThresholdFilter) );
      instance.SetNew(&new_KoaRecClusterThresholdFilter);
      instance.SetNewArray(&newArray_KoaRecClusterThresholdFilter);
      instance.SetDelete(&delete_KoaRecClusterThresholdFilter);
      instance.SetDeleteArray(&deleteArray_KoaRecClusterThresholdFilter);
      instance.SetDestructor(&destruct_KoaRecClusterThresholdFilter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaRecClusterThresholdFilter*)
   {
      return GenerateInitInstanceLocal((::KoaRecClusterThresholdFilter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaRecClusterThresholdFilter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr KoaRecNoiseFilter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecNoiseFilter::Class_Name()
{
   return "KoaRecNoiseFilter";
}

//______________________________________________________________________________
const char *KoaRecNoiseFilter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecNoiseFilter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecNoiseFilter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecNoiseFilter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecNoiseFilter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecNoiseFilter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecNoiseFilter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecNoiseFilter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecEnergyRecon::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecEnergyRecon::Class_Name()
{
   return "KoaRecEnergyRecon";
}

//______________________________________________________________________________
const char *KoaRecEnergyRecon::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecEnergyRecon*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecEnergyRecon::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecEnergyRecon*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecEnergyRecon::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecEnergyRecon*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecEnergyRecon::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecEnergyRecon*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecTimeShiftCorrect::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecTimeShiftCorrect::Class_Name()
{
   return "KoaRecTimeShiftCorrect";
}

//______________________________________________________________________________
const char *KoaRecTimeShiftCorrect::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeShiftCorrect*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecTimeShiftCorrect::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeShiftCorrect*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecTimeShiftCorrect::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeShiftCorrect*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecTimeShiftCorrect::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeShiftCorrect*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecTimeWalkCorrect::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecTimeWalkCorrect::Class_Name()
{
   return "KoaRecTimeWalkCorrect";
}

//______________________________________________________________________________
const char *KoaRecTimeWalkCorrect::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeWalkCorrect*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecTimeWalkCorrect::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeWalkCorrect*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecTimeWalkCorrect::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeWalkCorrect*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecTimeWalkCorrect::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecTimeWalkCorrect*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecRearRecon::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecRearRecon::Class_Name()
{
   return "KoaRecRearRecon";
}

//______________________________________________________________________________
const char *KoaRecRearRecon::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecRearRecon*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecRearRecon::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecRearRecon*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecRearRecon::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecRearRecon*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecRearRecon::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecRearRecon*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaFwdRecon::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaFwdRecon::Class_Name()
{
   return "KoaFwdRecon";
}

//______________________________________________________________________________
const char *KoaFwdRecon::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdRecon*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaFwdRecon::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdRecon*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaFwdRecon::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdRecon*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaFwdRecon::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdRecon*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecClusterCollect::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecClusterCollect::Class_Name()
{
   return "KoaRecClusterCollect";
}

//______________________________________________________________________________
const char *KoaRecClusterCollect::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecClusterCollect*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecClusterCollect::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecClusterCollect*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecClusterCollect::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecClusterCollect*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecClusterCollect::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecClusterCollect*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecClusterSeedFilter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecClusterSeedFilter::Class_Name()
{
   return "KoaRecClusterSeedFilter";
}

//______________________________________________________________________________
const char *KoaRecClusterSeedFilter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecClusterSeedFilter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecClusterSeedFilter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecClusterSeedFilter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecClusterSeedFilter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecClusterSeedFilter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecClusterSeedFilter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecClusterSeedFilter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaRecClusterThresholdFilter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaRecClusterThresholdFilter::Class_Name()
{
   return "KoaRecClusterThresholdFilter";
}

//______________________________________________________________________________
const char *KoaRecClusterThresholdFilter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecClusterThresholdFilter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaRecClusterThresholdFilter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaRecClusterThresholdFilter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaRecClusterThresholdFilter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecClusterThresholdFilter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaRecClusterThresholdFilter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaRecClusterThresholdFilter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void KoaRecNoiseFilter::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecNoiseFilter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecNoiseFilter::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecNoiseFilter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecNoiseFilter(void *p) {
      return  p ? new(p) ::KoaRecNoiseFilter : new ::KoaRecNoiseFilter;
   }
   static void *newArray_KoaRecNoiseFilter(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecNoiseFilter[nElements] : new ::KoaRecNoiseFilter[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecNoiseFilter(void *p) {
      delete ((::KoaRecNoiseFilter*)p);
   }
   static void deleteArray_KoaRecNoiseFilter(void *p) {
      delete [] ((::KoaRecNoiseFilter*)p);
   }
   static void destruct_KoaRecNoiseFilter(void *p) {
      typedef ::KoaRecNoiseFilter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecNoiseFilter

//______________________________________________________________________________
void KoaRecEnergyRecon::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecEnergyRecon.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecEnergyRecon::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecEnergyRecon::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecEnergyRecon(void *p) {
      return  p ? new(p) ::KoaRecEnergyRecon : new ::KoaRecEnergyRecon;
   }
   static void *newArray_KoaRecEnergyRecon(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecEnergyRecon[nElements] : new ::KoaRecEnergyRecon[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecEnergyRecon(void *p) {
      delete ((::KoaRecEnergyRecon*)p);
   }
   static void deleteArray_KoaRecEnergyRecon(void *p) {
      delete [] ((::KoaRecEnergyRecon*)p);
   }
   static void destruct_KoaRecEnergyRecon(void *p) {
      typedef ::KoaRecEnergyRecon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecEnergyRecon

//______________________________________________________________________________
void KoaRecTimeShiftCorrect::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecTimeShiftCorrect.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecTimeShiftCorrect::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecTimeShiftCorrect::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecTimeShiftCorrect(void *p) {
      return  p ? new(p) ::KoaRecTimeShiftCorrect : new ::KoaRecTimeShiftCorrect;
   }
   static void *newArray_KoaRecTimeShiftCorrect(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecTimeShiftCorrect[nElements] : new ::KoaRecTimeShiftCorrect[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecTimeShiftCorrect(void *p) {
      delete ((::KoaRecTimeShiftCorrect*)p);
   }
   static void deleteArray_KoaRecTimeShiftCorrect(void *p) {
      delete [] ((::KoaRecTimeShiftCorrect*)p);
   }
   static void destruct_KoaRecTimeShiftCorrect(void *p) {
      typedef ::KoaRecTimeShiftCorrect current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecTimeShiftCorrect

//______________________________________________________________________________
void KoaRecTimeWalkCorrect::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecTimeWalkCorrect.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecTimeWalkCorrect::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecTimeWalkCorrect::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecTimeWalkCorrect(void *p) {
      return  p ? new(p) ::KoaRecTimeWalkCorrect : new ::KoaRecTimeWalkCorrect;
   }
   static void *newArray_KoaRecTimeWalkCorrect(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecTimeWalkCorrect[nElements] : new ::KoaRecTimeWalkCorrect[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecTimeWalkCorrect(void *p) {
      delete ((::KoaRecTimeWalkCorrect*)p);
   }
   static void deleteArray_KoaRecTimeWalkCorrect(void *p) {
      delete [] ((::KoaRecTimeWalkCorrect*)p);
   }
   static void destruct_KoaRecTimeWalkCorrect(void *p) {
      typedef ::KoaRecTimeWalkCorrect current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecTimeWalkCorrect

//______________________________________________________________________________
void KoaRecRearRecon::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecRearRecon.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecRearRecon::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecRearRecon::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecRearRecon(void *p) {
      return  p ? new(p) ::KoaRecRearRecon : new ::KoaRecRearRecon;
   }
   static void *newArray_KoaRecRearRecon(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecRearRecon[nElements] : new ::KoaRecRearRecon[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecRearRecon(void *p) {
      delete ((::KoaRecRearRecon*)p);
   }
   static void deleteArray_KoaRecRearRecon(void *p) {
      delete [] ((::KoaRecRearRecon*)p);
   }
   static void destruct_KoaRecRearRecon(void *p) {
      typedef ::KoaRecRearRecon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecRearRecon

//______________________________________________________________________________
void KoaFwdRecon::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaFwdRecon.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaFwdRecon::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaFwdRecon::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaFwdRecon(void *p) {
      return  p ? new(p) ::KoaFwdRecon : new ::KoaFwdRecon;
   }
   static void *newArray_KoaFwdRecon(Long_t nElements, void *p) {
      return p ? new(p) ::KoaFwdRecon[nElements] : new ::KoaFwdRecon[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaFwdRecon(void *p) {
      delete ((::KoaFwdRecon*)p);
   }
   static void deleteArray_KoaFwdRecon(void *p) {
      delete [] ((::KoaFwdRecon*)p);
   }
   static void destruct_KoaFwdRecon(void *p) {
      typedef ::KoaFwdRecon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaFwdRecon

//______________________________________________________________________________
void KoaRecClusterCollect::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecClusterCollect.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecClusterCollect::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecClusterCollect::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecClusterCollect(void *p) {
      return  p ? new(p) ::KoaRecClusterCollect : new ::KoaRecClusterCollect;
   }
   static void *newArray_KoaRecClusterCollect(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecClusterCollect[nElements] : new ::KoaRecClusterCollect[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecClusterCollect(void *p) {
      delete ((::KoaRecClusterCollect*)p);
   }
   static void deleteArray_KoaRecClusterCollect(void *p) {
      delete [] ((::KoaRecClusterCollect*)p);
   }
   static void destruct_KoaRecClusterCollect(void *p) {
      typedef ::KoaRecClusterCollect current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecClusterCollect

//______________________________________________________________________________
void KoaRecClusterSeedFilter::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecClusterSeedFilter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecClusterSeedFilter::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecClusterSeedFilter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecClusterSeedFilter(void *p) {
      return  p ? new(p) ::KoaRecClusterSeedFilter : new ::KoaRecClusterSeedFilter;
   }
   static void *newArray_KoaRecClusterSeedFilter(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecClusterSeedFilter[nElements] : new ::KoaRecClusterSeedFilter[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecClusterSeedFilter(void *p) {
      delete ((::KoaRecClusterSeedFilter*)p);
   }
   static void deleteArray_KoaRecClusterSeedFilter(void *p) {
      delete [] ((::KoaRecClusterSeedFilter*)p);
   }
   static void destruct_KoaRecClusterSeedFilter(void *p) {
      typedef ::KoaRecClusterSeedFilter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecClusterSeedFilter

//______________________________________________________________________________
void KoaRecClusterThresholdFilter::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaRecClusterThresholdFilter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaRecClusterThresholdFilter::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaRecClusterThresholdFilter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaRecClusterThresholdFilter(void *p) {
      return  p ? new(p) ::KoaRecClusterThresholdFilter : new ::KoaRecClusterThresholdFilter;
   }
   static void *newArray_KoaRecClusterThresholdFilter(Long_t nElements, void *p) {
      return p ? new(p) ::KoaRecClusterThresholdFilter[nElements] : new ::KoaRecClusterThresholdFilter[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaRecClusterThresholdFilter(void *p) {
      delete ((::KoaRecClusterThresholdFilter*)p);
   }
   static void deleteArray_KoaRecClusterThresholdFilter(void *p) {
      delete [] ((::KoaRecClusterThresholdFilter*)p);
   }
   static void destruct_KoaRecClusterThresholdFilter(void *p) {
      typedef ::KoaRecClusterThresholdFilter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaRecClusterThresholdFilter

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

namespace {
  void TriggerDictionaryInitialization_G__KoaReconDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/home/yong/fairroot/v18_jun19/include",
"/home/yong/src/KoalaSoft/reconstruction/koala",
"/home/yong/src/KoalaSoft/tools",
"/home/yong/src/KoalaSoft/data",
"/home/yong/src/KoalaSoft/detectors/recoil/simple",
"/home/yong/src/KoalaSoft/detectors/scint-forward",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/src/KoalaSoft/build_jens/reconstruction/koala/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__KoaReconDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class KoaRecNoiseFilter;
class KoaRecEnergyRecon;
class KoaRecTimeShiftCorrect;
class KoaRecTimeWalkCorrect;
class KoaRecRearRecon;
class KoaFwdRecon;
class KoaRecClusterCollect;
class KoaRecClusterSeedFilter;
class KoaRecClusterThresholdFilter;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__KoaReconDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#ifndef KOARECNOISEFILTER_H
#define KOARECNOISEFILTER_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <map>
#include <string>

class TClonesArray;
class KoaRecDigi;
class KoaMapEncoder;

using namespace KoaUtility;

/* Filter out digis with a threshold above electronic noise level for the recoil
 * front channels (based on ADC pedestal)
 *
 * Input parameters:
 * 1. Pedestal parameter file
 * 2. Threshold: fThresh*PedSigma + PedMean
 */
class KoaRecNoiseFilter : public FairTask
{
public:
  /** Default constructor **/
  KoaRecNoiseFilter();

  /** Destructor **/
  ~KoaRecNoiseFilter();


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

  void SetPedestalFile(const char* name) {
    fPedestalFileName = name;
  }
  void SetThreshold(double thresh) {
    fThresh = thresh;
  }

private:
  // Input digit branch name
  std::string fInputName = "";
  // Output digit branch name
  std::string fOutputName = "";
  // Flag indicate save output branch to file or in memory
  bool fSaveOutput = false;

  /** Input array from previous already existing data level **/
  TClonesArray* fInputDigis = nullptr;
  /** Output array to  new data level**/
  TClonesArray* fOutputDigis = nullptr;

  // Noise parameter
  std::string fPedestalFileName = "";
  double fThresh = 5.;
  ValueContainer<double> fPedThresh;

  KoaRecNoiseFilter(const KoaRecNoiseFilter&);
  KoaRecNoiseFilter operator=(const KoaRecNoiseFilter&);

  ClassDef(KoaRecNoiseFilter,1);
};


#endif
#ifndef KOARECENERGYRECON_H
#define KOARECENERGYRECON_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <map>
#include <string>

class TClonesArray;
class KoaRecDigi;

using namespace KoaUtility;

/* Transfer ADC counts of recoil front side channels to energy in keV.
 * In the same time, the digis which has energy smaller than the threshold will
 * be filtered out.
 *
 * Input parameters:
 * 1. ADC calibration parameter file
 * 2. Energy threshold
 */
class KoaRecEnergyRecon : public FairTask
{
public:
  /** Default constructor **/
  KoaRecEnergyRecon();

  /** Destructor **/
  ~KoaRecEnergyRecon();


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

  void SetAdcParaFile(const char* name) {
    fAdcParaFile = name;
  }

  // set threshold in unit of keV
  void SetThreshold(double thresh) {
    fThreshold = thresh;
  }

private:
  // Input digit branch name
  std::string fInputName = "";
  // Output digit branch name
  std::string fOutputName = "";
  // Flag indicate save output branch to file or in memory
  bool fSaveOutput = false;

  /** Input array from previous already existing data level **/
  TClonesArray* fInputDigis = nullptr;
  /** Output array to  new data level**/
  TClonesArray* fOutputDigis = nullptr;

  // Noise parameter
  std::string fAdcParaFile = "";
  double fThreshold = 0.;
  ValueContainer<double> fP0;
  ValueContainer<double> fP1;

  KoaRecEnergyRecon(const KoaRecEnergyRecon&);
  KoaRecEnergyRecon operator=(const KoaRecEnergyRecon&);

  ClassDef(KoaRecEnergyRecon,1);
};

#endif
#ifndef KOARECTIMESHIFTCORRECT_H
#define KOARECTIMESHIFTCORRECT_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <map>
#include <string>

class TClonesArray;
class KoaRecDigi;

using namespace KoaUtility;

/* Correct the time offset between TDC channels of recoil front channels.
 *
 * Input parameters:
 * 1. TDC time shift parameter file
 */
class KoaRecTimeShiftCorrect : public FairTask
{
public:
  /** Default constructor **/
  KoaRecTimeShiftCorrect();

  /** Destructor **/
  ~KoaRecTimeShiftCorrect();


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

  void SetTdcParaFile(const char* name) {
    fTdcParaFile = name;
  }

  void SetTdcParaName(const char* name) {
    fTdcParaName = name;
  }

private:
  void CalcTimeShift(int ref_ch = 1);

private:
  // Input digit branch name
  std::string fInputName = "";
  // Output digit branch name
  std::string fOutputName = "";
  // Flag indicate save output branch to file or in memory
  bool fSaveOutput = false;

  /** Input array from previous already existing data level **/
  TClonesArray* fInputDigis = nullptr;
  /** Output array to  new data level**/
  TClonesArray* fOutputDigis = nullptr;

  // Noise parameter
  std::string fTdcParaFile = "";
  std::string fTdcParaName = "Mean";
  ValueContainer<double> fMean;
  ValueContainer<double> fTimeShift;

  KoaRecTimeShiftCorrect(const KoaRecTimeShiftCorrect&);
  KoaRecTimeShiftCorrect operator=(const KoaRecTimeShiftCorrect&);

  ClassDef(KoaRecTimeShiftCorrect,1);
};


#endif
#ifndef KOARECTIMEWALKCORRECT_H
#define KOARECTIMEWALKCORRECT_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <map>
#include <string>

class TClonesArray;
class KoaRecDigi;

using namespace KoaUtility;

/* Correct the time walk effect based on ADC value
 *
 * Input parameters:
 * 1. TDC time walk parameter file
 */
class KoaRecTimeWalkCorrect : public FairTask
{
public:
  /** Default constructor **/
  KoaRecTimeWalkCorrect();

  /** Destructor **/
  ~KoaRecTimeWalkCorrect();


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

  void SetTdcParaFile(const char* name) {
    fTdcParaFile = name;
  }

  void SetTdcParaName(const char* name) {
    fTdcParaName = name;
  }

private:
  // Input digit branch name
  std::string fInputName = "";
  // Output digit branch name
  std::string fOutputName = "";
  // Flag indicate save output branch to file or in memory
  bool fSaveOutput = false;

  /** Input array from previous already existing data level **/
  TClonesArray* fInputDigis = nullptr;
  /** Output array to  new data level**/
  TClonesArray* fOutputDigis = nullptr;

  // Noise parameter
  std::string fTdcParaFile = "";
  std::string fTdcParaName = "p0";
  ValueContainer<double> fP0;

  KoaRecTimeWalkCorrect(const KoaRecTimeWalkCorrect&);
  KoaRecTimeWalkCorrect operator=(const KoaRecTimeWalkCorrect&);

  ClassDef(KoaRecTimeWalkCorrect,1);
};



#endif
#ifndef KOA_RECREARRECON_H
#define KOA_RECREARRECON_H

#include "FairTask.h"

class TClonesArray;

/* A simple bridge to tranfer Recoil Rear side  digis from Raw file to reconstructed file without any changes.
 */
class KoaRecRearRecon : public FairTask
{
public:
  /** Default constructor **/
  KoaRecRearRecon();

  /** Destructor **/
  ~KoaRecRearRecon();

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

private:
  // Input digit branch name
  std::string fInputName = "KoaRecRearDigi";
  // Output digit branch name
  std::string fOutputName = "KoaRecRearDigi";

  /** Input array from previous already existing data level **/
  TClonesArray* fInputDigis = nullptr;

  KoaRecRearRecon(const KoaRecRearRecon&);
  KoaRecRearRecon operator=(const KoaRecRearRecon&);

  ClassDef(KoaRecRearRecon,1);
};


#endif
#ifndef KOA_FWDRECON_H
#define KOA_FWDRECON_H

#include "FairTask.h"

class TClonesArray;

/* A simple bridge to tranfer Fwd digis from Raw file to reconstructed file without any changes.
 */
class KoaFwdRecon : public FairTask
{
public:
  /** Default constructor **/
  KoaFwdRecon();

  /** Destructor **/
  ~KoaFwdRecon();

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

private:
  // Input digit branch name
  std::string fInputName = "KoaFwdDigi";
  // Output digit branch name
  std::string fOutputName = "KoaFwdDigi";

  /** Input array from previous already existing data level **/
  TClonesArray* fInputDigis = nullptr;

  KoaFwdRecon(const KoaFwdRecon&);
  KoaFwdRecon operator=(const KoaFwdRecon&);

  ClassDef(KoaFwdRecon,1);
};


#endif
#ifndef KOARECCLUSTERCOLLECT_H
#define KOARECCLUSTERCOLLECT_H

#include "FairTask.h"
#include <string>

class TClonesArray;
class KoaMapEncoder;

/* Clustering of Recoil strip digis
 */
class KoaRecClusterCollect : public FairTask
{
public:
  /** Default constructor **/
  KoaRecClusterCollect();

  /** Destructor **/
  ~KoaRecClusterCollect();


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
  void SetOutputClusterName(const char* name) {
    fOutputName = name;
  }
  void SaveOutputCluster(bool flag = true) {
    fSaveOutput = flag;
  }

private:
  // Input digit branch name
  std::string fInputName = "";
  // Output digit branch name
  std::string fOutputName = "";
  // Flag indicate save output branch to file or in memory
  bool fSaveOutput = true;

  /** Input array from previous already existing data level **/
  TClonesArray* fInputDigis = nullptr;
  /** Output array to  new data level**/
  TClonesArray* fOutputClusters = nullptr;

  // Map Encoder
  KoaMapEncoder *fEncoder;

  KoaRecClusterCollect(const KoaRecClusterCollect&);
  KoaRecClusterCollect operator=(const KoaRecClusterCollect&);

  ClassDef(KoaRecClusterCollect,1);
};

#endif
#ifndef KOAREC_CLUSTERSEEDFILTER_H
#define KOAREC_CLUSTERSEEDFILTER_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <map>
#include <string>

class TClonesArray;
class KoaRecDigi;
class KoaMapEncoder;

using namespace KoaUtility;

/* Collect digis into cluster first.
 * Then, filter out clusters in which the max-energy digi is smaller than threshold
 * The digis in the the remaining clusters are pushed into the output TClonesArray
 * for usage in later tasks.
 *
 * Input parameters:
 * 1. Pedestal parameter file
 * 2. Threshold: fThresh*PedSigma + PedMean
 */

class KoaRecClusterSeedFilter : public FairTask
{
public:
  /** Default constructor **/
  KoaRecClusterSeedFilter();

  /** Destructor **/
  ~KoaRecClusterSeedFilter();


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

  void SetPedestalFile(const char* name) {
    fPedestalFileName = name;
  }
  void SetThreshold(double thresh) {
    fThresh = thresh;
  }

private:
  // Input digit branch name
  std::string fInputName = "";
  // Output digit branch name
  std::string fOutputName = "";
  // Flag indicate save output branch to file or in memory
  bool fSaveOutput = false;

  /** Input array from previous already existing data level **/
  TClonesArray* fInputDigis = nullptr;
  /** Output array to  new data level**/
  TClonesArray* fOutputDigis = nullptr;
  /** Buffer array for intermediate clustesrs **/
  TClonesArray* fClusters = nullptr;

  // Noise parameter
  std::string fPedestalFileName = "";
  double fThresh = 3.;
  ValueContainer<double> fPedThresh;

  // Map Encoder
  KoaMapEncoder *fEncoder;

  KoaRecClusterSeedFilter(const KoaRecClusterSeedFilter&);
  KoaRecClusterSeedFilter operator=(const KoaRecClusterSeedFilter&);

  ClassDef(KoaRecClusterSeedFilter,1);
};


#endif
#ifndef KOAREC_CLUSTERTHRESHOLDFILTER_H
#define KOAREC_CLUSTERTHRESHOLDFILTER_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <string>

class TClonesArray;

using namespace KoaUtility;

/* Filter out clusters which have energy below threshold
 */
class KoaRecClusterThresholdFilter : public FairTask
{
public:
  /** Default constructor **/
  KoaRecClusterThresholdFilter();

  /** Destructor **/
  ~KoaRecClusterThresholdFilter();


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
  void SetInputClusterName(const char* name) {
    fInputName = name;
  }
  void SetOutputClusterName(const char* name) {
    fOutputName = name;
  }
  void SaveOutputCluster(bool flag = true) {
    fSaveOutput = flag;
  }
  void SetPedestalFile(const char* name) {
    fPedestalFileName = name;
  }
  void SetAdcParaFile(const char* name) {
    fAdcParaFile = name;
  }
  // set threshold in pedestal sigma
  void SetThreshold(double thresh) {
    fThresh = thresh;
  }

private:
  // Input digit branch name
  std::string fInputName = "";
  // Output digit branch name
  std::string fOutputName = "";
  // Flag indicate save output branch to file or in memory
  bool fSaveOutput = true;

  /** Input array from previous already existing data level **/
  TClonesArray* fInputClusters = nullptr;
  /** Output array to  new data level**/
  TClonesArray* fOutputClusters = nullptr;

  // Noise parameter in ADC
  std::string fPedestalFileName = "";

  // adc->E parameter
  std::string fAdcParaFile = "";

  ValueContainer<double> fNoiseThresh;
  double fThresh = 5.;

  KoaRecClusterThresholdFilter(const KoaRecClusterThresholdFilter&);
  KoaRecClusterThresholdFilter operator=(const KoaRecClusterThresholdFilter&);

  ClassDef(KoaRecClusterThresholdFilter,1);
};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"KoaFwdRecon", payloadCode, "@",
"KoaRecClusterCollect", payloadCode, "@",
"KoaRecClusterSeedFilter", payloadCode, "@",
"KoaRecClusterThresholdFilter", payloadCode, "@",
"KoaRecEnergyRecon", payloadCode, "@",
"KoaRecNoiseFilter", payloadCode, "@",
"KoaRecRearRecon", payloadCode, "@",
"KoaRecTimeShiftCorrect", payloadCode, "@",
"KoaRecTimeWalkCorrect", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__KoaReconDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__KoaReconDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__KoaReconDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__KoaReconDict() {
  TriggerDictionaryInitialization_G__KoaReconDict_Impl();
}
