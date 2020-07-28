# Create a library called "libKoaScintFwd"

set(INCLUDE_DIRECTORIES
#put here all directories where header files are located
${BASE_INCLUDE_DIRECTORIES}
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_SOURCE_DIR}/data
${CMAKE_SOURCE_DIR}/tools
${CMAKE_SOURCE_DIR}/data/MCData
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
KoaFwd.cxx
KoaFwdContFact.cxx
KoaFwdGeo.cxx
KoaFwdGeoPar.cxx
KoaFwdMisalignPar.cxx
KoaFwdPoint.cxx
KoaFwdDigi.cxx
KoaFwdDigitization.cxx
KoaFwdDigitizationPar.cxx
)

Set(LINKDEF ScintFwdLinkDef.h)
Set(LIBRARY_NAME KoaScintFwd)
Set(DEPENDENCIES
    Base
    Geom
    KoaData
    KoaTools
)

GENERATE_LIBRARY()
