cmake_minimum_required(VERSION 3.16)

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include(DeepsEngineSetup)

# Basic information about project
set(DEEPS_ENGINE_VERSION "0.1")
project(DeepsEngine VERSION ${DEEPS_ENGINE_VERSION})

# find the libraries for running deeps engine
DEEPS_ENGINE_SETUP()

# get include directories for libraries used
include_directories(${PROJECT_SOURCE_DIR}/src/engine/include)

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

if(WITH_EDITOR)
    find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)

    include_directories(${PROJECT_SOURCE_DIR}/src/editor/include)

    include(QtCommon)
    fix_project_version()

    FILE(GLOB EDITOR_SOURCE_FILES_2
            src/editor/*.cpp
            src/editor/*.h
            src/editor/widget/*.cpp
            src/editor/widget/*.h
            src/editor/widget/component/*.cpp
            src/editor/widget/component/*.h)

    set(EDITOR_SOURCE_FILES
            "src/editor/include/OpenGLWidget.h"
            "src/editor/include/SceneViewWidget.h"
            "src/editor/include/InspectorWidget.h"
            "src/editor/include/ConsoleWidget.h"
            "src/editor/include/TransformComponentWidget.h"
            "src/editor/include/TagComponentWidget.h"
            "src/editor/include/MeshFilterComponentWidget.h"
            "src/editor/include/CameraComponentWidget.h"
    )

    add_project_meta(META_FILES_TO_INCLUDE)

    set(RESOURCE_FILES src/editor/example.qrc)

    source_group("UI Files" FILES ${UI_FILES})

    add_executable(${PROJECT_NAME} ${OS_BUNDLE} ${ENGINE_SOURCE_FILES} ${EDITOR_SOURCE_FILES} ${EDITOR_SOURCE_FILES_2} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES})

    target_precompile_headers(${PROJECT_NAME} INTERFACE QtWidgets.h)

    target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::OpenGL)
else()
    # create shared .dll library
    if (AS_LIBRARY)
        # create compiled library
        add_library(${PROJECT_NAME} SHARED ${ENGINE_SOURCE_FILES})
        set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/src/engine/lib)
    else()
        # create executable application
        add_executable(${PROJECT_NAME} ${ENGINE_SOURCE_FILES})
    endif()

    if (EMSCRIPTEN)
        # web build
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
        target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
    endif ()
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE DEEPS_ENGINE_VERSION=${DEEPS_ENGINE_VERSION})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)