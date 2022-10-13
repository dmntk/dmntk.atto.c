#include "../src/plane.h"

#include "assertions.h"
#include "tc_cursor_move_up.h"

int tc_cursor_move_up() {
  // load input
  Plane *plane = load_plane_from_file("./examples/e1.dtb");
  if (plane == NULL) return ASSERT_RESULT_FAILURE;
  // evaluate tested functionality
  cursor_init(plane);
  cursor_move_up(plane);
  CursorPos pos_1 = cursor_pos(plane);
  for (int i = 0; i < 200; ++i) cursor_move_down(plane);
  CursorPos pos_2 = cursor_pos(plane);
  cursor_move_up(plane);
  CursorPos pos_3 = cursor_pos(plane);
  delete_plane(plane);
  // verify results
  ASSERT_EQUAL_CURSOR_POS(1, 1, pos_1);
  ASSERT_EQUAL_CURSOR_POS(15, 1, pos_2);
  ASSERT_EQUAL_CURSOR_POS(13, 1, pos_3);
  return ASSERT_RESULT_SUCCESS;
}
