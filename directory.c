#include "directory.h"
#include <stdio.h>
#include <string.h>

directory_h *new_directory() {
  size_t initial_capacity = 2;
  directory_h *directory = malloc(sizeof(directory_h));
  directory->files = (file_t *)malloc(sizeof(file_t) * initial_capacity);
  directory->capacity = initial_capacity;
  directory->size = 0;
  return directory;
}

void append_file_to_directory(directory_h *vector, file_t file) {
  if (vector->size >= vector->capacity) {
    vector->capacity *= 2;
    vector->files = realloc(vector->files, sizeof(int) * vector->capacity);
  }
  vector->files[vector->size] = file;
  vector->size++;
}

void remove_file_from_directory(directory_h *directory, file_t file) {
  int file_to_be_removed_index = -1;
  for (size_t i = 0; i < directory->size; i++) {
    const char *current_filename = directory->files[i].filename;
    if (strcmp(file.filename, current_filename) == 0) {
      file_to_be_removed_index = i;
      break;
    }
  }

  if (file_to_be_removed_index) {
    fprintf(stderr, "Arquivo não encontrado no diretório\n");
    return;
  }

  for (size_t i = file_to_be_removed_index; i < directory->size - 1; i++) {
    directory->files[i] = directory->files[i + 1];
  }
  printf("Arquivo removido do diretório\n");
}
