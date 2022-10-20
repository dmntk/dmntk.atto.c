#define NCURSES_WIDECHAR 1

#if NCURSES_WIDECHAR

// include and use ncurses only when wide characters are available
#include <ncurses.h>

#endif

#include <locale.h>
#include <string.h>

#include "editor.h"
#include "glyphs.h"

/*
 * Key names.
 */
#define KEY_NAME_BACKSPACE      "KEY_BACKSPACE"
#define KEY_NAME_CONTROL_HOME   "kHOM5"
#define KEY_NAME_CONTROL_END    "kEND5"
#define KEY_NAME_CONTROL_PG_DN  "kNXT5"
#define KEY_NAME_CONTROL_PG_UP  "kPRV5"
#define KEY_NAME_CONTROL_Q      "^Q"
#define KEY_NAME_DELETE         "KEY_DC"
#define KEY_NAME_DOWN           "KEY_DOWN"
#define KEY_NAME_END            "KEY_END"
#define KEY_NAME_F1             "KEY_F(1)"
#define KEY_NAME_HOME           "KEY_HOME"
#define KEY_NAME_LEFT           "KEY_LEFT"
#define KEY_NAME_PG_DN          "KEY_NPAGE"
#define KEY_NAME_PG_UP          "KEY_PPAGE"
#define KEY_NAME_RESIZE         "KEY_RESIZE"
#define KEY_NAME_RIGHT          "KEY_RIGHT"
#define KEY_NAME_SHIFT_TAB      "KEY_BTAB"
#define KEY_NAME_TAB            "^I"
#define KEY_NAME_UP             "KEY_UP"

/*
 * Compares key names.
 */
#define match_key(actual, expected) (strcmp(actual, expected) == 0)

/*
 * Key checks.
 */
#define is_key_backspace(key_name)      match_key(key_name, KEY_NAME_BACKSPACE)
#define is_key_control_end(key_name)    match_key(key_name, KEY_NAME_CONTROL_END)
#define is_key_control_home(key_name)   match_key(key_name, KEY_NAME_CONTROL_HOME)
#define is_key_control_pg_dn(key_name)  match_key(key_name, KEY_NAME_CONTROL_PG_DN)
#define is_key_control_pg_up(key_name)  match_key(key_name, KEY_NAME_CONTROL_PG_UP)
#define is_key_control_q(key_name)      match_key(key_name, KEY_NAME_CONTROL_Q)
#define is_key_delete(key_name)         match_key(key_name, KEY_NAME_DELETE)
#define is_key_down(key_name)           match_key(key_name, KEY_NAME_DOWN)
#define is_key_end(key_name)            match_key(key_name, KEY_NAME_END)
#define is_key_f1(key_name)             match_key(key_name, KEY_NAME_F1)
#define is_key_home(key_name)           match_key(key_name, KEY_NAME_HOME)
#define is_key_left(key_name)           match_key(key_name, KEY_NAME_LEFT)
#define is_key_pg_dn(key_name)          match_key(key_name, KEY_NAME_PG_DN)
#define is_key_pg_up(key_name)          match_key(key_name, KEY_NAME_PG_UP)
#define is_key_resize(key_name)         match_key(key_name, KEY_NAME_RESIZE)
#define is_key_right(key_name)          match_key(key_name, KEY_NAME_RIGHT)
#define is_key_shift_tab(key_name)      match_key(key_name, KEY_NAME_SHIFT_TAB)
#define is_key_tab(key_name)            match_key(key_name, KEY_NAME_TAB)
#define is_key_up(key_name)             match_key(key_name, KEY_NAME_UP)

/*
 * Names of available editor actions.
 */
typedef enum EditorActionType_t {
  CursorMoveCellStart,
  CursorMoveCellEnd,
  CursorMoveCellTop,
  CursorMoveCellBottom,
  CursorMoveCellLeft,
  CursorMoveCellRight,
  CursorMoveDown,
  CursorMoveLeft,
  CursorMoveRight,
  CursorMoveUp,
  CursorMoveTableStart,
  CursorMoveTableEnd,
  CursorMoveTableTop,
  CursorMoveTableBottom,
  DeleteChar,
  DeleteCharBefore,
  InsertChar,
  Nop,
  Quit,
  ShowHelp,
  SplitLine,
  ResizeWindow
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
void update_cursor_coordinates(Editor *editor, const Position *cur_pos, int x, int y) {
  char buffer[200];
  sprintf(buffer, "    %d:%d (%d:%d) [%d:%d] ", cur_pos->col, cur_pos->row, x, y, editor->width, editor->height);
  int pos_x = editor->width - (int) strlen(buffer);
  for (int i = 0; i < pos_x; ++i) mvwaddnwstr(editor->window, editor->height - 1, i, WSS, 1);
  mvwaddstr(editor->window, editor->height - 1, pos_x, buffer);
}

/*
 * Updates cursor position on terminal screen.
 */
void update_cursor(Editor *editor, const Position *cur_pos) {
  int x = cur_pos->col - editor->offset_x;
  int y = cur_pos->row - editor->offset_y;
  update_cursor_coordinates(editor, cur_pos, x, y);
  wmove(editor->window, y, x);
}

/*
 * Updates cursor position after moving to the right.
 */
void update_cursor_after_moving_right(Editor *editor) {
  Position cur_pos = cursor_pos(editor->plane);
  if (cur_pos.col - editor->offset_x > editor->width - 2) {
    editor->offset_x = cur_pos.col - editor->width + 2;
    repaint_plane(editor);
  }
  update_cursor(editor, &cur_pos);
}

/*
 * Updates cursor position after moving to the left.
 */
void update_cursor_after_moving_left(Editor *editor) {
  Position cur_pos = cursor_pos(editor->plane);
  if (cur_pos.col - editor->offset_x < 1) {
    editor->offset_x = cur_pos.col - 1;
    repaint_plane(editor);
  }
  update_cursor(editor, &cur_pos);
}

/*
 * Updates cursor position after moving up.
 */
void update_cursor_after_moving_up(Editor *editor) {
  Position cur_pos = cursor_pos(editor->plane);
  if (cur_pos.row - editor->offset_y < 1) {
    editor->offset_y = cur_pos.row - 1;
    repaint_plane(editor);
  }
  update_cursor(editor, &cur_pos);
}

/*
 * Updates cursor position after moving down.
 */
void update_cursor_after_moving_down(Editor *editor) {
  Position cur_pos = cursor_pos(editor->plane);
  if (cur_pos.row - editor->offset_y > editor->height - 3) {
    editor->offset_y = cur_pos.row - editor->height + 3;
    repaint_plane(editor);
  }
  update_cursor(editor, &cur_pos);
}

/*
 * Updates cursor position after resizing a window.
 */
void update_cursor_after_resize(Editor *editor) {
  // TODO implement updating the cursor position while window resizing
  repaint_plane(editor);
  wrefresh(editor->window);
}

/*
 * Action that performs moving cursor to the next cell to the right from current.
 */
void action_cursor_move_cell_right(Editor *editor) {
  cursor_move_cell_end(editor->plane);
  cursor_move_right(editor->plane);
  update_cursor_after_moving_right(editor);
}

/*
 * Action that performs moving cursor to the previous cell to the left from current.
 */
void action_cursor_move_cell_left(Editor *editor) {
  cursor_move_cell_start(editor->plane);
  cursor_move_left(editor->plane);
  update_cursor_after_moving_left(editor);
}

void action_cursor_move_cell_start(Editor *editor) {
  cursor_move_cell_start(editor->plane);
  update_cursor_after_moving_left(editor);
}

void action_cursor_move_cell_end(Editor *editor) {
  cursor_move_cell_end(editor->plane);
  update_cursor_after_moving_right(editor);
}

void action_cursor_move_cell_top(Editor *editor) {
  cursor_move_cell_top(editor->plane);
  update_cursor_after_moving_up(editor);
}

void action_cursor_move_cell_bottom(Editor *editor) {
  cursor_move_cell_bottom(editor->plane);
  update_cursor_after_moving_down(editor);
}

void action_cursor_move_table_start(Editor *editor) {
  cursor_move_table_start(editor->plane);
  update_cursor_after_moving_left(editor);
}

void action_cursor_move_table_end(Editor *editor) {
  cursor_move_table_end(editor->plane);
  update_cursor_after_moving_right(editor);
}

void action_cursor_move_table_top(Editor *editor) {
  cursor_move_table_top(editor->plane);
  update_cursor_after_moving_up(editor);
}

void action_cursor_move_table_bottom(Editor *editor) {
  cursor_move_table_bottom(editor->plane);
  update_cursor_after_moving_down(editor);
}

/*
 * Action that performs moving cursor to the right.
 */
void action_cursor_move_right(Editor *editor) {
  cursor_move_right(editor->plane);
  update_cursor_after_moving_right(editor);
}

/*
 * Action that performs moving cursor to the left.
 */
void action_cursor_move_left(Editor *editor) {
  cursor_move_left(editor->plane);
  update_cursor_after_moving_left(editor);
}

/*
 * Action that performs moving cursor down.
 */
void action_cursor_move_down(Editor *editor) {
  cursor_move_down(editor->plane);
  update_cursor_after_moving_down(editor);
}

/*
 * Action that performs moving cursor up.
 */
void action_cursor_move_up(Editor *editor) {
  cursor_move_up(editor->plane);
  update_cursor_after_moving_up(editor);
}

/*
 *
 */
void action_delete_char(Editor *editor) {
  debug(editor, "DeleteChar");
}

/*
 *
 */
void action_delete_char_before(Editor *editor) {
  debug(editor, "DeleteCharBefore");
}

/*
 *
 */
void action_insert_char(Editor *editor, wchar_t ch) {
  insert_char(editor->plane, ch);
  fix_vert_pointers(editor->plane);
  repaint_plane(editor);
  action_cursor_move_right(editor);
}

/*
 *
 */
void action_show_help(Editor *editor) {
  debug(editor, "ShowHelp");
}

/*
 *
 */
void action_split_line(Editor *editor) {
  debug(editor, "SplitLine");
}

/*
 *
 */
EditorAction map_key_to_editor_action(Editor *editor, wchar_t ch, int status) {
  const char *key_name = keyname(ch);
  if (key_name != NULL) {
    if (is_key_backspace(key_name)) return (EditorAction) {.type = DeleteCharBefore, .ch = 0};
    if (is_key_control_end(key_name)) return (EditorAction) {.type = CursorMoveTableEnd, .ch = 0};
    if (is_key_control_home(key_name)) return (EditorAction) {.type = CursorMoveTableStart, .ch = 0};
    if (is_key_control_pg_dn(key_name)) return (EditorAction) {.type = CursorMoveTableBottom, .ch = 0};
    if (is_key_control_pg_up(key_name)) return (EditorAction) {.type = CursorMoveTableTop, .ch = 0};
    if (is_key_control_q(key_name)) return (EditorAction) {.type = Quit, .ch = 0};
    if (is_key_delete(key_name)) return (EditorAction) {.type = DeleteChar, .ch = 0};
    if (is_key_down(key_name)) return (EditorAction) {.type = CursorMoveDown, .ch = 0};
    if (is_key_end(key_name)) return (EditorAction) {.type = CursorMoveCellEnd, .ch = 0};
    if (is_key_f1(key_name)) return (EditorAction) {.type = ShowHelp, .ch = 0};
    if (is_key_home(key_name)) return (EditorAction) {.type = CursorMoveCellStart, .ch = 0};
    if (is_key_left(key_name)) return (EditorAction) {.type = CursorMoveLeft, .ch = 0};
    if (is_key_pg_dn(key_name)) return (EditorAction) {.type = CursorMoveCellBottom, .ch = 0};
    if (is_key_pg_up(key_name)) return (EditorAction) {.type = CursorMoveCellTop, .ch = 0};
    if (is_key_right(key_name)) return (EditorAction) {.type = CursorMoveRight, .ch = 0};
    if (is_key_resize(key_name)) return (EditorAction) {.type = ResizeWindow, .ch = 0};
    if (is_key_shift_tab(key_name)) return (EditorAction) {.type = CursorMoveCellLeft, .ch = 0};
    if (is_key_tab(key_name)) return (EditorAction) {.type = CursorMoveCellRight, .ch = 0};
    if (is_key_up(key_name)) return (EditorAction) {.type = CursorMoveUp, .ch = 0};
  }
  if (status == OK) {
    if (ch == 10) return (EditorAction) {.type = SplitLine, .ch = 0};
    if (ch >= 32 && ch <= 126) return (EditorAction) {.type = InsertChar, .ch = (wchar_t) ch};
    if (ch == 127) return (EditorAction) {.type = DeleteCharBefore, .ch = 0};
  }
  // TODO remove begin
  // remove when not needed anymore
  if (key_name != NULL) {
    debug(editor, "%d %s", ch, key_name);
  } else {
    debug(editor, "%d", ch);
  }
  // TODO remove end
  return (EditorAction) {.type = Nop, .ch = 0};
}

/*
 * Processes keystrokes.
 */
void process_keystrokes(Editor *editor) {
  while (true) {
    wint_t ch;
    int status = wget_wch(editor->window, &ch);
    EditorAction editor_action = map_key_to_editor_action(editor, (wchar_t) ch, status);
    switch (editor_action.type) {
      case CursorMoveCellRight:
        action_cursor_move_cell_right(editor);
        break;
      case CursorMoveCellLeft:
        action_cursor_move_cell_left(editor);
        break;
      case CursorMoveCellTop:
        action_cursor_move_cell_top(editor);
        break;
      case CursorMoveCellBottom:
        action_cursor_move_cell_bottom(editor);
        break;
      case CursorMoveCellStart:
        action_cursor_move_cell_start(editor);
        break;
      case CursorMoveCellEnd:
        action_cursor_move_cell_end(editor);
        break;
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
      case CursorMoveTableStart:
        action_cursor_move_table_start(editor);
        break;
      case CursorMoveTableEnd:
        action_cursor_move_table_end(editor);
        break;
      case CursorMoveTableTop:
        action_cursor_move_table_top(editor);
        break;
      case CursorMoveTableBottom:
        action_cursor_move_table_bottom(editor);
        break;
      case DeleteChar:
        action_delete_char(editor);
        break;
      case DeleteCharBefore:
        action_delete_char_before(editor);
        break;
      case InsertChar:
        action_insert_char(editor, editor_action.ch);
        break;
      case Quit:
        return;
      case ShowHelp:
        action_show_help(editor);
        break;
      case SplitLine:
        action_split_line(editor);
        break;
      case ResizeWindow:
        editor->width = getmaxx(editor->window);
        editor->height = getmaxy(editor->window);
        update_cursor_after_resize(editor);
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
  Position cur_pos = cursor_pos(editor->plane);
  update_cursor(editor, &cur_pos);
  wrefresh(editor->window);
  process_keystrokes(editor);
}
