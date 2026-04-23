# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\MyNotebook_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MyNotebook_autogen.dir\\ParseCache.txt"
  "MyNotebook_autogen"
  )
endif()
