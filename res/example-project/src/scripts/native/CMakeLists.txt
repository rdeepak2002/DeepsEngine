cmake_minimum_required(VERSION 3.22)
project(native)

set(CMAKE_CXX_STANDARD 17)

set(WITH_EDITOR FALSE)
add_compile_definitions(STANDALONE)

include_directories(${PROJECT_SOURCE_DIR}/src/include)
#include_directories(${PROJECT_SOURCE_DIR}/sys/include)
#include_directories(${PROJECT_SOURCE_DIR}/sys/external/lua-5.4.4)
include_directories(../../../sys/DeepsEngine/include)
include_directories(../../../sys/DeepsEngine/external/lua-5.4.4)
include_directories(../../../sys/DeepsEngine/external/bullet-2.82/src)

FILE(GLOB PROJECT_SOURCE_FILES
        src/*.cpp)

add_library(native SHARED ${PROJECT_SOURCE_FILES})

target_link_libraries(native "-undefined dynamic_lookup")
