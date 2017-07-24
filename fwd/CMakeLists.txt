 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libKoaFwd" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
#put here all directories where header files are located
${CMAKE_SOURCE_DIR}/KoaData
${CMAKE_SOURCE_DIR}/fwd

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
KoaFwdPoint.cxx
)

Set(LINKDEF KoaFwdLinkDef.h)
Set(LIBRARY_NAME KoaFwd)
Set(DEPENDENCIES
    Base
)

GENERATE_LIBRARY()
