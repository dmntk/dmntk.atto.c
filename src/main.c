#include <locale.h>
#include <stdlib.h>

#include "actions.h"
#include "editor.h"

/* Opens a file to edit. */
void edit_file(const char file_name[static 1]) {
  Editor *editor = NULL;
  if ((editor = editor_new(file_name)) == NULL) return;
  editor_run(editor);
  editor_delete(editor);
}

/*
 * Main entrypoint of the application.
 */
int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  struct Action action = get_action(argc, argv);
  switch (action.type) {
    case EditFile:
      edit_file(action.file_name);
      break;
    default:
      break;
  }
  return EXIT_SUCCESS;
}
