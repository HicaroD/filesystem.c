main: main.c
	cc -O3 -Wall -Wextra -Wfloat-equal -Werror -o filesystem main.c
	./filesystem

clean:
	rm filesystem
