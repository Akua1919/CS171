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
include tests/CMakeFiles/triangle-vulkan.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/triangle-vulkan.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/triangle-vulkan.dir/flags.make

tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o: tests/CMakeFiles/triangle-vulkan.dir/flags.make
tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o: ../tests/triangle-vulkan.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o"
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o   -c /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/tests/triangle-vulkan.c

tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i"
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/tests/triangle-vulkan.c > CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i

tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s"
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/tests/triangle-vulkan.c -o CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s

tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o.requires:

.PHONY : tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o.requires

tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o.provides: tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o.requires
	$(MAKE) -f tests/CMakeFiles/triangle-vulkan.dir/build.make tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o.provides.build
.PHONY : tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o.provides

tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o.provides.build: tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o


tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o: tests/CMakeFiles/triangle-vulkan.dir/flags.make
tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o: ../deps/glad_vulkan.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o"
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o   -c /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/deps/glad_vulkan.c

tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.i"
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/deps/glad_vulkan.c > CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.i

tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.s"
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/deps/glad_vulkan.c -o CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.s

tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o.requires:

.PHONY : tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o.requires

tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o.provides: tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o.requires
	$(MAKE) -f tests/CMakeFiles/triangle-vulkan.dir/build.make tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o.provides.build
.PHONY : tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o.provides

tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o.provides.build: tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o


# Object files for target triangle-vulkan
triangle__vulkan_OBJECTS = \
"CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o" \
"CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o"

# External object files for target triangle-vulkan
triangle__vulkan_EXTERNAL_OBJECTS =

tests/triangle-vulkan: tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o
tests/triangle-vulkan: tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o
tests/triangle-vulkan: tests/CMakeFiles/triangle-vulkan.dir/build.make
tests/triangle-vulkan: src/libglfw3.a
tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/libm.so
tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/librt.so
tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/libm.so
tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/libX11.so
tests/triangle-vulkan: tests/CMakeFiles/triangle-vulkan.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable triangle-vulkan"
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/triangle-vulkan.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/triangle-vulkan.dir/build: tests/triangle-vulkan

.PHONY : tests/CMakeFiles/triangle-vulkan.dir/build

tests/CMakeFiles/triangle-vulkan.dir/requires: tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o.requires
tests/CMakeFiles/triangle-vulkan.dir/requires: tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o.requires

.PHONY : tests/CMakeFiles/triangle-vulkan.dir/requires

tests/CMakeFiles/triangle-vulkan.dir/clean:
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/triangle-vulkan.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/triangle-vulkan.dir/clean

tests/CMakeFiles/triangle-vulkan.dir/depend:
	cd /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2 /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/tests /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests /home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/tests/CMakeFiles/triangle-vulkan.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/triangle-vulkan.dir/depend

