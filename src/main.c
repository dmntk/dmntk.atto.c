#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <errno.h>

#include "plane.h"
#include "cell.h"

const short int BUF_SIZE = 100;

/*
 * Loads a plane from specified file.
 */
int load_plane_from_file(const char *file_name) {
  FILE *f;
  wchar_t buffer[BUF_SIZE];
  if ((f = fopen(file_name, "r")) == NULL) {
    fprintf(stderr, "failed to open file %s", file_name);
    return -1;
  }
  errno = 0;
  Cell *row = NULL, *row_tail = NULL, *current = NULL;
  Plane *plane = new_plane();
  while (fgetws(buffer, BUF_SIZE, f) != NULL) {
    int i = 0;
    while (buffer[i] != 0) {
      if (buffer[i] != '\n') {
        current = new_cell(buffer[i]);
        if (row == NULL) {
          row = current;
          row_tail = current;
        } else {
          row_tail->right = current;
          current->left = row_tail;
          row_tail = current;
        }
      } else {
        append_row(plane, row);
        row = NULL;
        row_tail = NULL;
      }
      i++;
    }
    if (row != NULL) {
      append_row(plane, row);
      row = NULL;
      row_tail = NULL;
    }
  }
  if (errno == EILSEQ) {
    fprintf(stderr, "an invalid wide character was encountered");
    fclose(f);
    return -1;
  } else if (!feof(f)) {
    fprintf(stderr, "file read error");
    fclose(f);
  }
  fclose(f);
  //
  display_plane(plane);
  delete_plane(plane);
  return 0;
}


/*
 * Main entrypoint of the application.
 */
int main() {
  setlocale(LC_ALL, "");
  if (load_plane_from_file("./examples/e1.dtb") != 0) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
