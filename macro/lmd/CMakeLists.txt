# Create a library called "" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${SIMPATH}/include
${ROOT_INCLUDE_DIR}
${GEANT3_INCLUDE_DIR}
${CLHEP_INCLUDE_DIR}
${BASE_INCLUDE_DIRECTORIES}  
${CMAKE_SOURCE_DIR}/data
${CMAKE_SOURCE_DIR}/data/TrackData
${CMAKE_SOURCE_DIR}/data/SdsData
#${CMAKE_SOURCE_DIR}/trackbase
${CMAKE_SOURCE_DIR}/passive
${CMAKE_SOURCE_DIR}/generators
#${CMAKE_SOURCE_DIR}/tools/buffers
#${CMAKE_SOURCE_DIR}/tracking/riemannfit
${CMAKE_SOURCE_DIR}/tools
${CMAKE_SOURCE_DIR}/detectors/sds/SdsMC
${CMAKE_SOURCE_DIR}/detectors/sds/SdsDigi
${CMAKE_SOURCE_DIR}/detectors/sds/SdsReco
${CMAKE_SOURCE_DIR}/detectors/sds/SdsTools
${CMAKE_SOURCE_DIR}/detectors/sds/SdsFEModel
${CMAKE_SOURCE_DIR}/detectors/sds
${CMAKE_SOURCE_DIR}/detectors/lmdforward/LmdMC
${CMAKE_SOURCE_DIR}/detectors/lmdforward/LmdDigi
${CMAKE_SOURCE_DIR}/detectors/lmdforward/LmdReco
${CMAKE_SOURCE_DIR}/detectors/lmdforward/LmdTrack
${CMAKE_SOURCE_DIR}/detectors/lmdforward/LmdTools
${CMAKE_SOURCE_DIR}/detectors/lmdforward
${CMAKE_SOURCE_DIR}/detectors/recoil/full
${CMAKE_SOURCE_DIR}/detectors/recoil/full/koaDigi
${CMAKE_SOURCE_DIR}/parameters
#${CMAKE_SOURCE_DIR}/genfit
#${CMAKE_SOURCE_DIR}/tracking/GenfitTools/trackrep
#${CMAKE_SOURCE_DIR}/tracking/GenfitTools/trackrep/GeaneTrackRep
#${CMAKE_SOURCE_DIR}/tracking/GenfitTools/trackrep/LSLtrackRep
#${CMAKE_SOURCE_DIR}/tracking/GenfitTools/trackrep/RKTrackRep

#${CMAKE_SOURCE_DIR}/geane
#${CMAKE_SOURCE_DIR}/tracking/GenfitTools/recohits
#${CMAKE_SOURCE_DIR}/tracking/GenfitTools/recotasks
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
${SIMPATH}/lib
${GLPK_LIB_DIR}
)

link_directories( ${LINK_DIRECTORIES})

################################## install #####################################

#add_executable(kdTreeExample runLumiPixel2fMatrixFinder.C)
#target_link_libraries(kdTreeExample LmdSensorAligner Core)

#add_executable(calc_cs Anastasia/tests/ModelUncert/CrossSecLim.C)
#target_link_libraries(calc_cs LmdFit)
#target_link_libraries(calc_cs $ENV{ROOT_LIBRARIES} MathMore LmdFit Model GL X11 GLU gsl gslcblas)
#add_executable(calc_cs_un Anastasia/tests/ModelUncert/DPM_ModelUncert.C)
#target_link_libraries(calc_cs_un $ENV{ROOT_LIBRARIES} MathMore LmdFit Model GL X11 GLU gsl gslcblas)
#add_executable(simple_mc_rec_match simpleMCandRECmatch.C)
#add_executable(createRootGeometry_lmd_HV_MAPS create_Lmd_HV_MAPS.C)	
#target_link_libraries(createRootGeometry_lmd_HV_MAPS -lrt ${ROOT_LIBRARIES} LmdTool  GeoBase ParBase Geom Sds Proof  PndData TrkBase VMC EG GeomPainter generalTools FairTools MathMore Base)
#add_executable(simple_mc_rec_match simpleMCandRECmatch.C)
#target_link_libraries(simple_mc_rec_match -lrt ${ROOT_LIBRARIES} LmdTool MathMore)
#add_subdirectory(LMD_alignment)
#add_subdirectory(Anastasia/test_macros)
#add_subdirectory(Promme)
