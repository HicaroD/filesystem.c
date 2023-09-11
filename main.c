#include "stdio.h"
#include "stdlib.h"

#define DISK_SIZE 32

typedef struct {
  char data;
  struct block *next;
} Block;

Block *newBlock(char data) {
  Block *block = (Block *)malloc(sizeof(Block));
  if (block == NULL) {
    fprintf(stderr, "Unable to allocate a single block");
    exit(1);
  }
  block->data = data;
  block->next = NULL;
  return block;
}

Block *newDisk() {
  Block *disk = (Block *)malloc(DISK_SIZE * sizeof(Block));
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
  Block *disk = newDisk();
  for (int i = 0; i < DISK_SIZE; i++)
    printf("%c\n", disk[i].data);

  free(disk); // NOTE: Na prática, você não iria desalocar o disco, obviamente
  return 0;
}
