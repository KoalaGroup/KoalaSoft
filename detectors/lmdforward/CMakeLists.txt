# Create a library called "libKoaTools"
Set(SYSTEM_INCLUDE_DIRECTORIES
  ${SYSTEM_INCLUDE_DIRECTORIES}
  ${GEANT3_INCLUDE_DIR}
  ${CLHEP_INCLUDE_DIR}
  ${BASE_INCLUDE_DIRECTORIES} 
  ${Boost_INCLUDE_DIR}
)
message("GEANT 3 INCLUDE DIRECTORY: ${GEANT3_INCLUDE_DIR}")


set(INCLUDE_DIRECTORIES
#put here all directories where header files are located
${BASE_INCLUDE_DIRECTORIES}
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_SOURCE_DIR}/detectors/sds/SdsMC
${CMAKE_SOURCE_DIR}/detectors/sds/SdsDigi
${CMAKE_SOURCE_DIR}/detectors/sds/SdsReco
${CMAKE_SOURCE_DIR}/detectors/sds/SdsTools
${CMAKE_SOURCE_DIR}/detectors/sds/SdsFEModel
${CMAKE_SOURCE_DIR}/detectors/sds
${CMAKE_SOURCE_DIR}/data/SdsData
${CMAKE_SOURCE_DIR}/data
${CMAKE_SOURCE_DIR}/data/MCData
${CMAKE_SOURCE_DIR}/data/TrackData
${CMAKE_SOURCE_DIR}/detectors/lmdforward
${CMAKE_SOURCE_DIR}/detectors/detectors/recoil/full/koaDigi
${CMAKE_SOURCE_DIR}/tools
# ${CMAKE_SOURCE_DIR}/detectors/lmd/LmdMC
${CMAKE_CURRENT_SOURCE_DIR}/LmdDigi
${CMAKE_CURRENT_SOURCE_DIR}/LmdReco
${CMAKE_CURRENT_SOURCE_DIR}/LmdTrack
${CMAKE_CURRENT_SOURCE_DIR}/LmdTools
# # ${CMAKE_SOURCE_DIR}/LmdQA
# ${CMAKE_SOURCE_DIR}/analysis
# ${CMAKE_SOURCE_DIR}/data
# ${CMAKE_SOURCE_DIR}/detectors/recoil/simple
# ${CMAKE_SOURCE_DIR}/detectors/recoil/full
# ${CMAKE_SOURCE_DIR}/detectors/recoil/full/koaDigi
# ${CMAKE_SOURCE_DIR}/detectors/lmdforward
# ${CMAKE_SOURCE_DIR}/tools
# ${CMAKE_SOURCE_DIR}/detectors/sds/SdsDigi
# ${CMAKE_SOURCE_DIR}/detectors/passive
# ${CMAKE_SOURCE_DIR}/tools
# ${CMAKE_SOURCE_DIR}/tracking/riemannfit
# ${CMAKE_SOURCE_DIR}/geane
# ${CMAKE_SOURCE_DIR}/detectors/passive
)

include_directories(${INCLUDE_DIRECTORIES}
)

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
)
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})
link_directories( ${LINK_DIRECTORIES})

########################### create libLmd #####################################\
#
set(SRCS

LmdTools/PndLmdContFact.cxx
LmdTools/PndLmdAlignPar.cxx
LmdDigi/PndLmdPixelHitProducerFast.cxx
LmdDigi/PndLmdHybridHitProducer.cxx
../recoil/full/koaDigi/KoaHybridHitProducer.cxx
LmdDigi/PndLmdHitProducerIdeal.cxx
PndLmdDetector.cxx
PndLmdGeo.cxx
PndLmdGeometryFactory.cxx
PndLmdGeometryHelper.cxx
geolumidetector.cxx
../recoil/full/geokoaladetector.cxx
../recoil/full/Koaladetector.cxx
)
set(LINKDEF  LmdLinkDef.h)
set(LIBRARY_NAME Lmd)

set(DEPENDENCIES Base ParBase GeoBase TrkBase KoaData Sds) # It is not derived from SDS!

GENERATE_LIBRARY()

########################### create libLmdReco #################################\
#
set(SRCS


LmdReco/PndLmdPixelClusterTask.cxx
LmdReco/KoaPixelClusterTask.cxx
LmdReco/PndLmdHitMergeTask.cxx
LmdReco/KoaHitMergeTask.cxx
LmdReco/PndLmdSimplePixelClusterFinder.cxx
LmdReco/KoaSimplePixelClusterFinder.cxx
LmdReco/PndLmdChargeWeightedPixelMapping.cxx
LmdReco/KoaChargeWeightedPixelMapping.cxx
LmdReco/PndSdsMergedHit.cxx
LmdReco/PndSdsCell.cxx
)
  set(LINKDEF  LmdRecoLinkDef.h)
set(LIBRARY_NAME LmdReco)

set(DEPENDENCIES SdsReco Lmd)

GENERATE_LIBRARY()




########################### create libLmdTrk #################################

set(SRCS

LmdTrack/PndLmdTrackFinderTask.cxx
LmdTrack/KoaTrackFinderTask.cxx
LmdTrack/PndLmdTrackFinderCATask.cxx
LmdTrack/PndLmdLinFitTask.cxx
LmdTrack/KoaLinFitTask.cxx
LmdTrack/PndLmdLineTask.cxx
LmdTrack/PndLmdIdealFitTask.cxx
LmdTrack/PndLinTrack.cxx
LmdTrack/KoaLinTrack.cxx
LmdTrack/PndLmdGeaneTask.cxx
LmdTrack/KoaGeaneTask.cxx
LmdTrack/KoaBackProp.cxx
LmdTrack/KoaComp.cxx
LmdTrack/KoaPloti.cxx
LmdTrack/KoaEffi.cxx
LmdTrack/MomentumVi.cxx
LmdTrack/LmdEffi.cxx
LmdTrack/KoaIPvis.cxx
LmdTrack/PndLmdTrksFilterTask.cxx
LmdTrack/KoaTrksFilterTask.cxx
LmdTrack/PndLmdSigCleanTask.cxx
LmdTrack/PndLmdNoiseTrkSuppressionTask.cxx
)
set(LINKDEF  LmdTrkLinkDef.h)
set(LIBRARY_NAME LmdTrk)

set(DEPENDENCIES TrkBase Geane LmdReco TMVA)

GENERATE_LIBRARY()

########################### create libLmdTools ###############################
#set(SRCS

#LmdQA/PndLmdTrackQ.cxx
#LmdQA/PndLmdTrkQTask.cxx
#LmdQA/PndLmdDigiQ.cxx
#LmdQA/PndLmdDigiQTask.cxx
#LmdQA/PndLmdQATask.cxx
#)

#set(LINKDEF  LmdToolLinkDef.h)
#set(LIBRARY_NAME LmdTool)

#set(DEPENDENCIES Sds LmdTrk)

#GENERATE_LIBRARY()
