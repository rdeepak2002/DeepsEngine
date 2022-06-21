cmake_minimum_required(VERSION 3.22)
project(native)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/sys/include)

FILE(GLOB PROJECT_SOURCE_FILES
        src/*.cpp)

add_library(native SHARED ${PROJECT_SOURCE_FILES})
