if( WIN32 )
  set( Unicap_FOUND FALSE )
endif( WIN32 )

if( APPLE )
 set( Unicap_FOUND FALSE )
endif( APPLE )

if( UNIX )
  find_path( Unicap_INCLUDE_DIRS NAMES unicap/unicap.h)
  find_library( Unicap_LIBRARIES NAMES unicap)

  if( Unicap_LIBRARIES AND Unicap_DIRS )
    set( Unicap_FOUND TRUE )
  endif()

endif( UNIX )

include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( Unicap DEFAULT_MSG Unicap_LIBRARIES Unicap_INCLUDE_DIRS )

mark_as_advanced( Unicap_INCLUDE_DIRS Unicap_LIBRARIES )

