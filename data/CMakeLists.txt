# Create a library called "libKoaData" 

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/SdsData
${CMAKE_CURRENT_SOURCE_DIR}/TrackData
${CMAKE_CURRENT_SOURCE_DIR}/MCData
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

set(SRCS
MCData/KoaStack.cxx
MCData/KoaMCTrack.cxx
)

Set(HEADERS )
Set(LINKDEF DataLinkDef.h)
Set(LIBRARY_NAME KoaData)
Set(DEPENDENCIES Base EG Physics Core)

GENERATE_LIBRARY()

############################## create SdsData ##############
set(SRCS
  SdsData/PndSdsMCPoint.cxx
  SdsData/PndSdsDigi.cxx
  SdsData/PndSdsPixel.cxx
  SdsData/PndSdsDigiPixel.cxx
  SdsData/PndSdsCluster.cxx
  SdsData/PndSdsClusterPixel.cxx
  SdsData/PndSdsHit.cxx
  #SdsData/PndSdsHitInfo.cxx
  SdsData/PndSdsPidCand.cxx
  SdsData/PndSdsRadDamHit.cxx
  SdsData/PndSdsDigiPixelMCInfo.cxx
  TrackData/PndTrackCand.cxx
  TrackData/PndTrackCandHit.cxx
  TrackData/PndTrack.cxx
)

set(HEADERS
  SdsData/PndSdsMCPoint.h
  SdsData/PndSdsDigi.h
  SdsData/PndSdsPixel.h
  SdsData/PndSdsDigiPixel.h
  SdsData/PndSdsCluster.h
  SdsData/PndSdsClusterPixel.h
  SdsData/PndSdsHit.h
  #SdsData/PndSdsHitInfo.h
  SdsData/PndSdsPidCand.h
  SdsData/PndSdsRadDamHit.h
  SdsData/PndSdsDigiPixelMCInfo.h
  TrackData/PndTrackCand.h
  TrackData/PndTrackCandHit.h
  TrackData/PndTrack.h
)

set(LINKDEF SdsDataLinkDef.h)
set(LIBRARY_NAME SdsData)

set(DEPENDENCIES Base GeoBase TrkBase KoaData)

GENERATE_LIBRARY()
