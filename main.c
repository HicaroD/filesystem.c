#include "bitmap.h"
#include "block.h"
#include "directory.h"
#include "file.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

void flush() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int main() {
  block_t *disk = new_disk();
  directory_h *directory = new_directory();
  int *bitmap = get_bitmap();

  while (1) {
    printf("Escolha um comando: \nW - Write\nR - Read\nD - Delete\nE - Exit\n");
    char input;
    scanf("%s", &input);
    flush();

    if (input == 'E') {
      printf("Exiting program...\n");
      break;
    }

    switch (input) {
    // DEBUGGING
    case 'S': {
      printf("Disco:\n");
      for (int i = 0; i < DISK_SIZE; i++) {
        printf("[%c:%d] ", disk[i].data, disk[i].next);
      }
      printf("\n");

      printf("\n\nDiretórios:\n");
      for (size_t i = 0; i < directory->size; i++) {
        const file_t current_file = directory->files[i];
        printf("%c:%d ", *current_file.filename, current_file.file_start_index);
      }
      printf("\n");

      printf("\n\nBitmap:\n");
      for (size_t i = 0; i < DISK_SIZE; i++) {
        printf("%d", bitmap[i]);
      }
      printf("\n");
      break;
    }
    // READ
    case 'R': {
      printf("Qual arquivo você quer procurar? ");
      char *file = (char *)malloc(sizeof(char) * DISK_SIZE);
      if (file == NULL) {
        fprintf(stderr, "Incapaz de alocar memória para receber input\n");
        return EXIT_FAILURE;
      }
      scanf("%32[^\n]", file);

      printf("Procurando pelo arquivo: ");
      for (size_t i = 0; i < strlen(file); i++) {
        printf("%c", file[i]);
      }

      int file_found = 0;

      for (size_t i = 0; i < directory->size; i++) {
        file_t current_file = directory->files[i];

        if (strcmp(current_file.filename, file) == 0) {
          file_found = 1;
          size_t file_length = strlen(current_file.filename);
          printf("\nArquivo encontrado! Resultado: ");
          for (size_t j = 0; j < file_length; j++) {
            printf("%c", current_file.filename[j]);
          }
          printf("\n");
          break;
        }
      }

      if (!file_found) {
        printf("\nArquivo não encontrado!\n");
      }
      break;
    }
    // WRITE
    case 'W': {
      printf("Qual arquivo você quer escrever? ");
      char *file = (char *)malloc(sizeof(char) * DISK_SIZE);

      if (file == NULL) {
        fprintf(stderr, "Incapaz de alocar memória para receber input\n");
        return EXIT_FAILURE;
      }

      scanf("%32[^\n]", file);
      flush();

      size_t file_length = strlen(file);

      if (has_not_enough_space_on_disk(bitmap, file_length)) {
        printf("Insufficient memory.\n");
        break;
      }

      int previous_block_index = get_next_free_block_index_from_bitmap(bitmap);
      int file_start_index = previous_block_index;

      bitmap[previous_block_index] = 0;
      disk[previous_block_index].data = file[0];

      for (size_t i = 1; i < file_length; i++) {
        int current_free_block_index =
            get_next_free_block_index_from_bitmap(bitmap);
        bitmap[current_free_block_index] = 0;
        disk[current_free_block_index].data = file[i];
        disk[previous_block_index].next = current_free_block_index;
        previous_block_index = current_free_block_index;
      }

      file_t *current_file = new_file(file, file_length, file_start_index);
      append_file_to_directory(directory, current_file);
      break;
    }
    // DELETE
    case 'D': {
      printf("Qual arquivo você quer remover? ");
      char *file_to_be_removed = (char *)malloc(sizeof(char) * DISK_SIZE);
      if (file_to_be_removed == NULL) {
        fprintf(stderr, "Incapaz de alocar memória para receber input\n");
        return EXIT_FAILURE;
      }

      scanf("%32[^\n]", file_to_be_removed);
      flush();

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
          // NOTA: Garantido que última letra também será removida
          bitmap[disk_pointer] = 1;
          remove_file_from_directory(directory, directory->files[i]);
          break;
        }
      }
      free(file_to_be_removed);
      break;
    }
    default: {
      printf("Comando invalido");
      break;
    }
    }
  }

  free(bitmap);
  free(disk); // NOTE: Na prática, você não iria desalocar o disco, obviamente
  return EXIT_SUCCESS;
}
