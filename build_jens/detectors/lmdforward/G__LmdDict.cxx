// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_jensdIdetectorsdIlmdforwarddIG__LmdDict

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
#include "LmdTools/PndLmdContFact.h"
#include "LmdTools/PndLmdAlignPar.h"
#include "LmdDigi/PndLmdPixelHitProducerFast.h"
#include "LmdDigi/PndLmdHybridHitProducer.h"
#include "../recoil/full/koaDigi/KoaHybridHitProducer.h"
#include "LmdDigi/PndLmdHitProducerIdeal.h"
#include "PndLmdDetector.h"
#include "PndLmdGeo.h"
#include "PndLmdGeometryFactory.h"
#include "PndLmdGeometryHelper.h"
#include "geolumidetector.h"
#include "../recoil/full/geokoaladetector.h"
#include "../recoil/full/Koaladetector.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_PndLmdContFact(void *p = 0);
   static void *newArray_PndLmdContFact(Long_t size, void *p);
   static void delete_PndLmdContFact(void *p);
   static void deleteArray_PndLmdContFact(void *p);
   static void destruct_PndLmdContFact(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdContFact*)
   {
      ::PndLmdContFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdContFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdContFact", ::PndLmdContFact::Class_Version(), "", 20,
                  typeid(::PndLmdContFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdContFact::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdContFact) );
      instance.SetNew(&new_PndLmdContFact);
      instance.SetNewArray(&newArray_PndLmdContFact);
      instance.SetDelete(&delete_PndLmdContFact);
      instance.SetDeleteArray(&deleteArray_PndLmdContFact);
      instance.SetDestructor(&destruct_PndLmdContFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdContFact*)
   {
      return GenerateInitInstanceLocal((::PndLmdContFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdContFact*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLmdAlignPar(void *p = 0);
   static void *newArray_PndLmdAlignPar(Long_t size, void *p);
   static void delete_PndLmdAlignPar(void *p);
   static void deleteArray_PndLmdAlignPar(void *p);
   static void destruct_PndLmdAlignPar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdAlignPar*)
   {
      ::PndLmdAlignPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdAlignPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdAlignPar", ::PndLmdAlignPar::Class_Version(), "", 52,
                  typeid(::PndLmdAlignPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdAlignPar::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdAlignPar) );
      instance.SetNew(&new_PndLmdAlignPar);
      instance.SetNewArray(&newArray_PndLmdAlignPar);
      instance.SetDelete(&delete_PndLmdAlignPar);
      instance.SetDeleteArray(&deleteArray_PndLmdAlignPar);
      instance.SetDestructor(&destruct_PndLmdAlignPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdAlignPar*)
   {
      return GenerateInitInstanceLocal((::PndLmdAlignPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdAlignPar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLmdPixelHitProducerFast(void *p = 0);
   static void *newArray_PndLmdPixelHitProducerFast(Long_t size, void *p);
   static void delete_PndLmdPixelHitProducerFast(void *p);
   static void deleteArray_PndLmdPixelHitProducerFast(void *p);
   static void destruct_PndLmdPixelHitProducerFast(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdPixelHitProducerFast*)
   {
      ::PndLmdPixelHitProducerFast *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdPixelHitProducerFast >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdPixelHitProducerFast", ::PndLmdPixelHitProducerFast::Class_Version(), "", 127,
                  typeid(::PndLmdPixelHitProducerFast), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdPixelHitProducerFast::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdPixelHitProducerFast) );
      instance.SetNew(&new_PndLmdPixelHitProducerFast);
      instance.SetNewArray(&newArray_PndLmdPixelHitProducerFast);
      instance.SetDelete(&delete_PndLmdPixelHitProducerFast);
      instance.SetDeleteArray(&deleteArray_PndLmdPixelHitProducerFast);
      instance.SetDestructor(&destruct_PndLmdPixelHitProducerFast);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdPixelHitProducerFast*)
   {
      return GenerateInitInstanceLocal((::PndLmdPixelHitProducerFast*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdPixelHitProducerFast*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLmdHybridHitProducer(void *p = 0);
   static void *newArray_PndLmdHybridHitProducer(Long_t size, void *p);
   static void delete_PndLmdHybridHitProducer(void *p);
   static void deleteArray_PndLmdHybridHitProducer(void *p);
   static void destruct_PndLmdHybridHitProducer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdHybridHitProducer*)
   {
      ::PndLmdHybridHitProducer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdHybridHitProducer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdHybridHitProducer", ::PndLmdHybridHitProducer::Class_Version(), "", 198,
                  typeid(::PndLmdHybridHitProducer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdHybridHitProducer::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdHybridHitProducer) );
      instance.SetNew(&new_PndLmdHybridHitProducer);
      instance.SetNewArray(&newArray_PndLmdHybridHitProducer);
      instance.SetDelete(&delete_PndLmdHybridHitProducer);
      instance.SetDeleteArray(&deleteArray_PndLmdHybridHitProducer);
      instance.SetDestructor(&destruct_PndLmdHybridHitProducer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdHybridHitProducer*)
   {
      return GenerateInitInstanceLocal((::PndLmdHybridHitProducer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdHybridHitProducer*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaHybridHitProducer(void *p = 0);
   static void *newArray_KoaHybridHitProducer(Long_t size, void *p);
   static void delete_KoaHybridHitProducer(void *p);
   static void deleteArray_KoaHybridHitProducer(void *p);
   static void destruct_KoaHybridHitProducer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaHybridHitProducer*)
   {
      ::KoaHybridHitProducer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaHybridHitProducer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaHybridHitProducer", ::KoaHybridHitProducer::Class_Version(), "", 237,
                  typeid(::KoaHybridHitProducer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaHybridHitProducer::Dictionary, isa_proxy, 4,
                  sizeof(::KoaHybridHitProducer) );
      instance.SetNew(&new_KoaHybridHitProducer);
      instance.SetNewArray(&newArray_KoaHybridHitProducer);
      instance.SetDelete(&delete_KoaHybridHitProducer);
      instance.SetDeleteArray(&deleteArray_KoaHybridHitProducer);
      instance.SetDestructor(&destruct_KoaHybridHitProducer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaHybridHitProducer*)
   {
      return GenerateInitInstanceLocal((::KoaHybridHitProducer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaHybridHitProducer*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLmdHitProducerIdeal(void *p = 0);
   static void *newArray_PndLmdHitProducerIdeal(Long_t size, void *p);
   static void delete_PndLmdHitProducerIdeal(void *p);
   static void deleteArray_PndLmdHitProducerIdeal(void *p);
   static void destruct_PndLmdHitProducerIdeal(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdHitProducerIdeal*)
   {
      ::PndLmdHitProducerIdeal *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdHitProducerIdeal >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdHitProducerIdeal", ::PndLmdHitProducerIdeal::Class_Version(), "", 289,
                  typeid(::PndLmdHitProducerIdeal), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdHitProducerIdeal::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdHitProducerIdeal) );
      instance.SetNew(&new_PndLmdHitProducerIdeal);
      instance.SetNewArray(&newArray_PndLmdHitProducerIdeal);
      instance.SetDelete(&delete_PndLmdHitProducerIdeal);
      instance.SetDeleteArray(&deleteArray_PndLmdHitProducerIdeal);
      instance.SetDestructor(&destruct_PndLmdHitProducerIdeal);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdHitProducerIdeal*)
   {
      return GenerateInitInstanceLocal((::PndLmdHitProducerIdeal*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdHitProducerIdeal*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLmdDetector(void *p = 0);
   static void *newArray_PndLmdDetector(Long_t size, void *p);
   static void delete_PndLmdDetector(void *p);
   static void deleteArray_PndLmdDetector(void *p);
   static void destruct_PndLmdDetector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdDetector*)
   {
      ::PndLmdDetector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdDetector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdDetector", ::PndLmdDetector::Class_Version(), "", 337,
                  typeid(::PndLmdDetector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdDetector::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdDetector) );
      instance.SetNew(&new_PndLmdDetector);
      instance.SetNewArray(&newArray_PndLmdDetector);
      instance.SetDelete(&delete_PndLmdDetector);
      instance.SetDeleteArray(&deleteArray_PndLmdDetector);
      instance.SetDestructor(&destruct_PndLmdDetector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdDetector*)
   {
      return GenerateInitInstanceLocal((::PndLmdDetector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdDetector*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLmdGeo(void *p = 0);
   static void *newArray_PndLmdGeo(Long_t size, void *p);
   static void delete_PndLmdGeo(void *p);
   static void deleteArray_PndLmdGeo(void *p);
   static void destruct_PndLmdGeo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdGeo*)
   {
      ::PndLmdGeo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdGeo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdGeo", ::PndLmdGeo::Class_Version(), "", 381,
                  typeid(::PndLmdGeo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdGeo::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdGeo) );
      instance.SetNew(&new_PndLmdGeo);
      instance.SetNewArray(&newArray_PndLmdGeo);
      instance.SetDelete(&delete_PndLmdGeo);
      instance.SetDeleteArray(&deleteArray_PndLmdGeo);
      instance.SetDestructor(&destruct_PndLmdGeo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdGeo*)
   {
      return GenerateInitInstanceLocal((::PndLmdGeo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdGeo*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Koaladetector(void *p = 0);
   static void *newArray_Koaladetector(Long_t size, void *p);
   static void delete_Koaladetector(void *p);
   static void deleteArray_Koaladetector(void *p);
   static void destruct_Koaladetector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Koaladetector*)
   {
      ::Koaladetector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Koaladetector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Koaladetector", ::Koaladetector::Class_Version(), "", 730,
                  typeid(::Koaladetector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Koaladetector::Dictionary, isa_proxy, 4,
                  sizeof(::Koaladetector) );
      instance.SetNew(&new_Koaladetector);
      instance.SetNewArray(&newArray_Koaladetector);
      instance.SetDelete(&delete_Koaladetector);
      instance.SetDeleteArray(&deleteArray_Koaladetector);
      instance.SetDestructor(&destruct_Koaladetector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Koaladetector*)
   {
      return GenerateInitInstanceLocal((::Koaladetector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Koaladetector*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr PndLmdContFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdContFact::Class_Name()
{
   return "PndLmdContFact";
}

//______________________________________________________________________________
const char *PndLmdContFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdContFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdContFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdContFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdContFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdContFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdContFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdContFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLmdAlignPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdAlignPar::Class_Name()
{
   return "PndLmdAlignPar";
}

//______________________________________________________________________________
const char *PndLmdAlignPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdAlignPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdAlignPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdAlignPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdAlignPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdAlignPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdAlignPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdAlignPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLmdPixelHitProducerFast::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdPixelHitProducerFast::Class_Name()
{
   return "PndLmdPixelHitProducerFast";
}

//______________________________________________________________________________
const char *PndLmdPixelHitProducerFast::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdPixelHitProducerFast*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdPixelHitProducerFast::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdPixelHitProducerFast*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdPixelHitProducerFast::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdPixelHitProducerFast*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdPixelHitProducerFast::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdPixelHitProducerFast*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLmdHybridHitProducer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdHybridHitProducer::Class_Name()
{
   return "PndLmdHybridHitProducer";
}

//______________________________________________________________________________
const char *PndLmdHybridHitProducer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdHybridHitProducer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdHybridHitProducer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdHybridHitProducer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdHybridHitProducer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdHybridHitProducer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdHybridHitProducer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdHybridHitProducer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaHybridHitProducer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaHybridHitProducer::Class_Name()
{
   return "KoaHybridHitProducer";
}

//______________________________________________________________________________
const char *KoaHybridHitProducer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaHybridHitProducer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaHybridHitProducer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaHybridHitProducer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaHybridHitProducer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaHybridHitProducer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaHybridHitProducer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaHybridHitProducer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLmdHitProducerIdeal::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdHitProducerIdeal::Class_Name()
{
   return "PndLmdHitProducerIdeal";
}

//______________________________________________________________________________
const char *PndLmdHitProducerIdeal::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdHitProducerIdeal*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdHitProducerIdeal::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdHitProducerIdeal*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdHitProducerIdeal::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdHitProducerIdeal*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdHitProducerIdeal::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdHitProducerIdeal*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLmdDetector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdDetector::Class_Name()
{
   return "PndLmdDetector";
}

//______________________________________________________________________________
const char *PndLmdDetector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdDetector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdDetector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdDetector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdDetector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdDetector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdDetector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdDetector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLmdGeo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdGeo::Class_Name()
{
   return "PndLmdGeo";
}

//______________________________________________________________________________
const char *PndLmdGeo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdGeo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdGeo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdGeo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdGeo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdGeo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdGeo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdGeo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Koaladetector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Koaladetector::Class_Name()
{
   return "Koaladetector";
}

//______________________________________________________________________________
const char *Koaladetector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Koaladetector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Koaladetector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Koaladetector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Koaladetector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Koaladetector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Koaladetector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Koaladetector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void PndLmdContFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdContFact.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdContFact::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdContFact::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdContFact(void *p) {
      return  p ? new(p) ::PndLmdContFact : new ::PndLmdContFact;
   }
   static void *newArray_PndLmdContFact(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdContFact[nElements] : new ::PndLmdContFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdContFact(void *p) {
      delete ((::PndLmdContFact*)p);
   }
   static void deleteArray_PndLmdContFact(void *p) {
      delete [] ((::PndLmdContFact*)p);
   }
   static void destruct_PndLmdContFact(void *p) {
      typedef ::PndLmdContFact current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdContFact

//______________________________________________________________________________
void PndLmdAlignPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdAlignPar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdAlignPar::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdAlignPar::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdAlignPar(void *p) {
      return  p ? new(p) ::PndLmdAlignPar : new ::PndLmdAlignPar;
   }
   static void *newArray_PndLmdAlignPar(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdAlignPar[nElements] : new ::PndLmdAlignPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdAlignPar(void *p) {
      delete ((::PndLmdAlignPar*)p);
   }
   static void deleteArray_PndLmdAlignPar(void *p) {
      delete [] ((::PndLmdAlignPar*)p);
   }
   static void destruct_PndLmdAlignPar(void *p) {
      typedef ::PndLmdAlignPar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdAlignPar

//______________________________________________________________________________
void PndLmdPixelHitProducerFast::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdPixelHitProducerFast.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdPixelHitProducerFast::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdPixelHitProducerFast::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdPixelHitProducerFast(void *p) {
      return  p ? new(p) ::PndLmdPixelHitProducerFast : new ::PndLmdPixelHitProducerFast;
   }
   static void *newArray_PndLmdPixelHitProducerFast(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdPixelHitProducerFast[nElements] : new ::PndLmdPixelHitProducerFast[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdPixelHitProducerFast(void *p) {
      delete ((::PndLmdPixelHitProducerFast*)p);
   }
   static void deleteArray_PndLmdPixelHitProducerFast(void *p) {
      delete [] ((::PndLmdPixelHitProducerFast*)p);
   }
   static void destruct_PndLmdPixelHitProducerFast(void *p) {
      typedef ::PndLmdPixelHitProducerFast current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdPixelHitProducerFast

//______________________________________________________________________________
void PndLmdHybridHitProducer::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdHybridHitProducer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdHybridHitProducer::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdHybridHitProducer::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdHybridHitProducer(void *p) {
      return  p ? new(p) ::PndLmdHybridHitProducer : new ::PndLmdHybridHitProducer;
   }
   static void *newArray_PndLmdHybridHitProducer(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdHybridHitProducer[nElements] : new ::PndLmdHybridHitProducer[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdHybridHitProducer(void *p) {
      delete ((::PndLmdHybridHitProducer*)p);
   }
   static void deleteArray_PndLmdHybridHitProducer(void *p) {
      delete [] ((::PndLmdHybridHitProducer*)p);
   }
   static void destruct_PndLmdHybridHitProducer(void *p) {
      typedef ::PndLmdHybridHitProducer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdHybridHitProducer

//______________________________________________________________________________
void KoaHybridHitProducer::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaHybridHitProducer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaHybridHitProducer::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaHybridHitProducer::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaHybridHitProducer(void *p) {
      return  p ? new(p) ::KoaHybridHitProducer : new ::KoaHybridHitProducer;
   }
   static void *newArray_KoaHybridHitProducer(Long_t nElements, void *p) {
      return p ? new(p) ::KoaHybridHitProducer[nElements] : new ::KoaHybridHitProducer[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaHybridHitProducer(void *p) {
      delete ((::KoaHybridHitProducer*)p);
   }
   static void deleteArray_KoaHybridHitProducer(void *p) {
      delete [] ((::KoaHybridHitProducer*)p);
   }
   static void destruct_KoaHybridHitProducer(void *p) {
      typedef ::KoaHybridHitProducer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaHybridHitProducer

//______________________________________________________________________________
void PndLmdHitProducerIdeal::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdHitProducerIdeal.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdHitProducerIdeal::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdHitProducerIdeal::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdHitProducerIdeal(void *p) {
      return  p ? new(p) ::PndLmdHitProducerIdeal : new ::PndLmdHitProducerIdeal;
   }
   static void *newArray_PndLmdHitProducerIdeal(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdHitProducerIdeal[nElements] : new ::PndLmdHitProducerIdeal[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdHitProducerIdeal(void *p) {
      delete ((::PndLmdHitProducerIdeal*)p);
   }
   static void deleteArray_PndLmdHitProducerIdeal(void *p) {
      delete [] ((::PndLmdHitProducerIdeal*)p);
   }
   static void destruct_PndLmdHitProducerIdeal(void *p) {
      typedef ::PndLmdHitProducerIdeal current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdHitProducerIdeal

//______________________________________________________________________________
void PndLmdDetector::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdDetector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdDetector::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdDetector::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdDetector(void *p) {
      return  p ? new(p) ::PndLmdDetector : new ::PndLmdDetector;
   }
   static void *newArray_PndLmdDetector(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdDetector[nElements] : new ::PndLmdDetector[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdDetector(void *p) {
      delete ((::PndLmdDetector*)p);
   }
   static void deleteArray_PndLmdDetector(void *p) {
      delete [] ((::PndLmdDetector*)p);
   }
   static void destruct_PndLmdDetector(void *p) {
      typedef ::PndLmdDetector current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdDetector

//______________________________________________________________________________
void PndLmdGeo::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdGeo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdGeo::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdGeo::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdGeo(void *p) {
      return  p ? new(p) ::PndLmdGeo : new ::PndLmdGeo;
   }
   static void *newArray_PndLmdGeo(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdGeo[nElements] : new ::PndLmdGeo[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdGeo(void *p) {
      delete ((::PndLmdGeo*)p);
   }
   static void deleteArray_PndLmdGeo(void *p) {
      delete [] ((::PndLmdGeo*)p);
   }
   static void destruct_PndLmdGeo(void *p) {
      typedef ::PndLmdGeo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdGeo

//______________________________________________________________________________
void Koaladetector::Streamer(TBuffer &R__b)
{
   // Stream an object of class Koaladetector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Koaladetector::Class(),this);
   } else {
      R__b.WriteClassBuffer(Koaladetector::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Koaladetector(void *p) {
      return  p ? new(p) ::Koaladetector : new ::Koaladetector;
   }
   static void *newArray_Koaladetector(Long_t nElements, void *p) {
      return p ? new(p) ::Koaladetector[nElements] : new ::Koaladetector[nElements];
   }
   // Wrapper around operator delete
   static void delete_Koaladetector(void *p) {
      delete ((::Koaladetector*)p);
   }
   static void deleteArray_Koaladetector(void *p) {
      delete [] ((::Koaladetector*)p);
   }
   static void destruct_Koaladetector(void *p) {
      typedef ::Koaladetector current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Koaladetector

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
   static TClass *maplEstringcOTGeoHMatrixgR_Dictionary();
   static void maplEstringcOTGeoHMatrixgR_TClassManip(TClass*);
   static void *new_maplEstringcOTGeoHMatrixgR(void *p = 0);
   static void *newArray_maplEstringcOTGeoHMatrixgR(Long_t size, void *p);
   static void delete_maplEstringcOTGeoHMatrixgR(void *p);
   static void deleteArray_maplEstringcOTGeoHMatrixgR(void *p);
   static void destruct_maplEstringcOTGeoHMatrixgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,TGeoHMatrix>*)
   {
      map<string,TGeoHMatrix> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,TGeoHMatrix>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,TGeoHMatrix>", -2, "map", 99,
                  typeid(map<string,TGeoHMatrix>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOTGeoHMatrixgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,TGeoHMatrix>) );
      instance.SetNew(&new_maplEstringcOTGeoHMatrixgR);
      instance.SetNewArray(&newArray_maplEstringcOTGeoHMatrixgR);
      instance.SetDelete(&delete_maplEstringcOTGeoHMatrixgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOTGeoHMatrixgR);
      instance.SetDestructor(&destruct_maplEstringcOTGeoHMatrixgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,TGeoHMatrix> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,TGeoHMatrix>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOTGeoHMatrixgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,TGeoHMatrix>*)0x0)->GetClass();
      maplEstringcOTGeoHMatrixgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOTGeoHMatrixgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOTGeoHMatrixgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,TGeoHMatrix> : new map<string,TGeoHMatrix>;
   }
   static void *newArray_maplEstringcOTGeoHMatrixgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,TGeoHMatrix>[nElements] : new map<string,TGeoHMatrix>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOTGeoHMatrixgR(void *p) {
      delete ((map<string,TGeoHMatrix>*)p);
   }
   static void deleteArray_maplEstringcOTGeoHMatrixgR(void *p) {
      delete [] ((map<string,TGeoHMatrix>*)p);
   }
   static void destruct_maplEstringcOTGeoHMatrixgR(void *p) {
      typedef map<string,TGeoHMatrix> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,TGeoHMatrix>

namespace {
  void TriggerDictionaryInitialization_G__LmdDict_Impl() {
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
#line 1 "G__LmdDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class PndLmdContFact;
class PndLmdAlignPar;
class PndLmdPixelHitProducerFast;
class PndLmdHybridHitProducer;
class KoaHybridHitProducer;
class PndLmdHitProducerIdeal;
class PndLmdDetector;
class PndLmdGeo;
class Koaladetector;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__LmdDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
/*
 * PndLmdContFact.h
 *
 *  Created on: May 29, 2009
 *      Author: huagen
 */

#ifndef PNDLMDCONTFACT_H_
#define PNDLMDCONTFACT_H_

#include "FairContFact.h"

class FairContainer;

class PndLmdContFact : public FairContFact {
public:
	PndLmdContFact();
	~PndLmdContFact();
	FairParSet* createContainer(FairContainer* c);
	TList* GetDigiParNames() {return fDigiParNames;};
	TList* GetAlignParNames() {return fAlignParNames;};
private:
	void setAllContainers();
	TList* fDigiParNames;
	TList* fAlignParNames;
	ClassDef(PndLmdContFact,3)
};

#endif /* PNDLMDCONTFACT_H_ */
//
// C++ Interface: PndLmdAlignPar
//
#ifndef PNDLMDALIGNPAR_H
#define PNDLMDALIGNPAR_H

#include <vector>
#include <TVector2.h>
#include <TString.h>
#include <TObjString.h>

#include "FairParGenericSet.h"
#include "FairParamList.h"

using namespace std;
//! Alignment Parameter Class for LMD
class PndLmdAlignPar : public FairParGenericSet
  {
    public :
		PndLmdAlignPar (const char* name="PndLmdAlignPar",
                        const char* title="PndLmd alignment parameter",
                        const char* context="TestDefaultContext");
		~PndLmdAlignPar(void){};
		void clear(void){};
		void putParams(FairParamList* list);
		Bool_t getParams(FairParamList* list);
		
		void Print();
		/** Accessor functions **/
		Double_t GetShiftX(int j) const {return fshift_x[j];}
		Double_t GetShiftY(int j) const {return fshift_y[j];}
		Double_t GetShiftZ(int j) const {return fshift_z[j];}
		Double_t GetRotateX(int j) const {return frotate_x[j];}
		Double_t GetRotateY(int j) const {return frotate_y[j];}
		Double_t GetRotateZ(int j) const {return frotate_z[j];}
		Int_t GetNsensors(){return fsensors;}
		Int_t GetNsides(){return fsides;}
		Int_t GetNplanes(){return fplanes;}
		//for pixel design
		Int_t GetNhalfs(){return fhalfs;}
		Int_t GetNmodules(){return fmodules;}
  private:
    //Planes parameters
    Int_t fsensors;//Number of sensors per module, 1 side
    Int_t fsides;//Number of sides per module
    Int_t fplanes;//Number of planes
    Int_t fhalfs;
    Int_t fmodules;//Number of modules per plane half
    //Sensor parameters
    vector<double> fshift_x;
    vector<double> fshift_y;
    vector<double> fshift_z;
    vector<double> frotate_x;
    vector<double> frotate_y;
    vector<double> frotate_z;  

    ClassDef(PndLmdAlignPar,6);
  };

#endif /* !PNDSDSSTRIPDIGIPAR_H*/

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


#ifndef PNDLMDPIXELHITPRODUCERFAST_H
#define PNDLMDPIXELHITPRODUCERFAST_H 

#include "PndSdsTask.h"
//#include "PndSdsGeoPar.h"
#include "KoaDetectorList.h"

#include "TVector3.h"
#include "TRandom.h"
 
class TClonesArray;

class PndLmdPixelHitProducerFast : public PndSdsTask
{
 public:

  /** Default constructor **/  
  PndLmdPixelHitProducerFast();
  PndLmdPixelHitProducerFast(Double_t pixelx, Double_t pixely);

  /** Named constructor **/  
  PndLmdPixelHitProducerFast(const char* name);

  /** Destructor **/
  virtual ~PndLmdPixelHitProducerFast();


  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();

  /** pure virtual method SetBranchNames
   **
   ** called by Init()
   ** function to set individual branch names
   **/
  virtual void SetBranchNames();
  virtual void SetBranchNames(TString inBranchname, TString outBranchname, TString folderName);

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  void SetPersistance(Bool_t p = kTRUE) {SetPersistency(p);};
  Bool_t GetPersistance() {return GetPersistency();};
  
protected:

  Double_t fPixelSizeX; //to round MC-Hit x-position
  Double_t fPixelSizeY; //to round MC-Hit y-position
  
  
  /** Input array of PndSdsMCPoints **/
  TClonesArray* fPointArray;

  /** Output array of PndSdsHits **/
  TClonesArray* fHitArray;  

  //PndSdsGeoPar* fGeoPar;
  
  void Register();
  
  void Reset();
  
  void ProduceHits();

  ClassDef(PndLmdPixelHitProducerFast,1);

};

#endif

/** PndLmdHybridHitProducer.h
 **
 **/

#ifndef PNDLMDHYBRIDHITPRODUCER_H
#define PNDLMDHYBRIDHITPRODUCER_H 1

#include "PndSdsHybridHitProducer.h"
#include "PndSdsTotDigiPar.h"
#include "TString.h"

class PndLmdHybridHitProducer : public PndSdsHybridHitProducer
{
 public:

  /** Default constructor **/
 PndLmdHybridHitProducer();

  /** Destructor **/
  virtual ~PndLmdHybridHitProducer();

  /** Specific Parameter set loading **/
  virtual void SetParContainers();
  
  virtual InitStatus Init();

  /** Specify the branch & folder names for the I/O **/
  void SetBranchNames(TString inBranchname, TString outBranchname, TString folderName);
  
  /** Take default naming **/
  virtual void SetBranchNames();
    
  ClassDef(PndLmdHybridHitProducer,9);

};

#endif

/** KoaHybridHitProducer.h
 **
 **/
        
#ifndef KOAHYBRIDHITPRODUCER_H
#define KOAHYBRIDHITPRODUCER_H 1

#include "PndSdsHybridHitProducer.h"
#include "PndSdsTotDigiPar.h"
#include "TString.h"

class KoaHybridHitProducer : public PndSdsHybridHitProducer
{
 public:

  /** Default constructor **/
 KoaHybridHitProducer();

  /** Destructor **/
  virtual ~KoaHybridHitProducer();

  /** Specific Parameter set loading **/
  virtual void SetParContainers();
  
  virtual InitStatus Init();

  /** Specify the branch & folder names for the I/O **/
  void SetBranchNames(TString inBranchname, TString outBranchname, TString folderName);
  
  /** Take default naming **/
  virtual void SetBranchNames();
    
  ClassDef(KoaHybridHitProducer,9);

};

#endif
// -------------------------------------------------------------------------
// -----                  PndLmdHitProducerIdeal header file           -----
// -----                    Created 04/02/10 by M. Michel              -----
// -----            Based on CbmStsHitProducerIdel by V. Friese        -----
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


#ifndef PNDLMDHITPRODUCERIDEAL_H
#define PNDLMDHITPRODUCERIDEAL_H 

#include "PndSdsHitProducerIdeal.h"
 
class TClonesArray;

class PndLmdHitProducerIdeal : public PndSdsHitProducerIdeal
{
 public:

  /** Default constructor **/  
  PndLmdHitProducerIdeal();


  /** Destructor **/
  virtual ~PndLmdHitProducerIdeal();

  virtual void SetBranchNames(TString inBranchname, TString outBranchname, TString folderName);
  virtual void SetBranchNames();


  ClassDef(PndLmdHitProducerIdeal,4);

};

#endif
// -------------------------------------------------------------------------
// -----                         PndLmdDetector header file -----
// -----                  Created 6/04/06  by T. Stockmanns            -----
// -----                          Based on PndMvdDetector -----
// -------------------------------------------------------------------------

/**  PndLmdDetector.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 *@author M.Michel <michel@kph.uni-mainz.de>
 *@author h.xu <h.xu@fz-juelich.de>
 **
 ** Defines the active detector PndLmdDetector. Constructs the geometry and
 ** registers MCPoints.
 ** Notes on Jun 30,2010 by Huagen:
 ** To construct detector geometry from ASCII file the detector name shall be
 ** defined by users. The function of ConstructASCIIGeometry() should be
 *reloaded
 ** by user who wants to define the DetName freely.Without reloading this
 *function
 ** the detector name was defined by PndSdsGeo class anyway.
 **/

#ifndef PNDLMDDETECTOR_H
#define PNDLMDDETECTOR_H

#include "PndSdsDetector.h"

class PndLmdDetector : public PndSdsDetector
{
  std::map<std::string, TGeoHMatrix> fAlignmentMatrices;

public:
  /** Default constructor **/
  PndLmdDetector();

  /** Standard constructor.
   *@param name    detetcor name
   *@param active  sensitivity flag
   **/
  PndLmdDetector(const char *name, Bool_t active);

  /** Destructor **/
  virtual ~PndLmdDetector();

  virtual void SetBranchNames(char *outBranchname, char *folderName);
  virtual void SetBranchNames();
  virtual void SetDefaultSensorNames();

  virtual void Initialize() { PndSdsDetector::Initialize(); };
  // virtual void ConstructASCIIGeometry();

  ClassDef(PndLmdDetector, 7);
};

#endif
/*
 * PndLmdGeo.h
 * *  Created on: Jun 30, 2010
 *      Author: huagen
 */
/*
 * PndLmdGeo class will define the detector name by user. It was inherited from
 * Sds base class PndSdsGeo.
 */

#ifndef PNDLMDGEO_H_
#define PNDLMDGEO_H_

#include "PndSdsGeo.h"

class PndLmdGeo : public PndSdsGeo {
 public:
  PndLmdGeo();
  ~PndLmdGeo();

  const char* getModuleName(Int_t m);
  const char* getEleName(Int_t m);

  ClassDef(PndLmdGeo, 1);
};

#endif /* PNDLMDGEO_H_ */
/*
 * PndLmdGeometryFactory.h
 *
 *  Created on: Nov 6, 2017
 *      Author: steve
 */

#ifndef LMD_LMDMC_PNDLMDGEOMETRYFACTORY_H_
#define LMD_LMDMC_PNDLMDGEOMETRYFACTORY_H_

#include <vector>

#include <boost/property_tree/ptree.hpp>

class TGeoManager;
class TGeoVolume;
class TGeoVolumeAssembly;
class FairGeoLoader;
class TGeoNode;

typedef std::pair<std::string, bool> StringBoolPair;

class PndLmdGeometryFactory {
  boost::property_tree::ptree geometry_property_tree;
  std::vector<StringBoolPair> navigation_paths;
  TGeoManager* gGeoMan;

  void retrieveMaterial(FairGeoLoader* geoLoad);

  TGeoVolume* generateLmdBox() const;
  TGeoVolume* generateBeamPipe() const;

  TGeoVolume* generateDetectorHalf(bool is_bottom_half) const;
  TGeoVolume* generateDetectorHalfPlane(bool is_bottom_half) const;
  TGeoVolume* generateAluminumCoolingStructure() const;
  TGeoVolume* generatePCB() const;
  TGeoVolume* generatePCBMountScrew() const;
  TGeoVolume* generatePCBCopperPlug() const;
  TGeoVolume* generatePCBBacksideElectronics() const;
  TGeoVolume* generateSensorModule() const;
  TGeoVolume* generateCVDCoolingDisc() const;
  TGeoVolume* generateSensor() const;

  TGeoVolume* generateBoxVacuum(const TGeoVolume* lmd_vol) const;
  void recursiveNodeSubtraction(std::stringstream& ss, TGeoNode* node) const;

  void makeNodesAlignable() const;
  void makeNodesAlignable(TGeoNode* node,
                          unsigned int current_navigation_path_index) const;

 public:
  PndLmdGeometryFactory(
      const boost::property_tree::ptree& geometry_property_tree_);
  virtual ~PndLmdGeometryFactory();

  void init(FairGeoLoader* geoLoad);

  TGeoVolumeAssembly* generateLmdGeometry() const;
};

#endif /* LMD_LMDMC_PNDLMDGEOMETRYFACTORY_H_ */
#ifndef LMD_LMDMC_PNDLMDGEOMETRYHELPER_H_
#define LMD_LMDMC_PNDLMDGEOMETRYHELPER_H_

#include <map>
#include <string>
#include <vector>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <TGeoManager.h>
#include <TVector3.h>

struct PndLmdHitLocationInfo {
	// we use small data types here as they can be packed into 8 bytes
	unsigned char detector_half;
	unsigned char plane;
	unsigned char module;
	unsigned char module_side;
	unsigned char module_sensor_id;

	friend std::ostream& operator<<(std::ostream& stream, const PndLmdHitLocationInfo& hit_info) {
		stream << "detector half: " << (unsigned int) hit_info.detector_half << "\n";
		stream << "detector plane: " << (unsigned int) hit_info.plane << "\n";
		stream << "module on half plane: " << (unsigned int) hit_info.module << "\n";
		stream << "side of module: " << (unsigned int) hit_info.module_side << "\n";
		stream << "sensor id: " << (unsigned int) hit_info.module_sensor_id << "\n";

		return stream;
	}

	bool operator <(const PndLmdHitLocationInfo &o) {
		return std::tie(detector_half, plane, module, module_side, module_sensor_id)
		    < std::tie(o.detector_half, o.plane, o.module, o.module_side, o.module_sensor_id);
	}
};

class PndLmdGeometryHelper {
	boost::property_tree::ptree geometry_properties;
	std::vector<std::pair<std::string, bool> > navigation_paths;

	std::map<std::string, PndLmdHitLocationInfo> volume_path_to_hit_info_mapping;
	std::map<int, PndLmdHitLocationInfo> sensor_id_to_hit_info_mapping;

	std::string lmd_root_path;

	TGeoManager* fGeoManager;

	PndLmdGeometryHelper(const std::string& geo_params_config_file_url = "../../parameters/lmd-geo-params.json") :
			fGeoManager(gGeoManager) {
		// load parameters
		read_json(geo_params_config_file_url, geometry_properties);
		auto pt_general = geometry_properties.get_child("general");
		for (boost::property_tree::ptree::value_type &nav_path : pt_general.get_child("navigation_paths")) {
			navigation_paths.push_back(
			    std::make_pair(nav_path.second.get<std::string>("name"),
			        nav_path.second.get<bool>("is_alignable")));
		}

		TString actPath = fGeoManager->GetPath();
		std::stringstream lmd_path;
		fGeoManager->CdTop();
		lmd_path << fGeoManager->GetPath() << "/" << navigation_paths[0].first << "_0";
		lmd_root_path = lmd_path.str();
		if (actPath != "" && actPath != " ") fGeoManager->cd(actPath);

	}

	const PndLmdHitLocationInfo& createMappingEntry(int sensor_id);
	const PndLmdHitLocationInfo& createMappingEntry(const std::string& volume_path);

	PndLmdHitLocationInfo translateVolumePathToHitLocationInfo(const std::string& volume_path) const;

public:
	static PndLmdGeometryHelper& getInstance() {
		static PndLmdGeometryHelper instance;
		return instance;
	}
	virtual ~PndLmdGeometryHelper();

	PndLmdGeometryHelper(const PndLmdGeometryHelper&) = delete;
	void operator=(const PndLmdGeometryHelper&) = delete;

	const PndLmdHitLocationInfo& getHitLocationInfo(const std::string& volume_path);
	// this function with the global sensor id is much faster for lookups
	// so use that if you need speed!

	const PndLmdHitLocationInfo& getHitLocationInfo(int sensor_id);

	static std::vector<int> getAvailableOverlapIDs();
	int getOverlapIdFromSensorIDs(int id1, int id2);

	TVector3 transformPndGlobalToLmdLocal(const TVector3 &vec);
	TVector3 transformPndGlobalToSensor(const TVector3 &vec, int sensorId);

	bool isOverlappingArea(const int id1, const int id2);

	const std::string getPath(unsigned char...);

	const TGeoHMatrix getMatrixPndGlobalToSensor(const int sensorId);
	const TGeoHMatrix getMatrixSensorToPndGlobal(const int sensorId);

	const TGeoHMatrix getMatrixPndGlobalToLmdLocal();
	const TGeoHMatrix getMatrixLmdLocalToPndGlobal();

	// returns all paths to alignable objects, filtered by bools
	    std::vector<std::string> getAllAlignPaths(bool sensors=true, bool modules=false, bool planes=false,
	    bool halfs=false, bool detector=false);

	    std::vector<std::string> getAllAlignableVolumePaths() const;

    };

#endif /* LMD_LMDMC_PNDLMDGEOMETRYHELPER_H_ */
#ifndef LMD_LMDMC_GEOMETRYFACTORY_H_
#define LMD_LMDMC_GEOMETRYFACTORY_H_

#include <vector>

#include <boost/property_tree/ptree.hpp>

class TGeoManager;
class TGeoVolume;
class TGeoVolumeAssembly;
class FairGeoLoader;
class TGeoNode;


typedef std::pair<std::string, bool> StringBoolPair;

class geolumidetector {
  boost::property_tree::ptree geometry_property_tree;
  std::vector<StringBoolPair> navigation_paths;
  TGeoManager* gGeoMan;

  void retrieveMaterial(FairGeoLoader* geoLoad);

  TGeoVolume* generateLmdBox() const;
  TGeoVolume* generateLmdBoxsecondary() const;
  TGeoVolume* generateBeamPipe() const;
  TGeoVolume* generateDetectorHalf(bool is_bottom_half) const;
  TGeoVolume* generateDetectorHalfPlane(bool is_bottom_half) const;
  TGeoVolume* generateSensorModule() const;
  TGeoVolume* generateSensor() const;
  TGeoVolume* generateSensorVert() const;
  TGeoVolume* generateBeamTPiece() const;
  TGeoVolume* generateAluminumCoolingStructure() const;
  TGeoVolume* generatePCB() const;
  TGeoVolume* generatePCBMountScrew() const;
  TGeoVolume* generatePCBCopperPlug() const;
  TGeoVolume* generatePCBBacksideElectronics() const;
  TGeoVolume* generateCVDCoolingDisc() const;

  
 

  TGeoVolume* generateBoxVacuum(const TGeoVolume* lmd_vol) const;
  void recursiveNodeSubtraction(std::stringstream& ss, TGeoNode* node) const;

  void makeNodesAlignable() const;
  void makeNodesAlignable(TGeoNode* node,
                          unsigned int current_navigation_path_index) const;

 public:
  geolumidetector(
      const boost::property_tree::ptree& geometry_property_tree_);
  virtual ~geolumidetector();

  void init(FairGeoLoader* geoLoad);

  TGeoVolumeAssembly* generateLmdGeometry() const;
};

#endif
#ifndef LMD_LMDMC_GEOMETRYFACTORYS_H_
#define LMD_LMDMC_GEOMETRYFACTORYS_H_

#include <vector>

#include <boost/property_tree/ptree.hpp>

class TGeoManager;
class TGeoVolume;
class TGeoVolumeAssembly;
class FairGeoLoader;
class TGeoNode;


typedef std::pair<std::string, bool> StringBoolPair;

class geokoaladetector {
  boost::property_tree::ptree geometry_property_tree;
  std::vector<StringBoolPair> navigation_paths;
  TGeoManager* gGeoMan;

  void retrieveMaterial(FairGeoLoader* geoLoad);

  TGeoVolume* generateLmdBox() const;
  TGeoVolume* generateLmdBoxsecondary() const;
  TGeoVolume* generateBeamPipe() const;
  TGeoVolume* generateDetectorHalf(bool is_bottom_half) const;
  TGeoVolume* generateDetectorHalfPlane(bool is_bottom_half) const;
  TGeoVolume* generateSensorModule() const;
  TGeoVolume* generateSensor() const;
  TGeoVolume* generateSensorVert() const;
  TGeoVolume* generateSensorGer() const;
TGeoVolume* generateSensorBox() const;
  TGeoVolume* generateSensorVertBox() const;
  TGeoVolume* generateSensorGerBox() const;
  TGeoVolume* generateBeamTPiece() const;
  TGeoVolume* generateAluminumCoolingStructure() const;
  TGeoVolume* generatePCB() const;
  TGeoVolume* generatePCBMountScrew() const;
  TGeoVolume* generatePCBCopperPlug() const;
  TGeoVolume* generatePCBBacksideElectronics() const;
  TGeoVolume* generateCVDCoolingDisc() const;
  TGeoVolume* generateKoalabase() const;
  TGeoVolume* generateKoalastand() const;
  TGeoVolume* generateKoalaChamberEnt() const;
  TGeoVolume* generateKoalaChamber() const;
  TGeoVolume* generateKoalaInnerChamber() const;
  TGeoVolume* generateKoalaSensorMount() const;

  
 

  TGeoVolume* generateBoxVacuum(const TGeoVolume* lmd_vol) const;
  void recursiveNodeSubtraction(std::stringstream& ss, TGeoNode* node) const;

  void makeNodesAlignable() const;
  void makeNodesAlignable(TGeoNode* node,
                          unsigned int current_navigation_path_index) const;

 public:
 geokoaladetector(
      const boost::property_tree::ptree& geometry_property_tree_);
  virtual ~geokoaladetector();

  void init(FairGeoLoader* geoLoad);

  TGeoVolumeAssembly* generateLmdGeometry() const;
};

#endif
// -------------------------------------------------------------------------
// -----                         PndLmdDetector header file -----
// -----                  Created 6/04/06  by T. Stockmanns            -----
// -----                          Based on PndMvdDetector -----
// -------------------------------------------------------------------------

/**  PndLmdDetector.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 *@author M.Michel <michel@kph.uni-mainz.de>
 *@author h.xu <h.xu@fz-juelich.de>
 **
 ** Defines the active detector PndLmdDetector. Constructs the geometry and
 ** registers MCPoints.
 ** Notes on Jun 30,2010 by Huagen:
 ** To construct detector geometry from ASCII file the detector name shall be
 ** defined by users. The function of ConstructASCIIGeometry() should be
 *reloaded
 ** by user who wants to define the DetName freely.Without reloading this
 *function
 ** the detector name was defined by PndSdsGeo class anyway.
 **/

#ifndef KOALADETECTOR_H
#define KOALADETECTOR_H

#include "PndSdsDetector.h"

class Koaladetector : public PndSdsDetector {

 public:
  /** Default constructor **/
  Koaladetector();

  /** Standard constructor.
   *@param name    detetcor name
   *@param active  sensitivity flag
   **/
 Koaladetector(const char* name, Bool_t active);

  /** Destructor **/
  virtual ~Koaladetector();

  virtual void SetBranchNames(char* outBranchname, char* folderName);
  virtual void SetBranchNames();
  virtual void SetDefaultSensorNames();

  virtual void Initialize() { PndSdsDetector::Initialize(); };
  // virtual void ConstructASCIIGeometry();


  ClassDef(Koaladetector, 7);
};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"KoaHybridHitProducer", payloadCode, "@",
"Koaladetector", payloadCode, "@",
"PndLmdAlignPar", payloadCode, "@",
"PndLmdContFact", payloadCode, "@",
"PndLmdDetector", payloadCode, "@",
"PndLmdGeo", payloadCode, "@",
"PndLmdHitProducerIdeal", payloadCode, "@",
"PndLmdHybridHitProducer", payloadCode, "@",
"PndLmdPixelHitProducerFast", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__LmdDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__LmdDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__LmdDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__LmdDict() {
  TriggerDictionaryInitialization_G__LmdDict_Impl();
}
