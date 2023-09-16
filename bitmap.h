#ifndef BITMAP_H
#define BITMAP_H

#include "block.h"
#include "stdio.h"
#include "stdlib.h"

int *get_bitmap();

int has_not_enough_space_on_disk(int *bitmap, size_t file_length);

int get_next_free_block_index_from_bitmap(int *bitmap, int start_index);

#endif
