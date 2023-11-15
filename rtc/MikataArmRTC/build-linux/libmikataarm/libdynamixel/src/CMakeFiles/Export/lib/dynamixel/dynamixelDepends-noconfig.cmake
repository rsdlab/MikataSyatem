#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "dynamixel" for configuration ""
set_property(TARGET dynamixel APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(dynamixel PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libdynamixel.so"
  IMPORTED_SONAME_NOCONFIG "libdynamixel.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS dynamixel )
list(APPEND _IMPORT_CHECK_FILES_FOR_dynamixel "${_IMPORT_PREFIX}/lib/libdynamixel.so" )

# Import target "dynamixelStatic" for configuration ""
set_property(TARGET dynamixelStatic APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(dynamixelStatic PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libdynamixelStatic.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS dynamixelStatic )
list(APPEND _IMPORT_CHECK_FILES_FOR_dynamixelStatic "${_IMPORT_PREFIX}/lib/libdynamixelStatic.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
