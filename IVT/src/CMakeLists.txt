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
set(IVT_INSTALL_HEADER_DIR "${CMAKE_INSTALL_PREFIX}/include/ivt")
set(IVT_INSTALL_CMAKE_DIR "${CMAKE_INSTALL_PREFIX}/share/ivt")
set(IVT_INSTALL_LIBRARY_DIR "${CMAKE_INSTALL_PREFIX}/lib")
set(IVT_INSTALL_DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/ivt")

################################################
# build all libraries
################################################
include(CMakeLists.ivt.txt)
include(CMakeLists.ivtgui.txt)
include(CMakeLists.ivtvideocapture.txt)
include(CMakeLists.ivtopencv.txt)



################################################
# export project configuration (to enable find_package)
################################################
configure_file(
    "${IVT_CMAKE_DIR}/templates/IVTConfig.cmake.in"
    "${IVT_BUILD_DIRECTORY}/IVTConfig.cmake"
    @ONLY)

configure_file(
    "${IVT_CMAKE_DIR}/templates/IVTBuildTreeSettings.cmake.in"
    "${IVT_BUILD_DIRECTORY}/IVTBuildTreeSettings.cmake"
    @ONLY)

configure_file(
    "${IVT_CMAKE_DIR}/templates/IVTConfigVersion.cmake.in"
    "${IVT_BUILD_DIRECTORY}/IVTConfigVersion.cmake"
    @ONLY)

configure_file(
    "${IVT_CMAKE_DIR}/templates/IVTUseFile.cmake.in"
    "${IVT_BUILD_DIRECTORY}/IVTUseFile.cmake"
    @ONLY)

configure_file(
    "${IVT_CMAKE_DIR}/templates/IVTFeatures.cmake.in"
    "${IVT_BUILD_DIRECTORY}/IVTFeatures.cmake"
    @ONLY)

################################################
# export library dependencies 
################################################
# in build-tree dependencies
export(TARGETS ${IVT_LIBRARIES} FILE "${IVT_BUILD_DIRECTORY}/IVTLibraryDepends.cmake")

################################################
# install files
################################################

# in install dependencies
install(EXPORT IVT-targets
         DESTINATION "${IVT_INSTALL_CMAKE_DIR}"
         FILE IVTLibraryDepends.cmake)

# install cmake files for find
install(FILES
    "${IVT_BUILD_DIRECTORY}/IVTConfig.cmake"
    "${IVT_BUILD_DIRECTORY}/IVTConfigVersion.cmake"
    "${IVT_BUILD_DIRECTORY}/IVTUseFile.cmake"
    "${IVT_BUILD_DIRECTORY}/IVTFeatures.cmake"
    "${IVT_CMAKE_DIR}/macros/IVTMacros.cmake"
    DESTINATION "${IVT_INSTALL_CMAKE_DIR}"
    COMPONENT ApplicationData)

# install data dir
install(DIRECTORY "${IVT_DATA_DIR}"
        DESTINATION "${IVT_INSTALL_DATA_DIR}"
        COMPONENT ApplicationData)
            
################################################
# packaging
################################################
include(InstallRequiredSystemLibraries)
set(CPACK_SET_DESTDIR "on")
set(CPACK_PACKAGING_INSTALL_PREFIX "/tmp")
set(CPACK_DEBIAN_PACKAGE_NAME "IVT")
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_DESCRIPTION "Integrating Vision Toolkit")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Integrating Vision Toolkit")
set(CPACK_PACKAGE_VENDOR "KIT")
set(CPACK_PACKAGE_CONTACT "Pedram Azad")
set(CPACK_PACKAGE_VERSION_MAJOR "${IVT_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${IVT_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${IVT_PATCH_VERSION}")
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${IVT_MAJOR_VERSION}.${IVT_MINOR_VERSION}.${IVT_PATCH_VERSION}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${IVT_MAJOR_VERSION}.${IVT_MINOR_VERSION}.${IVT_PATCH_VERSION}")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "${PACKAGE_DEPENDENCIES}")
set(CPACK_DEBIAN_ARCHITECTURE "${CMAKE_SYSTEM_PROCESSOR}")

set(CPACK_COMPONENT_APPLICATIONDATA_DISPLAY_NAME "IVT Files")
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "IVT Libraries")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "IVT C++ Headers")

set(CPACK_COMPONENTS_ALL ApplicationData Headers Libraries)
include(CPack)



