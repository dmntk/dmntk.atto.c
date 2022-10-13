#include <malloc.h>

#include "cell.h"

/*
 * Creates a new cell initialized with specified character.
 */
Cell *new_cell(wchar_t ch) {
  Cell *cell = malloc(sizeof(Cell));
  cell->content = ch;
  cell->up = NULL;
  cell->right = NULL;
  cell->down = NULL;
  cell->left = NULL;
  return cell;
}
