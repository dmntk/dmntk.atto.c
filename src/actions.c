#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include "actions.h"

/* Application name. */
static char app_name[] = "plane";

/* Application version. */
const char *argp_program_version = "v0.0.2";

/* Application bug reporting address. */
const char *argp_program_bug_address = "<plane@plane.io>";

/* Application description. */
static char doc[] = "plane";

/* A description of the application arguments. */
static char args_doc[] = "INPUT_FILE";

/* Application has no options. */
static struct argp_option options[] = {
    {0}
};

/*
 * Structure used by `main` to communicate with `parse_arguments` function.
 */
struct CliArgs {
  char *args[1];   // name of the input file
};

/*
 * Prints the usage message.
 */
void app_error_and_usage(const char message[static 1]) {
  fprintf(stderr, "%s: %s\n", app_name, message);
  fprintf(stderr, "Usage: %s INPUT_FILE\n", app_name);
  fprintf(stderr, "Try `%s --help' or `%s --usage' for more information.\n", app_name, app_name);
  exit(EXIT_FAILURE);
}

/* Parses application arguments. */
static error_t parser(int key, char *arg, struct argp_state *state) {
  struct CliArgs *cli_args = state->input;
  switch (key) {
    case ARGP_KEY_ARG:
      if (state->arg_num > 0) app_error_and_usage("too many arguments");
      cli_args->args[state->arg_num] = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 1) app_error_and_usage("not enough arguments");
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

/* Argument parser. */
static struct argp argp = {options, parser, args_doc, doc};

/*
 * Processes command line arguments and returns the action to be invoked.
 */
struct Action get_action(int argc, char *argv[]) {
  struct CliArgs cli_args;
  argp_parse(&argp, argc, argv, 0, 0, &cli_args);
  return (struct Action) {.type = EditFile, .file_name = cli_args.args[0]};
}
