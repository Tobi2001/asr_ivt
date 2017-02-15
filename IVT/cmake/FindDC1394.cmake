if( WIN32 )
  set( DC1394_FOUND FALSE )
endif( WIN32 )

if( APPLE )
 set( DC1394_FOUND FALSE )
endif( APPLE )

if( UNIX )
  find_path( DC1394_INCLUDE_DIR NAMES libdc1394/dc1394_control.h)
  find_path( RAW1394_INCLUDE_DIR NAMES libraw1394/raw1394.h)
  find_library( DC1394_LIBRARY NAMES dc1394_control)
  find_library( RAW1394_LIBRARY NAMES raw1394)

  if( DC1394_LIBRARY AND RAW1394_LIBRARY AND DC1394_INCLUDE_DIR AND RAW1394_INCLUDE_DIR )
    set( DC1394_LIBRARIES ${DC1394_LIBRARY} ${RAW1394_LIBRARY} )
    set( DC1394_INCLUDE_DIRS ${DC1394_INCLUDE_DIR} ${RAW1394_INCLUDE_DIR} )
    set( DC1394_FOUND TRUE )
    message(STATUS "dc1394 ${DC1394_LIBRARIES}")
  endif()
endif( UNIX )

include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( DC1394 DEFAULT_MSG DC1394_LIBRARIES DC1394_INCLUDE_DIRS )

mark_as_advanced( DC1394_INCLUDE_DIRS DC1394_LIBRARIES )

