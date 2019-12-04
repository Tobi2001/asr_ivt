if (IVT_INCLUDE_DIR AND IVT_LIBRARIES)

  # in cache already
  set(IVT_FOUND TRUE)

else()

    find_path(IVT_INCLUDE_DIR Image/ByteImage.h
        # installation selected by user
        ${IVT_DIR}/src
        ${IVT_DIR}
        $ENV{IVT_DIR}
        $ENV{IVT_DIR}/src
        $ENV{HOME}/IVT/src
    )
    
    set(IVT_USERLIBS_INCLUDE_DIR ${IVT_INCLUDE_DIR}/../userlibs)
    

    if (ARMARX_OS_WIN)
        # todo implement windows
    else()
        find_library(IVT_LIBRARY NAMES ivt PATHS ${IVT_INCLUDE_DIR}/../lib/linux)
        if (IVT_LIBRARY)
              set(IVT_FOUND TRUE)
              set(IVT_LIBRARIES ${IVT_LIBRARY})
        endif()

        find_library(IVT_GUI_LIBRARY NAMES ivtgui PATHS ${IVT_INCLUDE_DIR}/../lib/linux)
        if (IVT_GUI_LIBRARY)
            set(IVT_GUI_FOUND TRUE)
            set(IVT_LIBRARIES ${IVT_LIBRARIES} ${IVT_GUI_LIBRARY})
        endif()

        find_library(IVT_RECOGNITION_LIBRARY NAMES ivtrecognition PATHS ${IVT_INCLUDE_DIR}/../lib/linux)
        if (IVT_RECOGNITION_LIBRARY)
            set(IVT_RECOGNITION_FOUND TRUE)
            set(IVT_LIBRARIES ${IVT_LIBRARIES} ${IVT_RECOGNITION_LIBRARY})
        endif()

        find_library(IVT_VIDEOCAPTURE_LIBRARY NAMES ivtvideocapture PATHS ${IVT_INCLUDE_DIR}/../lib/linux)
        if (IVT_VIDEOCAPTURE_LIBRARY)
            find_library(DC1394_LIBRARY NAMES dc1394 PATHS /usr/lib)
            find_library(RAW1394_LIBRARY NAMES raw1394 PATHS /usr/lib)

            if(DC1394_LIBRARY AND RAW1394_LIBRARY)
                set(IVT_VIDEOCAPTURE_FOUND TRUE)
                set(IVT_LIBRARIES ${IVT_LIBRARIES} ${IVT_VIDEOCAPTURE_LIBRARY} ${DC1394_LIBRARY} ${RAW1394_LIBRARY})
            endif()
        endif()
        
        find_library(IVT_USERLIBS_LIBRARY NAMES ivtuserlibs PATHS ${IVT_INCLUDE_DIR}/../lib/linux)
        if (IVT_USERLIBS_LIBRARY)
            set(IVT_USERLIBS_FOUND TRUE)
            set(IVT_LIBRARIES ${IVT_LIBRARIES} ${IVT_USERLIBS_LIBRARY})
        endif()
        
        find_library(GL_LIBRARY NAMES GL)
        if (GL_LIBRARY)
            set(GL_LIBRARY_FOUND TRUE)
            set(IVT_LIBRARIES ${IVT_LIBRARIES} ${GL_LIBRARY})
        endif()
        
        find_library(GLU_LIBRARY NAMES GLU)
        if (GLU_LIBRARY)
            set(GLU_LIBRARY_FOUND TRUE)
            set(IVT_LIBRARIES ${IVT_LIBRARIES} ${GLU_LIBRARY})
        endif()
    endif()
    
    set(IVT_INCLUDE_DIRS ${IVT_INCLUDE_DIR} ${IVT_USERLIBS_INCLUDE_DIR})

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(IVT DEFAULT_MSG IVT_INCLUDE_DIR IVT_INCLUDE_DIRS)

    mark_as_advanced(IVT_INCLUDE_DIR)
endif()
