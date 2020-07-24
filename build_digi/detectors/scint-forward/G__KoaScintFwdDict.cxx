// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_digidIdetectorsdIscintmIforwarddIG__KoaScintFwdDict

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
#include "KoaFwd.h"
#include "KoaFwdContFact.h"
#include "KoaFwdGeo.h"
#include "KoaFwdGeoPar.h"
#include "KoaFwdMisalignPar.h"
#include "KoaFwdPoint.h"
#include "KoaFwdDigi.h"
#include "KoaFwdDigitization.h"
#include "KoaFwdDigitizationPar.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_KoaFwd(void *p = 0);
   static void *newArray_KoaFwd(Long_t size, void *p);
   static void delete_KoaFwd(void *p);
   static void deleteArray_KoaFwd(void *p);
   static void destruct_KoaFwd(void *p);
   static void streamer_KoaFwd(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaFwd*)
   {
      ::KoaFwd *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaFwd >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaFwd", ::KoaFwd::Class_Version(), "", 28,
                  typeid(::KoaFwd), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaFwd::Dictionary, isa_proxy, 16,
                  sizeof(::KoaFwd) );
      instance.SetNew(&new_KoaFwd);
      instance.SetNewArray(&newArray_KoaFwd);
      instance.SetDelete(&delete_KoaFwd);
      instance.SetDeleteArray(&deleteArray_KoaFwd);
      instance.SetDestructor(&destruct_KoaFwd);
      instance.SetStreamerFunc(&streamer_KoaFwd);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaFwd*)
   {
      return GenerateInitInstanceLocal((::KoaFwd*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaFwd*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaFwdContFact(void *p = 0);
   static void *newArray_KoaFwdContFact(Long_t size, void *p);
   static void delete_KoaFwdContFact(void *p);
   static void deleteArray_KoaFwdContFact(void *p);
   static void destruct_KoaFwdContFact(void *p);
   static void streamer_KoaFwdContFact(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaFwdContFact*)
   {
      ::KoaFwdContFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaFwdContFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaFwdContFact", ::KoaFwdContFact::Class_Version(), "", 166,
                  typeid(::KoaFwdContFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaFwdContFact::Dictionary, isa_proxy, 16,
                  sizeof(::KoaFwdContFact) );
      instance.SetNew(&new_KoaFwdContFact);
      instance.SetNewArray(&newArray_KoaFwdContFact);
      instance.SetDelete(&delete_KoaFwdContFact);
      instance.SetDeleteArray(&deleteArray_KoaFwdContFact);
      instance.SetDestructor(&destruct_KoaFwdContFact);
      instance.SetStreamerFunc(&streamer_KoaFwdContFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaFwdContFact*)
   {
      return GenerateInitInstanceLocal((::KoaFwdContFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaFwdContFact*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaFwdGeo(void *p = 0);
   static void *newArray_KoaFwdGeo(Long_t size, void *p);
   static void delete_KoaFwdGeo(void *p);
   static void deleteArray_KoaFwdGeo(void *p);
   static void destruct_KoaFwdGeo(void *p);
   static void streamer_KoaFwdGeo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaFwdGeo*)
   {
      ::KoaFwdGeo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaFwdGeo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaFwdGeo", ::KoaFwdGeo::Class_Version(), "", 192,
                  typeid(::KoaFwdGeo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaFwdGeo::Dictionary, isa_proxy, 16,
                  sizeof(::KoaFwdGeo) );
      instance.SetNew(&new_KoaFwdGeo);
      instance.SetNewArray(&newArray_KoaFwdGeo);
      instance.SetDelete(&delete_KoaFwdGeo);
      instance.SetDeleteArray(&deleteArray_KoaFwdGeo);
      instance.SetDestructor(&destruct_KoaFwdGeo);
      instance.SetStreamerFunc(&streamer_KoaFwdGeo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaFwdGeo*)
   {
      return GenerateInitInstanceLocal((::KoaFwdGeo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaFwdGeo*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaFwdGeoPar(void *p = 0);
   static void *newArray_KoaFwdGeoPar(Long_t size, void *p);
   static void delete_KoaFwdGeoPar(void *p);
   static void deleteArray_KoaFwdGeoPar(void *p);
   static void destruct_KoaFwdGeoPar(void *p);
   static void streamer_KoaFwdGeoPar(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaFwdGeoPar*)
   {
      ::KoaFwdGeoPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaFwdGeoPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaFwdGeoPar", ::KoaFwdGeoPar::Class_Version(), "", 235,
                  typeid(::KoaFwdGeoPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaFwdGeoPar::Dictionary, isa_proxy, 16,
                  sizeof(::KoaFwdGeoPar) );
      instance.SetNew(&new_KoaFwdGeoPar);
      instance.SetNewArray(&newArray_KoaFwdGeoPar);
      instance.SetDelete(&delete_KoaFwdGeoPar);
      instance.SetDeleteArray(&deleteArray_KoaFwdGeoPar);
      instance.SetDestructor(&destruct_KoaFwdGeoPar);
      instance.SetStreamerFunc(&streamer_KoaFwdGeoPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaFwdGeoPar*)
   {
      return GenerateInitInstanceLocal((::KoaFwdGeoPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaFwdGeoPar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaFwdMisalignPar(void *p = 0);
   static void *newArray_KoaFwdMisalignPar(Long_t size, void *p);
   static void delete_KoaFwdMisalignPar(void *p);
   static void deleteArray_KoaFwdMisalignPar(void *p);
   static void destruct_KoaFwdMisalignPar(void *p);
   static void streamer_KoaFwdMisalignPar(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaFwdMisalignPar*)
   {
      ::KoaFwdMisalignPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaFwdMisalignPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaFwdMisalignPar", ::KoaFwdMisalignPar::Class_Version(), "", 282,
                  typeid(::KoaFwdMisalignPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaFwdMisalignPar::Dictionary, isa_proxy, 16,
                  sizeof(::KoaFwdMisalignPar) );
      instance.SetNew(&new_KoaFwdMisalignPar);
      instance.SetNewArray(&newArray_KoaFwdMisalignPar);
      instance.SetDelete(&delete_KoaFwdMisalignPar);
      instance.SetDeleteArray(&deleteArray_KoaFwdMisalignPar);
      instance.SetDestructor(&destruct_KoaFwdMisalignPar);
      instance.SetStreamerFunc(&streamer_KoaFwdMisalignPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaFwdMisalignPar*)
   {
      return GenerateInitInstanceLocal((::KoaFwdMisalignPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaFwdMisalignPar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaFwdPoint(void *p = 0);
   static void *newArray_KoaFwdPoint(Long_t size, void *p);
   static void delete_KoaFwdPoint(void *p);
   static void deleteArray_KoaFwdPoint(void *p);
   static void destruct_KoaFwdPoint(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaFwdPoint*)
   {
      ::KoaFwdPoint *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaFwdPoint >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaFwdPoint", ::KoaFwdPoint::Class_Version(), "", 336,
                  typeid(::KoaFwdPoint), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaFwdPoint::Dictionary, isa_proxy, 4,
                  sizeof(::KoaFwdPoint) );
      instance.SetNew(&new_KoaFwdPoint);
      instance.SetNewArray(&newArray_KoaFwdPoint);
      instance.SetDelete(&delete_KoaFwdPoint);
      instance.SetDeleteArray(&deleteArray_KoaFwdPoint);
      instance.SetDestructor(&destruct_KoaFwdPoint);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaFwdPoint*)
   {
      return GenerateInitInstanceLocal((::KoaFwdPoint*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaFwdPoint*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaFwdDigi(void *p = 0);
   static void *newArray_KoaFwdDigi(Long_t size, void *p);
   static void delete_KoaFwdDigi(void *p);
   static void deleteArray_KoaFwdDigi(void *p);
   static void destruct_KoaFwdDigi(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaFwdDigi*)
   {
      ::KoaFwdDigi *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaFwdDigi >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaFwdDigi", ::KoaFwdDigi::Class_Version(), "", 403,
                  typeid(::KoaFwdDigi), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaFwdDigi::Dictionary, isa_proxy, 4,
                  sizeof(::KoaFwdDigi) );
      instance.SetNew(&new_KoaFwdDigi);
      instance.SetNewArray(&newArray_KoaFwdDigi);
      instance.SetDelete(&delete_KoaFwdDigi);
      instance.SetDeleteArray(&deleteArray_KoaFwdDigi);
      instance.SetDestructor(&destruct_KoaFwdDigi);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaFwdDigi*)
   {
      return GenerateInitInstanceLocal((::KoaFwdDigi*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaFwdDigi*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaFwdDigitization(void *p = 0);
   static void *newArray_KoaFwdDigitization(Long_t size, void *p);
   static void delete_KoaFwdDigitization(void *p);
   static void deleteArray_KoaFwdDigitization(void *p);
   static void destruct_KoaFwdDigitization(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaFwdDigitization*)
   {
      ::KoaFwdDigitization *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaFwdDigitization >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaFwdDigitization", ::KoaFwdDigitization::Class_Version(), "", 506,
                  typeid(::KoaFwdDigitization), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaFwdDigitization::Dictionary, isa_proxy, 4,
                  sizeof(::KoaFwdDigitization) );
      instance.SetNew(&new_KoaFwdDigitization);
      instance.SetNewArray(&newArray_KoaFwdDigitization);
      instance.SetDelete(&delete_KoaFwdDigitization);
      instance.SetDeleteArray(&deleteArray_KoaFwdDigitization);
      instance.SetDestructor(&destruct_KoaFwdDigitization);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaFwdDigitization*)
   {
      return GenerateInitInstanceLocal((::KoaFwdDigitization*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaFwdDigitization*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaFwdDigitizationPar(void *p = 0);
   static void *newArray_KoaFwdDigitizationPar(Long_t size, void *p);
   static void delete_KoaFwdDigitizationPar(void *p);
   static void deleteArray_KoaFwdDigitizationPar(void *p);
   static void destruct_KoaFwdDigitizationPar(void *p);
   static void streamer_KoaFwdDigitizationPar(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaFwdDigitizationPar*)
   {
      ::KoaFwdDigitizationPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaFwdDigitizationPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaFwdDigitizationPar", ::KoaFwdDigitizationPar::Class_Version(), "", 590,
                  typeid(::KoaFwdDigitizationPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaFwdDigitizationPar::Dictionary, isa_proxy, 16,
                  sizeof(::KoaFwdDigitizationPar) );
      instance.SetNew(&new_KoaFwdDigitizationPar);
      instance.SetNewArray(&newArray_KoaFwdDigitizationPar);
      instance.SetDelete(&delete_KoaFwdDigitizationPar);
      instance.SetDeleteArray(&deleteArray_KoaFwdDigitizationPar);
      instance.SetDestructor(&destruct_KoaFwdDigitizationPar);
      instance.SetStreamerFunc(&streamer_KoaFwdDigitizationPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaFwdDigitizationPar*)
   {
      return GenerateInitInstanceLocal((::KoaFwdDigitizationPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaFwdDigitizationPar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr KoaFwd::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaFwd::Class_Name()
{
   return "KoaFwd";
}

//______________________________________________________________________________
const char *KoaFwd::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwd*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaFwd::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwd*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaFwd::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwd*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaFwd::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwd*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaFwdContFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaFwdContFact::Class_Name()
{
   return "KoaFwdContFact";
}

//______________________________________________________________________________
const char *KoaFwdContFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdContFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaFwdContFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdContFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaFwdContFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdContFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaFwdContFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdContFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaFwdGeo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaFwdGeo::Class_Name()
{
   return "KoaFwdGeo";
}

//______________________________________________________________________________
const char *KoaFwdGeo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdGeo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaFwdGeo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdGeo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaFwdGeo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdGeo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaFwdGeo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdGeo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaFwdGeoPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaFwdGeoPar::Class_Name()
{
   return "KoaFwdGeoPar";
}

//______________________________________________________________________________
const char *KoaFwdGeoPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdGeoPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaFwdGeoPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdGeoPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaFwdGeoPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdGeoPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaFwdGeoPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdGeoPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaFwdMisalignPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaFwdMisalignPar::Class_Name()
{
   return "KoaFwdMisalignPar";
}

//______________________________________________________________________________
const char *KoaFwdMisalignPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdMisalignPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaFwdMisalignPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdMisalignPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaFwdMisalignPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdMisalignPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaFwdMisalignPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdMisalignPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaFwdPoint::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaFwdPoint::Class_Name()
{
   return "KoaFwdPoint";
}

//______________________________________________________________________________
const char *KoaFwdPoint::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdPoint*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaFwdPoint::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdPoint*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaFwdPoint::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdPoint*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaFwdPoint::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdPoint*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaFwdDigi::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaFwdDigi::Class_Name()
{
   return "KoaFwdDigi";
}

//______________________________________________________________________________
const char *KoaFwdDigi::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdDigi*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaFwdDigi::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdDigi*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaFwdDigi::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdDigi*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaFwdDigi::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdDigi*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaFwdDigitization::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaFwdDigitization::Class_Name()
{
   return "KoaFwdDigitization";
}

//______________________________________________________________________________
const char *KoaFwdDigitization::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdDigitization*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaFwdDigitization::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdDigitization*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaFwdDigitization::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdDigitization*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaFwdDigitization::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdDigitization*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaFwdDigitizationPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaFwdDigitizationPar::Class_Name()
{
   return "KoaFwdDigitizationPar";
}

//______________________________________________________________________________
const char *KoaFwdDigitizationPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdDigitizationPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaFwdDigitizationPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdDigitizationPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaFwdDigitizationPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdDigitizationPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaFwdDigitizationPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaFwdDigitizationPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void KoaFwd::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaFwd.

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
      R__b.CheckByteCount(R__s, R__c, KoaFwd::IsA());
   } else {
      R__c = R__b.WriteVersion(KoaFwd::IsA(), kTRUE);
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
   static void *new_KoaFwd(void *p) {
      return  p ? new(p) ::KoaFwd : new ::KoaFwd;
   }
   static void *newArray_KoaFwd(Long_t nElements, void *p) {
      return p ? new(p) ::KoaFwd[nElements] : new ::KoaFwd[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaFwd(void *p) {
      delete ((::KoaFwd*)p);
   }
   static void deleteArray_KoaFwd(void *p) {
      delete [] ((::KoaFwd*)p);
   }
   static void destruct_KoaFwd(void *p) {
      typedef ::KoaFwd current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_KoaFwd(TBuffer &buf, void *obj) {
      ((::KoaFwd*)obj)->::KoaFwd::Streamer(buf);
   }
} // end of namespace ROOT for class ::KoaFwd

//______________________________________________________________________________
void KoaFwdContFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaFwdContFact.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairContFact::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, KoaFwdContFact::IsA());
   } else {
      R__c = R__b.WriteVersion(KoaFwdContFact::IsA(), kTRUE);
      FairContFact::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaFwdContFact(void *p) {
      return  p ? new(p) ::KoaFwdContFact : new ::KoaFwdContFact;
   }
   static void *newArray_KoaFwdContFact(Long_t nElements, void *p) {
      return p ? new(p) ::KoaFwdContFact[nElements] : new ::KoaFwdContFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaFwdContFact(void *p) {
      delete ((::KoaFwdContFact*)p);
   }
   static void deleteArray_KoaFwdContFact(void *p) {
      delete [] ((::KoaFwdContFact*)p);
   }
   static void destruct_KoaFwdContFact(void *p) {
      typedef ::KoaFwdContFact current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_KoaFwdContFact(TBuffer &buf, void *obj) {
      ((::KoaFwdContFact*)obj)->::KoaFwdContFact::Streamer(buf);
   }
} // end of namespace ROOT for class ::KoaFwdContFact

//______________________________________________________________________________
void KoaFwdGeo::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaFwdGeo.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairGeoSet::Streamer(R__b);
      R__b.ReadStaticArray((char*)modName);
      R__b.ReadStaticArray((char*)eleName);
      R__b.CheckByteCount(R__s, R__c, KoaFwdGeo::IsA());
   } else {
      R__c = R__b.WriteVersion(KoaFwdGeo::IsA(), kTRUE);
      FairGeoSet::Streamer(R__b);
      R__b.WriteArray(modName, 20);
      R__b.WriteArray(eleName, 20);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaFwdGeo(void *p) {
      return  p ? new(p) ::KoaFwdGeo : new ::KoaFwdGeo;
   }
   static void *newArray_KoaFwdGeo(Long_t nElements, void *p) {
      return p ? new(p) ::KoaFwdGeo[nElements] : new ::KoaFwdGeo[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaFwdGeo(void *p) {
      delete ((::KoaFwdGeo*)p);
   }
   static void deleteArray_KoaFwdGeo(void *p) {
      delete [] ((::KoaFwdGeo*)p);
   }
   static void destruct_KoaFwdGeo(void *p) {
      typedef ::KoaFwdGeo current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_KoaFwdGeo(TBuffer &buf, void *obj) {
      ((::KoaFwdGeo*)obj)->::KoaFwdGeo::Streamer(buf);
   }
} // end of namespace ROOT for class ::KoaFwdGeo

//______________________________________________________________________________
void KoaFwdGeoPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaFwdGeoPar.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairParGenericSet::Streamer(R__b);
      R__b >> fGeoSensNodes;
      R__b >> fGeoPassNodes;
      R__b.CheckByteCount(R__s, R__c, KoaFwdGeoPar::IsA());
   } else {
      R__c = R__b.WriteVersion(KoaFwdGeoPar::IsA(), kTRUE);
      FairParGenericSet::Streamer(R__b);
      R__b << fGeoSensNodes;
      R__b << fGeoPassNodes;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaFwdGeoPar(void *p) {
      return  p ? new(p) ::KoaFwdGeoPar : new ::KoaFwdGeoPar;
   }
   static void *newArray_KoaFwdGeoPar(Long_t nElements, void *p) {
      return p ? new(p) ::KoaFwdGeoPar[nElements] : new ::KoaFwdGeoPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaFwdGeoPar(void *p) {
      delete ((::KoaFwdGeoPar*)p);
   }
   static void deleteArray_KoaFwdGeoPar(void *p) {
      delete [] ((::KoaFwdGeoPar*)p);
   }
   static void destruct_KoaFwdGeoPar(void *p) {
      typedef ::KoaFwdGeoPar current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_KoaFwdGeoPar(TBuffer &buf, void *obj) {
      ((::KoaFwdGeoPar*)obj)->::KoaFwdGeoPar::Streamer(buf);
   }
} // end of namespace ROOT for class ::KoaFwdGeoPar

//______________________________________________________________________________
void KoaFwdMisalignPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaFwdMisalignPar.

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
      R__b.CheckByteCount(R__s, R__c, KoaFwdMisalignPar::IsA());
   } else {
      R__c = R__b.WriteVersion(KoaFwdMisalignPar::IsA(), kTRUE);
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
   static void *new_KoaFwdMisalignPar(void *p) {
      return  p ? new(p) ::KoaFwdMisalignPar : new ::KoaFwdMisalignPar;
   }
   static void *newArray_KoaFwdMisalignPar(Long_t nElements, void *p) {
      return p ? new(p) ::KoaFwdMisalignPar[nElements] : new ::KoaFwdMisalignPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaFwdMisalignPar(void *p) {
      delete ((::KoaFwdMisalignPar*)p);
   }
   static void deleteArray_KoaFwdMisalignPar(void *p) {
      delete [] ((::KoaFwdMisalignPar*)p);
   }
   static void destruct_KoaFwdMisalignPar(void *p) {
      typedef ::KoaFwdMisalignPar current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_KoaFwdMisalignPar(TBuffer &buf, void *obj) {
      ((::KoaFwdMisalignPar*)obj)->::KoaFwdMisalignPar::Streamer(buf);
   }
} // end of namespace ROOT for class ::KoaFwdMisalignPar

//______________________________________________________________________________
void KoaFwdPoint::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaFwdPoint.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaFwdPoint::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaFwdPoint::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaFwdPoint(void *p) {
      return  p ? new(p) ::KoaFwdPoint : new ::KoaFwdPoint;
   }
   static void *newArray_KoaFwdPoint(Long_t nElements, void *p) {
      return p ? new(p) ::KoaFwdPoint[nElements] : new ::KoaFwdPoint[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaFwdPoint(void *p) {
      delete ((::KoaFwdPoint*)p);
   }
   static void deleteArray_KoaFwdPoint(void *p) {
      delete [] ((::KoaFwdPoint*)p);
   }
   static void destruct_KoaFwdPoint(void *p) {
      typedef ::KoaFwdPoint current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaFwdPoint

//______________________________________________________________________________
void KoaFwdDigi::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaFwdDigi.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaFwdDigi::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaFwdDigi::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaFwdDigi(void *p) {
      return  p ? new(p) ::KoaFwdDigi : new ::KoaFwdDigi;
   }
   static void *newArray_KoaFwdDigi(Long_t nElements, void *p) {
      return p ? new(p) ::KoaFwdDigi[nElements] : new ::KoaFwdDigi[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaFwdDigi(void *p) {
      delete ((::KoaFwdDigi*)p);
   }
   static void deleteArray_KoaFwdDigi(void *p) {
      delete [] ((::KoaFwdDigi*)p);
   }
   static void destruct_KoaFwdDigi(void *p) {
      typedef ::KoaFwdDigi current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaFwdDigi

//______________________________________________________________________________
void KoaFwdDigitization::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaFwdDigitization.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaFwdDigitization::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaFwdDigitization::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaFwdDigitization(void *p) {
      return  p ? new(p) ::KoaFwdDigitization : new ::KoaFwdDigitization;
   }
   static void *newArray_KoaFwdDigitization(Long_t nElements, void *p) {
      return p ? new(p) ::KoaFwdDigitization[nElements] : new ::KoaFwdDigitization[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaFwdDigitization(void *p) {
      delete ((::KoaFwdDigitization*)p);
   }
   static void deleteArray_KoaFwdDigitization(void *p) {
      delete [] ((::KoaFwdDigitization*)p);
   }
   static void destruct_KoaFwdDigitization(void *p) {
      typedef ::KoaFwdDigitization current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaFwdDigitization

//______________________________________________________________________________
void KoaFwdDigitizationPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaFwdDigitizationPar.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairParGenericSet::Streamer(R__b);
      R__b >> fTimeSigma;
      R__b >> fEnergySigma;
      R__b >> fEnergyNoise;
      R__b >> fEnergyNoiseSigma;
      R__b.CheckByteCount(R__s, R__c, KoaFwdDigitizationPar::IsA());
   } else {
      R__c = R__b.WriteVersion(KoaFwdDigitizationPar::IsA(), kTRUE);
      FairParGenericSet::Streamer(R__b);
      R__b << fTimeSigma;
      R__b << fEnergySigma;
      R__b << fEnergyNoise;
      R__b << fEnergyNoiseSigma;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaFwdDigitizationPar(void *p) {
      return  p ? new(p) ::KoaFwdDigitizationPar : new ::KoaFwdDigitizationPar;
   }
   static void *newArray_KoaFwdDigitizationPar(Long_t nElements, void *p) {
      return p ? new(p) ::KoaFwdDigitizationPar[nElements] : new ::KoaFwdDigitizationPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaFwdDigitizationPar(void *p) {
      delete ((::KoaFwdDigitizationPar*)p);
   }
   static void deleteArray_KoaFwdDigitizationPar(void *p) {
      delete [] ((::KoaFwdDigitizationPar*)p);
   }
   static void destruct_KoaFwdDigitizationPar(void *p) {
      typedef ::KoaFwdDigitizationPar current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_KoaFwdDigitizationPar(TBuffer &buf, void *obj) {
      ((::KoaFwdDigitizationPar*)obj)->::KoaFwdDigitizationPar::Streamer(buf);
   }
} // end of namespace ROOT for class ::KoaFwdDigitizationPar

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
   static TClass *maplEintcOKoaFwdStripgR_Dictionary();
   static void maplEintcOKoaFwdStripgR_TClassManip(TClass*);
   static void *new_maplEintcOKoaFwdStripgR(void *p = 0);
   static void *newArray_maplEintcOKoaFwdStripgR(Long_t size, void *p);
   static void delete_maplEintcOKoaFwdStripgR(void *p);
   static void deleteArray_maplEintcOKoaFwdStripgR(void *p);
   static void destruct_maplEintcOKoaFwdStripgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,KoaFwdStrip>*)
   {
      map<int,KoaFwdStrip> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,KoaFwdStrip>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,KoaFwdStrip>", -2, "map", 99,
                  typeid(map<int,KoaFwdStrip>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOKoaFwdStripgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,KoaFwdStrip>) );
      instance.SetNew(&new_maplEintcOKoaFwdStripgR);
      instance.SetNewArray(&newArray_maplEintcOKoaFwdStripgR);
      instance.SetDelete(&delete_maplEintcOKoaFwdStripgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOKoaFwdStripgR);
      instance.SetDestructor(&destruct_maplEintcOKoaFwdStripgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,KoaFwdStrip> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,KoaFwdStrip>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOKoaFwdStripgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,KoaFwdStrip>*)0x0)->GetClass();
      maplEintcOKoaFwdStripgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOKoaFwdStripgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOKoaFwdStripgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,KoaFwdStrip> : new map<int,KoaFwdStrip>;
   }
   static void *newArray_maplEintcOKoaFwdStripgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,KoaFwdStrip>[nElements] : new map<int,KoaFwdStrip>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOKoaFwdStripgR(void *p) {
      delete ((map<int,KoaFwdStrip>*)p);
   }
   static void deleteArray_maplEintcOKoaFwdStripgR(void *p) {
      delete [] ((map<int,KoaFwdStrip>*)p);
   }
   static void destruct_maplEintcOKoaFwdStripgR(void *p) {
      typedef map<int,KoaFwdStrip> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,KoaFwdStrip>

namespace {
  void TriggerDictionaryInitialization_G__KoaScintFwdDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/home/yong/fairroot/v18_jun19/include",
"/home/yong/src/KoalaSoft/detectors/scint-forward",
"/home/yong/src/KoalaSoft/data",
"/home/yong/src/KoalaSoft/tools",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/src/KoalaSoft/build_digi/detectors/scint-forward/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__KoaScintFwdDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class KoaFwd;
class __attribute__((annotate(R"ATTRDUMP(Factory for all KoaRec parameter containers)ATTRDUMP"))) KoaFwdContFact;
class KoaFwdGeo;
class KoaFwdGeoPar;
class KoaFwdMisalignPar;
class KoaFwdPoint;
class KoaFwdDigi;
class KoaFwdDigitization;
class KoaFwdDigitizationPar;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__KoaScintFwdDict dictionary payload"

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
#ifndef KOAFWD_H
#define KOAFWD_H

#include "FairDetector.h"

#include "TVector3.h"
#include "TLorentzVector.h"
#include <string>

class KoaFwdPoint;
class FairVolume;
class TClonesArray;
class KoaGeoHandler;
class KoaFwdMisalignPar;

class KoaFwd: public FairDetector
{

  public:

    /**      Name :  Detector Name
     *       Active: kTRUE for active detectors (ProcessHits() will be called)
     *               kFALSE for inactive detectors
    */
    KoaFwd(const char* Name, Bool_t Active);

    /**      default constructor    */
    KoaFwd();

    /**       destructor     */
    virtual ~KoaFwd();

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
     *       of type KoaFwdPoint to the clones array
    */
    KoaFwdPoint* AddHit(Int_t trackID, Int_t detID,
                             TVector3 pos, TVector3 mom,
                             Double_t time, Double_t length,
                             Double_t eLoss);

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
    TLorentzVector fMom;               //!  momentum at entrance
    Double32_t     fTime;              //!  time
    Double32_t     fLength;            //!  length
    Double32_t     fELoss;             //!  energy loss

    /** container for data points */

    TClonesArray*  fKoaFwdPointCollection;  //!

    KoaGeoHandler* fGeoHandler; //!

    /** parameters related to geometry misalignment **/
    Bool_t fModifyGeometry;

    // parameter container
    KoaFwdMisalignPar* fMisalignPar;

    // Individual Sensor's misalignment
    Int_t fNrOfSensors;
    TArrayD fSensorShiftX;
    TArrayD fSensorShiftY;
    TArrayD fSensorShiftZ;
    TArrayD fSensorRotPhi;
    TArrayD fSensorRotTheta;
    TArrayD fSensorRotPsi;
    
    KoaFwd(const KoaFwd&);
    KoaFwd& operator=(const KoaFwd&);

    ClassDef(KoaFwd,1)
};

#endif //NEWDETECTOR_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAFWDCONTFACT_H
#define KOAFWDCONTFACT_H

#include "FairContFact.h"

class FairContainer;

class KoaFwdContFact : public FairContFact
{
  private:
    void setAllContainers();

  public:
    KoaFwdContFact();
    ~KoaFwdContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( KoaFwdContFact,1) // Factory for all KoaRec parameter containers
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAFWDGEO_H
#define KOAFWDGEO_H

#include "FairGeoSet.h"

class  KoaFwdGeo : public FairGeoSet
{

  protected:
    char modName[20];  // name of module
    char eleName[20];  // substring for elements in module

  public:
    KoaFwdGeo();
    ~KoaFwdGeo() {}
    const char* getModuleName(Int_t);
    const char* getEleName(Int_t);
    inline Int_t getModNumInMod(const TString&);
    ClassDef(KoaFwdGeo,1)
};

inline Int_t KoaFwdGeo::getModNumInMod(const TString& name)
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
#ifndef KOAFWDGEOPAR_H
#define KOAFWDGEOPAR_H

#include "FairParGenericSet.h"

class TObjArray;
class FairParamList;

class KoaFwdGeoPar       : public FairParGenericSet
{
  public:

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoPassNodes;

    KoaFwdGeoPar(const char* name="KoaFwdGeoPar",
                      const char* title="KoaFwd Geometry Parameters",
                      const char* context="TestDefaultContext");
    ~KoaFwdGeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray* GetGeoPassiveNodes()   {return fGeoPassNodes;}

  private:
    KoaFwdGeoPar(const KoaFwdGeoPar&);
    KoaFwdGeoPar& operator=(const KoaFwdGeoPar&);

    ClassDef(KoaFwdGeoPar,1)
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAFWD_MISALIGNPAR_H
#define KOAFWD_MISALIGNPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet

#include "Rtypes.h"                     // for ClassDef

#include "TArrayD.h"                    // for TArrayD

class FairParamList;

class KoaFwdMisalignPar : public FairParGenericSet
{
  public:

    KoaFwdMisalignPar(const char* name="KoaFwdMisalignPar",
                                const char* title="Missalignment parameter for Koala Fwd Detector Module",
                                const char* context="TestDefaultContext");
    ~KoaFwdMisalignPar(void);
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

    KoaFwdMisalignPar(const KoaFwdMisalignPar&);
    KoaFwdMisalignPar& operator=(const KoaFwdMisalignPar&);

    ClassDef(KoaFwdMisalignPar,1)
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAFWDPOINT_H
#define KOAFWDPOINT_H 1


#include "FairMCPoint.h"

#include "TObject.h"
#include "TVector3.h"

class KoaFwdPoint : public FairMCPoint
{

  public:

    /** Default constructor **/
    KoaFwdPoint();


    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Ccoordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    KoaFwdPoint(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom,
                     Double_t tof, Double_t length, Double_t eLoss);




    /** Destructor **/
    virtual ~KoaFwdPoint();

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;

  private:
    /** Copy constructor **/
    KoaFwdPoint(const KoaFwdPoint& point);
    KoaFwdPoint operator=(const KoaFwdPoint& point);

    ClassDef(KoaFwdPoint,1)

};

#endif
// --------------------------------------------------------
// ----			KoaFwdDigi header file	---
// ----			Created 09.10.19 by Y.Zhou ---
// ----     Adopted from PndSdsDigi by T.Stockmanns in PandaRoot ---
// --------------------------------------------------------

/** KoaFwdDigi.h
 *@author Y.Zhou <y.zhou@fz-juelich.de>
 **
 ** \brief Base class for Digi information
 **
 **
 **/

#ifndef KOAFWDDIGI_H
#define KOAFWDDIGI_H

#include "FairTimeStamp.h"
#include "KoaMapEncoder.h"

#include "TObject.h"
#include "TString.h"
#include <iostream>
#include <vector>
#include <boost/serialization/void_cast.hpp>

class KoaFwdDigi : public FairTimeStamp
  {
    friend std::ostream& operator<< (std::ostream& out, KoaFwdDigi& digi){
      KoaMapEncoder *encoder = KoaMapEncoder::Instance();
      Int_t detId;
      encoder->DecodeChannelID(digi.GetDetID(), detId);
      out << "KoaFwdDigi in " << encoder->DetectorIDToVolName(detId) << ": "
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
    KoaFwdDigi();
    KoaFwdDigi(std::vector<Int_t> index, Int_t detID, Double_t charge);
    KoaFwdDigi(Int_t index, Int_t detID, Double_t charge);
		/**<constructor
     * \param index position of PndSdsMCPoint in TClonesArray
     * \param detID detector ID (from/for CbmPoint/Hit)
     * \param charge deposited charge in electrons
     */
		virtual ~KoaFwdDigi(){};
    
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
			boost::serialization::void_cast_register<KoaFwdDigi, FairTimeStamp>();

			ar & boost::serialization::base_object<FairTimeStamp>(*this);
			ar & fDetID;
			ar & fCharge;
		}

  protected:
		friend class boost::serialization::access;

		std::vector<Int_t> fIndex;   // indice of mc points contributing to this digi
		Int_t fDetID;                // branch ID of mc point array
		Double_t fCharge;            // collected charge, could be energy (MeV) in ideal Digitization
    
    ClassDef(KoaFwdDigi,1);
  };

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAFWDDIGITIZATION_H
#define KOAFWDDIGITIZATION_H

#include "FairTask.h"
#include "TRandom3.h"
#include <map>

class TClonesArray;
class KoaMapEncoder;
class KoaFwdPoint;
class KoaFwdDigitizationPar;

struct KoaFwdStrip{
  Double_t fTimestamp;
  Double_t fCharge;
};

using KoaFwdStrips = std::map<Int_t, KoaFwdStrip>;

class KoaFwdDigitization : public FairTask
{
  public:

    /** Default constructor **/
    KoaFwdDigitization();

    /** Constructor with parameters (Optional) **/
    //  KoaFwdDigitization(Int_t verbose);


    /** Destructor **/
    ~KoaFwdDigitization();


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
    void FillFiredStrip(KoaFwdPoint* McPoint);
    void SmearDigis();
    void AddDigis();

  private:
    /** MapEncoder **/
    KoaMapEncoder* fMapEncoder;

    /** Input array from previous already existing data level **/
    TClonesArray* fPoints;

    /** Output array to  new data level**/
    TClonesArray* fDigis;
    KoaFwdStrips  fFiredStrips;

    /** parameters used for time & energy smearing **/
  TRandom3 fRndEngine;
    KoaFwdDigitizationPar* fDigitizationPar;
    Double_t fTimeSigma;
    Double_t fEnergySigma;
    Double_t fEnergyNoise;
    Double_t fEnergyNoiseSigma;

    KoaFwdDigitization(const KoaFwdDigitization&);
    KoaFwdDigitization operator=(const KoaFwdDigitization&);

    ClassDef(KoaFwdDigitization,1);
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAFWD_DIGITIZATIONPAR_H
#define KOAFWD_DIGITIZATIONPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet

#include "Rtypes.h"                     // for ClassDef

#include "TArrayD.h"                    // for TArrayD

class FairParamList;

class KoaFwdDigitizationPar : public FairParGenericSet
{
  public:

    KoaFwdDigitizationPar(const char* name="KoaFwdDigitizationPar",
                                const char* title="Fwd Digitization Parameters",
                                const char* context="TestDefaultContext");
    ~KoaFwdDigitizationPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    Double_t GetTimeSigma() {return fTimeSigma;}
    Double_t GetEnergySigma() {return fEnergySigma;}
    Double_t GetEnergyNoise() {return fEnergyNoise;}
    Double_t GetEnergyNoiseSigma() {return fEnergyNoiseSigma;}

  private:
  Double_t fTimeSigma; // in ns
  Double_t fEnergySigma; // in keV
  Double_t fEnergyNoise; //in keV
  Double_t fEnergyNoiseSigma; // in keV

    KoaFwdDigitizationPar(const KoaFwdDigitizationPar&);
    KoaFwdDigitizationPar& operator=(const KoaFwdDigitizationPar&);

    ClassDef(KoaFwdDigitizationPar,1)
};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"KoaFwd", payloadCode, "@",
"KoaFwdContFact", payloadCode, "@",
"KoaFwdDigi", payloadCode, "@",
"KoaFwdDigitization", payloadCode, "@",
"KoaFwdDigitizationPar", payloadCode, "@",
"KoaFwdGeo", payloadCode, "@",
"KoaFwdGeoPar", payloadCode, "@",
"KoaFwdMisalignPar", payloadCode, "@",
"KoaFwdPoint", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__KoaScintFwdDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__KoaScintFwdDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__KoaScintFwdDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__KoaScintFwdDict() {
  TriggerDictionaryInitialization_G__KoaScintFwdDict_Impl();
}
