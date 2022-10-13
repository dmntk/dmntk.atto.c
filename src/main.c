#include <stdlib.h>
#include <locale.h>

#include "plane.h"
#include "box.h"

/*
 * Main entrypoint of the application.
 */
int main() {
  setlocale(LC_ALL, "");
  Plane *plane = load_plane_from_file("./examples/e1.dtb");
  if (plane == NULL) return EXIT_FAILURE;
  plane_init(plane);
  cursor_init(plane);
  // display_plane(plane);
  // display_plane_attributes(plane);
  // display_plane_pointers(plane);

  cursor_move_down(plane);
  insert_char(plane, L'A');
  insert_char(plane, L'B');
  display_plane_pointers(plane);
  cursor_move_up(plane);
  for (int i = 0; i < 49; ++i) insert_char(plane, L'X');
  // display_plane(plane);

  delete_plane(plane);
  return EXIT_SUCCESS;
}
