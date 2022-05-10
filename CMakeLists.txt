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
        src/engine/include/yaml/Yaml.cpp
        src/engine/*.cpp
        src/engine/component/*.cpp
        src/engine/renderer/*.cpp
        src/engine/scene/*.cpp
        src/engine/util/*.cpp)

message(STATUS "Engine source files: ${ENGINE_SOURCE_FILES}")

if(WITH_EDITOR)
    find_package(Qt5 COMPONENTS Widgets Concurrent OpenGL CONFIG REQUIRED)

    include_directories(${PROJECT_SOURCE_DIR}/src/editor/include)

    include(QtCommon)
    fix_project_version()

    FILE(GLOB EDITOR_SOURCE_FILES
            src/editor/*.cpp
            src/editor/widget/*.cpp
            src/editor/widget/component/*.cpp
            src/editor/include/*.h)

    add_project_meta(META_FILES_TO_INCLUDE)

    set(RESOURCE_FILES src/editor/example.qrc)

    source_group("UI Files" FILES ${UI_FILES})

    add_executable(${PROJECT_NAME} ${OS_BUNDLE} ${ENGINE_SOURCE_FILES} ${EDITOR_SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES})

    target_precompile_headers(${PROJECT_NAME} INTERFACE QtWidgets.h)

    target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::OpenGL yaml-cpp)

    add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/res
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.app/Contents/MacOS/assets/res)
else()
    if (AS_LIBRARY)
        # create shared library
        add_library(${PROJECT_NAME} SHARED ${ENGINE_SOURCE_FILES})
        set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/src/engine/lib)

        # copy build files to web build folder
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/src/engine/include ${PROJECT_SOURCE_DIR}/res/example-project/build/web/DeepsEngine/include)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/src/engine/lib ${PROJECT_SOURCE_DIR}/res/example-project/build/web/DeepsEngine/lib)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/cmake ${PROJECT_SOURCE_DIR}/res/example-project/build/web/DeepsEngine/cmake)
    else()
        # create executable application
        add_executable(${PROJECT_NAME} ${ENGINE_SOURCE_FILES})
    endif()

    if(NOT EMSCRIPTEN)
        # standalone build
        target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
    endif()

    DEEPS_ENGINE_LINK_LIBRARIES_TO_TARGET()
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE DEEPS_ENGINE_VERSION=${DEEPS_ENGINE_VERSION})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)