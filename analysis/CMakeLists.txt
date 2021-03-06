# Create a library called "libKoaAnalysis"

set(INCLUDE_DIRECTORIES
#put here all directories where header files are located
${BASE_INCLUDE_DIRECTORIES}
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_SOURCE_DIR}/data
${CMAKE_SOURCE_DIR}/data/MCData
${CMAKE_SOURCE_DIR}/detectors/recoil/simple
${CMAKE_SOURCE_DIR}/tools
${CMAKE_SOURCE_DIR}/daq/ems
${CMAKE_SOURCE_DIR}/detectors/scintforward
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
)

link_directories( ${LINK_DIRECTORIES})

set(SRCS
#Put here your sourcefiles
KoaAnaSolidAngle.cxx
KoaTransformToArray.cxx
KoaAnaTrigger.cxx
)

Set(LINKDEF AnalysisLinkDef.h)
Set(LIBRARY_NAME KoaAnalysis)

Set(DEPENDENCIES
    Base
    Geom
    KoaData
    KoaSimpleRec
    KoaTools
    KoaEmsDaq
    KoaScintFwd
)

GENERATE_LIBRARY()
