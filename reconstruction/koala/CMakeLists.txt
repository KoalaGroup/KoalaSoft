 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libKoaRecon" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
#put here all directories where header files are located
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_SOURCE_DIR}/tools
${CMAKE_SOURCE_DIR}/data
${CMAKE_SOURCE_DIR}/detectors/recoil/simple
${CMAKE_SOURCE_DIR}/detectors/scint-forward
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
)

link_directories( ${LINK_DIRECTORIES})

set(HEADERS
  KoaRecNoiseFilter.h
  KoaRecEnergyRecon.h
  KoaRecTimeShiftCorrect.h
  KoaRecTimeWalkCorrect.h
  KoaRecRearRecon.h
  KoaFwdRecon.h
  KoaRecClusterCollect.h
  KoaRecClusterSeedFilter.h
  KoaRecClusterThresholdFilter.h
  )

set(SRCS
  KoaRecNoiseFilter.cxx
  KoaRecEnergyRecon.cxx
  KoaRecTimeShiftCorrect.cxx
  KoaRecTimeWalkCorrect.cxx
  KoaRecRearRecon.cxx
  KoaFwdRecon.cxx
  KoaRecClusterCollect.cxx
  KoaRecClusterSeedFilter.cxx
  KoaRecClusterThresholdFilter.cxx
)

Set(LINKDEF KoaReconLinkDef.h)

Set(LIBRARY_NAME KoaRecon)

Set(DEPENDENCIES
    Alignment
    Base
    Geom
    Core
    RHTTP
    KoaTools
    KoaSimpleRec
    KoaScintFwd
)

GENERATE_LIBRARY()
