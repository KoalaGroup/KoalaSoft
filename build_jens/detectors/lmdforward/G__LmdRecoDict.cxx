// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_jensdIdetectorsdIlmdforwarddIG__LmdRecoDict

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
#include "LmdReco/PndLmdPixelClusterTask.h"
#include "LmdReco/KoaPixelClusterTask.h"
#include "LmdReco/PndLmdHitMergeTask.h"
#include "LmdReco/KoaHitMergeTask.h"
#include "LmdReco/PndLmdSimplePixelClusterFinder.h"
#include "LmdReco/KoaSimplePixelClusterFinder.h"
#include "LmdReco/PndLmdChargeWeightedPixelMapping.h"
#include "LmdReco/KoaChargeWeightedPixelMapping.h"
#include "LmdReco/PndSdsMergedHit.h"
#include "LmdReco/PndSdsCell.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_PndLmdPixelClusterTask(void *p = 0);
   static void *newArray_PndLmdPixelClusterTask(Long_t size, void *p);
   static void delete_PndLmdPixelClusterTask(void *p);
   static void deleteArray_PndLmdPixelClusterTask(void *p);
   static void destruct_PndLmdPixelClusterTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdPixelClusterTask*)
   {
      ::PndLmdPixelClusterTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdPixelClusterTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdPixelClusterTask", ::PndLmdPixelClusterTask::Class_Version(), "", 18,
                  typeid(::PndLmdPixelClusterTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdPixelClusterTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdPixelClusterTask) );
      instance.SetNew(&new_PndLmdPixelClusterTask);
      instance.SetNewArray(&newArray_PndLmdPixelClusterTask);
      instance.SetDelete(&delete_PndLmdPixelClusterTask);
      instance.SetDeleteArray(&deleteArray_PndLmdPixelClusterTask);
      instance.SetDestructor(&destruct_PndLmdPixelClusterTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdPixelClusterTask*)
   {
      return GenerateInitInstanceLocal((::PndLmdPixelClusterTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdPixelClusterTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaPixelClusterTask(void *p = 0);
   static void *newArray_KoaPixelClusterTask(Long_t size, void *p);
   static void delete_KoaPixelClusterTask(void *p);
   static void deleteArray_KoaPixelClusterTask(void *p);
   static void destruct_KoaPixelClusterTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaPixelClusterTask*)
   {
      ::KoaPixelClusterTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaPixelClusterTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaPixelClusterTask", ::KoaPixelClusterTask::Class_Version(), "", 57,
                  typeid(::KoaPixelClusterTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaPixelClusterTask::Dictionary, isa_proxy, 4,
                  sizeof(::KoaPixelClusterTask) );
      instance.SetNew(&new_KoaPixelClusterTask);
      instance.SetNewArray(&newArray_KoaPixelClusterTask);
      instance.SetDelete(&delete_KoaPixelClusterTask);
      instance.SetDeleteArray(&deleteArray_KoaPixelClusterTask);
      instance.SetDestructor(&destruct_KoaPixelClusterTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaPixelClusterTask*)
   {
      return GenerateInitInstanceLocal((::KoaPixelClusterTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaPixelClusterTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLmdHitMergeTask(void *p = 0);
   static void *newArray_PndLmdHitMergeTask(Long_t size, void *p);
   static void delete_PndLmdHitMergeTask(void *p);
   static void deleteArray_PndLmdHitMergeTask(void *p);
   static void destruct_PndLmdHitMergeTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdHitMergeTask*)
   {
      ::PndLmdHitMergeTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdHitMergeTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdHitMergeTask", ::PndLmdHitMergeTask::Class_Version(), "", 100,
                  typeid(::PndLmdHitMergeTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdHitMergeTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdHitMergeTask) );
      instance.SetNew(&new_PndLmdHitMergeTask);
      instance.SetNewArray(&newArray_PndLmdHitMergeTask);
      instance.SetDelete(&delete_PndLmdHitMergeTask);
      instance.SetDeleteArray(&deleteArray_PndLmdHitMergeTask);
      instance.SetDestructor(&destruct_PndLmdHitMergeTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdHitMergeTask*)
   {
      return GenerateInitInstanceLocal((::PndLmdHitMergeTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdHitMergeTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaHitMergeTask(void *p = 0);
   static void *newArray_KoaHitMergeTask(Long_t size, void *p);
   static void delete_KoaHitMergeTask(void *p);
   static void deleteArray_KoaHitMergeTask(void *p);
   static void destruct_KoaHitMergeTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaHitMergeTask*)
   {
      ::KoaHitMergeTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaHitMergeTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaHitMergeTask", ::KoaHitMergeTask::Class_Version(), "", 146,
                  typeid(::KoaHitMergeTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaHitMergeTask::Dictionary, isa_proxy, 4,
                  sizeof(::KoaHitMergeTask) );
      instance.SetNew(&new_KoaHitMergeTask);
      instance.SetNewArray(&newArray_KoaHitMergeTask);
      instance.SetDelete(&delete_KoaHitMergeTask);
      instance.SetDeleteArray(&deleteArray_KoaHitMergeTask);
      instance.SetDestructor(&destruct_KoaHitMergeTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaHitMergeTask*)
   {
      return GenerateInitInstanceLocal((::KoaHitMergeTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaHitMergeTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsMergedHit(void *p = 0);
   static void *newArray_PndSdsMergedHit(Long_t size, void *p);
   static void delete_PndSdsMergedHit(void *p);
   static void deleteArray_PndSdsMergedHit(void *p);
   static void destruct_PndSdsMergedHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsMergedHit*)
   {
      ::PndSdsMergedHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsMergedHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsMergedHit", ::PndSdsMergedHit::Class_Version(), "", 282,
                  typeid(::PndSdsMergedHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsMergedHit::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsMergedHit) );
      instance.SetNew(&new_PndSdsMergedHit);
      instance.SetNewArray(&newArray_PndSdsMergedHit);
      instance.SetDelete(&delete_PndSdsMergedHit);
      instance.SetDeleteArray(&deleteArray_PndSdsMergedHit);
      instance.SetDestructor(&destruct_PndSdsMergedHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsMergedHit*)
   {
      return GenerateInitInstanceLocal((::PndSdsMergedHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsMergedHit*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsCell(void *p = 0);
   static void *newArray_PndSdsCell(Long_t size, void *p);
   static void delete_PndSdsCell(void *p);
   static void deleteArray_PndSdsCell(void *p);
   static void destruct_PndSdsCell(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsCell*)
   {
      ::PndSdsCell *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsCell >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsCell", ::PndSdsCell::Class_Version(), "", 370,
                  typeid(::PndSdsCell), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsCell::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsCell) );
      instance.SetNew(&new_PndSdsCell);
      instance.SetNewArray(&newArray_PndSdsCell);
      instance.SetDelete(&delete_PndSdsCell);
      instance.SetDeleteArray(&deleteArray_PndSdsCell);
      instance.SetDestructor(&destruct_PndSdsCell);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsCell*)
   {
      return GenerateInitInstanceLocal((::PndSdsCell*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsCell*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr PndLmdPixelClusterTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdPixelClusterTask::Class_Name()
{
   return "PndLmdPixelClusterTask";
}

//______________________________________________________________________________
const char *PndLmdPixelClusterTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdPixelClusterTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdPixelClusterTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdPixelClusterTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdPixelClusterTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdPixelClusterTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdPixelClusterTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdPixelClusterTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaPixelClusterTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaPixelClusterTask::Class_Name()
{
   return "KoaPixelClusterTask";
}

//______________________________________________________________________________
const char *KoaPixelClusterTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPixelClusterTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaPixelClusterTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPixelClusterTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaPixelClusterTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPixelClusterTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaPixelClusterTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPixelClusterTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLmdHitMergeTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdHitMergeTask::Class_Name()
{
   return "PndLmdHitMergeTask";
}

//______________________________________________________________________________
const char *PndLmdHitMergeTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdHitMergeTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdHitMergeTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdHitMergeTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdHitMergeTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdHitMergeTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdHitMergeTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdHitMergeTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaHitMergeTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaHitMergeTask::Class_Name()
{
   return "KoaHitMergeTask";
}

//______________________________________________________________________________
const char *KoaHitMergeTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaHitMergeTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaHitMergeTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaHitMergeTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaHitMergeTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaHitMergeTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaHitMergeTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaHitMergeTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsMergedHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsMergedHit::Class_Name()
{
   return "PndSdsMergedHit";
}

//______________________________________________________________________________
const char *PndSdsMergedHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsMergedHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsMergedHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsMergedHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsMergedHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsMergedHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsMergedHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsMergedHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsCell::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsCell::Class_Name()
{
   return "PndSdsCell";
}

//______________________________________________________________________________
const char *PndSdsCell::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsCell*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsCell::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsCell*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsCell::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsCell*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsCell::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsCell*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void PndLmdPixelClusterTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdPixelClusterTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdPixelClusterTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdPixelClusterTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdPixelClusterTask(void *p) {
      return  p ? new(p) ::PndLmdPixelClusterTask : new ::PndLmdPixelClusterTask;
   }
   static void *newArray_PndLmdPixelClusterTask(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdPixelClusterTask[nElements] : new ::PndLmdPixelClusterTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdPixelClusterTask(void *p) {
      delete ((::PndLmdPixelClusterTask*)p);
   }
   static void deleteArray_PndLmdPixelClusterTask(void *p) {
      delete [] ((::PndLmdPixelClusterTask*)p);
   }
   static void destruct_PndLmdPixelClusterTask(void *p) {
      typedef ::PndLmdPixelClusterTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdPixelClusterTask

//______________________________________________________________________________
void KoaPixelClusterTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaPixelClusterTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaPixelClusterTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaPixelClusterTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaPixelClusterTask(void *p) {
      return  p ? new(p) ::KoaPixelClusterTask : new ::KoaPixelClusterTask;
   }
   static void *newArray_KoaPixelClusterTask(Long_t nElements, void *p) {
      return p ? new(p) ::KoaPixelClusterTask[nElements] : new ::KoaPixelClusterTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaPixelClusterTask(void *p) {
      delete ((::KoaPixelClusterTask*)p);
   }
   static void deleteArray_KoaPixelClusterTask(void *p) {
      delete [] ((::KoaPixelClusterTask*)p);
   }
   static void destruct_KoaPixelClusterTask(void *p) {
      typedef ::KoaPixelClusterTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaPixelClusterTask

//______________________________________________________________________________
void PndLmdHitMergeTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdHitMergeTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdHitMergeTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdHitMergeTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdHitMergeTask(void *p) {
      return  p ? new(p) ::PndLmdHitMergeTask : new ::PndLmdHitMergeTask;
   }
   static void *newArray_PndLmdHitMergeTask(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdHitMergeTask[nElements] : new ::PndLmdHitMergeTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdHitMergeTask(void *p) {
      delete ((::PndLmdHitMergeTask*)p);
   }
   static void deleteArray_PndLmdHitMergeTask(void *p) {
      delete [] ((::PndLmdHitMergeTask*)p);
   }
   static void destruct_PndLmdHitMergeTask(void *p) {
      typedef ::PndLmdHitMergeTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdHitMergeTask

//______________________________________________________________________________
void KoaHitMergeTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaHitMergeTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaHitMergeTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaHitMergeTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaHitMergeTask(void *p) {
      return  p ? new(p) ::KoaHitMergeTask : new ::KoaHitMergeTask;
   }
   static void *newArray_KoaHitMergeTask(Long_t nElements, void *p) {
      return p ? new(p) ::KoaHitMergeTask[nElements] : new ::KoaHitMergeTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaHitMergeTask(void *p) {
      delete ((::KoaHitMergeTask*)p);
   }
   static void deleteArray_KoaHitMergeTask(void *p) {
      delete [] ((::KoaHitMergeTask*)p);
   }
   static void destruct_KoaHitMergeTask(void *p) {
      typedef ::KoaHitMergeTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaHitMergeTask

//______________________________________________________________________________
void PndSdsMergedHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsMergedHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsMergedHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsMergedHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsMergedHit(void *p) {
      return  p ? new(p) ::PndSdsMergedHit : new ::PndSdsMergedHit;
   }
   static void *newArray_PndSdsMergedHit(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsMergedHit[nElements] : new ::PndSdsMergedHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsMergedHit(void *p) {
      delete ((::PndSdsMergedHit*)p);
   }
   static void deleteArray_PndSdsMergedHit(void *p) {
      delete [] ((::PndSdsMergedHit*)p);
   }
   static void destruct_PndSdsMergedHit(void *p) {
      typedef ::PndSdsMergedHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsMergedHit

//______________________________________________________________________________
void PndSdsCell::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsCell.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsCell::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsCell::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsCell(void *p) {
      return  p ? new(p) ::PndSdsCell : new ::PndSdsCell;
   }
   static void *newArray_PndSdsCell(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsCell[nElements] : new ::PndSdsCell[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsCell(void *p) {
      delete ((::PndSdsCell*)p);
   }
   static void deleteArray_PndSdsCell(void *p) {
      delete [] ((::PndSdsCell*)p);
   }
   static void destruct_PndSdsCell(void *p) {
      typedef ::PndSdsCell current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsCell

namespace {
  void TriggerDictionaryInitialization_G__LmdRecoDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/home/yong/fairroot/v18_jun19/include",
"/home/yong/src/KoalaSoft/detectors/lmdforward",
"/home/yong/src/KoalaSoft/detectors/sds/SdsMC",
"/home/yong/src/KoalaSoft/detectors/sds/SdsDigi",
"/home/yong/src/KoalaSoft/detectors/sds/SdsReco",
"/home/yong/src/KoalaSoft/detectors/sds/SdsTools",
"/home/yong/src/KoalaSoft/detectors/sds/SdsFEModel",
"/home/yong/src/KoalaSoft/detectors/sds",
"/home/yong/src/KoalaSoft/data/SdsData",
"/home/yong/src/KoalaSoft/data",
"/home/yong/src/KoalaSoft/data/MCData",
"/home/yong/src/KoalaSoft/data/TrackData",
"/home/yong/src/KoalaSoft/detectors/lmdforward",
"/home/yong/src/KoalaSoft/detectors/detectors/recoil/full/koaDigi",
"/home/yong/src/KoalaSoft/tools",
"/home/yong/src/KoalaSoft/detectors/lmdforward/LmdDigi",
"/home/yong/src/KoalaSoft/detectors/lmdforward/LmdReco",
"/home/yong/src/KoalaSoft/detectors/lmdforward/LmdTrack",
"/home/yong/src/KoalaSoft/detectors/lmdforward/LmdTools",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include/TGeant3",
"/home/yong/fairroot/v18_jun19/include",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/src/KoalaSoft/build_jens/detectors/lmdforward/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__LmdRecoDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class PndLmdPixelClusterTask;
class KoaPixelClusterTask;
class PndLmdHitMergeTask;
class KoaHitMergeTask;
class PndSdsMergedHit;
class PndSdsCell;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__LmdRecoDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

#ifndef PNDLMDPIXELCLUSTERTASK_H
#define PNDLMDPIXELCLUSTERTASK_H

#include "PndSdsPixelClusterTask.h"
#include "TString.h"

class FairRun;
class FairRuntimeDb;

class PndLmdPixelClusterTask : public PndSdsPixelClusterTask {
  FairRun* ana;
  FairRuntimeDb* rtdb;

 public:
  /** Default constructor **/
  PndLmdPixelClusterTask();

  /** Destructor **/
  virtual ~PndLmdPixelClusterTask();

  virtual void SetParContainers();
  virtual void SetBranchNames();
  virtual void SetClusterFinder();
  virtual void SetBackMapping();
  virtual void SetBranchNames(TString inBranchname, TString outHitBranchname,
                              TString outClustBranchname, TString folderName);
  /** Virtual method Exec **/
  void Exec(Option_t* opt);
  void FinishEvent();

  InitStatus Init();
  ClassDef(PndLmdPixelClusterTask, 3);
};

#endif /* LMDCLUSTERTASK_H */
// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

#ifndef KOAPIXELCLUSTERTASK_H
#define KOAPIXELCLUSTERTASK_H

#include "PndSdsPixelClusterTask.h"
#include "TString.h"

class FairRun;
class FairRuntimeDb;

class KoaPixelClusterTask : public PndSdsPixelClusterTask {
  FairRun* ana;
  FairRuntimeDb* rtdb;

 public:
  /** Default constructor **/
  KoaPixelClusterTask();

  /** Destructor **/
  virtual ~KoaPixelClusterTask();

  virtual void SetParContainers();
  virtual void SetBranchNames();
  virtual void SetClusterFinder();
  virtual void SetBackMapping();
  virtual void SetBranchNames(TString inBranchname, TString outHitBranchname,
                              TString outClustBranchname, TString folderName);
  /** Virtual method Exec **/
  void Exec(Option_t* opt);
  void FinishEvent();

  InitStatus Init();
  ClassDef(KoaPixelClusterTask, 3);
};

#endif /* LMDCLUSTERTASK_H */
// -------------------------------------------------------------------------
// -----                 PndLmdHitMergeTask header file             -----
// -------------------------------------------------------------------------

#ifndef PNDLMDHITMERGETASK_H
#define PNDLMDHITMERGETASK_H

#include "FairTask.h"

#include <string>
#include <vector>

class TH2;
class TH1;
class TClonesArray;

class PndLmdHitMergeTask : public FairTask {
 public:
  /** Default constructor **/

  PndLmdHitMergeTask();
  PndLmdHitMergeTask(const char* name);

  /** Destructor **/
  virtual ~PndLmdHitMergeTask();

  /** Virtual method Init **/
  virtual InitStatus Init();

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

 protected:
  TClonesArray* fHitArray;        // Input array of PndSdsHits
  TClonesArray* fMergedHitArray;  // Output array of PndSdsHits

  TString fHitBranchName;

  TH2* hdxdy;
  TH1* hdz;

  ClassDef(PndLmdHitMergeTask, 0);
};

#endif /* PNDLMDHITMERGETASK_H */
// -------------------------------------------------------------------------
// -----                 KoaHitMergeTask header file             -----
// -------------------------------------------------------------------------

#ifndef KOAHITMERGETASK_H
#define KOAHITMERGETASK_H

#include "FairTask.h"

#include <string>
#include <vector>

class TH2;
class TH1;
class TClonesArray;

class KoaHitMergeTask : public FairTask {
 public:
  /** Default constructor **/

  KoaHitMergeTask();
  KoaHitMergeTask(const char* name);

  /** Destructor **/
  virtual ~KoaHitMergeTask();

  /** Virtual method Init **/
  virtual InitStatus Init();

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

 protected:
  TClonesArray* fHitArray;        // Input array of PndSdsHits
  TClonesArray* fMergedHitArray;  // Output array of PndSdsHits

  TString fHitBranchName;

  TH2* hdxdy;
  TH1* hdz;

  ClassDef(KoaHitMergeTask, 0);
};

#endif /* KOALAHITMERGETASK_H */
#ifndef PNDLMDSIMPLEPIXELCLUSTERFINDER_H
#define PNDLMDSIMPLEPIXELCLUSTERFINDER_H

#include "PndSdsSimplePixelClusterFinder.h"
/// PndLmdSimplePixelClusterFinder.h
/// Simple cluster finder for pixel detectors.
///
/// It takes the first hit in the DigiArray and moves it into a new cluster.
/// Then it looks through the remaining hits in the DigiArray if there are hits
/// which are in the area around the first hit and moves them into the cluster.
/// The radius is given by the first parameter.
/// Then it takes the new hits in the cluster and looks if there are other hits
/// which are in the range of these hits and moves them into the cluster, too.
/// This process is repeated until no hits around the cluster are found
/// The the first hit of the remaining DigiHits is taken to create a new hit and
/// the cluster search process is started again.

class PndLmdSimplePixelClusterFinder : public PndSdsSimplePixelClusterFinder {
 public:
  PndLmdSimplePixelClusterFinder(Int_t verbose = 0);
};
#endif
#ifndef KOASIMPLEPIXELCLUSTERFINDER_H
#define KOASIMPLEPIXELCLUSTERFINDER_H

#include "PndSdsSimplePixelClusterFinder.h"
/// PndLmdSimplePixelClusterFinder.h
/// Simple cluster finder for pixel detectors.
///
/// It takes the first hit in the DigiArray and moves it into a new cluster.
/// Then it looks through the remaining hits in the DigiArray if there are hits
/// which are in the area around the first hit and moves them into the cluster.
/// The radius is given by the first parameter.
/// Then it takes the new hits in the cluster and looks if there are other hits
/// which are in the range of these hits and moves them into the cluster, too.
/// This process is repeated until no hits around the cluster are found
/// The the first hit of the remaining DigiHits is taken to create a new hit and
/// the cluster search process is started again.

class KoaSimplePixelClusterFinder : public PndSdsSimplePixelClusterFinder {
 public:
  KoaSimplePixelClusterFinder(Int_t verbose = 0);
};
#endif
#ifndef PNDLMDCHARGEWEIGHTEDPIXELMAPPING_H
#define PNDLMDCHARGEWEIGHTEDPIXELMAPPING_H

#include "PndSdsChargeWeightedPixelMapping.h"

//! PndMvdChargeWeightedPixelMapping.h
//! @author T.Stockmanns <t.stockmanns@fz-juelich.de>
//!
//! \brief PndSdsChargedWeightedPixelMapping: Gets a vector of DigiHits and
//! calculates the cluster center weighted with the charge

class PndLmdChargeWeightedPixelMapping
    : public PndSdsChargeWeightedPixelMapping {
 public:
  PndLmdChargeWeightedPixelMapping(Int_t verbose = 0);
  PndLmdChargeWeightedPixelMapping(PndGeoHandling* geo, Int_t verbose = 0);
};

#endif
#ifndef KOACHARGEWEIGHTEDPIXELMAPPING_H
#define KOACHARGEWEIGHTEDPIXELMAPPING_H

#include "PndSdsChargeWeightedPixelMapping.h"

//! PndMvdChargeWeightedPixelMapping.h
//! @author T.Stockmanns <t.stockmanns@fz-juelich.de>
//!
//! \brief PndSdsChargedWeightedPixelMapping: Gets a vector of DigiHits and
//! calculates the cluster center weighted with the charge

class KoaChargeWeightedPixelMapping
    : public PndSdsChargeWeightedPixelMapping {
 public:
  KoaChargeWeightedPixelMapping(Int_t verbose = 0);
  KoaChargeWeightedPixelMapping(PndGeoHandling* geo, Int_t verbose = 0);
};

#endif
// -------------------------------------------------------------------------
// -----                 PndSdsMergedHit header file                   -----
// -----                  Created by M. Michel            -----
// -------------------------------------------------------------------------

#ifndef PNDSDSMERGEDHIT_H
#define PNDSDSMERGEDHIT_H

#include "FairHit.h"
#include "KoaDetectorList.h"
#include "TMatrixD.h"
#include "TString.h"
#include "TVector3.h"
//#include "PndSingleLinkedData.h"

#include <stdio.h>
#include <iostream>

#include "PndSdsHit.h"

class PndSdsMergedHit : public PndSdsHit {
  friend std::ostream& operator<<(std::ostream& out,
                                  const PndSdsMergedHit& hit) {
    out << "PndSdsMergedHit in " << hit.GetSensorID() << " at" << std::endl;
    out << "(" << hit.GetX() << ", " << hit.GetY() << ", " << hit.GetZ()
        << ") cm "
        << " with " << hit.GetCharge() << " e"
        << " at Time: " << hit.GetTimeStamp() << " +/- "
        << hit.GetTimeStampError() << " , Cluster No. "
        << hit.GetClusterIndex();
    if (hit.GetBotIndex() > -1) out << " and bottom " << hit.GetBotIndex();
    if (hit.GetRefIndex() > -1) out << ", mc point id = " << hit.GetRefIndex();
    if (hit.GetSecondMCHit() > -1)
      out << ", mc point 2 id = " << hit.GetSecondMCHit();
    else
      out << ", noise hit without mc poit";
    out << std::endl;

    out << "hit.GetClusterIndex() " << hit.GetClusterIndex() << std::endl;
    out << "hit.GetBotIndex() " << hit.GetBotIndex() << std::endl;
    out << "hit.GetRefIndex() " << hit.GetRefIndex() << std::endl;
    out << "hit.GetNDigiHits() " << hit.GetNDigiHits() << std::endl;
    out << "hit.GetCharge() " << hit.GetCharge() << "(" << hit.GetEloss()
        << " GeV)" << std::endl;
    out << "hit.GetSensorID() " << hit.GetSensorID() << std::endl;
    out << "Error values in FairHit part: (dx,dy,dz) = (" << hit.GetDx() << ","
        << hit.GetDy() << "," << hit.GetDz() << ")" << std::endl;
    return out;
  }

 public:
  /** Default constructor (not for use) **/
  PndSdsMergedHit();

  /** Standard constructor with all paramneters
   *@param detID   Detector ID
   *@param sensorID Sensor ID
   *@param pos     Position vector [cm]
   *@param dpos    Position error vector [cm]
   *@param index   Array index of ClusterCand
   *@param charge  Charge measured in hit
   *@param NDigiHits Number of pixels fired for this event
   **/
  PndSdsMergedHit(Int_t detID, Int_t sensorID, TVector3& pos, TVector3& dpos,
                  Int_t clindex, Double_t charge, Int_t NDigiHits,
                  Int_t mcindex, Int_t secMC);

  PndSdsMergedHit(PndSdsHit& c, Int_t secMC);

  // PndSdsHit(PndSdsHit& c);
  /** Destructor **/
  virtual ~PndSdsMergedHit();

  /** Accessors **/

  void SetSecondMCHit(Int_t secMChit) { fsecMC = secMChit; }

  Int_t GetSecondMCHit() const { return fsecMC; }

  void SetIsMerged(bool fflag) { fisMerged = fflag; }
  bool GetIsMerged() const { return fisMerged; }

 private:
  Int_t fsecMC;  ///< unique sensor ID
  bool fisMerged;
  ClassDef(PndSdsMergedHit, 1);
};

#endif
// -------------------------------------------------------------------------
// -----                 PndSdsCell header file                   -----
// -----                  Created by A. Karavdina            -----
// -------------------------------------------------------------------------

/** PndSdsCell.h
 *@author A.Karavdina <karavdin@kph.uni-mainz.de>
 **
 ** A container for a cell (straight track's segment)
 **/

#ifndef PNDSDSCELL_H
#define PNDSDSCELL_H

#include <stdio.h>
#include <iostream>
#include "TObject.h"

class PndSdsCell : public TObject {
 public:
  /** Default constructor (not for use) **/
  PndSdsCell();

  PndSdsCell(unsigned int hitUp, unsigned int hitDw);

  /** Destructor **/
  ~PndSdsCell();

  /** Accessors **/

  void SetHitUp(unsigned int &ih) { fhit_upstream = ih; }
  void SetHitDw(unsigned int &ih) { fhit_downstream = ih; }
  void SetPV(int &ipv) { fpv = ipv; }
  int GetHitUp() { return fhit_upstream; }
  int GetHitDw() { return fhit_downstream; }
  int GetPV() { return fpv; }

 private:
  unsigned int fhit_upstream;    // hit upstream
  unsigned int fhit_downstream;  // hit downstream
  int fpv;                       // cell position in evolution

  /* Int_t fsecMC; ///< unique sensor ID */
  /* bool fisMerged; */
  ClassDef(PndSdsCell, 1);
};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"KoaHitMergeTask", payloadCode, "@",
"KoaPixelClusterTask", payloadCode, "@",
"PndLmdHitMergeTask", payloadCode, "@",
"PndLmdPixelClusterTask", payloadCode, "@",
"PndSdsCell", payloadCode, "@",
"PndSdsMergedHit", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__LmdRecoDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__LmdRecoDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__LmdRecoDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__LmdRecoDict() {
  TriggerDictionaryInitialization_G__LmdRecoDict_Impl();
}
