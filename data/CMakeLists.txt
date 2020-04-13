# Create a library called "libKoaData" 

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

set(SRCS
KoaStack.cxx
KoaMCTrack.cxx
)

Set(HEADERS )
Set(LINKDEF DataLinkDef.h)
Set(LIBRARY_NAME KoaData)
Set(DEPENDENCIES Base EG Physics Core)

GENERATE_LIBRARY()

