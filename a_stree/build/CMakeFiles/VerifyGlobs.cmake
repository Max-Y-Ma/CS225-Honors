# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.22
cmake_policy(SET CMP0009 NEW)

# src_sources at src/CMakeLists.txt:5 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225/CS225-Honors/a_stree/src/*.cpp")
set(OLD_GLOB
  "/workspaces/cs225/CS225-Honors/a_stree/src/stree.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225/CS225-Honors/a_stree/build/CMakeFiles/cmake.verify_globs")
endif()

# tests_src at CMakeLists.txt:130 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225/CS225-Honors/a_stree/tests/*.cpp")
set(OLD_GLOB
  "/workspaces/cs225/CS225-Honors/a_stree/tests/test-part1.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225/CS225-Honors/a_stree/build/CMakeFiles/cmake.verify_globs")
endif()
