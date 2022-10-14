#include <locale.h>
#include <stdlib.h>

#include "actions.h"
#include "editor.h"

/* Opens a file to edit. */
void edit_file(const char file_name[static 1]) {
  Editor *editor;
  if ((editor = editor_new(file_name)) == NULL) return;
  editor_delete(editor);
}

/*
 * Main entrypoint of the application.
 */
int main(int argc, char *argv[]) {
  setlocale(LC_ALL, ""); // crucial
  struct Action action = get_action(argc, argv);
  switch (action.type) {
    case EditFile:
      edit_file(action.file_name);
      break;
    default:
      break;
  }

//
//  WINDOW *w = initscr();                     /* Start curses mode 		  */
//  raw();
//  keypad(w, true);
//  noecho();
//
//  addstr("Hello World !!!");     /* Print Hello World		  */
//  refresh();                     /* Print it on to the real screen */
//  getch();                       /* Wait for user input */
//  endwin();                      /* End curses mode		  */



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
