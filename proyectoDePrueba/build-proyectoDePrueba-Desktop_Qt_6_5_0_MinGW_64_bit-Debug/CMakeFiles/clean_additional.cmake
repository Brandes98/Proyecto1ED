# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\proyectoDePrueba_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\proyectoDePrueba_autogen.dir\\ParseCache.txt"
  "proyectoDePrueba_autogen"
  )
endif()
