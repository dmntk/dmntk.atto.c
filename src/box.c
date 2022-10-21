#include <malloc.h>
#include <stdbool.h>

#include "box.h"

/*
 * Creates a new box initialized with specified character.
 */
Box *box_new(const wchar_t ch) {
  Box *box = malloc(sizeof(Box));
  box->ch = ch;
  box->attr = ATTR_CLEAR;
  box->up = NULL;
  box->right = NULL;
  box->down = NULL;
  box->left = NULL;
  return box;
}

/*
 * Returns `true` when this box is a part of a line
 * joining information item name and table body.
 */
bool is_join(const Box *box) {
  return (box->attr & ATTR_JOIN) != 0;
}

/*
 * Returns visual representation of box's attributes.
 */
wchar_t box_attributes_to_char(const Box *box) {
  return (box->attr & ATTR_JOIN) ? L'─' : L'•';
}

/*
 * Returns visual representation of box's pointers.
 */
wchar_t box_pointers_to_char(const Box *box) {
  bool l_null, r_null, u_null, d_null;
  bool l_ok, r_ok, u_ok, d_ok;
  l_null = box->left == NULL;
  r_null = box->right == NULL;
  u_null = box->up == NULL;
  d_null = box->down == NULL;
  l_ok = !l_null && box->left != NULL && box->left->right != NULL && box->left->right == box;
  r_ok = !r_null && box->right != NULL && box->right->left != NULL && box->right->left == box;
  u_ok = !u_null && box->up != NULL && box->up->down != NULL && box->up->down == box;
  d_ok = !d_null && box->down != NULL && box->down->up != NULL && box->down->up == box;
  if (!l_ok && !r_ok && !u_ok && !d_ok) return L'•';
  if (!l_ok && !r_ok && !u_ok && d_ok) return L'╷';
  if (!l_ok && !r_ok && u_ok && !d_ok) return L'╵';
  if (!l_ok && !r_ok && u_ok && d_ok) return L'│';
  if (!l_ok && r_ok && !u_ok && !d_ok) return L'╶';
  if (!l_ok && r_ok && !u_ok && d_ok) return L'┌';
  if (!l_ok && r_ok && u_ok && !d_ok) return L'└';
  if (!l_ok && r_ok && u_ok && d_ok) return L'├';
  if (l_ok && !r_ok && !u_ok && !d_ok) return L'╴';
  if (l_ok && !r_ok && !u_ok && d_ok) return L'┐';
  if (l_ok && !r_ok && u_ok && !d_ok) return L'┘';
  if (l_ok && !r_ok && u_ok && d_ok) return L'┤';
  if (l_ok && r_ok && !u_ok && !d_ok) return L'─';
  if (l_ok && r_ok && !u_ok && d_ok) return L'┬';
  if (l_ok && r_ok && u_ok && !d_ok) return L'┴';
  if (l_ok && r_ok && u_ok && d_ok) return L'┼';
}
