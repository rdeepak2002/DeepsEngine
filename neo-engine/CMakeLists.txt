cmake_minimum_required(VERSION 3.20)
# Name of the project (will be the name of the plugin)
project(neo_engine)
set(CMAKE_CXX_STANDARD 14)
# Don't add this line if you will try_compile with boost.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
endif()

# using M1 Chip to run engine (NAPI not supported): -DCMAKE_APPLE_SILICON_PROCESSOR=arm64
# message(STATUS ${CMAKE_APPLE_SILICON_PROCESSOR})

set(OpenCV_DIR /usr/local/include/opencv4)
find_package( OpenCV REQUIRED )

set(GLEW_H /usr/local/include/gl)
set(GLFW_H /usr/local/include/glfw)
set(GLM /usr/local/include/glm)
set(GLAD_H /usr/local/include/glad)
set(KH_H /usr/local/include/KHR)
set(RAPID_JSON /usr/local/include/rapidjson)
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H} ${KH_H} ${OpenCV_INCLUDE_DIRS} ${GLM} ${RAPID_JSON})

# Add target link
set(GLEW_LINK /usr/local/lib/libGLEW.dylib)
set(GLFW_LINK /usr/local/lib/libglfw.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK} ${OpenCV_LIBS})

# specify whether this should run as a standalone or library
if(DEFINED ENV{STANDALONE})
    message(STATUS "running engine in standalone mode")
    set(RUN_STANDALONE TRUE)
else()
    message(STATUS "building engine as compiled library")
    set(RUN_STANDALONE FALSE)
endif()

# standalone engine
if (RUN_STANDALONE)
    add_compile_definitions(STANDALONE)
    file(GLOB SOURCE_FILES_EXEC "src/main.cpp" "src/glad.c" "src/OpenGLRenderer.h" "src/OpenGLRenderer.cpp")
    add_executable(engine_standalone ${SOURCE_FILES_EXEC})
else ()
    file(GLOB SOURCE_FILES "src/glad.c" "src/OpenGLRenderer.h" "src/OpenGLRenderer.cpp")
    add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
endif ()