#include <malloc.h>

#include "../src/plane.h"

#include "assertions.h"
#include "utils.h"
#include "tc_cursor_init.h"

int tc_cursor_init(const char dir[]) {
  // load input
  char *input_file_name = concat(dir, "/examples/e1.dtb");
  Plane *plane = load_plane_from_file(input_file_name);
  free(input_file_name);
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