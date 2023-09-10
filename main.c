#include "stdio.h"
#include "stdlib.h"

typedef struct {
  char data;
  struct block *next;
} Block;

Block *newBlock(char data) {
  Block *block = (Block *)malloc(sizeof(Block));
  block->data = data;
  block->next = NULL;
  return block;
}

int main() {
  Block *firstBlock = newBlock('a');
  printf("%c", firstBlock->data);
  return 0;
}
