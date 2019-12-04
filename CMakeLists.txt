cmake_minimum_required(VERSION 2.8.3)
project(asr_ivt)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS)

# please not that the name of the last library depends on the version of qt used. See /IVT/src/CMakeLists.ivtgui.txt
# Export DC1394 since we use local cmake modules to which other packages have no access.
# Keep in mind libraries need to be in an order representing their interdependencies.
catkin_package(
        INCLUDE_DIRS src 
        LIBRARIES ivtvideocapture ivtopencv ivtguiqt4 ivt
	DEPENDS DC1394 DC1394V2
)

set(IVT_BASE_DIR "${PROJECT_SOURCE_DIR}")

set(IVT_LIBRARY_DIR "${CATKIN_PACKAGE_LIB_DESTINATION}")
set(IVT_BINARY_DIR "${CATKIN_PACKAGE_BIN_DESTINATION}")
set(IVT_INCLUDE_DIR "${IVT_BASE_DIR}/src")
set(IVT_CMAKE_DIR "${IVT_BASE_DIR}/cmake")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${IVT_CMAKE_DIR}")
set(PACKAGE_DEPENDENCIES "" CACHE STRING "" FORCE)


add_subdirectory(src)

