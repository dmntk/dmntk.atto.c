#ifndef PLANE_BOX_H
#define PLANE_BOX_H

#include <stddef.h>

/*
 * Box containing a single character.
 */
typedef struct Box_t {
  wchar_t content;       // the character stored in this box
  struct Box_t *left;    // points a box to the left from this box
  struct Box_t *right;   // points a box to the right from this box
  struct Box_t *up;      // points a box above this box
  struct Box_t *down;    // points a box below this box
} Box;

Box *new_box(wchar_t ch);

#endif // PLANE_BOX_H
