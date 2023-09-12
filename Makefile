main: main.c
	g++ -O3 -Wall -Wextra -Wfloat-equal -Werror -o filesystem main.c
	./filesystem

clean:
	rm filesystem
