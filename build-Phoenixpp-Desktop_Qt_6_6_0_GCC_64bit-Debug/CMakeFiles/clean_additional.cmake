# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Phoenixpp_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Phoenixpp_autogen.dir/ParseCache.txt"
  "Phoenixpp_autogen"
  )
endif()
