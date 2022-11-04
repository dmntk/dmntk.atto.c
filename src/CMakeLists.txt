cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

cmake_policy(SET CMP0048 NEW)

project(atto LANGUAGES C VERSION 0.0.3)

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

configure_file(atto.h.in atto.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(CURSES_NEED_WIDE TRUE)
set(CURSES_NEED_NCURSES TRUE)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})