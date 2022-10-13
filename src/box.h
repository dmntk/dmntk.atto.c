#ifndef PLANE_BOX_H
#define PLANE_BOX_H

#include <stddef.h>

#define ATTR_CLEAR 0x00000000  // Mask used tu clear all attributes.
#define ATTR_JOIN  0x00000001  // Boxes of the line between information item name and the body of the decision table have this attribute set.

#define IS_JOIN(attr) ((attr & ATTR_JOIN) != 0)

/*
 * Box containing a single character.
 */
typedef struct Box_t {
  wchar_t ch;            // the character stored in this box
  unsigned short attr;   // additional box attributes
  struct Box_t *left;    // points a box to the left from this box
  struct Box_t *right;   // points a box to the right from this box
  struct Box_t *up;      // points a box above this box
  struct Box_t *down;    // points a box below this box
} Box;

Box *box_new(wchar_t ch);

#endif // PLANE_BOX_H
