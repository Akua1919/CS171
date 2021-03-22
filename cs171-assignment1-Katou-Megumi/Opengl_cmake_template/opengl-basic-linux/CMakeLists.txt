cmake_minimum_required(VERSION 3.0.0)
project(opengl-basic VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)
#add opengl
find_package(OpenGL)
# add glfw
find_package(glfw3)
# add glad
include_directories(3rdLibs/glad/include)
add_library(glad SHARED 3rdLibs/glad/src/glad.c)
# find source codes
# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	src/*.c
    src/*.cpp)
if(WIN32)
add_definitions(-D_AMD64_)
endif()
message("Following files are complied " ${SOURCE_FILES})
add_executable(opengl-basic ${SOURCE_FILES})
target_link_libraries(opengl-basic glad glfw ${OPENGL_glu_LIBRARY} ${OPENGL_LIBRARIES})

