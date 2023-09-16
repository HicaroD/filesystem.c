#include "block.h"
#include "bitmap.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

typedef struct file {
  char *filename; // Obs.: O nome do arquivo é o mesmo que o conteúdo dele
  int file_start_index;
} file_t;

int main() {
  block_t *disk = new_disk();
  int *bitmap = get_bitmap();

  while (1) {
    printf("Escolha um comando: \nW - Write\nR - Read\nD - Delete\nE - Exit\n");
    char input;
    scanf("%s", &input);

    if (input == 'E') {
      printf("Exiting program...\n");
      break;
    }

    switch (input) {
    // READ
    case 'R': {
      // TODO: read specific word from disk
      for (int i = 0; i < DISK_SIZE; i++) {
        printf("%d:%c ", i, disk[i].data);
      }
      break;
    }
    // WRITE
    case 'W': {
      printf("Qual palavra você quer escrever? ");
      char file[DISK_SIZE];
      scanf("%s", file);
      size_t file_length = strlen(file);

      if (has_not_enough_space_on_disk(bitmap, file_length)) {
        printf("Insufficient memory.\n");
        break;
      }

      int previous_block_index =
          get_next_free_block_index_from_bitmap(bitmap, 0);
      bitmap[previous_block_index] = 0;
      disk[previous_block_index].data = file[previous_block_index];

      for (size_t i = 1; i < strlen(file); i++) {
        int current_free_block_index =
            get_next_free_block_index_from_bitmap(bitmap, i);
        bitmap[current_free_block_index] = 0;
        disk[current_free_block_index].data = file[current_free_block_index];
        disk[previous_block_index].next = current_free_block_index;
        previous_block_index = current_free_block_index;
      }
      break;
    }
    // DELETE
    case 'D': {
      printf("DELETE WORD\n");
      // TODO: delete word
      break;
    }
    default: {
      printf("Invalid command");
      break;
    }
    }
  }

  free(bitmap);
  free(disk); // NOTE: Na prática, você não iria desalocar o disco, obviamente
  return 0;
}
