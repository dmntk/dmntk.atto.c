#ifndef PLANE_GLYPHS_H
#define PLANE_GLYPHS_H

#define WS                               L' '

#define SINGLE_HORZ_LINE                 L'─'

#define DOUBLE_HORZ_LINE                 L'═'

#define is_whitespace(ch)                ((ch == L' '))

#define is_top_join(ch)                  ((ch == L'╥'))

#define is_vert_line(ch)                 ((ch == L'│') || (ch == L'║'))

#define is_vert_line_left(ch)            ((ch == L'│') || (ch == L'├') || (ch == L'║') || (ch == L'╟'))

#define is_vert_line_right(ch)           ((ch == L'│') || (ch == L'┤') || (ch == L'║') || (ch == L'╢'))

#define is_vert_line_crossing(ch)        ((ch == L'│') || (ch == L'┼') || (ch == L'┬') || (ch == L'┴') || (ch == L'╪') || (ch == L'┐') || (ch == L'┘') || (ch == L'├') || (ch == L'║') || (ch == L'╟') || (ch == L'╬') || (ch == L'╥') || (ch == L'╨') || (ch == L'╫') || (ch == L'╢') || (ch == L'┤') || (ch == L'╡'))

#define is_single_vert_line_crossing(ch) ((ch == L'┼') || (ch == L'┬') || (ch == L'┴') || (ch == L'┐') || (ch == L'┘') || (ch == L'┤') || (ch == L'╥') || (ch == L'╨') || (ch == L'╫') || (ch == L'╢'))

#define is_double_vert_line_crossing(ch) ((ch == L'╪') || (ch == L'╬') || (ch == L'╡') || (ch == L'╤') || (ch == L'╧'))

#define is_horz_line_top(ch)             ((ch == L'─') || (ch == L'┬') || (ch == L'╥') || (ch == L'═') || (ch == L'╤'))

#define is_horz_line_bottom(ch)          ((ch == L'─') || (ch == L'┴') || (ch == L'╨') || (ch == L'═') || (ch == L'╧'))

#define is_box_drawing_character(ch)     ((ch == L'┌') || (ch == L'┐') || (ch == L'└') || (ch == L'┘') || (ch == L'─') || (ch == L'│') || (ch == L'├') || (ch == L'┤') || (ch == L'┴') || (ch == L'┬') || (ch == L'┼') || (ch == L'╪') || (ch == L'╫') || (ch == L'╬') || (ch == L'╞') || (ch == L'╡') || (ch == L'╥') || (ch == L'╨') || (ch == L'═') || (ch == L'║') || (ch == L'╟') || (ch == L'╢') || (ch == L'╤') || (ch == L'╧'))

#endif // PLANE_GLYPHS_H
