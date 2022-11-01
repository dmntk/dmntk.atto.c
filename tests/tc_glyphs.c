#include "../src/glyphs.h"

#include "assertions.h"
#include "tc_glyphs.h"

int tc_glyphs() {
  // single whitespace
  ASSERT_TRUE(is_whitespace(L' '));
  ASSERT_FALSE(is_whitespace(L'A'));

  // top join character
  ASSERT_TRUE(is_top_join(L'╥'));
  ASSERT_FALSE(is_top_join(L'╨'));

  // vertical line seen from the left side
  ASSERT_TRUE(is_vert_line_left(L'│'));
  ASSERT_TRUE(is_vert_line_left(L'├'));
  ASSERT_TRUE(is_vert_line_left(L'║'));
  ASSERT_TRUE(is_vert_line_left(L'╟'));

  // horizontal line seen from the top side
  ASSERT_TRUE(is_horz_line_top(L'─'));
  ASSERT_TRUE(is_horz_line_top(L'┬'));
  ASSERT_TRUE(is_horz_line_top(L'╥'));
  ASSERT_TRUE(is_horz_line_top(L'═'));
  ASSERT_TRUE(is_horz_line_top(L'╤'));
  ASSERT_FALSE(is_horz_line_top(L'│'));
  ASSERT_FALSE(is_horz_line_top(L'║'));

  // horizontal line seen from the bottom side
  ASSERT_TRUE(is_horz_line_bottom(L'─'));
  ASSERT_TRUE(is_horz_line_bottom(L'┴'));
  ASSERT_TRUE(is_horz_line_bottom(L'╨'));
  ASSERT_TRUE(is_horz_line_bottom(L'═'));
  ASSERT_TRUE(is_horz_line_bottom(L'╧'));
  ASSERT_FALSE(is_horz_line_bottom(L'│'));
  ASSERT_FALSE(is_horz_line_bottom(L'║'));

  return ASSERT_RESULT_SUCCESS;
}