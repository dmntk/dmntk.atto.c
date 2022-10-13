#include <wchar.h>
#include "utils.h"

#define BLOCK_SIZE 512

/*
 * Loads the file content into string.
 */
wchar_t *load(const char file_name[]) {
  FILE *f;
  wchar_t buffer[BLOCK_SIZE];
  wchar_t* content = calloc(sizeof(wchar_t), BLOCK_SIZE);
  size_t capacity = BLOCK_SIZE; // total capacity of the allocated string
  size_t size = 0; // current size of the allocated string
  size_t len;      // length of the block read from file
  if ((f = fopen(file_name, "r")) == NULL) {
    fprintf(stderr, "failed to open file: %s", file_name);
    return NULL;
  }
  while (fgetws(buffer, BLOCK_SIZE, f) != NULL) {
    len = wcslen(buffer);
    if ((capacity - size) <= len) {
      capacity += BLOCK_SIZE;
      content = (wchar_t*)realloc(content, sizeof(wchar_t) * capacity);
    }
    wcscat(content, buffer);
    size = wcslen(content);
  }
  fclose(f);
  return content;
}