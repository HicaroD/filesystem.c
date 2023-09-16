#include "block.h"

block_t *new_disk() {
  block_t *disk = (block_t *)malloc(DISK_SIZE * sizeof(block_t));
  if (disk == NULL) {
    fprintf(stderr, "Unable to allocate disk space");
    exit(1);
  }
  for (int i = 0; i < DISK_SIZE; i++) {
    disk[i].data = '0';
    disk[i].next = -1;
  }
  return disk;
}
