#ifndef PLANE_PLANE_H
#define PLANE_PLANE_H

#include "box.h"

/*
 * Plane containing boxes with characters.
 */
typedef struct Plane_t {
  Box *start;   // the left-top box of the plane
  Box *cursor;  // box under the cursor
} Plane;

/*
 * Position of the cursor in plane coordinates.
 * Row index and column index is given relative to the top-left corner of the plane.
 */
typedef struct CursorPos_t {
  size_t row;  // row index
  size_t col;  // col index
} CursorPos;

/* Creates a new empty plane. */
Plane *plane_new();

/* Initializes a plane. */
void plane_init(Plane *plane);

/* Loads a plane from file. */
Plane *load_plane_from_file(const char file_name[]);

/* Deletes the plane. */
void delete_plane(Plane *plane);

/* Appends a row at the bottom of the plane. */
void append_row(Plane *plane, Box *row);

/* Prints the content of the plane to standard output. */
void display_plane(const Plane *plane);

/* Prints the attributes of all boxes of the plane to standard output. */
void display_plane_attributes(const Plane *plane);

/* Returns the total number of characters in plane. */
size_t plane_len(const Plane *plane);

/* Returns the content of the plane as a string of characters. */
wchar_t *plane_to_string(const Plane *plane);

/* Initializes cursor position. */
CursorPos cursor_init(Plane *plane);

/* Returns the current cursor position. */
CursorPos cursor_pos(Plane *plane);

/* Moves cursor one box to the right. */
void cursor_move_right(Plane *plane);

/* Moves cursor one box to the left. */
void cursor_move_left(Plane *plane);

/* Moves cursor one box up. */
void cursor_move_up(Plane *plane);

/* Moves cursor one box down. */
void cursor_move_down(Plane *plane);

/* Inserts a character at the current cursor position. */
void insert_char(Plane *plane, wchar_t ch);

#endif // PLANE_PLANE_H
