#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikataArm" for configuration ""
set_property(TARGET MikataArm APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(MikataArm PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/MikataArm.so"
  IMPORTED_SONAME_NOCONFIG "MikataArm.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikataArm )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikataArm "${_IMPORT_PREFIX}/lib/MikataArm.so" )

# Import target "MikataArmComp" for configuration ""
set_property(TARGET MikataArmComp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(MikataArmComp PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/bin/MikataArmComp"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikataArmComp )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikataArmComp "${_IMPORT_PREFIX}/bin/MikataArmComp" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
