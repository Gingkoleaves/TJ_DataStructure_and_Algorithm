# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\HeapSort_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\HeapSort_autogen.dir\\ParseCache.txt"
  "HeapSort_autogen"
  )
endif()
