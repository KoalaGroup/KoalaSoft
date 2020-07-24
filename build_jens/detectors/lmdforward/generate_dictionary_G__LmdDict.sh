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

/home/yong/fairsoft/jun19/bin/rootcint -f /home/yong/src/KoalaSoft/build_jens/detectors/lmdforward/G__LmdDict.cxx -rmf /home/yong/src/KoalaSoft/build_jens/lib/libLmd.rootmap -rml Lmd.so  -inlineInputHeader -c   -I/home/yong/fairroot/v18_jun19/include -I/home/yong/src/KoalaSoft/detectors/lmdforward -I/home/yong/src/KoalaSoft/detectors/sds/SdsMC -I/home/yong/src/KoalaSoft/detectors/sds/SdsDigi -I/home/yong/src/KoalaSoft/detectors/sds/SdsReco -I/home/yong/src/KoalaSoft/detectors/sds/SdsTools -I/home/yong/src/KoalaSoft/detectors/sds/SdsFEModel -I/home/yong/src/KoalaSoft/detectors/sds -I/home/yong/src/KoalaSoft/data/SdsData -I/home/yong/src/KoalaSoft/data -I/home/yong/src/KoalaSoft/data/MCData -I/home/yong/src/KoalaSoft/data/TrackData -I/home/yong/src/KoalaSoft/detectors/lmdforward -I/home/yong/src/KoalaSoft/detectors/detectors/recoil/full/koaDigi -I/home/yong/src/KoalaSoft/tools -I/home/yong/src/KoalaSoft/detectors/lmdforward/LmdDigi -I/home/yong/src/KoalaSoft/detectors/lmdforward/LmdReco -I/home/yong/src/KoalaSoft/detectors/lmdforward/LmdTrack -I/home/yong/src/KoalaSoft/detectors/lmdforward/LmdTools -I/home/yong/fairsoft/jun19/include/root6 -I/home/yong/fairsoft/jun19/include -I/home/yong/fairsoft/jun19/include/TGeant3 -I/home/yong/fairroot/v18_jun19/include -I/home/yong/fairsoft/jun19/include LmdTools/PndLmdContFact.h LmdTools/PndLmdAlignPar.h LmdDigi/PndLmdPixelHitProducerFast.h LmdDigi/PndLmdHybridHitProducer.h ../recoil/full/koaDigi/KoaHybridHitProducer.h LmdDigi/PndLmdHitProducerIdeal.h PndLmdDetector.h PndLmdGeo.h PndLmdGeometryFactory.h PndLmdGeometryHelper.h geolumidetector.h ../recoil/full/geokoaladetector.h ../recoil/full/Koaladetector.h LmdLinkDef.h