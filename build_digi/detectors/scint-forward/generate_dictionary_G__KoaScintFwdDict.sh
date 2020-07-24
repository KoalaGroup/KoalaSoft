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

/home/yong/fairsoft/jun19/bin/rootcint -f /home/yong/src/KoalaSoft/build_digi/detectors/scint-forward/G__KoaScintFwdDict.cxx -rmf /home/yong/src/KoalaSoft/build_digi/lib/libKoaScintFwd.rootmap -rml KoaScintFwd.so  -inlineInputHeader -c   -I/home/yong/fairroot/v18_jun19/include -I/home/yong/src/KoalaSoft/detectors/scint-forward -I/home/yong/src/KoalaSoft/data -I/home/yong/src/KoalaSoft/tools -I/home/yong/fairsoft/jun19/include/root6 -I/home/yong/fairsoft/jun19/include KoaFwd.h KoaFwdContFact.h KoaFwdGeo.h KoaFwdGeoPar.h KoaFwdMisalignPar.h KoaFwdPoint.h KoaFwdDigi.h KoaFwdDigitization.h KoaFwdDigitizationPar.h ScintFwdLinkDef.h