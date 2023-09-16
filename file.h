#ifndef FILE_H
#define FILE_H

#include <stdlib.h>

typedef struct file {
  const char *filename; // Obs.: O nome do arquivo é o mesmo que o conteúdo dele
  int file_start_index;
} file_t;

file_t* new_file(const char* filename, int file_start_index);

#endif // FILE_H
