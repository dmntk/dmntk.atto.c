#include "../src/glyphs.h"

#include "assertions.h"
#include "tc_glyphs.h"

int tc_glyphs() {
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