all:
	gcc -Wall -Wextra -o shell main.c tokenizer.c builtin.c executor.c
clean:
	gcc -o shell main.c tokenizer.c builtin.c executor.c
