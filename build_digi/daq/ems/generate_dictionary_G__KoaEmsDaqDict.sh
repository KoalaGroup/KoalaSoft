#!/bin/bash

# This macro is used to generate the ROOT dictionaries
# To use the ctest launchers one needs some environment variables which
# are only present when running CMake. To have the same environment at
# the time the dictionary is build this script is used which is build
# at the time cmake runs.

# Setup the needed environment
export LD_LIBRARY_PATH=/home/yong/fairsoft/jun19/lib/root::/home/yong/src/nat_framework/NAT/install/lib:/home/yong/src/nat_framework/NAT/install/lib/Xt:/home/yong/src/nat_framework/NAT/install/lib/EES:/home/yong/src/nat_framework/NAT/install/lib/CTP:/home/yong/src/KoalaSoft/build/lib:/home/yong/fairroot/v18_jun19/lib:/home/yong/fairsoft/jun19/lib/root:/home/yong/fairsoft/jun19/lib/Geant3-2.7.0/lib:/home/yong/fairsoft/jun19/lib
export DYLD_LIBRARY_PATH=/home/yong/fairsoft/jun19/lib/root::/home/yong/src/nat_framework/NAT/install/lib:/home/yong/src/nat_framework/NAT/install/lib/Xt:/home/yong/src/nat_framework/NAT/install/lib/EES:/home/yong/src/nat_framework/NAT/install/lib/CTP:/home/yong/src/KoalaSoft/build/lib:/home/yong/fairroot/v18_jun19/lib:/home/yong/fairsoft/jun19/lib/root:/home/yong/fairsoft/jun19/lib/Geant3-2.7.0/lib:/home/yong/fairsoft/jun19/lib
export ROOTSYS=/home/yong/fairsoft/jun19

/home/yong/fairsoft/jun19/bin/rootcint -f /home/yong/src/KoalaSoft/build_digi/daq/ems/G__KoaEmsDaqDict.cxx -rmf /home/yong/src/KoalaSoft/build_digi/lib/libKoaEmsDaq.rootmap -rml KoaEmsDaq.so  -inlineInputHeader -c   -I/home/yong/fairroot/v18_jun19/include -I/home/yong/src/KoalaSoft/daq/ems -I/home/yong/src/KoalaSoft/tools -I/home/yong/src/KoalaSoft/data -I/home/yong/src/KoalaSoft/detectors/recoil/simple -I/home/yong/src/KoalaSoft/detectors/scint-forward -I/home/yong/fairsoft/jun19/include/root6 -I/home/yong/fairsoft/jun19/include KoaRunOnline.h KoaEmsConfig.h KoaEmsSource.h KoaEmsFileSource.h KoaEmsStreamSource.h KoaUnpack.h KoaScalorUnpack.h KoaTimeUnpack.h KoaMxdc32Unpack.h KoaEmsRawEvent.h KoaRawEvent.h KoaRawEventAnalyzer.h KoaEventAnalyzer.h KoaEmsEventAnalyzer.h KoaEventAssembler.h KoaEventLgtAsm.h KoaRawEventTransform.h EmsDaqLinkDef.h
