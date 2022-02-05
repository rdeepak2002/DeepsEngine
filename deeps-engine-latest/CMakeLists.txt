# Reference: https://doc.qt.io/qt-6/cmake-manual.html

cmake_minimum_required(VERSION 3.16)

# specify whether this should run as a standalone or build as a node gui plugin
if(DEFINED ENV{STANDALONE})
    message(STATUS "running engine in standalone mode")
    set(RUN_STANDALONE TRUE)
else()
    message(STATUS "building engine as compiled library")
    set(RUN_STANDALONE FALSE)
endif()

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (NOT RUN_STANDALONE)
    # Include Qt basic functions
    include(QtCommon)
endif()

# Basic information about project

project(example VERSION 1.0)

if (NOT RUN_STANDALONE)
    # Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
    fix_project_version()
endif()

if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
endif()

# Set additional project information
set(COMPANY "Example")
set(COPYRIGHT "Copyright (c) 2021 Deepak Ramalingam. All rights reserved.")
set(IDENTIFIER "com.example.Example")

# get include directories for libraries used
set(GLEW_H /usr/local/include/gl)
set(GLFW_H /usr/local/include/glfw)
set(GLM /usr/local/include/glm)
set(GLAD_H /usr/local/include/glad)
set(KH_H /usr/local/include/KHR)
set(RAPID_JSON /usr/local/include/rapidjson)
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H} ${KH_H} ${GLM} ${RAPID_JSON})

# link libraries used
set(GLEW_LINK /usr/local/lib/libGLEW.dylib)
set(GLFW_LINK /usr/local/lib/libglfw.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

if(RUN_STANDALONE)
    # standalone engine
    add_compile_definitions(STANDALONE)

    file(GLOB SOURCE_FILES_EXEC
        "${PROJECT_SOURCE_DIR}/src/main.cpp"
        "${PROJECT_SOURCE_DIR}/src/Engine/include/glad.c"
        "${PROJECT_SOURCE_DIR}/src/Engine/include/stb_image.h"
        "${PROJECT_SOURCE_DIR}/src/Engine/include/entt.hpp"
#        "${PROJECT_SOURCE_DIR}/src/Engine/OpenGLRenderer.h"
#        "${PROJECT_SOURCE_DIR}/src/Engine/OpenGLRenderer.cpp"
        "${PROJECT_SOURCE_DIR}/src/Engine/Shader.h"
        "${PROJECT_SOURCE_DIR}/src/Engine/Shader.cpp"
        "${PROJECT_SOURCE_DIR}/src/Engine/Components.h"
        "${PROJECT_SOURCE_DIR}/src/Engine/Renderer.cpp"
        "${PROJECT_SOURCE_DIR}/src/Engine/Renderer.h"
    )

    add_executable(Release ${SOURCE_FILES_EXEC})

    set_property(TARGET Release PROPERTY CXX_STANDARD 17)
    set_property(TARGET Release PROPERTY CXX_STANDARD_REQUIRED ON)
else()
    # build as a node gui plugin
    add_compile_definitions(INCLUDE_DEEPS_ENGINE_LIBRARY)

    set(SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/src/main.cpp"
#        "${PROJECT_SOURCE_DIR}/src/Engine/include/glad.c"
        "${PROJECT_SOURCE_DIR}/src/Engine/include/stb_image.h"
        "${PROJECT_SOURCE_DIR}/src/Engine/include/entt.hpp"
#        "${PROJECT_SOURCE_DIR}/src/Engine/OpenGLRenderer.h"
#        "${PROJECT_SOURCE_DIR}/src/Engine/OpenGLRenderer.cpp"
        "${PROJECT_SOURCE_DIR}/src/Engine/Shader.h"
        "${PROJECT_SOURCE_DIR}/src/Engine/Shader.cpp"
        "${PROJECT_SOURCE_DIR}/src/Engine/Components.h"
        "${PROJECT_SOURCE_DIR}/src/Editor/mainwindow.cpp"
        "${PROJECT_SOURCE_DIR}/src/Editor/OpenGLCubeWidget.h"
        "${PROJECT_SOURCE_DIR}/src/Editor/OpenGLCubeWidget.cpp"
        "${PROJECT_SOURCE_DIR}/src/Engine/Renderer.cpp"
        "${PROJECT_SOURCE_DIR}/src/Engine/Renderer.h"
    )

    add_project_meta(META_FILES_TO_INCLUDE)

    set(RESOURCE_FILES src/Editor/example.qrc)

    find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)

    # source_group("UI Files" FILES ${UI_FILES})

    add_executable(${PROJECT_NAME} ${OS_BUNDLE} # Expands to WIN32 or MACOS_BUNDLE depending on OS
            ${SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES}
            )

    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

    target_precompile_headers(${PROJECT_NAME} INTERFACE QtWidgets.h)

    target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::OpenGL)
endif()
