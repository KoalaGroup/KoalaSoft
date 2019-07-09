# The name of our project is “KOALA”.  CMakeLists files in this project can
# refer to the root source directory of the project as ${KOALA_SOURCE_DIR}
# or as ${CMAKE_SOURCE_DIR} and to the root binary directory of the project as
# ${KOALA_BINARY_DIR} or ${CMAKE_BINARY_DIR}.
# This difference is important for the base classes which are in FAIRROOT 
# and the experiment part.

# Check if cmake has the required version
CMAKE_MINIMUM_REQUIRED(VERSION 3.11.0 FATAL_ERROR)

#######################################################
# Version number of KoalaSoft
set(KOALA_MAJOR_VERSION 0)
set(KOALA_MINOR_VERSION 1)
set(KOALA_PATCH_VERSION 0)

# Set name of our project to KOALASOFT. Has to be done
# after check of cmake version since this is a new feature
project(KOALA VERSION ${KOALA_MAJOR_VERSION}.${KOALA_MINOR_VERSION}.${KOALA_PATCH_VERSION})

#######################################################
# Check for needed environment variables
# FairSoft and FairRoot should be installed first and the environment variable of FAIRROOTPATH an SIMPATH should be defied
IF(NOT DEFINED ENV{FAIRROOTPATH})
  MESSAGE(FATAL_ERROR "You did not define the environment variable FAIRROOTPATH which is needed to find FairRoot. Please set this variable and execute cmake again.")
ENDIF(NOT DEFINED ENV{FAIRROOTPATH})

IF(NOT DEFINED ENV{SIMPATH})
   MESSAGE(FATAL_ERROR "You did not define the environment variable SIMPATH which is nedded to find the external packages. Please set this variable and execute cmake again.") 
ENDIF(NOT DEFINED ENV{SIMPATH})

SET(SIMPATH $ENV{SIMPATH})
SET(FAIRROOTPATH $ENV{FAIRROOTPATH})

#######################################################
# Set up the directories for include and find_package command

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
# module files under these directories are provided by FairRoot
set(CMAKE_MODULE_PATH "${FAIRROOTPATH}/share/fairbase/cmake/modules"  ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${FAIRROOTPATH}/share/fairbase/cmake/modules_old"  ${CMAKE_MODULE_PATH})

# module files under these directories are provided by KoalaSoft
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

if(SIMPATH)
  set(CMAKE_PREFIX_PATH ${SIMPATH} ${CMAKE_PREFIX_PATH})
endif()

#######################################################
# check c++11 support of compiler
Set(CheckSrcDir "${FAIRROOTPATH}/share/fairbase/cmake/checks")
include(CheckCXX11Features)
include(CheckSymbolExists)

If(NOT _HAS_CXX11_FLAG)
  Message(FATAL_ERROR "The used C++ compiler (${CMAKE_CXX_COMPILER}) does not support C++11. CbmRoot can only be compiled with compilers supporting C++11. Please install such a compiler.")
EndIf()

#######################################################
# set cmake policies
include(FairRootCmakePolicies)
set_fairroot_cmake_policies()

# Load some basic macros which are needed later on
include(FairMacros)
include(WriteConfigFile)
include(CTest)
include(CheckCompiler)

#######################################################
#Check the compiler and set the compile and link flags
If(NOT CMAKE_BUILD_TYPE)
  Message("Set BuildType DEBUG")
  set(CMAKE_BUILD_TYPE Debug)
EndIf(NOT CMAKE_BUILD_TYPE)

Check_Compiler()


#######################################################
# the default directory where the built library, executables and headers
# will be located. The target specific properties may overwrite this dire-
# -ctory
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(INCLUDE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/include")

#######################################################
# the default working directory of KoalaSoft
Set(VMCWORKDIR ${CMAKE_SOURCE_DIR})

#######################################################
# [TODO] ???
Option(USE_PATH_INFO "Information from PATH and LD_LIBRARY_PATH are
used." OFF)
If(USE_PATH_INFO)
  Set(PATH "$PATH")
  If (APPLE)
    Set(LD_LIBRARY_PATH $ENV{DYLD_LIBRARY_PATH})
  Else (APPLE)
    Set(LD_LIBRARY_PATH $ENV{LD_LIBRARY_PATH})
  EndIf (APPLE)
Else(USE_PATH_INFO)
  STRING(REGEX MATCHALL "[^:]+" PATH $ENV{PATH})
EndIf(USE_PATH_INFO)

#######################################################
# Check if the user wants to build the project in the source
# directory
CHECK_OUT_OF_SOURCE_BUILD()

# Check if we are on an UNIX system. If not stop with an error
# message
IF(NOT UNIX)
  MESSAGE(FATAL_ERROR "You're not on an UNIX system. The project was up to now only tested on UNIX systems, so we break here. If you want to go on please edit the CMakeLists.txt in the source directory.")
ENDIF(NOT UNIX)  

# Check if the external packages are installed into a separate install
# directory, i.e whether FairSoft is installed or not
CHECK_EXTERNAL_PACKAGE_INSTALL_DIR()

#######################################################
# find all the external packages needed

# find FairRoot
find_package(FairRoot)

# searches for needed packages
# REQUIRED means that cmake will stop if this packages are not found
# For example the framework can run without GEANT4, but ROOT is
# mandatory
<<<<<<< 718b91259252a0756b263de1f8eabf448a51096a
# some packages' cmake configuration file (the module method of find_package) are provided by FairRoot such as: ROOT, Pythia6/8, HEPMC
# others are provided through the config method of find_package by FairSoft such as: FairLogger, Geant3, Geant4, VGM, Geant4MC
find_package2(PUBLIC ROOT 6.10.00 REQUIRED)
find_package2(PUBLIC Pythia6 REQUIRED)
find_package2(PUBLIC Pythia8)
find_package2(PUBLIC GEANT3)
find_package2(PUBLIC GEANT4)
find_package2(PUBLIC GEANT4DATA)
find_package2(PUBLIC GEANT4VMC)
Find_Package2(PUBLIC VGM)
#find_package(CLHEP)
find_package2(PUBLIC HEPMC)
find_package2(PUBLIC FairMQ VERSION 1.2.3)

# find boost
If(FAIRSOFT_EXTERN)
  set(BOOST_ROOT ${SIMPATH})
  set(GSL_DIR ${SIMPATH})
Else(FAIRSOFT_EXTERN)
  set(BOOST_ROOT ${SIMPATH}/basics/boost)
  set(GSL_DIR ${SIMPATH}/basics/gsl)
EndIf(FAIRSOFT_EXTERN)

if(NOT DEFINED Boost_NO_SYSTEM_PATHS)
  Set(Boost_NO_SYSTEM_PATHS TRUE)
endif()
Set(Boost_NO_BOOST_CMAKE TRUE)

Unset(Boost_INCLUDE_DIR CACHE)
Unset(Boost_LIBRARY_DIRS CACHE)

find_package2(PUBLIC Boost
  VERSION 1.67 ${FairMQ_Boost_VERSION}
  COMPONENTS thread system timer program_options random filesystem chrono exception regex serialization log log_setup atomic date_time signals ${FairMQ_Boost_COMPONENTS}
)

If (Boost_FOUND)
  Set(Boost_Avail 1)
Else (Boost_FOUND)
  Set(Boost_Avail 0)
EndIf (Boost_FOUND)

#######################################################
# set some variables which should be used in all CMakeLists.txt
# BASE_INCLUDE_DIRECTORIES: FairRoot
# SYSTEM_INCLUDE_DIRECTORIES: ROOT, Boost
# ROOT_INCLUDE_PATH: FairRoot

# LD_LIBRARY_PATH: Add FairRoot Library path
# BASE_LINK_DIRECTORIES: ROOT, Boost
# most external libs are installed under $SIMPATH/lib except ROOT
SetBasicVariables()

#######################################################
# [TODO] what's FAIRROOT_LIBRARY_PROPERTIES uesd for
# Set the library version in the main CMakeLists.txt
SET(FAIRROOT_MAJOR_VERSION 0)
SET(FAIRROOT_MINOR_VERSION 0)
SET(FAIRROOT_PATCH_VERSION 0)
SET(FAIRROOT_VERSION "${FAIRROOT_MAJOR_VERSION}.${FAIRROOT_MINOR_VERSION}.${FAIRROOT_PATCH_VERSION}")

If(ROOT_FOUND_VERSION LESS 59999)
  SET(FAIRROOT_LIBRARY_PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES}
      VERSION "${FAIRROOT_VERSION}"
      SOVERSION "${FAIRROOT_MAJOR_VERSION}"
      SUFFIX ".so"
  )
Else()
  SET(FAIRROOT_LIBRARY_PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES}
      VERSION "${FAIRROOT_VERSION}"
      SOVERSION "${FAIRROOT_MAJOR_VERSION}"
  )
EndIf()

configure_file(${CMAKE_SOURCE_DIR}/cmake/scripts/FairRootConfigVersion.cmake.in "${CMAKE_BINARY_DIR}/FairRootConfigVersion.cmake" @ONLY)

Generate_Version_Info()

#######################################################
SET(_LIBDIR ${CMAKE_BINARY_DIR}/lib)
SET(LD_LIBRARY_PATH  ${_LIBDIR} ${LD_LIBRARY_PATH})

#######################################################
# Check if the compiler support specific C++11 features
# Up to now this is only a check since the code does not use
# any of the features of the new standard
include(CheckCXX11Features)

IF(HAS_CXX11_SHAREDPOINTER)
  Add_Definitions(-DHAS_SHAREDPOINTER)
ENDIF(HAS_CXX11_SHAREDPOINTER)

#######################################################
# Recurse into the given subdirectories.  This does not actually
# cause another cmake executable to run.  The same process will walk through
# the project's entire directory structure.

add_subdirectory (KoaData)
add_subdirectory (KoaGenerators)
add_subdirectory (rec)
add_subdirectory (fwd)
add_subdirectory (passive)
add_subdirectory (field)  
add_subdirectory (tools)  
add_subdirectory (analysis)  
add_subdirectory (MQ)  

#######################################################
WRITE_CONFIG_FILE(config.sh)
 
configure_file(${CMAKE_SOURCE_DIR}/CTestCustom.cmake 
               ${CMAKE_BINARY_DIR}/CTestCustom.cmake
              )

#######################################################
# Summary 
if(CMAKE_CXX_FLAGS)
  message(STATUS "  ")
  message(STATUS "  ${Cyan}GLOBAL CXX FLAGS${CR}  ${BGreen}${CMAKE_CXX_FLAGS}${CR}")
endif()
if(CMAKE_CONFIGURATION_TYPES)
  message(STATUS "  ")
  message(STATUS "  ${Cyan}BUILD TYPE         CXX FLAGS${CR}")
  string(TOUPPER "${CMAKE_BUILD_TYPE}" selected_type)
  foreach(type IN LISTS CMAKE_CONFIGURATION_TYPES)
   string(TOUPPER "${type}" type_upper)
   if(type_upper STREQUAL selected_type)
     pad("${type}" 18 " " type_padded)
     message(STATUS "${BGreen}* ${type_padded}${CMAKE_CXX_FLAGS_${type_upper}}${CR}")
   else()
     pad("${type}" 18 " " type_padded)
     message(STATUS "  ${BWhite}${type_padded}${CR}${CMAKE_CXX_FLAGS_${type_upper}}")
   endif()
   unset(type_padded)
   unset(type_upper)
 endforeach()
message(STATUS "  ")
message(STATUS "  (Change the build type with ${BMagenta}-DCMAKE_BUILD_TYPE=...${CR})")
endif()

