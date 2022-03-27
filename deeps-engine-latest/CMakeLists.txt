# Reference: https://doc.qt.io/qt-6/cmake-manual.html

cmake_minimum_required(VERSION 3.16)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_C_COMPILER "emcc")
endif ()

# specify whether this should run as a standalone or build as a node gui plugin
if(DEFINED ENV{STANDALONE})
    message(STATUS "running engine in standalone mode")
    set(RUN_STANDALONE TRUE)

    if(DEFINED ENV{DEVELOP_WEB})
        message(STATUS "developing in web mode")
        set(DEVELOP_WEB TRUE)
        add_compile_definitions(DEVELOP_WEB)
    endif()
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

project(Editor VERSION 1.0)

if (NOT RUN_STANDALONE)
    # Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
    fix_project_version()
endif()

if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
endif()

# Set additional project information
set(COMPANY "DeepDev")
set(COPYRIGHT "Copyright (c) 2022 Deepak Ramalingam. All rights reserved.")
set(IDENTIFIER "com.DeepDev.DeepsEngineEditor")

#FIND_PACKAGE(SDL2 REQUIRED)
#Message("")
#Message( STATUS "FINDING SDL2" )
#IF (${SDL2_FOUND})
#    Message( STATUS "SDL2_FOUND: " ${SDL2_FOUND})
#    Message( STATUS "SDL2_INCLUDE_DIR:" ${SDL2_INCLUDE_DIR})
#    Message( STATUS "SDL2_LIBRARY: " ${SDL2_LIBRARY})
#ELSE()
#    Message( STATUS "SDL2_FOUND: " ${SDL2_FOUND})
#    Message( FATAL_ERROR "SDL2 NOT FOUND" )
#ENDIF()

# find opengl package
if (EMSCRIPTEN)
else()
    find_package(OpenGL REQUIRED)
endif()

# get include directories for libraries used
set(GLEW_H /usr/local/include/gl)
set(GLFW_H /usr/local/include/glfw)
set(GLM /usr/local/include/glm)
set(GLAD_H /usr/local/include/glad)
set(KH_H /usr/local/include/KHR)
set(RAPID_JSON /usr/local/include/rapidjson)
set(SDL2_INCLUDE_DIR /usr/local/Cellar/sdl2/2.0.20/include/SDL2)
set(SDL2_IMAGE_INCLUDE_DIR /usr/local/Cellar/sdl2_image/2.0.5/include/SDL2)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_H} ${GLFW_H} ${GLAD_H} ${KH_H} ${GLM} ${RAPID_JSON} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

# link libraries used
set(GLEW_LINK /usr/local/lib/libGLEW.dylib)
set(GLFW_LINK /usr/local/lib/libglfw.dylib)
set(SDL2_LIBRARY /usr/local/Cellar/sdl2/2.0.20/lib/libSDL2.dylib)
set(SDL2_IMAGE_LIBRARY /usr/local/Cellar/sdl2_image/2.0.5/lib/libSDL2_image.dylib)
link_libraries(${OPENGL_LIBRARIES} ${OPENGL} ${GLEW_LINK} ${GLFW_LINK} ${SDL2_LIBRARY})

if(RUN_STANDALONE)
    # standalone engine
    add_compile_definitions(STANDALONE)

    file(GLOB SOURCE_FILES_EXEC
        "${PROJECT_SOURCE_DIR}/src/engine/include/glad.c"
        "${PROJECT_SOURCE_DIR}/src/main.cpp"
#        "${PROJECT_SOURCE_DIR}/src/engine/renderer/WebRenderer.hpp"
#        "${PROJECT_SOURCE_DIR}/src/engine/renderer/WebRenderer.cpp"
#        "${PROJECT_SOURCE_DIR}/src/engine/include/stb_image.h"
#        "${PROJECT_SOURCE_DIR}/src/engine/include/entt.hpp"
#        "${PROJECT_SOURCE_DIR}/src/engine/renderer/Shader.h"
#        "${PROJECT_SOURCE_DIR}/src/engine/renderer/Shader.cpp"
#        "${PROJECT_SOURCE_DIR}/src/engine/component/Component.h"
#        "${PROJECT_SOURCE_DIR}/src/engine/renderer/Renderer.cpp"
#        "${PROJECT_SOURCE_DIR}/src/engine/renderer/Renderer.h"
#        "${PROJECT_SOURCE_DIR}/src/engine/scene/Scene.cpp"
#        "${PROJECT_SOURCE_DIR}/src/engine/scene/Scene.h"
#        "${PROJECT_SOURCE_DIR}/src/engine/scene/Entity.cpp"
#        "${PROJECT_SOURCE_DIR}/src/engine/scene/Entity.h"
#        "${PROJECT_SOURCE_DIR}/src/engine/Logger.cpp"
#        "${PROJECT_SOURCE_DIR}/src/engine/Logger.h"
    )

    add_executable(Release ${SOURCE_FILES_EXEC})

    if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
        set_target_properties(Release PROPERTIES LINK_FLAGS "-s USE_WEBGL2=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s FULL_ES3=1 -s USE_GLFW=3")

        #        set_target_properties(Release PROPERTIES LINK_FLAGS "-s USE_WEBGL2=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s FULL_ES3=1 -s USE_GLFW=3")
    endif ()

    set_property(TARGET Release PROPERTY CXX_STANDARD 17)
    set_property(TARGET Release PROPERTY CXX_STANDARD_REQUIRED ON)
else()
    # build as a node gui plugin
    add_compile_definitions(INCLUDE_DEEPS_ENGINE_LIBRARY)

    set(SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/src/main.cpp"
        "${PROJECT_SOURCE_DIR}/src/linmath.h"
        "${PROJECT_SOURCE_DIR}/src/engine/include/stb_image.h"
        "${PROJECT_SOURCE_DIR}/src/engine/include/entt.hpp"
        "${PROJECT_SOURCE_DIR}/src/engine/renderer/Shader.h"
        "${PROJECT_SOURCE_DIR}/src/engine/renderer/Shader.cpp"
        "${PROJECT_SOURCE_DIR}/src/engine/component/Component.h"
        "${PROJECT_SOURCE_DIR}/src/editor/mainwindow.cpp"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/OpenGLWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/OpenGLWidget.cpp"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/SceneViewWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/SceneViewWidget.cpp"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/InspectorWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/InspectorWidget.cpp"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/ConsoleWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/ConsoleWidget.cpp"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/component/TransformComponentWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/component/TransformComponentWidget.cpp"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/component/TagComponentWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/component/TagComponentWidget.cpp"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/component/MeshFilterComponentWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/component/MeshFilterComponentWidget.cpp"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/component/CameraComponentWidget.h"
        "${PROJECT_SOURCE_DIR}/src/editor/widget/component/CameraComponentWidget.cpp"
        "${PROJECT_SOURCE_DIR}/src/engine/renderer/Renderer.cpp"
        "${PROJECT_SOURCE_DIR}/src/engine/renderer/Renderer.h"
        "${PROJECT_SOURCE_DIR}/src/engine/scene/Scene.cpp"
        "${PROJECT_SOURCE_DIR}/src/engine/scene/Scene.h"
        "${PROJECT_SOURCE_DIR}/src/engine/scene/Entity.cpp"
        "${PROJECT_SOURCE_DIR}/src/engine/scene/Entity.h"
        "${PROJECT_SOURCE_DIR}/src/engine/Logger.cpp"
        "${PROJECT_SOURCE_DIR}/src/engine/Logger.h"
    )

    add_project_meta(META_FILES_TO_INCLUDE)

    set(RESOURCE_FILES src/editor/example.qrc)

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
