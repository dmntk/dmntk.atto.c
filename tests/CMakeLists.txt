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

add_test(NAME tcDisplay COMMAND plane_tests tcDisplay ${CMAKE_SOURCE_DIR})
add_test(NAME tcCursorInit COMMAND plane_tests tcCursorInit ${CMAKE_SOURCE_DIR})



