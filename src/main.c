#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "plane.h"
#include "box.h"

/*
 * Main entrypoint of the application.
 */
int main() {
  setlocale(LC_ALL, "en_US.UTF-8");

  WINDOW *w = initscr();                     /* Start curses mode 		  */
  raw();
  keypad(w, true);
  noecho();

  addstr("Hello World !!!");     /* Print Hello World		  */
  refresh();                     /* Print it on to the real screen */
  getch();                       /* Wait for user input */
  endwin();                      /* End curses mode		  */



//  Plane *plane = load_plane_from_file("./examples/e2.dtb");
//  if (plane == NULL) return EXIT_FAILURE;
//  plane_init(plane);
//  cursor_init(plane);
//  // display_plane(plane);
//  // display_plane_attributes(plane);
//  // display_plane_pointers(plane);
//
//  cursor_move_down(plane);
//  insert_char(plane, L'A');
//  insert_char(plane, L'B');
//
//  struct timespec begin, end;
//  clock_gettime(CLOCK_MONOTONIC_RAW, &begin);
//  insert_char(plane, L'B');
//  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
//
//
//  printf("Total time = %f ns\n", ((double) (end.tv_nsec - begin.tv_nsec)));
//
//  clock_gettime(CLOCK_MONOTONIC_RAW, &begin);
//  fix_vert_pointers(plane);
//  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
//
//  //display_plane_pointers(plane);
//
//  printf("Total time = %f ns\n", ((double) (end.tv_nsec - begin.tv_nsec)));
//
//  cursor_move_up(plane);
//  for (int i = 0; i < 49; ++i) insert_char(plane, L'X');
//  // display_plane(plane);
//
//  delete_plane(plane);

  return EXIT_SUCCESS;
}
