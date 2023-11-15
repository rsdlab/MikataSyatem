# MikataArm CMake config file
#
# This file sets the following variables:
# MikataArm_FOUND - Always TRUE.
# MikataArm_INCLUDE_DIRS - Directories containing the MikataArm include files.
# MikataArm_IDL_DIRS - Directories containing the MikataArm IDL files.
# MikataArm_LIBRARIES - Libraries needed to use MikataArm.
# MikataArm_DEFINITIONS - Compiler flags for MikataArm.
# MikataArm_VERSION - The version of MikataArm found.
# MikataArm_VERSION_MAJOR - The major version of MikataArm found.
# MikataArm_VERSION_MINOR - The minor version of MikataArm found.
# MikataArm_VERSION_REVISION - The revision version of MikataArm found.
# MikataArm_VERSION_CANDIDATE - The candidate version of MikataArm found.

message(STATUS "Found MikataArm-")
set(MikataArm_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(MikataArm_INCLUDE_DIRS
#    "/usr/local/include/mikataarm-"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(MikataArm_IDL_DIRS
#    "/usr/local/include/mikataarm-/idl")
set(MikataArm_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(MikataArm_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(MikataArm_LIBRARIES
        "/usr/local//libmikataarm.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(MikataArm_LIBRARIES
        "/usr/local//libmikataarm.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(MikataArm_DEFINITIONS ${<dependency>_DEFINITIONS})

set(MikataArm_VERSION )
set(MikataArm_VERSION_MAJOR )
set(MikataArm_VERSION_MINOR )
set(MikataArm_VERSION_REVISION )
set(MikataArm_VERSION_CANDIDATE )

