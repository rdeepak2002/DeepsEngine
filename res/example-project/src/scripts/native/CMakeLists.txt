cmake_minimum_required(VERSION 3.22)
project(native)

set(CMAKE_CXX_STANDARD 17)

if (EMSCRIPTEN)
#    add_library(native SHARED NativeScriptComponent.h SpinningEntity.cpp)
    add_executable(native NativeScriptComponent.h SpinningEntity.cpp)
#    set_target_properties(native PROPERTIES LINK_FLAGS "-shared")
#    set_target_properties(native PROPERTIES LINK_FLAGS " ---use-preload-plugins -shared")
else()
    add_library(native SHARED NativeScriptComponent.h SpinningEntity.cpp)
endif()