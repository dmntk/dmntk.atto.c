project(plane_tests C)

cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(CMAKE_C_STANDARD 99)

set(APP_SOURCES
  ../src/cell.h
  ../src/cell.c
  ../src/plane.c
  ../src/plane.c)

set(TEST_SOURCES
  assertions.h
  assertions.c
  tc_display.h
  tc_display.c
  main.c utils.c utils.h)

add_executable(${PROJECT_NAME} ${APP_SOURCES} ${TEST_SOURCES})

add_test(NAME tcDisplay COMMAND plane_tests tcDisplay ${CMAKE_SOURCE_DIR})



