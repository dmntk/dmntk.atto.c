project(plane C)

cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

set(CMAKE_C_STANDARD 99)

set(SOURCES
  main.c
  box.c
  box.h
  plane.c
  plane.h
  glyphs.c
  glyphs.h)

add_executable(${PROJECT_NAME} ${SOURCES})

set(CURSES_NEED_WIDE TRUE)

find_package(Curses REQUIRED)

target_link_libraries(${PROJECT_NAME} ncurses)