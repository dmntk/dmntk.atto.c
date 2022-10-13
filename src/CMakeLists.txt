project(plane C)

cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

set(CMAKE_C_STANDARD 99)

set(SOURCES
  cell.h
  cell.c
  plane.h
  plane.c
  main.c
  )

add_executable(${PROJECT_NAME} ${SOURCES})
