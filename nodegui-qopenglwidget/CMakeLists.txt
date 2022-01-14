cmake_minimum_required(VERSION 3.1)

if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
endif()

# -------------- Plugin Config ---------------
execute_process(COMMAND node -p "require('@nodegui/nodegui/plugin').CMAKE_HELPER_FILE"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE NODEGUI_PLUGIN_CMAKE_HELPER
)
string(REPLACE "\n" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})
string(REPLACE "\"" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})
include("${NODEGUI_PLUGIN_CMAKE_HELPER}")

# -------------- User Config ---------------
set(PLUGIN_ADDON_NAME "OpenGLCube")

project(${PLUGIN_ADDON_NAME})

add_library(${PLUGIN_ADDON_NAME} SHARED
    "${CMAKE_JS_SRC}"
    "${PROJECT_SOURCE_DIR}/src/Native/index.cpp"
    "${PROJECT_SOURCE_DIR}/src/OpenGLCube/Native/OpenGLCubeWidget.cpp"
    "${PROJECT_SOURCE_DIR}/src/OpenGLCube/Native/OpenGLCubeNapiWrapper.cpp"
    "${PROJECT_SOURCE_DIR}/src/OpenGLCube/Native/OpenGLCubeNodeGuiWidget.h"
)

AddPluginConfig(${PLUGIN_ADDON_NAME})

target_include_directories(${PLUGIN_ADDON_NAME} PRIVATE
    "${CMAKE_JS_INC}"
    "${PROJECT_SOURCE_DIR}"
)
target_link_libraries(${PLUGIN_ADDON_NAME} PRIVATE
    "${CMAKE_JS_LIB}"
)
