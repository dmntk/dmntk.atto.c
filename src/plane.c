#include <errno.h>
#include <malloc.h>
#include <stdbool.h>
#include <wchar.h>

#include "plane.h"
#include "glyphs.h"

#define LOAD_BUFFER_SIZE 5000

/*
 * Moves the specified box pointer to the right,
 * until the left-vertical line is encountered.
 */
#define move_to_vert_line_left(box)      while (box != NULL && box->right != NULL && !is_vert_line_left(box->right->ch)) box = box->right

/*
 * Moves the specified box pointer to the right,
 * until the vertical line or crossing is encountered.
 */
#define move_to_vert_line_crossing(box)  while (box != NULL && box->right != NULL && !is_vert_line_crossing(box->right->ch)) box = box->right

#define C_RED     "\x001b[31m"
#define C_YELLOW  "\x001b[33m"
#define C_MAGENTA "\x001b[47m\x001b[31m"
#define C_RESET   "\x001b[0m"
#define C_CLEAR   "\x001b[0m"
#define C_NONE    ""

/*
 * Creates a new empty plane.
 */
Plane *plane_new() {
  Plane *plane = malloc(sizeof(Plane));
  plane->start = NULL;
  plane->cursor = NULL;
  return plane;
}

/*
 * Initializes a plane.
 */
void plane_init(Plane *plane) {
  if (plane->start == NULL) return;
  Box *row = plane->start; // points currently processed row
  Box *current; // points currently processed box
  bool is_join; // flag indicating if the current row is the join between information item name and the body of the table
  while (row != NULL) {
    current = row;
    is_join = false;
    while (current != NULL) {
      if (is_top_join(current->ch)) {
        is_join = true;
        break;
      }
      current = current->right;
    }
    if (is_join) {
      current = row;
      while (current != NULL) {
        current->attr |= ATTR_JOIN;
        current = current->right;
      }
    }
    row = row->down;
  }
}

/*
 * Loads a plane from specified file.
 */
Plane *load_plane_from_file(const char file_name[]) {
  FILE *f;
  wchar_t buffer[LOAD_BUFFER_SIZE];
  if ((f = fopen(file_name, "r")) == NULL) {
    fprintf(stderr, "failed to open file: %s\n", file_name);
    return NULL;
  }
  errno = 0;
  Box *row = NULL, *row_tail = NULL, *current = NULL;
  Plane *plane = plane_new();
  while (fgetws(buffer, LOAD_BUFFER_SIZE - 1, f) != NULL) {
    int i = 0;
    while (buffer[i] != 0) {
      if (buffer[i] != '\n') {
        current = box_new(buffer[i]);
        if (row == NULL) {
          row = current;
          row_tail = current;
        } else {
          row_tail->right = current;
          current->left = row_tail;
          row_tail = current;
        }
      } else {
        append_row(plane, row);
        row = NULL;
        row_tail = NULL;
      }
      i++;
    }
    if (row != NULL) {
      append_row(plane, row);
      row = NULL;
      row_tail = NULL;
    }
  }
  if (errno == EILSEQ) {
    fprintf(stderr, "an invalid wide character was encountered\n");
    fclose(f);
    delete_plane(plane);
    return NULL;
  }
  if (!feof(f)) {
    fprintf(stderr, "file read error\n");
    fclose(f);
    delete_plane(plane);
    return NULL;
  }
  fclose(f);
  return plane;
}


/*
 * Deletes the plane.
 */
void delete_plane(Plane *plane) {
  Box *row_head = plane->start;
  Box *row_next = NULL, *current = NULL;
  while (row_head != NULL) {
    row_next = row_head->down;
    current = row_head;
    while (current != NULL) {
      row_head = current->right;
      free(current);
      current = row_head;
    }
    row_head = row_next;
  }
  free(plane);
}

/*
 * Appends a row at the bottom of the plane.
 */
void append_row(Plane *plane, Box *row) {
  if (plane->start == NULL) {
    plane->start = row;
  } else {
    Box *row_last = plane->start;
    while (row_last->down != NULL) {
      row_last = row_last->down;
    }
    row_last->down = row;
    row->up = row_last;
    while (row_last->right != NULL && row->right != NULL) {
      row_last = row_last->right;
      row = row->right;
      row_last->down = row;
      row->up = row_last;
    }
  }
}

/*
 * Prints the attributes of all boxes of the plane to standard output.
 */
void display_attributes(const Plane *plane) {
  Box *box, *row = plane->start;
  while (row != NULL) {
    box = row;
    while (box != NULL) {
      if (box->attr & ATTR_JOIN) {
        printf("─");
      } else {
        printf("*");
      }
      box = box->right;
    }
    printf("\n");
    row = row->down;
  }
}

/*
 * Prints the pointers of all boxes to standard output.
 */
void display_plane_pointers(const Plane *plane) {
  Box *box, *row = plane->start;
  bool u, u_ok, r_ok, bottom_ok, down_ok, l_ok;
  char *s1, *r1, *s2, *r2;
  while (row != NULL) {
    box = row;
    while (box != NULL) {
      u = box->up != NULL;
      u_ok = box->up != NULL ? box->up->down != NULL && box->up->down == box : true;
      s1 = u_ok ? !u ? C_MAGENTA : C_NONE : C_RED;
      r1 = u_ok ? !u ? C_RESET : C_NONE : C_RESET;
      printf("┌%s%lc%s┐", s1, u ? L'┴' : L'─', r1);
      box = box->right;
    }
    printf("\n");
    box = row;
    while (box != NULL) {
      l_ok = box->left != NULL;
      r_ok = box->right != NULL;
      printf("%lc%lc%lc", l_ok ? L'┤' : L'│', box->ch, r_ok ? L'├' : L'│');
      box = box->right;
    }
    printf("\n");
    box = row;
    while (box != NULL) {
      printf("└%lc┘", box->down != NULL ? L'┬' : L'─');
      box = box->right;
    }
    printf("\n");
    row = row->down;
  }
}

void fix_vert_pointers(const Plane *plane) {
  Box *box, *box_below;
  Box *row = plane->start;
  Box *row_below = row != NULL ? row->down : NULL;
  while (row != NULL && row_below != NULL) {
    box = row;
    box_below = row_below;
    while (box != NULL && box_below != NULL) {
      box->down = box_below;
      box_below->up = box;
      box = box->right;
      box_below = box_below->right;
    }
    while (box != NULL) {
      box->down = NULL;
      box = box->right;
    }
    while (box_below != NULL) {
      box_below->up = NULL;
      box_below = box_below->right;
    }
    row = row_below;
    row_below = row_below->down;
  }
}

/*
 * Returns the total number of characters in plane,
 * including additional newline characters for each row.
 */
size_t plane_len(const Plane *plane) {
  size_t len = 0;
  Box *current = NULL, *row = plane->start;
  while (row != NULL) {
    current = row;
    while (current != NULL) {
      len++;
      current = current->right;
    }
    row = row->down;
    // additional space for ending newline (except the last row)
    if (row != NULL) len++;
  }
  return len;
}

/*
 * Returns the content of the plane as a string of characters.
 */
wchar_t *plane_to_string(const Plane *plane) {
  size_t len = plane_len(plane);
  wchar_t *buffer = calloc(sizeof(wchar_t), len + 1);
  wchar_t *pos = buffer;
  Box *current = NULL, *row = plane->start;
  while (row != NULL) {
    current = row;
    while (current != NULL) {
      *pos++ = current->ch;
      current = current->right;
    }
    row = row->down;
    if (row != NULL) *pos++ = L'\n';
  }
  *pos = 0;
  return buffer;
}

/*
 * Initializes cursor position.
 * This function tries to position a cursor below to the right of the top-left corner of the table.
 * When the plane is not empty and contains minimum two rows and two columns,
 * then the starting cursor position is set to row = 1 and col = 1.
 * Otherwise, row = 0 and col = 0 are returned.
 */
Position cursor_init(Plane *plane) {
  size_t row = 0, col = 0;
  if (plane->start != NULL) {
    plane->cursor = plane->start;
    if (plane->cursor->down != NULL) {
      plane->cursor = plane->cursor->down;
      row++;
    }
    if (plane->cursor->right != NULL) {
      plane->cursor = plane->cursor->right;
      col++;
    }
  } else {
    plane->cursor = NULL;
  }
  if (row == 1 && col == 1) {
    return (Position) {.row = 1, .col = 1};
  } else {
    return (Position) {.row = 0, .col = 0};
  }
}

/*
 * Returns the current cursor position.
 */
Position cursor_pos(Plane *plane) {
  int row = 0, col = 0;
  Box *current = plane->cursor;
  if (current != NULL) {
    while (current->left != NULL) {
      current = current->left;
      col++;
    }
    while (current->up != NULL) {
      current = current->up;
      row++;
    }
  }
  return (Position) {.row = row, .col = col};
}

/*
 * Moves cursor one box to the right.
 * If the box to the right contains a vertical line, then the cursor jumps over it,
 * except a case when after this line there are no more cells.
 */
void cursor_move_right(Plane *plane) {
  if (plane->cursor != NULL && plane->cursor->right != NULL) {
    if is_vert_line_left(plane->cursor->right->ch) {
      if (plane->cursor->right->right != NULL && !is_box_drawing_character(plane->cursor->right->right->ch)) {
        plane->cursor = plane->cursor->right->right;
      }
    } else {
      plane->cursor = plane->cursor->right;
    }
  }
}

/*
 * Moves cursor one box to the left.
 * If the box to the left contains a vertical line, then the cursor jumps over it,
 * except a case when before this line there are no more cells.
 */
void cursor_move_left(Plane *plane) {
  if (plane->cursor != NULL && plane->cursor->left != NULL) {
    if is_vert_line_right(plane->cursor->left->ch) {
      if (plane->cursor->left->left != NULL && !is_box_drawing_character(plane->cursor->left->left->ch)) {
        plane->cursor = plane->cursor->left->left;
      }
    } else {
      plane->cursor = plane->cursor->left;
    }
  }
}

/*
 * Moves cursor one box up.
 * If the box above contains a horizontal line, then the cursor jumps over it,
 * except a case when above this line there are no more cells.
 */
void cursor_move_up(Plane *plane) {
  if (plane->cursor != NULL && plane->cursor->up != NULL) {
    if is_horz_line_bottom(plane->cursor->up->ch) {
      if (plane->cursor->up->up != NULL && !is_box_drawing_character(plane->cursor->up->up->ch)) {
        plane->cursor = plane->cursor->up->up;
      }
    } else {
      plane->cursor = plane->cursor->up;
    }
  }
}

/*
 * Moves cursor one box down.
 * If the box below contains a vertical line, then the cursor jumps over it,
 * except a case when below this line there are no more cells.
 */
void cursor_move_down(Plane *plane) {
  if (plane->cursor != NULL && plane->cursor->down != NULL) {
    if is_horz_line_top(plane->cursor->down->ch) {
      if (plane->cursor->down->down != NULL && !is_box_drawing_character(plane->cursor->down->down->ch)) {
        plane->cursor = plane->cursor->down->down;
      }
    } else {
      plane->cursor = plane->cursor->down;
    }
  }
}

/*
 * Moves cursor to the beginning of the current cell.
 */
void cursor_move_cell_start(Plane *plane) {
  while (plane->cursor != NULL && plane->cursor->left != NULL &&
         !is_box_drawing_character(plane->cursor->left->ch)) {
    plane->cursor = plane->cursor->left;
  }
}

/*
 * Moves cursor to the end of the current cell.
 */
void cursor_move_cell_end(Plane *plane) {
  while (plane->cursor != NULL && plane->cursor->right != NULL &&
         !is_box_drawing_character(plane->cursor->right->ch)) {
    plane->cursor = plane->cursor->right;
  }
}

/*
 * Moves cursor to the top of the current cell.
 */
void cursor_move_cell_top(Plane *plane) {
  while (plane->cursor != NULL && plane->cursor->up != NULL &&
         !is_box_drawing_character(plane->cursor->up->ch)) {
    plane->cursor = plane->cursor->up;
  }
}

/*
 * Moves cursor to the bottom of the current cell.
 */
void cursor_move_cell_bottom(Plane *plane) {
  while (plane->cursor != NULL && plane->cursor->down != NULL &&
         !is_box_drawing_character(plane->cursor->down->ch)) {
    plane->cursor = plane->cursor->down;
  }
}

/*
 * Moves cursor to the beginning of the table.
 */
void cursor_move_table_start(Plane *plane) {
  Box *box = plane->cursor, *last = NULL;
  while (box != NULL && box->left != NULL) {
    if (!is_box_drawing_character(box->ch)) last = box;
    if (box->left->left == NULL) break;
    box = box->left;
  }
  plane->cursor = is_box_drawing_character(box->ch) ? last : box;
}

/*
 * Moves cursor to the end of the table.
 */
void cursor_move_table_end(Plane *plane) {
  Box *box = plane->cursor, *last = NULL;
  while (box != NULL && box->right != NULL) {
    if (!is_box_drawing_character(box->ch)) last = box;
    if (box->right->right == NULL) break;
    box = box->right;
  }
  plane->cursor = is_box_drawing_character(box->ch) ? last : box;
}

/*
 * Moves cursor to the top of the table.
 */
void cursor_move_table_top(Plane *plane) {
  Box *box = plane->cursor, *last = NULL;
  while (box != NULL && box->up != NULL) {
    if (!is_box_drawing_character(box->ch)) last = box;
    if (box->up->up == NULL) break;
    box = box->up;
  }
  plane->cursor = is_box_drawing_character(box->ch) ? last : box;
}

/*
 * Moves cursor to the end of the table.
 */
void cursor_move_table_bottom(Plane *plane) {
  Box *box = plane->cursor, *last = NULL;
  while (box != NULL && box->down != NULL) {
    if (!is_box_drawing_character(box->ch)) last = box;
    if (box->down->down == NULL) break;
    box = box->down;
  }
  plane->cursor = is_box_drawing_character(box->ch) ? last : box;
}

bool is_whitespace_column_before_vert_line(Box *pos) {
  Box *row = pos, *box = NULL;
  while (row->up != NULL && !IS_JOIN(row->attr)) {
    row = row->up;
  }
  while (row != NULL) {
    // check the character, if box-drawing then skip this row
    if (!is_box_drawing_character(row->ch)) {
      box = row;
      move_to_vert_line_crossing(box);
      // if there is no whitespace before vertical line, then no further checking is needed
      if (!is_whitespace(box->ch)) return false;
      // if there is a whitespace, but just between two box-drawing characters, then no further checking is needed
      if (box->left != NULL && is_box_drawing_character(box->left->ch)) return false;
    }
    row = row->down;
  }
  return true;
}

/*
 * Inserts a character at the current cursor position.
 * Starting from current cursor position, all characters in the cell are shifted to the right.
 * If there is no enough space for a new character, the cell is appended with one additional whitespace.
 * All cells in the same column of the table are also appended with a single whitespace when needed.
 */
void insert_char(Plane *plane, wchar_t ch) {
  if (plane->cursor == NULL) return;
  Box *box = NULL, *row = NULL, *current = plane->cursor;
  // move to the right (sic!) until left (sic!) vertical line is encountered
  move_to_vert_line_left(current);
  if (is_whitespace(current->ch) && current != plane->cursor) {
    // there is a whitespace before the vertical line,
    // all characters starting from current cursor position may be simply shifted right
    while (current != plane->cursor) {
      current->ch = current->left->ch;
      current = current->left;
    }
  } else {
    // There is no whitespace before the vertical line or the cursor is placed just before the vertical line.
    // A column of whitespaces must be inserted before the vertical line.
    row = current;
    while (row->up != NULL && !IS_JOIN(row->attr)) {
      row = row->up;
    }
    while (row != NULL) {
      box = row;
      move_to_vert_line_crossing(box);
      wchar_t new_char = WS;
      if is_single_vert_line_crossing(box->right->ch) new_char = SINGLE_HORZ_LINE;
      if is_double_vert_line_crossing(box->right->ch) new_char = DOUBLE_HORZ_LINE;
      Box *ws = box_new(new_char);
      ws->left = box;
      ws->right = box->right;
      box->right->left = ws;
      box->right = ws;
      ws->attr = box->attr;
      if (row->down != NULL && IS_JOIN(row->down->attr)) break;
      row = row->down;
    }
    // shift all characters the in the current line to the right
    box = plane->cursor;
    move_to_vert_line_left(box);
    while (box != plane->cursor) {
      box->ch = box->left->ch;
      box = box->left;
    }
  }
  // new character replaces the character under the cursor
  plane->cursor->ch = ch;
}

/*
 * Deletes a character at the current cursor position.
 */
void delete_char(Plane *plane) {
  if (plane->cursor == NULL) return;
  Box *box = plane->cursor, *row = NULL, *current = NULL;
  // shift all characters left starting at the current cursor position
  // and ending before the next box-drawing character,
  // place a whitespace just before the box-drawing character
  while (box->right != NULL && !is_box_drawing_character(box->right->ch)) {
    box->ch = box->right->ch;
    box = box->right;
  }
  box->ch = WS;
  // move to the top of the information item name or table body
  row = plane->cursor;
  while (row->up != NULL && !IS_JOIN(row->attr)) {
    row = row->up;
  }
  if (is_whitespace_column_before_vert_line(plane->cursor)) {

  }
}