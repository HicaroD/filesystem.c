#include "directory.h"

directory_h *new_directory() {
  size_t initial_capacity = 2;
  directory_h *directory = malloc(sizeof(directory_h));
  directory->files = (file_t *)malloc(sizeof(file_t) * initial_capacity);
  directory->capacity = initial_capacity;
  directory->size = 0;
  return directory;
}

void append_file_to_directory(directory_h *vector, file_t value) {
  if (vector->size >= vector->capacity) {
    vector->capacity *= 2;
    vector->files = realloc(vector->files, sizeof(int) * vector->capacity);
  }
  vector->files[vector->size] = value;
  vector->size++;
}

// TODO
// void remove_file_from_directory(directory_h *directory, file_t *file) {}
