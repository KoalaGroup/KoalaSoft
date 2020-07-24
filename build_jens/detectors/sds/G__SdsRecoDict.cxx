// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_jensdIdetectorsdIsdsdIG__SdsRecoDict

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
#include "SdsReco/PndSdsPixelClusterFinder.h"
#include "SdsReco/PndSdsSimplePixelClusterFinder.h"
#include "SdsReco/PndSdsIdealPixelClusterFinder.h"
#include "SdsReco/PndSdsPixelClusterTask.h"
#include "SdsReco/PndSdsIdealClusterTask.h"
#include "SdsReco/PndSdsPixelBackMapping.h"
#include "SdsReco/PndSdsChargeWeightedPixelMapping.h"
#include "SdsReco/PndSdsIdealRecoTask.h"
#include "SdsReco/PndSdsTimeWalkCorr.h"
#include "SdsReco/PndSdsTimeWalkCorrSimple.h"
#include "SdsReco/PndSdsTimeWalkCorrTask.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_PndSdsPixelClusterFinder(void *p);
   static void deleteArray_PndSdsPixelClusterFinder(void *p);
   static void destruct_PndSdsPixelClusterFinder(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsPixelClusterFinder*)
   {
      ::PndSdsPixelClusterFinder *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsPixelClusterFinder >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsPixelClusterFinder", ::PndSdsPixelClusterFinder::Class_Version(), "", 21,
                  typeid(::PndSdsPixelClusterFinder), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsPixelClusterFinder::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsPixelClusterFinder) );
      instance.SetDelete(&delete_PndSdsPixelClusterFinder);
      instance.SetDeleteArray(&deleteArray_PndSdsPixelClusterFinder);
      instance.SetDestructor(&destruct_PndSdsPixelClusterFinder);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsPixelClusterFinder*)
   {
      return GenerateInitInstanceLocal((::PndSdsPixelClusterFinder*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsPixelClusterFinder*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *PndSdsSimplePixelClusterFinder_Dictionary();
   static void PndSdsSimplePixelClusterFinder_TClassManip(TClass*);
   static void *new_PndSdsSimplePixelClusterFinder(void *p = 0);
   static void *newArray_PndSdsSimplePixelClusterFinder(Long_t size, void *p);
   static void delete_PndSdsSimplePixelClusterFinder(void *p);
   static void deleteArray_PndSdsSimplePixelClusterFinder(void *p);
   static void destruct_PndSdsSimplePixelClusterFinder(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsSimplePixelClusterFinder*)
   {
      ::PndSdsSimplePixelClusterFinder *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::PndSdsSimplePixelClusterFinder));
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsSimplePixelClusterFinder", "", 80,
                  typeid(::PndSdsSimplePixelClusterFinder), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &PndSdsSimplePixelClusterFinder_Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsSimplePixelClusterFinder) );
      instance.SetNew(&new_PndSdsSimplePixelClusterFinder);
      instance.SetNewArray(&newArray_PndSdsSimplePixelClusterFinder);
      instance.SetDelete(&delete_PndSdsSimplePixelClusterFinder);
      instance.SetDeleteArray(&deleteArray_PndSdsSimplePixelClusterFinder);
      instance.SetDestructor(&destruct_PndSdsSimplePixelClusterFinder);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsSimplePixelClusterFinder*)
   {
      return GenerateInitInstanceLocal((::PndSdsSimplePixelClusterFinder*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsSimplePixelClusterFinder*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *PndSdsSimplePixelClusterFinder_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::PndSdsSimplePixelClusterFinder*)0x0)->GetClass();
      PndSdsSimplePixelClusterFinder_TClassManip(theClass);
   return theClass;
   }

   static void PndSdsSimplePixelClusterFinder_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void delete_PndSdsPixelClusterTask(void *p);
   static void deleteArray_PndSdsPixelClusterTask(void *p);
   static void destruct_PndSdsPixelClusterTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsPixelClusterTask*)
   {
      ::PndSdsPixelClusterTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsPixelClusterTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsPixelClusterTask", ::PndSdsPixelClusterTask::Class_Version(), "", 186,
                  typeid(::PndSdsPixelClusterTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsPixelClusterTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsPixelClusterTask) );
      instance.SetDelete(&delete_PndSdsPixelClusterTask);
      instance.SetDeleteArray(&deleteArray_PndSdsPixelClusterTask);
      instance.SetDestructor(&destruct_PndSdsPixelClusterTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsPixelClusterTask*)
   {
      return GenerateInitInstanceLocal((::PndSdsPixelClusterTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsPixelClusterTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_PndSdsIdealClusterTask(void *p);
   static void deleteArray_PndSdsIdealClusterTask(void *p);
   static void destruct_PndSdsIdealClusterTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsIdealClusterTask*)
   {
      ::PndSdsIdealClusterTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsIdealClusterTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsIdealClusterTask", ::PndSdsIdealClusterTask::Class_Version(), "", 344,
                  typeid(::PndSdsIdealClusterTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsIdealClusterTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsIdealClusterTask) );
      instance.SetDelete(&delete_PndSdsIdealClusterTask);
      instance.SetDeleteArray(&deleteArray_PndSdsIdealClusterTask);
      instance.SetDestructor(&destruct_PndSdsIdealClusterTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsIdealClusterTask*)
   {
      return GenerateInitInstanceLocal((::PndSdsIdealClusterTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsIdealClusterTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_PndSdsIdealRecoTask(void *p);
   static void deleteArray_PndSdsIdealRecoTask(void *p);
   static void destruct_PndSdsIdealRecoTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsIdealRecoTask*)
   {
      ::PndSdsIdealRecoTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsIdealRecoTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsIdealRecoTask", ::PndSdsIdealRecoTask::Class_Version(), "", 568,
                  typeid(::PndSdsIdealRecoTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsIdealRecoTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsIdealRecoTask) );
      instance.SetDelete(&delete_PndSdsIdealRecoTask);
      instance.SetDeleteArray(&deleteArray_PndSdsIdealRecoTask);
      instance.SetDestructor(&destruct_PndSdsIdealRecoTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsIdealRecoTask*)
   {
      return GenerateInitInstanceLocal((::PndSdsIdealRecoTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsIdealRecoTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_PndSdsTimeWalkCorr(void *p);
   static void deleteArray_PndSdsTimeWalkCorr(void *p);
   static void destruct_PndSdsTimeWalkCorr(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsTimeWalkCorr*)
   {
      ::PndSdsTimeWalkCorr *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsTimeWalkCorr >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsTimeWalkCorr", ::PndSdsTimeWalkCorr::Class_Version(), "", 668,
                  typeid(::PndSdsTimeWalkCorr), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsTimeWalkCorr::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsTimeWalkCorr) );
      instance.SetDelete(&delete_PndSdsTimeWalkCorr);
      instance.SetDeleteArray(&deleteArray_PndSdsTimeWalkCorr);
      instance.SetDestructor(&destruct_PndSdsTimeWalkCorr);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsTimeWalkCorr*)
   {
      return GenerateInitInstanceLocal((::PndSdsTimeWalkCorr*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsTimeWalkCorr*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsTimeWalkCorrSimple(void *p = 0);
   static void *newArray_PndSdsTimeWalkCorrSimple(Long_t size, void *p);
   static void delete_PndSdsTimeWalkCorrSimple(void *p);
   static void deleteArray_PndSdsTimeWalkCorrSimple(void *p);
   static void destruct_PndSdsTimeWalkCorrSimple(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsTimeWalkCorrSimple*)
   {
      ::PndSdsTimeWalkCorrSimple *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsTimeWalkCorrSimple >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsTimeWalkCorrSimple", ::PndSdsTimeWalkCorrSimple::Class_Version(), "", 717,
                  typeid(::PndSdsTimeWalkCorrSimple), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsTimeWalkCorrSimple::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsTimeWalkCorrSimple) );
      instance.SetNew(&new_PndSdsTimeWalkCorrSimple);
      instance.SetNewArray(&newArray_PndSdsTimeWalkCorrSimple);
      instance.SetDelete(&delete_PndSdsTimeWalkCorrSimple);
      instance.SetDeleteArray(&deleteArray_PndSdsTimeWalkCorrSimple);
      instance.SetDestructor(&destruct_PndSdsTimeWalkCorrSimple);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsTimeWalkCorrSimple*)
   {
      return GenerateInitInstanceLocal((::PndSdsTimeWalkCorrSimple*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsTimeWalkCorrSimple*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_PndSdsTimeWalkCorrTask(void *p);
   static void deleteArray_PndSdsTimeWalkCorrTask(void *p);
   static void destruct_PndSdsTimeWalkCorrTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsTimeWalkCorrTask*)
   {
      ::PndSdsTimeWalkCorrTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsTimeWalkCorrTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsTimeWalkCorrTask", ::PndSdsTimeWalkCorrTask::Class_Version(), "", 768,
                  typeid(::PndSdsTimeWalkCorrTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsTimeWalkCorrTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsTimeWalkCorrTask) );
      instance.SetDelete(&delete_PndSdsTimeWalkCorrTask);
      instance.SetDeleteArray(&deleteArray_PndSdsTimeWalkCorrTask);
      instance.SetDestructor(&destruct_PndSdsTimeWalkCorrTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsTimeWalkCorrTask*)
   {
      return GenerateInitInstanceLocal((::PndSdsTimeWalkCorrTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsTimeWalkCorrTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr PndSdsPixelClusterFinder::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsPixelClusterFinder::Class_Name()
{
   return "PndSdsPixelClusterFinder";
}

//______________________________________________________________________________
const char *PndSdsPixelClusterFinder::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPixelClusterFinder*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsPixelClusterFinder::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPixelClusterFinder*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsPixelClusterFinder::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPixelClusterFinder*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsPixelClusterFinder::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPixelClusterFinder*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsPixelClusterTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsPixelClusterTask::Class_Name()
{
   return "PndSdsPixelClusterTask";
}

//______________________________________________________________________________
const char *PndSdsPixelClusterTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPixelClusterTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsPixelClusterTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPixelClusterTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsPixelClusterTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPixelClusterTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsPixelClusterTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPixelClusterTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsIdealClusterTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsIdealClusterTask::Class_Name()
{
   return "PndSdsIdealClusterTask";
}

//______________________________________________________________________________
const char *PndSdsIdealClusterTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsIdealClusterTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsIdealClusterTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsIdealClusterTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsIdealClusterTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsIdealClusterTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsIdealClusterTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsIdealClusterTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsIdealRecoTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsIdealRecoTask::Class_Name()
{
   return "PndSdsIdealRecoTask";
}

//______________________________________________________________________________
const char *PndSdsIdealRecoTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsIdealRecoTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsIdealRecoTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsIdealRecoTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsIdealRecoTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsIdealRecoTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsIdealRecoTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsIdealRecoTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsTimeWalkCorr::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsTimeWalkCorr::Class_Name()
{
   return "PndSdsTimeWalkCorr";
}

//______________________________________________________________________________
const char *PndSdsTimeWalkCorr::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTimeWalkCorr*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsTimeWalkCorr::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTimeWalkCorr*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsTimeWalkCorr::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTimeWalkCorr*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsTimeWalkCorr::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTimeWalkCorr*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsTimeWalkCorrSimple::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsTimeWalkCorrSimple::Class_Name()
{
   return "PndSdsTimeWalkCorrSimple";
}

//______________________________________________________________________________
const char *PndSdsTimeWalkCorrSimple::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTimeWalkCorrSimple*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsTimeWalkCorrSimple::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTimeWalkCorrSimple*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsTimeWalkCorrSimple::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTimeWalkCorrSimple*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsTimeWalkCorrSimple::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTimeWalkCorrSimple*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsTimeWalkCorrTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsTimeWalkCorrTask::Class_Name()
{
   return "PndSdsTimeWalkCorrTask";
}

//______________________________________________________________________________
const char *PndSdsTimeWalkCorrTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTimeWalkCorrTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsTimeWalkCorrTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTimeWalkCorrTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsTimeWalkCorrTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTimeWalkCorrTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsTimeWalkCorrTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsTimeWalkCorrTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void PndSdsPixelClusterFinder::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsPixelClusterFinder.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsPixelClusterFinder::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsPixelClusterFinder::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_PndSdsPixelClusterFinder(void *p) {
      delete ((::PndSdsPixelClusterFinder*)p);
   }
   static void deleteArray_PndSdsPixelClusterFinder(void *p) {
      delete [] ((::PndSdsPixelClusterFinder*)p);
   }
   static void destruct_PndSdsPixelClusterFinder(void *p) {
      typedef ::PndSdsPixelClusterFinder current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsPixelClusterFinder

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsSimplePixelClusterFinder(void *p) {
      return  p ? new(p) ::PndSdsSimplePixelClusterFinder : new ::PndSdsSimplePixelClusterFinder;
   }
   static void *newArray_PndSdsSimplePixelClusterFinder(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsSimplePixelClusterFinder[nElements] : new ::PndSdsSimplePixelClusterFinder[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsSimplePixelClusterFinder(void *p) {
      delete ((::PndSdsSimplePixelClusterFinder*)p);
   }
   static void deleteArray_PndSdsSimplePixelClusterFinder(void *p) {
      delete [] ((::PndSdsSimplePixelClusterFinder*)p);
   }
   static void destruct_PndSdsSimplePixelClusterFinder(void *p) {
      typedef ::PndSdsSimplePixelClusterFinder current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsSimplePixelClusterFinder

//______________________________________________________________________________
void PndSdsPixelClusterTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsPixelClusterTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsPixelClusterTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsPixelClusterTask::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_PndSdsPixelClusterTask(void *p) {
      delete ((::PndSdsPixelClusterTask*)p);
   }
   static void deleteArray_PndSdsPixelClusterTask(void *p) {
      delete [] ((::PndSdsPixelClusterTask*)p);
   }
   static void destruct_PndSdsPixelClusterTask(void *p) {
      typedef ::PndSdsPixelClusterTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsPixelClusterTask

//______________________________________________________________________________
void PndSdsIdealClusterTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsIdealClusterTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsIdealClusterTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsIdealClusterTask::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_PndSdsIdealClusterTask(void *p) {
      delete ((::PndSdsIdealClusterTask*)p);
   }
   static void deleteArray_PndSdsIdealClusterTask(void *p) {
      delete [] ((::PndSdsIdealClusterTask*)p);
   }
   static void destruct_PndSdsIdealClusterTask(void *p) {
      typedef ::PndSdsIdealClusterTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsIdealClusterTask

//______________________________________________________________________________
void PndSdsIdealRecoTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsIdealRecoTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsIdealRecoTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsIdealRecoTask::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_PndSdsIdealRecoTask(void *p) {
      delete ((::PndSdsIdealRecoTask*)p);
   }
   static void deleteArray_PndSdsIdealRecoTask(void *p) {
      delete [] ((::PndSdsIdealRecoTask*)p);
   }
   static void destruct_PndSdsIdealRecoTask(void *p) {
      typedef ::PndSdsIdealRecoTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsIdealRecoTask

//______________________________________________________________________________
void PndSdsTimeWalkCorr::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsTimeWalkCorr.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsTimeWalkCorr::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsTimeWalkCorr::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_PndSdsTimeWalkCorr(void *p) {
      delete ((::PndSdsTimeWalkCorr*)p);
   }
   static void deleteArray_PndSdsTimeWalkCorr(void *p) {
      delete [] ((::PndSdsTimeWalkCorr*)p);
   }
   static void destruct_PndSdsTimeWalkCorr(void *p) {
      typedef ::PndSdsTimeWalkCorr current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsTimeWalkCorr

//______________________________________________________________________________
void PndSdsTimeWalkCorrSimple::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsTimeWalkCorrSimple.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsTimeWalkCorrSimple::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsTimeWalkCorrSimple::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsTimeWalkCorrSimple(void *p) {
      return  p ? new(p) ::PndSdsTimeWalkCorrSimple : new ::PndSdsTimeWalkCorrSimple;
   }
   static void *newArray_PndSdsTimeWalkCorrSimple(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsTimeWalkCorrSimple[nElements] : new ::PndSdsTimeWalkCorrSimple[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsTimeWalkCorrSimple(void *p) {
      delete ((::PndSdsTimeWalkCorrSimple*)p);
   }
   static void deleteArray_PndSdsTimeWalkCorrSimple(void *p) {
      delete [] ((::PndSdsTimeWalkCorrSimple*)p);
   }
   static void destruct_PndSdsTimeWalkCorrSimple(void *p) {
      typedef ::PndSdsTimeWalkCorrSimple current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsTimeWalkCorrSimple

//______________________________________________________________________________
void PndSdsTimeWalkCorrTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsTimeWalkCorrTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsTimeWalkCorrTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsTimeWalkCorrTask::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_PndSdsTimeWalkCorrTask(void *p) {
      delete ((::PndSdsTimeWalkCorrTask*)p);
   }
   static void deleteArray_PndSdsTimeWalkCorrTask(void *p) {
      delete [] ((::PndSdsTimeWalkCorrTask*)p);
   }
   static void destruct_PndSdsTimeWalkCorrTask(void *p) {
      typedef ::PndSdsTimeWalkCorrTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsTimeWalkCorrTask

namespace ROOT {
   static TClass *vectorlEPndSdsDigiPixelgR_Dictionary();
   static void vectorlEPndSdsDigiPixelgR_TClassManip(TClass*);
   static void *new_vectorlEPndSdsDigiPixelgR(void *p = 0);
   static void *newArray_vectorlEPndSdsDigiPixelgR(Long_t size, void *p);
   static void delete_vectorlEPndSdsDigiPixelgR(void *p);
   static void deleteArray_vectorlEPndSdsDigiPixelgR(void *p);
   static void destruct_vectorlEPndSdsDigiPixelgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<PndSdsDigiPixel>*)
   {
      vector<PndSdsDigiPixel> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<PndSdsDigiPixel>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<PndSdsDigiPixel>", -2, "vector", 216,
                  typeid(vector<PndSdsDigiPixel>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEPndSdsDigiPixelgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<PndSdsDigiPixel>) );
      instance.SetNew(&new_vectorlEPndSdsDigiPixelgR);
      instance.SetNewArray(&newArray_vectorlEPndSdsDigiPixelgR);
      instance.SetDelete(&delete_vectorlEPndSdsDigiPixelgR);
      instance.SetDeleteArray(&deleteArray_vectorlEPndSdsDigiPixelgR);
      instance.SetDestructor(&destruct_vectorlEPndSdsDigiPixelgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<PndSdsDigiPixel> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<PndSdsDigiPixel>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPndSdsDigiPixelgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<PndSdsDigiPixel>*)0x0)->GetClass();
      vectorlEPndSdsDigiPixelgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPndSdsDigiPixelgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPndSdsDigiPixelgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<PndSdsDigiPixel> : new vector<PndSdsDigiPixel>;
   }
   static void *newArray_vectorlEPndSdsDigiPixelgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<PndSdsDigiPixel>[nElements] : new vector<PndSdsDigiPixel>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPndSdsDigiPixelgR(void *p) {
      delete ((vector<PndSdsDigiPixel>*)p);
   }
   static void deleteArray_vectorlEPndSdsDigiPixelgR(void *p) {
      delete [] ((vector<PndSdsDigiPixel>*)p);
   }
   static void destruct_vectorlEPndSdsDigiPixelgR(void *p) {
      typedef vector<PndSdsDigiPixel> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<PndSdsDigiPixel>

namespace {
  void TriggerDictionaryInitialization_G__SdsRecoDict_Impl() {
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
#line 1 "G__SdsRecoDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class PndSdsPixelClusterFinder;
class PndSdsSimplePixelClusterFinder;
class PndSdsPixelClusterTask;
class PndSdsIdealClusterTask;
class PndSdsIdealRecoTask;
class PndSdsTimeWalkCorr;
class PndSdsTimeWalkCorrSimple;
class PndSdsTimeWalkCorrTask;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__SdsRecoDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#ifndef PNDSDSPIXELCLUSTERFINDER_H
#define PNDSDSPIXELCLUSTERFINDER_H

#include <vector>
#include "PndSdsDigiPixel.h"
#include "PndSdsChargeConversion.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"

//! Base class for cluster finding algorithms
/** @author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
 * As input it gets all digis to be analyzed and a set of parameters vector<Double_t>
 * The output is a vector< vector <Int_t> > which contains the position of the hits in the TClonesArray containing the Digis
 */

class PndSdsPixelClusterFinder
  {
    public :
    PndSdsPixelClusterFinder()
    : fHits(),
      fVerbose(0),
      fChargeConverter(NULL)
    {};
    PndSdsPixelClusterFinder(PndSdsPixelClusterFinder& other)
    : fHits(other.fHits),
      fVerbose(other.fVerbose),
      fChargeConverter(other.fChargeConverter)
    {};
    PndSdsPixelClusterFinder& operator=(PndSdsPixelClusterFinder& other)
    {
      fHits=other.fHits;
      fVerbose=other.fVerbose;
      fChargeConverter=other.fChargeConverter;
    return *this;
    };
    virtual ~PndSdsPixelClusterFinder(){};
    virtual std::vector< std::vector < Int_t > > GetClusters(std::vector<PndSdsDigiPixel> hits) = 0;
    void Print();
    void Print(std::vector<PndSdsDigiPixel> hits);
    void PrintResult(std::vector<std::vector< Int_t> > clusters);
    void SetVerbose(Int_t level){fVerbose = level;};
    
    std::vector<PndSdsDigiPixel> fHits;
    Int_t fVerbose;
    
    PndSdsChargeConversion* fChargeConverter;
    
    ClassDef(PndSdsPixelClusterFinder, 2);
  };

#endif


#ifndef PNDSDSSIMPLEPIXELCLUSTERFINDER_H
#define PNDSDSSIMPLEPIXELCLUSTERFINDER_H

#include "PndSdsPixelClusterFinder.h"
/// PndSdsSimplePixelClusterFinder.h
/// Simple cluster finder for pixel detectors.
///
/// It takes the first hit in the DigiArray and moves it into a new cluster.
/// Then it looks through the remaining hits in the DigiArray if there are hits which are in the area around the first hit and moves them into the cluster.
/// The radius is given by the first parameter.
/// Then it takes the new hits in the cluster and looks if there are other hits which are in the range of these hits and moves them into the cluster, too.
/// This process is repeated until no hits around the cluster are found
/// The the first hit of the remaining DigiHits is taken to create a new hit and the cluster search process is started again.
///
/// params: Number of columns in a front-end
/// 		Number of rows in a front-end
/// 		Range as Int_t at which a pixel belongs to a cluster or not
/// params are taken from parameter database


class PndSdsSimplePixelClusterFinder : public PndSdsPixelClusterFinder
  {
    public :
    PndSdsSimplePixelClusterFinder():PndSdsPixelClusterFinder(), fcols(0), frows(0), fradius(-1.0){};
    //PndSdsSimplePixelClusterFinder(std::vector<PndSdsDigiPixel> hits):
    //	PndSdsPixelClusterFinder(hits){
    //	if(fVerbose>0)std::cout << "Hits in array: " << fHits.size() << std::endl;
    //};
    virtual ~PndSdsSimplePixelClusterFinder(){};
    
    ///Main method which searches for the clusters.
    ///It returns a matrix of ints where a column corresponds to a cluster and an integer to a hit in the DigiArray
    std::vector< std::vector< Int_t> > GetClusters(std::vector<PndSdsDigiPixel> hits);
    
    virtual void SetMaxCols(Int_t col){ fcols = col; }
    virtual void SetMaxRows(Int_t row){ frows = row; }
    virtual void SetRadius(Double_t rad) { fradius = rad; }

    protected :
    Int_t fcols;
    Int_t frows;
    Double_t fradius;
    
    private :
    //PndSdsDigiPixel MoveHit(std::vector<PndSdsDigiPixel>* hitVector, Int_t index);
    Int_t MoveHit(std::vector<Int_t>* hitVector, Int_t index) const;
    bool IsInRange(PndSdsDigiPixel hit1, PndSdsDigiPixel hit2) const;
    
  };
#endif
#ifndef PNDSDSIDEALPIXELCLUSTERFINDER_H
#define PNDSDSIDEALPIXELCLUSTERFINDER_H

#include "PndSdsPixelClusterFinder.h"
#include "PndSdsDigiPixel.h"
#include "TClonesArray.h"
#include <vector>
/// PndSdsIdealPixelClusterFinder.h
/// Ideal cluster finder using MCtruth information.

class PndSdsIdealPixelClusterFinder : public PndSdsPixelClusterFinder
  {
    public : 	PndSdsIdealPixelClusterFinder():PndSdsPixelClusterFinder(){};
    //		PndSdsIdealPixelClusterFinder(std::vector<PndSdsDigiPixel> hits):
    //			PndSdsPixelClusterFinder(hits){
    //			if(fVerbose>0) std::cout << "Hits in array: " << fHits.size() << std::endl;
    //		};
    virtual ~PndSdsIdealPixelClusterFinder(){};
    std::vector< std::vector< Int_t> > GetClusters(std::vector<PndSdsDigiPixel> hits);
    Int_t MoveHit(std::vector<Int_t>* hitVector, Int_t index) const;
    bool IsInRange(PndSdsDigiPixel hit1, PndSdsDigiPixel hit2) const;
    
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


#ifndef PNDSDSPIXELCLUSTERTASK_H
#define PNDSDSPIXELCLUSTERTASK_H 

#include "PndSdsTask.h"
//#include "PndSdsGeoPar.h"
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "PndSdsPixel.h"
#include "PndSdsFE.h"
// #include "PndSdsCluster.h"
#include "FairGeoVector.h"
#include "FairGeoTransform.h"
#include "TVector3.h"
#include "TRandom.h"
#include "TGeoMatrix.h"
#include "TGeoBBox.h"
#include "PndSdsHybridHitProducer.h"
#include "PndSdsPixelDigiPar.h"
#include "PndSdsTotDigiPar.h"
#include "PndSdsChargeConversion.h"
#include "KoaDetectorList.h"
#include "PndGeoHandling.h"

#include "PndSdsPixelClusterFinder.h"
#include "PndSdsPixelBackMapping.h"

#include "FairTSBufferFunctional.h"

#include <string>
#include <vector>

class TClonesArray;

class PndSdsPixelClusterTask : public PndSdsTask
  {
  public:
    
    /** Default constructor **/  
    PndSdsPixelClusterTask();
    PndSdsPixelClusterTask(const PndSdsPixelClusterTask& other):
      PndSdsTask(),
      fUseNoiseSuppression(other.fUseNoiseSuppression),
      fFEModel(other.fFEModel),
      fDigiArray(other.fDigiArray),
      fDigiPar(other.fDigiPar),
      fChargeConverter(other.fChargeConverter),
      fGeoH(other.fGeoH),
      fClustBranchName(other.fClustBranchName),
      fClusterArray(other.fClusterArray),
      fHitArray(other.fHitArray),
      fEventHeader(other.fEventHeader),
      fFunctor(other.fFunctor),
      fStartFunctor(other.fStartFunctor), 
      fClusterType(other.fClusterType),
      fEventNr(other.fEventNr),
      fClusterFinder(other.fClusterFinder),
      fBackMapping(other.fBackMapping)
    {};
    /** Named constructor **/  
    PndSdsPixelClusterTask(const char* name);
    
    /** Destructor **/
    virtual ~PndSdsPixelClusterTask();
    PndSdsPixelClusterTask& operator=(PndSdsPixelClusterTask& other)
    {
      fUseNoiseSuppression=other.fUseNoiseSuppression;
      fFEModel=other.fFEModel;
      fDigiArray=other.fDigiArray;
      fDigiPar=other.fDigiPar;
      fChargeConverter=other.fChargeConverter;
      fGeoH=other.fGeoH;
      fClustBranchName=other.fClustBranchName;
      fClusterArray=other.fClusterArray;
      fHitArray=other.fHitArray;
      fEventHeader=other.fEventHeader;
      fFunctor=other.fFunctor;
      fStartFunctor=other.fStartFunctor; 
      fClusterType=other.fClusterType;
      fEventNr=other.fEventNr;
      fClusterFinder=other.fClusterFinder;
      fBackMapping=other.fBackMapping;
      return *this;
    };
   virtual void SetClusterFinder()=0;
   virtual void SetBackMapping()=0;

   void SetNoiseSuppression(Bool_t val){fUseNoiseSuppression = val;}
   Bool_t GetNoiseSuppression() const {return fUseNoiseSuppression;}

   virtual void SetInBranchId(){
		FairRootManager *ioman = FairRootManager::Instance();
		fInBranchId = ioman->GetBranchId(fInBranchName);
		std::cout << "InBranchId: " << fInBranchId << " for Branch: " << fInBranchName.Data() << std::endl;
		fClusterType = ioman->GetBranchId(fClustBranchName);
		std::cout << "fClusterType: " << fClusterType << " for Branch: " << fClustBranchName.Data() << std::endl;
	}
     
    /** Virtual method Init **/
    virtual void SetParContainers();
    virtual InitStatus Init();
    virtual InitStatus ReInit();
    virtual void FinishEvent();
    
	/** Methods to run with MQ **/ 
    virtual void SetClusterFinderMQ(TList*){}; // tempList //[R.K.03/2017] unused variable(s)
	virtual void SetBackMappingMQ(TList* ){}; // tempList //[R.K.03/2017] unused variable(s)
    virtual void InitMQ(TList* tempList);
    virtual void GetParList(TList* tempList);
    virtual void ExecMQ(TList* inputList,TList* outputList);
    
    /** Virtual method Exec **/
    void Exec(Option_t* opt);

    
  protected:
    
    Bool_t fUseNoiseSuppression; // switch to turn on/off noise cancellation by introducing an additional cluster threshold

    PndSdsFE* fFEModel; //!

    /** Input array of PndSdsDigis **/
    TClonesArray* fDigiArray;
    PndSdsPixelDigiPar* fDigiPar;
    PndSdsChargeConversion* fChargeConverter;
    PndGeoHandling* fGeoH; //!
    
    TString fClustBranchName;
    /** Output array of PndSdsHits **/
    TClonesArray* fClusterArray;
    TClonesArray* fHitArray;
    FairEventHeader* fEventHeader;

    BinaryFunctor* fFunctor; //!
    BinaryFunctor* fStartFunctor; //!
    
    Int_t fClusterType;
    Int_t fEventNr;
    
    void Register();
    void Reset();  
    void ProduceHits();
    virtual std::vector<PndSdsDigiPixel> ConvertAndFilter(TClonesArray* digidata); ///< convert TClonesArray into std::vector and remove corrupted data (for test beam analysis)
    
  PndSdsPixelClusterFinder* fClusterFinder; //!
  PndSdsPixelBackMapping* fBackMapping; //!
  
//   TGeoHMatrix GetTransformation (std::string detName);
//   void GetLocalHitPoints(PndSdsMCPoint* myPoint, FairGeoVector& myHitIn, FairGeoVector& myHitOut);
//   PndSdsHit CalcGlobalPoint(std::vector<PndSdsPixel> pixels);
//   TVector3 GetSensorDimensions(std::string detName);  
        
    ClassDef(PndSdsPixelClusterTask,4);
    
  };

#endif /* SDSCLUSTERTASK_H */


/** PndSdsIdealClusterTask.h
 *@author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Ideal cluster finding task 
 */


#ifndef PndSdsIdealClusterTASK_H
#define PndSdsIdealClusterTASK_H 

#include "PndSdsTask.h"
//#include "PndSdsGeoPar.h"
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "PndSdsPixel.h"
#include "PndSdsIdealPixelClusterFinder.h"
#include "FairGeoVector.h"
#include "FairGeoTransform.h"
#include "TVector3.h"
#include "TRandom.h"
#include "TGeoMatrix.h"
#include "TGeoBBox.h"
#include "PndSdsHybridHitProducer.h"
#include "PndGeoHandling.h"
#include "PndSdsSimplePixelClusterFinder.h"
#include "PndSdsChargeWeightedPixelMapping.h"

#include <string>
#include <vector>
 
class TClonesArray;

class PndSdsIdealClusterTask : public PndSdsTask
{
 public:

    /** Default constructor **/  
    PndSdsIdealClusterTask();
    PndSdsIdealClusterTask(Double_t radius, Int_t FEcolumns, Int_t FErows, TString geoFile);
    PndSdsIdealClusterTask(PndSdsIdealClusterTask& other) :
      PndSdsTask(),
      fDigiArray(other.fDigiArray),
      fClustBranchName(other.fClustBranchName),
      fClusterType(other.fClusterType),
      fClusterArray(other.fClusterArray),
      fHitArray(other.fHitArray),
      fGeoH(other.fGeoH),
      fRadius(other.fRadius),
      fFEcolumns(other.fFEcolumns),
      fFErows(other.fFErows),
      fGeoFile(other.fGeoFile),
      finder(other.finder),
      mapping(other.mapping)
    {};
    /** Destructor **/
    virtual ~PndSdsIdealClusterTask();
    PndSdsIdealClusterTask& operator=(PndSdsIdealClusterTask& other)
    {
      fDigiArray=other.fDigiArray;
      fClustBranchName=other.fClustBranchName;
      fClusterType=other.fClusterType;
      fClusterArray=other.fClusterArray;
      fHitArray=other.fHitArray;
      fGeoH=other.fGeoH;
      fRadius=other.fRadius;
      fFEcolumns=other.fFEcolumns;
      fFErows=other.fFErows;
      fGeoFile=other.fGeoFile;
      finder=other.finder;
      mapping=other.mapping;
    return *this;
    };
   /** pure virtual method SetBranchNames
   **
   ** called by Init()
   ** function to set individual branch names
   **/
    /** Virtual method Init **/
    virtual void SetParContainers();
    virtual InitStatus Init();
    virtual InitStatus ReInit();

    virtual void SetInBranchId(){
 		  FairRootManager *ioman = FairRootManager::Instance();
 		  fInBranchId = ioman->GetBranchId(fInBranchName);
 		  std::cout << "InBranchId: " << fInBranchId << " for Branch: " << fInBranchName.Data() << std::endl;
 		  fClusterType = ioman->GetBranchId(fClustBranchName);
 	  }

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);
  
protected:

    /** Input array of PndSdsDigis **/
     TClonesArray* fDigiArray;

    TString fClustBranchName;
    Int_t fClusterType;

  /** Output array of PndSdsHits **/
      TClonesArray* fClusterArray;
      TClonesArray* fHitArray;
//   TClonesArray* fPixelArray;
//   TClonesArray* fFePixelArray;

      PndGeoHandling* fGeoH;
  
  void Register();
  void Reset();  
  void ProduceHits();

  Double_t fRadius;
  Int_t fFEcolumns;
  Int_t fFErows;
  TString fGeoFile;
  
//   TGeoHMatrix GetTransformation (std::string detName);
//   void GetLocalHitPoints(PndSdsMCPoint* myPoint, FairGeoVector& myHitIn, FairGeoVector& myHitOut);
//   PndSdsHit CalcGlobalPoint(std::vector<PndSdsPixel> pixels);
//   TVector3 GetSensorDimensions(std::string detName);  

  PndSdsIdealPixelClusterFinder* finder;
  PndSdsChargeWeightedPixelMapping* mapping;

  ClassDef(PndSdsIdealClusterTask,1);

};

#endif /* PndSdsIdealClusterTASK_H */

#ifndef PNDSDSPIXELBACKMAPPING_H
#define PNDSDSPIXELBACKMAPPING_H

#include "PndSdsDigiPixel.h"
#include "PndSdsHit.h"
#include "PndGeoHandling.h"
#include <vector>

class PndSdsPixelBackMapping
{
  public :  
  PndSdsPixelBackMapping();
  PndSdsPixelBackMapping(PndGeoHandling* geo);
  PndSdsPixelBackMapping(const PndSdsPixelBackMapping& other) :
    fDigiArray(other.fDigiArray),
    fGeoH(other.fGeoH),
    fVerbose(other.fVerbose)
  {};
  PndSdsPixelBackMapping& operator=(PndSdsPixelBackMapping& other)
  {
    fDigiArray=other.fDigiArray;
    fGeoH=other.fGeoH;
    fVerbose=other.fVerbose;
     return *this;
 };
  virtual ~PndSdsPixelBackMapping();

  void SetVerbose (Int_t level) {fVerbose = level;};
  virtual PndSdsHit GetCluster(std::vector<PndSdsDigiPixel> pixelArray) = 0;
      
  std::vector<PndSdsDigiPixel> fDigiArray;
  PndGeoHandling* fGeoH;
  Int_t fVerbose;

};

#endif

#ifndef PNDSDSCHARGEWEIGHTEDPIXELMAPPING_H
#define PNDSDSCHARGEWEIGHTEDPIXELMAPPING_H

#include "PndSdsPixelBackMapping.h"
#include "PndSdsChargeConversion.h"
#include "TGeoMatrix.h"
#include "TVector3.h"
//! PndSdsChargeWeightedPixelMapping.h
//! @author T.Stockmanns <t.stockmanns@fz-juelich.de>
//!
//! \brief PndSdsChargedWeightedPixelMapping: Gets a vector of DigiHits and calculates the cluster center weighted with the charge
//! params: Number of columns in FE, Number of rows in FE, Pixel dimension in x, Pixel dimension in y
//! params are taken from parameter database

class PndSdsChargeWeightedPixelMapping : public PndSdsPixelBackMapping
  {
    public :
    PndSdsChargeWeightedPixelMapping();
    PndSdsChargeWeightedPixelMapping(const PndSdsChargeWeightedPixelMapping& other) :
      PndSdsPixelBackMapping(other),
      fChargeConverter(other.fChargeConverter),
      flx(other.flx),
      fly(other.fly),
      fcols(other.fcols),
      frows(other.frows)
    {};
    PndSdsChargeWeightedPixelMapping(PndGeoHandling* geo);
    virtual ~PndSdsChargeWeightedPixelMapping(){};
    PndSdsChargeWeightedPixelMapping& operator=(PndSdsChargeWeightedPixelMapping& other)
    {
      fChargeConverter=other.fChargeConverter;
      flx=other.flx;
      fly=other.fly;
      fcols=other.fcols;
      frows=other.frows;
     return *this;
   };
    PndSdsHit GetCluster(std::vector<PndSdsDigiPixel> pixelArray); ///< Main function of class to calculate the PndSdsHit out of the given PndSdsDigis
    
    protected :
    PndSdsChargeConversion* fChargeConverter;
    Double_t flx;
    Double_t fly;
    Int_t fcols;
    Int_t frows;
    
    private :
    TGeoHMatrix GetTransformation(Int_t sensorID);
    TVector3 GetSensorDimensions(Int_t sensorID);
  };

#endif
// -------------------------------------------------------------------------
// -----                 PndSdsIdealRecoTask header file             -----
// -----                  Created 20/03/07  by R.Kliemt               -----
// -------------------------------------------------------------------------


/** PndSdsIdealRecoTask.h
 *@author R.Kliemt <r.kliemt@physik.tu-dresden.de>
 **
 ** The ideal tracking produces tracks of type PndSdsHit by using MC information
 ** directly, but with the correct data interface.
 **/


#ifndef PNDSDSIDEALRECOTASK_H
#define PNDSDSIDEALRECOTASK_H

// Root includes
#include "TVector3.h"
#include "TRandom.h"
#include "TString.h"
#include "TGeoManager.h"

// framework includes
#include "PndSdsTask.h"

// PndSds includes
#include "PndSdsMCPoint.h"
#include "PndGeoHandling.h"

class TClonesArray;

class PndSdsIdealRecoTask : public PndSdsTask
{
 public:

  /** Default constructor **/
  PndSdsIdealRecoTask();

  PndSdsIdealRecoTask(Double_t sx, Double_t sy, Double_t sz);
  
  PndSdsIdealRecoTask(PndSdsIdealRecoTask& other) :
    PndSdsTask(),
    fGeoH(other.fGeoH),
    fPointArray(other.fPointArray),
    fMctruthArray(other.fMctruthArray),
    fHitOutputArray(other.fHitOutputArray),
    fSigmaX(other.fSigmaX),
    fSigmaY(other.fSigmaY),
    fSigmaZ(other.fSigmaZ),
    fCurrentPndSdsMCPoint(other.fCurrentPndSdsMCPoint),
    fCurrentTransMat(other.fCurrentTransMat),
    fHitCovMatrix(other.fHitCovMatrix)
  {}

  /** Destructor **/
  virtual ~PndSdsIdealRecoTask();

  PndSdsIdealRecoTask& operator=(PndSdsIdealRecoTask& other)
  {
    fGeoH=other.fGeoH;
    fPointArray=other.fPointArray;
    fMctruthArray=other.fMctruthArray;
    fHitOutputArray=other.fHitOutputArray;
    fSigmaX=other.fSigmaX;
    fSigmaY=other.fSigmaY;
    fSigmaZ=other.fSigmaZ;
    fCurrentPndSdsMCPoint=other.fCurrentPndSdsMCPoint;
    fCurrentTransMat=other.fCurrentTransMat;
    fHitCovMatrix=other.fHitCovMatrix;
    return *this;
  };
  
  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();


  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);
  
protected:

  PndGeoHandling* fGeoH;

  /** Input array of Points **/
  TClonesArray* fPointArray;
  TClonesArray* fMctruthArray;

  /** Output array of Hits **/
  TClonesArray* fHitOutputArray;
  /** Properties **/
  Double_t fSigmaX;       // Variance vector of sensor smearing
  Double_t fSigmaY;       // Variance vector of sensor smearing
  Double_t fSigmaZ;       // Variance vector of sensor smearing
  PndSdsMCPoint* fCurrentPndSdsMCPoint;
  TGeoHMatrix* fCurrentTransMat;
  TMatrixT<Double_t> fHitCovMatrix;
  /** smearing and geometry access **/
  void InitTransMat();
  void smear(TVector3& pos);
  void smearLocal(TVector3& pos);
  void CalcDetPlane(TVector3& o,TVector3& u,TVector3& v);


  void Register();

  void Reset();

  void ProduceHits();

  ClassDef(PndSdsIdealRecoTask,1);

};

#endif
/*
 * PndSdsTimeWalkCorr.h
 *
 * Description:
 *
 *  Created on: Aug 26, 2010
 *      Author: Simone Esch
 *      Abstract Base Class to calculate the TimeWalkCorrection from the TOT time
 */

#include "TObject.h"

#ifndef PNDSDSTIMEWALKCORR_H_
#define PNDSDSTIMEWALKCORR_H_

class PndSdsTimeWalkCorr: public TObject {
public:

	PndSdsTimeWalkCorr();

	virtual ~PndSdsTimeWalkCorr();
	virtual Double_t CorrectionTimeWalk(Double_t tot)=0 ;
	virtual Double_t GetCharge()=0;

private:

ClassDef(PndSdsTimeWalkCorr, 1);
};

#endif /* PNDSDSTIMEWALKCORR_H_ */
/*
 * PndSdsTimeWalkCorrSimple.h
 *
 *  Created on: Aug 26, 2010
 *      Author: esch
 *
 *      This class calculates the TimeWalkCorrection from TOT time
 *      using a triangular model of the signal
 *      (see PndSdsTotChargeConversion)
 *                                           _____________________________________________
 *       			t_r*m-Q_thr-t_tot*m      | / t_r*m-Q_thr-t_tot*m \ 2                 |
 *      Q(tot) = - --------------------- + \ ||  -------------------  |  + t_r*Q_thr*m
 *                          2				\| \           2         /
 *                 Q_thr
 *      t_tw(Q) = -------- * t_r
 *                 Q(tot)
 *
 *
 *     Params from Parameter Database:
 *     ------------------------------
 *     t_r = rising time of the signal
 *     Q_thr = threshold charge
 *     m = constatnt current to unload the capacitor
 *
 */

#ifndef PNDSDSTIMEWALKCORRSIMPLE_H_
#define PNDSDSTIMEWALKCORRSIMPLE_H_

#include "PndSdsTimeWalkCorr.h"
#include <iostream>
#include <cmath>

class PndSdsTimeWalkCorrSimple: public PndSdsTimeWalkCorr {
public:
	PndSdsTimeWalkCorrSimple();

	PndSdsTimeWalkCorrSimple(Double_t risingtime, Double_t constcurrent, Double_t thr, Double_t frequency, Int_t verblevel);

	virtual ~PndSdsTimeWalkCorrSimple();

	virtual Double_t CorrectionTimeWalk(Double_t tot);
	virtual Double_t GetCharge() {return fCharge;};



private:
	Double_t fRisingTime;                 // ns
	Double_t fConstantCurrent;            // e/ns
	Double_t fTimeOverThreshold;          // ns
	Double_t fThreshold;                  // e
	Double_t fFrequency;				  // MHz
	Int_t fVerboseLevel;
	Double_t fCharge;					  // e
	Double_t fTimeWalk;                   // ns
	Double_t CalculateCharge(Double_t);
	Double_t CalculateTimeWalk(Double_t);

ClassDef(PndSdsTimeWalkCorrSimple, 1);
};

#endif /* PNDSDSTIMEWALKCORRSIMPLE_H_ */
/*
 * PndSdsPixelWimeWalkCorrTask.h
 *
 *  Created on: Aug 27, 2010
 *      Author: Simone Esch
 */

#ifndef PNDSDSTIMEWALKCORRTASK_H_
#define PNDSDSTIMEWALKCORRTASK_H_

#include "PndSdsTask.h"
#include "TClonesArray.h"
#include "PndSdsPixelDigiPar.h"
#include <vector>
#include "PndSdsDigiPixel.h"
#include "PndSdsDigiPixelMCInfo.h"
#include "PndSdsTotDigiPar.h"
#include "PndSdsTimeWalkCorrSimple.h"
#include "PndSdsFE.h"


class PndSdsTimeWalkCorrTask : public PndSdsTask {
public:
	PndSdsTimeWalkCorrTask();
	PndSdsTimeWalkCorrTask(const char* name);
  PndSdsTimeWalkCorrTask(PndSdsTimeWalkCorrTask& other) :
    PndSdsTask(),
	  fDigiArray(other.fDigiArray),
	  fDigiCorrArray(other.fDigiCorrArray),
    fDigiPar(other.fDigiPar),
    fDigiTotPar(other.fDigiTotPar),
    fFEModel(other.fFEModel),
    fVerbose(other.fVerbose)
  {};
	virtual ~PndSdsTimeWalkCorrTask();
  PndSdsTimeWalkCorrTask& operator=(PndSdsTimeWalkCorrTask& other)
  {
	  fDigiArray=other.fDigiArray;
	  fDigiCorrArray=other.fDigiCorrArray;
    fDigiPar=other.fDigiPar;
    fDigiTotPar=other.fDigiTotPar;
    fFEModel=other.fFEModel;
    fVerbose=other.fVerbose;
    return *this;
  };
	InitStatus Init();
	void SetParContainers();
	void Exec(Option_t* opt);
	  virtual void FinishTask();
protected:
	TClonesArray* fDigiArray;
	TClonesArray* fDigiCorrArray;
    PndSdsPixelDigiPar* fDigiPar;
    PndSdsTotDigiPar* fDigiTotPar;
    PndSdsFE* fFEModel;
    Int_t fVerbose;

    ClassDef(PndSdsTimeWalkCorrTask, 1);
};

#endif /* PNDSDSTIMEWALKCORRTASK_H_ */

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"PndSdsIdealClusterTask", payloadCode, "@",
"PndSdsIdealRecoTask", payloadCode, "@",
"PndSdsPixelClusterFinder", payloadCode, "@",
"PndSdsPixelClusterTask", payloadCode, "@",
"PndSdsSimplePixelClusterFinder", payloadCode, "@",
"PndSdsTimeWalkCorr", payloadCode, "@",
"PndSdsTimeWalkCorrSimple", payloadCode, "@",
"PndSdsTimeWalkCorrTask", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__SdsRecoDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__SdsRecoDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__SdsRecoDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__SdsRecoDict() {
  TriggerDictionaryInitialization_G__SdsRecoDict_Impl();
}
