if( WIN32 )
  set( V4L_FOUND FALSE )
endif( WIN32 )

if( APPLE )
  set( V4L_FOUND FALSE )
endif( APPLE )

if( UNIX )
  find_path( V4L_OLD_INCLUDE_DIRS NAMES linux/videodev.h)
  find_path( V4L_NEW_INCLUDE_DIRS NAMES linux/videodev2.h libv4l1-videodev.h)
  find_library( V4L_LIBRARIES NAMES v4l1)
    
  if(V4L_OLD_INCLUDE_DIRS)
    set(V4L_HAVE_LINUX_VIDEODEV_H TRUE)
    set(V4L_INCLUDE_DIRS ${V4L_OLD_INCLUDE_DIRS})
  elseif(V4L_NEW_INCLUDE_DIRS)
    set(V4L_HAVE_LINUX_VIDEODEV_H FALSE)
    set(V4L_INCLUDE_DIRS ${V4L_NEW_INCLUDE_DIRS})
  endif()
  
  if( V4L_LIBRARIES AND V4L_INCLUDE_DIRS)
    set( V4L_FOUND TRUE )
  endif()
endif( UNIX )

include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( V4L DEFAULT_MSG V4L_LIBRARIES V4L_INCLUDE_DIRS )

mark_as_advanced( V4L_INCLUDE_DIRS V4L_LIBRARIES )

