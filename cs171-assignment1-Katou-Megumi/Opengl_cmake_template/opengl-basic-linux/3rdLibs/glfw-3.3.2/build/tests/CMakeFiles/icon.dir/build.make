# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/icon.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/icon.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/icon.dir/flags.make

tests/CMakeFiles/icon.dir/icon.c.o: tests/CMakeFiles/icon.dir/flags.make
tests/CMakeFiles/icon.dir/icon.c.o: ../tests/icon.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/icon.dir/icon.c.o"
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/icon.dir/icon.c.o   -c /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/tests/icon.c

tests/CMakeFiles/icon.dir/icon.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/icon.dir/icon.c.i"
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/tests/icon.c > CMakeFiles/icon.dir/icon.c.i

tests/CMakeFiles/icon.dir/icon.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/icon.dir/icon.c.s"
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/tests/icon.c -o CMakeFiles/icon.dir/icon.c.s

tests/CMakeFiles/icon.dir/icon.c.o.requires:

.PHONY : tests/CMakeFiles/icon.dir/icon.c.o.requires

tests/CMakeFiles/icon.dir/icon.c.o.provides: tests/CMakeFiles/icon.dir/icon.c.o.requires
	$(MAKE) -f tests/CMakeFiles/icon.dir/build.make tests/CMakeFiles/icon.dir/icon.c.o.provides.build
.PHONY : tests/CMakeFiles/icon.dir/icon.c.o.provides

tests/CMakeFiles/icon.dir/icon.c.o.provides.build: tests/CMakeFiles/icon.dir/icon.c.o


tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o: tests/CMakeFiles/icon.dir/flags.make
tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o: ../deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o"
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/icon.dir/__/deps/glad_gl.c.o   -c /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/deps/glad_gl.c

tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/icon.dir/__/deps/glad_gl.c.i"
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/deps/glad_gl.c > CMakeFiles/icon.dir/__/deps/glad_gl.c.i

tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/icon.dir/__/deps/glad_gl.c.s"
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/deps/glad_gl.c -o CMakeFiles/icon.dir/__/deps/glad_gl.c.s

tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o.requires:

.PHONY : tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o.requires

tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o.provides: tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o.requires
	$(MAKE) -f tests/CMakeFiles/icon.dir/build.make tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o.provides.build
.PHONY : tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o.provides

tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o.provides.build: tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o


# Object files for target icon
icon_OBJECTS = \
"CMakeFiles/icon.dir/icon.c.o" \
"CMakeFiles/icon.dir/__/deps/glad_gl.c.o"

# External object files for target icon
icon_EXTERNAL_OBJECTS =

tests/icon: tests/CMakeFiles/icon.dir/icon.c.o
tests/icon: tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o
tests/icon: tests/CMakeFiles/icon.dir/build.make
tests/icon: src/libglfw3.a
tests/icon: /usr/lib/x86_64-linux-gnu/libm.so
tests/icon: /usr/lib/x86_64-linux-gnu/librt.so
tests/icon: /usr/lib/x86_64-linux-gnu/libm.so
tests/icon: /usr/lib/x86_64-linux-gnu/libX11.so
tests/icon: tests/CMakeFiles/icon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable icon"
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/icon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/icon.dir/build: tests/icon

.PHONY : tests/CMakeFiles/icon.dir/build

tests/CMakeFiles/icon.dir/requires: tests/CMakeFiles/icon.dir/icon.c.o.requires
tests/CMakeFiles/icon.dir/requires: tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o.requires

.PHONY : tests/CMakeFiles/icon.dir/requires

tests/CMakeFiles/icon.dir/clean:
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/icon.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/icon.dir/clean

tests/CMakeFiles/icon.dir/depend:
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2 /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/tests /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests/CMakeFiles/icon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/icon.dir/depend

