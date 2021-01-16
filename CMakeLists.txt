#Macro for choosing c++ version to use
macro(use_cxx version)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++${version}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD ${version})
  endif ()
endmacro(use_cxx version)

cmake_minimum_required(VERSION 2.8)
project (Hue_Integration)

use_cxx(14)

#bring in headers
include_directories(libs)
include_directories(include)

#wildcard to grab all source files
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

#create exe cmd
add_executable(hue_monitor ${SOURCES} ${HEADERS})

