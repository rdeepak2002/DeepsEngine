cmake_minimum_required(VERSION 3.20)
project(deeps_engine)

set(CMAKE_CXX_STANDARD 14)

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

# Execute compile command
# This glad.c said in step 2 that it should be pulled into the project. Pay attention to the path
set(SOURCE_FILES "src/glad.c" "main.cpp")
add_executable(deeps_engine ${SOURCE_FILES})

# mac, it's important to take this step
if (APPLE)
    target_link_libraries(deeps_engine "-framework OpenGL")
    target_link_libraries(deeps_engine "-framework GLUT")
endif()