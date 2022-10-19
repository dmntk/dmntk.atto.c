#define NCURSES_WIDECHAR 1

#include <locale.h>
#include <ncurses.h>
#include <string.h>

#include "editor.h"
#include "glyphs.h"

#define match_key(actual, expected) (strcmp(actual, expected) == 0)

/*
 * Keystroke definitions.
 */
#define KEY_NAME_BACKSPACE  "KEY_BACKSPACE"
#define KEY_NAME_CTRL_Q  "^Q"
#define KEY_NAME_DELETE  "KEY_DC"
#define KEY_NAME_DOWN    "KEY_DOWN"
#define KEY_NAME_F1      "KEY_F(1)"
#define KEY_NAME_LEFT    "KEY_LEFT"
#define KEY_NAME_RIGHT   "KEY_RIGHT"
#define KEY_NAME_UP      "KEY_UP"

#define is_key_resize(key_name)  match_key(key_name, "KEY_RESIZE")

/*
 * Names of available editor actions.
 */
typedef enum EditorActionType_t {
  CursorMoveDown,
  CursorMoveLeft,
  CursorMoveRight,
  CursorMoveUp,
  DeleteChar,
  DeleteCharBefore,
  InsertChar,
  Nop,
  Quit,
  ShowHelp,
  SplitLine,
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
 * Displays debug message.
 */
void debug(Editor *editor, const char *format, ...) {
  char buffer[2000];
  va_list args;
  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);
  int x = getcurx(editor->window);
  int y = getcury(editor->window);
  mvwaddstr(editor->window, editor->height - 2, 1, buffer);
  waddstr(editor->window, "                                                                              ");
  wmove(editor->window, y, x);
}

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
  werase(editor->window);
  Box *box = NULL, *row = editor->plane->start;
  int x = 0, y = 0, col_count = 0, row_count = 0;
  for (int i = editor->offset_y; i > 0 && row->down != NULL; --i) row = row->down;
  while (row != NULL && row_count < editor->height - 1) {
    box = row;
    for (int i = editor->offset_x; i > 0 && box != NULL; --i) box = box->right;
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
 * Updates cursor coordinates displayed in status bar.
 */
void update_cursor_coordinates(Editor *editor, int cur_pos_x, int cur_pos_y, int x, int y) {
  char buffer[200];
  sprintf(buffer, "    %d:%d (%d:%d) [%d:%d] ", cur_pos_x, cur_pos_y, x, y, editor->width, editor->height);
  int pos_x = editor->width - (int) strlen(buffer);
  for (int i = 0; i < pos_x; ++i) mvwaddnwstr(editor->window, editor->height - 1, i, WSS, 1);
  mvwaddstr(editor->window, editor->height - 1, pos_x, buffer);
}

/*
 * Updates cursor position.
 */
void update_cursor(Editor *editor) {
  Position cur_pos = cursor_pos(editor->plane);
  int x = cur_pos.col - editor->offset_x;
  int y = cur_pos.row - editor->offset_y;
  update_cursor_coordinates(editor, cur_pos.col, cur_pos.row, x, y);
  wmove(editor->window, y, x);
}

/*
 * Updates cursor position.
 */
void update_cursor_x(Editor *editor, int cur_pos_x, int cur_pos_y) {
  int x = cur_pos_x - editor->offset_x;
  int y = cur_pos_y - editor->offset_y;
  update_cursor_coordinates(editor, cur_pos_x, cur_pos_y, x, y);
  wmove(editor->window, y, x);
}

/*
 * Updates cursor position after resizing a window.
 */
void update_cursor_after_resize(Editor *editor) {
  // TODO
}

/*
 * Action that performs moving cursor to the right.
 */
void action_cursor_move_right(Editor *editor) {
  cursor_move_right(editor->plane);
  Position cur_pos = cursor_pos(editor->plane);
  if (cur_pos.col - editor->offset_x > editor->width - 2) {
    editor->offset_x = cur_pos.col - editor->width + 2;
    repaint_plane(editor);
  }
  update_cursor_x(editor, cur_pos.col, cur_pos.row);
  wrefresh(editor->window);
}

/*
 * Action that performs moving cursor to the left.
 */
void action_cursor_move_left(Editor *editor) {
  cursor_move_left(editor->plane);
  Position cur_pos = cursor_pos(editor->plane);
  if (cur_pos.col - editor->offset_x < 1) {
    editor->offset_x = cur_pos.col - 1;
    repaint_plane(editor);
  }
  update_cursor_x(editor, cur_pos.col, cur_pos.row);
  wrefresh(editor->window);
}

/*
 * Action that performs moving cursor down.
 */
void action_cursor_move_down(Editor *editor) {
  cursor_move_down(editor->plane);
  Position cur_pos = cursor_pos(editor->plane);
  if (cur_pos.row - editor->offset_y > editor->height - 3) {
    editor->offset_y = cur_pos.row - editor->height + 3;
    repaint_plane(editor);
  }
  update_cursor_x(editor, cur_pos.col, cur_pos.row);
  wrefresh(editor->window);
}

/*
 * Action that performs moving cursor up.
 */
void action_cursor_move_up(Editor *editor) {
  cursor_move_up(editor->plane);
  Position cur_pos = cursor_pos(editor->plane);
  if (cur_pos.row - editor->offset_y < 1) {
    editor->offset_y = cur_pos.row - 1;
    repaint_plane(editor);
  }
  update_cursor_x(editor, cur_pos.col, cur_pos.row);
  wrefresh(editor->window);
}

/*
 *
 */
EditorAction map_key_to_editor_action(Editor *editor, int ch) {
  const char *key_name = keyname(ch);
  if (key_name != NULL) {
    if match_key(key_name, KEY_NAME_BACKSPACE) return (EditorAction) {.type = DeleteCharBefore, .ch = 0};
    if match_key(key_name, KEY_NAME_CTRL_Q) return (EditorAction) {.type = Quit, .ch = 0};
    if match_key(key_name, KEY_NAME_DELETE) return (EditorAction) {.type = DeleteChar, .ch = 0};
    if match_key(key_name, KEY_NAME_DOWN) return (EditorAction) {.type = CursorMoveDown, .ch = 0};
    if match_key(key_name, KEY_NAME_F1) return (EditorAction) {.type = ShowHelp, .ch = 0};
    if match_key(key_name, KEY_NAME_LEFT) return (EditorAction) {.type = CursorMoveLeft, .ch = 0};
    if match_key(key_name, KEY_NAME_UP) return (EditorAction) {.type = CursorMoveUp, .ch = 0};
    if match_key(key_name, KEY_NAME_RIGHT) return (EditorAction) {.type = CursorMoveRight, .ch = 0};
    if (is_key_resize(key_name)) return (EditorAction) {.type = WindowResize, .ch = 0};
  }
  if (ch == 10) return (EditorAction) {.type = SplitLine, .ch = 0};
  if (ch >= 32 && ch <= 126) return (EditorAction) {.type = InsertChar, .ch = (wchar_t) ch};
  if (ch == 127) return (EditorAction) {.type = DeleteChar, .ch = 0};
  // TODO remove when not needed any more
  if (key_name != NULL) {
    debug(editor, "%d %s", ch, key_name);
  } else {
    debug(editor, "%d", ch);
  }
  return (EditorAction) {.type = Nop, .ch = 0};
}

/*
 * Processes keystrokes.
 */
void process_keystrokes(Editor *editor) {
  while (true) {
    EditorAction editor_action = map_key_to_editor_action(editor, getch());
    switch (editor_action.type) {
      case CursorMoveRight:
        action_cursor_move_right(editor);
        break;
      case CursorMoveLeft:
        action_cursor_move_left(editor);
        break;
      case CursorMoveDown:
        action_cursor_move_down(editor);
        break;
      case CursorMoveUp:
        action_cursor_move_up(editor);
        break;
      case DeleteChar:
        debug(editor, "DeleteChar");
        break;
      case DeleteCharBefore:
        debug(editor, "DeleteCharBefore");
        break;
      case InsertChar:
        insert_char(editor->plane, editor_action.ch);
        fix_vert_pointers(editor->plane);
        repaint_plane(editor);
        action_cursor_move_right(editor);
        //cursor_move_right(editor->plane);
        //update_cursor(editor);
        //wrefresh(editor->window);
        break;
      case Quit:
        return;
      case ShowHelp:
        debug(editor, "ShowHelp");
        break;
      case SplitLine:
        debug(editor, "SplitLine");
        break;
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
