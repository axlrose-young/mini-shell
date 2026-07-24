release:
	gcc -O2 -o shell main.c tokenizer.c executor.c 
all:
	gcc -Wall -Wextra -g -o shell main.c tokenizer.c executor.c 
clean:
	rm shell
