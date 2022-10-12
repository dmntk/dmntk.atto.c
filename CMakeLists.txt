cmake_minimum_required(VERSION 3.23)
project(plane C)

set(CMAKE_C_STANDARD 99)

add_executable(plane src/cell.c src/main.c src/plane.c src/plane.h)
