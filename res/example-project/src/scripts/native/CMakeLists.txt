cmake_minimum_required(VERSION 3.22)
project(native)

set(CMAKE_CXX_STANDARD 17)

set(WITH_EDITOR FALSE)
add_compile_definitions(STANDALONE)

if (NOT EMSCRIPTEN)
    find_package(OpenGL REQUIRED)

    if(NOT OPENGL_FOUND)
        message(FATAL_ERROR "OpenGL not found")
    endif()

    find_package(glfw3 CONFIG REQUIRED)
endif()


include_directories(${OPENGL_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/sys/include)
include_directories(${PROJECT_SOURCE_DIR}/sys/lua-5.4.4/src)
link_libraries(${PROJECT_SOURCE_DIR}/sys/lib/libDeepsEngine.dylib)

FILE(GLOB PROJECT_SOURCE_FILES
        src/*.cpp)

add_library(native SHARED ${PROJECT_SOURCE_FILES})

target_link_libraries(native glfw)
