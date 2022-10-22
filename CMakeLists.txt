project(atto C)

cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

enable_testing()

add_subdirectory(src)

add_subdirectory(tests)