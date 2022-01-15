cmake_minimum_required(VERSION 3.1)

set(CMAKE_OSX_ARCHITECTURES "x86_64")

# -------------- Plugin Config ---------------
execute_process(COMMAND node -p "require('@nodegui/nodegui/plugin').CMAKE_HELPER_FILE"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE NODEGUI_PLUGIN_CMAKE_HELPER
)
string(REPLACE "\n" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})
string(REPLACE "\"" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})
include("${NODEGUI_PLUGIN_CMAKE_HELPER}")

set(GLEW_H /usr/local/include/gl)
set(GLFW_H /usr/local/include/glfw)
set(GLM /usr/local/include/glm)
set(GLAD_H /usr/local/include/glad)
set(KH_H /usr/local/include/KHR)
set(RAPID_JSON /usr/local/include/rapidjson)
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H} ${KH_H} ${OpenCV_INCLUDE_DIRS} ${GLM} ${RAPID_JSON})

# -------------- User Config ---------------
set(PLUGIN_ADDON_NAME "OpenGLCube")
set(CMAKE_OSX_ARCHITECTURES "x86_64")

project(${PLUGIN_ADDON_NAME})

add_compile_definitions(INCLUDE_DEEPS_ENGINE_LIBRARY)

add_library(${PLUGIN_ADDON_NAME} SHARED
    "src/Engine/glad.c"
    "${CMAKE_JS_SRC}"
    "${PROJECT_SOURCE_DIR}/src/Engine/index.cpp"
    "${PROJECT_SOURCE_DIR}/src/Engine/OpenGLWidget.cpp"
    "${PROJECT_SOURCE_DIR}/src/Engine/OpenGLNapiWrapper.cpp"
    "${PROJECT_SOURCE_DIR}/src/Engine/OpenGLNodeGuiWidget.h"
    "${PROJECT_SOURCE_DIR}/src/Engine/OpenGLRenderer.h"
    "${PROJECT_SOURCE_DIR}/src/Engine/OpenGLRenderer.cpp"
)

AddPluginConfig(${PLUGIN_ADDON_NAME})

target_include_directories(${PLUGIN_ADDON_NAME} PRIVATE
    if (APPLE)
        ${PROJECT_NAME} /usr/local/include/node
    endif ()
    "${CMAKE_JS_INC}"
    "${PROJECT_SOURCE_DIR}"
)

file(GLOB LIBRARIES "${PROJECT_SOURCE_DIR}/src/Engine/*.dylib")
message("LIBRARIES = ${LIBRARIES}")

target_link_libraries(${PLUGIN_ADDON_NAME} PRIVATE
    "${CMAKE_JS_LIB}"
    ${LIBRARIES}
)
