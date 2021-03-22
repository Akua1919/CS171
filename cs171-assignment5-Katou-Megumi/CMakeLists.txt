cmake_minimum_required(VERSION 3.0.0)
project(volume_rendering VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)



find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# Add Include Path
include_directories(
	head
	src
	include
)

# find source codes
# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	src/*.c
    src/*.cpp
	src/*.cc)
if(WIN32)
add_definitions(-D_AMD64_)
endif()
message("Following files are complied " ${SOURCE_FILES})
add_executable(volume_rendering ${SOURCE_FILES})

