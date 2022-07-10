macro(DEEPS_ENGINE_IDENTIFIERS)
    # Set additional project information
    set(COMPANY "DeepDev")
    set(COPYRIGHT "Copyright (c) 2022 Deepak Ramalingam. All rights reserved.")
    set(IDENTIFIER "com.DeepDev.DeepsEngineEditor")
endmacro()

macro(DEEPS_ENGINE_DEFINITIONS)
    if(DEFINED ENV{WITH_EDITOR})
        message(STATUS "Building engine in editor mode")
        set(WITH_EDITOR TRUE)
        add_compile_definitions(WITH_EDITOR)
    else()
        if (DEFINED ENV{AS_LIBRARY})
            message(STATUS "Compiling engine as library")
            set(AS_LIBRARY TRUE)
        else()
            message(STATUS "Running engine in standalone mode")
            set(AS_LIBRARY FALSE)
        endif()
        set(WITH_EDITOR FALSE)
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

        find_package(OpenAL REQUIRED)

        if(NOT OPENAL_FOUND)
            message(FATAL_ERROR "OpenAL not found")
        endif()
    endif()

    # get OPENGL include path and libraries
    message(STATUS "OPENGL_INCLUDE_DIRS = ${OPENGL_INCLUDE_DIRS}")
    include_directories(${OPENGL_INCLUDE_DIRS})
    message(STATUS "OPENGL_LIBRARIES = ${OPENGL_LIBRARIES}")
    link_libraries(${OPENGL_LIBRARIES})


    message(STATUS "OPENAL_LIBRARY = ${OPENAL_LIBRARY}")
    link_libraries(${OPENAL_LIBRARY})

    if (EMSCRIPTEN)
        # TODO: this will cause errors when this library is not present...
        include_directories(${PROJECT_SOURCE_DIR}/res/example-project/build/web/lua-5.4.4/src)
    else()
        find_package(Lua REQUIRED)

        if (NOT LUA_FOUND)
            message(FATAL_ERROR "LUA not found. Please refer to https://github.com/rdeepak2002/DeepsEngine/blob/main/README.md")
        endif()
    endif()

    # get LUA path use macro to get around differing versions
    message(STATUS "LUA_INCLUDE_DIR ${LUA_INCLUDE_DIR}")
    include_directories(${LUA_INCLUDE_DIR})
    message(STATUS "LUA_LIBRARIES ${LUA_LIBRARIES}")
    link_libraries(${LUA_LIBRARIES})

    # find yaml parsing library
    if (EMSCRIPTEN)
        # TODO: this will cause errors when this library is not present...
        include_directories(${PROJECT_SOURCE_DIR}/res/example-project/build/web/yaml-cpp/include)
    else()
        find_package(yaml-cpp CONFIG REQUIRED)
    endif()

    # assimp
    if (APPLE)
        if(EXISTS "/opt/homebrew/Cellar/assimp@5.0.1/5.0.1/lib/libassimp.dylib")
            # arm64 mac
            message(STATUS "Using arm64 Assimp")
            link_libraries("/opt/homebrew/Cellar/assimp@5.0.1/5.0.1/lib/libassimp.dylib")
        elseif(EXISTS "/usr/local/Cellar/assimp@5.0.1/5.0.1/lib/libassimp.dylib")
            # intel mac
            message(STATUS "Using x86 Assimp")
            link_libraries("/usr/local/Cellar/assimp@5.0.1/5.0.1/lib/libassimp.dylib")
        else()
            message(FATAL_ERROR "Assimp version 5.0.1 not installed by Homebrew")
        endif()
    elseif (EMSCRIPTEN)
        # link assimp for web
        link_libraries("${PROJECT_SOURCE_DIR}/assimp-5.0.1/lib/libassimp.a")
        link_libraries("${PROJECT_SOURCE_DIR}/assimp-5.0.1/lib/libIrrXML.a")
        link_libraries("${PROJECT_SOURCE_DIR}/assimp-5.0.1/lib/libzlib.a")
    else()
        message(FATAL_ERROR "Assimp linking not supported for your Operating System")
    endif()
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
        if (NOT EMSCRIPTEN)
            # standalone build
            file(COPY res DESTINATION assets)
        endif ()
    endif()
endmacro()

macro(DEEPS_ENGINE_SETUP)
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
        message(WARNING "vcpkg folder not found. Please refer to https://github.com/rdeepak2002/DeepsEngine/blob/main/README.md")
    endif()
    DEEPS_ENGINE_IDENTIFIERS()
    DEEPS_ENGINE_DEFINITIONS()
    DEEPS_ENGINE_FIND_THIRD_PARTY_LIBRARIES()
    DEEPS_ENGINE_EXPORT_ASSETS_FOLDER()
endmacro()

macro(DEEPS_ENGINE_LINK_LIBRARIES_TO_TARGET)
    target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp)
endmacro()