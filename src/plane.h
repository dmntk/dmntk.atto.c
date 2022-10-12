#ifndef PLANE_PLANE_H
#define PLANE_PLANE_H

#include "cell.h"

/*
 * Plane containing cells with characters.
 */
typedef struct Plane_t {
  Cell *start;
} Plane;

/* Creates a new empty plane. */
Plane *new_plane();

/* Loads a plane from file. */
Plane *load_plane_from_file(const char file_name[]);

/* Deletes the plane. */
void delete_plane(Plane *plane);

/* Appends a row at the bottom of the plane. */
void append_row(Plane *plane, Cell *row);

/* Prints the content of the plane to standard output. */
void display_plane(const Plane *plane);

/* Returns the total number of characters in plane. */
size_t plane_len(const Plane *plane);

/* Returns the content of the plane as a string of characters. */
wchar_t *plane_to_string(const Plane *plane);

#endif /* PLANE_PLANE_H */
