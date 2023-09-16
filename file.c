#include "file.h"
#include <stdlib.h>

file_t *new_file(const char *filename, const size_t filename_length,
                 int file_start_index) {
  file_t *file = (file_t *)malloc(sizeof(file_t));
  file->filename = filename;
  file->file_start_index = file_start_index;
  file->filename_length = filename_length;
  return file;
}
