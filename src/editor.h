#ifndef PLANE_EDITOR_H
#define PLANE_EDITOR_H

#include <ncurses.h>
#include <malloc.h>

#include "plane.h"

typedef struct Editor_t {
  Plane *plane;   // plane where the edited text is stored and manipulated
  WINDOW *window; // handle of the main window of the terminal
} Editor;

/* Creates a new editor with the content loaded from file. */
Editor *editor_new(const char file_name[static 1]);

/* Deletes the editor. */
void editor_delete(Editor *editor);

#endif // PLANE_EDITOR_H
