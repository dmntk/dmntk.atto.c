#ifndef PLANE_CELL_H
#define PLANE_CELL_H

#include <stddef.h>

/*
 * Cell containing single character.
 */
typedef struct Cell_t {
  wchar_t content;        // the character stored in cell
  struct Cell_t *top;     // points a cell above
  struct Cell_t *right;   // points a cell to the right
  struct Cell_t *bottom;  // points a cell below
  struct Cell_t *left;    // points a cell to the left
} Cell;

Cell *new_cell(wchar_t ch);

#endif // PLANE_CELL_H
