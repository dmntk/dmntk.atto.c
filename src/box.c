#include <malloc.h>

#include "box.h"

/*
 * Creates a new box initialized with specified character.
 */
Box *new_box(wchar_t ch) {
  Box *box = malloc(sizeof(Box));
  box->content = ch;
  box->up = NULL;
  box->right = NULL;
  box->down = NULL;
  box->left = NULL;
  return box;
}
