project(plane C)

cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

set(CMAKE_C_STANDARD 99)

set(SOURCES
  main.c
  cell.c
  cell.h
  plane.c
  plane.h
  glyphs.c
  glyphs.h)

add_executable(${PROJECT_NAME} ${SOURCES})
