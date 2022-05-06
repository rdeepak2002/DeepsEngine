macro(DEEPS_ENGINE_IDENTIFIERS)
    # Set additional project information
    set(COMPANY "DeepDev")
    set(COPYRIGHT "Copyright (c) 2022 Deepak Ramalingam. All rights reserved.")
    set(IDENTIFIER "com.DeepDev.DeepsEngineEditor")
endmacro()

macro(DEEPS_ENGINE_DEFINITIONS)
    if(DEFINED ENV{WITH_EDITOR})
        message(STATUS "Building engine in editor mode")
        set(RUN_STANDALONE FALSE)
        add_compile_definitions(INCLUDE_DEEPS_ENGINE_LIBRARY)
    else()
        message(STATUS "Running engine in standalone mode")
        set(RUN_STANDALONE TRUE)
        add_compile_definitions(STANDALONE)
    endif()
endmacro()

macro(DEEPS_ENGINE_FIND_THIRD_PARTY_LIBRARIES)
    # find packages
    if (NOT EMSCRIPTEN)
        find_package(OpenGL REQUIRED)

        if(NOT OPENGL_FOUND)
            message(FATAL_ERROR "OpenGL not found")
        endif()

        find_package(glfw3 CONFIG REQUIRED)
    endif()

    # get OPENGL include path and libraries
    message(STATUS "OPENGL_INCLUDE_DIRS = ${OPENGL_INCLUDE_DIRS}")
    include_directories(${OPENGL_INCLUDE_DIRS})
    message(STATUS "OPENGL_LIBRARIES = ${OPENGL_LIBRARIES}")
    link_libraries(${OPENGL_LIBRARIES})

    find_package(Lua REQUIRED)

    if (NOT LUA_FOUND)
        message(FATAL_ERROR "LUA not found. Please refer to https://github.com/rdeepak2002/DeepsEngine/blob/main/README.md file.")
    endif()

    # get LUA path use macro to get around differing versions
    message(STATUS "LUA_INCLUDE_DIR ${LUA_INCLUDE_DIR}")
    include_directories(${LUA_INCLUDE_DIR})
    message(STATUS "LUA_LIBRARIES ${LUA_LIBRARIES}")
    link_libraries(${LUA_LIBRARIES})
endmacro()

macro(DEEPS_ENGINE_EXPORT_ASSETS_FOLDER)
    if(DEFINED ENV{WITH_EDITOR})
        # editor mode
        if(APPLE)
            file(COPY res DESTINATION ${PROJECT_NAME}.app/Contents/MacOS/assets)
        elseif(WIN32)
            # for Windows operating system in general
        elseif(UNIX AND NOT APPLE)
            # for Linux, BSD, Solaris, Minix
        endif()
    else()
        if (EMSCRIPTEN)
            # web build
            file(COPY res DESTINATION "${PROJECT_SOURCE_DIR}/src/build/web/src/build/assets")
        else()
            # standalone build
            file(COPY res DESTINATION assets)
        endif ()
    endif()
endmacro()

macro(DEEPS_ENGINE_SETUP)
    DEEPS_ENGINE_IDENTIFIERS()
    DEEPS_ENGINE_DEFINITIONS()
    DEEPS_ENGINE_FIND_THIRD_PARTY_LIBRARIES()
    DEEPS_ENGINE_EXPORT_ASSETS_FOLDER()
endmacro()