cmake_minimum_required(VERSION 3.22)
project(native)

set(CMAKE_CXX_STANDARD 17)

if (EMSCRIPTEN)
    add_executable(native NativeScriptComponent.hpp SpinningEntity.cpp)
else()
    add_library(native SHARED NativeScriptComponent.hpp SpinningEntity.cpp)
endif()