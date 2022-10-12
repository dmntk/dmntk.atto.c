#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

#include "assertions.h"
#include "tc_display.h"

/*
 * Run a test case with specified name.
 */
int run_test_case(const char name[], const char dir[]) {
  if (strcmp(name, TC_DISPLAY) == 0) {
    return tc_display(dir);
  }
  printf("unknown test case name: %s\n", name);
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
  printf("invalid number of arguments, expected: 3, actual: %d\n", argc);
  return EXIT_FAILURE;
}