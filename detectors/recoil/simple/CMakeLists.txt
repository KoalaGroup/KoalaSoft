# Create a library called "libKoaSimpleRec"

set(INCLUDE_DIRECTORIES
#put here all directories where header files are located
${BASE_INCLUDE_DIRECTORIES}
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_SOURCE_DIR}/data
${CMAKE_SOURCE_DIR}/tools
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
KoaRec.cxx
KoaRecContFact.cxx
KoaRecGeo.cxx
KoaRecGeoPar.cxx
KoaRecMisalignPar.cxx
KoaRecPoint.cxx
KoaRecDigi.cxx
KoaRecDigitizationIdeal.cxx
KoaRecCluster.cxx
)

Set(LINKDEF SimpleRecLinkDef.h)
Set(LIBRARY_NAME KoaSimpleRec)
Set(DEPENDENCIES
    Base
    Geom
    KoaData
    KoaTools
)

GENERATE_LIBRARY()
