cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(atto C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS NO)

enable_testing()

add_subdirectory(src)

add_subdirectory(tests)