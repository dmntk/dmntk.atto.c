#include <malloc.h>

#include "box.h"

/*
 * Creates a new box initialized with specified character.
 */
Box *box_new(wchar_t ch) {
  Box *box = malloc(sizeof(Box));
  box->ch = ch;
  box->attr = ATTR_CLEAR;
  box->up = NULL;
  box->right = NULL;
  box->down = NULL;
  box->left = NULL;
  return box;
}
