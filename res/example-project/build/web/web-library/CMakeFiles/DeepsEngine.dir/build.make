# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.23.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.23.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/deepakramalingam/Documents/Projects/DeepsEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library

# Include any dependencies generated for this target.
include CMakeFiles/DeepsEngine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DeepsEngine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DeepsEngine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DeepsEngine.dir/flags.make

CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.o: CMakeFiles/DeepsEngine.dir/flags.make
CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.o: CMakeFiles/DeepsEngine.dir/includes_CXX.rsp
CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.o: ../../../../../src/engine/Application.cpp
CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.o: CMakeFiles/DeepsEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.o"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.o -MF CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.o.d -o CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.o -c /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/Application.cpp

CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.i"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/Application.cpp > CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.i

CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.s"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/Application.cpp -o CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.s

CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.o: CMakeFiles/DeepsEngine.dir/flags.make
CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.o: CMakeFiles/DeepsEngine.dir/includes_CXX.rsp
CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.o: ../../../../../src/engine/Input.cpp
CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.o: CMakeFiles/DeepsEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.o"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.o -MF CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.o.d -o CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.o -c /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/Input.cpp

CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.i"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/Input.cpp > CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.i

CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.s"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/Input.cpp -o CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.s

CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.o: CMakeFiles/DeepsEngine.dir/flags.make
CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.o: CMakeFiles/DeepsEngine.dir/includes_CXX.rsp
CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.o: ../../../../../src/engine/component/LuaScriptComponentSystem.cpp
CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.o: CMakeFiles/DeepsEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.o"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.o -MF CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.o.d -o CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.o -c /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/component/LuaScriptComponentSystem.cpp

CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.i"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/component/LuaScriptComponentSystem.cpp > CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.i

CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.s"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/component/LuaScriptComponentSystem.cpp -o CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.s

CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.o: CMakeFiles/DeepsEngine.dir/flags.make
CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.o: CMakeFiles/DeepsEngine.dir/includes_CXX.rsp
CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.o: ../../../../../src/engine/renderer/Renderer.cpp
CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.o: CMakeFiles/DeepsEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.o"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.o -MF CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.o.d -o CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.o -c /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/renderer/Renderer.cpp

CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.i"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/renderer/Renderer.cpp > CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.i

CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.s"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/renderer/Renderer.cpp -o CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.s

CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.o: CMakeFiles/DeepsEngine.dir/flags.make
CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.o: CMakeFiles/DeepsEngine.dir/includes_CXX.rsp
CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.o: ../../../../../src/engine/renderer/Shader.cpp
CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.o: CMakeFiles/DeepsEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.o"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.o -MF CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.o.d -o CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.o -c /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/renderer/Shader.cpp

CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.i"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/renderer/Shader.cpp > CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.i

CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.s"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/renderer/Shader.cpp -o CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.s

CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.o: CMakeFiles/DeepsEngine.dir/flags.make
CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.o: CMakeFiles/DeepsEngine.dir/includes_C.rsp
CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.o: ../../../../../src/engine/renderer/glad.c
CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.o: CMakeFiles/DeepsEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.o"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.o -MF CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.o.d -o CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.o -c /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/renderer/glad.c

CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.i"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/renderer/glad.c > CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.i

CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.s"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/renderer/glad.c -o CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.s

CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.o: CMakeFiles/DeepsEngine.dir/flags.make
CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.o: CMakeFiles/DeepsEngine.dir/includes_CXX.rsp
CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.o: ../../../../../src/engine/scene/Entity.cpp
CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.o: CMakeFiles/DeepsEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.o"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.o -MF CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.o.d -o CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.o -c /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/scene/Entity.cpp

CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.i"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/scene/Entity.cpp > CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.i

CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.s"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/scene/Entity.cpp -o CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.s

CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.o: CMakeFiles/DeepsEngine.dir/flags.make
CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.o: CMakeFiles/DeepsEngine.dir/includes_CXX.rsp
CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.o: ../../../../../src/engine/scene/Scene.cpp
CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.o: CMakeFiles/DeepsEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.o"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.o -MF CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.o.d -o CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.o -c /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/scene/Scene.cpp

CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.i"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/scene/Scene.cpp > CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.i

CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.s"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/scene/Scene.cpp -o CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.s

CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.o: CMakeFiles/DeepsEngine.dir/flags.make
CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.o: CMakeFiles/DeepsEngine.dir/includes_CXX.rsp
CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.o: ../../../../../src/engine/util/DeepsMath.cpp
CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.o: CMakeFiles/DeepsEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.o"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.o -MF CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.o.d -o CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.o -c /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/util/DeepsMath.cpp

CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.i"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/util/DeepsMath.cpp > CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.i

CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.s"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/util/DeepsMath.cpp -o CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.s

CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.o: CMakeFiles/DeepsEngine.dir/flags.make
CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.o: CMakeFiles/DeepsEngine.dir/includes_CXX.rsp
CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.o: ../../../../../src/engine/util/Logger.cpp
CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.o: CMakeFiles/DeepsEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.o"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.o -MF CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.o.d -o CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.o -c /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/util/Logger.cpp

CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.i"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/util/Logger.cpp > CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.i

CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.s"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/util/Logger.cpp -o CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.s

CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.o: CMakeFiles/DeepsEngine.dir/flags.make
CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.o: CMakeFiles/DeepsEngine.dir/includes_CXX.rsp
CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.o: ../../../../../src/engine/window/GLFWWindow.cpp
CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.o: CMakeFiles/DeepsEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.o"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.o -MF CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.o.d -o CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.o -c /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/window/GLFWWindow.cpp

CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.i"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/window/GLFWWindow.cpp > CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.i

CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.s"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/window/GLFWWindow.cpp -o CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.s

CMakeFiles/DeepsEngine.dir/src/main.cpp.o: CMakeFiles/DeepsEngine.dir/flags.make
CMakeFiles/DeepsEngine.dir/src/main.cpp.o: CMakeFiles/DeepsEngine.dir/includes_CXX.rsp
CMakeFiles/DeepsEngine.dir/src/main.cpp.o: ../../../../../src/main.cpp
CMakeFiles/DeepsEngine.dir/src/main.cpp.o: CMakeFiles/DeepsEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/DeepsEngine.dir/src/main.cpp.o"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeepsEngine.dir/src/main.cpp.o -MF CMakeFiles/DeepsEngine.dir/src/main.cpp.o.d -o CMakeFiles/DeepsEngine.dir/src/main.cpp.o -c /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/main.cpp

CMakeFiles/DeepsEngine.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeepsEngine.dir/src/main.cpp.i"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/main.cpp > CMakeFiles/DeepsEngine.dir/src/main.cpp.i

CMakeFiles/DeepsEngine.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeepsEngine.dir/src/main.cpp.s"
	/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/main.cpp -o CMakeFiles/DeepsEngine.dir/src/main.cpp.s

# Object files for target DeepsEngine
DeepsEngine_OBJECTS = \
"CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.o" \
"CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.o" \
"CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.o" \
"CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.o" \
"CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.o" \
"CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.o" \
"CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.o" \
"CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.o" \
"CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.o" \
"CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.o" \
"CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.o" \
"CMakeFiles/DeepsEngine.dir/src/main.cpp.o"

# External object files for target DeepsEngine
DeepsEngine_EXTERNAL_OBJECTS =

libDeepsEngine.a: CMakeFiles/DeepsEngine.dir/src/engine/Application.cpp.o
libDeepsEngine.a: CMakeFiles/DeepsEngine.dir/src/engine/Input.cpp.o
libDeepsEngine.a: CMakeFiles/DeepsEngine.dir/src/engine/component/LuaScriptComponentSystem.cpp.o
libDeepsEngine.a: CMakeFiles/DeepsEngine.dir/src/engine/renderer/Renderer.cpp.o
libDeepsEngine.a: CMakeFiles/DeepsEngine.dir/src/engine/renderer/Shader.cpp.o
libDeepsEngine.a: CMakeFiles/DeepsEngine.dir/src/engine/renderer/glad.c.o
libDeepsEngine.a: CMakeFiles/DeepsEngine.dir/src/engine/scene/Entity.cpp.o
libDeepsEngine.a: CMakeFiles/DeepsEngine.dir/src/engine/scene/Scene.cpp.o
libDeepsEngine.a: CMakeFiles/DeepsEngine.dir/src/engine/util/DeepsMath.cpp.o
libDeepsEngine.a: CMakeFiles/DeepsEngine.dir/src/engine/util/Logger.cpp.o
libDeepsEngine.a: CMakeFiles/DeepsEngine.dir/src/engine/window/GLFWWindow.cpp.o
libDeepsEngine.a: CMakeFiles/DeepsEngine.dir/src/main.cpp.o
libDeepsEngine.a: CMakeFiles/DeepsEngine.dir/build.make
libDeepsEngine.a: CMakeFiles/DeepsEngine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX static library libDeepsEngine.a"
	$(CMAKE_COMMAND) -P CMakeFiles/DeepsEngine.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DeepsEngine.dir/link.txt --verbose=$(VERBOSE)
	/opt/homebrew/Cellar/cmake/3.23.1/bin/cmake -E copy_directory /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/include /Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/DeepsEngine/include
	/opt/homebrew/Cellar/cmake/3.23.1/bin/cmake -E copy_directory /Users/deepakramalingam/Documents/Projects/DeepsEngine/src/engine/lib /Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/DeepsEngine/lib
	/opt/homebrew/Cellar/cmake/3.23.1/bin/cmake -E copy_directory /Users/deepakramalingam/Documents/Projects/DeepsEngine/cmake /Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/DeepsEngine/cmake

# Rule to build all files generated by this target.
CMakeFiles/DeepsEngine.dir/build: libDeepsEngine.a
.PHONY : CMakeFiles/DeepsEngine.dir/build

CMakeFiles/DeepsEngine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DeepsEngine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DeepsEngine.dir/clean

CMakeFiles/DeepsEngine.dir/depend:
	cd /Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/deepakramalingam/Documents/Projects/DeepsEngine /Users/deepakramalingam/Documents/Projects/DeepsEngine /Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library /Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library /Users/deepakramalingam/Documents/Projects/DeepsEngine/res/example-project/build/web/web-library/CMakeFiles/DeepsEngine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DeepsEngine.dir/depend

