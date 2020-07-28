# Directory for sensitive detector modules

# Shared classes for implementation of semiconductor detectors
 add_subdirectory(sds)

# Implementation of recoil detector
# Two versions of geometry available:
# 1) simple
# 2) full
add_subdirectory(recoil)

# Implementation of recoil and forward detector from KOALA group
add_subdirectory(scint-forward)

# Implementation of forward detector from LMD group
 add_subdirectory(lmdforward)
