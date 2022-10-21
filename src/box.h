#ifndef PLANE_BOX_H
#define PLANE_BOX_H

#include <stddef.h>
#include <stdbool.h>

#define ATTR_CLEAR 0x0000  // Mask used tu clear all attributes.
#define ATTR_JOIN  0x0001  // Boxes of the line between information item name and the body of the decision table have this attribute set.

/*
 * Box containing a single character.
 */
typedef struct Box_t {
  wchar_t ch;            // the character stored in box
  unsigned char attr;    // additional box attributes
  struct Box_t *left;    // points a box to the left from current box
  struct Box_t *right;   // points a box to the right from current box
  struct Box_t *up;      // points a box above current box
  struct Box_t *down;    // points a box below current box
} Box;

/* Creates a new box containing specified character. */
Box *box_new(const wchar_t ch);

/* Returns `true` when this box is a part of a line joining information item name and table body. */
bool is_join(const Box *box);

/* Returns visual representation of box's attributes. */
wchar_t box_attributes_to_char(const Box *box);

/* Returns visual representation of box's pointers. */
wchar_t box_pointers_to_char(const Box *box);

#endif // PLANE_BOX_H
