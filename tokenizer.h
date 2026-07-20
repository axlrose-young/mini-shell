#ifndef TOKENIZER_H
#define TOKENIZER_H

#define ARG_MAX 256

typedef struct{
	char* cmds[ARG_MAX];
	char* outfile;
	size_t count;
}Pipes;

size_t tokenize(char *input, Pipes* p);

#endif
