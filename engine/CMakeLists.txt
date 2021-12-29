cmake_minimum_required(VERSION 3.20)
# Name of the project (will be the name of the plugin)
project(core)
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
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H} ${KH_H} ${OpenCV_INCLUDE_DIRS} ${GLM})

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
    file(GLOB SOURCE_FILES_EXEC "src/main.cpp" "src/stb_image.h" "src/stb_image_write.h" "src/glad.c" "src/Renderer.h" "src/Renderer.cpp" "src/Shader.h" "src/Component.h" "src/Component.cpp" "src/ComponentSystem.h" "src/ComponentSystem.cpp" "src/uuid.h" "src/uuid.cpp")
    add_executable(engine_standalone ${SOURCE_FILES_EXEC})
else ()
    # library
    # Essential include files to build a node addon,
    # you should add this line in every CMake.js based project.
    include_directories(${CMAKE_JS_INC})
    # Declare the location of the source files
    file(GLOB SOURCE_FILES "src/glad.c" "src/stb_image.h" "src/stb_image_write.h" "src/Renderer.h" "src/Renderer.cpp" "EditorBinding/exportbindings.cpp" "EditorBinding/bindings.cpp" "EditorBinding/bindings.h" "src/Shader.h"  "src/Component.h" "src/Component.cpp" "src/ComponentSystem.h" "src/ComponentSystem.cpp" "src/uuid.h" "src/uuid.cpp")

    # This line will tell CMake that we're building a shared library from the above source files
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
            ${CMAKE_SOURCE_DIR}/../editornative/node_modules/node-addon-api
            ${CMAKE_SOURCE_DIR}/../editornative/node_modules/node-addon-api/src
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
endif ()