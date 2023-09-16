#ifndef BLOCK_H
#define BLOCK_H

#include "stdio.h"
#include "stdlib.h"

#define DISK_SIZE 32

typedef struct block {
  char data;
  int next;
} block_t;

block_t *new_block(char data);

block_t *new_disk();

#endif
