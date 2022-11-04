project(atto C)

cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS NO)

set(SOURCES
  main.c
  box.c
  box.h
  plane.c
  plane.h
  glyphs.c
  glyphs.h
  actions.c
  actions.h
  editor.c
  editor.h)

set(CURSES_NEED_WIDE TRUE)
set(CURSES_NEED_NCURSES TRUE)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})