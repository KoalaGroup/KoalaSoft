// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_jensdItestdIG__KoaTestDict

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
#include "KoaTest.h"
#include "KoaDumy.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_KoaTest(void *p = 0);
   static void *newArray_KoaTest(Long_t size, void *p);
   static void delete_KoaTest(void *p);
   static void deleteArray_KoaTest(void *p);
   static void destruct_KoaTest(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaTest*)
   {
      ::KoaTest *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaTest >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaTest", ::KoaTest::Class_Version(), "", 10,
                  typeid(::KoaTest), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaTest::Dictionary, isa_proxy, 4,
                  sizeof(::KoaTest) );
      instance.SetNew(&new_KoaTest);
      instance.SetNewArray(&newArray_KoaTest);
      instance.SetDelete(&delete_KoaTest);
      instance.SetDeleteArray(&deleteArray_KoaTest);
      instance.SetDestructor(&destruct_KoaTest);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaTest*)
   {
      return GenerateInitInstanceLocal((::KoaTest*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaTest*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaDummy(void *p = 0);
   static void *newArray_KoaDummy(Long_t size, void *p);
   static void delete_KoaDummy(void *p);
   static void deleteArray_KoaDummy(void *p);
   static void destruct_KoaDummy(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaDummy*)
   {
      ::KoaDummy *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaDummy >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaDummy", ::KoaDummy::Class_Version(), "", 31,
                  typeid(::KoaDummy), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaDummy::Dictionary, isa_proxy, 4,
                  sizeof(::KoaDummy) );
      instance.SetNew(&new_KoaDummy);
      instance.SetNewArray(&newArray_KoaDummy);
      instance.SetDelete(&delete_KoaDummy);
      instance.SetDeleteArray(&deleteArray_KoaDummy);
      instance.SetDestructor(&destruct_KoaDummy);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaDummy*)
   {
      return GenerateInitInstanceLocal((::KoaDummy*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaDummy*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr KoaTest::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaTest::Class_Name()
{
   return "KoaTest";
}

//______________________________________________________________________________
const char *KoaTest::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaTest*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaTest::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaTest*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaTest::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaTest*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaTest::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaTest*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaDummy::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaDummy::Class_Name()
{
   return "KoaDummy";
}

//______________________________________________________________________________
const char *KoaDummy::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaDummy*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaDummy::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaDummy*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaDummy::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaDummy*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaDummy::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaDummy*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void KoaTest::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaTest.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaTest::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaTest::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaTest(void *p) {
      return  p ? new(p) ::KoaTest : new ::KoaTest;
   }
   static void *newArray_KoaTest(Long_t nElements, void *p) {
      return p ? new(p) ::KoaTest[nElements] : new ::KoaTest[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaTest(void *p) {
      delete ((::KoaTest*)p);
   }
   static void deleteArray_KoaTest(void *p) {
      delete [] ((::KoaTest*)p);
   }
   static void destruct_KoaTest(void *p) {
      typedef ::KoaTest current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaTest

//______________________________________________________________________________
void KoaDummy::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaDummy.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaDummy::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaDummy::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaDummy(void *p) {
      return  p ? new(p) ::KoaDummy : new ::KoaDummy;
   }
   static void *newArray_KoaDummy(Long_t nElements, void *p) {
      return p ? new(p) ::KoaDummy[nElements] : new ::KoaDummy[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaDummy(void *p) {
      delete ((::KoaDummy*)p);
   }
   static void deleteArray_KoaDummy(void *p) {
      delete [] ((::KoaDummy*)p);
   }
   static void destruct_KoaDummy(void *p) {
      typedef ::KoaDummy current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaDummy

namespace {
  void TriggerDictionaryInitialization_G__KoaTestDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/home/yong/fairroot/v18_jun19/include",
"/home/yong/src/KoalaSoft/test",
"/home/yong/src/KoalaSoft/tools",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/src/KoalaSoft/build_jens/test/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__KoaTestDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class KoaTest;
class KoaDummy;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__KoaTestDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#ifndef KOA_TEST_H
#define KOA_TEST_H
#include "TObject.h"

class KoaTest : public TObject
{
  
 public:
  KoaTest() {
    
  }
  ~KoaTest() {}

  void Print();

  ClassDef(KoaTest, 1)
};
#endif
#ifndef KOA_DUMMY_H
#define KOA_DUMMY_H

#include "TObject.h"
#include <iostream>

class KoaDummy : public TObject
{
  
 public:
  KoaDummy() {
    
  }
  ~KoaDummy() {}

  void Print() {
    std::cout << "I'm Dummy" << std::endl;
  }

  ClassDef(KoaDummy, 1)
};
#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"KoaDummy", payloadCode, "@",
"KoaTest", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__KoaTestDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__KoaTestDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__KoaTestDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__KoaTestDict() {
  TriggerDictionaryInitialization_G__KoaTestDict_Impl();
}
