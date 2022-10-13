#ifndef PLANE_UTILS_H
#define PLANE_UTILS_H

#include <string.h>
#include <malloc.h>

/* Concatenates two strings. */
char *concat(const char s1[], const char s2[]);

/* Loads the file content into string. */
wchar_t *load(const char file_name[]);

#endif // PLANE_UTILS_H
