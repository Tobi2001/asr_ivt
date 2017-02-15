cmake_minimum_required(VERSION 2.8.3)
project(asr_ivt)

#Using the catkin_make process for the building of the IVT package
set(MAIN_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR})

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS)

# please not that the name of the last library depends on the version of qt used. See /IVT/src/CMakeLists.ivtgui.txt
# Export DC1394 since we use local cmake modules to which other packages have no access.
# Keep in mind libraries need to be in an order representing their interdependencies.
catkin_package(
        INCLUDE_DIRS IVT/src 
        LIBRARIES  ivtvideocapture ivtopencv ivtguiqt4 ivt
	DEPENDS DC1394 DC1394V2
)

add_subdirectory(IVT)

