#define NCURSES_WIDECHAR 1

#include <locale.h>
#include <ncurses.h>

#include "editor.h"

/*
 * Initializes the terminal.
 */
WINDOW *initialize_terminal() {
  WINDOW *window = initscr();
  raw();
  keypad(window, true);
  noecho();
  return window;
}

/*
 * Finalizes the terminal.
 */
void finalize_terminal() {
  endwin();
}

/*
 * Creates a new editor with the content loaded from file.
 */
Editor *editor_new(const char file_name[static 1]) {
  Editor *editor;
  Plane *plane;
  WINDOW *window;
  if ((plane = load_plane_from_file(file_name)) == NULL) return NULL;
  plane_init(plane);
  cursor_init(plane);
  if ((window = initialize_terminal()) == NULL) return NULL;
  editor = malloc(sizeof(Editor));
  editor->window = window;
  editor->plane = plane;
  return editor;
}

/*
 * Deletes the editor.
 */
void editor_delete(Editor *editor) {
  finalize_terminal();
  delete_plane(editor->plane);
  free(editor);
}

/* Repaints the plane. */
void repaint_plane(Editor *editor) {
  Box *box, *row = editor->plane->start;
  int row_index = 0, col_index = 0;
  while (row != NULL) {
    box = row;
    while (box != NULL) {
      mvaddnwstr(row_index, col_index, &box->ch, 1);
      box = box->right;
      col_index++;
    }
    row = row->down;
    row_index++;
    col_index = 0;
  }
}

/* Processes keystrokes. */
void process_keystrokes(Editor *editor) {
  getch();
}

/*
 * Starts editing.
 */
void editor_run(Editor *editor) {
  repaint_plane(editor);
  process_keystrokes(editor);
}
