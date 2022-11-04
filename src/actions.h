#ifndef ATTO_ACTIONS_H
#define ATTO_ACTIONS_H

/*
 * Names of available actions.
 */
enum ActionType {
  EditFile, // open file to edit
};

/*
 * Actions struct with name and additional attributes.
 */
struct Action {
  enum ActionType type; // name of the action
  char *file_name;      // file name attribute
};

/* Processes command line arguments and returns the action to be invoked. */
struct Action get_action(int argc, char *argv[]);

#endif // ATTO_ACTIONS_H
