# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.16

# source_files_ at src/CMakeLists.txt:3 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/moritz-feik/st-escape-to-eclipse/src/./*.cpp")
set(OLD_GLOB
  "/home/moritz-feik/st-escape-to-eclipse/src/./System/System.cpp"
  "/home/moritz-feik/st-escape-to-eclipse/src/./main.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/moritz-feik/st-escape-to-eclipse/build/CMakeFiles/cmake.verify_globs")
endif()

# header_files_ at src/CMakeLists.txt:2 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/moritz-feik/st-escape-to-eclipse/src/./*.h")
set(OLD_GLOB
  "/home/moritz-feik/st-escape-to-eclipse/src/./System/System.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/moritz-feik/st-escape-to-eclipse/build/CMakeFiles/cmake.verify_globs")
endif()
