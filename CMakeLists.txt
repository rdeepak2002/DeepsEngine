cmake_minimum_required(VERSION 3.16)

if (EMSCRIPTEN)
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

# Basic information about project
project(DeepsEngine VERSION 1.0)

#if (APPLE)
#    set(CMAKE_OSX_ARCHITECTURES "x86_64")
#endif()

# Set additional project information
set(COMPANY "DeepDev")
set(COPYRIGHT "Copyright (c) 2022 Deepak Ramalingam. All rights reserved.")
set(IDENTIFIER "com.DeepDev.DeepsEngineEditor")

# find opengl package
if (NOT EMSCRIPTEN)
    find_package(OpenGL REQUIRED)

    if(OPENGL_FOUND)
        message("OPENGL_LIBRARIES = ${OPENGL_LIBRARIES} ")
        message("OPENGL_INCLUDE_DIRS = ${OPENGL_INCLUDE_DIRS} ")
    else( OPENGL_FOUND )
        message(FATAL_ERROR "OpenGL not found")
    endif( OPENGL_FOUND )
endif()

EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
message( STATUS "Architecture: ${ARCHITECTURE}" )

#find_package(glfw3 REQUIRED)
#
#if(GLFW_FOUND) # Works with some other methods
#    message(STATUS "GLFW3_INCLUDE_PATH=${GLFW3_INCLUDE_PATH}")
#    message(STATUS "GLFW_LIBRARIES=${GLFW_LIBRARIES}")
#else( GLFW_FOUND )
#    message(FATAL_ERROR "GLFW3 not found")
#endif( GLFW_FOUND )

#find_package(Lua REQUIRED)
#
#message(STATUS "LUA_INCLUDE_DIR=${LUA_INCLUDE_DIR}")
#message(STATUS "LUA_LIBRARIES=${LUA_LIBRARIES}")

# macro to return full path of first folder in a directory
MACRO(GETFIRSTDIR result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
            BREAK()
        ENDIF()
    ENDFOREACH()
    SET(${result} ${curdir}${dirlist})
ENDMACRO()

# get GLFW path use macro to get around differing versions
GETFIRSTDIR(GLFW_H_PATH /opt/homebrew/Cellar/glfw/)
message(${GLFW_H_PATH})

# get GLEW path use macro to get around differing versions
GETFIRSTDIR(GLEW_H_PATH /opt/homebrew/Cellar/glew/)
message(${GLEW_H_PATH})

# get LUA path use macro to get around differing versions
GETFIRSTDIR(LUA_PATH /opt/homebrew/Cellar/lua/)
message(${LUA_PATH})

# get include directories for libraries used
set(GLEW_H ${GLEW_H_PATH}/include/GL)
set(GLFW_H ${GLFW_H_PATH}/include/GLFW)
set(LUA_INCLUDE_DIR ${LUA_PATH}/include/lua)
set(GLM_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/engine/include/glm)
set(GLAD_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/engine/include/glad/include)
set(SOL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/engine/include/sol2/include)
set(ENTT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/engine/include/entt/single_include)
set(STB_IMAGE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/engine/include/stb)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_H} ${GLFW_H} ${GLAD_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${LUA_INCLUDE_DIR} ${SOL_INCLUDE_DIR} ${ENTT_INCLUDE_DIR} ${STB_IMAGE_INCLUDE_DIR})

# link libraries used
set(GLEW_LINK ${GLEW_H_PATH}/lib/libGLEW.dylib)
set(GLFW_LINK ${GLFW_H_PATH}/lib/libglfw.dylib)
set(LUA_LIBRARY ${LUA_PATH}/lib/liblua.dylib)
link_libraries(${OPENGL_LIBRARIES} ${OPENGL} ${GLEW_LINK} ${GLFW_LINK} ${LUA_LIBRARY})

set(ENGINE_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/src/main.cpp"
        "${PROJECT_SOURCE_DIR}/src/engine/include/glad/src/glad.c"
        "${PROJECT_SOURCE_DIR}/src/engine/renderer/Shader.h"
        "${PROJECT_SOURCE_DIR}/src/engine/renderer/Shader.cpp"
        "${PROJECT_SOURCE_DIR}/src/engine/component/Component.h"
        "${PROJECT_SOURCE_DIR}/src/engine/renderer/Renderer.cpp"
        "${PROJECT_SOURCE_DIR}/src/engine/renderer/Renderer.h"
        "${PROJECT_SOURCE_DIR}/src/engine/Application.cpp"
        "${PROJECT_SOURCE_DIR}/src/engine/Application.h"
        "${PROJECT_SOURCE_DIR}/src/engine/scene/Scene.cpp"
        "${PROJECT_SOURCE_DIR}/src/engine/scene/Scene.h"
        "${PROJECT_SOURCE_DIR}/src/engine/scene/Entity.cpp"
        "${PROJECT_SOURCE_DIR}/src/engine/scene/Entity.h"
        "${PROJECT_SOURCE_DIR}/src/engine/util/Logger.cpp"
        "${PROJECT_SOURCE_DIR}/src/engine/util/Logger.h"
        "${PROJECT_SOURCE_DIR}/src/engine/util/LoggerCallbackInterface.h"
        "${PROJECT_SOURCE_DIR}/src/engine/component/ComponentSystem.h"
        "${PROJECT_SOURCE_DIR}/src/engine/component/LuaScriptComponentSystem.cpp"
        "${PROJECT_SOURCE_DIR}/src/engine/component/LuaScriptComponentSystem.h"
        "${PROJECT_SOURCE_DIR}/src/engine/Input.cpp"
        "${PROJECT_SOURCE_DIR}/src/engine/Input.h"
        "${PROJECT_SOURCE_DIR}/src/engine/util/KeyCodes.h"
        )

if(RUN_STANDALONE)
    # standalone engine
    add_compile_definitions(STANDALONE)

    file(GLOB SOURCE_FILES_EXEC
        ${ENGINE_SOURCE_FILES}
    )

    add_executable(${PROJECT_NAME} ${SOURCE_FILES_EXEC})

    if (EMSCRIPTEN)
        file(COPY res DESTINATION "${PROJECT_SOURCE_DIR}/src/build/web/src/assets")
        FILE(GLOB LUA_WEB_BUILD_DIRECTORY "${PROJECT_SOURCE_DIR}/src/build/web/lua-*/src")
        message(STATUS ${LUA_WEB_BUILD_DIRECTORY})
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "--use-preload-plugins \
        -L${LUA_WEB_BUILD_DIRECTORY} \
         -s LLD_REPORT_UNDEFINED \
         -s EXPORTED_FUNCTIONS=['_main','_onResizeWindow'] \
         -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap'] \
         -s ALLOW_MEMORY_GROWTH=1 -s USE_WEBGL2=1 \
         -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 \
         -s FULL_ES3=1 \
         -s USE_GLFW=3 \
         --preload-file assets")
    else()
        file(COPY res DESTINATION assets)
    endif ()

    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
else()
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
    )

    add_project_meta(META_FILES_TO_INCLUDE)

    set(RESOURCE_FILES src/editor/example.qrc)

    find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)

    # source_group("UI Files" FILES ${UI_FILES})

    add_executable(${PROJECT_NAME} ${OS_BUNDLE} ${EDITOR_SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES})

    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

    target_precompile_headers(${PROJECT_NAME} INTERFACE QtWidgets.h)

    target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::OpenGL)
endif()
