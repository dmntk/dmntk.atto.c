#include <malloc.h>

#include "../src/plane.h"

#include "assertions.h"
#include "utils.h"
#include "tc_display.h"

int tc_display(const char dir[]) {
  // load input
  char *input_file_name = concat(dir, "/examples/e1.dtb");
  Plane *plane = load_plane_from_file(input_file_name);
  free(input_file_name);
  if (plane == NULL) return ASSERT_RESULT_FAILURE;
  // evaluate tested functionality
  wchar_t *actual = plane_to_string(plane);
  delete_plane(plane);
  // load expected output
  char *output_file_name = concat(dir, "/tests/expected/tc_display/e001.dtb");
  wchar_t * expected = load(output_file_name);
  free(output_file_name);
  if (expected == NULL) return ASSERT_RESULT_FAILURE;
  // compare results
  bool result = EQUAL_WIDE_STRING(expected, actual);
  free(expected);
  free(actual);
  return result ? ASSERT_RESULT_SUCCESS : ASSERT_RESULT_FAILURE;
}