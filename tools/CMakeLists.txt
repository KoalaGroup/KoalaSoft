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
)

include_directories(${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
)
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})
link_directories( ${LINK_DIRECTORIES})

set(SRCS
#Put here your sourcefiles
KoaGeoHandler.cxx
KoaMapHandler.cxx
KoaMapEncoder.cxx
KoaElasticCalculator.cxx
PndGeoHandling.cxx
PndSensorNamePar.cxx
PndSensorNameContFact.cxx
PndStringSeparator.cxx
)

Set(LINKDEF ToolsLinkDef.h)
Set(LIBRARY_NAME KoaTools)
Set(DEPENDENCIES
  Base
  Geom
  Core
  KoaData
  Physics
  Hist
  KoaData
)

GENERATE_LIBRARY()
