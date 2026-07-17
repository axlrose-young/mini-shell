#ifndef TOKENIZER_H
#define TOKENIZER_H

#define ARG_MAX 256

typedef struct{
	char* cmds[ARG_MAX];
	char* outfile;
	size_t count;
}Pipes;

extern Pipes pipeline[64]; // directly used in tokenizer and main

void tokenize(char *input);

#endif
