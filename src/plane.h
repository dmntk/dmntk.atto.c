#ifndef PLANE_PLANE_H
#define PLANE_PLANE_H

#include "cell.h"

/*
 * Plane containing cells with characters.
 */
typedef struct Plane_t {
  Cell *start;   // the left-top cell of the plane
  Cell *cursor;  // cell under the cursor
} Plane;

/*
 * Position of the cursor in plane coordinates.
 * Row index and column index is given relative to the top-left
 * corner of the plane.
 */
typedef struct CursorPos_t {
  size_t row;  // row index
  size_t col;  // col index
} CursorPos;

/* Creates a new empty plane. */
Plane *new_plane();

/* Loads a plane from file. */
Plane *load_plane_from_file(const char file_name[]);

/* Deletes the plane. */
void delete_plane(Plane *plane);

/* Appends a row at the bottom of the plane. */
void append_row(Plane *plane, Cell *row);

/* Prints the content of the plane to standard output. */
void display_plane(const Plane *plane);

/* Returns the total number of characters in plane. */
size_t plane_len(const Plane *plane);

/* Returns the content of the plane as a string of characters. */
wchar_t *plane_to_string(const Plane *plane);

/* Initializes cursor position. */
CursorPos cursor_init(Plane *plane);

/* Returns the current cursor position. */
CursorPos cursor_pos(Plane *plane);

/* Moves cursor one cell to the right. */
void cursor_move_right(Plane *plane);

/* Moves cursor one cell to the left. */
void cursor_move_left(Plane *plane);

/* Moves cursor one cell up. */
void cursor_move_up(Plane *plane);

/* Moves cursor one cell down. */
void cursor_move_down(Plane *plane);

#endif // PLANE_PLANE_H
