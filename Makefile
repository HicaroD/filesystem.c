main: main.c
	gcc -Wall -Wextra -Wfloat-equal -Werror -o filesystem main.c
	./filesystem

clean:
	rm filesystem
