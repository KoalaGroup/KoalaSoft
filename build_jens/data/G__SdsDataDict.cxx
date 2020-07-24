// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_jensdIdatadIG__SdsDataDict

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
#include "SdsData/PndSdsMCPoint.h"
#include "SdsData/PndSdsDigi.h"
#include "SdsData/PndSdsPixel.h"
#include "SdsData/PndSdsDigiPixel.h"
#include "SdsData/PndSdsDigiTopix4.h"
#include "SdsData/PndSdsDigiTopix4Header.h"
#include "SdsData/PndSdsCluster.h"
#include "SdsData/PndSdsClusterPixel.h"
#include "SdsData/PndSdsHit.h"
#include "SdsData/PndSdsPidCand.h"
#include "SdsData/PndSdsRadDamHit.h"
#include "SdsData/PndSdsDigiPixelMCInfo.h"
#include "TrackData/PndTrackCand.h"
#include "TrackData/PndTrackCandHit.h"
#include "TrackData/PndTrack.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_PndSdsMCPoint(void *p = 0);
   static void *newArray_PndSdsMCPoint(Long_t size, void *p);
   static void delete_PndSdsMCPoint(void *p);
   static void deleteArray_PndSdsMCPoint(void *p);
   static void destruct_PndSdsMCPoint(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsMCPoint*)
   {
      ::PndSdsMCPoint *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsMCPoint >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsMCPoint", ::PndSdsMCPoint::Class_Version(), "", 32,
                  typeid(::PndSdsMCPoint), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsMCPoint::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsMCPoint) );
      instance.SetNew(&new_PndSdsMCPoint);
      instance.SetNewArray(&newArray_PndSdsMCPoint);
      instance.SetDelete(&delete_PndSdsMCPoint);
      instance.SetDeleteArray(&deleteArray_PndSdsMCPoint);
      instance.SetDestructor(&destruct_PndSdsMCPoint);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsMCPoint*)
   {
      return GenerateInitInstanceLocal((::PndSdsMCPoint*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsMCPoint*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsDigi(void *p = 0);
   static void *newArray_PndSdsDigi(Long_t size, void *p);
   static void delete_PndSdsDigi(void *p);
   static void deleteArray_PndSdsDigi(void *p);
   static void destruct_PndSdsDigi(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsDigi*)
   {
      ::PndSdsDigi *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsDigi >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsDigi", ::PndSdsDigi::Class_Version(), "", 174,
                  typeid(::PndSdsDigi), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsDigi::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsDigi) );
      instance.SetNew(&new_PndSdsDigi);
      instance.SetNewArray(&newArray_PndSdsDigi);
      instance.SetDelete(&delete_PndSdsDigi);
      instance.SetDeleteArray(&deleteArray_PndSdsDigi);
      instance.SetDestructor(&destruct_PndSdsDigi);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsDigi*)
   {
      return GenerateInitInstanceLocal((::PndSdsDigi*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsDigi*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *PndSdsPixel_Dictionary();
   static void PndSdsPixel_TClassManip(TClass*);
   static void *new_PndSdsPixel(void *p = 0);
   static void *newArray_PndSdsPixel(Long_t size, void *p);
   static void delete_PndSdsPixel(void *p);
   static void deleteArray_PndSdsPixel(void *p);
   static void destruct_PndSdsPixel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsPixel*)
   {
      ::PndSdsPixel *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::PndSdsPixel));
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsPixel", "", 274,
                  typeid(::PndSdsPixel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &PndSdsPixel_Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsPixel) );
      instance.SetNew(&new_PndSdsPixel);
      instance.SetNewArray(&newArray_PndSdsPixel);
      instance.SetDelete(&delete_PndSdsPixel);
      instance.SetDeleteArray(&deleteArray_PndSdsPixel);
      instance.SetDestructor(&destruct_PndSdsPixel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsPixel*)
   {
      return GenerateInitInstanceLocal((::PndSdsPixel*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsPixel*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *PndSdsPixel_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::PndSdsPixel*)0x0)->GetClass();
      PndSdsPixel_TClassManip(theClass);
   return theClass;
   }

   static void PndSdsPixel_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsDigiPixel(void *p = 0);
   static void *newArray_PndSdsDigiPixel(Long_t size, void *p);
   static void delete_PndSdsDigiPixel(void *p);
   static void deleteArray_PndSdsDigiPixel(void *p);
   static void destruct_PndSdsDigiPixel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsDigiPixel*)
   {
      ::PndSdsDigiPixel *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsDigiPixel >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsDigiPixel", ::PndSdsDigiPixel::Class_Version(), "", 367,
                  typeid(::PndSdsDigiPixel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsDigiPixel::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsDigiPixel) );
      instance.SetNew(&new_PndSdsDigiPixel);
      instance.SetNewArray(&newArray_PndSdsDigiPixel);
      instance.SetDelete(&delete_PndSdsDigiPixel);
      instance.SetDeleteArray(&deleteArray_PndSdsDigiPixel);
      instance.SetDestructor(&destruct_PndSdsDigiPixel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsDigiPixel*)
   {
      return GenerateInitInstanceLocal((::PndSdsDigiPixel*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsDigiPixel*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsDigiTopix4(void *p = 0);
   static void *newArray_PndSdsDigiTopix4(Long_t size, void *p);
   static void delete_PndSdsDigiTopix4(void *p);
   static void deleteArray_PndSdsDigiTopix4(void *p);
   static void destruct_PndSdsDigiTopix4(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsDigiTopix4*)
   {
      ::PndSdsDigiTopix4 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsDigiTopix4 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsDigiTopix4", ::PndSdsDigiTopix4::Class_Version(), "", 495,
                  typeid(::PndSdsDigiTopix4), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsDigiTopix4::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsDigiTopix4) );
      instance.SetNew(&new_PndSdsDigiTopix4);
      instance.SetNewArray(&newArray_PndSdsDigiTopix4);
      instance.SetDelete(&delete_PndSdsDigiTopix4);
      instance.SetDeleteArray(&deleteArray_PndSdsDigiTopix4);
      instance.SetDestructor(&destruct_PndSdsDigiTopix4);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsDigiTopix4*)
   {
      return GenerateInitInstanceLocal((::PndSdsDigiTopix4*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsDigiTopix4*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsDigiTopix4Header(void *p = 0);
   static void *newArray_PndSdsDigiTopix4Header(Long_t size, void *p);
   static void delete_PndSdsDigiTopix4Header(void *p);
   static void deleteArray_PndSdsDigiTopix4Header(void *p);
   static void destruct_PndSdsDigiTopix4Header(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsDigiTopix4Header*)
   {
      ::PndSdsDigiTopix4Header *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsDigiTopix4Header >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsDigiTopix4Header", ::PndSdsDigiTopix4Header::Class_Version(), "", 595,
                  typeid(::PndSdsDigiTopix4Header), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsDigiTopix4Header::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsDigiTopix4Header) );
      instance.SetNew(&new_PndSdsDigiTopix4Header);
      instance.SetNewArray(&newArray_PndSdsDigiTopix4Header);
      instance.SetDelete(&delete_PndSdsDigiTopix4Header);
      instance.SetDeleteArray(&deleteArray_PndSdsDigiTopix4Header);
      instance.SetDestructor(&destruct_PndSdsDigiTopix4Header);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsDigiTopix4Header*)
   {
      return GenerateInitInstanceLocal((::PndSdsDigiTopix4Header*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsDigiTopix4Header*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_PndSdsCluster(void *p);
   static void deleteArray_PndSdsCluster(void *p);
   static void destruct_PndSdsCluster(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsCluster*)
   {
      ::PndSdsCluster *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsCluster >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsCluster", ::PndSdsCluster::Class_Version(), "", 684,
                  typeid(::PndSdsCluster), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsCluster::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsCluster) );
      instance.SetDelete(&delete_PndSdsCluster);
      instance.SetDeleteArray(&deleteArray_PndSdsCluster);
      instance.SetDestructor(&destruct_PndSdsCluster);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsCluster*)
   {
      return GenerateInitInstanceLocal((::PndSdsCluster*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsCluster*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsClusterPixel(void *p = 0);
   static void *newArray_PndSdsClusterPixel(Long_t size, void *p);
   static void delete_PndSdsClusterPixel(void *p);
   static void deleteArray_PndSdsClusterPixel(void *p);
   static void destruct_PndSdsClusterPixel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsClusterPixel*)
   {
      ::PndSdsClusterPixel *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsClusterPixel >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsClusterPixel", ::PndSdsClusterPixel::Class_Version(), "", 733,
                  typeid(::PndSdsClusterPixel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsClusterPixel::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsClusterPixel) );
      instance.SetNew(&new_PndSdsClusterPixel);
      instance.SetNewArray(&newArray_PndSdsClusterPixel);
      instance.SetDelete(&delete_PndSdsClusterPixel);
      instance.SetDeleteArray(&deleteArray_PndSdsClusterPixel);
      instance.SetDestructor(&destruct_PndSdsClusterPixel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsClusterPixel*)
   {
      return GenerateInitInstanceLocal((::PndSdsClusterPixel*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsClusterPixel*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsHit(void *p = 0);
   static void *newArray_PndSdsHit(Long_t size, void *p);
   static void delete_PndSdsHit(void *p);
   static void deleteArray_PndSdsHit(void *p);
   static void destruct_PndSdsHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsHit*)
   {
      ::PndSdsHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsHit", ::PndSdsHit::Class_Version(), "", 780,
                  typeid(::PndSdsHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsHit::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsHit) );
      instance.SetNew(&new_PndSdsHit);
      instance.SetNewArray(&newArray_PndSdsHit);
      instance.SetDelete(&delete_PndSdsHit);
      instance.SetDeleteArray(&deleteArray_PndSdsHit);
      instance.SetDestructor(&destruct_PndSdsHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsHit*)
   {
      return GenerateInitInstanceLocal((::PndSdsHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsHit*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsPidCand(void *p = 0);
   static void *newArray_PndSdsPidCand(Long_t size, void *p);
   static void delete_PndSdsPidCand(void *p);
   static void deleteArray_PndSdsPidCand(void *p);
   static void destruct_PndSdsPidCand(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsPidCand*)
   {
      ::PndSdsPidCand *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsPidCand >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsPidCand", ::PndSdsPidCand::Class_Version(), "", 938,
                  typeid(::PndSdsPidCand), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsPidCand::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsPidCand) );
      instance.SetNew(&new_PndSdsPidCand);
      instance.SetNewArray(&newArray_PndSdsPidCand);
      instance.SetDelete(&delete_PndSdsPidCand);
      instance.SetDeleteArray(&deleteArray_PndSdsPidCand);
      instance.SetDestructor(&destruct_PndSdsPidCand);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsPidCand*)
   {
      return GenerateInitInstanceLocal((::PndSdsPidCand*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsPidCand*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsRadDamHit(void *p = 0);
   static void *newArray_PndSdsRadDamHit(Long_t size, void *p);
   static void delete_PndSdsRadDamHit(void *p);
   static void deleteArray_PndSdsRadDamHit(void *p);
   static void destruct_PndSdsRadDamHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsRadDamHit*)
   {
      ::PndSdsRadDamHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsRadDamHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsRadDamHit", ::PndSdsRadDamHit::Class_Version(), "", 1003,
                  typeid(::PndSdsRadDamHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsRadDamHit::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsRadDamHit) );
      instance.SetNew(&new_PndSdsRadDamHit);
      instance.SetNewArray(&newArray_PndSdsRadDamHit);
      instance.SetDelete(&delete_PndSdsRadDamHit);
      instance.SetDeleteArray(&deleteArray_PndSdsRadDamHit);
      instance.SetDestructor(&destruct_PndSdsRadDamHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsRadDamHit*)
   {
      return GenerateInitInstanceLocal((::PndSdsRadDamHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsRadDamHit*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndSdsDigiPixelMCInfo(void *p = 0);
   static void *newArray_PndSdsDigiPixelMCInfo(Long_t size, void *p);
   static void delete_PndSdsDigiPixelMCInfo(void *p);
   static void deleteArray_PndSdsDigiPixelMCInfo(void *p);
   static void destruct_PndSdsDigiPixelMCInfo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndSdsDigiPixelMCInfo*)
   {
      ::PndSdsDigiPixelMCInfo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndSdsDigiPixelMCInfo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndSdsDigiPixelMCInfo", ::PndSdsDigiPixelMCInfo::Class_Version(), "", 1047,
                  typeid(::PndSdsDigiPixelMCInfo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndSdsDigiPixelMCInfo::Dictionary, isa_proxy, 4,
                  sizeof(::PndSdsDigiPixelMCInfo) );
      instance.SetNew(&new_PndSdsDigiPixelMCInfo);
      instance.SetNewArray(&newArray_PndSdsDigiPixelMCInfo);
      instance.SetDelete(&delete_PndSdsDigiPixelMCInfo);
      instance.SetDeleteArray(&deleteArray_PndSdsDigiPixelMCInfo);
      instance.SetDestructor(&destruct_PndSdsDigiPixelMCInfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndSdsDigiPixelMCInfo*)
   {
      return GenerateInitInstanceLocal((::PndSdsDigiPixelMCInfo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndSdsDigiPixelMCInfo*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndTrackCandHit(void *p = 0);
   static void *newArray_PndTrackCandHit(Long_t size, void *p);
   static void delete_PndTrackCandHit(void *p);
   static void deleteArray_PndTrackCandHit(void *p);
   static void destruct_PndTrackCandHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndTrackCandHit*)
   {
      ::PndTrackCandHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndTrackCandHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndTrackCandHit", ::PndTrackCandHit::Class_Version(), "PndTrackCandHit.h", 35,
                  typeid(::PndTrackCandHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndTrackCandHit::Dictionary, isa_proxy, 4,
                  sizeof(::PndTrackCandHit) );
      instance.SetNew(&new_PndTrackCandHit);
      instance.SetNewArray(&newArray_PndTrackCandHit);
      instance.SetDelete(&delete_PndTrackCandHit);
      instance.SetDeleteArray(&deleteArray_PndTrackCandHit);
      instance.SetDestructor(&destruct_PndTrackCandHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndTrackCandHit*)
   {
      return GenerateInitInstanceLocal((::PndTrackCandHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndTrackCandHit*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndTrackCand(void *p = 0);
   static void *newArray_PndTrackCand(Long_t size, void *p);
   static void delete_PndTrackCand(void *p);
   static void deleteArray_PndTrackCand(void *p);
   static void destruct_PndTrackCand(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndTrackCand*)
   {
      ::PndTrackCand *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndTrackCand >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndTrackCand", ::PndTrackCand::Class_Version(), "", 1144,
                  typeid(::PndTrackCand), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndTrackCand::Dictionary, isa_proxy, 4,
                  sizeof(::PndTrackCand) );
      instance.SetNew(&new_PndTrackCand);
      instance.SetNewArray(&newArray_PndTrackCand);
      instance.SetDelete(&delete_PndTrackCand);
      instance.SetDeleteArray(&deleteArray_PndTrackCand);
      instance.SetDestructor(&destruct_PndTrackCand);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndTrackCand*)
   {
      return GenerateInitInstanceLocal((::PndTrackCand*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndTrackCand*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndTrack(void *p = 0);
   static void *newArray_PndTrack(Long_t size, void *p);
   static void delete_PndTrack(void *p);
   static void deleteArray_PndTrack(void *p);
   static void destruct_PndTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndTrack*)
   {
      ::PndTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndTrack", ::PndTrack::Class_Version(), "", 1313,
                  typeid(::PndTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndTrack::Dictionary, isa_proxy, 4,
                  sizeof(::PndTrack) );
      instance.SetNew(&new_PndTrack);
      instance.SetNewArray(&newArray_PndTrack);
      instance.SetDelete(&delete_PndTrack);
      instance.SetDeleteArray(&deleteArray_PndTrack);
      instance.SetDestructor(&destruct_PndTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndTrack*)
   {
      return GenerateInitInstanceLocal((::PndTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndTrack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr PndSdsMCPoint::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsMCPoint::Class_Name()
{
   return "PndSdsMCPoint";
}

//______________________________________________________________________________
const char *PndSdsMCPoint::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsMCPoint*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsMCPoint::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsMCPoint*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsMCPoint::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsMCPoint*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsMCPoint::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsMCPoint*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsDigi::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsDigi::Class_Name()
{
   return "PndSdsDigi";
}

//______________________________________________________________________________
const char *PndSdsDigi::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigi*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsDigi::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigi*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsDigi::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigi*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsDigi::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigi*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsDigiPixel::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsDigiPixel::Class_Name()
{
   return "PndSdsDigiPixel";
}

//______________________________________________________________________________
const char *PndSdsDigiPixel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixel*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsDigiPixel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixel*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsDigiPixel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixel*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsDigiPixel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixel*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsDigiTopix4::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsDigiTopix4::Class_Name()
{
   return "PndSdsDigiTopix4";
}

//______________________________________________________________________________
const char *PndSdsDigiTopix4::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiTopix4*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsDigiTopix4::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiTopix4*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsDigiTopix4::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiTopix4*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsDigiTopix4::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiTopix4*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsDigiTopix4Header::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsDigiTopix4Header::Class_Name()
{
   return "PndSdsDigiTopix4Header";
}

//______________________________________________________________________________
const char *PndSdsDigiTopix4Header::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiTopix4Header*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsDigiTopix4Header::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiTopix4Header*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsDigiTopix4Header::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiTopix4Header*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsDigiTopix4Header::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiTopix4Header*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsCluster::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsCluster::Class_Name()
{
   return "PndSdsCluster";
}

//______________________________________________________________________________
const char *PndSdsCluster::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsCluster*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsCluster::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsCluster*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsCluster::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsCluster*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsCluster::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsCluster*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsClusterPixel::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsClusterPixel::Class_Name()
{
   return "PndSdsClusterPixel";
}

//______________________________________________________________________________
const char *PndSdsClusterPixel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsClusterPixel*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsClusterPixel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsClusterPixel*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsClusterPixel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsClusterPixel*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsClusterPixel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsClusterPixel*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsHit::Class_Name()
{
   return "PndSdsHit";
}

//______________________________________________________________________________
const char *PndSdsHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsPidCand::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsPidCand::Class_Name()
{
   return "PndSdsPidCand";
}

//______________________________________________________________________________
const char *PndSdsPidCand::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPidCand*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsPidCand::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPidCand*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsPidCand::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPidCand*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsPidCand::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsPidCand*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsRadDamHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsRadDamHit::Class_Name()
{
   return "PndSdsRadDamHit";
}

//______________________________________________________________________________
const char *PndSdsRadDamHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsRadDamHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsRadDamHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsRadDamHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsRadDamHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsRadDamHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsRadDamHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsRadDamHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndSdsDigiPixelMCInfo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndSdsDigiPixelMCInfo::Class_Name()
{
   return "PndSdsDigiPixelMCInfo";
}

//______________________________________________________________________________
const char *PndSdsDigiPixelMCInfo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelMCInfo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndSdsDigiPixelMCInfo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelMCInfo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndSdsDigiPixelMCInfo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelMCInfo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndSdsDigiPixelMCInfo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndSdsDigiPixelMCInfo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndTrackCandHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndTrackCandHit::Class_Name()
{
   return "PndTrackCandHit";
}

//______________________________________________________________________________
const char *PndTrackCandHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndTrackCandHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndTrackCandHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndTrackCandHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndTrackCandHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndTrackCandHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndTrackCandHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndTrackCandHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndTrackCand::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndTrackCand::Class_Name()
{
   return "PndTrackCand";
}

//______________________________________________________________________________
const char *PndTrackCand::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndTrackCand*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndTrackCand::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndTrackCand*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndTrackCand::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndTrackCand*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndTrackCand::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndTrackCand*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndTrack::Class_Name()
{
   return "PndTrack";
}

//______________________________________________________________________________
const char *PndTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void PndSdsMCPoint::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsMCPoint.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsMCPoint::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsMCPoint::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsMCPoint(void *p) {
      return  p ? new(p) ::PndSdsMCPoint : new ::PndSdsMCPoint;
   }
   static void *newArray_PndSdsMCPoint(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsMCPoint[nElements] : new ::PndSdsMCPoint[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsMCPoint(void *p) {
      delete ((::PndSdsMCPoint*)p);
   }
   static void deleteArray_PndSdsMCPoint(void *p) {
      delete [] ((::PndSdsMCPoint*)p);
   }
   static void destruct_PndSdsMCPoint(void *p) {
      typedef ::PndSdsMCPoint current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsMCPoint

//______________________________________________________________________________
void PndSdsDigi::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsDigi.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsDigi::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsDigi::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsDigi(void *p) {
      return  p ? new(p) ::PndSdsDigi : new ::PndSdsDigi;
   }
   static void *newArray_PndSdsDigi(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsDigi[nElements] : new ::PndSdsDigi[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsDigi(void *p) {
      delete ((::PndSdsDigi*)p);
   }
   static void deleteArray_PndSdsDigi(void *p) {
      delete [] ((::PndSdsDigi*)p);
   }
   static void destruct_PndSdsDigi(void *p) {
      typedef ::PndSdsDigi current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsDigi

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsPixel(void *p) {
      return  p ? new(p) ::PndSdsPixel : new ::PndSdsPixel;
   }
   static void *newArray_PndSdsPixel(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsPixel[nElements] : new ::PndSdsPixel[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsPixel(void *p) {
      delete ((::PndSdsPixel*)p);
   }
   static void deleteArray_PndSdsPixel(void *p) {
      delete [] ((::PndSdsPixel*)p);
   }
   static void destruct_PndSdsPixel(void *p) {
      typedef ::PndSdsPixel current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsPixel

//______________________________________________________________________________
void PndSdsDigiPixel::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsDigiPixel.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsDigiPixel::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsDigiPixel::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsDigiPixel(void *p) {
      return  p ? new(p) ::PndSdsDigiPixel : new ::PndSdsDigiPixel;
   }
   static void *newArray_PndSdsDigiPixel(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsDigiPixel[nElements] : new ::PndSdsDigiPixel[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsDigiPixel(void *p) {
      delete ((::PndSdsDigiPixel*)p);
   }
   static void deleteArray_PndSdsDigiPixel(void *p) {
      delete [] ((::PndSdsDigiPixel*)p);
   }
   static void destruct_PndSdsDigiPixel(void *p) {
      typedef ::PndSdsDigiPixel current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsDigiPixel

//______________________________________________________________________________
void PndSdsDigiTopix4::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsDigiTopix4.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsDigiTopix4::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsDigiTopix4::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsDigiTopix4(void *p) {
      return  p ? new(p) ::PndSdsDigiTopix4 : new ::PndSdsDigiTopix4;
   }
   static void *newArray_PndSdsDigiTopix4(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsDigiTopix4[nElements] : new ::PndSdsDigiTopix4[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsDigiTopix4(void *p) {
      delete ((::PndSdsDigiTopix4*)p);
   }
   static void deleteArray_PndSdsDigiTopix4(void *p) {
      delete [] ((::PndSdsDigiTopix4*)p);
   }
   static void destruct_PndSdsDigiTopix4(void *p) {
      typedef ::PndSdsDigiTopix4 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsDigiTopix4

//______________________________________________________________________________
void PndSdsDigiTopix4Header::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsDigiTopix4Header.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsDigiTopix4Header::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsDigiTopix4Header::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsDigiTopix4Header(void *p) {
      return  p ? new(p) ::PndSdsDigiTopix4Header : new ::PndSdsDigiTopix4Header;
   }
   static void *newArray_PndSdsDigiTopix4Header(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsDigiTopix4Header[nElements] : new ::PndSdsDigiTopix4Header[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsDigiTopix4Header(void *p) {
      delete ((::PndSdsDigiTopix4Header*)p);
   }
   static void deleteArray_PndSdsDigiTopix4Header(void *p) {
      delete [] ((::PndSdsDigiTopix4Header*)p);
   }
   static void destruct_PndSdsDigiTopix4Header(void *p) {
      typedef ::PndSdsDigiTopix4Header current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsDigiTopix4Header

//______________________________________________________________________________
void PndSdsCluster::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsCluster.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsCluster::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsCluster::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_PndSdsCluster(void *p) {
      delete ((::PndSdsCluster*)p);
   }
   static void deleteArray_PndSdsCluster(void *p) {
      delete [] ((::PndSdsCluster*)p);
   }
   static void destruct_PndSdsCluster(void *p) {
      typedef ::PndSdsCluster current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsCluster

//______________________________________________________________________________
void PndSdsClusterPixel::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsClusterPixel.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsClusterPixel::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsClusterPixel::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsClusterPixel(void *p) {
      return  p ? new(p) ::PndSdsClusterPixel : new ::PndSdsClusterPixel;
   }
   static void *newArray_PndSdsClusterPixel(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsClusterPixel[nElements] : new ::PndSdsClusterPixel[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsClusterPixel(void *p) {
      delete ((::PndSdsClusterPixel*)p);
   }
   static void deleteArray_PndSdsClusterPixel(void *p) {
      delete [] ((::PndSdsClusterPixel*)p);
   }
   static void destruct_PndSdsClusterPixel(void *p) {
      typedef ::PndSdsClusterPixel current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsClusterPixel

//______________________________________________________________________________
void PndSdsHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsHit(void *p) {
      return  p ? new(p) ::PndSdsHit : new ::PndSdsHit;
   }
   static void *newArray_PndSdsHit(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsHit[nElements] : new ::PndSdsHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsHit(void *p) {
      delete ((::PndSdsHit*)p);
   }
   static void deleteArray_PndSdsHit(void *p) {
      delete [] ((::PndSdsHit*)p);
   }
   static void destruct_PndSdsHit(void *p) {
      typedef ::PndSdsHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsHit

//______________________________________________________________________________
void PndSdsPidCand::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsPidCand.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsPidCand::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsPidCand::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsPidCand(void *p) {
      return  p ? new(p) ::PndSdsPidCand : new ::PndSdsPidCand;
   }
   static void *newArray_PndSdsPidCand(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsPidCand[nElements] : new ::PndSdsPidCand[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsPidCand(void *p) {
      delete ((::PndSdsPidCand*)p);
   }
   static void deleteArray_PndSdsPidCand(void *p) {
      delete [] ((::PndSdsPidCand*)p);
   }
   static void destruct_PndSdsPidCand(void *p) {
      typedef ::PndSdsPidCand current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsPidCand

//______________________________________________________________________________
void PndSdsRadDamHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsRadDamHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsRadDamHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsRadDamHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsRadDamHit(void *p) {
      return  p ? new(p) ::PndSdsRadDamHit : new ::PndSdsRadDamHit;
   }
   static void *newArray_PndSdsRadDamHit(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsRadDamHit[nElements] : new ::PndSdsRadDamHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsRadDamHit(void *p) {
      delete ((::PndSdsRadDamHit*)p);
   }
   static void deleteArray_PndSdsRadDamHit(void *p) {
      delete [] ((::PndSdsRadDamHit*)p);
   }
   static void destruct_PndSdsRadDamHit(void *p) {
      typedef ::PndSdsRadDamHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsRadDamHit

//______________________________________________________________________________
void PndSdsDigiPixelMCInfo::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndSdsDigiPixelMCInfo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndSdsDigiPixelMCInfo::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndSdsDigiPixelMCInfo::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndSdsDigiPixelMCInfo(void *p) {
      return  p ? new(p) ::PndSdsDigiPixelMCInfo : new ::PndSdsDigiPixelMCInfo;
   }
   static void *newArray_PndSdsDigiPixelMCInfo(Long_t nElements, void *p) {
      return p ? new(p) ::PndSdsDigiPixelMCInfo[nElements] : new ::PndSdsDigiPixelMCInfo[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndSdsDigiPixelMCInfo(void *p) {
      delete ((::PndSdsDigiPixelMCInfo*)p);
   }
   static void deleteArray_PndSdsDigiPixelMCInfo(void *p) {
      delete [] ((::PndSdsDigiPixelMCInfo*)p);
   }
   static void destruct_PndSdsDigiPixelMCInfo(void *p) {
      typedef ::PndSdsDigiPixelMCInfo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndSdsDigiPixelMCInfo

//______________________________________________________________________________
void PndTrackCandHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndTrackCandHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndTrackCandHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndTrackCandHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndTrackCandHit(void *p) {
      return  p ? new(p) ::PndTrackCandHit : new ::PndTrackCandHit;
   }
   static void *newArray_PndTrackCandHit(Long_t nElements, void *p) {
      return p ? new(p) ::PndTrackCandHit[nElements] : new ::PndTrackCandHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndTrackCandHit(void *p) {
      delete ((::PndTrackCandHit*)p);
   }
   static void deleteArray_PndTrackCandHit(void *p) {
      delete [] ((::PndTrackCandHit*)p);
   }
   static void destruct_PndTrackCandHit(void *p) {
      typedef ::PndTrackCandHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndTrackCandHit

//______________________________________________________________________________
void PndTrackCand::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndTrackCand.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndTrackCand::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndTrackCand::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndTrackCand(void *p) {
      return  p ? new(p) ::PndTrackCand : new ::PndTrackCand;
   }
   static void *newArray_PndTrackCand(Long_t nElements, void *p) {
      return p ? new(p) ::PndTrackCand[nElements] : new ::PndTrackCand[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndTrackCand(void *p) {
      delete ((::PndTrackCand*)p);
   }
   static void deleteArray_PndTrackCand(void *p) {
      delete [] ((::PndTrackCand*)p);
   }
   static void destruct_PndTrackCand(void *p) {
      typedef ::PndTrackCand current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndTrackCand

//______________________________________________________________________________
void PndTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndTrack(void *p) {
      return  p ? new(p) ::PndTrack : new ::PndTrack;
   }
   static void *newArray_PndTrack(Long_t nElements, void *p) {
      return p ? new(p) ::PndTrack[nElements] : new ::PndTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndTrack(void *p) {
      delete ((::PndTrack*)p);
   }
   static void deleteArray_PndTrack(void *p) {
      delete [] ((::PndTrack*)p);
   }
   static void destruct_PndTrack(void *p) {
      typedef ::PndTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndTrack

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
   static TClass *vectorlEPndTrackCandHitgR_Dictionary();
   static void vectorlEPndTrackCandHitgR_TClassManip(TClass*);
   static void *new_vectorlEPndTrackCandHitgR(void *p = 0);
   static void *newArray_vectorlEPndTrackCandHitgR(Long_t size, void *p);
   static void delete_vectorlEPndTrackCandHitgR(void *p);
   static void deleteArray_vectorlEPndTrackCandHitgR(void *p);
   static void destruct_vectorlEPndTrackCandHitgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<PndTrackCandHit>*)
   {
      vector<PndTrackCandHit> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<PndTrackCandHit>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<PndTrackCandHit>", -2, "vector", 216,
                  typeid(vector<PndTrackCandHit>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEPndTrackCandHitgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<PndTrackCandHit>) );
      instance.SetNew(&new_vectorlEPndTrackCandHitgR);
      instance.SetNewArray(&newArray_vectorlEPndTrackCandHitgR);
      instance.SetDelete(&delete_vectorlEPndTrackCandHitgR);
      instance.SetDeleteArray(&deleteArray_vectorlEPndTrackCandHitgR);
      instance.SetDestructor(&destruct_vectorlEPndTrackCandHitgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<PndTrackCandHit> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<PndTrackCandHit>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPndTrackCandHitgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<PndTrackCandHit>*)0x0)->GetClass();
      vectorlEPndTrackCandHitgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPndTrackCandHitgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPndTrackCandHitgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<PndTrackCandHit> : new vector<PndTrackCandHit>;
   }
   static void *newArray_vectorlEPndTrackCandHitgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<PndTrackCandHit>[nElements] : new vector<PndTrackCandHit>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPndTrackCandHitgR(void *p) {
      delete ((vector<PndTrackCandHit>*)p);
   }
   static void deleteArray_vectorlEPndTrackCandHitgR(void *p) {
      delete [] ((vector<PndTrackCandHit>*)p);
   }
   static void destruct_vectorlEPndTrackCandHitgR(void *p) {
      typedef vector<PndTrackCandHit> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<PndTrackCandHit>

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
  void TriggerDictionaryInitialization_G__SdsDataDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/home/yong/fairroot/v18_jun19/include",
"/home/yong/src/KoalaSoft/data",
"/home/yong/src/KoalaSoft/data/SdsData",
"/home/yong/src/KoalaSoft/data/TrackData",
"/home/yong/src/KoalaSoft/data/MCData",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/src/KoalaSoft/build_jens/data/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__SdsDataDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class PndSdsMCPoint;
class PndSdsDigi;
class PndSdsPixel;
class PndSdsDigiPixel;
class PndSdsDigiTopix4;
class PndSdsDigiTopix4Header;
class PndSdsCluster;
class PndSdsClusterPixel;
class PndSdsHit;
class PndSdsPidCand;
class PndSdsRadDamHit;
class PndSdsDigiPixelMCInfo;
class __attribute__((annotate("$clingAutoload$PndTrackCandHit.h")))  PndTrackCandHit;
class PndTrackCand;
class PndTrack;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__SdsDataDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
/**  PndSdsMCPoint.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 *
 * Interception of MC track with a SSD detetcor. Holds in addition
 * to the base class the coordinates and momentum at the exit from
 * the active volume.
 **/


#ifndef PNDSDSMCPOINT_H
#define PNDSDSMCPOINT_H


#include "TObject.h"
#include "TVector3.h"
#include "FairMCPoint.h"
#include "TString.h"
#include "KoaDetectorList.h" 

#include <stdio.h>
#include <iostream>

using namespace std;



class PndSdsMCPoint : public FairMCPoint
{
  friend std::ostream& operator<< (std::ostream& out, const PndSdsMCPoint& point){
    out << "-I- PndSdsMCPoint: PndSds Point for track " << point.GetTrackID()
         << " in detector " << point.GetDetectorID() << " with sensor "
       << point.GetSensorID() << std::endl;
    out << "    Position in  (" << point.GetX() << ", " << point.GetY() << ", " << point.GetZ() << ") cm" << std::endl;
    out << "    Position out (" << point.GetXOut() << ", " << point.GetYOut() << ", " << point.GetZOut() << ") cm" << std::endl;
    out << "    Momentum (" << point.GetPx() << ", " << point.GetPy() << ", " << point.GetPz() << ") GeV" << std::endl;
    out << "    Time " << point.GetTime() << " ns,  Length " << point.GetLength() << " cm,  Energy loss " << point.GetEnergyLoss()*1.0e06 << " keV" << std::endl;
    return out;
  }

 public:

  /** Default constructor **/
  PndSdsMCPoint();


  /** Constructor with arguments
   *@param trackID       Index of MCTrack
   *@param detID         Detector ID
   *@param sensorID		   Full nameId of the detector, see PndSdsGeoHandling
   *@param posIn         Coordinates of ingoing point[cm]
   *@param posOut	 Coordinates of outgoing point[cm]
   *@param momIn         Momentum of track at entrance [GeV]
   *@param momOut        Momentum of track at exit [GeV]
   *@param tof           Time since event start [ns]
   *@param length        Track length since creation [cm]
   *@param eLoss         Energy deposit [GeV]
   **/
  PndSdsMCPoint(Int_t trackID, Int_t detID, Int_t sensorID,
  	      TVector3 posIn, TVector3 posOut,
	      TVector3 momIn, TVector3 momOut,
	      Double_t tof, Double_t length, Double_t eLoss);


  /** Copy constructor **/
  PndSdsMCPoint(const PndSdsMCPoint& point) : FairMCPoint(point),
  fXfOut(point.fXfOut),
  fYfOut(point.fYfOut),
  fZfOut(point.fZfOut),
  fPxfOut(point.fPxfOut),
  fPyfOut(point.fPyfOut),
  fPzfOut(point.fPzfOut),
  fSensorID(point.fSensorID)
  { *this = point; };


  /** Destructor **/
  virtual ~PndSdsMCPoint();


  /** Accessors **/
  Double_t GetXOut() const { return fXfOut;};
  Double_t GetYOut() const { return fYfOut;};
  Double_t GetZOut() const { return fZfOut;};

  Double_t GetPxOut() const { return fPxfOut; }
  Double_t GetPyOut() const { return fPyfOut; }
  Double_t GetPzOut() const { return fPzfOut; }
 // TString  GetDetName() const { return fDetName;}
  Int_t GetSensorID() const { return fSensorID;}
  TVector3 GetPosition() const { return TVector3(fX, fY, fZ);}
  TVector3 GetPositionOut() const { return TVector3(fXfOut, fYfOut, fZfOut);}

  void PositionOut(TVector3& pos) const { pos.SetXYZ(fXfOut, fYfOut, fZfOut);};
  void MomentumOut(TVector3& mom) const { mom.SetXYZ(fPxfOut,fPyfOut,fPzfOut); }


  /** Modifiers **/
  void SetPositionOut(TVector3 pos);
  void SetMomentumOut(TVector3 mom);
  //void SetDetName(TString name) {fDetName = name;};
  void SetSensorID(Int_t sensorID){fSensorID = sensorID;}
  virtual void SetTrackID(Int_t id){ 
          //SetLink("MCTrack", id);
          FairMCPoint::SetTrackID(id); 
  }; 


  /** Output to screen **/
  virtual void Print(const Option_t* opt = 0) const;


 protected:

  Double32_t fXfOut, fYfOut, fZfOut;

  Double32_t fPxfOut, fPyfOut, fPzfOut;
  Int_t fSensorID;


  ClassDef(PndSdsMCPoint,6);

};

inline void PndSdsMCPoint::SetPositionOut(TVector3 pos) {
	fXfOut = pos.X();
	fYfOut = pos.Y();
	fZfOut = pos.Z();
}


inline void PndSdsMCPoint::SetMomentumOut(TVector3 mom) {
  fPxfOut = mom.Px();
  fPyfOut = mom.Py();
  fPzfOut = mom.Pz();
}



#endif
// --------------------------------------------------------
// ----			PndSdsDigi header file	---
// ----			Created 19.10.07 by T.Stockmanns ---
// --------------------------------------------------------

/** PndSdsDigi.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** \brief Base class for Digi information
 **
 **
 **/

#ifndef PNDSDSDIGI_H
#define PNDSDSDIGI_H

#include "FairTimeStamp.h"

#include "TObject.h"
#include "TString.h"
#include "KoaDetectorList.h" 
#include <iostream>
#include <vector>

#ifndef __CINT__ // for BOOST serialization
	#include <boost/serialization/void_cast.hpp>
#endif // for BOOST serialization

class PndSdsDigi : public FairTimeStamp
  {
    friend std::ostream& operator<< (std::ostream& out, PndSdsDigi& digi){
      out << "PndSds Digi in sensor: " << digi.GetSensorID() << " FE: "
      << digi.GetFE() << " "
      << " charge: " << digi.GetCharge() << " e"
      << " timestamp: "<<digi.GetTimeStamp()
      << ", from Point(s): ";
      std::vector<Int_t> indices = digi.GetIndices();
      for (unsigned int i = 0; i < indices.size(); i++){
        std::cout << digi.GetIndex(i) << " " << std::endl;
      }
      return out;
    }
    
  public: 
    PndSdsDigi();
    PndSdsDigi(std::vector<Int_t> index, Int_t detID, Int_t sensorID, Int_t fe, Double_t charge, Double_t timestamp = -1);
    PndSdsDigi(Int_t index, Int_t detID, Int_t fSensorID, Int_t fe, Double_t charge, Double_t timestamp = -1);
		/**<constructor
     * \param index position of PndSdsMCPoint in TClonesArray
     * \param detID detector ID (from/for CbmPoint/Hit)
     * \param detName geoH->GetID(gGeoManager->GetPath()) information
     * \param fe front end ID
     * \param charge deposited charge in electrons
     */
		virtual ~PndSdsDigi(){};
    
		Int_t GetFE() const { return fFE;}
		//TString GetDetName()   const { return fDetName; }
		Int_t GetSensorID() const { return fSensorID; }
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

    virtual bool operator<(const PndSdsDigi& myDigi) const{
    	if (fDetID < myDigi.GetDetID()) 		return true;	else if(fDetID > myDigi.GetDetID()) return false;
		if (fSensorID < myDigi.GetSensorID()) 	return true; 	else if (fSensorID > myDigi.GetSensorID()) return false;
		if (fFE < myDigi.GetFE()) 				return true;	else if (fFE > myDigi.GetFE()) return false;
    	return false;
    }

		virtual void Print() {
			std::cout << *this;
		}

	#ifndef __CINT__ // for BOOST serialization
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			boost::serialization::void_cast_register<PndSdsDigi, FairTimeStamp>();

			ar & boost::serialization::base_object<FairTimeStamp>(*this);
			ar & fDetID;
			ar & fSensorID;
			ar & fFE;
			ar & fCharge;
		}
	#endif // for BOOST serialization

  protected:
	#ifndef __CINT__ // for BOOST serialization
		friend class boost::serialization::access;

	#endif // for BOOST serialization
		std::vector<Int_t> fIndex;   // indice of mc points contributing to this digi
		Int_t fDetID;                // branch ID of mc point array
		Int_t fSensorID;             // Geometry ID for sensor volume
		Int_t fFE;                   // Frontend number
		Double_t fCharge;            // collected charge
    
    ClassDef(PndSdsDigi,4);
  };

#endif
#ifndef PndSdsPixel_HH
#define PndSdsPixel_HH

#include <iostream>
#include <string>
#include <vector>
#include "Rtypes.h"

class PndSdsPixel
{
	public :  
      PndSdsPixel() :
			  fFe(-1),
			  fCol(-1),
			  fRow(-1),
			  fCharge(-1.0),
		    fSensorID(-1),
		    fMCIndex(),
		    fAddNoise(0.)
		    {};
		  
		  PndSdsPixel(Int_t sensorID, Int_t fe, Int_t col, Int_t row, Double_t charge, int index=-1) :
			  fFe(fe),
			  fCol(col),
			  fRow(row),
			  fCharge(charge),
		    fSensorID(sensorID),
		    fMCIndex(),
		    fAddNoise(0.)
      {
			  if (index >= 0) fMCIndex.push_back(index);
		  };
		  
		  void SetCol(Int_t col) {fCol = col;};
		  void SetRow(Int_t row) {fRow = row;};
		  void SetCharge(Double_t charge) {fCharge = charge;};
		  void SetSensorID(Int_t sensorID) {fSensorID = sensorID;};
		  void SetFE (Int_t fe) {fFe = fe;};
		  void SetAddNoise (Double_t addnoise) {fAddNoise=addnoise;};
		  
		  Int_t GetCol() const {return fCol;};
		  Int_t GetRow() const {return fRow;};
		  Double_t GetCharge() const {return fCharge;};
		  Int_t GetSensorID() const {return fSensorID;};
		  Int_t GetFE() const {return fFe;};
		  std::vector<int> GetMCIndex(){return fMCIndex;};
                  int GetFirstMCIndex(){ 
		                        if (fMCIndex.size() > 0) 
		                          return fMCIndex[0]; 
		                        return -2; 
		                  }; 
          Double_t GetAddNoise() const {return fAddNoise;};
			  
		  void AddCharge(Double_t charge){fCharge+= charge;};
		  void AddMCIndex(int i){fMCIndex.push_back(i);};
		  
		  friend std::ostream& operator<< (std::ostream& out, PndSdsPixel pixel)
		  {
			out << "Detector: " << pixel.GetSensorID() << " FE: " << pixel.GetFE() << " Pixel (C/R): " << pixel.GetCol() << " " << pixel.GetRow()
			    << " Charge: " << pixel.GetCharge() << " from MCHit: " << pixel.GetFirstMCIndex();
			return out;
		  };	

	
	private : 
		  Int_t fFe;
		  Int_t fCol;
		  Int_t fRow;
		  Double_t fCharge;
		  Int_t fSensorID;
		  std::vector<int> fMCIndex;		///< List of indices of the corresponding MC hits
		  Double_t fAddNoise;               //  Variable for testing
};


#endif
// --------------------------------------------------------
// ----			PndSdsDigiPixel header file	---
// ----			Created 19.6.06 by T.Stockmanns ---
// --------------------------------------------------------

/** PndSdsDigiPixel.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 ** \brief Data class to store the digi output of a pixel module
 **
 ** \sa PndSdsDigi.h
 **/

#ifndef PNDSDSDIGIPIXEL_H
#define PNDSDSDIGIPIXEL_H

#include "PndSdsDigi.h"
#include "KoaDetectorList.h"

#include "TObject.h"
#include "TString.h"
#include <iostream>
#include <vector>


class PndSdsDigiPixel : public PndSdsDigi
  {
    friend std::ostream& operator<< (std::ostream& out, PndSdsDigiPixel& digi){
      out << "PndSdsDigiPixel in: " << digi.GetSensorID() << " FE: "
      << digi.GetFE() << " Col/Row " << digi.GetPixelColumn() << "/" << digi.GetPixelRow()
      << " charge " << digi.GetCharge() << " e"
      << " timestamp "<< digi.GetTimeStamp()
      << ", from Point(s) ";
      std::vector<Int_t>indices = digi.GetIndices();
      for (unsigned int i = 0; i < indices.size(); i++){
        out << indices[i] << "  ";
      }
      out << std::endl;
      
      return out;
    }
    
    public : PndSdsDigiPixel();
    PndSdsDigiPixel(std::vector<Int_t> index, Int_t detID, Int_t sensorID, Int_t fe, Int_t col, Int_t row, Double_t charge, Double_t timeStamp);
    
    
	virtual ~PndSdsDigiPixel(){};
    
    void Print() {
      std::cout << *this;
    }
    
	Int_t GetPixelColumn() const { return fCol; }
	Int_t GetPixelRow()    const { return fRow; }

	void SetPixelColumn(Int_t col){ fCol = col;}
	void SetPixelRow(Int_t row){ fRow = row;}

	bool operator==(PndSdsDigiPixel& myDigi){
		if (fSensorID == myDigi.GetSensorID())
			if (fFE == myDigi.GetFE())
				if (fCol == myDigi.GetPixelColumn())
					if (fRow == myDigi.GetPixelRow())
						return true;
		return false;
	}
	
	virtual bool equal(FairTimeStamp* data) {
	  PndSdsDigiPixel* myDigi = dynamic_cast <PndSdsDigiPixel*> (data);
	  if (myDigi != 0){
	    if (fSensorID == myDigi->GetSensorID())
			if (fFE == myDigi->GetFE())
				if (fCol == myDigi->GetPixelColumn())
					if (fRow == myDigi->GetPixelRow())
						return true;
	  }
	  return false;
	}

	virtual bool operator<(const PndSdsDigiPixel& myDigi) const{
		if (fDetID < myDigi.GetDetID()) 		return true;	else if(fDetID > myDigi.GetDetID()) return false;
		if (fSensorID < myDigi.GetSensorID()) 	return true; 	else if (fSensorID > myDigi.GetSensorID()) return false;
		if (fFE < myDigi.GetFE()) 				return true;	else if (fFE > myDigi.GetFE()) return false;
		if (fCol < myDigi.GetPixelColumn()) 	return true;	else if (fCol > myDigi.GetPixelColumn()) return false;
		if (fRow < myDigi.GetPixelRow()) 		return true;	else if (fRow > myDigi.GetPixelRow()) return false;
		return false;
	}
        
	virtual bool operator>(const PndSdsDigiPixel& myDigi) const{
		if (fDetID > myDigi.GetDetID()) 		return true;	else if(fDetID < myDigi.GetDetID()) return false;
		if (fSensorID > myDigi.GetSensorID()) 	return true; 	else if (fSensorID < myDigi.GetSensorID()) return false;
		if (fFE > myDigi.GetFE()) 				return true;	else if (fFE < myDigi.GetFE()) return false;
		if (fCol > myDigi.GetPixelColumn()) 	return true;	else if (fCol < myDigi.GetPixelColumn()) return false;
		if (fRow > myDigi.GetPixelRow()) 		return true;	else if (fRow < myDigi.GetPixelRow()) return false;
		return false;
	}

	PndSdsDigiPixel& operator=(const PndSdsDigiPixel& pix){
	        if (this != &pix){
		    this->PndSdsDigi::operator=(pix);
		    fCol = pix.GetPixelColumn();
		    fRow = pix.GetPixelRow();
	        }
		return *this;
	}

	#ifndef __CINT__ // for BOOST serialization
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			boost::serialization::void_cast_register<PndSdsDigiPixel, PndSdsDigi>();
			ar & boost::serialization::base_object<PndSdsDigi>(*this);
			ar & fCol;
			ar & fRow;
		}
	#endif // for BOOST serialization

    private :
	#ifndef __CINT__ // for BOOST serialization
		friend class boost::serialization::access;

	#endif // for BOOST serialization
		Int_t fCol, fRow;
    
    ClassDef(PndSdsDigiPixel,8);
  };

#endif
// --------------------------------------------------------
// ----			PndSdsDigiTopix4 header file	---
// ----			Created 19.6.06 by T.Stockmanns ---
// --------------------------------------------------------

/** PndSdsDigiTopix4.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 ** \brief Data class to store the digi output of a pixel module
 **
 ** \sa PndSdsDigi.h
 **/

#ifndef PndSdsDigiTopix4_H
#define PndSdsDigiTopix4_H

#include "PndSdsDigiPixel.h"
#include "KoaDetectorList.h"

#include "TObject.h"
#include "TString.h"
#include <iostream>
#include <vector>


class PndSdsDigiTopix4 : public PndSdsDigiPixel
  {
    friend std::ostream& operator<< (std::ostream& out, PndSdsDigiTopix4& digi){
      out << "PndSdsDigiTopix4 in Sensor: " << digi.GetSensorID() << " FE: "
      << digi.GetFE() << " Col/Row " << digi.GetPixelColumn() << "/" << digi.GetPixelRow()
      << " charge " << digi.GetCharge() << " e"
      << " timestamp "<< digi.GetTimeStamp()
      << " leadingEdge " << digi.GetLeadingEdge() << " trailingEdge " << digi.GetTrailingEdge()
      << " frameCount " << digi.GetFrameCount() << std::endl;

      //out << std::endl;
      
      return out;
    }
    
    public : PndSdsDigiTopix4();
    PndSdsDigiTopix4(std::vector<Int_t> index, Int_t detID, Int_t sensorID, Int_t fe, Int_t col, Int_t row, UInt_t leadingEdge, UInt_t trailingEdge, UInt_t frameCount, Double_t timeStamp, UInt_t hitcountcorrect, UInt_t hitCounterIndependent, Double_t timeStampIndependent);

    UInt_t GetLeadingEdge() const  { return fLeadingEdge;}
    UInt_t GetTrailingEdge() const { return fTrailingEdge;}
    UInt_t GetFrameCount() const   { return fFrameCount;}
    Double_t GetTimeStampIndependent() const { return fTimeStampIndependent;}
    UInt_t GetHitCountIndependent() const {return fHitCountIndependent;}
    UInt_t GetHitCountCorrect() const {return fHitCountCorrect;}
    
    void SetLeadingEdge(UInt_t le)  { fLeadingEdge = le;}
    void SetTrailingEdge(UInt_t te) { fTrailingEdge = te;}
    void SetFrameCount(UInt_t fc)   { fFrameCount = fc;}
    void SetHitCountIndependent(UInt_t hci) { fHitCountIndependent = hci;}
    void SetTimeStampIndependent(Double_t tsi) {fTimeStampIndependent = tsi;}
    void SetHitCountCorrect(UInt_t hcc) { fHitCountCorrect = hcc;}

		~PndSdsDigiTopix4(){};
    
    void Print() {
      std::cout << *this;
    }
    

	PndSdsDigiTopix4& operator=(const PndSdsDigiTopix4& pix){
	        if (this != &pix){
	        	this->PndSdsDigiPixel::operator=(pix);
	        }
	        SetLeadingEdge(pix.GetLeadingEdge());
	        SetTrailingEdge(pix.GetTrailingEdge());
	        SetFrameCount(pix.GetFrameCount());
		SetHitCountIndependent(pix.GetHitCountIndependent());
		SetTimeStampIndependent(pix.GetTimeStampIndependent());
		SetHitCountCorrect(pix.GetHitCountCorrect());
		return *this;
	}

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<PndSdsDigiPixel>(*this);
		ar & fLeadingEdge;
		ar & fTrailingEdge;
		ar & fFrameCount;
	}
    
    private :
	#ifndef __CINT__ // for BOOST serialization
		friend class boost::serialization::access;

	#endif // for BOOST serialization
	UInt_t fLeadingEdge;
	UInt_t fTrailingEdge;
	UInt_t fFrameCount;
	UInt_t fHitCountCorrect;
	UInt_t fHitCountIndependent;
	Double_t fTimeStampIndependent;
    
    ClassDef(PndSdsDigiTopix4,3);
  };

#endif
// --------------------------------------------------------
// ----	       PndSdsDigiTopix4Header header file	---
// ----	       Created 21.11.14 by S.Esch               ---
// --------------------------------------------------------

/** PndSdsDigiTopix4Header.h
 *@author S.Esch <s.esch@fz-juelich.de>
 ** \brief Data class to store the header of topix4 frames
 **/

#ifndef PndSdsDigiTopix4Header_H
#define PndSdsDigiTopix4Header_H

#include "PndSdsDigiPixel.h"
#include "KoaDetectorList.h"

#include "TObject.h"
#include "TString.h"
#include <iostream>
#include <vector>


class PndSdsDigiTopix4Header : public TObject
{
  friend std::ostream& operator<< (std::ostream& out, PndSdsDigiTopix4Header& digi)
  {
    out << "PndSdsDigiTopix4Header : Frame Count" << digi.GetFrameCount() 
	<< " FE: "<< digi.GetFE() 
	<< " Chip Address " << digi.GetChipAddress() 
	<< " Error Correction Code "<< digi.GetECC()
	<< " Frame Count Independent "<<  digi.GetFrameCountIndependent()
	<< std::endl;
    
    return out;
  }
  
 public :
  PndSdsDigiTopix4Header();
  PndSdsDigiTopix4Header(UInt_t framecount, Int_t fe, UInt_t chipaddress, UInt_t ecc, UInt_t framecountindependent, Int_t deltaframecount, UInt_t numberofevents, UInt_t numberofeventsinframe);
  	
  PndSdsDigiTopix4Header& operator=(const PndSdsDigiTopix4Header& pix){
    
    SetFrameCount(pix.GetFrameCount());
    SetFE(pix.GetFE());
    SetChipAddress(pix.GetChipAddress());
    SetECC(pix.GetECC());
    SetFrameCountIndependent(pix.GetFrameCountIndependent());
    SetDeltaFrameCount(pix.GetDeltaFrameCount());
    SetNumberOfEvents(pix.GetNumberOfEvents());
    SetNumberOfEventsInFrame(pix.GetNumberOfEventsInFrame());
    return *this;
  }
  
  UInt_t GetFrameCount() const   { return fFrameCount;}
  UInt_t GetFE() const           { return fFE;}
  UInt_t GetChipAddress() const  { return fChipAddress;}
  UInt_t GetECC() const          { return fECC;}
  UInt_t GetFrameCountIndependent() const   { return fFrameCountIndependent;}
  Int_t GetDeltaFrameCount() const { return fDeltaFrameCount;}
  UInt_t GetNumberOfEvents() const { return fNumberOfEvents;}
  UInt_t GetNumberOfEventsInFrame() const { return fNumberOfEvents;}

  void SetFrameCount(UInt_t fc)   { fFrameCount = fc;}
  void SetFE(Int_t fe)           { fFE = fe;}
  void SetChipAddress(UInt_t ca)  { fChipAddress = ca;}
  void SetECC(UInt_t ecc)         { fECC = ecc;}
  void SetFrameCountIndependent(UInt_t fc)   { fFrameCountIndependent = fc;}
  void SetDeltaFrameCount(Int_t dfc) { fDeltaFrameCount = dfc;}
  void SetNumberOfEvents(UInt_t noe) { fNumberOfEvents = noe;}
  void SetNumberOfEventsInFrame(UInt_t noe) { fNumberOfEventsInFrame = noe;}
  
  ~PndSdsDigiTopix4Header(){};
  
  void Print() {
    std::cout << *this;
  }
  

 private :
  UInt_t fFrameCount;
  Int_t fFE;
  UInt_t fChipAddress;
  UInt_t fECC;
  UInt_t fFrameCountIndependent;
  Int_t  fDeltaFrameCount;
  UInt_t fNumberOfEvents;
  UInt_t fNumberOfEventsInFrame;
  
  ClassDef(PndSdsDigiTopix4Header,1);
};

#endif
#ifndef PNDSDSCLUSTER_H
#define PNDSDSCLUSTER_H

//#include "FairMultiLinkedData.h" 
#include "KoaDetectorList.h" // contains SensorSide enumeration
#include "FairMultiLinkedData_Interface.h"
#include "TObject.h"
#include <vector>
#include <iostream>


//! PndSdsCluster.h
//! @author T.Stockmanns <t.stockmanns@fz-juelich.de>
//!
//! \brief Class to store the Digis which belong to one cluster
//! This class holds the information which Digi belongs to the actual cluster.
//! The information is stored in a vector<Int_t> which contains the
//! position of the digi in the TClonesArray where it is stored.
class PndSdsCluster : public FairMultiLinkedData_Interface
{

friend std::ostream& operator<< (std::ostream& out, PndSdsCluster& cl){
      std::vector<Int_t> list = cl.GetClusterList();
      out << "Hits in Cluster: (" ;
      for (UInt_t i = 0; i<list.size();i++)
        out << list[i] << " ";
      out << ")" << std::endl;

      return out;
    }

public :
    PndSdsCluster():fClusterList(){};
    ~PndSdsCluster(){};
    PndSdsCluster(std::vector<Int_t> list);

    virtual void SetClusterList(Int_t DigiType, std::vector<Int_t> list, Int_t fileId, Int_t eventId) = 0;
    std::vector<Int_t> GetClusterList() const {return fClusterList;}
    Int_t GetClusterSize() const {return fClusterList.size();}
    Int_t GetDigiIndex(Int_t i) const {return fClusterList[i];}

    bool DigiBelongsToCluster(Int_t digiIndex);

    virtual void Print();

protected :
    std::vector<Int_t> fClusterList;


ClassDef(PndSdsCluster,2);

};

#endif
/*
 * PndSdsClusterPixel.h
 *
 *  Created on: Dec 15, 2009
 *      Author: stockmanns, kliemt, michel
 */

#ifndef PNDSDSCLUSTERPIXEL_H_
#define PNDSDSCLUSTERPIXEL_H_

#include "PndSdsCluster.h"

class PndSdsClusterPixel: public PndSdsCluster {
public:
	PndSdsClusterPixel();
	PndSdsClusterPixel(Int_t DigiType, std::vector<Int_t> list, Int_t fileId = -1, Int_t evtId = -1){
		SetClusterList(DigiType, list, fileId, evtId);
	};
	virtual ~PndSdsClusterPixel();

	void SetClusterList(Int_t DigiType, std::vector<Int_t> list, Int_t fileId, Int_t evtId){
		fClusterList = list;
		SetLinks(FairMultiLinkedData(DigiType, list, fileId, evtId));
	}

	ClassDef(PndSdsClusterPixel, 1);
};

#endif /* PNDSDSCLUSTERPixel_H_ */
// -------------------------------------------------------------------------
// -----                    PndSdsHit header file                      -----
// -----                  Created by T.Stockmanns            -----
// -------------------------------------------------------------------------


/** PndSdsHit.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** A hit in a silicon sensor. In addition to the base class
 ** FairHit, it holds the number of digis & charge entry.
 ** There is also a bottom index for double sided strip sensors.
 ** All coordinates are in the LAB frame.
 **/

#ifndef PNDSDSHIT_H
#define PNDSDSHIT_H


#include "TVector3.h"
#include "TString.h"
#include "FairHit.h"
#include "KoaDetectorList.h"
#include "TMatrixD.h"
//#include "PndSingleLinkedData.h" 

#include <stdio.h>
#include <iostream>

class PndSdsHit : public FairHit
{
  friend std::ostream& operator<< (std::ostream& out, const PndSdsHit& hit){
    out << "PndSdsHit in " << hit.GetSensorID() << " at" << std::endl;
    out << "(" << hit.GetX() << ", " << hit.GetY() << ", " << hit.GetZ() << ") cm "
        << " with " << hit.GetCharge() << " e" << " at Time: " << hit.GetTimeStamp() << " +/- " << hit.GetTimeStampError() << " , Cluster No. " << hit.GetClusterIndex();
    if (hit.GetBotIndex() > -1)
    	out << " and bottom " << hit.GetBotIndex();
    if (hit.GetRefIndex() > -1)
      out << ", mc point id = " << hit.GetRefIndex();
    else 
      out << ", noise hit without mc poit";
    out << std::endl;

    out <<"hit.GetClusterIndex() "<<hit.GetClusterIndex() <<std::endl;
    out <<"hit.GetBotIndex() "<< hit.GetBotIndex() <<std::endl;
    out <<"hit.GetRefIndex() "<< hit.GetRefIndex()<<std::endl;
    out <<"hit.GetNDigiHits() "<< hit.GetNDigiHits()<<std::endl;
    out <<"hit.GetCharge() "<< hit.GetCharge()<<"("<<hit.GetEloss()<<" GeV)"<<std::endl;
    out <<"hit.GetSensorID() "<< hit.GetSensorID()<<std::endl;
    out <<"Error values in FairHit part: (dx,dy,dz) = ("<< hit.GetDx()<<","<<hit.GetDy()<<","<<hit.GetDz()<<")"<<std::endl;
    return out;
  }

 public:

  /** Default constructor (not for use) **/
  PndSdsHit();


  /** Standard constructor with all paramneters 
   *@param detID   Detector ID
   *@param sensorID Sensor ID
   *@param pos     Position vector [cm]
   *@param dpos    Position error vector [cm]
   *@param index   Array index of ClusterCand
   *@param charge  Charge measured in hit
   *@param NDigiHits Number of pixels fired for this event
   **/
  PndSdsHit(Int_t detID, Int_t sensorID,
  	    TVector3& pos, TVector3& dpos, Int_t clindex, Double_t charge, Int_t NDigiHits, Int_t mcindex);

  //PndSdsHit(PndSdsHit& c);
  /** Destructor **/
  virtual ~PndSdsHit();


  /** Accessors **/
  
  void SetSensorID(Int_t sensorID)  { fSensorID   = sensorID;}
  void SetCharge(Double_t charge){ fCharge    = charge;}
  void SetNDigiHits(Int_t pixel) { fNDigiHits = pixel;}
  void SetClusterIndex(Int_t datasource, Int_t id, Int_t fileId = -1, Int_t evtId = -1) {
	  fClusterIndex = id;
	  SetLink(FairLink(fileId, evtId, datasource, id));
  }
  void SetBotIndex(Int_t id)     { fBotIndex  = id;}
  void SetCov(TMatrixD cov);
  
  //TString 	GetDetName()      const { return fDetName;}
  Int_t     GetSensorID()			const { return fSensorID;}
  Double_t 	GetCharge()       const { return fCharge;}
  Int_t 	  GetNDigiHits()    const { return fNDigiHits;}
  TVector3  GetPosition()	    const { return TVector3(fX,fY,fZ);}
  Int_t     GetClusterIndex() const { return fClusterIndex;}
  Int_t     GetTopIndex()     const { return GetClusterIndex();}
  Int_t     GetBotIndex()     const { return fBotIndex;}
  Double_t  GetEloss()        const { return (fCharge * 3.61e-9);}  // 3.6 eV/Electron in Silicon
  TMatrixD  GetCov()          const { return fCov;}


//  FIXME: CAUTION The errors in the SsdHit are LOCAL, but the coordinates are in the LAB
// 
//   Double_t GetDxLocal() const { return fDx;};
//   Double_t GetDyLocal() const { return fDy;};
//   Double_t GetDzLocal() const { return fDz;};
//   void PositionErrorLocal(TVector3& dpos) const;

//   /** overloaded accessors **/
//   Double_t GetDx() {return GetD(0);};
//   Double_t GetDy() {return GetD(1);};
//   Double_t GetDz() {return GetD(2);};
//   void PositionError(TVector3& dpos);

#ifndef __CINT__ // for BOOST serialization
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  	{
  		ar & boost::serialization::base_object<FairHit>(*this);
  		ar & fSensorID;
  		ar & fCharge;
  		ar & fNDigiHits;
  		ar & fClusterIndex;
  		ar & fBotIndex;
  		//ar & fCov;
  	}
#endif // for BOOST serialization

  /** Screen output **/
  virtual void Print(const Option_t* opt = 0) const;

 private:
//   Double_t GetD(Int_t i);
#ifndef __CINT__ // for BOOST serialization
		friend class boost::serialization::access;

#endif // for BOOST serialization

  //TString fDetName;  // Detector name
  Int_t fSensorID; ///< unique sensor ID
  Double_t fCharge; /// deposited Charge
  Int_t fNDigiHits; /// number of fired Digis for this hit,
  Int_t fClusterIndex; /// top/pixel cluster index
  Int_t fBotIndex; /// bottom side of strip clusters
  TMatrixD fCov; /// Hit covariance Matrix
  ClassDef(PndSdsHit,8);

};

// inline void PndSdsHit::PositionErrorLocal(TVector3& dpos) const {
//   dpos.SetXYZ(fDx, fDy, fDz); 
// }
// 
// inline void PndSdsHit::PositionError(TVector3& dpos) {
//   dpos.SetXYZ(GetDx(), GetDy(), GetDz()); 
// }

#endif
//-----------------------------------------------------------
// File and Version Information:
// $Id$
//
// Description:
//      Track candidate. Basically a list of hit indices.
//
//
// Environment:
//      Software developed for the PANDA Detector at FAIR.
//
// Author List:
//      Sebastian Neubert    	TUM     (original author)
//	Tobias Baldauf		TUD	(adapted for SSD Pid)
//
//-----------------------------------------------------------

#ifndef PNDSSDPIDCAND_H
#define PNDSSDPIDCAND_H

// Base Class Headers ----------------
#include "TObject.h"

// Collaborating Class Headers -------
#include <vector>
#include <map>

// Collaborating Class Declarations --

class PndSdsPidCand : public TObject {
public:

  // Constructors/Destructors ---------
  PndSdsPidCand() : 
  fssdhits(0),
  fdE(),
  fdx(),
  fmomentum(),
  flikelihood()
  {  }

  // CopyConstructor
  PndSdsPidCand(PndSdsPidCand& point) : TObject(point),
  fssdhits(point.fssdhits),
  fdE(point.fdE),
  fdx(point.fdx),
  fmomentum(point.fmomentum),
  flikelihood(point.flikelihood)
  { *this = point; };

  // operators

  // Setting -----------------------
  void SetLikelihood(int lundId, double likelihood);
  void AddSsdHit(double dE, double dx, double p);

  // Getting -----------------------
  double GetSsdHitdE(int ssdhit) const;
  double GetSsdHitdx(int ssdhit) const;
  double GetSsdHitMomentum(int ssdhit) const;
  int GetSsdHits() const;
  double GetLikelihood(int lundId);

private:

  // Private Data Members ------------
  int fssdhits;
  std::vector<double> fdE;
  std::vector<double> fdx;
  std::vector<double> fmomentum;
  std::map<int, double> flikelihood;

//public:
  ClassDef(PndSdsPidCand,1);
};

#endif

//--------------------------------------------------------------
// $Log$
//--------------------------------------------------------------
/*
 * PndSdsRadDamHit.h
 *
 *  Created on: Dec 16, 2008
 *      Author: stockman
 */

#ifndef PNDSDSRADDAMHIT_H_
#define PNDSDSRADDAMHIT_H_

#include "TObject.h"
#include "TVector3.h"
class PndSdsRadDamHit : public TObject
{
public:
	PndSdsRadDamHit();
	PndSdsRadDamHit(Int_t trackID, Int_t hitID, TString detName, Int_t pdgCode, Double_t energy,
	  	    TVector3 pos, TVector3 mom, Double_t radDam);
	virtual ~PndSdsRadDamHit(){};

	void SetRadDam(Double_t radDam){fRadDam = radDam;};
	Double_t GetRadDam(){return fRadDam;};

private:
  Int_t fTrackID;
	Int_t fHitID;
	TString fDetName;
	Int_t fPdgCode;
	Double_t fEnergy;
	TVector3 fPos;
	TVector3 fMom;
  Double_t fRadDam;


	ClassDef(PndSdsRadDamHit,2);
};


#endif /* PNDSDSRADDAMHIT_H_ */
/*
 * PndSdsDigiPixelMCInfo.h
 *
 *  Created on: Oct 25, 2010
 *      Author: esch
 * brief class to save additional information for a digi
 *
 *
 */


#ifndef PNDSDSDIGIPIXELMCINFO_H_
#define PNDSDSDIGIPIXELMCINFO_H_

#include "PndSdsDigiPixel.h"

class PndSdsDigiPixelMCInfo: public PndSdsDigiPixel {

    friend std::ostream& operator<< (std::ostream& out, PndSdsDigiPixelMCInfo& digi){
      out << "PndSdsDigiPixelMCInfo in: " << digi.GetSensorID() << " FE: "
      << digi.GetFE() << " Col/Row " << digi.GetPixelColumn() << "/" << digi.GetPixelRow()
      << " charge " << digi.GetCharge() << " e"
      << " timestamp "<< digi.GetTimeStamp()
      << ", from Point(s) ";
      std::vector<Int_t>indices = digi.GetIndices();
      for (unsigned int i = 0; i < indices.size(); i++){
        std::cout << indices[i] << "  ";
      }

      out << " MCCharge: " << digi.GetMCCharge() << " AddNoise: " << digi.GetAddNoise() << " TimeWalk: " << digi.GetTimeWalk() << " TimeWalkCorrection: " << digi.GetTimeWalkCorrection();
      std::cout << std::endl;

      return out;
    }
public:
	PndSdsDigiPixelMCInfo();
	PndSdsDigiPixelMCInfo(std::vector<Int_t> index, Int_t detID, Int_t sensorID, Int_t fe, Int_t col, Int_t row, Double_t totcharge, Double_t timeStamp, Double_t chargewonoise, Double_t addnoise, Double_t timewalk, Double_t timewalkcorrection, Double_t tof, Double_t digicharge);
	virtual ~PndSdsDigiPixelMCInfo();

	void SetMCCharge(Double_t charge) {fMCCharge = charge;}
	Double_t GetMCCharge() {return fMCCharge;}

	void SetAddNoise(Double_t charge) {fAddNoise = charge;}
	Double_t GetAddNoise() {return fAddNoise;}

	void SetTimeWalk(Double_t timewalk) {fTimeWalk = timewalk;}
	Double_t GetTimeWalk() {return fTimeWalk;}

	void SetTimeWalkCorrection(Double_t timewalkcorrection) {fTimeWalkCorrection = timewalkcorrection;}
	Double_t GetTimeWalkCorrection() {return fTimeWalkCorrection;}

	void SetTof(Double_t tof) {fTof = tof;}
	Double_t GetTof() {return fTof;}

	void SetDigiCharge(Double_t digicharge) {fDigiCharge = digicharge;}
	Double_t GetDigiCharge() {return fDigiCharge;}

private:
	Double_t fMCCharge;  // MC Charge in a Pixel w/o gaussian noise
	Double_t fAddNoise;  // gaussian noise for a pixel
	Double_t fTimeWalk;
	Double_t fTimeWalkCorrection;
	Double_t fTof;
	Double_t fDigiCharge;  // MC Charge in a Pixel with gaussian noise

	  ClassDef(PndSdsDigiPixelMCInfo,2);

};

#endif /* PNDSDSDIGIPIXELMCINFO_H_ */
//-----------------------------------------------------------
// File and Version Information:
// $Id$
//
// Description:
//      Implementation of class PndTrackCand
//      see PndTrackCand.hh for details
//
// Environment:
//      Software developed for the PANDA Detector at FAIR.
//
// Author List:
//      Tobias Stockmanns (IKP - Juelich) during the Panda Meeting 03/09
//
//
//-----------------------------------------------------------

#ifndef PNDTRACKCAND_HH
#define PNDTRACKCAND_HH

// Root Class Headers ----------------
#include "PndTrackCandHit.h"
#include "FairTimeStamp.h"

#include "TObject.h"
#include "TVector3.h"
#include "TString.h"

#include <iostream>
#include <vector>
#include <map>

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#endif //__CINT__



typedef std::multimap<Double_t, std::pair<Int_t, Int_t> >::const_iterator mapIter;

class PndTrackCand : public FairTimeStamp {
public:

  // Constructors/Destructors ---------
  PndTrackCand();
  ~PndTrackCand();

  // operators
  bool operator== (const PndTrackCand& rhs);

  // Accessors -----------------------
  PndTrackCandHit GetSortedHit(UInt_t i){
	  if (sorted == false)
		  Sort();
	  return fHitId.at(i);
  }
  UInt_t GetNHits() const {return fHitId.size();}
  int getMcTrackId() const {return fMcTrackId;}

  UInt_t GetNHitsDet(Int_t detId);
  std::vector<PndTrackCandHit>GetSortedHits();
  void Sort();

  // Modifiers -----------------------
  void AddHit(UInt_t detId, UInt_t hitId, Double_t rho);
  void AddHit(TString branchName, UInt_t hitId, Double_t rho);
  void AddHit(FairLink link, Double_t rho);
  void DeleteHit(UInt_t detId, UInt_t hitId);
  Int_t HitInTrack(UInt_t detId, UInt_t hitId) const;
  void setMcTrackId(int i){fMcTrackId=i;}

  void CalcTimeStamp();

  void ResetLinks();

  void Print() const;

#ifndef __CINT__ // for BOOST serialization
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  	{
  		ar & boost::serialization::base_object<FairTimeStamp>(*this);
  		ar & fHitId;
  		ar & sorted;
  		ar & fMcTrackId;
  	}
#endif // for BOOST serialization

private:
  // Private Data Members ------------
	std::vector<PndTrackCandHit> fHitId;  ///< first index is detId, second index is hit Id
	bool sorted;
	int fMcTrackId; //track id for MC simulation
	Int_t fVerbose;
public:
  ClassDef(PndTrackCand,3);
};

#endif

//--------------------------------------------------------------
// $Log$
//--------------------------------------------------------------
//-----------------------------------------------------------
// File and Version Information:
// $Id$
//
// Description:
//      Implementation of class PndTrackCand
//      see PndTrackCand.hh for details
//
// Environment:
//      Software developed for the PANDA Detector at FAIR.
//
// Author List:
//      Tobias Stockmanns (IKP - Juelich) during the Panda Meeting 03/09
//
//
//-----------------------------------------------------------

#ifndef PNDTRACKCANDHIT_HH
#define PNDTRACKCANDHIT_HH

// Root Class Headers ----------------
#include "TObject.h"

#include "FairLink.h"

#include <iostream>
#include <vector>
#include <map>

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class PndTrackCandHit : public FairLink{
public:
  PndTrackCandHit():FairLink(), fRho(0){}
  PndTrackCandHit(Int_t detId, Int_t hitId, Double_t rho):FairLink(detId, hitId), fRho(rho){}
  PndTrackCandHit(FairLink& link, Double_t& rho):FairLink(link), fRho(rho){};
  virtual ~PndTrackCandHit() {}
  bool operator< (const PndTrackCandHit& rhs) const
  {return fRho<rhs.fRho;};
  bool operator> (const PndTrackCandHit& rhs) const
  {return fRho>rhs.fRho;};
  bool operator<= (const PndTrackCandHit& rhs) const
  {return fRho<=rhs.fRho;};
  bool operator>= (const PndTrackCandHit& rhs) const
  {return fRho>=rhs.fRho;};
  bool operator== (const PndTrackCandHit& hit) const {
    return ( FairLink::operator==((FairLink)hit) && fRho == hit.fRho);
  }
  bool operator!= (const PndTrackCandHit& hit) const {
    return (!(FairLink::operator==(hit)));
  }
  Int_t GetHitId()const {return GetIndex();}
  Int_t GetDetId()const {return GetType();}
  Double_t GetRho()const {return fRho;}

  void Print() const;

#ifndef __CINT__ // for BOOST serialization
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  	{
  		ar & boost::serialization::base_object<FairLink>(*this);
  		ar & fRho;
  	}
#endif // for BOOST serialization

  private :
  Double_t fRho;		///< sorting parameter

  ClassDef(PndTrackCandHit,2);
};



#endif

//--------------------------------------------------------------
// $Log$
//--------------------------------------------------------------
/*
 * PndTrack.h
 *
 *  Created on: 05.03.2009
 *      Author: everybody
 */

#ifndef PNDTRACK_H_
#define PNDTRACK_H_

#include "TObject.h"
#include "PndTrackCand.h"
#include "FairTrackParP.h"
#include "KoaDetectorList.h"
#include "FairTimeStamp.h"
#include "TRef.h"

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class PndTrack : public FairTimeStamp{
public:
	PndTrack();
	PndTrack(const FairTrackParP& first, const FairTrackParP& last, const PndTrackCand& cand,
		 Int_t flag = 0, Double_t chi2 = -1., Int_t ndf = 0, Int_t pid = 0, Int_t id = -1, Int_t type = -1);

	void Print();


	Int_t GetPidHypo()               const { return fPidHypo; }
	Int_t GetFlag()                  const { return fFlag; } //Quality flag
	Double_t GetChi2()               const { return fChi2; }
	Int_t GetNDF()                   const { return fNDF; }
        Int_t GetRefIndex()              const { return fRefIndex; }
	void SetPidHypo(Int_t i)         { fPidHypo=i; }
	void SetFlag(Int_t i)            { fFlag=i; }
	void SetChi2(Double_t d)         { fChi2=d; }
	void SetNDF(Int_t i)             { fNDF=i; }
    void SetRefIndex(TString branch, Int_t i)        { fRefIndex=i; SetLink(FairLink(branch, i)); }
    void SetRefIndex(Int_t i){fRefIndex = i;}
	void SetTrackCand(const PndTrackCand& cand) { fTrackCand = cand; };
	void SetTrackCandRef(PndTrackCand* candPointer){ fRefToPndTrackCand = candPointer; }
	PndTrackCand* GetPndTrackCandViaRef(){ return (PndTrackCand*)fRefToPndTrackCand.GetObject();}
	
	PndTrackCand GetTrackCand()      { return fTrackCand; }
	PndTrackCand* GetTrackCandPtr()  { return &fTrackCand; }
	FairTrackParP GetParamFirst() { return fTrackParamFirst; }
	FairTrackParP GetParamLast()  { return fTrackParamLast ; }

	virtual bool equal(FairTimeStamp* data) const {
    if(data) return false; // dummy
	  return false;
	}
	
	virtual bool operator<(const PndTrack& myTrack) const{
	  PndTrackCand myCand = ((PndTrack)myTrack).GetTrackCand();
	  if      (fTimeStamp < myCand.GetTimeStamp() ) return true; 
	  else if (fTimeStamp > myCand.GetTimeStamp() ) return false; 
	  return false;
	}
	
	virtual bool operator>(const PndTrack& myTrack) const{
	  PndTrackCand myCand = ((PndTrack)myTrack).GetTrackCand();
	  if      (fTimeStamp > myCand.GetTimeStamp() ) return true; 
	  else if (fTimeStamp < myCand.GetTimeStamp() ) return false; 
	  return false;
	}
	
	virtual bool operator==(const PndTrack& myTrack) const{
    if(fFlag==myTrack.fFlag) return false; // dummy
	  return false; 
	}

#ifndef __CINT__ // for BOOST serialization
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  	{
  		ar & boost::serialization::base_object<FairTimeStamp>(*this);
 // 		ar & fTrackParamFirst;
 // 		ar & fTrackParamLast;
  		ar & fTrackCand;
  		ar & fPidHypo;
  		ar & fFlag;
  		ar & fChi2;
  		ar & fNDF;
  		ar & fRefIndex;
  	}
#endif // for BOOST serialization

private:
	FairTrackParP fTrackParamFirst;
	FairTrackParP fTrackParamLast;

	PndTrackCand fTrackCand;
	TRef fRefToPndTrackCand;

	Int_t fPidHypo;
	Int_t fFlag;		///< recotasks: -10 if Pz < 1e-9, -2 if conversion error, -22 if PdgCode == 0
	Double_t fChi2;
	Int_t fNDF;
        Int_t fRefIndex;

public:
	ClassDef(PndTrack,2)

};

#endif /* PNDTRACK_H_ */

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"PndSdsCluster", payloadCode, "@",
"PndSdsClusterPixel", payloadCode, "@",
"PndSdsDigi", payloadCode, "@",
"PndSdsDigiPixel", payloadCode, "@",
"PndSdsDigiPixelMCInfo", payloadCode, "@",
"PndSdsDigiTopix4", payloadCode, "@",
"PndSdsDigiTopix4Header", payloadCode, "@",
"PndSdsHit", payloadCode, "@",
"PndSdsMCPoint", payloadCode, "@",
"PndSdsPidCand", payloadCode, "@",
"PndSdsPixel", payloadCode, "@",
"PndSdsRadDamHit", payloadCode, "@",
"PndTrack", payloadCode, "@",
"PndTrackCand", payloadCode, "@",
"PndTrackCandHit", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__SdsDataDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__SdsDataDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__SdsDataDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__SdsDataDict() {
  TriggerDictionaryInitialization_G__SdsDataDict_Impl();
}
