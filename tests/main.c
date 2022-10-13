#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

#include "assertions.h"
#include "tc_display.h"
#include "tc_cursor_init.h"

#define MATCH_NAME(actual, expected) (strcmp(actual, expected) == 0)

/*
 * Run a test case with specified name.
 */
int run_test_case(const char name[], const char dir[]) {
  if MATCH_NAME(name, TC_DISPLAY) return tc_display(dir);
  if MATCH_NAME(name, TC_CURSOR_INIT) return tc_cursor_init(dir);

  printf("\nERROR: Unknown test case name: %s", name);
  return ASSERT_RESULT_FAILURE;
}

/*
 * Main entrypoint of tests.
 */
int main(const int argc, const char *argv[]) {
  setlocale(LC_ALL, "");
  if (argc == 3) {
    switch (run_test_case(argv[1], argv[2])) {
      case ASSERT_RESULT_SUCCESS:
        return EXIT_SUCCESS;
      case ASSERT_RESULT_FAILURE:
        return EXIT_FAILURE;
    }
  }
  printf("ERROR: invalid number of arguments, expected: 3, actual: %d\n", argc);
  return EXIT_FAILURE;
}