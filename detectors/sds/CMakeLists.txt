# Create a library called "" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

Set(SYSTEM_INCLUDE_DIRECTORIES
  ${SYSTEM_INCLUDE_DIRECTORIES}
  ${GEANT3_INCLUDE_DIR}
  ${CLHEP_INCLUDE_DIR}
  ${BASE_INCLUDE_DIRECTORIES} 
)

Set(INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/detectors/sds/
  ${CMAKE_SOURCE_DIR}/detectors/lmdforward/
  ${CMAKE_SOURCE_DIR}/detectors/lmdforward/LmdDigi
  ${CMAKE_SOURCE_DIR}/data/
  ${CMAKE_SOURCE_DIR}/data/MCData
  ${CMAKE_SOURCE_DIR}/data/SdsData
  ${CMAKE_SOURCE_DIR}/tools
  ${CMAKE_CURRENT_SOURCE_DIR}/SdsMC
  ${CMAKE_CURRENT_SOURCE_DIR}/SdsTools
  ${CMAKE_CURRENT_SOURCE_DIR}/SdsDigi
  ${CMAKE_CURRENT_SOURCE_DIR}/SdsFEModel
  ${CMAKE_CURRENT_SOURCE_DIR}/SdsReco
)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
)

link_directories( ${LINK_DIRECTORIES})


########################### create libSds ######################################
set(SRCS

PndSdsTask.cxx
PndPersistencyTask.cxx

SdsDigi/PndSdsCalcFePixel.cxx
SdsDigi/PndSdsCalcPixel.cxx
SdsDigi/PndSdsCalcPixelDif.cxx
#SdsDigi/PndSdsCalcStripDif.cxx
#MvdDigi/PndMvdDigiAna.cxx
SdsDigi/PndSdsHybridHitProducer.cxx
#SdsDigi/PndSdsStripHitProducerDif.cxx
SdsDigi/PndSdsHitProducerIdeal.cxx
#MvdDigi/PndMvdDigiTask.cxx
SdsDigi/PndSdsNoiseProducer.cxx

SdsDigi/PndSdsChargeConversion.cxx
SdsDigi/PndSdsIdealChargeConversion.cxx
SdsDigi/PndSdsTotChargeConversion.cxx
SdsDigi/PndSdsAdcChargeConversion.cxx
SdsDigi/PndSdsDigiPixelWriteoutBuffer.cxx

SdsDigi/PndSdsDigiPixelSorterTask.cxx
SdsDigi/PndSdsDigiPixelRingSorter.cxx


SdsFEModel/PndSdsFE.cxx
SdsFEModel/PndSdsFESimple.cxx
SdsFEModel/PndSdsFEAmpModelSimple.cxx
SdsFEModel/PndSdsFESimple.cxx

SdsMC/PndSdsDetector.cxx
SdsMC/PndSdsGeo.cxx
SdsMC/PndSdsGeoPar.cxx
#SdsMC/PndSdsMaterialDet.cxx

#SdsTools/PndSdsContFact.cxx
SdsTools/PndSdsPixelDigiPar.cxx
SdsTools/PndSdsTotDigiPar.cxx
#SdsTools/PndStringSeparator.cxx
)
set(LINKDEF  SdsLinkDef.h)
set(LIBRARY_NAME Sds)

set(DEPENDENCIES Base GeoBase ParBase KoaData  SdsData KoaTools)

GENERATE_LIBRARY()
 

########################### create libSdsReco ##################################
set(SRCS

#SdsReco/PndSdsRecoTask.cxx
#SdsReco/PndSdsClusterTask.cxx
SdsReco/PndSdsPixelClusterFinder.cxx
SdsReco/PndSdsSimplePixelClusterFinder.cxx
SdsReco/PndSdsIdealPixelClusterFinder.cxx
SdsReco/PndSdsPixelClusterTask.cxx
SdsReco/PndSdsIdealClusterTask.cxx
SdsReco/PndSdsPixelBackMapping.cxx
SdsReco/PndSdsChargeWeightedPixelMapping.cxx
SdsReco/PndSdsIdealRecoTask.cxx
SdsReco/PndSdsTimeWalkCorr.cxx
SdsReco/PndSdsTimeWalkCorrSimple.cxx
SdsReco/PndSdsTimeWalkCorrTask.cxx

)

set(LINKDEF  SdsRecoLinkDef.h)
set(LIBRARY_NAME SdsReco)

set(DEPENDENCIES Base GeoBase ParBase Sds)

GENERATE_LIBRARY()
