cmake_minimum_required(VERSION 3.22)
project(native)

set(CMAKE_CXX_STANDARD 17)

set(WITH_EDITOR FALSE)
add_compile_definitions(STANDALONE)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/sys/include)
include_directories(${PROJECT_SOURCE_DIR}/sys/lua-5.4.4/src)
link_libraries(${PROJECT_SOURCE_DIR}/sys/lib/libDeepsEngine.dylib)

FILE(GLOB PROJECT_SOURCE_FILES
        src/*.cpp)

add_library(native SHARED ${PROJECT_SOURCE_FILES})
