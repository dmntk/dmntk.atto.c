#include <malloc.h>

#include "plane.h"

/*
 * Creates a new empty plane.
 *
 * Returns a pointer to newly created plane.
 */
Plane *new_plane() {
  Plane *plane = malloc(sizeof(Plane));
  plane->start = NULL;
  return plane;
}

/*
 * Deletes the plane.
 */
void delete_plane(Plane *plane) {
  Cell *row_head = plane->start;
  Cell *row_next = NULL, *current = NULL;
  while (row_head != NULL) {
    row_next = row_head->bottom;
    current = row_head;
    while (current != NULL) {
      row_head = current->right;
      free(current);
      current = row_head;
    }
    row_head = row_next;
  }
  free(plane);
}

/*
 * Appends a new row at the bottom of the plane.
 */
void append_row(Plane *plane, Cell *row) {
  if (plane->start == NULL) {
    plane->start = row;
  } else {
    Cell *row_last = plane->start;
    while (row_last->bottom != NULL) {
      row_last = row_last->bottom;
    }
    row_last->bottom = row;
    row->top = row_last;
    while (row_last->right != NULL && row->right != NULL) {
      row_last = row_last->right;
      row = row->right;
      row_last->bottom = row;
      row->top = row_last;
    }
  }
}

/*
 * Prints the content of the plane to standard output.
 */
void display_plane(const Plane *plane) {
  Cell *current = NULL, *row = plane->start;
  while (row != NULL) {
    current = row;
    while (current != NULL) {
      printf("%lc", current->content);
      current = current->right;
    }
    printf("\n");
    row = row->bottom;
  }
}