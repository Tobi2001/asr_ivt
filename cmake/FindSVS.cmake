if( APPLE )
 set( SVS_FOUND FALSE )
endif( APPLE )

if( UNIX )
  find_path( SVS_INCLUDE_DIRS NAMES svsclass.h)
  find_library( SVS_LIBRARIES NAMES svscap)

  if( SVS_LIBRARIES AND SVS_INCLUDE_DIRS )
    set( SVS_FOUND TRUE )
  endif()

endif( UNIX )

include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( SVS DEFAULT_MSG SVS_LIBRARIES SVS_INCLUDE_DIRS )

mark_as_advanced( SVS_LIBRARIES SVS_INCLUDE_DIRS )

