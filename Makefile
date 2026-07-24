all:
	gcc -Wall -Wextra -o shell main.c tokenizer.c executor.c 
clean:
	rm shell

