
if( WIN32 )
  if( CYGWIN )

    find_path( Coin3D_INCLUDE_DIRS Inventor/So.h)
    find_library( Coin3D_LIBRARIES coin)

  else()
    find_path( Coin3D_INCLUDE_DIRS Inventor/So.h "$ENV{Coin3D_DIR}/include" )
    find_library( Coin3D_LIBRARIES coin3 "$ENV{Coin3D_DIR}/lib" )

    if( Coin3D_LIBRARIES AND Coin3D_INCLUDE_DIRS)
        add_definitions( -DCOIN_DLL -DSOQT_DLL )
        set( Coin3D_FOUND TRUE )
    endif()

  endif( CYGWIN )
endif( WIN32 )

if( UNIX )
    find_path( Coin3D_INCLUDE_DIRS NAMES Inventor/So.h PATHS $ENV{Coin3D_DIR}/include /usr/include /usr/local/include NO_DEFAULT_PATH )
    find_library( Coin3D_LIBRARIES  NAMES Coin PATHS $ENV{Coin3D_DIR}/lib /usr/lib /usr/local/lib NO_DEFAULT_PATH )
    
   if( Coin3D_LIBRARIES AND Coin3D_INCLUDE_DIRS)
        set( Coin3D_FOUND TRUE )
    endif()
endif( UNIX )

IF(APPLE)
    FIND_PATH(Coin3D_INCLUDE_DIRS Inventor/So.h
     /Library/Frameworks/Inventor.framework/Headers
    )
    FIND_LIBRARY(Coin3D_LIBRARIES Coin
      /Library/Frameworks/Inventor.framework/Libraries
    )

    if( Coin3D_LIBRARIES AND Coin3D_INCLUDE_DIRS)
        set( Coin3D_FOUND TRUE )
    endif()
ENDIF(APPLE)

include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( Coin3D DEFAULT_MSG Coin3D_LIBRARIES Coin3D_INCLUDE_DIRS )

mark_as_advanced( Coin3D_INCLUDE_DIRS Coin3D_LIBRARIES )

