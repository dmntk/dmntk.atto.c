#ifndef ATTO_BOX_H
#define ATTO_BOX_H

#include <stddef.h>
#include <stdbool.h>

#define ATTR_CLEAR_ALL   0x00  // Mask used tu clear all attributes.
#define ATTR_JOIN        0x01  // JOIN attribute is set for boxes on the line between information item name and the body of the decision table.
#define ATTR_CLEAR_JOIN  0xFE  // Mask for clearing JOIN attribute.

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
Box *box_new(wchar_t ch);

/* Returns `true` when this box is a part of a line joining information item name and table body. */
bool is_join(const Box *box);

/* Returns visual representation of box's attributes. */
wchar_t box_attributes_to_char(const Box *box);

/* Returns visual representation of box's pointers. */
wchar_t box_pointers_to_char(const Box *box);

#endif // ATTO_BOX_H
