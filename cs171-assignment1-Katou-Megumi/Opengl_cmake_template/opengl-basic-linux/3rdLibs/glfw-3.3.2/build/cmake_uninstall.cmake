
if (NOT EXISTS "/home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"/home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/install_manifest.txt\"")
endif()

file(READ "/home/xiasuan/cs171-assignment1-Katou-Megumi/Opengl_cmake_template/opengl-basic-linux/3rdLibs/glfw-3.3.2/build/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")

foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    exec_program("/usr/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif()
  elseif (IS_SYMLINK "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM("/usr/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing symlink \"$ENV{DESTDIR}${file}\"")
    endif()
  else()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif()
endforeach()

