#define NCURSES_WIDECHAR 1

#include <locale.h>
#include <ncurses.h>
#include <string.h>

#include "editor.h"

/*
 * Keystroke definitions.
 */
#define KN_CTRL_Q  "^Q"
#define KN_DOWN    "KEY_DOWN"
#define KN_LEFT    "KEY_LEFT"
#define KN_RIGHT   "KEY_RIGHT"
#define KN_UP      "KEY_UP"

//#define KN_END     "KEY_END"

/*
 * Names of available editor actions.
 */
typedef enum EditorActionType_t {
  CursorMoveDown,
  CursorMoveLeft,
  CursorMoveRight,
  CursorMoveUp,
  Nop,
  Quit,
} EditorActionType;

/*
 * Editor action struct with additional attributes.
 */
typedef struct EditorAction_t {
  enum EditorActionType_t type; // name of the editor action
  wchar_t *ch;                // character read from user input
} EditorAction;

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

/*
 * Repaints the plane.
 */
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

/*
 * Updates cursor position.
 */
void update_cursor(Editor *editor) {
  Position cur_pos = cursor_pos(editor->plane);
  int row = (int) cur_pos.row;
  int col = (int) cur_pos.col;
  move(row, col);
}

/*
 *
 */
EditorAction map_key_to_editor_action(int ch) {
  const char *key_name = keyname(ch);
  if (key_name != NULL) {
    if (strcmp(key_name, KN_CTRL_Q) == 0) {
      return (EditorAction) {.type = Quit, .ch = 0};
    }
    if (strcmp(key_name, KN_RIGHT) == 0) {
      return (EditorAction) {.type = CursorMoveRight, .ch = 0};
    }
    if (strcmp(key_name, KN_LEFT) == 0) {
      return (EditorAction) {.type = CursorMoveLeft, .ch = 0};
    }
    if (strcmp(key_name, KN_UP) == 0) {
      return (EditorAction) {.type = CursorMoveUp, .ch = 0};
    }
    if (strcmp(key_name, KN_DOWN) == 0) {
      return (EditorAction) {.type = CursorMoveDown, .ch = 0};
    }
  } else {
    //
  }
  return (EditorAction) {.type = Nop, .ch = 0};
}

/*
 * Processes keystrokes.
 */
void process_keystrokes(Editor *editor) {
  while (true) {
    EditorAction editor_action = map_key_to_editor_action(getch());
    switch (editor_action.type) {
      case CursorMoveRight:
        cursor_move_right(editor->plane);
        update_cursor(editor);
        refresh();
        break;
      case CursorMoveLeft:
        cursor_move_left(editor->plane);
        update_cursor(editor);
        refresh();
        break;
      case CursorMoveUp:
        cursor_move_up(editor->plane);
        update_cursor(editor);
        refresh();
        break;
      case CursorMoveDown:
        cursor_move_down(editor->plane);
        update_cursor(editor);
        refresh();
        break;
      case Quit:
        return;
      case Nop:
      default:
        break;
    }
  }
}

/*
 * Starts editing.
 */
void editor_run(Editor *editor) {
  repaint_plane(editor);
  update_cursor(editor);
  refresh();
  process_keystrokes(editor);
}
