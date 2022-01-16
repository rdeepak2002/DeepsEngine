cmake_minimum_required(VERSION 3.1)

# -------------- User Config ---------------
set(PLUGIN_ADDON_NAME "OpenGLCube")
project(${PLUGIN_ADDON_NAME})

# specify x86_64 to use Rosetta on M1 Mac
if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
endif()

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

# specify whether this should run as a standalone or build as a node gui plugin
if(DEFINED ENV{STANDALONE})
    message(STATUS "running engine in standalone mode")
    set(RUN_STANDALONE TRUE)
else()
    message(STATUS "building engine as compiled library")
    set(RUN_STANDALONE FALSE)
endif()

if (RUN_STANDALONE)
    # standalone engine
    add_compile_definitions(STANDALONE)

    file(GLOB SOURCE_FILES_EXEC
        "${PROJECT_SOURCE_DIR}/src/Engine/glad.c"
        "${PROJECT_SOURCE_DIR}/src/Engine/main.cpp"
        "${PROJECT_SOURCE_DIR}/src/Engine/OpenGLRenderer.h"
        "${PROJECT_SOURCE_DIR}/src/Engine/OpenGLRenderer.cpp"
        "${PROJECT_SOURCE_DIR}/src/Engine/Shader.h"
        "${PROJECT_SOURCE_DIR}/src/Engine/Shader.cpp"
    )

    add_executable(Release ${SOURCE_FILES_EXEC})
else ()
    # build as a node gui plugin
    add_compile_definitions(INCLUDE_DEEPS_ENGINE_LIBRARY)

    # get node gui plugin commands
    execute_process(COMMAND node -p "require('@nodegui/nodegui/plugin').CMAKE_HELPER_FILE"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODEGUI_PLUGIN_CMAKE_HELPER
    )
    string(REPLACE "\n" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})
    string(REPLACE "\"" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})
    include("${NODEGUI_PLUGIN_CMAKE_HELPER}")

    add_library(${PLUGIN_ADDON_NAME} SHARED
        "${CMAKE_JS_SRC}"
        "${PROJECT_SOURCE_DIR}/src/QtRenderer/index.cpp"
        "${PROJECT_SOURCE_DIR}/src/QtRenderer/OpenGLWidget.cpp"
        "${PROJECT_SOURCE_DIR}/src/QtRenderer/OpenGLNapiWrapper.cpp"
        "${PROJECT_SOURCE_DIR}/src/QtRenderer/OpenGLNodeGuiWidget.h"
        "${PROJECT_SOURCE_DIR}/src/Engine/OpenGLRenderer.h"
        "${PROJECT_SOURCE_DIR}/src/Engine/OpenGLRenderer.cpp"
            "${PROJECT_SOURCE_DIR}/src/Engine/Shader.h"
            "${PROJECT_SOURCE_DIR}/src/Engine/Shader.cpp"
    )

    AddPluginConfig(${PLUGIN_ADDON_NAME})

    target_include_directories(${PLUGIN_ADDON_NAME} PRIVATE
        if (APPLE)
            ${PROJECT_NAME} /usr/local/include/node
        endif ()
        "${CMAKE_JS_INC}"
        "${PROJECT_SOURCE_DIR}"
    )

    target_link_libraries(${PLUGIN_ADDON_NAME} PRIVATE
        "${CMAKE_JS_LIB}"
    )
endif ()