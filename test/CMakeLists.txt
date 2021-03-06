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
${CMAKE_SOURCE_DIR}/test
${CMAKE_SOURCE_DIR}/tools
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
) 

link_directories( ${LINK_DIRECTORIES})

set(HEADERS
  KoaTest.h
  KoaDumy.h
  )

Set(LINKDEF TestLinkDef.h)

Set(LIBRARY_NAME KoaTest)

Set(DEPENDENCIES
    Base
    Geom
    Core
    KoaTools
)

GENERATE_LIBRARY()

add_executable(KoaTestApp KoaTest.cxx)
target_link_libraries(KoaTestApp KoaTest Boost::unit_test_framework)
target_include_directories(KoaTestApp PUBLIC ${INCLUDE_DIRECTORIES})

# Move testing binaries into a testBin directory
set_target_properties(
  KoaTestApp PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                      ${PROJECT_BINARY_DIR}/bin/test/)

add_test(
    NAME KoaTestApp
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/bin/test/
    COMMAND ${PROJECT_BINARY_DIR}/bin/test/KoaTestApp)
