#include "../src/plane.h"

#include "assertions.h"
#include "tc_cursor_init.h"

int tc_cursor_init() {
  // load input
  Plane *plane = load_plane_from_file("./examples/e1.dtb");
  if (plane == NULL) return ASSERT_RESULT_FAILURE;
  // evaluate tested functionality
  cursor_init(plane);
  CursorPos c_pos = cursor_pos(plane);
  delete_plane(plane);
  // verify results
  ASSERT_EQUAL_SIZE(1, c_pos.row);
  ASSERT_EQUAL_SIZE(1, c_pos.col);
  return ASSERT_RESULT_SUCCESS;
}