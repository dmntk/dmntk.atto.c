#include <malloc.h>

#include "../src/plane.h"

#include "assertions.h"
#include "utils.h"
#include "tc_display.h"

int tc_display() {
  // load input
  Plane *plane = load_plane_from_file("./examples/e1.dtb");
  if (plane == NULL) return ASSERT_RESULT_FAILURE;
  // evaluate tested functionality
  wchar_t *actual = plane_to_string(plane);
  delete_plane(plane);
  // load expected output
  wchar_t * expected = load("./tests/expected/tc_display/e001.dtb");
  if (expected == NULL) return ASSERT_RESULT_FAILURE;
  // compare results
  bool result = EQUAL_WIDE_STRING(expected, actual);
  free(expected);
  free(actual);
  return result ? ASSERT_RESULT_SUCCESS : ASSERT_RESULT_FAILURE;
}