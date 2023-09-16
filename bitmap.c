#include "bitmap.h"

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

int get_next_free_block_index_from_bitmap(int *bitmap, int start_index) {
  for (int i = start_index; i < DISK_SIZE; i++) {
    if (bitmap[i]) {
      return i;
    }
  }
  return -1;
}
