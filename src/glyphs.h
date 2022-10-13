#ifndef PLANE_GLYPHS_H
#define PLANE_GLYPHS_H

#define WS L' '
#define SINGLE_HORZ_LINE L'─'
#define DOUBLE_HORZ_LINE L'═'
#define IS_WHITESPACE(ch) ((ch == L' '))
#define IS_TOP_JOIN(ch) ((ch == L'╥'))
#define IS_VERT_LINE(ch) ((ch == L'│') || (ch == L'║'))
#define IS_VERT_LINE_LEFT(ch) ((ch == L'│') || (ch == L'├') || (ch == L'║') || (ch == L'╟'))
#define IS_VERT_LINE_CROSSING(ch) ((ch == L'│') || (ch == L'┼') || (ch == L'┬') || (ch == L'┴') || (ch == L'╪') || (ch == L'┐') || (ch == L'┘') || (ch == L'├') || (ch == L'║') || (ch == L'╟') || (ch == L'╬') || (ch == L'╥') || (ch == L'╨') || (ch == L'╫') || (ch == L'╢') || (ch == L'┤') || (ch == L'╡'))
#define IS_SINGLE_VERT_LINE_CROSSING(ch) ((ch == L'┼') || (ch == L'┬') || (ch == L'┴') || (ch == L'┐') || (ch == L'┘') || (ch == L'┤') || (ch == L'╥') || (ch == L'╨') || (ch == L'╫') || (ch == L'╢'))
#define IS_DOUBLE_VERT_LINE_CROSSING(ch) ((ch == L'╪') || (ch == L'╬') || (ch == L'╡'))
#define IS_HORZ_LINE(ch) ((ch == L'─') || (ch == L'═'))

#endif // PLANE_GLYPHS_H
