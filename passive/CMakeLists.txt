# Create a library called "libKoaPassive"

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
)

link_directories( ${LINK_DIRECTORIES})

set(SRCS
KoaCave.cxx
KoaPipe.cxx
KoaGeoCave.cxx
KoaPassiveContFact.cxx
)

Set(HEADERS )
Set(LINKDEF PassiveLinkDef.h)
Set(LIBRARY_NAME KoaPassive)
Set(DEPENDENCIES Base GeoBase ParBase Geom Core)

GENERATE_LIBRARY()
