main: main.c
	g++ -Wall -Wextra -Wfloat-equal -Werror -o filesystem main.c
	./filesystem

clean:
	rm filesystem
