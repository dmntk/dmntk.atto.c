#ifndef PFD_ASSERTIONS_H
#define PFD_ASSERTIONS_H

#include <stdbool.h>
#include <stddef.h>

#define ASSERT_RESULT_SUCCESS 0
#define ASSERT_RESULT_FAILURE 1

bool assert_true(bool actual);

bool assert_equal_string(char *expected, char *actual);

bool assert_equal_wide_string(const wchar_t *expected, const wchar_t *actual);

bool assert_equal_double(double expected, double actual);

bool assert_equal_double_eps(double expected, double actual, double epsilon);

#define ASSERT_TRUE(actual) if (!assert_true(actual)) return ASSERT_RESULT_FAILURE
#define ASSERT_EQUAL_STRING(expected, actual) if (!assert_equal_string(expected, actual)) return ASSERT_RESULT_FAILURE
#define ASSERT_EQUAL_DOUBLE(expected, actual) if (!assert_equal_double(expected, actual)) return ASSERT_RESULT_FAILURE
#define ASSERT_EQUAL_DOUBLE_EPS(expected, actual, epsilon) if (!assert_equal_double_eps(expected, actual, epsilon)) return ASSERT_RESULT_FAILURE

#define EQUAL_WIDE_STRING(expected, actual) assert_equal_wide_string(expected, actual)

#endif /* PFD_ASSERTIONS_H */
