 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libKoaUnpack" which includes the source files given in
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
  KoaRunOnline.h
  KoaEmsConfig.h
  KoaEmsSource.h
  KoaEmsFileSource.h
  KoaEmsStreamSource.h
  KoaUnpack.h
  KoaScalorUnpack.h
  KoaTimeUnpack.h
  KoaMxdc32Unpack.h
  KoaEmsRawEvent.h
  KoaRawEvent.h
  # KoaBufferTemplate.h
  # KoaEventData.h
  # KoaEmsEventData.h
  # KoaMxdc32Data.h
  KoaRawEventAnalyzer.h
  #  KoaTestAnalyzer.h
  KoaEventAnalyzer.h
  KoaEmsEventAnalyzer.h
  KoaEventAssembler.h
  KoaRawEventTransform.h
  )

set(SRCS
#Put here your sourcefiles
KoaRunOnline.cxx
KoaEmsConfig.cxx
KoaEmsSource.cxx
KoaEmsFileSource.cxx
KoaEmsStreamSource.cxx
KoaScalorUnpack.cxx
KoaTimeUnpack.cxx
KoaMxdc32Unpack.cxx
#KoaTestAnalyzer.cxx
KoaEventAnalyzer.cxx
KoaEmsEventAnalyzer.cxx
KoaEventAssembler.cxx
KoaRawEventTransform.cxx
)

Set(LINKDEF EmsDaqLinkDef.h)

Set(LIBRARY_NAME KoaEmsDaq)

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
