.PHONY: all clean debug

CC=gcc
CFLAGS= -Wall -Wextra -O2 
DEBUG= -Wall -Wextra -O0 -g

all: shell

shell: main.c tokenizer.c executor.c 
	$(CC) $(CFLAGS) $^ -o $@ 

debug: main.c tokenizer.c executor.c
	$(CC) $(DEBUG) $^ -o shell 

clean:
	rm -f shell
