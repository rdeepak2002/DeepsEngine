cmake_minimum_required(VERSION 3.22)
project(DeepsEngine)

set(CMAKE_CXX_STANDARD 17)

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/DeepsEngine/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include(DeepsEngineSetup)

# load third party libraries
DEEPS_ENGINE_SETUP()

include_directories(${PROJECT_SOURCE_DIR}/DeepsEngine/include)
link_libraries(${PROJECT_SOURCE_DIR}/DeepsEngine/lib/web/libDeepsEngine.a)
add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS " \
        --use-preload-plugins \
        -s LLD_REPORT_UNDEFINED \
        -s EXPORTED_FUNCTIONS=['_main','_onResizeWindow'] \
        -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap'] \
        -s ALLOW_MEMORY_GROWTH=1 -s USE_WEBGL2=1 \
        -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 \
        -s FULL_ES3=1 \
        -s USE_GLFW=3 \
        --preload-file assets")