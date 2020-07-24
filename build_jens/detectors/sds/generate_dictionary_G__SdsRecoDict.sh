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

/home/yong/fairsoft/jun19/bin/rootcint -f /home/yong/src/KoalaSoft/build_jens/detectors/sds/G__SdsRecoDict.cxx -rmf /home/yong/src/KoalaSoft/build_jens/lib/libSdsReco.rootmap -rml SdsReco.so  -inlineInputHeader -c   -I/home/yong/src/KoalaSoft/detectors/sds -I/home/yong/src/KoalaSoft/detectors/sds/ -I/home/yong/src/KoalaSoft/detectors/lmdforward/ -I/home/yong/src/KoalaSoft/detectors/lmdforward/LmdDigi -I/home/yong/src/KoalaSoft/data/ -I/home/yong/src/KoalaSoft/data/MCData -I/home/yong/src/KoalaSoft/data/SdsData -I/home/yong/src/KoalaSoft/tools -I/home/yong/src/KoalaSoft/detectors/sds/SdsMC -I/home/yong/src/KoalaSoft/detectors/sds/SdsTools -I/home/yong/src/KoalaSoft/detectors/sds/SdsDigi -I/home/yong/src/KoalaSoft/detectors/sds/SdsFEModel -I/home/yong/src/KoalaSoft/detectors/sds/SdsReco -I/home/yong/fairsoft/jun19/include/root6 -I/home/yong/fairsoft/jun19/include -I/home/yong/fairsoft/jun19/include/TGeant3 -I/home/yong/fairroot/v18_jun19/include SdsReco/PndSdsPixelClusterFinder.h SdsReco/PndSdsSimplePixelClusterFinder.h SdsReco/PndSdsIdealPixelClusterFinder.h SdsReco/PndSdsPixelClusterTask.h SdsReco/PndSdsIdealClusterTask.h SdsReco/PndSdsPixelBackMapping.h SdsReco/PndSdsChargeWeightedPixelMapping.h SdsReco/PndSdsIdealRecoTask.h SdsReco/PndSdsTimeWalkCorr.h SdsReco/PndSdsTimeWalkCorrSimple.h SdsReco/PndSdsTimeWalkCorrTask.h SdsRecoLinkDef.h
