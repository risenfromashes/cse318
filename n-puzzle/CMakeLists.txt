cmake_minimum_required(VERSION 3.20)

project(npuzzle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "-fsanitize=address")
endif()

file(GLOB src_files *.h *.cc)
add_executable(npuzzle ${src_files})
