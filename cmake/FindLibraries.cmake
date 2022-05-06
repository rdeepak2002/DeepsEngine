macro(FIND_DEEPS_ENGINE_LIBRARIES)
    # find packages
    if (NOT EMSCRIPTEN)
        find_package(OpenGL REQUIRED)

        if(NOT OPENGL_FOUND)
            message(FATAL_ERROR "OpenGL not found")
        endif()

        find_package(glfw3 CONFIG REQUIRED)
    endif()

    # get OPENGL include path and libraries
    message(STATUS "OPENGL_INCLUDE_DIRS = ${OPENGL_INCLUDE_DIRS}")
    include_directories(${OPENGL_INCLUDE_DIRS})
    message(STATUS "OPENGL_LIBRARIES = ${OPENGL_LIBRARIES}")
    link_libraries(${OPENGL_LIBRARIES})

    find_package(Lua REQUIRED)

    if (NOT LUA_FOUND)
        message(FATAL_ERROR "LUA not found")
    endif()

    # get LUA path use macro to get around differing versions
    message(STATUS "LUA_INCLUDE_DIR ${LUA_INCLUDE_DIR}")
    include_directories(${LUA_INCLUDE_DIR})
    message(STATUS "LUA_LIBRARIES ${LUA_LIBRARIES}")
    link_libraries(${LUA_LIBRARIES})
endmacro()
