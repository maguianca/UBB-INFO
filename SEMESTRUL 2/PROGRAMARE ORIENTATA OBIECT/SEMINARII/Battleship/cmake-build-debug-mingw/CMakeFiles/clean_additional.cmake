# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Battleship_autogen"
  "CMakeFiles\\Battleship_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Battleship_autogen.dir\\ParseCache.txt"
  )
endif()
