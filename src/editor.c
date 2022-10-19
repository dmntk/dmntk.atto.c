#define NCURSES_WIDECHAR 1

#include <locale.h>
#include <ncurses.h>
#include <string.h>

#include "editor.h"

#define match_key(actual, expected) (strcmp(actual, expected) == 0)

/*
 * Keystroke definitions.
 */
#define KEY_NAME_CTRL_Q  "^Q"
#define KEY_NAME_DOWN    "KEY_DOWN"
#define KEY_NAME_LEFT    "KEY_LEFT"
#define KEY_NAME_RIGHT   "KEY_RIGHT"
#define KEY_NAME_UP      "KEY_UP"
//#define KN_END     "KEY_END"

#define is_key_resize(key_name)  match_key(key_name, "KEY_RESIZE")

/*
 * Names of available editor actions.
 */
typedef enum EditorActionType_t {
  CursorMoveDown,
  CursorMoveLeft,
  CursorMoveRight,
  CursorMoveUp,
  InsertChar,
  Nop,
  Quit,
  WindowResize
} EditorActionType;

/*
 * Editor action struct with additional attributes.
 */
typedef struct EditorAction_t {
  enum EditorActionType_t type; // name of the editor action
  wchar_t ch;                   // character read from user input
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
  editor->plane = plane;
  editor->window = window;
  editor->width = getmaxx(window);
  editor->height = getmaxy(window);
  editor->offset_x = 0;
  editor->offset_y = 0;
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
  Box *box = NULL, *row = editor->plane->start;
  int x = 0, y = 0, col_count = 0, row_count = 0;
  for (int i = editor->offset_y; i > 0 && row->down != NULL; --i) row = row->down;
  while (row != NULL && row_count < editor->height - 1) {
    box = row;
    for (int i = editor->offset_x; i > 0 && box->right != NULL; --i) box = box->right;
    while (box != NULL && col_count < editor->width) {
      mvwaddnwstr(editor->window, y, x, &box->ch, 1);
      box = box->right;
      col_count++;
      x++;
    }
    row = row->down;
    row_count++;
    col_count = 0;
    y++;
    x = 0;
  }
}

/*
 * Updates cursor position.
 */
void update_cursor(Editor *editor) {
  Position cur_pos = cursor_pos(editor->plane);
  int col = cur_pos.col;
  if (col >= editor->width - 2) {
    editor->offset_x = col - editor->width + 1;
    col = editor->width - 2;
    repaint_plane(editor);
  }
  int row = cur_pos.row;
//  if (row > editor->height - 1) {
//    editor->offset_y = row - editor->height + 1;
//    row = editor->height - 1;
//  }
  wmove(editor->window, row, col);
}

/*
 * Updates cursor position after resizing a window.
 */
void update_cursor_after_resize(Editor *editor) {
  // TODO
}

/*
 *
 */
EditorAction map_key_to_editor_action(int ch) {
  const char *key_name = keyname(ch);
  if (key_name != NULL) {
    if match_key(key_name, KEY_NAME_CTRL_Q) {
      return (EditorAction) {.type = Quit, .ch = 0};
    }
    if match_key(key_name, KEY_NAME_RIGHT) {
      return (EditorAction) {.type = CursorMoveRight, .ch = 0};
    }
    if match_key(key_name, KEY_NAME_LEFT) {
      return (EditorAction) {.type = CursorMoveLeft, .ch = 0};
    }
    if match_key(key_name, KEY_NAME_UP) {
      return (EditorAction) {.type = CursorMoveUp, .ch = 0};
    }
    if match_key(key_name, KEY_NAME_DOWN) {
      return (EditorAction) {.type = CursorMoveDown, .ch = 0};
    }
    if (is_key_resize(key_name)) return (EditorAction) {.type = WindowResize, .ch = 0};
    //printf("KEY_NAME = %s ", key_name);
  }
  if (ch >= 32 && ch <= 126) {
    return (EditorAction) {.type = InsertChar, .ch = (wchar_t) ch};
  }
  //printf("KEY = %d ", ch);
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
        wrefresh(editor->window);
        break;
      case CursorMoveLeft:
        cursor_move_left(editor->plane);
        update_cursor(editor);
        wrefresh(editor->window);
        break;
      case CursorMoveUp:
        cursor_move_up(editor->plane);
        update_cursor(editor);
        wrefresh(editor->window);
        break;
      case CursorMoveDown:
        cursor_move_down(editor->plane);
        update_cursor(editor);
        wrefresh(editor->window);
        break;
      case InsertChar:
        insert_char(editor->plane, editor_action.ch);
        fix_vert_pointers(editor->plane);
        repaint_plane(editor);
        cursor_move_right(editor->plane);
        update_cursor(editor);
        wrefresh(editor->window);
        break;
      case Quit:
        return;
      case WindowResize:
        editor->width = getmaxx(editor->window);
        editor->height = getmaxy(editor->window);
        //printf("[%d:%d] ", editor->width, editor->height);
        repaint_plane(editor);
        update_cursor_after_resize(editor);
        wrefresh(editor->window);
        break;
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
  wrefresh(editor->window);
  process_keystrokes(editor);
}
