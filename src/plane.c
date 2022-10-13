#include <malloc.h>
#include <errno.h>
#include <wchar.h>

#include "plane.h"
#include "glyphs.h"

#define LOAD_BUFFER_SIZE 5000

/*
 * Creates a new empty plane.
 */
Plane *new_plane() {
  Plane *plane = malloc(sizeof(Plane));
  plane->start = NULL;
  plane->cursor = NULL;
  return plane;
}

/*
 * Loads a plane from specified file.
 */
Plane *load_plane_from_file(const char file_name[]) {
  FILE *f;
  wchar_t buffer[LOAD_BUFFER_SIZE];
  if ((f = fopen(file_name, "r")) == NULL) {
    fprintf(stderr, "failed to open file: %s", file_name);
    return NULL;
  }
  errno = 0;
  Box *row = NULL, *row_tail = NULL, *current = NULL;
  Plane *plane = new_plane();
  while (fgetws(buffer, LOAD_BUFFER_SIZE, f) != NULL) {
    int i = 0;
    while (buffer[i] != 0) {
      if (buffer[i] != '\n') {
        current = new_box(buffer[i]);
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
    fprintf(stderr, "an invalid wide character was encountered");
    fclose(f);
    delete_plane(plane);
    return NULL;
  }
  if (!feof(f)) {
    fprintf(stderr, "file read error");
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
 * Prints the content of the plane to standard output.
 */
void display_plane(const Plane *plane) {
  Box *current = NULL, *row = plane->start;
  while (row != NULL) {
    current = row;
    while (current != NULL) {
      printf("%lc", current->content);
      current = current->right;
    }
    printf("\n");
    row = row->down;
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
      *pos++ = current->content;
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
 * This function tries to position a cursor right below/right the top-left corner,
 * when the plane is not empty and contains minimum two rows and two columns,
 * then the starting cursor position is set to row = 1 and col = 1.
 */
CursorPos cursor_init(Plane *plane) {
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
  return (CursorPos) {.row = row, .col = col};
}

/*
 * Returns the current cursor position.
 */
CursorPos cursor_pos(Plane *plane) {
  size_t row = 0, col = 0;
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
  return (CursorPos) {.row = row, .col = col};
}

/*
 * Moves cursor one box to the right.
 * If the box to the right contains a vertical line, then the cursor jumps over it,
 * except a case when after this line there are no more cells.
 */
void cursor_move_right(Plane *plane) {
  if (plane->cursor != NULL && plane->cursor->right != NULL) {
    if IS_VERT_LINE(plane->cursor->right->content) {
      if (plane->cursor->right->right != NULL && !IS_VERT_LINE(plane->cursor->right->right->content)) {
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
    if IS_VERT_LINE(plane->cursor->left->content) {
      if (plane->cursor->left->left != NULL && !IS_VERT_LINE(plane->cursor->left->left->content)) {
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
    if IS_HORZ_LINE(plane->cursor->up->content) {
      if (plane->cursor->up->up != NULL && !IS_HORZ_LINE(plane->cursor->up->up->content)) {
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
    if IS_HORZ_LINE(plane->cursor->down->content) {
      if (plane->cursor->down->down != NULL && !IS_HORZ_LINE(plane->cursor->down->down->content)) {
        plane->cursor = plane->cursor->down->down;
      }
    } else {
      plane->cursor = plane->cursor->down;
    }
  }
}