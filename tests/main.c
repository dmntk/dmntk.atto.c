#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

#include "assertions.h"
#include "tc_display.h"
#include "tc_glyphs.h"
#include "tc_cursor_init.h"
#include "tc_cursor_move_right.h"
#include "tc_cursor_move_left.h"
#include "tc_cursor_move_up.h"
#include "tc_cursor_move_down.h"

#define EQUALS(s1, s2) (strcmp(s1, s2) == 0)
#define RUN_MATCH(name, test_name) if (EQUALS(name, #test_name)) return test_name()
#define RUN(test_name) if (test_name() == ASSERT_RESULT_FAILURE) return ASSERT_RESULT_FAILURE

/*
 * Run all test cases.
 */
int run_all() {
  RUN(tc_display);
  RUN(tc_glyphs);
  RUN(tc_cursor_init);
  RUN(tc_cursor_move_right);
  RUN(tc_cursor_move_left);
  RUN(tc_cursor_move_up);
  RUN(tc_cursor_move_down);
  return ASSERT_RESULT_SUCCESS;
}

/*
 * Run a test case with specified name.
 */
int run_test_case(const char name[]) {
  RUN_MATCH(name, tc_display);
  RUN_MATCH(name, tc_glyphs);
  RUN_MATCH(name, tc_cursor_init);
  RUN_MATCH(name, tc_cursor_move_right);
  RUN_MATCH(name, tc_cursor_move_left);
  RUN_MATCH(name, tc_cursor_move_up);
  RUN_MATCH(name, tc_cursor_move_down);
  printf("\nERROR: Unknown test case name: %s", name);
  return ASSERT_RESULT_FAILURE;
}

/*
 * Main entrypoint of tests.
 */
int main(const int argc, const char *argv[]) {
  setlocale(LC_ALL, "");
  if (argc == 2) {
    if (EQUALS(argv[1], "all")) return run_all();
    switch (run_test_case(argv[1])) {
      case ASSERT_RESULT_SUCCESS:
        return EXIT_SUCCESS;
      case ASSERT_RESULT_FAILURE:
        return EXIT_FAILURE;
    }
  }
  printf("ERROR: invalid number of arguments, expected: 2, actual: %d\n", argc);
  return EXIT_FAILURE;
}