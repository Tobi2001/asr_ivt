
macro(create_source_groups SOURCES)
    # extract all directories from source files
    foreach(FILENAME ${SOURCES})
        get_filename_component(SOURCE_DIR ${FILENAME} PATH)
        source_group(${SOURCE_DIR} REGULAR_EXPRESSION "${SOURCE_DIR}/.*\\.(h|cpp)")
    endforeach()
endmacro(create_source_groups)

macro(append_headers_from_cpp OUTPUT_HEADERS SOURCES INCLUDE_DIR)
    # extract all directories from source files
    set(HEADERS "")
    foreach(SOURCE ${SOURCES})
        string(REGEX REPLACE "\\.cpp" ".h" HEADER ${SOURCE})
        set(FULLPATH "${INCLUDE_DIR}/${HEADER}")
        if(EXISTS ${FULLPATH})
            list(APPEND HEADERS ${HEADER})
        endif()
    endforeach()
    
    list(APPEND ${OUTPUT_HEADERS} ${HEADERS})
endmacro(append_headers_from_cpp)

macro(make_windows_runtime_static)
    # Set static linking of runtime
    set(variables
      CMAKE_C_FLAGS_DEBUG
      CMAKE_C_FLAGS_MINSIZEREL
      CMAKE_C_FLAGS_RELEASE
      CMAKE_C_FLAGS_RELWITHDEBINFO
      CMAKE_CXX_FLAGS_DEBUG
      CMAKE_CXX_FLAGS_MINSIZEREL
      CMAKE_CXX_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_RELWITHDEBINFO
    )

    foreach(variable ${variables})
        if(${variable} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
            set(${variable} "${${variable}}" CACHE STRING "" FORCE)
        endif()
    endforeach()    
endmacro()

macro(cache_append_value VARIABLE_NAME ENTRY)
    if (${VARIABLE_NAME})
        SET(${VARIABLE_NAME} "${${VARIABLE_NAME}}, ${ENTRY}" CACHE INTERNAL "" FORCE)
    else()
        set(${VARIABLE_NAME} "${ENTRY}" CACHE INTERNAL "" FORCE)
    endif()
endmacro()
