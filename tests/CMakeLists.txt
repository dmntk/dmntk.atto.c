project(plane_tests C)

cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

set(CMAKE_C_STANDARD 99)

set(APP_SOURCES
  ../src/glyphs.c
  ../src/glyphs.h
  ../src/box.c
  ../src/box.h
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
  tc_cursor_init.h
  tc_cursor_move_right.c
  tc_cursor_move_right.h
  tc_cursor_move_left.c
  tc_cursor_move_left.h
  tc_cursor_move_up.c
  tc_cursor_move_up.h
  tc_cursor_move_down.c
  tc_cursor_move_down.h
  tc_glyphs.c
  tc_glyphs.h)

add_executable(${PROJECT_NAME} ${APP_SOURCES} ${TEST_SOURCES})

add_test(NAME tc_display COMMAND ${PROJECT_NAME} tc_display WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME tc_glyphs COMMAND ${PROJECT_NAME} tc_glyphs WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME tc_cursor_init COMMAND ${PROJECT_NAME} tc_cursor_init WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME tc_cursor_move_right COMMAND ${PROJECT_NAME} tc_cursor_move_right WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME tc_cursor_move_left COMMAND ${PROJECT_NAME} tc_cursor_move_left WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME tc_cursor_move_up COMMAND ${PROJECT_NAME} tc_cursor_move_up WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME tc_cursor_move_down COMMAND ${PROJECT_NAME} tc_cursor_move_down WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})



