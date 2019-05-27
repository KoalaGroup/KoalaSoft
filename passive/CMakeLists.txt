# Create a library called "libPassive" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${CMAKE_SOURCE_DIR}/passive
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
KoaMagnet.cxx         
KoaPassiveContFact.cxx
)

Set(HEADERS )
Set(LINKDEF PassiveLinkDef.h)
Set(LIBRARY_NAME KoaPassive)
Set(DEPENDENCIES Base GeoBase ParBase Geom Core)

GENERATE_LIBRARY()
