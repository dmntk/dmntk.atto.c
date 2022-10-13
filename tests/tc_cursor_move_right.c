#include "../src/plane.h"

#include "assertions.h"
#include "tc_cursor_move_right.h"

int tc_cursor_move_right() {
  // load input
  Plane *plane = load_plane_from_file("./examples/e1.dtb");
  if (plane == NULL) return ASSERT_RESULT_FAILURE;
  // evaluate tested functionality
  cursor_init(plane);
  cursor_move_right(plane);
  CursorPos pos_1 = cursor_pos(plane);
  for (int i = 0; i < 200; ++i) cursor_move_right(plane);
  CursorPos pos_2 = cursor_pos(plane);
  cursor_move_left(plane);
  CursorPos pos_3 = cursor_pos(plane);
  delete_plane(plane);
  // verify results
  ASSERT_EQUAL_CURSOR_POS(1, 2, pos_1);
  ASSERT_EQUAL_CURSOR_POS(1, 63, pos_2);
  ASSERT_EQUAL_CURSOR_POS(1, 62, pos_3);
  return ASSERT_RESULT_SUCCESS;
}