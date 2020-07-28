# Create a library called "libKoaGenerator"
set(INCLUDE_DIRECTORIES
${PYTHIA8_INCLUDE_DIR}
${SIMPATH}/include
${BASE_INCLUDE_DIRECTORIES}
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_SOURCE_DIR}/data
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
${SIMPATH}/lib
)

link_directories( ${LINK_DIRECTORIES})

set(SRCS
Pythia6Generator.cxx
Pythia8Generator.cxx
KoaPpelasticGenerator.cxx
FairFilteredPrimaryGenerator.cxx
FairEvtFilter.cxx
FairEvtFilterParams.cxx
KoaEvtFilterOnGeometry.cxx
KoaPPElasticIdealGenerator.cxx
)

set(LINKDEF  GeneratorLinkDef.h)
set(LIBRARY_NAME KoaGenerator)

set(DEPENDENCIES
  Base
  pythia8
  Pythia6
  KoaData
  )

GENERATE_LIBRARY()
