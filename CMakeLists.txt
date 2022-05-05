cmake_minimum_required(VERSION 3.16)

if (EMSCRIPTEN)
    set(CMAKE_C_COMPILER "emcc")
endif ()

# specify whether this should run as a standalone or build as a node gui plugin
if(DEFINED ENV{STANDALONE})
    message(STATUS "Running engine in standalone mode")
    set(RUN_STANDALONE TRUE)

    if(DEFINED ENV{DEVELOP_WEB})
        message(STATUS "developing in web mode")
        set(DEVELOP_WEB TRUE)
        add_compile_definitions(DEVELOP_WEB)
    endif()
else()
    message(STATUS "Building engine as compiled library")
    set(RUN_STANDALONE FALSE)
endif()

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include(Util)

# Basic information about project
project(DeepsEngine VERSION 1.0)

# Set additional project information
set(COMPANY "DeepDev")
set(COPYRIGHT "Copyright (c) 2022 Deepak Ramalingam. All rights reserved.")
set(IDENTIFIER "com.DeepDev.DeepsEngineEditor")

# print out the architecture
EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
message( STATUS "Architecture = ${ARCHITECTURE}" )

# find packages
if (NOT EMSCRIPTEN)
    find_package(OpenGL REQUIRED)

    if(NOT OPENGL_FOUND)
        message(FATAL_ERROR "OpenGL not found")
    endif()
endif()

#find_package(glfw REQUIRED)
#
#if(GLFW_FOUND) # Works with some other methods
#    message(STATUS "GLFW3_INCLUDE_PATH=${GLFW3_INCLUDE_PATH}")
#    message(STATUS "GLFW_LIBRARIES=${GLFW_LIBRARIES}")
#else( GLFW_FOUND )
#    message(FATAL_ERROR "GLFW3 not found")
#endif( GLFW_FOUND )

find_package(Lua REQUIRED)

message(STATUS "LUA_INCLUDE_DIR=${LUA_INCLUDE_DIR}")
message(STATUS "LUA_LIBRARIES=${LUA_LIBRARIES}")

# get OPENGL include path and libraries
message(STATUS "OPENGL_INCLUDE_DIRS = ${OPENGL_INCLUDE_DIRS}")
include_directories(${OPENGL_INCLUDE_DIRS})
message(STATUS "OPENGL_LIBRARIES = ${OPENGL_LIBRARIES}")
link_libraries(${OPENGL_LIBRARIES})

# get GLFW path use macro to get around differing versions
GETFIRSTDIR(GLFW_H_PATH /opt/homebrew/Cellar/glfw/)
set(GLFW3_INCLUDE_PATH ${GLFW_H_PATH}/include/GLFW)
message(STATUS "GLFW3_INCLUDE_PATH ${GLFW3_INCLUDE_PATH}")
include_directories(${GLFW3_INCLUDE_PATH})
set(GLFW_LIBRARIES ${GLFW_H_PATH}/lib/libglfw.dylib)
message(STATUS "GLFW_LIBRARIES ${GLFW_LIBRARIES}")
link_libraries(${GLFW_LIBRARIES})

# get GLEW path use macro to get around differing versions
GETFIRSTDIR(GLEW_H_PATH /opt/homebrew/Cellar/glew/)
set(GLEW_INCLUDE_DIRS ${GLEW_H_PATH}/include/GL)
message(STATUS "GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIRS}")
include_directories(${GLEW_INCLUDE_DIRS})
set(GLEW_LIBRARIES ${GLEW_H_PATH}/lib/libGLEW.dylib)
message(STATUS "GLEW_LIBRARIES ${GLEW_LIBRARIES}")
link_libraries(${GLEW_LIBRARIES})

# get LUA path use macro to get around differing versions
#GETFIRSTDIR(LUA_PATH /opt/homebrew/Cellar/lua/)
#set(LUA_INCLUDE_DIR ${LUA_PATH}/include/lua)
message(STATUS "LUA_INCLUDE_DIR ${LUA_INCLUDE_DIR}")
include_directories(${LUA_INCLUDE_DIR})
#set(LUA_LIBRARIES /opt/homebrew/lib/liblua.dylib)
message(STATUS "LUA_LIBRARIES ${LUA_LIBRARIES}")
link_libraries(${LUA_LIBRARIES})

# get include directories for libraries used
set(DEEPS_ENGINE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/engine/include)
message(STATUS "DEEPS_ENGINE_INCLUDE_DIRS ${DEEPS_ENGINE_INCLUDE_DIRS}")
include_directories(${DEEPS_ENGINE_INCLUDE_DIRS})

# source files for engine code
FILE(GLOB ENGINE_SOURCE_FILES
        src/main.cpp
        src/engine/renderer/glad.c
        src/engine/*.cpp
        src/engine/component/*.cpp
        src/engine/renderer/*.cpp
        src/engine/scene/*.cpp
        src/engine/util/*.cpp)

message(STATUS "Engine source files: ${ENGINE_SOURCE_FILES}")

if(RUN_STANDALONE)
    # standalone engine
    add_compile_definitions(STANDALONE)

    # create shared .dll library
#    add_library(${PROJECT_NAME} SHARED ${ENGINE_SOURCE_FILES})

    # create executable application
    add_executable(${PROJECT_NAME} ${ENGINE_SOURCE_FILES})

    if (EMSCRIPTEN)
        # web build
        file(COPY res DESTINATION "${PROJECT_SOURCE_DIR}/src/build/web/src/build/assets")
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS " \
        --use-preload-plugins \
        -s LLD_REPORT_UNDEFINED \
        -s EXPORTED_FUNCTIONS=['_main','_onResizeWindow'] \
        -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap'] \
        -s ALLOW_MEMORY_GROWTH=1 -s USE_WEBGL2=1 \
        -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 \
        -s FULL_ES3=1 \
        -s USE_GLFW=3 \
        --preload-file assets")
    else()
        # standalone build
        file(COPY res DESTINATION assets)
    endif ()
else()
    set(DEEPS_ENGINE_EDITOR_H ${PROJECT_SOURCE_DIR}/src/editor/include)
    include_directories(${DEEPS_ENGINE_EDITOR_H})

    if(APPLE)
        file(COPY res DESTINATION ${PROJECT_NAME}.app/Contents/MacOS/assets)
    elseif(WIN32)
        # for Windows operating system in general
    elseif(UNIX AND NOT APPLE)
        # for Linux, BSD, Solaris, Minix
    endif()

    include(QtCommon)
    fix_project_version()

    # build as a node gui plugin
    add_compile_definitions(INCLUDE_DEEPS_ENGINE_LIBRARY)

    set(EDITOR_SOURCE_FILES
        ${ENGINE_SOURCE_FILES}
        "${PROJECT_SOURCE_DIR}/src/main.cpp"
        "${PROJECT_SOURCE_DIR}/src/editor/mainwindow.cpp"
        "src/editor/include/OpenGLWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/OpenGLWidget.cpp"
        "src/editor/include/SceneViewWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/SceneViewWidget.cpp"
        "src/editor/include/InspectorWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/InspectorWidget.cpp"
        "src/editor/include/ConsoleWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/ConsoleWidget.cpp"
        "src/editor/include/TransformComponentWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/component/TransformComponentWidget.cpp"
        "src/editor/include/TagComponentWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/component/TagComponentWidget.cpp"
        "src/editor/include/MeshFilterComponentWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/component/MeshFilterComponentWidget.cpp"
        "src/editor/include/CameraComponentWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/component/CameraComponentWidget.cpp"
    )

    add_project_meta(META_FILES_TO_INCLUDE)

    set(RESOURCE_FILES src/editor/example.qrc)

    find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)

    source_group("UI Files" FILES ${UI_FILES})

    add_executable(${PROJECT_NAME} ${OS_BUNDLE} ${EDITOR_SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES})

    target_precompile_headers(${PROJECT_NAME} INTERFACE QtWidgets.h)

    target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::OpenGL)
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)