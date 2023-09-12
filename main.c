#include "stdio.h"
#include "stdlib.h"
#include <string.h>

#define DISK_SIZE 32

typedef struct block {
  char data;
  struct block *next;
} block_t;

block_t *new_block(char data) {
  block_t *block = (block_t *)malloc(sizeof(block_t));
  if (block == NULL) {
    fprintf(stderr, "Unable to allocate a single block");
    exit(1);
  }
  block->data = data;
  block->next = NULL;
  return block;
}

block_t *new_disk() {
  block_t *disk = (block_t *)malloc(DISK_SIZE * sizeof(block_t));
  if (disk == NULL) {
    fprintf(stderr, "Unable to allocate disk space");
    exit(1);
  }
  for (int i = 0; i < DISK_SIZE; i++) {
    disk[i].data = '0';
  }
  return disk;
}

int *get_bitmap() {
  int *bitmap = (int *)malloc(DISK_SIZE * sizeof(int));
  if (bitmap == NULL) {
    fprintf(stderr, "Unable to allocate bitmap space");
    exit(1);
  }
  for (int i = 0; i < DISK_SIZE; i++) {
    bitmap[i] = 1;
  }
  return bitmap;
}

int has_not_enough_space_on_disk(int *bitmap, size_t file_length) {
  size_t available_space_counter = 0;
  for (size_t i = 0; i < DISK_SIZE; i++) {
    if (bitmap[i])
      available_space_counter++;

    if (available_space_counter >= file_length)
      return 0;
  }
  return 1;
}

int main() {
  block_t *disk = new_disk();
  int *bitmap = get_bitmap();

  while (1) {
    char input;
    scanf("%s", &input);

    if (input == 'E') {
      printf("Exiting program...\n");
      break;
    }

    switch (input) {
    // READ
    case 'R': {
      printf("READ WORD\n");
      break;
    }
    // WRITE
    case 'W': {
      char file[DISK_SIZE];
      scanf("%s", file);
      size_t file_length = strlen(file);

      if (has_not_enough_space_on_disk(bitmap, file_length)) {
        printf("Insufficient memory.\n");
        break;
      }

      // TODO: it has enough space, then store it
      break;
    }
    // DELETE
    case 'D': {
      printf("DELETE WORD\n");
      break;
    }
    default: {
      printf("INVALID COMMAND");
      break;
    }
    }
  }

  free(disk); // NOTE: Na prática, você não iria desalocar o disco, obviamente
  return 0;
}
