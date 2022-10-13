project(plane_tests C)

cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

set(CMAKE_C_STANDARD 99)

set(APP_SOURCES
  ../src/cell.c
  ../src/cell.h
  ../src/plane.c
  ../src/plane.h)

set(TEST_SOURCES
  assertions.c
  assertions.h
  utils.c
  utils.h
  main.c
  tc_display.c
  tc_display.h
  tc_cursor_init.c
  tc_cursor_init.h)

add_executable(${PROJECT_NAME} ${APP_SOURCES} ${TEST_SOURCES})

add_test(NAME tc_display     COMMAND ${PROJECT_NAME} tc_display     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME tc_cursor_init COMMAND ${PROJECT_NAME} tc_cursor_init WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})



