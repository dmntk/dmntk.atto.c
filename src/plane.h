#ifndef PLANE_PLANE_H
#define PLANE_PLANE_H

#include "cell.h"

/*
 * Plane containing cells with characters.
 */
typedef struct Plane_t {
  Cell *start;
} Plane;

Plane *new_plane();

void delete_plane(Plane *plane);

void append_row(Plane *plane, Cell *row);

void display_plane(const Plane *plane);

#endif //PLANE_PLANE_H
