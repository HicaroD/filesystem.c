#ifndef FILE_H
#define FILE_H

#include <stdlib.h>

typedef struct file {
  char *filename; // Obs.: O nome do arquivo é o mesmo que o conteúdo dele
  int file_start_index;
} file_t;

#endif // FILE_H
