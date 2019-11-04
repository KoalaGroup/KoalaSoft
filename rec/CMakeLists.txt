 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libKoaRec" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
#put here all directories where header files are located
${CMAKE_SOURCE_DIR}/KoaData
${CMAKE_SOURCE_DIR}/rec
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

Set(LINKDEF KoaRecLinkDef.h)
Set(LIBRARY_NAME KoaRec)
Set(DEPENDENCIES
    Base
    Geom
    KoaTools
)

GENERATE_LIBRARY()
