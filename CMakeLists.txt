cmake_minimum_required(VERSION 3.28)

project(fmexercise VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 23)

include (dependencies/whiley.cmake)


add_subdirectory(libs)
add_subdirectory(bin)
