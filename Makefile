CC=cc
CFLAGS=-O3 -Wall -Wextra -Wfloat-equal -Werror -o filesystem
SOURCE_FILES=main.c

main: $(SOURCE_FILES)
	$(CC) $(CFLAGS) $(SOURCE_FILES)
	./filesystem

clean:
	rm filesystem
