cmake_minimum_required(VERSION 3.10)
project(Phoenix)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_GENERATOR "MinGW Makefiles")

add_subdirectory(src)
add_subdirectory(utils)
add_subdirectory(implementations)