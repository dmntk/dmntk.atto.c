#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <wchar.h>

#include "assertions.h"

bool assert_true(bool actual) {
  if (actual) {
    return true;
  } else {
    printf("expected = true\n");
    printf("  actual = false\n");
    return false;
  }
}

bool assert_equal_string(char *expected, char *actual) {
  if (strcmp(expected, actual) == 0) {
    return true;
  } else {
    printf("expected = %s\n", expected);
    printf("  actual = %s\n", actual);
    return false;
  }
}

bool assert_equal_size(size_t expected, size_t actual) {
  if (expected == actual) {
    return true;
  } else {
    printf("expected = %lu\n", expected);
    printf("  actual = %lu\n", actual);
    return false;
  }
}

bool assert_equal_wide_string(const wchar_t *expected, const wchar_t *actual) {
  if (wcscmp(expected, actual) == 0) {
    return true;
  } else {
    printf("expected:\n%ls\n", expected);
    printf("  actual:\n%ls\n", actual);
    return false;
  }
}

bool assert_equal_double(double expected, double actual) {
  if (fabs(expected - actual) < DBL_EPSILON) {
    return true;
  } else {
    printf("expected = %.80f\n", expected);
    printf("  actual = %.80f\n", actual);
    printf(" epsilon = %.80f\n", DBL_EPSILON);
    printf("    diff = %.80f\n", fabs(expected - actual));
    return false;
  }
}

bool assert_equal_double_eps(double expected, double actual, double epsilon) {
  if (fabs(expected - actual) < epsilon) {
    return true;
  } else {
    printf("expected = %.80f\n", expected);
    printf("  actual = %.80f\n", actual);
    printf(" epsilon = %.80f\n", epsilon);
    printf("    diff = %.80f\n", fabs(expected - actual));
    return false;
  }
}


