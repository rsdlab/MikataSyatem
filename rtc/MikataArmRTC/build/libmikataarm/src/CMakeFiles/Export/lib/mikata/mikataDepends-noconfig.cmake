#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "mikata" for configuration ""
set_property(TARGET mikata APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(mikata PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmikata.so"
  IMPORTED_SONAME_NOCONFIG "libmikata.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS mikata )
list(APPEND _IMPORT_CHECK_FILES_FOR_mikata "${_IMPORT_PREFIX}/lib/libmikata.so" )

# Import target "mikataStatic" for configuration ""
set_property(TARGET mikataStatic APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(mikataStatic PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmikataStatic.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS mikataStatic )
list(APPEND _IMPORT_CHECK_FILES_FOR_mikataStatic "${_IMPORT_PREFIX}/lib/libmikataStatic.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
