#ifndef ATTO_EDITOR_H
#define ATTO_EDITOR_H

#include <ncurses.h>
#include <malloc.h>

#include "plane.h"

typedef enum EditorState_t {
  AttributesView,
  EditorView,
  HelpView,
  PointersView,
} EditorState;

typedef struct Editor_t {
  Plane *plane;       // plane where the edited text is stored and manipulated
  WINDOW *window;     // handle of the main window of the terminal
  int width;          // width of the terminal screen in characters
  int height;         // height of the terminal screen in characters
  int offset_x;       // horizontal offset of the terminal screen against the table
  int offset_y;       // vertical offset of the terminal screen against the table
  EditorState state;  // current state (view) of the editor
} Editor;

/* Creates a new editor with the content loaded from file. */
Editor *editor_new(const char file_name[static 1]);

/* Deletes the editor. */
void editor_delete(Editor *editor);

/* Starts editing. */
void editor_run(Editor *editor);

#endif // ATTO_EDITOR_H
