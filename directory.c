#include "directory.h"
#include <stdio.h>
#include <string.h>

directory_h *new_directory() {
  directory_h *directory = malloc(sizeof(directory_h));
  directory->files =
      (file_t *)malloc(sizeof(file_t) * DIRECTORY_INITIAL_CAPACITY);
  directory->capacity = DIRECTORY_INITIAL_CAPACITY;
  directory->size = 0;
  return directory;
}

void append_file_to_directory(directory_h *directory, const file_t *file) {
  if (directory->size >= directory->capacity) {
    directory->capacity *= DIRECTORY_GROW_FACTOR;
    directory->files =
        realloc(directory->files, sizeof(file_t) * directory->capacity);
  }
  directory->files[directory->size] = *file;
  directory->size++;
}

// TODO: check if I'm removing it correctly
void remove_file_from_directory(directory_h *directory, file_t file) {
  int file_to_be_removed_index = find_file(directory, file);

  if (file_to_be_removed_index == -1) {
    fprintf(stderr, "Arquivo não encontrado no diretório\n");
    return;
  }

  for (size_t i = file_to_be_removed_index; i < directory->size - 1; i++) {
    directory->files[i] = directory->files[i + 1];
  }
  directory->size--;
  printf("Arquivo removido do diretório\n");
}

int find_file(directory_h *directory, const file_t file) {
  int file_to_be_removed_index = -1;

  for (size_t i = 0; i < directory->size; i++) {
    const char *current_filename = directory->files[i].filename;
    if (strcmp(file.filename, current_filename) == 0) {
      file_to_be_removed_index = i;
      break;
    }
  }

  return file_to_be_removed_index;
}
