#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

#include "assertions.h"
#include "tc_display.h"
#include "tc_cursor_init.h"

#define OUTPUT(s) #s
#define STRINGIFY(s) OUTPUT(s)
#define EQUALS(s1,s2) strcmp(s1, s2) == 0
#define RUN_MATCHED(name, test_name) if (EQUALS(name, STRINGIFY(test_name))) return test_name()
#define RUN(test_name) if (test_name() == ASSERT_RESULT_FAILURE) return ASSERT_RESULT_FAILURE

/*
 * Run all test cases.
 */
int run_all() {
  RUN(tc_display);
  RUN(tc_cursor_init);
  return ASSERT_RESULT_SUCCESS;
}

/*
 * Run a test case with specified name.
 */
int run_test_case(const char name[]) {
  RUN_MATCHED(name, tc_display);
  RUN_MATCHED(name, tc_cursor_init);
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
  printf("ERROR: invalid number of arguments, expected: 3, actual: %d\n", argc);
  return EXIT_FAILURE;
}