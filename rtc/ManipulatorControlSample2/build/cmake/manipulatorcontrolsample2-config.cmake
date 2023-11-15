# ManipulatorControlSample2 CMake config file
#
# This file sets the following variables:
# ManipulatorControlSample2_FOUND - Always TRUE.
# ManipulatorControlSample2_INCLUDE_DIRS - Directories containing the ManipulatorControlSample2 include files.
# ManipulatorControlSample2_IDL_DIRS - Directories containing the ManipulatorControlSample2 IDL files.
# ManipulatorControlSample2_LIBRARIES - Libraries needed to use ManipulatorControlSample2.
# ManipulatorControlSample2_DEFINITIONS - Compiler flags for ManipulatorControlSample2.
# ManipulatorControlSample2_VERSION - The version of ManipulatorControlSample2 found.
# ManipulatorControlSample2_VERSION_MAJOR - The major version of ManipulatorControlSample2 found.
# ManipulatorControlSample2_VERSION_MINOR - The minor version of ManipulatorControlSample2 found.
# ManipulatorControlSample2_VERSION_REVISION - The revision version of ManipulatorControlSample2 found.
# ManipulatorControlSample2_VERSION_CANDIDATE - The candidate version of ManipulatorControlSample2 found.

message(STATUS "Found ManipulatorControlSample2-")
set(ManipulatorControlSample2_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(ManipulatorControlSample2_INCLUDE_DIRS
#    "/usr/local/include/manipulatorcontrolsample2-"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(ManipulatorControlSample2_IDL_DIRS
#    "/usr/local/include/manipulatorcontrolsample2-/idl")
set(ManipulatorControlSample2_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(ManipulatorControlSample2_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(ManipulatorControlSample2_LIBRARIES
        "/usr/local//libmanipulatorcontrolsample2.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(ManipulatorControlSample2_LIBRARIES
        "/usr/local//libmanipulatorcontrolsample2.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(ManipulatorControlSample2_DEFINITIONS ${<dependency>_DEFINITIONS})

set(ManipulatorControlSample2_VERSION )
set(ManipulatorControlSample2_VERSION_MAJOR )
set(ManipulatorControlSample2_VERSION_MINOR )
set(ManipulatorControlSample2_VERSION_REVISION )
set(ManipulatorControlSample2_VERSION_CANDIDATE )

