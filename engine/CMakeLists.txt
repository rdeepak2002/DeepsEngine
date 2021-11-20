cmake_minimum_required(VERSION 3.20)
# Name of the project (will be the name of the plugin)
project(addon)
set(CMAKE_CXX_STANDARD 14)
# Don't add this line if you will try_compile with boost.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3.4/include/GLFW)
set(GLAD_H /usr/local/include/glad)
set(KH_H /usr/local/include/KHR)
set(stb /usr/local/include/stb)
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H} ${KH_H} ${stb})

# Add target link
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.4/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

# Essential include files to build a node addon,
# you should add this line in every CMake.js based project.
include_directories(${CMAKE_JS_INC} /usr/local/include/node/node_api.h)
# Declare the location of the source files
file(GLOB SOURCE_FILES "src/glad.c" "main.cpp" "Samples/functionexample.cpp" "Samples/functionexample.h" "Samples/Renderer.cpp" "Samples/Renderer.h")
# This line will tell CMake that we're building a shared library
# from the above source files
# named after the project's name
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
# This line will give our library file a .node extension without any "lib" prefix
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
# Essential library files to link to a node addon,
# you should add this line in every CMake.js based project.
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
target_include_directories(${PROJECT_NAME} PRIVATE
        if (APPLE)
            ${PROJECT_NAME} /usr/local/include/node
        endif ()
        ${CMAKE_SOURCE_DIR}/../editor/node_modules/node-addon-api
        ${CMAKE_SOURCE_DIR}/../editor/node_modules/node-addon-api/src
        ${CMAKE_JS_INC})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_JS_LIB})

add_definitions(-DNAPI_VERSION=3)

# Execute compile command
# This glad.c said in step 2 that it should be pulled into the project. Pay attention to the path
# note: in order to make this work, do not make this executable run napi stuff
# add_executable(engine_standalone ${SOURCE_FILES})

# mac, it's important to take this step
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
    target_link_libraries(${PROJECT_NAME} "-framework GLUT")
endif ()
