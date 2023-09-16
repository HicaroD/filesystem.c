#include "bitmap.h"
#include "block.h"
#include "directory.h"
#include "file.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

int main() {
  block_t *disk = new_disk();
  directory_h *directory = new_directory();
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
        printf("%d:%c:%d ", i, disk[i].data, disk[i].next);
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

      file_t current_file = {file, previous_block_index};
      append_file_to_directory(directory, current_file);

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
      printf("Qual palavra você quer remover? ");
      char file_to_be_removed[DISK_SIZE];
      scanf("%s", file_to_be_removed);

      printf("Arquivo escolhido para ser removido: ");
      for (size_t i = 0; i < strlen(file_to_be_removed); i++) {
        printf("%c", file_to_be_removed[i]);
      }

      for (size_t i = 0; i < directory->size; i++) {
        const char *current_filename = directory->files[i].filename;
        int current_file_start_index = directory->files[i].file_start_index;

        if (strcmp(file_to_be_removed, current_filename) == 0) {
          printf("\nArquivo foi encontrado e será marcado para remoção no "
                 "bitmap.\n");
          size_t disk_pointer = current_file_start_index;
          while (disk[disk_pointer].next != -1) {
            printf("Setando índice %lu para livre\n", disk_pointer);
            bitmap[disk_pointer] = 1;
            disk_pointer = disk[disk_pointer].next;
          }
          remove_file_from_directory(directory, directory->files[i]);
          break;
        }
      }
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
