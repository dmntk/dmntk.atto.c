#ifndef PLANE_CELL_H
#define PLANE_CELL_H

#include <stddef.h>

/*
 * Cell containing single character.
 */
typedef struct Cell_t {
  wchar_t content;        // the character stored in this cell
  struct Cell_t *left;    // points a cell to the left from this cell
  struct Cell_t *right;   // points a cell to the right from this cell
  struct Cell_t *up;      // points a cell above this cell
  struct Cell_t *down;    // points a cell below this cell
} Cell;

Cell *new_cell(wchar_t ch);

#endif // PLANE_CELL_H
