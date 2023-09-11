#include "stdio.h"
#include "stdlib.h"

#define DISK_SIZE 32

typedef struct {
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

int main() {
  block_t *disk = new_disk();
  for (int i = 0; i < DISK_SIZE; i++)
    printf("%c\n", disk[i].data);

  free(disk); // NOTE: Na prática, você não iria desalocar o disco, obviamente
  return 0;
}
