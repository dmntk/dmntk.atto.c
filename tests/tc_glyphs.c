#include "../src/glyphs.h"

#include "assertions.h"
#include "tc_glyphs.h"

int tc_glyphs() {
  // single whitespace
  ASSERT_TRUE(IS_WHITESPACE(L' '));
  ASSERT_FALSE(IS_WHITESPACE(L'A'));

  // top join character
  ASSERT_TRUE(IS_TOP_JOIN(L'╥'));
  ASSERT_FALSE(IS_TOP_JOIN(L'╨'));

  // plain vertical line
  ASSERT_TRUE(IS_VERT_LINE(L'│'));
  ASSERT_TRUE(IS_VERT_LINE(L'║'));
  ASSERT_FALSE(IS_VERT_LINE(L'═'));

  // vertical line seen from the left side
  ASSERT_TRUE(IS_VERT_LINE_LEFT(L'│'));
  ASSERT_TRUE(IS_VERT_LINE_LEFT(L'├'));
  ASSERT_TRUE(IS_VERT_LINE_LEFT(L'║'));
  ASSERT_TRUE(IS_VERT_LINE_LEFT(L'╟'));

  // plain horizontal line seen from the left side
  ASSERT_TRUE(IS_HORZ_LINE(L'─'));
  ASSERT_TRUE(IS_HORZ_LINE(L'═'));
  ASSERT_FALSE(IS_HORZ_LINE(L'│'));

  return ASSERT_RESULT_SUCCESS;
}