// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_jensdIdetectorsdIlmdforwarddIG__LmdTrkDict

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
#include "LmdTrack/PndLmdTrackFinderTask.h"
#include "LmdTrack/KoaTrackFinderTask.h"
#include "LmdTrack/PndLmdTrackFinderCATask.h"
#include "LmdTrack/PndLmdLinFitTask.h"
#include "LmdTrack/KoaLinFitTask.h"
#include "LmdTrack/PndLmdLineTask.h"
#include "LmdTrack/PndLmdIdealFitTask.h"
#include "LmdTrack/PndLinTrack.h"
#include "LmdTrack/KoaLinTrack.h"
#include "LmdTrack/PndLmdGeaneTask.h"
#include "LmdTrack/KoaGeaneTask.h"
#include "LmdTrack/KoaBackProp.h"
#include "LmdTrack/KoaComp.h"
#include "LmdTrack/KoaPloti.h"
#include "LmdTrack/KoaEffi.h"
#include "LmdTrack/MomentumVi.h"
#include "LmdTrack/LmdEffi.h"
#include "LmdTrack/KoaIPvis.h"
#include "LmdTrack/PndLmdTrksFilterTask.h"
#include "LmdTrack/KoaTrksFilterTask.h"
#include "LmdTrack/PndLmdSigCleanTask.h"
#include "LmdTrack/PndLmdNoiseTrkSuppressionTask.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_PndLmdTrackFinderTask(void *p = 0);
   static void *newArray_PndLmdTrackFinderTask(Long_t size, void *p);
   static void delete_PndLmdTrackFinderTask(void *p);
   static void deleteArray_PndLmdTrackFinderTask(void *p);
   static void destruct_PndLmdTrackFinderTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdTrackFinderTask*)
   {
      ::PndLmdTrackFinderTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdTrackFinderTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdTrackFinderTask", ::PndLmdTrackFinderTask::Class_Version(), "", 28,
                  typeid(::PndLmdTrackFinderTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdTrackFinderTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdTrackFinderTask) );
      instance.SetNew(&new_PndLmdTrackFinderTask);
      instance.SetNewArray(&newArray_PndLmdTrackFinderTask);
      instance.SetDelete(&delete_PndLmdTrackFinderTask);
      instance.SetDeleteArray(&deleteArray_PndLmdTrackFinderTask);
      instance.SetDestructor(&destruct_PndLmdTrackFinderTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdTrackFinderTask*)
   {
      return GenerateInitInstanceLocal((::PndLmdTrackFinderTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdTrackFinderTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaTrackFinderTask(void *p = 0);
   static void *newArray_KoaTrackFinderTask(Long_t size, void *p);
   static void delete_KoaTrackFinderTask(void *p);
   static void deleteArray_KoaTrackFinderTask(void *p);
   static void destruct_KoaTrackFinderTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaTrackFinderTask*)
   {
      ::KoaTrackFinderTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaTrackFinderTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaTrackFinderTask", ::KoaTrackFinderTask::Class_Version(), "", 116,
                  typeid(::KoaTrackFinderTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaTrackFinderTask::Dictionary, isa_proxy, 4,
                  sizeof(::KoaTrackFinderTask) );
      instance.SetNew(&new_KoaTrackFinderTask);
      instance.SetNewArray(&newArray_KoaTrackFinderTask);
      instance.SetDelete(&delete_KoaTrackFinderTask);
      instance.SetDeleteArray(&deleteArray_KoaTrackFinderTask);
      instance.SetDestructor(&destruct_KoaTrackFinderTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaTrackFinderTask*)
   {
      return GenerateInitInstanceLocal((::KoaTrackFinderTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaTrackFinderTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLmdTrackFinderCATask(void *p = 0);
   static void *newArray_PndLmdTrackFinderCATask(Long_t size, void *p);
   static void delete_PndLmdTrackFinderCATask(void *p);
   static void deleteArray_PndLmdTrackFinderCATask(void *p);
   static void destruct_PndLmdTrackFinderCATask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdTrackFinderCATask*)
   {
      ::PndLmdTrackFinderCATask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdTrackFinderCATask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdTrackFinderCATask", ::PndLmdTrackFinderCATask::Class_Version(), "", 205,
                  typeid(::PndLmdTrackFinderCATask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdTrackFinderCATask::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdTrackFinderCATask) );
      instance.SetNew(&new_PndLmdTrackFinderCATask);
      instance.SetNewArray(&newArray_PndLmdTrackFinderCATask);
      instance.SetDelete(&delete_PndLmdTrackFinderCATask);
      instance.SetDeleteArray(&deleteArray_PndLmdTrackFinderCATask);
      instance.SetDestructor(&destruct_PndLmdTrackFinderCATask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdTrackFinderCATask*)
   {
      return GenerateInitInstanceLocal((::PndLmdTrackFinderCATask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdTrackFinderCATask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLmdLinFitTask(void *p = 0);
   static void *newArray_PndLmdLinFitTask(Long_t size, void *p);
   static void delete_PndLmdLinFitTask(void *p);
   static void deleteArray_PndLmdLinFitTask(void *p);
   static void destruct_PndLmdLinFitTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdLinFitTask*)
   {
      ::PndLmdLinFitTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdLinFitTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdLinFitTask", ::PndLmdLinFitTask::Class_Version(), "", 304,
                  typeid(::PndLmdLinFitTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdLinFitTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdLinFitTask) );
      instance.SetNew(&new_PndLmdLinFitTask);
      instance.SetNewArray(&newArray_PndLmdLinFitTask);
      instance.SetDelete(&delete_PndLmdLinFitTask);
      instance.SetDeleteArray(&deleteArray_PndLmdLinFitTask);
      instance.SetDestructor(&destruct_PndLmdLinFitTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdLinFitTask*)
   {
      return GenerateInitInstanceLocal((::PndLmdLinFitTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdLinFitTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaLinFitTask(void *p = 0);
   static void *newArray_KoaLinFitTask(Long_t size, void *p);
   static void delete_KoaLinFitTask(void *p);
   static void deleteArray_KoaLinFitTask(void *p);
   static void destruct_KoaLinFitTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaLinFitTask*)
   {
      ::KoaLinFitTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaLinFitTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaLinFitTask", ::KoaLinFitTask::Class_Version(), "", 396,
                  typeid(::KoaLinFitTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaLinFitTask::Dictionary, isa_proxy, 4,
                  sizeof(::KoaLinFitTask) );
      instance.SetNew(&new_KoaLinFitTask);
      instance.SetNewArray(&newArray_KoaLinFitTask);
      instance.SetDelete(&delete_KoaLinFitTask);
      instance.SetDeleteArray(&deleteArray_KoaLinFitTask);
      instance.SetDestructor(&destruct_KoaLinFitTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaLinFitTask*)
   {
      return GenerateInitInstanceLocal((::KoaLinFitTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaLinFitTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLmdLineTask(void *p = 0);
   static void *newArray_PndLmdLineTask(Long_t size, void *p);
   static void delete_PndLmdLineTask(void *p);
   static void deleteArray_PndLmdLineTask(void *p);
   static void destruct_PndLmdLineTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdLineTask*)
   {
      ::PndLmdLineTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdLineTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdLineTask", ::PndLmdLineTask::Class_Version(), "", 487,
                  typeid(::PndLmdLineTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdLineTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdLineTask) );
      instance.SetNew(&new_PndLmdLineTask);
      instance.SetNewArray(&newArray_PndLmdLineTask);
      instance.SetDelete(&delete_PndLmdLineTask);
      instance.SetDeleteArray(&deleteArray_PndLmdLineTask);
      instance.SetDestructor(&destruct_PndLmdLineTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdLineTask*)
   {
      return GenerateInitInstanceLocal((::PndLmdLineTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdLineTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLmdIdealFitTask(void *p = 0);
   static void *newArray_PndLmdIdealFitTask(Long_t size, void *p);
   static void delete_PndLmdIdealFitTask(void *p);
   static void deleteArray_PndLmdIdealFitTask(void *p);
   static void destruct_PndLmdIdealFitTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdIdealFitTask*)
   {
      ::PndLmdIdealFitTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdIdealFitTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdIdealFitTask", ::PndLmdIdealFitTask::Class_Version(), "", 588,
                  typeid(::PndLmdIdealFitTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdIdealFitTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdIdealFitTask) );
      instance.SetNew(&new_PndLmdIdealFitTask);
      instance.SetNewArray(&newArray_PndLmdIdealFitTask);
      instance.SetDelete(&delete_PndLmdIdealFitTask);
      instance.SetDeleteArray(&deleteArray_PndLmdIdealFitTask);
      instance.SetDestructor(&destruct_PndLmdIdealFitTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdIdealFitTask*)
   {
      return GenerateInitInstanceLocal((::PndLmdIdealFitTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdIdealFitTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLinTrack(void *p = 0);
   static void *newArray_PndLinTrack(Long_t size, void *p);
   static void delete_PndLinTrack(void *p);
   static void deleteArray_PndLinTrack(void *p);
   static void destruct_PndLinTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLinTrack*)
   {
      ::PndLinTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLinTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLinTrack", ::PndLinTrack::Class_Version(), "", 654,
                  typeid(::PndLinTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLinTrack::Dictionary, isa_proxy, 4,
                  sizeof(::PndLinTrack) );
      instance.SetNew(&new_PndLinTrack);
      instance.SetNewArray(&newArray_PndLinTrack);
      instance.SetDelete(&delete_PndLinTrack);
      instance.SetDeleteArray(&deleteArray_PndLinTrack);
      instance.SetDestructor(&destruct_PndLinTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLinTrack*)
   {
      return GenerateInitInstanceLocal((::PndLinTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLinTrack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaLinTrack(void *p = 0);
   static void *newArray_KoaLinTrack(Long_t size, void *p);
   static void delete_KoaLinTrack(void *p);
   static void deleteArray_KoaLinTrack(void *p);
   static void destruct_KoaLinTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaLinTrack*)
   {
      ::KoaLinTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaLinTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaLinTrack", ::KoaLinTrack::Class_Version(), "", 757,
                  typeid(::KoaLinTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaLinTrack::Dictionary, isa_proxy, 4,
                  sizeof(::KoaLinTrack) );
      instance.SetNew(&new_KoaLinTrack);
      instance.SetNewArray(&newArray_KoaLinTrack);
      instance.SetDelete(&delete_KoaLinTrack);
      instance.SetDeleteArray(&deleteArray_KoaLinTrack);
      instance.SetDestructor(&destruct_KoaLinTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaLinTrack*)
   {
      return GenerateInitInstanceLocal((::KoaLinTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaLinTrack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLmdGeaneTask(void *p = 0);
   static void *newArray_PndLmdGeaneTask(Long_t size, void *p);
   static void delete_PndLmdGeaneTask(void *p);
   static void deleteArray_PndLmdGeaneTask(void *p);
   static void destruct_PndLmdGeaneTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdGeaneTask*)
   {
      ::PndLmdGeaneTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdGeaneTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdGeaneTask", ::PndLmdGeaneTask::Class_Version(), "", 870,
                  typeid(::PndLmdGeaneTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdGeaneTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdGeaneTask) );
      instance.SetNew(&new_PndLmdGeaneTask);
      instance.SetNewArray(&newArray_PndLmdGeaneTask);
      instance.SetDelete(&delete_PndLmdGeaneTask);
      instance.SetDeleteArray(&deleteArray_PndLmdGeaneTask);
      instance.SetDestructor(&destruct_PndLmdGeaneTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdGeaneTask*)
   {
      return GenerateInitInstanceLocal((::PndLmdGeaneTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdGeaneTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaGeaneTask(void *p = 0);
   static void *newArray_KoaGeaneTask(Long_t size, void *p);
   static void delete_KoaGeaneTask(void *p);
   static void deleteArray_KoaGeaneTask(void *p);
   static void destruct_KoaGeaneTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaGeaneTask*)
   {
      ::KoaGeaneTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaGeaneTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaGeaneTask", ::KoaGeaneTask::Class_Version(), "", 961,
                  typeid(::KoaGeaneTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaGeaneTask::Dictionary, isa_proxy, 4,
                  sizeof(::KoaGeaneTask) );
      instance.SetNew(&new_KoaGeaneTask);
      instance.SetNewArray(&newArray_KoaGeaneTask);
      instance.SetDelete(&delete_KoaGeaneTask);
      instance.SetDeleteArray(&deleteArray_KoaGeaneTask);
      instance.SetDestructor(&destruct_KoaGeaneTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaGeaneTask*)
   {
      return GenerateInitInstanceLocal((::KoaGeaneTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaGeaneTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaBackProp(void *p = 0);
   static void *newArray_KoaBackProp(Long_t size, void *p);
   static void delete_KoaBackProp(void *p);
   static void deleteArray_KoaBackProp(void *p);
   static void destruct_KoaBackProp(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaBackProp*)
   {
      ::KoaBackProp *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaBackProp >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaBackProp", ::KoaBackProp::Class_Version(), "", 1043,
                  typeid(::KoaBackProp), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaBackProp::Dictionary, isa_proxy, 4,
                  sizeof(::KoaBackProp) );
      instance.SetNew(&new_KoaBackProp);
      instance.SetNewArray(&newArray_KoaBackProp);
      instance.SetDelete(&delete_KoaBackProp);
      instance.SetDeleteArray(&deleteArray_KoaBackProp);
      instance.SetDestructor(&destruct_KoaBackProp);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaBackProp*)
   {
      return GenerateInitInstanceLocal((::KoaBackProp*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaBackProp*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaComp(void *p = 0);
   static void *newArray_KoaComp(Long_t size, void *p);
   static void delete_KoaComp(void *p);
   static void deleteArray_KoaComp(void *p);
   static void destruct_KoaComp(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaComp*)
   {
      ::KoaComp *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaComp >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaComp", ::KoaComp::Class_Version(), "", 1113,
                  typeid(::KoaComp), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaComp::Dictionary, isa_proxy, 4,
                  sizeof(::KoaComp) );
      instance.SetNew(&new_KoaComp);
      instance.SetNewArray(&newArray_KoaComp);
      instance.SetDelete(&delete_KoaComp);
      instance.SetDeleteArray(&deleteArray_KoaComp);
      instance.SetDestructor(&destruct_KoaComp);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaComp*)
   {
      return GenerateInitInstanceLocal((::KoaComp*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaComp*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaPloti(void *p = 0);
   static void *newArray_KoaPloti(Long_t size, void *p);
   static void delete_KoaPloti(void *p);
   static void deleteArray_KoaPloti(void *p);
   static void destruct_KoaPloti(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaPloti*)
   {
      ::KoaPloti *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaPloti >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaPloti", ::KoaPloti::Class_Version(), "", 1215,
                  typeid(::KoaPloti), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaPloti::Dictionary, isa_proxy, 4,
                  sizeof(::KoaPloti) );
      instance.SetNew(&new_KoaPloti);
      instance.SetNewArray(&newArray_KoaPloti);
      instance.SetDelete(&delete_KoaPloti);
      instance.SetDeleteArray(&deleteArray_KoaPloti);
      instance.SetDestructor(&destruct_KoaPloti);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaPloti*)
   {
      return GenerateInitInstanceLocal((::KoaPloti*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaPloti*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaEffi(void *p = 0);
   static void *newArray_KoaEffi(Long_t size, void *p);
   static void delete_KoaEffi(void *p);
   static void deleteArray_KoaEffi(void *p);
   static void destruct_KoaEffi(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaEffi*)
   {
      ::KoaEffi *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaEffi >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaEffi", ::KoaEffi::Class_Version(), "", 1321,
                  typeid(::KoaEffi), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaEffi::Dictionary, isa_proxy, 4,
                  sizeof(::KoaEffi) );
      instance.SetNew(&new_KoaEffi);
      instance.SetNewArray(&newArray_KoaEffi);
      instance.SetDelete(&delete_KoaEffi);
      instance.SetDeleteArray(&deleteArray_KoaEffi);
      instance.SetDestructor(&destruct_KoaEffi);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaEffi*)
   {
      return GenerateInitInstanceLocal((::KoaEffi*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaEffi*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MomentumVi(void *p = 0);
   static void *newArray_MomentumVi(Long_t size, void *p);
   static void delete_MomentumVi(void *p);
   static void deleteArray_MomentumVi(void *p);
   static void destruct_MomentumVi(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MomentumVi*)
   {
      ::MomentumVi *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MomentumVi >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MomentumVi", ::MomentumVi::Class_Version(), "", 1434,
                  typeid(::MomentumVi), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::MomentumVi::Dictionary, isa_proxy, 4,
                  sizeof(::MomentumVi) );
      instance.SetNew(&new_MomentumVi);
      instance.SetNewArray(&newArray_MomentumVi);
      instance.SetDelete(&delete_MomentumVi);
      instance.SetDeleteArray(&deleteArray_MomentumVi);
      instance.SetDestructor(&destruct_MomentumVi);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MomentumVi*)
   {
      return GenerateInitInstanceLocal((::MomentumVi*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::MomentumVi*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LmdEffi(void *p = 0);
   static void *newArray_LmdEffi(Long_t size, void *p);
   static void delete_LmdEffi(void *p);
   static void deleteArray_LmdEffi(void *p);
   static void destruct_LmdEffi(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LmdEffi*)
   {
      ::LmdEffi *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LmdEffi >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LmdEffi", ::LmdEffi::Class_Version(), "", 1586,
                  typeid(::LmdEffi), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LmdEffi::Dictionary, isa_proxy, 4,
                  sizeof(::LmdEffi) );
      instance.SetNew(&new_LmdEffi);
      instance.SetNewArray(&newArray_LmdEffi);
      instance.SetDelete(&delete_LmdEffi);
      instance.SetDeleteArray(&deleteArray_LmdEffi);
      instance.SetDestructor(&destruct_LmdEffi);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LmdEffi*)
   {
      return GenerateInitInstanceLocal((::LmdEffi*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::LmdEffi*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaIPvis(void *p = 0);
   static void *newArray_KoaIPvis(Long_t size, void *p);
   static void delete_KoaIPvis(void *p);
   static void deleteArray_KoaIPvis(void *p);
   static void destruct_KoaIPvis(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaIPvis*)
   {
      ::KoaIPvis *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaIPvis >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaIPvis", ::KoaIPvis::Class_Version(), "", 1711,
                  typeid(::KoaIPvis), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaIPvis::Dictionary, isa_proxy, 4,
                  sizeof(::KoaIPvis) );
      instance.SetNew(&new_KoaIPvis);
      instance.SetNewArray(&newArray_KoaIPvis);
      instance.SetDelete(&delete_KoaIPvis);
      instance.SetDeleteArray(&deleteArray_KoaIPvis);
      instance.SetDestructor(&destruct_KoaIPvis);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaIPvis*)
   {
      return GenerateInitInstanceLocal((::KoaIPvis*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaIPvis*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLmdTrksFilterTask(void *p = 0);
   static void *newArray_PndLmdTrksFilterTask(Long_t size, void *p);
   static void delete_PndLmdTrksFilterTask(void *p);
   static void deleteArray_PndLmdTrksFilterTask(void *p);
   static void destruct_PndLmdTrksFilterTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdTrksFilterTask*)
   {
      ::PndLmdTrksFilterTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdTrksFilterTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdTrksFilterTask", ::PndLmdTrksFilterTask::Class_Version(), "", 1780,
                  typeid(::PndLmdTrksFilterTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdTrksFilterTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdTrksFilterTask) );
      instance.SetNew(&new_PndLmdTrksFilterTask);
      instance.SetNewArray(&newArray_PndLmdTrksFilterTask);
      instance.SetDelete(&delete_PndLmdTrksFilterTask);
      instance.SetDeleteArray(&deleteArray_PndLmdTrksFilterTask);
      instance.SetDestructor(&destruct_PndLmdTrksFilterTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdTrksFilterTask*)
   {
      return GenerateInitInstanceLocal((::PndLmdTrksFilterTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdTrksFilterTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaTrksFilterTask(void *p = 0);
   static void *newArray_KoaTrksFilterTask(Long_t size, void *p);
   static void delete_KoaTrksFilterTask(void *p);
   static void deleteArray_KoaTrksFilterTask(void *p);
   static void destruct_KoaTrksFilterTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaTrksFilterTask*)
   {
      ::KoaTrksFilterTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaTrksFilterTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaTrksFilterTask", ::KoaTrksFilterTask::Class_Version(), "", 1852,
                  typeid(::KoaTrksFilterTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaTrksFilterTask::Dictionary, isa_proxy, 4,
                  sizeof(::KoaTrksFilterTask) );
      instance.SetNew(&new_KoaTrksFilterTask);
      instance.SetNewArray(&newArray_KoaTrksFilterTask);
      instance.SetDelete(&delete_KoaTrksFilterTask);
      instance.SetDeleteArray(&deleteArray_KoaTrksFilterTask);
      instance.SetDestructor(&destruct_KoaTrksFilterTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaTrksFilterTask*)
   {
      return GenerateInitInstanceLocal((::KoaTrksFilterTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaTrksFilterTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLmdSigCleanTask(void *p = 0);
   static void *newArray_PndLmdSigCleanTask(Long_t size, void *p);
   static void delete_PndLmdSigCleanTask(void *p);
   static void deleteArray_PndLmdSigCleanTask(void *p);
   static void destruct_PndLmdSigCleanTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdSigCleanTask*)
   {
      ::PndLmdSigCleanTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdSigCleanTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdSigCleanTask", ::PndLmdSigCleanTask::Class_Version(), "", 1935,
                  typeid(::PndLmdSigCleanTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdSigCleanTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdSigCleanTask) );
      instance.SetNew(&new_PndLmdSigCleanTask);
      instance.SetNewArray(&newArray_PndLmdSigCleanTask);
      instance.SetDelete(&delete_PndLmdSigCleanTask);
      instance.SetDeleteArray(&deleteArray_PndLmdSigCleanTask);
      instance.SetDestructor(&destruct_PndLmdSigCleanTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdSigCleanTask*)
   {
      return GenerateInitInstanceLocal((::PndLmdSigCleanTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdSigCleanTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PndLmdNoiseTrkSuppressionTask(void *p = 0);
   static void *newArray_PndLmdNoiseTrkSuppressionTask(Long_t size, void *p);
   static void delete_PndLmdNoiseTrkSuppressionTask(void *p);
   static void deleteArray_PndLmdNoiseTrkSuppressionTask(void *p);
   static void destruct_PndLmdNoiseTrkSuppressionTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PndLmdNoiseTrkSuppressionTask*)
   {
      ::PndLmdNoiseTrkSuppressionTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PndLmdNoiseTrkSuppressionTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PndLmdNoiseTrkSuppressionTask", ::PndLmdNoiseTrkSuppressionTask::Class_Version(), "", 2015,
                  typeid(::PndLmdNoiseTrkSuppressionTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PndLmdNoiseTrkSuppressionTask::Dictionary, isa_proxy, 4,
                  sizeof(::PndLmdNoiseTrkSuppressionTask) );
      instance.SetNew(&new_PndLmdNoiseTrkSuppressionTask);
      instance.SetNewArray(&newArray_PndLmdNoiseTrkSuppressionTask);
      instance.SetDelete(&delete_PndLmdNoiseTrkSuppressionTask);
      instance.SetDeleteArray(&deleteArray_PndLmdNoiseTrkSuppressionTask);
      instance.SetDestructor(&destruct_PndLmdNoiseTrkSuppressionTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PndLmdNoiseTrkSuppressionTask*)
   {
      return GenerateInitInstanceLocal((::PndLmdNoiseTrkSuppressionTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PndLmdNoiseTrkSuppressionTask*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr PndLmdTrackFinderTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdTrackFinderTask::Class_Name()
{
   return "PndLmdTrackFinderTask";
}

//______________________________________________________________________________
const char *PndLmdTrackFinderTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdTrackFinderTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdTrackFinderTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdTrackFinderTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdTrackFinderTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdTrackFinderTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdTrackFinderTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdTrackFinderTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaTrackFinderTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaTrackFinderTask::Class_Name()
{
   return "KoaTrackFinderTask";
}

//______________________________________________________________________________
const char *KoaTrackFinderTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaTrackFinderTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaTrackFinderTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaTrackFinderTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaTrackFinderTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaTrackFinderTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaTrackFinderTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaTrackFinderTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLmdTrackFinderCATask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdTrackFinderCATask::Class_Name()
{
   return "PndLmdTrackFinderCATask";
}

//______________________________________________________________________________
const char *PndLmdTrackFinderCATask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdTrackFinderCATask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdTrackFinderCATask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdTrackFinderCATask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdTrackFinderCATask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdTrackFinderCATask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdTrackFinderCATask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdTrackFinderCATask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLmdLinFitTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdLinFitTask::Class_Name()
{
   return "PndLmdLinFitTask";
}

//______________________________________________________________________________
const char *PndLmdLinFitTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdLinFitTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdLinFitTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdLinFitTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdLinFitTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdLinFitTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdLinFitTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdLinFitTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaLinFitTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaLinFitTask::Class_Name()
{
   return "KoaLinFitTask";
}

//______________________________________________________________________________
const char *KoaLinFitTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaLinFitTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaLinFitTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaLinFitTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaLinFitTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaLinFitTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaLinFitTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaLinFitTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLmdLineTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdLineTask::Class_Name()
{
   return "PndLmdLineTask";
}

//______________________________________________________________________________
const char *PndLmdLineTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdLineTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdLineTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdLineTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdLineTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdLineTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdLineTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdLineTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLmdIdealFitTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdIdealFitTask::Class_Name()
{
   return "PndLmdIdealFitTask";
}

//______________________________________________________________________________
const char *PndLmdIdealFitTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdIdealFitTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdIdealFitTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdIdealFitTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdIdealFitTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdIdealFitTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdIdealFitTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdIdealFitTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLinTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLinTrack::Class_Name()
{
   return "PndLinTrack";
}

//______________________________________________________________________________
const char *PndLinTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLinTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLinTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLinTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLinTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLinTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLinTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLinTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaLinTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaLinTrack::Class_Name()
{
   return "KoaLinTrack";
}

//______________________________________________________________________________
const char *KoaLinTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaLinTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaLinTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaLinTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaLinTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaLinTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaLinTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaLinTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLmdGeaneTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdGeaneTask::Class_Name()
{
   return "PndLmdGeaneTask";
}

//______________________________________________________________________________
const char *PndLmdGeaneTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdGeaneTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdGeaneTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdGeaneTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdGeaneTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdGeaneTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdGeaneTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdGeaneTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaGeaneTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaGeaneTask::Class_Name()
{
   return "KoaGeaneTask";
}

//______________________________________________________________________________
const char *KoaGeaneTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaGeaneTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaGeaneTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaGeaneTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaGeaneTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaGeaneTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaGeaneTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaGeaneTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaBackProp::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaBackProp::Class_Name()
{
   return "KoaBackProp";
}

//______________________________________________________________________________
const char *KoaBackProp::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaBackProp*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaBackProp::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaBackProp*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaBackProp::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaBackProp*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaBackProp::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaBackProp*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaComp::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaComp::Class_Name()
{
   return "KoaComp";
}

//______________________________________________________________________________
const char *KoaComp::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaComp*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaComp::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaComp*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaComp::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaComp*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaComp::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaComp*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaPloti::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaPloti::Class_Name()
{
   return "KoaPloti";
}

//______________________________________________________________________________
const char *KoaPloti::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPloti*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaPloti::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPloti*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaPloti::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPloti*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaPloti::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPloti*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaEffi::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaEffi::Class_Name()
{
   return "KoaEffi";
}

//______________________________________________________________________________
const char *KoaEffi::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEffi*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaEffi::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaEffi*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaEffi::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEffi*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaEffi::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaEffi*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MomentumVi::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MomentumVi::Class_Name()
{
   return "MomentumVi";
}

//______________________________________________________________________________
const char *MomentumVi::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MomentumVi*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MomentumVi::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MomentumVi*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MomentumVi::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MomentumVi*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MomentumVi::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MomentumVi*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LmdEffi::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LmdEffi::Class_Name()
{
   return "LmdEffi";
}

//______________________________________________________________________________
const char *LmdEffi::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LmdEffi*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LmdEffi::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LmdEffi*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LmdEffi::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LmdEffi*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LmdEffi::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LmdEffi*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaIPvis::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaIPvis::Class_Name()
{
   return "KoaIPvis";
}

//______________________________________________________________________________
const char *KoaIPvis::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaIPvis*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaIPvis::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaIPvis*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaIPvis::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaIPvis*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaIPvis::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaIPvis*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLmdTrksFilterTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdTrksFilterTask::Class_Name()
{
   return "PndLmdTrksFilterTask";
}

//______________________________________________________________________________
const char *PndLmdTrksFilterTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdTrksFilterTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdTrksFilterTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdTrksFilterTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdTrksFilterTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdTrksFilterTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdTrksFilterTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdTrksFilterTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaTrksFilterTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaTrksFilterTask::Class_Name()
{
   return "KoaTrksFilterTask";
}

//______________________________________________________________________________
const char *KoaTrksFilterTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaTrksFilterTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaTrksFilterTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaTrksFilterTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaTrksFilterTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaTrksFilterTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaTrksFilterTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaTrksFilterTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLmdSigCleanTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdSigCleanTask::Class_Name()
{
   return "PndLmdSigCleanTask";
}

//______________________________________________________________________________
const char *PndLmdSigCleanTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdSigCleanTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdSigCleanTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdSigCleanTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdSigCleanTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdSigCleanTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdSigCleanTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdSigCleanTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PndLmdNoiseTrkSuppressionTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PndLmdNoiseTrkSuppressionTask::Class_Name()
{
   return "PndLmdNoiseTrkSuppressionTask";
}

//______________________________________________________________________________
const char *PndLmdNoiseTrkSuppressionTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdNoiseTrkSuppressionTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PndLmdNoiseTrkSuppressionTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PndLmdNoiseTrkSuppressionTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PndLmdNoiseTrkSuppressionTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdNoiseTrkSuppressionTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PndLmdNoiseTrkSuppressionTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PndLmdNoiseTrkSuppressionTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void PndLmdTrackFinderTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdTrackFinderTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdTrackFinderTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdTrackFinderTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdTrackFinderTask(void *p) {
      return  p ? new(p) ::PndLmdTrackFinderTask : new ::PndLmdTrackFinderTask;
   }
   static void *newArray_PndLmdTrackFinderTask(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdTrackFinderTask[nElements] : new ::PndLmdTrackFinderTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdTrackFinderTask(void *p) {
      delete ((::PndLmdTrackFinderTask*)p);
   }
   static void deleteArray_PndLmdTrackFinderTask(void *p) {
      delete [] ((::PndLmdTrackFinderTask*)p);
   }
   static void destruct_PndLmdTrackFinderTask(void *p) {
      typedef ::PndLmdTrackFinderTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdTrackFinderTask

//______________________________________________________________________________
void KoaTrackFinderTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaTrackFinderTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaTrackFinderTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaTrackFinderTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaTrackFinderTask(void *p) {
      return  p ? new(p) ::KoaTrackFinderTask : new ::KoaTrackFinderTask;
   }
   static void *newArray_KoaTrackFinderTask(Long_t nElements, void *p) {
      return p ? new(p) ::KoaTrackFinderTask[nElements] : new ::KoaTrackFinderTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaTrackFinderTask(void *p) {
      delete ((::KoaTrackFinderTask*)p);
   }
   static void deleteArray_KoaTrackFinderTask(void *p) {
      delete [] ((::KoaTrackFinderTask*)p);
   }
   static void destruct_KoaTrackFinderTask(void *p) {
      typedef ::KoaTrackFinderTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaTrackFinderTask

//______________________________________________________________________________
void PndLmdTrackFinderCATask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdTrackFinderCATask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdTrackFinderCATask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdTrackFinderCATask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdTrackFinderCATask(void *p) {
      return  p ? new(p) ::PndLmdTrackFinderCATask : new ::PndLmdTrackFinderCATask;
   }
   static void *newArray_PndLmdTrackFinderCATask(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdTrackFinderCATask[nElements] : new ::PndLmdTrackFinderCATask[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdTrackFinderCATask(void *p) {
      delete ((::PndLmdTrackFinderCATask*)p);
   }
   static void deleteArray_PndLmdTrackFinderCATask(void *p) {
      delete [] ((::PndLmdTrackFinderCATask*)p);
   }
   static void destruct_PndLmdTrackFinderCATask(void *p) {
      typedef ::PndLmdTrackFinderCATask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdTrackFinderCATask

//______________________________________________________________________________
void PndLmdLinFitTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdLinFitTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdLinFitTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdLinFitTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdLinFitTask(void *p) {
      return  p ? new(p) ::PndLmdLinFitTask : new ::PndLmdLinFitTask;
   }
   static void *newArray_PndLmdLinFitTask(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdLinFitTask[nElements] : new ::PndLmdLinFitTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdLinFitTask(void *p) {
      delete ((::PndLmdLinFitTask*)p);
   }
   static void deleteArray_PndLmdLinFitTask(void *p) {
      delete [] ((::PndLmdLinFitTask*)p);
   }
   static void destruct_PndLmdLinFitTask(void *p) {
      typedef ::PndLmdLinFitTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdLinFitTask

//______________________________________________________________________________
void KoaLinFitTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaLinFitTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaLinFitTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaLinFitTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaLinFitTask(void *p) {
      return  p ? new(p) ::KoaLinFitTask : new ::KoaLinFitTask;
   }
   static void *newArray_KoaLinFitTask(Long_t nElements, void *p) {
      return p ? new(p) ::KoaLinFitTask[nElements] : new ::KoaLinFitTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaLinFitTask(void *p) {
      delete ((::KoaLinFitTask*)p);
   }
   static void deleteArray_KoaLinFitTask(void *p) {
      delete [] ((::KoaLinFitTask*)p);
   }
   static void destruct_KoaLinFitTask(void *p) {
      typedef ::KoaLinFitTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaLinFitTask

//______________________________________________________________________________
void PndLmdLineTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdLineTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdLineTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdLineTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdLineTask(void *p) {
      return  p ? new(p) ::PndLmdLineTask : new ::PndLmdLineTask;
   }
   static void *newArray_PndLmdLineTask(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdLineTask[nElements] : new ::PndLmdLineTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdLineTask(void *p) {
      delete ((::PndLmdLineTask*)p);
   }
   static void deleteArray_PndLmdLineTask(void *p) {
      delete [] ((::PndLmdLineTask*)p);
   }
   static void destruct_PndLmdLineTask(void *p) {
      typedef ::PndLmdLineTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdLineTask

//______________________________________________________________________________
void PndLmdIdealFitTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdIdealFitTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdIdealFitTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdIdealFitTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdIdealFitTask(void *p) {
      return  p ? new(p) ::PndLmdIdealFitTask : new ::PndLmdIdealFitTask;
   }
   static void *newArray_PndLmdIdealFitTask(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdIdealFitTask[nElements] : new ::PndLmdIdealFitTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdIdealFitTask(void *p) {
      delete ((::PndLmdIdealFitTask*)p);
   }
   static void deleteArray_PndLmdIdealFitTask(void *p) {
      delete [] ((::PndLmdIdealFitTask*)p);
   }
   static void destruct_PndLmdIdealFitTask(void *p) {
      typedef ::PndLmdIdealFitTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdIdealFitTask

//______________________________________________________________________________
void PndLinTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLinTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLinTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLinTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLinTrack(void *p) {
      return  p ? new(p) ::PndLinTrack : new ::PndLinTrack;
   }
   static void *newArray_PndLinTrack(Long_t nElements, void *p) {
      return p ? new(p) ::PndLinTrack[nElements] : new ::PndLinTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLinTrack(void *p) {
      delete ((::PndLinTrack*)p);
   }
   static void deleteArray_PndLinTrack(void *p) {
      delete [] ((::PndLinTrack*)p);
   }
   static void destruct_PndLinTrack(void *p) {
      typedef ::PndLinTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLinTrack

//______________________________________________________________________________
void KoaLinTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaLinTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaLinTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaLinTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaLinTrack(void *p) {
      return  p ? new(p) ::KoaLinTrack : new ::KoaLinTrack;
   }
   static void *newArray_KoaLinTrack(Long_t nElements, void *p) {
      return p ? new(p) ::KoaLinTrack[nElements] : new ::KoaLinTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaLinTrack(void *p) {
      delete ((::KoaLinTrack*)p);
   }
   static void deleteArray_KoaLinTrack(void *p) {
      delete [] ((::KoaLinTrack*)p);
   }
   static void destruct_KoaLinTrack(void *p) {
      typedef ::KoaLinTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaLinTrack

//______________________________________________________________________________
void PndLmdGeaneTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdGeaneTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdGeaneTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdGeaneTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdGeaneTask(void *p) {
      return  p ? new(p) ::PndLmdGeaneTask : new ::PndLmdGeaneTask;
   }
   static void *newArray_PndLmdGeaneTask(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdGeaneTask[nElements] : new ::PndLmdGeaneTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdGeaneTask(void *p) {
      delete ((::PndLmdGeaneTask*)p);
   }
   static void deleteArray_PndLmdGeaneTask(void *p) {
      delete [] ((::PndLmdGeaneTask*)p);
   }
   static void destruct_PndLmdGeaneTask(void *p) {
      typedef ::PndLmdGeaneTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdGeaneTask

//______________________________________________________________________________
void KoaGeaneTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaGeaneTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaGeaneTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaGeaneTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaGeaneTask(void *p) {
      return  p ? new(p) ::KoaGeaneTask : new ::KoaGeaneTask;
   }
   static void *newArray_KoaGeaneTask(Long_t nElements, void *p) {
      return p ? new(p) ::KoaGeaneTask[nElements] : new ::KoaGeaneTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaGeaneTask(void *p) {
      delete ((::KoaGeaneTask*)p);
   }
   static void deleteArray_KoaGeaneTask(void *p) {
      delete [] ((::KoaGeaneTask*)p);
   }
   static void destruct_KoaGeaneTask(void *p) {
      typedef ::KoaGeaneTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaGeaneTask

//______________________________________________________________________________
void KoaBackProp::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaBackProp.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaBackProp::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaBackProp::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaBackProp(void *p) {
      return  p ? new(p) ::KoaBackProp : new ::KoaBackProp;
   }
   static void *newArray_KoaBackProp(Long_t nElements, void *p) {
      return p ? new(p) ::KoaBackProp[nElements] : new ::KoaBackProp[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaBackProp(void *p) {
      delete ((::KoaBackProp*)p);
   }
   static void deleteArray_KoaBackProp(void *p) {
      delete [] ((::KoaBackProp*)p);
   }
   static void destruct_KoaBackProp(void *p) {
      typedef ::KoaBackProp current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaBackProp

//______________________________________________________________________________
void KoaComp::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaComp.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaComp::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaComp::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaComp(void *p) {
      return  p ? new(p) ::KoaComp : new ::KoaComp;
   }
   static void *newArray_KoaComp(Long_t nElements, void *p) {
      return p ? new(p) ::KoaComp[nElements] : new ::KoaComp[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaComp(void *p) {
      delete ((::KoaComp*)p);
   }
   static void deleteArray_KoaComp(void *p) {
      delete [] ((::KoaComp*)p);
   }
   static void destruct_KoaComp(void *p) {
      typedef ::KoaComp current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaComp

//______________________________________________________________________________
void KoaPloti::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaPloti.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaPloti::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaPloti::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaPloti(void *p) {
      return  p ? new(p) ::KoaPloti : new ::KoaPloti;
   }
   static void *newArray_KoaPloti(Long_t nElements, void *p) {
      return p ? new(p) ::KoaPloti[nElements] : new ::KoaPloti[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaPloti(void *p) {
      delete ((::KoaPloti*)p);
   }
   static void deleteArray_KoaPloti(void *p) {
      delete [] ((::KoaPloti*)p);
   }
   static void destruct_KoaPloti(void *p) {
      typedef ::KoaPloti current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaPloti

//______________________________________________________________________________
void KoaEffi::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaEffi.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaEffi::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaEffi::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaEffi(void *p) {
      return  p ? new(p) ::KoaEffi : new ::KoaEffi;
   }
   static void *newArray_KoaEffi(Long_t nElements, void *p) {
      return p ? new(p) ::KoaEffi[nElements] : new ::KoaEffi[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaEffi(void *p) {
      delete ((::KoaEffi*)p);
   }
   static void deleteArray_KoaEffi(void *p) {
      delete [] ((::KoaEffi*)p);
   }
   static void destruct_KoaEffi(void *p) {
      typedef ::KoaEffi current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaEffi

//______________________________________________________________________________
void MomentumVi::Streamer(TBuffer &R__b)
{
   // Stream an object of class MomentumVi.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MomentumVi::Class(),this);
   } else {
      R__b.WriteClassBuffer(MomentumVi::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MomentumVi(void *p) {
      return  p ? new(p) ::MomentumVi : new ::MomentumVi;
   }
   static void *newArray_MomentumVi(Long_t nElements, void *p) {
      return p ? new(p) ::MomentumVi[nElements] : new ::MomentumVi[nElements];
   }
   // Wrapper around operator delete
   static void delete_MomentumVi(void *p) {
      delete ((::MomentumVi*)p);
   }
   static void deleteArray_MomentumVi(void *p) {
      delete [] ((::MomentumVi*)p);
   }
   static void destruct_MomentumVi(void *p) {
      typedef ::MomentumVi current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MomentumVi

//______________________________________________________________________________
void LmdEffi::Streamer(TBuffer &R__b)
{
   // Stream an object of class LmdEffi.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LmdEffi::Class(),this);
   } else {
      R__b.WriteClassBuffer(LmdEffi::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LmdEffi(void *p) {
      return  p ? new(p) ::LmdEffi : new ::LmdEffi;
   }
   static void *newArray_LmdEffi(Long_t nElements, void *p) {
      return p ? new(p) ::LmdEffi[nElements] : new ::LmdEffi[nElements];
   }
   // Wrapper around operator delete
   static void delete_LmdEffi(void *p) {
      delete ((::LmdEffi*)p);
   }
   static void deleteArray_LmdEffi(void *p) {
      delete [] ((::LmdEffi*)p);
   }
   static void destruct_LmdEffi(void *p) {
      typedef ::LmdEffi current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LmdEffi

//______________________________________________________________________________
void KoaIPvis::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaIPvis.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaIPvis::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaIPvis::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaIPvis(void *p) {
      return  p ? new(p) ::KoaIPvis : new ::KoaIPvis;
   }
   static void *newArray_KoaIPvis(Long_t nElements, void *p) {
      return p ? new(p) ::KoaIPvis[nElements] : new ::KoaIPvis[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaIPvis(void *p) {
      delete ((::KoaIPvis*)p);
   }
   static void deleteArray_KoaIPvis(void *p) {
      delete [] ((::KoaIPvis*)p);
   }
   static void destruct_KoaIPvis(void *p) {
      typedef ::KoaIPvis current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaIPvis

//______________________________________________________________________________
void PndLmdTrksFilterTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdTrksFilterTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdTrksFilterTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdTrksFilterTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdTrksFilterTask(void *p) {
      return  p ? new(p) ::PndLmdTrksFilterTask : new ::PndLmdTrksFilterTask;
   }
   static void *newArray_PndLmdTrksFilterTask(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdTrksFilterTask[nElements] : new ::PndLmdTrksFilterTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdTrksFilterTask(void *p) {
      delete ((::PndLmdTrksFilterTask*)p);
   }
   static void deleteArray_PndLmdTrksFilterTask(void *p) {
      delete [] ((::PndLmdTrksFilterTask*)p);
   }
   static void destruct_PndLmdTrksFilterTask(void *p) {
      typedef ::PndLmdTrksFilterTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdTrksFilterTask

//______________________________________________________________________________
void KoaTrksFilterTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaTrksFilterTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaTrksFilterTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaTrksFilterTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaTrksFilterTask(void *p) {
      return  p ? new(p) ::KoaTrksFilterTask : new ::KoaTrksFilterTask;
   }
   static void *newArray_KoaTrksFilterTask(Long_t nElements, void *p) {
      return p ? new(p) ::KoaTrksFilterTask[nElements] : new ::KoaTrksFilterTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaTrksFilterTask(void *p) {
      delete ((::KoaTrksFilterTask*)p);
   }
   static void deleteArray_KoaTrksFilterTask(void *p) {
      delete [] ((::KoaTrksFilterTask*)p);
   }
   static void destruct_KoaTrksFilterTask(void *p) {
      typedef ::KoaTrksFilterTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaTrksFilterTask

//______________________________________________________________________________
void PndLmdSigCleanTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdSigCleanTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdSigCleanTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdSigCleanTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdSigCleanTask(void *p) {
      return  p ? new(p) ::PndLmdSigCleanTask : new ::PndLmdSigCleanTask;
   }
   static void *newArray_PndLmdSigCleanTask(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdSigCleanTask[nElements] : new ::PndLmdSigCleanTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdSigCleanTask(void *p) {
      delete ((::PndLmdSigCleanTask*)p);
   }
   static void deleteArray_PndLmdSigCleanTask(void *p) {
      delete [] ((::PndLmdSigCleanTask*)p);
   }
   static void destruct_PndLmdSigCleanTask(void *p) {
      typedef ::PndLmdSigCleanTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdSigCleanTask

//______________________________________________________________________________
void PndLmdNoiseTrkSuppressionTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class PndLmdNoiseTrkSuppressionTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PndLmdNoiseTrkSuppressionTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(PndLmdNoiseTrkSuppressionTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PndLmdNoiseTrkSuppressionTask(void *p) {
      return  p ? new(p) ::PndLmdNoiseTrkSuppressionTask : new ::PndLmdNoiseTrkSuppressionTask;
   }
   static void *newArray_PndLmdNoiseTrkSuppressionTask(Long_t nElements, void *p) {
      return p ? new(p) ::PndLmdNoiseTrkSuppressionTask[nElements] : new ::PndLmdNoiseTrkSuppressionTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_PndLmdNoiseTrkSuppressionTask(void *p) {
      delete ((::PndLmdNoiseTrkSuppressionTask*)p);
   }
   static void deleteArray_PndLmdNoiseTrkSuppressionTask(void *p) {
      delete [] ((::PndLmdNoiseTrkSuppressionTask*)p);
   }
   static void destruct_PndLmdNoiseTrkSuppressionTask(void *p) {
      typedef ::PndLmdNoiseTrkSuppressionTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PndLmdNoiseTrkSuppressionTask

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

namespace {
  void TriggerDictionaryInitialization_G__LmdTrkDict_Impl() {
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
#line 1 "G__LmdTrkDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class PndLmdTrackFinderTask;
class KoaTrackFinderTask;
class PndLmdTrackFinderCATask;
class PndLmdLinFitTask;
class KoaLinFitTask;
class PndLmdLineTask;
class PndLmdIdealFitTask;
class PndLinTrack;
class KoaLinTrack;
class PndLmdGeaneTask;
class KoaGeaneTask;
class KoaBackProp;
class KoaComp;
class KoaPloti;
class KoaEffi;
class MomentumVi;
class LmdEffi;
class KoaIPvis;
class PndLmdTrksFilterTask;
class KoaTrksFilterTask;
class PndLmdSigCleanTask;
class PndLmdNoiseTrkSuppressionTask;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__LmdTrkDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// -------------------------------------------------------------------------
// -----                      PndLmdTrackFinderTask                    -----
// -----                  Created 22/10/09  by M. Michel               -----
// -------------------------------------------------------------------------

#ifndef PNDLMDTRACKFINDERTASK_H
#define PNDLMDTRACKFINDERTASK_H

#include "FairTask.h"
#include "KoaMCTrack.h"
#include "PndSdsClusterPixel.h"
#include "PndSdsGeoPar.h"
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "TrackData/PndTrackCand.h"

#include <string>
#include <utility>
#include <vector>

class TClonesArray;

class PndLmdTrackFinderTask : public FairTask {
 public:
  /** Default constructor **/
  PndLmdTrackFinderTask(Int_t inFinderMode = 0,
                        TString hitBranch = "LMDHitsPixel",
                        Int_t innSensPP = 8);
  /** Destructor **/
  virtual ~PndLmdTrackFinderTask();

  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();
  virtual InitStatus ReInit();

  /** Virtual method Exec **/
  virtual void Exec(Option_t *opt);

  void SetVerbose(Int_t verbose) { fVerbose = verbose; };
  void SetInaccuracy(Double_t accu) { dXY = accu; };
  void SetSensStripFlag(bool fS) { flagStipSens = fS; };
  void SetSensPixelFlag(bool fS) { flagPixelSens = fS; };

 private:
  bool flagStipSens;
  bool flagPixelSens;
  Double_t dXY;
  Int_t fFinderMode;
  Int_t nSensPP;

  //    std::vector<Int_t> GetHitPerCluster(PndSdsClusterPixel* clusterCand);
  Double_t GetTrackDip(KoaMCTrack *myTrack);
  Double_t GetTrackCurvature(KoaMCTrack *myTrack);

  TString fHitBranchPixel;

  /** Input array of PndSdsDigis **/
  TClonesArray *fPixelHitArray;

  /** Output array of PndSdsHits **/
  TClonesArray *fTrackCandArray;

  void Register();
  void Reset();
  void ProduceHits();

  bool SortHitsByZ(std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                   Int_t nPixelHits);
  bool SortHitsByDet(std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                     Int_t nPixelHits);
  bool SortHitsByDet2(std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                      Int_t nPixelHits);  // uses PndLmdDim
  void FindHitsI(std::vector<PndTrackCand> &tofill,
                 std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                 Int_t nPixelHits);
  void FindHitsII(std::vector<PndTrackCand> &tofill,
                  std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                  Int_t nPixelHits);
  void FindHitsIII(std::vector<PndTrackCand> &tofill,
                   std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                   Int_t nPixelHits);

  ClassDef(PndLmdTrackFinderTask, 2);
};

#endif /* PndLmdTrackFinderTASK_H */
// -------------------------------------------------------------------------
// -----                      KoaTrackFinderTask                    -----
// -----                  Created 22/10/09  by M. Michel               -----
// -------------------------------------------------------------------------

#ifndef KOATRACKFINDERTASK_H
#define KOATRACKFINDERTASK_H

#include "FairTask.h"
#include "KoaMCTrack.h"
#include "PndSdsClusterPixel.h"
#include "PndSdsGeoPar.h"
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "TrackData/PndTrackCand.h"

#include <string>
#include <utility>
#include <vector>

class TClonesArray;

class KoaTrackFinderTask : public FairTask {
 public:
  /** Default constructor **/
  KoaTrackFinderTask(Int_t inFinderMode = 0,
                        TString hitBranch = "KOALAHitsPixel",
                        Int_t innSensPP = 8);
  /** Destructor **/
  virtual ~KoaTrackFinderTask();

  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();
  virtual InitStatus ReInit();

  /** Virtual method Exec **/
  virtual void Exec(Option_t *opt);

  void SetVerbose(Int_t verbose) { fVerbose = verbose; };
  void SetInaccuracy(Double_t accu) { dXY = accu; };
  void SetSensStripFlag(bool fS) { flagStipSens = fS; };
  void SetSensPixelFlag(bool fS) { flagPixelSens = fS; };

 private:
  bool flagStipSens;
  bool flagPixelSens;
  Double_t dXY;
  Int_t fFinderMode;
  Int_t nSensPP;

  //    std::vector<Int_t> GetHitPerCluster(PndSdsClusterPixel* clusterCand);
  Double_t GetTrackDip(KoaMCTrack *myTrack);
  Double_t GetTrackCurvature(KoaMCTrack *myTrack);

  TString fHitBranchPixel;

  /** Input array of PndSdsDigis **/
  TClonesArray *fPixelHitArray;

  /** Output array of PndSdsHits **/
  TClonesArray *fTrackCandArray;

  void Register();
  void Reset();
  void ProduceHits();

  bool SortHitsByZ(std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                   Int_t nPixelHits);
  bool SortHitsByDet(std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                     Int_t nPixelHits);
  bool SortHitsByDet2(std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                      Int_t nPixelHits);  // uses KoaDim
  void FindHitsI(std::vector<PndTrackCand> &tofill,
                 std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                 Int_t nPixelHits);
  void FindHitsII(std::vector<PndTrackCand> &tofill,
                  std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                  Int_t nPixelHits);
  void FindHitsIII(std::vector<PndTrackCand> &tofill,
                   std::vector<std::vector<std::pair<Int_t, bool> > > &hitsd,
                   Int_t nPixelHits);

  ClassDef(KoaTrackFinderTask, 2);
};

#endif /* KoaTrackFinderTASK_H */
// -------------------------------------------------------------------------
// -----            PndLmdTrackFinderCATask                    -----
// -----       Created 18/05/11  by A. Karavdina              -----
// -------------------------------------------------------------------------

#ifndef PNDLMDTRACKFINDERCATASK_H
#define PNDLMDTRACKFINDERCATASK_H
#include "FairTask.h"
#include "KoaMCTrack.h"
#include "PndSdsClusterPixel.h"
#include "PndSdsGeoPar.h"
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "TrackData/PndTrackCand.h"

#include <string>
#include <vector>
#include "PndSdsCell.h"
#include "TH2.h"
#include "TNtuple.h"

class TClonesArray;

class PndLmdTrackFinderCATask : public FairTask {
 public:
  /** Default constructor **/
  PndLmdTrackFinderCATask();
  /** Constructor **/
  PndLmdTrackFinderCATask(const bool missPl, const double setdmax,
                          Int_t innSensPP = 8, Int_t innP = 4,
                          TString hitBranch = "LMDHitsPixel");
  /** Destructor **/
  virtual ~PndLmdTrackFinderCATask();

  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();
  virtual InitStatus ReInit();

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  void SetVerbose(Int_t verbose) { fVerbose = verbose; };
  void SetInaccuracy(Double_t accu) { dXY = accu; };
  void SetSensStripFlag(bool fS) { flagStipSens = fS; };
  void SetSensPixelFlag(bool fS) { flagPixelSens = fS; };
  void SetTrkCandCutsFlag(bool fS) { flagTrkCandCuts = fS; };
  void FinishTask();

 private:
  Double_t dXY;
  double rule_max;
  int nSensPP;  // number of sensors on one plane
  int nP;       // number of planes
  bool SortHitsByDet(std::vector<std::vector<std::pair<Int_t, bool> > >& hitsd,
                     Int_t nPixelHits);
  bool SortHitsByDetSimple(std::vector<std::vector<Int_t> >& hitsd,
                           Int_t nPixelHits);
  bool SortHitsByDetSimple2(std::vector<std::vector<Int_t> >& hitsd,
                            Int_t nPixelHits);  // Uses PmdLmdDim class
  bool SortHitsByZ(std::vector<std::vector<std::pair<Int_t, bool> > >& hitsd,
                   Int_t nPixelHits);
  Double_t GetTrackDip(KoaMCTrack* myTrack);
  Double_t GetTrackCurvature(KoaMCTrack* myTrack);
  bool Neighbor(int& icell0, int& icell1);
  bool Neighbor(PndSdsCell* cell0, PndSdsCell* cell1);
  void Evolution(int& pv0, int& pv1, int& pv0_n, int& pv1_n, bool isch);
  TClonesArray* ForwardEvolution(TClonesArray* fCellArray, int niter = 100);
  TClonesArray* CookAllCells(std::vector<std::vector<Int_t> > hitsd);
  TClonesArray* CookCells(std::vector<std::vector<Int_t> > hitsd, int& pl0,
                          int& pl1, TClonesArray* tCellArray);
  TString fHitBranchPixel;

  bool missPlAlgo;
  bool flagStipSens;
  bool flagPixelSens;
  bool flagTrkCandCuts;
  /** Input array of PndSdsDigis and PndSdsHits**/
  TClonesArray* fPixelHitArray;

  /** Output array of Track-Cand **/
  TClonesArray* fTrackCandArray;
  TClonesArray* fCellArray;

  void Register();
  void Reset();
  void ProduceHits();

  ClassDef(PndLmdTrackFinderCATask, 4);
};

#endif /* PndLmdTrackFinderCATASK_H */
//-----------------------------------------------------------
//
// Description:
//      3D Straight Line fitter
//
// Author List:
//      Mathias Michel
//      Anastasia Karavdina
//-----------------------------------------------------------

#ifndef PNDLMDLINFITTASK_H
#define PNDLMDLINFITTASK_H

#include "FairTask.h"

#include "TMatrixDSym.h"
#include "TString.h"

class PndGeoHandling;
class TGraph2DErrors;
class TClonesArray;
class TGeoManager;
class TVector3;
namespace ROOT {
namespace Math {
class Minimizer;
}
}

class PndLmdLinFitTask : public FairTask {
 public:
  // Constructors/Destructors ---------
  PndLmdLinFitTask();
  PndLmdLinFitTask(TString tTCandBranchName, TString tRecoBranchName,
                   TString tOutputBranchName = "LMDPndTrack",
                   TString tOutputFolder = "PndLmd");

  virtual ~PndLmdLinFitTask();

  virtual InitStatus Init();

  virtual void Exec(Option_t* opt);

  virtual void Finish();

  void SetRadLen(double x) { ftotRadLen = 1e-2 * x; }  // rad.length X/X0 [%]

 protected:
  double FCN_MS(const double* vars);
  static double distance_MS(double x, double y, double z, double errx,
                            double erry, const double* p, double* zpr);
  double ScatteredAngle(double radLen);  // calculate uncertainty for kink angle
  double line3DfitMS(TGraph2DErrors* gr, const TVector3& posSeed,
                     const TVector3& dirSeed, std::vector<double>& fitpar,
                     TMatrixDSym* covmatrix);  // fit with kink angle
  double GetSigmaMS(int side) {
    if (side < 1)
      return fsigmaMSa;
    else
      return fsigmaMSb;
  }

  // Input Data------------
  TClonesArray* fTCandArray;
  TClonesArray* fRecoArray;

  TString fTCandBranchName;
  TString fRecoBranchName;
  TString fOutputBranchName;
  TString fOutputFolder;
  // Output Data----------
  TClonesArray* fTrackArray;

  double fPbeam;
  double fsigmaMSa;  // single hit before CVD diamond
  double fsigmaMSb;  // single hit after CVD diamond

  bool hitMergedfl[4];
  double fPDGCode;
  int fCharge;
  PndGeoHandling* fGeoH;

  ROOT::Math::Minimizer* fmin;
  TGraph2DErrors* fGraph2D;

  double ftotRadLen;  // X/X0

  ClassDef(PndLmdLinFitTask, 2);
};

#endif
//-----------------------------------------------------------
//
// Description:
//      3D Straight Line fitter
//
// Author List:
//      Mathias Michel
//      Anastasia Karavdina
//-----------------------------------------------------------

#ifndef KOALINFITTASK_H
#define KOALINFITTASK_H

#include "FairTask.h"

#include "TMatrixDSym.h"
#include "TString.h"

class PndGeoHandling;
class TGraph2DErrors;
class TClonesArray;
class TGeoManager;
class TVector3;
namespace ROOT {
namespace Math {
class Minimizer;
}
}

class KoaLinFitTask : public FairTask {
 public:
  // Constructors/Destructors ---------
  KoaLinFitTask();
  KoaLinFitTask(TString tTCandBranchName, TString tRecoBranchName,
                   TString tOutputBranchName = "KOALAPndTrack",
                   TString tOutputFolder = "Koala");

  virtual ~KoaLinFitTask();

  virtual InitStatus Init();

  virtual void Exec(Option_t* opt);

  virtual void Finish();

  void SetRadLen(double x) { ftotRadLen = 1e-2 * x; }  // rad.length X/X0 [%]

 protected:
  double FCN_MS(const double* vars);
  static double distance_MS(double x, double y, double z, double errx,
                            double erry, const double* p, double* zpr);
  double ScatteredAngle(double radLen);  // calculate uncertainty for kink angle
  double line3DfitMS(TGraph2DErrors* gr, const TVector3& posSeed,
                     const TVector3& dirSeed, std::vector<double>& fitpar,
                     TMatrixDSym* covmatrix);  // fit with kink angle
  double GetSigmaMS(int side) {
    if (side < 1)
      return fsigmaMSa;
    else
      return fsigmaMSb;
  }

  // Input Data------------
  TClonesArray* fTCandArray;
  TClonesArray* fRecoArray;

  TString fTCandBranchName;
  TString fRecoBranchName;
  TString fOutputBranchName;
  TString fOutputFolder;
  // Output Data----------
  TClonesArray* fTrackArray;

  double fPbeam;
  double fsigmaMSa;  // single hit before CVD diamond
  double fsigmaMSb;  // single hit after CVD diamond

  bool hitMergedfl[4];
  double fPDGCode;
  int fCharge;
  PndGeoHandling* fGeoH;

  ROOT::Math::Minimizer* fmin;
  TGraph2DErrors* fGraph2D;

  double ftotRadLen;  // X/X0

  ClassDef(KoaLinFitTask, 2);
};

#endif
//-----------------------------------------------------------
//
// Description:
//      3D Straight Line fitter
//
// Author List:
//      Mathias Michel
//
//-----------------------------------------------------------

#ifndef PNDLMDLINETASK_H
#define PNDLMDLINETASK_H

// Base Class Headers ----------------
#include <TGraph2D.h>
#include <TGraph2DErrors.h>
#include "FairTask.h"

// Collaborating Class Headers -------
#include <map>
#include "TMatrixDSym.h"
#include "TMatrixTSym.h"
#include "TString.h"
#include "TVector3.h"
// Collaborating Class Declarations --
class TClonesArray;
class TGeoManager;

class PndLmdLineTask : public FairTask {
 public:
  // Constructors/Destructors ---------
  PndLmdLineTask(TString hitBranch = "LMDHitsStrip");
#ifndef __CINT__
  PndLmdLineTask(const PndLmdLineTask&) = delete;
  PndLmdLineTask& operator=(const PndLmdLineTask&) = delete;
#endif
  virtual ~PndLmdLineTask();

  virtual InitStatus Init();

  virtual void Exec(Option_t* opt);

 protected:
  // static void SumDistance2(int &, double *, double & sum, double * par, int
  // ); //for Fitter
  // static void LocalFCN(int &, double *, double & sum, double * par, int );
  // //for Fitter in local coordinates
  /* //minimization distance in 3D */
  // static double distance2(double x,double y,double z, double *p);
  // minimization distance in 2D in local coordinates
  // static double distance_l(double x, double y, double z, double errx, double
  // erry, double errz, double *p);
  // minimization perpendicular distance between point and 3D line
  // static double distance_perp(double x,double y,double z, double errx,double
  // erry,double errz, double *p);

  // Input Data------------
  TClonesArray* fTCandArray;
  TClonesArray* fRecoArray;
  TClonesArray* fTruePointArray;

  TString fTCandBranchName;
  TString fRecoBranchName;
  TString fTruePointBranch;
  // Output Data----------
  TClonesArray* fTrackArray;

  // Bool_t firstIt;

  Int_t fTrackcount;

  Int_t fEvent;

  // Fitting ------------
  // void line(double t, double *p, double &x, double &y, double &z);
  double line3Dfit(Int_t nd, TGraph2DErrors* gr, Double_t* fitpar,
                   Double_t* fitparErr);
  double line3Dfit(Int_t nd, TGraph2DErrors* gr, TVector3 posSeed,
                   TVector3 dirSeed, Double_t* fitpar, TMatrixDSym* covmatrix);
  // double line3Dfit(Int_t nd, TGraph2DErrors* gr, TVector3 posSeed, TVector3
  // dirSeed, Double_t* fitpar);

  ClassDef(PndLmdLineTask, 1);
};

#endif
//-----------------------------------------------------------
//
// Description:
//      3D Straight Line fitter
//
// Author List:
//      Mathias Michel
//
//-----------------------------------------------------------

#ifndef PNDLMDIDEALFITTASK_H
#define PNDLMDIDEALFITTASK_H

// Base Class Headers ----------------
#include <TGraph2D.h>
#include <TGraph2DErrors.h>
#include "FairTask.h"

// Collaborating Class Headers -------
#include <map>
#include "TMatrixTSym.h"
#include "TString.h"
#include "TVector3.h"

// Collaborating Class Declarations --
class TClonesArray;
class TGeoManager;

// const Double_t fz0 = 1099.; //z-coordinate of first LMD plane
// void SumDistance2(int &, double *, double & sum, double * par, int ); //for
// Fitter
// void LocalFCN(int &, double *, double & sum, double * par, int ); //for
// Fitter in local coordinates
// minimization distance in 3D
// double distance2(double x,double y,double z, double *p);
// minimization distance in 2D in local coordinates
// double distance_l(double x, double y, double z, double errx, double erry,
// double errz, double *p);//in local coordinates
// minimization perpendicular distance between point and 3D line
// double distance_perp(double x,double y,double z, double errx,double
// erry,double errz, double *p);

class PndLmdIdealFitTask : public FairTask {
 public:
  // Constructors/Destructors ---------
  PndLmdIdealFitTask();
#ifndef __CINT__
  PndLmdIdealFitTask(const PndLmdIdealFitTask&) = delete;
  PndLmdIdealFitTask& operator=(const PndLmdIdealFitTask&) = delete;
#endif
  virtual ~PndLmdIdealFitTask();

  virtual InitStatus Init();

  virtual void Exec(Option_t* opt);

 protected:
  static Double_t fz0;  // z-coordinate of first LMD plane

  // Input Data------------
  TClonesArray* fTCandArray;
  TClonesArray* fRecoArray;
  TClonesArray* fMCPointArray;
  TClonesArray* fDigiArray;
  TClonesArray* fClustArray;
  TString fTCandBranchName;
  TString fRecoBranchName;
  TString fMCPointBranchName;
  TString fDigiBranchName;
  TString fClustBranchName;

  // Output Data----------
  TClonesArray* fTrackArray;

  // Bool_t firstIt;

  Int_t fTrackcount;

  Int_t fEvent;

  ClassDef(PndLmdIdealFitTask, 1);
};

#endif
// -------------------------------------------------------------------------
// -----                      PndLinTrack header file                  -----
// -----                       Created by M. Michel                    -----
// -----                       Modifided by A.Karavdina                -----
// -------------------------------------------------------------------------

/** PndLinTrack.h
 *@author M.Michel <michel@kph.uni-mainz.de>
 **
 ** A container for straight line tracks
 **/

#ifndef PNDLINTRACK_H
#define PNDLINTRACK_H

#include "TMatrixDSym.h"
#include "TMatrixTSym.h"
#include "TString.h"
#include "TVector3.h"

#include <stdio.h>
#include <iostream>

class PndLinTrack : public TObject {
 public:
  /** Default constructor (not for use) **/
  PndLinTrack();

  /** Standard constructor with all paramneters
   *@param detName Detector Name
   *@param pX      Parameter of Fit [cm]
   *@param chi     ChiSquare of Fit
   *@param first   Id of first Hit
   *@param last    Id of last Hit
   *@param cand    Id of TrackCandidate
   **/

  /* PndLinTrack(TString detName, Double_t z0, Double_t p0, Double_t p1,
   * Double_t p2, Double_t p3,  */
  /* 	      Double_t p0err, Double_t p1err, Double_t p2err, Double_t p3err, */
  /* 	      Double_t chi, Int_t first, Int_t last, Int_t cand); */
  PndLinTrack(TString detName, Double_t p0, Double_t p1, Double_t p2,
              Double_t p3, Double_t p4, Double_t p5, Double_t chi, Int_t first,
              Int_t last, Int_t cand);

  /** Destructor **/
  virtual ~PndLinTrack();

  /** Accessors **/

  void SetDetName(TString name) { fDetName = name; }
  void SetCovarianceMatrix(TMatrixDSym covmatrix) {
    for (size_t i = 0; i < 6; i++) {
      for (size_t j = 0; j < 6; j++) {
        fCovMatrix[i][j] = covmatrix[i][j];
      }
    }
  }

  TString GetDetName() const { return fDetName; }
  void GetPar(Double_t* par) const {
    par[0] = fP0;
    par[1] = fP1;
    par[2] = fP2;
    par[3] = fP3;
    par[4] = fP4;
    par[5] = fP5;
  }
  /* TVector3	GetStartVec()		const { return TVector3(fP0,fP2,0.);} */
  TVector3 GetStartVec() const { return TVector3(fP0, fP2, fP4); }
  // TVector3	GetStartVec();
  TVector3 GetDirectionVec() const { return TVector3(fP1, fP3, fP5); }
  // TVector3	GetDirectionVec();
  TVector3 GetStartErrVec();
  TVector3 GetDirectionErrVec();
  /* TVector3      GetParErr(Double_t* errpar)  */
  /*   const {
   * errpar[0]=fP0err;errpar[1]=fP1err;errpar[2]=fP2err;errpar[3]=fP3err;errpar[4]=fP4err;}
   */
  Double_t GetChiSquare() const { return fChiSq; }
  Int_t GetFirstHit() const { return fFirst; }
  Int_t GetLastHit() const { return fLast; }
  Int_t GetTCandID() const { return fCandId; }

  void GetParErr(Double_t* errpar);
  TMatrixDSym GetCovarianceMatrix() { return fCovMatrix; }

 private:
  TString fDetName;  // Detector name
  //  Double_t fz0;// z-position of first LMD plane
  Double_t fP0, fP1, fP2, fP3, fP4, fP5;  // fit-parameter
  // start (P0, P2, P4), direction (P1, P3, P5) straight line
  TMatrixDSym fCovMatrix;
  // Double_t fP0err, fP1err, fP2err, fP3err, fP4err; // errors of parameters
  Double_t fChiSq;  // Chi-Square of Fit
  Int_t fFirst, fLast;
  Int_t fCandId;  // TrackCand id

  ClassDef(PndLinTrack, 10);
};

#endif
// -------------------------------------------------------------------------
// -----                      PndLinTrack header file                  -----
// -----                       Created by M. Michel                    -----
// -----                       Modifided by A.Karavdina                -----
// -------------------------------------------------------------------------

/** PndLinTrack.h
 *@author M.Michel <michel@kph.uni-mainz.de>
 **
 ** A container for straight line tracks
 **/

#ifndef KOALINTRACK_H
#define KOALINTRACK_H

#include "TMatrixDSym.h"
#include "TMatrixTSym.h"
#include "TString.h"
#include "TVector3.h"

#include <stdio.h>
#include <iostream>

class KoaLinTrack : public TObject {
 public:
  /** Default constructor (not for use) **/
  KoaLinTrack();

  /** Standard constructor with all paramneters
   *@param detName Detector Name
   *@param pX      Parameter of Fit [cm]
   *@param chi     ChiSquare of Fit
   *@param first   Id of first Hit
   *@param last    Id of last Hit
   *@param cand    Id of TrackCandidate
   **/

  /* KoaLinTrack(TString detName, Double_t z0, Double_t p0, Double_t p1,
   * Double_t p2, Double_t p3,  */
  /* 	      Double_t p0err, Double_t p1err, Double_t p2err, Double_t p3err, */
  /* 	      Double_t chi, Int_t first, Int_t last, Int_t cand); */
  KoaLinTrack(TString detName, Double_t p0, Double_t p1, Double_t p2,
              Double_t p3, Double_t p4, Double_t p5, Double_t chi, Int_t first,
              Int_t last, Int_t cand);

  /** Destructor **/
  virtual ~KoaLinTrack();

  /** Accessors **/

  void SetDetName(TString name) { fDetName = name; }
  void SetCovarianceMatrix(TMatrixDSym covmatrix) {
    for (size_t i = 0; i < 6; i++) {
      for (size_t j = 0; j < 6; j++) {
        fCovMatrix[i][j] = covmatrix[i][j];
      }
    }
  }

  TString GetDetName() const { return fDetName; }
  void GetPar(Double_t* par) const {
    par[0] = fP0;
    par[1] = fP1;
    par[2] = fP2;
    par[3] = fP3;
    par[4] = fP4;
    par[5] = fP5;
  }
  /* TVector3	GetStartVec()		const { return TVector3(fP0,fP2,0.);} */
  TVector3 GetStartVec() const { return TVector3(fP0, fP2, fP4); }
  // TVector3	GetStartVec();
  TVector3 GetDirectionVec() const { return TVector3(fP1, fP3, fP5); }
  // TVector3	GetDirectionVec();
  TVector3 GetStartErrVec();
  TVector3 GetDirectionErrVec();
  /* TVector3      GetParErr(Double_t* errpar)  */
  /*   const {
   * errpar[0]=fP0err;errpar[1]=fP1err;errpar[2]=fP2err;errpar[3]=fP3err;errpar[4]=fP4err;}
   */
  Double_t GetChiSquare() const { return fChiSq; }
  Int_t GetFirstHit() const { return fFirst; }
  Int_t GetLastHit() const { return fLast; }
  Int_t GetTCandID() const { return fCandId; }

  void GetParErr(Double_t* errpar);
  TMatrixDSym GetCovarianceMatrix() { return fCovMatrix; }

 private:
  TString fDetName;  // Detector name
  //  Double_t fz0;// z-position of first LMD plane
  Double_t fP0, fP1, fP2, fP3, fP4, fP5;  // fit-parameter
  // start (P0, P2, P4), direction (P1, P3, P5) straight line
  TMatrixDSym fCovMatrix;
  // Double_t fP0err, fP1err, fP2err, fP3err, fP4err; // errors of parameters
  Double_t fChiSq;  // Chi-Square of Fit
  Int_t fFirst, fLast;
  Int_t fCandId;  // TrackCand id

  ClassDef(KoaLinTrack, 10);
};

#endif
// -------------------------------------------------------------------------
// -----                   PndLmdGeaneTask header file                 -----
// -----                  Created 20/03/07  by R.Kliemt                -----
// -----                  modified for Lmd by M. Michel & A.Karavdina  -----
// -------------------------------------------------------------------------

/** PndLmdGeaneTask.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Displays all available informations for a given event
 **/

#ifndef PndLmdGeaneTask_H
#define PndLmdGeaneTask_H

// framework includes
#include "FairTask.h"
#include "TH1.h"
//#include "GFTrackCand.h"
#include "FairGeanePro.h"
#include "FairTrackParP.h"
#include "TMatrixD.h"
#include "TNtuple.h"
#include "TVector3.h"
//#include "PndSdsGeoHandling.h"
#include <map>
#include <vector>
#include "PndGeoHandling.h"
class TClonesArray;
class PndSdsCluster;
// class TGeant3;//GEANE uses Geant3!
// class TGeant4;

class PndLmdGeaneTask : public FairTask {
 public:
  /** Default constructor **/
  PndLmdGeaneTask();

  /// Set up beam momuntum value and position of interaction point
  PndLmdGeaneTask(Double_t pBeam, TVector3 IP, bool is_prefiltered = true);

  /** Destructor **/
  ~PndLmdGeaneTask();

  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  virtual void Finish();

  FairTrackParP* PropToPlane(FairTrackParP* fStartPst, double zpos, int dir,
                             bool& isProp);  // propagation between planes
 private:
  FairGeanePro* fPro;
  PndGeoHandling* fGeoH;
  int fEventNr;
  bool fUseMVDPoint;
  Double_t fPbeam;
  Int_t fPDGid;
  TVector3 vtx;
  FairField* pndField;
  std::map<int, std::vector<int> > fTrackPixHitIdMap;    // Track -> PixHitId
  std::map<int, std::vector<int> > fTrackStripHitIdMap;  // Track -> StripHitId

  std::string track_branch_name;

  // Input Data ----------
  TClonesArray* fTracks;  // Real tracks

  // Output Data -------
  TClonesArray* fTrackParGeane;
  TClonesArray* fTrackParIni;
  TClonesArray* fTrackParFinal;
  TClonesArray* fDetName;

  //----------------------------------------

  void Register();

  void Reset();

  void ProduceHits();

  ClassDef(PndLmdGeaneTask, 2);
};

#endif
// -------------------------------------------------------------------------
// -----                   KoaGeaneTask header file                 -----
// -----                  Created 20/03/07  by R.Kliemt                -----
// -----                  modified for Lmd by M. Michel & A.Karavdina  -----
// -------------------------------------------------------------------------

/** KoaGeaneTask.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Displays all available informations for a given event
 **/

#ifndef KoaGeaneTask_H
#define KoaGeaneTask_H

// framework includes
#include "FairTask.h"
#include "TH1.h"
//#include "GFTrackCand.h"
#include "FairGeanePro.h"
#include "FairTrackParP.h"
#include "TMatrixD.h"
#include "TNtuple.h"
#include "TVector3.h"
//#include "PndSdsGeoHandling.h"
#include <map>
#include <vector>
#include "PndGeoHandling.h"
class TClonesArray;
class PndSdsCluster;
// class TGeant3;//GEANE uses Geant3!
// class TGeant4;

class KoaGeaneTask : public FairTask {
 public:
  /** Default constructor **/
  KoaGeaneTask();

  /// Set up beam momuntum value and position of interaction point
  KoaGeaneTask(Double_t pBeam, TVector3 IP, bool is_prefiltered = true);

  /** Destructor **/
  ~KoaGeaneTask();

  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  virtual void Finish();

  FairTrackParP* PropToPlane(FairTrackParP* fStartPst, double zpos, int dir,
                             bool& isProp);  // propagation between planes
 private:
  FairGeanePro* fPro;
  PndGeoHandling* fGeoH;
  int fEventNr;
  bool fUseMVDPoint;
  Double_t fPbeam;
  Int_t fPDGid;
  TVector3 vtx;
  std::map<int, std::vector<int> > fTrackPixHitIdMap;    // Track -> PixHitId
  std::map<int, std::vector<int> > fTrackStripHitIdMap;  // Track -> StripHitId

  std::string track_branch_name;

  // Input Data ----------
  TClonesArray* fTracks;  // Real tracks

  // Output Data -------
  TClonesArray* fTrackParGeane;
  TClonesArray* fTrackParIni;
  TClonesArray* fTrackParFinal;
  TClonesArray* fDetName;

  //----------------------------------------

  void Register();

  void Reset();

  void ProduceHits();

  ClassDef(KoaGeaneTask, 2);
};

#endif
//-----------------------------------------------------------
//
// Description:
//      Task to cut backgroundevents by backpropagating hit in the lumi detector to the z=0 plane 
//
// Author:
//	Jens Olaf Frech
//-----------------------------------------------------------

#ifndef KOABACKPROP_H
#define KOABACKPROP_H

// Base Class Headers ----------------
#include "FairTask.h"

// Collaborating Class Headers -------
#include <map>
#include "TH1.h"
#include "TH2.h"
#include "TString.h"

// Collaborating Class Declarations --
class TClonesArray;
class TGeoManager;

class KoaBackProp : public FairTask {
 public:
  // Constructors/Destructors ---------
  KoaBackProp();
#ifndef __CINT__
  KoaBackProp(const KoaBackProp&) = delete;
  KoaBackProp& operator=(const KoaBackProp&) = delete;
#endif
  virtual ~KoaBackProp();
  void SetVerboseLevel(int verbose) { verboseLevel = verbose; };
  virtual InitStatus Init();
  virtual void FinishTask();
  
  virtual void Exec(Option_t* opt);
  
  
 protected:
  int verboseLevel;
  
  TClonesArray* fTrkCandArray;
  TClonesArray* fTrkArray;
  TClonesArray* fMCArray;
  TClonesArray* fTrkOutArray;
  
  TString fHitName;
  TString fMCHitName;
  TString fTrkCandName;
  TString fTrkName;
  TString fTrkOutName;
  int fEventNr;




 ClassDef(KoaBackProp, 3);
};

#endif
//-----------------------------------------------------------
//
// Description:
//      3D Straight Line fitter
//
// Author List:
//      Mathias Michel
//      Anastasia Karavdina
//-----------------------------------------------------------

#ifndef KOACOMP_H
#define KOACOMP_H

#include "FairTask.h"

#include "TMatrixDSym.h"
#include "TString.h"
#include "PndTrackCand.h"
#include <vector>

class PndGeoHandling;
class TGraph2DErrors;
class TClonesArray;
class TGeoManager;
class TVector3;
namespace ROOT {
namespace Math {
class Minimizer;
}
}

class KoaComp : public FairTask {
 public:
  // Constructors/Destructors ---------
  KoaComp();
  KoaComp(TString tBackPropBranchName, TString tRecoBranchName,
	    TString tOutputBranchName = "LMDCompa",
	    TString tKoaOutputBranchName = "KOALACompa",
	    TString tOutputFolder = "Koala");

  virtual ~KoaComp();

  virtual InitStatus Init();

  virtual void Exec(Option_t* opt);

  virtual void Finish();

  void SetRadLen(double x) { ftotRadLen = 1e-2 * x; }  // rad.length X/X0 [%]

 protected:
  double FCN_MS(const double* vars);
  static double distance_MS(double x, double y, double z, double errx,
                            double erry, const double* p, double* zpr);
  double ScatteredAngle(double radLen);  // calculate uncertainty for kink angle
  double line3DfitMS(TGraph2DErrors* gr, const TVector3& posSeed,
                     const TVector3& dirSeed, std::vector<double>& fitpar,
                     TMatrixDSym* covmatrix);  // fit with kink angle
  double GetSigmaMS(int side) {
    if (side < 1)
      return fsigmaMSa;
    else
      return fsigmaMSb;
  }

  // Input Data------------
  TClonesArray* fBackPropArray;
  TClonesArray* fRecoArray;

  TString fBackPropBranchName;
  TString fRecoBranchName;
  TString fOutputBranchName;
  TString fOutputFolder;
  TString fKoaOutputBranchName;
  // Output Data----------
  TClonesArray* fTrackArray;
  TClonesArray* fKoaRecoArray;

  double fPbeam;
  double fsigmaMSa;  // single hit before CVD diamond
  double fsigmaMSb;  // single hit after CVD diamond

  bool hitMergedfl[4];
  double fPDGCode;
  int fCharge;
  PndGeoHandling* fGeoH;

  ROOT::Math::Minimizer* fmin;
  TGraph2DErrors* fGraph2D;

  double ftotRadLen;  // X/X0

std::vector <int> GetPndTrackCand();

  ClassDef(KoaComp, 2);
};

#endif
//-----------------------------------------------------------
//
// Description:
//      3D Straight Line fitter
//
// Author List:
//      Mathias Michel
//      Anastasia Karavdina
//-----------------------------------------------------------

#ifndef KOAPLOTI_H
#define KOAPLOTI_H

#include "FairTask.h"

#include "TMatrixDSym.h"
#include "TString.h"
#include "PndTrackCand.h"
#include <TH2.h>
#include <TF1.h>
#include <TCanvas.h>
#include <vector>

class PndGeoHandling;
class TGraph2DErrors;
class TClonesArray;
class TGeoManager;
class TVector3;
namespace ROOT {
namespace Math {
class Minimizer;
}
}

class KoaPloti : public FairTask {
 public:
  // Constructors/Destructors ---------
  KoaPloti();
  KoaPloti(TString tCompBranchName,TString tKoaCompBranchName, TString tRecoBranchName,TString tKoaRecoBranchName );

  virtual ~KoaPloti();

  virtual InitStatus Init();

  virtual void Exec(Option_t* opt);

  virtual void Finish();

  void SetRadLen(double x) { ftotRadLen = 1e-2 * x; }  // rad.length X/X0 [%]

 protected:
  double FCN_MS(const double* vars);
  static double distance_MS(double x, double y, double z, double errx,
                            double erry, const double* p, double* zpr);
  double ScatteredAngle(double radLen);  // calculate uncertainty for kink angle
  double line3DfitMS(TGraph2DErrors* gr, const TVector3& posSeed,
                     const TVector3& dirSeed, std::vector<double>& fitpar,
                     TMatrixDSym* covmatrix);  // fit with kink angle
  double GetSigmaMS(int side) {
    if (side < 1)
      return fsigmaMSa;
    else
      return fsigmaMSb;
  }

  // Input Data------------
  TClonesArray* fCompArray;
  TClonesArray* fKoaCompArray;
  TClonesArray* fRecoArray;
  TClonesArray* fKoaRecoArray;

  TString fCompBranchName;
  TString fKoaCompBranchName;
  TString fRecoBranchName;
  TString fKoaRecoBranchName;

  TH2F hReco2D;
  TH2F hComp2D;
  TH2F hKoaComp2D;
  TH2F hKoaReco2D;
  ;
  // Output Data----------
  TClonesArray* fTrackArray;
  TClonesArray* fKoaArray;

  double fPbeam;
  double fsigmaMSa;  // single hit before CVD diamond
  double fsigmaMSb;  // single hit after CVD diamond

  bool hitMergedfl[4];
  double fPDGCode;
  int fCharge;
  PndGeoHandling* fGeoH;

  ROOT::Math::Minimizer* fmin;
  TGraph2DErrors* fGraph2D;

  double ftotRadLen;  // X/X0



  ClassDef(KoaPloti, 2);
};

#endif
//-----------------------------------------------------------
//
// Description:
//      Efficiency determination tool
//
// Author List:
//      Jens Frech
//-----------------------------------------------------------

#ifndef KOAEFFI_H
#define KOAEFFI_H

#include "FairTask.h"

#include "TMatrixDSym.h"
#include "TString.h"
#include "PndTrackCand.h"
#include <TH2.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TEfficiency.h>
#include <vector>

class PndGeoHandling;
class TGraph2DErrors;
class TClonesArray;
class TGeoManager;
class TVector3;
namespace ROOT {
namespace Math {
class Minimizer;
}
}

class KoaEffi : public FairTask {
 public:
  // Constructors/Destructors ---------
  KoaEffi();
  KoaEffi(TString tMCBranchName, TString tMCTrackName,TString tRecoBranchName, TString tCompBranchName);

  virtual ~KoaEffi();

  virtual InitStatus Init();

  virtual void Exec(Option_t* opt);

  virtual void Finish();

  void SetRadLen(double x) { ftotRadLen = 1e-2 * x; }  // rad.length X/X0 [%]

 protected:
  double FCN_MS(const double* vars);
  static double distance_MS(double x, double y, double z, double errx,
                            double erry, const double* p, double* zpr);
  double ScatteredAngle(double radLen);  // calculate uncertainty for kink angle
  double line3DfitMS(TGraph2DErrors* gr, const TVector3& posSeed,
                     const TVector3& dirSeed, std::vector<double>& fitpar,
                     TMatrixDSym* covmatrix);  // fit with kink angle
  double GetSigmaMS(int side) {
    if (side < 1)
      return fsigmaMSa;
    else
      return fsigmaMSb;
  }

  // Input Data------------
  TClonesArray* fMCArray;
  TClonesArray* fMCTrackArray;
  TClonesArray* fRecoArray;
  TClonesArray* fCompArray;
  

  TString fMCBranchName;
  TString fMCTrackName;
  TString fRecoBranchName;
  TString fCompBranchName;
  

  TH2F hMC2D;
  TH2F hMCReco;
  TH2F hReco;
  TH2F hMCComp;
  TH2F hComp;
  TH2F hRecoComp;
  TH1F hKoalaResiY;
  TH1F hKoalaResiZ;
  
  
  // Output Data----------
  TClonesArray* fMCOutArray;
  TClonesArray* fBackoutArray;

  double fPbeam;
  double fsigmaMSa;  // single hit before CVD diamond
  double fsigmaMSb;  // single hit after CVD diamond

  bool hitMergedfl[4];
  double fPDGCode;
  int fCharge;
  PndGeoHandling* fGeoH;

  ROOT::Math::Minimizer* fmin;
  TGraph2DErrors* fGraph2D;

  double ftotRadLen;  // X/X0



  ClassDef(KoaEffi, 2);
};

#endif
//-----------------------------------------------------------
//
// Description:
//      Plot Angle vs Momentum
//
// Author List:
//      Jens Frech
//-----------------------------------------------------------

#ifndef MOMENTUMVIS_H
#define MOMENTUMVIS_H

#include "FairTask.h"

#include "TMatrixDSym.h"
#include "TString.h"
#include "PndTrackCand.h"
#include <TH2.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TEfficiency.h>
#include <vector>

class PndGeoHandling;
class TGraph2DErrors;
class TClonesArray;
class TGeoManager;
class TVector3;
namespace ROOT {
namespace Math {
class Minimizer;
}
}

class MomentumVi : public FairTask {
 public:
  // Constructors/Destructors ---------
  MomentumVi();
  MomentumVi(TString tMCBranchName, TString tMCTrackName,TString tRecoBranchName,TString tKoalaMCBranchName,TString tKoalaMCTrackName, TString tKoalaRecoBranchName, TString tBackBranchName, TString tTrkName);

  virtual ~MomentumVi();

  virtual InitStatus Init();

  virtual void Exec(Option_t* opt);

  virtual void Finish();

  void SetRadLen(double x) { ftotRadLen = 1e-2 * x; }  // rad.length X/X0 [%]

 protected:
  double FCN_MS(const double* vars);
  static double distance_MS(double x, double y, double z, double errx,
                            double erry, const double* p, double* zpr);
  double ScatteredAngle(double radLen);  // calculate uncertainty for kink angle
  double line3DfitMS(TGraph2DErrors* gr, const TVector3& posSeed,
                     const TVector3& dirSeed, std::vector<double>& fitpar,
                     TMatrixDSym* covmatrix);  // fit with kink angle
  double GetSigmaMS(int side) {
    if (side < 1)
      return fsigmaMSa;
    else
      return fsigmaMSb;
  }

  // Input Data------------
  TClonesArray* fMCArray;
  TClonesArray* fMCTrackArray;
  TClonesArray* fRecoArray;
  TClonesArray* fKoalaMCArray;
  TClonesArray* fKoalaMCTrackArray;
  TClonesArray* fKoalaRecoArray;
  TClonesArray* fBackArray;
  TClonesArray* fTrkArray;
  

  TString fMCBranchName;
  TString fMCTrackName;
  TString fRecoBranchName;
  TString fKoalaMCBranchName;
  TString fKoalaMCTrackName;
  TString fKoalaRecoBranchName;
  TString fBackBranchName;
  TString fTrkName;
  

  TH2F hLMDAng;
  TH2F hKoalaAng;
  TH2F hLMDX;
  TH2F hLMDY;
  TH2F hLMDtheta;
  TH2F hLMDMCphi;
  TH2F hLMDMCtheta;
  TH2F hLMDphi;
  TH2F hKoalaphi;
  TH2F hKoalatheta;
  TH2F hKoalathetaphi;
  TH2F hKoalaHitphi;
  TH2F hKoalaHittheta;
  TH2F hKoalaHitthetaphi;
  TH2F hKoalaHitphireco;
  TH2F hKoalaHitthetareco;
  TH2F hKoalaHitthetaphireco;
  TH2F hKoalaphiMC;
  TH2F hKoalathetaMC;
  TH2F hKoalathetaphiMC;
  TH2F hKoalaZ;
  TH2F hKoalaY;
  TH1F hLPhi;
  TH1F hLPhiMC;
  TH1F hLP;
  TH1F hLPMC;
  TH1F hLTheta;
  TH1F hLThetaMC;
  TH1F hKPhi;
  TH1F hKPhiMC;
  TH1F hKP;
  TH1F hKPMC;
  TH1F hKTheta;
  TH1F hKThetaMC;
  TH1F hKoPhi;
  TH1F hKoP;
  TH1F hKoTheta;
  TH1F hKoalaThetaReco;
  
  
  
  // Output Data----------
  TClonesArray* fMCOutArray;
  TClonesArray* fBackoutArray;

  double fPbeam;
  double fsigmaMSa;  // single hit before CVD diamond
  double fsigmaMSb;  // single hit after CVD diamond

  bool hitMergedfl[4];
  double fPDGCode;
  int fCharge;
  PndGeoHandling* fGeoH;

  ROOT::Math::Minimizer* fmin;
  TGraph2DErrors* fGraph2D;

  double ftotRadLen;  // X/X0



  ClassDef(MomentumVi, 2);
};

#endif
//-----------------------------------------------------------
//
// Description:
//      Efficiency determination tool
//
// Author List:
//      Jens Frech
//-----------------------------------------------------------

#ifndef LMDEFFI_H
#define LMDEFFI_H

#include "FairTask.h"

#include "TMatrixDSym.h"
#include "TString.h"
#include "PndTrackCand.h"
#include <TH2.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TEfficiency.h>
#include <vector>

class PndGeoHandling;
class TGraph2DErrors;
class TClonesArray;
class TGeoManager;
class TVector3;
namespace ROOT {
namespace Math {
class Minimizer;
}
}

class LmdEffi : public FairTask {
 public:
  // Constructors/Destructors ---------
  LmdEffi();
  LmdEffi(TString tMCBranchName, TString tMCTrackName,TString tRecoBranchName ,TString tTrkName ,TString tBackBranchName,TString tBackTrackBranchName, TString tCompBranchName );

  virtual ~LmdEffi();

  virtual InitStatus Init();

  virtual void Exec(Option_t* opt);

  virtual void Finish();

  void SetRadLen(double x) { ftotRadLen = 1e-2 * x; }  // rad.length X/X0 [%]

 protected:
  double FCN_MS(const double* vars);
  static double distance_MS(double x, double y, double z, double errx,
                            double erry, const double* p, double* zpr);
  double ScatteredAngle(double radLen);  // calculate uncertainty for kink angle
  double line3DfitMS(TGraph2DErrors* gr, const TVector3& posSeed,
                     const TVector3& dirSeed, std::vector<double>& fitpar,
                     TMatrixDSym* covmatrix);  // fit with kink angle
  double GetSigmaMS(int side) {
    if (side < 1)
      return fsigmaMSa;
    else
      return fsigmaMSb;
  }

  // Input Data------------
  TClonesArray* fMCArray;
  TClonesArray* fMCTrackArray;
  TClonesArray* fRecoArray;
  TClonesArray* fTrkArray;
  TClonesArray* fBackArray;  
  TClonesArray* fBackTrackArray;  
  TClonesArray* fCompArray;

  TString fMCBranchName;
  TString fMCTrackName;
  TString fRecoBranchName;
  TString fTrkName;
  TString fBackBranchName;
  TString fBackTrackBranchName;
  TString fCompBranchName;

  TH2F hMC2D;
  TH2F hBack2D;
  TH2F hComp2D;
  TH2F hMCComp;
  TH2F hCompBack;
  TH2F hBackdiv;
  TH2F hRecoTrack;
  TH2F hMCReco;
  TH2F hReco;
  TH2F hReco4Hits;
  TH2F hRecoComp;
  TH2F hTrackProp;
  TH2F hTrack2D;
  TH2F hBPPos;
  TH1F hRecoResiX;
  TH1F hRecoResiY;
  TH1F hCompResiX;
  TH1F hCompResiY;
  TH1F hCompBPResiZ;
  TH1F hCompBPResiY;
  TH1F hCompBPResiX;
  TH1F hCompResitheta;
  TH1F hCompResiphi;
  
  
  // Output Data----------
  TClonesArray* fMCOutArray;
  TClonesArray* fBackoutArray;

  double fPbeam;
  double fsigmaMSa;  // single hit before CVD diamond
  double fsigmaMSb;  // single hit after CVD diamond

  bool hitMergedfl[4];
  double fPDGCode;
  int fCharge;
  PndGeoHandling* fGeoH;

  ROOT::Math::Minimizer* fmin;
  TGraph2DErrors* fGraph2D;

  double ftotRadLen;  // X/X0



  ClassDef(LmdEffi, 2);
};

#endif
//-----------------------------------------------------------
//
// Description:
//      Task to show the origin of detectect Events on the IP-plan
//      Should not be placed in the script for the queue 
//
// Author:
//	Jens Olaf Frech
//-----------------------------------------------------------

#ifndef KOAIPVIS_H
#define KOAIPVIS_H

// Base Class Headers ----------------
#include "FairTask.h"

// Collaborating Class Headers -------
#include <map>
#include "TH1.h"
#include "TH2.h"
#include "TString.h"
#include <TCanvas.h>

// Collaborating Class Declarations --
class TClonesArray;
class TGeoManager;

class KoaIPvis : public FairTask {
 public:
  // Constructors/Destructors ---------
  KoaIPvis();
#ifndef __CINT__
  KoaIPvis(const KoaIPvis&) = delete;
  KoaIPvis& operator=(const KoaIPvis&) = delete;
#endif
  virtual ~KoaIPvis();
  void SetVerboseLevel(int verbose) { verboseLevel = verbose; };
  virtual InitStatus Init();
  virtual void FinishTask();
  
  virtual void Exec(Option_t* opt);
  
  
 protected:
  int verboseLevel;
  
  TClonesArray* fTrkCandArray;
  TClonesArray* fTrkArray;
  TClonesArray* fMCArray;
  TClonesArray* fTrkOutArray;
  
  TString fHitName;
  TString fMCHitName;
  TString fTrkCandName;
  TString fTrkName;
  TString fTrkOutName;
  int fEventNr;

   TH2F hIPBackProp;
   TH1F hIPBPresi;
   TH1F hIPresix;
   TH1F hIPresiy;
   TH1F hIPresiz;



 ClassDef(KoaIPvis, 3);
};

#endif
//-----------------------------------------------------------
//
// Description:
//      Task to filter fitted tracks based on chi2 and hits comparasion
//
// Author:
//	Anastasia Karavdina
//-----------------------------------------------------------

#ifndef PNDLMDTRKSFILTERTASK_H
#define PNDLMDTRKSFILTERTASK_H

// Base Class Headers ----------------
#include "FairTask.h"

// Collaborating Class Headers -------
#include <map>
#include "TH1.h"
#include "TH2.h"
#include "TString.h"

// Collaborating Class Declarations --
class TClonesArray;
class TGeoManager;

class PndLmdTrksFilterTask : public FairTask {
 public:
  // Constructors/Destructors ---------
  PndLmdTrksFilterTask();
#ifndef __CINT__
  PndLmdTrksFilterTask(const PndLmdTrksFilterTask&) = delete;
  PndLmdTrksFilterTask& operator=(const PndLmdTrksFilterTask&) = delete;
#endif
  virtual ~PndLmdTrksFilterTask();
  void SetVerboseLevel(int verbose) { verboseLevel = verbose; };
  virtual InitStatus Init();
  virtual void FinishTask();

  virtual void Exec(Option_t* opt);
  void SetSkipKinFilt(bool fl) { flSkipKinFilt = fl; };
  void SetBOXFilt(bool fl) { flBOXKinFilt = fl; };
  void SetXThFilt(bool fl) { flXThKinFilt = fl; };
  void SetYPhFilt(bool fl) { flYPhKinFilt = fl; };
  void SetDX(double dx) { fdX = dx; }
  void SetDY(double dy) { fdY = dy; }

 protected:
  int verboseLevel;
  // Input Data------------
  TClonesArray* fTrkCandArray;
  TClonesArray* fTrkArray;
  TClonesArray* fTrkOutArray;

  TString fHitName;
  TString fMCHitName;
  TString fTrkCandName;
  TString fTrkName;
  TString fTrkOutName;
  int fEventNr;
  bool flSkipKinFilt;
  bool flBOXKinFilt;
  bool flXThKinFilt;
  bool flYPhKinFilt;

  double fdX;  // beam shift in X
  double fdY;  // beam shift in Y

  ClassDef(PndLmdTrksFilterTask, 3);
};

#endif
//-----------------------------------------------------------
//
// Description:
//      Task to filter fitted tracks based on chi2 and hits comparasion
//
// Author:
//	Anastasia Karavdina
//-----------------------------------------------------------

#ifndef KOATRKSFILTERTASK_H
#define KOATRKSFILTERTASK_H

// Base Class Headers ----------------
#include "FairTask.h"

// Collaborating Class Headers -------
#include <map>
#include "TH1.h"
#include "TH2.h"
#include "TString.h"

// Collaborating Class Declarations --
class TClonesArray;
class TGeoManager;

class KoaTrksFilterTask : public FairTask {
 public:
  // Constructors/Destructors ---------
  KoaTrksFilterTask();
#ifndef __CINT__
  KoaTrksFilterTask(const KoaTrksFilterTask&) = delete;
  KoaTrksFilterTask& operator=(const KoaTrksFilterTask&) = delete;
#endif
  virtual ~KoaTrksFilterTask();
  void SetVerboseLevel(int verbose) { verboseLevel = verbose; };
  virtual InitStatus Init();
  virtual void FinishTask();

  virtual void Exec(Option_t* opt);
  void SetSkipKinFilt(bool fl) { flSkipKinFilt = fl; };
  void SetBOXFilt(bool fl) { flBOXKinFilt = fl; };
  void SetXThFilt(bool fl) { flXThKinFilt = fl; };
  void SetYPhFilt(bool fl) { flYPhKinFilt = fl; };
  void SetDX(double dx) { fdX = dx; }
  void SetDY(double dy) { fdY = dy; }

 protected:
  int verboseLevel;
  // Input Data------------
  TClonesArray* fTrkCandArray;
  TClonesArray* fTrkArray;
  TClonesArray* fTrkOutArray;

  TString fHitName;
  TString fMCHitName;
  TString fTrkCandName;
  TString fTrkName;
  TString fTrkOutName;
  int fEventNr;
  bool flSkipKinFilt;
  bool flBOXKinFilt;
  bool flXThKinFilt;
  bool flYPhKinFilt;

  double fdX;  // beam shift in X
  double fdY;  // beam shift in Y

  ClassDef(KoaTrksFilterTask, 3);
};

#endif
// -------------------------------------------------------------------------
// -----                   PndLmdSigCleanTask header file            -----
// -----                  Created 26/02/14  by A.Karavdina            -----
// -------------------------------------------------------------------------

/** PndLmdSigCleanTask.h
 *@author A.Karavdina <karavdin@kph.uni-mainz.de>
 **
 ** Clean sample with reconstructed tracks from background
 ** by using momentum cut or multivariable cut
 **/

#ifndef PndLmdSigCleanTask_H
#define PndLmdSigCleanTask_H

// framework includes
#include "FairTask.h"
#include "TH1.h"
//#include "GFTrackCand.h"
//#include "FairGeanePro.h"
#include "FairTrackParH.h"
#include "FairTrackParP.h"
#include "TMatrixD.h"
#include "TNtuple.h"
#include "TVector3.h"
//#include "PndSdsGeoHandling.h"
#include <map>
#include <vector>
#include "PndGeoHandling.h"
// TMVA includes
#include "TMVA/MethodCuts.h"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"
//#include "PndMultiField.h"
class TClonesArray;
class PndSdsCluster;
class PndLmdSigCleanTask : public FairTask {
 public:
  /** Default constructor **/
  PndLmdSigCleanTask();

  /// Set up beam momuntum value
  PndLmdSigCleanTask(Double_t pBeam, TString dir);

  /** Destructor **/
  ~PndLmdSigCleanTask();

  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  virtual void Finish();

  bool CheckMVA(FairTrackParH* fTrk);
  bool CheckMom(double prec);
  bool Check(FairTrackParH* fTrk);
  void SetXY(bool setXY) { fXYcut = setXY; };

  bool CheckXY(FairTrackParP* fTrk);
  void SetDX(double dx) { fdX = dx; }
  void SetDY(double dy) { fdY = dy; }

 private:
  TClonesArray* fTrackParFinal;

  PndGeoHandling* fGeoH;
  int fEventNr;
  Double_t fPbeam;
  bool fXYcut;

  // Input Data ----------
  TClonesArray* fRecBPTracks;
  TClonesArray* fTrkArray;

  // MVA Data -------
  TString fdir;
  TString fmethodName;
  Float_t axrec, ayrec, aprec;
  Float_t azrec, athrec, aphrec;
  TMVA::Reader* reader;

  //----------------------------------------
  double fdX;  // beam shift in X
  double fdY;  // beam shift in Y

  TH1* hResponse;

  ClassDef(PndLmdSigCleanTask, 2);
};

#endif
// -------------------------------------------------------------------------
// -----      PndLmdNoiseTrkSuppressionTask header file            -----
// -----                  Created 21/07/15  by A.Karavdina            -----
// -------------------------------------------------------------------------
/** PndLmdNoiseTrkSuppressionTask.h
 *@author A.Karavdina <karavdin@kph.uni-mainz.de>
 **
 ** Clean sample with reconstructed tracks before back propagation
 ** from background due to noise hits
 ** by multivariable cut
 **/
#ifndef PndLmdNoiseTrkSuppressionTask_H
#define PndLmdNoiseTrkSuppressionTask_H

// framework includes
#include "FairTask.h"
// TMVA includes
#include "TMVA/MethodCuts.h"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"

class PndLmdNoiseTrkSuppressionTask : public FairTask {
 public:
  /** Default constructor **/
  PndLmdNoiseTrkSuppressionTask();

  /// Set up beam momuntum value
  PndLmdNoiseTrkSuppressionTask(Double_t pBeam, TString dir);

  /** Destructor **/
  ~PndLmdNoiseTrkSuppressionTask();

  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();
  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  //  virtual void Finish();

 private:
  TClonesArray* fTrkInArray;
  TClonesArray* fTrkOutArray;

  // PndGeoHandling* fGeoH;
  int fEventNr;
  Double_t fPbeam;

  // MVA Data -------
  TString fdir;
  TString fmethodName;
  Float_t axrec, ayrec;
  Float_t athrec, aphrec;
  TMVA::Reader* reader;

  ClassDef(PndLmdNoiseTrkSuppressionTask, 1);
};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"KoaBackProp", payloadCode, "@",
"KoaComp", payloadCode, "@",
"KoaEffi", payloadCode, "@",
"KoaGeaneTask", payloadCode, "@",
"KoaIPvis", payloadCode, "@",
"KoaLinFitTask", payloadCode, "@",
"KoaLinTrack", payloadCode, "@",
"KoaPloti", payloadCode, "@",
"KoaTrackFinderTask", payloadCode, "@",
"KoaTrksFilterTask", payloadCode, "@",
"LmdEffi", payloadCode, "@",
"MomentumVi", payloadCode, "@",
"PndLinTrack", payloadCode, "@",
"PndLmdGeaneTask", payloadCode, "@",
"PndLmdIdealFitTask", payloadCode, "@",
"PndLmdLinFitTask", payloadCode, "@",
"PndLmdLineTask", payloadCode, "@",
"PndLmdNoiseTrkSuppressionTask", payloadCode, "@",
"PndLmdSigCleanTask", payloadCode, "@",
"PndLmdTrackFinderCATask", payloadCode, "@",
"PndLmdTrackFinderTask", payloadCode, "@",
"PndLmdTrksFilterTask", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__LmdTrkDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__LmdTrkDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__LmdTrkDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__LmdTrkDict() {
  TriggerDictionaryInitialization_G__LmdTrkDict_Impl();
}
