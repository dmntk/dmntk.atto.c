#ifndef PLANE_GLYPHS_H
#define PLANE_GLYPHS_H

#define WS                               L' '

#define WSS                              L" "

#define SINGLE_HORZ_LINE                 L'─'

#define DOUBLE_HORZ_LINE                 L'═'

#define SINGLE_VERT_LINE                 L'│'

#define DOUBLE_VERT_LINE                 L'║'

#define is_crossing(ch)                  (ch == L'┼') || (ch == L'┬') || (ch == L'┴') || (ch == L'╪') || (ch == L'┌') || (ch == L'┐') || (ch == L'└') || (ch == L'┘') || (ch == L'├') || (ch == L'┤') || (ch == L'╟') || (ch == L'╢') || (ch == L'╬') || (ch == L'╥') || (ch == L'╨') || (ch == L'╫') || (ch == L'╡') || (ch == L'╞') || (ch == L'╧') || (ch == L'╤')

#define is_whitespace(ch)                ((ch == L' '))

#define is_top_join(ch)                  ((ch == L'╥'))

#define is_single_vert_line(ch)          ((ch == L'│'))

#define is_vert_line_left(ch)            ((ch == L'│') || (ch == L'├') || (ch == L'║') || (ch == L'╟'))

#define is_vert_line_right(ch)           ((ch == L'│') || (ch == L'┤') || (ch == L'║') || (ch == L'╢'))

#define is_vert_line_or_crossing(ch)     ((ch == L'│') || (ch == L'║') || is_crossing(ch))

#define is_single_vert_line_crossing(ch) ((ch == L'┼') || (ch == L'┬') || (ch == L'┴') || (ch == L'┐') || (ch == L'┘') || (ch == L'┤') || (ch == L'╥') || (ch == L'╨') || (ch == L'╫') || (ch == L'╢'))

#define is_double_vert_line_crossing(ch) ((ch == L'╪') || (ch == L'╬') || (ch == L'╡') || (ch == L'╤') || (ch == L'╧'))

#define is_horz_line_top(ch)             ((ch == L'─') || (ch == L'┬') || (ch == L'╥') || (ch == L'═') || (ch == L'╤'))

#define is_horz_line_bottom(ch)          ((ch == L'─') || (ch == L'┴') || (ch == L'╨') || (ch == L'═') || (ch == L'╧'))

#define is_horz_line_or_crossing(ch)     ((ch == L'─') || (ch == L'═') || is_crossing(ch))

/*
 * Crossing of single vertical line seen from top with any horizontal line (single or double).
 */
#define is_single_horz_line_crossing(ch) ((ch == L'┼') || (ch == L'┴') || (ch == L'└') || (ch == L'┘') || (ch == L'├') || (ch == L'┤') || (ch == L'╧') || (ch == L'╞') || (ch == L'╡') || (ch == L'╪'))

/*
 * Crossing of double vertical line seen from top with any horizontal line (single or double).
 */
#define is_double_horz_line_crossing(ch) ((ch == L'╫') || (ch == L'╬') || (ch == L'╟') || (ch == L'╢') || (ch == L'╨'))

#define is_box_drawing_character(ch)     ((ch == L'┌') || (ch == L'┐') || (ch == L'└') || (ch == L'┘') || (ch == L'─') || (ch == L'│') || (ch == L'├') || (ch == L'┤') || (ch == L'┴') || (ch == L'┬') || (ch == L'┼') || (ch == L'╪') || (ch == L'╫') || (ch == L'╬') || (ch == L'╞') || (ch == L'╡') || (ch == L'╥') || (ch == L'╨') || (ch == L'═') || (ch == L'║') || (ch == L'╟') || (ch == L'╢') || (ch == L'╤') || (ch == L'╧'))

#endif // PLANE_GLYPHS_H
