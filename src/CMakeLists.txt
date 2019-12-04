################################################
# IVT Library CMakeFile
################################################
# authors:  Kai Welke (welke@kit.edu)
#           Manfred Kröhnert (kroenert@kit.edu)
################################################
include("${IVT_CMAKE_DIR}/macros/IVTMacros.cmake")

################################################
# options
################################################
option(IVT_LOAD_KPP "Compile IVT with Keyetech Performance Primitives" OFF)
option(IVT_USE_OPENCV1 "Use OpenCV 1.x.x instead of OpenCV 2.xx for libivtvideocapture and libivtopencv" OFF)

if(MSVC)
    option(IVT_WINDOWS_RUNTIME_STATIC "Use static linking against windows runtime libs in IVT and projects" OFF)
endif()
if(APPLE)
    option(IVT_USE_32BIT_QUICKTIME "Force 32 bit compilation on 64 bit MacOS in order to support Quicktime on MacOsX > 10.5" OFF)
endif()

################################################
# setup compiler options
################################################
# Set up for debug build
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: Debug Release."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Set OS specific options 
if(UNIX)
    # We are on Linux
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        if(NOT IVT_USE_32BIT_QUICKTIME)
            add_definitions(-fpic)
        endif()
    endif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")

    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        message(STATUS "Configuring Debug build")
        add_definitions(-D_DEBUG -ggdb) # -Wall -W -Werror -pedantic)
    else()
        message(STATUS "Configuring Release build")
        add_definitions(-O3)
    endif()
else(UNIX)
    if(MSVC)
        # We are on Windows
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
        add_definitions(/MP)
        
        # static runtime under windows if selected
        if(IVT_WINDOWS_RUNTIME_STATIC)
            make_windows_runtime_static()
        endif()
    endif(MSVC)
endif(UNIX)
if(APPLE)
    if(IVT_USE_32BIT_QUICKTIME)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
    endif()
endif()


################################################
# set install paths
################################################
set(IVT_INSTALL_HEADER_DIR "${CATKIN_GLOBAL_INCLUDE_DESTINATION}")
set(IVT_INSTALL_CMAKE_DIR "${CATKIN_GLOBAL_BIN_DESTINATION}")
set(IVT_INSTALL_LIBRARY_DIR "${CATKIN_PACKAGE_LIB_DESTINATION}")
set(IVT_INSTALL_DATA_DIR "${CATKIN_GLOBAL_BIN_DESTINATION}")

################################################
# build all libraries
################################################
include(CMakeLists.ivt.txt)
include(CMakeLists.ivtgui.txt)
include(CMakeLists.ivtvideocapture.txt)
include(CMakeLists.ivtopencv.txt)

