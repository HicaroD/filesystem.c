#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "file.h"
#include "stdio.h"
#include <stdlib.h>

typedef struct directory {
  file_t *files;
  size_t size;
  size_t capacity;
} directory_h;

directory_h *new_directory();

void append_file_to_directory(directory_h *directory, file_t file);

void remove_file_from_directory(directory_h *directory, file_t *file);

#endif // DIRECTORY_H
