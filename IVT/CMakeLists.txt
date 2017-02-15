project(IVT)
cmake_minimum_required(VERSION 2.6)

##########################################################
# version information
##########################################################
set(IVT_MAJOR_VERSION 1)
set(IVT_MINOR_VERSION 4)
set(IVT_PATCH_VERSION 1)

set(IVT_VERSION
    ${IVT_MAJOR_VERSION}.${IVT_MINOR_VERSION}.${IVT_PATCH_VERSION})

##########################################################
# setup project wide directories
##########################################################
set(BINARY_DIR bin)
set(LIBRARY_DIR lib)
set(INCLUDE_DIR src)
set(CMAKE_DIR cmake)
set(CONFIG_DIR config)
set(DATA_DIR files)

set(IVT_BASE_DIR "${PROJECT_SOURCE_DIR}")
set(IVT_BUILD_DIRECTORY "${CMAKE_BINARY_DIR}" CACHE STRING "IVT build directory")

set(IVT_LIBRARY_DIR "${IVT_BUILD_DIRECTORY}/${LIBRARY_DIR}")
set(IVT_BINARY_DIR "${IVT_BUILD_DIRECTORY}/${BINARY_DIR}")
set(IVT_INCLUDE_DIR "${IVT_BASE_DIR}/${INCLUDE_DIR}")
set(IVT_CMAKE_DIR "${IVT_BASE_DIR}/${CMAKE_DIR}")
set(IVT_DATA_DIR "${IVT_BASE_DIR}/${DATA_DIR}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${IVT_CMAKE_DIR}")
set(PACKAGE_DEPENDENCIES "" CACHE STRING "" FORCE)
###############################################
# build all ivt libraries
###############################################
add_subdirectory(src)

###############################################
# Export the package for use from the build-tree
###############################################
# (this registers the build-tree with a global CMake-registry)
if(CMAKE_VERSION VERSION_GREATER "2.8")
   export(PACKAGE IVT)
endif()

