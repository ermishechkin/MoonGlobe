# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ovv/Dropbox/projects/OpenGL/sphere

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ovv/Dropbox/projects/OpenGL/sphere

# Include any dependencies generated for this target.
include libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/depend.make

# Include the progress variables for this target.
include libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/progress.make

# Include the compile flags for this target's objects.
include libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/flags.make

libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.o: libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/flags.make
libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.o: libs/magnum/src/Magnum/Platform/Implementation/OpenGLFunctionLoader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ovv/Dropbox/projects/OpenGL/sphere/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.o"
	cd /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/Magnum/Platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.o -c /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/Magnum/Platform/Implementation/OpenGLFunctionLoader.cpp

libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.i"
	cd /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/Magnum/Platform && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/Magnum/Platform/Implementation/OpenGLFunctionLoader.cpp > CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.i

libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.s"
	cd /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/Magnum/Platform && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/Magnum/Platform/Implementation/OpenGLFunctionLoader.cpp -o CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.s

libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.o.requires:

.PHONY : libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.o.requires

libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.o.provides: libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.o.requires
	$(MAKE) -f libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/build.make libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.o.provides.build
.PHONY : libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.o.provides

libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.o.provides.build: libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.o


libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.o: libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/flags.make
libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.o: libs/magnum/src/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ovv/Dropbox/projects/OpenGL/sphere/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.o"
	cd /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/Magnum/Platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.o -c /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp

libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.i"
	cd /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/Magnum/Platform && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp > CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.i

libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.s"
	cd /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/Magnum/Platform && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp -o CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.s

libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.o.requires:

.PHONY : libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.o.requires

libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.o.provides: libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.o.requires
	$(MAKE) -f libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/build.make libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.o.provides.build
.PHONY : libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.o.provides

libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.o.provides.build: libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.o


MagnumEglContextObjects: libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.o
MagnumEglContextObjects: libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.o
MagnumEglContextObjects: libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/build.make

.PHONY : MagnumEglContextObjects

# Rule to build all files generated by this target.
libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/build: MagnumEglContextObjects

.PHONY : libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/build

libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/requires: libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/Implementation/OpenGLFunctionLoader.cpp.o.requires
libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/requires: libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/__/__/MagnumExternal/OpenGL/GLES2/flextGLPlatform.cpp.o.requires

.PHONY : libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/requires

libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/clean:
	cd /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/Magnum/Platform && $(CMAKE_COMMAND) -P CMakeFiles/MagnumEglContextObjects.dir/cmake_clean.cmake
.PHONY : libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/clean

libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/depend:
	cd /home/ovv/Dropbox/projects/OpenGL/sphere && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ovv/Dropbox/projects/OpenGL/sphere /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/Magnum/Platform /home/ovv/Dropbox/projects/OpenGL/sphere /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/Magnum/Platform /home/ovv/Dropbox/projects/OpenGL/sphere/libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libs/magnum/src/Magnum/Platform/CMakeFiles/MagnumEglContextObjects.dir/depend

