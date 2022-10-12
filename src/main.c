#include <stdlib.h>
#include <locale.h>

#include "plane.h"
#include "cell.h"

/*
 * Main entrypoint of the application.
 */
int main() {
  setlocale(LC_ALL, "");
  Plane *plane = load_plane_from_file("./examples/e1.dtb");
  if (plane == NULL) return EXIT_FAILURE;
  display_plane(plane);
  delete_plane(plane);
  return EXIT_SUCCESS;
}
